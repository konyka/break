# Runtime / ChaosSolverEngine

- module root: `Source/Runtime/Experimental/ChaosSolverEngine`
- headers: 14; symbols: 391
- symbol kinds: class=14, delegate=6, enum=6, enumerator=20, function=35, macro=1, member=116, namespace=12, prototype=149, struct=28, typedef=4
- PrivateDependencyModuleNames: Messaging, RigidPhysics
- PublicDependencyModuleNames: ChaosVDRuntime, Core, CoreUObject, DataflowCore, DataflowEngine, DataflowSimulation, DeveloperSettings, Engine, RHI, RenderCore, TraceBasedDebuggers

### `Source/Runtime/Experimental/ChaosSolverEngine/Private/Chaos/ChaosSolverEnginePluginPrivate.h` (Private)


#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_STATS_GROUP(TEXT("ChaosSolver"), STATGROUP_ChaosSolver, STATCAT`

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosDebugDrawComponent.h` (Public)


#### class `UChaosDebugDrawComponent`  
`class UChaosDebugDrawComponent : public UActorComponent`  
_L14-46_
- reflection: `UCLASS(BlueprintType, ClassGroup = Chaos, meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UActorComponent`
- L20 _public prototype_ `UChaosDebugDrawComponent();`
- L23 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L24 _public prototype_ `virtual void BeginPlay() override;`
- L25 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L26 _public prototype_ `virtual void BeginDestroy() override;`
- L29 _public prototype_ `static void BindWorldDelegates();`
- L33 _protected prototype_ `virtual void OnRegister() override;`
- L34 _protected prototype_ `virtual void OnUnregister() override;`
- L38 _private prototype_ `static void HandlePostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS);`
- L39 _private prototype_ `static void CreateDebugDrawActor(UWorld* World);`
- L41 _private member_ `bool bInPlay;`
- L44 _private member_ `TArray<Chaos::FLatentDrawCommand> DrawCommands;`

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosDebugDrawSubsystem.h` (Public)


#### class `UChaosDebugDrawSubsystem`  
`class UChaosDebugDrawSubsystem : public UWorldSubsystem`  
_L15-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- L21 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override final;`
- L22 _public prototype_ `virtual void PostInitialize() override final;`
- L23 _public prototype_ `virtual void Deinitialize() override final;`
- L25 _public prototype_ `static void Startup();`
- L26 _public prototype_ `static void Shutdown();`
- L31 _public function_ `const ChaosDD::Private::FChaosDDScenePtr& GetDebugDrawScene() const`
- L35 _protected prototype_ `void RenderScene(FChaosDDRenderer& Renderer, const ChaosDD::Private::FChaosDDScenePtr& Scene);`
- L36 _protected prototype_ `void RenderFrame(FChaosDDRenderer& Renderer, const ChaosDD::Private::FChaosDDFramePtr& Frame);`
- L37 _protected prototype_ `void OnWorldTickStart(ELevelTick TickType, float Dt);`
- L38 _protected prototype_ `void OnWorldTickEnd(ELevelTick TickType, float Dt);`
- L39 _protected prototype_ `void UpdateDrawRegion();`
- L40 _protected prototype_ `void RenderScene();`
- L41 _protected prototype_ `static void StaticOnWorldTickStart(UWorld* World, ELevelTick TickType, float Dt);`
- L42 _protected prototype_ `static void StaticOnWorldTickEnd(UWorld* World, ELevelTick TickType, float Dt);`
- L44 _protected member_ `ChaosDD::Private::FChaosDDScenePtr CDDScene;`
- L45 _protected member_ `ChaosDD::Private::FChaosDDTimelinePtr CDDWorldTimeline;`
- L46 _protected member_ `ChaosDD::Private::FChaosDDTimelineContext CDDWorldTimelineContext;`
- L48 _protected member_ `static FDelegateHandle OnTickWorldStartDelegate;`
- L49 _protected member_ `static FDelegateHandle OnTickWorldEndDelegate;`

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosEventListenerComponent.h` (Public)


