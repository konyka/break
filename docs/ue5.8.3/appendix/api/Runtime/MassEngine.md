# Runtime / MassEngine

- module root: `Source/Runtime/Mass/MassEngine`
- headers: 17; symbols: 462
- symbol kinds: class=18, enum=11, enumerator=18, function=19, macro=3, member=92, namespace=10, prototype=237, struct=39, typedef=5, variable=10
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, Engine, MassCore, MassEntity, MassSignals, RHI, RenderCore

### `Source/Runtime/Mass/MassEngine/Private/Mesh/MassDestroyRenderStateContext.h` (Private)


#### struct `FMassDestroyRenderStateContext`  
`struct FMassDestroyRenderStateContext`  
_L14-40_
- desc: Context to batch the destroy render states.
- L17 _public prototype_ `FMassDestroyRenderStateContext(FSceneInterface* InScene);`
- L18 _public prototype_ `~FMassDestroyRenderStateContext();`
- L20 _public function_ `bool IsInitialized() const`
- L25 _public function_ `void Initialize(FSceneInterface* InScene)`
- L31 _public prototype_ `void Process();`
- L33 _public prototype_ `static void DestroyProxy(FMassDestroyRenderStateContext* InContext, FPrimitiveSceneProxy* InPrimitiveSceneProxy, FSceneInterface* InScene);`
- L34 _public prototype_ `static void DestroyProxy(FMassDestroyRenderStateContext* InContext, FDeferredDecalProxy* InDeferredDecalProxy, FSceneInterface* InScene);`
- L37 _private member_ `FSceneInterface* Scene = nullptr;`
- L38 _private member_ `TArray<FPrimitiveSceneProxy*> PrimitiveSceneProxies;`
- L39 _private member_ `TArray<FDeferredDecalProxy*> DeferredDecalProxies;`

### `Source/Runtime/Mass/MassEngine/Private/Mesh/MassISMRenderStateHelper.h` (Private)


#### struct `FMassISMRenderStateHelper`  
`struct FMassISMRenderStateHelper : public FMassBaseStaticMeshRenderStateHelper`  
_L13-50_
- inherits: `FMassBaseStaticMeshRenderStateHelper`
- desc: Helper to handle all the communication to the renderer from Mass for an instanced static mesh
- L16 _public typedef_ `using Super = FMassBaseStaticMeshRenderStateHelper ;`
- L18 _public prototype_ `FMassISMRenderStateHelper(FMassEntityHandle InEntityHandle, TNotNull<FMassEntityManager*> InEntityManager, const FMassRenderPrimitiveFragment& RenderPrimitiveFragment, const FMassOverrideMaterialsFragment* OverrideMaterialsFragment, const FMassRenderISMFragment& RenderStaticMeshFragment);`
- L19 _public prototype_ `virtual ~FMassISMRenderStateHelper() override = default;`
- L23 _protected prototype_ `virtual FPrimitiveSceneProxyDesc& GetSceneProxyDesc() override;`
- L24 _protected prototype_ `virtual const FPrimitiveSceneProxyDesc& GetSceneProxyDesc() const override;`
- L25 _protected prototype_ `virtual void ResetSceneProxyDescUnsupportedProperties() override;`
- L29 _protected prototype_ `virtual FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() override;`
- L30 _protected prototype_ `virtual const FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() const override;`
- L31 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateStaticMeshSceneProxy(const Nanite::FMaterialAudit& NaniteMaterials, bool bCreateNanite) override;`
- L33 _protected prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams) override;`
- L37 _protected prototype_ `TSharedPtr<FInstanceDataSceneProxy, ESPMode::ThreadSafe>& BuildInstanceData();`
- L39 _protected prototype_ `const FMassRenderISMFragment& GetRenderISMFragment() const;`
- L40 _protected prototype_ `FMassRenderISMFragment& GetMutableRenderISMFragment();`
- L44 _protected prototype_ `virtual void InitializeSceneProxyDescDynamicProperties() override;`
- L46 _protected member_ `TSharedPtr<FInstanceDataSceneProxy, ESPMode::ThreadSafe> DataProxy{};`
- L47 _protected member_ `TArray<float> InstanceRandomIDs;`

### `Source/Runtime/Mass/MassEngine/Private/Mesh/MassMeshRenderStateHelper.h` (Private)


#### struct `FMassMeshRenderStateHelper`  
`struct FMassMeshRenderStateHelper : public FMassPrimitiveRenderStateHelper`  
_L16-41_
- inherits: `FMassPrimitiveRenderStateHelper`
- desc: Helper to handle all the communication to the renderer from Mass for all type of meshes
- L19 _public typedef_ `using Super = FMassPrimitiveRenderStateHelper;`
- L21 _public prototype_ `FMassMeshRenderStateHelper(FMassEntityHandle InEntityHandle, TNotNull<FMassEntityManager*> InEntityManager, const FMassRenderPrimitiveFragment& RenderPrimitiveFragment, const FMassOverrideMaterialsFragment* OverrideMaterialsFragment);`
- L22 _public prototype_ `virtual ~FMassMeshRenderStateHelper() override = default;`
- L24 _public prototype_ `FMaterialRelevance GetMaterialRelevance(EShaderPlatform InShaderPlatform) const;`
- L26 _public prototype_ `void GetMaterialSlotsOverlayMaterial(TArray<TObjectPtr<UMaterialInterface>>& OutMaterialSlotOverlayMaterials) const;`
- L29 _public prototype_ `virtual void GetDefaultMaterialSlotsOverlayMaterial(TArray<TObjectPtr<UMaterialInterface>>& AssetMaterialSlotOverlayMaterials) const = 0;` — Get the asset material slot overlay material
- L31 _public prototype_ `virtual const TArray<TObjectPtr<UMaterialInterface>>& GetComponentMaterialSlotsOverlayMaterial() const = 0;`
- L32 _public prototype_ `virtual UMaterialInterface* GetOverlayMaterial() const = 0;`
- L34 _public prototype_ `const FMassOverrideMaterialsFragment* GetOverrideMaterialsFragment() const;`
- L35 _public prototype_ `const FMassVisualizationMeshFragment& GetMeshFragment() const;`
- L37 _public prototype_ `const FMassEditorVisualizationMeshFragment* GetEditorMeshFragment() const;`
- L40 _public prototype_ `TConstArrayView<TObjectPtr<UMaterialInterface>> GetOverrideMaterials() const;`

### `Source/Runtime/Mass/MassEngine/Private/Mesh/MassPrimitiveRenderStateHelper.h` (Private)


