# Plugins / ChaosCaching

- module root: `Plugins/Experimental/ChaosCaching/Source/ChaosCaching`
- headers: 14; symbols: 520
- symbol kinds: class=14, delegate=3, enum=5, enumerator=12, function=74, member=177, namespace=8, prototype=195, struct=27, typedef=5
- PublicDependencyModuleNames: ChaosSolverEngine, Core, CoreUObject, Engine, EngineSettings, GeometryCollectionEngine, LevelSequence, MovieScene, MovieSceneTracks, RHI, RenderCore, Slate, SlateCore, UnrealEd

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Private/Chaos/Sequencer/MovieSceneChaosCacheTemplate.h` (Private)


#### struct `FMovieSceneChaosCacheSectionTemplateParameters`  
`struct FMovieSceneChaosCacheSectionTemplateParameters : public FMovieSceneBaseCacheSectionTemplateParameters`  
_L11-24_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneBaseCacheSectionTemplateParameters`
- L15 _public function_ `FMovieSceneChaosCacheSectionTemplateParameters()`
- L17 _public function_ `FMovieSceneChaosCacheSectionTemplateParameters(const FMovieSceneChaosCacheParams& InChaosCacheParams, FFrameNumber InSectionStartTime, FFrameNumber InSectionEndTime) : FMovieSceneBaseCacheSectionTemplateParameters(InSectionStartTime, InSectionEndTime), ChaosCacheParams(InChaosCacheParams)`
- L23 _public member_ `FMovieSceneChaosCacheParams ChaosCacheParams;` — `UPROPERTY()`

#### struct `FMovieSceneChaosCacheSectionTemplate`  
`struct FMovieSceneChaosCacheSectionTemplate : public FMovieSceneEvalTemplate`  
_L27-39_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- L31 _public function_ `FMovieSceneChaosCacheSectionTemplate()`
- L32 _public prototype_ `FMovieSceneChaosCacheSectionTemplate(const UMovieSceneChaosCacheSection& Section);`
- L34 _public function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L35 _public prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L38 _public member_ `FMovieSceneChaosCacheSectionTemplateParameters Params;` — `UPROPERTY()`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/Adapters/CacheAdapter.h` (Public)


#### struct `Chaos::FAdapterUtil`  
`struct FAdapterUtil`  
_L26-29_
- L28 _public prototype_ `static FComponentCacheAdapter* GetBestAdapterForClass(TSubclassOf<UPrimitiveComponent> InComponentClass, bool bAllowDerived = true);`

#### class `Chaos::FComponentCacheAdapter`  
`class FComponentCacheAdapter : public IModularFeature`  
_L38-227_
- inherits: `IModularFeature`
- desc: Base adapter type for interfacing with Chaos simulation caches. Any component wishing to use caches must have a compatible record adapter and a playback adapter to produce and consume cache data. This base interface should not be used to implement those adapters however but the derived classes FCacheRecordAdapter and FCachePlaybackAdapter (declared below) should instead be used.
- L49 _public member_ `static const FName FeatureName;` — Registration name for modular features module
- L50 _public member_ `static const uint8 EngineAdapterPriorityBegin;`
- L51 _public member_ `static const uint8 UserAdapterPriorityBegin;`
- L53 _public prototype_ `FComponentCacheAdapter() = default;`
- L54 _public prototype_ `virtual ~FComponentCacheAdapter() = default;`
- L74 _public prototype_ `virtual SupportType SupportsComponentClass(UClass* InComponentClass) const = 0;` — Query whether InComponentClass can be driven by this adapter. If a class implementing this interface says it can support a component it *may* be chosen as the driving adapter for that component and will be expeted to be able to handle Pull/Push operations if it is chosen. If the adapter returns SupportType::Derived and another adapter returns SupportType::Direct then the adapter that can directly drive the class is chosen to drive the cache. If multiple adapters return SupportType::Direct then the first is chosen. If multiple adapters return SupportType::Derived then the adapter with the closest desired class will be chosen (closest in terms of inheritance hierarchy between the desired direct class and the provided class) If the adapter can only handle one specific type then only using SupportType::Direct and SupportType::None will make sure it only receives calls from the cache if exactly that component class is selected @param InComponent - the component class to test @return the type of support this adapter can give for the specified class
- L93 _public prototype_ `virtual UClass* GetDesiredClass() const = 0;` — Query the class that this adapter wants to drive. This will be used to work out the most likely candidate for an adapter when multiple adapters return SupportType::Derived. For example in the following hierarchy: UPrimitiveComponent | UDerivedComponentA | UDerivedComponentB An adapter directly supporing UDerivedComponentA that returns SupportType::Derived for a class of UDerivedComponentB will be picked over an adapter that directly supports UPrimitiveComponent and returns SupportType::Derived for a class of UDerivedComponentB Note: All classes returned from this MUST have UPrimitiveComponent in their hierarchy as that is the base physically-capable component
- L104 _public prototype_ `virtual uint8 GetPriority() const = 0;` — Gets the priority for an adapter. When two or more adapters give the same support level for a given component class this priority will be used to decide which adapter will be used. All base engine level adapters per type will use a priority between EngineAdapterPriorityBegin and UserAdapterPriorityBegin defined in this interface. Users implementing adapters intended to override all engine functionality should return priorities above UserAdapterPriorityBegin to ensure they will always be selected above engine adapters.
- L112 _public prototype_ `virtual Chaos::FPhysicsSolver* GetComponentSolver(UPrimitiveComponent* InComponent) const = 0;` — Called to retrieve the rigid solver for a specific component if it exists. Required until a more generic method of solver binding for components is devised. #BGTODO Remove when multiple solver concept moved into primitive component @param InComponent Component to resolve the solver for
- L119 _public function_ `virtual Chaos::FPhysicsSolverEvents* BuildEventsSolver(UPrimitiveComponent* InComponent) const` — Called to retrieve the base events solver for a specific component. If the component is requiring it the solver could be rebuilt. @param InComponent Component to resolve the solver for
- L124 _public function_ `virtual void Initialize()` — Called from the game thread to perform any global setup that the adapter may need to perform.
- L129 _public function_ `virtual void Finalize()` — Called from the game thread to perform any final steps before deallocation.
- L134 _public prototype_ `virtual void SetRestState(UPrimitiveComponent* InComponent, UChaosCache* InCache, const FTransform& InRootTransform, Chaos::FReal InTime) const = 0;` — Called from the game thread to set rest state from an evaluated time in the cache.
- L139 _public function_ `virtual void EmitEvents(UPrimitiveComponent* InComponent, UChaosCache* InCache, FPlaybackTickRecord& TickRecord) const` — Called from the game thread to emit events
- L144 _public function_ `virtual void InitializeForLoad(UPrimitiveComponent* InComponent, FObservedComponent& InObserved)` — Called from the game thread to initialize a component and cache ready to load a cache at a given frame
- L151 _public function_ `virtual bool InitializeForRecord(UPrimitiveComponent* InComponent, UChaosCache* InCache)` — Called from the game thread to initialize a component and cache ready to record a cache @param InComponent Target component to initialize @param InCache Target cache to initialize
- L152 _public prototype_ `virtual bool InitializeForRecord(UPrimitiveComponent* InComponent, FObservedComponent& InObserved);`
- L160 _public function_ `virtual bool InitializeForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache, float InTime)` — Called from the game thread to initialize a component and cache ready to playback a cache @param InComponent Target component to initialize @param InCache Target cache to initialize @param InTime Time from cache start to evaluate initial conditions
- L161 _public prototype_ `virtual bool InitializeForPlayback(UPrimitiveComponent* InComponent, FObservedComponent& InObserved, float InTime);`
- L166 _public function_ `virtual void FinalizeComponent(UPrimitiveComponent* InComponent, UChaosCache* InCache)` — Called from the game thread to finalize for a specific component
- L173 _public prototype_ `virtual void Record_PostSolve(UPrimitiveComponent* InComp, const FTransform& InRootTransform, FPendingFrameWrite& OutFrame, Chaos::FReal InTime) const = 0;` — Called by a cache observer when a component should be recorded to a cache through this adapter. The time provided is the absolute time from the beginning of the cache recording that the adapter is expected to record to. Almost always recording should be done from Record_PostSolve
- L180 _public prototype_ `virtual void Playback_PreSolve(UPrimitiveComponent* InComponent, UChaosCache* InCache, Chaos::FReal InTime, FPlaybackTickRecord& TickRecord, TArray<TPBDRigidParticleHandle<Chaos::FReal, 3>*>& OutUpdatedRigids) const = 0;` — Called by a cache observer actor when a cache needs to be applied to a component through this adapter. The time provided is the absolute time from the beginning of the cache playback that the adapter is expected to apply to the supplied component. Note this is called on the physics thread.
- L194 _public prototype_ `virtual FGuid GetGuid() const = 0;` — Gets a unique identifier for the adapter This must return a stable GUID that uniquely identifies any derived classes. This GUID is embedded into any cache that an adapter writes to so it can be matched up on replay. Changing the GUID returned will permanently invalidate any caches that were recorded with this adapter and they will no longer be able to playback
- L203 _public prototype_ `virtual bool ValidForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache) const = 0;` — Determines whether a cache is able to safely playback on a component. After the GUID for an adapter is validated this check will be called from the game thread to ensure an adapter is able to safely play back for the provided component. @param InComponent Target component attempting playback. @param InCache Requested cache to playback.
- L208 _public function_ `virtual bool SupportsPlayWhileRecording() const` — if the cache adapter supports playback when recording
- L209 _public function_ `virtual bool SupportsRestartSimulation() const`
- L210 _public function_ `void SetRestartSimulation(bool InbRestartSimulation)`
- L211 _public function_ `void SetRestartTimeRange(float InRestartTimeStart, float InRestartTimeEnd)`
- L219 _public function_ `virtual void WaitForSolverTasks(UPrimitiveComponent* InComponent) const` — Stall on any solver tasks that could broadcast events via the EventsSolver. Called from game thread. This is necessary so that the cache manager can teardown and setup new event handling.
- L222 _protected member_ `bool bRestartSimulation = false;`
- L223 _protected member_ `float RestartTimeStart = TNumericLimits<float>::Max();` — if bRestartSimulation, use RestartTimeStart as an offset when saving, and clear cache data in [RestartTimeStart, RestartTimeEnd]
- L224 _protected member_ `float RestartTimeEnd = -TNumericLimits<float>::Max();`

#### enum `Chaos::FComponentCacheAdapter::SupportType`  
`enum class SupportType : uint8`  
_L41-46_
- L43 _public enumerator_ `None`
- L44 _public enumerator_ `Direct`
- L45 _public enumerator_ `Derived`

#### struct `Chaos::TAutoRegisterCacheAdapter`  
`template<typename AdapterType> struct TAutoRegisterCacheAdapter`  
_L234-250_
- desc: Helper to handle automatic global registration for adapter types - with type checking for valid adapter types
- L238 _public function_ `TAutoRegisterCacheAdapter()`
- L243 _public function_ `~TAutoRegisterCacheAdapter()`
- L249 _private member_ `AdapterType Adapter;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCacheAdapter, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCacheAdapter, Log, All);`
- L23 _namespace_ `namespace Chaos`
- L229 _prototype_ `void RegisterAdapter(FComponentCacheAdapter* InAdapter);` (scope `Chaos`)
- L230 _prototype_ `void UnregisterAdapter(FComponentCacheAdapter* InAdapter);` (scope `Chaos`)

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/Adapters/GeometryCollectionComponentCacheAdapter.h` (Public)


