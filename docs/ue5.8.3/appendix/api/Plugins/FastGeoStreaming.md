# Plugins / FastGeoStreaming

- module root: `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming`
- headers: 33; symbols: 1286
- symbol kinds: class=30, delegate=3, enum=12, enumerator=40, function=203, member=305, namespace=3, prototype=637, struct=24, typedef=29
- PrivateDependencyModuleNames: Chaos, Core, CoreUObject, Engine, NavigationSystem, PhysicsCore, RHI, RenderCore, TraceLog, UnrealEd

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoAsyncRenderStateJobQueue.h` (Internal)


#### struct `FFastGeoAsyncRenderStateJobQueue`  
`struct FFastGeoAsyncRenderStateJobQueue`  
_L11-101_
- L13 _public prototype_ `FFastGeoAsyncRenderStateJobQueue(FSceneInterface* Scene);`
- L14 _public prototype_ `~FFastGeoAsyncRenderStateJobQueue();`
- L43 _public function_ `friend inline uint32 GetTypeHash(const FJob& InJob)`
- L76 _public prototype_ `void Tick(bool bForceWaitCompletion);`
- L77 _public prototype_ `void AddJob(const FJob& Job);`
- L78 _public prototype_ `bool IsCompleted() const;`
- L82 _private prototype_ `void Launch();`
- L83 _private prototype_ `void WaitForAsyncTasksExecution();`
- L84 _private prototype_ `bool AreAsyncTasksExecuted() const;`
- L85 _private prototype_ `void OnAsyncTasksExecuted();`
- L86 _private prototype_ `void OnUpdateLevelStreamingDone();`
- L87 _private prototype_ `void TriggerIsReadyToRunAsyncTasksEvent();`
- L89 _private member_ `FSceneInterface* Scene;`
- L90 _private member_ `FDelegateHandle OnAllLevelsChangedHandle;`
- L91 _private typedef_ `using FJobs = TUniquePtr<FJobSet>;`
- L92 _private member_ `FJobs PendingJobs;`
- L97 _private member_ `TArray<FJobs> PipedJobs;` — PipedJobs and PipeTasks are parallel arrays kept aligned by index: PipeTasks[i] is the pipe task that executes PipedJobs[i]. Both are appended to in Launch() and removed at matching indices in Tick() and OnAsyncTasksExecuted(). All mutations must preserve the alignment invariant (PipedJobs.Num() == PipeTasks.Num()).
- L98 _private member_ `TArray<UE::Tasks::FTask> PipeTasks;`
- L99 _private member_ `TOptional<UE::Tasks::FTaskEvent> IsReadyToRunAsyncTasksEvent;`
- L100 _private member_ `UE::Tasks::FPipe Pipe{ TEXT("FastG`

#### enum `FFastGeoAsyncRenderStateJobQueue::EJobType`  
`enum class EJobType`  
_L16-25_
- L18 _public enumerator_ `PrecachePSOs`
- L19 _public enumerator_ `CreateRenderState`
- L20 _public enumerator_ `DestroyRenderState`
- L22 _public enumerator_ `DeferredCreateRenderState`
- L23 _public enumerator_ `RecreateRenderState`

#### struct `FFastGeoAsyncRenderStateJobQueue::FJob`  
`struct FJob`  
_L27-50_
- L29 _public function_ `FJob(UFastGeoContainer* InFastGeo, EJobType InType) : FastGeo(InFastGeo) , Type(InType)`
- L34 _public function_ `bool IsValid() const`
- L35 _public prototype_ `void Execute() const;`
- L36 _public prototype_ `void OnPostExecute_GameThread() const;`
- L38 _public function_ `inline bool operator == (const FJob& Other) const`
- L48 _public member_ `UFastGeoContainer* FastGeo;`
- L49 _public member_ `EJobType Type;`

#### struct `FFastGeoAsyncRenderStateJobQueue::FJobSet`  
`struct FJobSet`  
_L52-74_
- L54 _public function_ `void Add(const FJob& Job)`
- L59 _public function_ `int32 Remove(const FJob& Job)`
- L64 _public function_ `bool IsEmpty() const`
- L69 _public prototype_ `void Execute() const;`
- L70 _public prototype_ `void OnPostExecute_GameThread() const;`
- L73 _private member_ `TSet<FJob> Jobs;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoComponent.h` (Internal)


#### enum `ESceneProxyCreationError`  
`enum class ESceneProxyCreationError`  
_L31-36_
- L33 _public enumerator_ `None`
- L34 _public enumerator_ `WaitingPSOs`
- L35 _public enumerator_ `InvalidMesh`

#### class `FFastGeoComponent`  
`class FFastGeoComponent : public IFastGeoElement`  
_L38-148_
- inherits: `IFastGeoElement`
- L41 _public typedef_ `typedef IFastGeoElement Super;`
- L44 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L46 _public prototype_ `FFastGeoComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L47 _public prototype_ `FFastGeoComponent(const FFastGeoComponent& Other);`
- L48 _public prototype_ `virtual ~FFastGeoComponent() = default;`
- L51 _public prototype_ `virtual void InitializeFromComponent(UActorComponent* Component);`
- L53 _public prototype_ `virtual void Serialize(FArchive& Ar);`
- L54 _public function_ `virtual void InitializeDynamicProperties()`
- L55 _public prototype_ `virtual void ApplyWorldTransform(const FTransform& InTransform);`
- L56 _public prototype_ `UWorld* GetWorld() const;`
- L57 _public prototype_ `FSceneInterface* GetScene() const;`
- L58 _public prototype_ `FPhysScene* GetPhysicsScene() const;`
- L59 _public prototype_ `float GetWorldTimeSeconds() const;`
- L60 _public prototype_ `UFastGeoContainer* GetOwnerContainer() const;`
- L61 _public prototype_ `FFastGeoComponentCluster* GetOwnerComponentCluster() const;`
- L62 _public function_ `int32 GetComponentIndex() const`
- L63 _public prototype_ `FLinearColor GetDebugColor() const;`
- L67 _public function_ `virtual void ForEachMaterial(TFunctionRef<void(UMaterialInterface*, bool bIsNaniteOverride)> Func) const` — Enumerates all materials this component references, including Nanite overrides. bIsNaniteOverride is true for materials obtained via GetNaniteOverride().
- L70 _public function_ `virtual void UpdateVisibility()` — Render interface
- L71 _public prototype_ `virtual bool ShouldComponentAddToRenderScene() const;`
- L72 _public function_ `virtual void CreateRenderState(FRegisterComponentContext* Context)`
- L73 _public function_ `virtual void DestroyRenderState(FFastGeoDestroyRenderStateContext* Context)`
- L74 _public prototype_ `void MarkRenderStateDirty(bool bEvenIfNotCreated);`
- L75 _public prototype_ `bool IsRenderStateDirty() const;`
- L76 _public prototype_ `bool IsRenderStateDelayed() const;`
- L77 _public prototype_ `bool IsRenderStateCreated() const;`
- L80 _public function_ `virtual bool IsCollisionEnabled() const` — Physics interface
- L81 _public function_ `virtual UBodySetup* GetBodySetup() const`
- L84 _public function_ `virtual void OnAsyncCreatePhysicsStateBegin_GameThread()` — Async physics state creation/destruction
- L85 _public prototype_ `virtual void OnAsyncCreatePhysicsState();`
- L86 _public prototype_ `virtual void OnAsyncCreatePhysicsStateEnd_GameThread();`
- L87 _public prototype_ `virtual void OnAsyncDestroyPhysicsStateBegin_GameThread();`
- L88 _public prototype_ `virtual void OnAsyncDestroyPhysicsState();`
- L89 _public prototype_ `virtual void OnAsyncDestroyPhysicsStateEnd_GameThread();`
- L90 _public function_ `virtual void GetBodyInstances(TArray<FBodyInstance*>& OutBodyInstances)`
- L94 _public prototype_ `virtual bool ShouldPrecachePSOs() const;` — PSO Precaching interface
- L95 _public function_ `virtual void PrecachePSOs_Concurrent()`
- L96 _public prototype_ `virtual FPSOPrecacheComponentData& GetPSOPrecacheComponentData() = 0;`
- L97 _public prototype_ `virtual const FPSOPrecacheComponentData& GetPSOPrecacheComponentData() const = 0;`
- L99 _public function_ `virtual bool NeedsPSORecreate() const` — Returns true if the proxy was created with a fallback material and needs recreation when PSO completes.
- L104 _protected member_ `int32 ComponentIndex = INDEX_NONE;` — Persistent Data
- L105 _protected member_ `FTransform LocalTransform{ FTransform::Identity };`
- L106 _protected member_ `FTransform WorldTransform{ FTransform::Identity };`
- L110 _protected member_ `FFastGeoComponentCluster* Owner = nullptr;` — Transient Data
- L117 _protected member_ `TUniquePtr<FRWLock> Lock;` — Per-component RWLock guarding the (ProxyState, scene-proxy pointer) pair so readers always see a consistent tuple. Reader: render-thread UpdateVisibility lambda (cluster). Writers: Create/DestroyRenderState (worker in cooked-async, GT in sync) and the cluster UpdateVisibility helpers. Spans Scene->AddPrimitive in Create because the proxy pointer is populated by AddPrimitive and must become visible atomically with ProxyState=Created.
- L129 _protected member_ `EPhysicsStateCreation PhysicsStateCreation = EPhysicsStateCreation::NotCreated;`
- L141 _protected member_ `EProxyCreationState ProxyState = EProxyCreationState::None;`
- L142 _protected member_ `bool bRenderStateDirty = false;`
- L145 _private prototype_ `void SetOwnerComponentCluster(FFastGeoComponentCluster* InOwner);`

#### enum `FFastGeoComponent::EPhysicsStateCreation`  
`enum EPhysicsStateCreation`  
_L121-127_
- desc: Physics state
- L123 _public enumerator_ `NotCreated`
- L124 _public enumerator_ `Creating`
- L125 _public enumerator_ `Created`
- L126 _public enumerator_ `Destroying`

#### enum `FFastGeoComponent::EProxyCreationState`  
`enum class EProxyCreationState : uint8`  
_L133-139_
- desc: Render state
- L135 _public enumerator_ `None` — Constructed/Initialized
- L136 _public enumerator_ `Creating` — Actively creating the proxy
- L137 _public enumerator_ `Created` — Proxy is now created
- L138 _public enumerator_ `Delayed` — Proxy creation delayed (used when PSO precaching is not ready when creating proxy)

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoComponentCluster.h` (Internal)


#### class `FFastGeoComponentCluster`  
`class FFastGeoComponentCluster : public IFastGeoElement`  
_L26-215_
- inherits: `IFastGeoElement`
- L29 _public typedef_ `typedef IFastGeoElement Super;`
- L32 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L34 _public prototype_ `FFastGeoComponentCluster(UFastGeoContainer* InOwner = nullptr, FName InName = NAME_None, FFastGeoElementType InType = Type);`
- L36 _public prototype_ `FFastGeoComponentCluster(const FFastGeoComponentCluster& InOther);`
- L38 _public prototype_ `virtual ~FFastGeoComponentCluster() = default;`
- L39 _public function_ `virtual void OnRegister()`
- L40 _public function_ `virtual void OnUnregister()`
- L41 _public prototype_ `virtual void Serialize(FArchive& Ar);`
- L42 _public function_ `virtual bool IsVisible() const`
- L44 _public prototype_ `UFastGeoContainer* GetOwnerContainer() const;`
- L45 _public prototype_ `ULevel* GetLevel() const;`
- L46 _public prototype_ `FFastGeoComponent* GetComponent(uint32 InComponentTypeID, int32 InComponentIndex);`
- L47 _public function_ `const FString& GetName() const`
- L48 _public function_ `int32 GetComponentClusterIndex() const`
- L49 _public prototype_ `void UpdateVisibility();`
- L51 _public prototype_ `bool HasComponents() const;`
- L52 _public prototype_ `virtual FFastGeoComponent& AddComponent(FFastGeoElementType InComponentType);`
- L55 _public function_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext)`
- L56 _public prototype_ `void SerializeWithComponentFilter(FArchive& Ar, TFunctionRef<bool(const FFastGeoComponent&)> ShouldSerializeComponent);`
- L60 _public function_ `template <typename TComponent = const FFastGeoComponent, typename TFunc> void ForEachComponent(TFunc&& InFunc) const`
- L66 _public function_ `template <typename TComponent = FFastGeoComponent, typename TFunc> void ForEachComponent(TFunc&& InFunc)`
- L72 _public function_ `template <typename TComponent = const FFastGeoComponent, typename TFunc> bool ForEachComponentBreakable(TFunc&& InFunc) const`
- L78 _public function_ `template <typename TComponent = FFastGeoComponent, typename TFunc> bool ForEachComponentBreakable(TFunc&& InFunc)`
- L85 _protected member_ `UFastGeoContainer* Owner;` — Transient Data
- L88 _protected member_ `FString Name;` — Persistent Data
- L89 _protected member_ `int32 ComponentClusterIndex;`
- L91 _protected member_ `TArray<FFastGeoStaticMeshComponent> StaticMeshComponents;`
- L92 _protected member_ `TArray<FFastGeoInstancedStaticMeshComponent> InstancedStaticMeshComponents;`
- L93 _protected member_ `TArray<FFastGeoSkinnedMeshComponent> SkinnedMeshComponents;`
- L94 _protected member_ `TArray<FFastGeoInstancedSkinnedMeshComponent> InstancedSkinnedMeshComponents;`
- L95 _protected member_ `TArray<FFastGeoProceduralISMComponent> ProceduralISMComponents;`
- L96 _protected member_ `TArray<FFastGeoDecalComponent> DecalComponents;`
- L97 _protected member_ `TArray<FFastGeoRectLightComponent> RectLightComponents;`
- L98 _protected member_ `TArray<FFastGeoSpotLightComponent> SpotLightComponents;`
- L99 _protected member_ `TArray<FFastGeoPointLightComponent> PointLightComponents;`
- L103 _protected function_ `template <typename Func> void ForEachComponentArray(Func&& InFunc)` — Iterates all component arrays. Lambda can return void (non-breakable) or bool (return false to break).
- L130 _protected function_ `template <typename Func> void ForEachComponentArray(Func&& InFunc) const`
- L139 _protected function_ `template <typename ThisType, typename TComponent, typename TFunc> static void ForEachComponent(ThisType* Self, TFunc&& InFunc)`
- L165 _protected function_ `template <typename ThisType, typename TComponent, typename TFunc> static bool ForEachComponentBreakable(ThisType* Self, TFunc&& InFunc)`
- L204 _private prototype_ `int32 StripRenderOnlyComponents();`
- L206 _private prototype_ `void ForceUpdateVisibility(const TArray<FFastGeoPrimitiveComponent*>& Components, int32 UpdateCounter);`
- L207 _private prototype_ `void ForceUpdateVisibilityOrDeferTask(const TArray<FFastGeoPrimitiveComponent*>& Components, int32 UpdateCounter);`
- L208 _private prototype_ `void UpdateVisibility_Internal(TArray<FFastGeoPrimitiveComponent*>&& ShowComponents, TArray<FFastGeoPrimitiveComponent*>&& HideComponents, int32 UpdateCounter = 0);`
- L209 _private prototype_ `void InitializeDynamicProperties();`
- L210 _private prototype_ `void SetOwnerContainer(UFastGeoContainer* InOwner);`
- L211 _private prototype_ `void SetComponentClusterIndex(int32 InComponentClusterIndex);`

#### Free symbols / members of external scopes

- L106 _function_ `` (scope `FFastGeoComponentCluster::ForEachComponentArray`)
- L142 _function_ `` (scope `FFastGeoComponentCluster::ForEachComponent`)
- L143 _typedef_ `typedef typename TDecay<decltype(InArray)>::Type ArrayType;` (scope `FFastGeoComponentCluster::ForEachComponent::__anon7bfc6bc80202`)
- L144 _typedef_ `using TArrayComponent = typename ArrayType::ElementType;` (scope `FFastGeoComponentCluster::ForEachComponent::__anon7bfc6bc80202`)
- L169 _function_ `` (scope `FFastGeoComponentCluster::ForEachComponentBreakable`)
- L170 _typedef_ `typedef typename TDecay<decltype(InArray)>::Type ArrayType;` (scope `FFastGeoComponentCluster::ForEachComponentBreakable::__anon7bfc6bc80302`)
- L171 _typedef_ `using TArrayComponent = typename ArrayType::ElementType;` (scope `FFastGeoComponentCluster::ForEachComponentBreakable::__anon7bfc6bc80302`)

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoContainer.h` (Internal)


#### struct `FFastGeoCreateRuntimeResult`  
`struct FFastGeoCreateRuntimeResult`  
_L37-44_
- desc: Result of UFastGeoContainer::CreateRuntime.
- L40 _public member_ `UFastGeoContainer* Container = nullptr;` — The created container, or null on failure.
- L43 _public member_ `TArray<FFastGeoComponent*> Components;` — Component pointers built from the container's internal component iteration order.

#### struct `FFastGeoAsyncContext`  
`struct FFastGeoAsyncContext`  
_L54-82_
- desc: Cached world/scene/subsystem/physics pointers. Populated on GT before workers run. Workers read from this instead of performing lookups not safe from generic workers (e.g., subsystem collection access, world time reads, physics scene access). Reset on unregister. Re-populated on re-register. Lifetime: World/Scene/Subsystem all outlive the container's registered state.
- L56 _public prototype_ `void Initialize(UFastGeoContainer& Container);`
- L57 _public function_ `void Reset()`
- L66 _public function_ `bool IsInitialized() const`
- L68 _public function_ `UWorld* GetWorld() const`
- L69 _public function_ `FSceneInterface* GetScene() const`
- L70 _public function_ `FPhysScene* GetPhysicsScene() const`
- L71 _public function_ `UFastGeoWorldSubsystem* GetWorldSubsystem() const`
- L72 _public function_ `float GetTimeSeconds() const`
- L73 _public function_ `void UpdateTimeSeconds(float InTime)`
- L76 _private member_ `bool bInitialized = false;`
- L77 _private member_ `UWorld* World = nullptr;`
- L78 _private member_ `FSceneInterface* Scene = nullptr;`
- L79 _private member_ `FPhysScene* PhysicsScene = nullptr;`
- L80 _private member_ `UFastGeoWorldSubsystem* WorldSubsystem = nullptr;`
- L81 _private member_ `std::atomic<float> TimeSeconds = 0.0f;`

#### struct `FFastGeoMaterialPostLoadInit`  
`struct FFastGeoMaterialPostLoadInit`  
_L89-96_
- desc: Calls ConditionalPostLoad on all materials referenced by the container. Ensures RF_NeedPostLoad is cleared before workers access materials. Permanent - never reset. RF_NeedPostLoad is cleared once.
- L91 _public prototype_ `void Initialize(UFastGeoContainer& Container);`
- L92 _public function_ `bool IsInitialized() const`
- L95 _private member_ `bool bInitialized = false;`

#### struct `FFastGeoMaterialRelevanceInit`  
`struct FFastGeoMaterialRelevanceInit`  
_L104-111_
- desc: Warms UMaterialInterface::CachedRelevance for all materials + default material. Workers use the cached relevance instead of reading GameThreadShaderMap. Permanent - never reset. Cache persists on UMaterialInterface. Applies to async mode only.
- L106 _public prototype_ `void Initialize(UFastGeoContainer& Container);`
- L107 _public function_ `bool IsInitialized() const`
- L110 _private member_ `bool bInitialized = false;`

#### struct `FFastGeoComponentClusterPendingState`  
`struct FFastGeoComponentClusterPendingState`  
_L113-168_
- L115 _public member_ `FFastGeoRenderStateBatch RenderState;`
- L118 _public member_ `FFastGeoRenderStateBatch PrecachePSOState;`
- L141 _public member_ `} PhysicsState;`
- L143 _public function_ `FFastGeoComponentClusterPendingState()`
- L148 _public function_ `void Reset()`
- L157 _public function_ `bool HasAnyPendingState(bool bIncludePSOPrecaching = true) const`

#### struct `FFastGeoComponentClusterPendingState::FPhysicsState`  
`struct FPhysicsState`  
_L121-141_
- L123 _public function_ `FPhysicsState()`
- L128 _public function_ `void Reset()`
- L134 _public function_ `bool IsCompleted() const`
- L139 _public member_ `TArray<FFastGeoComponent*>* ComponentsToProcess;`
- L140 _public member_ `std::atomic<int32> TotalNumProcessed;`

#### class `UFastGeoContainer`  
`class UFastGeoContainer : public UAssetUserData, public IAsyncPhysicsStateProcessor, public IPhysicsBodyInstanceOwnerResolver`  
_L171-600_
- reflection: `UCLASS(Within = Level)`
- inherits: `UAssetUserData,IAsyncPhysicsStateProcessor,IPhysicsBodyInstanceOwnerResolver`
- L189 _public prototype_ `static FFastGeoCreateRuntimeResult CreateRuntime(UWorld* InWorld, FName InDebugName, TFunctionRef<void(FFastGeoComponentCluster&)> InInitCluster, bool bInCollectReferences = true);` — Creates a runtime FastGeoContainer and starts async registration. The subsystem drives registration ticks automatically. Subscribe to GetOnRegistered() for completion notification, or check IsFullyRegistered(). @param InWorld				World in which to create the container. @param InDebugName			Debug name for the container and its component cluster. @param InInitCluster			Callback to populate the component cluster with components. @param bInCollectReferences	Whether to collect asset references via serialization archive. Pass false if the caller manages asset lifetimes externally. @return Result containing the container and an ordered array of component pointers matching the components added in InInitCluster. Container is null on failure.
- L197 _public prototype_ `static void DestroyRuntime(UFastGeoContainer* InFastGeo);` — Destroys a runtime FastGeoContainer created by CreateRuntime. Initiates async unregistration; the subsystem drives completion. @param InFastGeo		The runtime container to destroy. Must satisfy IsRuntime().
- L200 _public function_ `bool IsRuntime() const` — Returns true if this is a runtime (transient) container. Only CreateRuntime sets RF_Transient on FastGeo containers.
- L202 _public prototype_ `void Register();`
- L203 _public prototype_ `void Unregister();`
- L204 _public prototype_ `bool IsRegistering() const;`
- L205 _public prototype_ `bool IsRegistered() const;`
- L206 _public prototype_ `bool IsUnregistering() const;`
- L207 _public prototype_ `bool IsUnregistered() const;`
- L208 _public prototype_ `bool IsFullyRegistered() const;`
- L209 _public prototype_ `bool IsFullyUnregistered() const;`
- L210 _public prototype_ `void Tick(bool bWaitForCompletion = false);`
- L211 _public prototype_ `bool HasAnyPendingTasks(bool bIncludePSOPrecaching = true) const;`
- L214 _public prototype_ `bool HasAnyPendingRegistrationTasks(bool bIncludePSOPrecaching = true) const;` — Returns true if registration-related tasks (create/destroy) are pending. Excludes post-registration PSO recreate work (UseFallbackMaterialUntilPSOPrecached).
- L215 _public prototype_ `bool HasAnyPendingCreateTasks(bool bIncludePSOPrecaching = true) const;`
- L216 _public prototype_ `bool HasAnyPendingDestroyTasks() const;`
- L217 _public prototype_ `void PrecachePSOs();`
- L218 _public prototype_ `UWorld* GetWorld() const;`
- L219 _public prototype_ `ULevel* GetLevel() const;`
- L220 _public prototype_ `FFastGeoComponentCluster* GetComponentCluster(uint32 InComponentClusterTypeID, int32 InComponentClusterIndex);`
- L222 _public prototype_ `TArray<IPrimitiveComponent*> GetPrimitiveComponents() const;`
- L223 _public prototype_ `TArray<IStaticMeshComponent*> GetStaticMeshComponents() const;`
- L226 _public prototype_ `virtual void BeginDestroy() override;`
- L227 _public prototype_ `virtual bool IsReadyForFinishDestroy() override;`
- L228 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L230 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L235 _public prototype_ `virtual IPhysicsBodyInstanceOwner* ResolvePhysicsBodyInstanceOwner(Chaos::FConstPhysicsObjectHandle PhysicsObject) override;`
- L238 _public prototype_ `bool IsUsingSurrogateComponents() const;`
- L239 _public prototype_ `AFastGeoSurrogateActor* GetSurrogateActor() const;`
- L241 _public prototype_ `void AddComponentCluster(FFastGeoComponentCluster* ComponentCluster);`
- L243 _public prototype_ `void InitializeDynamicProperties(bool bInitForPlay = false);`
- L245 _public prototype_ `void OnPrecachePSOsBegin_GameThread();`
- L246 _public prototype_ `void OnPrecachePSOs_Concurrent();`
- L247 _public prototype_ `void OnPrecachePSOsEnd_GameThread();`
- L249 _public prototype_ `void OnCreateRenderStateBegin_GameThread();`
- L250 _public prototype_ `void OnCreateRenderState_Concurrent();`
- L251 _public prototype_ `void OnCreateRenderStateEnd_GameThread();`
- L258 _public prototype_ `void OnComponentPSOPrecacheCompleted(FFastGeoComponent* Component);` — Called from PSO precache completion callback. Routes to the appropriate path: - DelayUntilPSOPrecached: moves component to ready set for deferred create. - UseFallbackMaterialUntilPSOPrecached: pushes to recreate queue for material swap. - Otherwise: no-op (early completion detected by CheckPSODeferredReadiness polling).
- L261 _public prototype_ `void OnPSODeferredReady(FFastGeoComponent* Component);` — DelayUntilPSOPrecached: deferred proxy creation for components whose PSOs were not ready.
- L262 _public prototype_ `void OnDeferredCreateRenderStateBegin_GameThread();`
- L263 _public prototype_ `void OnDeferredCreateRenderState_Concurrent();`
- L264 _public prototype_ `void OnDeferredCreateRenderStateEnd_GameThread();`
- L274 _public prototype_ `void CheckPSODeferredReadiness(bool bPollPending = false);` — Checks if deferred components are ready for proxy creation and triggers a deferred create pass. bPollPending: when true, polls IsPSOPrecaching() on pending components to detect lost PSO callbacks (safety net). Called with bPollPending=true from: - WorldSubsystem::Tick (periodic safety net poll) - OnCreateRenderStateEnd_GameThread (detect callbacks that fired before parking) - OnDeferredCreateRenderStateEnd_GameThread (re-check after batch completes) Called with bPollPending=false from: - OnPSODeferredReady (per-callback, skips O(n) poll).
- L277 _public prototype_ `void RoutePSORecreateComponent(FFastGeoComponent* Component);` — UseFallbackMaterialUntilPSOPrecached: recreate proxy with real material once PSOs are ready.
- L278 _public prototype_ `void PushPSORecreateComponent(FFastGeoComponent* Component);`
- L279 _public prototype_ `void OnRecreateRenderStateBegin_GameThread();`
- L280 _public prototype_ `void OnRecreateRenderState_Concurrent();`
- L281 _public prototype_ `void OnRecreateRenderStateEnd_GameThread();`
- L283 _public function_ `bool HasPSODeferredComponents() const`
- L284 _public prototype_ `bool HasAnyPendingRecreateTasks() const;`
- L287 _public prototype_ `void OnDestroyRenderStateBegin_GameThread();`
- L288 _public prototype_ `void OnDestroyRenderState_Concurrent();`
- L289 _public prototype_ `void OnDestroyRenderStateEnd_GameThread();`
- L291 _public prototype_ `void OnCreatePhysicsStateBegin_GameThread();`
- L292 _public prototype_ `void OnDestroyPhysicsStateBegin_GameThread();`
- L295 _public prototype_ `virtual bool AllowsAsyncPhysicsStateCreation() const override final;`
- L296 _public prototype_ `virtual bool AllowsAsyncPhysicsStateDestruction() const override final;`
- L297 _public prototype_ `virtual bool IsAsyncPhysicsStateCreated() const override final;`
- L298 _public prototype_ `virtual UObject* GetAsyncPhysicsStateObject() const override final;`
- L299 _public prototype_ `virtual void OnAsyncCreatePhysicsStateBegin_GameThread(TSet<UObject*>& OutRootedObjects) override;`
- L300 _public prototype_ `virtual bool OnAsyncCreatePhysicsState(const UE::FTimeout& Timeout) override;`
- L301 _public prototype_ `virtual void OnAsyncCreatePhysicsStateEnd_GameThread() override;`
- L302 _public prototype_ `virtual void OnAsyncDestroyPhysicsStateBegin_GameThread(TSet<UObject*>& OutRootedObjects) override;`
- L303 _public prototype_ `virtual bool OnAsyncDestroyPhysicsState(const UE::FTimeout& Timeout) override;`
- L304 _public prototype_ `virtual void OnAsyncDestroyPhysicsStateEnd_GameThread() override;`
- L305 _public prototype_ `virtual void CollectBodySetupsWithPhysicsMeshesToCreate(TSet<UBodySetup*>& OutBodySetups) const override;`
- L309 _public function_ `template <typename TComponentCluster = const FFastGeoComponentCluster, typename TFunc> void ForEachComponentCluster(TFunc&& InFunc) const`
- L315 _public function_ `template <typename TComponentCluster = FFastGeoComponentCluster, typename TFunc> void ForEachComponentCluster(TFunc&& InFunc)`
- L321 _public function_ `template <typename TComponentCluster = const FFastGeoComponentCluster, typename TFunc> bool ForEachComponentClusterBreakable(TFunc&& InFunc) const`
- L327 _public function_ `template <typename TComponentCluster = FFastGeoComponentCluster, typename TFunc> bool ForEachComponentClusterBreakable(TFunc&& InFunc)`
- L332 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRegistered);`
- L333 _public function_ `FOnRegistered& GetOnRegistered()`
- L335 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnUnregistered);`
- L336 _public function_ `FOnUnregistered& GetOnUnregistered()`
- L340 _protected member_ `FFastGeoComponentClusterPendingState PendingCreate;`
- L341 _protected member_ `FFastGeoComponentClusterPendingState PendingDestroy;`
- L350 _protected member_ `TSet<FFastGeoComponent*> PSODeferredPendingComponents;` — DelayUntilPSOPrecached: components whose proxy creation was deferred because PSOs were not ready. Part of registration -- blocks AddToWorld until all deferred proxies are created. Components start in PSODeferredPendingComponents. As each PSO callback fires, the component moves to PSODeferredReadyComponents. When the pending set is empty (or the safety poll detects all are ready), the ready array becomes ComponentsToProcess for the deferred create pass.
- L351 _protected member_ `TArray<FFastGeoComponent*> PSODeferredReadyComponents;`
- L352 _protected member_ `FFastGeoRenderStateBatch PSODeferredCreateState;`
- L353 _protected member_ `bool bIsProcessingPSODeferredCreate = false;`
- L362 _protected member_ `TArray<FFastGeoComponent*> PSORecreateComponents;` — UseFallbackMaterialUntilPSOPrecached: components created with fallback material that need recreation with the real material once PSOs are ready. Post-registration -- does NOT block AddToWorld. Populated by PushPSORecreateComponent (async-only, asserted), processed by the async job queue via StartRecreateRenderStateWork -> PushAsyncRecreateRenderStateJob. Sync mode does not use these fields -- it routes through MarkRenderStateDirty -> ProcessPendingRecreate instead.
- L363 _protected member_ `FFastGeoRenderStateBatch PSORecreateState;`
- L364 _protected member_ `bool bIsProcessingPSORecreate = false;`
- L373 _public prototype_ `UFastGeoWorldSubsystem* GetWorldSubsystem() const;` — Worker-safe accessors that route through the GT-populated FFastGeoAsyncContext when initialized. Component code on async render-state workers must use these instead of GetWorld()->GetSubsystem..., World->Scene, GetWorld()->GetPhysicsScene(), or GetWorld()->GetTimeSeconds() to avoid touching GT-mutable engine state from a generic worker thread.
- L374 _public prototype_ `FSceneInterface* GetScene() const;`
- L375 _public prototype_ `FPhysScene* GetPhysicsScene() const;`
- L376 _public prototype_ `float GetWorldTimeSeconds() const;`
- L380 _private prototype_ `void OnCreated(bool bCollectReferences = true);`
- L381 _private prototype_ `void InitializePrerequisites();`
- L382 _private prototype_ `void ForEachMaterialAsset(TFunctionRef<void(UMaterialInterface*)> Func);`
- L383 _private prototype_ `void BuildMaterialAssets();`
- L385 _private prototype_ `void ConditionalStripRenderOnlyComponentsAndAssets();`
- L386 _private prototype_ `void CacheMaterialAssets();`
- L389 _private prototype_ `void StartCreatePhysicsStateWork();`
- L390 _private prototype_ `void StartDestroyPhysicsStateWork();`
- L391 _private prototype_ `void TickPhysicsWork(bool bWaitForCompletion);`
- L393 _private prototype_ `void StartPrecachePSOWork();`
- L394 _private prototype_ `void StartCreateRenderStateWork();`
- L395 _private prototype_ `void StartDestroyRenderStateWork();`
- L397 _private prototype_ `template <bool bDestroyFirst> void ExecuteCreateRenderState_Concurrent(FFastGeoRenderStateBatch& State);`
- L399 _private prototype_ `void ForceCreateDeferredComponents();`
- L400 _private prototype_ `void StartDeferredCreateRenderStateWork();`
- L401 _private prototype_ `void StartRecreateRenderStateWork();`
- L402 _private prototype_ `bool TickDeferredCreate_Sync(const UE::FTimeout& Timeout);`
- L404 _private prototype_ `void TickRenderWork(bool bWaitForCompletion);`
- L405 _private prototype_ `void TickRenderWork_Sync(bool bWaitForCompletion);`
- L406 _private prototype_ `bool TickPrecachePSO_Sync(const UE::FTimeout& Timeout);`
- L407 _private prototype_ `bool TickCreateRenderState_Sync(const UE::FTimeout& Timeout);`
- L408 _private prototype_ `bool TickDestroyRenderState_Sync(const UE::FTimeout& Timeout);`
- L409 _private prototype_ `bool IsPrecachePSOCompleted() const;`
- L414 _private prototype_ `bool IsInitialCreateRenderStatePassCompleted() const;` — Returns true when all components in the current create pass have been attempted. Components whose proxy was deferred (e.g., DelayUntilPSOPrecached) are counted as attempted. Use IsCreateRenderStateFullyCompleted() to check if all proxies actually exist.
- L417 _private prototype_ `bool IsCreateRenderStateFullyCompleted() const;` — Returns true when all render state creation is truly done, including PSO-deferred proxies.
- L419 _private prototype_ `bool IsDestroyRenderStateCompleted() const;`
- L421 _private prototype_ `void CollectAssetReferences();`
- L422 _private prototype_ `void SerializeComponentClusters(FArchive& Ar);`
- L424 _private prototype_ `void SerializeComponentClustersWithFilter(FArchive& Ar, TFunctionRef<bool(const FFastGeoComponent&)> ShouldSerializeComponent);`
- L426 _private prototype_ `void RegisterToNavigationSystem();`
- L427 _private prototype_ `void UnregisterFromNavigationSystem();`
- L428 _private prototype_ `void OnNavigationInitDone(const UNavigationSystemBase& NavSys);`
- L429 _private prototype_ `void RegisterBodyInstances();`
- L430 _private prototype_ `void UnregisterBodyInstances();`
- L431 _private prototype_ `void OnRegisterCompleted();`
- L432 _private prototype_ `void OnUnregisterCompleted();`
- L433 _private prototype_ `void TryCompleteRegistration();`
- L434 _private prototype_ `void TryCompleteUnregistration();`
- L435 _private prototype_ `void ApplyRegistrationTargetState();`
- L436 _private prototype_ `void StartRegisterTransition();`
- L437 _private prototype_ `void StartUnregisterTransition();`
- L440 _private function_ `template <typename ThisType, typename TComponentCluster, typename TFunc> static void ForEachComponentCluster(ThisType* Self, TFunc&& InFunc)`
- L469 _private function_ `template <typename ThisType, typename TComponentCluster, typename TFunc> static bool ForEachComponentClusterBreakable(ThisType* Self, TFunc&& InFunc)`
- L513 _private member_ `EPhysicsState PhysicsState = EPhysicsState::None;`
- L523 _private member_ `ERegistrationState RegistrationState = ERegistrationState::Unregistered;`
- L531 _private member_ `ERegistrationTargetState RegistrationTargetState = ERegistrationTargetState::Unregistered;`
- L534 _private member_ `TArray<FFastGeoComponentCluster> ComponentClusters;` — Persistent data
- L535 _private member_ `TArray<FFastGeoHLOD> HLODs;`
- L538 _private member_ `TArray<TObjectPtr<UObject>> Assets;` — `UPROPERTY()`
- L547 _private member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialAssetHardRefs;` — Pre-computed unique material list, built at cook time in PreSave. Base materials (OverrideMaterials, mesh slots, decal, light function) are hard refs. Intentionally NOT a UPROPERTY: every material in this array is already GC-anchored transitively via Assets (component overrides serialized into Assets directly, mesh slot defaults reachable through UStaticMesh/USkinnedAsset entries in Assets). Skipping the UPROPERTY shaves a duplicate UObject* traversal pass per container during GC mark. Serialized manually in UFastGeoContainer::Serialize.
- L553 _private member_ `TArray<TSoftObjectPtr<UMaterialInterface>> MaterialAssetNaniteOverrideSoftRefs;` — `UPROPERTY()` — Nanite override materials are soft refs - may be stripped on non-Nanite platforms (FMaterialOverrideNanite::Serialize can null them during cook). Resolved in CacheMaterialAssets when loading (Serialize) cooked container.
- L557 _private member_ `TBitArray<> NonRenderOnlyAssetMask;` — Bitmask over Assets: set for entries referenced by non-render-only components. Computed at cook time. On non-rendering processes, unset entries are nulled at load time.
- L560 _private member_ `TObjectPtr<AFastGeoSurrogateActor> SurrogateActor;` — `UPROPERTY()`
- L563 _private member_ `bool bPSOPrecachingInitiated = false;`
- L568 _private member_ `TArray<TObjectPtr<UMaterialInterface>> CachedMaterialAssets;` — `UPROPERTY(Transient)` — Resolved material cache (transient).
- L569 _private member_ `bool bMaterialAssetsCached = false;`
- L570 _private member_ `bool bHasStrippedRenderOnlyComponents = false;`
- L573 _private member_ `TArray<IPrimitiveComponent*> PrimitiveComponents;` — Transient data
- L574 _private member_ `TArray<IStaticMeshComponent*> StaticMeshComponents;`
- L575 _private member_ `TArray<FFastGeoComponent*> CollisionComponents;`
- L576 _private member_ `TArray<FNavigationElementHandle> NavigationElementHandles;`
- L578 _private member_ `bool bIsBeingAsyncDestroyed = false;`
- L579 _private member_ `int32 RegistrationEpoch = 0;`
- L583 _private member_ `FFastGeoAsyncContext AsyncContext;` — Prerequisites: must be initialized on GT before starting render/physics work. Workers read from AsyncContext instead of performing lookups not safe from generic workers.
- L584 _private member_ `FFastGeoMaterialPostLoadInit MaterialPostLoadInit;`
- L585 _private member_ `FFastGeoMaterialRelevanceInit MaterialRelevanceInit;`
- L587 _private member_ `FRenderCommandFence DestroyFence;`
- L589 _private member_ `FOnRegistered OnRegistered;`
- L590 _private member_ `FOnUnregistered OnUnregistered;`

#### enum `UFastGeoContainer::EPhysicsState`  
`enum class EPhysicsState : uint8`  
_L506-512_
- desc: UFastGeoContainer's physics state
- L508 _public enumerator_ `None`
- L509 _public enumerator_ `Creating`
- L510 _public enumerator_ `Created`
- L511 _public enumerator_ `Destroying`

#### enum `UFastGeoContainer::ERegistrationState`  
`enum class ERegistrationState : uint8`  
_L516-522_
- desc: UFastGeoContainer's registration state
- L518 _public enumerator_ `Unregistered`
- L519 _public enumerator_ `Registering`
- L520 _public enumerator_ `Registered`
- L521 _public enumerator_ `Unregistering`

#### enum `UFastGeoContainer::ERegistrationTargetState`  
`enum class ERegistrationTargetState : uint8`  
_L526-530_
- desc: UFastGeoContainer's registration target state
- L528 _public enumerator_ `Registered`
- L529 _public enumerator_ `Unregistered`

#### Free symbols / members of external scopes

- L332 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRegistered);`
- L335 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnUnregistered);`
- L443 _function_ `` (scope `UFastGeoContainer::ForEachComponentCluster`)
- L444 _typedef_ `typedef typename TDecay<decltype(InArray)>::Type ArrayType;` (scope `UFastGeoContainer::ForEachComponentCluster::__anon910fc0d60102`)
- L445 _typedef_ `using TArrayComponentCluster = typename ArrayType::ElementType;` (scope `UFastGeoContainer::ForEachComponentCluster::__anon910fc0d60102`)
- L472 _function_ `` (scope `UFastGeoContainer::ForEachComponentClusterBreakable`)
- L473 _typedef_ `typedef typename TDecay<decltype(InArray)>::Type ArrayType;` (scope `UFastGeoContainer::ForEachComponentClusterBreakable::__anon910fc0d60202`)
- L474 _typedef_ `using TArrayComponentCluster = typename ArrayType::ElementType;` (scope `UFastGeoContainer::ForEachComponentClusterBreakable::__anon910fc0d60202`)

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoDecalComponent.h` (Internal)