#### struct `FMassPrimitiveRenderStateHelper`  
`struct FMassPrimitiveRenderStateHelper : public FMassRenderStateHelper, public IPrimitiveComponent`  
_L26-158_
- inherits: `FMassRenderStateHelper,IPrimitiveComponent`
- desc: Helper to handle all the communication to the renderer from Mass for all type of primitives
- L29 _public typedef_ `using Super = FMassRenderStateHelper;`
- L31 _public prototype_ `FMassPrimitiveRenderStateHelper(FMassEntityHandle InEntityHandle, TNotNull<FMassEntityManager*> InEntityManager, const FMassRenderPrimitiveFragment& RenderPrimitiveFragment);`
- L32 _public prototype_ `virtual ~FMassPrimitiveRenderStateHelper() override = default;`
- L34 _public prototype_ `TConstArrayView<URuntimeVirtualTexture*> GetRuntimeVirtualTextures() const;`
- L35 _public prototype_ `bool IsFirstPersonRelevant() const;`
- L37 _public prototype_ `FPrimitiveComponentId GetPrimitiveSceneId() const;`
- L38 _public function_ `virtual UObject const* AdditionalStatObject() const`
- L43 _public prototype_ `FMatrix GetRenderMatrix() const;`
- L46 _public function_ `FTransform GetComponentTransform() const` — Used by FStaticMeshComponentHelper/FInstancedStaticMeshComponentHelper
- L49 _public prototype_ `const FMassRenderPrimitiveFragment& GetRenderPrimitiveFragment() const;` — Primitive Fragments helpers
- L50 _public prototype_ `FMassRenderPrimitiveFragment& GetMutableRenderPrimitiveFragment();`
- L53 _public prototype_ `virtual void NotifyRenderStateChanged();`
- L54 _public prototype_ `void UpdateSelection();`
- L55 _public prototype_ `void UpdateLevelInstanceEditingState();`
- L57 _public prototype_ `bool IsDrawnInGame() const;`
- L58 _public prototype_ `bool CheckPSOPrecachingAndBoostPriority(EPSOPrecachePriority NewPSOPrecachePriority = EPSOPrecachePriority::High);`
- L59 _public prototype_ `bool IsPSOPrecaching() const;`
- L60 _public prototype_ `void SetCollisionEnabled(bool bInCollisionEnabled);`
- L61 _public prototype_ `void UpdateVisibility();`
- L62 _public prototype_ `void UpdateTransform();`
- L64 _public prototype_ `EComponentMobility::Type GetMobility() const;`
- L67 _public prototype_ `virtual bool IsRenderStateDirty() const override;`
- L68 _public prototype_ `virtual bool IsRenderStateCreated() const override;`
- L69 _public prototype_ `virtual bool ShouldCreateRenderState() const override;`
- L70 _public prototype_ `virtual bool IsRegistered() const override;`
- L71 _public prototype_ `virtual bool IsUnreachable() const override;`
- L72 _public prototype_ `virtual bool IsStaticMobility() const override;`
- L73 _public prototype_ `virtual bool IsMipStreamingForced() const override;`
- L74 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L75 _public prototype_ `virtual FSceneInterface* GetScene() const override;`
- L76 _public prototype_ `virtual FPrimitiveSceneProxy* GetSceneProxy() const override;`
- L77 _public prototype_ `virtual void MarkRenderStateDirty() override;`
- L78 _public prototype_ `virtual void DestroyRenderState() override;`
- L79 _public prototype_ `virtual void CreateRenderState(FRegisterComponentContext* Context) override;`
- L80 _public prototype_ `virtual FString GetName() const override;`
- L81 _public prototype_ `virtual FString GetFullName() const override;`
- L82 _public prototype_ `virtual FTransform GetTransform() const override;`
- L83 _public prototype_ `virtual const FBoxSphereBounds& GetBounds() const override;`
- L84 _public prototype_ `virtual float GetLastRenderTimeOnScreen() const override;`
- L85 _public prototype_ `virtual void GetPrimitiveStats(FPrimitiveStats& PrimitiveStats) const override;`
- L86 _public prototype_ `virtual UObject* GetUObject() override;`
- L87 _public prototype_ `virtual const UObject* GetUObject() const override;`
- L88 _public prototype_ `virtual void PrecachePSOs() override;`
- L89 _public prototype_ `virtual UObject* GetOwner() const override;`
- L90 _public prototype_ `virtual FString GetOwnerName() const override;`
- L91 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L92 _public prototype_ `virtual FRenderAssetOwnerStreamingState& GetStreamingState() const override;`
- L93 _public prototype_ `virtual ULevel* GetComponentLevel() const override;`
- L94 _public prototype_ `virtual IPrimitiveComponent* GetLODParentPrimitive() const override;`
- L95 _public prototype_ `virtual float GetMinDrawDistance() const override;`
- L96 _public prototype_ `virtual float GetStreamingScale() const override;`
- L97 _public prototype_ `virtual void OnRenderAssetFirstLodChange(const UStreamableRenderAsset* RenderAsset, int32 FirstLodIndex) override;`
- L98 _public prototype_ `virtual UStreamableRenderAsset* GetStreamableNaniteAsset() const override;`
- L99 _public prototype_ `virtual void GetStreamingRenderAssetInfo(FStreamingTextureLevelContext& LevelContext, TArray<FStreamingRenderAssetPrimitiveInfo>& OutStreamingRenderAssets) const override;`
- L101 _public prototype_ `virtual HHitProxy* CreateMeshHitProxy(int32 SectionIndex, int32 MaterialIndex) override;`
- L103 _public prototype_ `virtual HHitProxy* CreatePrimitiveHitProxies(TArray<TRefCountPtr<HHitProxy> >& OutHitProxies) override;`
- L107 _public prototype_ `virtual void DestroyRenderState(FMassDestroyRenderStateContext* Context) override;`
- L108 _public prototype_ `virtual void MarkPrecachePSOsRequired() override;`
- L112 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const = 0;`
- L113 _public prototype_ `virtual int32 GetNumMaterials() const = 0;`
- L114 _public prototype_ `FPrimitiveMaterialPropertyDescriptor GetUsedMaterialPropertyDesc(EShaderPlatform InShaderPlatform) const;`
- L118 _protected prototype_ `virtual void InitializeSceneProxyDescDynamicProperties();`
- L119 _protected prototype_ `virtual void ResetSceneProxyDescUnsupportedProperties();`
- L120 _protected prototype_ `virtual FPrimitiveSceneProxyDesc& GetSceneProxyDesc() = 0;`
- L121 _protected prototype_ `virtual const FPrimitiveSceneProxyDesc& GetSceneProxyDesc() const = 0;`
- L122 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy(ESceneProxyCreationError* OutError) = 0;`
- L123 _protected prototype_ `FPrimitiveSceneDesc BuildSceneDesc();`
- L127 _private prototype_ `bool UsePSOPrecacheFallbackMaterial() const;`
- L131 _public prototype_ `virtual void OnPrecacheFinished(int32 JobSetThatJustCompleted) override;`
- L134 _protected prototype_ `void RequestRecreateRenderStateWhenPSOPrecacheFinished(const FGraphEventArray& PSOPrecacheCompileEvents);`
- L135 _protected prototype_ `void SetupPrecachePSOParams(FPSOPrecacheParams& Params);`
- L136 _protected function_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams)`
- L139 _protected member_ `TArray<FMaterialPSOPrecacheRequestID> MaterialPSOPrecacheRequestIDs;` — Cached array of material PSO requests which can be used to boost the priority
- L141 _protected member_ `std::atomic<int> LatestPSOPrecacheJobSetCompleted = 0;` — Atomic int used to track the last PSO precache events
- L142 _protected member_ `int32 LatestPSOPrecacheJobSet = 0;`
- L144 _protected member_ `std::atomic<bool> bPSOPrecacheCalled = false;` — Helper flag to check if PSOs have been precached already
- L145 _protected member_ `std::atomic<bool> bPSOPrecacheRequired = false;`
- L147 _protected member_ `std::atomic<EPSOPrecachePriority> PSOPrecacheRequestPriority = EPSOPrecachePriority::Medium;` — PSOs requested priority
- L153 _protected member_ `FCustomPrimitiveData CustomPrimitiveData;` — Copied data from fragment as scene proxy decs take a view on this array
- L156 _protected member_ `FPrimitiveSceneDesc SceneDesc;` — Runtime data
- L157 _protected member_ `FPrimitiveSceneInfoData PrimitiveSceneData{};`

### `Source/Runtime/Mass/MassEngine/Private/Mesh/MassRenderStateHelper.h` (Private)


#### enum `ESceneProxyCreationError`  
`enum class ESceneProxyCreationError`  
_L20-25_
- L22 _public enumerator_ `None`
- L23 _public enumerator_ `WaitingPSOs`
- L24 _public enumerator_ `InvalidMesh`

#### struct `FMassRenderStateFragment`  
`struct FMassRenderStateFragment : public FMassFragment`  
_L31-66_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment holding the render state
- L35 _public prototype_ `FMassRenderStateFragment() = default;`
- L36 _public prototype_ `void DestroyRenderStateHelper();`
- L39 _public function_ `template<typename T = FMassRenderStateHelper> const T& GetRenderStateHelper() const requires TIsDerivedFrom<T, FMassRenderStateHelper>::Value`
- L47 _public function_ `template<typename T = FMassRenderStateHelper> T& GetRenderStateHelper() requires TIsDerivedFrom<T, FMassRenderStateHelper>::Value`
- L55 _public function_ `template<typename T, typename... TArgs> T* CreateRenderStateHelper(TArgs&&... InArgs) requires TIsDerivedFrom<T, FMassRenderStateHelper>::Value`
- L64 _private member_ `TSharedPtr<FMassRenderStateHelper> RenderStateHelper = nullptr;`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassRenderStateFragment> final`  
_L69-75_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L72-74_