#### struct `FEnableStateEvent`  
`struct FEnableStateEvent : public FCacheEventBase`  
_L12-35_
- reflection: `USTRUCT()`
- inherits: `FCacheEventBase`
- L16 _public member_ `static FName EventName;`
- L18 _public function_ `FEnableStateEvent() : Index(INDEX_NONE) , bEnable(false)`
- L24 _public function_ `FEnableStateEvent(int32 InIndex, bool bInEnable) : Index(InIndex) , bEnable(bInEnable)`
- L31 _public member_ `int32 Index;` — `UPROPERTY()`
- L34 _public member_ `bool bEnable;` — `UPROPERTY()`

#### struct `FBreakingEvent`  
`struct FBreakingEvent : public FCacheEventBase`  
_L38-93_
- reflection: `USTRUCT()`
- inherits: `FCacheEventBase`
- L42 _public member_ `static FName EventName;`
- L44 _public function_ `FBreakingEvent() : Index(INDEX_NONE) , Location(0.0f, 0.0f, 0.0f) , Orientation(FQuat::Identity) , Velocity(0.0f, 0.0f, 0.0f) , AngularVelocity(0.0f, 0.0f, 0.0f) , Mass(1.0f) , BoundingBoxMin(0.0f, 0.0f, 0.0f) , BoundingBoxMax(0.0f, 0.0f, 0.0f)`
- L55 _public function_ `FBreakingEvent(int32 InIndex, const Chaos::FBreakingData& InData, const FTransform& WorldToComponent) : Index(InIndex) , Location(WorldToComponent.TransformPosition(InData.Location)) , Orientation(WorldToComponent.TransformRotation(InData.Orientation)) , Velocity(WorldToComponent.TransformVector(InData.Velocity)) , AngularVelocity(InData.AngularVelocity) , Mass(InData.Mass) , BoundingBoxMin(InData.BoundingBox.Min()) , BoundingBoxMax(InData.BoundingBox.Max())`
- L71 _public member_ `int32 Index;` — `UPROPERTY()`
- L74 _public member_ `FVector Location;` — `UPROPERTY()`
- L77 _public member_ `FQuat Orientation;` — `UPROPERTY()`
- L80 _public member_ `FVector Velocity;` — `UPROPERTY()`
- L83 _public member_ `FVector AngularVelocity;` — `UPROPERTY()`
- L86 _public member_ `float Mass;` — `UPROPERTY()`
- L89 _public member_ `FVector BoundingBoxMin;` — `UPROPERTY()`
- L92 _public member_ `FVector BoundingBoxMax;` — `UPROPERTY()`

#### struct `FCollisionEvent`  
`struct FCollisionEvent : public FCacheEventBase`  
_L96-167_
- reflection: `USTRUCT()`
- inherits: `FCacheEventBase`
- L100 _public member_ `static FName EventName;`
- L102 _public function_ `FCollisionEvent() : Location(0.0f, 0.0f, 0.0f) , AccumulatedImpulse(0.0f, 0.0f, 0.0f) , Normal(0.0f, 0.0f, 1.0f) , Velocity1(0.0f, 0.0f, 0.0f) , Velocity2(0.0f, 0.0f, 0.0f) , DeltaVelocity1(0.0f, 0.0f, 0.0f) , DeltaVelocity2(0.0f, 0.0f, 0.0f) , AngularVelocity1(0.0f, 0.0f, 0.0f) , AngularVelocity2(0.0f, 0.0f, 0.0f) , Mass1(1.0f) , Mass2(1.0f) , PenetrationDepth(0.0f)`
- L117 _public function_ `FCollisionEvent(const Chaos::FCollidingData& InData, const FTransform& WorldToComponent) : Location(WorldToComponent.TransformPosition(InData.Location)) , AccumulatedImpulse(WorldToComponent.TransformVector(InData.AccumulatedImpulse)) , Normal(WorldToComponent.TransformVector(InData.Normal)) , Velocity1(WorldToComponent.TransformVector(InData.Velocity1)) , Velocity2(WorldToComponent.TransformVector(InData.Velocity2)) , DeltaVelocity1(WorldToComponent.TransformVector(InData.DeltaVelocity1)) , DeltaVelocity2(WorldToComponent.TransformVector(InData.DeltaVelocity2)) , AngularVelocity1(InData.AngularVelocity1) , AngularVelocity2(InData.AngularVelocity2) , Mass1(InData.Mass1) , Mass2(InData.Mass2) , PenetrationDepth(InData.PenetrationDepth)`
- L133 _public member_ `FVector Location;` — `UPROPERTY()`
- L136 _public member_ `FVector AccumulatedImpulse;` — `UPROPERTY()`
- L139 _public member_ `FVector Normal;` — `UPROPERTY()`
- L142 _public member_ `FVector Velocity1;` — `UPROPERTY()`
- L145 _public member_ `FVector Velocity2;` — `UPROPERTY()`
- L148 _public member_ `FVector DeltaVelocity1;` — `UPROPERTY()`
- L151 _public member_ `FVector DeltaVelocity2;` — `UPROPERTY()`
- L154 _public member_ `FVector AngularVelocity1;` — `UPROPERTY()`
- L157 _public member_ `FVector AngularVelocity2;` — `UPROPERTY()`
- L160 _public member_ `float Mass1;` — `UPROPERTY()`
- L163 _public member_ `float Mass2;` — `UPROPERTY()`
- L166 _public member_ `float PenetrationDepth;` — `UPROPERTY()`

#### struct `FTrailingEvent`  
`struct FTrailingEvent : public FCacheEventBase`  
_L170-220_
- reflection: `USTRUCT()`
- inherits: `FCacheEventBase`
- L174 _public member_ `static FName EventName;`
- L176 _public function_ `FTrailingEvent() : Index(INDEX_NONE) , Location(0.0f, 0.0f, 0.0f) , Orientation(FQuat::Identity) , Velocity(0.0f, 0.0f, 0.0f) , AngularVelocity(0.0f, 0.0f, 0.0f) , BoundingBoxMin(0.0f, 0.0f, 0.0f) , BoundingBoxMax(0.0f, 0.0f, 0.0f)`
- L186 _public function_ `FTrailingEvent(int32 InIndex, const Chaos::FTrailingData& InData, const FTransform& WorldToComponent) : Index(InIndex) , Location(WorldToComponent.TransformPosition(InData.Location)) , Orientation(WorldToComponent.TransformRotation(InData.Orientation)) , Velocity(WorldToComponent.TransformVector(InData.Velocity)) , AngularVelocity(InData.AngularVelocity) , BoundingBoxMin(InData.BoundingBox.Min()) , BoundingBoxMax(InData.BoundingBox.Max())`
- L201 _public member_ `int32 Index;` — `UPROPERTY()`
- L204 _public member_ `FVector Location;` — `UPROPERTY()`
- L207 _public member_ `FQuat Orientation;` — `UPROPERTY()`
- L210 _public member_ `FVector Velocity;` — `UPROPERTY()`
- L213 _public member_ `FVector AngularVelocity;` — `UPROPERTY()`
- L216 _public member_ `FVector BoundingBoxMin;` — `UPROPERTY()`
- L219 _public member_ `FVector BoundingBoxMax;` — `UPROPERTY()`