#### class `UChaosEventListenerComponent`  
`class UChaosEventListenerComponent : public UActorComponent`  
_L24-41_
- reflection: `UCLASS(BlueprintType, ClassGroup = Chaos, meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UActorComponent`
- L30 _public prototype_ `UChaosEventListenerComponent();`
- L33 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L40 _protected member_ `float LastCollisionTickTime;` — Used to know when the physics thread has updated the collision info for processing on the game thread

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosGameplayEventDispatcher.h` (Public)


#### struct `FBreakEventCallbackWrapper`  
`struct FBreakEventCallbackWrapper`  
_L27-33_
- reflection: `USTRUCT()`
- desc: UStruct wrapper so we can store the TFunction in a TMap
- L32 _public member_ `FOnBreakEventCallback BreakEventCallback;`

#### struct `FRemovalEventCallbackWrapper`  
`struct FRemovalEventCallbackWrapper`  
_L39-45_
- reflection: `USTRUCT()`
- desc: UStruct wrapper so we can store the TFunction in a TMap
- L44 _public member_ `FOnRemovalEventCallback RemovalEventCallback;`

#### struct `FCrumblingEventCallbackWrapper`  
`struct FCrumblingEventCallbackWrapper`  
_L51-57_
- reflection: `USTRUCT()`
- desc: UStruct wrapper so we can store the TFunction in a TMap
- L56 _public member_ `FOnCrumblingEventCallback CrumblingEventCallback;`

#### struct `FChaosHandlerSet`  
`struct FChaosHandlerSet`  
_L61-70_
- reflection: `USTRUCT()`
- desc: UStruct wrapper so we can store the TSet in a TMap
- L65 _public member_ `bool bLegacyComponentNotify;`
- L69 _public member_ `TSet<TObjectPtr<UObject>> ChaosHandlers;` — `UPROPERTY()` — These should be IChaosNotifyHandlerInterface refs, but we can't store those here

#### struct `FChaosPendingCollisionNotify`  
`struct FChaosPendingCollisionNotify`  
_L72-76_
- L74 _public member_ `FChaosPhysicsCollisionInfo CollisionInfo;`
- L75 _public member_ `TSet<TObjectPtr<UObject>> NotifyRecipients;`

#### class `UChaosGameplayEventDispatcher`  
`class UChaosGameplayEventDispatcher : public UChaosEventListenerComponent`  
_L80-183_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UChaosEventListenerComponent`
- L86 _public prototype_ `UChaosGameplayEventDispatcher();`
- L88 _public prototype_ `virtual void OnRegister() override;`
- L89 _public prototype_ `virtual void OnUnregister() override;`
- L91 _public prototype_ `void RegisterChaosEvents();`
- L92 _public prototype_ `void UnregisterChaosEvents();`
- L103 _private function_ `friend bool operator==(const FUniqueContactPairKey& Lhs, const FUniqueContactPairKey& Rhs)`
- L108 _private function_ `friend inline uint32 GetTypeHash(FUniqueContactPairKey const& P)`
- L114 _private prototype_ `FCollisionNotifyInfo& GetPendingCollisionForContactPair(const void* P0, const void* P1, bool& bNewEntry);`
- L116 _private member_ `TMap<FUniqueContactPairKey, int32> ContactPairToPendingNotifyMap;` — Key is the unique pair, value is index into PendingNotifies array
- L118 _private prototype_ `FChaosPendingCollisionNotify& GetPendingChaosCollisionForContactPair(const void* P0, const void* P1, bool& bNewEntry);`
- L120 _private member_ `TMap<FUniqueContactPairKey, int32> ContactPairToPendingChaosNotifyMap;` — Key is the unique pair, value is index into PendingChaosCollisionNotifies array
- L123 _private member_ `TArray<FChaosPendingCollisionNotify> PendingChaosCollisionNotifies;` — Holds the list of pending Chaos notifies that are to be processed
- L126 _private member_ `TArray<FCollisionNotifyInfo> PendingCollisionNotifies;` — Holds the list of pending legacy notifies that are to be processed
- L134 _public prototype_ `void RegisterForCollisionEvents(UPrimitiveComponent* ComponentToListenTo, UObject* ObjectToNotify);` — Use to subscribe to collision events. @param ComponentToListenTo	The component whose collisions will be reported @param ObjectToNotify		The object that will receive the notifications. Should be a PrimitiveComponent or implement IChaosNotifyHandlerInterface, or both.
- L135 _public prototype_ `void UnRegisterForCollisionEvents(UPrimitiveComponent* ComponentToListenTo, UObject* ObjectToNotify);`
- L137 _public prototype_ `void RegisterForBreakEvents(UPrimitiveComponent* Component, FOnBreakEventCallback InFunc);`
- L138 _public prototype_ `void UnRegisterForBreakEvents(UPrimitiveComponent* Component);`
- L140 _public prototype_ `void RegisterForRemovalEvents(UPrimitiveComponent* Component, FOnRemovalEventCallback InFunc);`
- L141 _public prototype_ `void UnRegisterForRemovalEvents(UPrimitiveComponent* Component);`
- L143 _public prototype_ `void RegisterForCrumblingEvents(UPrimitiveComponent* Component, FOnCrumblingEventCallback InFunc);`
- L144 _public prototype_ `void UnRegisterForCrumblingEvents(UPrimitiveComponent* Component);`
- L149 _private member_ `TMap<TObjectPtr<UPrimitiveComponent>, FChaosHandlerSet> CollisionEventRegistrations;` — `UPROPERTY()`
- L152 _private member_ `TMap<TObjectPtr<UPrimitiveComponent>, FBreakEventCallbackWrapper> BreakEventRegistrations;` — `UPROPERTY()`
- L155 _private member_ `TMap<TObjectPtr<UPrimitiveComponent>, FRemovalEventCallbackWrapper> RemovalEventRegistrations;` — `UPROPERTY()`
- L158 _private member_ `TMap<TObjectPtr<UPrimitiveComponent>, FCrumblingEventCallbackWrapper> CrumblingEventRegistrations;` — `UPROPERTY()`
- L161 _private member_ `float LastCollisionDataTime = -1.f;`
- L162 _private member_ `float LastBreakingDataTime = -1.f;`
- L163 _private member_ `float LastRemovalDataTime = -1.f;`
- L164 _private member_ `float LastCrumblingDataTime = -1.f;`
- L166 _private prototype_ `void DispatchPendingCollisionNotifies();`
- L169 _private prototype_ `template <typename EventIterator> void FillPhysicsProxy(FPhysScene_Chaos& Scene, TArray<UObject*>& Result, EventIterator& It);`
- L171 _private prototype_ `TArray<UObject*> GetInterestedProxyOwnersForCollisionEvents();`
- L172 _private prototype_ `TArray<UObject*> GetInterestedProxyOwnersForBreakingEvents();`
- L173 _private prototype_ `TArray<UObject*> GetInterestedProxyOwnersForRemovalEvents();`
- L174 _private prototype_ `TArray<UObject*> GetInterestedProxyOwnersForCrumblingEvents();`
- L177 _private prototype_ `void HandleCollisionEvents(const Chaos::FCollisionEventData& CollisionData);` — Chaos Event Handlers
- L178 _private prototype_ `void HandleBreakingEvents(const Chaos::FBreakingEventData& BreakingData);`
- L179 _private prototype_ `void HandleSleepingEvents(const Chaos::FSleepingEventData& SleepingData);`
- L180 _private prototype_ `void HandleRemovalEvents(const Chaos::FRemovalEventData& RemovalData);`
- L181 _private prototype_ `void HandleCrumblingEvents(const Chaos::FCrumblingEventData& CrumblingData);`

#### struct `UChaosGameplayEventDispatcher::FUniqueContactPairKey`  
`struct FUniqueContactPairKey`  
_L98-112_
- desc: contains the set of properties that uniquely identifies a reported collision Note that order matters, { Body0, Body1 } is not the same as { Body1, Body0 }
- L100 _public member_ `const void* Body0;`
- L101 _public member_ `const void* Body1;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`
- L23 _typedef_ `typedef TFunction<void(const FChaosBreakEvent&)> FOnBreakEventCallback;`
- L35 _typedef_ `typedef TFunction<void(const FChaosRemovalEvent&)> FOnRemovalEventCallback;`
- L47 _typedef_ `typedef TFunction<void(const FChaosCrumblingEvent&)> FOnCrumblingEventCallback;`

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosNotifyHandlerInterface.h` (Public)


#### struct `FChaosPhysicsCollisionInfo`  
`struct FChaosPhysicsCollisionInfo`  
_L12-53_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public prototype_ `FChaosPhysicsCollisionInfo();`
- L20 _public member_ `TObjectPtr<UPrimitiveComponent> Component = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chaos")`
- L23 _public member_ `TObjectPtr<UPrimitiveComponent> OtherComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos")`
- L27 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos")` — Location of the impact
- L31 _public member_ `FVector Normal;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos")` — Normal at the impact
- L34 _public member_ `FVector AccumulatedImpulse;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos")`
- L37 _public member_ `FVector Velocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos")`
- L40 _public member_ `FVector OtherVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos")`
- L43 _public member_ `FVector AngularVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos")`
- L46 _public member_ `FVector OtherAngularVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos")`
- L49 _public member_ `float Mass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos")`
- L52 _public member_ `float OtherMass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos")`