#### struct `FMassRenderStateHelper`  
`struct FMassRenderStateHelper`  
_L80-123_
- desc: Base helper to handle all the communication to the renderer from Mass
- L84 _public prototype_ `FMassRenderStateHelper(FMassEntityHandle InEntityHandle, TNotNull<FMassEntityManager*> InEntityManager);`
- L85 _public prototype_ `virtual ~FMassRenderStateHelper() = default;`
- L87 _public prototype_ `void MarkRenderStateDirty();`
- L88 _public prototype_ `bool IsRenderStateDirty() const;`
- L89 _public prototype_ `bool IsRenderStateDelayed() const;`
- L90 _public prototype_ `bool IsRenderStateCreated() const;`
- L91 _public prototype_ `virtual bool ShouldCreateRenderState() const;`
- L92 _public prototype_ `virtual void CreateRenderState(FRegisterComponentContext* Context);`
- L93 _public prototype_ `virtual void DestroyRenderState(FMassDestroyRenderStateContext* Context);`
- L94 _public prototype_ `virtual void UpdateVisibility();`
- L95 _public prototype_ `virtual void MarkPrecachePSOsRequired();`
- L96 _public prototype_ `virtual void PrecachePSOs();`
- L98 _public prototype_ `virtual void OnPrecacheFinished(int32 JobSetThatJustCompleted);`
- L101 _public prototype_ `UWorld* GetWorld() const;`
- L102 _public prototype_ `FSceneInterface* GetScene() const;`
- L104 _public prototype_ `FMassEntityManager& GetEntityManager() const;`
- L107 _protected member_ `FMassEntityHandle EntityHandle;`
- L108 _protected member_ `TSharedRef<FMassEntityManager> EntityManager;`
- L110 _protected prototype_ `const FMassRenderStateFragment& GetRenderStateFragment() const;`
- L111 _protected prototype_ `FMassRenderStateFragment& GetMutableRenderStateFragment();`
- L121 _protected member_ `EProxyCreationState ProxyState = EProxyCreationState::None;`
- L122 _protected member_ `bool bRenderStateDirty = false;`

#### enum `FMassRenderStateHelper::EProxyCreationState`  
`enum class EProxyCreationState : uint8`  
_L113-119_
- L115 _public enumerator_ `None` — Constructed/Initialized
- L116 _public enumerator_ `Creating` — Actively creating the proxy
- L117 _public enumerator_ `Created` — Proxy is now created
- L118 _public enumerator_ `Delayed` — Proxy creation delayed (used when PSO precaching is not ready when creating proxy)

#### Free symbols / members of external scopes

- L73 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anon66fca3960103`)

### `Source/Runtime/Mass/MassEngine/Private/Mesh/MassStaticMeshRenderStateHelper.h` (Private)


#### struct `FMassBaseStaticMeshRenderStateHelper`  
`struct FMassBaseStaticMeshRenderStateHelper : public FMassMeshRenderStateHelper, public IStaticMeshComponent`  
_L20-94_
- inherits: `FMassMeshRenderStateHelper,IStaticMeshComponent`
- desc: Base helper to handle all the communication to the renderer from Mass for all type of static meshes
- L23 _public typedef_ `using Super = FMassMeshRenderStateHelper;`
- L25 _public prototype_ `FMassBaseStaticMeshRenderStateHelper(FMassEntityHandle InEntityHandle, TNotNull<FMassEntityManager*> InEntityManager, const FMassRenderPrimitiveFragment& RenderPrimitiveFragment, const FMassOverrideMaterialsFragment* OverrideMaterialsFragment);`
- L26 _public prototype_ `virtual ~FMassBaseStaticMeshRenderStateHelper() override = default;`
- L28 _public prototype_ `const FCollisionResponseContainer& GetCollisionResponseToChannels() const;`
- L29 _public prototype_ `UMaterialInterface* GetNaniteAuditMaterial(int32 MaterialIndex) const;`
- L30 _public prototype_ `const Nanite::FResources* GetNaniteResources() const;`
- L31 _public prototype_ `bool HasValidNaniteData() const;`
- L32 _public prototype_ `bool UseNaniteOverrideMaterials(bool bDoingMaterialAudit) const;`
- L33 _public prototype_ `bool ShouldCreateNaniteProxy(Nanite::FMaterialAudit* OutNaniteMaterials) const;`
- L34 _public prototype_ `virtual UObject const* AdditionalStatObject() const override;`
- L35 _public prototype_ `bool IsReverseCulling() const;`
- L36 _public prototype_ `bool IsDisallowNanite() const;`
- L37 _public prototype_ `bool IsForceDisableNanite() const;`
- L38 _public prototype_ `bool IsForceNaniteForMasked() const;`
- L39 _public prototype_ `int32 GetForcedLodModel() const;`
- L40 _public prototype_ `bool GetOverrideMinLOD() const;`
- L41 _public prototype_ `int32 GetMinLOD() const;`
- L42 _public prototype_ `bool GetForceNaniteForMasked() const;`
- L43 _public prototype_ `int32 GetWorldPositionOffsetDisableDistance() const;`
- L44 _public prototype_ `float GetNanitePixelProgrammableDistance() const;`
- L45 _public prototype_ `bool EvaluateWorldPositionOffsetInRayTracing() const;`
- L47 _public prototype_ `bool IsDisplayNaniteFallbackMesh() const;`
- L52 _public function_ `virtual void OnMeshRebuild(bool bRenderDataChanged) override`
- L53 _public function_ `virtual void PreStaticMeshCompilation() override`
- L54 _public prototype_ `virtual void PostStaticMeshCompilation() override;`
- L56 _public prototype_ `virtual UStaticMesh* GetStaticMesh() const override;`
- L57 _public prototype_ `virtual IPrimitiveComponent* GetPrimitiveComponentInterface() override;`
- L61 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L62 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L63 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L65 _public prototype_ `virtual void NotifyRenderStateChanged() override;`
- L71 _protected prototype_ `virtual void ResetSceneProxyDescUnsupportedProperties() override;`
- L72 _protected prototype_ `virtual void InitializeSceneProxyDescDynamicProperties() override;`
- L73 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy(ESceneProxyCreationError* OutError = nullptr) override;`
- L77 _protected prototype_ `virtual UMaterialInterface* GetOverlayMaterial() const override;`
- L78 _protected prototype_ `virtual const TArray<TObjectPtr<UMaterialInterface>>& GetComponentMaterialSlotsOverlayMaterial() const override;`
- L79 _protected prototype_ `virtual void GetDefaultMaterialSlotsOverlayMaterial(TArray<TObjectPtr<UMaterialInterface>>& OutMaterialSlotOverlayMaterials) const override;`
- L82 _protected prototype_ `virtual FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() = 0;`
- L83 _protected prototype_ `virtual const FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() const = 0;`
- L84 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateStaticMeshSceneProxy(const Nanite::FMaterialAudit& NaniteMaterials, bool bCreateNanite);`
- L85 _protected prototype_ `UMaterialInterface* GetMaterial(int32 MaterialIndex, bool bDoingNaniteMaterialAudit) const;`
- L87 _protected prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams);`