#### struct `Chaos::FCachedEventData`  
`struct FCachedEventData`  
_L232-243_
- L234 _public function_ `FCachedEventData() : ProxyBreakingDataIndices(nullptr) , ProxyCollisionDataIndices(nullptr) , ProxyTrailingDataIndices(nullptr)`
- L240 _public member_ `const TArray<int32>* ProxyBreakingDataIndices;`
- L241 _public member_ `const TArray<int32>* ProxyCollisionDataIndices;`
- L242 _public member_ `const TArray<int32>* ProxyTrailingDataIndices;`

#### class `Chaos::FGeometryCollectionCacheAdapter`  
`class FGeometryCollectionCacheAdapter : public FComponentCacheAdapter`  
_L245-301_
- inherits: `FComponentCacheAdapter`
- L249 _public prototype_ `virtual ~FGeometryCollectionCacheAdapter() = default;`
- L252 _public prototype_ `virtual SupportType SupportsComponentClass(UClass* InComponentClass) const override;` — FComponentCacheAdapter interface
- L253 _public prototype_ `virtual UClass* GetDesiredClass() const override;`
- L254 _public prototype_ `virtual uint8 GetPriority() const override;`
- L255 _public prototype_ `virtual FGuid GetGuid() const override;`
- L256 _public prototype_ `virtual Chaos::FPhysicsSolver* GetComponentSolver(UPrimitiveComponent* InComponent) const override;`
- L257 _public prototype_ `virtual Chaos::FPhysicsSolverEvents* BuildEventsSolver(UPrimitiveComponent* InComponent) const override;`
- L258 _public prototype_ `virtual bool ValidForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache) const override;`
- L259 _public prototype_ `virtual void SetRestState(UPrimitiveComponent* InComponent, UChaosCache* InCache, const FTransform& InRootTransform, Chaos::FReal InTime) const override;`
- L260 _public prototype_ `virtual void EmitEvents(UPrimitiveComponent* InComponent, UChaosCache* InCache, FPlaybackTickRecord& TickRecord) const override;`
- L261 _public prototype_ `virtual bool InitializeForRecord(UPrimitiveComponent* InComponent, UChaosCache* InCache) override;`
- L262 _public prototype_ `virtual bool InitializeForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache, float InTime) override;`
- L263 _public prototype_ `virtual void FinalizeComponent(UPrimitiveComponent* InComponent, UChaosCache* InCache) override;`
- L264 _public prototype_ `virtual void Record_PostSolve(UPrimitiveComponent* InComp, const FTransform& InRootTransform, FPendingFrameWrite& OutFrame, Chaos::FReal InTime) const override;`
- L265 _public prototype_ `virtual void Playback_PreSolve(UPrimitiveComponent* InComponent, UChaosCache* InCache, Chaos::FReal InTime, FPlaybackTickRecord& TickRecord, TArray<TPBDRigidParticleHandle<Chaos::FReal, 3>*>& OutUpdatedRigids) const override;`
- L275 _protected prototype_ `void RegisterEventHandler(FGeometryCollectionPhysicsProxy* Proxy);`
- L276 _protected prototype_ `void UnregisterEventHandler(FGeometryCollectionPhysicsProxy* Proxy);`
- L277 _protected prototype_ `void HandleBreakingEvents(const Chaos::FBreakingEventData& Event);`
- L278 _protected prototype_ `void HandleCollisionEvents(const Chaos::FCollisionEventData& Event);`
- L279 _protected prototype_ `void HandleTrailingEvents(const Chaos::FTrailingEventData& Event);`
- L281 _protected prototype_ `void EmitCollisionEvents_GameThread(UPrimitiveComponent& InComponent, const FCacheEvaluationResult& Results) const;`
- L282 _protected prototype_ `void EmitBreakingEvents_GameThread(UPrimitiveComponent& InComponent, const FCacheEvaluationResult& Results) const;`
- L286 _private prototype_ `TArray<int32> GatherAllBreaksUpToTime(UChaosCache* InCache, float InTime) const;`
- L292 _private typedef_ `using FSolverEventPair = TPair<Chaos::FPhysicsSolver*, Chaos::EEventType>;` — List of the solvers we are currently listening for events for recording we need to track them because each of them owns a seperate unique event manager
- L293 _private member_ `TSet<FSolverEventPair> SolversListenedToForEvents;`
- L295 _private member_ `TMap<IPhysicsProxyBase*, FCachedEventData> CachedData;`
- L296 _private member_ `const FBreakingDataArray* BreakingDataArray;`
- L297 _private member_ `const FCollisionDataArray* CollisionDataArray;`
- L298 _private member_ `const FTrailingDataArray* TrailingDataArray;`

#### Free symbols / members of external scopes

- L227 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/Adapters/StaticMeshComponentCacheAdapter.h` (Public)


#### class `Chaos::FStaticMeshCacheAdapter`  
`class FStaticMeshCacheAdapter : public FComponentCacheAdapter`  
_L10-32_
- inherits: `FComponentCacheAdapter`
- L13 _public prototype_ `virtual ~FStaticMeshCacheAdapter() = default;`
- L15 _public prototype_ `virtual SupportType SupportsComponentClass(UClass* InComponentClass) const override;`
- L16 _public prototype_ `virtual UClass* GetDesiredClass() const override;`
- L17 _public prototype_ `virtual uint8 GetPriority() const override;`
- L18 _public prototype_ `virtual FGuid GetGuid() const override;`
- L19 _public prototype_ `virtual bool ValidForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache) const override;`
- L20 _public prototype_ `virtual Chaos::FPhysicsSolver* GetComponentSolver(UPrimitiveComponent* InComponent) const override;`
- L21 _public prototype_ `virtual Chaos::FPhysicsSolverEvents* BuildEventsSolver(UPrimitiveComponent* InComponent) const override;`
- L22 _public prototype_ `virtual void SetRestState(UPrimitiveComponent* InComponent, UChaosCache* InCache, const FTransform& InRootTransform, Chaos::FReal InTime) const override;`
- L23 _public prototype_ `virtual bool InitializeForRecord(UPrimitiveComponent* InComponent, UChaosCache* InCache) override;`
- L24 _public prototype_ `virtual bool InitializeForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache, float InTime) override;`
- L25 _public prototype_ `virtual void Record_PostSolve(UPrimitiveComponent* InComp, const FTransform& InRootTransform, FPendingFrameWrite& OutFrame, Chaos::FReal InTime) const override;`
- L26 _public prototype_ `virtual void Playback_PreSolve(UPrimitiveComponent* InComponent, UChaosCache* InCache, Chaos::FReal InTime, FPlaybackTickRecord& TickRecord, TArray<TPBDRigidParticleHandle<Chaos::FReal, 3>*>& OutUpdatedRigids) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/CacheCollection.h` (Public)


#### class `UChaosCacheCollection`  
`class UChaosCacheCollection : public UObject`  
_L12-50_
- reflection: `UCLASS(Experimental, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- L18 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L20 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L22 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);`
- L26 _public prototype_ `UChaosCache* FindCache(const FName& CacheName) const;`
- L27 _public prototype_ `UChaosCache* FindOrAddCache(const FName& CacheName);`
- L29 _public prototype_ `void FlushAllCacheWrites();`
- L31 _public function_ `const TArray<UChaosCache*>& GetCaches() const`
- L34 _public prototype_ `float GetMaxDuration() const;` — Return the max duration of all the caches stored in the collection
- L37 _public prototype_ `uint32 GetMaxNumFrames() const;` — Return the max number of frames of all the caches stored in the collection
- L40 _public prototype_ `void SetInterpolationMode(EChaosCacheInterpolationMode Mode);` — Set the interpolation mode on this cache collection
- L42 _public function_ `EChaosCacheInterpolationMode GetInterpolationMode() const`
- L45 _public member_ `TArray<TObjectPtr<UChaosCache>> Caches;` — `UPROPERTY(EditAnywhere, Instanced, Category="Caching", meta=(EditFixedOrder))`
- L49 _private member_ `EChaosCacheInterpolationMode InterpolationMode;` — `UPROPERTY(EditAnywhere, Category = "Caching")`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/CacheEvents.h` (Public)


#### struct `FCacheEventBase`  
`struct FCacheEventBase`  
_L14-21_
- reflection: `USTRUCT()`
- desc: Base type for all events, ALL events must derive from this so we have a fallback for serialization when we can't find the actual event struct.
- L18 _public function_ `FCacheEventBase()`
- L20 _public prototype_ `virtual ~FCacheEventBase() = default;`