#### class `UChaosNotifyHandlerInterface`  
`class UChaosNotifyHandlerInterface : public UInterface`  
_L59-62_
- reflection: `UINTERFACE(BlueprintType, MinimalAPI)`
- inherits: `UInterface`
- desc: Interface for objects that want collision and trailing notifies from the Chaos solver

#### class `IChaosNotifyHandlerInterface`  
`class IChaosNotifyHandlerInterface : public IInterface`  
_L64-78_
- inherits: `IInterface`
- L70 _public function_ `virtual void NotifyPhysicsCollision(const FChaosPhysicsCollisionInfo& CollisionInfo)` — Override for native handling of a physics collision
- L73 _public function_ `virtual void DispatchChaosPhysicsCollisionBlueprintEvents(const FChaosPhysicsCollisionInfo& CollisionInfo)` — Implementing classes should override to dispatch whatever blueprint events they choose to offer
- L76 _public prototype_ `void HandlePhysicsCollision(const FChaosPhysicsCollisionInfo& CollisionInfo);` — Entry point for collision notifications, called by the underlying system. Not for overriding.

#### class `UChaosSolverEngineBlueprintLibrary`  
`class UChaosSolverEngineBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L86-93_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L92 _public prototype_ `static FHitResult ConvertPhysicsCollisionToHitResult(const FChaosPhysicsCollisionInfo& PhysicsCollision);` — `UFUNCTION(BlueprintPure, Category = "Chaos", meta = (WorldContext = "WorldContextObject"))`

#### Free symbols / members of external scopes

- L55 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosPhysicsCollision, const FChaosPhysicsCollisionInfo&, CollisionInfo);`
- L55 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosPhysicsCollision, const FChaosPhysicsCollisionInfo&, CollisionInfo);`

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosSolver.h` (Public)


#### class `UChaosSolver`  
`class UChaosSolver : public UObject`  
_L17-24_
- reflection: `UCLASS(customconstructor, MinimalAPI)`
- inherits: `UObject`
- desc: UChaosSolver (UObject)
- L22 _public prototype_ `UChaosSolver(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L23 _public function_ `bool IsVisible()`

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosSolverActor.h` (Public)


#### enum `EClusterConnectionTypeEnum`  
`enum class EClusterConnectionTypeEnum : uint8`  
_L33-43_
- reflection: `UENUM()`
- desc: Legacy enum for old deprecated configuration properties. To be removed when those properties are
- L35 _public enumerator_ `Chaos_PointImplicit = Chaos::FClusterCreationParameters::PointImplicit`
- L36 _public enumerator_ `Chaos_DelaunayTriangulation = Chaos::FClusterCreationParameters::DelaunayTriangulation UMETA(Hidden)`
- L37 _public enumerator_ `Chaos_MinimalSpanningSubsetDelaunayTriangulation = Chaos::FClusterCreationParameters::MinimalSpanningSubsetDelaunayTriangulation`
- L38 _public enumerator_ `Chaos_PointImplicitAugmentedWithMinimalDelaunay = Chaos::FClusterCreationParameters::PointImplicitAugmentedWithMinimalDelaunay`
- L39 _public enumerator_ `Chaos_BoundsOverlapFilteredDelaunayTriangulation = Chaos::FClusterCreationParameters::BoundsOverlapFilteredDelaunayTriangulation`
- L40 _public enumerator_ `Chaos_None = Chaos::FClusterCreationParameters::None UMETA(Hidden)`
- L42 _public enumerator_ `Chaos_EClsuterCreationParameters_Max UMETA(Hidden)`

#### struct `FChaosDebugSubstepControl`  
`struct FChaosDebugSubstepControl`  
_L46-73_
- reflection: `USTRUCT()`
- L50 _public function_ `FChaosDebugSubstepControl() : bPause(false), bSubstep(false), bStep(false)`
- L56 _public member_ `bool bPause;` — `UPROPERTY(EditAnywhere, Category = "ChaosPhysics|Debug")` — Pause the solver at the next synchronization point.
- L62 _public member_ `bool bSubstep;` — `UPROPERTY(EditAnywhere, Category = "ChaosPhysics|Debug", meta = (EditCondition = "bPause"))` — Substep the solver to the next synchronization point.
- L68 _public member_ `bool bStep;` — `UPROPERTY(EditAnywhere, Category = "ChaosPhysics|Debug", meta = (EditCondition = "bPause"))` — Step the solver to the next synchronization point.
- L71 _public member_ `FSimpleDelegate OnPauseChanged;` — Delegate used to refresh the Editor's details customization when the pause value changed.

