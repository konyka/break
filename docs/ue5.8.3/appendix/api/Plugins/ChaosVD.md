# Plugins / ChaosVD

- module root: `Plugins/ChaosVD/Source/ChaosVD`
- headers: 145; symbols: 3357
- symbol kinds: class=175, delegate=37, enum=42, enumerator=210, externvar=7, function=477, macro=8, member=864, namespace=81, prototype=1370, struct=65, typedef=13, variable=8
- PrivateDependencyModuleNames: ApplicationCore, ChaosSolverEngine, ChaosVDData, ChaosVDRuntime, CommonMenuExtensions, CoreUObject, DesktopPlatform, DynamicMesh, EditorFramework, EditorWidgets, Engine, GeometryCore, GeometryFramework, InputCore, MeshConversion, MeshDescription, OutputLog, Projects, PropertyEditor, RenderCore, SceneOutliner, Slate, SlateCore, Sockets, StaticMeshDescription, StatusBar, SubobjectDataInterface, SubobjectEditor, TedsOutliner, ToolMenus, TraceAnalysis, TraceBasedDebuggers, TraceBasedDebuggersAnalysis, TraceInsights, TraceLog, TraceServices, TypedElementFramework, TypedElementRuntime, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/ChaosVD/Source/ChaosVD/Private/Actors/ChaosVDGameFrameInfoActor.h` (Private)


#### class `AChaosVDGameFrameInfoActor`  
`class AChaosVDGameFrameInfoActor : public AChaosVDDataContainerBaseActor`  
_L16-22_
- reflection: `UCLASS(NotBlueprintable, NotPlaceable)`
- inherits: `AChaosVDDataContainerBaseActor`
- desc: Actor that contains game frame related data
- L21 _public prototype_ `AChaosVDGameFrameInfoActor();`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Actors/ChaosVDGeometryContainer.h` (Private)


#### class `AChaosVDGeometryContainer`  
`class AChaosVDGeometryContainer : public AActor`  
_L14-35_
- reflection: `UCLASS()`
- inherits: `AActor`
- desc: Actor that contains Static Mesh Components used to visualize the geometry we generated from the recorded data
- L19 _public prototype_ `AChaosVDGeometryContainer();`
- L21 _public function_ `virtual void SetScene(TWeakPtr<FChaosVDScene> InScene)`
- L26 _public function_ `TSharedPtr<FChaosVDScene> GetScene() const`
- L31 _public prototype_ `void CleanUp();`
- L34 _protected member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Actors/ChaosVDSolverInfoActor.h` (Private)


#### class `AChaosVDSolverInfoActor`  
`class AChaosVDSolverInfoActor : public AChaosVDDataContainerBaseActor, public FChaosVDSceneSelectionObserver`  
_L28-133_
- reflection: `UCLASS(NotBlueprintable, NotPlaceable)`
- inherits: `AChaosVDDataContainerBaseActor,FChaosVDSceneSelectionObserver`
- desc: Actor that contains all relevant data for the current visualized solver frame
- L34 _public prototype_ `AChaosVDSolverInfoActor();`
- L36 _public prototype_ `void SetSolverName(const FName& InSolverName);`
- L37 _public function_ `const FName& GetSolverName()`
- L42 _public function_ `void SetIsServer(bool bInIsServer)`
- L47 _public function_ `bool GetIsServer() const`
- L53 _public prototype_ `virtual void UpdateFromNewGameFrameData(const FChaosVDGameFrameData& InGameFrameData) override;`
- L55 _public prototype_ `virtual void UpdateFromNewSolverFrameData(const FChaosVDSolverFrameData& InSolverFrameData) override;`
- L57 _public prototype_ `virtual void SetScene(TWeakPtr<FChaosVDScene> InScene) override;`
- L59 _public function_ `void SetSimulationTransform(const FTransform& InSimulationTransform)`
- L63 _public function_ `virtual const FTransform& GetSimulationTransform() const override`
- L68 _public function_ `UChaosVDSolverCollisionDataComponent* GetCollisionDataComponent()`
- L73 _public function_ `UChaosVDParticleDataComponent* GetParticleDataComponent()`
- L78 _public function_ `UChaosVDSolverCharacterGroundConstraintDataComponent* GetCharacterGroundConstraintDataComponent()`
- L83 _public function_ `UChaosVDSceneQueryDataComponent* GetSceneQueryDataComponent() const`
- L88 _public prototype_ `virtual FName GetCustomIconName() const override;`
- L90 _public prototype_ `TSharedPtr<FChaosVDSceneParticle> GetParticleInstance(int32 ParticleID) const;`
- L92 _public prototype_ `virtual bool IsVisible() const override;`
- L95 _public prototype_ `void SetIsTemporarilyHiddenInEditor(bool bIsHidden) override;`
- L103 _protected prototype_ `void FindAndUpdateFromCorrectGameFrameData(const FChaosVDSolverFrameData& InSolverFrameData);` — Finds the correct game frame data and executes the update flow for it based on the provided solver frame timing data. @param InSolverFrameData Solver frame data where to get the timing data from
- L106 _protected member_ `FTransform SimulationTransform;` — `UPROPERTY(VisibleAnywhere, Category="Solver Data")`
- L109 _protected member_ `FName SolverName;` — `UPROPERTY(VisibleAnywhere, Category="Solver Data")`
- L112 _protected member_ `TObjectPtr<UChaosVDSolverCollisionDataComponent> CollisionDataComponent;` — `UPROPERTY()`
- L114 _protected member_ `bool bIsServer;`
- L117 _protected member_ `TObjectPtr<UChaosVDParticleDataComponent> ParticleDataComponent;` — `UPROPERTY()`
- L120 _protected member_ `TObjectPtr<UChaosVDSolverJointConstraintDataComponent> JointsDataComponent;` — `UPROPERTY()`
- L123 _protected member_ `TObjectPtr<UChaosVDSolverCharacterGroundConstraintDataComponent> CharacterGroundConstraintDataComponent;` — `UPROPERTY()`
- L126 _protected member_ `TObjectPtr<UChaosVDSceneQueryDataComponent> SceneQueryDataComponent;` — `UPROPERTY()`
- L129 _protected member_ `TObjectPtr<UChaosVDAdditionalGTDataRouterComponent> GTDataReRouteComponent;` — `UPROPERTY()`
- L132 _protected member_ `TObjectPtr<UChaosVDParticleExtraDataComponent> ParticleExtraDataComponent;` — `UPROPERTY()`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDCollisionDataDetailsTab.h` (Private)


#### class `FChaosVDCollisionDataDetailsTab`  
`class FChaosVDCollisionDataDetailsTab : public FChaosVDTabSpawnerBase`  
_L12-29_
- inherits: `FChaosVDTabSpawnerBase`
- L15 _public function_ `FChaosVDCollisionDataDetailsTab(const FName& InTabID, const TSharedPtr<FTabManager>& InTabManager, const TWeakPtr<SChaosVDMainTab>& InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget)`
- L21 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`
- L22 _public prototype_ `virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed) override;`
- L24 _public function_ `TWeakPtr<SChaosVDCollisionDataInspector> GetCollisionInspectorInstance() const`
- L28 _protected member_ `TSharedPtr<SChaosVDCollisionDataInspector> CollisionDataInspector;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDCommands.h` (Private)


#### class `FChaosVDCommands`  
`class FChaosVDCommands : public TCommands<FChaosVDCommands>`  
_L8-39_
- inherits: `TCommands<FChaosVDCommands>`
- L12 _public prototype_ `FChaosVDCommands();`
- L15 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L18 _public member_ `TSharedPtr<FUICommandInfo> ToggleFollowSelectedObject;` — Viewport Commands
- L19 _public member_ `TSharedPtr<FUICommandInfo> OverridePlaybackFrameRate;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> AllowTranslucentSelection;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> DeselectAll;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> HideSelected;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ShowAll;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> OpenFile;` — Main Toolbar Commands
- L27 _public member_ `TSharedPtr<FUICommandInfo> BrowseLiveSessions;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> DisconnectFromLiveSession;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> CombineOpenFiles;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> OpenSceneQueryBrowser;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> PlayPauseTrack;` — Playback Controls commands
- L34 _public member_ `TSharedPtr<FUICommandInfo> StopTrack;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> NextFrame;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> PrevFrame;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> NextStage;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> PrevStage;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDConstraintDataInspectorTab.h` (Private)


#### class `FChaosVDConstraintDataInspectorTab`  
`class FChaosVDConstraintDataInspectorTab final : public FChaosVDTabSpawnerBase`  
_L12-28_
- inherits: `FChaosVDTabSpawnerBase`
- desc: Spawns and handles and instance for the visual debugger Constraints Inspector tab
- L15 _public function_ `FChaosVDConstraintDataInspectorTab(const FName& InTabID, const TSharedPtr<FTabManager>& InTabManager, const TWeakPtr<SChaosVDMainTab>& InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget)`
- L21 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`
- L22 _public prototype_ `virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed) override;`
- L24 _public function_ `TWeakPtr<SChaosVDConstraintDataInspector> GetConstraintDataInspectorInstance() const`
- L27 _protected member_ `TSharedPtr<SChaosVDConstraintDataInspector> ConstraintDataInspector;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDConvexMeshGenerator.h` (Private)


#### class `FChaosVDConvexMeshGenerator`  
`class FChaosVDConvexMeshGenerator : public UE::Geometry::FMeshShapeGenerator`  
_L15-29_
- inherits: `UE::Geometry::FMeshShapeGenerator`
- desc: Generates an convex mesh with the smallest number of triangles possible
- L22 _public prototype_ `void GenerateFromConvex(const Chaos::FConvex& Convex);` — Prepares the Mesh Generator so the Generate method can generate the desired Dynamic Mesh @param Convex shape data used to generate the dynamic mesh
- L24 _public prototype_ `virtual FMeshShapeGenerator& Generate() override;`
- L28 _private member_ `bool bIsGenerated = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDEditorMode.h` (Private)


#### class `FChaosVDEdModeWidgetHelper`  
`class FChaosVDEdModeWidgetHelper final : public FLegacyEdModeWidgetHelper`  
_L15-25_
- inherits: `FLegacyEdModeWidgetHelper`
- desc: LegacyEdModeWidgetHelper implementation for the Chaos Visual Debugger tool
- L18 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L19 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L20 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override;`
- L21 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L24 _private prototype_ `AActor* GetCurrentSelectedActor() const;`

#### class `UChaosVDEditorMode`  
`class UChaosVDEditorMode : public UBaseLegacyWidgetEdMode`  
_L31-55_
- reflection: `UCLASS()`
- inherits: `UBaseLegacyWidgetEdMode`
- desc: Main Editor Mode for the Chaos Visual Debugger tool.
- L36 _public prototype_ `UChaosVDEditorMode();`
- L38 _public function_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override`
- L40 _public member_ `static const FEditorModeID EM_ChaosVisualDebugger;`
- L42 _public function_ `virtual bool UsesToolkits() const override`
- L44 _public prototype_ `virtual bool CanAutoSave() const override;`
- L46 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L48 _public function_ `void SetWorld(UWorld* InWorld)`
- L52 _protected prototype_ `virtual TSharedRef<FLegacyEdModeWidgetHelper> CreateWidgetHelper() override;`
- L54 _protected member_ `TWeakObjectPtr<UWorld> CVDWorldPtr;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDEditorModeTools.h` (Private)


#### class `FChaosVDEditorModeTools`  
`class FChaosVDEditorModeTools : public FEditorModeTools`  
_L9-26_
- inherits: `FEditorModeTools`
- desc: Editor Mode tools for the Chaos Visual Debugger tool
- L12 _public prototype_ `FChaosVDEditorModeTools(const TWeakPtr<FChaosVDScene>& InScenePtr);`
- L14 _public prototype_ `virtual FString GetReferencerName() const override;`
- L15 _public prototype_ `virtual USelection* GetSelectedActors() const override;`
- L16 _public prototype_ `virtual USelection* GetSelectedObjects() const override;`
- L17 _public prototype_ `virtual USelection* GetSelectedComponents() const override;`
- L18 _public prototype_ `virtual UTypedElementSelectionSet* GetEditorSelectionSet() const override;`
- L19 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L22 _public function_ `TWeakPtr<FChaosVDScene> GetScene() const` — Returns the Chaos Visual Debugger Scene
- L25 _protected member_ `TWeakPtr<FChaosVDScene> ScenePtr;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDHeightfieldMeshGenerator.h` (Private)


#### class `FChaosVDHeightFieldMeshGenerator`  
`class FChaosVDHeightFieldMeshGenerator : public UE::Geometry::FMeshShapeGenerator`  
_L15-30_
- inherits: `UE::Geometry::FMeshShapeGenerator`
- desc: Generates an dynamic mesh using the data stored in a FHeightField implicit object
- L22 _public prototype_ `void GenerateFromHeightField(const Chaos::FHeightField& InHeightField);` — Prepares the Mesh Generator so the Generate method can generate the desired Dynamic Mesh @param InHeightField Implicit object used to generate the dynamic mesh
- L24 _public prototype_ `virtual FMeshShapeGenerator& Generate() override;`
- L27 _private prototype_ `void AppendTriangle(const Chaos::TVec2<Chaos::FReal>& InCellCoordinates, const UE::Geometry::FIndex3i& InTriangle, const Chaos::FHeightField& InHeightField, int32 PolygonID, int32 TriangleIndex);`
- L29 _private member_ `bool bIsGenerated = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDIndependentDetailsPanelManager.h` (Private)


#### class `FChaosVDIndependentDetailsPanelManager`  
`class FChaosVDIndependentDetailsPanelManager : public TSharedFromThis<FChaosVDIndependentDetailsPanelManager>`  
_L14-29_
- inherits: `TSharedFromThis<FChaosVDIndependentDetailsPanelManager>`
- desc: Manager class that handles any selection independent details panel tab.
- L17 _public prototype_ `FChaosVDIndependentDetailsPanelManager(const TSharedRef<SChaosVDMainTab>& InMainTab);`
- L20 _public prototype_ `TSharedPtr<FChaosVDStandAloneObjectDetailsTab> GetAvailableStandAloneDetailsPanelTab();` — Returns a shared ptr to a new selection independent details panel tab or null if no panels are available
- L24 _private prototype_ `void HandleTabDestroyed(TSharedRef<SDockTab> Tab, FName TabID);`
- L26 _private member_ `TArray<FName> AvailableDetailsPanelIDs;`
- L28 _private member_ `TWeakPtr<SChaosVDMainTab> MainTab;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDMeshComponentPool.h` (Private)


#### class `FChaosVDMeshComponentPool`  
`class FChaosVDMeshComponentPool : public FGCObject`  
_L10-39_
- inherits: `FGCObject`
- L14 _public prototype_ `FChaosVDMeshComponentPool();`
- L16 _public function_ `virtual FString GetReferencerName() const override`
- L21 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L24 _public prototype_ `template<typename TMeshComponent> TMeshComponent* AcquireMeshComponent(UObject* Outer, FName Name);`
- L26 _public prototype_ `void DisposeMeshComponent(UMeshComponent* MeshComponent);`
- L28 _public prototype_ `UMaterialInterface* GetMaterialForType(EChaosVDMaterialType Type);`
- L32 _private member_ `TChaosVDObjectPool<UChaosVDStaticMeshComponent> StaticMeshComponentPool;`
- L33 _private member_ `TChaosVDObjectPool<UChaosVDInstancedStaticMeshComponent> InstancedStaticMeshComponentPool;`
- L35 _private member_ `TObjectPtr<UMaterialInterface> CachedISMCOpaqueMaterialBase;`
- L36 _private member_ `TObjectPtr<UMaterialInterface> CachedISMCTranslucentBase;`
- L37 _private member_ `TObjectPtr<UMaterialInterface> CachedStaticMeshComponentTranslucentMaterialBase;`
- L38 _private member_ `TObjectPtr<UMaterialInterface> CachedStaticMeshComponentOpaqueMaterialBase;`
- L42 _function_ `template <typename TMeshComponent> TMeshComponent* FChaosVDMeshComponentPool::AcquireMeshComponent(UObject* Outer, FName Name)`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDObjectPool.h` (Private)


#### struct `FChaosVDObjectPoolCVars`  
`struct FChaosVDObjectPoolCVars`  
_L16-20_
- L18 _public member_ `static bool bUseObjectPool;`
- L19 _public member_ `static FAutoConsoleVariableRef CVarUseObjectPool;`

#### class `TChaosVDObjectPool`  
`template<typename ObjectType> class TChaosVDObjectPool : public FGCObject, public FTSTickerObjectBase`  
_L24-57_
- inherits: `FGCObject,FTSTickerObjectBase`
- desc: Basic Pool system for UObjects
- L27 _public prototype_ `TChaosVDObjectPool() = default;`
- L30 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L32 _public function_ `void SetPoolName(const FString& InName)`
- L34 _public function_ `virtual FString GetReferencerName() const override`
- L39 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L41 _public prototype_ `ObjectType* AcquireObject(UObject* Outer, FName Name);`
- L43 _public prototype_ `void DisposeObject(UObject* Object);`
- L45 _public member_ `TFunction<ObjectType*(UObject*,FName)> ObjectFactoryOverride;`
- L48 _protected prototype_ `void DestroyUObject(UObject* Object);`
- L50 _protected member_ `FString PoolName = TEXT("Cha`
- L51 _protected member_ `int32 PoolHits = 0;`
- L52 _protected member_ `int32 PoolRequests = 0;`
- L53 _protected member_ `std::atomic<bool> bGrowingPoolInBackground = false;`
- L54 _protected member_ `std::atomic<int32> PoolSize = 0;`
- L55 _protected member_ `FRWLock PoolLock;`
- L56 _protected member_ `TArray<TObjectPtr<ObjectType>> PooledObjects;`
- L60 _function_ `template <typename ObjectType> TChaosVDObjectPool<ObjectType>::~TChaosVDObjectPool()`
- L78 _function_ `template <typename ObjectType> void TChaosVDObjectPool<ObjectType>::AddReferencedObjects(FReferenceCollector& Collector)`
- L84 _function_ `template <typename ObjectType> bool TChaosVDObjectPool<ObjectType>::Tick(float DeltaTime)`
- L136 _function_ `template <typename ObjectType> ObjectType* TChaosVDObjectPool<ObjectType>::AcquireObject(UObject* Outer, FName Name)`
- L188 _function_ `template <typename ObjectType> void TChaosVDObjectPool<ObjectType>::DisposeObject(UObject* Object)`
- L217 _function_ `template <typename ObjectType> void TChaosVDObjectPool<ObjectType>::DestroyUObject(UObject* Object)`

#### Free symbols / members of external scopes

- L91 _function_ `` (scope `TChaosVDObjectPool::Tick`)
- L123 _function_ `` (scope `TChaosVDObjectPool::Tick::__anon847a978e0102`)

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDOutputLogTab.h` (Private)


#### class `FChaosVDOutputLogTab`  
`class FChaosVDOutputLogTab : public FChaosVDTabSpawnerBase, public TSharedFromThis<FChaosVDOutputLogTab>`  
_L13-26_
- inherits: `FChaosVDTabSpawnerBase,TSharedFromThis<FChaosVDOutputLogTab>`
- desc: Spawns and handles and instance for the visual debugger Output Panel
- L17 _public function_ `FChaosVDOutputLogTab(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget)`
- L21 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`
- L24 _private member_ `TSharedPtr<FOutputLogHistory> OutputLogHistory;`
- L25 _private member_ `TSharedPtr<SOutputLog> OutputLog;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDPlaybackControllerInstigator.h` (Private)


#### class `IChaosVDPlaybackControllerInstigator`  
`class IChaosVDPlaybackControllerInstigator`  
_L7-19_
- desc: Common interface for any object that alters a ChaosVDPlaybackController
- L10 _public function_ `IChaosVDPlaybackControllerInstigator() : ID(FGuid::NewGuid())`
- L14 _public member_ `static FGuid InvalidGuid;`
- L16 _public function_ `const FGuid& GetInstigatorID() const`
- L18 _private member_ `FGuid ID;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDPlaybackControllerObserver.h` (Private)


#### class `FChaosVDPlaybackControllerObserver`  
`class FChaosVDPlaybackControllerObserver : public FChaosVDSceneSelectionObserver`  
_L17-34_
- inherits: `FChaosVDSceneSelectionObserver`
- desc: Class to be used as base to any object that needs to Process Player Controller changes, and scene Selection Changes
- L24 _public prototype_ `TWeakPtr<FChaosVDPlaybackController> GetObservedController();` — Returns a Weak Ptr to the Playback Controller we are currently observing
- L27 _protected prototype_ `virtual void RegisterNewController(TWeakPtr<FChaosVDPlaybackController> NewController);`
- L28 _protected function_ `virtual void HandlePlaybackControllerDataUpdated(TWeakPtr<FChaosVDPlaybackController> InController)`
- L29 _protected function_ `virtual void HandleControllerTrackFrameUpdated(TWeakPtr<FChaosVDPlaybackController> InController, TWeakPtr<const FChaosVDTrackInfo> UpdatedTrackInfo, FGuid InstigatorGuid)`
- L31 _protected function_ `virtual void HandlePostSelectionChange(const UTypedElementSelectionSet* ChangesSelectionSet) override`
- L33 _protected member_ `TWeakPtr<FChaosVDPlaybackController> PlaybackController;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDPlaybackViewportTab.h` (Private)


#### class `FChaosVDPlaybackViewportTab`  
`class FChaosVDPlaybackViewportTab : public FChaosVDTabSpawnerBase, public TSharedFromThis<FChaosVDPlaybackViewportTab>`  
_L14-29_
- inherits: `FChaosVDTabSpawnerBase,TSharedFromThis<FChaosVDPlaybackViewportTab>`
- desc: Spawns and handles and instance for the visual debugger Playback viewport tab It contains the Playback controls and the 3D viewport
- L17 _public function_ `FChaosVDPlaybackViewportTab(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget)`
- L21 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`
- L23 _public prototype_ `virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed) override;`
- L25 _public function_ `TWeakPtr<SChaosVDPlaybackViewport> GetPlaybackViewportWidget()`
- L28 _protected member_ `TSharedPtr<SChaosVDPlaybackViewport> PlaybackViewportWidget;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDRecordedLogTab.h` (Private)


#### class `FChaosVDRecordedLogTab`  
`class FChaosVDRecordedLogTab : public FChaosVDTabSpawnerBase, public TSharedFromThis<FChaosVDRecordedLogTab>`  
_L13-22_
- inherits: `FChaosVDTabSpawnerBase,TSharedFromThis<FChaosVDRecordedLogTab>`
- desc: Spawns and handles and instance for the visual debugger Recorded Output Panel
- L17 _public function_ `FChaosVDRecordedLogTab(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget)`
- L21 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDSceneParticleCustomization.h` (Private)


#### class `FChaosVDSceneParticleCustomization`  
`class FChaosVDSceneParticleCustomization : public IDetailCustomization`  
_L19-80_
- inherits: `IDetailCustomization`
- desc: Custom details panel for the ChaosVD Particle Actor
- L22 _public prototype_ `FChaosVDSceneParticleCustomization(const TWeakPtr<SChaosVDMainTab>& InMainTab);`
- L25 _public member_ `inline static FName ParticleDataCategoryName = FName("Par`
- L26 _public member_ `inline static FName GeometryCategoryName = FName("Geo`
- L28 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<SChaosVDMainTab> InMainTab);`
- L30 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L34 _private prototype_ `void AddParticleDataButtons(IDetailLayoutBuilder& DetailBuilder);`
- L37 _private prototype_ `template<typename TStruct> TSharedPtr<IPropertyHandle> AddExternalStructure(TStruct& CachedStruct, IDetailLayoutBuilder& DetailBuilder, FName CategoryName, const FText& InPropertyName);`
- L39 _private member_ `TSet<FName> AllowedCategories;`
- L40 _private member_ `FChaosVDSceneParticle* CurrentObservedParticle = nullptr;`
- L41 _private member_ `TSharedPtr<FStructOnScope> CurrentlyObserverParticleDataStruct;`
- L43 _private prototype_ `void ResetCachedView();`
- L45 _private prototype_ `void RegisterCVDScene(const TSharedPtr<FChaosVDScene>& InScene);`
- L47 _private prototype_ `void HandleSceneUpdated();`
- L49 _private prototype_ `bool GetCollisionDataButtonEnabled() const;`
- L51 _private prototype_ `FReply ShowCollisionDataForSelectedObject();`
- L52 _private prototype_ `FReply OpenNewDetailsPanel();`
- L54 _private prototype_ `TSharedPtr<SWidget> GenerateShowCollisionDataButton();`
- L55 _private prototype_ `TSharedPtr<SWidget> GenerateOpenInNewDetailsPanelButton();`
- L57 _private prototype_ `void UpdateObserverParticlePtr(FChaosVDSceneParticle* NewObservedParticle);`
- L59 _private prototype_ `void HandleObservedParticleInstanceDestroyed();`
- L62 _private member_ `FChaosVDParticleDataWrapper CachedParticleData;` — Copy of the last known geometry shape data structure of a selected particle and mesh instance -  Used to avoid rebuild the layout every time we change frame in CVD
- L64 _private member_ `FChaosVDMeshDataInstanceState CachedGeometryDataInstanceCopy;` — Copy of the last known particle data structure of a selected particle -  Used to avoid rebuild the layout every time we change frame in CVD
- L66 _private member_ `FChaosVDParticleMetadata CachedParticleMetadata;` — Copy of the last known particle metadata data structure of a selected particle -  Used to avoid rebuild the layout every time we change frame in CVD
- L68 _private member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr = nullptr;`
- L70 _private member_ `TWeakPtr<SChaosVDMainTab> MainTabWeakPtr = nullptr;`
- L75 _private member_ `IDetailLayoutBuilder* CachedDetailBuilder = nullptr;` — Cached builder pointer used to trigger a ForceRefreshDetails if an extra data subscriber reports a layout mismatch during an in-place refresh. Nulled before the call to avoid dangling use if the rebuild is synchronous.
- L79 _private member_ `bool bIsInsideCustomizeDetails = false;` — Guard that prevents HandleSceneUpdated from issuing a ForceRefreshDetails while CustomizeDetails is already on the call stack, avoiding an infinite rebuild loop.
- L83 _function_ `template <typename TStruct> TSharedPtr<IPropertyHandle> FChaosVDSceneParticleCustomization::AddExternalStructure(TStruct& CachedStruct, IDetailLayoutBuilder& DetailBuilder, FName CategoryName, const FText& InPropertyName)`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDSceneQueryDataInspectorTab.h` (Private)


#### class `FChaosVDSceneQueryDataInspectorTab`  
`class FChaosVDSceneQueryDataInspectorTab : public FChaosVDTabSpawnerBase`  
_L11-27_
- inherits: `FChaosVDTabSpawnerBase`
- desc: Spawns and handles and instance for the visual debugger Scene Query Data Inspector tab
- L14 _public function_ `FChaosVDSceneQueryDataInspectorTab(const FName& InTabID, const TSharedPtr<FTabManager>& InTabManager, const TWeakPtr<SChaosVDMainTab>& InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget)`
- L20 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`
- L21 _public prototype_ `virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed) override;`
- L23 _public function_ `TWeakPtr<SChaosVDSceneQueryDataInspector> GetSceneQueryDataInspectorInstance() const`
- L26 _protected member_ `TSharedPtr<SChaosVDSceneQueryDataInspector> SceneQueryDataInspector;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDSelectionCustomization.h` (Private)


#### class `FChaosVDSelectionCustomization`  
`class FChaosVDSelectionCustomization : public FTypedElementSelectionCustomization`  
_L10-22_
- inherits: `FTypedElementSelectionCustomization`
- desc: Customization class used to intercept selection actions and route Selection Events into CVD's Scene
- L13 _public function_ `FChaosVDSelectionCustomization(const TWeakPtr<FChaosVDScene>& InScene) : SceneWeakPtr(InScene)`
- L17 _public prototype_ `virtual bool DeselectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L18 _public prototype_ `virtual bool SelectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L21 _protected member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDSkySphereInterface.h` (Private)


#### class `UChaosVDSkySphereInterface`  
`class UChaosVDSkySphereInterface : public UInterface`  
_L11-14_
- reflection: `UINTERFACE()`
- inherits: `UInterface`

#### class `IChaosVDSkySphereInterface`  
`class IChaosVDSkySphereInterface`  
_L19-29_
- desc: Simple interface to allow update the light source in the BP SkySphere from C++
- L25 _public prototype_ `void SetDirectionalLightSource(ADirectionalLight* NewLightSource);` — `UFUNCTION(BlueprintNativeEvent, CallInEditor)`
- L28 _public prototype_ `void Refresh();` — `UFUNCTION(BlueprintNativeEvent, CallInEditor)`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDSolversTracksTab.h` (Private)


#### class `FChaosVDSolversTracksTab`  
`class FChaosVDSolversTracksTab : public FChaosVDTabSpawnerBase, public TSharedFromThis<FChaosVDSolversTracksTab>`  
_L11-24_
- inherits: `FChaosVDTabSpawnerBase,TSharedFromThis<FChaosVDSolversTracksTab>`
- desc: Spawns and handles and instance for the visual debugger Solvers Tracks tab Which provides playback controls for each recorded solver
- L14 _public function_ `FChaosVDSolversTracksTab(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget)`
- L18 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`
- L20 _public prototype_ `virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed) override;`
- L23 _protected member_ `TSharedPtr<SChaosVDSolverTracks> SolverTracksWidget;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDTriMeshGenerator.h` (Private)


#### class `FChaosVDTriMeshGenerator`  
`class FChaosVDTriMeshGenerator : public UE::Geometry::FMeshShapeGenerator`  
_L13-33_
- inherits: `UE::Geometry::FMeshShapeGenerator`
- desc: Generates a Dynamic mesh based on a Triangle Mesh Implicit object
- L18 _public prototype_ `void GenerateFromTriMesh(const Chaos::FTriangleMeshImplicitObject& InTriMesh);` — Triangle Mesh Implicit object used as data source to generate the dynamic mesh
- L20 _public prototype_ `virtual FMeshShapeGenerator& Generate() override;`
- L25 _private prototype_ `template<typename BufferIndexType> void ProcessTriangles(const TArray<BufferIndexType>& InTriangles, const int32 NumTriangles, const Chaos::FTriangleMeshImplicitObject& InTriMesh);`
- L27 _private member_ `bool bIsGenerated = false;`
- L32 _private member_ `static constexpr int32 MaxElementsNumToProcessInSingleThread = 64;` — Max number of elements after which we will process elements in parallel using worker threads Note: This value is not tuned yet
- L36 _function_ `template <typename BufferIndexType> void FChaosVDTriMeshGenerator::ProcessTriangles(const TArray<BufferIndexType>& InTriangles, const int32 NumTriangles, const Chaos::FTriangleMeshImplicitObject& InTriMesh)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`
- L40 _function_ `` (scope `FChaosVDTriMeshGenerator::ProcessTriangles`)

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDWorldOutlinerMode.h` (Private)


#### struct `FChaosVDParticleOutlinerSelector`  
`struct FChaosVDParticleOutlinerSelector`  
_L18-25_
- desc: Functor which can be used to get actors from a selection including component parents
- L20 _public function_ `FChaosVDParticleOutlinerSelector()`
- L24 _public prototype_ `bool operator()(const TWeakPtr<ISceneOutlinerTreeItem>& Item, FChaosVDSceneParticle*& ParticlePtrOut) const;`

#### struct `FChaosVDActorOutlinerSelector`  
`struct FChaosVDActorOutlinerSelector`  
_L27-34_
- L29 _public function_ `FChaosVDActorOutlinerSelector()`
- L33 _public prototype_ `bool operator()(const TWeakPtr<ISceneOutlinerTreeItem>& Item, AActor*& ActorPtrOut) const;`

#### class `FChaosVDWorldOutlinerMode`  
`class FChaosVDWorldOutlinerMode : public UE::Editor::Outliner::FTedsOutlinerMode, public FChaosVDSceneSelectionObserver`  
_L41-112_
- inherits: `UE::Editor::Outliner::FTedsOutlinerMode,FChaosVDSceneSelectionObserver`
- desc: Scene outliner mode used to represent a CVD (Chaos Visual Debugger) world It has a more limited view compared to the normal outliner, hiding features we don't support, and it is integrated with the CVD local selection system
- L45 _public prototype_ `FChaosVDWorldOutlinerMode(const UE::Editor::Outliner::FTedsOutlinerParams& InModeParams, TWeakPtr<FChaosVDScene> InScene, TWeakPtr<FChaosVDPlaybackController> InPlaybackController);`
- L49 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L50 _public prototype_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override;`
- L52 _public function_ `virtual void CreateViewContent(FMenuBuilder& MenuBuilder) override`
- L57 _public function_ `virtual bool ShouldShowFolders() const override`
- L62 _public prototype_ `virtual bool CanInteract(const ISceneOutlinerTreeItem& Item) const override;`
- L63 _public prototype_ `virtual bool CanPopulate() const override;`
- L66 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L70 _public function_ `virtual bool CanSupportDragAndDrop() const override`
- L75 _public function_ `virtual TSharedPtr<SWidget> CreateContextMenu() override`
- L80 _public prototype_ `void OnDataStorageUpdateCompleted();`
- L82 _public function_ `virtual bool ShowStatusBar() const override`
- L87 _public prototype_ `virtual FText GetStatusText() const override;`
- L89 _public prototype_ `virtual FSlateColor GetStatusTextColor() const override;`
- L93 _private prototype_ `virtual void HandlePostSelectionChange(const UTypedElementSelectionSet* ChangesSelectionSet) override;`
- L100 _private prototype_ `void ProcessPendingActionsList(double TimeBudgetInSeconds, TSet<UE::Editor::DataStorage::RowHandle>& PendingItemsToProcess, EPendingOperationType Type);`
- L102 _private member_ `TSet<UE::Editor::DataStorage::RowHandle> RowsPendingRemoval;`
- L103 _private member_ `TSet<UE::Editor::DataStorage::RowHandle> RowsPendingAddition;`
- L105 _private member_ `UE::Editor::DataStorage::QueryHandle CustomRowAdditionQueryHandle;`
- L106 _private member_ `UE::Editor::DataStorage::QueryHandle CustomRowRemovalQueryHandle;`
- L108 _private member_ `TWeakPtr<FChaosVDScene> CVDScene;`
- L109 _private member_ `TWeakPtr<FChaosVDPlaybackController> PlaybackController;`
- L111 _private member_ `TMap<FSceneOutlinerTreeItemID, FSceneOutlinerHierarchyChangedData> PendingOutlinerEventsMap;`

#### enum `FChaosVDWorldOutlinerMode::EPendingOperationType`  
`enum class EPendingOperationType`  
_L95-99_
- L97 _public enumerator_ `Add`
- L98 _public enumerator_ `Remove`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ChaosVDWorldOutlinerTab.h` (Private)


#### class `FChaosVDWorldOutlinerTab`  
`class FChaosVDWorldOutlinerTab : public FChaosVDTabSpawnerBase, public TSharedFromThis<FChaosVDWorldOutlinerTab>`  
_L26-42_
- inherits: `FChaosVDTabSpawnerBase,TSharedFromThis<FChaosVDWorldOutlinerTab>`
- desc: Spawns and handles and instance for the visual debugger World Outliner
- L29 _public function_ `FChaosVDWorldOutlinerTab(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget)`
- L33 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`
- L34 _public prototype_ `virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed) override;`
- L37 _private prototype_ `void CreateWorldOutlinerWidget();`
- L39 _private member_ `TSharedPtr<ISceneOutliner> SceneOutlinerWidget;`
- L41 _private member_ `FTSTicker::FDelegateHandle DeferredOutlinerUpdateHandle;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FChaosVDSelectionChanged, AActor* SelectedActor) class FChaosVDWorldOutlinerTab : public FChaosVDTabSpawnerBase, public TSharedFromThis<FChaosVDWorldOutlinerTab> { public: FChaosVDWorldOutlinerTab(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget) { } virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override; virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed) override; private: void CreateWorldOutlinerWidget(); TSharedPtr<ISceneOutliner> SceneOutlinerWidget; FTSTicker::FDelegateHandle DeferredOutlinerUpdateHandle; };`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Components/ChaosVDAdditionalGTDataRouterComponent.h` (Private)


#### class `UChaosVDAdditionalGTDataRouterComponent`  
`class UChaosVDAdditionalGTDataRouterComponent : public UChaosVDSolverDataComponent`  
_L15-24_
- reflection: `UCLASS()`
- inherits: `UChaosVDSolverDataComponent`
- desc: Helper component used to re-route GT data loaded as a Solver Frame. This is part of a compatibility layer to support GT data from multiple files Until we refactor CVD to either support multiple GT Tracks, or remove the difference between GT track and solver track
- L19 _private prototype_ `virtual void UpdateFromSolverFrameData(const FChaosVDSolverFrameData& InSolverFrameData) override;`
- L21 _private prototype_ `virtual void ClearData() override;`
- L23 _private prototype_ `void ApplyDelayedSolverFrameDataUpdate(TSharedPtr<FChaosVDGameFrameDataWrapper> PendingFrameUpdate);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Components/ChaosVDConstraintDataComponent.h` (Private)


#### class `UChaosVDConstraintDataComponent`  
`class UChaosVDConstraintDataComponent : public UChaosVDSolverDataComponent`  
_L16-44_
- reflection: `UCLASS()`
- inherits: `UChaosVDSolverDataComponent`
- L21 _public prototype_ `UChaosVDConstraintDataComponent();`
- L24 _public prototype_ `template<typename ConstraintDataType> void UpdateConstraintData(const TArray<TSharedPtr<ConstraintDataType>>& InData);`
- L26 _public function_ `const FChaosVDConstraintDataArray& GetAllConstraints() const`
- L27 _public prototype_ `const FChaosVDConstraintDataArray* GetConstraintsForParticle(int32 ParticleID, EChaosVDParticlePairSlot Options) const;`
- L29 _public prototype_ `virtual void ClearData() override;`
- L31 _public prototype_ `virtual void AppendSceneCompositionTestData(FChaosVDSceneCompositionTestData& OutStateTestData) override;`
- L35 _protected prototype_ `TSharedPtr<FChaosVDConstraintDataWrapperBase> GetConstraintByIndex(int32 ConstraintIndex);`
- L37 _protected member_ `FChaosVDConstraintDataArray AllConstraints;`
- L39 _protected member_ `FChaosVDConstraintDataByParticleMap ConstraintByParticle0;`
- L40 _protected member_ `FChaosVDConstraintDataByParticleMap ConstraintByParticle1;`
- L42 _protected member_ `FChaosVDConstraintDataByConstraintIndexMap ConstraintByConstraintIndex;`
- L47 _function_ `template <typename ConstraintDataType> void UChaosVDConstraintDataComponent::UpdateConstraintData(const TArray<TSharedPtr<ConstraintDataType>>& InData)`

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TMap<int32, TArray<TSharedPtr<FChaosVDConstraintDataWrapperBase>>> FChaosVDConstraintDataByParticleMap;`
- L12 _typedef_ `typedef TMap<int32, TSharedPtr<FChaosVDConstraintDataWrapperBase>> FChaosVDConstraintDataByConstraintIndexMap;`
- L13 _typedef_ `typedef TArray<TSharedPtr<FChaosVDConstraintDataWrapperBase>> FChaosVDConstraintDataArray;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Components/ChaosVDConstraintDataHelpers.h` (Private)


#### enum `EChaosVDParticlePairSlot`  
`enum class EChaosVDParticlePairSlot : uint8`  
_L12-17_
- L14 _public enumerator_ `Primary`
- L15 _public enumerator_ `Secondary`
- L16 _public enumerator_ `Any`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Chaos`
- L19 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L19 _namespace_ `namespace Utils` (scope `Chaos::VisualDebugger`)
- L22 _function_ `template <typename MapType, typename TData> void AddDataDataToParticleIDMap(MapType& MapToUpdate, const TData& MidPhaseData, int32 ParticleID)` (scope `Chaos::VisualDebugger::Utils`)
- L35 _function_ `template <typename MapType, typename TData> const TArray<TData>* GetDataFromParticlePairMaps(const MapType& Map0ToQuery, const MapType& Map1ToQuery, int32 ParticleID, EChaosVDParticlePairSlot Options)` (scope `Chaos::VisualDebugger::Utils`)

### `Plugins/ChaosVD/Source/ChaosVD/Private/Components/ChaosVDInstancedStaticMeshComponent.h` (Private)


#### enum `EChaosVDMeshInstanceOperationsFlags`  
`enum class EChaosVDMeshInstanceOperationsFlags`  
_L13-21_
- reflection: `UENUM()`
- L15 _public enumerator_ `None = 0`
- L16 _public enumerator_ `Add = 1 << 0`
- L17 _public enumerator_ `Remove = 1 << 1`
- L18 _public enumerator_ `ColorUpdate = 1 << 2`
- L19 _public enumerator_ `SelectionUpdate = 1 << 3`
- L20 _public enumerator_ `TransformUpdate = 1 << 4`

#### class `UChaosVDInstancedStaticMeshComponent`  
`class UChaosVDInstancedStaticMeshComponent : public UInstancedStaticMeshComponent, public IChaosVDGeometryComponent, public IChaosVDPooledObject`  
_L26-150_
- reflection: `UCLASS(HideCategories=("Transform"))`
- inherits: `UInstancedStaticMeshComponent,IChaosVDGeometryComponent,IChaosVDPooledObject`
- desc: CVD version of an Instance Static Mesh Component that holds additional CVD data
- L30 _public function_ `UChaosVDInstancedStaticMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L41 _public prototype_ `void EnqueueMeshInstanceOperation(const TSharedRef<FChaosVDInstancedMeshData>& MeshInstanceHandle, EChaosVDMeshInstanceOperationsFlags Operation);`
- L42 _public prototype_ `void CancelMeshInstanceOperation(const TSharedRef<FChaosVDInstancedMeshData>& MeshInstanceHandle, EChaosVDMeshInstanceOperationsFlags Operation);`
- L44 _public prototype_ `bool CanExecuteOperation(EChaosVDMeshInstanceOperationsFlags Operation, EChaosVDMeshInstanceOperationsFlags PendingOperations);`
- L46 _public prototype_ `void ProcessChanges();`
- L50 _public prototype_ `virtual uint32 GetGeometryKey() const override;`
- L52 _public prototype_ `virtual TSharedPtr<FChaosVDInstancedMeshData> GetMeshDataInstanceHandle(int32 InstanceIndex) const override;`
- L54 _public function_ `virtual bool IsMeshReady() const override`
- L59 _public prototype_ `virtual void SetIsMeshReady(bool bIsReady) override;`
- L61 _public function_ `virtual FChaosVDMeshReadyDelegate* OnMeshReady() override`
- L66 _public function_ `virtual FChaosVDMeshComponentEmptyDelegate* OnComponentEmpty() override`
- L71 _public prototype_ `virtual void UpdateVisibilityForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) override;`
- L73 _public prototype_ `virtual void UpdateSelectionStateForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) override;`
- L75 _public prototype_ `virtual void UpdateColorForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) override;`
- L77 _public prototype_ `virtual void UpdateWorldTransformForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) override;`
- L79 _public function_ `virtual void SetMeshComponentAttributeFlags(EChaosVDMeshAttributesFlags Flags) override`
- L83 _public function_ `virtual EChaosVDMeshAttributesFlags GetMeshComponentAttributeFlags() const override`
- L88 _public function_ `virtual bool GetIsDestroyed() const override`
- L93 _public function_ `virtual void SetIsDestroyed(bool bNewIsDestroyed) override`
- L98 _public prototype_ `virtual void Reset() override;`
- L100 _public prototype_ `virtual void Initialize() override;`
- L102 _public prototype_ `virtual void SetGeometryBuilder(TWeakPtr<FChaosVDGeometryBuilder> GeometryBuilder) override;`
- L104 _public prototype_ `virtual EChaosVDMaterialType GetMaterialType() const override;`
- L107 _public prototype_ `virtual TSharedPtr<FChaosVDInstancedMeshData> AddMeshInstance(const FTransform InstanceTransform, bool bIsWorldSpace, const TSharedRef<FChaosVDExtractedGeometryDataHandle>& InGeometryHandle, int32 ParticleID, int32 SolverID) override;`
- L108 _public prototype_ `virtual void AddExistingMeshInstance(const TSharedRef<FChaosVDInstancedMeshData>& InMeshDataHandle) override;`
- L109 _public prototype_ `virtual void RemoveMeshInstance(const TSharedRef<FChaosVDInstancedMeshData>& InHandleToRemove, ERemovalMode Mode = ERemovalMode::Deferred) override;`
- L111 _public prototype_ `void UpdateInstanceHandle(int32 OldIndex, int32 NewIndex);`
- L114 _public prototype_ `void HandleInstanceIndexUpdated(TArrayView<const FInstancedStaticMeshDelegates::FInstanceIndexUpdateData> InIndexUpdates);` — Handles a mesh instance index update reported by the mesh component used to render this mesh instance
- L116 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty) override;`
- L118 _public prototype_ `virtual bool IsNavigationRelevant() const override;`
- L120 _public prototype_ `void ClearInstanceHandles();`
- L123 _public prototype_ `virtual void OnAcquired() override;` — BEGIN IChaosVDPooledObject Interface
- L124 _public prototype_ `virtual void OnDisposed() override;`
- L127 _public prototype_ `bool ExternalTick(float DeltaTime);`
- L131 _protected prototype_ `bool UpdateGeometryKey(uint32 NewHandleGeometryKey);`
- L133 _protected member_ `EChaosVDMeshAttributesFlags MeshComponentAttributeFlags = EChaosVDMeshAttributesFlags::None;`
- L135 _protected member_ `uint32 CurrentGeometryKey = 0;`
- L137 _protected member_ `uint8 bIsMeshReady:1 = false;`
- L138 _protected member_ `uint8 bIsDestroyed:1 = false;`
- L140 _protected member_ `FChaosVDMeshReadyDelegate MeshReadyDelegate;`
- L141 _protected member_ `FChaosVDMeshComponentEmptyDelegate ComponentEmptyDelegate;`
- L143 _protected member_ `TWeakPtr<FChaosVDGeometryBuilder> GeometryBuilderWeakPtr;`
- L145 _protected member_ `TMap<TSharedPtr<FChaosVDInstancedMeshData>, EChaosVDMeshInstanceOperationsFlags> PendingOperationsByInstance;`
- L147 _protected member_ `TMap<int32, TSharedPtr<FChaosVDInstancedMeshData>> CurrentInstanceHandlesByIndex;`
- L149 _protected member_ `FTSTicker::FDelegateHandle ExternalTickerHandle;`

#### Free symbols / members of external scopes

- L22 _prototype_ `ENUM_CLASS_FLAGS(EChaosVDMeshInstanceOperationsFlags);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Components/ChaosVDSceneQueryDataComponent.h` (Private)


#### class `UChaosVDSceneQueryDataComponent`  
`class UChaosVDSceneQueryDataComponent : public UChaosVDSolverDataComponent`  
_L15-40_
- reflection: `UCLASS()`
- inherits: `UChaosVDSolverDataComponent`
- desc: Actor Component that contains all the scene queries recorded at the current loaded frame
- L20 _public prototype_ `UChaosVDSceneQueryDataComponent();`
- L21 _public prototype_ `void ClearSceneQuerySelection();`
- L23 _public prototype_ `virtual void UpdateFromNewGameFrameData(const FChaosVDGameFrameData& InGameFrameData) override;`
- L25 _public prototype_ `TConstArrayView<TSharedPtr<FChaosVDQueryDataWrapper>> GetQueriesByType(EChaosVDSceneQueryType Type) const;`
- L26 _public prototype_ `TConstArrayView<TSharedPtr<FChaosVDQueryDataWrapper>> GetAllQueries() const;`
- L27 _public prototype_ `TSharedPtr<FChaosVDQueryDataWrapper> GetQueryByID(int32 QueryID) const;`
- L29 _public prototype_ `virtual void ClearData() override;`
- L31 _public prototype_ `virtual void AppendSceneCompositionTestData(FChaosVDSceneCompositionTestData& OutStateTestData) override;`
- L35 _protected prototype_ `void ProccessSQData(const TMap<int32, TSharedPtr<FChaosVDQueryDataWrapper>>* RecordedQueriesByQueryID);`
- L37 _protected member_ `TMap<EChaosVDSceneQueryType, TArray<TSharedPtr<FChaosVDQueryDataWrapper>>> RecordedQueriesByType;`
- L38 _protected member_ `TMap<int32, TSharedPtr<FChaosVDQueryDataWrapper>> RecordedQueriesByID;`
- L39 _protected member_ `TArray<TSharedPtr<FChaosVDQueryDataWrapper>> RecordedQueries;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Components/ChaosVDSolverCharacterGroundConstraintDataComponent.h` (Private)


#### class `UChaosVDSolverCharacterGroundConstraintDataComponent`  
`class UChaosVDSolverCharacterGroundConstraintDataComponent : public UChaosVDConstraintDataComponent`  
_L11-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UChaosVDConstraintDataComponent`
- L15 _public prototype_ `virtual void SetScene(const TWeakPtr<FChaosVDScene>& InSceneWeakPtr) override;`
- L17 _public prototype_ `virtual void UpdateFromSolverFrameData(const FChaosVDSolverFrameData& InSolverFrameData) override;`
- L19 _public prototype_ `void HandleSceneUpdated();`
- L21 _public prototype_ `virtual void BeginDestroy() override;`
- L23 _public prototype_ `virtual void AppendSceneCompositionTestData(FChaosVDSceneCompositionTestData& OutStateTestData) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSVD_API`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Components/ChaosVDSolverCollisionDataComponent.h` (Private)


#### class `UChaosVDSolverCollisionDataComponent`  
`class UChaosVDSolverCollisionDataComponent : public UChaosVDSolverDataComponent`  
_L22-52_
- reflection: `UCLASS()`
- inherits: `UChaosVDSolverDataComponent`
- L27 _public prototype_ `UChaosVDSolverCollisionDataComponent();`
- L29 _public prototype_ `virtual void UpdateFromNewSolverStageData(const FChaosVDSolverFrameData& InSolverFrameData, const FChaosVDFrameStageData& InSolverFrameStageData) override;`
- L31 _public function_ `const TArray<TSharedPtr<FChaosVDParticlePairMidPhase>>& GetMidPhases() const`
- L36 _public prototype_ `const TArray<TSharedPtr<FChaosVDParticlePairMidPhase>>* GetMidPhasesForParticle(int32 ParticleID, EChaosVDParticlePairSlot Options) const;`
- L37 _public prototype_ `const TArray<FChaosVDConstraint*>* GetConstraintsForParticle(int32 ParticleID, EChaosVDParticlePairSlot Options) const;`
- L39 _public prototype_ `virtual void ClearData() override;`
- L43 _protected prototype_ `void UpdateCollisionData(const TArray<TSharedPtr<FChaosVDParticlePairMidPhase>>& InMidPhaseData);`
- L45 _protected member_ `TArray<TSharedPtr<FChaosVDParticlePairMidPhase>> AllMidPhases;`
- L46 _protected member_ `FChaosVDMidPhaseByParticleMap MidPhasesByParticleID0;`
- L47 _protected member_ `FChaosVDMidPhaseByParticleMap MidPhasesByParticleID1;`
- L49 _protected member_ `FChaosVDConstraintByParticleMap ConstraintsByParticleID0;`
- L50 _protected member_ `FChaosVDConstraintByParticleMap ConstraintsByParticleID1;`

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef TMap<int32, TArray<TSharedPtr<FChaosVDParticlePairMidPhase>>> FChaosVDMidPhaseByParticleMap;`
- L19 _typedef_ `typedef TMap<int32, TArray<FChaosVDConstraint*>> FChaosVDConstraintByParticleMap;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Components/ChaosVDSolverJointConstraintDataComponent.h` (Private)


#### class `UChaosVDSolverJointConstraintDataComponent`  
`class UChaosVDSolverJointConstraintDataComponent : public UChaosVDConstraintDataComponent`  
_L12-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UChaosVDConstraintDataComponent`
- L16 _private prototype_ `virtual void UpdateFromNewSolverStageData(const FChaosVDSolverFrameData& InSolverFrameData, const FChaosVDFrameStageData& InSolverFrameStageData) override;`
- L18 _private prototype_ `virtual void AppendSceneCompositionTestData(FChaosVDSceneCompositionTestData& OutStateTestData) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSVD_API`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Components/ChaosVDStaticMeshComponent.h` (Private)


#### class `UChaosVDStaticMeshComponent`  
`class UChaosVDStaticMeshComponent : public UStaticMeshComponent, public IChaosVDGeometryComponent, public IChaosVDPooledObject`  
_L12-101_
- reflection: `UCLASS(HideCategories=("Transform"))`
- inherits: `UStaticMeshComponent,IChaosVDGeometryComponent,IChaosVDPooledObject`
- desc: CVD version of a Static Mesh Component that holds additional CVD data
- L17 _public function_ `UChaosVDStaticMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L28 _public function_ `virtual bool IsMeshReady() const override`
- L30 _public function_ `virtual void SetIsMeshReady(bool bIsReady) override`
- L32 _public function_ `virtual FChaosVDMeshReadyDelegate* OnMeshReady() override`
- L34 _public function_ `virtual FChaosVDMeshComponentEmptyDelegate* OnComponentEmpty() override`
- L36 _public prototype_ `virtual uint32 GetGeometryKey() const override;`
- L37 _public prototype_ `virtual void UpdateVisibilityForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) override;`
- L39 _public prototype_ `virtual void UpdateSelectionStateForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) override;`
- L41 _public prototype_ `virtual bool ShouldRenderSelected() const override;`
- L43 _public prototype_ `virtual void UpdateColorForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) override;`
- L44 _public prototype_ `virtual void UpdateWorldTransformForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) override;`
- L46 _public function_ `virtual void SetMeshComponentAttributeFlags(EChaosVDMeshAttributesFlags Flags) override`
- L47 _public function_ `virtual EChaosVDMeshAttributesFlags GetMeshComponentAttributeFlags() const override`
- L49 _public prototype_ `virtual TSharedPtr<FChaosVDInstancedMeshData> GetMeshDataInstanceHandle(int32 InstanceIndex) const override;`
- L51 _public prototype_ `virtual void Initialize() override;`
- L52 _public prototype_ `virtual void Reset() override;`
- L54 _public prototype_ `virtual TSharedPtr<FChaosVDInstancedMeshData> AddMeshInstance(const FTransform InstanceTransform, bool bIsWorldSpace, const TSharedRef<FChaosVDExtractedGeometryDataHandle>& InGeometryHandle, int32 ParticleID, int32 SolverID) override;`
- L55 _public prototype_ `virtual void AddExistingMeshInstance(const TSharedRef<FChaosVDInstancedMeshData>& InMeshDataHandle) override;`
- L56 _public prototype_ `virtual void RemoveMeshInstance(const TSharedRef<FChaosVDInstancedMeshData>& InHandleToRemove, ERemovalMode Mode = ERemovalMode::Deferred) override;`
- L58 _public prototype_ `virtual void SetGeometryBuilder(TWeakPtr<FChaosVDGeometryBuilder> GeometryBuilder) override;`
- L60 _public prototype_ `virtual EChaosVDMaterialType GetMaterialType() const override;`
- L62 _public function_ `virtual bool GetIsDestroyed() const override`
- L67 _public function_ `virtual void SetIsDestroyed(bool bNewIsPendingDestroy) override`
- L75 _public function_ `virtual void OnAcquired() override` — BEGIN IChaosVDPooledObject Interface
- L80 _public prototype_ `virtual void OnDisposed() override;`
- L85 _protected prototype_ `bool UpdateGeometryKey(uint32 NewHandleGeometryKey);`
- L87 _protected member_ `EChaosVDMeshAttributesFlags MeshComponentAttributeFlags = EChaosVDMeshAttributesFlags::None;`
- L88 _protected member_ `uint32 CurrentGeometryKey = 0;`
- L89 _protected member_ `bool bIsMeshReady = false;`
- L90 _protected member_ `bool bIsOwningParticleSelected = false;`
- L91 _protected member_ `FChaosVDMeshReadyDelegate MeshReadyDelegate;`
- L92 _protected member_ `FChaosVDMeshComponentEmptyDelegate ComponentEmptyDelegate;`
- L94 _protected member_ `bool bIsDestroyed = false;`
- L96 _protected member_ `TSharedPtr<FChaosVDInstancedMeshData> CurrentMeshDataHandle = nullptr;`
- L98 _protected member_ `TSharedPtr<FChaosVDExtractedGeometryDataHandle> CurrentGeometryHandle = nullptr;`
- L100 _protected member_ `TWeakPtr<FChaosVDGeometryBuilder> GeometryBuilderWeakPtr;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/DetailsCustomizations/ChaosVDDetailsCustomizationUtils.h` (Private)


#### struct `FChaosVDDetailsPropertyDataHandle`  
`template<typename PropertyType> struct FChaosVDDetailsPropertyDataHandle`  
_L30-39_
- L32 _public prototype_ `explicit FChaosVDDetailsPropertyDataHandle(const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L34 _public prototype_ `PropertyType* GetDataInstance();`
- L37 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L38 _private member_ `PropertyType* DataInstance = nullptr;`
- L42 _function_ `template <typename PropertyType> FChaosVDDetailsPropertyDataHandle<PropertyType>::FChaosVDDetailsPropertyDataHandle(const TSharedRef<IPropertyHandle>& InPropertyHandle)`
- L65 _function_ `template <typename PropertyType> PropertyType* FChaosVDDetailsPropertyDataHandle<PropertyType>::GetDataInstance()`

#### class `FChaosVDDetailsCustomizationUtils`  
`class FChaosVDDetailsCustomizationUtils`  
_L76-121_
- desc: Helper Class for CVD Custom Details view
- L84 _public prototype_ `static void HideAllCategories(IDetailLayoutBuilder& DetailBuilder, const TSet<FName>& AllowedCategories = TSet<FName>());` — Hides all categories of this view, except the ones provided in the Allowed Categories set @param DetailBuilder Layout builder of the class we are customizing @param AllowedCategories Set of category names we do not want to hide
- L90 _public prototype_ `static void HideInvalidCVDDataWrapperProperties(TConstArrayView<TSharedPtr<IPropertyHandle>> InPropertyHandles);` — Marks any property of the provided handles array as hidden if they are not valid CVD properties (meaning they don't have serialized data loaded from a CVD recording) @param InPropertyHandles Handles of properties to evaluate and hide if needed
- L97 _public prototype_ `static void HideInvalidCVDDataWrapperProperties(TConstArrayView<TSharedRef<IPropertyHandle>> InPropertyHandles, IDetailLayoutBuilder& DetailBuilder);` — Marks any property of the provided handles array as hidden if they are not valid CVD properties (meaning they don't have serialized data loaded from a CVD recording), using the provided details builder @param InPropertyHandles Handles of properties to evaluate and hide if needed @param DetailBuilder Details builder that will hide the property
- L104 _public prototype_ `static bool HasValidCVDWrapperData(const TSharedPtr<IPropertyHandle>& InPropertyHandle, bool& bOutIsCVDBaseDataStruct);` — Marks any property of the provided handles array as hidden if they are not valid CVD properties (meaning they don't have serialized data loaded from a CVD recording), using the provided details builder @param InPropertyHandle Property Handle to evaluate if it is valid @param bOutIsCVDBaseDataStruct Set to true if the property handle provided is from a CVD Wrapper Data Base. All other types will be deemed valid
- L106 _public prototype_ `static void CreateCollisionChannelsMatrixRow(int32 ChannelIndex, const FChaosVDCollisionChannelStateGetter& InChannelStateGetter, const FText& InChannelName, IDetailGroup& CollisionGroup, const float RowWidthCustomization);`
- L108 _public prototype_ `static TSharedPtr<FChaosVDCollisionChannelsInfoContainer> BuildDefaultCollisionChannelInfo();`
- L110 _public prototype_ `static void BuildCollisionChannelMatrix(const FChaosVDCollisionChannelStateGetter& InCollisionChannelStateGetter, TConstArrayView<FChaosVDCollisionChannelInfo> CollisionChannelsInfo, IDetailGroup& ParentCategoryGroup);`
- L112 _public prototype_ `static TSharedRef<SWidget> CreateCollisionResponseMatrixCheckbox(const FChaosVDCollisionChannelStateGetter& InStateGetter, int32 ChannelIndex, ECollisionResponse TargetResponse, float Width);`
- L114 _public prototype_ `static constexpr int32 GetMaxCollisionChannelIndex();`
- L116 _public prototype_ `UE_INTERNAL static void ExtractResponseContainer(const uint64 BlockMask, const uint64 OverlapMask, FCollisionResponseContainer& OutResponses);`
- L118 _public prototype_ `static void AddWidgetRowForCheckboxValue(TAttribute<ECheckBoxState>&& State, const FText& InValueName, IDetailGroup& DetailGroup);`
- L120 _public prototype_ `static FText GetDefaultCollisionChannelsUseWarningMessage();`
- L123 _function_ `constexpr int32 FChaosVDDetailsCustomizationUtils::GetMaxCollisionChannelIndex()`

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(ECollisionResponse, FChaosVDCollisionChannelStateGetter, int32 );`
- L27 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(ECollisionResponse, FChaosVDCollisionChannelStateGetter, int32 );`

### `Plugins/ChaosVD/Source/ChaosVD/Private/DetailsCustomizations/ChaosVDGeometryComponentCustomization.h` (Private)


#### class `FChaosVDGeometryComponentCustomization`  
`class FChaosVDGeometryComponentCustomization : public IDetailCustomization`  
_L9-20_
- inherits: `IDetailCustomization`
- desc: Customization view for CVD Geometry component classes
- L12 _public prototype_ `FChaosVDGeometryComponentCustomization();`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L19 _private member_ `TSet<FName> AllowedCategories;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/DetailsCustomizations/ChaosVDParticleDataWrapperCustomization.h` (Private)


#### class `FChaosVDParticleDataWrapperCustomization`  
`class FChaosVDParticleDataWrapperCustomization : public IPropertyTypeCustomization`  
_L13-21_
- inherits: `IPropertyTypeCustomization`
- desc: Property Customization used to only show the available particle data withing the ChaosVDParticleDataViewer
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/DetailsCustomizations/ChaosVDParticleMetadataCustomization.h` (Private)


#### class `FChaosVDParticleMetadataCustomization`  
`class FChaosVDParticleMetadataCustomization : public IPropertyTypeCustomization`  
_L13-24_
- inherits: `IPropertyTypeCustomization`
- desc: Property Customization for particle metadata in the Chaos Visual Debugger
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L22 _private prototype_ `TSharedRef<SWidget> GenerateBrowseParticleOwnerButton(FTopLevelAssetPath AssetPath);`
- L23 _private prototype_ `FReply BrowseParticleOwner(FTopLevelAssetPath AssetPath);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/DetailsCustomizations/ChaosVDQueryDataWrappersCustomizationDetails.h` (Private)


#### class `FChaosVDQueryDataWrappersCustomizationDetails`  
`class FChaosVDQueryDataWrappersCustomizationDetails : public IPropertyTypeCustomization`  
_L15-21_
- inherits: `IPropertyTypeCustomization`
- desc: Custom property layout for the ChaosVD SQ Data wrapper struct
- L17 _private prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _private function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L20 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `FChaosVDQueryVisitDataCustomization`  
`class FChaosVDQueryVisitDataCustomization : public IDetailCustomization`  
_L24-38_
- inherits: `IDetailCustomization`
- desc: Custom details panel for the ChaosVD SQ Visit Data struct
- L27 _public prototype_ `FChaosVDQueryVisitDataCustomization(const TWeakPtr<SChaosVDMainTab>& InMainTab);`
- L29 _public prototype_ `virtual ~FChaosVDQueryVisitDataCustomization() override = default;`
- L31 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<SChaosVDMainTab> MainTab);`
- L32 _public prototype_ `void ReplaceParticleIndexWithParticleName(IDetailLayoutBuilder& DetailBuilder);`
- L34 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L37 _protected member_ `TWeakPtr<SChaosVDMainTab> MainTabWeakPtr = nullptr;`

#### class `FChaosVDQueryVisitDataPropertyCustomization`  
`class FChaosVDQueryVisitDataPropertyCustomization : public IPropertyTypeCustomization`  
_L41-57_
- inherits: `IPropertyTypeCustomization`
- desc: Custom property details for the ChaosVD SQ Visit Data struct
- L44 _public function_ `FChaosVDQueryVisitDataPropertyCustomization(const TWeakPtr<SChaosVDMainTab>& InMainTab) : MainTabWeakPtr(InMainTab)`
- L48 _public prototype_ `virtual ~FChaosVDQueryVisitDataPropertyCustomization() override = default;`
- L50 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TWeakPtr<SChaosVDMainTab> MainTab);`
- L52 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L53 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L56 _protected member_ `TWeakPtr<SChaosVDMainTab> MainTabWeakPtr = nullptr;`

#### class `FChaosVDQueryDataWrapperCustomization`  
`class FChaosVDQueryDataWrapperCustomization : public IDetailCustomization`  
_L60-69_
- inherits: `IDetailCustomization`
- desc: Custom details panel for the ChaosVD SQ Data Wrapper struct
- L63 _public function_ `FChaosVDQueryDataWrapperCustomization()`
- L64 _public prototype_ `virtual ~FChaosVDQueryDataWrapperCustomization() override= default;`
- L66 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L68 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### class `FChaosVDCollisionChannelsCustomizationBase`  
`class FChaosVDCollisionChannelsCustomizationBase : public IPropertyTypeCustomization`  
_L72-88_
- inherits: `IPropertyTypeCustomization`
- desc: Custom details panel for the ChaosVD SQ Data Collision Response View
- L76 _public prototype_ `FChaosVDCollisionChannelsCustomizationBase(const TWeakPtr<SChaosVDMainTab>& InMainTab);`
- L78 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L79 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L82 _protected prototype_ `void UpdateCollisionChannelsInfoCache(TSharedPtr<FChaosVDCollisionChannelsInfoContainer> NewCollisionChannelsInfo);`
- L84 _protected member_ `TSharedPtr<FChaosVDCollisionChannelsInfoContainer> CachedCollisionChannelInfos;`
- L85 _protected member_ `bool bChannelInfoBuiltFromDefaults = true;`
- L87 _protected member_ `TWeakPtr<SChaosVDMainTab> MainTabWeakPtr = nullptr;`

#### class `FChaosVDCollisionResponseParamsCustomization`  
`class FChaosVDCollisionResponseParamsCustomization : public FChaosVDCollisionChannelsCustomizationBase`  
_L91-108_
- inherits: `FChaosVDCollisionChannelsCustomizationBase`
- desc: Custom details panel for the ChaosVD SQ Data Collision Response View
- L94 _public function_ `FChaosVDCollisionResponseParamsCustomization(const TWeakPtr<SChaosVDMainTab>& InMainTab) : FChaosVDCollisionChannelsCustomizationBase(InMainTab)`
- L98 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TWeakPtr<SChaosVDMainTab> MainTab);`
- L100 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L101 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L105 _private prototype_ `ECollisionResponse GetCurrentCollisionResponseForChannel(int32 ChannelIndex) const;`
- L107 _private member_ `TSharedPtr<FChaosVDDetailsPropertyDataHandle<FChaosVDCollisionResponseParams>> CurrentPropertyDataHandle = nullptr;`

#### class `FChaosVDCollisionObjectParamsCustomization`  
`class FChaosVDCollisionObjectParamsCustomization : public FChaosVDCollisionChannelsCustomizationBase`  
_L111-128_
- inherits: `FChaosVDCollisionChannelsCustomizationBase`
- desc: Custom details panel for the ChaosVD SQ Data Collision Object Response View
- L114 _public function_ `FChaosVDCollisionObjectParamsCustomization(const TWeakPtr<SChaosVDMainTab>& InMainTab) : FChaosVDCollisionChannelsCustomizationBase(InMainTab)`
- L118 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TWeakPtr<SChaosVDMainTab> MainTab);`
- L120 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L121 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L125 _private prototype_ `ECheckBoxState GetCurrentObjectFlag(int32 ChannelIndex) const;`
- L127 _private member_ `TSharedPtr<FChaosVDDetailsPropertyDataHandle<FChaosVDCollisionObjectQueryParams>> CurrentPropertyDataHandle = nullptr;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/DetailsCustomizations/ChaosVDSelectionMultipleViewCustomization.h` (Private)


#### class `FChaosVDSelectionMultipleViewCustomization`  
`class FChaosVDSelectionMultipleViewCustomization : public IDetailCustomization`  
_L8-15_
- inherits: `IDetailCustomization`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/DetailsCustomizations/ChaosVDShapeDataCustomization.h` (Private)


#### class `FChaosVDShapeDataCustomization`  
`class FChaosVDShapeDataCustomization : public IPropertyTypeCustomization`  
_L18-89_
- inherits: `IPropertyTypeCustomization`
- desc: Custom details panel for the ChaosVD SQ Data Collision Response View
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TWeakPtr<SChaosVDMainTab> MainTab);`
- L23 _public prototype_ `FChaosVDShapeDataCustomization(const TWeakPtr<SChaosVDMainTab>& InMainTab);`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L30 _private prototype_ `void UpdateCollisionChannelsInfoCache(const TSharedPtr<FChaosVDCollisionChannelsInfoContainer>& NewCollisionChannelsInfo);`
- L32 _private prototype_ `FText GetCurrentCollisionEnabledAsText() const;`
- L34 _private prototype_ `ECheckBoxState GetCurrentIsComplexCollision() const;`
- L60 _private prototype_ `void BuildCollisionFilerDataLayout(ECollisionFilterDataType FilterDataType, const FText& InDetailsGroupLabel, IDetailLayoutBuilder& ParentLayoutBuilder, ECollisionFilterLayoutFlags LayoutFlags);`
- L62 _private prototype_ `FText GetCurrentCollisionChannelAsText(ECollisionFilterDataType FilterDataType) const;`
- L63 _private prototype_ `uint8 GetCurrentExtraFilter(ECollisionFilterDataType FilterDataType) const;`
- L65 _private prototype_ `ECollisionResponse GetCurrentCollisionResponseForChannel(int32 ChannelIndex, ECollisionFilterDataType Type) const;`
- L67 _private prototype_ `void AddCollisionFilterFlagRow(ECollisionFilterDataType Type, Chaos::EFilterFlags Flag, IDetailGroup& DetailGroup) const;`
- L68 _private prototype_ `ECheckBoxState GetCurrentStateForFilteringFlag(ECollisionFilterDataType Type, Chaos::EFilterFlags FilteringFlag) const;`
- L70 _private prototype_ `void AddExtraCollisionFilterFlags(ECollisionFilterDataType Type, const FText& IntSectionLabel, IDetailCategoryBuilder& CategoryBuilder);`
- L72 _private prototype_ `void CacheCollisionFilterData();`
- L74 _private prototype_ `void RegisterCVDScene(const TSharedPtr<FChaosVDScene>& InScene);`
- L76 _private prototype_ `void HandleSceneUpdated();`
- L78 _private member_ `TSharedPtr<FChaosVDCollisionChannelsInfoContainer> CachedCollisionChannelInfos;`
- L79 _private member_ `bool bChannelInfoBuiltFromDefaults = true;`
- L81 _private member_ `TStaticArray<FCachedFilterData, ECollisionFilterDataType::Count> CachedFilterData;`
- L82 _private member_ `bool bFiltersRequireSplitView = false;`
- L84 _private member_ `TSharedPtr<FChaosVDDetailsPropertyDataHandle<FChaosVDShapeCollisionData>> CurrentShapeDataHandle = nullptr;`
- L86 _private member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr = nullptr;`
- L88 _private member_ `TWeakPtr<SChaosVDMainTab> MainTabWeakPtr = nullptr;`

#### enum `FChaosVDShapeDataCustomization::ECollisionFilterDataType`  
`enum ECollisionFilterDataType`  
_L36-41_
- L38 _public enumerator_ `Query`
- L39 _public enumerator_ `Sim`
- L40 _public enumerator_ `Count`

#### enum `FChaosVDShapeDataCustomization::ECollisionFilterLayoutFlags`  
`enum class ECollisionFilterLayoutFlags : uint8`  
_L43-49_
- L45 _public enumerator_ `None = 0`
- L46 _public enumerator_ `StartExpanded = 1 << 0`
- L47 _public enumerator_ `IsEditable = 1 << 1`
- L48 _public enumerator_ `IsAdvanced = 1 << 2`

#### struct `FChaosVDShapeDataCustomization::FCachedFilterData`  
`struct FCachedFilterData`  
_L52-58_
- L54 _public member_ `uint8 ChannelIndex = 0;`
- L55 _public member_ `uint8 MaskFilter = 0;`
- L56 _public member_ `Chaos::EFilterFlags Flags = Chaos::EFilterFlags::None;`
- L57 _public member_ `FCollisionResponseContainer Responses;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/ObjectsWaitingGeometryList.h` (Private)


#### class `FObjectsWaitingGeometryList`  
`template<typename ObjectType> class FObjectsWaitingGeometryList`  
_L17-64_
- desc: Object that handles objects waiting for geometry to be ready to perform a desired operation The operation has to run on the Game Thread, and there is a limit on how many operations will be processed per tick
- L21 _public function_ `FObjectsWaitingGeometryList(const TFunction<bool(uint32, ObjectType)>& InObjectProcessorCallback, const FTextFormat& InProgressNotificationNameFormat, const TFunction<bool(uint32)>& InShouldProcessObjectsOverride) : ObjectProcessorCallback(InObjectProcessorCallback) , ShouldProcessObjectsForKeyOverride(InShouldProcessObjectsOverride) , AsyncProgressNotification(InProgressNotificationNameFormat)`
- L28 _public function_ `~FObjectsWaitingGeometryList()`
- L36 _public prototype_ `void AddObject(uint32 GeometryKey, ObjectType ObjectToProcess);` — Adds an object to process when the provided geometry key is ready
- L39 _public prototype_ `void RemoveObject(uint32 GeometryKey, ObjectType& OutToProcess);` — Removed an object to process
- L42 _public prototype_ `bool ProcessWaitingObjects(float TimeBudgetSeconds);` — Evaluates the current geometry available, and process any objects on the waiting list for it
- L46 _private function_ `bool ShouldProcessObjectsForKey(uint32 GeometryKey) const`
- L55 _private member_ `TFunction<bool(uint32, ObjectType)> ObjectProcessorCallback;`
- L57 _private member_ `TFunction<bool(uint32)> ShouldProcessObjectsForKeyOverride;`
- L59 _private member_ `TMap<uint32, TArray<ObjectType>> WaitingObjectsByGeometryKey;`
- L61 _private member_ `FAsyncCompilationNotification AsyncProgressNotification;`
- L63 _private member_ `int32 QueuedObjectsToProcessNum = 0;`
- L67 _function_ `template <typename ObjectType> void FObjectsWaitingGeometryList<ObjectType>::AddObject(uint32 GeometryKey, ObjectType ObjectToProcess)`
- L84 _function_ `template <typename ObjectType> void FObjectsWaitingGeometryList<ObjectType>::RemoveObject(uint32 GeometryKey, ObjectType& OutToProcess)`
- L106 _function_ `template <typename ObjectType> bool FObjectsWaitingGeometryList<ObjectType>::ProcessWaitingObjects(float TimeBudgetSeconds)`

#### class `FObjectsWaitingProcessingQueue`  
`template<typename ObjectType> class FObjectsWaitingProcessingQueue`  
_L165-190_
- desc: Object that allows adding objects that need processing to a queue, and provide a processor callback. When there are pending objects in the queue, a progress notification will be shown in the editor
- L169 _public function_ `FObjectsWaitingProcessingQueue(const TFunction<bool(ObjectType)>& InObjectProcessorCallback, const FTextFormat& InProgressNotificationNameFormat) : ObjectProcessorCallback(InObjectProcessorCallback) , AsyncProgressNotification(InProgressNotificationNameFormat)`
- L175 _public prototype_ `~FObjectsWaitingProcessingQueue();`
- L177 _public prototype_ `void EnqueueObject(ObjectType ObjectToProcess);`
- L179 _public prototype_ `void ProcessWaitingTasks(float TimeBudgetSeconds);`
- L183 _private member_ `TFunction<bool(ObjectType)> ObjectProcessorCallback;`
- L185 _private member_ `TQueue<ObjectType> WaitingObjectQueue;`
- L187 _private member_ `FAsyncCompilationNotification AsyncProgressNotification;`
- L189 _private member_ `int32 QueuedObjectsToProcessNum = 0;`
- L194 _function_ `template <typename ObjectType> FObjectsWaitingProcessingQueue<ObjectType>::~FObjectsWaitingProcessingQueue()`
- L201 _function_ `template <typename ObjectType> void FObjectsWaitingProcessingQueue<ObjectType>::EnqueueObject(ObjectType ObjectToProcess)`
- L208 _function_ `template <typename ObjectType> void FObjectsWaitingProcessingQueue<ObjectType>::ProcessWaitingTasks(float TimeBudgetSeconds)`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDCharacterConstraintsVisualizationSettings.h` (Private)


#### enum `EChaosVDCharacterGroundConstraintDataVisualizationFlags`  
`enum class EChaosVDCharacterGroundConstraintDataVisualizationFlags : uint32`  
_L10-33_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L12 _public enumerator_ `None = 0 UMETA(Hidden)`
- L14 _public enumerator_ `TargetDeltaPosition = 1 << 0` — Draw the target movement vector
- L16 _public enumerator_ `TargetDeltaFacing = 1 << 1` — Draw the target orientation facing vector
- L18 _public enumerator_ `GroundQueryDistance = 1 << 2` — Draw the ground query distance based on the constraint's data
- L20 _public enumerator_ `GroundQueryNormal = 1 << 3` — Draw the ground query normal based on the constraint's data
- L22 _public enumerator_ `AppliedRadialForce = 1 << 4` — Draw the applied force vector
- L24 _public enumerator_ `AppliedNormalForce = 1 << 5` — Draw the applied force vector
- L26 _public enumerator_ `AppliedTorque = 1 << 6` — Draw the applied force vector
- L28 _public enumerator_ `DrawDisabled = 1 << 7` — Draw the constraint even if it is disabled
- L30 _public enumerator_ `OnlyDrawSelected = 1 << 8` — Only debugs draw data for a selected constraint
- L32 _public enumerator_ `EnableDraw = 1 << 9` — Enables debug draw for constraint data from any solver

#### class `UChaosVDCharacterConstraintsVisualizationSettings`  
`class UChaosVDCharacterConstraintsVisualizationSettings : public UChaosVDVisualizationSettingsObjectBase`  
_L37-85_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDVisualizationSettingsObjectBase`
- L45 _public member_ `bool bShowDebugText = false;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — If true, any debug draw text available will be drawn
- L49 _public member_ `bool bAutoSelectConstraintFromSelectedParticle = false;` — `UPROPERTY(config, EditAnywhere, Category = DetailsPanel)` — Color used for torque vector
- L53 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — The depth priority used for while drawing data. Can be World or Foreground (with this one the shapes will be drawn on top of the geometry and be always visible)
- L56 _public member_ `float ForceScale = 0.01f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Scale to apply to the force vector before draw it.
- L59 _public member_ `float TorqueScale = 0.01f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Scale to apply to the torque vector before draw it.
- L62 _public member_ `float GeneralScale = 1.0f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Scale to apply to anything that does not have a dedicated scale setting before draw it.
- L65 _public member_ `float BaseLineThickness = 2.0f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Line thickness to use as a base to calculate the different line thickness values used to debug draw the data.
- L68 _public member_ `FColor NormalForceColor = FColor(255, 0, 0);` — `UPROPERTY(config, EditAnywhere, Category = DebugDraw)` — Color used for normal force vector
- L71 _public member_ `FColor RadialForceColor = FColor(255, 255, 0);` — `UPROPERTY(config, EditAnywhere, Category = DebugDraw)` — Color used for radial force vector
- L74 _public member_ `FColor TorqueColor = FColor(255, 0, 255);` — `UPROPERTY(config, EditAnywhere, Category = DebugDraw)` — Color used for torque vector
- L76 _public prototype_ `static void SetDataVisualizationFlags(EChaosVDCharacterGroundConstraintDataVisualizationFlags NewFlags);`
- L77 _public prototype_ `static EChaosVDCharacterGroundConstraintDataVisualizationFlags GetDataVisualizationFlags();`
- L79 _public prototype_ `virtual bool CanVisualizationFlagBeChangedByUI(uint32 Flag) override;`
- L84 _private member_ `uint32 GlobalCharacterGroundConstraintDataVisualizationFlags = static_cast<uint32>(EChaosVDCharacterGroundConstraintDataVisualizationFlags::GroundQueryDistance | EChaosVDCharacterGroundConstraintDataVisualizationFlags::GroundQueryNormal | EChaosVDCharacterGroundConstraintDataVisualizationFlags::TargetDeltaPosition);` — `UPROPERTY(config, meta = (Bitmask, BitmaskEnum = "/Script/ChaosVD.EChaosVDCharacterGroundConstraintDataVisualizationFlags"))` — Set of flags to enable/disable visualization of specific character ground constraint data as debug draw

#### Free symbols / members of external scopes

- L34 _prototype_ `ENUM_CLASS_FLAGS(EChaosVDCharacterGroundConstraintDataVisualizationFlags);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDCollisionVisualizationSettings.h` (Private)


#### enum `EChaosVDCollisionVisualizationFlags`  
`enum class EChaosVDCollisionVisualizationFlags: uint32`  
_L10-22_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L12 _public enumerator_ `None = 0 UMETA(Hidden)`
- L13 _public enumerator_ `ContactPoints = 1 << 0`
- L14 _public enumerator_ `ContactInfo = 1 << 1`
- L15 _public enumerator_ `NetPushOut = 1 << 2`
- L16 _public enumerator_ `NetImpulse = 1 << 3`
- L17 _public enumerator_ `ContactNormal = 1 << 4`
- L18 _public enumerator_ `AccumulatedImpulse = 1 << 5`
- L19 _public enumerator_ `DrawInactiveContacts = 1 << 6`
- L20 _public enumerator_ `DrawDataOnlyForSelectedParticle = 1 << 7`
- L21 _public enumerator_ `EnableDraw = 1 << 8`

#### class `UChaosVDCollisionDataVisualizationSettings`  
`class UChaosVDCollisionDataVisualizationSettings : public UChaosVDVisualizationSettingsObjectBase`  
_L26-56_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDVisualizationSettingsObjectBase`
- L33 _public member_ `bool bShowDebugText = false;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — If true, any available debug text will be drawn
- L37 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriority = ESceneDepthPriorityGroup::SDPG_World;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — The depth priority used for while drawing contact data. Can be World or Foreground (with this one the shapes will be drawn on top of the geometry and be always visible)
- L41 _public member_ `float ContactCircleRadius = 6.0f;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — The radius of the debug draw circle used to represent a contact point
- L45 _public member_ `float ContactNormalScale = 30.0f;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — The scale value to be applied to the normal vector of a contact used to change its size to make it easier to see
- L47 _public prototype_ `static void SetDataVisualizationFlags(EChaosVDCollisionVisualizationFlags NewFlags);`
- L48 _public prototype_ `static EChaosVDCollisionVisualizationFlags GetDataVisualizationFlags();`
- L50 _public prototype_ `virtual bool CanVisualizationFlagBeChangedByUI(uint32 Flag) override;`
- L55 _private member_ `uint32 CollisionDataVisualizationFlags = static_cast<uint32>(EChaosVDCollisionVisualizationFlags::ContactInfo | EChaosVDCollisionVisualizationFlags::ContactPoints | EChaosVDCollisionVisualizationFlags::ContactNormal);` — Set of flags to enable/disable visualization of specific collision data as debug draw

#### Free symbols / members of external scopes

- L23 _prototype_ `ENUM_CLASS_FLAGS(EChaosVDCollisionVisualizationFlags);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDJointConstraintVisualizationSettings.h` (Private)


#### enum `EChaosVDJointsDataVisualizationFlags`  
`enum class EChaosVDJointsDataVisualizationFlags : uint32`  
_L10-29_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L12 _public enumerator_ `None = 0 UMETA(Hidden)`
- L14 _public enumerator_ `PushOut = 1 << 0` — Draw the PushOut vector based on the constraint's data
- L16 _public enumerator_ `AngularImpulse = 1 << 1 UMETA(Hidden)` — Draw the Angular Impulse vector based on the constraint's data
- L17 _public enumerator_ `ActorConnector = 1 << 2`
- L18 _public enumerator_ `CenterOfMassConnector = 1 << 3`
- L19 _public enumerator_ `Stretch = 1 << 4`
- L20 _public enumerator_ `Axes = 1 << 5`
- L22 _public enumerator_ `DrawKinematic = 1 << 6` — Draw the joint even if one of the particles or both are kinematic
- L24 _public enumerator_ `DrawDisabled = 1 << 7` — Draw the joint even if it is disabled
- L26 _public enumerator_ `OnlyDrawSelected = 1 << 8` — Only debugs draw data for a selected joint constraint
- L28 _public enumerator_ `EnableDraw = 1 << 9` — Enables Debug draw for Joint Constraint data from any solver that is visible

#### class `UChaosVDJointConstraintsVisualizationSettings`  
`class UChaosVDJointConstraintsVisualizationSettings : public UChaosVDVisualizationSettingsObjectBase`  
_L33-80_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDVisualizationSettingsObjectBase`
- L41 _public member_ `bool bShowDebugText = false;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — If true, any debug draw text available will be drawn
- L45 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — The depth priority used for while drawing data. Can be World or Foreground (with this one the shapes will be drawn on top of the geometry and be always visible)
- L49 _public member_ `float LinearImpulseScale = 0.001f;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — Scale to apply to the Linear Impulse vector before draw it.
- L53 _public member_ `float AngularImpulseScale = 0.1f;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — Scale to apply to the Angular Impulse vector before draw it.
- L57 _public member_ `float GeneralScale = 1.0f;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — Scale to apply to anything that does not have a dedicated scale setting before draw it.
- L61 _public member_ `float BaseLineThickness = 2.0f;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — Line thickness to use as a base to calculate the different line thickness values used to debug draw the data.
- L65 _public member_ `float CenterOfMassSize = 1.0f;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — Size of the debug drawn Center Of Mass.
- L69 _public member_ `float ConstraintAxisLength = 10.0f;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — Size of the debug drawn if the Constraint Axis
- L71 _public prototype_ `static void SetDataVisualizationFlags(EChaosVDJointsDataVisualizationFlags NewFlags);`
- L72 _public prototype_ `static EChaosVDJointsDataVisualizationFlags GetDataVisualizationFlags();`
- L74 _public prototype_ `virtual bool CanVisualizationFlagBeChangedByUI(uint32 Flag) override;`
- L79 _private member_ `uint32 GlobalJointsDataVisualizationFlags = static_cast<uint32>(EChaosVDJointsDataVisualizationFlags::ActorConnector | EChaosVDJointsDataVisualizationFlags::DrawKinematic);` — `UPROPERTY(config, meta = (Bitmask, BitmaskEnum = "/Script/ChaosVD.EChaosVDJointsDataVisualizationFlags"))` — Set of flags to enable/disable visualization of specific joint constraints data as debug draw

#### Free symbols / members of external scopes

- L30 _prototype_ `ENUM_CLASS_FLAGS(EChaosVDJointsDataVisualizationFlags);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDMiscSettings.h` (Private)


#### struct `FChaosVDRecentFile`  
`struct FChaosVDRecentFile`  
_L10-52_
- reflection: `USTRUCT()`
- desc: Structure with the details about a recently open CVD file
- L16 _public member_ `FString FileName;` — `UPROPERTY(config)` — Path to the CVD File
- L20 _public member_ `FDateTime LastOpenTime;` — `UPROPERTY(config)` — Timestamp of the last time the CVD opened this file
- L22 _public function_ `FChaosVDRecentFile()`
- L25 _public function_ `FChaosVDRecentFile(const FString& InProjectName, FDateTime InLastOpenTime) : FileName(InProjectName) , LastOpenTime(InLastOpenTime)`
- L38 _public function_ `bool operator<(const FChaosVDRecentFile& Other) const`
- L43 _public function_ `bool operator==(const FChaosVDRecentFile& Other) const`
- L48 _public function_ `bool operator==(const FString& OtherProjectName) const`

#### struct `FChaosVDRecentFile::FRecentFilesSortPredicate`  
`struct FRecentFilesSortPredicate`  
_L30-36_
- L32 _public function_ `bool operator()( const FChaosVDRecentFile& A, const FChaosVDRecentFile& B ) const`

#### class `UChaosVDMiscSettings`  
`class UChaosVDMiscSettings : public UChaosVDSettingsObjectBase`  
_L58-74_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDSettingsObjectBase`
- desc: General non-core CVD settings
- L65 _public member_ `TArray<FChaosVDRecentFile> RecentFiles;` — `UPROPERTY(config)` — List of recently opened files
- L69 _public member_ `int32 MaxRecentFilesNum = 10;` — `UPROPERTY(config)` — Maximum number of recent files we can keep track of
- L73 _public member_ `TMap<FString, bool> DataChannelEnabledState;` — `UPROPERTY(config)` — Saved data channel enabled state

### `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDParticleVisualizationSettings.h` (Private)


#### enum `EChaosVDGeometryVisibilityFlags`  
`enum class EChaosVDGeometryVisibilityFlags : uint8`  
_L13-28_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L15 _public enumerator_ `None = 0 UMETA(Hidden)`
- L17 _public enumerator_ `Query = 1 << 1` — Draws all geometry that is for Query Only
- L19 _public enumerator_ `Simulated = 1 << 2` — Draws all geometry that is for [Physics Collision] or [Physics Collision and Query only]
- L21 _public enumerator_ `Simple = 1 << 3` — Draws all simple geometry
- L23 _public enumerator_ `Complex = 1 << 4` — Draws all complex geometry
- L25 _public enumerator_ `ShowHeightfields = 1 << 5` — Draws heightfields even if complex is not selected
- L27 _public enumerator_ `ShowDisabledParticles = 1 << 6` — Draws all particles that are in a disabled state

#### enum `EChaosVDParticleDataVisualizationFlags`  
`enum class EChaosVDParticleDataVisualizationFlags : uint32`  
_L32-49_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L34 _public enumerator_ `None = 0 UMETA(Hidden)`
- L35 _public enumerator_ `Velocity = 1 << 0`
- L36 _public enumerator_ `AngularVelocity = 1 << 1`
- L37 _public enumerator_ `Acceleration = 1 << 2`
- L38 _public enumerator_ `AngularAcceleration = 1 << 3`
- L39 _public enumerator_ `LinearImpulse = 1 << 4`
- L40 _public enumerator_ `AngularImpulse = 1 << 5`
- L41 _public enumerator_ `ClusterConnectivityEdge = 1 << 6`
- L42 _public enumerator_ `CenterOfMass = 1 << 7`
- L43 _public enumerator_ `DrawDataOnlyForSelectedParticle = 1 << 8`
- L45 _public enumerator_ `Bounds = 1 << 10`
- L46 _public enumerator_ `InflatedBounds = 1 << 11`
- L48 _public enumerator_ `EnableDraw = 1 << 9`

#### struct `FChaosDebugDrawColorsByShapeType`  
`struct FChaosDebugDrawColorsByShapeType`  
_L55-80_
- reflection: `USTRUCT()`
- desc: Structure holding the settings using to debug draw Particles shape based on their shape type on the Chaos Visual Debugger
- L61 _public member_ `FColor SimpleTypeColor = FColor(0, 158, 115);` — `UPROPERTY(EditAnywhere, Category=DebugDraw)` — Color used for Sphere, Plane, Cube, Capsule, Cylinder, tapered shapes
- L65 _public member_ `FColor ConvexColor = FColor(240, 228, 66);` — `UPROPERTY(EditAnywhere, Category=DebugDraw)` — Color used for convex shapes
- L69 _public member_ `FColor HeightFieldColor = FColor(86, 180, 233);` — `UPROPERTY(EditAnywhere, Category=DebugDraw)` — Color used for heightfield
- L73 _public member_ `FColor TriangleMeshColor = FColor(213, 94, 0);` — `UPROPERTY(EditAnywhere, Category=DebugDraw)` — Color used for triangle meshes
- L77 _public member_ `FColor LevelSetColor = FColor(204, 121, 167);` — `UPROPERTY(EditAnywhere, Category=DebugDraw)` — Color used for triangle LevelSets
- L79 _public prototype_ `FColor GetColorFromShapeType(Chaos::EImplicitObjectType ShapeType) const;`

#### struct `FChaosDebugDrawColorsByClientServer`  
`struct FChaosDebugDrawColorsByClientServer`  
_L84-98_
- reflection: `USTRUCT()`
- desc: Structure holding the settings using to debug draw Particles shape based on whether they are client or server objects (in PIE) Chaos Visual Debugger
- L90 _public member_ `FColor ServerBaseColor = FColor(231, 92, 80);` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color used for server shapes that are not awake or sleeping dynamic
- L94 _public member_ `FColor ClientBaseColor = FColor(0, 114, 178);` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color used for server shapes that are not awake or sleeping dynamic
- L96 _public prototype_ `FColor GetColorFromState(bool bIsServer, EChaosVDObjectStateType State) const;`
- L97 _public prototype_ `FColor GetColorAtIntensity(const FColor& InColor, float Intensity) const;`

#### enum `EChaosVDParticleDebugColorMode`  
`enum class EChaosVDParticleDebugColorMode`  
_L101-111_
- reflection: `UENUM()`
- L104 _public enumerator_ `None` — Draw particles with the default gray color
- L106 _public enumerator_ `State` — Draw particles with a specific color based on the recorded particle state
- L108 _public enumerator_ `ShapeType` — Draw particles with a specific color based on their shape type
- L110 _public enumerator_ `ClientServer` — Draw particles with a specific color based on if they are a Server Particle or Client particle

#### struct `FChaosDebugDrawColorsByState`  
`struct FChaosDebugDrawColorsByState`  
_L115-136_
- reflection: `USTRUCT()`
- desc: Structure holding the settings using to debug draw Particles shape based on their state on the Chaos Visual Debugger
- L121 _public member_ `FColor DynamicColor = FColor(253, 246, 98);` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color used for dynamic particles
- L125 _public member_ `FColor SleepingColor = FColor(231, 92, 80);` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color used for sleeping particles
- L129 _public member_ `FColor KinematicColor = FColor(0, 114, 178);` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color used for kinematic particles
- L133 _public member_ `FColor StaticColor = FColor(150, 159, 156);` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color used for static particles
- L135 _public prototype_ `FColor GetColorFromState(EChaosVDObjectStateType State) const;`

#### struct `FChaosParticleDataDebugDrawColors`  
`struct FChaosParticleDataDebugDrawColors`  
_L139-177_
- reflection: `USTRUCT()`
- L145 _public member_ `FLinearColor VelocityColor = FColor::Green;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color to apply to the Velocity vector when drawing it
- L149 _public member_ `FLinearColor AngularVelocityColor = FColor::Blue;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color to apply to the Angular Velocity vector when drawing it
- L153 _public member_ `FLinearColor AccelerationColor = FColor::Orange;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color to apply to the Acceleration vector when drawing it
- L157 _public member_ `FLinearColor AngularAccelerationColor = FColor::Silver;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color to apply to the Angular Acceleration vector when drawing it
- L161 _public member_ `FLinearColor LinearImpulseColor = FColor::Turquoise;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color to apply to the Linear Impulse when drawing it
- L165 _public member_ `FLinearColor AngularImpulseColor = FColor::Emerald;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color to apply to the Angular Impulse vector when drawing it
- L169 _public member_ `FLinearColor CenterOfMassColor = FColor::Red;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color to apply the debug drawn sphere representing the center of mass location
- L173 _public member_ `FLinearColor ConnectivityDataColor = FColor::Yellow;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Color to apply to when drawing the connectivity data
- L175 _public prototype_ `FColor GetColorForDataID(EChaosVDParticleDataVisualizationFlags DataID, bool bIsSelected = false) const;`
- L176 _public prototype_ `const FLinearColor& GetLinearColorForDataID(EChaosVDParticleDataVisualizationFlags DataID) const;`

#### class `UChaosVDParticleVisualizationColorSettings`  
`class UChaosVDParticleVisualizationColorSettings : public UChaosVDVisualizationSettingsObjectBase`  
_L216-232_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDVisualizationSettingsObjectBase`
- L222 _public member_ `EChaosVDParticleDebugColorMode ParticleColorMode = EChaosVDParticleDebugColorMode::State;` — `UPROPERTY(config, EditAnywhere, Category = "Colors Mode")`
- L225 _public member_ `FChaosDebugDrawColorsByShapeType ColorsByShapeType;` — `UPROPERTY(config, EditAnywhere, Category = "Colors By Shape", meta=(EditCondition = "ParticleColorMode == EChaosVDParticleDebugColorMode::ShapeType", EditConditionHides))`
- L228 _public member_ `FChaosDebugDrawColorsByState ColorsByParticleState;` — `UPROPERTY(config, EditAnywhere, Category = "Colors By State", meta=(EditCondition = "ParticleColorMode == EChaosVDParticleDebugColorMode::State", EditConditionHides))`
- L231 _public member_ `FChaosDebugDrawColorsByClientServer ColorsByClientServer;` — `UPROPERTY(config, EditAnywhere, Category = "Colors By Solver", meta=(EditCondition = "ParticleColorMode == EChaosVDParticleDebugColorMode::ClientServer", EditConditionHides))`

#### class `UChaosVDParticleVisualizationDebugDrawSettings`  
`class UChaosVDParticleVisualizationDebugDrawSettings : public UChaosVDVisualizationSettingsObjectBase`  
_L235-298_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDVisualizationSettingsObjectBase`
- L241 _public member_ `bool bShowDebugText = false;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)`
- L245 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriority = ESceneDepthPriorityGroup::SDPG_World;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — The depth priority used for while drawing contact data. Can be World or Foreground (with this one the shapes will be drawn on top of the geometry and be always visible)
- L249 _public member_ `float VelocityScale = 0.5f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Scale to apply to the Velocity vector before draw it. Unit is cm/s
- L253 _public member_ `float AngularVelocityScale = 50.0f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Scale to apply to the Angular Velocity vector before draw it. Unit is rad/s
- L257 _public member_ `float AccelerationScale = 0.005f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Scale to apply to the Acceleration vector before draw it. Unit is cm/s2
- L261 _public member_ `float AngularAccelerationScale = 0.5f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Scale to apply to the Angular Acceleration vector before draw it. Unit is rad/s2
- L265 _public member_ `float LinearImpulseScale = 0.001f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Scale to apply to the Linear Impulse vector before draw it. Unit is g.m/s
- L269 _public member_ `float AngularImpulseScale = 0.1f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Scale to apply to the Angular Impulse vector before draw it. Unit is g.m2/s
- L273 _public member_ `float CenterOfMassRadius = 10.0f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Radius to use when creating the sphere that will represent the center of mass location
- L277 _public member_ `bool bDrawTriMeshBVH = false;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Should a triangle mesh's BVH draw.
- L281 _public member_ `int TriMeshBVHDrawLevel = 0;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw, meta = (EditCondition = "bDrawTriMeshBVH", EditConditionHides))` — What depth of a triangle mesh's BVH to draw. Level '-1' means draw everything.
- L284 _public member_ `FChaosParticleDataDebugDrawColors ColorSettings;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)`
- L286 _public prototype_ `float GetScaleFortDataID(EChaosVDParticleDataVisualizationFlags DataID) const;`
- L288 _public prototype_ `static void SetDataDebugDrawVisualizationFlags(EChaosVDParticleDataVisualizationFlags Flags);`
- L290 _public prototype_ `static EChaosVDParticleDataVisualizationFlags GetDataDebugDrawVisualizationFlags();`
- L292 _public prototype_ `virtual bool CanVisualizationFlagBeChangedByUI(uint32 Flag) override;`
- L297 _private member_ `uint32 ParticleDataVisualizationFlags = static_cast<uint32>(EChaosVDParticleDataVisualizationFlags::Velocity | EChaosVDParticleDataVisualizationFlags::AngularVelocity);` — `UPROPERTY(config, meta = (Bitmask, BitmaskEnum = "/Script/ChaosVD.EChaosVDParticleDataVisualizationFlags"))` — Set of flags to enable/disable visualization of specific particle data as debug draw

#### class `UChaosVDParticleVisualizationSettings`  
`class UChaosVDParticleVisualizationSettings : public UChaosVDVisualizationSettingsObjectBase`  
_L301-312_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDVisualizationSettingsObjectBase`
- L306 _public prototype_ `static void SetGeometryVisualizationFlags(EChaosVDGeometryVisibilityFlags Flags);`
- L307 _public prototype_ `static EChaosVDGeometryVisibilityFlags GetGeometryVisualizationFlags();`
- L311 _public member_ `uint32 GeometryVisibilityFlags = static_cast<uint32>(EChaosVDGeometryVisibilityFlags::Simulated | EChaosVDGeometryVisibilityFlags::Simple | EChaosVDGeometryVisibilityFlags::ShowHeightfields | EChaosVDGeometryVisibilityFlags::Complex | EChaosVDGeometryVisibilityFlags::Query);` — `UPROPERTY(config, meta = (Bitmask, BitmaskEnum = "/Script/ChaosVD.EChaosVDGeometryVisibilityFlags"))` — Set of flags to enable/disable visibility of specific types of geometry/particles

#### Free symbols / members of external scopes

- L50 _prototype_ `ENUM_CLASS_FLAGS(EChaosVDParticleDataVisualizationFlags);`
- L179 _namespace_ `namespace Chaos`
- L179 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L179 _namespace_ `namespace ParticleDataUnitsStrings` (scope `Chaos::VisualDebugger`)
- L181 _variable_ `static FString Velocity = TEXT("cm/` (scope `Chaos::VisualDebugger::ParticleDataUnitsStrings`)
- L182 _variable_ `static FString AngularVelocity = TEXT("rad` (scope `Chaos::VisualDebugger::ParticleDataUnitsStrings`)
- L183 _variable_ `static FString Acceleration = TEXT("cm/` (scope `Chaos::VisualDebugger::ParticleDataUnitsStrings`)
- L184 _variable_ `static FString AngularAcceleration = TEXT("rad` (scope `Chaos::VisualDebugger::ParticleDataUnitsStrings`)
- L185 _variable_ `static FString LinearImpulse = TEXT("g.m` (scope `Chaos::VisualDebugger::ParticleDataUnitsStrings`)
- L186 _variable_ `static FString AngularImpulse = TEXT("g.m` (scope `Chaos::VisualDebugger::ParticleDataUnitsStrings`)
- L188 _function_ `static FString GetUnitByID(EChaosVDParticleDataVisualizationFlags DataID)` (scope `Chaos::VisualDebugger::ParticleDataUnitsStrings`)

### `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDSceneQueryVisualizationSettings.h` (Private)


#### enum `EChaosVDSceneQueryVisualizationFlags`  
`enum class EChaosVDSceneQueryVisualizationFlags: uint32`  
_L11-22_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Set of visualization flags options for Scene Queries
- L13 _public enumerator_ `None = 0 UMETA(Hidden)`
- L14 _public enumerator_ `EnableDraw = 1 << 0`
- L15 _public enumerator_ `DrawLineTraceQueries = 1 << 1`
- L16 _public enumerator_ `DrawSweepQueries = 1 << 2`
- L17 _public enumerator_ `DrawOverlapQueries = 1 << 3`
- L18 _public enumerator_ `DrawHits = 1 << 4`
- L19 _public enumerator_ `OnlyDrawSelectedQuery = 1 << 5`
- L20 _public enumerator_ `HideEmptyQueries = 1 << 6`
- L21 _public enumerator_ `HideSubQueries = 1 << 7`

#### enum `EChaosVDSQFrameVisualizationMode`  
`enum class EChaosVDSQFrameVisualizationMode : uint8`  
_L27-34_
- reflection: `UENUM()`
- desc: Available scene query Visualization Modes
- L31 _public enumerator_ `AllEnabledQueries` — All the recorded scene queries for the current frame, that passes the visualization flag filter will be shown
- L33 _public enumerator_ `PerSolverRecordingOrder` — Scene queries will be shown one at the time, in the order they were recorded (per solver), controlled by the Scene Query browser timeline

#### class `UChaosVDSceneQueriesVisualizationSettings`  
`class UChaosVDSceneQueriesVisualizationSettings : public UChaosVDVisualizationSettingsObjectBase`  
_L37-64_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDVisualizationSettingsObjectBase`
- L43 _public prototype_ `static void SetDataVisualizationFlags(EChaosVDSceneQueryVisualizationFlags NewFlags);`
- L44 _public prototype_ `static EChaosVDSceneQueryVisualizationFlags GetDataVisualizationFlags();`
- L46 _public prototype_ `virtual bool CanVisualizationFlagBeChangedByUI(uint32 Flag) override;`
- L50 _public member_ `bool bShowText = false;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — If true, any debug draw text available will be drawn
- L55 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriority = ESceneDepthPriorityGroup::SDPG_World;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — The depth priority used for while drawing. Can be World or Foreground (with this one the shapes representing the query will be drawn on top of the geometry and be always visible)
- L58 _public member_ `EChaosVDSQFrameVisualizationMode CurrentVisualizationMode = EChaosVDSQFrameVisualizationMode::AllEnabledQueries;` — `UPROPERTY()`
- L63 _private member_ `uint32 GlobalSceneQueriesVisualizationFlags = static_cast<uint32>(EChaosVDSceneQueryVisualizationFlags::DrawHits | EChaosVDSceneQueryVisualizationFlags::DrawLineTraceQueries);` — `UPROPERTY(config, meta = (Bitmask, BitmaskEnum = "/Script/ChaosVD.EChaosVDSceneQueryVisualizationFlags"))` — Set of flags to enable/disable visualization of specific scene queries data as debug draw

#### Free symbols / members of external scopes

- L23 _prototype_ `ENUM_CLASS_FLAGS(EChaosVDSceneQueryVisualizationFlags);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDSolverTrackSettings.h` (Private)


#### class `UChaosVDSolverTrackSettings`  
`class UChaosVDSolverTrackSettings : public UChaosVDSettingsObjectBase`  
_L13-23_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDSettingsObjectBase`
- desc: Settings object for Solver Tracks configuration
- L22 _public member_ `EChaosVDSyncTimelinesMode SyncMode = EChaosVDSyncTimelinesMode::RecordedTimestamp;` — `UPROPERTY(config, EditAnywhere, Category="Timeline Sync")` — Sync mode used to keep all timelines in sync during playback. Not: Not all solver tracks support all modes. When an unsupported mode is selected, the default mode, RecordedTimestamp, will be used

### `Plugins/ChaosVD/Source/ChaosVD/Private/TEDS/ChaosVDCustomIconDataStorageFactory.h` (Private)


#### class `UChaosVDCustomIconDataStorageFactory`  
`class UChaosVDCustomIconDataStorageFactory : public UEditorDataStorageFactory`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _private prototype_ `virtual ~UChaosVDCustomIconDataStorageFactory() override = default;`
- L18 _private prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/TEDS/ChaosVDDataStorageVisibilityQueries.h` (Private)


#### class `UChaosVDDataStorageVisibilityQueries`  
`class UChaosVDDataStorageVisibilityQueries : public UEditorDataStorageFactory`  
_L9-34_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L14 _public prototype_ `~UChaosVDDataStorageVisibilityQueries() override = default;`
- L16 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L23 _private prototype_ `void RegisterParticleAddVisibilityColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Adds the Visibility columns to new actors that do not have one already.
- L28 _private prototype_ `void RegisterParticleVisibilityToColumnQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the visibility set on an actor and copies it to the Data Storage if they differ.
- L33 _private prototype_ `void RegisterVisibilityColumnToParticleQuery(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Takes the visibility stored in the Data Storage and copies it to the actor's visibility if the FTypedElementSyncBackToWorldTag has been set and the visibility differ.

### `Plugins/ChaosVD/Source/ChaosVD/Private/TEDS/ChaosVDParentDataStorageFactory.h` (Private)


#### struct `FChaosVDTableRowParentColumn`  
`struct FChaosVDTableRowParentColumn final : public FEditorDataStorageColumn`  
_L10-18_
- reflection: `USTRUCT(meta = (DisplayName = "Parent"))`
- inherits: `FEditorDataStorageColumn`
- L14 _public member_ `UE::Editor::DataStorage::RowHandle ParentObject = UE::Editor::DataStorage::InvalidRowHandle;`
- L16 _public member_ `TArray<UE::Editor::DataStorage::RowHandle> Children;`
- L17 _public member_ `TSet<UE::Editor::DataStorage::RowHandle> ChildrenSet;`

#### class `UChaosVDParentDataStorageFactory`  
`class UChaosVDParentDataStorageFactory : public UEditorDataStorageFactory`  
_L26-48_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L31 _public prototype_ `virtual ~UChaosVDParentDataStorageFactory() override = default;`
- L33 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L40 _private prototype_ `void RegisterAddParentColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Checks rows with actors that don't have a parent column yet if one needs to be added whenever the row is marked for updates.
- L45 _private prototype_ `void RegisterUpdateOrRemoveParentColumn(UE::Editor::DataStorage::ICoreProvider& DataStorage) const;` — Updates the parent column with the parent from the actor or removes it if there's no parent associated with the actor anymore.
- L47 _private member_ `TSharedPtr<FChaosVDBaseSceneObject> DefaultRootObjectForCVDActors;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/TEDS/ChaosVDParticleEditorDataFactory.h` (Private)


#### struct `FChaosVDObjectDataTag`  
`struct FChaosVDObjectDataTag final : public FEditorDataStorageTag`  
_L17-20_
- reflection: `USTRUCT(meta = (DisplayName = "CVD Object Data"))`
- inherits: `FEditorDataStorageTag`
- desc: TEDS tag added to any object that belongs to a CVD

#### struct `FTypedElementFromCVDWorldTag`  
`struct FTypedElementFromCVDWorldTag final : public FEditorDataStorageTag`  
_L26-29_
- reflection: `USTRUCT(meta = (DisplayName = "From CVD World"))`
- inherits: `FEditorDataStorageTag`
- desc: TEDS tag added to any object that belongs to a CVD World

#### struct `FChaosVDActiveObjectTag`  
`struct FChaosVDActiveObjectTag final : public FEditorDataStorageTag`  
_L35-38_
- reflection: `USTRUCT(meta = (DisplayName = "CVD Active Object"))`
- inherits: `FEditorDataStorageTag`
- desc: TEDS tag added to any object that belongs to a CVD World, and is active (visible in the scene outliner, and with valid data)

#### class `UChaosVDParticleEditorDataFactory`  
`class UChaosVDParticleEditorDataFactory : public UEditorDataStorageFactory`  
_L41-50_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L46 _public prototype_ `virtual ~UChaosVDParticleEditorDataFactory() override = default;`
- L48 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::ICompatibilityProvider& DataStorageCompatibility) override;`
- L49 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/TEDS/ChaosVDTedsUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L9 _namespace_ `namespace VD` (scope `Chaos`)
- L9 _namespace_ `namespace TedsUtils` (scope `Chaos::VD`)
- L12 _function_ `template<typename ColumnType, typename ObjectType> static void AddColumnToObject(ObjectType* Object)` (scope `Chaos::VD::TedsUtils`)
- L30 _function_ `template<typename ColumnType> static void AddColumnToHandle(UE::Editor::DataStorage::RowHandle Handle)` (scope `Chaos::VD::TedsUtils`)
- L44 _function_ `template<typename ColumnType> static void BatchAddOrRemoveColumn(TConstArrayView<UE::Editor::DataStorage::RowHandle> Rows)` (scope `Chaos::VD::TedsUtils`)
- L55 _function_ `template<typename ColumnType> static void RemoveColumnToHandle(UE::Editor::DataStorage::RowHandle Handle)` (scope `Chaos::VD::TedsUtils`)
- L69 _function_ `template<typename ColumnType, typename ObjectType> static void RemoveColumnFromObject(ObjectType* Object)` (scope `Chaos::VD::TedsUtils`)
- L88 _function_ `template<typename ObjectType> static UE::Editor::DataStorage::RowHandle AddObjectToDataStorage(ObjectType* Object, UE::Editor::DataStorage::ICoreProvider* DataStorageInterface, UE::Editor::DataStorage::ICompatibilityProvider* DataStorageCompatibility)` (scope `Chaos::VD::TedsUtils`)
- L102 _function_ `template<typename ObjectType> static UE::Editor::DataStorage::RowHandle AddObjectToDataStorage(ObjectType* Object)` (scope `Chaos::VD::TedsUtils`)
- L112 _function_ `template<typename ObjectType> static void RemoveObjectToFromDataStorage(ObjectType* Object, UE::Editor::DataStorage::ICompatibilityProvider* DataStorageCompatibility)` (scope `Chaos::VD::TedsUtils`)
- L121 _function_ `template<typename ObjectType> static void RemoveObjectToFromDataStorage(ObjectType* Object)` (scope `Chaos::VD::TedsUtils`)

### `Plugins/ChaosVD/Source/ChaosVD/Private/TabSpawers/ChaosVDSceneQueryBrowserTab.h` (Private)


#### class `FChaosVDSceneQueryBrowserTab`  
`class FChaosVDSceneQueryBrowserTab : public FChaosVDTabSpawnerBase`  
_L11-27_
- inherits: `FChaosVDTabSpawnerBase`
- desc: Spawns and handles and instance for the visual debugger Scene Query browser tab
- L14 _public function_ `FChaosVDSceneQueryBrowserTab(const FName& InTabID, const TSharedPtr<FTabManager>& InTabManager, const TWeakPtr<SChaosVDMainTab>& InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget)`
- L20 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`
- L21 _public prototype_ `virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed) override;`
- L23 _public function_ `TWeakPtr<SChaosVDSceneQueryBrowser> GetSceneQueryDataInspectorInstance() const`
- L26 _protected member_ `TSharedPtr<SChaosVDSceneQueryBrowser> SceneQueryBrowser;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/ChaosVDCombinedTraceFile.h` (Private)


#### class `Chaos::VisualDebugger::CombinedTraceFile::FInnerFileHandle`  
`class FInnerFileHandle : public IFileHandle`  
_L12-36_
- inherits: `IFileHandle`
- desc: File handle that allows other systems, like UE Trace, to read data from a combined file, as it was a separated file
- L15 _public prototype_ `virtual int64 Tell() override;`
- L16 _public prototype_ `virtual bool Seek(int64 NewPosition) override;`
- L17 _public prototype_ `virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd = 0) override;`
- L18 _public prototype_ `virtual bool Read(uint8* Destination, int64 BytesToRead) override;`
- L19 _public prototype_ `virtual bool ReadAt(uint8* Destination, int64 BytesToRead, int64 Offset) override;`
- L20 _public prototype_ `virtual bool Write(const uint8* Source, int64 BytesToWrite) override;`
- L21 _public prototype_ `virtual bool Flush(const bool bFullFlush = false) override;`
- L22 _public prototype_ `virtual bool Truncate(int64 NewSize) override;`
- L23 _public prototype_ `virtual int64 Size() override;`
- L25 _public prototype_ `FInnerFileHandle(const FString& InContainerFilePath, int64 DataOffset, int64 DataSize);`
- L27 _public function_ `bool IsValidHandle() const`
- L33 _private member_ `TUniquePtr<IFileHandle> ContainerFileHandle;`
- L34 _private member_ `int64 DataOffset;`
- L35 _private member_ `int64 DataSize;`

#### struct `Chaos::VisualDebugger::CombinedTraceFile::FFileEntry`  
`struct FFileEntry`  
_L38-48_
- L40 _public member_ `int64 StartPos = 0;`
- L41 _public member_ `int64 Size = 0;`
- L43 _public function_ `void Serialize(FArchive& Ar)`

#### struct `Chaos::VisualDebugger::CombinedTraceFile::FFileTable`  
`struct FFileTable`  
_L50-58_
- L52 _public member_ `TArray<FFileEntry> Files;`
- L54 _public function_ `void Serialize(FArchive& Ar)`

#### struct `Chaos::VisualDebugger::CombinedTraceFile::FFileTableHeader`  
`struct FFileTableHeader`  
_L60-68_
- L62 _public member_ `int64 FileTablePos = 0;`
- L64 _public function_ `void Serialize(FArchive& Ar)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L9 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L9 _namespace_ `namespace CombinedTraceFile` (scope `Chaos::VisualDebugger`)
- L70 _function_ `inline FArchive& operator<<(FArchive& Ar, FFileTableHeader& Data)` (scope `Chaos::VisualDebugger::CombinedTraceFile`)
- L76 _function_ `inline FArchive& operator<<(FArchive& Ar, FFileTable& Data)` (scope `Chaos::VisualDebugger::CombinedTraceFile`)
- L82 _function_ `inline FArchive& operator<<(FArchive& Ar, FFileEntry& Data)` (scope `Chaos::VisualDebugger::CombinedTraceFile`)
- L94 _prototype_ `bool CombineFiles(const TArray<TUniquePtr<IFileHandle>>& InFileHandlesToCombine, const FString& InCombinedFilePathName);` (scope `Chaos::VisualDebugger::CombinedTraceFile`) — Takes an array of file handles and creates a new file that contains all their data, but that can be accessive as indivitual files later on @param InFileHandlesToCombine File handles to get the data to combine from @param InCombinedFilePathName Desired file path name for the generated file @return true if successful
- L101 _prototype_ `TArray<TUniquePtr<IFileHandle>> GetInnerFileHandles(const FString& InContainerFilePath);` (scope `Chaos::VisualDebugger::CombinedTraceFile`) — Take a file path to a combined CVD recording file, and returns file handles for the individual files inside it @param InContainerFilePath File path name to the combined CVD file @return Unique file handles for each one of the files that were combined

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/ChaosVDTraceAnalyzer.h` (Private)


#### class `FChaosVDTraceAnalyzer`  
`class FChaosVDTraceAnalyzer final : public UE::Trace::IAnalyzer`  
_L21-66_
- inherits: `UE::Trace::IAnalyzer`
- desc: Analyzer class for Chaos VD trace recordings. It processes all Chaos VD trace events and rebuilds the recording in a usable Recording struct handled by a custom Trace Provider
- L24 _public function_ `FChaosVDTraceAnalyzer(TraceServices::IAnalysisSession& Session, const TSharedRef<FChaosVDTraceProvider>& InChaosVDTraceProvider) : Session(Session), ChaosVDTraceProvider(InChaosVDTraceProvider)`
- L30 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L31 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L32 _public prototype_ `void PushSimulatedSolverTrackForGTData(const UE::Trace::IAnalyzer::FOnEventContext& Context, const UE::Trace::IAnalyzer::FEventData& EventData);`
- L33 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L35 _public function_ `FChaosVDTraceAnalysisComplete& OnAnalysisComplete()`
- L61 _private member_ `TraceServices::IAnalysisSession& Session;`
- L63 _private member_ `TSharedRef<FChaosVDTraceProvider> ChaosVDTraceProvider;`
- L65 _private member_ `FChaosVDTraceAnalysisComplete ChaosVDTraceAnalysisCompleteDelegate;`

#### enum `FChaosVDTraceAnalyzer::(anonymous)`  
``  
_L43-59_

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TraceServices`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE(FChaosVDTraceAnalysisComplete) class FChaosVDTraceAnalyzer final : public UE::Trace::IAnalyzer { public: FChaosVDTraceAnalyzer(TraceServices::IAnalysisSession& Session, const TSharedRef<FChaosVDTraceProvider>& InChaosVDTraceProvider) : Session(Session), ChaosVDTraceProvider(InChaosVDTraceProvider) { } virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override; virtual void OnAnalysisEnd() override; void PushSimulatedSolverTrackForGTData(const UE::Trace::IAnalyzer::FOnEventContext& Context, const UE::Trace::IAnalyzer::FEventData& EventData); virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override; FChaosVDTraceAnalysisComplete& OnAnalysisComplete() { return ChaosVDTraceAnalysisCompleteDelegate; } private: enum : uint16 { RouteId_ChaosVDSolverStepStart, RouteId_ChaosVDSolverStepEnd, RouteId_ChaosVDSolverFrameStart, RouteId_ChaosVDSolverFrameEnd, RouteId_ChaosVDBinaryDataStart, RouteId_ChaosVDBinaryDataContent, RouteId_ChaosVDBinaryDataEnd, RouteId_ChaosVDSolverSimulationSpace, RouteId_BeginFrame, RouteId_EndFrame, RouteId_ChaosVDParticleDestroyed,`
- L44 _enumerator_ `RouteId_ChaosVDSolverStepStart` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L45 _enumerator_ `RouteId_ChaosVDSolverStepEnd` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L46 _enumerator_ `RouteId_ChaosVDSolverFrameStart` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L47 _enumerator_ `RouteId_ChaosVDSolverFrameEnd` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L48 _enumerator_ `RouteId_ChaosVDBinaryDataStart` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L49 _enumerator_ `RouteId_ChaosVDBinaryDataContent` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L50 _enumerator_ `RouteId_ChaosVDBinaryDataEnd` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L51 _enumerator_ `RouteId_ChaosVDSolverSimulationSpace` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L52 _enumerator_ `RouteId_BeginFrame` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L53 _enumerator_ `RouteId_EndFrame` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L54 _enumerator_ `RouteId_ChaosVDParticleDestroyed` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L55 _enumerator_ `RouteId_ChaosVDNetworkTickOffset` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L56 _enumerator_ `RouteId_ChaosVDRolledBackDataID` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L57 _enumerator_ `RouteId_ChaosVDUsesAutoRTFM` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L58 _enumerator_ `RouteId_ChaosVDMiscHeaderData` (scope `FChaosVDTraceAnalyzer::__anon0198fb900103`)
- L69 _macro_ `#define CVD_READ_TRACE_VECTOR(Vector, VectorName, ValueType, EventData) \`
- L76 _macro_ `#define CVD_READ_TRACE_QUAT(Rotator, RotatorName, ValueType, EventData) \`
- L84 _macro_ `#define CVD_READ_TRACE_TRANSFORM(Transform, ValueType, EventData) \`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/ChaosVDTraceModule.h` (Private)


#### class `FChaosVDTraceModule`  
`class FChaosVDTraceModule : public TraceServices::IModule`  
_L7-23_
- inherits: `TraceServices::IModule`
- desc: Modular feature used by ChaosVD to interface with the Trace Services system
- L10 _public function_ `FChaosVDTraceModule()`
- L14 _public member_ `static FName ModuleName;`
- L17 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L18 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& InSession) override;`
- L19 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L20 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L21 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDArchiveHeaderProcessor.h` (Private)


#### class `FChaosVDArchiveHeaderProcessor`  
`class FChaosVDArchiveHeaderProcessor final : public FChaosVDDataProcessorBase`  
_L9-15_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced Archive headers
- L12 _public prototype_ `explicit FChaosVDArchiveHeaderProcessor();`
- L14 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDCharacterGroundConstraintDataProcessor.h` (Private)


#### class `FChaosVDCharacterGroundConstraintDataProcessor`  
`class FChaosVDCharacterGroundConstraintDataProcessor final : public FChaosVDDataProcessorBase`  
_L14-20_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced character ground constraints
- L17 _public prototype_ `explicit FChaosVDCharacterGroundConstraintDataProcessor();`
- L19 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDCollisionChannelsInfoDataProcessor.h` (Private)


#### class `FChaosVDCollisionChannelsInfoDataProcessor`  
`class FChaosVDCollisionChannelsInfoDataProcessor final : public FChaosVDDataProcessorBase`  
_L11-23_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that read any recorded collision channels info
- L14 _public prototype_ `explicit FChaosVDCollisionChannelsInfoDataProcessor();`
- L16 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`
- L20 _private prototype_ `bool ProcessPendingCollisionChannelData(const TArray<uint8>& InData);`
- L22 _private member_ `TArray<uint8> PendingCollisionChannelDataToProcess;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDConstraintDataProcessor.h` (Private)


#### class `FChaosVDConstraintDataProcessor`  
`class FChaosVDConstraintDataProcessor final : public FChaosVDDataProcessorBase`  
_L13-21_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced Constraints
- L16 _public prototype_ `explicit FChaosVDConstraintDataProcessor();`
- L18 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`
- L20 _public prototype_ `void AddConstraintToParticleIDMap(const FChaosVDConstraint& InConstraintData, int32 ParticleID, FChaosVDFrameStageData& InSolverStageData);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDJointConstraintDataProcessor.h` (Private)


#### class `FChaosVDJointConstraintDataProcessor`  
`class FChaosVDJointConstraintDataProcessor final : public FChaosVDDataProcessorBase`  
_L14-20_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced joint constraints
- L17 _public prototype_ `explicit FChaosVDJointConstraintDataProcessor();`
- L19 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDMidPhaseDataProcessor.h` (Private)


#### class `FChaosVDMidPhaseDataProcessor`  
`class FChaosVDMidPhaseDataProcessor final : public FChaosVDDataProcessorBase`  
_L14-22_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced MidPhases
- L17 _public prototype_ `explicit FChaosVDMidPhaseDataProcessor();`
- L19 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`
- L21 _public prototype_ `void AddMidPhaseToParticleIDMap(const TSharedPtr<FChaosVDParticlePairMidPhase>& MidPhaseData, int32 ParticleID, FChaosVDFrameStageData& InSolverStageData);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDParticleMetadataProcessor.h` (Private)


#### class `FChaosVDParticleMetadataProcessor`  
`class FChaosVDParticleMetadataProcessor final : public FChaosVDDataProcessorBase`  
_L10-17_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced Particles meta data
- L13 _public prototype_ `virtual ~FChaosVDParticleMetadataProcessor() override = default;`
- L14 _public prototype_ `explicit FChaosVDParticleMetadataProcessor();`
- L16 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDSceneQueryDataProcessor.h` (Private)


#### class `FChaosVDSceneQueryDataProcessor`  
`class FChaosVDSceneQueryDataProcessor final : public FChaosVDDataProcessorBase`  
_L10-16_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced scene queries data
- L13 _public prototype_ `explicit FChaosVDSceneQueryDataProcessor();`
- L15 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDSceneQueryVisitDataProcessor.h` (Private)


#### class `FChaosVDSceneQueryVisitDataProcessor`  
`class FChaosVDSceneQueryVisitDataProcessor final : public FChaosVDDataProcessorBase`  
_L9-15_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced SQ Visits
- L12 _public prototype_ `explicit FChaosVDSceneQueryVisitDataProcessor();`
- L14 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDSerializedNameEntryDataProcessor.h` (Private)


#### class `FChaosVDSerializedNameEntryDataProcessor`  
`class FChaosVDSerializedNameEntryDataProcessor final : public FChaosVDDataProcessorBase`  
_L10-16_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced Name Entries
- L13 _public prototype_ `explicit FChaosVDSerializedNameEntryDataProcessor();`
- L15 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDTraceImplicitObjectProcessor.h` (Private)


#### class `FChaosVDTraceImplicitObjectProcessor`  
`class FChaosVDTraceImplicitObjectProcessor final : public FChaosVDDataProcessorBase`  
_L10-16_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced Implicit objects
- L13 _public prototype_ `explicit FChaosVDTraceImplicitObjectProcessor();`
- L15 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Trace/DataProcessors/ChaosVDTraceParticleDataProcessor.h` (Private)


#### class `FChaosVDTraceParticleDataProcessor`  
`class FChaosVDTraceParticleDataProcessor final : public FChaosVDDataProcessorBase`  
_L10-16_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced Particles data
- L13 _public prototype_ `explicit FChaosVDTraceParticleDataProcessor();`
- L15 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Utils/ChaosVDMenus.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L9 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L9 _namespace_ `namespace Menus` (scope `Chaos::VisualDebugger`)
- L12 _variable_ `const FName ShowMenuName = "Ch` (scope `Chaos::VisualDebugger::Menus`)
- L14 _prototype_ `FToolMenuEntry CreateShowSubmenu();` (scope `Chaos::VisualDebugger::Menus`)
- L16 _prototype_ `FToolMenuEntry CreateSettingsSubmenu();` (scope `Chaos::VisualDebugger::Menus`)

### `Plugins/ChaosVD/Source/ChaosVD/Private/Visualizers/ChaosVDCharacterGroundConstraintsDataComponentVisualizer.h` (Private)


#### struct `FChaosVDCharacterGroundConstraintVisualizationDataContext`  
`struct FChaosVDCharacterGroundConstraintVisualizationDataContext : public FChaosVDVisualizationContext`  
_L15-22_
- inherits: `FChaosVDVisualizationContext`
- desc: Visualization context structure specific for character ground constraint visualizations
- L17 _public member_ `TSharedPtr<FChaosVDSolverDataSelectionHandle> DataSelectionHandle = nullptr;`
- L19 _public member_ `AChaosVDSolverInfoActor* SolverInfoActor = nullptr;`
- L21 _public prototype_ `bool IsVisualizationFlagEnabled(EChaosVDCharacterGroundConstraintDataVisualizationFlags Flag) const;`

#### class `FChaosVDCharacterGroundConstraintDataComponentVisualizer`  
`class FChaosVDCharacterGroundConstraintDataComponentVisualizer final : public FChaosVDComponentVisualizerBase`  
_L27-41_
- inherits: `FChaosVDComponentVisualizerBase`
- desc: Component visualizer in charge of generating debug draw visualizations for character ground constraints in a UChaosVDSolverCharacterGroundConstraintDataComponent
- L30 _public prototype_ `FChaosVDCharacterGroundConstraintDataComponentVisualizer();`
- L32 _public prototype_ `virtual void RegisterVisualizerMenus() override;`
- L34 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L36 _public prototype_ `virtual bool CanHandleClick(const HChaosVDComponentVisProxy& VisProxy) override;`
- L40 _protected prototype_ `void DrawConstraint(const UActorComponent* Component, const FChaosVDCharacterGroundConstraint& InConstraintData, FChaosVDCharacterGroundConstraintVisualizationDataContext& VisualizationContext, const FSceneView* View, FPrimitiveDrawInterface* PDI);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Visualizers/ChaosVDJointConstraintsDataComponentVisualizer.h` (Private)


#### struct `FChaosVDJointVisualizationDataContext`  
`struct FChaosVDJointVisualizationDataContext : public FChaosVDVisualizationContext`  
_L16-33_
- inherits: `FChaosVDVisualizationContext`
- desc: Visualization context structure specific for Joints visualizations
- L18 _public member_ `TSharedPtr<FChaosVDSolverDataSelectionHandle> DataSelectionHandle = MakeShared<FChaosVDSolverDataSelectionHandle>();`
- L20 _public member_ `bool bIsServerVisualizationEnabled = false;`
- L22 _public member_ `AChaosVDSolverInfoActor* SolverInfoActor = nullptr;`
- L24 _public member_ `const UChaosVDJointConstraintsVisualizationSettings* DebugDrawSettings = nullptr;`
- L26 _public member_ `bool bShowDebugText = false;`
- L28 _public function_ `bool IsVisualizationFlagEnabled(EChaosVDJointsDataVisualizationFlags Flag) const`

#### class `FChaosVDJointConstraintsDataComponentVisualizer`  
`class FChaosVDJointConstraintsDataComponentVisualizer final : public FChaosVDComponentVisualizerBase`  
_L38-53_
- inherits: `FChaosVDComponentVisualizerBase`
- desc: Component visualizer in charge of generating debug draw visualizations for Joint Constraints in a UChaosVDSolverJointConstraintDataComponent
- L41 _public prototype_ `FChaosVDJointConstraintsDataComponentVisualizer();`
- L43 _public prototype_ `virtual void RegisterVisualizerMenus() override;`
- L45 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L47 _public prototype_ `virtual bool CanHandleClick(const HChaosVDComponentVisProxy& VisProxy) override;`
- L51 _protected prototype_ `void DebugDrawAllAxis(const FChaosVDJointConstraint& InJointConstraintData, FChaosVDJointVisualizationDataContext& VisualizationContext, FPrimitiveDrawInterface* PDI, const float LineThickness, const FVector& InPosition, const Chaos::FMatrix33& InRotationMatrix, TConstArrayView<FLinearColor> AxisColors, bool bIsSelected);`
- L52 _protected prototype_ `void DrawJointConstraint(const UActorComponent* Component, const FChaosVDJointConstraint& InJointConstraintData, FChaosVDJointVisualizationDataContext& VisualizationContext, const FSceneView* View, FPrimitiveDrawInterface* PDI);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Visualizers/ChaosVDSceneQueryDataComponentVisualizer.h` (Private)


#### struct `FChaosVDSceneQuerySelectionContext`  
`struct FChaosVDSceneQuerySelectionContext : public FChaosVDSelectionContext`  
_L20-25_
- reflection: `USTRUCT()`
- inherits: `FChaosVDSelectionContext`
- desc: Struct used to pass data about a specific query to other objects
- L24 _public member_ `int32 SQVisitIndex = INDEX_NONE;`

#### struct `FChaosVDSceneQueryVisualizationDataContext`  
`struct FChaosVDSceneQueryVisualizationDataContext : public FChaosVDVisualizationContext`  
_L28-48_
- inherits: `FChaosVDVisualizationContext`
- desc: Visualization context structure specific for Scene Queries visualizations
- L30 _public member_ `TSharedPtr<FChaosVDSolverDataSelectionHandle> DataSelectionHandle = nullptr;`
- L33 _public function_ `void GenerateColor(int32 QueryID, bool bIsSelected)` — Generates a random color based on the selection state and query ID, which will be used to debug draw the scene query
- L41 _public member_ `FLinearColor RandomSeededColor = FLinearColor(EForceInit::ForceInit);`
- L42 _public member_ `FColor DebugDrawColor = FColor(EForceInit::ForceInit);`
- L43 _public member_ `FColor DebugDrawDarkerColor = FColor(EForceInit::ForceInit);`
- L44 _public member_ `FColor HitColor = FColor(EForceInit::ForceInit);`
- L46 _public member_ `Chaos::FConstImplicitObjectPtr InputGeometry = nullptr;`
- L47 _public member_ `TWeakPtr<FChaosVDGeometryBuilder> GeometryGenerator = nullptr;`

#### class `FChaosVDSceneQueryDataComponentVisualizer`  
`class FChaosVDSceneQueryDataComponentVisualizer final : public FChaosVDComponentVisualizerBase`  
_L53-78_
- inherits: `FChaosVDComponentVisualizerBase`
- desc: Component visualizer in charge of generating debug draw visualizations for scene queries in a ChaosVDSceneQueryDataComponent
- L57 _public prototype_ `FChaosVDSceneQueryDataComponentVisualizer();`
- L59 _public prototype_ `virtual void RegisterVisualizerMenus() override;`
- L61 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L64 _public prototype_ `virtual bool CanHandleClick(const HChaosVDComponentVisProxy& VisProxy) override;`
- L68 _private prototype_ `void DrawLineTraceQuery(const UActorComponent* Component, const FChaosVDQueryDataWrapper& SceneQueryData, FChaosVDSceneQueryVisualizationDataContext& VisualizationContext, const FSceneView* View, FPrimitiveDrawInterface* PDI);`
- L69 _private prototype_ `void DrawOverlapQuery(const UActorComponent* Component, const FChaosVDQueryDataWrapper& SceneQueryData, FChaosVDSceneQueryVisualizationDataContext& VisualizationContext, const FSceneView* View, FPrimitiveDrawInterface* PDI);`
- L70 _private prototype_ `void DrawSweepQuery(const UActorComponent* Component, const FChaosVDQueryDataWrapper& SceneQueryData, FChaosVDSceneQueryVisualizationDataContext& VisualizationContext, const FSceneView* View, FPrimitiveDrawInterface* PDI);`
- L71 _private prototype_ `void DrawHits(const UActorComponent* Component, const FChaosVDQueryDataWrapper& SceneQueryData, FPrimitiveDrawInterface* PDI, const FColor& InColor, FChaosVDSceneQueryVisualizationDataContext& VisualizationContext);`
- L73 _private prototype_ `void DrawSceneQuery(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI, const TSharedPtr<FChaosVDScene>& CVDScene, const TSharedPtr<FChaosVDRecording>& CVDRecording, FChaosVDSceneQueryVisualizationDataContext& VisualizationContext, const TSharedPtr<FChaosVDQueryDataWrapper>& Query);`
- L75 _private prototype_ `bool HasEndLocation(const FChaosVDQueryDataWrapper& SceneQueryData) const;`
- L77 _private prototype_ `bool IsHitSelected(int32 SQVisitIndex, const TSharedRef<FChaosVDSolverDataSelectionHandle>& CurrentSelection, const TSharedRef<FChaosVDSolverDataSelectionHandle>& SQVisitSelectionHandle);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Visualizers/ChaosVDSolverCollisionDataComponentVisualizer.h` (Private)


#### struct `FChaosVDCollisionDataSelectionContext`  
`struct FChaosVDCollisionDataSelectionContext : public FChaosVDSelectionContext`  
_L18-25_
- reflection: `USTRUCT()`
- inherits: `FChaosVDSelectionContext`
- L22 _public member_ `TSharedPtr<FChaosVDParticlePairMidPhase> MidPhase;`
- L23 _public member_ `FChaosVDConstraint* ConstraintDataPtr = nullptr;`
- L24 _public member_ `int32 ContactDataIndex = INDEX_NONE;`

#### class `FChaosVDSolverCollisionDataComponentVisualizer`  
`class FChaosVDSolverCollisionDataComponentVisualizer : public FChaosVDComponentVisualizerBase`  
_L27-43_
- inherits: `FChaosVDComponentVisualizerBase`
- L31 _public prototype_ `FChaosVDSolverCollisionDataComponentVisualizer();`
- L34 _public prototype_ `virtual void RegisterVisualizerMenus() override;`
- L36 _public prototype_ `virtual bool ShouldShowForSelectedSubcomponents(const UActorComponent* Component) override;`
- L37 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L39 _public prototype_ `virtual bool CanHandleClick(const HChaosVDComponentVisProxy& VisProxy) override;`
- L42 _protected prototype_ `void DrawMidPhaseData(const UActorComponent* Component, const TSharedPtr<FChaosVDParticlePairMidPhase>& MidPhase, const FChaosVDVisualizationContext& VisualizationContext, const FSceneView* View, FPrimitiveDrawInterface* PDI);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/ChaosVDRecordingControls.h` (Private)


#### class `FChaosVDRecordingControls`  
`class FChaosVDRecordingControls : public UE::TraceBasedDebuggers::FRecordingControls`  
_L24-89_
- inherits: `UE::TraceBasedDebuggers::FRecordingControls`
- L28 _public prototype_ `FChaosVDRecordingControls(const TSharedRef<SChaosVDMainTab>& InMainTab, const TSharedRef<UE::TraceBasedDebuggers::FRemoteSessionsManager>& InRemoteSessionManager);`
- L32 _protected prototype_ `virtual void AddToMenuInternal(FToolMenuSection& InSection) override;`
- L33 _protected prototype_ `virtual void OnGenerateTargetSessionSelectorInternal(FMenuBuilder& InMenuBuilder) override;`
- L34 _protected prototype_ `virtual FString GetSaveDirPath() const override;`
- L36 _protected prototype_ `virtual int32 GetMaxConnectionRetriesInternal() const override;`
- L37 _protected prototype_ `virtual UE::TraceBasedDebuggers::ETraceTransportMode GetTransportModeOverrideForTargetTypeInternal(EBuildTargetType InBuildTarget) const override;`
- L39 _protected prototype_ `virtual bool ConnectToLiveSession_RelayInternal(const FGuid& InSessionId) override;`
- L40 _protected prototype_ `virtual bool ConnectToLiveSession_DirectInternal(const FGuid& InSessionId) override;`
- L42 _protected prototype_ `[[nodiscard]] virtual TNotNull<TUniquePtr<UE::TraceBasedDebuggers::FStartRecordingCommandMessage>> BuildStartRecordingParamsInternal() override;`
- L43 _protected prototype_ `virtual void SendStartRecordingCommandInternal(const FMessageAddress& InAddress, TUniquePtr<UE::TraceBasedDebuggers::FStartRecordingCommandMessage> InStartRecordingCommand) override;`
- L44 _protected prototype_ `virtual void SendStopRecordingCommandInternal(const FMessageAddress& InAddress) override;`
- L46 _protected prototype_ `virtual bool IsRecordingAvailableForSessionInternal(const TSharedRef<UE::TraceBasedDebuggers::FSessionInfo>& InSessionInfo) const override;`
- L47 _protected prototype_ `virtual void OnToggleRecordingStateInternal(const TSharedRef<UE::TraceBasedDebuggers::FSessionInfo>& InSessionInfo) override;`
- L49 _protected prototype_ `virtual void CloseSessionByRemoteSessionIDInternal(const FGuid& InSessionId) override;`
- L51 _protected prototype_ `virtual const UE::TraceBasedDebuggers::FTraceSessionDescriptor& GetCurrentSessionDescriptorInternal() override;`
- L54 _protected prototype_ `TSharedRef<SWidget> GenerateDataChannelsMenu();`
- L55 _protected prototype_ `TSharedRef<SWidget> GenerateDataChannelsButton();`
- L56 _protected prototype_ `TSharedRef<SWidget> GenerateLoadingModeSelector();`
- L57 _protected prototype_ `TSharedRef<SWidget> GenerateAdvancedRecordOptionsButton();`
- L58 _protected prototype_ `TSharedRef<SWidget> GenerateAdvancedRecordOptionsMenu();`
- L60 _protected prototype_ `void ToggleChannelEnabledState(FString ChannelName);`
- L61 _protected prototype_ `bool IsChannelEnabled(FString ChannelName);`
- L62 _protected prototype_ `bool CanChangeChannelEnabledState(FString ChannelName);`
- L64 _protected prototype_ `void GenerateCustomTargetsMenu(FMenuBuilder& MenuBuilder);`
- L66 _protected prototype_ `bool IsSessionPartOfCustomTargetSelection(FGuid SessionGuid);`
- L67 _protected prototype_ `void ToggleSessionSelectionInCustomTarget(FGuid SessionGuid);`
- L68 _protected prototype_ `bool CanSelectInCustomTarget(FGuid SessionGuid) const;`
- L70 _protected prototype_ `bool CanSelectMultiSessionTarget(FGuid SessionGuid) const;`
- L71 _protected prototype_ `bool CanSelectMultiSessionTarget(const TSharedRef<UE::TraceBasedDebuggers::FSessionInfo>& SessionInfoRef) const;`
- L73 _protected prototype_ `void ToggleAutoStartPlayback();`
- L74 _protected prototype_ `bool IsAutoStartPlaybackEnabled() const;`
- L75 _protected prototype_ `void ToggleSaveTracesToDisk();`
- L76 _protected prototype_ `bool IsSaveTracesToDiskEnabled();`
- L78 _protected prototype_ `FChaosVDSessionData* GetChaosDataForCurrentSession() const;`
- L80 _protected prototype_ `bool HasDataChannelsSupport() const;`
- L82 _protected prototype_ `bool CanChangeLoadingMode() const;`
- L84 _protected prototype_ `void ToggleMultiSessionSessionRecordingState(const TSharedRef<UE::TraceBasedDebuggers::FMultiSessionInfo>& InSessionInfoRef);`
- L86 _protected member_ `TWeakPtr<SChaosVDMainTab> MainTabWeakPtr;`
- L88 _protected member_ `EChaosVDLoadRecordedDataMode CurrentLoadingMode;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L12 _namespace_ `namespace Chaos`
- L12 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L22 _typedef_ `typedef Chaos::VisualDebugger::FChaosVDOptionalDataChannel FCVDDataChannel;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosBrowseTraceFileSourceModal.h` (Private)


#### enum `EChaosVDBrowseFileModalResponse`  
`enum class EChaosVDBrowseFileModalResponse`  
_L18-27_
- reflection: `UENUM()`
- desc: Available default folder locations where CVD files might be located
- L21 _public enumerator_ `LastOpened` — Opens the file picker at the last opened folder
- L23 _public enumerator_ `CurrentSaveFolder` — Opens the file picker at the currently configure save folder. The documents folder is the default
- L25 _public enumerator_ `LocalTraceStore` — Opens the file picker at local trace store folder (This is where live recordings are located)
- L26 _public enumerator_ `Cancel UMETA(Hidden)`

#### class `SChaosBrowseTraceFileSourceModal`  
`class SChaosBrowseTraceFileSourceModal : public SWindow`  
_L32-72_
- inherits: `SWindow`
- desc: Simple modal window that allows user pick a file to load and the mode to be used.
- L35 _public function_ `SLATE_BEGIN_ARGS(SChaosBrowseTraceFileSourceModal)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L45 _public prototype_ `EChaosVDBrowseFileModalResponse ShowModal();` — Displays the dialog in a blocking fashion
- L48 _public function_ `EChaosVDLoadRecordedDataMode GetSelectedLoadingMode() const` — Returns the default connection mode to be used when loading the data for the selected session
- L55 _protected prototype_ `TSharedPtr<SWidget> GenerateConnectionModeWidget();`
- L56 _protected prototype_ `TSharedPtr<SWidget> GenerateSourceFolderWidget();`
- L58 _protected prototype_ `FReply OnOpenButtonClick();`
- L59 _protected prototype_ `FReply OnCancelButtonClick();`
- L61 _protected member_ `TSharedPtr<SChaosVDNameListPicker> NamePickerWidget;`
- L63 _protected member_ `TMap<FName, EChaosVDBrowseFileModalResponse> LocationNameToResponseID;`
- L65 _protected member_ `FName CurrentSelectedLocationName;`
- L67 _protected member_ `EChaosVDBrowseFileModalResponse UserSelectedResponse = EChaosVDBrowseFileModalResponse::LastOpened;`
- L69 _protected member_ `EChaosVDLoadRecordedDataMode LoadingMode = EChaosVDLoadRecordedDataMode::SingleSource;`
- L71 _protected member_ `bool bUserClickedOpen = false;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDBrowseSessionsModal.h` (Private)


#### struct `FChaosVDTraceSessionInfo`  
`struct FChaosVDTraceSessionInfo`  
_L19-25_
- desc: Structure containing info about a Trace Session
- L21 _public member_ `uint32 TraceID = 0;`
- L22 _public member_ `uint32 IPAddress = 0;`
- L23 _public member_ `uint32 ControlPort = 0;`
- L24 _public member_ `bool bIsValid = false;`

#### class `SChaosVDBrowseSessionsModal`  
`class SChaosVDBrowseSessionsModal : public SWindow`  
_L31-99_
- inherits: `SWindow`
- desc: Modal window used to find, show and select active Trace Sessions to be used with Chaos Visual Debugger
- L34 _public function_ `SLATE_BEGIN_ARGS(SChaosVDBrowseSessionsModal)`
- L39 _public prototype_ `virtual ~SChaosVDBrowseSessionsModal() override;`
- L41 _public prototype_ `void Construct(const FArguments& InArgs);`
- L44 _public prototype_ `EAppReturnType::Type ShowModal();` — Displays the dialog in a blocking fashion
- L47 _public function_ `EAppReturnType::Type GetResponse() const` — Response that triggered the closing of this modal
- L53 _public prototype_ `FChaosVDTraceSessionInfo GetSelectedTraceInfo();` — Returns information about the active trace session selected
- L56 _public function_ `FString GetSelectedTraceStoreAddress() const` — Returns the address of the trace store selected while looking for active Trace Sessions
- L62 _public function_ `EChaosVDLoadRecordedDataMode GetSelectedConnectionMode() const` — Returns the default connection mode to be used when loading the data for the selected session
- L67 _public prototype_ `void ModalTick(float InDeltaTime);`
- L71 _protected prototype_ `TSharedPtr<SWidget> GenerateConnectionModeWidget();`
- L73 _protected prototype_ `bool CanOpenSession() const;`
- L75 _protected prototype_ `void UpdateCurrentSessionInfoMap();`
- L77 _protected prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L79 _protected prototype_ `void HandleSessionNameSelected(TSharedPtr<FName> SelectedName);`
- L81 _protected prototype_ `void OnTraceStoreAddressUpdated(const FText& InText, ETextCommit::Type CommitType);`
- L83 _protected member_ `TSharedPtr<SChaosVDNameListPicker> NamePickerWidget;`
- L85 _protected member_ `TSharedPtr<SEditableTextBox> TraceStoreAddressWidget;`
- L87 _protected member_ `TMap<FName, FChaosVDTraceSessionInfo> CurrentSessionInfosMap;`
- L89 _protected member_ `EAppReturnType::Type UserResponse = EAppReturnType::Cancel;`
- L91 _protected member_ `FString CurrentTraceStoreAddress;`
- L93 _protected member_ `FName CurrentTraceSessionSelected;`
- L95 _protected member_ `EChaosVDLoadRecordedDataMode ConnectionMode = EChaosVDLoadRecordedDataMode::SingleSource;`
- L97 _protected member_ `FDelegateHandle ModalTickHandle;`
- L98 _protected member_ `float AccumulatedTimeBetweenTicks = 0.0f;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace EAppReturnType`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDCollisionDataInspector.h` (Private)


#### class `SChaosVDCollisionDataInspector`  
`class SChaosVDCollisionDataInspector : public SChaosVDConstraintDataInspector`  
_L17-60_
- inherits: `SChaosVDConstraintDataInspector`
- L21 _public prototype_ `void SetCollisionDataListToInspect(TConstArrayView<TSharedPtr<FChaosVDParticlePairMidPhase>> CollisionDataList);`
- L23 _public prototype_ `virtual void SetConstraintDataToInspect(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InDataSelectionHandle) override;`
- L26 _protected prototype_ `virtual void SetupWidgets() override;`
- L27 _protected prototype_ `virtual void HandleSceneUpdated() override;`
- L29 _protected prototype_ `virtual void ClearInspector() override;`
- L31 _protected prototype_ `virtual TSharedRef<SWidget> GenerateHeaderWidget(FMargin Margin) override;`
- L32 _protected prototype_ `virtual TSharedRef<SWidget> GenerateDetailsViewWidget(FMargin Margin) override;`
- L34 _protected prototype_ `virtual FText GetParticleName(EChaosVDParticlePairIndex ParticleSlot, const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InSelectionHandle) const override;`
- L36 _protected prototype_ `void GetParticleIDForSelectedData(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InSelectionHandle, EChaosVDParticlePairIndex ParticleSlot, int32& OutSolverID, int32& OutParticleID) const;`
- L38 _protected prototype_ `virtual const TSharedRef<FChaosVDSolverDataSelectionHandle>& GetCurrentDataBeingInspected() const override;`
- L40 _protected prototype_ `void HandleCollisionDataEntryNameSelected(TSharedPtr<FName> SelectedName);`
- L42 _protected prototype_ `TSharedRef<FName> GenerateNameForCollisionDataItem(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InDataSelectionHandle) const;`
- L44 _protected prototype_ `TSharedPtr<IStructureDetailsView> CreateCollisionDataDetailsView();`
- L46 _protected prototype_ `virtual EVisibility GetDetailsSectionVisibility() const override;`
- L48 _protected prototype_ `virtual FReply SelectParticleForCurrentSelectedData(EChaosVDParticlePairIndex ParticleSlot) override;`
- L50 _protected prototype_ `TSharedPtr<FChaosVDSolverDataSelectionHandle> GetSelectionNameForName(const TSharedPtr<FName>& InName);`
- L52 _protected member_ `TSharedPtr<SChaosVDNameListPicker> CollisionDataAvailableList;`
- L54 _protected member_ `TMap<FName, TSharedPtr<FChaosVDSolverDataSelectionHandle>> CollisionDataByNameMap;`
- L56 _protected member_ `TSharedPtr<FName> CurrentSelectedName;`
- L58 _protected member_ `TSharedPtr<IStructureDetailsView> SecondaryCollisionDataDetailsPanel;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDConstraintDataInspector.h` (Private)


#### class `FReadOnlyCopyStructOnScope`  
`class FReadOnlyCopyStructOnScope : public FStructOnScope`  
_L21-27_
- inherits: `FStructOnScope`
- desc: Version of FStructOnScope that will take another FStructOnScope, and copy its data over. This allows us update a details panel without making a full rebuild when we want to inspect another struct that is of the same type As long we don't mind the copy and not being able to edit the source struct (which is 99% of the use cases in CVD)
- L24 _public prototype_ `explicit FReadOnlyCopyStructOnScope(const FStructOnScope& StructToCopy);`
- L26 _public prototype_ `void UpdateFromOther(const FStructOnScope& StructToCopy);`

#### class `SChaosVDConstraintDataInspector`  
`class SChaosVDConstraintDataInspector : public SCompoundWidget`  
_L29-97_
- inherits: `SCompoundWidget`
- L32 _public prototype_ `SChaosVDConstraintDataInspector();`
- L34 _public function_ `SLATE_BEGIN_ARGS(SChaosVDConstraintDataInspector)`
- L40 _public prototype_ `virtual ~SChaosVDConstraintDataInspector() override;`
- L43 _public prototype_ `void Construct(const FArguments& InArgs, const TWeakPtr<FChaosVDScene>& InScenePtr, const TSharedRef<SChaosVDMainTab>& InMainTab);` — Constructs this widget with InArgs
- L46 _public prototype_ `virtual void SetConstraintDataToInspect(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InDataSelectionHandle);` — Sets a new query data to be inspected
- L50 _protected prototype_ `virtual void SetupWidgets();`
- L52 _protected prototype_ `virtual TSharedRef<SWidget> GenerateDetailsViewWidget(FMargin Margin);`
- L53 _protected prototype_ `virtual TSharedRef<SWidget> GenerateHeaderWidget(FMargin Margin);`
- L55 _protected prototype_ `virtual FText GetParticleName(EChaosVDParticlePairIndex ParticleSlot) const;`
- L56 _protected prototype_ `virtual FText GetParticleName(const EChaosVDParticlePairIndex ParticleSlot, const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InSelectionHandle) const;`
- L58 _protected prototype_ `TSharedPtr<IStructureDetailsView> CreateDataDetailsView() const;`
- L60 _protected prototype_ `TSharedRef<SWidget> GenerateParticleSelectorButtons();`
- L62 _protected prototype_ `virtual FReply SelectParticleForCurrentSelectedData(EChaosVDParticlePairIndex ParticleSlot);`
- L64 _protected prototype_ `bool HasCompatibleStructScopeView(const TSharedRef<FChaosVDSolverDataSelectionHandle>& InSelectionHandle) const;`
- L66 _protected prototype_ `EVisibility GetOutOfDateWarningVisibility() const;`
- L67 _protected prototype_ `virtual EVisibility GetDetailsSectionVisibility() const;`
- L68 _protected prototype_ `EVisibility GetNothingSelectedMessageVisibility() const;`
- L70 _protected prototype_ `void RegisterSceneEvents();`
- L71 _protected prototype_ `void UnregisterSceneEvents() const;`
- L73 _protected prototype_ `virtual void HandleSceneUpdated();`
- L75 _protected prototype_ `virtual void ClearInspector();`
- L77 _protected prototype_ `FText GetParticleName_Internal(int32 SolverID, int32 ParticleID) const;`
- L79 _protected prototype_ `void SelectParticle(int32 SolverID, int32 ParticleID) const;`
- L81 _protected prototype_ `FChaosVDConstraintDataWrapperBase* GetConstraintDataFromSelectionHandle() const;`
- L83 _protected prototype_ `virtual const TSharedRef<FChaosVDSolverDataSelectionHandle>& GetCurrentDataBeingInspected() const;`
- L85 _protected member_ `TSharedPtr<IStructureDetailsView> MainDataDetailsView;`
- L86 _protected member_ `TSharedPtr<IStructureDetailsView> ConstraintSecondaryDataDetailsView;`
- L88 _protected member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;`
- L90 _protected member_ `mutable TSharedRef<FChaosVDSolverDataSelectionHandle> CurrentDataSelectionHandle;`
- L92 _protected member_ `TSharedPtr<FReadOnlyCopyStructOnScope> DataBeingInspectedCopy;`
- L94 _protected member_ `bool bIsUpToDate = true;`
- L96 _protected member_ `TWeakPtr<SChaosVDMainTab> MainTabWeakPtr;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDGameFramesPlaybackControls.h` (Private)


#### class `SChaosVDGameFramesPlaybackControls`  
`class SChaosVDGameFramesPlaybackControls : public SCompoundWidget , public FChaosVDPlaybackControllerObserver, public IChaosVDPlaybackControllerInstigator`  
_L18-55_
- inherits: `SCompoundWidget,FChaosVDPlaybackControllerObserver,IChaosVDPlaybackControllerInstigator`
- L22 _public function_ `explicit SChaosVDGameFramesPlaybackControls() : GameTrackInfoRef(MakeShared<FChaosVDTrackInfo>())`
- L27 _public function_ `SLATE_BEGIN_ARGS(SChaosVDGameFramesPlaybackControls)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FChaosVDPlaybackController>& InPlaybackController);`
- L33 _protected prototype_ `void OnFrameSelectionUpdated(int32 NewFrameIndex);`
- L35 _protected prototype_ `virtual void RegisterNewController(TWeakPtr<FChaosVDPlaybackController> NewController) override;`
- L37 _protected prototype_ `void HandleFramePlaybackButtonClicked(EChaosVDPlaybackButtonsID ButtonID);`
- L39 _protected prototype_ `virtual void HandlePlaybackControllerDataUpdated(TWeakPtr<FChaosVDPlaybackController> InController) override;`
- L41 _protected prototype_ `void HandleTimelineScrubStart();`
- L42 _protected prototype_ `void HandleTimelineScrubEnd();`
- L44 _protected prototype_ `bool CanPlayback() const;`
- L46 _protected prototype_ `bool IsPlaying() const;`
- L48 _protected prototype_ `int32 GetCurrentFrame() const;`
- L49 _protected prototype_ `int32 GetMinFrames() const;`
- L50 _protected prototype_ `int32 GetMaxFrames() const;`
- L51 _protected prototype_ `EChaosVDTimelineElementIDFlags GetElementEnabledFlags() const;`
- L53 _protected member_ `TSharedRef<FChaosVDTrackInfo> GameTrackInfoRef;`
- L54 _protected member_ `TSharedPtr<SChaosVDTimelineWidget> FramesTimelineWidget;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDGeometryTree.h` (Private)


#### struct `FChaosVDGeometryTreeItem`  
`struct FChaosVDGeometryTreeItem`  
_L21-29_
- L23 _public member_ `TWeakPtr<Chaos::VD::FChaosVDImplicitObjectView> ItemWeakPtr;`
- L24 _public member_ `TArray<TSharedPtr<FChaosVDGeometryTreeItem>> Children;`
- L25 _public member_ `FText Name = FText::GetEmpty();`
- L26 _public member_ `Chaos::EImplicitObjectType Type;`
- L27 _public member_ `FText CollisionEnabled = FText::GetEmpty();`
- L28 _public member_ `FText TraceType = FText::GetEmpty();`

#### class `SChaosVDGeometryTree`  
`class SChaosVDGeometryTree : public SCompoundWidget`  
_L37-94_
- inherits: `SCompoundWidget`
- desc: Tree for geometry hierarchy
- L41 _public function_ `SLATE_BEGIN_ARGS(SChaosVDGeometryTree)`
- L42 _public prototype_ `SLATE_EVENT(FChaosVDGeometryTreeItemSelected, OnItemSelected) SLATE_EVENT(FChaosVDGeometryTreeItemFocused, OnItemFocused) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FChaosVDScene>& InScenePtr);`
- L48 _public prototype_ `void SelectItem(const TSharedPtr<FChaosVDGeometryTreeItem>& ItemToSelect, ESelectInfo::Type Type);`
- L50 _public prototype_ `void ExpandAll(const TArray<TSharedPtr<FChaosVDGeometryTreeItem>>& Items);`
- L52 _public prototype_ `void SetDataToInspect(const FChaosVDSceneParticle* Particle);`
- L54 _public prototype_ `void RefreshTreeData(bool bRegenTree);`
- L56 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L60 _protected prototype_ `void HandleFocusRequest(TSharedPtr<FChaosVDGeometryTreeItem> InFocusedItem);`
- L62 _protected prototype_ `TSharedRef<ITableRow> GenerateGeometryDataRow(TSharedPtr<FChaosVDGeometryTreeItem> GeometryData, const TSharedRef<STableViewBase>& OwnerTable);`
- L64 _protected prototype_ `void GeometryTreeSelectionChanged(TSharedPtr<FChaosVDGeometryTreeItem> SelectedItem, ESelectInfo::Type Type);`
- L66 _protected prototype_ `void OnGetChildrenForGeometryItem(TSharedPtr<FChaosVDGeometryTreeItem> GeomEntry, TArray<TSharedPtr<FChaosVDGeometryTreeItem>>& OutGeoms);`
- L68 _protected prototype_ `void GenerateTree(Chaos::VD::FChaosVDImplicitObjectView* InLeafImplicitObject, TArray<TSharedPtr<FChaosVDGeometryTreeItem>>& Nodes);`
- L70 _protected prototype_ `void GenerateTree(const Chaos::FImplicitObject* InLeafImplicitObject, TArray<TSharedPtr<FChaosVDGeometryTreeItem>>& Nodes, int ShapeIndex = 0);`
- L72 _protected member_ `TSharedPtr<STreeView<TSharedPtr<FChaosVDGeometryTreeItem>>> GeometryTreeWidget;`
- L74 _protected member_ `TArray<TSharedPtr<FChaosVDGeometryTreeItem>> InternalGeometryTreeData;`
- L76 _protected member_ `FChaosVDGeometryTreeItemSelected GeometryItemSelectedDelegate;`
- L77 _protected member_ `FChaosVDGeometryTreeItemFocused GeometryItemFocusedDelegate;`
- L79 _protected member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;`
- L81 _protected member_ `const FChaosVDSceneParticle* SelectedParticle = nullptr;`
- L82 _protected member_ `FChaosVDBaseSceneObject::EStreamingState ParticleStreamingState = FChaosVDBaseSceneObject::EStreamingState::Hidden;`
- L93 _public member_ `static FColumnNames ColumnNames;`

#### struct `SChaosVDGeometryTree::FColumnNames`  
`struct FColumnNames`  
_L86-91_
- L88 _public member_ `const FName Type = FName("Typ`
- L89 _public member_ `const FName TraceType = FName("Col`
- L90 _public member_ `const FName CollisionEnabled = FName("Col`

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_DELEGATE_TwoParams(FChaosVDGeometryTreeItemSelected, const TSharedPtr<FChaosVDGeometryTreeItem>&, ESelectInfo::Type) DECLARE_DELEGATE_OneParam(FChaosVDGeometryTreeItemFocused, const TSharedPtr<FChaosVDGeometryTreeItem>&) class SChaosVDGeometryTree : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SChaosVDGeometryTree) {} SLATE_EVENT(FChaosVDGeometryTreeItemSelected, OnItemSelected) SLATE_EVENT(FChaosVDGeometryTreeItemFocused, OnItemFocused) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FChaosVDScene>& InScenePtr); void SelectItem(const TSharedPtr<FChaosVDGeometryTreeItem>& ItemToSelect, ESelectInfo::Type Type); void ExpandAll(const TArray<TSharedPtr<FChaosVDGeometryTreeItem>>& Items); void SetDataToInspect(const FChaosVDSceneParticle* Particle); void RefreshTreeData(bool bRegenTree); virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; protected: void HandleFocusRequest(TSharedPtr<FChaosVDGeometryTreeItem> InFocusedItem); TSharedRef<ITableRow> GenerateGeometryDataRow(TSharedPtr<FChaosVDGeometryTreeItem> GeometryData, const TSharedRef<STableViewBase>& OwnerTable); void GeometryTreeSelectionChanged(TSharedPtr<FChaosVDGeometryTreeItem> SelectedItem, ESelectInfo::Type Type); void OnGetChildrenForGeometryItem(TSharedPtr<FChaosVDGeometryTreeItem> GeomEntry, TArray<TSharedPtr<FChaosVDGeometryTreeItem>>& OutGeoms); void GenerateTree(Chaos::VD::FChaosVDImplicitObjectView* InLeafImplicit`
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FChaosVDGeometryTreeItemFocused, const TSharedPtr<FChaosVDGeometryTreeItem>&) class SChaosVDGeometryTree : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SChaosVDGeometryTree) {} SLATE_EVENT(FChaosVDGeometryTreeItemSelected, OnItemSelected) SLATE_EVENT(FChaosVDGeometryTreeItemFocused, OnItemFocused) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FChaosVDScene>& InScenePtr); void SelectItem(const TSharedPtr<FChaosVDGeometryTreeItem>& ItemToSelect, ESelectInfo::Type Type); void ExpandAll(const TArray<TSharedPtr<FChaosVDGeometryTreeItem>>& Items); void SetDataToInspect(const FChaosVDSceneParticle* Particle); void RefreshTreeData(bool bRegenTree); virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; protected: void HandleFocusRequest(TSharedPtr<FChaosVDGeometryTreeItem> InFocusedItem); TSharedRef<ITableRow> GenerateGeometryDataRow(TSharedPtr<FChaosVDGeometryTreeItem> GeometryData, const TSharedRef<STableViewBase>& OwnerTable); void GeometryTreeSelectionChanged(TSharedPtr<FChaosVDGeometryTreeItem> SelectedItem, ESelectInfo::Type Type); void OnGetChildrenForGeometryItem(TSharedPtr<FChaosVDGeometryTreeItem> GeomEntry, TArray<TSharedPtr<FChaosVDGeometryTreeItem>>& OutGeoms); void GenerateTree(Chaos::VD::FChaosVDImplicitObjectView* InLeafImplicitObject, TArray<TSharedPtr<FChaosVDGeometryTreeItem>>& Nodes); void GenerateTree(const Chaos::FImplicitObject* InLeafImplicitO`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDGeometryTreeRow.h` (Private)


#### class `SChaosVDGeometryTreeRow`  
`class SChaosVDGeometryTreeRow : public SMultiColumnTableRow<TSharedPtr<const FChaosVDGeometryTreeItem>>`  
_L16-38_
- inherits: `SMultiColumnTableRow<TSharedPtr<constFChaosVDGeometryTreeItem>>`
- desc: Widget used to represent a row on the geometry hierarchy tree view
- L19 _public function_ `SLATE_BEGIN_ARGS(SChaosVDGeometryTreeRow)`
- L22 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FChaosVDGeometryTreeItem>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L28 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L32 _private prototype_ `TSharedRef<SWidget> GenerateTextWidgetFromName(FName Name);`
- L33 _private prototype_ `TSharedRef<SWidget> GenerateTextWidgetFromText(const FText& Text);`
- L35 _private prototype_ `const FSlateBrush* GetTypeIcon() const;`
- L37 _private member_ `TSharedPtr<FChaosVDGeometryTreeItem> Item;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDLogBrowserToolbar.h` (Private)


#### class `UChaosVDLogBrowserToolbarMenuContext`  
`class UChaosVDLogBrowserToolbarMenuContext : public UObject`  
_L14-20_
- reflection: `UCLASS()`
- inherits: `UObject`
- L19 _public member_ `TWeakPtr<class SChaosVDLogBrowserToolbar> ToolbarInstanceWeak;`

#### class `SChaosVDLogBrowserToolbar`  
`class SChaosVDLogBrowserToolbar : public SCompoundWidget`  
_L25-53_
- inherits: `SCompoundWidget`
- desc: Toolbar Widget for the Recorded Log Browser tab
- L28 _public function_ `SLATE_BEGIN_ARGS(SChaosVDLogBrowserToolbar)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<SChaosVDRecordedLogBrowser>& InLogBrowserWeakPtr);`
- L36 _private prototype_ `void RegisterMainToolbarMenu();`
- L38 _private prototype_ `TSharedRef<SWidget> GenerateMainToolbarWidget();`
- L39 _private prototype_ `TSharedRef<SWidget> GenerateSearchBarWidget();`
- L41 _private prototype_ `void GenerateCategoriesSubMenu(UToolMenu* Menu);`
- L42 _private prototype_ `void GenerateFiltersSubMenu(UToolMenu* Menu, FText FiltersMenuLabel);`
- L44 _private prototype_ `void ToggleCategoryEnabledState(FName CategoryName);`
- L45 _private prototype_ `bool IsCategoryEnabled(FName CategoryName);`
- L47 _private prototype_ `void SetVerbosityFlags(EChaosVDLogVerbosityFlags NewFlags);`
- L48 _private prototype_ `EChaosVDLogVerbosityFlags GetVerbosityFlags() const;`
- L50 _private member_ `TWeakPtr<SChaosVDRecordedLogBrowser> LogBrowserInstanceWeakPtr;`
- L52 _private prototype_ `void HandleSearchTextChanged(const FText& Text);`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDNameListPicker.h` (Private)


#### class `SChaosVDNameListPicker`  
`class SChaosVDNameListPicker : public SCompoundWidget`  
_L16-58_
- inherits: `SCompoundWidget`
- desc: Widget that takes a list of String Views and creates a drop down menu for it for the Chaos Visual Debugger Tool.
- L19 _public function_ `SLATE_BEGIN_ARGS(SChaosVDNameListPicker)`
- L20 _public prototype_ `SLATE_EVENT(FChaosVDNameListSelected, OnNameSleceted) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `void UpdateNameList(TArray<TSharedPtr<FName>>&& NewNameList);` — Replaces the names in the list view @param NewNameList Array of Name to represent.
- L31 _public prototype_ `void SelectName(const TSharedPtr<FName>& NameToSelect, ESelectInfo::Type SelectionInfo = ESelectInfo::Direct);`
- L35 _protected prototype_ `bool HasElements() const;`
- L37 _protected prototype_ `FText GetCurrentDropDownButtonLabel() const;`
- L39 _protected prototype_ `void OnClickItem(TSharedPtr<FName> Item);`
- L41 _protected prototype_ `void OnListOpened();`
- L43 _protected prototype_ `TSharedRef<ITableRow> MakeNameItemForList(TSharedPtr<FName> Name, const TSharedRef<STableViewBase>& OwnerTable);`
- L45 _protected member_ `TSharedPtr<SComboButton> PickerComboButton;`
- L47 _protected member_ `TSharedPtr<STextBlock> DropDownButtonLabelTextBox;`
- L49 _protected member_ `TSharedPtr<SListView<TSharedPtr<FName>>> NameListWidget;`
- L51 _protected member_ `TSharedPtr<SListViewSelectorDropdownMenu<TSharedPtr<FName>>> NamesListDropdown;`
- L53 _protected member_ `TArray<TSharedPtr<FName>> CachedNameList;`
- L55 _protected member_ `TSharedPtr<FName> CurrentSelectedName;`
- L57 _protected member_ `FChaosVDNameListSelected NameSelectedDelegate;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FChaosVDNameListSelected, TSharedPtr<FName>) class SChaosVDNameListPicker : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SChaosVDNameListPicker){} SLATE_EVENT(FChaosVDNameListSelected, OnNameSleceted) SLATE_END_ARGS() void Construct(const FArguments& InArgs); void UpdateNameList(TArray<TSharedPtr<FName>>&& NewNameList); void SelectName(const TSharedPtr<FName>& NameToSelect, ESelectInfo::Type SelectionInfo = ESelectInfo::Direct); protected: bool HasElements() const; FText GetCurrentDropDownButtonLabel() const; void OnClickItem(TSharedPtr<FName> Item); void OnListOpened(); TSharedRef<ITableRow> MakeNameItemForList(TSharedPtr<FName> Name, const TSharedRef<STableViewBase>& OwnerTable); TSharedPtr<SComboButton> PickerComboButton; TSharedPtr<STextBlock> DropDownButtonLabelTextBox; TSharedPtr<SListView<TSharedPtr<FName>>> NameListWidget; TSharedPtr<SListViewSelectorDropdownMenu<TSharedPtr<FName>>> NamesListDropdown;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDPlaybackViewport.h` (Private)


#### class `SChaosVDPlaybackViewport`  
`class SChaosVDPlaybackViewport : public SEditorViewport, public FChaosVDPlaybackControllerObserver, public IChaosVDPlaybackControllerInstigator, public ICommonEditorViewportToolbarInfoProvider`  
_L28-119_
- inherits: `SEditorViewport,FChaosVDPlaybackControllerObserver,IChaosVDPlaybackControllerInstigator,ICommonEditorViewportToolbarInfoProvider`
- desc: Widget that contains the 3D viewport and playback controls
- L32 _public function_ `SLATE_BEGIN_ARGS(SChaosVDPlaybackViewport)`
- L35 _public prototype_ `virtual ~SChaosVDPlaybackViewport() override;`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FChaosVDScene> InScene, TWeakPtr<FChaosVDPlaybackController> InPlaybackController, TSharedPtr<FEditorModeTools> InEditorModeTools);`
- L40 _public prototype_ `virtual TSharedRef<SEditorViewport> GetViewportWidget() override;` — BEING ICommonEditorViewportToolbarInfoProvider interface
- L41 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L42 _public function_ `virtual void OnFloatingButtonClicked() override`
- L45 _public prototype_ `virtual void BindCommands() override;`
- L47 _public prototype_ `void BindGlobalUICommands();`
- L49 _public prototype_ `void UnBindEditorViewportUnsupportedCommands();`
- L51 _public prototype_ `virtual EVisibility GetTransformToolbarVisibility() const override;`
- L53 _public prototype_ `void GoToLocation(const FVector& InLocation) const;`
- L55 _public prototype_ `void ToggleUseFrameRateOverride();`
- L56 _public prototype_ `bool IsUsingFrameRateOverride() const;`
- L58 _public prototype_ `int32 GetCurrentTargetFrameRateOverride() const;`
- L60 _public prototype_ `void SetCurrentTargetFrameRateOverride(int32 NewTarget);`
- L62 _public function_ `TWeakPtr<FChaosVDScene> GetCVDScene()`
- L64 _public prototype_ `static void ExecuteExternalViewportInvalidateRequest();`
- L66 _public prototype_ `virtual void OnFocusViewportToSelection() override;`
- L68 _public prototype_ `void AddViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget, int32 ZOrder);`
- L72 _protected prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L74 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L75 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L77 _protected prototype_ `EVisibility GetTrackSelectorKeyVisibility() const;`
- L79 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L81 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L83 _protected prototype_ `virtual void RegisterNewController(TWeakPtr<FChaosVDPlaybackController> NewController )override;`
- L84 _protected prototype_ `virtual void HandlePlaybackControllerDataUpdated(TWeakPtr<FChaosVDPlaybackController> InController) override;`
- L85 _protected prototype_ `virtual void HandlePostSelectionChange(const UTypedElementSelectionSet* ChangesSelectionSet) override;`
- L87 _protected prototype_ `void HandleFramePlaybackControlInput(EChaosVDPlaybackButtonsID ButtonID);`
- L88 _protected prototype_ `void HandleFrameStagePlaybackControlInput(EChaosVDPlaybackButtonsID ButtonID);`
- L90 _protected prototype_ `void DeselectAll() const;`
- L91 _protected prototype_ `void HideSelected() const;`
- L92 _protected prototype_ `void ShowAll() const;`
- L94 _protected prototype_ `void OnPlaybackSceneUpdated();`
- L95 _protected prototype_ `void OnSolverVisibilityUpdated(int32 SolverID, bool bNewVisibility);`
- L96 _protected prototype_ `void BindToSceneUpdateEvents();`
- L97 _protected prototype_ `void UnbindFromSceneUpdateEvents();`
- L99 _protected prototype_ `void HandleExternalViewportInvalidateRequest();`
- L101 _protected member_ `TSharedPtr<FChaosVDTrackInfo> CurrentGameTrackInfo;`
- L103 _protected member_ `TSharedPtr<SChaosVDGameFramesPlaybackControls> GameFramesPlaybackControls;`
- L105 _protected member_ `TSharedPtr<FChaosVDPlaybackViewportClient> PlaybackViewportClient;`
- L107 _protected member_ `TWeakPtr<FChaosVDScene> CVDSceneWeakPtr;`
- L109 _protected member_ `TSharedPtr<FExtender> Extender;`
- L111 _protected member_ `TSharedPtr<FEditorModeTools> EditorModeTools;`
- L113 _protected prototype_ `DECLARE_MULTICAST_DELEGATE(FChaosVDViewportInvalidationRequestHandler) static inline FChaosVDViewportInvalidationRequestHandler ExternalViewportInvalidationRequestHandler = FChaosVDViewportInvalidationRequestHandler();`
- L116 _protected member_ `FDelegateHandle ExternalInvalidateHandlerHandle;`
- L118 _protected member_ `bool bIsPlaying = false;`

#### Free symbols / members of external scopes

- L113 _delegate_ `DECLARE_MULTICAST_DELEGATE(FChaosVDViewportInvalidationRequestHandler) static inline FChaosVDViewportInvalidationRequestHandler ExternalViewportInvalidationRequestHandler = FChaosVDViewportInvalidationRequestHandler();`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDRecordedLogBrowser.h` (Private)


#### class `FChaosVDBasicLogFilterExpressionContext`  
`class FChaosVDBasicLogFilterExpressionContext : public ITextFilterExpressionContext`  
_L31-47_
- inherits: `ITextFilterExpressionContext`
- L34 _public function_ `explicit FChaosVDBasicLogFilterExpressionContext(const TSharedRef<FChaosVDCachedLogItemEntry>& InTestLogEntry) : LogEntry(InTestLogEntry)`
- L39 _public prototype_ `virtual bool TestBasicStringExpression(const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode) const override;`
- L40 _public function_ `virtual bool TestComplexExpression(const FName& InKey, const FTextFilterString& InValue, const ETextFilterComparisonOperation InComparisonOperation, const ETextFilterTextComparisonMode InTextComparisonMode) const override`
- L46 _private member_ `const TSharedRef<FChaosVDCachedLogItemEntry> LogEntry;`

#### class `FChaosVDLogFilteringAsyncTask`  
`class FChaosVDLogFilteringAsyncTask : public FNonAbandonableTask`  
_L49-69_
- inherits: `FNonAbandonableTask`
- L53 _public function_ `explicit FChaosVDLogFilteringAsyncTask(const TWeakPtr<SChaosVDRecordedLogBrowser>& InLogBrowser) : LogBrowser(InLogBrowser)`
- L57 _public prototype_ `void DoWork();`
- L59 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L66 _private member_ `TWeakPtr<SChaosVDRecordedLogBrowser> LogBrowser;`
- L68 _private member_ `bool bAbandonTask = false;`

#### enum `EChaosVDLogVerbosityFlags`  
`enum class EChaosVDLogVerbosityFlags : uint8`  
_L72-80_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L74 _public enumerator_ `None = 0 UMETA(Hidden)`
- L75 _public enumerator_ `Messages = 1 << 0`
- L76 _public enumerator_ `Warnings = 1 << 1`
- L77 _public enumerator_ `Errors = 1 << 2`
- L79 _public enumerator_ `All = Messages | Warnings | Errors`

#### enum `EChaosVDLogBrowserDirtyFlags`  
`enum class EChaosVDLogBrowserDirtyFlags : uint8`  
_L84-92_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L86 _public enumerator_ `None = 0 UMETA(Hidden)`
- L87 _public enumerator_ `Categories = 1 << 0`
- L88 _public enumerator_ `Messages = 1 << 1`
- L89 _public enumerator_ `Verbosity = 1 << 2`
- L90 _public enumerator_ `Filtering = 1 << 3`
- L91 _public enumerator_ `Playback = 1 << 4`

#### class `FChaosVDLogInFlightFilteringTaskWrapper`  
`class FChaosVDLogInFlightFilteringTaskWrapper`  
_L95-137_
- L117 _public function_ `explicit FChaosVDLogInFlightFilteringTaskWrapper(const FContext& InContext, const TWeakPtr<SChaosVDRecordedLogBrowser>& LogBrowser) : Context(InContext)`
- L123 _public function_ `bool HasSameContext(const FContext& InContext) const`
- L128 _public function_ `FAsyncTask<FChaosVDLogFilteringAsyncTask>& GetAsyncTaskRef() const`
- L135 _private member_ `TUniquePtr<FAsyncTask<FChaosVDLogFilteringAsyncTask>> AsyncTask;`
- L136 _private member_ `FContext Context;`

#### struct `FChaosVDLogInFlightFilteringTaskWrapper::FContext`  
`struct FContext`  
_L98-115_
- L100 _public function_ `explicit FContext(uint64 CurrentLogEntriesNum, const FText& InTextFilter, EChaosVDLogBrowserDirtyFlags InDirtyFlags, EChaosVDLogVerbosityFlags InnVerbosityFlags) : CurrentLogEntriesNum(CurrentLogEntriesNum), DirtyFlags(InDirtyFlags), VerbosityFlags(InnVerbosityFlags), TextFilter(InTextFilter.ToString())`
- L108 _public member_ `uint64 CurrentLogEntriesNum;`
- L109 _public member_ `EChaosVDLogBrowserDirtyFlags DirtyFlags;`
- L110 _public member_ `EChaosVDLogVerbosityFlags VerbosityFlags;`
- L112 _public member_ `FName TextFilter;`
- L114 _public prototype_ `bool operator==(const FContext& OtherContext) const = default;`

#### class `SChaosVDRecordedLogBrowser`  
`class SChaosVDRecordedLogBrowser : public SCompoundWidget, public FChaosVDPlaybackControllerObserver, public IChaosVDPlaybackControllerInstigator`  
_L142-280_
- inherits: `SCompoundWidget,FChaosVDPlaybackControllerObserver,IChaosVDPlaybackControllerInstigator`
- desc: Widget used to render the recorded log stream in a CVD Recording
- L145 _public function_ `SLATE_BEGIN_ARGS(SChaosVDRecordedLogBrowser)`
- L150 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FChaosVDEngine>& InEngineInstance);`
- L157 _public prototype_ `void HandleSearchTextChanged(const FText& NewText);`
- L158 _public prototype_ `void UpdateLogLineSelectionFromGameTrack();`
- L160 _public prototype_ `void SetSessionName(const FString& NewSessionName);`
- L162 _public function_ `TSharedPtr<SChaosVDLogBrowserToolbar> GetToolBar()`
- L167 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L169 _public member_ `static const FName ToolBarName;`
- L171 _public function_ `bool GetShowAllCategories() const`
- L176 _public prototype_ `void ToggleShowAllCategories();`
- L179 _public function_ `template<typename Visitor> void EnumerateNonEmptyCategories(Visitor VisitorFunc)`
- L189 _public prototype_ `bool IsCategoryEnabled(FName CategoryName);`
- L190 _public prototype_ `void ToggleCategoryEnabled(FName CategoryName);`
- L192 _public prototype_ `void SetVerbosityFlags(EChaosVDLogVerbosityFlags NewFlags);`
- L194 _public function_ `EChaosVDLogVerbosityFlags GetVerbosityFlags() const`
- L207 _protected prototype_ `virtual void HandlePlaybackControllerDataUpdated(TWeakPtr<FChaosVDPlaybackController> InController) override;`
- L208 _protected prototype_ `virtual void HandleControllerTrackFrameUpdated(TWeakPtr<FChaosVDPlaybackController> InController, TWeakPtr<const FChaosVDTrackInfo> UpdatedTrackInfo, FGuid InstigatorGuid) override;`
- L212 _private prototype_ `void ProcessTrackUpdate(const TSharedRef<FChaosVDRecording>& InRecordingData, const TSharedRef<SChaosVDRecordedLogView>& InLogViewList, const TraceServices::ILogProvider& InLogProvider, const TWeakPtr<const FChaosVDTrackInfo>& InPendingTrackInfo);`
- L214 _private prototype_ `void SetDirtyFlag(EChaosVDLogBrowserDirtyFlags Flag);`
- L215 _private prototype_ `void RemoveDirtyFlag(EChaosVDLogBrowserDirtyFlags Flag);`
- L216 _private prototype_ `void ClearAllDirtyFlags();`
- L217 _private prototype_ `EChaosVDLogBrowserDirtyFlags GetDirtyFlags() const;`
- L219 _private prototype_ `FCategorizedItemsContainer& FindOrAddCategorizedItemsContainer_AssumesLocked(FName CategoryName);`
- L221 _private prototype_ `bool IsVerbosityEnabled(ELogVerbosity::Type VerbosityLevel);`
- L223 _private prototype_ `void ProcessPendingTrackUpdates();`
- L225 _private prototype_ `void Reset();`
- L227 _private prototype_ `FText GetFilterStatusText() const;`
- L228 _private prototype_ `FSlateColor GetFilterStatusTextColor() const;`
- L230 _private prototype_ `void CleanPendingCanceledTaskList();`
- L231 _private prototype_ `void UpdateBrowserContents();`
- L233 _private prototype_ `TSharedPtr<FChaosVDLogViewListItem> MakeLogItem_AssumesLocked(const TSharedPtr<FChaosVDCachedLogItemEntry>& InLogData);`
- L235 _private prototype_ `void ApplyFiltersAsync();`
- L237 _private prototype_ `void ApplyFilterToData_AssumesLocked(TConstArrayView<TSharedPtr<FChaosVDLogViewListItem>> InDataSource, const TSharedRef<TArray<TSharedPtr<FChaosVDLogViewListItem>>>& OutFilteredData);`
- L238 _private prototype_ `void RefreshLogListView();`
- L240 _private prototype_ `void HandleItemSelected(const TSharedPtr<FChaosVDLogViewListItem>& InLogViewListItem, ESelectInfo::Type SelectInfo);`
- L241 _private prototype_ `void HandleItemFocused(const TSharedPtr<FChaosVDLogViewListItem>& InLogViewListItem);`
- L244 _private prototype_ `template<typename FrameType, typename IndexesContainerType> void GetLogMessageIndexesForFrame(const TraceServices::ILogProvider& InLogProvider, const FrameType& InFrameData, IndexesContainerType& OutIndexesContainer);`
- L246 _private member_ `TQueue<TWeakPtr<const FChaosVDTrackInfo>> PendingTrackUpdatesToProcess;`
- L247 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> FilterEvaluator;`
- L249 _private member_ `TWeakPtr<FChaosVDEngine> EngineInstanceWeakPtr;`
- L251 _private member_ `TWeakPtr<SChaosVDRecordedLogView> LogViewWidget;`
- L253 _private member_ `TSharedPtr<TArray<TSharedPtr<FChaosVDLogViewListItem>>> FilteredCachedLogItems;`
- L254 _private member_ `TArray<TSharedPtr<FChaosVDLogViewListItem>> UnfilteredCachedLogItems;`
- L256 _private member_ `TArray<TSharedPtr<FChaosVDLogViewListItem>> SelectedLogItems;`
- L258 _private member_ `TArray<TSharedPtr<FChaosVDCachedLogItemEntry>> CachedReadLogData;`
- L259 _private member_ `TMap<uint64, TSharedPtr<FChaosVDLogViewListItem>> CachedLogItemsByID;`
- L260 _private member_ `TMap<FName, FCategorizedItemsContainer> CachedLogItemsByCategory;`
- L262 _private member_ `TSharedPtr<FChaosVDLogInFlightFilteringTaskWrapper> CurrentFilteringTask;`
- L263 _private member_ `TArray<TSharedRef<FChaosVDLogInFlightFilteringTaskWrapper>> FilteringTasksBeingCancelled;`
- L265 _private member_ `TSharedPtr<SChaosVDLogBrowserToolbar> ToolbarPtr;`
- L267 _private member_ `bool bShowAllCategories = true;`
- L269 _private member_ `EChaosVDLogVerbosityFlags VerbosityFlags = EChaosVDLogVerbosityFlags::All;`
- L271 _private member_ `EChaosVDLogBrowserDirtyFlags DirtyFlags = EChaosVDLogBrowserDirtyFlags::None;`
- L273 _private member_ `mutable FRWLock SourceDataCacheLock;`
- L274 _private member_ `mutable FRWLock DirtyFlagsLock;`
- L275 _private member_ `mutable FRWLock VerbosityFlagsLock;`
- L277 _private member_ `FString CurrentSessionName;`
- L283 _function_ `template <typename FrameType, typename IndexesContainerType> void SChaosVDRecordedLogBrowser::GetLogMessageIndexesForFrame(const TraceServices::ILogProvider& InLogProvider, const FrameType& InFrameData, IndexesContainerType& OutIndexesContainer)`

#### struct `SChaosVDRecordedLogBrowser::FCategorizedItemsContainer`  
`struct FCategorizedItemsContainer`  
_L199-204_
- L201 _public member_ `TArray<TSharedPtr<FChaosVDLogViewListItem>> Items;`
- L202 _public member_ `FName CategoryName = NAME_None;`
- L203 _public member_ `bool bIsEnabled = true;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace TraceServices`
- L286 _function_ `` (scope `SChaosVDRecordedLogBrowser::GetLogMessageIndexesForFrame`)

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDRecordedLogInstances.h` (Private)


#### class `SChaosVDRecordedLogInstances`  
`class SChaosVDRecordedLogInstances : public SCompoundWidget`  
_L20-59_
- inherits: `SCompoundWidget`
- desc: Widget that owns and manages multiple tabs of the recorded log browser widget
- L23 _public function_ `SLATE_BEGIN_ARGS(SChaosVDRecordedLogInstances)`
- L28 _public prototype_ `virtual ~SChaosVDRecordedLogInstances() override;`
- L30 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& InOwnerTab, const TSharedRef<FChaosVDEngine>& InEngineInstance);`
- L34 _private prototype_ `void HandleSessionOpened(const UE::TraceBasedDebuggers::FTraceSessionDescriptor& InSessionDescriptor);`
- L35 _private prototype_ `void HandleSessionClosed(const UE::TraceBasedDebuggers::FTraceSessionDescriptor& InSessionDescriptor);`
- L37 _private prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args, FName TabSessionID);`
- L39 _private prototype_ `void HandleTabClosed(TSharedRef<SDockTab> InTabClosed, FName TabSessionID);`
- L40 _private prototype_ `FName GenerateTabID();`
- L42 _private prototype_ `FName GetAvailableTabID();`
- L44 _private prototype_ `TSharedRef<FTabManager::FLayout> GenerateMainLayout();`
- L46 _private member_ `TSharedPtr<FTabManager> InstancesTabManager;`
- L48 _private member_ `TSharedPtr<FTabManager::FStack> TabsStack;`
- L50 _private member_ `TWeakPtr<FChaosVDEngine> EngineInstanceWeakPtr;`
- L52 _private member_ `TMap<FName, TWeakPtr<SDockTab>> ActiveTabsByID;`
- L53 _private member_ `TMap<FString, TWeakPtr<SDockTab>> ActiveTabsBySessionName;`
- L54 _private member_ `TMap<FName, FString> ActiveTabsBySessionNameByTabID;`
- L56 _private member_ `int32 LastInstanceNumberUsed = 0;`
- L58 _private member_ `TArray<FName> AvailableTabIDs;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDRecordedLogView.h` (Private)


#### struct `FChaosVDCachedLogItemEntry`  
`struct FChaosVDCachedLogItemEntry`  
_L14-21_
- L16 _public member_ `uint64 Index = 0;`
- L17 _public member_ `FName Category = NAME_None;`
- L18 _public member_ `ELogVerbosity::Type Verbosity = ELogVerbosity::Type::All;`
- L19 _public member_ `FString Message;`
- L20 _public member_ `double Time = 0.0;`

#### struct `FChaosVDLogViewListItem`  
`struct FChaosVDLogViewListItem`  
_L23-27_
- L25 _public member_ `TWeakPtr<FChaosVDCachedLogItemEntry> ItemWeakPtr;`
- L26 _public member_ `uint64 EntryIndex = 0;`

#### class `SChaosVDLogViewRow`  
`class SChaosVDLogViewRow : public SMultiColumnTableRow<TSharedPtr<const FChaosVDLogViewListItem>>`  
_L36-54_
- inherits: `SMultiColumnTableRow<TSharedPtr<constFChaosVDLogViewListItem>>`
- desc: Widget used to represent a row on the Scene Query Browser tree view
- L39 _public function_ `SLATE_BEGIN_ARGS(SChaosVDLogViewRow)`
- L42 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FChaosVDLogViewListItem>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L48 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L50 _public prototype_ `TSharedRef<SWidget> GenerateTextWidgetFromText(const FText& Text, const FLinearColor& InColor = FLinearColor::White);`
- L53 _private member_ `TSharedPtr<FChaosVDLogViewListItem> Item;`

#### class `SChaosVDRecordedLogView`  
`class SChaosVDRecordedLogView : public SCompoundWidget`  
_L59-105_
- inherits: `SCompoundWidget`
- L62 _public function_ `SLATE_BEGIN_ARGS(SChaosVDRecordedLogView)`
- L63 _public prototype_ `SLATE_EVENT(FChaosVDLogIetmItemSelected, OnItemSelected) SLATE_EVENT(FChaosVDLogItemFocused, OnItemFocused) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L69 _public prototype_ `int32 GetSelectedItems(TArray<TSharedPtr<FChaosVDLogViewListItem>>& OutItems);`
- L70 _public prototype_ `void SelectItem(const TSharedPtr<FChaosVDLogViewListItem>& ItemToSelect, ESelectInfo::Type Type);`
- L71 _public prototype_ `void SelectItems(TConstArrayView<TSharedPtr<FChaosVDLogViewListItem>> ItemsToSelect, ESelectInfo::Type Type);`
- L72 _public prototype_ `void ClearSelection();`
- L74 _public prototype_ `void SetSourceList(const TSharedPtr<TArray<TSharedPtr<FChaosVDLogViewListItem>>>& InSourceList);`
- L76 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L80 _protected prototype_ `void HandleFocusRequest(TSharedPtr<FChaosVDLogViewListItem> InFocusedItem);`
- L82 _protected prototype_ `TSharedRef<ITableRow> GenerateLogEntryRow(TSharedPtr<FChaosVDLogViewListItem> LogEntryData, const TSharedRef<STableViewBase>& OwnerTable);`
- L84 _protected prototype_ `void LogItemSelectionChanged(TSharedPtr<FChaosVDLogViewListItem> SelectedLogItem, ESelectInfo::Type Type);`
- L86 _protected member_ `TSharedPtr<SListView<TSharedPtr<FChaosVDLogViewListItem>>> LogListWidget;`
- L88 _protected member_ `TArray<TSharedPtr<FChaosVDLogViewListItem>> InternalItemSourceData;`
- L90 _protected member_ `FChaosVDLogIetmItemSelected ItemSelectedDelegate;`
- L91 _protected member_ `FChaosVDLogItemFocused ItemFocusedDelegate;`
- L103 _public member_ `static FColumNames ColumnNames;`

#### struct `SChaosVDRecordedLogView::FColumNames`  
`struct FColumNames`  
_L95-101_
- L97 _public member_ `const FName Time = FName("Tim`
- L98 _public member_ `const FName Category = FName("Cat`
- L99 _public member_ `const FName Verbosity = FName("Ver`
- L100 _public member_ `const FName Message = FName("Mes`

#### Free symbols / members of external scopes

- L56 _delegate_ `DECLARE_DELEGATE_TwoParams(FChaosVDLogIetmItemSelected, const TSharedPtr<FChaosVDLogViewListItem>&, ESelectInfo::Type) DECLARE_DELEGATE_OneParam(FChaosVDLogItemFocused, const TSharedPtr<FChaosVDLogViewListItem>&) class SChaosVDRecordedLogView : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SChaosVDRecordedLogView) {} SLATE_EVENT(FChaosVDLogIetmItemSelected, OnItemSelected) SLATE_EVENT(FChaosVDLogItemFocused, OnItemFocused) SLATE_END_ARGS() void Construct(const FArguments& InArgs); int32 GetSelectedItems(TArray<TSharedPtr<FChaosVDLogViewListItem>>& OutItems); void SelectItem(const TSharedPtr<FChaosVDLogViewListItem>& ItemToSelect, ESelectInfo::Type Type); void SelectItems(TConstArrayView<TSharedPtr<FChaosVDLogViewListItem>> ItemsToSelect, ESelectInfo::Type Type); void ClearSelection(); void SetSourceList(const TSharedPtr<TArray<TSharedPtr<FChaosVDLogViewListItem>>>& InSourceList); void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; protected: void HandleFocusRequest(TSharedPtr<FChaosVDLogViewListItem> InFocusedItem); TSharedRef<ITableRow> GenerateLogEntryRow(TSharedPtr<FChaosVDLogViewListItem> LogEntryData, const TSharedRef<STableViewBase>& OwnerTable); void LogItemSelectionChanged(TSharedPtr<FChaosVDLogViewListItem> SelectedLogItem, ESelectInfo::Type Type); TSharedPtr<SListView<TSharedPtr<FChaosVDLogViewListItem>>> LogListWidget; TArray<TSharedPtr<FChaosVDLogViewListItem>> InternalItemSourceData; FChaosVDLogIetmItemS`
- L57 _delegate_ `DECLARE_DELEGATE_OneParam(FChaosVDLogItemFocused, const TSharedPtr<FChaosVDLogViewListItem>&) class SChaosVDRecordedLogView : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SChaosVDRecordedLogView) {} SLATE_EVENT(FChaosVDLogIetmItemSelected, OnItemSelected) SLATE_EVENT(FChaosVDLogItemFocused, OnItemFocused) SLATE_END_ARGS() void Construct(const FArguments& InArgs); int32 GetSelectedItems(TArray<TSharedPtr<FChaosVDLogViewListItem>>& OutItems); void SelectItem(const TSharedPtr<FChaosVDLogViewListItem>& ItemToSelect, ESelectInfo::Type Type); void SelectItems(TConstArrayView<TSharedPtr<FChaosVDLogViewListItem>> ItemsToSelect, ESelectInfo::Type Type); void ClearSelection(); void SetSourceList(const TSharedPtr<TArray<TSharedPtr<FChaosVDLogViewListItem>>>& InSourceList); void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; protected: void HandleFocusRequest(TSharedPtr<FChaosVDLogViewListItem> InFocusedItem); TSharedRef<ITableRow> GenerateLogEntryRow(TSharedPtr<FChaosVDLogViewListItem> LogEntryData, const TSharedRef<STableViewBase>& OwnerTable); void LogItemSelectionChanged(TSharedPtr<FChaosVDLogViewListItem> SelectedLogItem, ESelectInfo::Type Type); TSharedPtr<SListView<TSharedPtr<FChaosVDLogViewListItem>>> LogListWidget; TArray<TSharedPtr<FChaosVDLogViewListItem>> InternalItemSourceData; FChaosVDLogIetmItemSelected ItemSelectedDelegate; FChaosVDLogItemFocused ItemFocusedDelegate; public: struct FColumNames {`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDSceneQueryBrowser.h` (Private)


#### class `UChaosVDSceneQueryBrowserToolbarMenuContext`  
`class UChaosVDSceneQueryBrowserToolbarMenuContext : public UObject`  
_L20-27_
- reflection: `UCLASS()`
- inherits: `UObject`
- L26 _public member_ `TWeakPtr<class SChaosVDSceneQueryBrowser> BrowserInstance;`

#### class `SChaosVDSceneQueryBrowser`  
`class SChaosVDSceneQueryBrowser : public SCompoundWidget`  
_L33-137_
- inherits: `SCompoundWidget`
- desc: Widget class of the Scene Query Browser window, where all available scene queries are shown for the currently visualized frame in a Scene Outliner kind of way
- L36 _public function_ `SLATE_BEGIN_ARGS(SChaosVDSceneQueryBrowser)`
- L43 _public prototype_ `virtual ~SChaosVDSceneQueryBrowser() override;`
- L45 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FChaosVDScene> Scene, TWeakPtr<FEditorModeTools> EditorModeTools);`
- L46 _public prototype_ `void RegisterSceneEvents();`
- L47 _public prototype_ `void UnregisterSceneEvents();`
- L49 _public member_ `static inline const FName ToolBarName = FName("Cha`
- L51 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L55 _protected prototype_ `void SelectSceneQuery(const TSharedPtr<const FChaosVDQueryDataWrapper>& InQuery, ESelectInfo::Type Type);`
- L56 _protected prototype_ `void SelectSceneQuery(const TSharedPtr<FChaosVDSceneQueryTreeItem>& SceneQueryTreeItem, ESelectInfo::Type Type);`
- L57 _protected prototype_ `void HandleExternalSelectionEvent(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InDataSelectionHandle);`
- L58 _protected prototype_ `void HandleSolverVisibilityChanged(int32 SolverID, bool bNewVisibility);`
- L60 _protected prototype_ `void RegisterMainToolbarMenu();`
- L62 _protected prototype_ `TSharedRef<SWidget> GenerateMainToolbarWidget();`
- L63 _protected prototype_ `TSharedRef<SWidget> GenerateSearchBarWidget();`
- L64 _protected prototype_ `TSharedRef<SWidget> GenerateQueryVisualizationModeWidget();`
- L66 _protected prototype_ `EVisibility GetUpdatesPausedMessageVisibility() const;`
- L68 _protected prototype_ `void HandleSearchTextChanged(const FText& NewText);`
- L70 _protected prototype_ `void HandleSettingsChanged(UObject* SettingsObject);`
- L72 _protected prototype_ `void ApplySettingsChange();`
- L74 _protected prototype_ `void UpdateBrowserContents();`
- L76 _protected prototype_ `void HandleSceneUpdated();`
- L78 _protected prototype_ `bool CanUpdate() const;`
- L80 _protected prototype_ `bool GetQueryTreeWidgetEnabled() const;`
- L82 _protected prototype_ `FText GetFilterStatusText() const;`
- L83 _protected prototype_ `FSlateColor GetFilterStatusTextColor() const;`
- L85 _protected prototype_ `TSharedRef<SWidget> GenerateQueriesPlaybackControls();`
- L87 _protected prototype_ `bool GetPlaybackControlsEnabled() const;`
- L89 _protected prototype_ `void HandlePlaybackControlInput(EChaosVDPlaybackButtonsID InputID);`
- L91 _protected prototype_ `void HandlePlaybackQueryIndexUpdated(int32 NewIndex);`
- L93 _protected prototype_ `FText GetPlaybackQueryControlText() const;`
- L94 _protected prototype_ `int32 GetCurrentMinPlaybackQueryIndex() const;`
- L95 _protected prototype_ `int32 GetCurrentMaxPlaybackQueryIndex() const;`
- L96 _protected prototype_ `int32 GetCurrentPlaybackQueryIndex() const;`
- L98 _protected prototype_ `TSharedPtr<FChaosVDSceneQueryTreeItem> MakeSceneQueryTreeItem(const TSharedPtr<FChaosVDQueryDataWrapper>& InQueryData, const UChaosVDSceneQueryDataComponent* DataComponent);`
- L100 _protected prototype_ `bool IsQueryDataVisible(const TSharedRef<FChaosVDQueryDataWrapper>& InQueryData);`
- L102 _protected prototype_ `void UpdateAllTreeItemsVisibility();`
- L103 _protected prototype_ `void UpdateTreeItemVisibility(const TSharedPtr<FChaosVDSceneQueryTreeItem>& InTreeItem);`
- L105 _protected prototype_ `void HandleTreeItemSelected(const TSharedPtr<FChaosVDSceneQueryTreeItem>& SelectedTreeItem, ESelectInfo::Type Type);`
- L106 _protected prototype_ `void HandleTreeItemFocused(const TSharedPtr<FChaosVDSceneQueryTreeItem>& FocusedTreeItem);`
- L108 _protected prototype_ `void ApplyFilterToData(TConstArrayView<TSharedPtr<FChaosVDSceneQueryTreeItem>> InDataSource, const TSharedRef<TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>>>& OutFilteredData);`
- L110 _protected prototype_ `TSharedRef<FString> GetCachedStringFromName(FName Name);`
- L112 _protected prototype_ `bool GetCachedSolverVisibility(int32 SolverID);`
- L114 _protected member_ `TSharedPtr<SChaosVDTimelineWidget> PlaybackControlsTimelineWidget;`
- L116 _protected member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;`
- L118 _protected member_ `TWeakPtr<FEditorModeTools> EditorModeToolsWeakPtr;`
- L120 _protected member_ `TWeakPtr<SChaosVDSceneQueryTree> SceneQueryTreeWidget;`
- L122 _protected member_ `TSharedPtr<TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>>> FilteredCachedTreeItems;`
- L123 _protected member_ `TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>> UnfilteredCachedTreeItems;`
- L124 _protected member_ `TMap<uint32, TSharedPtr<FChaosVDSceneQueryTreeItem>> CachedTreeItemsByID;`
- L125 _protected member_ `TMap<int32, bool> CachedSolverVisibilityByID;`
- L127 _protected member_ `TMap<FName, TSharedPtr<FString>> CachedNameToStringMap;`
- L129 _protected member_ `EChaosVDSQFrameVisualizationMode CurrentVisualizationMode = EChaosVDSQFrameVisualizationMode::AllEnabledQueries;`
- L131 _protected member_ `FText CurrentTextFilter;`
- L133 _protected member_ `int32 CurrentPlaybackIndex = 0;`
- L135 _protected member_ `bool bIsUpToDate = false;`
- L136 _protected member_ `bool bNeedsToUpdateSettings = true;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDSceneQueryDataInspector.h` (Private)


#### struct `FChaosVDSQSubQueryID`  
`struct FChaosVDSQSubQueryID`  
_L20-24_
- L22 _public member_ `int32 QueryID = INDEX_NONE;`
- L23 _public member_ `int32 SolverID = INDEX_NONE;`

#### class `SChaosVDSceneQueryDataInspector`  
`class SChaosVDSceneQueryDataInspector : public SCompoundWidget`  
_L29-114_
- inherits: `SCompoundWidget`
- desc: Widget for the Chaos Visual Debugger Scene Queries data inspector
- L32 _public prototype_ `SChaosVDSceneQueryDataInspector();`
- L33 _public prototype_ `void RegisterSceneEvents();`
- L34 _public prototype_ `void UnregisterSceneEvents();`
- L36 _public function_ `SLATE_BEGIN_ARGS(SChaosVDSceneQueryDataInspector)`
- L41 _public prototype_ `virtual ~SChaosVDSceneQueryDataInspector() override;`
- L44 _public prototype_ `void Construct(const FArguments& InArgs, const TWeakPtr<FChaosVDScene>& InScenePtr, const TSharedRef<SChaosVDMainTab>& InMainTab);` — Constructs this widget with InArgs
- L47 _public prototype_ `void SetQueryDataToInspect(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InDataSelectionHandle);` — Sets a new query data to be inspected
- L51 _protected prototype_ `TSharedRef<SWidget> GenerateQueryTagInfoRow();`
- L52 _protected prototype_ `TSharedRef<SWidget> GenerateQueryNavigationBoxWidget(float TagTitleBoxHorizontalPadding, float TagTitleBoxVerticalPadding);`
- L53 _protected prototype_ `TSharedRef<SWidget> GenerateQueryDetailsPanelSection(float InnerDetailsPanelsHorizontalPadding, float InnerDetailsPanelsVerticalPadding);`
- L54 _protected prototype_ `TSharedRef<SWidget> GenerateVisitStepControls();`
- L56 _protected prototype_ `void HandleQueryStepSelectionUpdated(int32 NewStepIndex);`
- L58 _protected prototype_ `FText GetQueryBeingInspectedTag() const;`
- L59 _protected prototype_ `FText GetSQVisitsStepsText() const;`
- L61 _protected prototype_ `FReply SelectParticleForCurrentQueryData() const;`
- L62 _protected prototype_ `FReply SelectQueryToInspectByID(int32 QueryID, int32 SolverID);`
- L63 _protected prototype_ `FReply SelectParentQuery();`
- L65 _protected prototype_ `TSharedPtr<IStructureDetailsView> CreateDataDetailsView() const;`
- L67 _protected prototype_ `void HandleSceneUpdated();`
- L68 _protected prototype_ `void HandleSubQueryNameSelected(TSharedPtr<FName> Name);`
- L70 _protected prototype_ `void ClearInspector();`
- L72 _protected prototype_ `EVisibility GetOutOfDateWarningVisibility() const;`
- L73 _protected prototype_ `EVisibility GetQueryDetailsSectionVisibility() const;`
- L74 _protected prototype_ `EVisibility GetQueryStepPlaybackControlsVisibility() const;`
- L75 _protected prototype_ `EVisibility GetSQVisitDetailsSectionVisibility() const;`
- L76 _protected prototype_ `EVisibility GetNothingSelectedMessageVisibility() const;`
- L77 _protected prototype_ `EVisibility GetSubQuerySelectorVisibility() const;`
- L78 _protected prototype_ `EVisibility GetParentQuerySelectorVisibility() const;`
- L80 _protected prototype_ `bool GetSelectParticleHitStateEnable() const;`
- L81 _protected prototype_ `bool GetSQVisitStepsEnabled() const;`
- L83 _protected prototype_ `TSharedPtr<FChaosVDQueryDataWrapper> GetCurrentDataBeingInspected() const;`
- L85 _protected member_ `TSharedPtr<SChaosVDTimelineWidget> QueryStepsTimelineWidget;`
- L87 _protected member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;`
- L89 _protected member_ `TSharedPtr<IStructureDetailsView> SceneQueryDataDetailsView;`
- L91 _protected member_ `TSharedPtr<IStructureDetailsView> SceneQueryHitDataDetailsView;`
- L93 _protected member_ `TSharedPtr<SChaosVDNameListPicker> SubQueryNamePickerWidget;`
- L95 _protected member_ `TWeakPtr<FEditorModeTools> EditorModeToolsWeakPtr;`
- L97 _protected member_ `TMap<TSharedPtr<FName>, FChaosVDSQSubQueryID> CurrentSubQueriesByName;`
- L99 _protected member_ `TSharedRef<FChaosVDSolverDataSelectionHandle> CurrentSceneQueryBeingInspectedHandle;`
- L101 _protected member_ `bool bIsUpToDate = true;`
- L103 _protected member_ `bool bListenToSelectionEvents = true;`
- L105 _protected member_ `TWeakPtr<SChaosVDMainTab> MainTabWeakPtr;`
- L107 _protected prototype_ `int32 GetCurrentMinSQVisitIndex() const;`
- L108 _protected prototype_ `int32 GetCurrentMaxSQVisitIndex() const;`
- L109 _protected prototype_ `int32 GetCurrentSQVisitIndex() const;`
- L111 _protected prototype_ `void HandleSQVisitTimelineInput(EChaosVDPlaybackButtonsID InputID);`

#### struct `FScopedSQInspectorSilencedSelectionEvents`  
`struct FScopedSQInspectorSilencedSelectionEvents`  
_L117-131_
- desc: Structure that makes a SQ Inspector ignore selection events withing a scope
- L119 _public function_ `FScopedSQInspectorSilencedSelectionEvents(SChaosVDSceneQueryDataInspector& InInspectorIgnoringEvents) : InspectorIgnoringSelectionEvents(InInspectorIgnoringEvents)`
- L124 _public function_ `~FScopedSQInspectorSilencedSelectionEvents()`
- L130 _private member_ `SChaosVDSceneQueryDataInspector& InspectorIgnoringSelectionEvents;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDSceneQueryTree.h` (Private)


#### struct `FChaosVDSceneQueryTreeItem`  
`struct FChaosVDSceneQueryTreeItem`  
_L16-24_
- L18 _public member_ `TWeakPtr<FChaosVDQueryDataWrapper> ItemWeakPtr;`
- L19 _public member_ `TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>> SubItems;`
- L20 _public member_ `int32 QueryID = INDEX_NONE;`
- L21 _public member_ `FName OwnerSolverName = FName("Inv`
- L22 _public member_ `int32 OwnerSolverID = INDEX_NONE;`
- L23 _public member_ `bool bIsVisible = true;`

#### class `SChaosVDSceneQueryTree`  
`class SChaosVDSceneQueryTree : public SCompoundWidget`  
_L32-79_
- inherits: `SCompoundWidget`
- desc: Tree Widget used to represent the recorded scene queries hierachy
- L35 _public function_ `SLATE_BEGIN_ARGS(SChaosVDSceneQueryTree)`
- L36 _public prototype_ `SLATE_EVENT(FChaosVDQueryTreeItemSelected, OnItemSelected) SLATE_EVENT(FChaosVDQueryTreeItemFocused, OnItemFocused) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L42 _public prototype_ `void SetExternalSourceData(const TSharedPtr<TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>>>& InUpdatedSceneQueryDataSource);`
- L44 _public prototype_ `void SelectItem(const TSharedPtr<FChaosVDSceneQueryTreeItem>& ItemToSelect, ESelectInfo::Type Type);`
- L46 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L50 _protected prototype_ `void HandleFocusRequest(TSharedPtr<FChaosVDSceneQueryTreeItem> InFocusedItem);`
- L52 _protected prototype_ `TSharedRef<ITableRow> GenerateSceneQueryDataRow(TSharedPtr<FChaosVDSceneQueryTreeItem> SceneQueryData, const TSharedRef<STableViewBase>& OwnerTable);`
- L54 _protected prototype_ `void QueryTreeSelectionChanged(TSharedPtr<FChaosVDSceneQueryTreeItem> SelectedQuery, ESelectInfo::Type Type);`
- L56 _protected prototype_ `void OnGetChildrenForQueryItem(TSharedPtr<FChaosVDSceneQueryTreeItem> QueryEntry, TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>>& OutQueries);`
- L58 _protected member_ `TSharedPtr<STreeView<TSharedPtr<FChaosVDSceneQueryTreeItem>>> SceneQueriesListWidget;`
- L60 _protected member_ `TSharedPtr<TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>>> ExternalTreeItemSourceData;`
- L62 _protected member_ `TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>> InternalTreeItemSourceData;`
- L64 _protected member_ `FChaosVDQueryTreeItemSelected QueryItemSelectedDelegate;`
- L65 _protected member_ `FChaosVDQueryTreeItemFocused QueryItemFocusedDelegate;`
- L78 _public member_ `static FColumNames ColumnNames;`

#### struct `SChaosVDSceneQueryTree::FColumNames`  
`struct FColumNames`  
_L69-76_
- L71 _public member_ `const FName Visibility = FName("Vis`
- L72 _public member_ `const FName TraceTag = FName("Tra`
- L73 _public member_ `const FName TraceOwner = FName("Tra`
- L74 _public member_ `const FName QueryType = FName("Que`
- L75 _public member_ `const FName SolverName = FName("Sol`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DELEGATE_TwoParams(FChaosVDQueryTreeItemSelected, const TSharedPtr<FChaosVDSceneQueryTreeItem>&, ESelectInfo::Type) DECLARE_DELEGATE_OneParam(FChaosVDQueryTreeItemFocused, const TSharedPtr<FChaosVDSceneQueryTreeItem>&) class SChaosVDSceneQueryTree : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SChaosVDSceneQueryTree) {} SLATE_EVENT(FChaosVDQueryTreeItemSelected, OnItemSelected) SLATE_EVENT(FChaosVDQueryTreeItemFocused, OnItemFocused) SLATE_END_ARGS() void Construct(const FArguments& InArgs); void SetExternalSourceData(const TSharedPtr<TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>>>& InUpdatedSceneQueryDataSource); void SelectItem(const TSharedPtr<FChaosVDSceneQueryTreeItem>& ItemToSelect, ESelectInfo::Type Type); virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; protected: void HandleFocusRequest(TSharedPtr<FChaosVDSceneQueryTreeItem> InFocusedItem); TSharedRef<ITableRow> GenerateSceneQueryDataRow(TSharedPtr<FChaosVDSceneQueryTreeItem> SceneQueryData, const TSharedRef<STableViewBase>& OwnerTable); void QueryTreeSelectionChanged(TSharedPtr<FChaosVDSceneQueryTreeItem> SelectedQuery, ESelectInfo::Type Type); void OnGetChildrenForQueryItem(TSharedPtr<FChaosVDSceneQueryTreeItem> QueryEntry, TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>>& OutQueries); TSharedPtr<STreeView<TSharedPtr<FChaosVDSceneQueryTreeItem>>> SceneQueriesListWidget; TSharedPtr<TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>>> ExternalTr`
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FChaosVDQueryTreeItemFocused, const TSharedPtr<FChaosVDSceneQueryTreeItem>&) class SChaosVDSceneQueryTree : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SChaosVDSceneQueryTree) {} SLATE_EVENT(FChaosVDQueryTreeItemSelected, OnItemSelected) SLATE_EVENT(FChaosVDQueryTreeItemFocused, OnItemFocused) SLATE_END_ARGS() void Construct(const FArguments& InArgs); void SetExternalSourceData(const TSharedPtr<TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>>>& InUpdatedSceneQueryDataSource); void SelectItem(const TSharedPtr<FChaosVDSceneQueryTreeItem>& ItemToSelect, ESelectInfo::Type Type); virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; protected: void HandleFocusRequest(TSharedPtr<FChaosVDSceneQueryTreeItem> InFocusedItem); TSharedRef<ITableRow> GenerateSceneQueryDataRow(TSharedPtr<FChaosVDSceneQueryTreeItem> SceneQueryData, const TSharedRef<STableViewBase>& OwnerTable); void QueryTreeSelectionChanged(TSharedPtr<FChaosVDSceneQueryTreeItem> SelectedQuery, ESelectInfo::Type Type); void OnGetChildrenForQueryItem(TSharedPtr<FChaosVDSceneQueryTreeItem> QueryEntry, TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>>& OutQueries); TSharedPtr<STreeView<TSharedPtr<FChaosVDSceneQueryTreeItem>>> SceneQueriesListWidget; TSharedPtr<TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>>> ExternalTreeItemSourceData; TArray<TSharedPtr<FChaosVDSceneQueryTreeItem>> InternalTreeItemSourceData; FChaosVDQueryTreeItemSelected Q`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDSceneQueryTreeRow.h` (Private)


#### class `SChaosVDSceneQueryTreeRow`  
`class SChaosVDSceneQueryTreeRow : public SMultiColumnTableRow<TSharedPtr<const FChaosVDSceneQueryTreeItem>>`  
_L16-40_
- inherits: `SMultiColumnTableRow<TSharedPtr<constFChaosVDSceneQueryTreeItem>>`
- desc: Widget used to represent a row on the Scene Query Browser tree view
- L19 _public function_ `SLATE_BEGIN_ARGS(SChaosVDSceneQueryTreeRow)`
- L22 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FChaosVDSceneQueryTreeItem>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L28 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L32 _private prototype_ `EVisibility GetVisibilityIconVisibility() const;`
- L34 _private prototype_ `TSharedRef<SWidget> GenerateTextWidgetFromName(FName Name);`
- L35 _private prototype_ `TSharedRef<SWidget> GenerateTextWidgetFromText(const FText& Text);`
- L37 _private prototype_ `const FSlateBrush* GetVisibilityIconForCurrentItem() const;`
- L39 _private member_ `TSharedPtr<FChaosVDSceneQueryTreeItem> Item;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDSolverPlaybackControls.h` (Private)


#### enum `EChaosVDStepsWidgetUpdateFlags`  
`enum class EChaosVDStepsWidgetUpdateFlags`  
_L22-28_
- desc: Options flags to control how the Step timeline widgets should be updated
- L24 _public enumerator_ `UpdateText = 1 << 0`
- L25 _public enumerator_ `SetTimelineStep = 1 << 1`
- L27 _public enumerator_ `Default = UpdateText | SetTimelineStep`

#### class `SChaosVDSolverPlaybackControls`  
`class SChaosVDSolverPlaybackControls : public SCompoundWidget, public FChaosVDPlaybackControllerObserver, public IChaosVDPlaybackControllerInstigator`  
_L34-108_
- inherits: `SCompoundWidget,FChaosVDPlaybackControllerObserver,IChaosVDPlaybackControllerInstigator`
- desc: Widget that Generates playback controls for solvers Which are two timelines, one for physics frames and other for steps
- L38 _public function_ `explicit SChaosVDSolverPlaybackControls() : SolverTrackInfoRef(MakeShared<const FChaosVDTrackInfo>())`
- L44 _public function_ `SLATE_BEGIN_ARGS(SChaosVDSolverPlaybackControls)`
- L45 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<const FChaosVDTrackInfo>& InSolverTrackInfo, const TWeakPtr<FChaosVDPlaybackController>& InPlaybackController);`
- L50 _public prototype_ `void HandleTimelineScrubStart();`
- L51 _public prototype_ `void HandleTimelineScrubEnd();`
- L55 _private prototype_ `void OnFrameSelectionUpdated(int32 NewFrameIndex);`
- L56 _private prototype_ `void OnSolverStageSelectionUpdated(int32 NewStepIndex);`
- L58 _private prototype_ `virtual void RegisterNewController(TWeakPtr<FChaosVDPlaybackController> NewController) override;`
- L60 _private prototype_ `FStringView GetCurrentSolverStageName() const;`
- L62 _private prototype_ `void HandleFramePlaybackButtonClicked(EChaosVDPlaybackButtonsID ButtonID);`
- L63 _private prototype_ `void HandleSolverStagePlaybackButtonClicked(EChaosVDPlaybackButtonsID ButtonID);`
- L65 _private prototype_ `void HandleSolverVisibilityChanged(int32 InSolverID, bool bNewVisibility);`
- L67 _private prototype_ `FReply ToggleSolverVisibility() const;`
- L68 _private prototype_ `FReply ToggleSolverSyncLink() const;`
- L70 _private prototype_ `bool CanChangeVisibility() const;`
- L71 _private prototype_ `const FSlateBrush* GetBrushForCurrentVisibility() const;`
- L72 _private prototype_ `const FSlateBrush* GetBrushForCurrentLinkState() const;`
- L74 _private prototype_ `const FSlateBrush* GetFrameTypeBadgeBrush() const;`
- L76 _private prototype_ `TSharedPtr<SWidget> CreateVisibilityWidget();`
- L77 _private prototype_ `TSharedPtr<SWidget> CreateSyncLinkWidget();`
- L79 _private prototype_ `FText GetVisibilityButtonToolTipText() const;`
- L80 _private prototype_ `FText GetSyncLinkTipText() const;`
- L82 _private prototype_ `bool CanPlayback() const;`
- L84 _private prototype_ `bool IsPlaying() const;`
- L86 _private prototype_ `int32 GetCurrentFrame() const;`
- L87 _private prototype_ `int32 GetMinFrames() const;`
- L88 _private prototype_ `int32 GetMaxFrames() const;`
- L90 _private prototype_ `int32 GetCurrentSolverStage() const;`
- L91 _private prototype_ `int32 GetMinSolverStage() const;`
- L92 _private prototype_ `int32 GetMaxSolverStage() const;`
- L94 _private member_ `TSharedRef<const FChaosVDTrackInfo> SolverTrackInfoRef;`
- L95 _private member_ `bool bIsReSimFrame = false;`
- L96 _private member_ `FString CurrentStepName;`
- L97 _private member_ `TSharedPtr<SChaosVDTimelineWidget> FramesTimelineWidget;`
- L98 _private member_ `TSharedPtr<SChaosVDTimelineWidget> StepsTimelineWidget;`
- L99 _private member_ `bool bIsVisible = true;`
- L101 _private member_ `const FSlateBrush* SolverVisibleIconBrush = nullptr;`
- L102 _private member_ `const FSlateBrush* SolverHiddenIconBrush = nullptr;`
- L104 _private member_ `const FSlateBrush* SolverTrackSyncEnabledBrush = nullptr;`
- L105 _private member_ `const FSlateBrush* SolverTrackSyncDisabledBrush = nullptr;`
- L107 _private member_ `FButtonStyle ResimBadgeButtonStyle;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDSolverTracks.h` (Private)


#### class `UChaosVDSolverTracksToolbarMenuContext`  
`class UChaosVDSolverTracksToolbarMenuContext : public UObject`  
_L19-26_
- reflection: `UCLASS()`
- inherits: `UObject`
- L25 _public member_ `TWeakPtr<class SChaosVDSolverTracks> SolverTracksWidget;`

#### class `SChaosVDSolverTracks`  
`class SChaosVDSolverTracks : public SCompoundWidget, public FChaosVDPlaybackControllerObserver, public IChaosVDPlaybackControllerInstigator`  
_L31-70_
- inherits: `SCompoundWidget,FChaosVDPlaybackControllerObserver,IChaosVDPlaybackControllerInstigator`
- desc: Widget that Generates a expandable list of solver controls, based on the existing solver data on the ChaosVDPlaybackController
- L35 _public function_ `SLATE_BEGIN_ARGS( SChaosVDSolverTracks )`
- L36 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FChaosVDPlaybackController> InPlaybackController, TWeakPtr<SChaosVDMainTab> MainTab);`
- L40 _public prototype_ `~SChaosVDSolverTracks();`
- L44 _private prototype_ `void UpdatedCachedTrackInfoData(TWeakPtr<FChaosVDPlaybackController> InPlaybackController, const TSharedRef<const FChaosVDTrackInfo>& UpdatedTrackInfo);`
- L45 _private prototype_ `virtual void HandlePlaybackControllerDataUpdated(TWeakPtr<FChaosVDPlaybackController> InPlaybackController) override;`
- L46 _private prototype_ `virtual void HandleControllerTrackFrameUpdated(TWeakPtr<FChaosVDPlaybackController> InPlaybackController, TWeakPtr<const FChaosVDTrackInfo> UpdatedTrackInfo, FGuid InstigatorGuid) override;`
- L48 _private prototype_ `TSharedRef<ITableRow> MakeSolverTrackControlsFromTrackInfo(TSharedPtr<const FChaosVDTrackInfo> TrackInfo, const TSharedRef<STableViewBase>& OwnerTable);`
- L50 _private member_ `TSharedPtr<SListView<TSharedPtr<const FChaosVDTrackInfo>>> SolverTracksListWidget;`
- L52 _private member_ `TArray<TSharedPtr<const FChaosVDTrackInfo>> CachedTrackInfoArray;`
- L54 _private prototype_ `EVisibility GetSelectorKeyVisibility(int32 TrackSlot) const;`
- L56 _private prototype_ `bool IsActiveTrack(const TWeakPtr<const FChaosVDTrackInfo>& TrackInfo) const;`
- L58 _private prototype_ `TSharedRef<SWidget> GenerateToolbarWidget();`
- L59 _private prototype_ `TSharedRef<SWidget> GenerateSyncModeMenuWidget();`
- L61 _private prototype_ `void HandleSettingsChanged(UObject* SettingsObject);`
- L63 _private prototype_ `void RegisterMenus();`
- L65 _private member_ `bool bShowSelectorKeyShortcut = false;`
- L67 _private member_ `TWeakPtr<SChaosVDMainTab> MainTabWeakPtr;`
- L69 _private member_ `FName MenuName;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDTimelineWidget.h` (Private)


#### enum `EChaosVDPlaybackButtonsID`  
`enum class EChaosVDPlaybackButtonsID : uint8`  
_L14-21_
- reflection: `UENUM()`
- L16 _public enumerator_ `Play`
- L17 _public enumerator_ `Pause`
- L18 _public enumerator_ `Stop`
- L19 _public enumerator_ `Next`
- L20 _public enumerator_ `Prev`

#### enum `EChaosVDSetTimelineFrameFlags`  
`enum class EChaosVDSetTimelineFrameFlags`  
_L26-31_
- L28 _public enumerator_ `None = 0`
- L29 _public enumerator_ `BroadcastChange = 1 << 0`
- L30 _public enumerator_ `Silent = 1 << 1`

#### enum `EChaosVDTimelineElementIDFlags`  
`enum class EChaosVDTimelineElementIDFlags : uint16`  
_L34-49_
- L36 _public enumerator_ `None = 0`
- L37 _public enumerator_ `Play = 1 << 0`
- L38 _public enumerator_ `Stop = 1 << 1`
- L39 _public enumerator_ `Next = 1 << 2`
- L40 _public enumerator_ `Prev = 1 << 3`
- L41 _public enumerator_ `Lock = 1 << 4`
- L42 _public enumerator_ `Timeline = 1 << 5`
- L44 _public enumerator_ `ManualSteppingButtons = Next | Prev`
- L45 _public enumerator_ `AllManualStepping = Next | Prev | Timeline`
- L46 _public enumerator_ `AllPlaybackButtons = Play | Stop | Next | Prev`
- L47 _public enumerator_ `AllPlayback = Play | Stop | Next | Prev | Timeline`
- L48 _public enumerator_ `All = Play | Stop | Next | Prev | Timeline | Lock`

#### class `SChaosVDTimelineWidget`  
`class SChaosVDTimelineWidget : public SCompoundWidget`  
_L56-123_
- inherits: `SCompoundWidget`
- desc: Simple timeline control widget
- L60 _public function_ `SLATE_BEGIN_ARGS( SChaosVDTimelineWidget )`
- L61 _public prototype_ `SLATE_ATTRIBUTE(int32, MaxFrames) SLATE_ATTRIBUTE(int32, MinFrames) SLATE_ATTRIBUTE(int32, CurrentFrame) SLATE_ARGUMENT(EChaosVDTimelineElementIDFlags, ButtonVisibilityFlags) SLATE_ATTRIBUTE(EChaosVDTimelineElementIDFlags, ButtonEnabledFlags) SLATE_ATTRIBUTE(bool, IsPlaying) SLATE_EVENT(FChaosVDFrameChangedDelegate, OnFrameChanged) SLATE_EVENT(FChaosControlButtonClicked, OnButtonClicked) SLATE_EVENT(FChaosVDFrameScrubDelegate, OnTimelineScrubStart) SLATE_EVENT(FChaosVDFrameScrubDelegate, OnTimelineScrubEnd) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L77 _protected prototype_ `void Play();`
- L78 _protected prototype_ `FReply Stop();`
- L80 _protected prototype_ `void SetCurrentTimelineFrame(float FrameNumber, EChaosVDSetTimelineFrameFlags Options);`
- L82 _protected prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L84 _protected prototype_ `void Pause();`
- L85 _protected prototype_ `FReply TogglePlay();`
- L86 _protected prototype_ `FReply Next();`
- L87 _protected prototype_ `FReply Prev();`
- L89 _protected prototype_ `const FSlateBrush* GetPlayOrPauseIcon() const;`
- L91 _protected prototype_ `EVisibility GetElementVisibility(EChaosVDTimelineElementIDFlags ElementID) const;`
- L92 _protected prototype_ `bool GetElementEnabled(EChaosVDTimelineElementIDFlags ElementID) const;`
- L94 _protected prototype_ `bool IsPlaying() const;`
- L96 _protected prototype_ `int32 GetCurrentFrame() const;`
- L97 _protected prototype_ `float GetCurrentFrameAsFloat() const;`
- L98 _protected prototype_ `int32 GetCurrentMinFrames() const;`
- L99 _protected prototype_ `int32 GetCurrentMaxFrames() const;`
- L101 _protected prototype_ `void HandleTimelineScrubStart();`
- L102 _protected prototype_ `void HandleTimelineScrubEnd();`
- L104 _protected member_ `TOptional<float> PendingValueChange = 0.0f;`
- L106 _protected member_ `TSharedPtr<SSlider> TimelineSlider;`
- L108 _protected member_ `TAttribute<int32> CurrentFrame = 0;`
- L109 _protected member_ `TAttribute<int32> MinFrames = 0;`
- L110 _protected member_ `TAttribute<int32> MaxFrames = 1000;`
- L111 _protected member_ `TAttribute<EChaosVDTimelineElementIDFlags> ElementEnabledFlags = EChaosVDTimelineElementIDFlags::All;`
- L113 _protected member_ `TAttribute<bool> bIsPlaying = false;`
- L115 _protected member_ `FChaosVDFrameChangedDelegate FrameChangedDelegate;`
- L116 _protected member_ `FChaosControlButtonClicked ButtonClickedDelegate;`
- L117 _protected member_ `FChaosVDFrameScrubDelegate TimelineScrubStartDelegate;`
- L118 _protected member_ `FChaosVDFrameScrubDelegate TimelineScrubEndDelegate;`
- L120 _protected member_ `TAttribute<EChaosVDTimelineElementIDFlags> ElementVisibilityFlags = EChaosVDTimelineElementIDFlags::All;`
- L122 _protected member_ `EChaosVDTimelineElementIDFlags DefaultEnabledElementsFlags =EChaosVDTimelineElementIDFlags::All;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FChaosControlButtonClicked, EChaosVDPlaybackButtonsID) DECLARE_DELEGATE_OneParam(FChaosVDFrameLockStateDelegate, bool) enum class EChaosVDSetTimelineFrameFlags { None = 0, BroadcastChange = 1 << 0, Silent = 1 << 1, };`
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FChaosVDFrameLockStateDelegate, bool) enum class EChaosVDSetTimelineFrameFlags { None = 0, BroadcastChange = 1 << 0, Silent = 1 << 1, };`
- L52 _delegate_ `DECLARE_DELEGATE_OneParam(FChaosVDFrameChangedDelegate, int32) DECLARE_DELEGATE(FChaosVDFrameScrubDelegate) class SChaosVDTimelineWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS( SChaosVDTimelineWidget ){} SLATE_ATTRIBUTE(int32, MaxFrames) SLATE_ATTRIBUTE(int32, MinFrames) SLATE_ATTRIBUTE(int32, CurrentFrame) SLATE_ARGUMENT(EChaosVDTimelineElementIDFlags, ButtonVisibilityFlags) SLATE_ATTRIBUTE(EChaosVDTimelineElementIDFlags, ButtonEnabledFlags) SLATE_ATTRIBUTE(bool, IsPlaying) SLATE_EVENT(FChaosVDFrameChangedDelegate, OnFrameChanged) SLATE_EVENT(FChaosControlButtonClicked, OnButtonClicked) SLATE_EVENT(FChaosVDFrameScrubDelegate, OnTimelineScrubStart) SLATE_EVENT(FChaosVDFrameScrubDelegate, OnTimelineScrubEnd) SLATE_END_ARGS() void Construct(const FArguments& InArgs); protected: void Play(); FReply Stop(); void SetCurrentTimelineFrame(float FrameNumber, EChaosVDSetTimelineFrameFlags Options); void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; void Pause(); FReply TogglePlay(); FReply Next(); FReply Prev(); const FSlateBrush* GetPlayOrPauseIcon() const; EVisibility GetElementVisibility(EChaosVDTimelineElementIDFlags ElementID) const;`
- L53 _delegate_ `DECLARE_DELEGATE(FChaosVDFrameScrubDelegate) class SChaosVDTimelineWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS( SChaosVDTimelineWidget ){} SLATE_ATTRIBUTE(int32, MaxFrames) SLATE_ATTRIBUTE(int32, MinFrames) SLATE_ATTRIBUTE(int32, CurrentFrame) SLATE_ARGUMENT(EChaosVDTimelineElementIDFlags, ButtonVisibilityFlags) SLATE_ATTRIBUTE(EChaosVDTimelineElementIDFlags, ButtonEnabledFlags) SLATE_ATTRIBUTE(bool, IsPlaying) SLATE_EVENT(FChaosVDFrameChangedDelegate, OnFrameChanged) SLATE_EVENT(FChaosControlButtonClicked, OnButtonClicked) SLATE_EVENT(FChaosVDFrameScrubDelegate, OnTimelineScrubStart) SLATE_EVENT(FChaosVDFrameScrubDelegate, OnTimelineScrubEnd) SLATE_END_ARGS() void Construct(const FArguments& InArgs); protected: void Play(); FReply Stop(); void SetCurrentTimelineFrame(float FrameNumber, EChaosVDSetTimelineFrameFlags Options); void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; void Pause(); FReply TogglePlay(); FReply Next(); FReply Prev(); const FSlateBrush* GetPlayOrPauseIcon() const; EVisibility GetElementVisibility(EChaosVDTimelineElementIDFlags ElementID) const; bool GetElementEnabled(EChaosVDTimelineElementIDFlags ElementID) const;`

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SChaosVDWarningMessageBox.h` (Private)


#### class `SChaosVDWarningMessageBox`  
`class SChaosVDWarningMessageBox : public SCompoundWidget`  
_L8-19_
- inherits: `SCompoundWidget`
- L11 _public function_ `SLATE_BEGIN_ARGS(SChaosVDWarningMessageBox) : _WarningText()`
- L15 _public prototype_ `SLATE_ATTRIBUTE(FText, WarningText) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The  text to show in the warning

### `Plugins/ChaosVD/Source/ChaosVD/Private/Widgets/SStreamingStatus.h` (Private)


#### class `Chaos::VD::SStreamingStatus`  
`class SStreamingStatus : public SCompoundWidget`  
_L12-32_
- inherits: `SCompoundWidget`
- desc: Widget to be used as overlay in the main viewport to indicate the user the streaming system status
- L15 _public function_ `SLATE_BEGIN_ARGS(SStreamingStatus)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L24 _private prototype_ `void HandleSettingsChanged(UObject* SettingsObject);`
- L25 _private prototype_ `FText GetStreamingStatusText() const;`
- L26 _private prototype_ `FSlateColor GetStreamingStatusColor() const;`
- L27 _private prototype_ `const FSlateBrush* GetStreamingStatusImage() const;`
- L28 _private prototype_ `FText GetStreamingStatusTooltipText() const;`
- L29 _private prototype_ `FReply OpenToggleStreamingStatePopup();`
- L31 _private member_ `bool bCachedStreamingEnabledState = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`
- L7 _namespace_ `namespace VD` (scope `Chaos`)

### `Plugins/ChaosVD/Source/ChaosVD/Public/Actors/ChaosVDDataContainerBaseActor.h` (Public)


#### class `AChaosVDDataContainerBaseActor`  
`class AChaosVDDataContainerBaseActor : public AActor`  
_L23-117_
- reflection: `UCLASS(MinimalAPI, Abstract, NotBlueprintable, NotPlaceable)`
- inherits: `AActor`
- desc: Base class for any CVD actor that will contain frame related data (either solver frame or game frame)
- L28 _public prototype_ `AChaosVDDataContainerBaseActor();`
- L31 _public prototype_ `virtual void UpdateFromNewGameFrameData(const FChaosVDGameFrameData& InGameFrameData);`
- L33 _public prototype_ `virtual void UpdateFromNewSolverFrameData(const FChaosVDSolverFrameData& InSolverFrameData);`
- L35 _public prototype_ `virtual void UpdateFromNewSolverStageData(const FChaosVDSolverFrameData& InSolverFrameData, const FChaosVDFrameStageData& InSolverFrameStageData);`
- L37 _public prototype_ `virtual void Destroyed() override;`
- L39 _public function_ `virtual void SetScene(TWeakPtr<FChaosVDScene> InScene)`
- L44 _public prototype_ `virtual void HandleWorldStreamingLocationUpdated(const FVector& InLocation);`
- L46 _public prototype_ `void SetSolverID(int32 InSolverID);`
- L48 _public function_ `int32 GetSolverID() const`
- L53 _public function_ `virtual const FTransform& GetSimulationTransform() const`
- L58 _public prototype_ `virtual void UpdateVisibility(bool bIsVisible);`
- L60 _public function_ `virtual bool IsVisible() const`
- L65 _public prototype_ `virtual void PostActorCreated() override;`
- L67 _public function_ `TWeakPtr<FChaosVDScene> GetScene() const`
- L97 _public prototype_ `void SetIsTemporarilyHiddenInEditor(bool bIsHidden) override;`
- L106 _public prototype_ `virtual void AppendSceneCompositionTestData(FChaosVDSceneCompositionTestData& OutStateTestData);` — Appends Scene Data relevant for functional tests @param OutStateTestData Structure instance where to add the data @note If you change the data being added here, you need to re-generate the snapshots used by the scene integrity playback tests in the Simulation Tests Plugin
- L110 _protected prototype_ `void HandlePostInitializationExtensionRegistered(const TSharedRef<FChaosVDExtension>& NewExtension);`
- L112 _protected member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;`
- L114 _protected member_ `int32 SolverDataID = INDEX_NONE;`
- L116 _protected member_ `bool bInternallyReRoutingGameFrameData = false;`

#### struct `AChaosVDDataContainerBaseActor::FScopedGameFrameDataReRouting`  
`struct FScopedGameFrameDataReRouting`  
_L77-94_
- desc: Flags a CVD Data container actor for game frame data re-routing. Used by some data container actors to know when the GT data they are processing comes from a re-routing execution path.
- L79 _public function_ `explicit FScopedGameFrameDataReRouting(AChaosVDDataContainerBaseActor* InDataContainerBaseActor)`
- L87 _public function_ `~FScopedGameFrameDataReRouting()`
- L93 _private member_ `AChaosVDDataContainerBaseActor* DataContainerBaseActor = nullptr;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Chaos`
- L16 _namespace_ `namespace VD` (scope `Chaos`)
- L16 _namespace_ `namespace Test` (scope `Chaos::VD`)
- L16 _namespace_ `namespace SceneObjectTypes` (scope `Chaos::VD::Test`)
- L18 _externvar_ `extern FName SolverID;` (scope `Chaos::VD::Test::SceneObjectTypes`)

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDBaseSceneObject.h` (Public)


#### struct `FChaosVDBaseSceneObject`  
`struct FChaosVDBaseSceneObject`  
_L15-153_
- reflection: `USTRUCT()`
- desc: Base Class for any UStruct based object that has a representation in CVD's World and outliner
- L19 _public prototype_ `virtual ~FChaosVDBaseSceneObject() = default;`
- L25 _public function_ `void SetDisplayName(const FString& NewDisplayName)` — Sets the name that will be used for this object in the scene outliner @param NewDisplayName New name
- L34 _public function_ `void SetIconName(FName NewIconName)` — Sets the name of the icon that will be shown as part of the label for this object in the scene outliner @param NewIconName Registered name of the icon in an editor style
- L43 _public function_ `virtual void SetParent(const TSharedPtr<FChaosVDBaseSceneObject>& NewParent)` — Sets a weak reference to another UStruct based scene object, that is the parent of this object @param NewParent Parent Object
- L52 _public prototype_ `void SetParentParentActor(AActor* NewParent);` — Sets a weak reference to an actor that is the parent of this object. @param NewParent Parent Actor
- L58 _public function_ `FString GetDisplayName() const` — Returns a copy the name that will be used for this object in the scene outliner
- L66 _public function_ `const FString& GetDisplayNameRef() const` — Returns a reference to the name that will be used for this object in the scene outliner
- L74 _public function_ `FName GetIconName() const` — Returns the registered name of the icon that will be shown as part of the label for this object in the scene outliner
- L82 _public function_ `TWeakPtr<FChaosVDBaseSceneObject> GetParent() const` — Returns a weak ptr to this object's parent
- L90 _public function_ `AActor* GetParentActor() const` — Returns a weak ptr to this object's parent Actor
- L98 _public function_ `UE::Editor::DataStorage::RowHandle GetTedsRowHandle() const` — Returns the handle for this object in TEDS
- L106 _public function_ `void SetTedsRowHandle(UE::Editor::DataStorage::RowHandle Handle)` — Sets the handle for this object in TEDS
- L117 _public function_ `void SetStreamingState(EStreamingState NewState)`
- L122 _public function_ `EStreamingState GetStreamingState() const`
- L127 _public function_ `virtual void SyncStreamingState()`
- L131 _public function_ `virtual FBox GetStreamingBounds() const`
- L136 _public function_ `virtual int32 GetStreamingID() const`
- L142 _protected member_ `TWeakPtr<FChaosVDBaseSceneObject> Parent = nullptr;`
- L144 _protected member_ `TWeakObjectPtr<AActor> ParentActor = nullptr;`
- L146 _protected member_ `FString DisplayName = TEXT("Non`
- L148 _protected member_ `UE::Editor::DataStorage::RowHandle CachedRowHandle = UE::Editor::DataStorage::InvalidRowHandle;`
- L150 _protected member_ `FName IconName = NAME_None;`
- L152 _protected member_ `EStreamingState StreamingState = EStreamingState::Hidden;`

#### enum `FChaosVDBaseSceneObject::EStreamingState`  
`enum class EStreamingState`  
_L111-115_
- L113 _public enumerator_ `Visible`
- L114 _public enumerator_ `Hidden`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDCharacterGroundConstraintDataProviderInterface.h` (Public)


#### class `UChaosVDCharacterGroundConstraintDataProviderInterface`  
`class UChaosVDCharacterGroundConstraintDataProviderInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE()`
- inherits: `UInterface`
- desc: This class does not need to be modified.

#### class `IChaosVDCharacterGroundConstraintDataProviderInterface`  
`class IChaosVDCharacterGroundConstraintDataProviderInterface`  
_L20-42_
- desc: Interface for any object that is able to provide CVD Character Ground Constraint Data

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDEngine.h` (Public)


#### enum `EChaosVDLoadRecordedDataMode`  
`enum class EChaosVDLoadRecordedDataMode : uint8`  
_L27-33_
- reflection: `UENUM()`
- desc: Enumeration of the available modes controlling how data is loaded into CVD
- L30 _public enumerator_ `SingleSource` — This mode will unload any CVD recording currently loaded before loading the selected file
- L32 _public enumerator_ `MultiSource` — CVD will load and merge the data of the selected recording into the currently loaded recording

#### class `FChaosVDEngine`  
`class FChaosVDEngine : public FTSTickerObjectBase, public TSharedFromThis<FChaosVDEngine>`  
_L43-162_
- inherits: `FTSTickerObjectBase,TSharedFromThis<FChaosVDEngine>`
- desc: Core Implementation of the visual debugger - Owns the systems that are not UI
- L46 _public prototype_ `FChaosVDEngine();`
- L47 _public prototype_ `virtual ~FChaosVDEngine();`
- L49 _public prototype_ `void Initialize();`
- L50 _public prototype_ `void CloseActiveTraceSessions();`
- L51 _public prototype_ `void CloseSessionByRemoteSessionID(FGuid RemoteSessionID);`
- L53 _public prototype_ `void StopActiveTraceSessions();`
- L55 _public prototype_ `void DeInitialize();`
- L57 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L59 _public function_ `const FGuid& GetInstanceGuid() const`
- L64 _public function_ `TSharedPtr<FChaosVDScene>& GetCurrentScene()`
- L69 _public function_ `TSharedPtr<FChaosVDPlaybackController>& GetPlaybackController()`
- L74 _public prototype_ `bool HasAnyLiveSessionActive() const;`
- L76 _public prototype_ `void LoadRecording(const FString& FilePath, EChaosVDLoadRecordedDataMode LoadingMode = EChaosVDLoadRecordedDataMode::MultiSource);`
- L77 _public prototype_ `void LoadCombinedMultiRecording(const FString& FilePath);`
- L79 _public prototype_ `bool ConnectToLiveSession(uint32 SessionID, const FString& InSessionAddress, EChaosVDLoadRecordedDataMode LoadingMode = EChaosVDLoadRecordedDataMode::MultiSource);`
- L80 _public prototype_ `bool ConnectToLiveSession_Direct(FGuid RemoteSessionID, EChaosVDLoadRecordedDataMode LoadingMode = EChaosVDLoadRecordedDataMode::MultiSource);`
- L81 _public prototype_ `bool ConnectToLiveSession_Relay(FGuid RemoteSessionID, EChaosVDLoadRecordedDataMode LoadingMode = EChaosVDLoadRecordedDataMode::MultiSource);`
- L83 _public prototype_ `void OpenSession(const UE::TraceBasedDebuggers::FTraceSessionDescriptor& SessionDescriptor, EChaosVDLoadRecordedDataMode LoadingMode = EChaosVDLoadRecordedDataMode::MultiSource);`
- L85 _public prototype_ `bool SaveOpenSessionToCombinedFile(const FString& InTargetFilePath = FString());`
- L87 _public prototype_ `bool CanCombineOpenSessions() const;`
- L92 _public function_ `TArrayView<FChaosVDTraceSessionDescriptor> GetCurrentSessionDescriptors()` — `UE_DEPRECATED(5.8, "Use GetTraceSessionDescriptors")`
- L98 _public prototype_ `bool ConnectToLiveSession_Direct(EChaosVDLoadRecordedDataMode LoadingMode = EChaosVDLoadRecordedDataMode::MultiSource);` — `UE_DEPRECATED(5.8, "Please use the version that takes a remote Session ID")`
- L101 _public function_ `void OpenSession(const FChaosVDTraceSessionDescriptor& SessionDescriptor, EChaosVDLoadRecordedDataMode LoadingMode = EChaosVDLoadRecordedDataMode::MultiSource)` — `UE_DEPRECATED(5.8, "Use the version taking UE::TraceBasedDebuggers::FTraceSessionDescriptor in parameter")`
- L106 _public function_ `FSessionStateChangedDelegate& OnSessionOpened()` — `UE_DEPRECATED(5.8, "Use OnTraceSessionOpened instead")`
- L113 _public function_ `FSessionStateChangedDelegate& OnSessionClosed()` — `UE_DEPRECATED(5.8, "Use OnTraceSessionClosed instead")`
- L120 _public prototype_ `const FChaosVDTraceSessionDescriptor& GetSessionDescriptor(FGuid RemoteSessionID) const;` — `UE_DEPRECATED(5.8, "Use GetTraceSessionDescriptor")`
- L124 _public function_ `FTraceSessionStateChangedDelegate& OnTraceSessionOpened()`
- L129 _public function_ `FTraceSessionStateChangedDelegate& OnTraceSessionClosed()`
- L134 _public prototype_ `const UE::TraceBasedDebuggers::FTraceSessionDescriptor& GetTraceSessionDescriptor(FGuid RemoteSessionID) const;`
- L136 _public prototype_ `TArrayView<UE::TraceBasedDebuggers::FTraceSessionDescriptor> GetTraceSessionDescriptors();`
- L140 _private prototype_ `void LoadRecording_Internal(const TFunction<FString(const TSharedPtr<FChaosVDRecording>&)>&, EChaosVDLoadRecordedDataMode LoadingMode = EChaosVDLoadRecordedDataMode::MultiSource);`
- L142 _private prototype_ `void RestoreDataChannelsEnabledStateFromSave();`
- L143 _private prototype_ `void UpdateSavedDataChannelsEnabledState(TWeakPtr<Chaos::VisualDebugger::FChaosVDOptionalDataChannel> DataChannelChanged);`
- L145 _private prototype_ `void UpdateRecentFilesList(const FString& InFilename);`
- L147 _private member_ `FGuid InstanceGUID;`
- L149 _private member_ `TArray<UE::TraceBasedDebuggers::FTraceSessionDescriptor> CurrentSessionDescriptors;`
- L151 _private member_ `TSharedPtr<FChaosVDScene> CurrentScene;`
- L152 _private member_ `TSharedPtr<FChaosVDPlaybackController> PlaybackController;`
- L154 _private member_ `bool bIsInitialized = false;`
- L156 _private member_ `FDelegateHandle LiveSessionStoppedDelegateHandle;`
- L158 _private member_ `FDelegateHandle DataChannelStateUpdatedHandle;`
- L160 _private member_ `FTraceSessionStateChangedDelegate OnSessionOpenedDelegate;`
- L161 _private member_ `FTraceSessionStateChangedDelegate OnSessionClosedDelegate;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L10 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FTraceSessionStateChangedDelegate, const UE::TraceBasedDebuggers::FTraceSessionDescriptor& InSessionDescriptor) PRAGMA_DISABLE_DEPRECATION_WARNINGS UE_DEPRECATED(5.8, "Use FTraceSessionStateChangedDelegate taking UE::TraceBasedDebuggers::FTraceSessionDescriptor in parameter") DECLARE_MULTICAST_DELEGATE_OneParam(FSessionStateChangedDelegate, const struct FChaosVDTraceSessionDescriptor& InSessionDescriptor) PRAGMA_ENABLE_DEPRECATION_WARNINGS class FChaosVDEngine : public FTSTickerObjectBase, public TSharedFromThis<FChaosVDEngine> { public: FChaosVDEngine(); virtual ~FChaosVDEngine(); void Initialize(); void CloseActiveTraceSessions(); void CloseSessionByRemoteSessionID(FGuid RemoteSessionID); void StopActiveTraceSessions(); void DeInitialize(); virtual bool Tick(float DeltaTime) override; const FGuid& GetInstanceGuid() const { return InstanceGUID; } TSharedPtr<FChaosVDScene>& GetCurrentScene() { return CurrentScene; } TSharedPtr<FChaosVDPlaybackController>& GetPlaybackController() { return PlaybackController; } bool HasAnyLiveSessionActive() const;`
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSessionStateChangedDelegate, const struct FChaosVDTraceSessionDescriptor& InSessionDescriptor) PRAGMA_ENABLE_DEPRECATION_WARNINGS class FChaosVDEngine : public FTSTickerObjectBase, public TSharedFromThis<FChaosVDEngine> { public: FChaosVDEngine(); virtual ~FChaosVDEngine(); void Initialize(); void CloseActiveTraceSessions(); void CloseSessionByRemoteSessionID(FGuid RemoteSessionID); void StopActiveTraceSessions(); void DeInitialize(); virtual bool Tick(float DeltaTime) override; const FGuid& GetInstanceGuid() const { return InstanceGUID; } TSharedPtr<FChaosVDScene>& GetCurrentScene() { return CurrentScene; } TSharedPtr<FChaosVDPlaybackController>& GetPlaybackController() { return PlaybackController; } bool HasAnyLiveSessionActive() const; void LoadRecording(const FString& FilePath, EChaosVDLoadRecordedDataMode LoadingMode = EChaosVDLoadRecordedDataMode::MultiSource); void LoadCombinedMultiRecording(const FString& FilePath);`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDExtractedGeometryDataHandle.h` (Public)


#### struct `FChaosVDExtractedGeometryDataHandle`  
`struct FChaosVDExtractedGeometryDataHandle`  
_L20-117_
- desc: Structure that acts as a handle to access the generated static mesh of a implicit object, plus other data extracted from it
- L23 _public function_ `uint32 GetDataComponentKey() const` — Key to be used to match this geometry with recorded Shape Data
- L27 _public function_ `void SetDataComponentKey(const uint32 Key)`
- L33 _public function_ `uint32 GetGeometryKey() const` — Key representing the generated static mesh - Handles for different implicit objects can point to the same geometry key, if after being unpacked they result in essentially the same mesh
- L37 _public prototype_ `void SetGeometryKey(const uint32 Key);`
- L40 _public prototype_ `FName GetTypeName() const;` — Name of the type this underlying implicit object this instance represents
- L43 _public function_ `const FTransform& GetRelativeTransform() const` — Extracted transform of the generated implicit object in component space
- L47 _public function_ `void SetTransform(const FTransform& InTransform)`
- L53 _public function_ `const Chaos::FImplicitObject* GetImplicitObject() const` — Ptr to the implicit object this handle provides access to and from which the mesh was generated
- L59 _public function_ `int32 GetShapeInstanceIndex() const` — Returns the Index to correct the shape data instance in the shape instances array of the particle that owns this geometry
- L65 _public function_ `const Chaos::FImplicitObject* GetRootImplicitObject() const` — If the object was an union and this was a leaf, this getter returns the root union object, otherwise it will be the same as GetImplicitObject
- L71 _public function_ `void SetImplicitObject(const Chaos::FImplicitObject* InImplicitObject)` — Sets the Implicit Object Ptr from which the data was extracted and the mesh was generated
- L77 _public function_ `void SetShapeInstanceIndex(int32 InObjectIndex)` — Sets the Index on which this Implicit object was in the Hierarchy of the root one
- L83 _public function_ `void SetRootImplicitObject(const Chaos::FImplicitObject* InImplicitObject)` — Sets the Implicit Object Ptr from which the data was extracted and the mesh was generated
- L88 _public function_ `bool operator==(const FChaosVDExtractedGeometryDataHandle& Other) const`
- L101 _private member_ `uint32 GeometryKey = 0;` — Key representing the generated static mesh
- L104 _private member_ `uint32 DataComponentKey = 0;` — Key to be used to match this geometry with recorded Shape Data
- L107 _private member_ `int32 ShapeInstanceIndex = INDEX_NONE;` — Index on which this Implicit object was in the Hierarchy of the root one
- L110 _private member_ `FTransform Transform;` — Extracted transform of the generated implicit object in component space
- L113 _private member_ `const Chaos::FImplicitObject* ImplicitObject = nullptr;` — The Implicit Object Ptr from which the data was extracted and the mesh was generated
- L116 _private member_ `const Chaos::FImplicitObject* RootImplicitObject = nullptr;` — If the object was an union and this was a leaf, this will be the root union object, otherwise it will be the same as ImplicitObject

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Chaos`
- L93 _function_ `friend uint32 GetTypeHash(const FChaosVDExtractedGeometryDataHandle& Handle)`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDGeometryBuilder.h` (Public)


#### enum `EChaosVDGeometryTransformGeneratorFlags`  
`enum class EChaosVDGeometryTransformGeneratorFlags`  
_L46-51_
- desc: Set of flags used to control how we generate a transform from implicit object data
- L48 _public enumerator_ `None = 0`
- L50 _public enumerator_ `UseScaleForSize = 1 << 0` — When calculating the adjusted transform, it will generate a scale to represent the actual size of the implicit object

#### class `FChaosVDGeometryBuilder`  
`class FChaosVDGeometryBuilder : public FGCObject, public TSharedFromThis<FChaosVDGeometryBuilder>`  
_L57-399_
- inherits: `FGCObject,TSharedFromThis<FChaosVDGeometryBuilder>`
- desc: Generates Dynamic mesh components and dynamic meshes based on Chaos implicit object data
- L61 _public function_ `FChaosVDGeometryBuilder()`
- L68 _public prototype_ `void Initialize(const TWeakPtr<FChaosVDScene>& ChaosVDScene);`
- L69 _public prototype_ `void DeInitialize();`
- L79 _public prototype_ `void CreateMeshesFromImplicitObject(const Chaos::FImplicitObject* InImplicitObject, TArray<TPair<TSharedPtr<FChaosVDExtractedGeometryDataHandle>, TSharedPtr<Chaos::VD::FChaosVDImplicitObjectView>>>& OutMeshDataHandles, Chaos::VD::FChaosVDImplicitObjectView* Root, int32 AvailableShapeDataNum = 0, const int32 DesiredLODCount = 0, const Chaos::FRigidTransform3& InTransform = Chaos::FRigidTransform3(), const int32 MeshIndex = 0);` — Creates Dynamic Mesh components for each object within the provided Implicit object @param InImplicitObject : Implicit object to process @param OutMeshDataHandles Array containing all the generated components paired with their corresponding implicit objects @param Root ImplicitObjectView to attach children to @param DesiredLODCount Number of LODs to generate for the mesh. @param MeshIndex Index of the current component being processed. This is useful when this method is called recursively @param InTransform to apply to the generated components/geometry
- L81 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L82 _public function_ `virtual FString GetReferencerName() const override`
- L93 _public prototype_ `static bool DoesImplicitContainType(const Chaos::FImplicitObject* InImplicitObject, const Chaos::EImplicitObjectType ImplicitTypeToCheck);` — Evaluates an Implicit objects and returns true if it contains an object of the specified type @param InImplicitObject Object to evaluate @param ImplicitTypeToCheck Object type to compare against @return
- L99 _public prototype_ `static bool HasNegativeScale(const Chaos::FRigidTransform3& InTransform);` — Evaluates the provided transform's scale, and returns true if the scale has a negative component @param InTransform Transform to evaluate
- L103 _private prototype_ `void CreateMeshesFromImplicit_Internal(const Chaos::FImplicitObject* InRootImplicitObject,const Chaos::FImplicitObject* InLeafImplicitObject, TArray<TPair<TSharedPtr<FChaosVDExtractedGeometryDataHandle>, TSharedPtr<Chaos::VD::FChaosVDImplicitObjectView>>>& OutMeshDataHandles, Chaos::VD::FChaosVDImplicitObjectView* Root, const int32 DesiredLODCount = 0, const Chaos::FRigidTransform3& InTransform = Chaos::FRigidTransform3(), const int32 ParentShapeInstanceIndex = 0, int32 AvailableShapeDataNum = 0);`
- L110 _public prototype_ `bool HasGeometryInCache(uint32 GeometryKey);` — Return true if we have cached geometry for the provided Geometry Key @param GeometryKey Cache key for the geometry we are looking for
- L111 _public prototype_ `bool HasGeometryInCache_AssumesLocked(uint32 GeometryKey) const;`
- L116 _public prototype_ `UStaticMesh* GetCachedMeshForImplicit(const uint32 GeometryCacheKey);` — Returns an already mesh for the provided implicit object if exists, otherwise returns null @param GeometryCacheKey Key to be used to find this geometry in the cache
- L125 _private prototype_ `UStaticMesh* CreateAndCacheStaticMesh(const uint32 GeometryCacheKey, UE::Geometry::FMeshShapeGenerator& MeshGenerator, const int32 LODsToGenerateNum = 0);` — Creates a Dynamic Mesh for the provided Implicit object and generator, and then caches it to be reused later @param GeometryCacheKey Key to be used to find this geometry in the cache @param MeshGenerator Generator class with the data and rules to create the mesh @param LODsToGenerateNum Number of LODs to generate for this static mesh
- L132 _private prototype_ `template <class ComponentType> bool InitializeMeshComponent(AActor* Owner, ComponentType* MeshComponent);` — Takes a Mesh component ptr and initializes it to be used with the provided owner @param Owner Actor that will own the provided Mesh Component @param MeshComponent Component to initialize
- L137 _private prototype_ `void SetMeshComponentMaterial(IChaosVDGeometryComponent* GeometryComponent);` — Sets the correct material for the provided Geometry component based on its configuration @param GeometryComponent Component that needs its materia updated
- L141 _public prototype_ `void HandleNewGeometryData(const Chaos::FConstImplicitObjectPtr& Geometry, const uint32 GeometryID);`
- L149 _public prototype_ `template<typename ComponentType> TSharedPtr<FChaosVDInstancedMeshData> CreateMeshDataInstance(const FChaosVDParticleDataWrapper& InOwningParticleData, const TSharedRef<FChaosVDExtractedGeometryDataHandle>& InExtractedGeometryDataHandle);` — Finds or creates a Mesh component for the geometry data handle provided, and add a new instance of that geometry to it @param InOwningParticleData Particle data from which the implicit object is from @param InExtractedGeometryDataHandle Handle to the extracted geometry data the new component will use
- L158 _public prototype_ `template<typename ComponentType> void UpdateMeshDataInstance(const TSharedRef<FChaosVDInstancedMeshData>& InHandleToUpdate, EChaosVDMeshAttributesFlags MeshAttributes);` — Finds or creates a Mesh component compatible with the provided mesh data handle, and updates the handle to use that new component. This is used when data in the handle changed and becomes no longer compatible with the mesh component in use. @param HandleToUpdate Instance handle we need to update to a new component @param MeshAttributes Attributes of the mesh that the new component needs to be compativle with
- L165 _public prototype_ `void DestroyMeshComponent(UMeshComponent* MeshComponent);` — Destroys a Mesh component that will not longer be used. If pooling is enabled, the component will be reset and added back to the pool @param MeshComponent Component to Destroy
- L170 _public prototype_ `void RequestMaterialUpdate(UMeshComponent* MeshComponent);` — Enqueues a component to have its material updated based on its configuration @param MeshComponent Component to Update
- L174 _private prototype_ `void CachePreBuiltMeshes();`
- L181 _private prototype_ `template<typename ComponentType> ComponentType* GetMeshComponentForNewInstance(const TSharedRef<FChaosVDExtractedGeometryDataHandle>& GeometryDataHandle, EChaosVDMeshAttributesFlags MeshAttributes);` — Gets a ptr to a fully initialized Mesh component compatible with the provided geometry handle and mesh attribute flags, ready to accept a new mesh instance @param GeometryDataHandle Handle with the data of the geometry to be used for the new instance @param MeshAttributes Set of flags that the mesh component needs to be compatible with
- L186 _private prototype_ `TMap<uint32, UChaosVDInstancedStaticMeshComponent*>& GetInstancedStaticMeshComponentCacheMap(EChaosVDMeshAttributesFlags MeshAttributeFlags);` — Gets a reference to the correct instanced static mesh component cache that is compatible with the provided mesh attribute flags @param MeshAttributeFlags GeometryHandle this component will render
- L195 _private prototype_ `template <typename ComponentType> ComponentType* GetAvailableInstancedStaticMeshComponent(const TSharedPtr<FChaosVDExtractedGeometryDataHandle>& InExtractedGeometryDataHandle, AActor* MeshComponentsContainerActor, EChaosVDMeshAttributesFlags MeshComponentAttributeFlags, bool& bOutIsNewComponent);` — Gets any available instanced static mesh component that is compatible with the provided mesh attributes and component type @param InExtractedGeometryDataHandle GeometryHandle this component will render @param MeshComponentsContainerActor Actor that will owns the mesh component @param MeshComponentAttributeFlags Set of flags that the mesh component needs to be compatible with @param bOutIsNewComponent True if the component we are returning is new. False if it is an existing one but that can take a new mesh instance
- L204 _private prototype_ `template <typename ComponentType> ComponentType* GetAvailableMeshComponent(const TSharedPtr<FChaosVDExtractedGeometryDataHandle>& InExtractedGeometryDataHandle, AActor* MeshComponentsContainerActor, EChaosVDMeshAttributesFlags MeshComponentAttributeFlags, bool& bOutIsNewComponent);` — Gets any available mesh component that is compatible with the provided mesh attributes and component type @param InExtractedGeometryDataHandle GeometryHandle this component will render @param MeshComponentsContainerActor Actor that will owns the mesh component @param MeshComponentAttributeFlags Set of flags that the mesh component needs to be compatible with @param bOutIsNewComponent True if the component we are returning is new. False if it is an existing one but that can take a new mesh instance
- L211 _private prototype_ `bool ApplyMeshToComponentFromKey(TWeakObjectPtr<UMeshComponent> MeshComponent, const uint32 GeometryKey);` — Applies a mesh to a mesh component based on its type @param MeshComponent Mesh component to apply the mesh to @param GeometryKey Key to find the mesh to apply in the cache
- L218 _public prototype_ `TSharedPtr<UE::Geometry::FMeshShapeGenerator> CreateMeshGeneratorForImplicitObject(const Chaos::FImplicitObject* InImplicit, float SimpleShapesComplexityFactor = 1.0f);` — Creates a mesh generator for the provided Implicit object which will be used to create a Static Mesh @param InImplicit ImplicitObject used a data source for the mesh generator @param SimpleShapesComplexityFactor Factor used to reduce or increase the complexity (number of triangles generated) of simple shapes (Sphere/Capsule)
- L221 _public prototype_ `bool ImplicitObjectNeedsUnpacking(const Chaos::FImplicitObject* InImplicitObject) const;` — Returns true if the implicit object if of one of the types we need to unpack before generating a mesh for it
- L227 _public prototype_ `const Chaos::FImplicitObject* UnpackImplicitObject(const Chaos::FImplicitObject* InImplicitObject, Chaos::FRigidTransform3& InOutTransform) const;` — Unwraps the provided Implicit object into the object it self so a mesh can be generated from it @param InImplicitObject Object to unwrap @param InOutTransform Transform that was extracted from the implicit object. Might be unchanged if the implicit proved was not transformed or scaled
- L233 _public prototype_ `void AdjustedTransformForImplicit(const Chaos::FImplicitObject* InImplicit, FTransform& OutAdjustedTransform, EChaosVDGeometryTransformGeneratorFlags Options = EChaosVDGeometryTransformGeneratorFlags::None);` — Re-adjust the provided transform if needed, so it can be visualized properly with its generated mesh @param InImplicit Source implicit object @param OutAdjustedTransform Updated transform
- L240 _private prototype_ `TSharedPtr<FChaosVDExtractedGeometryDataHandle> ExtractGeometryDataForImplicit(const Chaos::FImplicitObject* InImplicitObject, const Chaos::FRigidTransform3& InTransform);` — Extracts data from an implicit object in a format CVD can use, and starts the Mesh generation process if needed @return Returns a handle to the generated data that can be used to access the generated mesh when ready
- L248 _private prototype_ `void DispatchCreateAndCacheMeshForImplicitAsync(const uint32 GeometryCacheKey, const Chaos::FImplicitObject* ImplicitObject, const int32 LODsToGenerateNum = 0);` — Creates a Mesh from the provided Implicit object geometry data. This is a async operation, and the mesh will be assigned to the component once is ready @param GeometryCacheKey Key to be used to find this geometry in the cache @param ImplicitObject Implicit object to use a sdata source to create the static mesh @param LODsToGenerateNum Num of LODs to Generate. Not all mesh types support this
- L252 _private prototype_ `template <bool bIsInstanced, typename GeometryType> const GeometryType* GetGeometry(const Chaos::FImplicitObject* InImplicit, const bool bIsScaled, Chaos::FRigidTransform3& OutTransform) const;` — Process an FImplicitObject and returns de desired geometry type. Could be directly the shape or another version of the implicit
- L256 _private prototype_ `template<typename GeometryType> const GeometryType* GetGeometryBasedOnPackedType(const Chaos::FImplicitObject* InImplicitObject, Chaos::FRigidTransform3& Transform, const Chaos::EImplicitObjectType PackedType) const;` — Process an FImplicitObject and returns de desired geometry type based on the packed object flags. Could be directly the shape or another version of the implicit
- L259 _private prototype_ `bool GameThreadTick(float DeltaTime);` — Tick method of this Geometry builder. Used to do everything that needs to be performed in the GT, like applying the generated meshes to mesh component
- L266 _private prototype_ `void AddMeshComponentWaitingForGeometry(uint32 GeometryKey, TWeakObjectPtr<UMeshComponent> MeshComponent) const;` — Add a mesh component to the waiting list for Geometry. This needs to be called before dispatching a generation job for new Geometry @param GeometryKey Key of the geometry that is being generated (or will be generated) @param MeshComponent Component where the geometry needs to be applied
- L273 _private prototype_ `void RemoveMeshComponentWaitingForGeometry(uint32 GeometryKey, TWeakObjectPtr<UMeshComponent> MeshComponent) const;` — Add a mesh component to the waiting list for Geometry. This needs to be called before dispatching a generation job for new Geometry @param GeometryKey Key of the geometry that is being generated (or will be generated) @param MeshComponent Component where the geometry needs to be applied
- L275 _private prototype_ `void RequestMeshForComponent(const TSharedRef<FChaosVDExtractedGeometryDataHandle>& SourceGeometry, UMeshComponent* MeshComponent);`
- L278 _private function_ `FChaosVDMeshComponentPool& GetMeshComponentDataPool()` — Returns a reference to the Mesh components pool used by this builder
- L286 _private prototype_ `bool UsesPreBuiltGeometry(Chaos::EImplicitObjectType ObjetType) const;` — Returns true if the provided Implicit object type can use a pre-built static mesh* @param ObjetType Type to evaluate
- L289 _private prototype_ `void HandleStaticMeshComponentInstanceIndexUpdated(UInstancedStaticMeshComponent* InComponent, TArrayView<const FInstancedStaticMeshDelegates::FInstanceIndexUpdateData> InIndexUpdates);` — Handles any changes to the indexes of created instanced mesh components we are managing, making corrections/updates as needed
- L292 _private member_ `TMap<uint32, TObjectPtr<UStaticMesh>> StaticMeshCacheMap;` — Map containing already generated static mesh for any given implicit object
- L295 _private member_ `TMap<uint32, TSharedPtr<FChaosVDGeometryGenerationTask>> GeometryBeingGeneratedByKey;` — Set of all geometry keys of the Meshes that are being generated but not ready yet
- L298 _private member_ `FRWLock GeometryCacheRWLock;` — Used to lock Read or Writes to the Geometry cache and in flight job tracking containers
- L301 _private member_ `FTSTicker::FDelegateHandle GameThreadTickDelegate;` — Handle to the ticker used to ticker the Geometry Builder in the game thread
- L304 _private member_ `TUniquePtr<FObjectsWaitingGeometryList<FMeshComponentWeakPtr>> MeshComponentsWaitingForGeometry;` — Object containing all the meshes component waiting for geometry, by geometry key
- L306 _private member_ `TUniquePtr<FObjectsWaitingProcessingQueue<FMeshComponentWeakPtr>> MeshComponentsWaitingForMaterial;`
- L308 _private member_ `TUniquePtr<FObjectsWaitingProcessingQueue<TSharedPtr<FChaosVDGeometryGenerationTask>>> GeometryTasksPendingLaunch;`
- L311 _private member_ `TMap<uint32, UChaosVDInstancedStaticMeshComponent*> InstancedMeshComponentByGeometryKey;` — Map containing already initialized Instanced static mesh components for any given geometry key
- L314 _private member_ `TMap<uint32, UChaosVDInstancedStaticMeshComponent*> TranslucentInstancedMeshComponentByGeometryKey;` — Map containing already initialized Instanced static mesh components ready to be use with translucent materials, for any given geometry key
- L317 _private member_ `TMap<uint32, UChaosVDInstancedStaticMeshComponent*> MirroredInstancedMeshComponentByGeometryKey;` — Map containing already initialized Instanced static mesh components for mesh instances that required a negative scale transform, for any given geometry key
- L320 _private member_ `TMap<uint32, UChaosVDInstancedStaticMeshComponent*> TranslucentMirroredInstancedMeshComponentByGeometryKey;` — Map containing already initialized Instanced static mesh components for mesh instances that required a negative scale transform and use a translucent material, for any given geometry key
- L323 _private member_ `TArray<TObjectPtr<UMeshComponent>> MeshComponentsPendingDisposal;` — Components that need to be processed and added to the pool in the next frame
- L326 _private member_ `FChaosVDMeshComponentPool ComponentMeshPool;` — Instance of uninitialized mesh components pool
- L329 _private member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;` — Weak Ptr to the CVD scene owning this geometry builder
- L331 _private member_ `TObjectPtr<UStaticMesh> BasicShapesMeshes[Chaos::ImplicitObjectType::ConcreteObjectCount];`
- L333 _private member_ `bool bInitialized = false;`
- L396 _private member_ `FSourceGeometryHashCache SourceGeometryCache;`
- L438 _function_ `template <typename ComponentType> bool FChaosVDGeometryBuilder::InitializeMeshComponent(AActor* Owner, ComponentType* MeshComponent)`
- L469 _function_ `template <typename ComponentType> ComponentType* FChaosVDGeometryBuilder::GetAvailableInstancedStaticMeshComponent(const TSharedPtr<FChaosVDExtractedGeometryDataHandle>& InExtractedGeometryDataHandle, AActor* MeshComponentsContainerActor, EChaosVDMeshAttributesFlags MeshComponentAttributeFlags, bool& bOutIsNewComponent)`
- L493 _function_ `template <typename ComponentType> ComponentType* FChaosVDGeometryBuilder::GetAvailableMeshComponent(const TSharedPtr<FChaosVDExtractedGeometryDataHandle>& InExtractedGeometryDataHandle, AActor* MeshComponentsContainerActor, EChaosVDMeshAttributesFlags MeshComponentAttributeFlags, bool& bOutIsNewComponent)`
- L518 _function_ `template <typename ComponentType> TSharedPtr<FChaosVDInstancedMeshData> FChaosVDGeometryBuilder::CreateMeshDataInstance(const FChaosVDParticleDataWrapper& InOwningParticleData, const TSharedRef<FChaosVDExtractedGeometryDataHandle>& InExtractedGeometryDataHandle)`
- L546 _function_ `template <typename ComponentType> void FChaosVDGeometryBuilder::UpdateMeshDataInstance(const TSharedRef<FChaosVDInstancedMeshData>& InHandleToUpdate, EChaosVDMeshAttributesFlags MeshAttributes)`
- L559 _function_ `template <typename ComponentType> ComponentType* FChaosVDGeometryBuilder::GetMeshComponentForNewInstance(const TSharedRef<FChaosVDExtractedGeometryDataHandle>& GeometryDataHandle, EChaosVDMeshAttributesFlags MeshAttributes)`
- L596 _function_ `template <bool bIsInstanced, typename GeometryType> const GeometryType* FChaosVDGeometryBuilder::GetGeometry(const Chaos::FImplicitObject* InImplicitObject, const bool bIsScaled, Chaos::FRigidTransform3& OutTransform) const`
- L623 _function_ `template <typename GeometryType> const GeometryType* FChaosVDGeometryBuilder::GetGeometryBasedOnPackedType(const Chaos::FImplicitObject* InImplicitObject, Chaos::FRigidTransform3& Transform, const Chaos::EImplicitObjectType PackedType) const`

#### struct `FChaosVDGeometryBuilder::FSourceGeometryHashCache`  
`struct FSourceGeometryHashCache`  
_L335-394_
- L340 _public function_ `[[nodiscard]] uint32 GetAndCacheGeometryHash(const Chaos::FImplicitObject* ImplicitObject)` — Returns the hash for the provided implicit object and caches it if it is the first time we see it. @param ImplicitObject Implicit Object from which get the hash from
- L364 _public function_ `bool HasGeometryInHashCache(const Chaos::FImplicitObject* ImplicitObject)` — Returns true if we have the hash for the provided implicit object in cache @param ImplicitObject Implicit Object to cache
- L374 _public function_ `void CacheImplicitObjectHash(const Chaos::FImplicitObject* ImplicitObject, uint32 Hash)` — Caches the provided hash linking it to the provided implicit object @param ImplicitObject Implicit Object from which the has was calculated from @param Hash Hash from the Implicit Object
- L386 _public function_ `void Reset()` — Clears the hash cache
- L392 _public member_ `FRWLock CacheLock;`
- L393 _public member_ `TMap<const void*, uint32> CachedGeometryHashes;`

#### class `FChaosVDGeometryGenerationTask`  
`class FChaosVDGeometryGenerationTask`  
_L404-435_
- desc: Used to execute each individual Geometry Generation task using the data with which was constructed. It allows the task to skip the actual generation attempt if the Geometry builder instance goes away which happens when the tool is closed
- L407 _public function_ `FChaosVDGeometryGenerationTask(const TWeakPtr<FChaosVDGeometryBuilder>& InBuilder, const uint32 GeometryKey, const Chaos::FImplicitObject* ImplicitObject, const int32 LODsToGenerateNum) : Builder(InBuilder), ImplicitObject(ImplicitObject), GeometryKey(GeometryKey), LODsToGenerateNum(LODsToGenerateNum), bIsCanceled(false)`
- L417 _public prototype_ `void GenerateGeometry();`
- L419 _public function_ `uint32 GetGeometryKey() const`
- L424 _public function_ `bool IsCanceled()`
- L425 _public function_ `void CancelTask()`
- L427 _public member_ `UE::Tasks::FTask TaskHandle;`
- L430 _private member_ `TWeakPtr<FChaosVDGeometryBuilder> Builder;`
- L431 _private member_ `const Chaos::FImplicitObject* ImplicitObject;`
- L432 _private member_ `uint32 GeometryKey;`
- L433 _private member_ `int32 LODsToGenerateNum;`
- L434 _private member_ `std::atomic<bool> bIsCanceled;`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace UE`
- L35 _namespace_ `namespace Geometry` (scope `UE`)
- L42 _typedef_ `typedef TWeakObjectPtr<UMeshComponent> FMeshComponentWeakPtr;`
- L43 _typedef_ `typedef TSharedPtr<FChaosVDExtractedGeometryDataHandle> FExtractedGeometryHandle;`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDGeometryDataComponent.h` (Public)


#### enum `EChaosVDMaterialType`  
`enum class EChaosVDMaterialType`  
_L38-44_
- reflection: `UENUM()`
- L40 _public enumerator_ `SMOpaque`
- L41 _public enumerator_ `SMTranslucent`
- L42 _public enumerator_ `ISMCOpaque`
- L43 _public enumerator_ `ISMCTranslucent`

#### enum `EChaosVDMeshComponent`  
`enum class EChaosVDMeshComponent`  
_L47-53_
- reflection: `UENUM()`
- L49 _public enumerator_ `Invalid`
- L50 _public enumerator_ `Static`
- L51 _public enumerator_ `InstancedStatic`
- L52 _public enumerator_ `Dynamic`

#### struct `FChaosVDImplicitObjectBasicView`  
`struct FChaosVDImplicitObjectBasicView`  
_L57-78_
- reflection: `USTRUCT()`
- desc: Struct holding the a minimum amount of data about a Implicit object to be shown in the details panel
- L63 _public member_ `FName ImplicitObjectType;` — `UPROPERTY(VisibleAnywhere, Category="Recorded GeometryData")` — Geometry type name
- L65 _public member_ `Chaos::EImplicitObjectType ImplicitObjectTypeEnum = Chaos::ImplicitObjectType::Unknown;`
- L69 _public member_ `int32 ShapeInstanceIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Recorded GeometryData")` — Index of the Shape Instance data for this geometry in the Shape Instance data array
- L73 _public member_ `bool bIsRootObject = false;` — `UPROPERTY(VisibleAnywhere, Category="Recorded GeometryData")` — True if this is the root implicit object
- L77 _public member_ `FTransform RelativeTransform;` — `UPROPERTY(VisibleAnywhere, Category="Recorded GeometryData")` — If this is a transformed implicit, this will contain the recorded relative transform

#### struct `FChaosVDMeshDataInstanceState`  
`struct FChaosVDMeshDataInstanceState`  
_L82-130_
- reflection: `USTRUCT()`
- desc: Struct holding the state of a mesh instance - Is separated from the Mesh instance class so we can show the data in the Details panel
- L88 _public member_ `FChaosVDShapeCollisionData CollisionData;` — `UPROPERTY(VisibleAnywhere, Category="Recorded GeometryData")` — Recorded Shape instance Data
- L92 _public member_ `FChaosVDImplicitObjectBasicView ImplicitObjectInfo;` — `UPROPERTY(VisibleAnywhere, Category="Recorded GeometryData")` — Minimum set of data about the recorded implicit object
- L96 _public member_ `FTransform CurrentWorldTransform;` — `UPROPERTY(VisibleAnywhere, Category="CVD GeometryData", meta=(EditCondition=bShowCVDDebugData, EditConditionHides))` — CVD Debug - Current world transform used to render this Mesh
- L100 _public member_ `EChaosVDMeshComponent MeshComponentType = EChaosVDMeshComponent::Invalid;` — `UPROPERTY(VisibleAnywhere, Category="CVD GeometryData", meta=(EditCondition=bShowCVDDebugData, EditConditionHides))` — CVD Debug - Current mesh component type to render this Mesh
- L104 _public member_ `TObjectPtr<UMeshComponent> MeshComponent;` — `UPROPERTY()` — CVD Debug - Pointer to the mesh component used to render this Mesh
- L108 _public member_ `int32 MeshInstanceIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="CVD GeometryData", meta=(EditCondition=bShowCVDDebugData, EditConditionHides))` — CVD Debug - Instance index of mesh component used to render this Mesh
- L112 _public member_ `FLinearColor CurrentGeometryColor = FLinearColor(ForceInitToZero);` — `UPROPERTY(VisibleAnywhere, Category="CVD GeometryData", meta=(EditCondition=bShowCVDDebugData, EditConditionHides))` — CVD Debug - Color used to render this mesh
- L116 _public member_ `int32 OwningParticleID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="CVD GeometryData", meta=(EditCondition=bShowCVDDebugData, EditConditionHides))` — CVD Debug - Id of the particle this geometry belongs
- L120 _public member_ `int32 OwningSolverID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="CVD GeometryData", meta=(EditCondition=bShowCVDDebugData, EditConditionHides))` — CVD Debug - Id of the solver this geometry belongs
- L123 _public member_ `bool bIsVisible = true;` — `UPROPERTY(VisibleAnywhere, Category="CVD GeometryData", meta=(EditCondition=bShowCVDDebugData, EditConditionHides))`
- L126 _public member_ `bool bIsSelected = false;` — `UPROPERTY(VisibleAnywhere, Category="CVD GeometryData", meta=(EditCondition=bShowCVDDebugData, EditConditionHides))`
- L129 _public member_ `bool bShowCVDDebugData = false;` — `UPROPERTY(EditAnywhere, Category="CVD GeometryData")`

#### class `FChaosVDInstancedMeshData`  
`class FChaosVDInstancedMeshData : public TSharedFromThis<FChaosVDInstancedMeshData>`  
_L133-272_
- inherits: `TSharedFromThis<FChaosVDInstancedMeshData>`
- desc: Structure that represents a specific mesh instance on a CVD Mesh component (instanced or static)
- L136 _public prototype_ `explicit FChaosVDInstancedMeshData(int32 InInstanceIndex, UMeshComponent* InMeshComponent, int32 InParticleID, int32 InSolverID, const TSharedRef<FChaosVDExtractedGeometryDataHandle>& InSourceGeometryHandle);`
- L139 _public function_ `int32 GetOwningParticleID() const` — Returns the Particle ID of the particle owning this mesh instance
- L145 _public function_ `int32 GetOwningSolverID() const` — Returns the Solver ID of the particle owning this mesh instance
- L153 _public prototype_ `void SetWorldTransform(const FTransform& InTransform);` — Applies the provided world transform to the mesh instance this handle represents @param InTransform Transform to apply
- L156 _public function_ `const FTransform& GetWorldTransform() const` — Returns the world transform of the mesh instance this handle represents
- L162 _public function_ `const TSharedRef<FChaosVDExtractedGeometryDataHandle>& GetGeometryHandle() const` — Returns the geometry handle used to create the mesh instance this handle represents
- L168 _public prototype_ `void SetInstanceColor(const FLinearColor& NewColor);` — Applies to the provided color to the mesh instance this handle represents
- L171 _public function_ `FLinearColor GetInstanceColor() const` — Returns the current color of the mesh instance this handle represents
- L177 _public prototype_ `void UpdateMeshComponentForCollisionData(const FChaosVDShapeCollisionData& InCollisionData);` — Applies to the provided shape collision data to the mesh instance this handle represents
- L180 _public function_ `UMeshComponent* GetMeshComponent() const` — Returns the mesh component used to render the mesh instance this handle represents
- L186 _public function_ `int32 GetMeshInstanceIndex() const` — Returns the instance index of the mesh instance this handle represents
- L192 _public function_ `EChaosVDMeshComponent GetMeshComponentType() const` — Returns the type of the component used to render the mesh instance this handle represents
- L198 _public function_ `void SetGeometryBuilder(const TWeakPtr<FChaosVDGeometryBuilder>& InGeometryBuilder)` — Sets a Ptr to the geometry builder used to generate and manage the geometry/mesh components this handle represents
- L202 _public function_ `TWeakPtr<FChaosVDGeometryBuilder> GetGeometryBuilder()`
- L208 _public prototype_ `void SetIsSelected(bool bInIsSelected);` — Marks this mesh instance as selected. Used to handle Selection in Editor
- L211 _public prototype_ `void SetVisibility(bool bInIsVisible);` — Sets the visibility of this mesh instance
- L214 _public function_ `bool GetVisibility() const` — Returns the current visibility state this mesh instance
- L220 _public prototype_ `void SetGeometryCollisionData(const FChaosVDShapeCollisionData&& InCollisionData);` — Applies a new shape collision data to this mesh instance
- L223 _public function_ `FChaosVDShapeCollisionData& GetGeometryCollisionData()` — Returns the current shape collision data to this mesh instance
- L228 _public function_ `FChaosVDMeshDataInstanceState& GetState()`
- L234 _public member_ `bool bFailedToUpdateShapeInstanceData = false;` — Used only for debugging purposes - It will be set to true if we received new Shape Instance data but the Shape Index for the implicit object we represent is not valid
- L237 _public function_ `void SetMeshInstanceIndex(int32 NewIndex)` — Sets the mesh instance index of the mesh instance this handle represents
- L243 _public function_ `bool IsPendingDestroy() const` — Returns true if this instance is queued to be destroyed
- L249 _public function_ `void MarkPendingDestroy()` — Marks a instance that is queued to be destroyed at the end of the frame
- L257 _private function_ `void SetMeshComponent(UMeshComponent* NewComponent)` — Sets the mesh component used to render the mesh instance this handle represents
- L262 _private member_ `FChaosVDMeshDataInstanceState InstanceState;`
- L264 _private member_ `bool bIsPendingDestroy = false;`
- L266 _private member_ `TSharedRef<FChaosVDExtractedGeometryDataHandle> ExtractedGeometryHandle;`
- L268 _private member_ `TWeakPtr<FChaosVDGeometryBuilder> GeometryBuilderInstance = nullptr;`

#### class `Chaos::VD::FChaosVDImplicitObjectView`  
`class FChaosVDImplicitObjectView : public TSharedFromThis<FChaosVDImplicitObjectView>`  
_L278-307_
- inherits: `TSharedFromThis<FChaosVDImplicitObjectView>`
- desc: Class that represents an Implicit Object to be shown in the Geometry Hierarchy Viewer
- L281 _public member_ `Chaos::EImplicitObjectType ImplicitObjectType;`
- L282 _public member_ `FChaosVDImplicitObjectBasicView ImplicitObjectInfo;`
- L284 _public function_ `void AddChild(TSharedPtr<FChaosVDImplicitObjectView> Child)`
- L289 _public function_ `TSharedPtr<TArray<TSharedPtr<FChaosVDImplicitObjectView>>> GetChildren()`
- L294 _public function_ `void SetMeshData(TSharedPtr<FChaosVDInstancedMeshData> InMeshData)`
- L299 _public function_ `TSharedPtr<FChaosVDInstancedMeshData> GetMeshData()`
- L305 _private member_ `TSharedPtr<TArray<TSharedPtr<FChaosVDImplicitObjectView>>> Children = MakeShared<TArray<TSharedPtr<FChaosVDImplicitObjectView>>>();`
- L306 _private member_ `TSharedPtr<FChaosVDInstancedMeshData> MeshData;`

#### enum `EChaosVDMeshAttributesFlags`  
`enum class EChaosVDMeshAttributesFlags : uint8`  
_L310-315_
- L312 _public enumerator_ `None = 0`
- L313 _public enumerator_ `MirroredGeometry = 1 << 0`
- L314 _public enumerator_ `TranslucentGeometry = 1 << 1`

#### class `UChaosVDGeometryComponent`  
`class UChaosVDGeometryComponent : public UInterface`  
_L320-323_
- reflection: `UINTERFACE()`
- inherits: `UInterface`

#### class `IChaosVDGeometryComponent`  
`class IChaosVDGeometryComponent`  
_L329-413_
- desc: Interface with a default implementation for any Geometry component that contains CVD data
- L336 _public prototype_ `virtual uint32 GetGeometryKey() const PURE_VIRTUAL(IChaosVDGeometryDataComponent::GetGeometryKey, return 0;);` — Returns the Geometry Handle used to identify the geometry data this component represents
- L339 _public prototype_ `virtual TSharedPtr<FChaosVDInstancedMeshData> GetMeshDataInstanceHandle(int32 InstanceIndex) const PURE_VIRTUAL(IChaosVDGeometryDataComponent::GetMeshDataInstanceHandle, return nullptr;);` — Returns the CVD Mesh Data Instance handle for the provided Instance index
- L350 _public prototype_ `virtual TSharedPtr<FChaosVDInstancedMeshData> AddMeshInstance(const FTransform InstanceTransform, bool bIsWorldSpace, const TSharedRef<FChaosVDExtractedGeometryDataHandle>& InGeometryHandle, int32 ParticleID, int32 SolverID) PURE_VIRTUAL(IChaosVDGeometryDataComponent::AddMeshInstance, return nullptr;);` — Add a new instance to this mesh component @param InstanceTransform The transform the new instance will use @param bIsWorldSpace True if the provide transform is in world space @param InGeometryHandle The CVD Geometry Handle with data about the geometry instantiate @param ParticleID Particle ID owning this geometry @param SolverID Solver ID of the particle owning this geometry @return CVD Mesh instance handle that provides access to this component and specific instance, allowing manipulation of it
- L356 _public prototype_ `virtual void AddExistingMeshInstance(const TSharedRef<FChaosVDInstancedMeshData>& InMeshDataHandle) PURE_VIRTUAL(IChaosVDGeometryDataComponent::AddExistingMeshInstance);` — Adds a new instance to this mesh component, but using an existing Mesh Data Handle instead of creating a new one @param InMeshDataHandle Handle that will provide access to this mesh instance
- L368 _public prototype_ `virtual void RemoveMeshInstance(const TSharedRef<FChaosVDInstancedMeshData>& InHandleToRemove, ERemovalMode Mode = ERemovalMode::Deferred) PURE_VIRTUAL(IChaosVDGeometryDataComponent::RemoveMeshInstance);` — Removes the instance the provided handle represents @param InHandleToRemove
- L371 _public prototype_ `virtual bool IsMeshReady() const PURE_VIRTUAL(IChaosVDGeometryDataComponent::IsMeshReady, return false;);` — True if the mesh this component represents is ready for use
- L374 _public prototype_ `virtual void SetIsMeshReady(bool bIsReady) PURE_VIRTUAL(IChaosVDGeometryDataComponent::SetIsMeshReady);` — Sets if the mesh this component represents is ready for use or not
- L377 _public prototype_ `virtual FChaosVDMeshReadyDelegate* OnMeshReady() PURE_VIRTUAL(IChaosVDGeometryDataComponent::OnMeshReady, return nullptr;);` — Triggers when the mesh this component represents is ready
- L380 _public prototype_ `virtual FChaosVDMeshComponentEmptyDelegate* OnComponentEmpty() PURE_VIRTUAL(IChaosVDGeometryDataComponent::OnComponentEmpty, return nullptr;);` — Triggers when the component does not have any instance to render. Used to allow it to return to the mesh component tool for future re-use
- L383 _public prototype_ `virtual void UpdateVisibilityForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) PURE_VIRTUAL(IChaosVDGeometryDataComponent::UpdateVisibilityForInstance);` — Updates the visibility of this component based on the stored CVD data
- L386 _public prototype_ `virtual void UpdateSelectionStateForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) PURE_VIRTUAL(IChaosVDGeometryDataComponent::UpdateSelectionStateForInstance);` — Changes the selection state of the provided instance - Used for Selection in Editor
- L389 _public prototype_ `virtual void UpdateColorForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) PURE_VIRTUAL(IChaosVDGeometryDataComponent::UpdateColorForInstance);` — Updates the colors of this component based on the stored CVD data
- L392 _public prototype_ `virtual void UpdateWorldTransformForInstance(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle) PURE_VIRTUAL(IChaosVDGeometryDataComponent::UpdateWorldTransformForInstance);` — Updates the colors of this component based on the stored CVD data
- L395 _public prototype_ `virtual void SetMeshComponentAttributeFlags(EChaosVDMeshAttributesFlags Flags) PURE_VIRTUAL(IChaosVDGeometryDataComponent::SetMeshComponentAttributeFlags);` — Sets the CVD Mesh Attribute flags this component is compatible with
- L398 _public prototype_ `virtual EChaosVDMeshAttributesFlags GetMeshComponentAttributeFlags() const PURE_VIRTUAL(IChaosVDGeometryDataComponent::GetMeshComponentAttributeFlags, return EChaosVDMeshAttributesFlags::None;);` — Returns the CVD Mesh Attribute flags this component is compatible with
- L401 _public prototype_ `virtual void Reset() PURE_VIRTUAL(IChaosVDGeometryDataComponent::Reset);` — Resets the state of this mesh component, so it can be re-used later on
- L403 _public prototype_ `virtual void Initialize() PURE_VIRTUAL(IChaosVDGeometryDataComponent::Initialize);`
- L406 _public prototype_ `virtual void SetGeometryBuilder(TWeakPtr<FChaosVDGeometryBuilder> GeometryBuilder) PURE_VIRTUAL(IChaosVDGeometryDataComponent::SetGeometryBuilder);` — Sets a Ptr to the geometry builder used to generate and manage the geometry/mesh components
- L408 _public prototype_ `virtual EChaosVDMaterialType GetMaterialType() const PURE_VIRTUAL(IChaosVDGeometryDataComponent::GetMaterialType, return EChaosVDMaterialType::SMOpaque;);`
- L410 _public prototype_ `virtual bool GetIsDestroyed() const PURE_VIRTUAL(IChaosVDGeometryDataComponent::GetIsDestroyed, return false;);`
- L412 _public prototype_ `virtual void SetIsDestroyed(bool bNewIsDestroyed) PURE_VIRTUAL(IChaosVDGeometryDataComponent::SetIsDestroyed);`

#### enum `IChaosVDGeometryComponent::ERemovalMode`  
`enum class ERemovalMode`  
_L358-362_
- L360 _public enumerator_ `Instant`
- L361 _public enumerator_ `Deferred`

#### class `FChaosVDGeometryComponentUtils`  
`class FChaosVDGeometryComponentUtils`  
_L415-443_
- L419 _public prototype_ `static void UpdateCollisionDataFromShapeArray(TArrayView<FChaosVDShapeCollisionData> InShapeArray, const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle);` — Finds and updates the Shape data using the provided array as source
- L422 _public prototype_ `static void UpdateMeshColor(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle, const FChaosVDParticleDataWrapper& InParticleData, bool bIsServer);` — Calculates and updates the color used to render the mesh represented by the provided handle, based on the particle state
- L425 _public prototype_ `static void UpdateMeshVisibility(const TSharedRef<FChaosVDInstancedMeshData>& InInstanceHandle, const FChaosVDParticleDataWrapper& InParticleData, bool bIsActive);` — Calculates the correct visibility state based on the particle state, and applies it to the mesh instance the provided handle represents
- L428 _public prototype_ `static UMaterialInterface* GetBaseMaterialForType(EChaosVDMaterialType Type);` — Returns the material to use as a base to create material instances for the provided type
- L432 _public prototype_ `template<typename TComponent> static EChaosVDMaterialType GetMaterialTypeForComponent(EChaosVDMeshAttributesFlags MeshAttributes);` — Returns the correct material type to use based on the provided Component type and Mesh Attributes
- L436 _private prototype_ `static FLinearColor GetGeometryParticleColor(const TSharedRef<FChaosVDExtractedGeometryDataHandle>& InGeometryHandle, const FChaosVDParticleDataWrapper& InParticleData, bool bIsServer);` — Returns the color that needs to be used to present the provided particle data based on its state and current selected options
- L438 _private prototype_ `static const UChaosVDParticleVisualizationColorSettings* GetParticleColorSettings();`
- L439 _private prototype_ `static const UChaosVDParticleVisualizationSettings* GetParticleVisualizationSettings();`
- L441 _private member_ `static TObjectPtr<UChaosVDParticleVisualizationColorSettings> CachedParticleColorSettings;`
- L442 _private member_ `static TObjectPtr<UChaosVDParticleVisualizationSettings> CachedParticleVisualizationSettings;`
- L446 _function_ `template <typename TComponent> EChaosVDMaterialType FChaosVDGeometryComponentUtils::GetMaterialTypeForComponent(EChaosVDMeshAttributesFlags MeshAttributes)`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace Chaos`
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDMeshReadyDelegate, IChaosVDGeometryComponent&) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDMeshComponentEmptyDelegate, UMeshComponent*) UENUM() enum class EChaosVDMaterialType { SMOpaque, SMTranslucent, ISMCOpaque, ISMCTranslucent };`
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDMeshComponentEmptyDelegate, UMeshComponent*) UENUM() enum class EChaosVDMaterialType { SMOpaque, SMTranslucent, ISMCOpaque, ISMCTranslucent };`
- L275 _namespace_ `namespace Chaos`
- L275 _namespace_ `namespace VD` (scope `Chaos`)
- L459 _namespace_ `namespace Chaos`
- L459 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L461 _prototype_ `void SelectParticleWithGeometryInstance(const TSharedRef<FChaosVDScene>& InScene, FChaosVDSceneParticle* Particle, const TSharedPtr<FChaosVDInstancedMeshData>& InMeshDataHandle);` (scope `Chaos::VisualDebugger`)

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDMiscSceneObjectTypeNamesForTesting.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`
- L7 _namespace_ `namespace VD` (scope `Chaos`)
- L7 _namespace_ `namespace Test` (scope `Chaos::VD`)
- L7 _namespace_ `namespace SceneObjectTypes` (scope `Chaos::VD::Test`)
- L9 _externvar_ `extern FName SceneQuery;` (scope `Chaos::VD::Test::SceneObjectTypes`)
- L10 _externvar_ `extern FName CollisionConstraint;` (scope `Chaos::VD::Test::SceneObjectTypes`)
- L11 _externvar_ `extern FName JointConstraint;` (scope `Chaos::VD::Test::SceneObjectTypes`)
- L12 _externvar_ `extern FName CharacterGroundConstraint;` (scope `Chaos::VD::Test::SceneObjectTypes`)

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDModule.h` (Public)


#### class `FChaosVDModule`  
`class FChaosVDModule : public IModuleInterface`  
_L25-82_
- inherits: `IModuleInterface`
- L29 _public typedef_ `using ToolkitHostType = SChaosVDMainTab;`
- L31 _public prototype_ `static FChaosVDModule& Get();`
- L34 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L35 _public prototype_ `virtual void ShutdownModule() override;`
- L38 _public function_ `TSharedPtr<UE::TraceBasedDebuggers::FTraceSessionsManager>& GetTraceSessionsManager()` — Returns the Trace manager instance used by CVD
- L44 _public function_ `TSharedPtr<class FChaosVDTraceManager> GetTraceManager()` — `UE_DEPRECATED(5.8, "Use GetTraceSessionsManager")`
- L50 _public prototype_ `void SpawnCVDTab();` — Spawns a new instance of CVD
- L52 _public prototype_ `static bool IsStandaloneChaosVisualDebugger();`
- L55 _public prototype_ `void ReloadInstanceUI(FGuid InstanceGUID);` — Re-instantiates CVD's widgets without restarting the underlying CVD engine instance
- L57 _public prototype_ `void TakePlaybackEngineStateSnapshot();`
- L61 _private prototype_ `TSharedRef<SDockTab> SpawnMainTab(const FSpawnTabArgs& Args);`
- L63 _private prototype_ `void HandleTabClosed(TSharedRef<SDockTab> ClosedTab, FGuid InstanceGUID);`
- L65 _private prototype_ `void RegisterChaosVDEngineInstance(const FGuid& InstanceGuid, TSharedPtr<FChaosVDEngine> Instance);`
- L66 _private prototype_ `void DeregisterChaosVDEngineInstance(const FGuid& InstanceGuid);`
- L68 _private prototype_ `void RegisterChaosVDTabInstance(const FGuid& InstanceGuid, TSharedPtr<SDockTab> Instance);`
- L69 _private prototype_ `void DeregisterChaosVDTabInstance(const FGuid& InstanceGuid);`
- L71 _private prototype_ `void CloseActiveInstances();`
- L73 _private member_ `TMap<FGuid, TSharedPtr<FChaosVDEngine>> ActiveChaosVDInstances;`
- L75 _private member_ `TMap<FGuid, TWeakPtr<SDockTab>> ActiveCVDTabs;`
- L77 _private member_ `TSharedPtr<UE::TraceBasedDebuggers::FTraceSessionsManager> ChaosVDTraceManager;`
- L79 _private member_ `static FString ChaosVisualDebuggerProgramName;`
- L81 _private member_ `bool bIsShuttingDown = false;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L24 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosVDEditor, Log, VeryVerbose);` — Main module class for the Chaos Visual Debugger editor
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosVDEditor, Log, VeryVerbose);` — Main module class for the Chaos Visual Debugger editor

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDObjectDetailsTab.h` (Public)


#### class `FChaosVDStandAloneObjectDetailsTab`  
`class FChaosVDStandAloneObjectDetailsTab : public FChaosVDTabSpawnerBase, public TSharedFromThis<FChaosVDStandAloneObjectDetailsTab>`  
_L23-62_
- inherits: `FChaosVDTabSpawnerBase,TSharedFromThis<FChaosVDStandAloneObjectDetailsTab>`
- desc: Spawns and handles an instance for a selection independent details panel
- L27 _public function_ `FChaosVDStandAloneObjectDetailsTab(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget)`
- L31 _public function_ `TSharedPtr<SChaosVDDetailsView> GetDetailsPanel()`
- L36 _public prototype_ `void AddUnsupportedStruct(const UStruct* Struct);`
- L40 _public prototype_ `template<typename TStruct> void SetStructToInspect(TStruct* NewStruct);` — Updates the current object this view details is viewing
- L43 _public prototype_ `void UpdateTabLabel(const FText& NewLabel);` — Updates the label shown on the docked tab header
- L47 _protected prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`
- L48 _protected prototype_ `virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed) override;`
- L50 _protected prototype_ `bool IsSupportedStruct(const TWeakObjectPtr<const UStruct>& InWeakStructPtr);`
- L52 _protected prototype_ `void UpdateTreeDetailsSplit(const FChaosVDSceneParticle* Particle);`
- L54 _protected member_ `TSharedPtr<SChaosVDDetailsView> DetailsPanelView;`
- L55 _protected member_ `TSharedPtr<SChaosVDGeometryTree> GeometryTreeWidget;`
- L56 _protected member_ `TSharedPtr<SSplitter> DetailsSplitter;`
- L57 _protected member_ `float SavedSplitSize = 0.2f;`
- L59 _protected member_ `TSet<TWeakObjectPtr<const UStruct>> UnsupportedStructs;`
- L61 _protected member_ `TWeakPtr<SDockTab> SpawnedTab;`
- L65 _function_ `template <typename TStruct> void FChaosVDStandAloneObjectDetailsTab::SetStructToInspect(TStruct* NewStruct)`

#### class `FChaosVDObjectDetailsTab`  
`class FChaosVDObjectDetailsTab : public FChaosVDStandAloneObjectDetailsTab, public FChaosVDSceneSelectionObserver`  
_L71-92_
- inherits: `FChaosVDStandAloneObjectDetailsTab,FChaosVDSceneSelectionObserver`
- desc: Spawns and handles an instance for the visual debugger details panel
- L75 _public function_ `FChaosVDObjectDetailsTab(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget) : FChaosVDStandAloneObjectDetailsTab(InTabID, InTabManager, InOwningTabWidget)`
- L81 _protected prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`
- L82 _protected prototype_ `virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed) override;`
- L84 _protected prototype_ `virtual void HandlePostSelectionChange(const UTypedElementSelectionSet* ChangedSelectionSet) override;`
- L86 _protected prototype_ `void HandleActorsSelection(TArrayView<AActor*> SelectedActors);`
- L88 _protected prototype_ `virtual void HandleSolverDataSelectionChange(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& SelectionHandle);`
- L90 _protected member_ `FDelegateHandle SelectionDelegateHandle;`
- L91 _protected member_ `TWeakObjectPtr<UObject> CurrentSelectedObject = nullptr;`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDPlaybackController.h` (Public)


#### enum `EChaosVDTrackType`  
`enum class EChaosVDTrackType : int32`  
_L34-41_
- desc: Enum with the available game track types
- L36 _public enumerator_ `Invalid`
- L37 _public enumerator_ `Game`
- L38 _public enumerator_ `Solver`
- L40 _public enumerator_ `All` — Used mostly for search

#### struct `FChaosVDTrackInfo`  
`struct FChaosVDTrackInfo`  
_L44-71_
- desc: Data that represents the current state of a track and ID info
- L46 _public member_ `int32 TrackID = INDEX_NONE;`
- L47 _public member_ `int32 TrackSlot = INDEX_NONE;`
- L48 _public member_ `EChaosVDTrackType TrackType = EChaosVDTrackType::Invalid;`
- L49 _public member_ `int32 CurrentFrame = INDEX_NONE;`
- L50 _public member_ `int32 CurrentStage = INDEX_NONE;`
- L51 _public member_ `int32 LockedOnStage = INDEX_NONE;`
- L52 _public member_ `int32 MaxFrames = INDEX_NONE;`
- L53 _public member_ `FName TrackName;`
- L54 _public member_ `TArray<FStringView> CurrentStageNames;`
- L55 _public member_ `bool bIsReSimulated = false;`
- L56 _public member_ `bool bIsPlaying = false;`
- L57 _public member_ `bool bTrackSyncEnabled = true;`
- L58 _public member_ `bool bIsServer = false;`
- L59 _public member_ `bool bHasNetworkSyncData = false;`
- L60 _public member_ `bool bSupportsVisibilityChange = true;`
- L61 _public member_ `bool bCanShowTrackControls = true;`
- L63 _public prototype_ `bool operator==(const FChaosVDTrackInfo& Other) const;`
- L65 _public prototype_ `static bool AreSameTrack(const TSharedRef<const FChaosVDTrackInfo>& TrackA, const TSharedRef<const FChaosVDTrackInfo>& TrackB);`
- L67 _public function_ `bool IsValidTrack() const`

#### struct `FChaosVDQueuedTrackInfoUpdate`  
`struct FChaosVDQueuedTrackInfoUpdate`  
_L73-77_
- L75 _public member_ `TWeakPtr<const FChaosVDTrackInfo> TrackInfo;`
- L76 _public member_ `FGuid InstigatorID;`

#### struct `FChaosVDGeometryDataUpdate`  
`struct FChaosVDGeometryDataUpdate`  
_L79-83_
- L81 _public member_ `Chaos::FConstImplicitObjectPtr NewGeometry;`
- L82 _public member_ `uint32 GeometryID;`

#### enum `EChaosVDUnloadRecordingFlags`  
`enum class EChaosVDUnloadRecordingFlags : uint8`  
_L86-91_
- desc: Flags used to control how the unload of a recording is performed
- L88 _public enumerator_ `None = 0`
- L89 _public enumerator_ `BroadcastChanges = 1 << 0`
- L90 _public enumerator_ `Silent = 1 << 1`

#### enum `EChaosVDSyncTimelinesMode`  
`enum class EChaosVDSyncTimelinesMode : uint8`  
_L96-107_
- reflection: `UENUM()`
- desc: Available sync modes that determine how tracks will sync between each other during playback
- L98 _public enumerator_ `None UMETA(Hidden)`
- L100 _public enumerator_ `RecordedTimestamp` — Syncs all tracks using the recorded timestamp
- L102 _public enumerator_ `NetworkTick` — Syncs all tracks using the recorded network ticks offset of the Predictive networked physics system
- L106 _public enumerator_ `Manual` — No-Auto sync is performed and all available solver tracks inside the recording are visible at once and can be scrubbed independently

#### class `FChaosVDPlaybackController`  
`class FChaosVDPlaybackController : public TSharedFromThis<FChaosVDPlaybackController>, public FTSTickerObjectBase`  
_L112-566_
- inherits: `TSharedFromThis<FChaosVDPlaybackController>,FTSTickerObjectBase`
- desc: Loads,unloads and owns a Chaos VD recording file
- L117 _public member_ `static constexpr int32 GameTrackID = 0;` — ID used for the Game Track
- L118 _public member_ `static constexpr int32 GameTrackSlot = 0;`
- L119 _public member_ `static constexpr int32 InvalidFrameRateOverride = -1;`
- L120 _public member_ `static constexpr float FallbackFrameTime = 1.0f / 60.0f;`
- L122 _public member_ `static inline FGuid PlaybackSelfInstigatorID = FGuid::NewGuid();`
- L124 _public prototype_ `FChaosVDPlaybackController(const TWeakPtr<FChaosVDScene>& InSceneToControl);`
- L127 _public prototype_ `void Initialize();`
- L128 _public prototype_ `void DeInitialize();`
- L131 _public prototype_ `bool LoadChaosVDRecordingFromTraceSession(const UE::TraceBasedDebuggers::FTraceSessionDescriptor& InSessionDescriptor);` — Loads a recording using a CVD Trace Session Descriptor
- L135 _public prototype_ `bool LoadChaosVDRecordingFromTraceSession(const struct FChaosVDTraceSessionDescriptor& InSessionDescriptor);` — `UE_DEPRECATED(5.8, "Use the version taking UE::TraceBasedDebuggers::FTraceSessionDescriptor in parameter")`
- L141 _public prototype_ `void UnloadCurrentRecording(EChaosVDUnloadRecordingFlags UnloadOptions = EChaosVDUnloadRecordingFlags::BroadcastChanges);` — Unloads the currently loaded recording @param UnloadOptions Options flags to change the steps performed during the unload
- L144 _public function_ `bool IsRecordingLoaded() const` — Returns true if the controller has a valid recording loaded
- L150 _public function_ `TWeakPtr<FChaosVDScene> GetControllerScene()` — Returns a weak ptr to the Scene this controller is controlling during playback
- L163 _public prototype_ `void GoToTrackFrame(FGuid InstigatorID, EChaosVDTrackType TrackType, int32 InTrackID, int32 FrameNumber, int32 StageNumber);` — Moves a track of the recording to the specified stage and frame numbers @param InstigatorID ID of the system that requested the move @param TrackType Type of the track to move @param InTrackID ID of the track to move @param FrameNumber Frame number to go to @param StageNumber Stage number to go to
- L164 _public prototype_ `void GoToTrackFrame_AssumesLocked(FGuid InstigatorID, EChaosVDTrackType TrackType, int32 InTrackID, int32 FrameNumber, int32 StageNumber);`
- L174 _public prototype_ `void GoToTrackFrameAndSync(FGuid InstigatorID, EChaosVDTrackType TrackType, int32 InTrackID, int32 FrameNumber, int32 StageNumber);` — Moves a track of the recording to the specified stage and frame numbers. And then syncs every other track to it @param InstigatorID ID of the system that requested the move @param TrackType Type of the track to move @param InTrackID ID of the track to move @param FrameNumber Frame number to go to @param StageNumber Stage number to go to
- L175 _public prototype_ `void GoToTrackFrame_AssumesLockedAndSync(FGuid InstigatorID, EChaosVDTrackType TrackType, int32 InTrackID, int32 FrameNumber, int32 StageNumber);`
- L184 _public prototype_ `int32 GetTrackStagesNumberAtFrame_AssumesLocked(EChaosVDTrackType TrackType, int32 InTrackID, int32 FrameNumber) const;` — Gets the number of available stages in a track at the specified frame @param TrackType Type of the track to evaluate @param InTrackID ID of the track to evaluate @param FrameNumber Frame number to evaluate @return Number of available Stages
- L193 _public prototype_ `const FChaosVDFrameStagesContainer* GetTrackStagesDataAtFrame_AssumesLocked(EChaosVDTrackType TrackType, int32 InTrackID, int32 FrameNumber) const;` — Gets the available stages container in a track at the specified frame @param TrackType Type of the track to evaluate @param InTrackID ID of the track to evaluate @param FrameNumber Frame number to evaluate @return Ptr to the stages data container
- L201 _public prototype_ `int32 GetTrackFramesNumber(EChaosVDTrackType TrackType, int32 InTrackID) const;` — Gets the number of available frames for the specified track @param TrackType Type of the track to evaluate @param InTrackID ID of the track to evaluate @return Number of available frames
- L202 _public prototype_ `int32 GetTrackFramesNumber_AssumesLocked(EChaosVDTrackType TrackType, int32 InTrackID) const;`
- L210 _public prototype_ `int32 GetTrackCurrentFrame(EChaosVDTrackType TrackType, int32 InTrackID) const;` — Gets the current frame number at which the specified track is at @param TrackType Type of the track to evaluate @param InTrackID ID of the track to evaluate @return Current frame number for the track
- L218 _public prototype_ `int32 GetTrackCurrentStage(EChaosVDTrackType TrackType, int32 InTrackID) const;` — Gets the number of available frames for the specified track @param TrackType Type of the track to evaluate @param InTrackID ID of the track to evaluate @return Number of available frames
- L226 _public prototype_ `int32 GetTrackLastStageAtFrame(EChaosVDTrackType TrackType, int32 InTrackID, int32 InFrameNumber) const;` — Gets the index number of the last stage available (available stages -1) @param TrackType Type of the track to evaluate @param InTrackID ID of the track to evaluate @return Number of the last stages
- L227 _public prototype_ `int32 GetTrackLastStageAtFrame_AssumesLocked(EChaosVDTrackType TrackType, int32 InTrackID, int32 InFrameNumber) const;`
- L235 _public prototype_ `int32 ConvertCurrentFrameToOtherTrackFrame_AssumesLocked(const TSharedRef<const FChaosVDTrackInfo>& InFromTrack, const TSharedRef<const FChaosVDTrackInfo>& InToTrack, EChaosVDSyncTimelinesMode TrackSyncMode = EChaosVDSyncTimelinesMode::RecordedTimestamp);` — Converts the current frame number of a track, to a frame number in other tracks space time @param InFromTrack Track info with the current frame number we want to convert @param InToTrack Track info we want to use to convert the frame to @param TrackSyncMode Criteria or "mode" that should be used to sync a track frame with another @return Converted Frame Number
- L243 _public prototype_ `void GetAvailableTracks(EChaosVDTrackType TrackType, TArray<TSharedPtr<const FChaosVDTrackInfo>>& OutTrackInfo);`
- L244 _public prototype_ `void GetMutableAvailableTracks(EChaosVDTrackType TrackType, TArray<TSharedPtr<FChaosVDTrackInfo>>& OutTrackInfo);`
- L252 _public prototype_ `void GetAvailableTrackInfosAtTrackFrame(EChaosVDTrackType TrackTypeToFind, const TSharedRef<const FChaosVDTrackInfo>& InFromTrack, TArray<TSharedPtr<const FChaosVDTrackInfo>>& OutTrackInfo);` — Gets all the ids of the tracks, of the specified type, that are available available on the loaded recording, at a specified frame @param TrackTypeToFind Type of the tracks we are interested in @param OutTrackInfo Array where any found track info data will be added @param InFromTrack Ptr to the track info with the current frame to evaluate
- L253 _public prototype_ `void GetAvailableTrackInfosAtTrackFrame_AssumesLocked(EChaosVDTrackType TrackTypeToFind, const TSharedRef<const FChaosVDTrackInfo>& InFromTrack, TArray<TSharedPtr<const FChaosVDTrackInfo>>& OutTrackInfo);`
- L261 _public prototype_ `TSharedPtr<const FChaosVDTrackInfo> GetTrackInfo(EChaosVDTrackType TrackType, int32 TrackID);` — Gets the track info of the specified type with the specified ID @param TrackType Type of the track to find @param TrackID ID of the track to find @return Ptr to the found track info data - Null if nothing was found
- L269 _public prototype_ `TSharedPtr<FChaosVDTrackInfo> GetMutableTrackInfo(EChaosVDTrackType TrackType, int32 TrackID);` — Gets the track info of the specified type with the specified ID @param TrackType Type of the track to find @param TrackID ID of the track to find @return Ptr to the found track info data - Null if nothing was found.
- L276 _public prototype_ `void LockTrackInCurrentStage(EChaosVDTrackType TrackType, int32 TrackID);` — Locks the stages timeline of a given track so each time you move between frames, it will automatically scrub to the locked in stage @param TrackType Type of the track to find @param TrackID ID of the track to find
- L283 _public prototype_ `void UnlockTrackStage(EChaosVDTrackType TrackType, int32 TrackID);` — UnLocks the stages timeline of a given track so each time you move between frames, it will automatically scrub to the default stage @param TrackType Type of the track to find @param TrackID ID of the track to find
- L286 _public function_ `TWeakPtr<FChaosVDRecording> GetCurrentRecording()` — Returns a weak ptr pointer to the loaded recording
- L292 _public function_ `FChaosVDPlaybackControllerUpdated& OnDataUpdated()` — Called when data on the recording being controlled gets updated internally or externally (for example, during Trace Analysis)
- L298 _public function_ `FChaosVDPlaybackControllerFrameUpdated& OnTrackFrameUpdated()` — Called when a frame on a track is updated
- L303 _public function_ `FChaosVDInitialFirstFramePlayed& OnFirstFramePlayed()`
- L308 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L311 _public prototype_ `bool IsPlayingLiveSession() const;` — Returns true if we are playing a live debugging session
- L314 _public prototype_ `void HandleDisconnectedFromSession();` — Updates the loaded recording state to indicate is not longer receiving live updates
- L320 _public prototype_ `void StopPlayback(const FGuid& InstigatorGUID);` — Stops the playback (if active) @param InstigatorGUID ID of the system that is making the stop attempt
- L323 _public function_ `bool IsUsingFrameRateOverride() const` — Returns if we are playing back at a custom framerate instead of the recorded framerate
- L329 _public function_ `bool ToggleUseFrameRateOverride()` — Toggles on or off the framerate override feature
- L335 _public prototype_ `float GetFrameTimeOverride() const;` — Returns the frame rate override value, as frame time
- L337 _public prototype_ `int32 GetFrameRateOverride() const;` — Returns the frame rate override value
- L340 _public prototype_ `void SetFrameRateOverride(float NewFrameRateOverride);` — Sets the desired framerate override value
- L349 _public prototype_ `float GetFrameTimeForTrack(EChaosVDTrackType TrackType, int32 TrackID, const TSharedRef<const FChaosVDTrackInfo>& InTrackInfo) const;` — Returns the the recorded frame time for the provided track info @param TrackType Type of the track (Game or Solver) @param TrackID ID of the track @param InTrackInfo Track info structure used to identify data as what frame we are currently in @return
- L350 _public prototype_ `float GetFrameTimeForTrack_AssumesLocked(EChaosVDTrackType TrackType, int32 TrackID, const TSharedRef<const FChaosVDTrackInfo>& InTrackInfo) const;`
- L358 _public prototype_ `void UpdateTrackVisibility(EChaosVDTrackType Type, int32 TrackID, bool bNewVisibility);` — Changes the visibility of a specific track @param Type Type of the track (Game or Solver) @param TrackID ID of the track @param bNewVisibility New visibility value
- L366 _public prototype_ `bool IsTrackVisible(EChaosVDTrackType Type, int32 TrackID);` — Return the current visibility state of the specified track @param Type Type of the track (Game or Solver) @param TrackID ID of the track @return true if the track is visible
- L374 _public prototype_ `void HandleFramePlaybackControlInput(EChaosVDPlaybackButtonsID ButtonID, const TSharedRef<const FChaosVDTrackInfo>& InTrackInfoRef, FGuid Instigator);` — Handles an external playback control input (usually from the UI) for a frame @param ButtonID ID determinig the playback action @param InTrackInfoRef RefPtr to the track the actions should be applied to @param Instigator ID of the system that is making the input attempt
- L382 _public prototype_ `void HandleFrameStagePlaybackControlInput(EChaosVDPlaybackButtonsID ButtonID, const TSharedRef<const FChaosVDTrackInfo>& InTrackInfoRef, FGuid Instigator);` — Handles an external playback control input (usually from the UI) for a solver stage @param ButtonID ID determinig the playback action @param InTrackInfoRef RefPtr to the track the actions should be applied to @param Instigator ID of the system that is making the input attempt
- L387 _public prototype_ `void TickPlayback(float DeltaTime);` — Advances the playback @param DeltaTime Current Delta Time
- L390 _public function_ `TSharedRef<FChaosVDTrackInfo> GetActiveTrackInfo() const` — Returns the state of the current active track.
- L400 _public prototype_ `void GetTracksByType(EChaosVDTrackType Type, TArray<TSharedPtr<FChaosVDTrackInfo>>& OutTracks);` — Gathers all track states of the specified type @param Type Track type (Gamne or Solver) @param OutTracks Outs a list of matching track states
- L408 _public prototype_ `void SyncTracks(const TSharedRef<const FChaosVDTrackInfo>& FromTrack, FGuid InstigatorID, EChaosVDSyncTimelinesMode TrackSyncMode = EChaosVDSyncTimelinesMode::RecordedTimestamp);` — Scrubs all tracks to the correct frame to be in sync with the provided track @param FromTrack Track that every other track needs to sync to @param InstigatorID ID of the system that is instigating the playback action @param TrackSyncMode Sync mode determining how the sync is calculated (Timestamp, Network tick, etc)
- L409 _public prototype_ `void SyncTracks_AssumesLocked(const TSharedRef<const FChaosVDTrackInfo>& FromTrack, FGuid InstigatorID, EChaosVDSyncTimelinesMode TrackSyncMode = EChaosVDSyncTimelinesMode::RecordedTimestamp);`
- L415 _public prototype_ `void ToggleTrackSyncEnabled(const TSharedRef<const FChaosVDTrackInfo>& InTrackInfoRef);` — Toggles the sync functionality on the provided track @param InTrackInfoRef RefPtr to the track we want to change
- L418 _public prototype_ `bool IsPlaying() const;` — Returns true if we are in continuous playback mode
- L420 _public function_ `bool IsScrubbingTimeline() const`
- L425 _public prototype_ `void SetScrubbingTimeline(bool bNewIsScrubbingTimeline);`
- L428 _public function_ `EChaosVDSyncTimelinesMode GetTimelineSyncMode() const` — Returns the current sync mode for tracks
- L437 _public prototype_ `TSharedPtr<const FChaosVDTrackInfo> GetTrackToReSyncFromOnModeChange(EChaosVDSyncTimelinesMode SyncMode);` — Finds and returns a track instance that can be used as sync point for the new timeline mode change @param SyncMode New timeline Sync Mode
- L438 _public prototype_ `TSharedPtr<const FChaosVDTrackInfo> GetTrackToReSyncFromOnModeChange_AssumesLocked(EChaosVDSyncTimelinesMode SyncMode);`
- L446 _public prototype_ `bool IsCompatibleWithSyncMode(const TSharedRef<const FChaosVDTrackInfo>& InTrackRef, EChaosVDSyncTimelinesMode SyncMode);` — Checks if the provided track is compatible with a specific sync mode @param InTrackRef Track to check against @param SyncMode Timeline sync mode to verify if the provided track is compatible with @return true if the provided track is compatible with the provided sync mode
- L449 _public prototype_ `void SetTimelineSyncMode(EChaosVDSyncTimelinesMode SyncMode);` — Sets a new sync mode to be used between tracks
- L455 _public prototype_ `void TrySetActiveTrack(int32 SlotIndex);` — Attempts to set the track on the specified slot as active. An active track is the track to all key shortcuts will be applied @param SlotIndex Slot of the track we want to make active
- L461 _public prototype_ `void TrySetActiveTrack(const TSharedRef<const FChaosVDTrackInfo>& NewActiveTrack);` — Attempts to set the provided track as active. An active track is the track to all key shortcuts will be applied @param NewActiveTrack Slot of the track we want to make active
- L470 _public prototype_ `FChaosVDPlaybackEngineSnapshot GeneratePlaybackEngineSnapshot();` — Creates and populates an object containing information about the state of the playback engine and scene. This is used by functional tests to compare a known good state agains ones generated in future versions @return Playback engine state data @note If you change the data being added here, you need to re-generate the snapshots used by the scene integrity playback tests in the Simulation Tests Plugin
- L477 _protected prototype_ `void BroadcastGTDataUpdate(const TWeakPtr<FChaosVDPlaybackController>& InControllerWeakPtr);` — Broadcast from the game thread data in this controller was updated @param InControllerWeakPtr A pre created weak ptr instance to this controller
- L483 _protected prototype_ `void ProcessQueuedTrackInfoUpdates(const TWeakPtr<FChaosVDPlaybackController>& InControllerWeakPtr);` — Process and broadcast from the game thread track info updates @param InControllerWeakPtr A pre created weak ptr instance to this controller
- L486 _protected prototype_ `void UpdateSolverTracksData();` — Updates (or adds) solvers data from the loaded recording to the solver tracks
- L489 _protected prototype_ `void GoToRecordedGameFrame_AssumesLocked(int32 FrameNumber, FGuid InstigatorID);` — Updates the controlled scene with the loaded data at specified game frame
- L492 _protected prototype_ `void GoToRecordedSolverStage_AssumesLocked(int32 InTrackID, int32 FrameNumber, int32 StageNumber, FGuid InstigatorID);` — Updates the controlled scene with the loaded data at specified solver frame and solver Stage
- L495 _protected prototype_ `void HandleCurrentRecordingUpdated();` — Handles any data changes on the loaded recording - Usually called during Trace analysis
- L498 _protected prototype_ `void PlayFromClosestKeyFrame_AssumesLocked(int32 InTrackID, int32 FrameNumber, FChaosVDScene& InSceneToControl);` — Finds the closest Key frame to the provided frame number, and plays all the following frames until the specified frame number (no inclusive)
- L501 _protected prototype_ `void EnqueueTrackInfoUpdate(const TSharedRef<const FChaosVDTrackInfo>& InTrackInfo, FGuid InstigatorID);` — Add the provided track info update to the queue. The update will be broadcast in the game thread
- L503 _protected prototype_ `void PlaySolverStageData(int32 TrackID, const TSharedRef<FChaosVDScene>& InSceneToControlSharedPtr, const FChaosVDSolverFrameData& InSolverFrameData, int32 StageIndex);`
- L506 _protected prototype_ `template <typename TVisitorCallback> void VisitAvailableTracks(const TVisitorCallback& VisitorCallback);`
- L508 _protected prototype_ `TSharedRef<FChaosVDTrackInfo> CreateTrackInfo(int32 SlotIndex = INDEX_NONE);`
- L510 _protected prototype_ `void HandleGeneralSettingsUpdated(UObject* SettingsObject);`
- L512 _protected member_ `bool bIsScrubbingTimeline = false;`
- L515 _protected member_ `TMap<EChaosVDTrackType, TrackInfoByIDMap> TrackInfoPerType;` — Map containing all track info, by track type
- L518 _protected member_ `TSharedPtr<FChaosVDRecording> LoadedRecording;` — Ptr to the loaded recording
- L521 _protected member_ `TWeakPtr<FChaosVDScene> SceneToControl;` — Ptr to the current Chaos VD Scene this controller controls
- L524 _protected member_ `FChaosVDPlaybackControllerUpdated ControllerUpdatedDelegate;` — Delegate called when the data on the loaded recording changes
- L527 _protected member_ `FChaosVDPlaybackControllerFrameUpdated ControllerFrameUpdatedDelegate;` — Delegate called when the data in a track changes
- L530 _protected member_ `FChaosVDInitialFirstFramePlayed ControllerFirstFramePlayedDelegate;` — Delegate called when the first frame is played on recording load
- L533 _protected member_ `std::atomic<bool> bHasPendingGTUpdateBroadcast;` — Set to true when the recording data controlled by this Playback Controller is updated, the update delegate will be called on the GT
- L536 _protected member_ `uint64 RecordingLastSeenTimeUpdatedAsCycle = 0;` — Last seen Platform Cycle on which the loaded recording was updated
- L539 _protected member_ `TQueue<FChaosVDQueuedTrackInfoUpdate, EQueueMode::Mpsc> TrackInfoUpdateGTQueue;` — Queue with a copy of all Track Info Updates that needs to be done in the Game thread
- L541 _protected member_ `bool bPlayedFirstFrame = false;`
- L543 _protected member_ `int32 MaxFramesLaggingBehindDuringLiveSession = 50;`
- L544 _protected member_ `int32 MinFramesLaggingBehindDuringLiveSession = 5;`
- L546 _protected member_ `int32 CurrentFrameRateOverride = 60;`
- L548 _protected member_ `bool bUseFrameRateOverride = false;`
- L550 _protected member_ `bool bPauseRequested = false;`
- L552 _protected member_ `FDelegateHandle RecordingStoppedHandle;`
- L554 _protected member_ `TSharedRef<FChaosVDTrackInfo> ActiveTrack;`
- L556 _protected member_ `float CurrentPlaybackTime = 0.0f;`
- L559 _protected member_ `int32 LastAssignedTrackSlot = 0;` — Counter used to create Track Slot IDs. Game track is always Slot 0
- L561 _protected member_ `EChaosVDSyncTimelinesMode CurrentSyncMode = EChaosVDSyncTimelinesMode::RecordedTimestamp;`
- L563 _protected member_ `bool bStartLiveSessionPlaybackAutomatically = true;`
- L565 _protected member_ `bool bInitialized = false;`
- L569 _function_ `template <typename TVisitorCallback> void FChaosVDPlaybackController::VisitAvailableTracks(const TVisitorCallback& VisitorCallback)`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDInitialFirstFramePlayed, TWeakPtr<FChaosVDPlaybackController>) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDPlaybackControllerUpdated, TWeakPtr<FChaosVDPlaybackController>) DECLARE_MULTICAST_DELEGATE_ThreeParams(FChaosVDPlaybackControllerFrameUpdated, TWeakPtr<FChaosVDPlaybackController>, TWeakPtr<const FChaosVDTrackInfo>, FGuid);`
- L29 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDInitialFirstFramePlayed, TWeakPtr<FChaosVDPlaybackController>) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDPlaybackControllerUpdated, TWeakPtr<FChaosVDPlaybackController>) DECLARE_MULTICAST_DELEGATE_ThreeParams(FChaosVDPlaybackControllerFrameUpdated, TWeakPtr<FChaosVDPlaybackController>, TWeakPtr<const FChaosVDTrackInfo>, FGuid);`
- L30 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDPlaybackControllerUpdated, TWeakPtr<FChaosVDPlaybackController>) DECLARE_MULTICAST_DELEGATE_ThreeParams(FChaosVDPlaybackControllerFrameUpdated, TWeakPtr<FChaosVDPlaybackController>, TWeakPtr<const FChaosVDTrackInfo>, FGuid);`
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FChaosVDPlaybackControllerFrameUpdated, TWeakPtr<FChaosVDPlaybackController>, TWeakPtr<const FChaosVDTrackInfo>, FGuid);`
- L109 _typedef_ `typedef TMap<int32, TSharedPtr<FChaosVDTrackInfo>> TrackInfoByIDMap;`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDPlaybackViewportClient.h` (Public)


#### class `FChaosVDPlaybackViewportClient`  
`class FChaosVDPlaybackViewportClient : public FEditorViewportClient`  
_L16-89_
- inherits: `FEditorViewportClient`
- desc: Client viewport class used for to handle a Chaos Visual Debugger world Interaction/Rendering. It re-routes interaction events to our Chaos VD scene
- L20 _public prototype_ `FChaosVDPlaybackViewportClient(const TSharedPtr<FEditorModeTools>& InModeTools, const TSharedPtr<SEditorViewport>& InEditorViewportWidget);`
- L23 _public prototype_ `virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;`
- L25 _public prototype_ `void SetScene(TWeakPtr<FChaosVDScene> InScene);`
- L27 _public function_ `virtual UWorld* GetWorld() const override`
- L32 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L33 _public prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L35 _public prototype_ `void ToggleObjectTrackingIfSelected();`
- L37 _public function_ `bool IsAutoTrackingSelectedObject() const`
- L42 _public prototype_ `void SetAutoTrackingViewDistance(float NewDistance);`
- L44 _public function_ `float GetAutoTrackingViewDistance() const`
- L49 _public prototype_ `void GoToLocation(const FVector& InLocation);`
- L51 _public prototype_ `void UpdateObjectTracking();`
- L53 _public prototype_ `void FocusOnSelectedObject();`
- L55 _public prototype_ `FBox GetSelectionBounds() const;`
- L57 _public prototype_ `virtual void UpdateMouseDelta() override;`
- L59 _public prototype_ `void HandleCVDSceneUpdated();`
- L61 _public function_ `bool GetCanSelectTranslucentGeometry() const`
- L66 _public prototype_ `void SetCanSelectTranslucentGeometry(bool bCanSelect);`
- L67 _public prototype_ `void ToggleCanSelectTranslucentGeometry();`
- L71 _protected prototype_ `virtual bool Internal_InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L75 _private prototype_ `void ExecuteVisualizationCallback(const TSharedRef<SChaosVDMainTab>& InMainTabToolkitHostRef, const TSharedRef<FChaosVDScene>& SceneRef, const TFunction<void(const UActorComponent*, const TSharedRef<FComponentVisualizer>&)>& VisitorCallback);`
- L78 _private prototype_ `void HandleFocusRequest(FBox BoxToFocusOn);`
- L79 _private prototype_ `void HandleActorMoving(AActor* MovedActor) const;`
- L81 _private member_ `FDelegateHandle FocusRequestDelegateHandle;`
- L82 _private member_ `UWorld* CVDWorld;`
- L83 _private member_ `TWeakPtr<FChaosVDScene> CVDScene;`
- L85 _private member_ `bool bAutoTrackSelectedObject = false;`
- L86 _private member_ `float TrackingViewDistance = 120.0f;`
- L88 _private member_ `bool bAllowTranslucentHitProxies = true;`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDScene.h` (Public)


#### enum `EChaosVDSceneCleanUpOptions`  
`enum class EChaosVDSceneCleanUpOptions`  
_L65-70_
- reflection: `UENUM()`
- L67 _public enumerator_ `None = 0`
- L68 _public enumerator_ `ReInitializeGeometryBuilder = 1 << 0`
- L69 _public enumerator_ `CollectGarbage = 1 << 1`

#### class `FChaosVDScene`  
`class FChaosVDScene : public FGCObject , public TSharedFromThis<FChaosVDScene>, public FTSTickerObjectBase`  
_L75-375_
- inherits: `FGCObject,TSharedFromThis<FChaosVDScene>,FTSTickerObjectBase`
- desc: Recreates a UWorld from a recorded Chaos VD Frame
- L79 _public prototype_ `FChaosVDScene();`
- L82 _public prototype_ `void Initialize();`
- L83 _public prototype_ `void DeInitialize();`
- L85 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L86 _public function_ `virtual FString GetReferencerName() const override`
- L92 _public function_ `FChaosVDSceneUpdatedDelegate& OnSceneUpdated()` — Called each time this Scene is modified
- L99 _public function_ `FChaosVDParticleDetailsExtraDataDelegate& OnParticleDetailsExtraDataRequested()` — Fired when the particle details panel is being built for a selected particle. Subscribers can append additional categories/structs to the panel via IDetailLayoutBuilder.
- L106 _public function_ `FChaosVDParticleDetailsExtraDataRefreshDelegate& OnParticleDetailsExtraDataRefreshRequested()` — Fired on every frame change while a particle remains selected. Subscribers should update their cached struct scope memory in-place (no layout rebuild).
- L112 _public prototype_ `void UpdateFromRecordedSolverStageData(const int32 SolverID, const FChaosVDFrameStageData& InRecordedStepData, const FChaosVDSolverFrameData& InFrameData);` — Updates, Adds and Remove actors to match the provided Solver Stage Data
- L121 _public prototype_ `void HandleEnterNewGameFrame(int32 FrameNumber, const TArray<int32, TInlineAllocator<16>>& AvailableSolversIds, const FChaosVDGameFrameData& InNewGameFrameData, TArray<int32, TInlineAllocator<16>>& OutRemovedSolversIds);` — Handles the Playback switching to a new Game Thread Frame @param FrameNumber Number of the GT Frame @param AvailableSolversIds List of Solver IDs available for this GT Frame data @param InNewGameFrameData New Frame Data @param OutRemovedSolversIds Out List of Solver IDs that are no longer available in this GT frame
- L128 _public prototype_ `void HandleEnterNewSolverFrame(int32 FrameNumber, const FChaosVDSolverFrameData& InFrameData);` — Handles the playback switching to a new solver frame @param FrameNumber Number of the solver frame @param InFrameData New Solver frame data
- L135 _public prototype_ `void CleanUpScene(EChaosVDSceneCleanUpOptions Options = EChaosVDSceneCleanUpOptions::None);` — Deletes all actors of the Scene and underlying UWorld @param Options Flags controlling how the cleanup is performed
- L138 _public function_ `UWorld* GetUnderlyingWorld() const` — Returns a ptr to the UWorld used to represent the current recorded frame data
- L144 _public function_ `bool IsInitialized() const` — Returns true if the scene is initialized and ready to use
- L150 _public function_ `TWeakPtr<FChaosVDGeometryBuilder> GetGeometryGenerator()` — Returns a weak ptr to the geometry builder object handling geometry generation and caching for this scene
- L158 _public prototype_ `Chaos::FConstImplicitObjectPtr GetUpdatedGeometry(int32 GeometryID) const;` — Returns an instance to the loaded implicit object for the provided id @param GeometryID ID of the geometry
- L160 _public prototype_ `const Chaos::FImplicitObject* UnpackGeometry(const Chaos::FImplicitObject* InImplicitObject, Chaos::FRigidTransform3& InOutTransform) const;`
- L161 _public prototype_ `bool DoesGeometryNeedUnpacking(const Chaos::FImplicitObject* InImplicitObject) const;`
- L164 _public prototype_ `void SetSelectedObject(UObject* SelectedObject);` — Adds an object to the selection set if it was not selected already, making it selected in practice
- L165 _public prototype_ `void SetSelected(const FTypedElementHandle& InElementHandle);`
- L168 _public prototype_ `bool IsObjectSelected(const UObject* Object);` — Evaluates an object and returns true if it is selected
- L171 _public prototype_ `bool IsSelected(const FTypedElementHandle& InElementHandle) const;` — Evaluates an object and returns true if it is selected
- L174 _public function_ `UTypedElementSelectionSet* GetElementSelectionSet() const` — Returns a ptr to the current selection set object
- L179 _public function_ `USelection* GetActorSelectionObject() const`
- L184 _public function_ `USelection* GetComponentsSelectionObject() const`
- L189 _public function_ `USelection* GetObjectsSelectionObject() const`
- L195 _public function_ `FChaosVDFocusRequestDelegate& OnFocusRequest()` — Event triggered when an object is focused in the scene (double-click in the scene outliner)
- L204 _public prototype_ `TSharedPtr<FChaosVDSceneParticle> GetParticleInstance(int32 SolverID, int32 ParticleID);` — Returns a ptr to the particle actor representing the provided Particle ID @param SolverID ID of the solver owning the Particle @param ParticleID ID of the particle
- L207 _public function_ `const FChaosVDSolverInfoByIDMap& GetSolverInfoActorsMap()` — Returns a const reference for all Solver Data info actor currently available
- L215 _public prototype_ `AChaosVDSolverInfoActor* GetSolverInfoActor(int32 SolverID);` — Returns a ptr of a Solver info actor instance for the provided solver ID, if exists @param SolverID ID of the solver
- L218 _public function_ `FChaosVDSolverInfoActorCreatedDelegate& OnSolverInfoActorCreated()` — Event called when a solver info actor is created
- L224 _public function_ `FChaosVDSolverVisibilityChangedDelegate& OnSolverVisibilityUpdated()` — Event called when a solver visibility has changed
- L230 _public prototype_ `void UpdateSelectionProxiesForActors(TArrayView<AActor*> SelectedActors);` — Updates the render state of the hit proxies of an array of actors. This used to update the selection outline state
- L233 _public function_ `TWeakPtr<FChaosVDSolverDataSelection> GetSolverDataSelectionObject()` — Returns the generic selection data manager object for this scene
- L239 _public function_ `TConstArrayView<TObjectPtr<AChaosVDDataContainerBaseActor>> GetDataContainerActorsView() const` — Returns an array view with all available Data info actors
- L244 _public function_ `TSharedPtr<FChaosVDRecording> GetLoadedRecording() const`
- L250 _public prototype_ `TArray<FTypedElementHandle> GetSelectedElementHandles();` — Returns the currently selected elements in the scene, which can then be further inspected with GetStructDataFromTypedElementHandle
- L252 _public prototype_ `FName GetTEDSSelectionSetName();`
- L254 _public prototype_ `void ClearSelectionAndNotify();`
- L256 _public prototype_ `void RequestUpdate();`
- L258 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L260 _public prototype_ `void UpdateWorldStreamingLocation(const FVector& InLocation);`
- L262 _public function_ `const FVector& GetWorldStreamingLocation() const`
- L273 _public prototype_ `void AppendSceneCompositionTestData(FChaosVDPlaybackEngineSnapshot& OutStateTestData);` — Appends Scene Data relevant for functional tests @param OutStateTestData Structure instance where to add the data @note If you change the data being added here, you need to re-generate the snapshots used by the scene integrity playback tests in the Simulation Tests Plugin
- L277 _private member_ `FVector WorldStreamingLocation = FVector::ZeroVector;`
- L279 _private prototype_ `void AddFromCVDWorldTagToActor(AActor* Actor);`
- L281 _private member_ `FName TEDSSelectionSetName;`
- L283 _private prototype_ `void SetLoadedRecording(const TSharedPtr<FChaosVDRecording>& NewRecordingInstance);`
- L285 _private member_ `TSharedPtr<FChaosVDRecording> LoadedRecording;`
- L287 _private prototype_ `AActor* GetMeshComponentsContainerActor() const;`
- L289 _private function_ `AActor* GetSkySphereActor() const`
- L294 _private prototype_ `void PerformGarbageCollection();`
- L296 _private prototype_ `void CreateBaseLights(UWorld* TargetWorld);`
- L298 _private prototype_ `void CreatePostProcessingVolumes(UWorld* TargetWorld);`
- L301 _private prototype_ `AChaosVDSolverInfoActor* GetOrCreateSolverInfoActor(int32 SolverID);` — Creates an actor that will contain all solver data for the provided Solver ID
- L304 _private prototype_ `AChaosVDGameFrameInfoActor* GetOrCreateGameFrameInfoActor();` — Creates an actor that will contain all non-solver data for recorded from any thread
- L306 _private prototype_ `AActor* CreateMeshComponentsContainer(UWorld* TargetWorld);`
- L309 _private prototype_ `UWorld* CreatePhysicsVDWorld();` — Creates the instance of the World which will be used the recorded data
- L312 _private member_ `FChaosVDSolverInfoByIDMap SolverDataContainerBySolverID;` — Map of SolverID-ChaosVDSolverInfo Actor. Used to keep track of active solvers representations and be able to modify them as needed
- L315 _private prototype_ `FTypedElementHandle GetSelectionHandleForObject(const UObject* Object) const;` — Returns the correct TypedElementHandle based on an object type so it can be used with the selection set object
- L317 _private prototype_ `void HandleDeSelectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);`
- L318 _private prototype_ `void HandleSelectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);`
- L320 _private prototype_ `void InitializeSelectionSets();`
- L321 _private prototype_ `void DeInitializeSelectionSets();`
- L323 _private prototype_ `void HandleActorDestroyed(AActor* ActorDestroyed);`
- L326 _private member_ `TObjectPtr<UWorld> PhysicsVDWorld = nullptr;` — UWorld instance used to represent the recorded debug data
- L328 _private member_ `FChaosVDSceneUpdatedDelegate SceneUpdatedDelegate;`
- L329 _private member_ `FChaosVDParticleDetailsExtraDataDelegate ParticleDetailsExtraDataDelegate;`
- L330 _private member_ `FChaosVDParticleDetailsExtraDataRefreshDelegate ParticleDetailsExtraDataRefreshDelegate;`
- L332 _private member_ `TSharedPtr<FChaosVDGeometryBuilder> GeometryGenerator;`
- L334 _private member_ `FChaosVDGeometryDataLoaded NewGeometryAvailableDelegate;`
- L336 _private member_ `FChaosVDFocusRequestDelegate FocusRequestDelegate;`
- L339 _private member_ `TObjectPtr<UTypedElementSelectionSet> SelectionSet;` — Selection set object holding the current selection state
- L341 _private member_ `TObjectPtr<USelection> ActorSelection = nullptr;`
- L342 _private member_ `TObjectPtr<USelection> ComponentSelection = nullptr;`
- L343 _private member_ `TObjectPtr<USelection> ObjectSelection = nullptr;`
- L346 _private member_ `TArray<AActor*> PendingActorsToUpdateSelectionProxy;` — Array of actors with hit proxies that need to be updated
- L349 _private member_ `TSharedPtr<struct FStreamableManager> StreamableManager;` — Scene Streamable manager that we'll use to async load any assets we depend on
- L351 _private member_ `mutable AActor* SkySphere = nullptr;`
- L353 _private member_ `AChaosVDGeometryContainer* MeshComponentContainerActor = nullptr;`
- L355 _private member_ `AChaosVDGameFrameInfoActor* GameFrameDataInfoActor = nullptr;`
- L357 _private member_ `bool bIsInitialized = false;`
- L359 _private member_ `FDelegateHandle ActorDestroyedHandle;`
- L361 _private member_ `FChaosVDSolverInfoActorCreatedDelegate SolverInfoActorCreatedDelegate;`
- L363 _private member_ `FChaosVDSolverVisibilityChangedDelegate SolverVisibilityChangedDelegate;`
- L365 _private member_ `TSharedPtr<FChaosVDSolverDataSelection> SolverDataSelectionObject;`
- L367 _private member_ `TArray<TObjectPtr<AChaosVDDataContainerBaseActor>> AvailableDataContainerActors;`
- L369 _private member_ `bool bPendingUpdateRequest = false;`

#### Free symbols / members of external scopes

- L43 _typedef_ `typedef TMap<int32, AChaosVDSolverInfoActor*> FChaosVDSolverInfoByIDMap;`
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE(FChaosVDSceneUpdatedDelegate) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDOnObjectSelectedDelegate, UObject*) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDFocusRequestDelegate, FBox) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDSolverInfoActorCreatedDelegate, AChaosVDSolverInfoActor*) DECLARE_MULTICAST_DELEGATE_TwoParams(FChaosVDSolverVisibilityChangedDelegate, int32 SolverID, bool bNewVisibility) class IDetailLayoutBuilder;`
- L46 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDOnObjectSelectedDelegate, UObject*) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDFocusRequestDelegate, FBox) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDSolverInfoActorCreatedDelegate, AChaosVDSolverInfoActor*) DECLARE_MULTICAST_DELEGATE_TwoParams(FChaosVDSolverVisibilityChangedDelegate, int32 SolverID, bool bNewVisibility) class IDetailLayoutBuilder;`
- L47 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDFocusRequestDelegate, FBox) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDSolverInfoActorCreatedDelegate, AChaosVDSolverInfoActor*) DECLARE_MULTICAST_DELEGATE_TwoParams(FChaosVDSolverVisibilityChangedDelegate, int32 SolverID, bool bNewVisibility) class IDetailLayoutBuilder;`
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDSolverInfoActorCreatedDelegate, AChaosVDSolverInfoActor*) DECLARE_MULTICAST_DELEGATE_TwoParams(FChaosVDSolverVisibilityChangedDelegate, int32 SolverID, bool bNewVisibility) class IDetailLayoutBuilder;`
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FChaosVDSolverVisibilityChangedDelegate, int32 SolverID, bool bNewVisibility) class IDetailLayoutBuilder;`
- L57 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FChaosVDParticleDetailsExtraDataDelegate, int32 , int32 , IDetailLayoutBuilder& ) /** Lightweight delegate broadcast on every frame change for an already-selected particle. * Subscribers update their cached struct scope memory in-place;` — Fired by FChaosVDSceneParticleCustomization when building details for a selected particle. Subscribers (e.g. UChaosVDParticleExtraDataComponent) can append additional categories and struct entries to the details panel via the provided IDetailLayoutBuilder.
- L62 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FChaosVDParticleDetailsExtraDataRefreshDelegate, int32 , int32 , bool& ) UENUM() enum class EChaosVDSceneCleanUpOptions { None = 0, ReInitializeGeometryBuilder = 1 << 0, CollectGarbage = 1 << 1 };` — Lightweight delegate broadcast on every frame change for an already-selected particle. Subscribers update their cached struct scope memory in-place; they set bOutNeedsFullRebuild=true if the data layout has changed and a full IDetailLayoutBuilder refresh is required.

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDSceneCompositionReport.h` (Public)


#### struct `FChaosVDFrameIndexTestData`  
`struct FChaosVDFrameIndexTestData`  
_L15-24_
- reflection: `USTRUCT()`
- L20 _public member_ `int32 FrameNumber = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category=SceneComposition)`
- L23 _public member_ `int32 StageNumber = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category=SceneComposition)`

#### struct `FChaosVDSceneCompositionTestData`  
`struct FChaosVDSceneCompositionTestData`  
_L31-37_
- reflection: `USTRUCT()`
- desc: Structure containing data about how a CVD scene is composed. This is used for functional testing, to verify if a loaded file at a specific frame keeps the expected composition
- L36 _public member_ `TMap<FName, int32> ObjectsCountByType;` — `UPROPERTY(VisibleAnywhere, Category=SceneComposition)`

#### struct `FChaosVDPlaybackEngineSnapshot`  
`struct FChaosVDPlaybackEngineSnapshot`  
_L47-62_
- reflection: `USTRUCT()`
- desc: Structure containing data about the playback engine state at the time when this struct is created. This is used for functional testing, to verify if a loaded file at a specific frame keeps the expected composition @note If you change the composition of this structure or of the structures used by it, you need to re-generate the snapshots used by the scene integrity playback tests in the Simulation Tests Plugin
- L52 _public member_ `TArray<FName> InstalledExtensionsNames;` — `UPROPERTY(VisibleAnywhere, Category=SceneComposition)`
- L55 _public member_ `TMap<int32, FChaosVDFrameIndexTestData> FrameIndexDataByTrackID;` — `UPROPERTY(VisibleAnywhere, Category=SceneComposition)`
- L58 _public member_ `EChaosVDSyncTimelinesMode TimelineSyncMode = EChaosVDSyncTimelinesMode::RecordedTimestamp;` — `UPROPERTY(VisibleAnywhere, Category=SceneComposition)`
- L61 _public member_ `FChaosVDSceneCompositionTestData SceneComposition;` — `UPROPERTY(VisibleAnywhere, Category=SceneComposition)`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDSceneParticle.h` (Public)


#### enum `EChaosVDParticleVisibilityUpdateFlags`  
`enum class EChaosVDParticleVisibilityUpdateFlags`  
_L22-26_
- reflection: `UENUM()`
- L24 _public enumerator_ `None = 0`
- L25 _public enumerator_ `DirtyScene = 1 << 0`

#### struct `FChaosVDSceneParticle`  
`struct FChaosVDSceneParticle : public FChaosVDBaseSceneObject`  
_L30-225_
- reflection: `USTRUCT()`
- inherits: `FChaosVDBaseSceneObject`
- L38 _public prototype_ `FChaosVDSceneParticle();`
- L40 _public prototype_ `void PreUpdateFromRecordedParticleData(const TSharedPtr<FChaosVDParticleDataWrapper>& InRecordedData, const Chaos::FRigidTransform3& SimulationTransform);`
- L41 _public prototype_ `void ProcessPendingParticleDataUpdates();`
- L43 _public function_ `TSharedPtr<const FChaosVDParticleDataWrapper> GetParticleData() const`
- L48 _public prototype_ `virtual void SetParent(const TSharedPtr<FChaosVDBaseSceneObject>& NewParent) override;`
- L50 _public prototype_ `void UpdateGeometryComponentsVisibility(EChaosVDParticleVisibilityUpdateFlags Flags = EChaosVDParticleVisibilityUpdateFlags::None);`
- L52 _public prototype_ `void UpdateGeometryColors();`
- L55 _public prototype_ `void SetIsActive(bool bNewActive);` — Changes the active state of this CVD Particle Actor
- L57 _public prototype_ `void AddHiddenFlag(EChaosVDHideParticleFlags Flag);`
- L59 _public prototype_ `void RemoveHiddenFlag(EChaosVDHideParticleFlags Flag);`
- L66 _public prototype_ `void HideImmediate(EChaosVDHideParticleFlags Flag);` — Performs all the required steps to hide a particle and update the viewport / scene outliner. @param Flag Context flags about what is hiding this particle @note Don't use when performing operation on multiple particles or other performance sensitive operations. See UChaosVDParticleDataComponent for examples of batch visibility update operations
- L72 _public prototype_ `void ShowImmediate();` — Performs all the required steps to show a particle and update the viewport / scene outliner. @note Don't use when performing operation on multiple particles or other performance sensitive operations. See UChaosVDParticleDataComponent for examples of batch visibility update operations
- L74 _public function_ `EChaosVDHideParticleFlags GetHideFlags() const`
- L79 _public function_ `bool IsVisible() const`
- L87 _public function_ `bool IsActive() const` — Returns true if this particle actor is active - Inactive Particle actors are still in the world but with outdated data and hidden from the viewport and outliner. They represent particles that were destroyed.
- L92 _public prototype_ `FBox GetBoundingBox() const;`
- L93 _public prototype_ `FBox GetInflatedBoundingBox() const;`
- L94 _public prototype_ `Chaos::TAABB<double, 3> GetChaosBoundingBox() const;`
- L96 _public prototype_ `TConstArrayView<TSharedPtr<FChaosVDParticlePairMidPhase>> GetCollisionData();`
- L97 _public prototype_ `bool HasCollisionData();`
- L100 _public prototype_ `void GetCharacterGroundConstraintData(TArray<TSharedPtr<FChaosVDCharacterGroundConstraint>>& OutConstraintsFound);` — BEGIN IChaosVDCharacterGroundConstraintDataProviderInterface
- L101 _public prototype_ `bool HasCharacterGroundConstraintData();`
- L104 _public function_ `void SetIsServerParticle(bool bNewIsServer)`
- L109 _public function_ `bool GetIsServerParticle() const`
- L114 _public prototype_ `void UpdateMeshInstancesSelectionState();`
- L117 _public function_ `TConstArrayView<TSharedRef<FChaosVDInstancedMeshData>> GetMeshInstances() const` — BEGIN IChaosVDGeometryOwner Interface
- L122 _public prototype_ `virtual void SetSelectedMeshInstance(const TWeakPtr<FChaosVDInstancedMeshData>& GeometryInstanceToSelect);`
- L124 _public function_ `virtual TWeakPtr<FChaosVDInstancedMeshData> GetSelectedMeshInstance() const`
- L131 _public prototype_ `void HandleDeSelected();`
- L132 _public prototype_ `void HandleSelected();`
- L134 _public prototype_ `bool IsSelected();`
- L136 _public function_ `void SetScene(const TWeakPtr<FChaosVDScene>& NewScene)`
- L141 _public function_ `TWeakPtr<FChaosVDScene> GetScene() const`
- L146 _public function_ `TWeakPtr<FChaosVDSceneParticle> GetParentParticle()`
- L151 _public function_ `TWeakPtr<Chaos::VD::FChaosVDImplicitObjectView> GetRootImplicitView() const`
- L156 _public function_ `EChaosVDSceneParticleDirtyFlags GetDirtyFlags() const`
- L161 _public prototype_ `void RemoveAllGeometry();`
- L163 _public prototype_ `virtual FBox GetStreamingBounds() const override;`
- L165 _public prototype_ `virtual void SyncStreamingState() override;`
- L167 _public prototype_ `virtual int32 GetStreamingID() const override;`
- L171 _protected prototype_ `void UpdateGeometry(const Chaos::FConstImplicitObjectPtr& InImplicitObject, EChaosVDActorGeometryUpdateFlags OptionsFlags = EChaosVDActorGeometryUpdateFlags::None);`
- L173 _protected prototype_ `void CalculateAndCacheBounds() const;`
- L175 _protected prototype_ `void UpdateParent(const TSharedPtr<FChaosVDParticleDataWrapper>& InRecordedData);`
- L177 _protected prototype_ `void ProcessUpdatedAndRemovedHandles(TArray<TPair<TSharedPtr<FChaosVDExtractedGeometryDataHandle>, TSharedPtr<Chaos::VD::FChaosVDImplicitObjectView>>>& OutExtractedGeometryDataHandles);`
- L179 _protected prototype_ `const TArray<TSharedPtr<FChaosVDParticlePairMidPhase>>* GetCollisionMidPhasesArray() const;`
- L181 _protected prototype_ `const TArray<TSharedPtr<FChaosVDConstraintDataWrapperBase>>* GetCharacterGroundConstraintArray() const;`
- L183 _protected prototype_ `void UpdateShapeDataComponents();`
- L185 _protected prototype_ `void ApplyPendingTransformData();`
- L188 _protected prototype_ `template<typename TTaskCallback> void VisitGeometryInstances(const TTaskCallback& VisitorCallback);`
- L190 _protected member_ `uint8 bIsGeometryDataGenerationStarted : 1 = false;`
- L191 _protected member_ `uint8 bIsActive: 1 = false;`
- L192 _protected member_ `uint8 bIsServer: 1 = false;`
- L193 _protected member_ `EChaosVDHideParticleFlags HideParticleFlags = EChaosVDHideParticleFlags::None;`
- L194 _protected member_ `EChaosVDSceneParticleDirtyFlags DirtyFlags = EChaosVDSceneParticleDirtyFlags::None;`
- L196 _protected member_ `Chaos::FConstImplicitObjectPtr CurrentRootGeometry = nullptr;`
- L198 _protected member_ `TWeakPtr<FChaosVDSceneParticle> ParentParticleInstance;`
- L200 _protected member_ `TSharedPtr<FChaosVDParticleDataWrapper> ParticleDataPtr;`
- L202 _protected member_ `FDelegateHandle GeometryUpdatedDelegate;`
- L204 _protected member_ `TArray<TSharedRef<FChaosVDInstancedMeshData>> MeshDataHandles;`
- L206 _protected member_ `TWeakPtr<FChaosVDInstancedMeshData> CurrentSelectedGeometryInstance;`
- L208 _protected member_ `TSharedPtr<Chaos::VD::FChaosVDImplicitObjectView> RootImplicitView;`
- L211 _protected member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;`
- L213 _protected member_ `FTransform PendingParticleTransform;`
- L214 _protected member_ `FTransform CachedSimulationTransform;`
- L216 _protected member_ `mutable FBox CachedBounds = FBox(ForceInitToZero);`
- L221 _protected member_ `FSimpleDelegate ParticleDestroyedDelegate;` — Called when this particle is destroyed. This is intentionally private and only intended to be used by the customization class for this object
- L228 _function_ `template <typename TVisitorCallback> void FChaosVDSceneParticle::VisitGeometryInstances(const TVisitorCallback& VisitorCallback)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDSceneParticleFlags.h` (Public)


#### enum `EChaosVDActorGeometryUpdateFlags`  
`enum class EChaosVDActorGeometryUpdateFlags : uint8`  
_L12-16_
- reflection: `UENUM()`
- desc: Options flags to control how geometry is updated in a ChaosVDActor
- L14 _public enumerator_ `None = 0`
- L15 _public enumerator_ `ForceUpdate = 1 << 0`

#### enum `EChaosVDHideParticleFlags`  
`enum class EChaosVDHideParticleFlags : uint8`  
_L20-27_
- reflection: `UENUM()`
- L22 _public enumerator_ `None = 0`
- L23 _public enumerator_ `HiddenByVisualizationFlags = 1 << 0`
- L24 _public enumerator_ `HiddenBySceneOutliner = 1 << 1`
- L25 _public enumerator_ `HiddenByActiveState = 1 << 2`
- L26 _public enumerator_ `HiddenBySolverVisibility = 1 << 3`

#### enum `EChaosVDSceneParticleDirtyFlags`  
`enum class EChaosVDSceneParticleDirtyFlags : uint16`  
_L32-45_
- reflection: `UENUM()`
- desc: Set of flags used to indicate which data was modified and needs to be evaluated again by other systems
- L34 _public enumerator_ `None = 0`
- L35 _public enumerator_ `Visibility = 1 << 0`
- L36 _public enumerator_ `Coloring = 1 << 1`
- L37 _public enumerator_ `Active = 1 << 2`
- L38 _public enumerator_ `Transform = 1 << 3`
- L39 _public enumerator_ `Parent = 1 << 4`
- L40 _public enumerator_ `Geometry = 1 << 5`
- L41 _public enumerator_ `CollisionData = 1 << 6`
- L42 _public enumerator_ `PreUpdatePass = 1 << 7`
- L43 _public enumerator_ `TEDS = 1 << 8`
- L44 _public enumerator_ `StreamingBounds = 1 << 9`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDSceneSelectionObserver.h` (Public)


#### class `FChaosVDSceneSelectionObserver`  
`class FChaosVDSceneSelectionObserver`  
_L13-39_
- desc: Base class that provided access to selection events from the Chaos visual debugger local selection system.
- L17 _public prototype_ `FChaosVDSceneSelectionObserver();`
- L18 _public prototype_ `virtual ~FChaosVDSceneSelectionObserver();`
- L23 _protected prototype_ `void RegisterSelectionSetObject(UTypedElementSelectionSet* SelectionSetObject);` — Stores a weak ptr to the selection set object containing the current selection state
- L25 _protected function_ `const UTypedElementSelectionSet* GetSelectionSetObject() const`
- L30 _protected function_ `virtual void HandlePreSelectionChange(const UTypedElementSelectionSet* SelectionSetPreChange)` — Called when the current selection might change @param SelectionSetPreChange the pointer to the selection set object that might be about to change
- L35 _protected function_ `virtual void HandlePostSelectionChange(const UTypedElementSelectionSet* ChangesSelectionSet)` — Called when the current selection has changed @param ChangesSelectionSet the pointer to the selection set object that has changed
- L38 _protected member_ `TWeakObjectPtr<UTypedElementSelectionSet> ObservedSelection;` — Weak Ptr to the selection set object we are observing

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDSceneStreaming.h` (Public)


#### enum `EChaosVDStreamingDirtyFlags`  
`enum class EChaosVDStreamingDirtyFlags : uint32`  
_L22-29_
- reflection: `UENUM()`
- L24 _public enumerator_ `None = 0`
- L25 _public enumerator_ `StreamingExtents = 1 << 0`
- L26 _public enumerator_ `StreamingEnabled = 1 << 1`
- L27 _public enumerator_ `StreamingSourceLocation = 1 << 2`
- L28 _public enumerator_ `AccelerationStructure = 1 << 3`

#### class `IChaosVDStreamingDataSource`  
`class IChaosVDStreamingDataSource`  
_L32-39_
- L35 _public prototype_ `virtual ~IChaosVDStreamingDataSource() = default;`
- L37 _public prototype_ `virtual TConstArrayView<TSharedRef<FChaosVDBaseSceneObject>> GetStreamableSceneObjects() const = 0;`
- L38 _public prototype_ `virtual FRWLock& GetObjectsLock() const = 0;`

#### class `FChaosVDSceneStreaming`  
`class FChaosVDSceneStreaming : public FTSTickerObjectBase`  
_L45-252_
- inherits: `FTSTickerObjectBase`
- desc: Simple pseudo level streaming system that works with a collection of ChaosVDSceneObjects - This system only updates a desired streaming state (from multiple threads) and issues a sync request in the GT. How these actions are executed depends on the implementations of each ChaosVDSceneObjects derived object
- L51 _public prototype_ `FChaosVDSceneStreaming();`
- L69 _public prototype_ `void Initialize();`
- L70 _public prototype_ `void DeInitialize();`
- L72 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L75 _public prototype_ `void EnqueuePendingTrackingOperation(const FPendingTrackingOperation&& Operation);` — Adds an object tracking operation to the queue
- L82 _public prototype_ `void EnqueuePendingTrackingOperation(const TSharedRef<FChaosVDBaseSceneObject>& InSceneObject, FPendingTrackingOperation::EType Type);` — Creates the request object tracking operation for the provided object and adds it to the queue @param InSceneObject Object from which create the operation from @param Type Type of operation to perform (AddOrUpdate, Remove)
- L88 _public prototype_ `void UpdateStreamingSourceLocation(const FVector& NewLocation);` — Updates the current location used to calculate what objects should be fully loaded or not @param NewLocation New streaming source location
- L94 _public prototype_ `bool IsInStreamingRange(const FBox& Bounds) const;` — Returns true if the provided bounds are within the current calculated streaming volume @param Bounds Bounds to evaluate
- L100 _public prototype_ `void UpdateStreamingStateForObject(const TSharedRef<FChaosVDBaseSceneObject>& InSceneObject) const;` — Sets the correct streaming state for the provided object based on its bounds @param InSceneObject Object to evaluate
- L107 _public prototype_ `FPendingTrackingOperation CreateStreamingTrackingOperation(const TSharedRef<FChaosVDBaseSceneObject>& InSceneObject, FPendingTrackingOperation::EType Type);` — Creates an object tracking operation structure with the necessary data to update the streaming system state for this object @param InSceneObject Object from which get the necessary data @param Type Operation type (AddOrUpdate, Remove)
- L112 _public prototype_ `void Reset();` — Resets the streaming system state
- L118 _public prototype_ `void SetStreamingDataSource(IChaosVDStreamingDataSource* InStreamingDataSource);` — Sets a ptr to an array with all the objects managed by this streaming system @param InStreamingDataSource Object that provides access to the data this system will manage
- L123 _public prototype_ `void SetStreamingEnabled(bool bNewEnabled);` — Changes the enabled state of this streaming system, and updates the world acordingly @param bNewEnabled New enabled state
- L129 _public function_ `void SetScene(const TWeakPtr<FChaosVDScene>& InSceneWeakPtr)` — Sets a weak ptr to the CVD scene where all the objects managed by this system live @param InSceneWeakPtr
- L138 _public prototype_ `void HandleSettingsChanged(UObject* SettingsObject);` — Handles any streaming settings changes done by the user and updates the world accordingly @param SettingsObject Object containing the new settings data
- L142 _public function_ `bool IsEnabled() const` — Returns true if this system is enabled
- L149 _protected prototype_ `void SetDirtyFlags(EChaosVDStreamingDirtyFlags Flag);`
- L150 _protected prototype_ `void RemoveDirtyFlag(EChaosVDStreamingDirtyFlags Flag);`
- L152 _protected prototype_ `void ProcessPendingOperations();`
- L154 _protected prototype_ `void UpdateStreamingState();`
- L156 _protected prototype_ `void SetStreamingExtent(float NewExtent);`
- L158 _protected prototype_ `void UpdateStreamingQueryShape();`
- L160 _protected prototype_ `void ReBuildAccelStructureFromSourceDataArray();`
- L162 _protected prototype_ `void MakeEverythingVisible();`
- L164 _protected member_ `float StreamingExtent = 5000.0f;`
- L166 _protected member_ `float MovementThreshold = 10.0f;`
- L168 _protected member_ `FVector CurrentStreamingSourceLocation = FVector::ZeroVector;`
- L170 _protected member_ `TOptional<FVector> LastStreamingLocationUpdate;`
- L172 _protected member_ `FBox SteamingViewBox;`
- L174 _protected member_ `Chaos::TAABBTree<int32, Chaos::TAABBTreeLeafArray<int32>> StreamingAccelerationStructure;`
- L176 _protected member_ `IChaosVDStreamingDataSource* StreamingDataSource = nullptr;`
- L178 _protected member_ `TQueue<FPendingTrackingOperation, EQueueMode::Mpsc> PendingOperationsPerParticle;`
- L180 _protected member_ `EChaosVDStreamingDirtyFlags DirtyFlags;`
- L182 _protected member_ `bool bIsStreamingSystemEnabled = true;`
- L184 _protected member_ `bool bProcessPendingOperationsQueueInWorkerThread = true;`
- L186 _protected member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;`
- L188 _protected member_ `UE::Tasks::FTask CurrentProcessingTaskHandle;`
- L190 _protected member_ `mutable FRWLock StreamingAccelerationOperationsLock;`
- L192 _protected member_ `mutable FRWLock DirtyFlagsLock;`

#### class `FChaosVDSceneStreaming::TMemStackSetAllocator`  
`template<uint32 Alignment = DEFAULT_ALIGNMENT> class TMemStackSetAllocator : public TSetAllocator<TSparseArrayAllocator<TMemStackAllocator<Alignment>, TMemStackAllocator<Alignment>>, TMemStackAllocator<Alignment>>`  
_L49-49_
- inherits: `TSetAllocator<TSparseArrayAllocator<TMemStackAllocator<Alignment>,TMemStackAllocator<Alignment>>,TMemStackAllocator<Alignment>>`

#### struct `FChaosVDSceneStreaming::FPendingTrackingOperation`  
`struct FPendingTrackingOperation`  
_L55-67_
- desc: Relevant streaming system data that needs processing
- L64 _public member_ `FBox Bounds = FBox(EForceInit::ForceInitToZero);`
- L65 _public member_ `int32 ObjectID = INDEX_NONE;`
- L66 _public member_ `EType OperationType = EType::None;`

#### enum `FChaosVDSceneStreaming::FPendingTrackingOperation::EType`  
`enum class EType`  
_L57-62_
- L59 _public enumerator_ `None`
- L60 _public enumerator_ `AddOrUpdate`
- L61 _public enumerator_ `Remove`

#### struct `FChaosVDSceneStreaming::FQueryVisitor`  
`struct FQueryVisitor`  
_L194-251_
- L196 _public function_ `FQueryVisitor(TSet<int32>& InResults) : CollectedResults(InResults)`
- L201 _public function_ `bool VisitOverlap(const Chaos::TSpatialVisitorData<int32>& Instance)`
- L206 _public function_ `bool VisitSweep(const Chaos::TSpatialVisitorData<int32>& Instance, Chaos::FQueryFastData& CurData)`
- L211 _public function_ `bool VisitRaycast(const Chaos::TSpatialVisitorData<int32>& Instance, Chaos::FQueryFastData& CurData)`
- L218 _public function_ `const void* GetQueryData() const` — `UE_DEPRECATED(5.8, "This was unused and is being removed")`
- L224 _public function_ `const void* GetSimData() const` — `UE_DEPRECATED(5.8, "This was unused and is being removed")`
- L229 _public function_ `const void* GetQueryPayload() const`
- L234 _public function_ `bool HasBlockingHit() const`
- L240 _public function_ `bool ShouldIgnore(const Chaos::TSpatialVisitorData<int32>& Instance) const` — `UE_DEPRECATED(5.8, "This was unused and is being removed")`
- L245 _public function_ `const bool PrePreFilter(int) const`
- L250 _public member_ `TSet<int32>& CollectedResults;`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDSettingsManager.h` (Public)


#### class `FChaosVDSettingsManager`  
`class FChaosVDSettingsManager : public FGCObject`  
_L10-43_
- inherits: `FGCObject`
- desc: Manager class that handles all available CVD settings objects
- L13 _public prototype_ `FChaosVDSettingsManager();`
- L15 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L16 _public prototype_ `virtual FString GetReferencerName() const override;`
- L18 _public prototype_ `static FChaosVDSettingsManager& Get();`
- L20 _public prototype_ `static FChaosVDSettingsManager* TryGet();` — Returns nullptr if the singleton has not been created yet or has already been torn down.
- L21 _public prototype_ `static void TearDown();`
- L25 _public prototype_ `template<typename SettingsClass> SettingsClass* GetSettingsObject();` — Returns the setting object of the specified class - If the object does not exist yet, it will be created during this call
- L28 _public prototype_ `UChaosVDSettingsObjectBase* GetSettingsObject(UClass* SettingsClass);` — Returns the setting object of the specified class - If the object does not exist yet, it will be created during this call
- L32 _public prototype_ `template<typename SettingsClass> void ResetSettings();` — Deletes any saved config for the setting object of the specified class, and restores its values to be the same as the CDO
- L35 _public prototype_ `void ResetSettings(UClass* SettingsClass);` — Deletes any saved config for the setting object of the specified class, and restores its values to be the same as the CDO
- L39 _protected prototype_ `void RestoreConfigPropertiesValuesFromCDO(UChaosVDSettingsObjectBase* TargetSettingsObject);`
- L41 _protected member_ `TMap<TObjectPtr<UClass>, TObjectPtr<UChaosVDSettingsObjectBase>> AvailableSettingsObject;`
- L42 _protected member_ `TObjectPtr<UChaosVDSettingsObjectsOuter> SettingsOuter;`
- L46 _function_ `template <typename SettingsClass> SettingsClass* FChaosVDSettingsManager::GetSettingsObject()`
- L52 _function_ `template <typename SettingsClass> void FChaosVDSettingsManager::ResetSettings()`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDSolverDataSelection.h` (Public)


#### struct `FChaosVDSelectionContext`  
`struct FChaosVDSelectionContext`  
_L12-15_
- reflection: `USTRUCT()`
- desc: Base struct type used for any context data we want to add for a selection handle

#### struct `FChaosVDSelectionMultipleView`  
`struct FChaosVDSelectionMultipleView`  
_L23-50_
- reflection: `USTRUCT()`
- desc: Struct used to create a combined view of multiple structs to be used in a vanilla details panel. This struct type has a customization that will show each data entry as an individual property. Entries may optionally carry a group name; entries sharing the same name are displayed under a single collapsible category with that name. Entries with no group go into "Recorded Data".
- L34 _public prototype_ `template<typename StructType> void AddData(StructType* Struct, FName GroupName = NAME_None);`
- L36 _public function_ `void AddData(TSharedPtr<FStructOnScope> StructOnScope, FName GroupName = NAME_None)`
- L41 _public function_ `void Clear()`
- L47 _protected member_ `TArray<FDataEntry> DataInstances;`
- L53 _function_ `template <typename StructType> void FChaosVDSelectionMultipleView::AddData(StructType* Struct, FName GroupName)`

#### struct `FChaosVDSelectionMultipleView::FDataEntry`  
`struct FDataEntry`  
_L27-31_
- L29 _public member_ `TSharedPtr<FStructOnScope> StructOnScope;`
- L30 _public member_ `FName GroupName = NAME_None;`

#### struct `FChaosVDSolverDataSelectionHandle`  
`struct FChaosVDSolverDataSelectionHandle : public TSharedFromThis<FChaosVDSolverDataSelectionHandle>`  
_L66-140_
- inherits: `TSharedFromThis<FChaosVDSolverDataSelectionHandle>`
- desc: Selection handle that holds a reference to the selected solver data
- L68 _public prototype_ `virtual ~FChaosVDSolverDataSelectionHandle() = default;`
- L72 _public prototype_ `template<typename DataStructType> void SetHandleData(const TSharedPtr<DataStructType>& Data);` — Set the data this handle points to
- L76 _public prototype_ `template<typename ContextDataStructType> void SetHandleContext(ContextDataStructType&& ContextData);` — Set the data that acts as context for this handle
- L79 _public prototype_ `void SetOwner(const TSharedPtr<FChaosVDSolverDataSelection>& InOwner);` — Sets the selection system instance that owns this handle
- L82 _public prototype_ `virtual bool IsSelected();` — Returns tru if the data from this selection handle is currently selected
- L85 _public prototype_ `bool IsValid() const;` — Return true if this handle is valid
- L89 _public prototype_ `template<typename DataStructType> bool IsA() const;` — Returns true if the data referenced by this handle is from the specified type
- L93 _public prototype_ `template<typename DataStructType> DataStructType* GetData() const;` — Returns a raw ptr to the data this handled references
- L97 _public prototype_ `template<typename DataStructType> TSharedPtr<DataStructType> GetDataAsShared() const;` — Returns a shared ptr to the data this handled references
- L101 _public prototype_ `template<typename ContextDataStructType> ContextDataStructType* GetContextData() const;` — Returns a raw ptr to the context data this handled references
- L104 _public function_ `TSharedPtr<FStructOnScope> GetDataAsStructScope()` — Returns the referenced data as FStructOnScope, so it can be feeded directly to a struct details panel
- L112 _public function_ `virtual TSharedPtr<FStructOnScope> GetCustomDataReadOnlyStructViewForDetails()` — Returns a struct on Scope view that can be fed into a CVD details panel - Usually used to combine data and context into a single read only struct that can be inspected
- L117 _public function_ `bool operator==(const FChaosVDSolverDataSelectionHandle& Other) const`
- L122 _public function_ `bool operator!=(const FChaosVDSolverDataSelectionHandle& Other) const`
- L130 _private prototype_ `template<typename DataStructType> bool IsA_Internal(const TSharedPtr<FStructOnScope>& InStructOnScope) const;`
- L132 _private member_ `TSharedPtr<FStructOnScope> SelectedDataStruct;`
- L133 _private member_ `TSharedPtr<FStructOnScope> SelectedDataContext;`
- L135 _private member_ `TSharedPtr<void> DataSharedPtr;`
- L136 _private member_ `TSharedPtr<void> SelectedDataContextSharedPtr;`
- L139 _protected member_ `TWeakPtr<FChaosVDSolverDataSelection> Owner;`
- L143 _function_ `template <typename DataStructType> void FChaosVDSolverDataSelectionHandle::SetHandleData(const TSharedPtr<DataStructType>& Data)`
- L158 _function_ `template <typename ContextDataStructType> void FChaosVDSolverDataSelectionHandle::SetHandleContext(ContextDataStructType&& ContextData)`
- L168 _function_ `template <typename DataStructType> bool FChaosVDSolverDataSelectionHandle::IsA() const`
- L174 _function_ `template <typename DataStructType> DataStructType* FChaosVDSolverDataSelectionHandle::GetData() const`
- L185 _function_ `template <typename DataStructType> TSharedPtr<DataStructType> FChaosVDSolverDataSelectionHandle::GetDataAsShared() const`
- L195 _function_ `template <typename ContextDataStructType> ContextDataStructType* FChaosVDSolverDataSelectionHandle::GetContextData() const`
- L206 _function_ `template <typename DataStructType> bool FChaosVDSolverDataSelectionHandle::IsA_Internal(const TSharedPtr<FStructOnScope>& InStructOnScope) const`

#### class `FChaosVDSolverDataSelection`  
`class FChaosVDSolverDataSelection : public TSharedFromThis<FChaosVDSolverDataSelection>`  
_L221-257_
- inherits: `TSharedFromThis<FChaosVDSolverDataSelection>`
- desc: Generic Solver Data selection system. The data this selection system can use must be UStructs
- L228 _public prototype_ `void SelectData(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InSelectionHandle);` — Selects the data in provided selection handle @param InSelectionHandle Handle that references the data we want to select
- L232 _public prototype_ `template<typename SolverDataType, typename HandleType = FChaosVDSolverDataSelectionHandle> TSharedPtr<FChaosVDSolverDataSelectionHandle> MakeSelectionHandle(const TSharedPtr<SolverDataType>& InSolverData);` — Creates a selection handle for the provided data instance. The handle will be owned by this selection systems
- L235 _public function_ `FChaosVDSolverDataSelectionChangedDelegate& GetDataSelectionChangedDelegate()` — Event that is called when the selection in this system changes
- L241 _public function_ `TSharedPtr<FChaosVDSolverDataSelectionHandle> GetCurrentSelectionHandle()` — Returns the selection handle for the currently selected data
- L250 _public prototype_ `template <typename SolverDataType> bool IsDataSelected(const TSharedPtr<SolverDataType>& InSolverData);` — Returns true if the provided solver data instance is selected @param InSolverData Solver data instance to evaluate
- L252 _public prototype_ `bool IsSelectionHandleSelected(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InSelectionHandle) const;`
- L255 _private member_ `FChaosVDSolverDataSelectionChangedDelegate SolverDataSelectionChangeDelegate;`
- L256 _private member_ `TSharedPtr<FChaosVDSolverDataSelectionHandle> CurrentSelectedSolverDataHandle;`
- L260 _function_ `template <typename SolverDataType, typename HandleType> TSharedPtr<FChaosVDSolverDataSelectionHandle> FChaosVDSolverDataSelection::MakeSelectionHandle(const TSharedPtr<SolverDataType>& InSolverData)`
- L272 _function_ `template <typename SolverDataType> bool FChaosVDSolverDataSelection::IsDataSelected(const TSharedPtr<SolverDataType>& InSolverData)`

#### Free symbols / members of external scopes

- L218 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDSolverDataSelectionChangedDelegate, const TSharedPtr<FChaosVDSolverDataSelectionHandle>& SelectionHandle) class FChaosVDSolverDataSelection : public TSharedFromThis<FChaosVDSolverDataSelection> { public: void SelectData(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InSelectionHandle); template<typename SolverDataType, typename HandleType = FChaosVDSolverDataSelectionHandle> TSharedPtr<FChaosVDSolverDataSelectionHandle> MakeSelectionHandle(const TSharedPtr<SolverDataType>& InSolverData); FChaosVDSolverDataSelectionChangedDelegate& GetDataSelectionChangedDelegate() { return SolverDataSelectionChangeDelegate; } TSharedPtr<FChaosVDSolverDataSelectionHandle> GetCurrentSelectionHandle() { return CurrentSelectedSolverDataHandle; } template <typename SolverDataType> bool IsDataSelected(const TSharedPtr<SolverDataType>& InSolverData); bool IsSelectionHandleSelected(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InSelectionHandle) const; private: FChaosVDSolverDataSelectionChangedDelegate SolverDataSelectionChangeDelegate; TSharedPtr<FChaosVDSolverDataSelectionHandle> CurrentSelectedSolverDataHandle; };`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDStyle.h` (Public)


#### class `FChaosVDStyle`  
`class FChaosVDStyle`  
_L11-30_
- L15 _public prototype_ `static void Initialize();`
- L17 _public prototype_ `static void Shutdown();`
- L19 _public prototype_ `static void ReloadTextures();`
- L21 _public prototype_ `static const ISlateStyle& Get();`
- L23 _public prototype_ `static FName GetStyleSetName();`
- L27 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L29 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDTabSpawnerBase.h` (Public)


#### class `FChaosVDTabSpawnerBase`  
`class FChaosVDTabSpawnerBase`  
_L21-84_
- desc: Base class for any tab of the Chaos Visual Debugger tool
- L24 _public prototype_ `virtual ~FChaosVDTabSpawnerBase() = default;`
- L26 _public prototype_ `FChaosVDTabSpawnerBase(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget);`
- L32 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) = 0;` — Handles a spawn request for this tab. It controls how and what contents this tab will have @param Args Arguments about the spawn request
- L38 _public prototype_ `virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed);` — Handles a tab being spawned by this spawner being closed @param InTabClosed RefPtr to the tab that was closed
- L44 _public prototype_ `virtual void HandleTabSpawned(TSharedRef<SDockTab> InTabSpawned);` — Handles a tab being spawned by this spawner being closed @param InTabClosed RefPtr to the tab that was closed
- L47 _public function_ `FChaosVDTabSpawned& OnTabSpawned()` — Event called when the tab is spawned
- L53 _public function_ `FChaosVDTabDestroyed& OnTabDestroyed()` — Event called when the tab this spawner created is destroyed
- L61 _public function_ `FName GetTabID() const` — Returns the name uses as ID for this tab
- L71 _protected prototype_ `TSharedRef<SWidget> GenerateErrorWidget();` — Generates a generic error widget to indicate that this tab was created, but something went wrong
- L74 _protected member_ `TWeakPtr<SChaosVDMainTab> OwningTabWidget;` — Ptr to the main tab of the owning visual debugger tool instance
- L76 _protected member_ `FChaosVDTabSpawned TabSpawnedDelegate;`
- L77 _protected member_ `FChaosVDTabDestroyed TabDestroyedDelegate;`
- L79 _protected prototype_ `UWorld* GetChaosVDWorld() const;`
- L81 _protected prototype_ `TWeakPtr<FChaosVDScene> GetChaosVDScene() const;`
- L83 _protected member_ `FName TabID;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDTabSpawned, TSharedRef<SDockTab>) DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDTabDestroyed, TSharedRef<SDockTab>) class FChaosVDTabSpawnerBase { public: virtual ~FChaosVDTabSpawnerBase() = default; FChaosVDTabSpawnerBase(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget); virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) = 0; virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed); virtual void HandleTabSpawned(TSharedRef<SDockTab> InTabSpawned); FChaosVDTabSpawned& OnTabSpawned() { return TabSpawnedDelegate; } FChaosVDTabDestroyed& OnTabDestroyed() { return TabDestroyedDelegate; }`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDTabDestroyed, TSharedRef<SDockTab>) class FChaosVDTabSpawnerBase { public: virtual ~FChaosVDTabSpawnerBase() = default; FChaosVDTabSpawnerBase(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget); virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) = 0; virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed); virtual void HandleTabSpawned(TSharedRef<SDockTab> InTabSpawned); FChaosVDTabSpawned& OnTabSpawned() { return TabSpawnedDelegate; } FChaosVDTabDestroyed& OnTabDestroyed() { return TabDestroyedDelegate; }`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ChaosVDTabsIDs.h` (Public)


#### class `FChaosVDTabID`  
`class FChaosVDTabID`  
_L10-30_
- desc: Built-in CVD tab IDs
- L14 _public member_ `static const FName ChaosVisualDebuggerTab;`
- L15 _public member_ `static const FName PlaybackViewport;`
- L16 _public member_ `static const FName WorldOutliner;`
- L17 _public member_ `static const FName DetailsPanel;`
- L18 _public member_ `static const FName IndependentDetailsPanel1;`
- L19 _public member_ `static const FName IndependentDetailsPanel2;`
- L20 _public member_ `static const FName IndependentDetailsPanel3;`
- L21 _public member_ `static const FName IndependentDetailsPanel4;`
- L22 _public member_ `static const FName OutputLog;`
- L23 _public member_ `static const FName SolversTrack;`
- L24 _public member_ `static const FName StatusBar;`
- L25 _public member_ `static const FName CollisionDataDetails;`
- L26 _public member_ `static const FName SceneQueryDataDetails;`
- L27 _public member_ `static const FName ConstraintsInspector;`
- L28 _public member_ `static const FName SceneQueryBrowser;`
- L29 _public member_ `static const FName RecordedOutputLog;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSVD_API`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Components/ChaosVDParticleDataComponent.h` (Public)


#### class `UChaosVDParticleDataComponent`  
`class UChaosVDParticleDataComponent : public UChaosVDSolverDataComponent, public IChaosVDStreamingDataSource`  
_L29-128_
- reflection: `UCLASS()`
- inherits: `UChaosVDSolverDataComponent,IChaosVDStreamingDataSource`
- desc: Component that references all particle data for a specific solver for the current frame, and handles how the visualization is updated based on that data
- L33 _public prototype_ `UChaosVDParticleDataComponent();`
- L35 _public typedef_ `typedef TArray<UE::Editor::DataStorage::RowHandle, TInlineAllocator<256, TMemStackAllocator<>>> FTedsHandlesForBatchArray;`
- L42 _public prototype_ `virtual void SetScene(const TWeakPtr<FChaosVDScene>& InSceneWeakPtr) override;`
- L43 _public prototype_ `virtual void ClearData() override;`
- L45 _public prototype_ `virtual void UpdateFromNewSolverStageData(const FChaosVDSolverFrameData& InSolverFrameData, const FChaosVDFrameStageData& InSolverFrameStageData) override;`
- L46 _public prototype_ `virtual void UpdateFromSolverFrameData(const FChaosVDSolverFrameData& InSolverFrameData) override;`
- L49 _public prototype_ `template <class TCallback> void VisitSelectedParticleData(TCallback VisitCallback) const;`
- L52 _public prototype_ `template <class TCallback> void VisitAllParticleInstances(TCallback VisitCallback) const;`
- L55 _public prototype_ `template <class TCallback> void VisitAllParticleData(TCallback VisitCallback) const;`
- L57 _public prototype_ `virtual void SetVisibility(bool bNewIsVisible) override;`
- L59 _public prototype_ `TSharedPtr<FChaosVDSceneParticle> GetParticleInstanceByID(int32 ParticleID) const;`
- L60 _public prototype_ `TSharedPtr<FChaosVDSceneParticle> GetParticleInstanceByID_AssumesLocked(int32 ParticleID) const;`
- L62 _public prototype_ `TSharedPtr<FChaosVDBaseSceneObject> GetParticleContainerByType(EChaosVDParticleType ParticleType);`
- L63 _public prototype_ `TSharedPtr<FChaosVDBaseSceneObject> GetParticleContainerByType_AssumesLocked(EChaosVDParticleType ParticleType);`
- L65 _public function_ `const TSortedMap<EChaosVDParticleType, TSharedPtr<FChaosVDBaseSceneObject>>& GetParticleSceneContainersByType()`
- L70 _public prototype_ `FChaosVDSceneParticle* GetSelectedParticle() const;`
- L72 _public prototype_ `virtual void HandleWorldStreamingLocationUpdated(const FVector& InLocation) override;`
- L75 _public function_ `virtual TConstArrayView<TSharedRef<FChaosVDBaseSceneObject>> GetStreamableSceneObjects() const override` — BEGIN IChaosVDStreamingDataSource
- L80 _public function_ `virtual FRWLock& GetObjectsLock() const override`
- L86 _public prototype_ `virtual void AppendSceneCompositionTestData(FChaosVDSceneCompositionTestData& OutStateTestData) override;`
- L90 _protected prototype_ `int32 GetMaxElementCountForBatchTEDSUpdate_AssumesLocked() const;`
- L92 _protected prototype_ `void BatchTEDSSyncFromWorldTag(FTedsHandlesForBatchArray& ParticlesPendingTEDSTagSync, const UE::Editor::DataStorage::ICompatibilityProvider* CompatibilityStorage, UE::Editor::DataStorage::ICoreProvider* DataStorage);`
- L96 _protected prototype_ `void BatchTEDSCombinedSyncFromWorldAndActiveTag(FTedsHandlesForBatchArray& ParticlesPendingCombinedTEDSTagSync, const UE::Editor::DataStorage::ICompatibilityProvider* CompatibilityStorage, UE::Editor::DataStorage::ICoreProvider* DataStorage);`
- L100 _protected prototype_ `void BatchTEDSAddRemoveTags(UE::Editor::DataStorage::ICoreProvider* EditorDataStorage, FTedsHandlesForBatchArray& ParticlesPendingTEDSTagSync, TConstArrayView<const UScriptStruct*> ColumnsToAdd, TConstArrayView<const UScriptStruct*> ColumnsToRemove);`
- L103 _protected prototype_ `void ProcessRemovedParticles_AssumessLocked(const TSharedRef<FChaosVDScene>& SceneRef, const FChaosVDSolverFrameData& InSolverFrameData, const FChaosVDFrameStageData& InSolverFrameStageData, const TSet<int32>& ParticlesUpdatedIDsForKeyFrameDiff, FTedsHandlesForBatchArray& OutRemovedTedsHandles);`
- L106 _protected prototype_ `void BatchApplySolverVisibilityToParticle(bool bNewIsVisible);`
- L108 _protected prototype_ `void HandleVisibilitySettingsUpdated(UObject* SettingsObject);`
- L109 _protected prototype_ `void HandleColorsSettingsUpdated(UObject* SettingsObject);`
- L111 _protected prototype_ `bool IsServerData();`
- L112 _protected prototype_ `const FString& GetSolverName();`
- L115 _protected prototype_ `TSharedRef<FChaosVDSceneParticle> CreateSceneParticle_AssumesLocked(const TSharedRef<FChaosVDParticleDataWrapper>& InParticleData, const FChaosVDSolverFrameData& InFrameData);` — Creates an ChaosVDParticle actor for the Provided recorded Particle Data
- L117 _protected member_ `TOptional<bool> bCachedIsServerData;`
- L118 _protected member_ `TOptional<FString> bCachedSolverName;`
- L120 _protected member_ `TSortedMap<EChaosVDParticleType, TSharedPtr<FChaosVDBaseSceneObject>> ParticleSceneContainersByType;`
- L122 _protected member_ `TMap<int32, TSharedRef<FChaosVDSceneParticle>> SolverParticlesByID;`
- L123 _protected member_ `TArray<TSharedRef<FChaosVDBaseSceneObject>> SolverParticlesArray;`
- L125 _protected member_ `mutable FRWLock ParticleSceneObjectsLock;`
- L127 _protected member_ `FChaosVDSceneStreaming StreamingSystem;`
- L131 _function_ `template <typename TCallback> void UChaosVDParticleDataComponent::VisitSelectedParticleData(TCallback VisitCallback) const`
- L168 _function_ `template <typename TCallback> void UChaosVDParticleDataComponent::VisitAllParticleInstances(TCallback VisitCallback) const`
- L182 _function_ `template <typename TCallback> void UChaosVDParticleDataComponent::VisitAllParticleData(TCallback VisitCallback) const`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Chaos`
- L19 _namespace_ `namespace VD` (scope `Chaos`)
- L19 _namespace_ `namespace Test` (scope `Chaos::VD`)
- L19 _namespace_ `namespace SceneObjectTypes` (scope `Chaos::VD::Test`)
- L21 _externvar_ `extern FName ActiveParticles;` (scope `Chaos::VD::Test::SceneObjectTypes`)

### `Plugins/ChaosVD/Source/ChaosVD/Public/Components/ChaosVDParticleExtraDataComponent.h` (Public)


#### struct `FChaosVDExtraDataScopeEntry`  
`struct FChaosVDExtraDataScopeEntry`  
_L14-19_
- desc: Holds a deserialized struct scope together with enough metadata to match it against fresh frame data for in-place memory updates.
- L16 _public member_ `FName CategoryName;`
- L17 _public member_ `FName StructTypePath;`
- L18 _public member_ `TSharedPtr<FStructOnScope> Scope;`

#### class `UChaosVDParticleExtraDataComponent`  
`class UChaosVDParticleExtraDataComponent : public UChaosVDSolverDataComponent`  
_L35-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UChaosVDSolverDataComponent`
- desc: Solver data component that reads FChaosVDParticleExtraDataContainer from the current solver frame and injects the recorded structs into the CVD particle details panel. Added to AChaosVDSolverInfoActor as a default subobject. It binds to FChaosVDScene::OnParticleDetailsExtraDataRequested and for each selected particle adds the traced categories to the IDetailLayoutBuilder, so the extra data appears alongside "Particle Data" in the details panel (and in "Show Data in New Panel"). On subsequent frame changes (OnParticleDetailsExtraDataRefreshRequested), it updates the cached FStructOnScope memory in-place so Slate picks up the new values without requiring a full layout rebuild.
- L41 _public prototype_ `virtual void ClearData() override;`
- L42 _public prototype_ `virtual void UpdateFromSolverFrameData(const FChaosVDSolverFrameData& InSolverFrameData) override;`
- L43 _public prototype_ `virtual void SetScene(const TWeakPtr<FChaosVDScene>& InSceneWeakPtr) override;`
- L47 _private prototype_ `void HandleParticleDetailsExtraData(int32 InSolverID, int32 InParticleID, IDetailLayoutBuilder& DetailBuilder);`
- L48 _private prototype_ `void HandleParticleDetailsRefresh(int32 InSolverID, int32 InParticleID, bool& bOutNeedsFullRebuild);`
- L49 _private prototype_ `void UnbindFromScene(const TSharedPtr<FChaosVDScene>& Scene);`
- L52 _private member_ `TSharedPtr<FChaosVDParticleExtraDataContainer> CurrentFrameContainer;` — Extra data container for the current frame, looked up once per frame update.
- L56 _private member_ `TArray<FChaosVDExtraDataScopeEntry> CachedScopeEntries;` — Stable FStructOnScope instances added to the details panel for the currently selected particle. Kept alive so we can update their memory in-place on frame changes without rebuilding the layout.
- L59 _private member_ `int32 CachedSolverID = INDEX_NONE;` — Solver/particle for which CachedScopeEntries were built.
- L60 _private member_ `int32 CachedParticleID = INDEX_NONE;`
- L62 _private member_ `FDelegateHandle ExtraDataDelegateHandle;`
- L63 _private member_ `FDelegateHandle RefreshDelegateHandle;`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Components/ChaosVDSolverDataComponent.h` (Public)


#### class `UChaosVDSolverDataComponent`  
`class UChaosVDSolverDataComponent : public UActorComponent`  
_L17-57_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UActorComponent`
- desc: Base class for all components that stores recorded solver data
- L21 _public prototype_ `virtual void ClearData() PURE_VIRTUAL(UChaosVDSolverDataComponent::ClearData);`
- L22 _public prototype_ `virtual void SetScene(const TWeakPtr<FChaosVDScene>& InSceneWeakPtr);`
- L24 _public function_ `virtual void UpdateFromNewGameFrameData(const FChaosVDGameFrameData& InGameFrameData)`
- L25 _public function_ `virtual void UpdateFromNewSolverStageData(const FChaosVDSolverFrameData& InSolverFrameData, const FChaosVDFrameStageData& InSolverFrameStageData)`
- L26 _public function_ `virtual void UpdateFromSolverFrameData(const FChaosVDSolverFrameData& InSolverFrameData)`
- L28 _public function_ `bool IsVisible() const`
- L33 _public prototype_ `virtual void SetVisibility(bool bNewIsVisible);`
- L35 _public function_ `virtual void HandleWorldStreamingLocationUpdated(const FVector& InLocation)`
- L37 _public function_ `void SetSolverID(int32 InSolverID)`
- L48 _public function_ `virtual void AppendSceneCompositionTestData(FChaosVDSceneCompositionTestData& OutStateTestData)` — Appends Scene Data relevant for functional tests @param OutStateTestData Structure instance where to add the data @note If you change the data being added here, you need to re-generate the snapshots used by the scene integrity playback tests in the Simulation Tests Plugin
- L52 _protected member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;`
- L54 _protected member_ `int32 SolverID = INDEX_NONE;`
- L56 _protected member_ `bool bIsVisible = true;`

### `Plugins/ChaosVD/Source/ChaosVD/Public/DataWrappers/ChaosVDParticleExtraDataContainer.h` (Public)


#### struct `FChaosVDParticleExtraDataContainer`  
`struct FChaosVDParticleExtraDataContainer`  
_L24-36_
- reflection: `USTRUCT()`
- desc: Custom data container stored in FChaosVDSolverFrameData::CustomData. Maps SolverID -> ParticleID -> extra data payload for O(1) lookup at display time. Must be a USTRUCT so FChaosVDCustomFrameData::GetOrAddDefaultData<T>() can key it via StaticStruct()->GetFName() The NameTable is set by FChaosVDParticleExtraDataProcessor at load time so that UChaosVDParticleExtraDataComponent can deserialize inner struct bytes without needing a separate route to the trace provider.
- L28 _public member_ `TMap<int32, TMap<int32, TSharedPtr<Chaos::VisualDebugger::FChaosVDParticleExtraData>>> DataBySolverAndParticleID;`
- L31 _public member_ `TSharedPtr<Chaos::VisualDebugger::FChaosVDSerializableNameTable> NameTable;` — Recording-session name table, cached here by the processor so the component can resolve FName IDs in inner struct bytes.
- L35 _public member_ `TSet<FName> NativeSerializedStructTypes;` — Struct type paths for entries that used NativeSerialization mode. Populated by FChaosVDParticleExtraDataProcessor at load time.

### `Plugins/ChaosVD/Source/ChaosVD/Public/ExtensionsSystem/ChaosVDExtension.h` (Public)


#### class `FChaosVDExtension`  
`class FChaosVDExtension : public IModularFeature`  
_L22-68_
- inherits: `IModularFeature`
- desc: Base class for any CVD Extension. This object will auto register itself with the extensions system, and receive any relevant CVD callbacks
- L26 _public prototype_ `FChaosVDExtension() = default;`
- L28 _public prototype_ `virtual ~FChaosVDExtension() = default;`
- L31 _public function_ `FName GetExtensionType() const` — FName used as Type within CVD Extension system
- L37 _public function_ `virtual void RegisterDataProcessorsInstancesForProvider(const TSharedRef<FChaosVDTraceProvider>& InTraceProvider)` — Returns an array view of all available data processors instances in this extension
- L40 _public function_ `virtual TConstArrayView<TSubclassOf<UActorComponent>> GetSolverDataComponentsClasses()` — Returns an array view of all available solver data component instances in this extension, if any
- L46 _public function_ `virtual void RegisterComponentVisualizers(const TSharedRef<SChaosVDMainTab>& InCVDToolKit)` — Registers all available component visualizer instances in this extension, if any
- L49 _public function_ `virtual void RegisterCustomTabSpawners(const TSharedRef<SChaosVDMainTab>& InParentTabWidget)` — Registers all available Tab Spawner instances in this extension, if any
- L52 _public function_ `virtual void PostMainTabInitialization(const TSharedRef<SChaosVDMainTab>& InParentTabWidget)` — Initialization by Extension after MainTab is constructed
- L55 _public function_ `virtual void SetCustomPropertyLayouts(IDetailsView* DetailsView, TSharedRef<SChaosVDMainTab> InCVDToolKit)` — Injects any customization implementations for CVD's details panels
- L58 _public function_ `virtual void HandlePlaybackControllerDataUpdated(TWeakPtr<FChaosVDPlaybackController> InController)` — Handles new data being loaded into a CVD Instance
- L61 _public function_ `virtual void HandleControllerTrackFrameUpdated(TWeakPtr<FChaosVDPlaybackController> InController, TWeakPtr<const FChaosVDTrackInfo> UpdatedTrackInfo, FGuid InstigatorGuid)` — Handles playback state changes on a CVD Instance
- L64 _public function_ `virtual void HandleRecordingFirstFrameLoaded(TWeakPtr<FChaosVDPlaybackController> InController)` — Handles initial first frame playback after a recording is loading
- L67 _protected member_ `FName ExtensionName;`

### `Plugins/ChaosVD/Source/ChaosVD/Public/ExtensionsSystem/ChaosVDExtensionsManager.h` (Public)


#### class `FChaosVDExtensionsManager`  
`class FChaosVDExtensionsManager`  
_L9-57_
- desc: Manager class where all CVD extensions are registered to
- L12 _public prototype_ `FChaosVDExtensionsManager();`
- L13 _public prototype_ `~FChaosVDExtensionsManager();`
- L19 _public prototype_ `template <class VisitorType> void EnumerateExtensions(const VisitorType& ExtensionVisitor);` — Iterates through all registered extensions, and calls the provided callback with them @param ExtensionVisitor Callback to call for each extension
- L22 _public prototype_ `static FChaosVDExtensionsManager& Get();` — Returns an instance to CVD's extensions manager
- L25 _public prototype_ `static void TearDown();` — De-initializes CVD extenisons manager
- L30 _public prototype_ `void RegisterExtension(const TSharedRef<FChaosVDExtension>& InExtension);` — Registers a CVD extension instance @param InExtension Instances of the extension to register
- L35 _public prototype_ `void UnRegisterExtension(const TSharedRef<FChaosVDExtension>& InExtension);` — Unregisters a CVD extension instance. Usually called during editor shutdown @param InExtension Instances of the extension to unregister
- L37 _public prototype_ `DECLARE_EVENT_OneParam(FChaosVDExtensionsManager, FOnExtensionChanged, const TSharedRef<FChaosVDExtension>&);`
- L40 _public function_ `FOnExtensionChanged& OnExtensionRegistered()` — Event called each time a new CVD extension is registered
- L46 _public function_ `FOnExtensionChanged& OnExtensionUnRegistered()` — Event called each time a new CVD extension is unregistered. Usually during editor shutdown
- L53 _private member_ `FOnExtensionChanged ExtensionRegisteredEvent;`
- L54 _private member_ `FOnExtensionChanged ExtensionUnRegisteredEvent;`
- L56 _private member_ `TMap<FName, TSharedRef<FChaosVDExtension>> AvailableExtensions;`
- L60 _function_ `template <typename VisitorType> void FChaosVDExtensionsManager::EnumerateExtensions(const VisitorType& ExtensionVisitor)`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_EVENT_OneParam(FChaosVDExtensionsManager, FOnExtensionChanged, const TSharedRef<FChaosVDExtension>&);`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Interfaces/ChaosVDPooledObject.h` (Public)


#### class `UChaosVDPooledObject`  
`class UChaosVDPooledObject : public UInterface`  
_L9-12_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IChaosVDPooledObject`  
`class IChaosVDPooledObject`  
_L17-24_
- desc: Interface used by any object that can be pooled

### `Plugins/ChaosVD/Source/ChaosVD/Public/Interfaces/ChaosVDSelectableObject.h` (Public)


#### class `UChaosVDSelectableObject`  
`class UChaosVDSelectableObject : public UInterface`  
_L9-12_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IChaosVDSelectableObject`  
`class IChaosVDSelectableObject`  
_L17-24_
- desc: Interface used for any object that can be selected in CVD and need to process selection events performed on it.
- L22 _public prototype_ `virtual void HandleSelected() PURE_VIRTUAL(IChaosVDSelectionAware::HandleSelected);`
- L23 _public prototype_ `virtual void HandleDeSelected() PURE_VIRTUAL(IChaosVDSelectionAware::HandleUnSelected);`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Settings/ChaosVDCoreSettings.h` (Public)


#### class `UChaosVDSettingsObjectsOuter`  
`class UChaosVDSettingsObjectsOuter : public UObject`  
_L19-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`

#### class `UChaosVDSettingsObjectBase`  
`class UChaosVDSettingsObjectBase : public UObject`  
_L28-60_
- reflection: `UCLASS(config = ChaosVD, MinimalAPI)`
- inherits: `UObject`
- desc: Base class to be used by any CVD settings. Contains the base logic to make these settings work with CVD's options save system
- L31 _public prototype_ `UChaosVDSettingsObjectBase();`
- L38 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _public function_ `FChaosVDSettingChanged& OnSettingsChanged()`
- L42 _public prototype_ `virtual void PostEditUndo() override;`
- L44 _public prototype_ `virtual void OverridePerObjectConfigSection(FString& SectionName) override;`
- L46 _public function_ `FStringView GetConfigSectionName()`
- L52 _protected prototype_ `virtual void BroadcastSettingsChanged();`
- L56 _private member_ `FString OverrideConfigSectionName;`
- L57 _private member_ `FChaosVDSettingChanged SettingsChangedDelegate;`

#### class `UChaosVDVisualizationSettingsObjectBase`  
`class UChaosVDVisualizationSettingsObjectBase : public UChaosVDSettingsObjectBase`  
_L68-77_
- reflection: `UCLASS(config = ChaosVD, MinimalAPI)`
- inherits: `UChaosVDSettingsObjectBase`
- desc: Base class to be used by any CVD settings related to visualization. Contains the base logic to make these settings work with CVD's options save system And makes sure that the viewport gets re-draw when a setting changes
- L72 _protected prototype_ `virtual void BroadcastSettingsChanged() override;`
- L76 _public prototype_ `virtual bool CanVisualizationFlagBeChangedByUI(uint32 Flag);` — Returns true if a visualization flag option of this setting option should be enabled in the UI

#### class `UChaosVDCoreSettings`  
`class UChaosVDCoreSettings : public UChaosVDSettingsObjectBase`  
_L81-109_
- reflection: `UCLASS(config = Engine)`
- inherits: `UChaosVDSettingsObjectBase`
- desc: Core settings class for CVD
- L87 _public member_ `TSoftObjectPtr<UMaterial> QueryOnlyMeshesMaterial;` — `UPROPERTY(Config, Transient)`
- L90 _public member_ `TSoftObjectPtr<UMaterial> SimOnlyMeshesMaterial;` — `UPROPERTY(Config, Transient)`
- L93 _public member_ `TSoftObjectPtr<UMaterial> InstancedMeshesMaterial;` — `UPROPERTY(Config, Transient)`
- L96 _public member_ `TSoftObjectPtr<UMaterial> InstancedMeshesQueryOnlyMaterial;` — `UPROPERTY(Config, Transient)`
- L99 _public member_ `FSoftClassPath SkySphereActorClass;` — `UPROPERTY(Config)`
- L102 _public member_ `TSoftObjectPtr<UTextureCube> AmbientCubeMapTexture;` — `UPROPERTY(Config)`
- L105 _public member_ `TSoftObjectPtr<UStaticMesh> BoxMesh;` — `UPROPERTY(Config)`
- L108 _public member_ `TSoftObjectPtr<UStaticMesh> SphereMesh;` — `UPROPERTY(Config)`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDSettingChanged, UObject* SettingsObject) UCLASS(MinimalAPI) class UChaosVDSettingsObjectsOuter : public UObject { GENERATED_BODY() };`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Settings/ChaosVDGeneralSettings.h` (Public)


#### enum `EChaosVDParticleExtraDataLoadingMode`  
`enum class EChaosVDParticleExtraDataLoadingMode : uint8`  
_L20-37_
- reflection: `UENUM()`
- desc: Controls how FChaosVDParticleExtraDataProcessor handles particle extra data at load time. Reflection-based entries use property-tagged serialization: properties are matched by name at load time against the *current* struct layout, so adds/removes/renames are handled gracefully (missing props show defaults; added props are lost). No crash risk. Natively-serialized entries invoke the struct's native Serialize function, which reads bytes at fixed offsets. When the struct layout matches, values are exact. When it does not match, the result is a crash or silently corrupt values -- there is no graceful degradation.
- L25 _public enumerator_ `SkipAll UMETA(DisplayName = "Skip All (Safe)")` — Skip the processor entirely — no extra data is loaded or displayed. The only mode that guarantees neither incorrect values nor crashes regardless of how much struct definitions have changed since recording.
- L30 _public enumerator_ `SerializeBinOnly UMETA(DisplayName = "Reflection-Based Only")` — Load only reflection-based entries; natively-serialized entries are stripped in the processor before reaching memory. No crash risk, but displayed values may be inaccurate if struct definitions changed since recording.
- L36 _public enumerator_ `LoadAll UMETA(DisplayName = "Load All (Unsafe)")` — Load all entries including natively-serialized ones. Displays exact recorded values when the struct layout matches the recording. If the layout has changed, natively-serialized entries may crash or display corrupt values. Only use when the recording and viewer binaries are known to match.

#### class `UChaosVDGeneralSettings`  
`class UChaosVDGeneralSettings : public UChaosVDSettingsObjectBase`  
_L43-167_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDSettingsObjectBase`
- desc: General settings that controls how CVD behaves
- L52 _public prototype_ `UE::TraceBasedDebuggers::ETraceTransportMode GetTransportModeForTargetType(EBuildTargetType TargetType) const;` — Returns the configured transport mode for the provided target type @param TargetType Build target type to evaluate
- L58 _public prototype_ `void SetTransportModeForTargetType(EBuildTargetType TargetType, UE::TraceBasedDebuggers::ETraceTransportMode NewTransportMode);` — Sets a specific transport mode for the provided target type @param TargetType Build target type to evaluate @param NewTransportMode New transport mode to use for the provided target
- L62 _public prototype_ `EChaosVDTransportMode GetTransportModeForTarget(EBuildTargetType TargetType) const;` — `UE_DEPRECATED(5.8, "Use GetTransportModeForTargetType")`
- L65 _public prototype_ `void SetTransportModeForTarget(EBuildTargetType TargetType, EChaosVDTransportMode NewTransportMode);` — `UE_DEPRECATED(5.8, "Use SetTransportModeForTargetType")`
- L70 _public member_ `bool bTrimEmptyFrames = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Session Data Loading")` — If true, CVD will only load frames that have solver data in them - Only takes effect before loading a file
- L74 _public member_ `int32 MaxGameThreadFramesToQueueNum = 10;` — `UPROPERTY(Config, EditAnywhere, Category = "Session Data Loading")` — How many Game thread frames CVD should queue internally before making them available in the visualization and timeline controls - Only takes effect before loading a file
- L78 _public member_ `bool bStreamingSystemEnabled = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Performance | Streaming")` — If true, CVD will only load collision geometry that is visible
- L82 _public member_ `float StreamingBoxExtentSize = 10000.0f;` — `UPROPERTY(Config, EditAnywhere, Category = "Performance | Streaming")` — Extent size of the box used for calculate what should be streamed in
- L86 _public member_ `bool bProcessPendingOperationsQueueInWorkerThread = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Performance | Streaming")` — If set to true CVD will process any updates to the streaming accel structure in worker threads, in between streaming updates
- L91 _public member_ `bool bUpdateSceneOutlinerDuringPlayback = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Performance | Scene Outliner")` — If set to true CVD will keep the scene outliner up to date as the recording is played. If during the recording a significant amount of objects are loaded/unloaded, the performance impact will be significant enough to degrade the playback stability.
- L95 _public member_ `int32 MaxConnectionRetries = 14;` — `UPROPERTY(Config, EditAnywhere, Category = Connection)` — How many times CVD will attempt to connect to a live trace or load from file session if the first attempt failed
- L99 _public member_ `bool bSaveRecordingsToDisk = true;` — `UPROPERTY(EditAnywhere, Category = Connection)` — If True, any traces done to memory will also be saved to disk at the same time in the user's document folder (or a user specified folder). This is not saved by design
- L103 _public member_ `FFilePath DefaultSavePathOverride;` — `UPROPERTY(Config, EditAnywhere, Category = Connection)` — Custom path where recordings will be saved from. By default, recordings are saved in a Chaos Visual Debugger folder in the documents folder
- L107 _public member_ `bool bAutoStartLiveSessionsPlayback = true;` — `UPROPERTY(Config, EditAnywhere, Category = Connection)` — If True, playback will start automatically after a recording started, and we successfully connect to it
- L118 _public member_ `bool bSafeLoadingMode = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Backwards Compatibility")` — If true, CVD will skip data whose binary format is not guaranteed to be backwards compatible (e.g. raw-serialized structs such as generic particle extra data). This prevents crashes when opening a recording made with a different executable than the viewer. When enabled, any skipped data types are reported in a dialog after loading. Disable this only when you are certain the recording was made with the same binary as the viewer.
- L142 _public member_ `EChaosVDParticleExtraDataLoadingMode ParticleExtraDataLoadingMode = EChaosVDParticleExtraDataLoadingMode::SerializeBinOnly;` — `UPROPERTY(Config, EditAnywhere, Category = "Backwards Compatibility")` — Controls how particle extra data is loaded. Particle extra data is not backwards compatible by design -- it accepts arbitrary UStructs without requiring dedicated data wrappers. SkipAll: processor is skipped entirely. No extra data is loaded or displayed. The only mode that guarantees neither crashes nor silently incorrect values, regardless of how much struct definitions have changed since recording. Reflection-Based Only (default): only reflection-based (property-tagged) entries are loaded; natively-serialized entries are filtered out in the processor and never stored in memory. No crash risk, but values may be inaccurate if struct properties were added, removed, or renamed since recording. LoadAll: all entries including natively-serialized ones are loaded. Displays exact recorded values when the viewer binary matches the recording binary. If struct layouts have changed, natively-serialized entries may crash or show corrupt values. Only use when recording and viewer are known to match. Note: bSafeLoadingMode applies to any other non-backwards-compatible processors; this enum takes precedence for particle extra data specifically.
- L147 _public member_ `bool bShowUnsafeDataWarning = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Backwards Compatibility")` — If true, a warning dialog is shown after loading when non-backwards-compatible data was processed with Safe Loading Mode disabled. Uncheck to suppress the warning.
- L152 _public member_ `bool bShowSafeModeSkippedWarning = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Backwards Compatibility")` — If true, an informational dialog is shown after loading when data types were skipped because Safe Loading Mode is enabled. Uncheck to suppress the warning.
- L157 _public member_ `bool bShowNativeSerializationWarning = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Backwards Compatibility")` — If true, shows a warning dialog after loading when native-serialized extra data is present and ParticleExtraDataLoadingMode is LoadAll.
- L162 _private member_ `UE::TraceBasedDebuggers::ETraceTransportMode GameServerDataTransportMode = UE::TraceBasedDebuggers::ETraceTransportMode::Direct;` — `UPROPERTY(EditAnywhere, Category = Connection)` — [DEBUG Setting] Default Data Transport for Game Servers - Used to change the transport mode for the trace data. This is not saved by design
- L166 _private member_ `UE::TraceBasedDebuggers::ETraceTransportMode GameClientDataTransportMode = UE::TraceBasedDebuggers::ETraceTransportMode::Direct;` — `UPROPERTY(EditAnywhere, Category = Connection)` — [DEBUG Setting] Default Data Transport for Game Clients - Used to change the transport mode for the trace data. This is not saved by design

### `Plugins/ChaosVD/Source/ChaosVD/Public/TEDS/ChaosVDSelectionInterface.h` (Public)


#### class `UChaosVDSelectionInterface`  
`class UChaosVDSelectionInterface : public UObject, public ITypedElementSelectionInterface`  
_L14-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,ITypedElementSelectionInterface`
- desc: CVD Custom Selection Interface. We don't have any specific implementation overrides yet

#### class `UChaosVDTedsTypedElementBridgeInterface`  
`class UChaosVDTedsTypedElementBridgeInterface : public UObject, public ITedsTypedElementBridgeInterface`  
_L20-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,ITedsTypedElementBridgeInterface`
- L24 _public prototype_ `virtual FTedsRowHandle GetRowHandle(const FTypedElementHandle& InElementHandle) const override;`

### `Plugins/ChaosVD/Source/ChaosVD/Public/TEDS/ChaosVDStructTypedElementData.h` (Public)


#### struct `Chaos::VD::TypedElementDataUtil::FStructTypedElementData`  
`struct FStructTypedElementData`  
_L18-29_
- L22 _public member_ `UStruct* TypeInfo = nullptr;`
- L23 _public member_ `void* RawData = nullptr;`
- L26 _public prototype_ `template<typename StructDataType> StructDataType* GetData() const;`
- L28 _public prototype_ `TSharedPtr<FStructOnScope> GetDataAsStructScope() const;`
- L34 _function_ `template <typename StructDataType> StructDataType* FStructTypedElementData::GetData() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSVD_API`
- L14 _namespace_ `namespace Chaos`
- L14 _namespace_ `namespace VD` (scope `Chaos`)
- L14 _namespace_ `namespace TypedElementDataUtil` (scope `Chaos::VD`)
- L16 _variable_ `static const FName NAME_CVD_StructDataElement = FName("CVD` (scope `Chaos::VD::TypedElementDataUtil`)
- L31 _externvar_ `extern TTypedElementOwnerStore<FStructTypedElementData, void*> GCVDTypedStructDataElementOwnerStore;` (scope `Chaos::VD::TypedElementDataUtil`)
- L45 _function_ `template<typename StructDataType> TTypedElementOwner<FStructTypedElementData> CreateTypedElementDataForStructData(StructDataType* InElementData)` (scope `Chaos::VD::TypedElementDataUtil`)
- L64 _function_ `template<typename StructDataType> FTypedElementHandle AcquireTypedElementHandleForStruct(StructDataType* ElementInstance, const bool bAllowCreate)` (scope `Chaos::VD::TypedElementDataUtil`)
- L73 _function_ `` (scope `Chaos::VD::TypedElementDataUtil::AcquireTypedElementHandleForStruct`)
- L86 _prototype_ `void DestroyTypedElementHandleForStruct(void* InElementData);` (scope `Chaos::VD::TypedElementDataUtil`)
- L89 _function_ `template <typename StructDataType> StructDataType* GetStructDataFromTypedElementHandle(const FTypedElementHandle& InHandle, const bool bSilent = true)` (scope `Chaos::VD::TypedElementDataUtil`)
- L95 _prototype_ `TSharedPtr<FStructOnScope> GetStructOnScopeDataFromTypedElementHandle(const FTypedElementHandle& InHandle, const bool bSilent = false);` (scope `Chaos::VD::TypedElementDataUtil`)
- L97 _prototype_ `void CleanUpTypedElementStore();` (scope `Chaos::VD::TypedElementDataUtil`)
- L101 _function_ `template <> inline FString GetTypedElementDebugId< Chaos::VD::TypedElementDataUtil::FStructTypedElementData>(const Chaos::VD::TypedElementDataUtil::FStructTypedElementData& InElementData)`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Trace/ChaosVDTraceManager.h` (Public)


#### struct `Chaos::VD::FAsyncProgressNotification`  
`struct UE_DEPRECATED(5.8, "This struct will no longer be exposed publicly") FAsyncProgressNotification : FTSTickerObjectBase`  
_L23-27_
- inherits: `FTSTickerObjectBase`
- L25 _public function_ `FAsyncProgressNotification(const FText&)`
- L26 _public function_ `void EnterProgress(int32 InCurrentProgress)`

#### class `Chaos::VD::IRemoteSessionDataStream`  
`class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::IRemoteSessionDataStream instead") IRemoteSessionDataStream`  
_L29-35_
- L32 _public prototype_ `virtual ~IRemoteSessionDataStream() = default;`
- L33 _public prototype_ `virtual FGuid GetOwningRemoteSessionID() const = 0;`
- L34 _public prototype_ `virtual uint64 UpdateAndGetBytesReadSinceLastMeasurement() = 0;`

#### class `Chaos::VD::FSessionStreamStatsUpdater`  
`class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FSessionStreamStatsUpdater instead") FSessionStreamStatsUpdater : FTSTickerObjectBase`  
_L37-41_
- inherits: `FTSTickerObjectBase`
- L40 _public function_ `explicit FSessionStreamStatsUpdater(IRemoteSessionDataStream* const DataStreamInstance)`

#### class `Chaos::VD::FDirectSocketStream`  
`class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FDirectSocketStream instead") FDirectSocketStream : public UE::Trace::FDirectSocketStream, public IRemoteSessionDataStream`  
_L43-56_
- inherits: `UE::Trace::FDirectSocketStream,IRemoteSessionDataStream`
- L46 _public prototype_ `FDirectSocketStream() = delete;`
- L47 _public function_ `explicit FDirectSocketStream(FGuid)`
- L48 _public function_ `explicit FDirectSocketStream(FGuid, TUniquePtr<FArchiveFileWriterGeneric>&& InFileWriter) : UE::Trace::FDirectSocketStream(MoveTemp(InFileWriter))`
- L53 _public function_ `virtual int32 Read(void* Data, uint32 Size) override`
- L54 _public function_ `virtual FGuid GetOwningRemoteSessionID() const override`
- L55 _public function_ `virtual uint64 UpdateAndGetBytesReadSinceLastMeasurement() override`

#### class `Chaos::VD::FRelayDataStream`  
`class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FRelayDataStream instead") FRelayDataStream : public UE::Trace::IInDataStream, public IRemoteSessionDataStream`  
_L58-69_
- inherits: `UE::Trace::IInDataStream,IRemoteSessionDataStream`
- L61 _public function_ `explicit FRelayDataStream(FGuid InRemoteSessionID)`
- L62 _public function_ `explicit FRelayDataStream(FGuid InRemoteSessionID, TUniquePtr<FArchiveFileWriterGeneric>&& InFileWriter)`
- L64 _public function_ `void EnqueueRelayedData(const TConstArrayView<uint8> InTraceDataBuffer)`
- L65 _public function_ `void EnqueueRelayedData(TArray<uint8>&& InTraceDataBuffer)`
- L67 _public function_ `virtual FGuid GetOwningRemoteSessionID() const override`
- L68 _public function_ `virtual uint64 UpdateAndGetBytesReadSinceLastMeasurement() override`

#### struct `FChaosVDTraceSessionDescriptor`  
`struct UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FTraceSessionDescriptor instead") FChaosVDTraceSessionDescriptor`  
_L72-101_
- L76 _public member_ `FString SessionName;` — The trace session name. Used to get the trace analysis instance for this CVD session
- L78 _public member_ `uint16 SessionPort = 0;` — Port number used to establish a connection to this session. The value is 0 if no specific port was used
- L80 _public member_ `FGuid RemoteSessionID;` — Session ID of this CVD session in the Remote Session management system
- L83 _public member_ `bool bIsLiveSession = false;` — True if this is a session recorded live (not loaded from disk)
- L86 _public function_ `bool IsValid() const` — Returns true if valid. For a session to be valued needs at minimum have a Trace Session name

#### class `FChaosVDTraceManagerThreadContext`  
`FChaosVDTraceManagerThreadContext : public TThreadSingleton<FChaosVDTraceManagerThreadContext>`  
_L109-114_
- inherits: `TThreadSingleton<FChaosVDTraceManagerThreadContext>`
- L113 _public member_ `TWeakPtr<FChaosVDRecording> PendingExternalRecordingWeakPtr;`

#### class `FChaosVDTraceManager`  
`class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FTraceSessionsManager instead") FChaosVDTraceManager : public TThreadSingleton<FChaosVDTraceManagerThreadContext>`  
_L116-235_
- inherits: `TThreadSingleton<FChaosVDTraceManagerThreadContext>`
- L119 _public prototype_ `FChaosVDTraceManager();`
- L120 _public prototype_ `~FChaosVDTraceManager();`
- L125 _public function_ `FString LoadTraceFile(const FString& InTraceFilename, const TSharedPtr<FChaosVDRecording>& ExistingRecordingPtr = nullptr)` — Load a trace file and starts analyzing it @param InTraceFilename File Name including (Path Included) of the Trace file to load
- L130 _public function_ `FString LoadTraceFile(TUniquePtr<IFileHandle>&& InFileHandle, const FString& InTraceSessionName, const TSharedPtr<FChaosVDRecording>& ExistingRecordingPtr)`
- L142 _public function_ `FString ConnectToLiveSession(FStringView InSessionHost, uint32 SessionID, const TSharedPtr<FChaosVDRecording>& ExistingRecordingPtr = nullptr)` — Connects to a live Trace Session and starts analyzing it. @param InSessionHost Trace Store Address for this session @param SessionID Trace ID in the Trace Store provided as host @param ExistingRecordingPtr Ptr to an existing recording instance to append the new CVD data to, if any @return Session Name
- L148 _public function_ `FString ConnectToLiveSession_Direct( uint16& OutSessionPort, const TSharedPtr<FChaosVDRecording>& ExistingRecordingPtr = nullptr)` — `UE_DEPRECATED(5.8, "Please use the version that takes a Remote Session ID")`
- L160 _public function_ `FString ConnectToLiveSession_Direct(FGuid RemoteSessionID, uint16& OutSessionPort, const TSharedPtr<FChaosVDRecording>& ExistingRecordingPtr = nullptr)` — Opens up a direct trace stream and waits for data @param RemoteSessionID Session ID to which we want to connect to @param OutSessionPort Number of the port we open for this session @param ExistingRecordingPtr Ptr to an existing recording instance to append the new CVD data to, if any @return Session Name
- L171 _public function_ `FString ConnectToLiveSession_Relay(FGuid RemoteSessionID, const TSharedPtr<FChaosVDRecording>& ExistingRecordingPtr = nullptr)` — Opens up a relay trace stream and waits for data @param RemoteSessionID Session ID to which we want to connect to @param ExistingRecordingPtr Ptr to an existing recording instance to append the new CVD data to, if any @return Session Name
- L177 _public function_ `FString GetLocalTraceStoreDirPath()` — Returns the path to the local trace store
- L183 _public function_ `TSharedPtr<const TraceServices::IAnalysisSession> GetSession(const FString& InSessionName)` — Returns a ptr to the session registered with the provided session name. Null if no session is found
- L189 _public function_ `void CloseSession(const FString& InSessionName)` — Stops and de-registers a trace session registered with the provided session name
- L194 _public function_ `void StopSession(const FString& InSessionName)` — Stops a trace session registered with the provided session name
- L199 _public function_ `template<typename TVisitor> static void EnumerateActiveSessions(FStringView InSessionHost, TVisitor Callback)`
- L204 _public function_ `static const UE::Trace::FStoreClient::FSessionInfo* GetTraceSessionInfo(FStringView InSessionHost, FGuid TraceGuid)`
- L210 _public function_ `template<typename TVisitor> void EnumerateActiveSessions(TVisitor Callback)`
- L220 _public function_ `FString GetTraceFileNameFromStoreForSession(FStringView InSessionHost, uint32 SessionID)` — Access the trace store at the provided host address, and returns the file name for the trace file @param InSessionHost Address of the Trace Store @param SessionID Session id of the trace data from which get the file name from @return Full Filename with path to the trace file if exist. Returns an empty string if a trace file cannot be found
- L229 _public function_ `UE::Trace::FStoreClient::FTraceData GetTraceDataStreamFromStore(FStringView InSessionHost, uint32 SessionID)` — Access the trace store at the provided host address, and returns a trace data stream ready to use @param InSessionHost Address of the Trace Store @param SessionID Session id of the trace data
- L234 _public prototype_ `static FString GetDefaultSaveDirectoryPath();`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace TraceServices`
- L20 _namespace_ `namespace Chaos`
- L20 _namespace_ `namespace VD` (scope `Chaos`)
- L91 _function_ `friend bool operator==(const FChaosVDTraceSessionDescriptor& Lhs, const FChaosVDTraceSessionDescriptor& RHS)`
- L97 _function_ `friend bool operator!=(const FChaosVDTraceSessionDescriptor& Lhs, const FChaosVDTraceSessionDescriptor& RHS)`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Trace/ChaosVDTraceProvider.h` (Public)


#### enum `EChaosVDSolverStageAccessorFlags`  
`enum class EChaosVDSolverStageAccessorFlags : uint8`  
_L29-36_
- desc: Set of flags that control how a solver stage is accessed
- L31 _public enumerator_ `None = 0`
- L33 _public enumerator_ `CreateNewIfClosed = 1 << 0` — If the solver frame has valid stage data but the last stage is closed, create a new stage which will be labeled as non-staged data
- L35 _public enumerator_ `CreateNewIfEmpty = 1 << 1` — If the solver frame does not have any solver stage data, create a new stage which will be labeled as non-staged data

#### class `FChaosVDTraceProvider`  
`class FChaosVDTraceProvider : public TraceServices::IProvider, public TraceServices::IEditableProvider, public TSharedFromThis<FChaosVDTraceProvider>`  
_L43-278_
- inherits: `TraceServices::IProvider,TraceServices::IEditableProvider,TSharedFromThis<FChaosVDTraceProvider>`
- desc: Provider class for Chaos VD trace recordings. It stores and handles rebuilt recorded frame data from Trace events dispatched by the Chaos VD Trace analyzer
- L47 _public member_ `static FName ProviderName;`
- L49 _public prototype_ `FChaosVDTraceProvider(TraceServices::IAnalysisSession& InSession);`
- L54 _public prototype_ `void CreateRecordingInstanceForSession(const FString& InSessionName);` — Creates a CVD recording instances where all the data loaded from the Trace Analisis session will be stored @param InSessionName Trace session name
- L56 _public prototype_ `void SetExternalRecordingInstanceForSession(const TSharedRef<FChaosVDRecording>& InExternalCVDRecording);`
- L62 _public prototype_ `void StartSolverFrame(const int32 InSolverGUID, FChaosVDSolverFrameData&& FrameData);` — Opens a solver frame entry into the active CVD recording structure @param InSolverGUID ID of the solver @param FrameData Solver frame data
- L67 _public prototype_ `void StartGameFrame(const TSharedPtr<FChaosVDGameFrameData>& InFrameData);` — Opens a game thread frame entry into the active CVD recording structure @param InFrameData Solver frame data
- L72 _public prototype_ `FChaosVDSolverFrameData* GetCurrentSolverFrame(const int32 InSolverGUID);` — Returns the current solver frame instance that is open and accepting data @param InSolverGUID ID of the solver
- L75 _public prototype_ `TWeakPtr<FChaosVDGameFrameData> GetCurrentGameFrame();` — Returns the game thread frame instance that is open and accepting data
- L78 _public prototype_ `TSharedPtr<FChaosVDRecording> GetRecordingForSession() const;` — Returns the active CVD recording instance
- L83 _public prototype_ `void RegisterDataProcessor(TSharedPtr<FChaosVDDataProcessorBase> InDataProcessor);` — Registers a CVD data processors. These are used to process raw serialized data from CVD's or custom user extensions @param InDataProcessor Shared ptr to the CVD Data processor we want to register
- L89 _public prototype_ `FChaosVDFrameStageData* GetCurrentSolverStageDataForCurrentFrame(int32 SolverID, EChaosVDSolverStageAccessorFlags Flags);` — Returns the current open solver stage data for the provided solver ID @param SolverID ID of the solver @param Flags Indicating what to do if no solver stage is available
- L108 _private function_ `TMap<int32,int32>& GetCurrentTickOffsetsBySolverID()`
- L113 _private prototype_ `void HandleAnalysisComplete();`
- L116 _private prototype_ `void ShowSafeModeSkippedDialog();` — Shows a Slate dialog listing data types skipped because Safe Loading Mode was active.
- L119 _private prototype_ `void ShowUnsafeDataDialog();` — Shows a Slate dialog warning that non-backwards-compatible types were loaded with Safe Loading Mode disabled.
- L123 _private prototype_ `void ShowNativeSerializationDialog();` — Shows a Slate dialog warning that natively-serialized particle extra data entries are present, and lets the user choose whether to display them or skip them.
- L127 _private prototype_ `void ShowSerializeBinOnlyStrippedDialog();` — Shows a Slate dialog informing the user that natively-serialized particle extra data entries were stripped because Particle Extra Data Loading Mode is set to SerializeBin Only.
- L129 _private prototype_ `FBinaryDataContainer& FindOrAddUnprocessedData(const int32 DataID);`
- L130 _private prototype_ `void RemoveUnprocessedData(const int32 DataID);`
- L132 _private prototype_ `bool ProcessBinaryData(const int32 DataID);`
- L134 _private prototype_ `void DeleteRecordingInstanceForSession();`
- L136 _private prototype_ `void RegisterDefaultDataProcessorsIfNeeded();`
- L138 _private prototype_ `void EnqueueGameFrameForProcessing(const TSharedPtr<FChaosVDGameFrameData>& FrameData);`
- L139 _private prototype_ `void DeQueueGameFrameForProcessing(TSharedPtr<FChaosVDGameFrameData>& OutFrameData);`
- L141 _private prototype_ `void CommitProcessedGameFramesToRecording();`
- L144 _private prototype_ `void GetAvailablePendingSolverIDsAtGameFrame(const TSharedRef<FChaosVDGameFrameData>& InProcessedGameFrameData, TArray<int32, TInlineAllocator<16>>& OutSolverIDs);` — Gathers any solver id from solver data that is not fully processed yet but that will be valid for the provided game frame data later on
- L148 _public prototype_ `FString GenerateFormattedStringListFromSet(const TSet<FString>& StringsSet) const;`
- L150 _public prototype_ `int32 RemapSolverID(int32 SolverID);`
- L152 _public function_ `virtual void BeginEdit() const override`
- L153 _public function_ `virtual void EndEdit() const override`
- L154 _public function_ `virtual void EditAccessCheck() const override`
- L156 _public prototype_ `int32 GetRemappedSolverID(int32 SolverID);`
- L158 _public function_ `bool DoesOwnRecordingInstance() const`
- L164 _public function_ `TSharedPtr<Chaos::VisualDebugger::FChaosVDSerializableNameTable> GetNameTableInstance() const` — Returns the name table instances used to de-duplicate strings serialization
- L170 _public function_ `const Chaos::VisualDebugger::FChaosVDArchiveHeader& GetHeaderData() const` — Returns the FArchive header used to read the serialized binary data
- L176 _public function_ `void SetHeaderData(Chaos::VisualDebugger::FChaosVDArchiveHeader& InNewHeader)` — Sets the FArchive header used to read the serialized binary data
- L182 _public function_ `int64 GetDataProcessedSoFarNum() const` — Returns how many pieces of data we processed so far with a data processor (even if it failed)
- L187 _public function_ `const TSet<FString>& GetTypesFailedToSerialize() const`
- L193 _public function_ `const TSet<FString>& GetTypesSkippedInSafeMode() const` — Types whose data was skipped entirely because Safe Loading Mode was enabled and they are not backwards compatible.
- L199 _public function_ `const TSet<FString>& GetUnsafeTypesProcessed() const` — Types that were processed despite not being backwards compatible (Safe Loading Mode was off).
- L204 _public prototype_ `void AddParticleMetadata(uint64 MetadaId, const TSharedPtr<FChaosVDParticleMetadata>& InMetadata);`
- L205 _public prototype_ `TSharedPtr<FChaosVDParticleMetadata> GetParticleMetadata(uint64 MetadataId);`
- L207 _public prototype_ `void CreateGeometryArchiveContext();`
- L209 _public function_ `TSharedPtr<Chaos::FChaosArchiveContext> GetGeometryArchiveContext()`
- L216 _private function_ `int32 GetCurrentGameThreadTrackID() const`
- L221 _private function_ `void SetCurrentGameThreadTrackID(int32 NewID)`
- L226 _private member_ `Chaos::VisualDebugger::FChaosVDArchiveHeader HeaderData;`
- L228 _private member_ `TSharedPtr<Chaos::VisualDebugger::FChaosVDSerializableNameTable> NameTable;`
- L230 _private member_ `TraceServices::IAnalysisSession& Session;`
- L232 _private member_ `TSharedPtr<FChaosVDRecording> InternalRecording;`
- L234 _private member_ `TMap<int32, TSharedPtr<FBinaryDataContainer>> UnprocessedDataByID;`
- L236 _private member_ `TMap<FStringView, TSharedPtr<FChaosVDDataProcessorBase>> RegisteredDataProcessors;`
- L238 _private member_ `TMap<int32, FChaosVDSolverFrameData> CurrentSolverFramesByID;`
- L240 _private member_ `TQueue<TSharedPtr<FChaosVDGameFrameData>> CurrentGameFrameQueue;`
- L242 _private member_ `TWeakPtr<FChaosVDGameFrameData> CurrentGameFrame = nullptr;`
- L244 _private member_ `TUniquePtr<Chaos::VisualDebugger::FChaosVDArchiveHeader> CurrentHeaderData;`
- L246 _private member_ `int32 CurrentGameFrameQueueSize = 0;`
- L248 _private member_ `bool bDefaultDataProcessorsRegistered = false;`
- L250 _private member_ `double StartLastCommitedFrameTimeSeconds = 0.0;`
- L252 _private member_ `bool bHasRecordingOverride = false;`
- L254 _private member_ `TMap<int32, int32> CurrentNetworkTickOffsets;`
- L255 _private member_ `TSortedMap<int32, int32> RemappedSolversIDs;`
- L257 _private member_ `int32 RemappedGameThreadTrackID = INDEX_NONE;`
- L259 _private member_ `TSet<FString> MissingDataProcessors;`
- L260 _private member_ `TSet<FString> TypesFailedToSerialize;`
- L261 _private member_ `TSet<FString> TypesSkippedInSafeMode;`
- L262 _private member_ `TSet<FString> UnsafeTypesProcessed;`
- L264 _private member_ `int64 DataProcessedSoFarCounter = 0;`
- L266 _private member_ `bool bShouldTrimOutStartEmptyFrames = false;`
- L267 _private member_ `int32 MaxGameFramesToQueueNum = 10;`
- L269 _private member_ `TMap<uint64, TSharedPtr<FChaosVDParticleMetadata>> SerializedParticleMetadata;`
- L271 _private member_ `TSharedPtr<Chaos::FChaosArchiveContext> GeometryArchiveContext;`

#### struct `FChaosVDTraceProvider::FBinaryDataContainer`  
`struct FBinaryDataContainer`  
_L93-106_
- L95 _public function_ `explicit FBinaryDataContainer(const int32 InDataID) : DataID(InDataID)`
- L100 _public member_ `int32 DataID;`
- L101 _public member_ `bool bIsReady = false;`
- L102 _public member_ `bool bIsCompressed = false;`
- L103 _public member_ `uint32 UncompressedSize = 0;`
- L104 _public member_ `FString TypeName;`
- L105 _public member_ `TArray<uint8> RawData;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`
- L20 _namespace_ `namespace Chaos`
- L20 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L37 _prototype_ `ENUM_CLASS_FLAGS(EChaosVDSolverStageAccessorFlags);`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Trace/DataProcessors/ChaosVDDataProcessorBase.h` (Public)


#### class `FChaosVDDataProcessorBase`  
`class FChaosVDDataProcessorBase`  
_L74-128_
- desc: Abstract base class that should be used for any class that is able to process traced Chaos Visual Debugger binary data
- L78 _public function_ `explicit FChaosVDDataProcessorBase(FStringView InCompatibleType) : TraceProvider(nullptr), CompatibleType(InCompatibleType), ProcessedBytes(0)`
- L82 _public prototype_ `virtual ~FChaosVDDataProcessorBase() = 0;`
- L85 _public prototype_ `FStringView GetCompatibleTypeName() const;` — Type name this data processor can interpret
- L88 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData);` — Called with the raw serialized data to be processed
- L91 _public prototype_ `uint64 GetProcessedBytes() const;` — Returns the amount of data in bytes processed by this data processor at the moment of being called
- L94 _public prototype_ `void SetTraceProvider(const TSharedPtr<FChaosVDTraceProvider>& InProvider);` — Sets the Trace Provider that is storing the data being analyzed
- L99 _public function_ `virtual void GetPostLoadNativeTypesWithChannels(TMap<FName, FName>& OutTypeToChannel) const` — Returns natively-serialized struct types encountered during ProcessRawData, mapped to the CVD optional data channel they were traced through (NAME_None if unknown). Used by the post-load NativeSerialization warning dialog.
- L111 _public function_ `virtual bool IsBackwardsCompatible() const` — Returns true if this processor's data format is backwards compatible, meaning it uses UE's property system or explicit version fields that allow graceful forward/backward reading. Processors that serialise raw binary struct layouts (no versioning) must set bBackwardsCompatible = false in their constructor. When Safe Loading Mode is enabled in CVD General Settings, the trace provider will skip those processors entirely rather than risk a crash on a format mismatch.
- L115 _public function_ `virtual bool ShouldAlwaysSkip() const` — When true, the provider skips this processor silently regardless of bSafeLoadingMode. Use when the processor has its own loading-mode control (e.g. EChaosVDParticleExtraDataLoadingMode).
- L118 _protected member_ `TWeakPtr<FChaosVDTraceProvider> TraceProvider;`
- L119 _protected member_ `FStringView CompatibleType;`
- L120 _protected member_ `uint64 ProcessedBytes;`
- L127 _protected member_ `bool bBackwardsCompatible = true;` — Set to false in the constructor of any derived processor whose serialised format is not guaranteed to be stable across engine versions or local source changes. Defaults to true so existing processors are unaffected until explicitly opted out.

#### class `FChaosVDGenericDataProcessor`  
`class FChaosVDGenericDataProcessor : FChaosVDDataProcessorBase`  
_L130-140_
- inherits: `FChaosVDDataProcessorBase`
- L134 _public prototype_ `explicit FChaosVDGenericDataProcessor(FStringView InCompatibleType, const TFunction<bool(const TArray<uint8>&)>& InProcessDataCallback);`
- L136 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`
- L139 _private member_ `TFunction<bool(const TArray<uint8>&)> ProcessDataCallback;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace Chaos`
- L23 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L26 _function_ `template<typename TArchive> void ApplyHeaderDataToArchive(TArchive& InOutArchive, const FChaosVDArchiveHeader& InRecordedHeader)` (scope `Chaos::VisualDebugger`)
- L34 _function_ `template<typename TDataToSerialize> bool ReadDataFromBuffer(const TArray<uint8>& InDataBuffer, TDataToSerialize& Data, const TSharedRef<FChaosVDTraceProvider>& DataProvider)` (scope `Chaos::VisualDebugger`)

### `Plugins/ChaosVD/Source/ChaosVD/Public/Trace/DataProcessors/ChaosVDParticleExtraDataProcessor.h` (Public)


#### class `FChaosVDParticleExtraDataProcessor`  
`class FChaosVDParticleExtraDataProcessor final : public FChaosVDDataProcessorBase`  
_L14-31_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor that deserializes traced FChaosVDParticleExtraData payloads and stores them in FChaosVDParticleExtraDataContainer inside the solver frame's custom data.
- L17 _public prototype_ `explicit FChaosVDParticleExtraDataProcessor();`
- L18 _public prototype_ `~FChaosVDParticleExtraDataProcessor();`
- L20 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`
- L22 _public prototype_ `virtual bool ShouldAlwaysSkip() const override;`
- L23 _public prototype_ `virtual bool IsBackwardsCompatible() const override;`
- L24 _public prototype_ `virtual void GetPostLoadNativeTypesWithChannels(TMap<FName, FName>& OutTypeToChannel) const override;`
- L27 _private prototype_ `void HandleSettingsChanged(UObject* InSettings);`
- L29 _private member_ `TMap<FName, FName> NativeTypesToChannel;`
- L30 _private member_ `EChaosVDParticleExtraDataLoadingMode CachedLoadingMode;`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Utils/ChaosVDUserInterfaceUtils.h` (Public)


#### enum `Chaos::VisualDebugger::Utils::EChaosVDSaveSettingsOptions`  
`enum class EChaosVDSaveSettingsOptions`  
_L42-47_
- L44 _public enumerator_ `None = 0`
- L45 _public enumerator_ `ShowSaveButton = 1 << 0`
- L46 _public enumerator_ `ShowResetButton = 1 << 1`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`
- L13 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L13 _namespace_ `namespace Utils` (scope `Chaos::VisualDebugger`)
- L15 _prototype_ `TSharedRef<IStructureDetailsView> MakeStructDetailsViewForMenu();` (scope `Chaos::VisualDebugger::Utils`)
- L17 _prototype_ `TSharedRef<IDetailsView> MakeObjectDetailsViewForMenu();` (scope `Chaos::VisualDebugger::Utils`)
- L20 _function_ `template <typename EnumType> TSharedRef<SWidget> MakeEnumMenuEntryWidget(const FText& MenuEntryLabel, const SEnumComboBox::FOnEnumSelectionChanged&& EnumValueChanged, const TAttribute<int32>&& CurrentValueAttribute)` (scope `Chaos::VisualDebugger::Utils`)
- L48 _prototype_ `ENUM_CLASS_FLAGS(EChaosVDSaveSettingsOptions) void CreateMenuEntryForObject(UToolMenu* Menu, UObject* Object, EChaosVDSaveSettingsOptions MenuEntryOptions = EChaosVDSaveSettingsOptions::None);` (scope `Chaos::VisualDebugger::Utils`)
- L53 _function_ `template <typename Object> void CreateMenuEntryForSettingsObject(UToolMenu* Menu, EChaosVDSaveSettingsOptions MenuEntryOptions = EChaosVDSaveSettingsOptions::None)` (scope `Chaos::VisualDebugger::Utils`)
- L59 _function_ `template <typename TStruct> void SetStructToDetailsView(TStruct* NewStruct, TSharedRef<IStructureDetailsView>& InDetailsView)` (scope `Chaos::VisualDebugger::Utils`)
- L72 _function_ `template <typename ObjectSettingsType, typename VisualizationFlagsType> bool ShouldSettingsObjectVisFlagBeEnabledInUI(VisualizationFlagsType Flag)` (scope `Chaos::VisualDebugger::Utils`)
- L83 _function_ `template <typename ObjectSettingsType, typename VisualizationFlagsType> void CreateVisualizationOptionsMenuSections(UToolMenu* Menu, FName SectionName, const FText& InSectionLabel, const FText& InFlagsMenuLabel, const FText& InFlagsMenuTooltip, FSlateIcon FlagsMenuIcon, const FText& InSettingsMenuLabel, const FText& InSettingsMenuTooltip)` (scope `Chaos::VisualDebugger::Utils`)
- L88 _function_ `` (scope `Chaos::VisualDebugger::Utils::CreateVisualizationOptionsMenuSections`)
- L111 _function_ `template<typename VisFlagsType> bool ShouldVisFlagBeEnabledInUI(uint32 FlagToEvaluate, uint32 CurrentFlags, VisFlagsType EnableDrawFlags)` (scope `Chaos::VisualDebugger::Utils`) — Evaluates a flag and determines if it should be considered enabled in the UI, based on the provided current active flags and the general enable draw flags @tparam VisFlagsType Type of the enum visualization flags @return true if the flag should be enabled in the UI

### `Plugins/ChaosVD/Source/ChaosVD/Public/Visualizers/ChaosVDComponentVisualizerBase.h` (Public)


#### struct `FChaosVDVisualizationContext`  
`struct FChaosVDVisualizationContext`  
_L25-33_
- desc: Context needed to be able to visualize data in the viewport
- L27 _public member_ `FTransform SpaceTransform;`
- L28 _public member_ `TWeakPtr<FChaosVDScene> CVDScene;`
- L29 _public member_ `int32 SolverID = INDEX_NONE;`
- L30 _public member_ `uint32 VisualizationFlags = 0;`
- L31 _public member_ `const UChaosVDSettingsObjectBase* DebugDrawSettings = nullptr;`
- L32 _public member_ `TSharedPtr<FChaosVDSolverDataSelection> SolverDataSelectionObject = nullptr;`

#### struct `HChaosVDComponentVisProxy`  
`struct HChaosVDComponentVisProxy : public HComponentVisProxy`  
_L36-51_
- inherits: `HComponentVisProxy`
- desc: Custom Hit Proxy for debug drawn particle data
- L40 _public function_ `HChaosVDComponentVisProxy(const UActorComponent* InComponent, const TSharedPtr<FChaosVDSolverDataSelectionHandle>& InDataSelectionHandle) : HComponentVisProxy(InComponent), DataSelectionHandle(InDataSelectionHandle)`
- L45 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`
- L50 _public member_ `TSharedPtr<FChaosVDSolverDataSelectionHandle> DataSelectionHandle;`

#### class `FChaosVDComponentVisualizerBase`  
`class FChaosVDComponentVisualizerBase : public FComponentVisualizer`  
_L56-98_
- inherits: `FComponentVisualizer`
- desc: Base class used for all component visualizers in CVD - It provides a common code to handle selection and clicks @note Not all functionality of UE's component visualizer framework is supported in CVD
- L65 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click) override;` — Handles a click to any CVD componentvisualization hit proxy @param InViewportClient Viewport Client where the click happened @param VisProxy Hit proxy clicked @param Click Click data
- L72 _protected prototype_ `virtual void RegisterVisualizerMenus() = 0;` — Called when the menu for this visualizer (if any) can be registered. And does so if implemented. This needs to be manually called in the constructor of ech visualizer
- L76 _protected prototype_ `virtual bool CanHandleClick(const HChaosVDComponentVisProxy& VisProxy);` — Returns true if this visualizer can handle a click in the viewport
- L83 _protected prototype_ `virtual bool SelectVisualizedData(const HChaosVDComponentVisProxy& VisProxy, const TSharedRef<FChaosVDScene>& InCVDScene,const TSharedRef<SChaosVDMainTab>& InMainTabToolkitHost);` — Selects the visualized data referenced by the provided hitproxy @param VisProxy HitProxy referencing the data to select @param InCVDScene RefPtr to CVD's Main Scene @param InMainTabToolkitHost RefPtr to CVD's Main tab (which is also the Editor Toolkit Host)
- L95 _protected prototype_ `template<typename ObjectSettingsType, typename VisualizationFlagsType> void CreateGenericVisualizerMenu(FName MenuToExtend, FName SectionName, const FText& InSectionLabel, const FText& InFlagsMenuLabel, const FText& InFlagsMenuTooltip, FSlateIcon FlagsMenuIcon, const FText& InSettingsMenuLabel, const FText& InSettingsMenuTooltip);` — Creates a menu entry for this visualizer data, as long it is using the supporting settings format and types for visualizers @param MenuToExtend Name of the menu will be extension @param SectionName Name of the section for this menu @param InFlagsMenuLabel Label to use for the submenu created to the visualization flags of this visualizer @param InFlagsMenuTooltip Tooltip to use for the submenu created to the visualization flags of this visualizer @param FlagsMenuIcon Icon to use for the submenu created to the visualization flags of this visualizer @param InSettingsMenuLabel Label to use for the submenu created to the visualization settings of this visualizer @param InSettingsMenuTooltip Tooltip to use for the submenu created to the visualization settings of this visualizer
- L97 _protected member_ `FName InspectorTabID = NAME_None;`
- L101 _function_ `template <typename ObjectSettingsType, typename VisualizationFlagsType> void FChaosVDComponentVisualizerBase::CreateGenericVisualizerMenu(FName MenuToExtend, FName SectionName, const FText& InSectionLabel, const FText& InFlagsMenuLabel, const FText& InFlagsMenuTooltip, FSlateIcon FlagsMenuIcon, const FText& InSettingsMenuLabel, const FText& InSettingsMenuTooltip)`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CHAOSVD_API`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Visualizers/ChaosVDDebugDrawUtils.h` (Public)


#### enum `EChaosVDDebugDrawTextLocationMode`  
`enum class EChaosVDDebugDrawTextLocationMode`  
_L17-21_
- L19 _public enumerator_ `World`
- L20 _public enumerator_ `Screen`

#### class `FChaosVDDebugDrawUtils`  
`class FChaosVDDebugDrawUtils`  
_L24-66_
- desc: Utility methods that allows Debug draw into the Chaos VD Editor
- L29 _public prototype_ `static void DrawArrowVector(FPrimitiveDrawInterface* PDI, const FVector& StartLocation, const FVector& EndLocation, const FText& InDebugText, const FColor& Color, ESceneDepthPriorityGroup DepthPriority = SDPG_World, float Thickness = 0.0f);`
- L30 _public prototype_ `static void DrawPoint(FPrimitiveDrawInterface* PDI, const FVector& Location, const FText& InDebugText, const FColor& Color, float Size = 10.0f, ESceneDepthPriorityGroup DepthPriority = SDPG_World);`
- L31 _public prototype_ `static void DrawString(FStringView StringToDraw, const FVector& Location, const FColor& Color, EChaosVDDebugDrawTextLocationMode LocationMode = EChaosVDDebugDrawTextLocationMode::World);`
- L32 _public prototype_ `static void DrawText(const FText& InText, const FVector& Location, const FColor& Color, EChaosVDDebugDrawTextLocationMode LocationMode = EChaosVDDebugDrawTextLocationMode::World);`
- L33 _public prototype_ `static void DrawOnScreenWarning(const FText& InText, const FColor& Color);`
- L34 _public prototype_ `static void DrawCircle(FPrimitiveDrawInterface* PDI, const FVector& Origin, float Radius, int32 Segments, const FColor& Color, float Thickness, const FVector& XAxis, const FVector& YAxis, const FText& InDebugText, ESceneDepthPriorityGroup DepthPriority = SDPG_World);`
- L35 _public prototype_ `static void DrawBox(FPrimitiveDrawInterface* PDI, const FVector& InExtents, const FColor& InColor, const FTransform& InTransform, const FText& InDebugText, ESceneDepthPriorityGroup DepthPriority = SDPG_World, float Thickness = 2.0f);`
- L36 _public prototype_ `static void DrawLine(FPrimitiveDrawInterface* PDI, const FVector& InStartPosition, const FVector& InEndPosition, const FColor& InColor, const FText& InDebugText, ESceneDepthPriorityGroup DepthPriority = SDPG_World, float Thickness = 2.0f);`
- L37 _public prototype_ `static void DrawImplicitObject(FPrimitiveDrawInterface* PDI, const TSharedPtr<FChaosVDGeometryBuilder>& GeometryGenerator, const Chaos::FConstImplicitObjectPtr& ImplicitObject, const FTransform& InWorldTransform, const FColor& InColor, const FText& InDebugText, ESceneDepthPriorityGroup DepthPriority = SDPG_World, float Thickness = 2.0f);`
- L39 _public prototype_ `static void DrawSphere(FPrimitiveDrawInterface* PDI, const FVector& Center, float Radius, int32 Segments, const FColor& InColor, const FText& InDebugText, ESceneDepthPriorityGroup DepthPriority = SDPG_World, float Thickness = 2.0f);`
- L41 _public prototype_ `static void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas);`
- L43 _public prototype_ `static bool CanDebugDraw();`
- L45 _public member_ `static int32 MaxLinesToDrawPerFrame;`
- L56 _private prototype_ `static void DebugDrawFrameEnd();`
- L57 _private prototype_ `static void IncreaseDebugDrawLineCounter();`
- L59 _private member_ `static TQueue<FChaosVDQueuedTextToDraw> TextToDrawQueue;`
- L61 _private member_ `static int32 CurrentLinesDrawn;`
- L62 _private member_ `static bool bIsShowingDebugDrawLimitWarning;`
- L63 _private member_ `static int32 CurrentWarningsBeingDrawn;`

#### struct `FChaosVDDebugDrawUtils::FChaosVDQueuedTextToDraw`  
`struct FChaosVDQueuedTextToDraw`  
_L48-54_
- L50 _public member_ `FText Text;`
- L51 _public member_ `EChaosVDDebugDrawTextLocationMode LocationMode;`
- L52 _public member_ `FVector Location;`
- L53 _public member_ `FLinearColor Color;`

#### Free symbols / members of external scopes

- L68 _namespace_ `namespace Chaos`
- L68 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L68 _namespace_ `namespace Utils` (scope `Chaos::VisualDebugger`)
- L70 _prototype_ `FString GenerateDebugTextForVector(const FVector& InVector, const FString& VectorName, const FString& InVectorUnits);` (scope `Chaos::VisualDebugger::Utils`)
- L72 _prototype_ `FBox CalculateSceneQueryShapeBounds(const TSharedRef<FChaosVDQueryDataWrapper>& InSceneQueryData, const TSharedRef<FChaosVDRecording> InRecordedData);` (scope `Chaos::VisualDebugger::Utils`)

### `Plugins/ChaosVD/Source/ChaosVD/Public/Visualizers/ChaosVDParticleDataComponentVisualizer.h` (Public)


#### struct `FChaosVDParticleDataVisualizationContext`  
`struct FChaosVDParticleDataVisualizationContext : public FChaosVDVisualizationContext`  
_L27-36_
- inherits: `FChaosVDVisualizationContext`
- L29 _public member_ `TWeakPtr<FChaosVDGeometryBuilder> GeometryGenerator = nullptr;`
- L30 _public member_ `bool bIsSelectedData = false;`
- L31 _public member_ `bool bShowDebugText = false;`
- L33 _public member_ `const UChaosVDParticleVisualizationDebugDrawSettings* DebugDrawSettings = nullptr;`
- L35 _public prototype_ `bool IsVisualizationFlagEnabled(EChaosVDParticleDataVisualizationFlags Flag) const;`

#### class `FChaosVDParticleDataComponentVisualizer`  
`class FChaosVDParticleDataComponentVisualizer : public FChaosVDComponentVisualizerBase`  
_L41-58_
- inherits: `FChaosVDComponentVisualizerBase`
- desc: Component visualizer in charge of generating debug draw visualizations for for particles
- L44 _public prototype_ `FChaosVDParticleDataComponentVisualizer();`
- L46 _public prototype_ `virtual void RegisterVisualizerMenus() override;`
- L48 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L50 _public prototype_ `virtual bool CanHandleClick(const HChaosVDComponentVisProxy& VisProxy) override;`
- L52 _public prototype_ `virtual bool SelectVisualizedData(const HChaosVDComponentVisProxy& VisProxy, const TSharedRef<FChaosVDScene>& InCVDScene, const TSharedRef<SChaosVDMainTab>& InMainTabToolkitHost) override;`
- L56 _protected prototype_ `void DrawParticleVector(FPrimitiveDrawInterface* PDI, const FVector& StartLocation, const FVector& InVector, EChaosVDParticleDataVisualizationFlags VectorID, const FChaosVDParticleDataVisualizationContext& InVisualizationContext, float LineThickness);`
- L57 _protected prototype_ `void DrawVisualizationForParticleData(const UActorComponent* Component, FPrimitiveDrawInterface* PDI, const FSceneView* View, const FChaosVDParticleDataVisualizationContext& InVisualizationContext, const FChaosVDSceneParticle& InParticleInstance);`

#### class `FChaosVDTrimeshBVHVisualizer`  
`class FChaosVDTrimeshBVHVisualizer`  
_L60-69_
- L63 _public prototype_ `void Draw(FPrimitiveDrawInterface* PDI, const FChaosVDParticleDataVisualizationContext& InVisualizationContext, const FTransform& LocalToWorldTransform, const Chaos::FTriangleMeshImplicitObject& TriMesh) const;`
- L65 _private prototype_ `void DrawBVH(FPrimitiveDrawInterface* PDI, const FTransform& LocalToWorldTransform, const Chaos::FTrimeshBVH& BVH, const int32 TargetLevel) const;`
- L66 _private prototype_ `void DrawBVHLevel(FPrimitiveDrawInterface* PDI, const FTransform& LocalToWorldTransform, const Chaos::FTrimeshBVH& BVH, const int32 NodeIndex, const int32 CurrentLevel, const int32 TargetLevel) const;`
- L67 _private prototype_ `void DrawAabb(FPrimitiveDrawInterface* PDI, const FTransform& LocalToWorldTransform, const Chaos::FAABB3& Aabb, const int32 ColorSeed) const;`
- L68 _private prototype_ `Chaos::FAABB3 ToAabb(const Chaos::FAABBVectorized& AabbVectorized) const;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Chaos`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Widgets/SChaosVDDetailsView.h` (Public)


#### class `SChaosVDDetailsView`  
`class SChaosVDDetailsView : public SCompoundWidget`  
_L24-61_
- inherits: `SCompoundWidget`
- desc: Simple details for CVD objects and structures
- L27 _public function_ `SLATE_BEGIN_ARGS(SChaosVDDetailsView)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SChaosVDMainTab>& InMainTab);`
- L36 _public prototype_ `void SetSelectedObject(UObject* NewObject);` — Updates the current object this view details is viewing
- L40 _public prototype_ `template<typename TStruct> void SetSelectedStruct(TStruct* NewStruct);` — Updates the current object this view details is viewing
- L42 _public prototype_ `void SetSelectedStruct(const TSharedPtr<FStructOnScope>& NewStruct);`
- L46 _protected prototype_ `TSharedPtr<IDetailsView> CreateObjectDetailsView();`
- L47 _protected prototype_ `TSharedPtr<IStructureDetailsView> CreateStructureDataDetailsView() const;`
- L49 _protected prototype_ `EVisibility GetStructDetailsVisibility() const;`
- L50 _protected prototype_ `EVisibility GetObjectDetailsVisibility() const;`
- L52 _protected member_ `TWeakObjectPtr<UObject> CurrentObjectInView;`
- L54 _protected member_ `TWeakPtr<FStructOnScope> CurrentStructInView;`
- L56 _protected member_ `TSharedPtr<IDetailsView> DetailsView;`
- L58 _protected member_ `TSharedPtr<IStructureDetailsView> StructDetailsView;`
- L60 _protected member_ `TWeakPtr<SChaosVDMainTab> MainTabWeakPtr;`
- L64 _function_ `template <typename TStruct> void SChaosVDDetailsView::SetSelectedStruct(TStruct* NewStruct)`

### `Plugins/ChaosVD/Source/ChaosVD/Public/Widgets/SChaosVDEnumFlagsMenu.h` (Public)


#### class `SChaosVDEnumFlagsMenu`  
`template<typename TEnum> class SChaosVDEnumFlagsMenu : public SCompoundWidget`  
_L15-57_
- inherits: `SCompoundWidget`
- desc: Simple widget that allows that created a checkbox style menu for enum flags
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnEnumSelectionChanged, TEnum);`
- L20 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsEnumValueEnabled, TEnum);`
- L33 _public function_ `SLATE_BEGIN_ARGS(SChaosVDEnumFlagsMenu) : _CurrentValue()`
- L37 _public prototype_ `SLATE_ATTRIBUTE(TEnum, CurrentValue) SLATE_EVENT(FOnEnumSelectionChanged, OnEnumSelectionChanged) SLATE_EVENT(FIsEnumValueEnabled, IsFlagEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L46 _public prototype_ `void UpdateEnumFlagValue(FEnumInfo FlagInfo);`
- L47 _public prototype_ `bool IsEnumFlagSet(FEnumInfo FlagInfo) const;`
- L49 _public prototype_ `bool IsEnumFlagEnabled(TEnum FlagValue) const;`
- L51 _public member_ `TAttribute<TEnum> CurrentValue;`
- L53 _public member_ `FOnEnumSelectionChanged OnEnumSelectionChangedDelegate;`
- L54 _public member_ `FIsEnumValueEnabled EnumValueEnabledDelegate;`
- L56 _public member_ `const UEnum* Enum = nullptr;`
- L70 _function_ `template <typename TEnum> void SChaosVDEnumFlagsMenu<TEnum>::Construct(const FArguments& InArgs)`
- L145 _function_ `template <typename TEnum> void SChaosVDEnumFlagsMenu<TEnum>::UpdateEnumFlagValue(FEnumInfo FlagInfo)`
- L154 _function_ `template <typename TEnum> bool SChaosVDEnumFlagsMenu<TEnum>::IsEnumFlagSet(FEnumInfo FlagInfo) const`
- L160 _function_ `template <typename TEnum> bool SChaosVDEnumFlagsMenu<TEnum>::IsEnumFlagEnabled(TEnum FlagValue) const`

#### struct `SChaosVDEnumFlagsMenu::FEnumInfo`  
`struct FEnumInfo`  
_L21-31_
- L23 _public function_ `explicit FEnumInfo(const int32 InIndex, const TEnum InValue, const FText& InDisplayName, const FText& InTooltipText) : Index(InIndex), Value(InValue), DisplayName(InDisplayName), TooltipText(InTooltipText)`
- L27 _public member_ `int32 Index = 0;`
- L28 _public member_ `TEnum Value;`
- L29 _public member_ `FText DisplayName;`
- L30 _public member_ `FText TooltipText;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEnumSelectionChanged, TEnum);`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsEnumValueEnabled, TEnum);`
- L59 _namespace_ `namespace Chaos`
- L59 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L59 _namespace_ `namespace Utils` (scope `Chaos::VisualDebugger`)
- L62 _function_ `template<typename Enum> void EnumAddToggleFlag(Enum& Flags, Enum Flag)` (scope `Chaos::VisualDebugger::Utils`)
- L64 _typedef_ `using UnderlyingType = __underlying_type(Enum);` (scope `Chaos::VisualDebugger::Utils::EnumAddToggleFlag`)

### `Plugins/ChaosVD/Source/ChaosVD/Public/Widgets/SChaosVDMainTab.h` (Public)


#### class `UChaosVDMainToolbarMenuContext`  
`class UChaosVDMainToolbarMenuContext : public UObject`  
_L42-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L48 _public member_ `TWeakPtr<class SChaosVDMainTab> MainTab;`

#### class `SChaosVDMainTab`  
`class SChaosVDMainTab : public SCompoundWidget, public IToolkitHost`  
_L52-266_
- inherits: `SCompoundWidget,IToolkitHost`
- desc: The main widget containing the Chaos Visual Debugger interface
- L56 _public function_ `SLATE_BEGIN_ARGS(SChaosVDMainTab)`
- L57 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, OwnerTab) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FChaosVDEngine> InChaosVDEngine);`
- L64 _public prototype_ `void BindUICommands(const TSharedRef<FUICommandList>& InGlobalUICommandsRef);`
- L66 _public function_ `TSharedRef<FChaosVDEngine> GetChaosVDEngineInstance() const`
- L71 _public prototype_ `TSharedPtr<FChaosVDScene> GetScene();`
- L74 _public prototype_ `template<typename TabType> TWeakPtr<TabType> GetTabSpawnerInstance(FName TabID);`
- L77 _public function_ `virtual TSharedRef<SWidget> GetParentWidget() override` — BEGIN ITOOLKITHOST Interface
- L82 _public prototype_ `virtual void BringToFront() override;`
- L83 _public function_ `virtual TSharedPtr<FTabManager> GetTabManager() const override`
- L87 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L88 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L89 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L90 _public prototype_ `virtual FEditorModeTools& GetEditorModeManager() const override;`
- L92 _public function_ `virtual UTypedElementCommonActions* GetCommonActions() const override`
- L96 _public function_ `virtual FName GetStatusBarName() const override`
- L97 _public function_ `virtual FOnActiveViewportChanged& OnActiveViewportChanged() override`
- L103 _public prototype_ `TSharedPtr<FComponentVisualizer> FindComponentVisualizer(UClass* ClassPtr);`
- L104 _public prototype_ `TSharedPtr<FComponentVisualizer> FindComponentVisualizer(FName ClassName);`
- L106 _public function_ `TConstArrayView<TSharedPtr<FComponentVisualizer>> GetAllComponentVisualizers()`
- L112 _public prototype_ `bool ConnectToLiveSession(int32 SessionID, const FString& InSessionAddress, EChaosVDLoadRecordedDataMode LoadingMode) const;` — Connects to a live session using via the Unreal Trace Server and its Trace Store. This is a legacy option
- L115 _public prototype_ `bool ConnectToLiveSession_Direct(EChaosVDLoadRecordedDataMode LoadingMode) const;` — `UE_DEPRECATED(5.8, "Use the version that takes a Remote session ID")`
- L117 _public prototype_ `bool ConnectToLiveSession_Direct(FGuid RemoteSessionID, EChaosVDLoadRecordedDataMode LoadingMode) const;`
- L119 _public prototype_ `bool ConnectToLiveSession_Relay(FGuid RemoteSessionID, EChaosVDLoadRecordedDataMode LoadingMode) const;`
- L126 _public prototype_ `bool IsSupportedFile(const FString& InFilename);` — Evaluates a filename to determine if it is a supported filetype @param InFilename Filename to evaluate @return true if the file is supported
- L133 _public prototype_ `void LoadCVDFile(const FString& InFilename, EChaosVDLoadRecordedDataMode LoadingMode);` — Load the provided file into the current CVD instance @param InFilename Filename with path to load @param LoadingMode Desired loading mode (Single source or multi source)
- L140 _public prototype_ `void LoadCVDFiles(TConstArrayView<FString> InFilenames, EChaosVDLoadRecordedDataMode LoadingMode);` — Load the provided files into the current CVD instance @param InFilenames Array view of Filename with paths to load @param LoadingMode Desired loading mode (Single source or multi source)
- L142 _public prototype_ `TSharedRef<IDetailsView> CreateDetailsView(const FDetailsViewArgs& InDetailsViewArgs);`
- L144 _public prototype_ `TSharedRef<IStructureDetailsView> CreateStructureDetailsView(const FDetailsViewArgs& InDetailsViewArgs, const FStructureDetailsViewArgs& InStructureDetailsViewArgs, const TSharedPtr<FStructOnScope>& InStructData = nullptr, const FText& CustomName = FText::GetEmpty());`
- L145 _public prototype_ `void ProccessKeyEventForPlaybackTrackSelector(const FKeyEvent& InKeyEvent);`
- L147 _public function_ `TSharedPtr<FUICommandList> GetGlobalUICommandList() const`
- L152 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L153 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L155 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L160 _public prototype_ `bool ShouldShowTracksKeyShortcuts();`
- L163 _public prototype_ `template<typename TabType> void RegisterTabSpawner(FName TabID);`
- L165 _public prototype_ `void RegisterComponentVisualizer(FName ClassName, const TSharedPtr<FComponentVisualizer>& Visualizer);`
- L167 _public prototype_ `const TSharedPtr<FChaosVDIndependentDetailsPanelManager>& GetIndependentDetailsPanelManager();`
- L169 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L171 _public function_ `TSharedPtr<FChaosVDRecordingControls> GetRecordingControls()`
- L176 _public prototype_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget, int32 ZOrder, TSharedPtr<IAssetViewport> InViewport = nullptr) override;`
- L180 _private prototype_ `void ExtendMainToolbar();`
- L181 _private prototype_ `void ExtendStatusToolbar();`
- L183 _private prototype_ `TSharedPtr<SNotificationItem> CreateProcessingTraceDataNotification();`
- L185 _private prototype_ `void UpdateTraceProcessingNotificationUpdate();`
- L186 _private prototype_ `void ShowTraceDataProcessingNotification();`
- L187 _private prototype_ `void HideTraceDataProcessingNotification();`
- L189 _private prototype_ `void HandlePersistLayout(const TSharedRef<FTabManager::FLayout>& InLayoutToSave);`
- L191 _private prototype_ `void HandlePostInitializationExtensionRegistered(const TSharedRef<FChaosVDExtension>& NewExtension);`
- L193 _private prototype_ `void SetCustomPropertyLayouts(IDetailsView* DetailsView);`
- L195 _private prototype_ `void SetUpDisableCPUThrottlingDelegate();`
- L196 _private prototype_ `void CleanUpDisableCPUThrottlingDelegate() const;`
- L198 _private prototype_ `void CreateMainToolbarMenu();`
- L199 _private prototype_ `void AddSettingsMenu();`
- L201 _private prototype_ `void HandleTabSpawned(TSharedRef<SDockTab> Tab, FName TabID);`
- L202 _private prototype_ `void HandleTabDestroyed(TSharedRef<SDockTab> Tab, FName TabID);`
- L204 _private prototype_ `TSharedRef<FTabManager::FLayout> GenerateDefaultLayout();`
- L206 _private prototype_ `void ResetLayout();`
- L208 _private prototype_ `void CombineOpenSessions();`
- L210 _private prototype_ `void GenerateMainWindowMenu();`
- L211 _private prototype_ `void GenerateRecentFilesMenu(FMenuBuilder& MenuBuilder, UToolMenu* Menu);`
- L213 _private prototype_ `FReply BrowseAndOpenChaosVDRecording();`
- L215 _private prototype_ `TSharedRef<SButton> CreateSimpleButton(TFunction<FText()>&& GetTextDelegate, TFunction<FText()>&& ToolTipTextDelegate, const FSlateBrush* ButtonIcon, const UChaosVDMainToolbarMenuContext* MenuContext, const FOnClicked& InButtonClickedCallback);`
- L217 _private prototype_ `TSharedRef<SWidget> GenerateMainToolbarWidget();`
- L219 _private prototype_ `void BrowseChaosVDRecordingFromFolder(FStringView FolderPath, EChaosVDLoadRecordedDataMode LoadingMode);`
- L221 _private prototype_ `void BrowseLiveSessionsFromTraceStore() const;`
- L223 _private prototype_ `bool ShouldDisableCPUThrottling() const;`
- L225 _private member_ `TSharedPtr<SNotificationItem> ActiveProcessingTraceDataNotification;`
- L227 _private member_ `bool bCanTabManagerPersistLayout = true;`
- L229 _private member_ `TArray<TWeakPtr<IDetailsView>> CustomizedDetailsPanels;`
- L231 _private member_ `TSharedPtr<FChaosVDEngine> ChaosVDEngine;`
- L233 _private member_ `FName StatusBarID;`
- L235 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L236 _private member_ `TWeakPtr<SDockTab> OwnerTab;`
- L237 _private member_ `TSharedPtr<FChaosVDEditorModeTools> EditorModeTools;`
- L239 _private member_ `TMap<FName, TSharedPtr<FChaosVDTabSpawnerBase>> TabSpawnersByIDMap;`
- L241 _private member_ `TMap<FName, TSharedPtr<FComponentVisualizer>> ComponentVisualizersMap;`
- L242 _private member_ `TArray<TSharedPtr<FComponentVisualizer>> ComponentVisualizers;`
- L244 _private member_ `TMap<FName, TWeakPtr<SDockTab>> ActiveTabsByID;`
- L246 _private member_ `FOnActiveViewportChanged ViewportChangedDelegate;`
- L248 _private member_ `FDelegateHandle DisableCPUThrottleHandle;`
- L250 _private prototype_ `FReply HandleSessionConnectionClicked();`
- L251 _private prototype_ `void HandleDisconnectSessionClicked();`
- L252 _private prototype_ `FText GetDisconnectButtonText() const;`
- L254 _private member_ `bool bShowTrackSelectorKeyShortcut = false;`
- L256 _private member_ `TSharedPtr<FChaosVDIndependentDetailsPanelManager> IndependentDetailsPanelManager;`
- L259 _private member_ `TSharedPtr<FUICommandList> GlobalCommandList;` — Commandlist used for any UI actions that need to be processed globally regardless on which specific widget we are in
- L261 _private member_ `TSharedPtr<FChaosVDRecordingControls> RecordingControls;`
- L263 _private member_ `static const FName MainToolBarName;`
- L265 _private member_ `static const FName MainMenuName;`
- L269 _function_ `template <typename TabType> TWeakPtr<TabType> SChaosVDMainTab::GetTabSpawnerInstance(FName TabID)`
- L280 _function_ `template <typename TabType> void SChaosVDMainTab::RegisterTabSpawner(FName TabID)`