#### struct `FCacheEventTrack`  
`struct FCacheEventTrack`  
_L24-175_
- reflection: `USTRUCT()`
- L61 _public prototype_ `FCacheEventTrack();`
- L62 _public prototype_ `FCacheEventTrack(FName InName, UScriptStruct* InStruct);`
- L64 _public prototype_ `~FCacheEventTrack();`
- L67 _public member_ `FName Name;` — `UPROPERTY()`
- L71 _public member_ `TObjectPtr<UScriptStruct> Struct;` — `UPROPERTY()` — Type of the event stored in this track. Must inherit FCacheEventBase
- L74 _public member_ `TArray<float> TimeStamps;` — `UPROPERTY()`
- L76 _public member_ `TArray<uint8*> EventData;`
- L80 _public function_ `template<typename T> void PushEvent(float TimeStamp, const T& InEvent)` — Pushes an event to the track, this will perform a copy of the event and store it inside the track
- L94 _public function_ `template<typename T> T* GetEvent(int32 Index)`
- L106 _public function_ `template<typename T> const T* GetEvent(int32 Index) const`
- L118 _public prototype_ `FHandle GetEventHandle(int32 Index) const;` — Get a handle to an event that can easily resolve the inner event type without knowing the track
- L121 _public function_ `template<typename T> TArray<T*> GetEvents(float T0, float T1, int32* OptOutBeginIndex = nullptr)`
- L150 _public prototype_ `void DestroyAll();` — Because the memory management for this track is manual, Destroy all will destroy the stored structs correctly
- L153 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom serialize handles generic event serialization
- L156 _public prototype_ `void Merge(FCacheEventTrack&& Other);` — Merge the events from another track, leaving the other empty. The other track must be of the same event type
- L159 _public prototype_ `int32 GetTransientVersion() const;` — The transient version changes whenever the size of the event array changes and invalidates all old event handles
- L161 _public function_ `int32 Num() const`
- L171 _private member_ `int32 TransientVersion;` — Version/Modified counter to invalidate evaluation handles if something holds on to them over time Because handles are used during evaluation we don't need to store this per event
- L172 _private prototype_ `void PushEventInternal(float TimeStep, const void* Event);`
- L173 _private prototype_ `void LoadEventsFromArchive(FArchive& Ar);`
- L174 _private prototype_ `void SaveEventsToArchive(FArchive& Ar);`