#### class `FFastGeoDecalComponent`  
`class FFastGeoDecalComponent : public FFastGeoComponent`  
_L11-66_
- inherits: `FFastGeoComponent`
- L14 _public typedef_ `typedef FFastGeoComponent Super;`
- L17 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L19 _public prototype_ `FFastGeoDecalComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L20 _public prototype_ `FFastGeoDecalComponent(const FFastGeoDecalComponent& Other);`
- L21 _public prototype_ `virtual ~FFastGeoDecalComponent() = default;`
- L24 _public prototype_ `virtual void ForEachMaterial(TFunctionRef<void(UMaterialInterface*, bool bIsNaniteOverride)> Func) const override;`
- L25 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L26 _public prototype_ `virtual void ApplyWorldTransform(const FTransform& InTransform) override;`
- L27 _public prototype_ `virtual bool ShouldComponentAddToRenderScene() const override;`
- L28 _public prototype_ `virtual void CreateRenderState(FRegisterComponentContext* Context) override;`
- L29 _public prototype_ `virtual void DestroyRenderState(FFastGeoDestroyRenderStateContext* Context) override;`
- L30 _public prototype_ `virtual void UpdateVisibility() override;`
- L32 _public prototype_ `virtual void InitializeFromComponent(UActorComponent* Component) override;`
- L35 _public prototype_ `virtual bool ShouldPrecachePSOs() const override;`
- L36 _public prototype_ `virtual void PrecachePSOs_Concurrent() override;`
- L37 _public function_ `virtual FPSOPrecacheComponentData& GetPSOPrecacheComponentData() override`
- L38 _public function_ `virtual const FPSOPrecacheComponentData& GetPSOPrecacheComponentData() const override`
- L43 _protected prototype_ `FBoxSphereBounds CalcBounds() const;`
- L44 _protected prototype_ `FTransform GetTransformIncludingDecalSize() const;`
- L45 _protected prototype_ `FDeferredDecalProxy* CreateSceneProxy(ESceneProxyCreationError& OutError);`
- L46 _protected prototype_ `void InitializeSceneProxyDescDynamicProperties();`
- L47 _protected prototype_ `void UpdateVisibilityInternal();`
- L48 _protected prototype_ `void SetLifeSpan(const float InLifeSpan);`
- L52 _private member_ `FVector DecalSize;` — Persistent data
- L53 _private member_ `FDeferredDecalSceneProxyDesc SceneProxyDesc{};`
- L54 _private member_ `uint8 bIsVisible : 1 = true;`
- L55 _private member_ `uint8 bDestroyOwnerAfterFade : 1 = false;`
- L58 _private member_ `uint8 bFadeCompleted : 1 = false;` — Transient runtime state
- L59 _private member_ `FDeferredDecalProxy* SceneProxy = nullptr;`
- L60 _private member_ `FTimerHandle TimerHandle_DestroyDecalComponent;`
- L64 _private member_ `FPSOPrecacheComponentData PSOPrecacheComponentData;` — All PSO related data for the component

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoDestroyRenderStateContext.h` (Internal)


