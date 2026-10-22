# Plugins / ChaosDataflowSolver

- module root: `Plugins/Experimental/ChaosDataflowSolver/Source/ChaosDataflowSolver`
- headers: 8; symbols: 45
- symbol kinds: class=8, function=10, member=6, prototype=21
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, Landscape, Slate, SlateCore
- PublicDependencyModuleNames: Core, DataflowCore, DataflowEngine, DataflowSimulation, RigidPhysics

### `Plugins/Experimental/ChaosDataflowSolver/Source/ChaosDataflowSolver/Private/RigidComponents/InstancedRigidComponentInterface.h` (Private)


#### class `InstancedRigidComponentInterface`  
`class InstancedRigidComponentInterface`  
_L19-89_
- L22 _public function_ `static void OnCreateSolverBodies(UInstancedStaticMeshComponent* Component, UE::Physics::FRigidSceneHandle& SceneHandle, TArray<UE::Physics::FRigidBodyHandle>& OutBodies)`

### `Plugins/Experimental/ChaosDataflowSolver/Source/ChaosDataflowSolver/Private/RigidComponents/LandscapeRigidComponentInterface.h` (Private)


#### class `LandscapeRigidComponentInterface`  
`class LandscapeRigidComponentInterface`  
_L16-19_

### `Plugins/Experimental/ChaosDataflowSolver/Source/ChaosDataflowSolver/Private/RigidComponents/PrimitiveRigidComponentInterface.h` (Private)


#### class `PrimitiveRigidComponentInterface`  
`class PrimitiveRigidComponentInterface`  
_L19-125_
- L22 _public function_ `static void OnCreateSolverBodies(UPrimitiveComponent* Component, UE::Physics::FRigidSceneHandle& SceneHandle, TArray<UE::Physics::FRigidBodyHandle>& OutBodies)`
- L97 _public function_ `static void OnSolverEndFrame(UPrimitiveComponent* Component, UE::Physics::FRigidSceneHandle& SceneHandle, TArray<UE::Physics::FRigidBodyHandle>& Bodies)`

### `Plugins/Experimental/ChaosDataflowSolver/Source/ChaosDataflowSolver/Private/RigidComponents/SkeletalRigidComponentInterface.h` (Private)


#### class `SkeletalRigidComponentInterface`  
`class SkeletalRigidComponentInterface`  
_L14-24_
- L17 _public function_ `static void OnCreateSolverBodies(USkeletalMeshComponent* Component, UE::Physics::FRigidSceneHandle& SceneHandle, TArray<UE::Physics::FRigidBodyHandle>& OutBodies)`
- L21 _public function_ `static void OnSolverEndFrame(USkeletalMeshComponent* Component, UE::Physics::FRigidSceneHandle& SceneHandle, TArray<UE::Physics::FRigidBodyHandle>& Bodies)`

### `Plugins/Experimental/ChaosDataflowSolver/Source/ChaosDataflowSolver/Public/ChaosDataflowSolver.h` (Public)


#### class `FChaosDataflowSolverModule`  
`class FChaosDataflowSolverModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/ChaosDataflowSolver/Source/ChaosDataflowSolver/Public/ChaosDataflowSolverActor.h` (Public)


#### class `AChaosDataflowSolverActor`  
`class AChaosDataflowSolverActor : public AActor, public IDataflowPhysicsSolverInterface`  
_L25-60_
- reflection: `UCLASS(meta=(Experimental), MinimalAPI)`
- inherits: `AActor,IDataflowPhysicsSolverInterface`
- L30 _public prototype_ `virtual void PostInitializeComponents() override;`
- L31 _public prototype_ `virtual void BeginPlay() override;`
- L32 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type ReasonEnd) override;`
- L35 _public prototype_ `virtual void SetSolverActive(bool bActive);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Controls whether the solver is able to simulate particles it controls
- L38 _public function_ `virtual FString GetSimulationName() const override`
- L39 _public function_ `virtual FDataflowSimulationAsset& GetSimulationAsset() override`
- L40 _public function_ `virtual const FDataflowSimulationAsset& GetSimulationAsset() const override`
- L41 _public function_ `virtual FDataflowSimulationProxy* GetSimulationProxy() override`
- L42 _public function_ `virtual const FDataflowSimulationProxy* GetSimulationProxy() const override`
- L43 _public prototype_ `virtual void BuildSimulationProxy() override;`
- L44 _public prototype_ `virtual void ResetSimulationProxy() override;`
- L45 _public prototype_ `virtual void WriteToSimulation(const float DeltaTime, const bool bAsyncTask) override;`
- L46 _public prototype_ `virtual void ReadFromSimulation(const float DeltaTime, const bool bAsyncTask) override;`
- L47 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L49 _public prototype_ `void RegisterPhysicsComponent(UPrimitiveComponent* Component);`
- L50 _public prototype_ `void UnregisterPhysicsComponent(UPrimitiveComponent* Component);`
- L55 _private member_ `FDataflowSimulationAsset SimulationAsset;` — `UPROPERTY(EditAnywhere, Category = "Physics", meta=(EditConditionHides))` — Solver dataflow asset used to advance in time
- L57 _private member_ `TArray<TWeakObjectPtr<UPrimitiveComponent>> RegisteredComponents;`
- L59 _private member_ `TUniquePtr<UE::Dataflow::FDataflowSimulationContext> SolverContext;`

### `Plugins/Experimental/ChaosDataflowSolver/Source/ChaosDataflowSolver/Public/ChaosSolverBindingComponent.h` (Public)


#### class `UChaosSolverBindingComponent`  
`class UChaosSolverBindingComponent: public UActorComponent`  
_L14-44_
- reflection: `UCLASS(BlueprintType, ClassGroup = Chaos, meta = (Experimental, BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UActorComponent`
- L20 _public prototype_ `UChaosSolverBindingComponent();`
- L23 _public prototype_ `virtual void BeginPlay() override;`
- L24 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L25 _public prototype_ `virtual void BeginDestroy() override;`
- L28 _public prototype_ `static void BindWorldDelegates();`
- L32 _protected prototype_ `virtual void OnRegister() override;`
- L33 _protected prototype_ `virtual void OnUnregister() override;`
- L37 _private prototype_ `static void HandlePostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS);`
- L40 _private member_ `TSoftObjectPtr<AChaosDataflowSolverActor> SimulationActor;` — `UPROPERTY(EditAnywhere, Category = "Physics")`
- L43 _private member_ `bool bKeepKinematicInOriginal;` — `UPROPERTY(EditAnywhere, Category = "Physics")`

### `Plugins/Experimental/ChaosDataflowSolver/Source/ChaosDataflowSolver/Public/RigidAssetUserData.h` (Public)


#### class `URigidAssetUserData`  
`class URigidAssetUserData : public UAssetUserData`  
_L18-27_
- reflection: `UCLASS(meta=(Experimental), MinimalAPI, NotBlueprintable, HideCategories = (Object))`
- inherits: `UAssetUserData`
- L24 _public member_ `TArray<UE::Physics::FRigidBodyHandle> Bodies;`