#### struct `FMassStaticMeshRenderStateHelper`  
`struct FMassStaticMeshRenderStateHelper : public FMassBaseStaticMeshRenderStateHelper`  
_L99-121_
- inherits: `FMassBaseStaticMeshRenderStateHelper`
- desc: Helper to handle all the communication to the renderer from Mass for all type of static meshes
- L102 _public typedef_ `using Super = FMassBaseStaticMeshRenderStateHelper;`
- L104 _public prototype_ `FMassStaticMeshRenderStateHelper(FMassEntityHandle InEntityHandle, TNotNull<FMassEntityManager*> InEntityManager, const FMassRenderPrimitiveFragment& RenderPrimitiveFragment, const FMassOverrideMaterialsFragment* OverrideMaterialsFragment, const FMassRenderStaticMeshFragment& RenderStaticMeshFragment);`
- L105 _public prototype_ `virtual ~FMassStaticMeshRenderStateHelper() = default;`
- L108 _public prototype_ `const FMassRenderStaticMeshFragment& GetRenderStaticMeshFragment() const;` — StaticMesh Fragments helpers
- L109 _public prototype_ `FMassRenderStaticMeshFragment& GetMutableRenderStaticMeshFragment();`
- L113 _protected prototype_ `virtual FPrimitiveSceneProxyDesc& GetSceneProxyDesc() override;`
- L114 _protected prototype_ `virtual const FPrimitiveSceneProxyDesc& GetSceneProxyDesc() const override;`
- L118 _protected prototype_ `virtual FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() override;`
- L119 _protected prototype_ `virtual const FStaticMeshSceneProxyDesc& GetStaticMeshSceneProxyDesc() const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Nanite`

### `Source/Runtime/Mass/MassEngine/Private/RigidBody/MassPhysicsProcessors.h` (Private)


#### class `UMassPhysicsBodyInstancesBatcher`  
`class UMassPhysicsBodyInstancesBatcher : public UMassProcessor`  
_L17-30_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- desc: Processor responsible for batching individual BodyInstance owner into a single initialization request.
- L22 _public prototype_ `explicit UMassPhysicsBodyInstancesBatcher(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L25 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L26 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& ExecutionContext) override;`
- L28 _protected member_ `FMassArchetypeHandle BatchInitializationRequestArchetype;`
- L29 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassPhysicsBodyInstancesBatchInitializer`  
`class UMassPhysicsBodyInstancesBatchInitializer : public UMassProcessor`  
_L36-49_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- desc: Processor responsible for initializing batches of FBodyInstances.
- L41 _public prototype_ `explicit UMassPhysicsBodyInstancesBatchInitializer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L45 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L46 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& ExecutionContext) override;`
- L48 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassPhysicsBodyInstanceReInitializer`  
`class UMassPhysicsBodyInstanceReInitializer : public UMassObserverProcessor`  
_L55-68_
- reflection: `UCLASS()`
- inherits: `UMassObserverProcessor`
- desc: Processor responsible to monitor changes to body instances configurations to trigger a re-initialization of the instance.
- L60 _public prototype_ `explicit UMassPhysicsBodyInstanceReInitializer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L64 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L65 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& ExecutionContext) override;`
- L67 _protected member_ `FMassEntityQuery EntityQuery;`

### `Source/Runtime/Mass/MassEngine/Public/AI/MassEngineNavigationFragments.h` (Public)


#### struct `FMassNavigationRelevantParameters`  
`struct FMassNavigationRelevantParameters : public FMassConstSharedFragment`  
_L15-22_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Shared Fragment holding the properties defining how a given entity should affect navigation data
- L21 _public member_ `bool bFillCollisionUnderneathForNavData = false;` — `UPROPERTY()` — If set, navmesh will not be generated under the surface of the geometry

#### struct `FMassNavigationEvaluatedTag`  
`struct FMassNavigationEvaluatedTag : public FMassTag`  
_L30-33_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag indicating that the entity has been evaluated for navigation relevance. Added to all entities after initial evaluation regardless of relevance outcome, so that non-relevant entities are not re-evaluated every frame.

#### struct `FMassNavigationRelevantFragment`  
`struct FMassNavigationRelevantFragment : public FMassFragment`  
_L40-52_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment holding the registration handle to the navigation element created from a Mass entity. The fragment is added to indicate that a Mass entity is relevant to the AI navigation system.
- L44 _public prototype_ `FMassNavigationRelevantFragment() = default;`
- L45 _public function_ `explicit FMassNavigationRelevantFragment(const FNavigationElementHandle Handle) : Handle(Handle)`
- L51 _public member_ `FNavigationElementHandle Handle;` — Handle to the Navigation element created and registered for the entity

### `Source/Runtime/Mass/MassEngine/Public/AI/MassEngineNavigationProcessors.h` (Public)


#### class `UMassNavigationElementProcessor`  
`class UMassNavigationElementProcessor : public UMassProcessor`  
_L19-31_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- desc: Processor responsible for registering new NavigationElement representing Mass entities that are relevant to the AI navigation system and adding the FMassNavigationRelevantFragment fragment to the entities.
- L24 _public prototype_ `UMassNavigationElementProcessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L27 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L28 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L30 _protected member_ `FMassEntityQuery NewRelevantEntityQuery;`

#### class `UMassDirtyNavigationRelevantUpdateProcessor`  
`class UMassDirtyNavigationRelevantUpdateProcessor : public UMassSignalProcessorBase`  
_L41-52_
- reflection: `UCLASS()`
- inherits: `UMassSignalProcessorBase`
- desc: Processor responsible for updating NavigationElement representing Mass entities that are relevant to the AI navigation system when one of its core property gets modified (e.g., transform, mesh, navigation bounds, etc.) This processor subscribes to the following signals to perform an update: - UE::Mass::Signals::TransformChanged - UE::Mass::Signals::MeshChanged
- L46 _public prototype_ `UMassDirtyNavigationRelevantUpdateProcessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L49 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L50 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L51 _protected prototype_ `virtual void SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& EntitySignals) override;`