#### class `FFastGeoDestroyRenderStateContext`  
`class FFastGeoDestroyRenderStateContext`  
_L11-24_
- L14 _public prototype_ `FFastGeoDestroyRenderStateContext(FSceneInterface* InScene);`
- L15 _public prototype_ `~FFastGeoDestroyRenderStateContext();`
- L17 _public prototype_ `static void DestroyProxy(FFastGeoDestroyRenderStateContext* InContext, FPrimitiveSceneProxy* InPrimitiveSceneProxy, FSceneInterface* InScene);`
- L18 _public prototype_ `static void DestroyProxy(FFastGeoDestroyRenderStateContext* InContext, FDeferredDecalProxy* InDeferredDecalProxy, FSceneInterface* InScene);`
- L21 _private member_ `FSceneInterface* Scene;`
- L22 _private member_ `TArray<FPrimitiveSceneProxy*> PrimitiveSceneProxies;`
- L23 _private member_ `TArray<FDeferredDecalProxy*> DeferredDecalProxies;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoElementType.h` (Internal)


#### struct `FFastGeoElementType`  
`struct FFastGeoElementType`  
_L7-44_
- L10 _public member_ `static const FFastGeoElementType Invalid;`
- L12 _public function_ `explicit FFastGeoElementType(const FFastGeoElementType* Parent = nullptr) : ID(++NextUniqueID), ParentType(Parent)`
- L14 _public function_ `bool operator==(const FFastGeoElementType& Other) const`
- L19 _public function_ `bool IsA(const FFastGeoElementType& Other) const`
- L25 _public function_ `bool IsSameTypeID(uint32 InID) const` — Returns true if element has the same type ID than the specified type
- L30 _public function_ `bool IsValid() const`
- L37 _private function_ `explicit FFastGeoElementType(EInitMode) : ID(0xFFFFFFFF), ParentType(nullptr)`
- L39 _private member_ `static uint32 NextUniqueID;`
- L40 _private member_ `uint32 ID;`
- L41 _private member_ `const FFastGeoElementType* ParentType;`

#### enum `FFastGeoElementType::EInitMode`  
`enum class EInitMode`  
_L36-36_
- L36 _public enumerator_ `enum class EInitMode { Invalid }; explicit FFastGeoElementType(EInitMode) : ID(0xFFFFFFFF)`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoHLOD.h` (Internal)


#### class `FFastGeoHLOD`  
`class FFastGeoHLOD : public FFastGeoComponentCluster, public IWorldPartitionHLODObject`  
_L8-73_
- inherits: `FFastGeoComponentCluster,IWorldPartitionHLODObject`
- L11 _public typedef_ `typedef FFastGeoComponentCluster Super;`
- L14 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L16 _public prototype_ `FFastGeoHLOD(UFastGeoContainer* InOwner = nullptr, FName InName = NAME_None, FFastGeoElementType InType = Type);`
- L17 _public prototype_ `~FFastGeoHLOD() = default;`
- L19 _public function_ `virtual bool IsVisible() const override`
- L22 _public prototype_ `virtual void OnRegister() override;`
- L23 _public prototype_ `virtual void OnUnregister() override;`
- L24 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L28 _public function_ `virtual UObject* GetUObject() const override`
- L29 _public prototype_ `virtual ULevel* GetHLODLevel() const override;`
- L30 _public prototype_ `virtual FString GetHLODNameOrLabel() const override;`
- L31 _public prototype_ `virtual bool DoesRequireWarmup() const override;`
- L32 _public prototype_ `virtual TSet<UObject*> GetAssetsToWarmup() const override;`
- L33 _public prototype_ `virtual void SetVisibility(bool bIsVisible) override;`
- L34 _public prototype_ `virtual const FGuid& GetSourceCellGuid() const override;`
- L35 _public prototype_ `virtual bool IsStandalone() const override;`
- L36 _public prototype_ `virtual const FGuid& GetStandaloneHLODGuid() const override;`
- L37 _public prototype_ `virtual bool IsCustomHLOD() const override;`
- L38 _public prototype_ `virtual const FGuid& GetCustomHLODGuid() const override;`
- L43 _public prototype_ `virtual FFastGeoComponent& AddComponent(FFastGeoElementType InComponentType) override;`
- L44 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L47 _public prototype_ `void SetSourceCellGuid(const FGuid& InSourceCellGuid);`
- L48 _public prototype_ `void SetRequireWarmup(bool bInRequireWarmup);`
- L49 _public prototype_ `void SetStandaloneHLODGuid(const FGuid& InStandaloneHLODGuid);`
- L50 _public prototype_ `void SetCustomHLODGuid(const FGuid& InCustomHLODGuid);`
- L56 _private member_ `bool bIsVisible;` — Transient Data
- L59 _private member_ `bool bRequireWarmup;` — Persistent Data
- L60 _private member_ `FGuid SourceCellGuid;`
- L68 _private member_ `FGuid HLODGuid;`
- L69 _private member_ `EHLODGuidType HLODGuidType = EHLODGuidType::None;`
- L71 _private prototype_ `const FGuid& GetHLODGuid(EHLODGuidType InGuidType) const;`
- L72 _private prototype_ `void SetHLODGuid(const FGuid& InGuid, EHLODGuidType InGuidType);`

#### enum `FFastGeoHLOD::EHLODGuidType`  
`enum class EHLODGuidType : uint8`  
_L62-67_
- L64 _public enumerator_ `None`
- L65 _public enumerator_ `Standalone`
- L66 _public enumerator_ `Custom`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoInstancedSkinnedMeshComponent.h` (Internal)


