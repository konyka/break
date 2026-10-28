# Plugins / ZoneGraphDebug

- module root: `Plugins/Runtime/ZoneGraph/Source/ZoneGraphDebug`
- headers: 2; symbols: 53
- symbol kinds: class=4, function=6, macro=1, member=23, prototype=19
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, GameplayTags, GameplayTasks, ZoneGraph

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphDebug/Public/IZoneGraphDebug.h` (Public)


#### class `IZoneGraphDebug`  
`class IZoneGraphDebug : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IZoneGraphDebug& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphDebug/Public/ZoneGraphTestingActor.h` (Public)


#### class `UZoneLaneTest`  
`class UZoneLaneTest : public UObject`  
_L21-37_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew)`
- inherits: `UObject`
- desc: Base class to inherit from to be able to perform custom actions on lane detected by the testing actor.
- L26 _public prototype_ `virtual void OnLaneLocationUpdated(const FZoneGraphLaneLocation& PrevLaneLocation, const FZoneGraphLaneLocation& NextLaneLocation) PURE_VIRTUAL(UZoneLaneTest::OnLaneLocationUpdated, );`
- L27 _public function_ `virtual void Draw(FPrimitiveDrawInterface* PDI) const`
- L29 _public function_ `void SetOwner(UZoneGraphTestingComponent* Owner)`
- L30 _public function_ `const UZoneGraphTestingComponent* GetOwner() const`
- L33 _protected function_ `virtual void OnOwnerSet()`
- L36 _protected member_ `TObjectPtr<UZoneGraphTestingComponent> OwnerComponent;` — `UPROPERTY()`

#### class `UZoneGraphTestingComponent`  
`class UZoneGraphTestingComponent : public UPrimitiveComponent`  
_L41-142_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Custom, hidecategories = (Physics, Collision, Rendering, Cooking, Lighting, Navigation, Tags, HLOD, Mobile, AssetUserData, Activation))`
- inherits: `UPrimitiveComponent`
- desc: Actor for testing ZoneGraph functionality.
- L45 _public prototype_ `UZoneGraphTestingComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L48 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L51 _public prototype_ `virtual void OnRegister() override;`
- L52 _public prototype_ `virtual void OnUnregister() override;`
- L54 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L56 _public prototype_ `void UpdateTests();`
- L60 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L65 _public prototype_ `const FZoneGraphStorage* GetZoneGraphStorage(const FZoneGraphLaneHandle& LaneHandle) const;` — Returns the graph storage corresponding to the provided lane handle, if any.
- L69 _public prototype_ `void EnableCustomTests();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = Test)` — Allow custom tests to be notified when lane location is updated.
- L73 _public prototype_ `void DisableCustomTests();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = Test)` — Prevent custom tests to be notified when lane location is updated. Currently active tests will get notified with an invalid location.
- L78 _protected prototype_ `void OnZoneGraphDataBuildDone(const struct FZoneGraphBuildData& BuildData);`
- L80 _protected prototype_ `void OnZoneGraphDataChanged(const AZoneGraphData* ZoneGraphData);`
- L83 _protected member_ `FDelegateHandle OnDataChangedHandle;`
- L85 _protected member_ `FDelegateHandle OnDataAddedHandle;`
- L86 _protected member_ `FDelegateHandle OnDataRemovedHandle;`
- L89 _protected member_ `TObjectPtr<UZoneGraphSubsystem> ZoneGraph;` — `UPROPERTY(Transient)`
- L92 _protected member_ `FZoneGraphLaneLocation LaneLocation;` — `UPROPERTY(Transient)`
- L95 _protected member_ `FZoneGraphLaneLocation NextLaneLocation;` — `UPROPERTY(Transient)`
- L98 _protected member_ `FZoneGraphLaneLocation NearestLaneLocation;` — `UPROPERTY(Transient)`
- L101 _protected member_ `FVector SearchExtent;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L104 _protected member_ `float AdvanceDistance;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L107 _protected member_ `FVector NearestTestOffset;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L110 _protected member_ `FZoneGraphTagFilter QueryFilter;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L113 _protected member_ `bool bDrawLinkedLanes = false;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L116 _protected member_ `bool bDrawLaneTangentVectors = false;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L119 _protected member_ `bool bDrawLaneSmoothing = false;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L122 _protected member_ `bool bDrawBVTreeQuery = false;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L126 _protected member_ `bool bDrawLanePath = false;` — `UPROPERTY(EditAnywhere, Category = Test)` — Experimental
- L129 _protected member_ `TObjectPtr<AZoneGraphTestingActor> OtherActor;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L131 _protected member_ `TArray<FZoneGraphLinkedLane> LinkedLanes;`
- L132 _protected member_ `FZoneGraphLanePath LanePath;`
- L135 _protected member_ `TArray<TObjectPtr<UZoneLaneTest>> CustomTests;` — `UPROPERTY(EditAnywhere, Category = Test, Instanced)`
- L138 _private prototype_ `void ExecuteOnEachCustomTest(TFunctionRef<void(UZoneLaneTest&)> ExecFunc);`
- L139 _private prototype_ `void ExecuteOnEachCustomTest(TFunctionRef<void(const UZoneLaneTest&)> ExecFunc) const;`
- L141 _private member_ `bool bCustomTestsDisabled = false;`

#### class `AZoneGraphTestingActor`  
`class AZoneGraphTestingActor : public AActor`  
_L146-167_
- reflection: `UCLASS(hidecategories = (Actor, Input, Collision, Rendering, Replication, Partition, HLOD, Cooking))`
- inherits: `AActor`
- desc: Debug actor to visually test zone graph.
- L150 _public prototype_ `AZoneGraphTestingActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L153 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L158 _public prototype_ `void EnableCustomTests();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = Test)` — Allow custom tests to be notified when lane location is updated.
- L162 _public prototype_ `void DisableCustomTests();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = Test)` — Prevent custom tests to be notified when lane location is updated. Currently active tests will get notified with an invalid location.
- L166 _protected member_ `TObjectPtr<UZoneGraphTestingComponent> DebugComp;` — `UPROPERTY(Category = Default, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ZONEGRAPHDEBUG_API`