#### class `UMassNavigationRelevantMassDeinitializer`  
`class UMassNavigationRelevantMassDeinitializer : public UMassObserverProcessor`  
_L59-72_
- reflection: `UCLASS()`
- inherits: `UMassObserverProcessor`
- desc: Processor responsible for unregistering the NavigationElements when Mass entities are destroyed or no longer relevant to the AI navigation system.
- L64 _public prototype_ `UMassNavigationRelevantMassDeinitializer();`
- L67 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L68 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L70 _protected member_ `FMassEntityQuery EntityQuery;`
- L71 _protected member_ `FMassEntityQuery NonRelevantEntityQuery;`

### `Source/Runtime/Mass/MassEngine/Public/IMassEngineModule.h` (Public)


#### class `IMassEngineModule`  
`class IMassEngineModule : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L23 _public function_ `static inline IMassEngineModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Runtime/Mass/MassEngine/Public/MassEngineTypes.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassEngine, Warning, All);`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mass` (scope `UE`)
- L10 _namespace_ `namespace Signals` (scope `UE::Mass`)
- L12 _variable_ `const FName TransformChanged = FName(TEXT("Tran` (scope `UE::Mass::Signals`)
- L13 _variable_ `const FName MeshChanged = FName(TEXT("Mesh` (scope `UE::Mass::Signals`)
- L14 _variable_ `const FName MeshVisualPropertyChanged = FName(TEXT("Mesh` (scope `UE::Mass::Signals`)
- L15 _variable_ `const FName RenderStateDirty = FName(TEXT("Rend` (scope `UE::Mass::Signals`)
- L18 _variable_ `const FName SelectionChanged = FName(TEXT("Sele` (scope `UE::Mass::Signals`)
- L19 _variable_ `const FName LevelEditingStateChanged = FName(TEXT("Leve` (scope `UE::Mass::Signals`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Mass` (scope `UE`)
- L23 _namespace_ `namespace ProcessorGroupNames` (scope `UE::Mass`)
- L25 _variable_ `const FName SetupRenderState = FName(TEXT("Setu` (scope `UE::Mass::ProcessorGroupNames`)
- L26 _variable_ `const FName CreateRenderState = FName(TEXT("Crea` (scope `UE::Mass::ProcessorGroupNames`)
- L28 _variable_ `const FName SetupBatchedInitializations = FName(TEXT("Setu` (scope `UE::Mass::ProcessorGroupNames`)
- L29 _variable_ `const FName ProcessBatchedInitializations = FName(TEXT("Proc` (scope `UE::Mass::ProcessorGroupNames`)

### `Source/Runtime/Mass/MassEngine/Public/Mesh/MassEngineMeshFragments.h` (Public)


#### struct `FMassStaticMeshFragment`  
`struct FMassStaticMeshFragment : public FMassConstSharedFragment`  
_L26-35_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Const shared fragment holding a pointer to the static mesh associated to the entity
- L30 _public prototype_ `FMassStaticMeshFragment() = default;`
- L31 _public prototype_ `explicit FMassStaticMeshFragment(TNotNull<const UStaticMesh*> InMesh);`
- L34 _public member_ `TWeakObjectPtr<const UStaticMesh> Mesh;` — `UPROPERTY(VisibleAnywhere, Category=Debug)`

#### struct `FMassVisualizationMeshFragment`  
`struct FMassVisualizationMeshFragment : public FMassConstSharedFragment`  
_L41-75_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Const shared fragment holding all the visualization flags for a mesh
- L46 _public member_ `int64 CustomDepthStencilValue = 0;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L48 _public member_ `int32 TranslucencySortPriority = 0;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L50 _public member_ `FLightingChannels LightingChannels;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L52 _public member_ `uint8 HiddenInGame : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L54 _public member_ `uint8 CastShadow : 1 = true;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L56 _public member_ `uint8 CastShadowAsTwoSided : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L58 _public member_ `uint8 CastHiddenShadow : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L60 _public member_ `uint8 AffectDynamicIndirectLighting : 1 = true;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L62 _public member_ `uint8 AffectIndirectLightingWhileHidden : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L64 _public member_ `uint8 ReceivesDecals : 1 = true;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L66 _public member_ `uint8 NeverDistanceCull : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L68 _public member_ `uint8 CastFarShadow : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L70 _public member_ `uint8 CastInsetShadow : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L72 _public member_ `uint8 CastContactShadow : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L74 _public member_ `uint8 RenderCustomDepth : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`

#### struct `FMassEditorVisualizationMeshFragment`  
`struct FMassEditorVisualizationMeshFragment : public FMassConstSharedFragment`  
_L81-93_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Const shared fragment holding the editor visualization flags for a mesh
- L87 _public member_ `uint8 bShouldRenderSelected : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L89 _public member_ `uint8 bHiddenInEditor : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`
- L91 _public member_ `uint8 bLevelInstanceEditingState : 1 = false;` — `UPROPERTY(VisibleAnywhere, Category = Mesh)`

#### struct `FMassOverrideMaterialsFragment`  
`struct FMassOverrideMaterialsFragment : public FMassConstSharedFragment`  
_L99-105_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Const shared fragment holding the list of material override for a mesh
- L104 _public member_ `TArray<TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(VisibleAnywhere, Category = Debug)`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassVisualizationMeshFragment> final`  
_L108-114_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L111-113_

#### struct `FMassRenderPrimitiveFragment`  
`struct FMassRenderPrimitiveFragment : public FMassFragment`  
_L120-138_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment holding rendering information of all the different primitives
- L125 _public member_ `FBoxSphereBounds LocalBounds = {};` — `UPROPERTY(Transient, VisibleAnywhere, Category = Debug)`
- L127 _public member_ `FBoxSphereBounds WorldBounds = {};` — `UPROPERTY(Transient, VisibleAnywhere, Category = Debug)` — Maybe not here...
- L129 _public member_ `FCustomPrimitiveData CustomPrimitiveData;` — `UPROPERTY(Transient, VisibleAnywhere, Category = Debug)`
- L133 _public member_ `uint8 bIsVisible : 1 = true;` — `UPROPERTY(Transient, VisibleAnywhere, Category = Debug)`
- L135 _public member_ `uint8 bRasterizeAsFilledConvexVolume : 1 = false;` — `UPROPERTY(Transient, VisibleAnywhere, Category = Debug)`
- L137 _public member_ `TArray<TObjectPtr<URuntimeVirtualTexture>> RuntimeVirtualTextures;` — `UPROPERTY(Transient, VisibleAnywhere, Category = Debug)`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassRenderPrimitiveFragment> final`  
_L141-147_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L144-146_

#### struct `FMassRenderStaticMeshFragment`  
`struct FMassRenderStaticMeshFragment : public FMassFragment`  
_L154-165_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment holding the rendering information for a static mesh
- L158 _public prototype_ `FMassRenderStaticMeshFragment();`
- L159 _public prototype_ `explicit FMassRenderStaticMeshFragment(const TSharedRef<FStaticMeshSceneProxyDesc>& InStaticMeshSceneProxyDesc);`
- L161 _public prototype_ `UStaticMesh* GetStaticMesh();`
- L162 _public prototype_ `const UStaticMesh* GetStaticMesh() const;`
- L164 _public member_ `TSharedPtr<FStaticMeshSceneProxyDesc> StaticMeshSceneProxyDesc = nullptr;`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassRenderStaticMeshFragment> final`  
_L168-174_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L171-173_

#### struct `HTypeElementHandleHitProxy`  
`struct HTypeElementHandleHitProxy : public HHitProxy`  
_L180-213_
- inherits: `HHitProxy`
- desc: Hit proxy to use along with the FMassTypeElementFragment
- L182 _public prototype_ `DECLARE_HIT_PROXY();`
- L184 _public function_ `HTypeElementHandleHitProxy(const FTypedElementHandle& InElementHandle) : HHitProxy(HPP_World), ElementHandle(InElementHandle)`
- L190 _public function_ `HTypeElementHandleHitProxy(const FTypedElementHandle& InElementHandle, int32 InMaterialIndex, int32 InSectionIndex) : HHitProxy(HPP_World), ElementHandle(InElementHandle), SectionIndex(InSectionIndex), MaterialIndex(InMaterialIndex)`
- L198 _public member_ `FTypedElementHandle ElementHandle;`
- L199 _public member_ `int32 SectionIndex = -1;`
- L200 _public member_ `int32 MaterialIndex = -1;`
- L202 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override`
- L207 _public function_ `virtual FTypedElementHandle GetElementHandle() const override`
- L212 _public prototype_ `virtual EMouseCursor::Type GetMouseCursor() override;`

#### struct `FMassRenderISMFragment`  
`struct FMassRenderISMFragment : public FMassFragment`  
_L220-239_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment holding rendering information for a instanced static mesh
- L224 _public prototype_ `FMassRenderISMFragment();`
- L225 _public prototype_ `explicit FMassRenderISMFragment(const TSharedRef<FInstancedStaticMeshSceneProxyDesc>& InInstancedStaticMeshSceneProxyDesc);`
- L227 _public prototype_ `UStaticMesh* GetStaticMesh();`
- L228 _public prototype_ `const UStaticMesh* GetStaticMesh() const;`
- L231 _public member_ `TSparseArray<TRefCountPtr<HTypeElementHandleHitProxy>> PerInstanceHitProxy;`
- L233 _public member_ `TSparseArray<FInstancedStaticMeshInstanceData> PerInstanceSMData;`
- L234 _public member_ `TArray<float> PerInstanceSMCustomData;`
- L235 _public member_ `TArray<FInstancedStaticMeshRandomSeed> AdditionalRandomSeeds;`
- L237 _public member_ `TSharedPtr<FInstancedStaticMeshSceneProxyDesc> InstancedStaticMeshSceneProxyDesc = nullptr;`
- L238 _public member_ `int32 InstancingRandomSeed = 0;`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassRenderISMFragment> final`  
_L242-248_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L245-247_

#### struct `FMassRenderISMLinkFragment`  
`struct FMassRenderISMLinkFragment : public FMassEntityLinkFragment`  
_L255-258_
- reflection: `USTRUCT()`
- inherits: `FMassEntityLinkFragment`
- desc: Fragment holding the instanced static mesh entity for the instances

#### struct `FMassRenderISMInstanceFragment`  
`struct FMassRenderISMInstanceFragment : public FMassFragment`  
_L264-274_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment holding the index for the instances of an instanced static mesh
- L269 _public member_ `int32 InstanceIndex = -1;` — `UPROPERTY(Transient, VisibleAnywhere, Category = Debug)`
- L272 _public member_ `int32 HitProxyIndex = -1;` — `UPROPERTY(Transient, VisibleAnywhere, Category = Debug)`

#### struct `FMassTypeElementFragment`  
`struct FMassTypeElementFragment : public FMassFragment`  
_L280-285_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment hold the type element for selection
- L284 _public member_ `FTypedElementHandle TypeElementHandle;`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassTypeElementFragment> final`  
_L288-294_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L291-293_

#### struct `FMassSceneProxyCreatedTag`  
`struct FMassSceneProxyCreatedTag : public FMassTag`  
_L300-303_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag to tell if the SceneProxy was created

#### struct `FMassRenderISMCandidateTag`  
`struct FMassRenderISMCandidateTag : public FMassTag`  
_L309-312_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag to tell if the static mesh is a candidate for instantiation

#### struct `FMassISMGroupingFragment`  
`struct FMassISMGroupingFragment : public FMassConstSharedFragment`  
_L321-332_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Optional const shared fragment for ISM grouping scoping. When present, its GroupId is included in the ISM hash, ensuring entities with different GroupIds get separate ISM entities even if they share the same mesh/vis flags. Use cases: per-cell scoping, per-level scoping, etc.
- L325 _public prototype_ `FMassISMGroupingFragment() = default;`
- L326 _public function_ `explicit FMassISMGroupingFragment(const FGuid& InGroupId) : GroupId(InGroupId)`
- L331 _public member_ `FGuid GroupId;` — `UPROPERTY(VisibleAnywhere, Category = Debug)`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MASSENGINE_API`
- L112 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anond7cb4a830103`)
- L145 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anond7cb4a830203`)
- L172 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anond7cb4a830303`)
- L246 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anond7cb4a830403`)
- L292 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anond7cb4a830503`)

### `Source/Runtime/Mass/MassEngine/Public/Mesh/MassEngineMeshUtils.h` (Public)


#### enum `UE::MassEngine::Mesh::EBoundsType`  
`enum class EBoundsType`  
_L49-54_
- L51 _public enumerator_ `LocalBounds`
- L52 _public enumerator_ `WorldBounds`
- L53 _public enumerator_ `NavigationBounds`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MASSENGINE_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MassEngine` (scope `UE`)
- L21 _namespace_ `namespace Mesh` (scope `UE::MassEngine`)
- L29 _prototype_ `void InitializePrimitiveFragmentsFromComponent(TNotNull<const UActorComponent*> Component, FTransformFragment& TransformFragment, FMassRenderPrimitiveFragment& RenderPrimitiveFragment);` (scope `UE::MassEngine::Mesh`) — Initializes the transform, primitive fragments from a UActorComponent @param Component to initialize the fragments from @param TransformFragment to set up @param RenderPrimitiveFragment to set up
- L38 _prototype_ `void InitializeStaticMeshFragmentsFromComponent(TNotNull<const UActorComponent*> Component, FTransformFragment& TransformFragment, FMassRenderPrimitiveFragment& RenderPrimitiveFragment, FMassRenderStaticMeshFragment& RenderStaticMeshFragment);` (scope `UE::MassEngine::Mesh`) — Initializes the render transform, primitive, render static mesh fragments from a UActorComponent @param Component to initialize the fragments from @param TransformFragment the transform fragment to set up @param RenderPrimitiveFragment the render primitive fragment to set up @param RenderStaticMeshFragment the render static mesh fragment to set up
- L47 _prototype_ `void InitializeISMFragmentsFromComponent(TNotNull<const UActorComponent*> Component, FTransformFragment& TransformFragment, FMassRenderPrimitiveFragment& RenderPrimitiveFragment, FMassRenderISMFragment& RenderISMFragment);` (scope `UE::MassEngine::Mesh`) — Initializes the render transform, primitive, render instanced static mesh fragments from a UActorComponent @param Component to initialize the fragments from @param TransformFragment the transform fragment to set up @param RenderPrimitiveFragment the render primitive fragment to set up @param RenderISMFragment the render instanced static mesh fragment to set up
- L63 _prototype_ `FBoxSphereBounds CalculateInstancedStaticMeshBounds(const FTransformFragment& TransformFragment, const FMassRenderISMFragment& RenderISMFragment, const EBoundsType BoundsType);` (scope `UE::MassEngine::Mesh`) — Calculates the bounds of the instanced static mesh from the mass fragments @param TransformFragment Transform to use as a root of the ISM @param RenderISMFragment List of instances transform of the ISM @param BoundsType Bounds type to calculate @return
- L71 _prototype_ `void InitializePrimitiveSceneProxyDescFromEditorFragment(const FMassEditorVisualizationMeshFragment& EditorMeshFragment, FPrimitiveSceneProxyDesc& PrimitiveSceneProxyDesc);` (scope `UE::MassEngine::Mesh`) — Initialize the scene proxy desc from the editor mesh fragments @param EditorMeshFragment fragment describing the editor mesh parameters @param PrimitiveSceneProxyDesc scene proxy desc to initialize
- L81 _prototype_ `void InitializeStaticMeshSceneProxyDescFromFragment(const FMassStaticMeshFragment& StaticMeshFragment, const FMassVisualizationMeshFragment& MeshFragment, const FTransformFragment& TransformFragment, FStaticMeshSceneProxyDesc& StaticMeshSceneProxyDesc);` (scope `UE::MassEngine::Mesh`) — Initialize the static mesh scene proxy desc from mass fragments @param StaticMeshFragment fragment describing the static mesh @param MeshFragment fragment describing the mesh parameters @param TransformFragment fragment specifying the transform @param StaticMeshSceneProxyDesc scene proxy desc to initialize
- L90 _prototype_ `void InitializeInstanceStaticMeshSceneProxyDescFromFragment(const FMassStaticMeshFragment& StaticMeshFragment, const FMassVisualizationMeshFragment& MeshFragment, const FTransformFragment& TransformFragment, FInstancedStaticMeshSceneProxyDesc& ISMSceneProxyDesc);` (scope `UE::MassEngine::Mesh`) — Initialize the instanced static mesh scene proxy desc from mass fragments @param StaticMeshFragment fragment describing the static mesh @param MeshFragment fragment describing the mesh parameters @param TransformFragment fragment specifying the transform @param ISMSceneProxyDesc scene proxy desc to initialize

### `Source/Runtime/Mass/MassEngine/Public/Mesh/MassEngineRenderISMProcessors.h` (Public)


#### class `UMassInstantiateStaticMeshAndCreateISMRenderStateProcessor`  
`class UMassInstantiateStaticMeshAndCreateISMRenderStateProcessor : public UMassBaseStaticMeshSetupRenderStateProcessor`  
_L19-38_
- reflection: `UCLASS()`
- inherits: `UMassBaseStaticMeshSetupRenderStateProcessor`
- desc: Processor responsible for creating instanced static mesh entity and setting up its render state for the renderer
- L24 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L25 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& ExecutionContext) override;`
- L27 _protected member_ `FMassElementBitSet ISMEntityComposition;`
- L28 _protected member_ `FMassArchetypeHandle ISMEntityArchetype;`
- L29 _protected member_ `FMassElementBitSet ISMEntityCompositionWithMaterialOverrides;`
- L30 _protected member_ `FMassArchetypeHandle ISMEntityArchetypeWithMaterialOverrides;`
- L33 _protected member_ `FMassElementBitSet ISMEntityCompositionWithEditorMesh;`
- L34 _protected member_ `FMassArchetypeHandle ISMEntityArchetypeWithEditorMesh;`
- L35 _protected member_ `FMassElementBitSet ISMEntityCompositionWithMaterialOverridesAndEditorMesh;`
- L36 _protected member_ `FMassArchetypeHandle ISMEntityArchetypeWithMaterialOverridesAndEditorMesh;`

#### class `UMassDirtyRenderISMInstanceProcessor`  
`class UMassDirtyRenderISMInstanceProcessor : public UMassSignalProcessorBase`  
_L47-58_
- reflection: `UCLASS()`
- inherits: `UMassSignalProcessorBase`
- desc: Processor responsible for notifying the linked instanced static mesh entity to update the render proxy This processor listen to the following signals on the instances entities - UE::Mass::Signals::TransformChanged - UE::Mass::Signals::SelectionChanged
- L52 _public prototype_ `explicit UMassDirtyRenderISMInstanceProcessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L55 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L56 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L57 _protected prototype_ `virtual void SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& EntitySignals) override;`