#### class `FFastGeoInstancedSkinnedMeshComponent`  
`class FFastGeoInstancedSkinnedMeshComponent : public FFastGeoSkinnedMeshComponentBase`  
_L10-72_
- inherits: `FFastGeoSkinnedMeshComponentBase`
- L13 _public typedef_ `typedef FFastGeoSkinnedMeshComponentBase Super;`
- L16 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L18 _public prototype_ `FFastGeoInstancedSkinnedMeshComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L19 _public prototype_ `virtual ~FFastGeoInstancedSkinnedMeshComponent() = default;`
- L23 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L25 _protected prototype_ `virtual void InitializeFromComponent(UActorComponent* Component) override;`
- L30 _protected function_ `virtual FPrimitiveSceneProxyDesc& GetSceneProxyDesc() override`
- L31 _protected function_ `virtual const FPrimitiveSceneProxyDesc& GetSceneProxyDesc() const override`
- L33 _protected prototype_ `virtual void InitializeSceneProxyDescFromComponent(UActorComponent* Component) override;`
- L34 _protected prototype_ `virtual void ResetSceneProxyDescUnsupportedProperties() override;`
- L36 _protected prototype_ `virtual void InitializeSceneProxyDescDynamicProperties() override;`
- L37 _protected prototype_ `virtual void ApplyWorldTransform(const FTransform& InTransform) override;`
- L41 _protected function_ `virtual FSkinnedMeshSceneProxyDesc& GetSkinnedMeshSceneProxyDesc() override`
- L42 _protected function_ `virtual const FSkinnedMeshSceneProxyDesc& GetSkinnedMeshSceneProxyDesc() const override`
- L43 _protected prototype_ `virtual FSkeletalMeshObject* CreateMeshObject() override;`
- L44 _protected prototype_ `virtual FPrimitiveSceneProxy* AllocateSceneProxy() override;`
- L47 _protected prototype_ `virtual void UpdateSkinning() override;` — FInstancedSkeletalMeshObject::Update consumes only LODIndex; skinning runs GPU-side through the AnimBank scene-extension proxy (or static-pose path), so we skip the ref-pose fill.
- L49 _protected function_ `int32 GetInstanceCount() const`
- L54 _protected function_ `UTransformProviderData* GetTransformProvider() const`
- L60 _protected function_ `TConstArrayView<FTransform3f> GetInstancePrevTransforms() const`
- L63 _private member_ `TArray<FSkinnedMeshInstanceData> InstanceData;`
- L64 _private member_ `int32 NumCustomDataFloats = 0;`
- L65 _private member_ `TArray<float> InstanceCustomData;`
- L67 _private member_ `FInstancedSkinnedMeshSceneProxyDesc SceneProxyDesc;`
- L69 _private member_ `TSharedPtr<FInstanceDataManager> InstanceDataManager;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoInstancedStaticMeshComponent.h` (Internal)


#### class `FFastGeoInstancedStaticMeshComponent`  
`class FFastGeoInstancedStaticMeshComponent : public FFastGeoStaticMeshComponentBase`  
_L8-111_
- inherits: `FFastGeoStaticMeshComponentBase`
- L11 _public typedef_ `typedef FFastGeoStaticMeshComponentBase Super;`
- L14 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L16 _public prototype_ `FFastGeoInstancedStaticMeshComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L17 _public prototype_ `virtual ~FFastGeoInstancedStaticMeshComponent() = default;`
- L20 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L22 _public prototype_ `virtual void OnAsyncCreatePhysicsStateBegin_GameThread() override;`
- L24 _public prototype_ `virtual void OnAsyncCreatePhysicsState() override;`
- L25 _public prototype_ `virtual void OnAsyncCreatePhysicsStateEnd_GameThread() override;`
- L26 _public prototype_ `virtual void OnAsyncDestroyPhysicsState() override;`
- L27 _public prototype_ `virtual void OnAsyncDestroyPhysicsStateBegin_GameThread() override;`
- L28 _public prototype_ `virtual void OnAsyncDestroyPhysicsStateEnd_GameThread() override;`
- L30 _public prototype_ `virtual void InitializeFromComponent(UActorComponent* Component) override;`
- L35 _public prototype_ `virtual void GetNavigationData(FNavigationRelevantData& Data) const override;`
- L36 _public prototype_ `virtual FBox GetNavigationBounds() const override;`
- L37 _public prototype_ `virtual bool IsNavigationRelevant() const override;`
- L38 _public prototype_ `virtual bool DoCustomNavigableGeometryExport(FNavigableGeometryExport& GeomExport) const override;`
- L39 _public function_ `virtual bool ShouldSkipNavigationDirtyAreaOnAddOrRemove() override`
- L40 _public prototype_ `virtual Chaos::FPhysicsObject* GetPhysicsObjectById(Chaos::FPhysicsObjectId Id) const override;`
- L41 _public prototype_ `virtual TArray<Chaos::FPhysicsObject*> GetAllPhysicsObjects() const override;`
- L42 _public prototype_ `virtual FBodyInstance* GetBodyInstance(FName BoneName = NAME_None, bool bGetWelded = true, int32 Index = INDEX_NONE) const override;`
- L44 _public prototype_ `virtual void ReserveSurrogateInstanceBodyIndices(FFastGeoSurrogateBodyInstanceIndex& InOutNextAvailableInstanceBodyIndex) override;`
- L48 _public prototype_ `void ForEachInstanceMatrix(TFunctionRef<void(const FMatrix&)> Func) const;`
- L49 _public prototype_ `int32 GetInstanceCount() const;`
- L53 _protected function_ `virtual FPrimitiveSceneProxyDesc& GetSceneProxyDesc() override`
- L54 _protected function_ `virtual const FPrimitiveSceneProxyDesc& GetSceneProxyDesc() const override`
- L56 _protected prototype_ `virtual void InitializeSceneProxyDescFromComponent(UActorComponent* Component) override;`
- L57 _protected prototype_ `virtual void ResetSceneProxyDescUnsupportedProperties() override;`
- L59 _protected prototype_ `virtual void ApplyWorldTransform(const FTransform& InTransform) override;`
- L60 _protected prototype_ `virtual void GetBodyInstances(TArray<FBodyInstance*>& OutBodyInstances) override;`
- L64 _protected function_ `virtual FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() override`
- L65 _protected function_ `virtual const FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() const override`
- L66 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateStaticMeshSceneProxy(const Nanite::FMaterialAudit& NaniteMaterials, bool bCreateNanite) override;`
- L68 _protected prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams) override;`
- L79 _private prototype_ `FBoxSphereBounds CalculateBounds(EBoundsType BoundsType);`
- L80 _private prototype_ `void BuildInstanceData();`
- L81 _private prototype_ `void CreateAllInstanceBodies();`
- L82 _private prototype_ `static TArray<Chaos::FPhysicsObject*> GetAllPhysicsObjects(const TArray<FBodyInstance*>& InInstanceBodies);`
- L84 _private prototype_ `void InitializePerInstanceSMData(const TArray<FInstancedStaticMeshInstanceData>& InPerInstanceSMData);`
- L90 _private member_ `TArray<FInstancedStaticMeshInstanceData> HighPrecisionPerInstanceSMData;`
- L91 _private member_ `TArray<FTransform3f> LowPrecisionPerInstanceSMData;`
- L92 _private member_ `int32 LastInstanceBodyIndex = INDEX_NONE;`
- L93 _private member_ `int32 InstancingRandomSeed = 0;`
- L94 _private member_ `TArray<float> PerInstanceSMCustomData;`
- L95 _private member_ `TArray<FInstancedStaticMeshRandomSeed> AdditionalRandomSeeds;`
- L96 _private member_ `FBox NavigationBounds;`
- L97 _private member_ `TArray<FInstanceSceneDataBuffers::FCompressedSpatialHashItem> SpatialHashes;`
- L98 _private member_ `TArray<float> PerInstanceRandomIDs;`
- L99 _private member_ `FInstancedStaticMeshSceneProxyDesc SceneProxyDesc{};`
- L100 _private member_ `bool bUseHighPrecisionPerInstanceSMData : 1 = false;`
- L104 _private member_ `bool bAppliedWorldTransform : 1 = false;`
- L106 _private member_ `TArray<FBodyInstance*> InstanceBodies;` — Physics representation of the instance bodies.
- L108 _private member_ `TArray<FBodyInstance*> AsyncDestroyPhysicsStatePayload;` — Payload used by asynchronous destruction of physics state (see OnAsyncDestroyPhysicsState).

#### enum `FFastGeoInstancedStaticMeshComponent::EBoundsType`  
`enum class EBoundsType`  
_L73-78_
- L75 _public enumerator_ `LocalBounds`
- L76 _public enumerator_ `WorldBounds`
- L77 _public enumerator_ `NavigationBounds`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoLocalLightComponent.h` (Internal)


#### class `FFastGeoLocalLightComponent`  
`class FFastGeoLocalLightComponent : public FFastGeoComponent`  
_L10-64_
- inherits: `FFastGeoComponent`
- L13 _public typedef_ `typedef FFastGeoComponent Super;`
- L16 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L18 _public prototype_ `FFastGeoLocalLightComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L19 _public prototype_ `FFastGeoLocalLightComponent(const FFastGeoLocalLightComponent& Other);`
- L20 _public prototype_ `virtual ~FFastGeoLocalLightComponent() = default;`
- L23 _public prototype_ `virtual void ForEachMaterial(TFunctionRef<void(UMaterialInterface*, bool bIsNaniteOverride)> Func) const override;`
- L24 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L25 _public prototype_ `virtual bool ShouldComponentAddToRenderScene() const override;`
- L26 _public prototype_ `virtual void CreateRenderState(FRegisterComponentContext* Context) override;`
- L27 _public prototype_ `virtual void DestroyRenderState(FFastGeoDestroyRenderStateContext* Context) override;`
- L28 _public prototype_ `virtual void UpdateVisibility() override;`
- L30 _public prototype_ `virtual void InitializeFromComponent(UActorComponent* Component) override;`
- L35 _public prototype_ `virtual bool ShouldPrecachePSOs() const override;`
- L36 _public prototype_ `virtual void PrecachePSOs_Concurrent() override;`
- L37 _public function_ `virtual FPSOPrecacheComponentData& GetPSOPrecacheComponentData() override`
- L38 _public function_ `virtual const FPSOPrecacheComponentData& GetPSOPrecacheComponentData() const override`
- L42 _protected prototype_ `virtual FLocalLightSceneProxyDesc& GetLocalLightSceneProxyDesc() = 0;`
- L43 _protected prototype_ `virtual const FLocalLightSceneProxyDesc& GetLocalLightSceneProxyDesc() const = 0;`
- L44 _protected prototype_ `virtual FLightSceneProxy* CreateTypedSceneProxy() = 0;`
- L46 _protected prototype_ `void InitializeSceneProxyDescDynamicProperties();`
- L47 _protected prototype_ `bool UpdateVisibilityInternal();`
- L50 _private prototype_ `FLightSceneProxy* CreateSceneProxy(ESceneProxyCreationError& OutError);`
- L53 _private member_ `bool bAffectsWorld = true;` — Persistent data
- L54 _private member_ `bool bSourceComponentIsVisible = true;`
- L57 _private member_ `bool bIsVisible = true;` — Transient data
- L58 _private member_ `FLightSceneProxy* SceneProxy = nullptr;`
- L62 _private member_ `FPSOPrecacheComponentData PSOPrecacheComponentData;` — All PSO related data for the component

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoMeshComponent.h` (Internal)


#### class `FFastGeoMeshComponent`  
`class FFastGeoMeshComponent : public FFastGeoPrimitiveComponent`  
_L9-47_
- inherits: `FFastGeoPrimitiveComponent`
- L12 _public typedef_ `typedef FFastGeoPrimitiveComponent Super;`
- L15 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L17 _public prototype_ `FFastGeoMeshComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L18 _public prototype_ `virtual ~FFastGeoMeshComponent() = default;`
- L21 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L23 _public prototype_ `virtual void InitializeFromComponent(UActorComponent* InComponent) override;`
- L27 _public prototype_ `FMaterialRelevance GetMaterialRelevance(EShaderPlatform InShaderPlatform) const;`
- L29 _public prototype_ `void GetMaterialSlotsOverlayMaterial(TArray<TObjectPtr<UMaterialInterface>>& OutMaterialSlotOverlayMaterials) const;`
- L32 _public prototype_ `virtual void GetDefaultMaterialSlotsOverlayMaterial(TArray<TObjectPtr<UMaterialInterface>>& AssetMaterialSlotOverlayMaterials) const = 0;` — Get the asset material slot overlay material
- L34 _public prototype_ `virtual const TArray<TObjectPtr<UMaterialInterface>>& GetComponentMaterialSlotsOverlayMaterial() const = 0;`
- L35 _public prototype_ `virtual UMaterialInterface* GetOverlayMaterial() const = 0;`
- L37 _public function_ `TConstArrayView<TObjectPtr<UMaterialInterface>> GetOverrideMaterials() const`
- L43 _protected member_ `TArray<TObjectPtr<UMaterialInterface>> OverrideMaterials;` — Persistent Data

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoPSOWeakPtrTraits.h` (Internal)


#### struct `TPSOWeakPtrTraits`  
`template<typename T> struct TPSOWeakPtrTraits<T, typename TEnableIf<TIsDerivedFrom<T, FFastGeoComponent>::Value>::Type>`  
_L12-18_
- desc: Specialization: if T : FFastGeoComponent -> use FWeakFastGeoComponent
- L14 _public typedef_ `using WeakType = FWeakFastGeoComponent;`
- L16 _public function_ `static WeakType Make(T* Ptr)`
- L17 _public function_ `static T* Get(const WeakType& W)`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoPhysicsBodyInstanceOwner.h` (Internal)