#### struct `FDataflowRigidSolverProxy`  
`struct FDataflowRigidSolverProxy : public FDataflowPhysicsSolverProxy`  
_L76-98_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDataflowPhysicsSolverProxy`
- L80 _public function_ `FDataflowRigidSolverProxy() : FDataflowPhysicsSolverProxy()`
- L82 _public prototype_ `virtual ~FDataflowRigidSolverProxy() override = default;`
- L85 _public prototype_ `virtual void AdvanceSolverDatas(const float DeltaTime) override;`
- L86 _public function_ `virtual bool IsValid() const override`
- L87 _public function_ `virtual const UScriptStruct* GetScriptStruct() const override`
- L94 _public member_ `Chaos::FPhysicsSolver* Solver = nullptr;` — Chaos deformable solver that will be used in the component
- L97 _public member_ `TArray<Chaos::FPushPhysicsData*> PushDatas = {};` — List of push datas that will be used to advance the solver

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FDataflowRigidSolverProxy> : public TStructOpsTypeTraitsBase2<FDataflowRigidSolverProxy>`  
_L101-104_
- inherits: `TStructOpsTypeTraitsBase2<FDataflowRigidSolverProxy>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L103-103_

#### class `AChaosSolverActor`  
`class AChaosSolverActor : public AActor, public IDataflowPhysicsSolverInterface`  
_L107-232_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor,IDataflowPhysicsSolverInterface`
- L114 _public member_ `FChaosSolverConfiguration Properties;` — `UPROPERTY(EditAnywhere, Category = "Chaos", meta=(ShowOnlyInnerProperties))`
- L118 _public member_ `float TimeStepMultiplier_DEPRECATED;` — `UPROPERTY()` — Deprecated solver properties (moved to FChaosSolverConfiguration)
- L120 _public member_ `int32 CollisionIterations_DEPRECATED;` — `UPROPERTY()`
- L122 _public member_ `int32 PushOutIterations_DEPRECATED;` — `UPROPERTY()`
- L124 _public member_ `int32 PushOutPairIterations_DEPRECATED;` — `UPROPERTY()`
- L126 _public member_ `float ClusterConnectionFactor_DEPRECATED;` — `UPROPERTY()`
- L128 _public member_ `EClusterConnectionTypeEnum ClusterUnionConnectionType_DEPRECATED;` — `UPROPERTY()`
- L130 _public member_ `bool DoGenerateCollisionData_DEPRECATED;` — `UPROPERTY()`
- L132 _public member_ `FSolverCollisionFilterSettings CollisionFilterSettings_DEPRECATED;` — `UPROPERTY()`
- L134 _public member_ `bool DoGenerateBreakingData_DEPRECATED;` — `UPROPERTY()`
- L136 _public member_ `FSolverBreakingFilterSettings BreakingFilterSettings_DEPRECATED;` — `UPROPERTY()`
- L138 _public member_ `bool DoGenerateTrailingData_DEPRECATED;` — `UPROPERTY()`
- L140 _public member_ `FSolverTrailingFilterSettings TrailingFilterSettings_DEPRECATED;` — `UPROPERTY()`
- L142 _public member_ `float MassScale_DEPRECATED;` — `UPROPERTY()`
- L146 _public member_ `bool bHasFloor;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L149 _public member_ `float FloorHeight;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L155 _public member_ `FChaosDebugSubstepControl ChaosDebugSubstepControl;` — `UPROPERTY(EditAnywhere, Category = "ChaosPhysics|Debug")` — Control to pause/step/substep the solver to the next synchronization point.
- L159 _public prototype_ `void SetAsCurrentWorldSolver();` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Makes this solver the current world solver. Dynamically spawned objects will have their physics state created in this solver.
- L163 _public prototype_ `virtual void SetSolverActive(bool bActive);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Controls whether the solver is able to simulate particles it controls
- L166 _public function_ `virtual FString GetSimulationName() const override`
- L167 _public function_ `virtual FDataflowSimulationAsset& GetSimulationAsset() override`
- L168 _public function_ `virtual const FDataflowSimulationAsset& GetSimulationAsset() const override`
- L169 _public function_ `virtual FDataflowSimulationProxy* GetSimulationProxy() override`
- L170 _public function_ `virtual const FDataflowSimulationProxy* GetSimulationProxy() const override`
- L171 _public prototype_ `virtual void BuildSimulationProxy() override;`
- L172 _public prototype_ `virtual void ResetSimulationProxy() override;`
- L173 _public prototype_ `virtual void WriteToSimulation(const float DeltaTime, const bool bAsyncTask) override;`
- L174 _public prototype_ `virtual void ReadFromSimulation(const float DeltaTime, const bool bAsyncTask) override;`
- L181 _public member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY()` — Display icon in the editor
- L183 _public function_ `UChaosGameplayEventDispatcher* GetGameplayEventDispatcher() const`
- L185 _public function_ `TSharedPtr<FPhysScene_Chaos> GetPhysicsScene() const`
- L186 _public function_ `Chaos::FPhysicsSolver* GetSolver() const`
- L188 _public prototype_ `virtual void PreRegisterAllComponents() override;`
- L189 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L190 _public prototype_ `virtual void PreInitializeComponents() override;`
- L191 _public prototype_ `virtual void PostUnregisterAllComponents() override;`
- L193 _public prototype_ `virtual void BeginPlay() override;`
- L194 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type ReasonEnd) override;`
- L198 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L199 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L201 _public prototype_ `void PostLoad() override;`
- L202 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L203 _public prototype_ `void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L210 _private member_ `FDataflowSimulationAsset SimulationAsset;` — `UPROPERTY(EditAnywhere, Category = "Physics", meta=(EditConditionHides), AdvancedDisplay)` — Solver dataflow asset used to advance in time
- L213 _private prototype_ `void MakeFloor();` — If floor is enabled, make a particle to represent it
- L215 _private member_ `TSharedPtr<FPhysScene_Chaos> PhysScene;`
- L218 _private member_ `FDataflowRigidSolverProxy RigidSolverProxy;` — Rigid solver proxy used in dataflow simulation
- L221 _private prototype_ `void ConditionalCreateSolver();` — Ensure that the solver actor has a valid solver and scene
- L224 _private prototype_ `void MigrateSolver() const;` — Migrate the solver onto the right owner (World vs Actor)
- L228 _private member_ `TObjectPtr<UChaosGameplayEventDispatcher> GameplayEventDispatcherComponent;` — `UPROPERTY()` — Component responsible for harvesting and triggering physics-related gameplay events (hits, breaks, etc)
- L231 _private member_ `Chaos::FSingleParticlePhysicsProxy* Proxy;` — If floor is enabled - this will point to the solver particle for it

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace Chaos`
- L103 _enumerator_ `enum { WithCopy = false };` (scope `TStructOpsTypeTraits::__anon415d17b70103`)

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosSolverComponentTypes.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosSolverEnginePlugin.h` (Public)


#### class `IChaosSolverEnginePlugin`  
`class IChaosSolverEnginePlugin : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IChaosSolverEnginePlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosSolverSettings.h` (Public)