#### struct `FCacheEventTrack::FHandle`  
`struct FHandle`  
_L28-59_
- L30 _public function_ `FHandle() : Track(nullptr) , Version(0) , Index(INDEX_NONE)`
- L39 _public function_ `T* Get() const` — `UE_DEPRECATED(5.6, "Non-const access is deprecated. Use GetConst instead")`
- L45 _public function_ `template<typename T> const T* GetConst() const`
- L54 _private prototype_ `bool IsAlive() const;`
- L56 _private member_ `const FCacheEventTrack* Track;`
- L57 _private member_ `int32 Version;`
- L58 _private member_ `int32 Index;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FCacheEventTrack> : public TStructOpsTypeTraitsBase2<FCacheEventTrack>`  
_L180-186_
- inherits: `TStructOpsTypeTraitsBase2<FCacheEventTrack>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L183-185_

#### Free symbols / members of external scopes

- L177 _typedef_ `using FCacheEventHandle = FCacheEventTrack::FHandle;`
- L184 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonb77554a20103`)

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/CacheManagerActor.h` (Public)


#### enum `ECacheMode`  
`enum class ECacheMode : uint8`  
_L24-29_
- reflection: `UENUM()`
- L26 _public enumerator_ `None UMETA(DisplayName = "Static Pose")`
- L27 _public enumerator_ `Play`
- L28 _public enumerator_ `Record`

#### enum `EStartMode`  
`enum class EStartMode : uint8`  
_L32-36_
- reflection: `UENUM()`
- L34 _public enumerator_ `Timed`
- L35 _public enumerator_ `Triggered`

#### struct `FObservedComponent`  
`struct FObservedComponent`  
_L44-167_
- reflection: `USTRUCT(BlueprintType)`
- L48 _public function_ `FObservedComponent() : CacheName(NAME_None) , bIsSimulating(true) , bPlaybackEnabled(true) , bHasNotifyBreaks(false) , Cache(nullptr) , BestFitAdapter(nullptr)`
- L58 _public function_ `FObservedComponent(const FObservedComponent& OtherComponent)`
- L74 _public function_ `FObservedComponent& operator=(const FObservedComponent& OtherComponent)`
- L93 _public function_ `~FObservedComponent()`
- L101 _public member_ `FName CacheName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caching")` — Unique name for the cache, used as a key into the cache collection
- L107 _public member_ `FComponentReference ComponentRef;` — `UE_DEPRECATED(5.1, "This property is going to be deleted. Use the SoftComponentRef instead")` — `UPROPERTY()` — Deprecated hard object reference. Not working with sequencer and take recorder since all the pointers from any other packages are cleared out. Use TSoftObjectPtr instead.
- L111 _public member_ `FSoftComponentReference SoftComponentRef;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caching", meta = (UseComponentPicker, AllowAnyActor))` — The component observed by this object for either playback or recording
- L115 _public member_ `bool bIsSimulating;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Caching")` — Capture of the initial state of the component before cache manager takes control.
- L119 _public member_ `bool bPlaybackEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caching")` — Whether this component is enabled for playback, this allow a cache to hold many component but only replay some of them.
- L123 _public member_ `FDirectoryPath USDCacheDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caching", meta=(ContentDir))` — USD cache directory, if supported for this simulated structure type.
- L131 _public member_ `bool bHasNotifyBreaks;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Caching")` — Capture the state of bNotifyBreaks of the component before cache manager takes control. this is because when recording the cache needs the component to have bNotifyBreaks set on the component to be able to properly record when clusters are breaking into smaller pieces
- L134 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Post serialize function to transfer datas from the deprecated TObjectPtr -> TSoftObjectPtr
- L137 _public prototype_ `void ResetRuntimeData(const EStartMode ManagerStartMode);` — Prepare runtime tick data for a new run
- L140 _public prototype_ `bool IsEnabled(ECacheMode CacheMode) const;` — Check if the Observed component is enabled for a specific cache mode
- L143 _public function_ `UChaosCache* GetChaosCache() const` — Gets the chaos cache from the observed component
- L146 _public prototype_ `UPrimitiveComponent* GetComponent(AActor* OwningActor);` — Gets the component from the internal component ref
- L147 _public prototype_ `UPrimitiveComponent* GetComponent(AActor* OwningActor) const;`
- L149 _public function_ `UPrimitiveComponent* GetComponent()` — `UE_DEPRECATED(5.3, "Use GetComponent(OwningActor) instead.")`
- L151 _public function_ `UPrimitiveComponent* GetComponent() const` — `UE_DEPRECATED(5.3, "Use GetComponent(OwningActor) instead.")`
- L157 _private member_ `bool bTriggered;` — Whether the observed component is active
- L158 _private member_ `Chaos::FReal AbsoluteTime;` — Time since BeginPlay
- L159 _private member_ `Chaos::FReal TimeSinceTrigger;` — Time since our trigger happened
- L160 _private member_ `UChaosCache* Cache;` — Cache to play - picked up in BeginPlay on the manager.
- L161 _private member_ `FPlaybackTickRecord TickRecord;` — Tick record to track where we are in playback
- L163 _private member_ `Chaos::FComponentCacheAdapter* BestFitAdapter;` — Cache a pointer to the best adapter, required for cache random access handling.
- L165 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnDestroying, const FObservedComponent&);`
- L166 _private member_ `FOnDestroying OnDestroying;`

#### struct `FPerSolverData`  
`struct FPerSolverData`  
_L169-185_
- L172 _public member_ `FDelegateHandle PreSolveHandle;` — Handles to solver events to push/pull cache data
- L173 _public member_ `FDelegateHandle PreBufferHandle;`
- L174 _public member_ `FDelegateHandle PostSolveHandle;`
- L175 _public member_ `FDelegateHandle TeardownHandle;`
- L178 _public member_ `TArray<FPlaybackTickRecord> PlaybackTickRecords;` — List of the tick records for each playback index, tracks where the last tick was
- L180 _public member_ `TArray<int32> PlaybackIndices;` — List of indices for components tagged for playback - avoids iterating non playback components
- L182 _public member_ `TArray<int32> RecordIndices;` — List of indices for components tagged for record - avoids iterating non record components
- L184 _public member_ `TArray<Chaos::TPBDRigidParticleHandle<Chaos::FReal, 3>*> PendingKinematicUpdates;` — List of particles in the solver that are pending a kinematic update to be pushed back to their owner

#### class `AChaosCacheManager`  
`class AChaosCacheManager : public AActor`  
_L188-488_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `AActor`
- L193 _public prototype_ `AChaosCacheManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L200 _public member_ `TObjectPtr<UChaosCacheCollection> CacheCollection;` — `UPROPERTY(EditInstanceOnly, Category = "Caching")` — The Cache Collection asset to use for this observer. This can be used for playback and record simultaneously across multiple components depending on the settings for that component.
- L206 _public member_ `bool bCreateNewCacheCollectionAssetOnRecord = false;` — `UPROPERTY(EditAnywhere, Category = "Caching", meta = (EditCondition = "CacheCollection != nullptr"))` — When on, each time the cache starts recording a new asset will be created as an increment of the previous one
- L210 _public member_ `ECacheMode CacheMode;` — `UPROPERTY(EditAnywhere, Category = "Caching")` — How to use the cache - playback or record
- L218 _public member_ `EStartMode StartMode;` — `UPROPERTY(EditAnywhere, Category = "Caching")` — How to trigger the cache record or playback, timed will start counting at BeginPlay, Triggered will begin counting from when the owning cache manager is requested to trigger the cache action @see AChaosCacheManager::TriggerObservedComponent
- L225 _public member_ `float StartTime;` — `UPROPERTY(EditAnywhere, Interp, BlueprintReadWrite, Category = "Caching", meta=(SequencerTrackClass="/Script/MovieSceneTracks.MovieSceneFloatTrack"))` — Defines the (random access) time that represents the rest pose of the components managed by this cache. When in Play mode, the components are set to the state provided by the caches at this evaluated time.
- L232 _public member_ `bool bStartOnBeginPlay;` — `UPROPERTY(EditAnywhere, Category = "Caching")` — if true, cache will start automatically on begin play(playing or recording) if false, the function Start must be used to tsrat the cache again ( and can be stopped again using Stop )
- L238 _public member_ `bool bReplayEventsInStaticPoseMode = true;` — `UPROPERTY(EditAnywhere, Category = "Caching", meta = (EditCondition = "CacheMode == ECacheMode::None"))` — When in static pose, replay the breaking and collision events through the Chaos Event Relay
- L241 _public prototype_ `void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;` — AActor interface
- L245 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L251 _public prototype_ `bool ContainsProperty(const UStruct* Struct, const void* InProperty) const;`
- L252 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L256 _public prototype_ `virtual void PreEditChange(class FProperty* PropertyAboutToChange) override;`
- L257 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L261 _public prototype_ `void SetCacheMode(ECacheMode NewCacheMode);`
- L264 _public prototype_ `bool IsRecording() const;` — `UFUNCTION(BlueprintCallable, Category = "Caching")`
- L271 _public prototype_ `void SetStartTime(float InStartTime);` — `UFUNCTION(CallInEditor)` — Expose StartTime property to Sequencer. GetStartTime will be called on keys. Note this will be ignored for evaluating in Play mode ( for that case, make sure to use Start(time) instead as this will properly stop the physics thread evalution and restert it after setting the time )
- L278 _public prototype_ `void SetCurrentTime(float CurrentTime);` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — Used to set the start time of the cache from a blueprint Note this will be ignored for evaluating in Play mode ( for that case, make sure to use Start(time) instead as this will properly stop the physics thread evalution and restert it after setting the time )
- L286 _public prototype_ `void Start(float InStartTime = 0);` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — Start the cache evaluation at a specific time If the cache if already eveluating, stop it, set the time, then re-start only works when the cache is in Static Pose or Play mode
- L292 _public prototype_ `void Stop();` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — stop the cache from eveluating
- L299 _public prototype_ `void ResetAllComponentTransforms();` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — Resets all components back to the world space transform they had when the cache for them was originally recorded if one is available
- L307 _public prototype_ `void ResetSingleTransform(int32 InIndex);` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — Resets the component at the specified index in the observed list back to the world space transform it had when the cache for it was originally recorded if one is available @param InIndex Index of the component to reset
- L314 _public prototype_ `void SelectComponent(int32 InIndex);` — Set the component at the specified index in the observed array to be the selected component in the outliner. This will also make that component's owner the selected actor in the outliner.
- L318 _public function_ `bool CanRecord() const` — Returns true if this cache manager is allowed to record caches.
- L321 _public prototype_ `void BeginEvaluate();` — Initialize the cache adapters before playing/recording the cache.
- L324 _public prototype_ `void EndEvaluate();` — Clean the cache adapters after playing/recording the cache.
- L327 _public function_ `const TArray<FObservedComponent>& GetObservedComponents() const` — Accessor to the manager observed components (read only)
- L330 _public function_ `TArray<FObservedComponent>& GetObservedComponents()` — Accessor to the manager observed components (read/write)
- L334 _public prototype_ `void FindOrAddObservedComponent(UPrimitiveComponent* InComponent, const FName& CacheName = TEXT(""), const bool bTransferSimulationFlag = false);` — `UFUNCTION(BlueprintCallable, Category = "Caching", meta = (DisplayName = "UpdateOrAddObservedComponent"))` — Find or add a primitive component to a cache manager
- L338 _public prototype_ `void RemoveObservedComponent(UPrimitiveComponent* InComponent);` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — Remove a primitive component from the cache manager
- L342 _public prototype_ `void ClearObservedComponents(bool bDestroyComponents = true);` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — Clear all the observed components
- L345 _public prototype_ `void SetObservedComponentProperties(const ECacheMode& NewCacheMode);`
- L347 _public prototype_ `void SetEditorIconVisibility(bool bVisibility);`
- L349 _public function_ `void SetRestartSimulation(bool InbRestartSimulation)`
- L350 _public function_ `void SetRestartTimeRange(float InRestartTimeStart, float InRestartTimeEnd)`
- L353 _public function_ `void SetIsSimulating(bool InbIsSimulating)`
- L355 _public prototype_ `void ReadRestartData();` — sets state for all observed components at the restart time.
- L360 _protected prototype_ `void BeginPlay() override;` — AActor interface
- L361 _protected prototype_ `void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L362 _protected prototype_ `void Destroyed() override;`
- L366 _protected prototype_ `void HandlePreSolve(Chaos::FReal InDt, Chaos::FPhysicsSolverEvents* InSolver);` — Handles physics thread pre-solve (push kinematic data for components under playback)
- L369 _protected prototype_ `void HandlePreBuffer(Chaos::FReal InDt, Chaos::FPhysicsSolverEvents* InSolver);` — Handles physics thread pre-buffer (mark dirty kinematic particles)
- L372 _protected prototype_ `void HandlePostSolve(Chaos::FReal InDt, Chaos::FPhysicsSolverEvents* InSolver);` — Handles physics thread post-solve (record data for components under record)
- L375 _protected prototype_ `void HandleTeardown(Chaos::FPhysicsSolverEvents* InSolver);` — Handles solver teardown due to solver destruction / stream-out
- L378 _protected prototype_ `void OnStartFrameChanged(Chaos::FReal InT);` — Evaluates and sets state for all observed components at the specified time.
- L385 _protected prototype_ `void SetCacheCollection(UChaosCacheCollection* InCacheCollection);` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — change the cache collection for this player if the cache is playing or recording this will have no effect
- L395 _public prototype_ `void TriggerComponent(UPrimitiveComponent* InComponent);` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — Triggers a component to play or record. If the cache manager has an observed component entry for InComponent and it is a triggered entry this will begin the playback or record for that component, otherwise no action is taken. @param InComponent Component to trigger
- L404 _public prototype_ `void TriggerComponentByCache(FName InCacheName);` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — Triggers a component to play or record. Searches the observed component list for an entry matching InCacheName and triggers the playback or recording of the linked observed component @param InCacheName Cache name to trigger
- L408 _public prototype_ `void TriggerAll();` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — Triggers the recording or playback of all observed components
- L413 _protected prototype_ `void EnablePlaybackByCache(FName InCacheName, bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — Enable playback for a specific component using its cache name
- L417 _protected prototype_ `void EnablePlayback(int32 Index, bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = "Caching")` — Enable playback for a specific component using its index in the list of observed component
- L419 _protected prototype_ `FObservedComponent* FindObservedComponent(UPrimitiveComponent* InComponent);`
- L420 _protected prototype_ `FObservedComponent& AddNewObservedComponent(UPrimitiveComponent* InComponent);`
- L423 _protected member_ `bool bCanRecord;` — Determines if the actor is allowed to record a cache.
- L426 _protected member_ `bool bIsSimulating;` — true if observed components are actively simulating, dynamically or kinematically.
- L432 _private typedef_ `using FTickObservedFunction = TUniqueFunction<void(UChaosCache*, FObservedComponent&, Chaos::FComponentCacheAdapter*)>;`
- L441 _private prototype_ `void TickObservedComponents(const TArray<int32>& InIndices, Chaos::FReal InDt, FTickObservedFunction InCallable);` — Helper function to apply a callable to observed components if they've been triggered, all of the Dt/time bookkeeping is handled in one place @param InIndices Index list of the observed components to update @param InDt Delta for the tick @param InCallable Callable to fire if the observed component is active
- L446 _private prototype_ `void WaitForObservedComponentSolverTasks();` — Stall on any in flight solver tasks that might call callbacks. Necessary before editing callbacks.
- L452 _private prototype_ `void CreateAndSetNewCacheAsset();` — this creates a new cache collection asset based on the existing one and set it as the current this also find the editor counterpart actor and update the cache collection accordingly
- L454 _private prototype_ `void OnObservedComponentDestroyed(const FObservedComponent& Component);`
- L455 _private prototype_ `void RegisterObservedComponentsNotifiers();`
- L456 _private prototype_ `void UnregisterObservedComponentsNotifiers();`
- L457 _private prototype_ `void EnsureObservedComponentsNotifierRegistration();`
- L461 _private member_ `TArray<FObservedComponent> ObservedComponents;` — `UPROPERTY(EditAnywhere, Category = "Caching")` — List of observed objects and their caches
- L464 _private member_ `TArray<Chaos::FComponentCacheAdapter*> ActiveAdapters;` — 1-1 list of adapters for the observed components, populated on BeginEvaluate
- L467 _private member_ `TMap<Chaos::FPhysicsSolverEvents*, FPerSolverData> PerSolverData;` — List of particles returned by the adapter as requiring a kinematic update
- L470 _private member_ `TArray<TTuple<FCacheUserToken, UChaosCache*>> OpenRecordCaches;` — Lists of currently open caches that need to be closed when complete
- L471 _private member_ `TArray<TTuple<FCacheUserToken, UChaosCache*>> OpenPlaybackCaches;`
- L474 _private member_ `float StartTimeAtBeginPlay;` — since the object persists
- L477 _private member_ `float PreviousStartTime;` — previous start time so we can keep track of the elasped time between SetStartTime calls
- L479 _private member_ `bool bRestartSimulation = false;` — if restart for a specified time range
- L480 _private member_ `float RestartTimeStart = TNumericLimits<float>::Max();` — if bRestartSimulation, use RestartTimeStart as an offset when saving, and clear cache data in [RestartTimeStart, RestartTimeEnd]
- L481 _private member_ `float RestartTimeEnd = -TNumericLimits<float>::Max();`
- L485 _private member_ `TObjectPtr<UBillboardComponent> EditorIconComponent;` — `UPROPERTY(Transient)`

#### class `AChaosCachePlayer`  
`class AChaosCachePlayer : public AChaosCacheManager`  
_L491-498_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `AChaosCacheManager`
- L496 _public prototype_ `AChaosCachePlayer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Chaos`
- L18 _namespace_ `namespace Chaos`
- L38 _namespace_ `namespace Chaos`
- L40 _typedef_ `using FPhysicsSolver = FPBDRigidsSolver;` (scope `Chaos`)
- L165 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDestroying, const FObservedComponent&);`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/ChaosCache.h` (Public)