#### class `FFastGeoPhysicsBodyInstanceOwner`  
`class FFastGeoPhysicsBodyInstanceOwner : public FChaosUserDefinedEntity, public IPhysicsBodyInstanceOwner`  
_L13-75_
- inherits: `FChaosUserDefinedEntity,IPhysicsBodyInstanceOwner`
- L16 _public prototype_ `FFastGeoPhysicsBodyInstanceOwner();`
- L17 _public prototype_ `virtual ~FFastGeoPhysicsBodyInstanceOwner() = default;`
- L20 _public prototype_ `static IPhysicsBodyInstanceOwner* GetPhysicsBodyInstanceOwner(FChaosUserDefinedEntity* InUserDefinedEntity);` — Returns the IPhysicsBodyInstanceOwner based on the provided FChaosUserDefinedEntity
- L23 _public prototype_ `static const FFastGeoPhysicsBodyInstanceOwner* FromHitResult(const FHitResult& HitResult);` — Returns the typed FFastGeoPhysicsBodyInstanceOwner from a hit result, or nullptr if the hit did not involve FastGeo geometry or the physics object/owner references are no longer valid.
- L26 _public prototype_ `static const FFastGeoPhysicsBodyInstanceOwner* FromOverlapResult(const FOverlapResult& OverlapResult);` — Returns the typed FFastGeoPhysicsBodyInstanceOwner from an overlap result, or nullptr if the overlap did not involve FastGeo geometry or the physics object/owner references are no longer valid.
- L29 _public prototype_ `TWeakObjectPtr<UObject> GetOwnerObject() override;`
- L34 _public prototype_ `virtual bool IsStaticPhysics() const override;`
- L35 _public prototype_ `virtual bool IsMultiBodyOverlap() const override;`
- L36 _public prototype_ `virtual UObject* GetSourceObject() const override;`
- L37 _public prototype_ `virtual FTransform GetPhysicsOwnerTransform() const override;`
- L38 _public prototype_ `virtual ECollisionChannel GetCollisionObjectType() const override;`
- L39 _public prototype_ `virtual ECollisionEnabled::Type GetCollisionEnabled() const override;`
- L40 _public prototype_ `virtual ECollisionResponse GetCollisionResponseToChannel(ECollisionChannel Channel) const override;`
- L41 _public prototype_ `virtual Chaos::FPhysicsObject* GetPhysicsObjectById(Chaos::FPhysicsObjectId Id) const override;`
- L42 _public prototype_ `virtual TArray<Chaos::FPhysicsObject*> GetAllPhysicsObjects() const override;`
- L43 _public prototype_ `virtual FBodyInstance* GetBodyInstance(FName BoneName = NAME_None, bool bGetWelded = true, int32 Index = INDEX_NONE) const override;`
- L44 _public prototype_ `virtual UPhysicalMaterial* GetPhysicsMaterialOverride() const override;`
- L45 _public prototype_ `virtual UMaterialInterface* GetPhysicsMaterialBase() const override;`
- L46 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L47 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 Index) const override;`
- L48 _public prototype_ `virtual UBodySetup* GetPhysicsBodySetup() const override;`
- L49 _public prototype_ `virtual UObject* GetSourceObjectOwner() const override;`
- L50 _public prototype_ `virtual FTransform GetPhysicsOwnerSocketTransform(FName InSocketName) const override;`
- L51 _public prototype_ `virtual bool IsPhysicsOwnerMovable() const override;`
- L52 _public prototype_ `virtual bool IsPhysicsOwnerSimulatingPhysics() const override;`
- L53 _public prototype_ `virtual FVector GetPhysicsOwnerVelocity() const override;`
- L54 _public prototype_ `virtual UObject* GetPhysicsOwnerAttachmentRoot() const override;`
- L55 _public prototype_ `virtual bool IsPhysicsObjectWorldGeometry() const override;`
- L56 _public prototype_ `virtual bool DoesSocketExistOnPhysicsOwner(FName InSocketName) const override;`
- L57 _public prototype_ `virtual const FWalkableSlopeOverride& GetWalkableSlopeOverride() const override;`
- L60 _public function_ `FFastGeoPrimitiveComponent* GetOwnerComponent() const`
- L61 _public function_ `UFastGeoContainer* GetOwnerContainer() const`
- L64 _private prototype_ `static const FFastGeoPhysicsBodyInstanceOwner* FromPhysicsObject(Chaos::FConstPhysicsObjectHandle PhysicsObject);`
- L66 _private prototype_ `void Uninitialize();`
- L67 _private prototype_ `void Initialize(FFastGeoPrimitiveComponent* InOwner);`
- L69 _private member_ `FFastGeoPrimitiveComponent* OwnerComponent;`
- L70 _private member_ `TWeakObjectPtr<UFastGeoContainer> OwnerContainer;`
- L71 _private member_ `static const FName NAME_FastGeoPhysicsBodyInstanceOwner;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoPointLightComponent.h` (Internal)


#### class `FFastGeoPointLightComponentBase`  
`class FFastGeoPointLightComponentBase : public FFastGeoLocalLightComponent`  
_L10-41_
- inherits: `FFastGeoLocalLightComponent`
- L13 _public typedef_ `typedef FFastGeoLocalLightComponent Super;`
- L16 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L18 _public prototype_ `FFastGeoPointLightComponentBase(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L19 _public prototype_ `virtual ~FFastGeoPointLightComponentBase() = default;`
- L23 _public prototype_ `virtual bool ShouldPrecachePSOs() const override;`
- L29 _protected prototype_ `bool ShouldComponentAddToRenderScene() const;`
- L33 _protected function_ `virtual FLocalLightSceneProxyDesc& GetLocalLightSceneProxyDesc() override`
- L34 _protected function_ `virtual const FLocalLightSceneProxyDesc& GetLocalLightSceneProxyDesc() const override`
- L37 _protected prototype_ `virtual FPointLightSceneProxyDesc& GetPointLightSceneProxyDesc() = 0;`
- L38 _protected prototype_ `virtual const FPointLightSceneProxyDesc& GetPointLightSceneProxyDesc() const = 0;`
- L40 _protected prototype_ `bool IsPointLightSupported() const;`

#### class `FFastGeoPointLightComponent`  
`class FFastGeoPointLightComponent : public FFastGeoPointLightComponentBase`  
_L43-72_
- inherits: `FFastGeoPointLightComponentBase`
- L46 _public typedef_ `typedef FFastGeoPointLightComponentBase Super;`
- L49 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L51 _public prototype_ `FFastGeoPointLightComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L52 _public prototype_ `virtual ~FFastGeoPointLightComponent() = default;`
- L56 _public prototype_ `virtual void InitializeFromComponent(UActorComponent* Component) override;`
- L62 _protected prototype_ `virtual FLightSceneProxy* CreateTypedSceneProxy() override;`
- L66 _protected function_ `virtual FPointLightSceneProxyDesc& GetPointLightSceneProxyDesc() override`
- L67 _protected function_ `virtual const FPointLightSceneProxyDesc& GetPointLightSceneProxyDesc() const override`
- L71 _private member_ `FPointLightSceneProxyDesc SceneProxyDesc{};`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoPrimitiveComponent.h` (Internal)


#### class `FFastGeoPrimitiveComponent`  
`class FFastGeoPrimitiveComponent : public FFastGeoComponent, public IPrimitiveComponent`  
_L29-217_
- inherits: `FFastGeoComponent,IPrimitiveComponent`
- L32 _public typedef_ `typedef FFastGeoComponent Super;`
- L35 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L37 _public prototype_ `FFastGeoPrimitiveComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L38 _public prototype_ `virtual ~FFastGeoPrimitiveComponent() = default;`
- L39 _public prototype_ `FFastGeoPrimitiveComponent(const FFastGeoPrimitiveComponent& Other);`
- L41 _public function_ `TArray<URuntimeVirtualTexture*> const& GetRuntimeVirtualTextures() const`
- L42 _public prototype_ `bool IsFirstPersonRelevant() const;`
- L44 _public function_ `FPrimitiveComponentId GetPrimitiveSceneId() const`
- L45 _public function_ `virtual UObject const* AdditionalStatObject() const`
- L47 _public prototype_ `FMatrix GetRenderMatrix() const;`
- L50 _public function_ `FTransform GetComponentTransform() const` — Used by FStaticMeshComponentHelper/FInstancedStaticMeshComponentHelper
- L53 _public prototype_ `virtual void NotifyRenderStateChanged();`
- L55 _public prototype_ `bool IsDrawnInGame() const;`
- L56 _public prototype_ `void SetCollisionEnabled(bool bInCollisionEnabled);`
- L57 _public prototype_ `void SetCustomPrimitiveData(TConstArrayView<float> InCustomPrimitiveData);`
- L58 _public prototype_ `void UpdateVisibility();`
- L59 _public prototype_ `EComponentMobility::Type GetMobility() const;`
- L60 _public prototype_ `UFastGeoSurrogateComponent* GetSurrogateComponent() const;`
- L63 _public prototype_ `virtual bool IsRenderStateDirty() const override;`
- L64 _public prototype_ `virtual bool IsRenderStateCreated() const override;`
- L65 _public prototype_ `virtual bool ShouldCreateRenderState() const override;`
- L66 _public prototype_ `virtual bool IsRegistered() const override;`
- L67 _public prototype_ `virtual bool IsUnreachable() const override;`
- L68 _public prototype_ `virtual bool IsStaticMobility() const override;`
- L69 _public prototype_ `virtual bool IsMipStreamingForced() const override;`
- L70 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L71 _public prototype_ `virtual FSceneInterface* GetScene() const override;`
- L72 _public prototype_ `virtual FPrimitiveSceneProxy* GetSceneProxy() const override;`
- L73 _public prototype_ `virtual void MarkRenderStateDirty() override;`
- L74 _public prototype_ `virtual void DestroyRenderState() override;`
- L75 _public prototype_ `virtual void CreateRenderState(FRegisterComponentContext* Context) override;`
- L76 _public prototype_ `virtual FString GetName() const override;`
- L77 _public prototype_ `virtual FString GetFullName() const override;`
- L78 _public prototype_ `virtual FTransform GetTransform() const override;`
- L79 _public prototype_ `virtual const FBoxSphereBounds& GetBounds() const override;`
- L80 _public prototype_ `float GetLastRenderTimeOnScreen() const override;`
- L81 _public prototype_ `virtual void GetPrimitiveStats(FPrimitiveStats& PrimitiveStats) const override;`
- L82 _public prototype_ `virtual UObject* GetUObject() override;`
- L83 _public prototype_ `virtual const UObject* GetUObject() const override;`
- L84 _public prototype_ `virtual void PrecachePSOs() override;`
- L85 _public prototype_ `virtual UObject* GetOwner() const override;`
- L86 _public prototype_ `virtual FString GetOwnerName() const override;`
- L87 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L88 _public prototype_ `virtual FRenderAssetOwnerStreamingState& GetStreamingState() const override;`
- L89 _public prototype_ `virtual ULevel* GetComponentLevel() const override;`
- L90 _public prototype_ `virtual IPrimitiveComponent* GetLODParentPrimitive() const override;`
- L91 _public prototype_ `virtual float GetMinDrawDistance() const override;`
- L92 _public prototype_ `virtual float GetStreamingScale() const override;`
- L93 _public prototype_ `virtual void OnRenderAssetFirstLodChange(const UStreamableRenderAsset* RenderAsset, int32 FirstLodIndex) override;`
- L94 _public prototype_ `virtual UStreamableRenderAsset* GetStreamableNaniteAsset() const override;`
- L95 _public prototype_ `virtual void GetStreamingRenderAssetInfo(FStreamingTextureLevelContext& LevelContext, TArray<FStreamingRenderAssetPrimitiveInfo>& OutStreamingRenderAssets) const override;`
- L97 _public prototype_ `virtual HHitProxy* CreateMeshHitProxy(int32 SectionIndex, int32 MaterialIndex) override;`
- L99 _public prototype_ `virtual HHitProxy* CreatePrimitiveHitProxies(TArray<TRefCountPtr<HHitProxy> >& OutHitProxies) override;`
- L103 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L104 _public prototype_ `virtual void InitializeDynamicProperties() override;`
- L105 _public prototype_ `virtual void OnAsyncCreatePhysicsStateBegin_GameThread() override;`
- L106 _public prototype_ `virtual void OnAsyncCreatePhysicsState() override;`
- L107 _public prototype_ `virtual void OnAsyncCreatePhysicsStateEnd_GameThread() override;`
- L108 _public prototype_ `virtual void OnAsyncDestroyPhysicsStateBegin_GameThread() override;`
- L109 _public prototype_ `virtual void OnAsyncDestroyPhysicsStateEnd_GameThread() override;`
- L110 _public prototype_ `virtual void OnAsyncDestroyPhysicsState() override;`
- L111 _public prototype_ `virtual bool IsCollisionEnabled() const override;`
- L112 _public prototype_ `virtual bool ShouldComponentAddToRenderScene() const override;`
- L113 _public prototype_ `virtual void DestroyRenderState(FFastGeoDestroyRenderStateContext* Context) override;`
- L115 _public prototype_ `virtual void InitializeFromComponent(UActorComponent* Component) override;`
- L118 _public prototype_ `virtual void PrecachePSOs_Concurrent() override;`
- L119 _public function_ `virtual FPSOPrecacheComponentData& GetPSOPrecacheComponentData() override`
- L120 _public function_ `virtual const FPSOPrecacheComponentData& GetPSOPrecacheComponentData() const override`
- L121 _public function_ `virtual bool NeedsPSORecreate() const override`
- L123 _public prototype_ `bool CheckPSOPrecachingAndBoostPriority(EPSOPrecachePriority NewPSOPrecachePriority = EPSOPrecachePriority::High);`
- L127 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const = 0;`
- L128 _public prototype_ `virtual int32 GetNumMaterials() const = 0;`
- L130 _public prototype_ `FPrimitiveMaterialPropertyDescriptor GetUsedMaterialPropertyDesc(ERHIFeatureLevel::Type FeatureLevel) const;` — `UE_DEPRECATED(5.7, "Please use GetUsedMaterialPropertyDesc with EShaderPlatform argument and not ERHIFeatureLevel::Type")`
- L131 _public prototype_ `FPrimitiveMaterialPropertyDescriptor GetUsedMaterialPropertyDesc(EShaderPlatform InShaderPlatform) const;`
- L135 _public prototype_ `virtual bool IsNavigationRelevant() const;`
- L136 _public function_ `virtual bool ShouldSkipNavigationDirtyAreaOnAddOrRemove()`
- L137 _public prototype_ `virtual FBox GetNavigationBounds() const;`
- L138 _public prototype_ `virtual void GetNavigationData(FNavigationRelevantData& OutData) const;`
- L139 _public prototype_ `virtual EHasCustomNavigableGeometry::Type HasCustomNavigableGeometry() const;`
- L140 _public function_ `virtual bool DoCustomNavigableGeometryExport(FNavigableGeometryExport& GeomExport) const`
- L144 _public prototype_ `virtual void ReserveSurrogateInstanceBodyIndices(FFastGeoSurrogateBodyInstanceIndex& InOutNextAvailableInstanceBodyIndex);`
- L148 _protected prototype_ `virtual FPrimitiveSceneProxyDesc& GetSceneProxyDesc() = 0;`
- L149 _protected prototype_ `virtual const FPrimitiveSceneProxyDesc& GetSceneProxyDesc() const = 0;`
- L151 _protected prototype_ `virtual void InitializeSceneProxyDescFromComponent(UActorComponent* Component) = 0;`
- L152 _protected prototype_ `virtual void ResetSceneProxyDescUnsupportedProperties();`
- L154 _protected prototype_ `virtual void InitializeSceneProxyDescDynamicProperties();`
- L155 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy(ESceneProxyCreationError* OutError) = 0;`
- L156 _protected prototype_ `virtual FPrimitiveSceneDesc BuildSceneDesc();`
- L159 _protected prototype_ `virtual bool IsStaticPhysics() const;`
- L160 _protected prototype_ `virtual bool IsMultiBodyOverlap() const;`
- L161 _protected prototype_ `virtual UObject* GetSourceObject() const;`
- L162 _protected prototype_ `virtual ECollisionChannel GetCollisionObjectType() const;`
- L163 _protected prototype_ `virtual ECollisionEnabled::Type GetCollisionEnabled() const;`
- L164 _protected prototype_ `virtual UPhysicalMaterial* GetPhysicsMaterialOverride() const;`
- L165 _protected prototype_ `virtual ECollisionResponse GetCollisionResponseToChannel(ECollisionChannel Channel) const;`
- L166 _protected prototype_ `virtual Chaos::FPhysicsObject* GetPhysicsObjectById(Chaos::FPhysicsObjectId Id) const;`
- L167 _protected prototype_ `virtual TArray<Chaos::FPhysicsObject*> GetAllPhysicsObjects() const;`
- L168 _protected prototype_ `virtual FBodyInstance* GetBodyInstance(FName BoneName = NAME_None, bool bGetWelded = true, int32 Index = INDEX_NONE) const;`
- L171 _protected function_ `virtual UPhysicalMaterial* GetPhysicalMaterial() const` — `UE_DEPRECATED(5.8, "GetPhysicalMaterial was removed.")`
- L176 _protected member_ `FBoxSphereBounds LocalBounds;` — Persistent data
- L177 _protected member_ `FBoxSphereBounds WorldBounds;`
- L178 _protected member_ `uint8 bIsVisible : 1 = true;`
- L179 _protected member_ `uint8 bStaticWhenNotMoveable : 1 = true;`
- L180 _protected member_ `uint8 bFillCollisionUnderneathForNavmesh : 1 = false;`
- L181 _protected member_ `uint8 bRasterizeAsFilledConvexVolume : 1 = false;`
- L182 _protected member_ `uint8 bCanEverAffectNavigation : 1 = false;`
- L183 _protected member_ `uint8 bMultiBodyOverlap : 1 = false;`
- L184 _protected member_ `int32 SurrogateComponentDescriptorIndex = INDEX_NONE;`
- L185 _protected member_ `FCustomPrimitiveData CustomPrimitiveData;`
- L186 _protected member_ `TEnumAsByte<EHasCustomNavigableGeometry::Type> bHasCustomNavigableGeometry = EHasCustomNavigableGeometry::No;`
- L187 _protected member_ `FBodyInstance BodyInstance;`
- L188 _protected member_ `TArray<URuntimeVirtualTexture*> RuntimeVirtualTextures;`
- L191 _protected member_ `FFastGeoPhysicsBodyInstanceOwner BodyInstanceOwner;` — Runtime Data (transient)
- L192 _protected member_ `FPrimitiveSceneInfoData PrimitiveSceneData{};`
- L194 _protected member_ `TOptional<FBodyInstance::FAsyncTermBodyPayload> AsyncTermBodyPayload;` — Payload used to release BodyInstance resources in asynchronous mode (see OnAsyncDestroyPhysicsState).
- L198 _protected function_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams)`
- L199 _protected prototype_ `void SetupPrecachePSOParams(FPSOPrecacheParams& Params);`
- L202 _protected member_ `FPSOPrecacheComponentData PSOPrecacheComponentData;` — All PSO related data for the component
- L206 _protected member_ `bool bCreatedWithPSOFallbackMaterial = false;` — True when the proxy was created with a fallback material (UseFallbackMaterialUntilPSOPrecached). Used by OnComponentPSOPrecacheCompleted to know this component needs a recreate when PSO completes.
- L210 _private prototype_ `bool UsePSOPrecacheFallbackMaterial() const;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoProceduralISMComponent.h` (Internal)


#### class `FFastGeoProceduralISMComponent`  
`class FFastGeoProceduralISMComponent : public FFastGeoStaticMeshComponentBase`  
_L13-84_
- inherits: `FFastGeoStaticMeshComponentBase`
- L16 _public typedef_ `typedef FFastGeoStaticMeshComponentBase Super;`
- L19 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L21 _public prototype_ `FFastGeoProceduralISMComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L22 _public prototype_ `virtual ~FFastGeoProceduralISMComponent() = default;`
- L24 _public prototype_ `void InitializeFromComponentDescriptor(const FProceduralISMComponentDescriptor& InDescriptor);`
- L27 _public prototype_ `void SetSpatialHashes(TArray<FInstanceSceneDataBuffers::FCompressedSpatialHashItem>&& InSpatialHashes);` — Set spatial hashes which provide bounds for sub-ranges of instances within this primitive, enabling early CPU culling.
- L34 _public prototype_ `void SetHitProxyTargetActor(AActor* InActor);` — Sets an actor to use as the hit proxy target when this component is clicked in the editor. If set, clicking this primitive in the editor will select InActor instead of the container. Must be called before Register().
- L36 _public prototype_ `void UpdateEditorSelectionState();`
- L40 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L45 _protected function_ `virtual FPrimitiveSceneProxyDesc& GetSceneProxyDesc() override`
- L46 _protected function_ `virtual const FPrimitiveSceneProxyDesc& GetSceneProxyDesc() const override`
- L47 _protected prototype_ `virtual FPrimitiveSceneDesc BuildSceneDesc() override;`
- L48 _protected function_ `virtual bool IsNavigationRelevant() const override`
- L50 _protected prototype_ `virtual void ResetSceneProxyDescUnsupportedProperties() override;`
- L51 _protected prototype_ `virtual HHitProxy* CreateMeshHitProxy(int32 SectionIndex, int32 MaterialIndex) override;`
- L53 _protected prototype_ `virtual void InitializeSceneProxyDescDynamicProperties() override;`
- L54 _protected prototype_ `virtual void ApplyWorldTransform(const FTransform& InTransform) override;`
- L55 _protected prototype_ `virtual HHitProxy* CreatePrimitiveHitProxies(TArray<TRefCountPtr<HHitProxy>>& OutHitProxies) override;`
- L59 _protected function_ `virtual FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() override`
- L60 _protected function_ `virtual const FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() const override`
- L61 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateStaticMeshSceneProxy(const Nanite::FMaterialAudit& NaniteMaterials, bool bCreateNanite) override;`
- L63 _protected prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams) override;`
- L67 _protected prototype_ `TSharedPtr<FInstanceDataSceneProxy, ESPMode::ThreadSafe>& BuildInstanceData();`
- L71 _private member_ `int32 NumInstances = 0;` — Persistent Data
- L72 _private member_ `int32 NumCustomDataFloats = 0;`
- L73 _private member_ `FBox PrimitiveBoundsOverride = FBox(ForceInit);`
- L74 _private member_ `FInstancedStaticMeshSceneProxyDesc SceneProxyDesc{};`
- L77 _private member_ `TSharedPtr<FInstanceDataSceneProxy, ESPMode::ThreadSafe> DataProxy{};` — Transient data
- L78 _private member_ `TArray<FInstanceSceneDataBuffers::FCompressedSpatialHashItem> SpatialHashes;`
- L80 _private member_ `TWeakObjectPtr<AActor> HitProxyTargetActor;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoRectLightComponent.h` (Internal)


#### class `FFastGeoRectLightComponent`  
`class FFastGeoRectLightComponent : public FFastGeoLocalLightComponent`  
_L8-37_
- inherits: `FFastGeoLocalLightComponent`
- L11 _public typedef_ `typedef FFastGeoLocalLightComponent Super;`
- L14 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L16 _public prototype_ `FFastGeoRectLightComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L17 _public prototype_ `virtual ~FFastGeoRectLightComponent() = default;`
- L21 _public prototype_ `virtual void InitializeFromComponent(UActorComponent* Component) override;`
- L27 _protected prototype_ `virtual FLightSceneProxy* CreateTypedSceneProxy() override;`
- L31 _protected function_ `virtual FLocalLightSceneProxyDesc& GetLocalLightSceneProxyDesc() override`
- L32 _protected function_ `virtual const FLocalLightSceneProxyDesc& GetLocalLightSceneProxyDesc() const override`
- L36 _private member_ `FRectLightSceneProxyDesc SceneProxyDesc{};`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoRegisteredComponent.h` (Internal)


#### struct `FFastGeoRegisteredComponent`  
`struct FFastGeoRegisteredComponent`  
_L9-45_
- L11 _public function_ `FFastGeoRegisteredComponent(FFastGeoComponent* InComponent) : Component(InComponent)`
- L21 _public function_ `template <class T> FORCEINLINE T* TryGetRegistered() const` — Game-thread only -- IsRegistered / IsRegistering below assert IsInGameThread.
- L37 _public function_ `FORCEINLINE bool operator==(const FFastGeoRegisteredComponent& Other) const`
- L43 _private member_ `FWeakFastGeoComponent Component;`
- L44 _private member_ `int32 RegistrationEpoch = -1;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoRenderStateUtils.h` (Internal)


#### struct `TFastGeoRenderStateBatch`  
`template <typename T = FFastGeoComponent*> struct TFastGeoRenderStateBatch`  
_L18-45_
- desc: General-purpose progress tracker for budgeted render state work. Used by create, deferred create, recreate, and ProcessPendingRecreate paths. Default element type is FFastGeoComponent* (raw pointer). ProcessPendingRecreate uses TFastGeoRenderStateBatch<FFastGeoRegisteredComponent> to avoid persisting raw pointers across frames -- stale components are validated inline via TryGetRegistered.
- L20 _public function_ `TFastGeoRenderStateBatch()`
- L25 _public function_ `void Reset()`
- L34 _public function_ `bool IsCompleted() const`
- L39 _public member_ `TArray<T> ComponentsToProcess;`
- L41 _public member_ `int32 NumToProcess;`
- L42 _public member_ `int32 NumProcessed;`
- L43 _public member_ `int32 TotalNumProcessed;`
- L44 _public member_ `bool bIsInBlockingWait = false;`

#### Free symbols / members of external scopes

- L47 _typedef_ `using FFastGeoRenderStateBatch = TFastGeoRenderStateBatch<FFastGeoComponent*>;`
- L49 _namespace_ `namespace FastGeo`
- L56 _function_ `template <typename T, typename FWorkFn> FORCEINLINE bool AdvanceRenderStateBudgeted(TFastGeoRenderStateBatch<T>& State, const UE::FTimeout& Timeout, FWorkFn&& WorkFn)` (scope `FastGeo`) — Processes components in a batch using ParallelFor with FTaskTagScope (ParallelGT pattern). Used by sync-mode create, destroy, deferred create, recreate, and ProcessPendingRecreate. Returns true if all components were processed, false if timeout expired. WorkFn receives T& (e.g., FFastGeoComponent*& for raw batches, FFastGeoRegisteredComponent& for safe batches).
- L79 _function_ `` (scope `FastGeo::AdvanceRenderStateBudgeted`)

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoSkinnedMeshComponent.h` (Internal)