#### class `UChaosSolverSettings`  
`class UChaosSolverSettings : public UDeveloperSettings, public IChaosSolverActorClassProvider`  
_L14-44_
- reflection: `UCLASS(config = Engine, defaultconfig, meta = (DisplayName = "Chaos Solver"), MinimalAPI)`
- inherits: `UDeveloperSettings,IChaosSolverActorClassProvider`
- L20 _public prototype_ `UChaosSolverSettings();`
- L23 _public prototype_ `virtual UClass* GetSolverActorClass() const;` — IChaosSolverActorClassProvider interface
- L27 _public member_ `FSoftClassPath DefaultChaosSolverActorClass;` — `UPROPERTY(config, noclear, EditAnywhere, Category = GameInstance, meta = (MetaClass = "/Script/ChaosSolverEngine.ChaosSolverActor"))` — The class to use when auto-creating a default chaos solver actor
- L30 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L33 _public prototype_ `virtual void PostInitProperties() override;`
- L34 _public prototype_ `virtual void PostReloadConfig(class FProperty* PropertyThatWasLoaded) override;`
- L40 _private prototype_ `void UpdateProperty(FProperty* InProperty);` — Chaos can't read the properties here as it doesn't depend on engine, the following functions push changes to the chaos module as properties change
- L41 _private prototype_ `void UpdateAllProperties();`
- L42 _private prototype_ `void RegisterSolverActorProvider();`

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosVDEngineEditorBridge.h` (Public)


#### class `FChaosVDEngineEditorBridge`  
`class FChaosVDEngineEditorBridge : public UE::TraceBasedDebuggers::FEngineEditorBridge`  
_L46-111_
- inherits: `UE::TraceBasedDebuggers::FEngineEditorBridge`
- desc: Object that bridges the gap between the ChaosVD runtime module and the Engine & CVD editor. As the ChaosVDRuntime module does not have access to the engine module, this object reacts to events and performs necessary operation the runtime module cannot do directly
- L49 _public prototype_ `FChaosVDEngineEditorBridge();`
- L51 _public prototype_ `~FChaosVDEngineEditorBridge() = default;`
- L53 _public prototype_ `static FChaosVDEngineEditorBridge& Get();`
- L56 _public prototype_ `static bool IsInstantiated();` — @return Whether the static instance has been created (i.e., Get() was called and teardown is required)
- L60 _public function_ `TSharedPtr<FChaosVDRemoteSessionsManager> GetRemoteSessionsManager()` — `UE_DEPRECATED(5.8, "Use GetSessionsManager instead")`
- L65 _public typedef_ `using FChaosVDDataDataChannel = Chaos::VisualDebugger::FChaosVDOptionalDataChannel;`
- L68 _public function_ `TSharedPtr<Chaos::VD::ITraceDataRelayTransport> GetRelayTransportInstance()` — `UE_DEPRECATED(5.8, "Use GetDataTransportInstance instead")`
- L74 _public prototype_ `void SetExternalTraceRelayInstance(const TSharedPtr<Chaos::VD::ITraceDataRelayTransport>& InExternalTraceRelayInstance);` — `UE_DEPRECATED(5.8, "Use SetDataRelayTransportInstance instead")`
- L78 _private prototype_ `virtual void OnInitializeInternal() override;`
- L79 _private prototype_ `virtual void OnTearDownInternal() override;`
- L80 _private prototype_ `virtual void OnRecordingStartedInternal() override;`
- L81 _private prototype_ `virtual void OnRecordingStoppedInternal() override;`
- L82 _private prototype_ `virtual void BuildRecordingStatusInternal(UE::TraceBasedDebuggers::FRecordingStatusMessage& OutStatusMessage) const override;`
- L84 _private prototype_ `void HandleTraceConnectionDetailsUpdated() const;`
- L85 _private prototype_ `bool AddOnScreenRecordingMessage(float DummyDeltaTime = 0.1f);`
- L86 _private prototype_ `void RemoveOnScreenRecordingMessage();`
- L87 _private prototype_ `void HandleCVDRecordingStarted();`
- L88 _private prototype_ `void HandleCVDPostRecordingStarted();`
- L89 _private prototype_ `void HandleCVDRecordingStopped();`
- L90 _private prototype_ `void HandleCVDRecordingStartFailed(const FText& InFailureReason) const;`
- L91 _private prototype_ `void HandlePIEStarted(UGameInstance* GameInstance);`
- L93 _private prototype_ `void HandleDataChannelChanged(TWeakPtr<FChaosVDDataDataChannel> ChannelWeakPtr);`
- L95 _private prototype_ `void SerializeCollisionChannelsNames();`
- L97 _private prototype_ `static FChaosVDParticleMetadata GenerateParticleMetadata(const IPhysicsProxyBase* ParticleProxy, const Chaos::FGeometryParticleHandle* ParticleHandle);`
- L99 _private member_ `FDelegateHandle RecordingStartedHandle;`
- L100 _private member_ `FDelegateHandle PostRecordingStartedHandle;`
- L101 _private member_ `FDelegateHandle RecordingStoppedHandle;`
- L102 _private member_ `FDelegateHandle RecordingStartFailedHandle;`
- L103 _private member_ `uint64 CVDRecordingMessageKey = 0;`
- L106 _private member_ `FDelegateHandle PIEStartedHandle;`
- L109 _private member_ `FTSTicker::FDelegateHandle DeferredShowMessageOnScreenHandle;`
- L110 _private member_ `static bool bIsInstantiated;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Chaos`
- L12 _namespace_ `namespace VD` (scope `Chaos`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L38 _namespace_ `namespace Chaos`
- L38 _namespace_ `namespace VisualDebugger` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosVDRemoteSessionsManager.h` (Public)


#### struct `FChaosVDSessionPing`  
`struct UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FSessionPing instead.") FChaosVDSessionPing : UE::TraceBasedDebuggers::FSessionPing`  
_L21-23_
- inherits: `UE::TraceBasedDebuggers::FSessionPing`

#### struct `FChaosVDSessionPong`  
`struct UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FSessionPong instead.") FChaosVDSessionPong : UE::TraceBasedDebuggers::FSessionPong`  
_L25-27_
- inherits: `UE::TraceBasedDebuggers::FSessionPong`

#### struct `FChaosVDStopRecordingCommandMessage`  
`struct FChaosVDStopRecordingCommandMessage : public UE::TraceBasedDebuggers::FStopRecordingCommandMessage`  
_L31-34_
- reflection: `USTRUCT()`
- inherits: `UE::TraceBasedDebuggers::FStopRecordingCommandMessage`
- desc: Message specific to ChaosVD to send a stop recording command.

#### struct `FChaosVDRecordingStatusMessage`  
`struct UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FRecordingStatusMessage instead.") FChaosVDRecordingStatusMessage : UE::TraceBasedDebuggers::FRecordingStatusMessage`  
_L37-50_
- inherits: `UE::TraceBasedDebuggers::FRecordingStatusMessage`
- L39 _public function_ `FChaosVDRecordingStatusMessage()`
- L43 _public prototype_ `FChaosVDRecordingStatusMessage(const FChaosVDRecordingStatusMessage& Other) = default;`
- L44 _public prototype_ `FChaosVDRecordingStatusMessage(FChaosVDRecordingStatusMessage&& Other) noexcept = default;`
- L45 _public prototype_ `FChaosVDRecordingStatusMessage& operator=(const FChaosVDRecordingStatusMessage& Other) = default;`
- L46 _public prototype_ `FChaosVDRecordingStatusMessage& operator=(FChaosVDRecordingStatusMessage&& Other) noexcept = default;`
- L49 _public member_ `FChaosVDTraceDetails TraceDetails;` — `UE_DEPRECATED(5.7, "Please get the trace details directly from the session info object")`