#### class `UMassISMDestroyRenderStateProcessor`  
`class UMassISMDestroyRenderStateProcessor : public UMassBaseStaticMeshDestroyRenderStateProcessor`  
_L64-74_
- reflection: `UCLASS()`
- inherits: `UMassBaseStaticMeshDestroyRenderStateProcessor`
- desc: Processor responsible for removing instances when the required fragments are being removed
- L69 _public prototype_ `UMassISMDestroyRenderStateProcessor();`
- L72 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L73 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

### `Source/Runtime/Mass/MassEngine/Public/Mesh/MassEngineRenderStateProcessors.h` (Public)


#### class `UMassCreateRenderStateProcessor`  
`class UMassCreateRenderStateProcessor : public UMassProcessor`  
_L17-29_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- desc: Processor responsible for creating the renderer states
- L22 _public prototype_ `UMassCreateRenderStateProcessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L25 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L26 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& ExecutionContext) override;`
- L28 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassRenderStateDirtyUpdateProcessor`  
`class UMassRenderStateDirtyUpdateProcessor : public UMassSignalProcessorBase`  
_L42-53_
- reflection: `UCLASS()`
- inherits: `UMassSignalProcessorBase`
- desc: Processor responsible for updating or recreating the render state when dirtied Listens to the following signals: - UE::Mass::Signals::TransformChanged - UE::Mass::Signals::MeshVisualPropertyChanged - UE::Mass::Signals::MeshChanged - UE::Mass::Signals::SelectionChanged - UE::Mass::Signals::LevelEditingStateChanged - UE::Mass::Signals::RenderStateDirty
- L47 _public prototype_ `UMassRenderStateDirtyUpdateProcessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L50 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L51 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L52 _protected prototype_ `virtual void SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& EntitySignals) override;`