#### class `FFastGeoSkinnedMeshComponentBase`  
`class FFastGeoSkinnedMeshComponentBase : public FFastGeoMeshComponent`  
_L15-101_
- inherits: `FFastGeoMeshComponent`
- L18 _public typedef_ `typedef FFastGeoMeshComponent Super;`
- L21 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L23 _public prototype_ `FFastGeoSkinnedMeshComponentBase(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L24 _public prototype_ `virtual ~FFastGeoSkinnedMeshComponentBase() = default;`
- L27 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L28 _public prototype_ `virtual UBodySetup* GetBodySetup() const override;`
- L30 _public prototype_ `virtual void InitializeFromComponent(UActorComponent* Component) override;`
- L35 _public prototype_ `virtual void ForEachMaterial(TFunctionRef<void(UMaterialInterface*, bool bIsNaniteOverride)> Func) const override;`
- L36 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L37 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L38 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L44 _protected prototype_ `virtual void InitializeSceneProxyDescFromComponent(UActorComponent* Component) override;`
- L45 _protected prototype_ `virtual void ResetSceneProxyDescUnsupportedProperties() override;`
- L47 _protected prototype_ `virtual void InitializeSceneProxyDescDynamicProperties() override;`
- L48 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy(ESceneProxyCreationError* OutError = nullptr) override;`
- L49 _protected prototype_ `virtual void DestroyRenderState(FFastGeoDestroyRenderStateContext* Context) override;`
- L53 _protected prototype_ `virtual UMaterialInterface* GetOverlayMaterial() const override;`
- L54 _protected prototype_ `virtual const TArray<TObjectPtr<UMaterialInterface>>& GetComponentMaterialSlotsOverlayMaterial() const override;`
- L55 _protected prototype_ `virtual void GetDefaultMaterialSlotsOverlayMaterial(TArray<TObjectPtr<UMaterialInterface>>& AssetMaterialSlotOverlayMaterials) const override;`
- L59 _protected prototype_ `virtual FSkeletalMeshObject* CreateMeshObject();`
- L60 _protected prototype_ `virtual FSkinnedMeshSceneProxyDesc& GetSkinnedMeshSceneProxyDesc() = 0;`
- L61 _protected prototype_ `virtual const FSkinnedMeshSceneProxyDesc& GetSkinnedMeshSceneProxyDesc() const = 0;`
- L62 _protected prototype_ `virtual FPrimitiveSceneProxy* AllocateSceneProxy() = 0;`
- L66 _protected prototype_ `virtual void UpdateSkinning();` — Default implementation builds ref-pose DynamicData and calls RunMeshObjectUpdate. Paths whose FSkeletalMeshObject consumes only LODIndex (e.g. the instanced path) override this to skip the ref-pose fill.
- L72 _protected prototype_ `void RunMeshObjectUpdate(FSkinnedMeshSceneProxyDynamicData& InOutDynamicData);` — Shared MeshObject->Update plumbing: LOD compute + clamp + asset/render-data validation + the Update call itself. Callers provide a pre-built DynamicData; this routine fills in the LOD index and does the safety guards.
- L74 _protected prototype_ `FBoxSphereBounds CalcMeshBound(const FVector3f& InRootOffset, bool bInUsePhysicsAsset, const FTransform& InLocalToWorld) const;`
- L75 _protected function_ `USkinnedAsset* GetSkinnedAsset() const`
- L76 _protected function_ `FSkeletalMeshObject* GetMeshObject()`
- L77 _protected function_ `const FSkeletalMeshObject* GetMeshObject() const`
- L78 _protected prototype_ `void DestroyMeshObject();`
- L80 _protected function_ `bool IsDisallowNanite() const`
- L81 _protected function_ `bool IsForceDisableNanite() const`
- L84 _protected function_ `UPhysicsAsset* GetPhysicsAsset() const`
- L85 _protected function_ `int32 GetPredictedLODLevel() const`
- L90 _protected member_ `TArray<ESkinCacheUsage> SkinCacheUsage;` — Persistent data
- L91 _protected member_ `bool bOverrideMinLod : 1 = false;`
- L92 _protected member_ `bool bIncludeComponentLocationIntoBounds = false;`
- L93 _protected member_ `bool bHideSkin : 1 = false;`
- L94 _protected member_ `int32 MinLodModel = 0;`
- L97 _protected member_ `TArray<FSkelMeshComponentLODInfo> LODInfo;` — Transient
- L98 _protected member_ `FSkeletalMeshObject* MeshObject = nullptr;`

#### class `FFastGeoSkinnedMeshComponent`  
`class FFastGeoSkinnedMeshComponent : public FFastGeoSkinnedMeshComponentBase`  
_L103-131_
- inherits: `FFastGeoSkinnedMeshComponentBase`
- L106 _public typedef_ `typedef FFastGeoSkinnedMeshComponentBase Super;`
- L109 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L111 _public prototype_ `FFastGeoSkinnedMeshComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L112 _public prototype_ `virtual ~FFastGeoSkinnedMeshComponent() = default;`
- L116 _protected function_ `virtual FPrimitiveSceneProxyDesc& GetSceneProxyDesc() override`
- L117 _protected function_ `virtual const FPrimitiveSceneProxyDesc& GetSceneProxyDesc() const override`
- L118 _protected prototype_ `virtual void ApplyWorldTransform(const FTransform& InTransform) override;`
- L122 _protected function_ `virtual FSkinnedMeshSceneProxyDesc& GetSkinnedMeshSceneProxyDesc() override`
- L123 _protected function_ `virtual const FSkinnedMeshSceneProxyDesc& GetSkinnedMeshSceneProxyDesc() const override`
- L124 _protected prototype_ `virtual FPrimitiveSceneProxy* AllocateSceneProxy() override;`
- L130 _private member_ `FSkinnedMeshSceneProxyDesc SceneProxyDesc{};`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoSpotLightComponent.h` (Internal)


#### class `FFastGeoSpotLightComponent`  
`class FFastGeoSpotLightComponent : public FFastGeoPointLightComponentBase`  
_L8-37_
- inherits: `FFastGeoPointLightComponentBase`
- L11 _public typedef_ `typedef FFastGeoPointLightComponentBase Super;`
- L14 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L16 _public prototype_ `FFastGeoSpotLightComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L17 _public prototype_ `virtual ~FFastGeoSpotLightComponent() = default;`
- L21 _public prototype_ `virtual void InitializeFromComponent(UActorComponent* Component) override;`
- L27 _protected prototype_ `virtual FLightSceneProxy* CreateTypedSceneProxy() override;`
- L31 _protected function_ `virtual FPointLightSceneProxyDesc& GetPointLightSceneProxyDesc() override`
- L32 _protected function_ `virtual const FPointLightSceneProxyDesc& GetPointLightSceneProxyDesc() const override`
- L36 _private member_ `FSpotLightSceneProxyDesc SceneProxyDesc{};`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoStaticMeshComponent.h` (Internal)


#### class `FFastGeoStaticMeshComponentBase`  
`class FFastGeoStaticMeshComponentBase : public FFastGeoMeshComponent, public IStaticMeshComponent`  
_L22-131_
- inherits: `FFastGeoMeshComponent,IStaticMeshComponent`
- L25 _public typedef_ `typedef FFastGeoMeshComponent Super;`
- L28 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L30 _public prototype_ `FFastGeoStaticMeshComponentBase(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L31 _public prototype_ `virtual ~FFastGeoStaticMeshComponentBase() = default;`
- L33 _public prototype_ `const FCollisionResponseContainer& GetCollisionResponseToChannels() const;`
- L34 _public prototype_ `UMaterialInterface* GetNaniteAuditMaterial(int32 MaterialIndex) const;`
- L35 _public prototype_ `const Nanite::FResources* GetNaniteResources() const;`
- L36 _public prototype_ `bool HasValidNaniteData() const;`
- L37 _public prototype_ `bool UseNaniteOverrideMaterials(bool bDoingMaterialAudit) const;`
- L38 _public prototype_ `bool ShouldCreateNaniteProxy(Nanite::FMaterialAudit* OutNaniteMaterials) const;`
- L39 _public prototype_ `virtual UObject const* AdditionalStatObject() const override;`
- L40 _public prototype_ `bool IsReverseCulling() const;`
- L41 _public prototype_ `bool IsDisallowNanite() const;`
- L42 _public prototype_ `bool IsForceDisableNanite() const;`
- L43 _public prototype_ `bool IsForceNaniteForMasked() const;`
- L44 _public prototype_ `int32 GetForcedLodModel() const;`
- L45 _public prototype_ `bool GetOverrideMinLOD() const;`
- L46 _public prototype_ `int32 GetMinLOD() const;`
- L47 _public prototype_ `bool GetForceNaniteForMasked() const;`
- L48 _public prototype_ `int32 GetWorldPositionOffsetDisableDistance() const;`
- L49 _public prototype_ `float GetNanitePixelProgrammableDistance() const;`
- L50 _public prototype_ `bool EvaluateWorldPositionOffsetInRayTracing() const;`
- L52 _public prototype_ `bool IsDisplayNaniteFallbackMesh() const;`
- L56 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L57 _public prototype_ `virtual void InitializeDynamicProperties() override;`
- L58 _public prototype_ `virtual UBodySetup* GetBodySetup() const override;`
- L60 _public prototype_ `virtual void InitializeFromComponent(UActorComponent* Component) override;`
- L66 _public function_ `virtual void OnMeshRebuild(bool bRenderDataChanged) override`
- L67 _public function_ `virtual void PreStaticMeshCompilation() override`
- L68 _public function_ `virtual void PostStaticMeshCompilation() override`
- L70 _public prototype_ `virtual UStaticMesh* GetStaticMesh() const override;`
- L71 _public prototype_ `virtual IPrimitiveComponent* GetPrimitiveComponentInterface() override;`
- L75 _public prototype_ `virtual bool IsNavigationRelevant() const override;`
- L76 _public prototype_ `virtual FBox GetNavigationBounds() const override;`
- L77 _public prototype_ `virtual void GetNavigationData(FNavigationRelevantData& Data) const override;`
- L78 _public prototype_ `virtual bool DoCustomNavigableGeometryExport(FNavigableGeometryExport& GeomExport) const override;`
- L79 _public prototype_ `virtual void ForEachMaterial(TFunctionRef<void(UMaterialInterface*, bool bIsNaniteOverride)> Func) const override;`
- L80 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L81 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L82 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L84 _public prototype_ `virtual void NotifyRenderStateChanged() override;`
- L91 _protected prototype_ `virtual void InitializeSceneProxyDescFromComponent(UActorComponent* Component) override;`
- L92 _protected prototype_ `virtual void ResetSceneProxyDescUnsupportedProperties() override;`
- L94 _protected prototype_ `virtual void InitializeSceneProxyDescDynamicProperties() override;`
- L95 _protected prototype_ `virtual void ApplyWorldTransform(const FTransform& InTransform) override;`
- L96 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy(ESceneProxyCreationError* OutError = nullptr) override;`
- L100 _protected prototype_ `virtual UMaterialInterface* GetOverlayMaterial() const override;`
- L101 _protected prototype_ `virtual const TArray<TObjectPtr<UMaterialInterface>>& GetComponentMaterialSlotsOverlayMaterial() const override;`
- L102 _protected prototype_ `virtual void GetDefaultMaterialSlotsOverlayMaterial(TArray<TObjectPtr<UMaterialInterface>>& OutMaterialSlotOverlayMaterials) const override;`
- L105 _protected prototype_ `virtual FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() = 0;`
- L106 _protected prototype_ `virtual const FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() const = 0;`
- L107 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateStaticMeshSceneProxy(const Nanite::FMaterialAudit& NaniteMaterials, bool bCreateNanite);`
- L108 _protected prototype_ `UMaterialInterface* GetMaterial(int32 MaterialIndex, bool bDoingNaniteMaterialAudit) const;`
- L109 _protected prototype_ `bool ShouldExportAsObstacle(const UNavCollisionBase& InNavCollision) const;`
- L111 _protected prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams);`
- L115 _protected member_ `bool bUseDefaultCollision = false;`
- L121 _protected member_ `TArray<FFastGeoStaticMeshComponentLODInfo> LODData;`
- L122 _protected member_ `FDelegateHandle OnResourceUpdated;`
- L123 _protected member_ `FDelegateHandle OnContainerUnregistered;`

#### struct `FFastGeoStaticMeshComponentBase::FFastGeoStaticMeshComponentLODInfo`  
`struct FFastGeoStaticMeshComponentLODInfo`  
_L117-120_
- desc: Temporary until LODData support
- L119 _public member_ `FColorVertexBuffer* OverrideVertexColors;`

#### class `FFastGeoStaticMeshComponent`  
`class FFastGeoStaticMeshComponent : public FFastGeoStaticMeshComponentBase`  
_L133-158_
- inherits: `FFastGeoStaticMeshComponentBase`
- L136 _public typedef_ `typedef FFastGeoStaticMeshComponentBase Super;`
- L139 _public member_ `static const FFastGeoElementType Type;` — Static type identifier for this element class
- L141 _public prototype_ `FFastGeoStaticMeshComponent(int32 InComponentIndex = INDEX_NONE, FFastGeoElementType InType = Type);`
- L142 _public prototype_ `virtual ~FFastGeoStaticMeshComponent() = default;`
- L146 _protected function_ `virtual FPrimitiveSceneProxyDesc& GetSceneProxyDesc() override`
- L147 _protected function_ `virtual const FPrimitiveSceneProxyDesc& GetSceneProxyDesc() const override`
- L148 _protected prototype_ `virtual void GetBodyInstances(TArray<FBodyInstance*>& OutBodyInstances) override;`
- L152 _protected function_ `virtual FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() override`
- L153 _protected function_ `virtual const FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() const override`
- L157 _private member_ `FStaticMeshSceneProxyDesc SceneProxyDesc{};`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace ERHIFeatureLevel`
- L16 _namespace_ `namespace Nanite`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoSurrogateActor.h` (Internal)


#### class `AFastGeoSurrogateActor`  
`class AFastGeoSurrogateActor : public AActor`  
_L12-53_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `AActor`
- L18 _public prototype_ `AFastGeoSurrogateActor();`
- L20 _public prototype_ `const FFastGeoSurrogateComponentDescriptor* GetSurrogateComponentDescriptor(int32 SurrogateComponentDescriptorIndex) const;`
- L21 _public prototype_ `UFastGeoSurrogateComponent* GetSurrogateComponent(int32 SurrogateComponentDescriptorIndex) const;`
- L22 _public function_ `bool HasRegisteredWithFastGeo() const`
- L23 _public function_ `bool IsActive() const`
- L28 _protected prototype_ `virtual void PostInitializeComponents() override;`
- L29 _protected prototype_ `virtual void PostUnregisterAllComponents() override;`
- L30 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L35 _private prototype_ `bool UnregisterFromFastGeo();`
- L39 _private member_ `TArray<FFastGeoSurrogateComponentDescriptor> SurrogateComponentDescriptors;` — `UPROPERTY()` — Maps surrogate component descriptor index to surrogate component descriptor
- L43 _private member_ `TArray<TObjectPtr<UFastGeoSurrogateComponent>> SurrogateComponents;` — `UPROPERTY(Transient)` — Maps surrogate component descriptor index to surrogate component
- L47 _private member_ `bool bHasRegisteredWithFastGeo = false;` — `UPROPERTY(Transient)` — Whether actor has registered with FastGeo container
- L50 _private member_ `bool bIsActive = false;` — `UPROPERTY(Transient)`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoSurrogateBodyInstanceIndex.h` (Internal)


#### struct `FFastGeoSurrogateBodyInstanceIndex`  
`struct FFastGeoSurrogateBodyInstanceIndex`  
_L7-98_
- L9 _public function_ `static FFastGeoSurrogateBodyInstanceIndex FromEncoded(int32 InEncodedIndex)`
- L15 _public function_ `static FFastGeoSurrogateBodyInstanceIndex Encode(int32 InRawIndex)`
- L24 _public function_ `static int32 Decode(int32 Index)`
- L29 _public function_ `static bool IsEncoded(int32 Index)`
- L34 _public function_ `int32 Decode() const`
- L39 _public function_ `bool IsEncoded() const`
- L44 _public function_ `int32 GetEncoded() const`
- L49 _public function_ `explicit operator int32() const`
- L54 _public function_ `FFastGeoSurrogateBodyInstanceIndex& operator++()`
- L59 _public function_ `FFastGeoSurrogateBodyInstanceIndex operator++(int)`
- L66 _public function_ `FFastGeoSurrogateBodyInstanceIndex& operator+=(int32 Count)`
- L88 _private function_ `explicit FFastGeoSurrogateBodyInstanceIndex(int32 InEncoded) : EncodedIndex(InEncoded)`
- L94 _private member_ `int32 EncodedIndex = INDEX_NONE;`
- L97 _private member_ `static constexpr int32 BodyInstanceIndexEncodeBit = 1 << 30;` — Bit 30 used to flag that a BodyInstance Index has been encoded.

#### Free symbols / members of external scopes

- L81 _function_ `friend FFastGeoSurrogateBodyInstanceIndex operator+(FFastGeoSurrogateBodyInstanceIndex Lhs, int32 Count)`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoSurrogateComponent.h` (Internal)