#### struct `FChaosVDTraceConnectionDetailsMessage`  
`struct UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FTraceConnectionDetailsMessage instead.") FChaosVDTraceConnectionDetailsMessage : UE::TraceBasedDebuggers::FTraceConnectionDetailsMessage`  
_L52-55_
- inherits: `UE::TraceBasedDebuggers::FTraceConnectionDetailsMessage`
- L54 _public member_ `FChaosVDTraceDetails TraceDetails;`

#### struct `FChaosVDRelayTraceDataMessage`  
`struct FChaosVDRelayTraceDataMessage`  
_L59-72_
- reflection: `USTRUCT()`
- L63 _public function_ `FChaosVDRelayTraceDataMessage()`
- L68 _public member_ `FGuid InstanceId = FGuid();` — `UPROPERTY()`
- L71 _public member_ `TArray<uint8> DataBuffer;` — `UPROPERTY()`

#### enum `ERelayThrottlingState`  
`enum class ERelayThrottlingState : uint8`  
_L75-79_
- reflection: `UENUM()`
- L77 _public enumerator_ `Inactive`
- L78 _public enumerator_ `Active`

#### struct `FChaosVDRelayTraceStatusMessage`  
`struct FChaosVDRelayTraceStatusMessage`  
_L82-98_
- reflection: `USTRUCT()`
- L86 _public function_ `FChaosVDRelayTraceStatusMessage()`
- L91 _public member_ `FGuid InstanceId = FGuid();` — `UPROPERTY()`
- L94 _public member_ `int64 QueuedDataBytesNum = 0;` — `UPROPERTY()`
- L97 _public member_ `ERelayThrottlingState ThrottlingState = ERelayThrottlingState::Inactive;` — `UPROPERTY()`

#### struct `FChaosVDDataChannelState`  
`struct FChaosVDDataChannelState`  
_L101-115_
- reflection: `USTRUCT()`
- L106 _public member_ `FString ChannelName;` — `UPROPERTY()`
- L109 _public member_ `bool bIsEnabled = false;` — `UPROPERTY()`
- L112 _public member_ `bool bCanChangeChannelState = false;` — `UPROPERTY()`
- L114 _public member_ `bool bWaitingUpdatedState = false;`

#### struct `FChaosVDChannelStateChangeCommandMessage`  
`struct FChaosVDChannelStateChangeCommandMessage`  
_L118-124_
- reflection: `USTRUCT()`
- L123 _public member_ `FChaosVDDataChannelState NewState;` — `UPROPERTY()`

#### struct `FChaosVDChannelStateChangeResponseMessage`  
`struct FChaosVDChannelStateChangeResponseMessage`  
_L127-136_
- reflection: `USTRUCT()`
- L132 _public member_ `FGuid InstanceID = FGuid();` — `UPROPERTY()`
- L135 _public member_ `FChaosVDDataChannelState NewState;` — `UPROPERTY()`

#### struct `FChaosVDFullSessionInfoResponseData`  
`struct FChaosVDFullSessionInfoResponseData`  
_L143-149_
- reflection: `USTRUCT()`
- desc: Structure specific to ChaosVD to store the states of the data channels. The struct is stored as the DebuggerSpecificData for the message type UE::TraceBasedDebuggers::FFullSessionInfoResponseMessage.
- L148 _public member_ `TArray<FChaosVDDataChannelState> DataChannelsStates;` — `UPROPERTY()`

#### struct `FChaosVDSessionData`  
`struct FChaosVDSessionData`  
_L157-162_
- reflection: `USTRUCT()`
- desc: Structure specific to ChaosVD to store the states of the data channels in the session info struct. The struct is stored as a DebuggerSpecificSessionData inside UE::TraceBasedDebuggers::FSessionInfo and get be retrieved using GetDebuggerData<FChaosVDSessionData>().
- L161 _public member_ `TMap<FString, FChaosVDDataChannelState> DataChannelsStatesByName;`

#### struct `FChaosVDRemoteSessionsHandler`  
`struct FChaosVDRemoteSessionsHandler : UE::TraceBasedDebuggers::IRemoteSessionsHandler`  
_L168-174_
- inherits: `UE::TraceBasedDebuggers::IRemoteSessionsHandler`
- desc: Remote sessions handler to handle ChaosVD specific message types.
- L170 _public prototype_ `virtual void OnCreatingMessageEndpoint(const TSharedPtr<UE::TraceBasedDebuggers::FRemoteSessionsManager>&, FMessageEndpointBuilder&) override;`
- L171 _public prototype_ `virtual void OnSubscribingMessageTypes(const TSharedPtr<UE::TraceBasedDebuggers::FRemoteSessionsManager>&, FMessageEndpoint&) override;`
- L172 _public prototype_ `virtual void OnBuildingFullSessionInfoResponseMessage(UE::TraceBasedDebuggers::FFullSessionInfoResponseMessage&) override;`
- L173 _public prototype_ `virtual void OnHandlingFullSessionInfoResponseMessage(const UE::TraceBasedDebuggers::FFullSessionInfoResponseMessage&, const TSharedPtr<UE::TraceBasedDebuggers::FSessionInfo>&) override;`

#### struct `FChaosVDFullSessionInfoRequestMessage`  
`struct UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FFullSessionInfoRequestMessage instead.") FChaosVDFullSessionInfoRequestMessage`  
_L179-181_

#### struct `FChaosVFFullSessionInfoResponseMessage`  
`struct UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FFullSessionInfoResponseMessage instead.") FChaosVFFullSessionInfoResponseMessage : UE::TraceBasedDebuggers::FFullSessionInfoResponseMessage`  
_L183-186_
- inherits: `UE::TraceBasedDebuggers::FFullSessionInfoResponseMessage`
- L185 _public member_ `TArray<FChaosVDDataChannelState> DataChannelsStates;`

#### enum `EChaosVDRemoteSessionAttributes`  
`enum class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::ERemoteSessionAttributes instead.") EChaosVDRemoteSessionAttributes`  
_L188-194_
- L190 _public enumerator_ `None = 0`
- L191 _public enumerator_ `SupportsDataChannelChange = 1 << 0`
- L192 _public enumerator_ `CanExpire = 1 << 1`
- L193 _public enumerator_ `IsMultiSessionWrapper = 1 << 2`

#### enum `EChaosVDRemoteSessionReadyState`  
`enum class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::ERemoteSessionReadyState instead.") EChaosVDRemoteSessionReadyState : uint8`  
_L197-201_
- L199 _public enumerator_ `Ready`
- L200 _public enumerator_ `Busy`