#### struct `FParticleTransformTrack`  
`struct FParticleTransformTrack`  
_L17-77_
- reflection: `USTRUCT()`
- L26 _public member_ `FRawAnimSequenceTrack RawTransformTrack;` — `UPROPERTY()` — List of all the transforms this cache cares about, recorded from the simulated transforms of the particles observed by the adapter that created the cache
- L30 _public member_ `float BeginOffset = 0.f;` — `UPROPERTY()` — The offset from the beginning of the cache that holds this track that the track starts
- L34 _public member_ `bool bDeactivateOnEnd = false;` — `UPROPERTY()` — If this flag is set true, the particle represented by this track deactives on the final keyframe.
- L41 _public member_ `TArray<float> KeyTimestamps;` — `UPROPERTY()` — The above raw track is just the key data and doesn't know at which time those keys are placed, this is a list of the timestamps for each entry in TransformTrack
- L49 _public prototype_ `FTransform Evaluate(float InCacheTime, const FTransform* MassToLocal, EChaosCacheInterpolationMode InterpolationMode = EChaosCacheInterpolationMode::QuatInterp) const;` — Evaluates the transform track at the specified time, returning the evaluated transform. When in between keys translations will be linearly interpolated and rotations spherically interpolated @param InCacheTime Absolute time from the beginning of the entire owning cache to evaluate. @param MassToLocal if not null, the will be premultiplied to transform before interpolation
- L58 _public prototype_ `int32 GetUpperBoundEvaluationIndex(float InCacheTime) const;` — Find the index the key where timestamp is directly above InCacheTime returned value is garanteed to be within the range of keys if there's any in the case there's no key in the track, 0 is returned @param InCacheTime Absolute time from the beginning of the entire owning cache to evaluate. @return Valid key index
- L65 _public prototype_ `FTransform EvaluateAt(int32 Index) const;` — Evaluate the acche at a sepcific index this assumes that index is within the range of valid keys * if the track is empty identity transform is returned
- L67 _public prototype_ `const int32 GetNumKeys() const;`
- L68 _public prototype_ `const float GetDuration() const;`
- L69 _public prototype_ `const float GetBeginTime() const;`
- L70 _public prototype_ `const float GetEndTime() const;`
- L72 _public prototype_ `void Compress();`
- L75 _private prototype_ `void CopyTrackEntry(int32 FromIndex, int32 ToIndex);`
- L76 _private prototype_ `void ResizeTrack(int32 NewSize);`

#### struct `FPerParticleCacheData`  
`struct FPerParticleCacheData`  
_L80-94_
- reflection: `USTRUCT()`
- L85 _public member_ `FParticleTransformTrack TransformData;` — `UPROPERTY()`
- L93 _public member_ `TMap<FName, FRichCurve> CurveData;` — `UPROPERTY()` — Named curve data. This can be particle or other continuous curve data pushed by the adapter that created the cache. Any particle property outside of the transforms will be placed in this container with a suitable name for the property. Blueprints and adapters can add whatever data they need to this container.

#### struct `FCacheSpawnableTemplate`  
`struct FCacheSpawnableTemplate`  
_L97-115_
- reflection: `USTRUCT()`
- L101 _public function_ `FCacheSpawnableTemplate() : DuplicatedTemplate(nullptr) , InitialTransform(FTransform::Identity) , ComponentTransform(FTransform::Identity)`
- L108 _public member_ `TObjectPtr<UObject> DuplicatedTemplate;` — `UPROPERTY(VisibleAnywhere, Category = "Caching")`
- L111 _public member_ `FTransform InitialTransform;` — `UPROPERTY(VisibleAnywhere, Category = "Caching")`
- L114 _public member_ `FTransform ComponentTransform;` — `UPROPERTY(VisibleAnywhere, Category = "Caching")`

#### struct `FPlaybackTickRecord`  
`struct FPlaybackTickRecord`  
_L117-163_
- L119 _public function_ `FPlaybackTickRecord() : CurrentDt(0.0f) , LastTime(0.0f) , SpaceTransform(FTransform::Identity)`
- L126 _public function_ `void Reset()`
- L132 _public function_ `void SetLastTime(float InTime)`
- L137 _public function_ `float GetTime() const`
- L142 _public function_ `void SetDt(float NewDt)`
- L147 _public function_ `void SetSpaceTransform(const FTransform& InTransform)`
- L152 _public function_ `const FTransform& GetSpaceTransform() const`
- L159 _private member_ `float CurrentDt;`
- L160 _private member_ `float LastTime;`
- L161 _private member_ `TMap<FName, int32> LastEventPerTrack;`
- L162 _private member_ `FTransform SpaceTransform;`

#### struct `FCacheEvaluationContext`  
`struct FCacheEvaluationContext`  
_L165-184_
- L167 _public prototype_ `FCacheEvaluationContext() = delete;`
- L168 _public function_ `explicit FCacheEvaluationContext(FPlaybackTickRecord& InRecord) : TickRecord(InRecord) , bEvaluateTransform(false) , bEvaluateCurves(false) , bEvaluateEvents(false) , bEvaluateNamedTransforms(false)`
- L177 _public member_ `FPlaybackTickRecord& TickRecord;`
- L178 _public member_ `bool bEvaluateTransform;`
- L179 _public member_ `bool bEvaluateCurves;`
- L180 _public member_ `bool bEvaluateEvents;`
- L181 _public member_ `TArray<int32> EvaluationIndices;`
- L182 _public member_ `bool bEvaluateChannels;`
- L183 _public member_ `bool bEvaluateNamedTransforms;`

#### struct `FCacheEvaluationResult`  
`struct FCacheEvaluationResult`  
_L186-196_
- L189 _public member_ `float EvaluatedTime;`
- L190 _public member_ `TArray<int32> ParticleIndices;`
- L191 _public member_ `TArray<FTransform> Transform;`
- L192 _public member_ `TArray<TMap<FName, float>> Curves;`
- L193 _public member_ `TMap<FName, TArray<FCacheEventHandle>> Events;`
- L194 _public member_ `TMap<FName, TArray<float>> Channels;`
- L195 _public member_ `TMap<FName, FTransform> NamedTransforms;`

#### struct `FPendingParticleWrite`  
`struct FPendingParticleWrite`  
_L198-204_
- L200 _public member_ `int32 ParticleIndex;`
- L201 _public member_ `FTransform PendingTransform;`
- L202 _public member_ `bool bPendingDeactivate = false;`
- L203 _public member_ `TArray<TPair<FName, float>> PendingCurveData;`

#### struct `FRichCurves`  
`struct FRichCurves`  
_L207-213_
- reflection: `USTRUCT()`
- L212 _public member_ `TArray<FRichCurve> RichCurves;` — `UPROPERTY()`