#### class `UMassDestroyRenderStateProcessor`  
`class UMassDestroyRenderStateProcessor : public UMassObserverProcessor`  
_L59-71_
- reflection: `UCLASS()`
- inherits: `UMassObserverProcessor`
- desc: Processor responsible for destroying the render states
- L64 _public prototype_ `UMassDestroyRenderStateProcessor();`
- L67 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L68 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L70 _protected member_ `FMassEntityQuery EntityQuery;`

### `Source/Runtime/Mass/MassEngine/Public/Mesh/MassEngineRenderStaticMeshProcessors.h` (Public)


#### class `UMassBaseStaticMeshSetupRenderStateProcessor`  
`class UMassBaseStaticMeshSetupRenderStateProcessor : public UMassProcessor`  
_L17-28_
- reflection: `UCLASS(Abstract)`
- inherits: `UMassProcessor`
- desc: Base processor responsible for setting up the static mesh render state for the renderer
- L22 _public prototype_ `UMassBaseStaticMeshSetupRenderStateProcessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L25 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L27 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassStaticMeshSetupRenderStateProcessor`  
`class UMassStaticMeshSetupRenderStateProcessor : public UMassBaseStaticMeshSetupRenderStateProcessor`  
_L34-41_
- reflection: `UCLASS()`
- inherits: `UMassBaseStaticMeshSetupRenderStateProcessor`
- desc: Processor responsible for setting up the static mesh render state for the renderer
- L39 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L40 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& ExecutionContext) override;`

#### class `UMassStaticMeshUpdateRenderStateProcessor`  
`class UMassStaticMeshUpdateRenderStateProcessor : public UMassSignalProcessorBase`  
_L53-64_
- reflection: `UCLASS()`
- inherits: `UMassSignalProcessorBase`
- desc: Processor responsible for updating the static mesh render state when dirtied Listening the following signals on the entity - UE::Mass::Signals::TransformChanged - UE::Mass::Signals::MeshVisualPropertyChanged - UE::Mass::Signals::MeshChanged - UE::Mass::Signals::SelectionChanged - UE::Mass::Signals::LevelEditingStateChanged
- L58 _public prototype_ `UMassStaticMeshUpdateRenderStateProcessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L61 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L62 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L63 _protected prototype_ `virtual void SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& EntitySignals) override;`