#### struct `FChaosVDSessionInfo`  
`struct UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FSessionInfo instead.") FChaosVDSessionInfo`  
_L203-263_
- L205 _public function_ `explicit FChaosVDSessionInfo() : InstanceId(FGuid()), SessionTypeAttributes(EChaosVDRemoteSessionAttributes::CanExpire | EChaosVDRemoteSessionAttributes::SupportsDataChannelChange)`
- L210 _public prototype_ `virtual ~FChaosVDSessionInfo() = default;`
- L214 _protected function_ `explicit FChaosVDSessionInfo(EChaosVDRemoteSessionAttributes InSessionTypeAttributes) : SessionTypeAttributes(InSessionTypeAttributes)`
- L220 _public member_ `FGuid InstanceId;`
- L221 _public member_ `FString SessionName;`
- L222 _public member_ `FMessageAddress Address;`
- L223 _public member_ `FDateTime LastPingTime;`
- L224 _public member_ `EBuildTargetType BuildTargetType = EBuildTargetType::Unknown;`
- L225 _public member_ `EChaosVDRemoteSessionReadyState ReadyState = EChaosVDRemoteSessionReadyState::Ready;`
- L227 _public member_ `FChaosVDRecordingStatusMessage LastKnownRecordingState;`
- L229 _public member_ `TMap<FString, FChaosVDDataChannelState> DataChannelsStatesByName;`
- L231 _public prototype_ `const FChaosVDTraceDetails& GetConnectionDetails();`
- L233 _public prototype_ `virtual bool IsRecording() const;`
- L234 _public prototype_ `virtual uint64 GetBufferedBytesNum() const;`
- L237 _public prototype_ `virtual EChaosVDRecordingMode GetRecordingMode() const;` — `UE_DEPRECATED(5.8, "This method will no longer be used and there is not a replacement planned.")`
- L239 _public prototype_ `virtual EChaosVDRecordingMode GetLastRequestedRecordingMode() const final;` — `UE_DEPRECATED(5.8, "This method will no longer be used and there is not a replacement planned.")`
- L241 _public prototype_ `virtual void SetLastRequestedRecordingMode(EChaosVDRecordingMode NewRecordingMode) final;` — `UE_DEPRECATED(5.8, "This method will no longer be used and there is not a replacement planned.")`
- L245 _public prototype_ `virtual bool IsConnected() const final;` — `UE_DEPRECATED(5.7, "This method will no longer be used and there is not a replacement planned.")`
- L247 _public function_ `EChaosVDRemoteSessionAttributes GetSessionTypeAttributes() const`
- L252 _public prototype_ `void SetReceivedBytesPerSecond(uint64 InNewBytesPerSecond);`
- L253 _public prototype_ `uint64 GetReceivedBytesPerSecond() const;`
- L257 _protected member_ `EChaosVDRecordingMode LastRequestedRecordingMode = EChaosVDRecordingMode::Invalid;` — `UE_DEPRECATED(5.8, "This method will no longer be used and there is not a replacement planned.")`
- L258 _protected member_ `FChaosVDTraceDetails LastKnownConnectionDetails;`
- L260 _protected member_ `uint64 ReceivedBytesPerSecond = 0;`
- L262 _protected member_ `const EChaosVDRemoteSessionAttributes SessionTypeAttributes;`

#### struct `FChaosVDMultiSessionInfo`  
`struct UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FMultiSessionInfo instead.") FChaosVDMultiSessionInfo : public FChaosVDSessionInfo`  
_L265-295_
- inherits: `FChaosVDSessionInfo`
- L267 _public function_ `explicit FChaosVDMultiSessionInfo() : FChaosVDSessionInfo(EChaosVDRemoteSessionAttributes::IsMultiSessionWrapper)`
- L271 _public prototype_ `virtual ~FChaosVDMultiSessionInfo() override = default;`
- L273 _public prototype_ `virtual bool IsRecording() const override;`
- L274 _public prototype_ `virtual uint64 GetBufferedBytesNum() const override;`
- L277 _public prototype_ `virtual EChaosVDRecordingMode GetRecordingMode() const override;` — `UE_DEPRECATED(5.8, "This method will no longer be used and there is not a replacement planned.")`
- L280 _public function_ `template<typename TCallback> void EnumerateInnerSessions(const TCallback& Callback) const`
- L294 _public member_ `TMap<FGuid, TWeakPtr<FChaosVDSessionInfo>> InnerSessionsByInstanceID;`