#### struct `FCompressedRichCurves`  
`struct FCompressedRichCurves`  
_L216-222_
- reflection: `USTRUCT()`
- L221 _public member_ `TArray<FCompressedRichCurve> CompressedRichCurves;` — `UPROPERTY()`

#### struct `FPendingFrameWrite`  
`struct FPendingFrameWrite`  
_L224-253_
- L226 _public member_ `float Time;`
- L227 _public member_ `TArray<FPendingParticleWrite> PendingParticleData;`
- L228 _public member_ `TArray<TPair<FName, float>> PendingCurveData;`
- L229 _public member_ `TMap<FName, FCacheEventTrack> PendingEvents;`
- L231 _public member_ `TArray<int32> PendingChannelsIndices;`
- L232 _public member_ `TMap<FName, TArray<float>> PendingChannelsData;`
- L234 _public member_ `TMap<FName, FTransform> PendingNamedTransformData;`
- L237 _public function_ `template<typename T> FCacheEventTrack& FindOrAddEventTrack(FName InName)`
- L248 _public function_ `template<typename T> void PushEvent(FName InName, float InTime, const T& InEventStruct)`

#### struct `FCacheUserToken`  
`struct FCacheUserToken`  
_L260-297_
- L262 _public function_ `bool IsOpen() const`
- L268 _public function_ `FCacheUserToken(FCacheUserToken&& Other)` — Allow moving, invalidating the old token
- L282 _private member_ `bool bIsOpen;`
- L283 _private member_ `bool bIsRecord;`
- L284 _private member_ `const UChaosCache* Owner;`
- L286 _private function_ `explicit FCacheUserToken(bool bInOpen, bool bInRecord, const UChaosCache* InOwner) : bIsOpen(bInOpen) , bIsRecord(bInRecord) , Owner(InOwner)`
- L293 _private prototype_ `FCacheUserToken() = delete;`
- L294 _private prototype_ `FCacheUserToken(const FCacheUserToken&) = delete;`
- L295 _private prototype_ `FCacheUserToken& operator=(const FCacheUserToken&) = delete;`
- L296 _private prototype_ `FCacheUserToken& operator=(FCacheUserToken&&) = delete;`

#### class `UChaosCacheData`  
`class UChaosCacheData : public UInterface`  
_L301-304_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`
- desc: Interface for the chaos cache data storage. @todo(chaos) : We should probably refactor the chaos cache to allow more custom storage

#### class `IChaosCacheData`  
`class IChaosCacheData`  
_L305-312_
- L311 _public prototype_ `virtual float GetDuration() const = 0;` — Duration of the chaos cache

#### class `UChaosCache`  
`class UChaosCache : public UObject`  
_L315-527_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UObject`
- L320 _public prototype_ `UChaosCache();`
- L323 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L324 _public prototype_ `virtual void PostLoad() override;`
- L332 _public prototype_ `void FlushPendingFrames();` — As we record post-simulate of physics, we're almost always taking data from a non-main thread (physics thread). Because of this we can't directly write into the cache, but instead into a pending frame queue that needs to be flushed on the main thread to write the pending data into the final storage.
- L338 _public prototype_ `FCacheUserToken BeginRecord(const UPrimitiveComponent* InComponent, FGuid InAdapterId, const FTransform& SpaceTransform);` — Reset and initialize a cache to make it ready to record the specified component @param InComponent Component to prepare the cache for
- L346 _public prototype_ `void EndRecord(FCacheUserToken& InOutToken);` — End the recording session for the cache. At this point the cache is deemed to now contain all of the required data from the recording session and can then be post-processed and optimized which may involve key elimination and compression into a final format for runtime @param InOutToken The token that was given by BeginRecord
- L352 _public prototype_ `FCacheUserToken BeginPlayback() const;` — Initialise the cache for playback, may not take any actual action on the cache but will provide the caller with a valid cache user token if it is safe to continue with playback
- L360 _public prototype_ `void EndPlayback(FCacheUserToken& InOutToken) const;` — End a playback session for the cache. There can be multiple playback sessions open for a cache as long as there isn't a recording session. Calling EndPlayback with a valid open token will decrease the session count. @param InOutToken The token that was given by BeginRecord
- L366 _public prototype_ `void AddFrame_Concurrent(FPendingFrameWrite&& InFrame);` — Adds a new frame to process to a threadsafe queue for later processing in FlushPendingFrames @param InFrame New frame to accept, moved into the internal threadsafe queue
- L371 _public prototype_ `float GetDuration() const;` — Gets the recorded duration of the cache
- L379 _public prototype_ `FCacheEvaluationResult Evaluate(const FCacheEvaluationContext& InContext, const TArray<FTransform>* MassToLocalTransforms) const;` — Evaluate the cache with the specified parameters, returning the evaluated results @param InContext evaluation context @param MassToLocalTransforms MassToLocal trasnform if available ( geometry collection are using them ) @see FCacheEvaluationContext
- L386 _public prototype_ `void BuildSpawnableFromComponent(const UPrimitiveComponent* InComponent, const FTransform& SpaceTransform);` — Initializes the spawnable template from a currently existing component so it can be spawned by the editor when a cache is dragged into the scene. @param InComponent Component to build the spawnable template from
- L391 _public prototype_ `const FCacheSpawnableTemplate& GetSpawnableTemplate() const;` — Read access to the spawnable template stored in the cache
- L394 _public function_ `IChaosCacheData* GetCacheData() const` — Get the cache data asset if defined
- L397 _public function_ `void SetCacheData(IChaosCacheData* InCacheData)` — Set the cache data asset interface
- L407 _public prototype_ `void EvaluateSingle(int32 InIndex, FPlaybackTickRecord& InTickRecord, const FTransform* MassToLocal, FTransform* OutOptTransform, TMap<FName, float>* OutOptCurves) const;` — Evaluates a single particle from the tracks array @param InIndex Particle track index (unchecked, ensure valid before call) @param InTickRecord Tick record for this evaluation @param MassToLocal MassToLocal transform, necessary for proper interpolation, if not available, nullptr shoudl used instead @param OutOptTransform Transform to fill, skipped if null @param OutOptCurves Curves to fill, skipped if null
- L409 _public prototype_ `void EvaluateTransform(const FPerParticleCacheData& InData, float InTime, const FTransform* MassToLocal, FTransform& OutTransform) const;`
- L410 _public prototype_ `void EvaluateCurves(const FPerParticleCacheData& InData, float InTime, TMap<FName, float>& OutCurves) const;`
- L411 _public prototype_ `void EvaluateEvents(FPlaybackTickRecord& InTickRecord, TMap<FName, TArray<FCacheEventHandle>>& OutEvents) const;`
- L413 _public prototype_ `void CompressChannelsData(float ErrorThreshold, float SampleRate);`
- L416 _public member_ `float RecordedDuration;` — `UPROPERTY(VisibleAnywhere, Category = "Caching")`
- L419 _public member_ `uint32 NumRecordedFrames;` — `UPROPERTY(VisibleAnywhere, Category = "Caching")`
- L422 _public member_ `EChaosCacheInterpolationMode InterpolationMode = EChaosCacheInterpolationMode::QuatInterp;` — `UPROPERTY(VisibleAnywhere, Category = "Caching")`
- L426 _public member_ `TArray<int32> TrackToParticle;` — `UPROPERTY()` — Maps a track index in the cache to the original particle index specified when recording
- L430 _public member_ `TArray<FPerParticleCacheData> ParticleTracks;` — `UPROPERTY()` — Per-particle data, includes transforms, velocities and other per-particle, per-frame data
- L434 _public member_ `TArray<int32> ChannelCurveToParticle;` — `UPROPERTY()` — Map a curve index in the cache to the original particle index specified when recording
- L438 _public member_ `TMap<FName,FRichCurves> ChannelsTracks;` — `UPROPERTY()` — Per-particle data,  continuous per-frame data
- L441 _public member_ `TMap<FName, FCompressedRichCurves> CompressedChannelsTracks;` — `UPROPERTY()`
- L445 _public member_ `TMap<FName, FRichCurve> CurveData;` — `UPROPERTY()` — Per component/cache curve data, any continuous data that isn't per-particle can be stored here
- L448 _public typedef_ `typedef FParticleTransformTrack FNamedTransformTrack;` — Per component/cache transform data.
- L450 _public member_ `TMap<FName, FParticleTransformTrack> NamedTransformTracks;` — `UPROPERTY()`
- L453 _public member_ `bool bCompressChannels = false;` — `UPROPERTY()`
- L456 _public member_ `float ChannelsCompressionErrorThreshold = 1e-5f;` — `UPROPERTY()`
- L459 _public member_ `float ChannelsCompressionSampleRate = 1.f / 30.f;` — `UPROPERTY()`
- L462 _public function_ `template<typename T> FCacheEventTrack& FindOrAddEventTrack(FName InName)`
- L476 _private member_ `TScriptInterface<IChaosCacheData> CacheData;` — `UPROPERTY()` — Optional cache data to store on the chaos cache
- L478 _private prototype_ `void FlushPendingFrames_ChannelOnlyReservePass(TQueue<FPendingFrameWrite, EQueueMode::Spsc>& LocalPendingWrites, bool& bCanSimpleCopyChannelData);`
- L483 _private prototype_ `template<EQueueMode Mode> bool FlushPendingFrames_MainPass(TQueue<FPendingFrameWrite, Mode>& InPendingWrites, bool bCanSimpleCopyChannelData);` — @return Whether or not any particle data was written
- L485 _private prototype_ `void CompressTracks();`
- L491 _private member_ `TMap<FName, FCacheEventTrack> EventTracks;` — `UPROPERTY()` — Timestamped generic event tracks
- L495 _private member_ `FCacheSpawnableTemplate Spawnable;` — `UPROPERTY(VisibleAnywhere, Category = "Caching")` — Spawn template for an actor that can play this cache
- L499 _private member_ `FGuid AdapterGuid;` — `UPROPERTY()` — GUID identifier for the adapter that spawned this cache
- L503 _private member_ `int32 Version;` — `UPROPERTY()` — Version for controlling conditioning of older caches to work with current system. Newly created caches should always be saved as CurrentVersion.
- L507 _private member_ `static constexpr int32 CurrentVersion = 1;` — Version 0 : Pre versioning. Version 1 : Introduction of actor space transforms & removal of baked MassTOLocal transform in GeometryCollections.
- L510 _private member_ `TQueue<FPendingFrameWrite, EQueueMode::Mpsc> PendingWrites;` — Pending writes from all threads to be consumed on the game thread, triggered by the recording cache manager
- L513 _private member_ `std::atomic<int32> CurrentRecordCount;` — Counts for current number of users, should only ever have one recorder, and if we do no playbacks
- L514 _private member_ `mutable std::atomic<int32> CurrentPlaybackCount;`
- L517 _private member_ `bool bStripMassToLocal;` — Indicates that we need to strip MassToLocal before playing the cache.
- L520 _private member_ `TMap<int32,int32> ParticleToChannelCurve;` — Reverse Lookup for ChannelCurveToParticle. Rebuilt on load.
- L523 _private member_ `float MinTime = TNumericLimits<float>::Max();` — Min time in case we are not writing to particle/curves/channels datas
- L526 _private member_ `float MaxTime = TNumericLimits<float>::Lowest();` — Max time in case we are not writing to particle/curves/channels datas

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/ChaosCacheInterpolationMode.h` (Public)


#### enum `EChaosCacheInterpolationMode`  
`enum class EChaosCacheInterpolationMode : uint8`  
_L8-18_
- reflection: `UENUM()`
- L11 _public enumerator_ `QuatInterp` — Shortest Path or Quaternion interpolation for the rotation.
- L14 _public enumerator_ `EulerInterp` — Rotor or Euler Angle interpolation.
- L17 _public enumerator_ `DualQuatInterp` — Dual quaternion interpolation, follows helix or screw-motion path between keyframes.

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/ChaosCachingPlugin.h` (Public)


