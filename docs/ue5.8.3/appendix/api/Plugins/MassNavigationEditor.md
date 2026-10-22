# Plugins / MassNavigationEditor

- module root: `Plugins/AI/MassAI/Source/MassNavigationEditor`
- headers: 3; symbols: 43
- symbol kinds: class=5, macro=1, member=16, prototype=21
- PrivateDependencyModuleNames: AppFramework, KismetWidgets, Projects, RenderCore, ToolMenus
- PublicDependencyModuleNames: AssetTools, Core, CoreUObject, DetailCustomizations, EditorFramework, Engine, InputCore, MassCommon, MassCore, MassEntity, MassNavigation, MassZoneGraphNavigation, PropertyEditor, RHI, Slate, SlateCore, UnrealEd, ZoneGraph

### `Plugins/AI/MassAI/Source/MassNavigationEditor/Private/MassNavigationTestingActor.h` (Private)


#### class `FMassNavigationTestingSceneProxy`  
`class FMassNavigationTestingSceneProxy final : public FDebugRenderSceneProxy`  
_L20-28_
- inherits: `FDebugRenderSceneProxy`
- L23 _public prototype_ `FMassNavigationTestingSceneProxy(const UPrimitiveComponent& InComponent);`
- L25 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L26 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L27 _public prototype_ `virtual uint32 GetMemoryFootprint(void) const override;`

#### class `UMassNavigationTestingComponent`  
`class UMassNavigationTestingComponent : public UDebugDrawComponent`  
_L33-100_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Debug)`
- inherits: `UDebugDrawComponent`
- desc: Component for testing MassMovement functionality.
- L37 _public prototype_ `UMassNavigationTestingComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L40 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _public prototype_ `virtual void OnRegister() override;`
- L44 _public prototype_ `virtual void OnUnregister() override;`
- L46 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L49 _public prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L52 _public prototype_ `void UpdateTests();`
- L53 _public prototype_ `void PinLane();`
- L54 _public prototype_ `void ClearPinnedLane();`
- L59 _protected prototype_ `void OnZoneGraphDataBuildDone(const struct FZoneGraphBuildData& BuildData);`
- L61 _protected prototype_ `void OnZoneGraphDataChanged(const AZoneGraphData* ZoneGraphData);`
- L64 _protected member_ `FDelegateHandle OnDataChangedHandle;`
- L66 _protected member_ `FDelegateHandle OnDataAddedHandle;`
- L67 _protected member_ `FDelegateHandle OnDataRemovedHandle;`
- L70 _protected member_ `TObjectPtr<UZoneGraphSubsystem> ZoneGraph;` — `UPROPERTY(Transient)`
- L73 _protected member_ `FZoneGraphLaneLocation LaneLocation;` — `UPROPERTY(Transient)`
- L76 _protected member_ `FZoneGraphLaneLocation GoalLaneLocation;` — `UPROPERTY(Transient)`
- L79 _protected member_ `FVector SearchExtent;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L82 _protected member_ `float AnticipationDistance = 50.0f;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L85 _protected member_ `float AgentRadius = 40.0f;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L88 _protected member_ `bool bHasSpecificEndPoint = true;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L91 _protected member_ `FZoneGraphTagFilter QueryFilter;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L94 _protected member_ `FVector GoalPosition;` — `UPROPERTY(EditAnywhere, Category = Default, meta = (MakeEditWidget=true))`
- L96 _protected member_ `FZoneGraphLaneHandle PinnedLane;`
- L98 _protected member_ `FMassZoneGraphCachedLaneFragment CachedLane;`
- L99 _protected member_ `TArray<FMassZoneGraphShortPathFragment> ShortPaths;`

#### class `AMassNavigationTestingActor`  
`class AMassNavigationTestingActor : public AActor`  
_L104-123_
- reflection: `UCLASS(MinimalAPI, hidecategories = (Actor, Input, Collision, Rendering, Replication, Partition, HLOD, Cooking))`
- inherits: `AActor`
- desc: Debug actor to visually test zone graph.
- L108 _public prototype_ `AMassNavigationTestingActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L111 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L115 _public prototype_ `void PinLane();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Default")`
- L118 _public prototype_ `void ClearPinnedLane();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Default")`
- L122 _protected member_ `TObjectPtr<UMassNavigationTestingComponent> DebugComp;` — `UPROPERTY(Category = Default, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSNAVIGATIONEDITOR_API`

### `Plugins/AI/MassAI/Source/MassNavigationEditor/Public/IMassNavigationEditor.h` (Public)


#### class `IMassNavigationEditor`  
`class IMassNavigationEditor : public FAssetEditorToolkit`  
_L9-13_
- inherits: `FAssetEditorToolkit`
- desc: MassNavigation Editor public interface

### `Plugins/AI/MassAI/Source/MassNavigationEditor/Public/MassNavigationEditorModule.h` (Public)


#### class `FMassNavigationEditorModule`  
`class FMassNavigationEditorModule : public IModuleInterface`  
_L16-25_
- inherits: `IModuleInterface`
- L20 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