#### class `FChaosVDRemoteSessionsManager`  
`class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FRemoteSessionsManager instead.") FChaosVDRemoteSessionsManager : public UE::TraceBasedDebuggers::FRemoteSessionsManager`  
_L306-412_
- inherits: `UE::TraceBasedDebuggers::FRemoteSessionsManager`
- desc: Object that is able to discover, issue and execute commands back and forth between CVD and client/server/editor instances
- L309 _public prototype_ `FChaosVDRemoteSessionsManager();`
- L312 _public prototype_ `void Initialize(const TSharedPtr<IMessageBus>& InMessageBus);` — `UE_DEPRECATED(5.7, "Use Initialize()")`
- L314 _public function_ `FChaosVDSessionDiscoverDelegate& OnSessionDiscovered()`
- L319 _public function_ `FChaosVDSessionDiscoverDelegate& OnSessionExpired()`
- L329 _public prototype_ `void SendStartRecordingCommand(const FMessageAddress& InDestinationAddress, const FChaosVDStartRecordingCommandMessage& RecordingStartCommandParams);` — Issues a command to the provided address that will start a CVD recording @param InDestinationAddress Message bus address that will execute the command @param RecordingStartCommandParams Desired parameters to be used to start the recording
- L336 _public prototype_ `void SendDataChannelStateChangeCommand(const FMessageAddress& InDestinationAddress, const FChaosVDChannelStateChangeCommandMessage& InNewStateData);` — Issues a command to the provided address to change the state of a data channel @param InDestinationAddress Message bus address that will execute the command @param InNewStateData New data channel state to apply in the receiving instance
- L342 _public prototype_ `TWeakPtr<FChaosVDSessionInfo> GetSessionInfo(FGuid Id);` — Returns the session info object for the provided ID @param Id CVD SessionID
- L347 _public prototype_ `TWeakPtr<FChaosVDSessionInfo> GetFirstAvailableSingleSessionInfo();` — Returns the first available session info
- L354 _public function_ `template<typename CallbackType> void EnumerateActiveSessions(const CallbackType& Callback)` — Iterates through all active and valid cvd sessions, and executes the provided callback to it. if the callbacks returns false, the iteration will stop
- L374 _public prototype_ `void PublishRecordingStatusUpdate(const FChaosVDRecordingStatusMessage& InUpdateMessage);` — Broadcast to the network a recording state update @param InUpdateMessage latest recording state of the issuing instance
- L380 _public prototype_ `void PublishTraceConnectionDetailsUpdate(const FChaosVDTraceConnectionDetailsMessage& InUpdateMessage);` — Broadcast to the network new trace connection details as they become available @param InUpdateMessage latest connection details
- L386 _public prototype_ `void PublishDataChannelStateChangeUpdate(const FChaosVDChannelStateChangeResponseMessage& InNewStateData);` — Broadcast to the network a data channel state update @param InNewStateData latest data channel state of the issuing instance
- L391 _public function_ `FChaosVDRecordingStateChangeDelegate& OnSessionRecordingStarted()` — Delegate that broadcast when a recording was started in a session (either local or remote)
- L399 _public function_ `FChaosVDRecordingStateChangeDelegate& OnSessionRecordingStopped()` — Delegate that broadcast when a recording stops in a session (either local or remote)
- L405 _private member_ `TMap<FGuid, TSharedPtr<FChaosVDSessionInfo>> ActiveSessionsByInstanceId;`
- L407 _private member_ `FChaosVDSessionDiscoverDelegate SessionDiscoveredDelegate;`
- L408 _private member_ `FChaosVDSessionDiscoverDelegate SessionExpiredDelegate;`
- L410 _private member_ `FChaosVDRecordingStateChangeDelegate RecordingStartedDelegate;`
- L411 _private member_ `FChaosVDRecordingStateChangeDelegate RecordingStoppedDelegate;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API CHAOSSOLVERENGINE_API`
- L297 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosVDRemoteSession, Log, VeryVerbose);`
- L297 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosVDRemoteSession, Log, VeryVerbose);`
- L300 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDRecordingStateChangeDelegate, TWeakPtr<FChaosVDSessionInfo> Session) UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FSessionLifetimeDelegate()") DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDSessionDiscoverDelegate, FGuid SessionID) class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FRemoteSessionsManager instead.") FChaosVDRemoteSessionsManager : public UE::TraceBasedDebuggers::FRemoteSessionsManager { public: FChaosVDRemoteSessionsManager(); UE_DEPRECATED(5.7, "Use Initialize()") void Initialize(const TSharedPtr<IMessageBus>& InMessageBus); FChaosVDSessionDiscoverDelegate& OnSessionDiscovered() { return SessionDiscoveredDelegate; } FChaosVDSessionDiscoverDelegate& OnSessionExpired() { return SessionExpiredDelegate; } void SendStartRecordingCommand(const FMessageAddress& InDestinationAddress, const FChaosVDStartRecordingCommandMessage& RecordingStartCommandParams); void SendDataChannelStateChangeCommand(const FMessageAddress& InDestinationAddress, const FChaosVDChannelStateChangeCommandMessage& InNewStateData); /** * Returns the session info object for the provided ID`
- L303 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FChaosVDSessionDiscoverDelegate, FGuid SessionID) class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FRemoteSessionsManager instead.") FChaosVDRemoteSessionsManager : public UE::TraceBasedDebuggers::FRemoteSessionsManager { public: FChaosVDRemoteSessionsManager(); UE_DEPRECATED(5.7, "Use Initialize()") void Initialize(const TSharedPtr<IMessageBus>& InMessageBus); FChaosVDSessionDiscoverDelegate& OnSessionDiscovered() { return SessionDiscoveredDelegate; } FChaosVDSessionDiscoverDelegate& OnSessionExpired() { return SessionExpiredDelegate; } void SendStartRecordingCommand(const FMessageAddress& InDestinationAddress, const FChaosVDStartRecordingCommandMessage& RecordingStartCommandParams); void SendDataChannelStateChangeCommand(const FMessageAddress& InDestinationAddress, const FChaosVDChannelStateChangeCommandMessage& InNewStateData); TWeakPtr<FChaosVDSessionInfo> GetSessionInfo(FGuid Id);`

### `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosVDTraceRelayTransport.h` (Public)


#### struct `Chaos::VD::FRelayConnectionInfo`  
`struct UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::FRelayConnectionInfo instead") FRelayConnectionInfo`  
_L13-18_
- desc: Structure containing the details necessary to connect to a relay instance
- L15 _public member_ `FString Address;`
- L16 _public member_ `uint16 Port = 0;`
- L17 _public member_ `TArray<uint8> CertificateAuthority;`

#### enum `Chaos::VD::EConnectionAttemptResult`  
`enum UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::EConnectionAttemptResult instead") EConnectionAttemptResult`  
_L31-37_
- desc: Possible connection attempt results
- L33 _public enumerator_ `NotStarted`
- L34 _public enumerator_ `InProgress`
- L35 _public enumerator_ `Success`
- L36 _public enumerator_ `Failed`

#### class `Chaos::VD::ITraceDataRelayTransport`  
`class UE_DEPRECATED(5.8, "Use UE::TraceBasedDebuggers::IDataRelayTransport instead") ITraceDataRelayTransport`  
_L43-60_
- desc: Interface for any CVD trace relay transport implementation
- L46 _public prototype_ `virtual ~ITraceDataRelayTransport() = default;`
- L48 _public prototype_ `virtual void Initialize() = 0;`
- L49 _public prototype_ `virtual void Shutdown() = 0;`
- L51 _public prototype_ `DECLARE_DELEGATE_OneParam(FProcessReceivedRelayDataDelegate, const TConstArrayView<uint8> DataPacket);`
- L52 _public prototype_ `virtual void RegisterRelayDataReceiverForSessionID(FGuid RemoteSessionID, const FProcessReceivedRelayDataDelegate& InProcessDataDelegate) = 0;`
- L53 _public prototype_ `virtual void UnregisterRelayDataReceiverForSessionID(FGuid RemoteSessionID) = 0;`
- L55 _public prototype_ `virtual void RelayTraceDataFromWriter(FRelayTraceWriter& InRelayTraceWriter) = 0;`
- L57 _public prototype_ `virtual FRelayConnectionInfo GetConnectionInfo() = 0;`
- L58 _public prototype_ `virtual EConnectionAttemptResult ConnectToRelay(FGuid RemoteSessionID, const FRelayConnectionInfo ConnectionInfo) = 0;`
- L59 _public prototype_ `virtual EConnectionAttemptResult GetConnectionAttemptResult(FGuid RemoteSessionID) = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L9 _namespace_ `namespace VD` (scope `Chaos`)
- L26 _namespace_ `namespace Chaos`
- L26 _namespace_ `namespace VD` (scope `Chaos`)
- L51 _delegate_ `DECLARE_DELEGATE_OneParam(FProcessReceivedRelayDataDelegate, const TConstArrayView<uint8> DataPacket);`