#### class `UFastGeoSurrogateComponent`  
`class UFastGeoSurrogateComponent : public UPrimitiveComponent`  
_L13-80_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `UPrimitiveComponent`
- L19 _public prototype_ `UFastGeoSurrogateComponent();`
- L22 _public prototype_ `virtual void OnRegister() override;`
- L23 _public prototype_ `virtual bool ShouldCreatePhysicsState() const override;`
- L24 _public prototype_ `virtual void OnCreatePhysicsState() override;`
- L25 _public prototype_ `virtual void OnDestroyPhysicsState() override;`
- L32 _public function_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override`
- L33 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L34 _public prototype_ `virtual FBodyInstance* GetBodyInstance(FName BoneName = NAME_None, bool bGetWelded = true, int32 Index = INDEX_NONE) const override;`
- L35 _public function_ `virtual bool IsGravityEnabled() const override`
- L36 _public function_ `virtual bool GetUpdateKinematicFromSimulation() const override`
- L37 _public function_ `virtual bool GetGyroscopicTorqueEnabled() const override`
- L38 _public function_ `virtual bool ShouldDispatchWakeEvents(FName BoneName) const override`
- L39 _public function_ `virtual float GetLinearDamping() const override`
- L40 _public function_ `virtual float GetAngularDamping() const override`
- L41 _public function_ `virtual FVector GetInertiaTensor(FName BoneName = NAME_None) const override`
- L42 _public function_ `virtual float GetMaxDepenetrationVelocity(FName BoneName = NAME_None) override`
- L43 _public function_ `virtual bool IsAnyRigidBodyAwake() override`
- L47 _public function_ `virtual FVector GetComponentVelocity() const override`
- L48 _public function_ `virtual bool IsSimulatingPhysics(FName BoneName = NAME_None) const override`
- L49 _public prototype_ `virtual ECollisionEnabled::Type GetCollisionEnabled() const override;`
- L50 _public prototype_ `virtual ECollisionResponse GetCollisionResponseToChannel(ECollisionChannel Channel) const override;`
- L51 _public prototype_ `virtual const FCollisionResponseContainer& GetCollisionResponseToChannels() const override;`
- L55 _public function_ `virtual bool IsMultiBodyOverlap() const override`
- L59 _public prototype_ `virtual Chaos::FPhysicsObject* GetPhysicsObjectById(Chaos::FPhysicsObjectId Id) const override;`
- L60 _public prototype_ `virtual TArray<Chaos::FPhysicsObject*> GetAllPhysicsObjects() const override;`
- L63 _public prototype_ `void RegisterBodyInstances(const TArray<FBodyInstance*>& InBodyInstances);`
- L64 _public prototype_ `void UnregisterBodyInstances();`
- L68 _protected function_ `bool HasRegisteredBodyInstances() const`
- L69 _protected prototype_ `void SetSurrogateComponentDescriptor(const FFastGeoSurrogateComponentDescriptor& InComponentDesc);`
- L70 _protected function_ `int32 GetDescriptorIndex() const`
- L73 _protected member_ `int32 DescriptorIndex = INDEX_NONE;` — `UPROPERTY()`
- L75 _protected member_ `TArray<FBodyInstance*> IndexToBodyInstance;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoSurrogateComponentDescriptor.h` (Internal)


#### struct `FFastGeoSurrogateComponentDescriptor`  
`struct FFastGeoSurrogateComponentDescriptor`  
_L11-80_
- reflection: `USTRUCT()`
- L16 _public member_ `TEnumAsByte<ECollisionEnabled::Type> CollisionEnabled;` — `UPROPERTY()`
- L19 _public member_ `TEnumAsByte<ECollisionChannel> ObjectType;` — `UPROPERTY()`
- L22 _public member_ `FCollisionResponseContainer ResponseContainer;` — `UPROPERTY()`
- L25 _public member_ `FWalkableSlopeOverride WalkableSlopeOverride;` — `UPROPERTY()`
- L28 _public member_ `TEnumAsByte<ECanBeCharacterBase> CanCharacterStepUpOn;` — `UPROPERTY()`
- L30 _public function_ `FFastGeoSurrogateComponentDescriptor() : CollisionEnabled(ECollisionEnabled::NoCollision) , ObjectType(ECollisionChannel::ECC_WorldStatic) , CanCharacterStepUpOn(ECanBeCharacterBase::ECB_No)`
- L38 _public function_ `FFastGeoSurrogateComponentDescriptor(const UPrimitiveComponent& InPrimitiveComponent) : CollisionEnabled(InPrimitiveComponent.BodyInstance.GetCollisionEnabled()) , ObjectType(InPrimitiveComponent.BodyInstance.GetObjectType()) , ResponseContainer(InPrimitiveComponent.BodyInstance.GetResponseToChannels()) , WalkableSlopeOverride(ResolveWalkableSlopeOverride(InPrimitiveComponent)) , CanCharacterStepUpOn(InPrimitiveComponent.CanCharacterStepUpOn)`
- L54 _private function_ `static FWalkableSlopeOverride ResolveWalkableSlopeOverride(const UPrimitiveComponent& InPrimitiveComponent)` — FBodyInstance::GetWalkableSlopeOverride() falls back to the BodySetup's value only when FBodyInstance::BodySetup is valid -- which is only true after InitBody() has run. The surrogate descriptor is built at cell-transform time before any per-actor physics state creation, so the BodyInstance read short-circuits to its (default-empty) member and the BodySetup default authored on the static mesh asset is lost. Resolve it explicitly here, mirroring what FBodyInstance::GetWalkableSlopeOverride() would return after init.
- L71 _public function_ `FORCEINLINE bool operator==(const FFastGeoSurrogateComponentDescriptor& Other) const`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoWeakElement.h` (Internal)


#### class `FWeakFastGeoComponentCluster`  
`class FWeakFastGeoComponentCluster`  
_L10-50_
- L13 _public function_ `FWeakFastGeoComponentCluster(FFastGeoComponentCluster* InComponentCluster = nullptr)`
- L23 _public function_ `FORCEINLINE bool operator==(const FWeakFastGeoComponentCluster& Other) const`
- L30 _public function_ `FORCEINLINE FFastGeoComponentCluster* Get() const`
- L40 _public function_ `template <class T> FORCEINLINE T* Get() const`
- L47 _private member_ `TWeakObjectPtr<UFastGeoContainer> ContainerWeak;`
- L48 _private member_ `uint32 ComponentClusterTypeID = INDEX_NONE;`
- L49 _private member_ `int32 ComponentClusterIndex = INDEX_NONE;`

#### class `FWeakFastGeoComponent`  
`class FWeakFastGeoComponent`  
_L52-98_
- L55 _public prototype_ `FWeakFastGeoComponent() = default;`
- L57 _public function_ `FWeakFastGeoComponent(FFastGeoComponent* InComponent)`
- L71 _public function_ `FORCEINLINE bool operator==(const FWeakFastGeoComponent& Other) const`
- L78 _public function_ `FORCEINLINE FFastGeoComponent* Get() const`
- L88 _public function_ `template <class T> FORCEINLINE T* Get() const`
- L95 _private member_ `FWeakFastGeoComponentCluster ComponentClusterWeak;`
- L96 _private member_ `uint32 ComponentTypeID = INDEX_NONE;`
- L97 _private member_ `int32 ComponentIndex = INDEX_NONE;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/FastGeoWorldSubsystem.h` (Internal)


#### class `UFastGeoWorldSubsystem`  
`class UFastGeoWorldSubsystem : public UTickableWorldSubsystem`  
_L18-207_
- reflection: `UCLASS()`
- inherits: `UTickableWorldSubsystem`
- L22 _private prototype_ `UFastGeoWorldSubsystem();`
- L23 _private prototype_ `~UFastGeoWorldSubsystem();`
- L27 _public prototype_ `virtual void Deinitialize() override;`
- L31 _public prototype_ `virtual void PostInitialize() override;`
- L32 _public prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;`
- L36 _public prototype_ `virtual bool IsTickableInEditor() const override;`
- L37 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L38 _public prototype_ `virtual TStatId GetStatId() const override;`
- L41 _public prototype_ `void AddToComponentsPendingRecreate(FFastGeoComponent* InComponent);`
- L42 _public prototype_ `void ProcessPendingRecreate();`
- L48 _public prototype_ `void PushAsyncPrecachePSOsJob(UFastGeoContainer* FastGeo);` — Start a job that will precache PSOs asynchronously for a specified FastGeo container. @param FastGeo: FastGeo container.
- L54 _public prototype_ `void PushAsyncCreateRenderStateJob(UFastGeoContainer* FastGeo);` — Start a job that will create render state asynchronously for a specified FastGeo container. @param FastGeo: FastGeo container.
- L60 _public prototype_ `void PushAsyncDestroyRenderStateJob(UFastGeoContainer* FastGeo);` — Start a job that will destroy render state asynchronously for a specified FastGeo container. @param FastGeo: FastGeo container.
- L64 _public prototype_ `void PushAsyncDeferredCreateJob(UFastGeoContainer* FastGeo);` — Start a job to create render state for PSO-deferred components (DelayUntilPSOPrecached).
- L67 _public prototype_ `void PushAsyncRecreateRenderStateJob(UFastGeoContainer* FastGeo);` — Start a job to recreate render state for components with fallback material (UseFallbackMaterialUntilPSOPrecached).
- L74 _public prototype_ `void ProcessAsyncRenderStateJobs(bool bWaitForCompletion = false);` — Update progress of asynchronous render state creation and destruction. @param bWaitForCompletion : Whether to wait for pending asynchronous tasks to complete.
- L80 _public prototype_ `void PushAsyncCreatePhysicsStateJobs(UFastGeoContainer* FastGeo);` — Start a job that will create physics state asynchronously for a specified FastGeo container. @param FastGeo: FastGeo container.
- L86 _public prototype_ `void PushAsyncDestroyPhysicsStateJobs(UFastGeoContainer* FastGeo);` — Start a job that will destroy physics state asynchronously for a specified FastGeo container. @param FastGeo: FastGeo container.
- L88 _public prototype_ `static bool IsEnableDebugView();`
- L89 _public prototype_ `static bool ShouldAllowSurrogateComponents();`
- L92 _public prototype_ `static bool IsFastGeoVisible();`
- L95 _public prototype_ `bool IsWaitingForCompletion() const;`
- L96 _public function_ `bool IsReregistering() const`
- L100 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnComponentsPreRecreate, const TArray<FFastGeoRegisteredComponent>&);`
- L103 _public member_ `static FOnComponentsPreRecreate ComponentsPreRecreateEvent;` — Called right before processing any registered FastGeo components pending recreate each frame.
- L108 _private prototype_ `void TickDebugTraceHUD();`
- L111 _private prototype_ `void OnUpdateLevelStreaming();`
- L112 _private prototype_ `void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);`
- L113 _private prototype_ `void OnLevelStreamingStateChanged(UWorld* World, const ULevelStreaming* StreamingLevel, ULevel* LevelIfLoaded, ELevelStreamingState PrevState, ELevelStreamingState NewState);`
- L114 _private prototype_ `void OnLevelStartedAddToWorld(UWorld* World, const ULevelStreaming* StreamingLevel, ULevel* Level);`
- L115 _private prototype_ `void OnLevelStartedRemoveFromWorld(UWorld* World, const ULevelStreaming* StreamingLevel, ULevel* Level);`
- L116 _private prototype_ `void OnLevelComponentsUpdated(UWorld* World, ULevel* Level);`
- L117 _private prototype_ `void OnLevelComponentsCleared(UWorld* World, ULevel* Level);`
- L118 _private prototype_ `void OnAddLevelToWorldExtension(ULevel* Level, const bool bWaitForCompletion, bool& bOutHasCompleted);`
- L119 _private prototype_ `void OnRemoveLevelFromWorldExtension(ULevel* Level, const bool bWaitForCompletion, bool& bOutHasCompleted);`
- L120 _private prototype_ `void OnGlobalComponentReregisterContextCreated();`
- L121 _private prototype_ `void OnGlobalComponentReregisterContextDestroyed();`
- L123 _private prototype_ `void OnLevelAddedToWorld(ULevel* Level, UWorld* World);`
- L124 _private prototype_ `void OnLevelRemovedFromWorld(ULevel* Level, UWorld* World);`
- L125 _private prototype_ `void CheckNoPendingTasks(ULevel* Level, UWorld* World, bool bIncludeRecreateTasks = true);`
- L128 _private prototype_ `void OnPreRecreateScene(UWorld* World);`
- L130 _private prototype_ `void ForEachHLODObjectInCell(const UWorldPartitionRuntimeCell*, TFunction<void(IWorldPartitionHLODObject*)>);`
- L131 _private prototype_ `void RequestAsyncRenderStateTasksBudget_Concurrent(float& OutAvailableTimeBudgetMS, int32& OutAvaiableComponentsBudget, int32& OutTimeEpoch);`
- L132 _private prototype_ `void CommitAsyncRenderStateTasksBudget_Concurrent(float InUsedTimeBudgetMS, int32& InUsedComponentsBudget, int32 TimeEpoch);`
- L133 _private prototype_ `FFastGeoAsyncRenderStateJobQueue* GetOrCreateJobQueue();`
- L134 _private prototype_ `void WaitForAllPendingWorkCompletion();`
- L135 _private prototype_ `void PushRuntimeContainerForRegistration(UFastGeoContainer* FastGeo);`
- L136 _private prototype_ `void PushRuntimeContainerForDestruction(UFastGeoContainer* FastGeo);`
- L137 _private prototype_ `void DrainPendingRuntimeContainers();`
- L139 _private prototype_ `void RegisterContainerWithPSODeferredWork(UFastGeoContainer* FastGeo);`
- L140 _private prototype_ `void UnregisterContainerWithPSODeferredWork(UFastGeoContainer* FastGeo);`
- L141 _private prototype_ `void RegisterContainerWithAsyncPSORecreateWork(UFastGeoContainer* FastGeo);`
- L142 _private prototype_ `void UnregisterContainerWithAsyncPSORecreateWork(UFastGeoContainer* FastGeo);`
- L146 _private member_ `TSet<TObjectPtr<UFastGeoContainer>> PendingRuntimeRegisterContainers;` — `UPROPERTY()`
- L149 _private member_ `TSet<TObjectPtr<UFastGeoContainer>> PendingRuntimeDestroyContainers;` — `UPROPERTY()`
- L151 _private member_ `FDelegateHandle Handle_OnLevelStreamingStateChanged;`
- L152 _private member_ `FDelegateHandle Handle_OnLevelBeginAddToWorld;`
- L153 _private member_ `FDelegateHandle Handle_OnLevelBeginRemoveFromWorld;`
- L154 _private member_ `FDelegateHandle Handle_OnForEachHLODObjectInCell;`
- L177 _private member_ `} PendingRecreateManager;`
- L183 _private member_ `TSet<TWeakObjectPtr<UFastGeoContainer>> ContainersWithPSODeferredWork;` — Containers with PSO-deferred components waiting for PSO callbacks. Polled each Tick() to detect lost callbacks (component destroyed, world torn down, etc.) and unblock registration that would otherwise hang forever.
- L188 _private member_ `TSet<TWeakObjectPtr<UFastGeoContainer>> ContainersWithAsyncPSORecreateWork;` — Containers with pending PSO recreate work (UseFallbackMaterialUntilPSOPrecached). Tracked so Tick() can drive ProcessAsyncRenderStateJobs for recreate jobs that were pushed after OnAddLevelToWorldExtension completed. See Tick() comment for details.
- L191 _private member_ `static bool bEnableDebugView;`
- L193 _private member_ `FRWLock Lock;`
- L194 _private member_ `int32 TimeEpoch = 0;`
- L195 _private member_ `float UsedAsyncRenderStateTasksTimeBudgetMS = 0;`
- L196 _private member_ `int32 UsedNumComponentsToProcessBudget = 0;`
- L200 _private member_ `std::atomic<bool> bWaitingForCompletion{ false };` — Stamped on GT when entering a blocking wait window (level add/remove with bWaitForCompletion, global reregister, full drain). Read from worker threads via IsWaitingForCompletion() to make PSO-skip decisions during proxy creation.
- L201 _private member_ `bool bIsReregistering = false;`
- L203 _private member_ `TUniquePtr<FFastGeoAsyncRenderStateJobQueue> AsyncRenderStateJobQueue;`
- L204 _private member_ `TArray<TWeakObjectPtr<UFastGeoContainer>> ReregisteringFastGeoContainers;`

#### struct `UFastGeoWorldSubsystem::FFastGeoPendingRecreateManager`  
`struct FFastGeoPendingRecreateManager`  
_L160-177_
- desc: Manages components pending render state recreation (e.g., MarkRenderStateDirty from runtime property changes, decal fade, or PSO fallback material swap in sync mode). Non-PSO recreates are processed immediately (same frame guarantee). PSO recreates (NeedsPSORecreate) are time-sliced with a per-frame budget.
- L162 _public prototype_ `void Add(FFastGeoComponent* Component);`
- L163 _public prototype_ `void Process(UWorld* World);`
- L164 _public prototype_ `bool IsEmpty() const;`
- L165 _public prototype_ `void Reset();`
- L168 _public function_ `const TArray<FFastGeoRegisteredComponent>& GetComponents() const`
- L172 _private member_ `TArray<FFastGeoRegisteredComponent> Components;`
- L174 _private member_ `TFastGeoRenderStateBatch<FFastGeoRegisteredComponent> PSORecreateBatch;`
- L176 _private member_ `bool bHasNonPSORecreate = false;`