#### class `UMassBaseStaticMeshDestroyRenderStateProcessor`  
`class UMassBaseStaticMeshDestroyRenderStateProcessor : public UMassObserverProcessor`  
_L71-82_
- reflection: `UCLASS(Abstract)`
- inherits: `UMassObserverProcessor`
- desc: Base processor responsible for removing the common static mesh render state fragments when the required fragments are being removed
- L76 _public prototype_ `UMassBaseStaticMeshDestroyRenderStateProcessor();`
- L78 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager);`
- L81 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassStaticMeshDestroyRenderStateProcessor`  
`class UMassStaticMeshDestroyRenderStateProcessor : public UMassBaseStaticMeshDestroyRenderStateProcessor`  
_L88-95_
- reflection: `UCLASS()`
- inherits: `UMassBaseStaticMeshDestroyRenderStateProcessor`
- desc: Processor responsible for removing the static mesh render state fragments when the required fragments are being removed
- L93 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L94 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

### `Source/Runtime/Mass/MassEngine/Public/Physics/MassEnginePhysicsFragments.h` (Public)


#### struct `FMassPhysicsCollisionSettingsFragment`  
`struct FMassPhysicsCollisionSettingsFragment : public FMassConstSharedFragment`  
_L21-30_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Fragment holding data related to physics collision setup
- L26 _public member_ `TEnumAsByte<ECollisionEnabled::Type> CollisionType = ECollisionEnabled::NoCollision;` — `UPROPERTY(VisibleAnywhere, Category = Physics)`
- L29 _public member_ `FCollisionResponseContainer CollisionResponse;` — `UPROPERTY(VisibleAnywhere, Category = Physics)`

#### struct `FMassPhysicsBodyInstanceFragment`  
`struct FMassPhysicsBodyInstanceFragment : public FMassFragment`  
_L36-60_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment holding data related to a specific rigid body instance
- L40 _public prototype_ `FMassPhysicsBodyInstanceFragment() = default;`
- L42 _public function_ `explicit FMassPhysicsBodyInstanceFragment(const TSharedRef<FBodyInstance>& BodyInstance) : BodyInstance(BodyInstance)`
- L50 _public member_ `TWeakObjectPtr<UObject> BodyInstanceOwnerObject;` — `UPROPERTY(VisibleAnywhere, Category = Physics)` — Weak object pointer to the owning component. Validate before using BodyInstance and ChaosUserDefinedEntity, as those shared pointers may outlive the owner and become semantically stale.
- L53 _public member_ `TSharedPtr<FBodyInstance> BodyInstance = nullptr;` — Shared pointer to the BodyInstance created by the owning component.
- L59 _public member_ `TSharedPtr<FChaosUserDefinedEntity> ChaosUserDefinedEntity = nullptr;` — Optional payload to associate with the created PhysicsObject after BodyInstance initialization (i.e., FWritePhysicsObjectInterface::SetUserDefinedEntity).

#### struct `TMassFragmentTraits`  
`template <> struct TMassFragmentTraits<FMassPhysicsBodyInstanceFragment> final`  
_L63-69_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L66-68_

#### struct `FMassPhysicsDynamicBodyTag`  
`struct FMassPhysicsDynamicBodyTag : public FMassTag`  
_L76-79_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag that indicates that a given body should be initialized as dynamic with the possibility to be simulated in the physics scene @see FMassPhysicsSimulatedBodyTag

#### struct `FMassPhysicsSimulatedBodyTag`  
`struct FMassPhysicsSimulatedBodyTag : public FMassTag`  
_L85-88_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag that indicates that a given body should be simulated in the physics scene

#### struct `FMassPhysicsBodyInstanceInitializedTag`  
`struct FMassPhysicsBodyInstanceInitializedTag : public FMassTag`  
_L96-99_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag added after a body instance has been batched for initialization. Entities with this tag are excluded from further batching. Removed by UMassPhysicsBodyInstanceReInitializer to re-trigger the initialization cycle.

#### struct `FMassPhysicsBodyInstancesInitializationRequestFragment`  
`struct FMassPhysicsBodyInstancesInitializationRequestFragment : public FMassFragment`  
_L102-138_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L108 _public member_ `TWeakObjectPtr<const UStaticMesh> StaticMesh = nullptr;` — `UPROPERTY(Transient, VisibleAnywhere, Category = Physics)` — Mandatory weak pointer to the mesh used by all instances
- L112 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY(Transient, VisibleAnywhere, Category = Physics)` — Mandatory list of transforms that should match the number of body instances
- L115 _public member_ `TArray<TSharedPtr<FBodyInstance>> InstanceBodies;` — Mandatory list of body instances to initialize
- L121 _public member_ `TObjectPtr<UPrimitiveComponent> PrimitiveComponent;` — `UPROPERTY(Transient, VisibleAnywhere, Category = Physics)` — Optional interface pointer that will be provided to the BodyInstance initialization
- L127 _public member_ `TWeakInterfacePtr<IPhysicsBodyInstanceOwner> BodyInstanceOwner;` — Optional interface pointer that will be provided to the BodyInstance initialization. Stored as a TWeakInterfacePtr; check IsStale() before use.
- L133 _public member_ `TArray<TSharedPtr<FChaosUserDefinedEntity>> ChaosUserDefinedEntity;` — Optional list of user data payloads to associate to the created PhysicsObjects after the body instances get initialized. @note It is possible to provide a single payload for owners relying on body indices (i.e., InstanceBodyIndex).
- L137 _public member_ `bool bDynamic = false;` — `UPROPERTY(Transient, VisibleAnywhere, Category = Physics)` — Whether the instances are simulated/dynamic physics objects

#### struct `TMassFragmentTraits`  
`template <> struct TMassFragmentTraits<FMassPhysicsBodyInstancesInitializationRequestFragment> final`  
_L141-147_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L144-146_

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MASSENGINE_API`
- L67 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anon4421152f0103`)
- L145 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anon4421152f0203`)