#### class `IChaosCachingPlugin`  
`class IChaosCachingPlugin : public IModuleInterface`  
_L15-47_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule();`
- L19 _public prototype_ `virtual void ShutdownModule();`
- L27 _public function_ `static inline IChaosCachingPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L43 _private member_ `TUniquePtr<Chaos::FGeometryCollectionCacheAdapter> GeometryCollectionAdapter;`
- L44 _private member_ `TUniquePtr<Chaos::FStaticMeshCacheAdapter> StaticMeshAdapter;`
- L46 _private member_ `FDelegateHandle OnCreateMovieSceneObjectSpawnerHandle;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosCache, Verbose, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosCache, Verbose, All);`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/Sequencer/ChaosCacheObjectSpawner.h` (Public)


#### class `FChaosCacheObjectSpawner`  
`class FChaosCacheObjectSpawner : public FLevelSequenceActorSpawner`  
_L8-29_
- inherits: `FLevelSequenceActorSpawner`
- desc: Chaos cache Manager spawner to create a new cache manager from the spawnable template
- L12 _public prototype_ `FChaosCacheObjectSpawner();` — `UE_DEPRECATED(5.5, "This has been deprecated as it is no longer necessary. We use UMovieSceneSpawnableChaosCache custom binding instead to handle this logic")`
- L16 _public prototype_ `static TSharedRef<IMovieSceneObjectSpawner> CreateObjectSpawner();` — `UE_DEPRECATED(5.5, "This has been deprecated as it is no longer necessary. We use UMovieSceneSpawnableChaosCache custom binding instead to handle this logic")` — Static method to create the object spawner
- L20 _public prototype_ `virtual UClass* GetSupportedTemplateType() const override;` — `UE_DEPRECATED(5.5, "This has been deprecated as it is no longer necessary. We use UMovieSceneSpawnableChaosCache custom binding instead to handle this logic")` — IMovieSceneObjectSpawner interface
- L23 _public prototype_ `virtual UObject* SpawnObject(FMovieSceneSpawnable& Spawnable, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;` — `UE_DEPRECATED(5.5, "This has been deprecated as it is no longer necessary. We use UMovieSceneSpawnableChaosCache custom binding instead to handle this logic")`
- L26 _public prototype_ `virtual void DestroySpawnedObject(UObject& Object) override;` — `UE_DEPRECATED(5.5, "This has been deprecated as it is no longer necessary. We use UMovieSceneSpawnableChaosCache custom binding instead to handle this logic")`
- L27 _public function_ `virtual bool IsEditor() const override`
- L28 _public function_ `virtual int32 GetSpawnerPriority() const override`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/Sequencer/MovieSceneChaosCacheSection.h` (Public)


#### struct `FMovieSceneChaosCacheParams`  
`struct FMovieSceneChaosCacheParams : public FMovieSceneBaseCacheParams`  
_L9-22_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneBaseCacheParams`
- L13 _public prototype_ `FMovieSceneChaosCacheParams();`
- L14 _public prototype_ `virtual ~FMovieSceneChaosCacheParams() override = default;`
- L17 _public prototype_ `virtual float GetSequenceLength() const override;` — Gets the animation sequence length, not modified by play rate
- L21 _public member_ `TObjectPtr<class UChaosCacheCollection> CacheCollection;` — `UPROPERTY(EditAnywhere, Category = "ChaosCache")` — The animation this section plays

#### class `UMovieSceneChaosCacheSection`  
`class UMovieSceneChaosCacheSection : public UMovieSceneBaseCacheSection`  
_L28-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneBaseCacheSection`
- desc: Movie scene section that control ChaosCache playback
- L35 _public member_ `FMovieSceneChaosCacheParams Params;` — `UPROPERTY(EditAnywhere, Category = "Animation", meta = (ShowOnlyInnerProperties))`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/Sequencer/MovieSceneChaosCacheTrack.h` (Public)


#### class `UMovieSceneChaosCacheTrack`  
`class UMovieSceneChaosCacheTrack : public UMovieSceneNameableTrack , public IMovieSceneTrackTemplateProducer`  
_L13-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack,IMovieSceneTrackTemplateProducer`
- desc: Handles animation of ChaosCache
- L22 _public prototype_ `virtual UMovieSceneSection* AddNewAnimation(FFrameNumber KeyTime, class AChaosCacheManager* ChaosCache);` — Adds a new animation to this track
- L25 _public prototype_ `TArray<UMovieSceneSection*> GetAnimSectionsAtTime(FFrameNumber Time);` — Gets the animation sections at a certain time
- L30 _public prototype_ `virtual void RemoveAllAnimationData() override;` — UMovieSceneTrack interface
- L31 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L32 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L33 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L34 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L35 _public prototype_ `virtual bool IsEmpty() const override;`
- L36 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L37 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L38 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L41 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L44 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L51 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> AnimationSections;` — `UPROPERTY()` — List of all animation sections

### `Plugins/Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos/Sequencer/MovieSceneSpawnableChaosCacheBinding.h` (Public)


#### class `UMovieSceneSpawnableChaosCacheBinding`  
`class UMovieSceneSpawnableChaosCacheBinding : public UMovieSceneSpawnableActorBinding`  
_L13-37_
- reflection: `UCLASS(BlueprintType, MinimalAPI, EditInlineNew, DefaultToInstanced, Meta=(DisplayName="Spawnable Chaos Cache"))`
- inherits: `UMovieSceneSpawnableActorBinding`
- desc: An override of UMovieSceneSpawnableActorBinding that adds some custom behavior on Spawn
- L23 _public prototype_ `bool SupportsBindingCreationFromObject(const UObject* SourceObject) const override;` — MovieSceneCustomBinding overrides
- L26 _public prototype_ `FText GetBindingTypePrettyName() const override;`
- L30 _public prototype_ `UObject* SpawnObjectInternal(UWorld* WorldContext, FName SpawnName, const FGuid& BindingId, int32 BindingIndex, UMovieScene& MovieScene, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;` — Overridden to handle Chaos Cache -specific spawning
- L35 _protected function_ `int32 GetCustomBindingPriority() const override` — Ensures we override priority of UMovieSceneSpawnableActorBinding