#### Free symbols / members of external scopes

- L100 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnComponentsPreRecreate, const TArray<FFastGeoRegisteredComponent>&);`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Internal/IFastGeoElement.h` (Internal)


#### class `IFastGeoElement`  
`class IFastGeoElement`  
_L7-56_
- L11 _public function_ `IFastGeoElement(FFastGeoElementType InType) : ElementType(InType)` — Default constructor
- L12 _public prototype_ `virtual ~IFastGeoElement() = default;`
- L16 _public function_ `template <typename T> T* CastTo()` — Attempt to cast this element to another type if it is of that type. Returns nullptr if it fails
- L22 _public function_ `template <typename T> const T* CastTo() const` — Attempt to cast this element to another type if it is of that type. Returns nullptr if it fails
- L28 _public function_ `template <typename T> T& CastToRef()` — Cast this element to another type and return a reference. Will assert if the cast fails.
- L35 _public function_ `template <typename T> const T& CastToRef() const` — Cast this element to another type and return a reference. Will assert if the cast fails.
- L42 _public function_ `template <typename T> bool IsA() const` — Returns true if this element is of the specified type
- L48 _public function_ `uint32 GetTypeID()` — Returns the element type unique ID
- L52 _protected member_ `static const FFastGeoElementType Type;` — Static type identifier for the base class
- L55 _protected member_ `FFastGeoElementType ElementType;` — Element type identifier

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Private/FastGeoLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFastGeoStreaming, Log, All);`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Public/FastGeoStreamingModule.h` (Public)


#### class `FFastGeoStreamingModule`  
`class FFastGeoStreamingModule : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- L14 _public prototype_ `static FFastGeoStreamingModule& Get();`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public prototype_ `static bool IsFastGeoEnabled();`
- L21 _public prototype_ `static bool IsAsyncRenderWorkAllowed();`
- L24 _private prototype_ `void OnWorldPreSendAllEndOfFrameUpdates(UWorld* InWorld);`
- L27 _private member_ `FDelegateHandle Handle_OnWorldPreSendAllEndOfFrameUpdates;`
- L29 _private member_ `static bool bIsFastGeoEnabled;`
- L30 _private member_ `static FAutoConsoleVariableRef CVarIsEnabled;`
- L33 _private member_ `static bool bAllowAsyncRenderWork;`
- L34 _private member_ `static FAutoConsoleVariableRef CVarAllowAsyncRenderWork;`

### `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Public/FastGeoWorldPartitionRuntimeCellTransformer.h` (Public)


#### enum `EFastGeoTransform`  
`enum class EFastGeoTransform : uint32`  
_L15-21_
- L17 _public enumerator_ `Allow` — Actor or component can be transformed.
- L18 _public enumerator_ `Reject` — Actor or component can't be transformed.
- L19 _public enumerator_ `Discard` — Actor or component is not relevant and can be fully discarded without impact on the game.
- L20 _public enumerator_ `MAX`

#### struct `FFastGeoTransformResult`  
`struct FFastGeoTransformResult`  
_L29-44_
- desc: Stores the transformation result and optionally collects the failure reason for debug reports.
- L32 _public prototype_ `FFastGeoTransformResult(EFastGeoTransform InTransformResult, const TCHAR* FailureReason = nullptr);`
- L33 _public prototype_ `FFastGeoTransformResult(EFastGeoTransform InTransformResult, TFunctionRef<FString()> FailureReasonFunc);`
- L35 _public function_ `EFastGeoTransform GetResult() const`
- L36 _public function_ `uint32 GetResultIndex() const`
- L37 _public function_ `const FString& GetReason() const`
- L39 _public member_ `static bool bShouldCollectReasons;`
- L42 _private member_ `EFastGeoTransform TransformResult;`
- L43 _private member_ `FString Reason;`

#### enum `EFastGeoInstanceStorageMode`  
`enum class EFastGeoInstanceStorageMode : uint8`  
_L48-63_
- reflection: `UENUM()`
- desc: Defines the memory storage format for FastGeo instance transforms.
- L54 _public enumerator_ `Auto` — Automatically selects the storage format by checking if compression causes precision loss in position, rotation, or scale beyond the allowed thresholds.
- L58 _public enumerator_ `Compressed` — Forces using FTransform3f (recommended for most game levels to optimize memory footprint).
- L62 _public enumerator_ `Full` — Forces using FMatrix (Best for absolute accuracy when instances show jitter or scale artifacts).

#### struct `FFastGeoInstanceCompressionSettings`  
`struct FFastGeoInstanceCompressionSettings`  
_L69-85_
- reflection: `USTRUCT()`
- desc: Threshold values used when transforming InstanceStaticMeshComponent tranforms when FastGeo transformer InstanceStorageMode is set to EFastGeoInstanceStorageMode::Auto.
- L76 _public member_ `float PositionEpsilon = 5e-2f;` — `UPROPERTY(EditAnywhere, Category = "Instance Precision", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0", Step = "0.001"))` — Threshold for Position (cm)
- L80 _public member_ `float RotationEpsilon = 1e-4f;` — `UPROPERTY(EditAnywhere, Category = "Instance Precision", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "0.01", Step = "0.0001"))` — Threshold for Rotation
- L84 _public member_ `float ScaleEpsilon = 1e-4f;` — `UPROPERTY(EditAnywhere, Category = "Instance Precision", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "0.01", Step = "0.0001"))` — Threshold for Scale

#### struct `FFastGeoConversionButton`  
`struct FFastGeoConversionButton`  
_L89-92_
- reflection: `USTRUCT()`
- desc: Empty type used to present a Button in the property grid - not actual data

#### class `UFastGeoTransformerSettings`  
`class UFastGeoTransformerSettings : public UDataAsset`  
_L95-170_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories)`
- inherits: `UDataAsset`
- L101 _public prototype_ `virtual void PostLoad() override;`
- L106 _public member_ `TArray<TSubclassOf<AActor>> AllowedActorClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta= (AllowAbstract = "true"))` — Allowed actor classes (recursive) to convert to FastGeo
- L110 _public member_ `TArray<TSubclassOf<AActor>> AllowedExactActorClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (AllowAbstract = "true"))` — Allowed actor classes (exact) to convert to FastGeo
- L114 _public member_ `TArray<TSubclassOf<UActorComponent>> AllowedComponentClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (AllowAbstract = "true"))` — Allowed component classes (recursive) to convert to FastGeo
- L118 _public member_ `TArray<TSubclassOf<UActorComponent>> AllowedExactComponentClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (AllowAbstract = "true"))` — Allowed component classes (exact) to convert to FastGeo
- L122 _public member_ `TArray<TSubclassOf<AActor>> DisallowedActorClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (AllowAbstract = "true"))` — Disallowed actor classes (recursive) to convert to FastGeo
- L126 _public member_ `TArray<TSubclassOf<AActor>> DisallowedExactActorClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (AllowAbstract = "true"))` — Disallowed actor classes (exact) to convert to FastGeo
- L130 _public member_ `TArray<TSubclassOf<UActorComponent>> DisallowedComponentClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (AllowAbstract = "true"))` — Disallowed component classes (recursive) to convert to FastGeo
- L134 _public member_ `TArray<TSubclassOf<UActorComponent>> DisallowedExactComponentClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (AllowAbstract = "true"))` — Disallowed component classes (exact) to convert to FastGeo
- L138 _public member_ `TArray<TSubclassOf<UActorComponent>> DisallowedActorsContainingComponentClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (AllowAbstract = "true"))` — Disallow any actor that contains a component of these classes (recursive)
- L142 _public member_ `TArray<TSubclassOf<UActorComponent>> DisallowedActorsContainingExactComponentClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (AllowAbstract = "true"))` — Disallow any actor that contains a component of these exact classes
- L146 _public member_ `TArray<TSubclassOf<UActorComponent>> IgnoredRemainingComponentClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (AllowAbstract = "true"))` — Component classes (recursive) to ignore when deciding to destroy a converted actor to FastGeo
- L150 _public member_ `TArray<TSubclassOf<UActorComponent>> IgnoredRemainingExactComponentClasses;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (AllowAbstract = "true"))` — Component classes (exact) to ignore when deciding to destroy a converted actor to FastGeo
- L159 _public member_ `bool bGenerateSurrogateComponents = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Whether the transformer should generate a surrogate actor and surrogate components which will be linked to the physics body instances when initialized. When hitting FastGeo content, a surrogate component will be available in the HitResult & OverlapResult. HitResult.Item & OverlapResult.ItemIndex will map to the actual FastGeo component body instance index.
- L163 _public member_ `EFastGeoInstanceStorageMode InstanceStorageMode = EFastGeoInstanceStorageMode::Auto;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Determines how instance transforms are stored in memory
- L166 _public member_ `FFastGeoInstanceCompressionSettings InstanceCompressionSettings;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "InstanceStorageMode == EFastGeoInstanceStorageMode::Auto", EditConditionHides))`
- L169 _public member_ `FFastGeoConversionButton FastGeoConversionButton;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (DisplayName = "Convert settings to reusable Asset"))`

#### class `UFastGeoWorldPartitionRuntimeCellTransformer`  
`class UFastGeoWorldPartitionRuntimeCellTransformer : public UWorldPartitionRuntimeCellTransformer`  
_L173-340_
- reflection: `UCLASS(Config = FastGeoStreaming, DefaultConfig)`
- inherits: `UWorldPartitionRuntimeCellTransformer`
- L179 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L185 _public prototype_ `virtual void Transform(ULevel* InLevel) override final;`
- L186 _public prototype_ `virtual void ForEachIgnoredComponentClass(TFunctionRef<bool(const TSubclassOf<UActorComponent>&)> Func) const override final;`
- L187 _public prototype_ `virtual void ForEachIgnoredExactComponentClass(TFunctionRef<bool(const TSubclassOf<UActorComponent>&)> Func) const override final;`
- L191 _public prototype_ `virtual void BeginDestroy() override;`
- L192 _public prototype_ `virtual void PreEditChange(FProperty* InPropertyAboutToChange) override;`
- L193 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L197 _public function_ `static const UFastGeoWorldPartitionRuntimeCellTransformer* GetCurrentTransformer()` — Used internally to get transformer settings.
- L201 _protected function_ `virtual bool IsActorTransformable(AActor* InActor, FString& OutReason) const` — Whether the actor can be processed by the transformer.
- L203 _protected function_ `virtual bool IsComponentTransformable(UActorComponent* InComponent, FString& OutReason) const` — Whether the component can be processed by the transformer.
- L205 _protected function_ `virtual bool IsFullyTransformedActorDeletable(AActor* InActor, FString& OutReason) const` — Whether the fully transformed actor can be deleted by the transformer.
- L207 _protected prototype_ `bool IsComponentMobilitySupported(USceneComponent* InComponent, FString& OutReason) const;` — Whether component mobility is supported by the transformer.
- L242 _protected prototype_ `FFastGeoTransformResult CanTransformActor(AActor* InActor, bool& bOutIsActorFullyTransformable, TArray<UActorComponent*>& OutTransformableComponents, TArray<FComponentReport>* OutComponentReports = nullptr) const;`
- L243 _protected prototype_ `FFastGeoTransformResult IsAllowedActorClass(AActor* InActor) const;`
- L244 _protected prototype_ `FFastGeoTransformResult CanTransformComponent(UActorComponent* InComponent) const;`
- L245 _protected prototype_ `FFastGeoTransformResult IsAllowedComponentClass(UActorComponent* InComponent) const;`
- L246 _protected prototype_ `bool CanRemoveActor(AActor* InActor, TSet<UActorComponent*>& InIgnoredComponents) const;`
- L247 _protected prototype_ `bool CanAlwaysIgnoreActor(AActor* InActor) const;`
- L248 _protected prototype_ `void OnSelectionChanged(UObject* Object);`
- L249 _protected prototype_ `bool IsDebugMode() const;`
- L251 _protected prototype_ `TMap<AActor*, TArray<AActor*>> BuildActorsReferencesMap(const TArray<AActor*>& InActors);`
- L252 _protected prototype_ `void GatherTransformableActors(const TArray<AActor*>& InActors, const ULevel* InLevel, TArray<TPair<AActor*, FTransformableActor>>& OutTransformableActors, FTransformationStats& OutStats, TArray<FActorReport>* OutReports = nullptr);`
- L253 _protected prototype_ `static void DumpDebugReport(const TCHAR* Title, const TArray<AActor*>& IgnoredActors, const TArray<FActorReport>& ActorReports, const FTransformationStats& Stats);`
- L259 _public member_ `TObjectPtr<UFastGeoTransformerSettings> Settings = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L261 _public function_ `const UFastGeoTransformerSettings& GetSettings() const`
- L271 _protected member_ `TObjectPtr<UFastGeoTransformerSettings> EmbeddedSettings;` — `UPROPERTY(EditAnywhere, Instanced, NoClear, Meta = (EditCondition = "Settings == nullptr", Tooltip = "Fallback only available when no Settings asset is used."), Category = "Settings")`
- L274 _protected member_ `bool bDebugMode;` — `UPROPERTY(EditAnywhere, Transient, SkipSerialization, Category = "Debug")`
- L277 _protected member_ `bool bDebugSelectionMode;` — `UPROPERTY(EditAnywhere, Transient, SkipSerialization, Category = "Debug")`
- L281 _protected member_ `TArray<TSubclassOf<AActor>> AllowedActorClasses_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))` — The following properties are all deprecated in favor of the separate Settings property pointing to a reusable settings asset
- L284 _protected member_ `TArray<TSubclassOf<AActor>> AllowedExactActorClasses_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L287 _protected member_ `TArray<TSubclassOf<UActorComponent>> AllowedComponentClasses_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L290 _protected member_ `TArray<TSubclassOf<UActorComponent>> AllowedExactComponentClasses_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L293 _protected member_ `TArray<TSubclassOf<AActor>> DisallowedActorClasses_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L296 _protected member_ `TArray<TSubclassOf<AActor>> DisallowedExactActorClasses_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L299 _protected member_ `TArray<TSubclassOf<UActorComponent>> DisallowedComponentClasses_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L302 _protected member_ `TArray<TSubclassOf<UActorComponent>> DisallowedExactComponentClasses_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L305 _protected member_ `TArray<TSubclassOf<UActorComponent>> IgnoredRemainingComponentClasses_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L308 _protected member_ `TArray<TSubclassOf<UActorComponent>> IgnoredRemainingExactComponentClasses_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L312 _protected member_ `static bool IsDebugModeEnabled;`
- L313 _protected member_ `static bool IsFastGeoTransformerEnabled;`
- L314 _protected member_ `static FAutoConsoleVariableRef CVarIsDebugModeEnabled;`
- L315 _protected member_ `static FAutoConsoleVariableRef CVarIsFastGeoTransformerEnabled;`
- L320 _protected member_ `TArray<TSubclassOf<AActor>> BuiltinAllowedActorClasses;` — `UPROPERTY(Config)`
- L323 _protected member_ `TArray<TSubclassOf<AActor>> BuiltinDisallowedActorClasses;` — `UPROPERTY(Config)`
- L326 _protected member_ `TArray<TSubclassOf<UActorComponent>> BuiltinAllowedComponentClasses;` — `UPROPERTY(Config)`
- L329 _protected member_ `TArray<TSubclassOf<UActorComponent>> BuiltinDisallowedComponentClasses;` — `UPROPERTY(Config)`
- L332 _protected member_ `TArray<TSubclassOf<UActorComponent>> BuiltinIgnoredRemainingComponentClasses;` — `UPROPERTY(Config)`
- L335 _protected member_ `TArray<TSubclassOf<UActorComponent>> BuiltinIgnoredRemainingExactComponentClasses;` — `UPROPERTY(Config)`
- L339 _private member_ `static UFastGeoWorldPartitionRuntimeCellTransformer* CurrentTransformer;`

#### struct `UFastGeoWorldPartitionRuntimeCellTransformer::FTransformableActor`  
`struct FTransformableActor`  
_L209-214_
- L211 _public member_ `int32 ActorIndex = INDEX_NONE;`
- L212 _public member_ `bool bIsActorFullyTransformable = false;`
- L213 _public member_ `TArray<UActorComponent*> TransformableComponents;`

#### struct `UFastGeoWorldPartitionRuntimeCellTransformer::FTransformationStats`  
`struct FTransformationStats`  
_L216-225_
- L218 _public member_ `int32 TotalActorCount = 0;`
- L219 _public member_ `int32 TotalComponentCount = 0;`
- L220 _public member_ `int32 FullyTransformableActorCount = 0;`
- L221 _public member_ `int32 PartiallyTransformableActorCount = 0;`
- L222 _public member_ `int32 TransformedComponentCount = 0;`
- L224 _public prototype_ `void DumpStats(const TCHAR* InPrefixString) const;`

#### struct `UFastGeoWorldPartitionRuntimeCellTransformer::FComponentReport`  
`struct FComponentReport`  
_L227-232_
- L229 _public member_ `UActorComponent* Component = nullptr;`
- L230 _public member_ `EFastGeoTransform Result = EFastGeoTransform::Allow;`
- L231 _public member_ `FString Reason;`

#### struct `UFastGeoWorldPartitionRuntimeCellTransformer::FActorReport`  
`struct FActorReport`  
_L234-240_
- L236 _public member_ `AActor* Actor = nullptr;`
- L237 _public member_ `EFastGeoTransform Result = EFastGeoTransform::Allow;`
- L238 _public member_ `FString Reason;`
- L239 _public member_ `TArray<FComponentReport> ComponentReports;`

#### Free symbols / members of external scopes

- L23 _function_ `inline constexpr uint32 EnumToIndex(EFastGeoTransform Value)`
