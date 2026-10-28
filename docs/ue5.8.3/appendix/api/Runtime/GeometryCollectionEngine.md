# Runtime / GeometryCollectionEngine

- module root: `Source/Runtime/Experimental/GeometryCollectionEngine`
- headers: 39; symbols: 1907
- symbol kinds: class=44, delegate=14, enum=18, enumerator=104, function=215, macro=5, member=712, namespace=12, prototype=714, struct=57, typedef=12
- DynamicallyLoadedModuleNames: NaniteBuilder
- PrivateDependencyModuleNames: GeometryCore, MeshConversion, PhysicsCore, SkeletalMeshUtilitiesCommon
- PrivateIncludePathModuleNames: DerivedDataCache, NaniteBuilder
- PublicDependencyModuleNames: ChaosSolverEngine, Core, CoreUObject, DataflowCore, DataflowEngine, EditorFramework, Engine, FieldSystemEngine, ISMPool, IntelISPC, MeshDescription, NetCore, RHI, RenderCore, Renderer, SkeletalMeshDescription, StaticMeshDescription, UnrealEd

### `Source/Runtime/Experimental/GeometryCollectionEngine/Private/GeometryCollection/GeometryCollectionComponentPluginPrivate.h` (Private)


#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_STATS_GROUP(TEXT("GeometryCollection"), STATGROUP_GeometryCollection,`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Private/GeometryCollection/GeometryCollectionISMPoolRenderer.h` (Private)


#### class `UGeometryCollectionISMPoolRenderer`  
`class UGeometryCollectionISMPoolRenderer : public UObject, public IGeometryCollectionExternalRenderInterface`  
_L15-66_
- reflection: `UCLASS()`
- inherits: `UObject,IGeometryCollectionExternalRenderInterface`
- desc: Implementation of a geometry collection custom renderer that pushes AutoInstanceMeshes to an ISMPool.
- L21 _private member_ `TObjectPtr<UISMPoolComponent> CachedISMPoolComponent;` — `UPROPERTY(Transient)` — Instanced Static Mesh Pool component that is used to render our meshes.
- L25 _private member_ `TObjectPtr<UISMPoolComponent> LocalISMPoolComponent;` — `UPROPERTY()` — Set if we have an Instanced Static Mesh Pool component owned by this renderer (ie when in Editor mode). Non-transient to behave correctly under actor duplication.
- L29 _public prototype_ `virtual void OnRegisterGeometryCollection(UGeometryCollectionComponent& InComponent) override;`
- L30 _public prototype_ `virtual void OnUnregisterGeometryCollection() override;`
- L31 _public prototype_ `virtual void UpdateState(UGeometryCollection const& InGeometryCollection, FTransform const& InComponentTransform, uint32 InStateFlags) override;`
- L32 _public prototype_ `virtual void UpdateRootTransform(UGeometryCollection const& InGeometryCollection, FTransform const& InRootTransform) override;`
- L33 _public prototype_ `virtual void UpdateRootTransforms(UGeometryCollection const& InGeometryCollection, FTransform const& InRootTransform, TArrayView<const FTransform3f> InRootLocalTransforms) override;`
- L34 _public prototype_ `virtual void UpdateTransforms(UGeometryCollection const& InGeometryCollection, TArrayView<const FTransform3f> InTransforms) override;`
- L46 _protected member_ `FTransform ComponentTransform = FTransform::Identity;` — Cached component transform.
- L49 _protected member_ `FISMPoolGroup MergedMeshGroup;` — ISM pool groups per rendering element type.
- L50 _protected member_ `FISMPoolGroup InstancesGroup;`
- L53 _protected member_ `TWeakObjectPtr<ULevel> OwningLevel;` — Level of the owning component of this renderer
- L56 _protected member_ `bool bIsRegistered = false;` — Registered flag set true in between calls to OnRegister() and OnUnregister().
- L59 _private prototype_ `UISMPoolComponent* GetISMPoolComponent() const;`
- L60 _private prototype_ `UISMPoolComponent* GetOrCreateISMPoolComponent();`
- L61 _private prototype_ `void InitMergedMeshFromGeometryCollection(UGeometryCollection const& InGeometryCollection);`
- L62 _private prototype_ `void InitInstancesFromGeometryCollection(UGeometryCollection const& InGeometryCollection);`
- L63 _private prototype_ `void UpdateMergedMeshTransforms(FTransform const& InBaseTransform, TArrayView<const FTransform3f> InLocalTransforms);`
- L64 _private prototype_ `void UpdateInstanceTransforms(UGeometryCollection const& InGeometryCollection, FTransform const& InBaseTransform, TArrayView<const FTransform3f> InTransforms);`
- L65 _private prototype_ `void ReleaseGroup(FISMPoolGroup& InOutGroup);`

#### struct `UGeometryCollectionISMPoolRenderer::FISMPoolGroup`  
`struct FISMPoolGroup`  
_L39-43_
- desc: Description for a group of meshes that are added/updated together.
- L41 _public member_ `int32 GroupIndex = INDEX_NONE;`
- L42 _public member_ `TArray<int32> MeshIds;`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Private/GeometryCollection/GeometryCollectionRenderData.h` (Private)


#### class `FBoneMapVertexBuffer`  
`class FBoneMapVertexBuffer : public FVertexBuffer`  
_L18-52_
- inherits: `FVertexBuffer`
- desc: Vertex Buffer for Bone Map.
- L21 _public prototype_ `~FBoneMapVertexBuffer();`
- L23 _public prototype_ `void Init(TArray<uint16> const& InBoneMap, bool bInNeedsCPUAccess = true);`
- L24 _public prototype_ `void Serialize(FArchive& Ar, bool bInNeedsCPUAccess);`
- L25 _public function_ `FRHIShaderResourceView* GetSRV() const`
- L27 _public function_ `FORCEINLINE uint16& BoneIndex(uint32 VertexIndex) const`
- L33 _public function_ `SIZE_T GetAllocatedSize() const`
- L36 _protected prototype_ `void CleanUp();`
- L37 _protected prototype_ `void AllocateData(bool bInNeedsCPUAccess = true);`
- L38 _protected prototype_ `void ResizeBuffer(uint32 InNumVertices);`
- L40 _protected prototype_ `void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L41 _protected prototype_ `void ReleaseRHI() override;`
- L43 _protected member_ `static const EPixelFormat PixelFormat = PF_R16_UINT;`
- L44 _protected member_ `static const uint32 PixelFormatStride = 2;`
- L47 _private member_ `uint32 NumVertices = 0;`
- L48 _private member_ `bool bNeedsCPUAccess = true;`
- L49 _private member_ `FShaderResourceViewRHIRef VertexBufferSRV = nullptr;`
- L50 _private member_ `FStaticMeshVertexDataInterface* BoneMapData = nullptr;`
- L51 _private member_ `uint8* Data = nullptr;`

#### struct `FGeometryCollectionMeshResources`  
`struct FGeometryCollectionMeshResources`  
_L55-69_
- desc: Set of GPU vertex and index buffers required to render a geometry collection.
- L57 _public member_ `FRawStaticIndexBuffer IndexBuffer;`
- L58 _public member_ `FPositionVertexBuffer PositionVertexBuffer;`
- L59 _public member_ `FStaticMeshVertexBuffer StaticMeshVertexBuffer;`
- L60 _public member_ `FColorVertexBuffer ColorVertexBuffer;`
- L61 _public member_ `FBoneMapVertexBuffer BoneMapVertexBuffer;`
- L64 _public prototype_ `void InitResources(UGeometryCollection const& Owner);` — Initialize the render resources.
- L66 _public prototype_ `void ReleaseResources();` — Release the render resources.
- L68 _public prototype_ `void Serialize(FArchive& Ar);` — Serialization.

#### struct `FGeometryCollectionMeshElement`  
`struct FGeometryCollectionMeshElement`  
_L72-88_
- desc: Description of a single mesh element within a set of vertex and vertex buffers.
- L74 _public member_ `int16 TransformIndex;`
- L75 _public member_ `uint8 MaterialIndex;`
- L76 _public member_ `uint8 bIsInternal;`
- L77 _public member_ `uint32 TriangleStart;`
- L78 _public member_ `uint32 TriangleCount;`
- L79 _public member_ `uint32 VertexStart;`
- L80 _public member_ `uint32 VertexEnd;`

#### struct `FGeometryCollectionMeshDescription`  
`struct FGeometryCollectionMeshDescription`  
_L91-107_
- desc: CPU side data required to render a geometry collection.
- L93 _public member_ `uint32 NumVertices = 0;`
- L94 _public member_ `uint32 NumTriangles = 0;`
- L98 _public member_ `TArray<FGeometryCollectionMeshElement> Sections;` — Info on grouped material sections within vertex buffers. A section has a uniform material index and can contain multiple per-bone subsections.
- L100 _public member_ `TArray<FGeometryCollectionMeshElement> SectionsNoInternal;` — Info on grouped material sections within vertex buffers but with internal faces added by the fracture tool removed.
- L103 _public member_ `TArray<FGeometryCollectionMeshElement> SubSections;` — Info on individual subsections within vertex buffers. A subsection has a uniform bone and material index.
- L106 _public prototype_ `void Serialize(FArchive& Ar);` — Serialization.

#### struct `FGeometryCollectionRayTracingResources`  
`struct FGeometryCollectionRayTracingResources`  
_L111-115_
- desc: Set of resources required to ray trace a geometry collection.
- L113 _public member_ `RayTracing::FGeometryGroupHandle GroupHandle;`
- L114 _public member_ `TArray<FRayTracingGeometry> PartGeometries;`

#### class `FGeometryCollectionRenderData`  
`class FGeometryCollectionRenderData`  
_L119-175_
- desc: Built render data compiled and ready for use by the geometry collection scene proxy.
- L122 _public prototype_ `FGeometryCollectionRenderData() = default;`
- L123 _public prototype_ `~FGeometryCollectionRenderData();`
- L135 _public prototype_ `static TUniquePtr<FGeometryCollectionRenderData> Create(FGeometryCollection& InCollection, FCreateDesc const& InDesc);`
- L138 _public function_ `bool IsInitialized()`
- L144 _public prototype_ `void Serialize(FArchive& Ar, UGeometryCollection& Owner);` — Serialization.
- L147 _public prototype_ `void InitResources(UGeometryCollection const& Owner);` — Initialize the render resources.
- L150 _public prototype_ `void ReleaseResources();` — Releases the render resources.
- L153 _public member_ `bool bHasMeshData = false;` — False if we don't store valid non-nanite mesh data.
- L155 _public member_ `bool bHasNaniteData = false;` — False if we don't store valid nanite data.
- L158 _public member_ `FGeometryCollectionMeshResources MeshResource;` — Mesh GPU resources.
- L161 _public member_ `FGeometryCollectionMeshDescription MeshDescription;` — Mesh CPU description.
- L164 _public member_ `TPimplPtr<Nanite::FResources> NaniteResourcesPtr;` — Nanite resources.
- L167 _public member_ `FBoxSphereBounds PreSkinnedBounds = FBoxSphereBounds(ForceInitToZero);` — Object local bounds before any animation.
- L170 _public member_ `FGeometryCollectionRayTracingResources RayTracingResource;`
- L174 _private member_ `bool bIsInitialized = false;`

#### struct `FGeometryCollectionRenderData::FCreateDesc`  
`struct FCreateDesc`  
_L126-133_
- L128 _public member_ `bool bEnableNanite = false;`
- L129 _public member_ `bool bEnableNaniteFallback = false;`
- L130 _public member_ `bool bUseFullPrecisionUVs = false;`
- L131 _public member_ `bool bConvertVertexColorsToSRGB = false;`
- L132 _public member_ `uint32 NaniteMinimumResidencyInKB = 0;`

#### Free symbols / members of external scopes

- L83 _function_ `friend FArchive& operator<<(FArchive& Ar, FGeometryCollectionMeshElement& Item)` — Serialization.

### `Source/Runtime/Experimental/GeometryCollectionEngine/Private/GeometryCollection/GeometryCollectionSQAccelerator.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/Experimental/GeometryCollectionEngine/Private/GeometryCollection/GeometryCollectionSceneProxy.h` (Private)


#### class `FGeometryCollectionTransformBuffer`  
`class FGeometryCollectionTransformBuffer : public FVertexBuffer`  
_L33-58_
- inherits: `FVertexBuffer`
- desc: Vertex Buffer for transform data
- L36 _public function_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override`
- L53 _public prototype_ `void UpdateDynamicData(FRHICommandListBase& RHICmdList, const TArray<FMatrix44f>& Transforms, EResourceLockMode LockMode);`
- L55 _public member_ `int32 NumTransforms;`
- L57 _public member_ `FShaderResourceViewRHIRef VertexBufferSRV;`

#### struct `FGeometryCollectionDynamicData`  
`struct FGeometryCollectionDynamicData`  
_L90-116_
- desc: Mutable rendering data
- L92 _public member_ `TArray<FMatrix44f> Transforms;`
- L93 _public member_ `uint64 FrameIndex = 0;`
- L95 _public function_ `FGeometryCollectionDynamicData()`
- L100 _public function_ `void Reset()`
- L106 _public function_ `void SetTransforms(const TArray<FTransform>& InTransforms)`
- L112 _public function_ `void SetTransforms(const TArray<FTransform3f>& InTransforms)`

#### class `FGeometryCollectionDynamicDataPool`  
`class FGeometryCollectionDynamicDataPool`  
_L119-133_
- L122 _public prototype_ `FGeometryCollectionDynamicDataPool();`
- L123 _public prototype_ `~FGeometryCollectionDynamicDataPool();`
- L125 _public prototype_ `FGeometryCollectionDynamicData* Allocate();`
- L126 _public prototype_ `void Release(FGeometryCollectionDynamicData* DynamicData);`
- L129 _private member_ `TArray<FGeometryCollectionDynamicData*> UsedList;`
- L130 _private member_ `TArray<FGeometryCollectionDynamicData*> FreeList;`
- L132 _private member_ `FCriticalSection ListLock;`

#### class `FGeometryCollectionSceneProxyBase`  
`class FGeometryCollectionSceneProxyBase`  
_L136-259_
- L139 _protected prototype_ `FGeometryCollectionSceneProxyBase(UGeometryCollectionComponent* Component, bool bInIsNanite);`
- L140 _protected prototype_ `virtual ~FGeometryCollectionSceneProxyBase();`
- L142 _protected prototype_ `void CreateRenderThreadResources(FRHICommandListBase& RHICmdList);`
- L143 _protected prototype_ `void DestroyRenderThreadResources();`
- L146 _protected prototype_ `void SetupVertexFactory(FRHICommandListBase& RHICmdList, FGeometryCollectionVertexFactory& GeometryCollectionVertexFactory, FColorVertexBuffer* ColorOverride = nullptr) const;` — Setup a geometry collection vertex factory.
- L149 _protected prototype_ `void SetDynamicData_RenderThread(FRHICommandListBase& RHICmdList, FGeometryCollectionDynamicData* NewDynamicData);` — Called on render thread to setup dynamic geometry for rendering
- L151 _protected function_ `FGeometryCollectionTransformBuffer& GetCurrentTransformBuffer()`
- L156 _protected function_ `const FGeometryCollectionTransformBuffer& GetCurrentTransformBuffer() const`
- L161 _protected function_ `const FGeometryCollectionTransformBuffer& GetCurrentPrevTransformBuffer() const`
- L168 _protected function_ `void CycleTransformBuffers(bool bCycle)`
- L176 _protected prototype_ `TConstArrayView<FGeometryCollectionMeshElement> GetSectionArray(bool bUsesSubSections, bool bRemoveInternalFaces) const;`
- L179 _protected prototype_ `void GetMeshElement( int32 LODIndex, int32 SectionIndex, const FGeometryCollectionMeshElement& Section, const FVertexFactory* InVertexFactory, FMaterialRenderProxy* MaterialProxy, uint8 InDepthPriorityGroup, FRHIUniformBuffer* UniformBuffer, bool bWireframe, bool bReverseCulling, FMeshBatch& OutMeshBatch) const;` — Sets up a FMeshBatch for a specific LOD and section.
- L191 _protected typedef_ `using FMaterialArrayType = TArray<FMaterialRenderProxy*, TInlineAllocator<32>>;`
- L193 _protected prototype_ `void GetSectionMaterialProxies(TConstArrayView<FGeometryCollectionMeshElement> InSectionArray, FMaterialArrayType& OutMaterialProxies) const;`
- L196 _protected prototype_ `void UpdatingRayTracingGeometry_RenderingThread(FRHICommandListBase& RHICmdList, TConstArrayView<FGeometryCollectionMeshElement> InSectionArray, bool bRayTracingGeometryPerSection);`
- L198 _protected function_ `bool IsRayTracingRelevant() const`
- L199 _protected function_ `bool IsRayTracingStaticRelevant() const`
- L200 _protected function_ `bool HasRayTracingRepresentation() const`
- L201 _protected prototype_ `void GetDynamicRayTracingInstances(FRayTracingInstanceCollector& Collector, const FMatrix& LocalToWorld, FRHIUniformBuffer* UniformBuffer, bool bAnyMaterialHasWorldPositionOffset);`
- L202 _protected prototype_ `void GetStaticRayTracingInstances(FStaticRayTracingInstances& OutRayTracingInstances, FRHIUniformBuffer* UniformBuffer);`
- L203 _protected prototype_ `RayTracing::FGeometryGroupHandle GetRayTracingGeometryGroupHandle() const;`
- L206 _protected prototype_ `uint32 GetAllocatedSize() const;`
- L210 _protected member_ `const bool bIsNanite;`
- L211 _protected member_ `ERHIFeatureLevel::Type FeatureLevel;`
- L213 _protected member_ `const FGeometryCollectionMeshResources& MeshResource;`
- L214 _protected member_ `FGeometryCollectionMeshDescription MeshDescription;`
- L215 _protected member_ `FMaterialRelevance MaterialRelevance;`
- L217 _protected member_ `FBoxSphereBounds PreSkinnedBounds;`
- L219 _protected member_ `FGeometryCollectionVertexFactory VertexFactory;`
- L220 _protected member_ `const bool bUseShaderBoneTransform;`
- L221 _protected member_ `const bool bSupportsTripleBufferVertexUpload;`
- L223 _protected member_ `TArray<UMaterialInterface*> Materials;`
- L225 _protected member_ `TArray<int32> TransformToInstanceMapping;`
- L227 _protected member_ `int32 NumTransforms = 0;`
- L229 _protected member_ `FGeometryCollectionDynamicData* DynamicData = nullptr;`
- L232 _protected member_ `bool bUseStaticRayTracingInstances = false;`
- L238 _private prototype_ `void UpdateSkinnedPositions(FRHICommandListBase& RHICmdList, TArray<FMatrix44f> const& Transforms);` — Update skinned position buffer used by mobile CPU skinning path.
- L240 _private member_ `FPositionVertexBuffer SkinnedPositionVertexBuffer;`
- L242 _private member_ `int32 CurrentTransformBufferIndex = 0;`
- L243 _private member_ `TArray<FGeometryCollectionTransformBuffer, TInlineAllocator<4>> TransformBuffers;`
- L245 _private member_ `const bool bHasRayTracingRepresentation = false;`
- L248 _private member_ `const FGeometryCollectionRayTracingResources& RayTracingResources;`
- L249 _private member_ `RayTracing::FGeometryGroupHandle RayTracingGeometryGroupHandle;`
- L251 _private member_ `FRayTracingGeometry RayTracingGeometry;`
- L252 _private member_ `FRWBuffer RayTracingDynamicVertexBuffer;`
- L254 _private member_ `TArray<FMeshBatch> CachedPartRayTracingMaterials;`
- L255 _private member_ `TArray<uint32> PrimitiveInstanceIndices;`
- L258 _private member_ `bool bRenderResourcesCreated = false;`

#### class `FGeometryCollectionSceneProxy`  
`class FGeometryCollectionSceneProxy final : public FPrimitiveSceneProxy, private FGeometryCollectionSceneProxyBase`  
_L273-340_
- inherits: `FPrimitiveSceneProxy,FGeometryCollectionSceneProxyBase`
- desc: FGeometryCollectionSceneProxy The FGeometryCollectionSceneProxy manages the interaction between the GeometryCollectionComponent on the game thread and the vertex buffers on the render thread. NOTE : This class is still in flux, and has a few pending todos. Your comments and thoughts are appreciated though. The remaining items to address involve: - @todo double buffer - The double buffering of the FGeometryCollectionDynamicData. - @todo GPU skin : Make the skinning use the GpuVertexShader
- L275 _private member_ `TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe> GeometryCollection;`
- L277 _private member_ `FCollisionResponseContainer CollisionResponse;`
- L279 _private member_ `bool bRenderResourcesCreated = false;`
- L282 _private member_ `bool bShowBoneColors = false;`
- L283 _private member_ `bool bSuppressSelectionMaterial = false;`
- L284 _private member_ `TArray<FColor> BoneColors;`
- L285 _private member_ `FColorVertexBuffer ColorVertexBuffer;`
- L286 _private member_ `FGeometryCollectionVertexFactory VertexFactoryDebugColor;`
- L287 _private member_ `UMaterialInterface* BoneSelectedMaterial = nullptr;`
- L291 _private member_ `bool bUsesSubSections = false;`
- L292 _private member_ `bool bEnableBoneSelection = false;`
- L293 _private member_ `TArray<TRefCountPtr<HHitProxy>> HitProxies;`
- L294 _private member_ `FColorVertexBuffer HitProxyIdBuffer;`
- L298 _public prototype_ `FGeometryCollectionSceneProxy(UGeometryCollectionComponent* Component);`
- L299 _public prototype_ `virtual ~FGeometryCollectionSceneProxy();`
- L302 _public prototype_ `void SetDynamicData_RenderThread(FRHICommandListBase& RHICmdList, FGeometryCollectionDynamicData* NewDynamicData);` — Called on render thread to setup dynamic geometry for rendering
- L304 _public function_ `virtual uint32 GetMemoryFootprint() const override`
- L305 _public prototype_ `uint32 GetAllocatedSize() const;`
- L307 _public prototype_ `SIZE_T GetTypeHash() const override;`
- L308 _public prototype_ `void CreateRenderThreadResources(FRHICommandListBase& RHICmdList) override;`
- L309 _public prototype_ `void DestroyRenderThreadResources() override;`
- L310 _public prototype_ `void GetPreSkinnedLocalBounds(FBoxSphereBounds& OutBounds) const override;`
- L311 _public prototype_ `FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L312 _public prototype_ `void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L314 _public function_ `virtual bool AllowInstanceCullingOcclusionQueries() const override`
- L317 _public prototype_ `virtual HHitProxy* CreateHitProxies(UPrimitiveComponent* Component, TArray<TRefCountPtr<HHitProxy> >& OutHitProxies) override;`
- L318 _public function_ `virtual const FColorVertexBuffer* GetCustomHitProxyIdBuffer() const override`
- L323 _public prototype_ `virtual void DrawStaticElements(FStaticPrimitiveDrawInterface* PDI) override;`
- L326 _public function_ `virtual bool IsRayTracingRelevant() const override`
- L327 _public function_ `virtual bool IsRayTracingStaticRelevant() const override`
- L328 _public function_ `virtual bool HasRayTracingRepresentation() const override`
- L329 _public function_ `virtual void GetDynamicRayTracingInstances(FRayTracingInstanceCollector& Collector) override`
- L334 _protected prototype_ `FMaterialRenderProxy* GetMaterial(FMeshElementCollector& Collector, int32 MaterialIndex) const;` — Get material proxy from material ID
- L336 _protected prototype_ `FVertexFactory const* GetVertexFactory() const;` — Get the standard or debug vertex factory dependent on current state.
- L339 _private prototype_ `bool ShowCollisionMeshes(const FEngineShowFlags& EngineShowFlags) const;`

#### class `FNaniteGeometryCollectionSceneProxy`  
`class FNaniteGeometryCollectionSceneProxy : public Nanite::FSceneProxyBase, private FGeometryCollectionSceneProxyBase`  
_L343-442_
- inherits: `Nanite::FSceneProxyBase,FGeometryCollectionSceneProxyBase`
- L346 _public typedef_ `using Super = Nanite::FSceneProxyBase;`
- L348 _public prototype_ `FNaniteGeometryCollectionSceneProxy(UGeometryCollectionComponent* Component);`
- L349 _public prototype_ `virtual ~FNaniteGeometryCollectionSceneProxy();`
- L353 _public prototype_ `virtual void CreateRenderThreadResources(FRHICommandListBase& RHICmdList) override;` — FPrimitiveSceneProxy interface.
- L354 _public prototype_ `virtual void DestroyRenderThreadResources() override;`
- L355 _public prototype_ `virtual void GetPreSkinnedLocalBounds(FBoxSphereBounds& OutBounds) const override;`
- L356 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L357 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L358 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L360 _public prototype_ `virtual HHitProxy* CreateHitProxies(UPrimitiveComponent* Component, TArray<TRefCountPtr<HHitProxy> >& OutHitProxies) override;`
- L362 _public prototype_ `virtual void DrawStaticElements(FStaticPrimitiveDrawInterface* PDI) override;`
- L364 _public function_ `virtual uint32 GetMemoryFootprint() const override`
- L365 _public prototype_ `uint32 GetAllocatedSize() const;`
- L368 _public prototype_ `virtual Nanite::FResourceMeshInfo GetResourceMeshInfo() const override;` — FSceneProxyBase interface.
- L369 _public prototype_ `virtual Nanite::FResourcePrimitiveInfo GetResourcePrimitiveInfo() const override;`
- L372 _public prototype_ `void SetDynamicData_RenderThread(FRHICommandListBase& RHICmdList, FGeometryCollectionDynamicData* NewDynamicData, const FMatrix &PrimitiveLocalToWorld);` — Called on render thread to setup dynamic geometry for rendering
- L374 _public prototype_ `void FlushGPUSceneUpdate_GameThread();`
- L376 _public function_ `FORCEINLINE void SetRequiresGPUSceneUpdate_RenderThread(bool bRequireUpdate)`
- L381 _public function_ `FORCEINLINE bool GetRequiresGPUSceneUpdate_RenderThread() const`
- L386 _public function_ `inline virtual void GetLCIs(FLCIArray& LCIs) override`
- L393 _public function_ `virtual bool IsRayTracingRelevant() const override`
- L394 _public function_ `virtual bool IsRayTracingStaticRelevant() const override`
- L395 _public function_ `virtual bool HasRayTracingRepresentation() const override`
- L396 _public function_ `virtual void GetDynamicRayTracingInstances(FRayTracingInstanceCollector& Collector) override`
- L397 _public prototype_ `virtual ERayTracingPrimitiveFlags GetRayTracingPrimitiveFlags() override;`
- L398 _public function_ `virtual void GetStaticRayTracingInstances(FStaticRayTracingInstances& OutRayTracingInstances) override`
- L399 _public function_ `virtual RayTracing::FGeometryGroupHandle GetRayTracingGeometryGroupHandle() const override`
- L404 _protected member_ `const UGeometryCollection* GeometryCollection = nullptr;` — TODO : Copy required data from UObject instead of using unsafe object pointer.
- L405 _protected member_ `FCollisionResponseContainer CollisionResponse;`
- L412 _protected member_ `TArray<FGeometryNaniteData> GeometryNaniteData;`
- L414 _protected member_ `uint32 bCastShadow : 1;`
- L415 _protected member_ `uint32 bReverseCulling : 1;`
- L416 _protected member_ `uint32 bHasMaterialErrors : 1;`
- L417 _protected member_ `uint32 bRequiresGPUSceneUpdate : 1;`
- L418 _protected member_ `uint32 bEnableBoneSelection : 1;`
- L421 _protected member_ `TArray<TRefCountPtr<HHitProxy>> HitProxies;`
- L424 _protected member_ `FInstanceSceneDataBuffers InstanceSceneDataBuffersImpl;`
- L436 _private prototype_ `void UpdateInstanceSceneDataBuffers(const FMatrix& PrimitiveLocalToWorld);`
- L438 _private prototype_ `bool ShowCollisionMeshes(const FEngineShowFlags& EngineShowFlags) const;`
- L441 _private member_ `static FEmptyLightCacheInfo EmptyLightCacheInfo;`

#### struct `FNaniteGeometryCollectionSceneProxy::FGeometryNaniteData`  
`struct FGeometryNaniteData`  
_L407-411_
- L409 _public member_ `FBoxSphereBounds LocalBounds;`
- L410 _public member_ `uint32 HierarchyOffset;`

#### class `FNaniteGeometryCollectionSceneProxy::FEmptyLightCacheInfo`  
`class FEmptyLightCacheInfo : public FLightCacheInterface`  
_L427-433_
- inherits: `FLightCacheInterface`
- desc: Geometry collection doesn't currently support baked light maps, so we use this simple empty light cache info for all nanite geometry collection proxies
- L432 _public prototype_ `virtual FLightInteraction GetInteraction(const FLightSceneProxy* LightSceneProxy) const override;` — FLightCacheInterface.

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace Nanite`
- L60 _function_ `inline void CopyTransformsWithConversionWhenNeeded(TArray<FMatrix44f>& DstTransforms, const TArray<FMatrix>& SrcTransforms)`
- L70 _function_ `inline void CopyTransformsWithConversionWhenNeeded(TArray<FMatrix44f>& DstTransforms, const TArray<FTransform>& SrcTransforms)`
- L80 _function_ `inline void CopyTransformsWithConversionWhenNeeded(TArray<FMatrix44f>& DstTransforms, const TArray<FTransform3f>& SrcTransforms)`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/ChaosBlueprint.h` (Public)


#### class `UChaosDestructionListener`  
`class UChaosDestructionListener : public USceneComponent`  
_L43-269_
- reflection: `UCLASS(ClassGroup = (Chaos), hidecategories = (Object, ActorComponent, Physics, Rendering, Mobility, LOD), ShowCategories = Trigger, meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `USceneComponent`
- desc: Object allowing for retrieving Chaos Destruction data.
- L50 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L55 _public prototype_ `virtual void BeginPlay() override;`
- L56 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L57 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L62 _public member_ `uint8 bIsCollisionEventListeningEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision Events")` — Whether or not collision event listening is enabled
- L66 _public member_ `uint8 bIsBreakingEventListeningEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Breaking Events")` — Whether or not collision event listening is enabled
- L70 _public member_ `uint8 bIsTrailingEventListeningEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trailing Events")` — Whether or not trailing event listening is enabled
- L74 _public member_ `uint8 bIsRemovalEventListeningEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Removal Events")` — Whether or not removal event listening is enabled
- L78 _public member_ `FChaosCollisionEventRequestSettings CollisionEventRequestSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision Events", meta = (EditCondition = "bIsCollisionEventListeningEnabled"))` — The settings to use for collision event listening
- L82 _public member_ `FChaosBreakingEventRequestSettings BreakingEventRequestSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Breaking Events", meta = (EditCondition = "bIsBreakingEventListeningEnabled"))` — The settings to use for breaking event listening
- L86 _public member_ `FChaosTrailingEventRequestSettings TrailingEventRequestSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trailing Events", meta = (EditCondition = "bIsTrailingEventListeningEnabled"))` — The settings to use for trailing event listening
- L90 _public member_ `FChaosRemovalEventRequestSettings RemovalEventRequestSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Removal Events", meta = (EditCondition = "bIsRemovalEventListeningEnabled"))` — The settings to use for removal event listening
- L94 _public member_ `TSet<TObjectPtr<AChaosSolverActor>> ChaosSolverActors;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Solvers")` — Which chaos solver actors we're using. If empty, this listener will fallback to the "world" solver.
- L98 _public member_ `TSet<TObjectPtr<AGeometryCollectionActor>> GeometryCollectionActors;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GeometryCollections")` — Which chaos solver actors we're using. If empty, this listener will fallback to the "world" solver.
- L102 _public prototype_ `void AddChaosSolverActor(AChaosSolverActor* ChaosSolverActor);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Dynamically adds a chaos solver to the listener
- L106 _public prototype_ `void RemoveChaosSolverActor(AChaosSolverActor* ChaosSolverActor);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Dynamically removes a chaos solver from the listener
- L110 _public prototype_ `void AddGeometryCollectionActor(AGeometryCollectionActor* GeometryCollectionActor);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Dynamically adds a chaos solver to the listener
- L114 _public prototype_ `void RemoveGeometryCollectionActor(AGeometryCollectionActor* GeometryCollectionActor);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Dynamically removes a chaos solver from the listener
- L118 _public prototype_ `void SetCollisionEventRequestSettings(const FChaosCollisionEventRequestSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Sets collision event request settings dynamically
- L122 _public prototype_ `void SetBreakingEventRequestSettings(const FChaosBreakingEventRequestSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Sets breaking event request settings dynamically
- L126 _public prototype_ `void SetTrailingEventRequestSettings(const FChaosTrailingEventRequestSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Sets trailing event request settings dynamically
- L130 _public prototype_ `void SetRemovalEventRequestSettings(const FChaosRemovalEventRequestSettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Sets removal event request settings dynamically
- L134 _public prototype_ `void SetCollisionEventEnabled(bool bIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Enables or disables collision event listening
- L138 _public prototype_ `void SetBreakingEventEnabled(bool bIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Enables or disables breaking event listening
- L142 _public prototype_ `void SetTrailingEventEnabled(bool bIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Enables or disables trailing event listening
- L146 _public prototype_ `void SetRemovalEventEnabled(bool bIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Enables or disables removal event listening
- L150 _public prototype_ `bool IsEventListening() const;` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Returns if the destruction listener is listening to any events
- L154 _public member_ `FOnChaosCollisionEvents OnCollisionEvents;` — `UPROPERTY(BlueprintAssignable)` — Called when new collision events are available.
- L158 _public member_ `FOnChaosBreakingEvents OnBreakingEvents;` — `UPROPERTY(BlueprintAssignable)` — Called when new breaking events are available.
- L162 _public member_ `FOnChaosTrailingEvents OnTrailingEvents;` — `UPROPERTY(BlueprintAssignable)` — Called when new trailing events are available.
- L166 _public member_ `FOnChaosRemovalEvents OnRemovalEvents;` — `UPROPERTY(BlueprintAssignable)` — Called when new trailing events are available.
- L170 _public prototype_ `void SortCollisionEvents(UPARAM(ref) TArray<FChaosCollisionEventData>& CollisionEvents, EChaosCollisionSortMethod SortMethod);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Sorts collision events according to the given sort method
- L174 _public prototype_ `void SortBreakingEvents(UPARAM(ref) TArray<FChaosBreakingEventData>& BreakingEvents, EChaosBreakingSortMethod SortMethod);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Sorts breaking events according to the given sort method
- L178 _public prototype_ `void SortTrailingEvents(UPARAM(ref) TArray<FChaosTrailingEventData>& TrailingEvents, EChaosTrailingSortMethod SortMethod);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Sorts trailing events according to the given sort method
- L182 _public prototype_ `void SortRemovalEvents(UPARAM(ref) TArray<FChaosRemovalEventData>& RemovalEvents, EChaosRemovalSortMethod SortMethod);` — `UFUNCTION(BlueprintCallable, Category = "Destruction Listener", meta = (WorldContext = "WorldContextObject"))` — Sorts removal events according to the given sort method
- L186 _private prototype_ `void UpdateTransformSettings();` — Updates the scene component transform settings
- L189 _private prototype_ `void GetDataFromSolvers();` — Retrieves data from solvers
- L191 _private prototype_ `void ClearEvents();`
- L192 _private prototype_ `void UpdateEvents();`
- L208 _protected member_ `FThreadSafeCounter TaskState;`
- L211 _protected member_ `Chaos::FCollisionDataArray RawCollisionDataArray;` — The raw data arrays derived from the solvers
- L212 _protected member_ `Chaos::FBreakingDataArray RawBreakingDataArray;`
- L213 _protected member_ `Chaos::FTrailingDataArray RawTrailingDataArray;`
- L214 _protected member_ `Chaos::FRemovalDataArray RawRemovalDataArray;`
- L216 _protected member_ `FTransform ChaosComponentTransform;`
- L218 _protected member_ `FThreadSafeBool bChanged;`
- L220 _protected member_ `float LastCollisionDataTimeStamp;`
- L221 _protected member_ `float LastBreakingDataTimeStamp;`
- L222 _protected member_ `float LastTrailingDataTimeStamp;`
- L223 _protected member_ `float LastRemovalDataTimeStamp;`
- L226 _protected member_ `TSet<Chaos::FPhysicsSolver*> Solvers;` — The list of rigid body solvers, used to retrieve destruction events
- L229 _protected member_ `TArray<const FGeometryCollectionPhysicsProxy*> GeometryCollectionPhysicsProxies;` — The list of GeometryCollectionPhysicsProxy, used to retrieve destruction events
- L231 _protected member_ `TSharedPtr<FChaosCollisionEventFilter> ChaosCollisionFilter;`
- L232 _protected member_ `TSharedPtr<FChaosBreakingEventFilter> ChaosBreakingFilter;`
- L233 _protected member_ `TSharedPtr<FChaosTrailingEventFilter> ChaosTrailingFilter;`
- L234 _protected member_ `TSharedPtr<FChaosRemovalEventFilter> ChaosRemovalFilter;`
- L237 _public function_ `void SetCollisionFilter(TSharedPtr<FChaosCollisionEventFilter> InCollisionFilter)`
- L242 _public function_ `void SetBreakingFilter(TSharedPtr<FChaosBreakingEventFilter> InBreakingFilter)`
- L247 _public function_ `void SetTrailingFilter(TSharedPtr<FChaosTrailingEventFilter> InTrailingFilter)`
- L252 _public function_ `void SetRemovalFilter(TSharedPtr<FChaosRemovalEventFilter> InRemovalFilter)`
- L257 _public prototype_ `void RegisterChaosEvents(FPhysScene* Scene);`
- L258 _public prototype_ `void UnregisterChaosEvents(FPhysScene* Scene);`
- L260 _public prototype_ `void RegisterChaosEvents(TSharedPtr<FPhysScene_Chaos> Scene);`
- L261 _public prototype_ `void UnregisterChaosEvents(TSharedPtr<FPhysScene_Chaos> Scene);`
- L265 _public prototype_ `void HandleCollisionEvents(const Chaos::FCollisionEventData& CollisionData);` — Chaos Event Handlers
- L266 _public prototype_ `void HandleBreakingEvents(const Chaos::FBreakingEventData& BreakingData);`
- L267 _public prototype_ `void HandleTrailingEvents(const Chaos::FTrailingEventData& TrailingData);`
- L268 _public prototype_ `void HandleRemovalEvents(const Chaos::FRemovalEventData& RemovalData);`

#### enum `UChaosDestructionListener::ETaskState`  
`enum class ETaskState`  
_L197-207_
- desc: Task state enumeration used to track if there is an async processing task in-flight
- L200 _public enumerator_ `NoTask = 0` — If there is no filtering and sorting task in-flight
- L203 _public enumerator_ `Processing` — If there is a task in-flight
- L206 _public enumerator_ `Finished` — If there was a task in flight but it is now finished with results ready for broadcast

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosCollisionEvents, const TArray<FChaosCollisionEventData>&, CollisionEvents);` — Called when new destruction events are available for collisions. Collision listening must be enabled to get callbacks on this delegate.
- L23 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosCollisionEvents, const TArray<FChaosCollisionEventData>&, CollisionEvents);` — Called when new destruction events are available for collisions. Collision listening must be enabled to get callbacks on this delegate.
- L28 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosBreakingEvents, const TArray<FChaosBreakingEventData>&, BreakingEvents);` — Called when new destruction events are available for breaks. Breaking listening must be enabled to get callbacks on this delegate.
- L28 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosBreakingEvents, const TArray<FChaosBreakingEventData>&, BreakingEvents);` — Called when new destruction events are available for breaks. Breaking listening must be enabled to get callbacks on this delegate.
- L33 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosTrailingEvents, const TArray<FChaosTrailingEventData>&, TrailingEvents);` — Called when new trailing events are available for breaks. Trailing listening must be enabled to get callbacks on this delegate.
- L33 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosTrailingEvents, const TArray<FChaosTrailingEventData>&, TrailingEvents);` — Called when new trailing events are available for breaks. Trailing listening must be enabled to get callbacks on this delegate.
- L38 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosRemovalEvents, const TArray<FChaosRemovalEventData>&, RemovalEvents);` — Called when new destruction events are available for removals. Removal listening must be enabled to get callbacks on this delegate.
- L38 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosRemovalEvents, const TArray<FChaosRemovalEventData>&, RemovalEvents);` — Called when new destruction events are available for removals. Removal listening must be enabled to get callbacks on this delegate.

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/ChaosBreakingEventFilter.h` (Public)


#### struct `FChaosBreakingEventData`  
`struct FChaosBreakingEventData`  
_L12-34_
- reflection: `USTRUCT(BlueprintType)`
- desc: A breaking event data structure.
- L18 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")` — Location of the breaking event (centroid)
- L22 _public member_ `FVector Velocity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")` — The velocity of the breaking event
- L26 _public member_ `float Mass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")` — The mass of the breaking event
- L28 _public function_ `FChaosBreakingEventData() : Location(FVector::ZeroVector) , Velocity(FVector::ZeroVector) , Mass(0.0f)`

#### enum `EChaosBreakingSortMethod`  
`enum class EChaosBreakingSortMethod : uint8`  
_L38-46_
- reflection: `UENUM(BlueprintType)`
- desc: Enumeration defining how to sort breaking results
- L40 _public enumerator_ `SortNone`
- L41 _public enumerator_ `SortByHighestMass`
- L42 _public enumerator_ `SortByHighestSpeed`
- L43 _public enumerator_ `SortByNearestFirst`
- L45 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FChaosBreakingEventRequestSettings`  
`struct FChaosBreakingEventRequestSettings`  
_L50-86_
- reflection: `USTRUCT(BlueprintType)`
- desc: Settings used to refine breaking event requests
- L56 _public member_ `int32 MaxNumberOfResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The maximum number of results to return.
- L60 _public member_ `float MinRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The minimum breaking radius threshold for the results.
- L64 _public member_ `float MinSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The minimum speed threshold for the results.
- L68 _public member_ `float MinMass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The minimum mass threshold for the results.
- L72 _public member_ `float MaxDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The maximum distance threshold for the results.
- L76 _public member_ `EChaosBreakingSortMethod SortMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sort")` — The method used to sort the breaking events.
- L78 _public function_ `FChaosBreakingEventRequestSettings() : MaxNumberOfResults(0) , MinRadius(0.0f) , MinSpeed(0.0f) , MinMass(0.0f) , MaxDistance(0.0f) , SortMethod(EChaosBreakingSortMethod::SortByHighestMass)`

#### class `FChaosBreakingEventFilter`  
`class FChaosBreakingEventFilter : public IChaosEventFilter<Chaos::FBreakingDataArray, TArray<FChaosBreakingEventData>, EChaosBreakingSortMethod>`  
_L88-100_
- inherits: `IChaosEventFilter<Chaos::FBreakingDataArray,TArray<FChaosBreakingEventData>,EChaosBreakingSortMethod>`
- L91 _public function_ `FChaosBreakingEventFilter(FChaosBreakingEventRequestSettings* FilterSettingsIn) : BreakingEventRequestSettings(FilterSettingsIn)`
- L93 _public prototype_ `virtual void FilterEvents(const FTransform& ChaosComponentTransform, const Chaos::FBreakingDataArray& RawBreakingDataArray) override;`
- L95 _public prototype_ `virtual void SortEvents(TArray<FChaosBreakingEventData>& InOutBreakingEvents, EChaosBreakingSortMethod SortMethod, const FTransform& InTransform) override;`
- L98 _private function_ `FChaosBreakingEventFilter() : BreakingEventRequestSettings(nullptr)`
- L99 _private member_ `const FChaosBreakingEventRequestSettings* BreakingEventRequestSettings;`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/ChaosCollisionEventFilter.h` (Public)


#### struct `FChaosCollisionEventData`  
`struct FChaosCollisionEventData`  
_L12-54_
- reflection: `USTRUCT(BlueprintType)`
- desc: A collision event data structure
- L18 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")` — Location of the collision event
- L22 _public member_ `FVector Normal;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")` — Normal of the collision event
- L26 _public member_ `FVector Velocity1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")` — The velocity of object 1 of the collision event
- L30 _public member_ `FVector Velocity2;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")` — The velocity of object 2 of the collision event
- L34 _public member_ `float Mass1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")` — The mass of object 1 of the collision event
- L38 _public member_ `float Mass2;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")` — The mass of object 2 of the collision event
- L42 _public member_ `FVector Impulse;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")` — The accumulated impulse vector of the collision event
- L44 _public function_ `FChaosCollisionEventData() : Location(FVector::ZeroVector) , Normal(FVector::ZeroVector) , Velocity1(FVector::ZeroVector) , Velocity2(FVector::ZeroVector) , Mass1(0.0f) , Mass2(0.0f) , Impulse(FVector::ZeroVector)`

#### enum `EChaosCollisionSortMethod`  
`enum class EChaosCollisionSortMethod : uint8`  
_L58-67_
- reflection: `UENUM(BlueprintType)`
- desc: Enumeration defining how to sort collision results
- L60 _public enumerator_ `SortNone`
- L61 _public enumerator_ `SortByHighestMass`
- L62 _public enumerator_ `SortByHighestSpeed`
- L63 _public enumerator_ `SortByHighestImpulse`
- L64 _public enumerator_ `SortByNearestFirst`
- L66 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FChaosCollisionEventRequestSettings`  
`struct FChaosCollisionEventRequestSettings`  
_L71-107_
- reflection: `USTRUCT(BlueprintType)`
- desc: Settings used to define collision event requests
- L77 _public member_ `int32 MaxNumberResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The maximum number of results to return.
- L81 _public member_ `float MinMass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The minimum mass threshold for the results (compared with min of particle 1 mass and particle 2 mass).
- L85 _public member_ `float MinSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The min speed threshold for the results (compared with min of particle 1 speed and particle 2 speed).
- L89 _public member_ `float MinImpulse;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The minimum impulse threshold for the results.
- L93 _public member_ `float MaxDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The maximum distance threshold for the results.
- L97 _public member_ `EChaosCollisionSortMethod SortMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sort")` — The method used to sort the collision events.
- L99 _public function_ `FChaosCollisionEventRequestSettings() : MaxNumberResults(0) , MinMass(0.0f) , MinSpeed(0.0f) , MinImpulse(0.0f) , MaxDistance(0.0f) , SortMethod(EChaosCollisionSortMethod::SortByHighestMass)`

#### class `FChaosCollisionEventFilter`  
`class FChaosCollisionEventFilter : public IChaosEventFilter<Chaos::FCollisionDataArray, TArray<FChaosCollisionEventData>, EChaosCollisionSortMethod>`  
_L109-121_
- inherits: `IChaosEventFilter<Chaos::FCollisionDataArray,TArray<FChaosCollisionEventData>,EChaosCollisionSortMethod>`
- L113 _public function_ `FChaosCollisionEventFilter(FChaosCollisionEventRequestSettings* FilterSettingsIn) : CollisionEventRequestSettings(FilterSettingsIn)`
- L115 _public prototype_ `virtual void FilterEvents(const FTransform& ChaosComponentTransform, const Chaos::FCollisionDataArray& RawCollisionDataArray) override;`
- L116 _public prototype_ `virtual void SortEvents(TArray<FChaosCollisionEventData>& InOutCollisionEvents, EChaosCollisionSortMethod SortMethod, const FTransform& InTransform) override;`
- L119 _private function_ `FChaosCollisionEventFilter() : CollisionEventRequestSettings(nullptr)`
- L120 _private member_ `const FChaosCollisionEventRequestSettings* CollisionEventRequestSettings;`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/ChaosFilter.h` (Public)


#### class `IChaosEventFilter`  
`template<class SourceType, class DestinationType, class SortMethodType> class IChaosEventFilter`  
_L10-58_
- desc: TChaosEventFilter (template for Chaos Event Filters)
- L14 _public prototype_ `virtual ~IChaosEventFilter() = default;`
- L19 _public prototype_ `virtual void FilterEvents(const FTransform& ChaosComponentTransform, const SourceType& RawInputDataArray) = 0;` — Filters the raw events from the physics system to reduce the number supplied to the game systems
- L24 _public function_ `virtual void FilterEvents(const SourceType& RawInputDataArray)` — Filters the raw events from the physics system to reduce the number supplied to the game systems
- L29 _public prototype_ `virtual void SortEvents(DestinationType& InOutFilteredEvents, SortMethodType SortMethod, const FTransform& InTransform) = 0;` — Optionally Sort events based on increasing or decreasing values of FilteredDataArray fields
- L35 _public function_ `const DestinationType& GetFilteredResults() const` — Gain access to the filtered results
- L40 _public function_ `int32 GetNumEvents() const` — Get the number of filtered results
- L42 _public function_ `void SetTransform(const FTransform& TransformIn)`
- L52 _protected member_ `DestinationType FilteredDataArray;` — The filtered results (a subset of the full raw events buffer)
- L57 _protected member_ `FTransform Transform;` — Filter results relative to a transform location

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/ChaosRemovalEventFilter.h` (Public)


#### struct `FChaosRemovalEventData`  
`struct FChaosRemovalEventData`  
_L12-34_
- reflection: `USTRUCT(BlueprintType)`
- desc: A Removal event data structure.
- L18 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — Current removal location.
- L22 _public member_ `float Mass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The mass of the removal.
- L26 _public member_ `int32 ParticleIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The particle index of the removal.
- L28 _public function_ `FChaosRemovalEventData() : Location(FVector::ZeroVector) , Mass(0.0f) , ParticleIndex(INDEX_NONE)`

#### enum `EChaosRemovalSortMethod`  
`enum class EChaosRemovalSortMethod : uint8`  
_L38-45_
- reflection: `UENUM(BlueprintType)`
- desc: Enumeration defining how to sort removal results
- L40 _public enumerator_ `SortNone`
- L41 _public enumerator_ `SortByHighestMass`
- L42 _public enumerator_ `SortByNearestFirst`
- L44 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FChaosRemovalEventRequestSettings`  
`struct FChaosRemovalEventRequestSettings`  
_L48-75_
- reflection: `USTRUCT(BlueprintType)`
- L54 _public member_ `int32 MaxNumberOfResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The maximum number of results to return.
- L58 _public member_ `float MinMass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The minimum mass treshold for the results.
- L62 _public member_ `float MaxDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The maximum distance threshold for the results (if location is set on destruction event listener).
- L66 _public member_ `EChaosRemovalSortMethod SortMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sort")` — The method used to sort the removal events.
- L68 _public function_ `FChaosRemovalEventRequestSettings() : MaxNumberOfResults(0) , MinMass(0.0f) , MaxDistance(0.0f) , SortMethod(EChaosRemovalSortMethod::SortByHighestMass)`

#### class `FChaosRemovalEventFilter`  
`class FChaosRemovalEventFilter : public IChaosEventFilter<Chaos::FRemovalDataArray, TArray<FChaosRemovalEventData>, EChaosRemovalSortMethod>`  
_L77-90_
- inherits: `IChaosEventFilter<Chaos::FRemovalDataArray,TArray<FChaosRemovalEventData>,EChaosRemovalSortMethod>`
- L81 _public function_ `FChaosRemovalEventFilter(FChaosRemovalEventRequestSettings* FilterSettingsIn) : RemovalEventRequestSettings(FilterSettingsIn)`
- L83 _public prototype_ `virtual void FilterEvents(const FTransform& ChaosComponentTransform, const Chaos::FRemovalDataArray& RawRemovalDataArray) override;`
- L85 _public prototype_ `virtual void SortEvents(TArray<FChaosRemovalEventData>& InOutRemovalEvents, EChaosRemovalSortMethod SortMethod, const FTransform& InTransform) override;`
- L88 _private function_ `FChaosRemovalEventFilter() : RemovalEventRequestSettings(nullptr)`
- L89 _private member_ `const FChaosRemovalEventRequestSettings* RemovalEventRequestSettings;`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/ChaosTrailingEventFilter.h` (Public)


#### struct `FChaosTrailingEventData`  
`struct FChaosTrailingEventData`  
_L12-44_
- reflection: `USTRUCT(BlueprintType)`
- desc: A trailing event data structure.
- L18 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — Current trail location.
- L22 _public member_ `FVector Velocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The velocity of the trail.
- L26 _public member_ `FVector AngularVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The angular velocity of the trail.
- L30 _public member_ `float Mass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The mass of the trail.
- L34 _public member_ `int32 ParticleIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The particle index of the trail.
- L36 _public function_ `FChaosTrailingEventData() : Location(FVector::ZeroVector) , Velocity(FVector::ZeroVector) , AngularVelocity(FVector::ZeroVector) , Mass(0.0f) , ParticleIndex(INDEX_NONE)`

#### enum `EChaosTrailingSortMethod`  
`enum class EChaosTrailingSortMethod : uint8`  
_L48-56_
- reflection: `UENUM(BlueprintType)`
- desc: Enumeration defining how to sort trailing results
- L50 _public enumerator_ `SortNone`
- L51 _public enumerator_ `SortByHighestMass`
- L52 _public enumerator_ `SortByHighestSpeed`
- L53 _public enumerator_ `SortByNearestFirst`
- L55 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FChaosTrailingEventRequestSettings`  
`struct FChaosTrailingEventRequestSettings`  
_L59-96_
- reflection: `USTRUCT(BlueprintType)`
- L65 _public member_ `int32 MaxNumberOfResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The maximum number of results to return.
- L69 _public member_ `float MinMass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The minimum mass treshold for the results.
- L73 _public member_ `float MinSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The minimum speed threshold for the results.
- L77 _public member_ `float MinAngularSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The minimum angular speed threshold for the results.
- L81 _public member_ `float MaxDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")` — The maximum distance threshold for the results (if location is set on destruction event listener).
- L85 _public member_ `EChaosTrailingSortMethod SortMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sort")` — The method used to sort the breaking events.
- L87 _public function_ `FChaosTrailingEventRequestSettings() : MaxNumberOfResults(0) , MinMass(0.0f) , MinSpeed(0.0f) , MinAngularSpeed(0.0f) , MaxDistance(0.0f) , SortMethod(EChaosTrailingSortMethod::SortByHighestMass)`

#### class `FChaosTrailingEventFilter`  
`class FChaosTrailingEventFilter : public IChaosEventFilter<Chaos::FTrailingDataArray, TArray<FChaosTrailingEventData>, EChaosTrailingSortMethod>`  
_L98-111_
- inherits: `IChaosEventFilter<Chaos::FTrailingDataArray,TArray<FChaosTrailingEventData>,EChaosTrailingSortMethod>`
- L102 _public function_ `FChaosTrailingEventFilter(FChaosTrailingEventRequestSettings* FilterSettingsIn) : TrailingEventRequestSettings(FilterSettingsIn)`
- L104 _public prototype_ `virtual void FilterEvents(const FTransform& ChaosComponentTransform, const Chaos::FTrailingDataArray& RawTrailingDataArray) override;`
- L106 _public prototype_ `virtual void SortEvents(TArray<FChaosTrailingEventData>& InOutTrailingEvents, EChaosTrailingSortMethod SortMethod, const FTransform& InTransform) override;`
- L109 _private function_ `FChaosTrailingEventFilter() : TrailingEventRequestSettings(nullptr)`
- L110 _private member_ `const FChaosTrailingEventRequestSettings* TrailingEventRequestSettings;`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/DerivedDataGeometryCollectionCooker.h` (Public)


#### class `FDerivedDataGeometryCollectionCooker`  
`class FDerivedDataGeometryCollectionCooker : public FDerivedDataPluginInterface`  
_L14-52_
- inherits: `FDerivedDataPluginInterface`
- L17 _public prototype_ `FDerivedDataGeometryCollectionCooker(UGeometryCollection& InGeometryCollection);`
- L19 _public function_ `virtual const TCHAR* GetPluginName() const override`
- L24 _public prototype_ `virtual const TCHAR* GetVersionString() const override;`
- L27 _public prototype_ `virtual FString GetPluginSpecificCacheKeySuffix() const override;`
- L30 _public function_ `virtual bool IsBuildThreadsafe() const override`
- L35 _public function_ `virtual bool IsDeterministic() const override`
- L40 _public prototype_ `virtual FString GetDebugContextString() const override;`
- L42 _public prototype_ `virtual bool Build(TArray<uint8>& OutData) override;`
- L45 _public function_ `bool CanBuild() const` — Return true if we can build
- L51 _private member_ `UGeometryCollection& GeometryCollection;`

#### class `FDerivedDataGeometryCollectionRenderDataCooker`  
`class FDerivedDataGeometryCollectionRenderDataCooker : public FDerivedDataPluginInterface`  
_L55-74_
- inherits: `FDerivedDataPluginInterface`
- L58 _public function_ `FDerivedDataGeometryCollectionRenderDataCooker(UGeometryCollection& InGeometryCollection) : GeometryCollection(InGeometryCollection)`
- L60 _public function_ `virtual const TCHAR* GetPluginName() const override`
- L61 _public prototype_ `virtual const TCHAR* GetVersionString() const override;`
- L62 _public prototype_ `virtual FString GetPluginSpecificCacheKeySuffix() const override;`
- L63 _public function_ `virtual bool IsBuildThreadsafe() const override`
- L64 _public function_ `virtual bool IsDeterministic() const override`
- L65 _public prototype_ `virtual FString GetDebugContextString() const override;`
- L66 _public prototype_ `virtual bool Build(TArray<uint8>& OutData) override;`
- L68 _public function_ `bool CanBuild() const`
- L70 _public member_ `static const TCHAR* VersionString;`
- L73 _private member_ `UGeometryCollection& GeometryCollection;`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionActor.h` (Public)


#### class `AGeometryCollectionActor`  
`class AGeometryCollectionActor: public AActor`  
_L19-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L25 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L30 _public member_ `TObjectPtr<UGeometryCollectionComponent> GeometryCollectionComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destruction, meta = (ExposeFunctionCategories = "Components|GeometryCollection", AllowPrivateAccess = "true"))` — GeometryCollectionComponent
- L31 _public function_ `UGeometryCollectionComponent* GetGeometryCollectionComponent() const`
- L35 _public member_ `TObjectPtr<UGeometryCollectionDebugDrawComponent> GeometryCollectionDebugDrawComponent_DEPRECATED;` — `UPROPERTY()`
- L40 _public prototype_ `bool RaycastSingle(FVector Start, FVector End, FHitResult& OutHit) const;` — `UE_DEPRECATED(5.8, "RaycastSingle is now deprecated, use regular Unreal trace system to query geometry collections")` — `UFUNCTION(BlueprintCallable, Category = "Physics")`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionBlueprintLibrary.h` (Public)


#### class `UGeometryCollectionBlueprintLibrary`  
`class UGeometryCollectionBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L13-54_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GeometryCollectionLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint library for Geometry Collections.
- L26 _public prototype_ `static void SetCustomInstanceDataByIndex(UGeometryCollectionComponent* GeometryCollectionComponent, int32 CustomDataIndex, float CustomDataValue);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Set a custom instance data value for all instances associated with a geometry collection. This assumes that the geometry collection is using a custom renderer that supports IGeometryCollectionCustomDataInterface. @param GeometryCollectionComponent	The Geometry Collection Component that we want to set custom instance data on. @param CustomDataIndex	The index of the custom instance data slot that we want to set. @param CustomDataValue	The value to set to the custom instance data slot.
- L36 _public prototype_ `static void SetCustomInstanceDataByName(UGeometryCollectionComponent* GeometryCollectionComponent, FName CustomDataName, float CustomDataValue);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Set a custom instance data value for all instances associated with a geometry collection. This assumes that the geometry collection is using a custom renderer that supports IGeometryCollectionCustomDataInterface. @param GeometryCollectionComponent	The Geometry Collection Component that we want to set custom instance data on. @param CustomDataName	The name of the custom instance data slot that we want to set. @param CustomDataValue	The value to set to the custom instance data slot.
- L46 _public prototype_ `static void SetCustomDepthStencil(UGeometryCollectionComponent* GeometryCollectionComponent, bool bEnable, int32 CustomStencilValue);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Specify custom depth and a value to write during the custom depth pass for all instances associated with a geometry collection. This assumes that the geometry collection is using a custom renderer that supports IGeometryCollectionCustomDataInterface. @param GeometryCollectionComponent	The Geometry Collection Component that we want to set custom depth data on. @param bEnable	Enable or disable custom depth writing. @param CustomStencilValue	The value which will be written to the stencil buffer during the custom depth pass if bEnable is true.
- L50 _public prototype_ `static void SetISMPoolCustomInstanceData(UGeometryCollectionComponent* GeometryCollectionComponent, int32 CustomDataIndex, float CustomDataValue);` — `UE_DEPRECATED(5.5, "Use SetCustomInstanceDataByIndex() instead")` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics", meta = (DeprecatedFunction, DeprecationMessage = "Use SetCustomInstanceDataByIndex() instead"))`
- L53 _public prototype_ `static bool AddGeometryCollectionsToBlueprint(UBlueprint* Blueprint, const TArray<UObject*>& Collections);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYCOLLECTIONENGINE_API`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionCache.h` (Public)


#### class `UGeometryCollectionCache`  
`class UGeometryCollectionCache : public UObject`  
_L15-73_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UObject`
- L22 _public member_ `static FName TagName_Name;` — Tagnames for asset registry tags
- L23 _public member_ `static FName TagName_IdGuid;` — ID GUID for the cache - never changes for a given cache
- L24 _public member_ `static FName TagName_StateGuid;` — State GUID - changes when an edit is made to
- L30 _public prototype_ `void SetFromRawTrack(const FRecordedTransformTrack& InTrack);` — Given a raw track with transforms per-particle on each frame record, set to this cache and strip out any data we don't need (transform repeats and disabled particles etc.)
- L33 _public prototype_ `void SetFromTrack(const FRecordedTransformTrack& InTrack);` — Set directly from a track, does not do any data stripping.
- L36 _public prototype_ `void SetSupportedCollection(const UGeometryCollection* InCollection);` — Sets the geometry collection that this cache supports, empties the recorded data in this cache
- L39 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;` — UObject Interface
- L41 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L45 _public function_ `const FRecordedTransformTrack* GetData() const` — Access the recorded tracks
- L48 _public prototype_ `static UGeometryCollectionCache* CreateCacheForCollection(const UGeometryCollection* InCollection);` — Given a collection, create an empty compatible cache for it
- L51 _public function_ `FGuid GetCompatibleStateGuid() const` — Get the GUID for the state of the supported collection when this cache was last recorded to.
- L54 _public prototype_ `bool CompatibleWithForRecord(const UGeometryCollection* InCollection);` — Tests whether a cache is compatible with a provided collection
- L55 _public prototype_ `bool CompatibleWithForPlayback(const UGeometryCollection* InCollection);`
- L59 _private prototype_ `void ProcessRawRecordedDataInternal(const FRecordedTransformTrack& InTrack);`
- L63 _private member_ `FRecordedTransformTrack RecordedData;` — `UPROPERTY()` — The recorded data from the simulation
- L67 _private member_ `TObjectPtr<const UGeometryCollection> SupportedCollection;` — `UPROPERTY()` — The collection that we recorded the data from
- L71 _private member_ `FGuid CompatibleCollectionState;` — `UPROPERTY()` — Guid pulled from the collection when the recording was last saved

#### class `ITargetCacheProvider`  
`class ITargetCacheProvider : public IModularFeature`  
_L80-85_
- inherits: `IModularFeature`
- desc: Provider for target caches when recording is requested but we don't have a target cache Initial purpose is to allow an opaque way to call some editor system to generate new assets but this could be expanded later for runtime recording and playback if the need arises
- L83 _public function_ `static FName GetFeatureName()`
- L84 _public prototype_ `virtual UGeometryCollectionCache* GetCacheForCollection(const UGeometryCollection* InCollection) = 0;`

#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryCollectionCache, Log, All);`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionComponent.h` (Public)


#### enum `GeometryCollection::ESelectionMode`  
`enum class ESelectionMode : uint8`  
_L66-78_
- L68 _public enumerator_ `None = 0`
- L69 _public enumerator_ `AllGeometry`
- L70 _public enumerator_ `InverseGeometry`
- L71 _public enumerator_ `Siblings`
- L72 _public enumerator_ `Neighbors`
- L73 _public enumerator_ `Parent`
- L74 _public enumerator_ `Children`
- L75 _public enumerator_ `Level`
- L76 _public enumerator_ `Leaves`
- L77 _public enumerator_ `Clusters`

#### struct `FGeomComponentCacheParameters`  
`struct FGeomComponentCacheParameters`  
_L82-167_
- reflection: `USTRUCT()`
- L86 _public prototype_ `FGeomComponentCacheParameters();`
- L90 _public member_ `EGeometryCollectionCacheType CacheMode;` — `UPROPERTY(EditAnywhere, Category = Cache)` — Cache mode, whether disabled, playing or recording
- L94 _public member_ `TObjectPtr<UGeometryCollectionCache> TargetCache;` — `UPROPERTY(EditAnywhere, Category = Cache)` — The cache to target when recording or playing
- L98 _public member_ `float ReverseCacheBeginTime;` — `UPROPERTY(EditAnywhere, Category = Cache)` — Cache mode, whether disabled, playing or recording
- L102 _public member_ `bool SaveCollisionData;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Record Collision Data"))` — Whether to buffer collisions during recording
- L106 _public member_ `bool DoGenerateCollisionData;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Generate Collision Data during Playback"))` — Whether to generate collisions during playback
- L110 _public member_ `int32 CollisionDataSizeMax;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Collision Data Size Maximum"))` — Maximum size of the collision buffer
- L114 _public member_ `bool DoCollisionDataSpatialHash;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Spatial Hash Collision Data"))` — Spatial hash collision data
- L118 _public member_ `float CollisionDataSpatialHashRadius;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Spatial Hash Radius"))` — Spatial hash radius for collision data
- L122 _public member_ `int32 MaxCollisionPerCell;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Maximum Number of Collisions Per Cell"))` — Maximum number of collisions per cell
- L126 _public member_ `bool SaveBreakingData;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Record Breaking Data"))` — Whether to buffer breakings during recording
- L130 _public member_ `bool DoGenerateBreakingData;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Generate Breaking Data during Playback"))` — Whether to generate breakings during playback
- L134 _public member_ `int32 BreakingDataSizeMax;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Breaking Data Size Maximum"))` — Maximum size of the breaking buffer
- L138 _public member_ `bool DoBreakingDataSpatialHash;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Spatial Hash Breaking Data"))` — Spatial hash breaking data
- L142 _public member_ `float BreakingDataSpatialHashRadius;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Spatial Hash Radius"))` — Spatial hash radius for breaking data
- L146 _public member_ `int32 MaxBreakingPerCell;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Maximum Number of Breakings Per Cell"))` — Maximum number of breaking per cell
- L150 _public member_ `bool SaveTrailingData;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Record Trailing Data"))` — Whether to buffer trailings during recording
- L154 _public member_ `bool DoGenerateTrailingData;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Generate Trailing Data during Playback"))` — Whether to generate trailings during playback
- L158 _public member_ `int32 TrailingDataSizeMax;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Trailing Data Size Maximum"))` — Maximum size of the trailing buffer
- L162 _public member_ `float TrailingMinSpeedThreshold;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Trailing Minimum Speed Threshold"))` — Minimum speed to record trailing
- L166 _public member_ `float TrailingMinVolumeThreshold;` — `UPROPERTY(EditAnywhere, Category = Cache, meta = (DisplayName = "Trailing Minimum Volume Threshold"))` — Minimum volume to record trailing

#### enum `GeometryCollection::EEditUpdate`  
`enum class EEditUpdate : uint8`  
_L172-186_
- desc: Type of updates used at the end of an edit operation.
- L175 _public enumerator_ `None = 0` — No update.
- L177 _public enumerator_ `Rest = 1 << 0` — Mark the rest collection as changed.
- L179 _public enumerator_ `Physics = 1 << 1` — Recreate the physics state (proxy).
- L181 _public enumerator_ `Dynamic = 1 << 2` — Reset the dynamic collection.
- L183 _public enumerator_ `RestPhysics = Rest | Physics` — Mark the rest collection as changed, and recreate the physics state (proxy).
- L185 _public enumerator_ `RestPhysicsDynamic = Rest | Physics | Dynamic` — Reset dynamic collection, mark the rest collection as changed, and recreate the physics state (proxy).

#### class `FGeometryCollectionEdit`  
`class FGeometryCollectionEdit`  
_L200-220_
- desc: FGeometryCollectionEdit Structured RestCollection access where the scope of the object controls serialization back into the dynamic collection This will force any simulating geometry collection out of the solver so it can be edited and afterwards will recreate the proxy The update can also be specified to reset the dynamic collection
- L209 _public prototype_ `FGeometryCollectionEdit(UGeometryCollectionComponent* InComponent, GeometryCollection::EEditUpdate EditUpdate = GeometryCollection::EEditUpdate::RestPhysicsDynamic, bool bShapeIsUnchanged = false, bool bPropagateToAllMatchingComponents = true);` — @param InComponent					The component to edit @param EditUpdate					What parts of the geometry collection to update @param bShapeIsUnchanged				Override indicating the overall shape of the geometry and clusters is unchanged, even if the rest collection changed.  Useful to e.g., not re-compute convex hulls when we don't need to. @param bPropagateAcrossComponents	Propagate updates to all components with the same underlying Rest Collection
- L210 _public prototype_ `~FGeometryCollectionEdit();`
- L212 _public prototype_ `UGeometryCollection* GetRestCollection();`
- L215 _private member_ `UGeometryCollectionComponent* Component;`
- L216 _private member_ `const GeometryCollection::EEditUpdate EditUpdate;`
- L217 _private member_ `TSet<UGeometryCollectionComponent*> HadPhysicsState;`
- L218 _private member_ `bool bShapeIsUnchanged;`
- L219 _private member_ `bool bPropagateToAllMatchingComponents;`

#### class `FScopedColorEdit`  
`class FScopedColorEdit`  
_L223-266_
- L226 _public prototype_ `FScopedColorEdit(UGeometryCollectionComponent* InComponent, bool bForceUpdate = false);`
- L227 _public prototype_ `~FScopedColorEdit();`
- L229 _public prototype_ `void SetShowBoneColors(bool ShowBoneColorsIn);`
- L230 _public prototype_ `bool GetShowBoneColors() const;`
- L232 _public prototype_ `void SetEnableBoneSelection(bool ShowSelectedBonesIn);`
- L233 _public prototype_ `bool GetEnableBoneSelection() const;`
- L235 _public prototype_ `bool IsBoneSelected(int BoneIndex) const;`
- L236 _public prototype_ `void Sanitize();`
- L237 _public prototype_ `void SetSelectedBones(const TArray<int32>& SelectedBonesIn);`
- L238 _public prototype_ `void AppendSelectedBones(const TArray<int32>& SelectedBonesIn);`
- L239 _public prototype_ `void ToggleSelectedBones(const TArray<int32>& SelectedBonesIn, bool bAdd, bool bSnapToLevel = true);`
- L240 _public prototype_ `void AddSelectedBone(int32 BoneIndex);`
- L241 _public prototype_ `void ClearSelectedBone(int32 BoneIndex);`
- L242 _public prototype_ `const TArray<int32>& GetSelectedBones() const;`
- L243 _public prototype_ `void ResetBoneSelection();`
- L244 _public prototype_ `void SelectBones(GeometryCollection::ESelectionMode SelectionMode);`
- L245 _public prototype_ `void FilterSelectionToLevel(bool bPreferLowestOnly = false);`
- L246 _public prototype_ `int32 GetMaxSelectedLevel(bool bOnlyRigid) const;`
- L247 _public prototype_ `bool IsSelectionValidAtLevel(int32 TargetLevel) const;`
- L249 _public prototype_ `bool IsBoneHighlighted(int BoneIndex) const;`
- L250 _public prototype_ `void SetHighlightedBones(const TArray<int32>& HighlightedBonesIn, bool bHighlightChildren = false);`
- L251 _public prototype_ `void AddHighlightedBone(int32 BoneIndex);`
- L252 _public prototype_ `const TArray<int32>& GetHighlightedBones() const;`
- L253 _public prototype_ `void ResetHighlightedBones();`
- L255 _public prototype_ `void SetLevelViewMode(int ViewLevel);`
- L256 _public prototype_ `int GetViewLevel();`
- L259 _private prototype_ `void UpdateBoneColors();`
- L261 _private member_ `bool bUpdated;`
- L264 _private member_ `UGeometryCollectionComponent * Component;`
- L265 _private member_ `static TArray<FLinearColor> RandomColors;`

#### struct `FGeometryCollectionClusterRep`  
`struct FGeometryCollectionClusterRep`  
_L296-355_
- desc: Raw struct to serialize for network. We need to custom netserialize to optimize the vector serialize as much as possible and rather than have the property system iterate an array of reflected structs we handle everything in the NetSerialize for the container (FGeometryCollectionClusterRep)
- L339 _public member_ `FVector_NetQuantize100 Position;`
- L340 _public member_ `FVector_NetQuantize100 LinearVelocity;`
- L341 _public member_ `FVector_NetQuantize100 AngularVelocity;`
- L342 _public member_ `FQuat Rotation;`
- L343 _public member_ `uint16 ClusterIdx;` — index of the cluster or one of its child if the cluster is internal ( see ClusterState)
- L344 _public member_ `FClusterState ClusterState;`
- L346 _public function_ `bool ClusterChanged(const FGeometryCollectionClusterRep& Other) const`

#### struct `FGeometryCollectionClusterRep::FClusterState`  
`struct FClusterState`  
_L298-337_
- L300 _public member_ `static constexpr uint8 StateMask = 0b111;`
- L301 _public member_ `static constexpr uint8 StateOffset = 0;`
- L302 _public member_ `static constexpr uint8 InternalClusterMask = 0b1;`
- L303 _public member_ `static constexpr uint8 InternalClusterOffset = 3;`
- L305 _public function_ `void SetMaskedValue(uint8 Val, uint8 Mask, uint8 Offset)`
- L311 _public function_ `uint8 GetMaskedValue(uint8 Mask, uint8 Offset) const`
- L316 _public function_ `void SetObjectState(Chaos::EObjectStateType State)`
- L321 _public function_ `void SetInternalCluster(bool bInternalCluster)`
- L326 _public function_ `Chaos::EObjectStateType GetObjectState()`
- L331 _public function_ `bool IsInternalCluster() const`
- L336 _public member_ `uint8 Value = 0;`

#### struct `FGeometryCollectionActivatedCluster`  
`struct FGeometryCollectionActivatedCluster`  
_L357-374_
- L359 _public prototype_ `FGeometryCollectionActivatedCluster() = default;`
- L360 _public function_ `FGeometryCollectionActivatedCluster(uint16 Index, const FVector& InitialLinearVel, const FVector& InitialAngularVel ) : ActivatedIndex(Index) , InitialLinearVelocity(InitialLinearVel) , InitialAngularVelocity(InitialAngularVel)`
- L366 _public member_ `uint16 ActivatedIndex;`
- L367 _public member_ `FVector_NetQuantize100 InitialLinearVelocity;`
- L368 _public member_ `FVector_NetQuantize100 InitialAngularVelocity;`
- L370 _public function_ `bool operator==(const FGeometryCollectionActivatedCluster& Other) const`

#### struct `FGeometryCollectionRepData`  
`struct FGeometryCollectionRepData`  
_L390-432_
- reflection: `USTRUCT()`
- desc: Replicated data for a geometry collection when bEnableReplication is true for that component. See UGeomtryCollectionComponent::UpdateRepData
- L394 _public function_ `FGeometryCollectionRepData() : Version(0), ServerFrame(0), bIsRootAnchored(false)`
- L401 _public member_ `TArray<FGeometryCollectionActivatedCluster> OneOffActivated;` — Array of one off pieces that became activated
- L404 _public member_ `TArray<FGeometryCollectionClusterRep> Clusters;` — Array of cluster data requires to synchronize clients
- L408 _public member_ `int32 Version;` — Version counter, every write to the rep data is a new state so Identical only references this version as there's no reason to compare the Poses array.
- L411 _public member_ `int32 ServerFrame;` — For Network Prediction Mode we require the frame number on the server when the data was gathered
- L414 _public member_ `TOptional<float> RepDataReceivedTime;` — The sim-time that this rep data was received
- L417 _public member_ `bool bIsRootAnchored;` — Is the root particle of the GC currently anchored
- L420 _public prototype_ `bool Identical(const FGeometryCollectionRepData* Other, uint32 PortFlags) const;` — Just test version to skip having to traverse the whole pose array for replication
- L421 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`
- L424 _public prototype_ `bool HasChanged(const FGeometryCollectionRepData& BaseData) const;` — Check if the data has changed
- L426 _public function_ `void Reset()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryCollectionRepData> : public TStructOpsTypeTraitsBase2<FGeometryCollectionRepData>`  
_L435-442_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryCollectionRepData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L438-441_

#### struct `FGeometryCollectionRepStateData`  
`struct FGeometryCollectionRepStateData`  
_L450-497_
- reflection: `USTRUCT()`
- desc: Replicated state data for a geometry collection when bEnableReplication is true for that component. State data means what is broken and what is not See UGeomtryCollectionComponent::UpdateRepData
- L454 _public function_ `FGeometryCollectionRepStateData() : Version(0) , bIsRootAnchored(false)`
- L461 _public prototype_ `bool SetBroken(int32 TransformIndex, int32 NumTransforms, bool bDisabled, const FVector& LinV, const FVector& AngVInRadiansPerSecond);` — mark a transform as broken nd return true if this was a state change
- L464 _public member_ `int32 Version;` — version for fast comparison
- L467 _public member_ `TBitArray<> BrokenState;` — broken state of each piece of the GC
- L471 _public member_ `uint8 bIsRootAnchored;` — Is the root particle of the GC currently anchored could possibily change in the future to also be a bit array
- L482 _public member_ `TArray<FReleasedData> ReleasedData;`
- L485 _public prototype_ `bool Identical(const FGeometryCollectionRepStateData* Other, uint32 PortFlags) const;` — Just test version to skip having to traverse the whole pose array for replication
- L486 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`
- L489 _public prototype_ `bool HasChanged(const FGeometryCollectionRepStateData& BaseData) const;` — Check if the data has changed
- L491 _public function_ `void Reset()`

#### struct `FGeometryCollectionRepStateData::FReleasedData`  
`struct FReleasedData`  
_L476-481_
- desc: this represents the data for when a particle is released from its parent cluster this data is added when the particle is released but will be cleared after a while so that late client will not replay the break as it is in their past
- L478 _public member_ `int16 TransformIndex;`
- L479 _public member_ `FVector_NetQuantize10 LinearVelocity;`
- L480 _public member_ `FVector_NetQuantize10 AngularVelocityInDegreesPerSecond;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryCollectionRepStateData> : public TStructOpsTypeTraitsBase2<FGeometryCollectionRepStateData>`  
_L500-507_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryCollectionRepStateData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L503-506_

#### struct `FGeometryCollectionRepDynamicData`  
`struct FGeometryCollectionRepDynamicData`  
_L511-559_
- reflection: `USTRUCT()`
- desc: this structure holds entries for the tracked pieces to be replicated
- L535 _public function_ `FGeometryCollectionRepDynamicData() : Version(0)`
- L539 _public member_ `int32 Version;`
- L540 _public member_ `TArray<FClusterData> ClusterData;`
- L543 _public prototype_ `bool SetData(const FClusterData& Data);` — return true if the data has changed from stored one
- L546 _public prototype_ `bool RemoveOutOfDateClusterData();` — return true if any entries was removed
- L549 _public prototype_ `bool Identical(const FGeometryCollectionRepDynamicData* Other, uint32 PortFlags) const;` — Just test version to skip having to traverse the whole pose array for replication
- L550 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`
- L553 _public prototype_ `bool HasChanged(const FGeometryCollectionRepDynamicData& BaseData) const;` — Check if the data has changed
- L555 _public function_ `void Reset()`

#### struct `FGeometryCollectionRepDynamicData::FClusterData`  
`struct FClusterData`  
_L515-533_
- L517 _public member_ `FVector_NetQuantize10 Position;`
- L518 _public member_ `FVector_NetQuantize10 EulerRotation;`
- L519 _public member_ `FVector_NetQuantize10 LinearVelocity;`
- L520 _public member_ `FVector_NetQuantize10 AngularVelocityInDegreesPerSecond;`
- L523 _public member_ `uint16 TransformIndex = INDEX_NONE;` — Index of the cluster or one of its child if the cluster is internal ( see bIsInternalCluster)
- L526 _public member_ `uint8 bIsInternalCluster = false;` — Whether this refers to an internal cluster or directly to a cluster in the geometry collection
- L529 _public member_ `int32 LastUpdatedVersion = 0;` — non serialized data, used to trimn the data back when no longer updated
- L532 _public prototype_ `bool IsEqualPositionsAndVelocities(const FClusterData& Data) const;` — comp

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryCollectionRepDynamicData> : public TStructOpsTypeTraitsBase2<FGeometryCollectionRepDynamicData>`  
_L562-569_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryCollectionRepDynamicData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L565-568_

#### class `UGeometryCollectionComponent`  
`class UGeometryCollectionComponent : public UMeshComponent, public IChaosNotifyHandlerInterface`  
_L577-1977_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UMeshComponent,IChaosNotifyHandlerInterface`
- desc: GeometryCollectionComponent
- L589 _public prototype_ `virtual ~UGeometryCollectionComponent();`
- L592 _public member_ `static FName DefaultCollisionProfileName;` — Collision profile name that indicates we should use the geometry collection's default collision profile.
- L595 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L599 _public prototype_ `virtual bool ShouldCreateRenderState() const override;`
- L600 _public prototype_ `virtual void CreateRenderState_Concurrent(FRegisterComponentContext* Context) override;`
- L601 _public prototype_ `virtual void SendRenderDynamicData_Concurrent() override;`
- L604 _public function_ `FORCEINLINE void SetRenderStateDirty()` — `UE_DEPRECATED(5.6, "Render state dirty state is now based on the geometry collection change events")`
- L606 _public prototype_ `virtual void SetCollisionObjectType(ECollisionChannel Channel) override;`
- L607 _public prototype_ `virtual void OnActorEnableCollisionChanged() override;`
- L608 _public prototype_ `virtual void BeginPlay() override;`
- L609 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type ReasonEnd) override;`
- L610 _public prototype_ `virtual void OnVisibilityChanged() override;`
- L611 _public prototype_ `virtual void OnActorVisibilityChanged() override;`
- L612 _public prototype_ `virtual void OnHiddenInGameChanged() override;`
- L613 _public prototype_ `virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;`
- L614 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L615 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L618 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L619 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L621 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGeometryCollectionPropertyChangedMulticaster) FOnGeometryCollectionPropertyChangedMulticaster OnGeometryCollectionPropertyChanged;`
- L623 _public typedef_ `typedef FOnGeometryCollectionPropertyChangedMulticaster::FDelegate FOnGeometryCollectionPropertyChanged;`
- L626 _public prototype_ `FDelegateHandle RegisterOnGeometryCollectionPropertyChanged(const FOnGeometryCollectionPropertyChanged& Delegate);` — Register / Unregister delegates called when the skeletal mesh property is changed
- L627 _public prototype_ `void UnregisterOnGeometryCollectionPropertyChanged(FDelegateHandle Handle);`
- L632 _public prototype_ `virtual bool IsNavigationRelevant() const override;`
- L636 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L637 _public function_ `virtual FBoxSphereBounds CalcLocalBounds() const`
- L639 _public prototype_ `virtual bool HasAnySockets() const override;`
- L640 _public prototype_ `virtual bool DoesSocketExist(FName InSocketName) const override;`
- L641 _public prototype_ `virtual FTransform GetSocketTransform(FName InSocketName, ERelativeTransformSpace TransformSpace = RTS_World) const override;`
- L642 _public prototype_ `virtual void QuerySupportedSockets(TArray<FComponentSocketDescription>& OutSockets) const override;`
- L644 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L645 _public prototype_ `virtual void AsyncPhysicsTickComponent(float DeltaTime, float SimTime) override;`
- L651 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L652 _public prototype_ `virtual void OnRegister() override;`
- L653 _public prototype_ `virtual void OnUnregister() override;`
- L654 _public prototype_ `virtual FBodyInstance* GetBodyInstance(FName BoneName = NAME_None, bool bGetWelded = true, int32 Index = -1) const override;`
- L655 _public prototype_ `virtual void SetNotifyRigidBodyCollision(bool bNewNotifyRigidBodyCollision) override;`
- L656 _public prototype_ `virtual bool CanEditSimulatePhysics() override;`
- L657 _public prototype_ `virtual void SetSimulatePhysics(bool bEnabled) override;`
- L658 _public prototype_ `virtual void SetEnableGravity(bool bGravityEnabled) override;`
- L659 _public prototype_ `virtual void AddForce(FVector Force, FName BoneName = NAME_None, bool bAccelChange = false) override;`
- L660 _public prototype_ `virtual void AddForceAtLocation(FVector Force, FVector WorldLocation, FName BoneName = NAME_None) override;`
- L661 _public prototype_ `virtual void AddImpulse(FVector Impulse, FName BoneName = NAME_None, bool bVelChange = false) override;`
- L662 _public prototype_ `virtual void AddImpulseAtLocation(FVector Impulse, FVector WorldLocation, FName BoneName = NAME_None) override;`
- L663 _public prototype_ `virtual void AddRadialForce(FVector Origin, float Radius, float Strength, ERadialImpulseFalloff Falloff, bool bAccelChange = false) override;`
- L664 _public prototype_ `virtual void AddRadialImpulse(FVector Origin, float Radius, float Strength, enum ERadialImpulseFalloff Falloff, bool bVelChange = false) override;`
- L665 _public prototype_ `virtual void AddTorqueInRadians(FVector Torque, FName BoneName = NAME_None, bool bAccelChange = false) override;`
- L666 _public prototype_ `virtual void PostLoad() override;`
- L667 _public prototype_ `virtual void SetPhysMaterialOverride(UPhysicalMaterial* NewPhysMaterial) override;`
- L668 _public prototype_ `virtual void SetLinearDamping(float InDamping) override;`
- L669 _public prototype_ `virtual void SetAngularDamping(float InDamping) override;`
- L672 _protected prototype_ `virtual void OnComponentCollisionSettingsChanged(bool bUpdateOverlaps=true) override;`
- L673 _protected prototype_ `virtual bool CanBeUsedInPhysicsReplication(const FName BoneName = NAME_None) const override;`
- L677 _protected prototype_ `void SetLinearDampingPerTransform(const TArray<int32>& TransformIndices, float InDamping);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")`
- L680 _protected prototype_ `void SetAngularDampingPerTransform(const TArray<int32>& TransformIndices, float InDamping);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")`
- L684 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L685 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L686 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L688 _public prototype_ `virtual FMaterialRelevance GetMaterialRelevance(ERHIFeatureLevel::Type InFeatureLevel) const override;` — `UE_DEPRECATED(5.7, "Please use GetMaterialRelevance with EShaderPlatform argument and not ERHIFeatureLevel::Type")`
- L689 _public prototype_ `virtual FMaterialRelevance GetMaterialRelevance(EShaderPlatform InShaderPlatform) const override;`
- L694 _public member_ `TObjectPtr<AChaosSolverActor> ChaosSolverActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter=GetSolverActor, BlueprintSetter=SetSolverActor, Category = "ChaosPhysics", meta = (DisplayName = "Chaos Solver"))` — Chaos RBD Solver override. Will use the world's default solver actor if null.
- L702 _public function_ `FBox GetLocalBounds() const` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Get local bounds of the geometry collection
- L714 _public prototype_ `void ApplyExternalStrain(int32 ItemIndex, const FVector& Location, float Radius = 0, int32 PropagationDepth = 0, float PropagationFactor = 1, float Strain = 0);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Apply an external strain to specific piece of the geometry collection @param ItemIndex item index ( from HitResult) of the piece to apply strain on @param Location world location of where to apply the strain @param Radius radius from the location point to apply the strain to ( using the center of mass of the pieces ) @param PropagationDepth How many level of connection to follow to propagate the strain through @param PropagationFactor when using propagation, the factor to multiply the strain from one level to the other, allowing falloff effect @param Strain strain / damage to apply
- L726 _public prototype_ `void ApplyInternalStrain(int32 ItemIndex, const FVector& Location, float Radius = 0, int32 PropagationDepth = 0, float PropagationFactor = 1, float Strain = 0);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Apply an internal strain to specific piece of the geometry collection @param ItemIndex item index ( from HitResult) of the piece to apply strain on @param Location world location of where to apply the strain @param Radius radius from the location point to apply the strain to ( using the center of mass of the pieces ) @param PropagationDepth How many level of connection to follow to propagate the strain through @param PropagationFactor when using propagation, the factor to multiply the strain from one level to the other, allowing falloff effect @param Strain strain / damage to apply
- L733 _public prototype_ `void CrumbleCluster(int32 ItemIndex);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Crumbe a cluster into all its pieces @param ItemIndex item index ( from HitResult) of the cluster to crumble
- L740 _public prototype_ `void CrumbleActiveClusters();` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Crumbe active clusters for this entire geometry collection this will apply to internal and regular clusters
- L746 _public prototype_ `void SetAnchoredByIndex(int32 Index, bool bAnchored);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Set a piece or cluster to be anchored or not
- L752 _public prototype_ `void SetAnchoredByBox(FBox WorldSpaceBox, bool bAnchored, int32 MaxLevel = -1);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Set all pieces within a world space bounding box to be anchored or not
- L758 _public prototype_ `void SetAnchoredByTransformedBox(FBox Box, FTransform Transform, bool bAnchored, int32 MaxLevel = -1);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Set all pieces within a world transformed bounding box to be anchored or not
- L764 _public prototype_ `void RemoveAllAnchors();` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — this will remove anchors on all the pieces ( including the static and kinematic initial states ones ) of the geometry colection
- L773 _public prototype_ `void ApplyBreakingLinearVelocity(int32 ItemIndex, const FVector& LinearVelocity);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Apply linear velocity on breaking pieces for a specific cluster If ItemIndex does not represent a cluster this will do nothing @param ItemIndex item index ( from HitResult) of the cluster owning the breaking pieces to apply velocity on @param LinearVelocity linear velocity to apply
- L782 _public prototype_ `void ApplyBreakingAngularVelocity(int32 ItemIndex, const FVector& AngularVelocity);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Apply linear velocity on breaking pieces for a specific cluster If ItemIndex does not represent a cluster this will do nothing @param ItemIndex item index ( from HitResult) of the cluster owning the breaking pieces to apply velocity on @param AngularVelocity linear velocity to apply
- L790 _public prototype_ `void ApplyLinearVelocity(int32 ItemIndex, const FVector& LinearVelocity);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Apply linear velocity on specific piece @param ItemIndex item index ( from HitResult) of the piece to apply velocity on @param LinearVelocity linear velocity to apply
- L798 _public prototype_ `void ApplyAngularVelocity(int32 ItemIndex, const FVector& AngularVelocity);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Apply angular velocity on specific piece @param ItemIndex item index ( from HitResult) of the piece to apply velocity on @param AngularVelocity linear velocity to apply
- L807 _public prototype_ `int32 GetInitialLevel(int32 ItemIndex);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Get the initial level of a specific piece Initial level means the level as it is in the unbroken state @param ItemIndex item index ( from HitResult) of the cluster to get level from @param Level of the piece ( 0 for root level and positive for the rest )
- L811 _public prototype_ `int32 GetRootIndex() const;` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Get the root item index of the hierarchy
- L815 _public prototype_ `FTransform GetRootInitialTransform() const;` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Get the root item initial transform in world space
- L819 _public prototype_ `FTransform GetRootCurrentTransform() const;` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Get the root item current world transform
- L821 _public prototype_ `FTransform GetRootCurrentComponentSpaceTransform() const;`
- L823 _public prototype_ `FTransform GetRootParticleMassOffset() const;`
- L827 _public function_ `bool IsRootBroken() const` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — return true if the root cluster is not longer active at runtime
- L834 _public prototype_ `TArray<FTransform> GetInitialLocalRestTransforms() const;` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Get the initial rest transforms in component (local) space  space, they are the transforms as defined in the rest collection asset
- L842 _public prototype_ `TArray<FTransform> GetLocalRestTransforms(bool bInitialTransforms = false) const;` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Get the rest transforms in component (local) space  space, if none have been set by SetLocalRestTransforms or if RestTransform property is empty , then the initial ones are returned @param bInitialTransform force the initial transforms to be returned ( false by default )
- L849 _public prototype_ `void SetLocalRestTransforms(const TArray<FTransform>& Transforms, bool bOnlyLeaves);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Set the local rest transform, this may be different from the rest collection If the geometry collection is already simulating those matrices will be overriden by the physics state updates
- L857 _public prototype_ `void GetMassAndExtents(int32 ItemIndex, float& OutMass, FBox& OutExtents);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Get mass and extent of a specific piece @param ItemIndex item index ( from HitResult) of the cluster to get level from @param Level of the piece ( 0 for root level and positive for the rest )
- L860 _public prototype_ `virtual float GetMass() const override;` — Returns the mass of this component in kg.
- L863 _public prototype_ `virtual float CalculateMass(FName BoneName = NAME_None) override;` — Returns the calculated mass in kg. This is not 100% exactly the mass physx will calculate, but it is very close ( difference < 0.1kg ).
- L867 _public prototype_ `void SetRestCollection(const UGeometryCollection * RestCollectionIn, bool bApplyAssetDefaults = true);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — RestCollection
- L871 _public prototype_ `void ResetState();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "ChaosPhysics")` — Reset the state of the component : object will be rest to be unbroken and physics will reset accordingly
- L875 _public prototype_ `FString GetDebugInfo();` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — RestCollection
- L877 _public function_ `inline const UGeometryCollection* GetRestCollection() const`
- L879 _public function_ `inline FGeometryCollectionEdit EditRestCollection(GeometryCollection::EEditUpdate EditUpdate = GeometryCollection::EEditUpdate::RestPhysicsDynamic, bool bShapeIsUnchanged = false)`
- L881 _public function_ `inline FScopedColorEdit EditBoneSelection(bool bForceUpdate = false)`
- L884 _public prototype_ `void SelectEmbeddedGeometry();` — Propagate bone selection to embedded geometry components.
- L888 _public prototype_ `void SetEnableDamageFromCollision(bool bValue);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")`
- L892 _public prototype_ `void SetAbandonedParticleCollisionProfileName(FName CollisionProfile);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")`
- L895 _public prototype_ `void SetPerLevelCollisionProfileNames(const TArray<FName>& ProfileNames);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")`
- L898 _public prototype_ `void SetPerParticleCollisionProfileName(const TArray<int32>& BoneIds, FName ProfileName);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")`
- L900 _public prototype_ `void SetPerParticleCollisionProfileName(const TSet<int32>& BoneIds, FName ProfileName);`
- L902 _public prototype_ `void SetParticleCollisionProfileName(int32 BoneId, FName ProfileName, FGCCollisionProfileScopedTransaction& InProfileNameUpdateTransaction);`
- L906 _private prototype_ `bool UpdatePerParticleCollisionProfilesNum();`
- L911 _public prototype_ `int32 GetNumElements(FName Group) const;` — API for getting at geometry collection data
- L914 _public prototype_ `void UpdateCachedBounds();` — Update cached bounds; used e.g. when updating the exploded view of the geometry collection
- L954 _public prototype_ `int32 GetParent(int32 Index) const;`
- L955 _public prototype_ `const TManagedArray<int32>& GetParentArrayRest() const;`
- L958 _public member_ `TObjectPtr<const UGeometryCollection> RestCollection;` — `UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = "ChaosPhysics")`
- L962 _public prototype_ `void ApplyAssetDefaults();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "ChaosPhysics", meta = (EditCondition = "RestCollection != nullptr"))` — Apply default values from asset ( damage related data and physics material )
- L965 _public member_ `TArray<TObjectPtr<const AFieldSystemActor>> InitializationFields;` — `UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = "ChaosPhysics")`
- L968 _public member_ `bool Simulating_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "GeometryCollection now abides the bSimulatePhysics flag from the base class."))`
- L970 _public member_ `ESimulationInitializationState InitializationState;`
- L974 _public member_ `EObjectStateTypeEnum ObjectType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|General")` — ObjectType defines how to initialize the rigid objects state, Kinematic, Sleeping, Dynamic.
- L977 _public member_ `int32 GravityGroupIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetGravityGroupIndex, Category = "ChaosPhysics|General")`
- L980 _public prototype_ `void SetGravityGroupIndex(int32 InGravityGroupIndex);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)`
- L985 _public member_ `int32 OneWayInteractionLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetOneWayInteractionLevel, Category = "ChaosPhysics|General")` — All bodies with a level greater than or equal to this will have One-Way Interaction enabled and act like debris (will not apply forces to non-debris bodies) Set to -1 to disable (no bodies will have One-Way Interaction enabled)
- L988 _public prototype_ `void SetOneWayInteractionLevel(int32 InOneWayInteractionLevel);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)`
- L992 _public member_ `bool bDensityFromPhysicsMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDensityFromPhysicsMaterial, Category = "ChaosPhysics|General")` — when true, density will be used to compute mass using the assigned physics material
- L995 _public prototype_ `void SetDensityFromPhysicsMaterial(bool bInDensityFromPhysicsMaterial);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)`
- L999 _public member_ `bool bForceMotionBlur;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|General")` — If ForceMotionBlur is on, motion blur will always be active, even if the GeometryCollection is at rest.
- L1002 _public member_ `bool EnableClustering;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Clustering")`
- L1006 _public member_ `int32 ClusterGroupIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Clustering")` — Cluster group index - Geometry Collections using the same index will simulate as one single cluster.
- L1010 _public member_ `int32 MaxClusterLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Clustering")` — Maximum level for cluster breaks.
- L1020 _public member_ `int32 MaxSimulatedLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Clustering")` — The maximum level to create rigid bodies that could be simulated. Example: If we have a Geometry Collection with 2 levels, where: 0 = Root 1 = Clusters 2 = Leaf Nodes A setting of '1' would only generate a physics representation of the Root transform and Level 1 clusters. The leaf nodes on Level 2 would never be created on the solver, and would therefore never be considered as part of the simulation.
- L1024 _public member_ `EDamageModelTypeEnum DamageModel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDamageModel, Category = "ChaosPhysics|Damage")` — Damage model to use for evaluating destruction.
- L1027 _public prototype_ `void SetDamageModel(EDamageModelTypeEnum InDamageModel);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)`
- L1030 _public member_ `TArray<float> DamageThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter=GetDamageThreshold, BlueprintSetter=SetDamageThreshold, Category = "ChaosPhysics|Damage", meta = (EditCondition = "!bUseSizeSpecificDamageThreshold && DamageModel == EDamageModelTypeEnum::Chaos_Damage_Model_UserDefined_Damage_Threshold"))`
- L1033 _public function_ `TArray<float> GetDamageThreshold() const` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)`
- L1036 _public prototype_ `void SetDamageThreshold(const TArray<float>& InDamageThreshold);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)`
- L1040 _public member_ `bool bUseSizeSpecificDamageThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Damage", meta = (EditCondition = "DamageModel == EDamageModelTypeEnum::Chaos_Damage_Model_UserDefined_Damage_Threshold"))` — Damage threshold for clusters at different levels.
- L1044 _public member_ `bool bUseMaterialDamageModifiers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetUseMaterialDamageModifiers, Category = "ChaosPhysics|Damage", meta = (EditCondition = "DamageModel == EDamageModelTypeEnum::Chaos_Damage_Model_UserDefined_Damage_Threshold"))` — When on , use the modifiers on the material to adjust the user defined damage threshold values
- L1047 _public prototype_ `void SetUseMaterialDamageModifiers(bool bInUseMaterialDamageModifiers);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)`
- L1051 _public member_ `FGeometryCollectionDamagePropagationData DamagePropagationData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDamagePropagationData, Category = "ChaosPhysics|Damage")` — Data about how damage propagation shoudl behave.
- L1054 _public prototype_ `void SetDamagePropagationData(const FGeometryCollectionDamagePropagationData& InDamagePropagationData);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)`
- L1058 _public member_ `bool bEnableDamageFromCollision;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetEnableDamageFromCollision, Category = "ChaosPhysics|Damage")` — Whether or not collisions against this geometry collection will apply strain which could cause the geometry collection to fracture.
- L1062 _public member_ `bool bAllowRemovalOnSleep;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Removal")` — Allow removal on sleep for the instance if the rest collection has it enabled
- L1066 _public member_ `bool bAllowRemovalOnBreak;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Removal")` — Allow removal on break for the instance if the rest collection has it enabled
- L1070 _public member_ `bool bForceUpdateActiveTransforms;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Clustering")` — Update transforms of active particles even when they are not moving. Has performance implications. Use only when GC is a child of a moving actor, to prevent released particle 'following the actor around'
- L1074 _public member_ `EClusterConnectionTypeEnum ClusterConnectionType_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Connection types are defined on the asset now."))`
- L1078 _public member_ `int32 CollisionGroup;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Collisions")`
- L1082 _public member_ `float CollisionSampleFraction;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Collisions")` — Fraction of collision sample particles to keep
- L1086 _public member_ `float LinearEtherDrag_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use PhysicalMaterial instead."))` — Uniform linear ether drag.
- L1090 _public member_ `TObjectPtr<const UChaosPhysicalMaterial> PhysicalMaterial_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Physical material now derived from render materials, for instance overrides use PhysicalMaterialOverride."))` — Physical Properties
- L1094 _public member_ `EInitialVelocityTypeEnum InitialVelocityType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Initial Velocity")`
- L1098 _public member_ `FVector InitialLinearVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Initial Velocity")`
- L1102 _public member_ `FVector InitialAngularVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Initial Velocity")`
- L1105 _public member_ `TObjectPtr<UPhysicalMaterial> PhysicalMaterialOverride_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Physical material now derived from render materials, for instance overrides use Colliisons PhysicalMaterialOverride."))`
- L1108 _public member_ `FGeomComponentCacheParameters CacheParameters;` — `UPROPERTY()`
- L1112 _public member_ `TArray<FTransform> RestTransforms;` — `UPROPERTY()` — Optional transforms to initialize scene proxy if difference from the RestCollection.
- L1124 _public prototype_ `void ApplyKinematicField(UPARAM(DisplayName = "Field Radius") float Radius, UPARAM(DisplayName = "Center Position") FVe` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Set Dynamic State")` — SetDynamicState This function will dispatch a command to the physics thread to apply a kinematic to dynamic state change for the geo collection particles within the field. @param Radius Radial influence from the position @param Position The location of the command
- L1141 _public prototype_ `void ApplyPhysicsField(UPARAM(DisplayName = "Enable Field") bool Enabled, UPARAM(DisplayName = "Physics Type") EGeometryCollectionPhysicsTypeEnum Target, UPARAM(DisplayName = "Meta Data") UFieldSystemMetaData* MetaData, UPARAM(DisplayName = "Field Node") UFieldNodeBas` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Add Physics Field")` — AddPhysicsField This function will dispatch a command to the physics thread to apply a generic evaluation of a user defined transient field network. See documentation, for examples of how to recreate variations of the above generic fields using field networks @param Enabled Is this force enabled for evaluation. @param Target Type of field supported by the solver. @param MetaData Meta data used to assist in evaluation @param Field Base evaluation node for the field network.
- L1150 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyGeometryCollectionPhysicsStateChange, UGeometryCollectionComponent*, FracturedComponent);`
- L1153 _public member_ `FNotifyGeometryCollectionPhysicsStateChange NotifyGeometryCollectionPhysicsStateChange;` — `UPROPERTY(BlueprintAssignable, Category = "Game|Damage")`
- L1155 _public prototype_ `bool GetIsObjectDynamic() const;`
- L1157 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyGeometryCollectionPhysicsLoadingStateChange, UGeometryCollectionComponent*, FracturedComponent);`
- L1159 _public member_ `FNotifyGeometryCollectionPhysicsLoadingStateChange NotifyGeometryCollectionPhysicsLoadingStateChange;` — `UPROPERTY(BlueprintAssignable, Category = "Game|Loading")`
- L1161 _public function_ `bool GetIsObjectLoading()`
- L1168 _public function_ `bool GetNotifyTrailing() const`
- L1170 _public function_ `void SetShowBoneColors(bool ShowBoneColorsIn)`
- L1171 _public function_ `bool GetShowBoneColors() const`
- L1172 _public function_ `bool GetEnableBoneSelection() const`
- L1174 _public prototype_ `bool GetSuppressSelectionMaterial() const;`
- L1177 _public function_ `const int GetBoneSelectedMaterialID() const` — `UE_DEPRECATED(5.5, "Bone Selected Material does not have a material ID anymore.")`
- L1183 _public function_ `inline const TArray<int32>& GetSelectedBones() const`
- L1184 _public function_ `inline const TArray<int32>& GetHighlightedBones() const`
- L1187 _public prototype_ `FPhysScene_Chaos* GetInnerChaosScene() const;`
- L1188 _public prototype_ `AChaosSolverActor* GetPhysicsSolverActor() const;`
- L1190 _public function_ `const FGeometryCollectionPhysicsProxy* GetPhysicsProxy() const`
- L1191 _public function_ `FGeometryCollectionPhysicsProxy* GetPhysicsProxy()`
- L1195 _public prototype_ `void EnableTransformSelectionMode(bool bEnable);` — Enable/disable the scene proxy per transform selection mode. When disabled the per material id default selection is used instead.
- L1196 _public function_ `bool GetIsTransformSelectionMode() const`
- L1201 _public function_ `void ForceRenderUpdateConstantData()` — Force render after constant data changes (such as visibility, or hitproxy subsections). Will also work while paused.
- L1204 _public function_ `void ForceRenderUpdateDynamicData()` — Force render after dynamic data changes (such as transforms). Will also work while paused.
- L1209 _public function_ `const TArray<bool>& GetDisabledFlags() const` — `UE_DEPRECATED(5.4, "Disabled flags are no longer used.")` — /
- L1211 _public prototype_ `virtual void OnCreatePhysicsState() override;`
- L1212 _public prototype_ `void RegisterAndInitializePhysicsProxy();`
- L1213 _public prototype_ `virtual void OnDestroyPhysicsState() override;`
- L1214 _public prototype_ `virtual bool ShouldCreatePhysicsState() const override;`
- L1215 _public prototype_ `virtual bool HasValidPhysicsState() const override;`
- L1217 _public prototype_ `virtual bool MoveComponentImpl(const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult* Hit, EMoveComponentFlags MoveFlags, ETeleportType Teleport) override;`
- L1218 _public prototype_ `virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport = ETeleportType::None) override;`
- L1222 _public member_ `TArray<bool> DisabledFlags;` — Mirrored from the proxy on a sync TManagedArray<int32> RigidBodyIds;
- L1223 _public member_ `int32 BaseRigidBodyIndex;`
- L1224 _public member_ `int32 NumParticlesAdded;`
- L1228 _public prototype_ `void SetNotifyBreaks(bool bNewNotifyBreaks);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Changes whether or not this component will get future break notifications.
- L1232 _public prototype_ `void SetNotifyRemovals(bool bNewNotifyRemovals);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Changes whether or not this component will get future removal notifications.
- L1236 _public prototype_ `void SetNotifyCrumblings(bool bNewNotifyCrumblings, bool bNewCrumblingEventIncludesChildren = false);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Changes whether or not this component will get future crumbling notifications.
- L1240 _public prototype_ `void SetNotifyTrailings(bool bNewNotifyTrailings);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Changes whether or not this component will get future trailing notifications.
- L1244 _public prototype_ `void SetNotifyGlobalBreaks(bool bNewNotifyGlobalBreaks);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Changes whether or not this component will get future global break notifications.
- L1248 _public prototype_ `void SetNotifyGlobalCollision(bool bNewNotifyGlobalCollisions);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Changes whether or not this component will get future global collision notifications.
- L1252 _public prototype_ `void SetNotifyGlobalRemovals(bool bNewNotifyGlobalRemovals);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Changes whether or not this component will get future global removal notifications.
- L1256 _public prototype_ `void SetNotifyGlobalCrumblings(bool bNewNotifyGlobalCrumblings, bool bGlobalNewCrumblingEventIncludesChildren);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Changes whether or not this component will get future global crumbling notifications.
- L1260 _public prototype_ `void SetNotifyGlobalTrailings(bool bNewNotifyGlobalTrailings);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Changes whether or not this component will get future global trailing notifications.
- L1263 _public function_ `virtual void NotifyBreak(const FChaosBreakEvent& Event)` — Overrideable native notification
- L1266 _public function_ `virtual void NotifyRemoval(const FChaosRemovalEvent& Event)` — Overrideable native notification
- L1269 _public member_ `FOnChaosBreakEvent OnChaosBreakEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Chaos")`
- L1272 _public member_ `FOnChaosRemovalEvent OnChaosRemovalEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Chaos")`
- L1275 _public member_ `FOnChaosCrumblingEvent OnChaosCrumblingEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Chaos")`
- L1278 _public member_ `FOnChaosBreakEvent OnRootBreakEvent;` — todo(chaos) remove when no longer necessary
- L1280 _public member_ `FOnGeometryCollectionFullyDecayedEvent OnFullyDecayedEvent;`
- L1281 _public member_ `FOnGeometryCollectionRootMovedEvent OnRootMovedEvent;`
- L1282 _public member_ `FOnGeometryCollectionRootMovedNativeEvent OnRootMovedNativeEvent;`
- L1284 _public prototype_ `bool IsFullyDecayed() const;`
- L1286 _public prototype_ `void DispatchBreakEvent(const FChaosBreakEvent& Event);`
- L1288 _public prototype_ `void DispatchRemovalEvent(const FChaosRemovalEvent& Event);`
- L1290 _public prototype_ `void DispatchCrumblingEvent(const FChaosCrumblingEvent& Event);`
- L1293 _public member_ `float DesiredCacheTime;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite, Interp, Category = "Chaos")`
- L1296 _public member_ `bool CachePlayback;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite, Category = "Chaos")`
- L1298 _public prototype_ `bool DoCustomNavigableGeometryExport(FNavigableGeometryExport& GeomExport) const override;`
- L1301 _public prototype_ `UPhysicalMaterial* GetPhysicalMaterial() const;` — Gets the physical material to use for this geometry collection, taking into account instance overrides and render materials
- L1304 _public prototype_ `void InitializeEmbeddedGeometry();` — Update component structure to reflect any changes to the embedded geometry
- L1307 _public prototype_ `void RefreshEmbeddedGeometry();` — Update instanced static mesh components to reflect internal embedded geometry state.
- L1310 _public prototype_ `void SetEmbeddedGeometrySelectable(bool bSelectableIn);`
- L1311 _public prototype_ `void ForceNativeRendering(bool bForce);`
- L1312 _public prototype_ `int32 EmbeddedIndexToTransformIndex(const UInstancedStaticMeshComponent* ISMComponent, int32 InstanceIndex) const;`
- L1313 _public prototype_ `void GetBoneColors(TArray<FColor>& OutColors) const;`
- L1314 _public prototype_ `void GetHiddenTransforms(TArray<bool>& OutHiddenTransforms) const;`
- L1317 _public prototype_ `void GetRestTransforms(TArray<FMatrix44f>& OutRestTransforms) const;`
- L1320 _public prototype_ `const FDamageCollector* GetRunTimeDataCollector() const;`
- L1324 _public prototype_ `void SetRestState(TArray<FTransform>&& InRestTransforms);` — #todo should this only be available in editor?
- L1327 _public prototype_ `void ResetRestTransforms();` — this reset the rest transform to use the rest collection asset ones
- L1330 _public prototype_ `void SetDynamicState(const Chaos::EObjectStateType& NewDynamicState);` — Set the dynamic state for all bodies in the DynamicCollection.
- L1333 _public prototype_ `void SetInitialTransforms(const TArray<FTransform>& InitialTransforms);` — Set transforms for all bodies in the DynamicCollection.
- L1336 _public prototype_ `void SetInitialClusterBreaks(const TArray<int32>& ReleaseIndices);` — Modify DynamicCollection transform hierarchy to effect cluster breaks releasing the specified indices.
- L1340 _public function_ `TArray<FMatrix> GetGlobalMatrices()` — `UE_DEPRECATED(5.3, "Use GetComponentSpaceTransforms instead")` — Used by Niagara DI to query global matrices rather than recalculating them again
- L1343 _public prototype_ `TArray<FTransform> GetComponentSpaceTransforms();` — `UE_DEPRECATED(5.4, "Use GetComponentSpaceTransforms3f instead")`
- L1345 _public prototype_ `const TArray<FTransform3f>& GetComponentSpaceTransforms3f();`
- L1352 _public prototype_ `TArray<FTransform> GetCurrentTransforms();` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Get current transforms The transforms are representing the center of mass of each piece and are in component space
- L1359 _public prototype_ `TArray<FTransform> GetCurrentTransformsFromIndices(const TArray<int32>& TransformIndices);` — `UFUNCTION(BlueprintCallable, Category = "ChaosPhysics")` — Get current transforms from a specific list of indices The transforms are representing the center of mass of each piece and are in component space
- L1361 _public prototype_ `const FGeometryDynamicCollection* GetDynamicCollection() const;`
- L1362 _public prototype_ `FGeometryDynamicCollection* GetDynamicCollection();` — TEMP HACK?
- L1364 _public function_ `void SetUpdateNavigationInTick(const bool bUpdateInTick)`
- L1366 _public function_ `void SetUseRootProxyForNavigation(const bool bUseRootProxyForNav)`
- L1370 _public function_ `bool GetUseStaticMeshCollisionForTraces() const` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "Physics")` — todo(chaos): Remove this and move to a cook time approach of the SM data based on the GC property
- L1374 _public prototype_ `void SetUseStaticMeshCollisionForTraces(bool bInUseStaticMeshCollisionForTraces);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "Physics")` — todo(chaos): Remove this and move to a cook time approach of the SM data based on the GC property
- L1377 _public function_ `IGeometryCollectionExternalRenderInterface* GetCustomRenderer()` — Get any custom renderer. Returns nullptr if none is set.
- L1381 _public prototype_ `void ForceBrokenForCustomRenderer(bool bForceBroken);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Force any custom renderer to render using the broken/decayed path. This can be set at runtime
- L1383 _public function_ `bool IsForceBrokenForCustomRenderer() const`
- L1394 _public prototype_ `bool FindLeafTransformByLineTrace(const FVector Start, const FVector End, int32& LeafTransformIndex, FName& LeafTransformName) const;` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Find a leaf transform from a line trace @param Start Start position for the line trace @param End position for the line trace @param LeafTransformIndex the index of leaf transform found by the line trace @param LeafTransformName the name of leaf transform found by the line trace @return true if a leaf was found
- L1402 _public prototype_ `void SetRootProxyComponentSpaceTransform(int32 Index, const FTransform& RootProxyTransform);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — blueprint function to set a specific root proxy local transform warning: when called from C++ and calling it on multiple root proxies it is recommended to use SetRootProxyLocalTransform instead and then call RefreshCustomRenderer to avoid the cost of refreshing the renderer each time
- L1405 _public prototype_ `void SetRootProxyLocalTransform(int32 Index, const FTransform3f& RootProxyTransform);` — Set a specific root proxy local transform
- L1408 _public prototype_ `void ClearRootProxyLocalTransforms();` — clear all the root proxies local transforms - all proxies will now have the same default transform
- L1411 _public prototype_ `static void ReregisterAllCustomRenderers();` — Force all GC components to reregister their custom renderer objects.
- L1414 _public function_ `void SetUpdateCustomRendererOnPostPhysicsSync(bool bValue)` — update of the custom renderer when post physics sync callback is executing ( valid if custom redner is being used ) - true by default
- L1415 _public function_ `bool GetUpdateCustomRendererOnPostPhysicsSync() const`
- L1418 _public function_ `void SetUpdateCustomRenderer(bool bValue)` — `UE_DEPRECATED(5.5, "SetUpdateCustomRenderer() shouldn't be called")`
- L1422 _public function_ `void EnableRootProxyForCustomRenderer(bool bEnable)` — `UE_DEPRECATED(5.5, "Please use ForceBrokenForCustomRenderer() instead")` — `UFUNCTION(BlueprintCallable, Category = "Physics", meta = (DeprecatedFunction, DeprecationMessage = "Please use ForceBrokenForCustomRenderer() instead"))`
- L1424 _public function_ `bool ShouldUpdateComponentTransformToRootBone() const`
- L1426 _public function_ `double GetRootBrokenElapsedTimeInMs() const`
- L1429 _public function_ `void SetEnableReplication(bool bInEnableReplication)` — Attn: these replication methods are helpers meant to be called before the component is fully registered, like a constructor!
- L1430 _public function_ `void SetReplicationAbandonAfterLevel(int32 InReplicationAbandonAfterLevel)`
- L1431 _public function_ `void SetReplicationMaxPositionAndVelocityCorrectionLevel(int32 InReplicationMaxPositionAndVelocityCorrectionLevel)`
- L1433 _public prototype_ `const FTransform& GetPreviousComponentToWorld() const;`
- L1436 _public member_ `FOnChaosPhysicsCollision OnChaosPhysicsCollision;` — `UPROPERTY(BlueprintAssignable, Category = "Collision")`
- L1439 _public prototype_ `void ReceivePhysicsCollision(const FChaosPhysicsCollisionInfo& CollisionInfo);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Physics Collision"), Category = "Collision")`
- L1442 _public prototype_ `virtual void DispatchChaosPhysicsCollisionBlueprintEvents(const FChaosPhysicsCollisionInfo& CollisionInfo) override;` — IChaosNotifyHandlerInterface
- L1446 _public member_ `bool bNotifyBreaks;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events")` — If true, this component will generate breaking events that other systems may subscribe to.
- L1450 _public member_ `bool bNotifyCollisions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events")` — If true, this component will generate collision events that other systems may subscribe to.
- L1454 _public member_ `bool bNotifyTrailing;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events")` — If true, this component will generate trailing events that other systems may subscribe to.
- L1458 _public member_ `bool bNotifyRemovals;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events")` — If true, this component will generate removal events that other systems may subscribe to.
- L1462 _public member_ `bool bNotifyCrumblings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events")` — If true, this component will generate crumbling events that other systems may subscribe to.
- L1466 _public member_ `bool bCrumblingEventIncludesChildren;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events", meta = (EditCondition = "bNotifyCrumblings"))` — If this and bNotifyCrumblings are true, the crumbling events will contain released children indices.
- L1470 _public member_ `bool bNotifyGlobalBreaks;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events|Global")` — If true, this component will generate breaking events that will be listened by the global event relay.
- L1474 _public member_ `bool bNotifyGlobalCollisions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events|Global")` — If true, this component will generate collision events that will be listened by the global event relay.
- L1478 _public member_ `bool bNotifyGlobalRemovals;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events|Global")` — If true, this component will generate removal events that will be listened by the global event relay.
- L1482 _public member_ `bool bNotifyGlobalCrumblings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events|Global")` — If true, this component will generate crumbling events that will be listened by the global event relay.
- L1486 _public member_ `bool bGlobalCrumblingEventIncludesChildren;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events|Global", meta = (EditCondition = "bNotifyGlobalCrumblings"))` — If this and bNotifyGlobalCrumblings are true, the crumbling events will contain released children indices.
- L1490 _public member_ `bool bNotifyGlobalTrailings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|Events|Global")` — If true, this component will generate trailing events that will be listened by the global event relay.
- L1494 _public member_ `bool bStoreVelocities;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChaosPhysics|General")` — If true, this component will save linear and angular velocities on its DynamicCollection.
- L1497 _public member_ `bool bIsCurrentlyNavigationRelevant = true;` — `UPROPERTY(Transient)`
- L1502 _protected member_ `bool bShowBoneColors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|General")` — Display Bone Colors instead of assigned materials
- L1509 _protected member_ `bool bUpdateComponentTransformToRootBone;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|General")` — Move the component each tick to follow the dynamically-simulated root bone; stops once the root breaks. Not supported for kinematic roots or cluster union members.
- L1512 _protected member_ `bool bUseRootProxyForNavigation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, AdvancedDisplay, config)`
- L1515 _protected member_ `bool bUpdateNavigationInTick;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, AdvancedDisplay, config)`
- L1519 _protected member_ `bool bEnableRunTimeDataCollection;` — `UPROPERTY(EditAnywhere, Category = "ChaosPhysics|General")`
- L1522 _protected member_ `FGuid RunTimeDataCollectionGuid;` — `UPROPERTY(BlueprintReadOnly, Category = "ChaosPhysics|General")`
- L1526 _protected member_ `uint8 bForceBrokenForCustomRenderer : 1;` — Force the broken state for custom renderer rendering.
- L1528 _protected member_ `uint8 bUpdateCustomRendererOnPostPhysicsSync : 1;` — Whether to refresh the custom renderer on physics updates.
- L1530 _protected member_ `uint8 bCustomRendererCanUseNativeFallback : 1;` — Custom renderer flag to specify if custom renderer can ever require native fallback.
- L1532 _protected member_ `uint8 bCustomRendererShouldUseNativeFallback : 1;` — Custom renderer flag to specify if custom renderer should use native fallback.
- L1534 _protected member_ `uint8 bForceNativeRenderer : 1;` — Force native geometry collection rendering. This is used in the editor fracture mode.
- L1538 _protected member_ `bool bEnableReplication;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Network)` — Per-instance override to enable/disable replication for the geometry collection
- L1545 _protected member_ `bool bEnableAbandonAfterLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Network)` — Enables use of ReplicationAbandonAfterLevel to stop providing network updates to clients when the updated particle is of a level higher then specified.
- L1552 _protected member_ `FName AbandonedCollisionProfileName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter= SetAbandonedParticleCollisionProfileName, Category = Network)` — Whether abandoned particles on the client should continue to have collision (i.e. still be in the external/internal acceleration structure).
- L1556 _protected member_ `TObjectPtr<AISMPoolActor> ISMPool_DEPRECATED;` — `UPROPERTY()` — Deprecated for CustomRendererType.
- L1560 _protected member_ `TObjectPtr<UClass> CustomRendererType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Rendering", meta = (editcondition = "bOverrideCustomRenderer", MustImplement = "/Script/GeometryCollectionEngine.GeometryCollectionExternalRenderInterface"))` — Custom class type that will be used to render the geometry collection instead of using the native rendering.
- L1564 _protected member_ `bool bOverrideCustomRenderer = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosPhysics|Rendering", meta = (InlineEditConditionToggle))` — If true, CustomRendererType will be used. If false, CustomRendererType comes from the RestCollection.
- L1568 _protected member_ `bool bAutoAssignISMPool_DEPRECATED = false;` — `UPROPERTY()` — Deprecated for CustomRendererType.
- L1570 _protected prototype_ `void CheckFullyDecayed();`
- L1571 _protected member_ `bool bAlreadyFullyDecayed = false;`
- L1575 _protected member_ `bool bUseStaticMeshCollisionForTraces = false;` — `UPROPERTY(EditAnywhere, BlueprintGetter="GetUseStaticMeshCollisionForTraces", BlueprintSetter="SetUseStaticMeshCollisionForTraces", Category = "Physics")` — todo(chaos): Remove the ability to change this at runtime, as we'll want to use this at cook time instead
- L1584 _protected member_ `int32 ReplicationAbandonClusterLevel_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "GeometryCollection now uses ReplicationAbandonAfterLevel instead of ReplicationAbandonClusterLevel."))` — If replicating - the cluster level to stop sending corrections for geometry collection chunks. recommended for smaller leaf levels when the size of the objects means they are no longer gameplay relevant to cut down on required bandwidth to update a collection. @see bEnableAbandonAfterLevel
- L1588 _protected member_ `TScriptInterface<IGeometryCollectionExternalRenderInterface> CustomRenderer;` — `UPROPERTY(SkipSerialization)` — A custom renderer object created from CustomRenderType.
- L1591 _protected prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams) override;` — Collect all the PSO precache data used by the geometry collection
- L1594 _protected prototype_ `FGeometryCollectionDynamicData* InitDynamicData(bool bInitialization = false);` — Populate the dynamic particle data for the render thread.
- L1597 _protected prototype_ `void ResetDynamicCollection();` — Reset the dynamic collection from the current rest state.
- L1600 _protected prototype_ `void GetInitializationCommands(TArray<FFieldSystemCommand>& CombinedCommmands);` — Combine the commands from the input field assets
- L1603 _protected prototype_ `void DispatchFieldCommand(const FFieldSystemCommand& InCommand);` — Issue a field command for the physics thread
- L1605 _protected prototype_ `static Chaos::FPhysicsSolver* GetSolver(const UGeometryCollectionComponent& GeometryCollectionComponent);`
- L1608 _protected function_ `void CalculateLocalBounds()` — `UE_DEPRECATED(5.4, "CalculateLocalBounds is now Deprecated as it does not need to be called anymore, see ComponentSpaceBounds which replace LocalBounds")`
- L1611 _protected prototype_ `FBox ComputeBoundsFromGlobalMatrices(const FMatrix& LocalToWorldWithScale, const TArray<FMatrix>& GlobalMatricesArray) const;` — `UE_DEPRECATED(5.3, "Use ComputeBoundsFromComponentSpaceTransforms instead")`
- L1613 _protected prototype_ `FBox ComputeBoundsFromComponentSpaceTransforms(const FTransform& LocalToWorldWithScale, const TArray<FTransform>& ComponentSpaceTransformsArray) const;`
- L1614 _protected prototype_ `FBox ComputeBoundsFromComponentSpaceTransforms(const FTransform& LocalToWorldWithScale, const TArray<FTransform3f>& ComponentSpaceTransformsArray) const;`
- L1617 _protected prototype_ `FBox ComputeBounds(const FMatrix& LocalToWorldWithScale) const;` — `UE_DEPRECATED(5.3, "Use FTransform version of ComputeBounds instead")`
- L1619 _protected prototype_ `FBox ComputeBounds(const FTransform& LocalToWorldWithScale) const;`
- L1621 _protected prototype_ `void RegisterForEvents();`
- L1622 _protected prototype_ `void UpdateRBCollisionEventRegistration();`
- L1623 _protected prototype_ `void UpdateGlobalCollisionEventRegistration();`
- L1624 _protected prototype_ `void UpdateGlobalRemovalEventRegistration();`
- L1633 _protected member_ `TArray<FName> CollisionProfilePerLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetPerLevelCollisionProfileNames, Category=Physics)` — A per-level collision profile name. If the name is set to NONE or an invalid collision profile, nothing will be changed. If the there are more levels than elements in this array, then each level will use the index that best matches it. For example, if the particle is level 2, and there is only 1 element in the array, then the particle will use the 0th collision profile. AbandonedCollisionProfileName will override this on the client when relevant.
- L1638 _protected member_ `TArray<FName> CollisionProfilePerParticle;` — A per-particle collision profile name. If the per-particle collision profile name exists, it will override the per-level profile name.
- L1645 _protected member_ `int32 ReplicationAbandonAfterLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Network)` — If replicating - the cluster level after which replication will not happen @see bEnableAbandonAfterLevel
- L1655 _protected member_ `int32 ReplicationMaxPositionAndVelocityCorrectionLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Network)` — If replicating - the maximum level where clusters will have their position and velocity send over to the client for tracking and correcting When breaking, client will only receive the initial break velocity This helps save bandwidth where only the destruction state of the GC is to be replicated but the falling pieces do not need to be tracked precisely @note This will have an effect only if set to a value less than ReplicationAbandonAfterLevel @see ReplicationAbandonAfterLevel
- L1658 _protected member_ `FGeometryCollectionRepData RepData;` — `UPROPERTY(ReplicatedUsing=OnRep_RepData)`
- L1661 _protected member_ `FGeometryCollectionRepStateData RepStateData;` — `UPROPERTY(ReplicatedUsing = OnRep_RepStateData)`
- L1664 _protected member_ `FGeometryCollectionRepDynamicData RepDynamicData;` — `UPROPERTY(ReplicatedUsing = OnRep_RepDynamicData)`
- L1668 _protected prototype_ `void OnRep_RepData();` — `UFUNCTION()` — Called post solve to allow authoritative components to update their replication data
- L1671 _protected prototype_ `void OnRep_RepStateData();` — `UFUNCTION()`
- L1674 _protected prototype_ `void OnRep_RepDynamicData();` — `UFUNCTION()`
- L1676 _protected prototype_ `void RequestUpdateRepData();`
- L1677 _protected prototype_ `virtual void UpdateRepData();`
- L1678 _protected prototype_ `virtual void UpdateRepStateAndDynamicData();`
- L1681 _protected prototype_ `virtual void ResetRepData();` — Clear all rep data, this is required if the physics proxy has been recreated
- L1684 _protected prototype_ `virtual void ProcessRepData();` — `UE_DEPRECATED(5.3, "The argument-free version of ProcessRepData will be removed. Please use the version which takes DeltaTime and SimTime instead.")`
- L1686 _protected prototype_ `virtual bool ProcessRepData(float DeltaTime, float SimTime);`
- L1688 _protected member_ `int32 VersionProcessed = INDEX_NONE;`
- L1689 _protected member_ `int32 DynamicRepDataVersionProcessed = INDEX_NONE;`
- L1694 _protected member_ `int64 LastAsyncPhysicsTickMs = 0;` — The last time (in milliseconds) the async physics component tick fired. We track this on the client to be able to turn off the tick for perf reasons if we spend a lot of ticks sequentially doing nothing.
- L1697 _private prototype_ `void ProcessRepDataOnPT();`
- L1698 _private prototype_ `void ProcessRepStateDataOnPT();`
- L1699 _private prototype_ `void ProcessRepDynamicDataOnPT();`
- L1700 _private prototype_ `void InitializeRemovalDynamicAttributesIfNeeded();`
- L1701 _private prototype_ `void SendDynamicDataToSceneProxy();`
- L1705 _private prototype_ `void RestTransformsChanged();` — called when the rest transform are updated from SetRestState / ResetRestTransforms this updates only the renderer, the dynamic collection should be initialized when calling this function
- L1709 _private prototype_ `FTransform3f GetCurrentTransform(int32 Index) const;` — return the most actual transforms this can be the rest collection ones, the overridden RestTransforms or the dynamic collection ones
- L1710 _private prototype_ `void ComputeCurrentGlobalsMatrices(TArray<FTransform3f>& OutTransforms) const;`
- L1712 _private member_ `uint8 bInitializedRemovalDynamicAttribute : 1;`
- L1713 _private member_ `uint8 bEnableBoneSelection : 1;`
- L1714 _private member_ `uint8 IsObjectDynamic : 1;`
- L1715 _private member_ `uint8 IsObjectLoading : 1;`
- L1717 _private member_ `int ViewLevel;`
- L1719 _private member_ `uint32 NavmeshInvalidationTimeSliceIndex;`
- L1721 _private member_ `Chaos::Filter::FShapeFilterData InitialShapeFilterData;`
- L1722 _private member_ `Chaos::Filter::FInstanceData InitialFilterInstanceData;`
- L1723 _private member_ `float CurrentCacheTime;`
- L1724 _private member_ `FChaosUserData PhysicsUserData;`
- L1728 _private member_ `TArray<int32> SelectedBones;` — `UPROPERTY(Transient)`
- L1731 _private member_ `TArray<int32> HighlightedBones;` — `UPROPERTY(Transient)`
- L1735 _private member_ `TArray<FMatrix> GlobalMatrices;` — `UE_DEPRECATED(5.3, "Use ComponentSpaceTransforms instead")`
- L1780 _private member_ `FComponentSpaceTransforms ComponentSpaceTransforms;`
- L1783 _private member_ `mutable FBox RootSpaceBounds;` — bounds for unbroken state bounds in root space
- L1789 _private member_ `mutable FBox ComponentSpaceBounds;` — Bounds in component space if unbroken this will use computed from RootSpaceBounds
- L1791 _private member_ `TArray<bool> EventsPlayed;`
- L1793 _private member_ `FGeometryCollectionPhysicsProxy* PhysicsProxy = nullptr;`
- L1794 _private member_ `TSharedPtr<FGeometryDynamicCollection> DynamicCollection;`
- L1798 _private member_ `TObjectPtr<UBodySetup> DummyBodySetup;` — `UPROPERTY(Transient)` — Temporary storage for body setup in order to initialise a dummy body instance
- L1804 _private member_ `TObjectPtr<AActor> EditorActor;` — `UPROPERTY(Transient)` — Tracked editor actor that owns the original component so we can write back recorded caches from PIE.
- L1806 _private prototype_ `void SwitchRenderModels(const AActor* Actor);`
- L1810 _private member_ `TObjectPtr<UChaosGameplayEventDispatcher> EventDispatcher;` — `UPROPERTY(transient)` — Event dispatcher for break, crumble, removal and collision events
- L1813 _private member_ `bool bIsTransformSelectionModeEnabled;`
- L1818 _private member_ `TArray<TObjectPtr<UInstancedStaticMeshComponent>> EmbeddedGeometryComponents;` — `UPROPERTY()` — The information of all the embedded instanced static meshes
- L1821 _private member_ `TArray<TArray<int32>> EmbeddedBoneMaps;`
- L1822 _private member_ `TArray<int32> EmbeddedInstanceIndex;`
- L1825 _private prototype_ `bool IsEmbeddedGeometryValid() const;`
- L1826 _private prototype_ `void ClearEmbeddedGeometry();`
- L1829 _private prototype_ `bool IsCustomRendererAvailable() const;` — return true if a custom renderer has been set and the feature is enabled
- L1831 _private prototype_ `bool IsUsingCustomRenderer() const;` — return true if a custom renderer is active
- L1833 _private prototype_ `void InitializeCustomRenderer();`
- L1834 _private prototype_ `void RegisterCustomRenderer();`
- L1835 _private prototype_ `void UnregisterCustomRenderer();`
- L1839 _public prototype_ `void RefreshCustomRenderer();` — Updates the custom renderer to the reflect the current state of the Geometry Collection
- L1842 _public prototype_ `void RefreshRootProxies();` — Refresh root proxies whether they are drawn through the custom renderer or normal static mesh components
- L1847 _private prototype_ `bool CanRunSimulationInEditor() const;` — Return true if the simulation can be run in editor
- L1851 _private function_ `AChaosSolverActor* GetSolverActor() const` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)` — BP internal function to get the solver actor
- L1855 _private prototype_ `void SetSolverActor(AChaosSolverActor* InSolverActor);` — `UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)` — BP internal function to set the solver actor
- L1857 _private prototype_ `void IncrementSleepTimer(float DeltaTime);`
- L1858 _private prototype_ `void IncrementBreakTimer(float DeltaTime);`
- L1859 _private prototype_ `bool CalculateInnerSphere(int32 TransformIndex, UE::Math::TSphere<double>& SphereOut) const;`
- L1860 _private prototype_ `void UpdateDecay(int32 TransformIdx, float UpdatedDecay, bool UseClusterCrumbling, bool HasDynamicInternalClusterParent, FGeometryCollectionDecayContext& ContextInOut);`
- L1862 _private prototype_ `void UpdateAttachedChildrenTransform() const;`
- L1864 _private prototype_ `void UpdateRenderSystemsIfNeeded(bool bDynamicCollectionDirty);`
- L1865 _private prototype_ `void UpdateNavigationDataIfNeeded(bool bDynamicCollectionDirty);`
- L1866 _private prototype_ `void UpdateRemovalIfNeeded();`
- L1868 _private prototype_ `void BuildInitialFilterData();`
- L1870 _private prototype_ `void LoadCollisionProfiles();`
- L1872 _private prototype_ `void OnPostPhysicsSync();`
- L1874 _private prototype_ `void OnPostCreateParticles();`
- L1876 _private prototype_ `bool HasVisibleGeometry() const;`
- L1879 _private prototype_ `TArray<FMatrix> ComputeGlobalMatricesFromComponentSpaceTransforms() const;` — backward compatibility method, until we can remove GlobalMatrices
- L1881 _private prototype_ `float ComputeMassScaleRelativeToAsset() const;`
- L1883 _private prototype_ `void MoveComponentToRootTransform();`
- L1886 _private prototype_ `void OnTransformsDirty();` — called when the dynamic collection is found to be dirty
- L1889 _private member_ `TUniquePtr<TSet<Chaos::FPBDRigidClusteredParticleHandle*>> ClustersToRep;` — The clusters we need to replicate
- L1891 _private member_ `double LastHardsnapTimeInMs = 0;`
- L1894 _private member_ `int32 OneOffActivatedProcessed = 0;` — One off activation is processed in the same order as server so remember the last one we processed
- L1899 _public member_ `float AngularEtherDrag_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use PhysicalMaterial instead."))` — Uniform angular ether drag.
- L1932 _private member_ `FBrokenAndDecayedStates BrokenAndDecayedStates;`
- L1934 _private prototype_ `void UpdateBrokenAndDecayedStates();`
- L1936 _private prototype_ `bool ShouldCreateRootProxyComponents() const;`
- L1938 _private member_ `TArray<FTransform3f> RootProxyLocalTransforms;`
- L1949 _private prototype_ `void FlushNetDormancyIfNeeded() const;` — Flushes the net dormancy of our owner if this action is enabled and we are dormant
- L1951 _private prototype_ `ENetAwakeningMode GetDesiredNetAwakeningMode() const;`
- L1955 _public prototype_ `virtual Chaos::FPhysicsObject* GetPhysicsObjectById(Chaos::FPhysicsObjectId Id) const override;`
- L1956 _public prototype_ `virtual Chaos::FPhysicsObject* GetPhysicsObjectByName(const FName& Name) const override;`
- L1957 _public prototype_ `virtual TArray<Chaos::FPhysicsObject*> GetAllPhysicsObjects() const override;`
- L1958 _public prototype_ `virtual Chaos::FPhysicsObjectId GetIdFromGTParticle(Chaos::FGeometryParticle* Particle) const override;`
- L1963 _public prototype_ `virtual bool IsHLODRelevant() const override;`
- L1964 _public prototype_ `virtual TArray<UActorComponent*> GetHLODProxyComponents() const override;`
- L1974 _public prototype_ `void RebaseDynamicCollectionTransformsOnNewWorldTransform();` — Currently, component space transforms for every particle is compute relative to the component transform. By default, this means that when the component transform changes, every particle is shifted along with the component. However, there are times when you may change the component transform but instead want every particle to stay in the same world position. In those cases, RebaseDynamicCollectionTransformsOnNewWorldTransform can be called.

#### struct `UGeometryCollectionComponent::FComponentSpaceTransforms`  
`struct FComponentSpaceTransforms`  
_L1737-1778_
- L1740 _public function_ `FComponentSpaceTransforms(const UGeometryCollectionComponent* InComponent = nullptr) : RootIndex(INDEX_NONE) , Component(InComponent)`
- L1748 _public function_ `void Reset(int32 NumTransforms, int32 InRootIndex)`
- L1755 _public function_ `void MarkDirty()`
- L1761 _public function_ `int32 Num() const`
- L1763 _public function_ `SIZE_T GetAllocatedSize() const`
- L1767 _public prototype_ `const TArray<FTransform3f>& RequestAllTransforms() const;` — request all transform to be update this will trigger an update if it is still marked dirty
- L1770 _public prototype_ `const FTransform3f& RequestRootTransform() const;` — request the root transform, this may compute it if it is still marked dirty
- L1773 _private member_ `int32 RootIndex;`
- L1774 _private member_ `mutable uint8 bIsRootDirty : 1;`
- L1775 _private member_ `mutable uint8 bIsDirty : 1;`
- L1776 _private member_ `mutable TArray<FTransform3f> Transforms;`
- L1777 _private member_ `const UGeometryCollectionComponent* Component;`

#### struct `UGeometryCollectionComponent::FBrokenAndDecayedStates`  
`struct FBrokenAndDecayedStates`  
_L1902-1930_
- L1905 _public prototype_ `void Reset(int32 NumTransforms);`
- L1907 _public function_ `bool GetIsRootBroken() const`
- L1908 _public prototype_ `bool GetIsBroken(int32 TransformIndex) const;`
- L1909 _public prototype_ `bool GetHasDecayed(int32 TransformIndex) const;`
- L1910 _public prototype_ `double GetRootBrokenEventTimeInMs() const;`
- L1911 _public prototype_ `double GetRootBrokenElapsedTimeInMs() const;`
- L1913 _public prototype_ `void SetRootIsBroken(bool bIsBroken);`
- L1914 _public prototype_ `void SetIsBroken(int32 TransformIndex);`
- L1915 _public prototype_ `void SetHasDecayed(int32 TransformIndex);`
- L1916 _public prototype_ `void SetHasDecayedRecursive(int32 TransformIndex, const TArray<TSet<int32>>& Children);`
- L1919 _public prototype_ `bool HasAnyDecaying() const;` — return true if any broken piece is not yet decayed
- L1921 _public prototype_ `bool HasFullyDecayed() const;`
- L1924 _private member_ `int32 NumTransforms = 0;`
- L1925 _private member_ `bool bIsRootBroken = false;`
- L1926 _private member_ `double RootBrokenEventTimeInMs = 0;`
- L1927 _private member_ `TBitArray<> IsBroken;`
- L1928 _private member_ `TBitArray<> HasDecayed;`
- L1929 _private member_ `int32 NumDecaying = 0;`

#### enum `UGeometryCollectionComponent::ENetAwakeningMode`  
`enum class ENetAwakeningMode`  
_L1942-1946_
- L1944 _public enumerator_ `ForceDormancyAwake`
- L1945 _public enumerator_ `FlushNetDormancy`

#### struct `FGCCollisionProfileScopedTransaction`  
`struct FGCCollisionProfileScopedTransaction`  
_L1982-2023_
- desc: Struct to be used as Transaction object used to make updates on particle per particle basis within a scope. It makes sure the collision profile names containers is up to date and the Collision profiles are loaded if needed when it goes out of scope
- L1984 _public function_ `explicit FGCCollisionProfileScopedTransaction(UGeometryCollectionComponent* InGCComponentInstance) : GCComponentInstance(InGCComponentInstance)`
- L1994 _public function_ `~FGCCollisionProfileScopedTransaction()`
- L2007 _public prototype_ `FGCCollisionProfileScopedTransaction& operator=(const FGCCollisionProfileScopedTransaction& Other) = delete;`
- L2008 _public prototype_ `FGCCollisionProfileScopedTransaction& operator=(FGCCollisionProfileScopedTransaction&& Other) = delete;`
- L2009 _public prototype_ `FGCCollisionProfileScopedTransaction(FGCCollisionProfileScopedTransaction&& Other) = delete;`
- L2010 _public prototype_ `FGCCollisionProfileScopedTransaction(FGCCollisionProfileScopedTransaction& Other) = delete;`
- L2013 _public function_ `void MarkDirty()` — Marks this transaction dirty. It will load the collision profiles if needed when this transaction goes out of scope
- L2018 _public function_ `bool IsValid() const`
- L2021 _private member_ `UGeometryCollectionComponent* GCComponentInstance = nullptr;`
- L2022 _private member_ `bool bHasChanged = false;`

#### Free symbols / members of external scopes

- L50 _namespace_ `namespace Chaos`
- L53 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosBreakEvent, const FChaosBreakEvent&, BreakEvent);`
- L53 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosBreakEvent, const FChaosBreakEvent&, BreakEvent);`
- L55 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosRemovalEvent, const FChaosRemovalEvent&, RemovalEvent);`
- L55 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosRemovalEvent, const FChaosRemovalEvent&, RemovalEvent);`
- L57 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosCrumblingEvent, const FChaosCrumblingEvent&, CrumbleEvent);`
- L57 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChaosCrumblingEvent, const FChaosCrumblingEvent&, CrumbleEvent);`
- L59 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGeometryCollectionFullyDecayedEvent);`
- L59 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGeometryCollectionFullyDecayedEvent);`
- L61 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGeometryCollectionRootMovedEvent);`
- L61 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGeometryCollectionRootMovedEvent);`
- L62 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGeometryCollectionRootMovedNativeEvent, UGeometryCollectionComponent*);`
- L62 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGeometryCollectionRootMovedNativeEvent, UGeometryCollectionComponent*);`
- L64 _namespace_ `namespace GeometryCollection`
- L169 _namespace_ `namespace GeometryCollection`
- L187 _prototype_ `ENUM_CLASS_FLAGS(EEditUpdate);` (scope `GeometryCollection`)
- L276 _macro_ `#define COPY_ON_WRITE_ATTRIBUTE(Type, Name, Group) \` — Provides copy on write functionality: GetArray (const access) GetArrayCopyOnWrite GetArrayRest (gives original rest value) This generates pointers to arrays marked private. Macro assumes getters are public todo(ocohen): may want to take in a static name
- L376 _function_ `inline FArchive& operator<<(FArchive& Ar, FGeometryCollectionActivatedCluster& ActivatedCluster)`
- L439 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon512c27790103`)
- L440 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anon512c27790103`)
- L504 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon512c27790203`)
- L505 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anon512c27790203`)
- L566 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon512c27790303`)
- L567 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anon512c27790303`)
- L621 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGeometryCollectionPropertyChangedMulticaster) FOnGeometryCollectionPropertyChangedMulticaster OnGeometryCollectionPropertyChanged;`
- L916 _macro_ `#define COPY_ON_WRITE_ATTRIBUTES \`
- L1150 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyGeometryCollectionPhysicsStateChange, UGeometryCollectionComponent*, FracturedComponent);`
- L1157 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyGeometryCollectionPhysicsLoadingStateChange, UGeometryCollectionComponent*, FracturedComponent);`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionComponentPlugin.h` (Public)


#### class `IGeometryCollectionComponentPlugin`  
`class IGeometryCollectionComponentPlugin : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IGeometryCollectionComponentPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionCreationParameters.h` (Public)


#### class `FGeometryCollectionCreationParameters`  
`class FGeometryCollectionCreationParameters`  
_L9-20_
- L12 _public prototype_ `FGeometryCollectionCreationParameters(FGeometryCollection& GeometryCollection, bool ReCalculateNormalsIn = false, bool ReCalculateTangetsIn = false);`
- L13 _public prototype_ `~FGeometryCollectionCreationParameters();`
- L16 _private member_ `bool ReCalculateNormals;`
- L17 _private member_ `bool ReCalculateTangents;`
- L18 _private member_ `FGeometryCollection& GeometryCollection;`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionDamagePropagationData.h` (Public)


#### struct `FGeometryCollectionDamagePropagationData`  
`struct FGeometryCollectionDamagePropagationData`  
_L8-24_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Propagation")` — Whether or not damage propagation is enabled.
- L19 _public member_ `float BreakDamagePropagationFactor = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Propagation")` — factor of the remaining strain propagated through the connection graph after a piece breaks.
- L23 _public member_ `float ShockDamagePropagationFactor = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Propagation")` — factor of the received strain propagated throug the connection graph if the piece did not break.

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionDebugDraw.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace GeometryCollectionDebugDraw`
- L14 _prototype_ `void DrawSolid(const FGeometryCollection& Collection, const FTransform& CollectionWorldTransform, FMeshElementCollector& MeshCollector, int32 ViewIndex, const FMaterialRenderProxy* MaterialProxy);` (scope `GeometryCollectionDebugDraw`)
- L15 _prototype_ `void DrawWireframe(const FGeometryCollection& Collection, const FTransform& CollectionWorldTransform, FMeshElementCollector& MeshCollector, int32 ViewIndex, const FColor& Color);` (scope `GeometryCollectionDebugDraw`)

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionDebugDrawActor.h` (Public)


#### enum `EGeometryCollectionDebugDrawActorHideGeometry`  
`enum class EGeometryCollectionDebugDrawActorHideGeometry : uint8`  
_L24-36_
- reflection: `UENUM()`
- desc: EGeometryCollectionDebugDrawActorHideGeometry Visibility enum.
- L27 _public enumerator_ `HideNone` — Do not hide any geometry.
- L29 _public enumerator_ `HideWithCollision` — Hide the geometry associated with rigid bodies that are selected for collision volume visualization.
- L31 _public enumerator_ `HideSelected` — Hide the geometry associated with the selected rigid bodies.
- L33 _public enumerator_ `HideWholeCollection` — Hide the entire geometry collection associated with the selected rigid bodies.
- L35 _public enumerator_ `HideAll` — Hide all geometry collections.

#### struct `FGeometryCollectionDebugDrawWarningMessage`  
`struct UE_DEPRECATED(5.0, "Deprecated. Use normal debug draw Chaos Physics commands") FGeometryCollectionDebugDrawWarningMessage`  
_L43-46_
- reflection: `USTRUCT()`
- desc: FGeometryCollectionDebugDrawWarningMessage Empty structure used to embed a warning message in the UI through a detail customization.

#### struct `FGeometryCollectionDebugDrawActorSelectedRigidBody`  
`struct UE_DEPRECATED(5.0, "Deprecated. Use normal debug draw Chaos Physics commands") FGeometryCollectionDebugDrawActorSelectedRigidBody`  
_L53-75_
- reflection: `USTRUCT()`
- desc: FGeometryCollectionDebugDrawActorSelectedRigidBody Structure used to select a rigid body id with a picking tool through a detail customization.
- L57 _public function_ `explicit FGeometryCollectionDebugDrawActorSelectedRigidBody(int32 InId = -1) : Id(InId), Solver(nullptr), GeometryCollection(nullptr)`
- L62 _public member_ `int32 Id;` — `UPROPERTY(EditAnywhere, Category = "Selected Rigid Body", meta = (ClampMin="-1"))` — Id of the selected rigid body whose to visualize debug informations. Use -1 to visualize all Geometry Collections.
- L67 _public member_ `TObjectPtr<AChaosSolverActor> Solver;` — `UPROPERTY(EditAnywhere, Category = "Selected Rigid Body")` — Chaos RBD Solver. Will use the world's default solver actor if null.
- L71 _public member_ `TObjectPtr<AGeometryCollectionActor> GeometryCollection;` — `UPROPERTY(VisibleAnywhere, Category = "Selected Rigid Body")` — Currently selected geometry collection.
- L74 _public prototype_ `FString GetSolverName() const;` — Return the name of selected solver, or "None" if none is selected.

#### class `AGeometryCollectionDebugDrawActor`  
`class AGeometryCollectionDebugDrawActor : public AActor`  
_L86-336_
- reflection: `UE_DEPRECATED(5.0, "Deprecated. Use normal debug draw Chaos Physics commands")`
- reflection: `UCLASS(HideCategories = ("Rendering", "Replication", "Input", "Actor", "Collision", "LOD", "Cooking"), MinimalAPI)`
- inherits: `AActor`
- desc: AGeometryCollectionDebugDrawActor An actor representing the collection of data necessary to visualize the geometry collections' debug informations. Only one actor is to be used in the world, and should be automatically spawned by any GeometryDebugDrawComponent that needs it.
- L93 _public member_ `FGeometryCollectionDebugDrawWarningMessage WarningMessage_DEPRECATED;` — `UPROPERTY()` — Warning message to explain that the debug draw properties have no effect until starting playing/simulating.
- L97 _public member_ `FGeometryCollectionDebugDrawActorSelectedRigidBody SelectedRigidBody_DEPRECATED;` — `UPROPERTY()` — Picking tool used to select a rigid body id.
- L102 _public member_ `bool bDebugDrawWholeCollection;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Show debug visualization for the rest of the geometry collection related to the current rigid body id selection.
- L107 _public member_ `bool bDebugDrawHierarchy;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Show debug visualization for the top level node rather than the bottom leaf nodes of a cluster's hierarchy. * Only affects Clustering and Geometry visualization.
- L111 _public member_ `bool bDebugDrawClustering;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Show debug visualization for all clustered children associated to the current rigid body id selection.
- L115 _public member_ `EGeometryCollectionDebugDrawActorHideGeometry HideGeometry;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw")` — Geometry visibility setting. Select the part of the geometry to hide in order to better visualize the debug information.
- L119 _public member_ `bool bShowRigidBodyId;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Rigid Body")` — Display the selected rigid body's id.
- L123 _public member_ `bool bShowRigidBodyCollision;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Rigid Body")` — Show the selected rigid body's collision volume.
- L127 _public member_ `bool bCollisionAtOrigin;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Rigid Body")` — Show the selected rigid body's collision volume at the origin, in local space.
- L131 _public member_ `bool bShowRigidBodyTransform;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Rigid Body")` — Show the selected rigid body's transform.
- L135 _public member_ `bool bShowRigidBodyInertia;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Rigid Body")` — Show the selected rigid body's inertia tensor box.
- L139 _public member_ `bool bShowRigidBodyVelocity;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Rigid Body")` — Show the selected rigid body's linear and angular velocity.
- L143 _public member_ `bool bShowRigidBodyForce;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Rigid Body")` — Show the selected rigid body's applied force and torque.
- L147 _public member_ `bool bShowRigidBodyInfos;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Rigid Body")` — Show the selected rigid body's on screen text information.
- L151 _public member_ `bool bShowTransformIndex;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Clustering")` — Show the transform index for the selected rigid body's associated cluster nodes.
- L155 _public member_ `bool bShowTransform;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Clustering")` — Show the transform for the selected rigid body's associated cluster nodes.
- L159 _public member_ `bool bShowParent;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Clustering")` — Show a link from the selected rigid body's associated cluster nodes to their parent's nodes.
- L163 _public member_ `bool bShowLevel;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Clustering")` — Show the hierarchical level for the selected rigid body's associated cluster nodes.
- L167 _public member_ `bool bShowConnectivityEdges;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Clustering")` — Show the connectivity edges for the selected rigid body's associated cluster nodes.
- L171 _public member_ `bool bShowGeometryIndex;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Geometry")` — Show the geometry index for the selected rigid body's associated geometries.
- L175 _public member_ `bool bShowGeometryTransform;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Geometry")` — Show the geometry transform for the selected rigid body's associated geometries.
- L179 _public member_ `bool bShowBoundingBox;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Geometry")` — Show the bounding box for the selected rigid body's associated geometries.
- L183 _public member_ `bool bShowFaces;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Geometry")` — Show the faces for the selected rigid body's associated geometries.
- L187 _public member_ `bool bShowFaceIndices;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Geometry")` — Show the face indices for the selected rigid body's associated geometries.
- L191 _public member_ `bool bShowFaceNormals;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Geometry")` — Show the face normals for the selected rigid body's associated geometries.
- L195 _public member_ `bool bShowSingleFace;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Geometry")` — Enable single face visualization for the selected rigid body's associated geometries.
- L199 _public member_ `int32 SingleFaceIndex;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Geometry", meta = (ClampMin="0"))` — The index of the single face to visualize.
- L203 _public member_ `bool bShowVertices;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Geometry")` — Show the vertices for the selected rigid body's associated geometries.
- L207 _public member_ `bool bShowVertexIndices;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Geometry")` — Show the vertex indices for the selected rigid body's associated geometries.
- L211 _public member_ `bool bShowVertexNormals;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Geometry")` — Show the vertex normals for the selected rigid body's associated geometries.
- L215 _public member_ `bool bUseActiveVisualization;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings")` — Adapt visualization depending of the cluster nodes' hierarchical level.
- L219 _public member_ `float PointThickness;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (ClampMin="0"))` — Thickness of points when visualizing vertices.
- L223 _public member_ `float LineThickness;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (ClampMin="0"))` — Thickness of lines when visualizing faces, normals, ...etc.
- L227 _public member_ `bool bTextShadow;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings")` — Draw shadows under the displayed text.
- L231 _public member_ `float TextScale;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (ClampMin="0.0001"))` — Scale of the font used to display text.
- L235 _public member_ `float NormalScale;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (ClampMin="0.0001"))` — Scale factor used for visualizing normals.
- L239 _public member_ `float AxisScale;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (ClampMin="0.0001"))` — Scale of the axis used for visualizing all transforms.
- L243 _public member_ `float ArrowScale;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (ClampMin="0.0001"))` — Size of arrows used for visualizing normals, breaking information, ...etc.
- L247 _public member_ `FColor RigidBodyIdColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the rigid body ids.
- L251 _public member_ `float RigidBodyTransformScale;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (ClampMin="0.0001"))` — Scale for rigid body transform visualization.
- L255 _public member_ `FColor RigidBodyCollisionColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for collision primitives visualization.
- L259 _public member_ `FColor RigidBodyInertiaColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the rigid body inertia tensor box.
- L263 _public member_ `FColor RigidBodyVelocityColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for rigid body velocities visualization.
- L267 _public member_ `FColor RigidBodyForceColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for rigid body applied force and torque visualization.
- L271 _public member_ `FColor RigidBodyInfoColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the rigid body infos.
- L275 _public member_ `FColor TransformIndexColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the transform indices.
- L279 _public member_ `float TransformScale;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (ClampMin="0.0001"))` — Scale for cluster transform visualization.
- L283 _public member_ `FColor LevelColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the levels.
- L287 _public member_ `FColor ParentColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the link from the parents.
- L291 _public member_ `float ConnectivityEdgeThickness;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (ClampMin="0.0001"))` — Line thickness used for the visualization of the rigid clustering connectivity edges.
- L295 _public member_ `FColor GeometryIndexColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the geometry indices.
- L299 _public member_ `float GeometryTransformScale;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (ClampMin="0.0001"))` — Scale for geometry transform visualization.
- L303 _public member_ `FColor BoundingBoxColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the bounding boxes.
- L307 _public member_ `FColor FaceColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the faces.
- L311 _public member_ `FColor FaceIndexColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the face indices.
- L315 _public member_ `FColor FaceNormalColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the face normals.
- L319 _public member_ `FColor SingleFaceColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the single face.
- L323 _public member_ `FColor VertexColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the vertices.
- L327 _public member_ `FColor VertexIndexColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the vertex indices.
- L331 _public member_ `FColor VertexNormalColor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw|Settings", meta = (HideAlphaChannel))` — Color used for the visualization of the vertex normals.
- L335 _public member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY()` — Display icon in the editor.

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionDebugDrawComponent.h` (Public)


#### class `UGeometryCollectionDebugDrawComponent`  
`class UGeometryCollectionDebugDrawComponent : public UActorComponent`  
_L27-43_
- reflection: `UE_DEPRECATED(5.0, "Deprecated. Use normal debug draw Chaos Physics commands")`
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent), HideCategories = ("Tags", "Activation", "Cooking", "AssetUserData", "Collision"), MinimalAPI)`
- inherits: `UActorComponent`
- desc: UGeometryCollectionDebugDrawComponent Component adding debug drawing functionality to a GeometryCollectionActor. This component is automatically added to every GeometryCollectionActor.
- L35 _public member_ `TObjectPtr<AGeometryCollectionDebugDrawActor> GeometryCollectionDebugDrawActor_DEPRECATED;` — `UPROPERTY()` — Singleton actor, containing the debug draw properties. Automatically populated at play time unless explicitly set.
- L40 _public member_ `TObjectPtr<AGeometryCollectionRenderLevelSetActor> GeometryCollectionRenderLevelSetActor;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw", AdvancedDisplay)` — Level Set singleton actor, containing the Render properties. Automatically populated at play time unless explicitly set.
- L42 _public member_ `UGeometryCollectionComponent* GeometryCollectionComponent;` — the component we are debug rendering for, set by the GeometryCollectionActor after creation

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Chaos`
- L17 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionEditorSelection.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define GEOMETRYCOLLECTION_EDITOR_SELECTION WITH_EDITOR`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionEngineConversion.h` (Public)


#### class `FGeometryCollectionEngineConversion`  
`class FGeometryCollectionEngineConversion`  
_L26-246_
- desc: The public interface to this module
- L40 _public prototype_ `static int32 AppendMaterials(const TArray<UMaterialInterface*>& Materials, UGeometryCollection* GeometryCollectionObject, bool bAddInteriorCopy);` — Appends materials to a GeometryCollectionComponent. @param Materials : Materials fetched from the StaticMeshComponent used to configure this geometry @param GeometryCollection  : Collection to append the mesh into.
- L49 _public prototype_ `static void AppendAutoInstanceMeshIndices(UGeometryCollection* GeometryCollectionObject, int32 FromTransformIndex, const UStaticMesh* StaticMesh, const TArray<UMaterialInterface*>& Materials);` — Appends instanced mesh indices @param GeometryCollectionObject geometry collection to add to @param FromTransformIndex transform index to start from @param StaticMesh  static mesh to add reference to @param Materials materials corresponding to the static mesh instance to get the index from
- L61 _public prototype_ `static void AppendMeshDescription(const FMeshDescription* MeshDescription, const FString& Name, int32 StartMaterialIndex, const FTransform& StaticMeshTransform, FGeometryCollection* GeometryCollection, UBodySetup* BodySetup = nullptr, bool bReindexMaterials = true, bool bAddInternalMaterials = true, bool bSetInternalFromMaterialIndex = false);` — Appends a MeshDescription to a GeometryCollection. @param MeshDescription : Const mesh description to read vertex/normals/index data from @param Name : A name to use for the Mesh, e.g. from the source UObject's GetName() @param StartMaterialIndex : Index of materials to be used, e.g. as returned by AppendMaterials() (see below) @param StaticMeshTransform : Mesh transform. @param GeometryCollection  : Collection to append the mesh into. @param BodySetup : Optional collision setup to transfer to the geometry collection @param bReindexMaterials	: Whether to reindex materials -- if appending multiple meshes, pass false and call ReindexMaterials afterwards
- L68 _public prototype_ `static FMeshDescription* GetMaxResMeshDescriptionWithNormalsAndTangents(const UStaticMesh* StaticMesh);` — Get a HiRes (or LOD 0 if no HiRes available) MeshDescription for the given static mesh, and make sure it includes normals and tangents. (i.e., to pass to AppendMeshDescription)
- L79 _public prototype_ `static bool AppendStaticMesh(const UStaticMesh* StaticMesh, const TArray<UMaterialInterface*>& Materials, const FTransform& StaticMeshTransform, UGeometryCollection* GeometryCollectionObject, bool bReindexMaterials = true, bool bAddInternalMaterials = true, bool bSplitComponents = false, bool bSetInternalFromMaterialIndex = false);` — Appends a static mesh to a GeometryCollectionComponent. @param StaticMesh : Const mesh to read vertex/normals/index data from @param Materials : Materials fetched from the StaticMeshComponent used to configure this geometry @param StaticMeshTransform : Mesh transform. @param GeometryCollection  : Collection to append the mesh into. @param bReindexMaterials	: Whether to reindex materials -- if appending multiple meshes, pass false and call ReindexMaterials afterwards @return true if succeeded in appending a mesh
- L96 _public prototype_ `static bool AppendStaticMesh(const UStaticMesh* StaticMesh, int32 StartMaterialIndex, const FTransform& StaticMeshTransform, FGeometryCollection* GeometryCollection, bool bReindexMaterials = true, bool bAddInternalMaterials = true, bool bSplitComponents = false, bool bSetInternalFromMaterialIndex = false);` — Appends a static mesh to a GeometryCollectionComponent. @param StaticMesh : Const mesh to read vertex/normals/index data from @param StartMaterialIndex : Index of materials to be used, e.g. as returned by AppendMaterials() (see below) @param StaticMeshTransform : Mesh transform. @param GeometryCollection  : Collection to append the mesh into. @param bReindexMaterials	: Whether to reindex materials -- if appending multiple meshes, pass false and call ReindexMaterials afterwards @return true if succeeded in appending a mesh
- L105 _public prototype_ `static void AppendStaticMesh(const UStaticMesh* StaticMesh, const UStaticMeshComponent *StaticMeshComponent, const FTransform& StaticMeshTransform, UGeometryCollection* GeometryCollection, bool bReindexMaterials = true, bool bAddInternalMaterials = true, bool bSplitComponents = false, bool bSetInternalFromMaterialIndex = false);` — Appends a static mesh to a GeometryCollectionComponent. @param StaticMeshComponent : Const mesh to read vertex/normals/index data from @param StaticMeshTransform : Mesh transform. @param GeometryCollection  : Collection to append the mesh into.
- L114 _public prototype_ `static void AppendSkeletalMesh(const USkeletalMesh* SkeletalMesh, const USkeletalMeshComponent *SkeletalMeshComponent, const FTransform& SkeletalMeshTransform, UGeometryCollection* GeometryCollection, bool bReindexMaterials = true);` — Appends a skeletal mesh to a GeometryCollectionComponent. @param SkeletalMeshComponent : Const mesh to read vertex/normals/index data from @param SkeletalMeshTransform : Mesh transform. @param GeometryCollection    : Collection to append the mesh into.
- L123 _public prototype_ `static bool AppendSkeletalMesh(const USkeletalMesh* SkeletalMesh, int32 MaterialStartIndex, const FTransform& SkeletalMeshTransform, FManagedArrayCollection* InCollection, bool bReindexMaterials = true, bool bImportTransformOnly = false);` — Appends a skeletal mesh to a GeometryCollection. @param SkeletalMesh : Const mesh to read vertex/normals/index data from @param MaterialStartIndex : First index of materials to use, as returned by AppendSkeletalMeshMaterials @param SkeletalMeshTransform : Mesh transform. @param GeometryCollection    : Collection to append the mesh into.
- L131 _public prototype_ `static void AppendSkeleton(const USkeleton* Skeleton, const FTransform& SkeletalMeshTransform, FManagedArrayCollection* InCollection);` — Appends a skeleton mesh to a GeometryCollection. @param USkeleton : Const mesh to read vertex/normals/index data from @param SkeletalMeshTransform : Mesh transform. @param GeometryCollection    : Collection to append the mesh into.
- L139 _public prototype_ `static int32 AppendSkeletalMeshMaterials(const USkeletalMesh* SkeletalMesh, const USkeletalMeshComponent* SkeletalMeshComponent, UGeometryCollection* GeometryCollectionObject);` — Appends a skeletal mesh to a GeometryCollectionComponent. @param SkeletalMeshComponent : Const mesh to read vertex/normals/index data from @param SkeletalMeshTransform : Mesh transform. @param GeometryCollection    : Collection to append the mesh into.
- L141 _public prototype_ `static const FSkeletalMeshLODRenderData* GetSkeletalMeshLOD(const USkeletalMesh* SkeletalMesh, int32 LOD);`
- L143 _public prototype_ `static int32 AppendGeometryCollectionMaterials(const UGeometryCollection* SourceGeometryCollection, const UGeometryCollectionComponent* GeometryCollectionComponent, UGeometryCollection* TargetGeometryCollectionObject);`
- L145 _public prototype_ `static void AppendGeometryCollectionInstancedMeshes(const UGeometryCollection* SourceGeometryCollectionObject, UGeometryCollection* TargetGeometryCollectionObject, int32 TargetTransformStartIndex);`
- L156 _public prototype_ `static bool AppendGeometryCollection(const FGeometryCollection* SourceGeometryCollection, int32 MaterialStartIndex, const FTransform& GeometryCollectionTransform, FGeometryCollection* TargetGeometryCollection, bool bReindexMaterials = true);` — Appends a GeometryCollection to another GeometryCollection. @param SourceGeometryCollection : Const GeometryCollection to read vertex/normals/index data from @param MaterialStartIndex : First index of materials to use @param GeometryCollectionTransform : GeometryCollection transform. @param TargetGeometryCollection  : Collection to append the GeometryCollection into. @param bReindexMaterials	: Whether to reindex materials -- if appending multiple meshes, pass false and call ReindexMaterials afterwards @return true if succeeded in appending a geometry collection
- L165 _public prototype_ `static void AppendGeometryCollection(const UGeometryCollection* SourceGeometryCollection, const TArray<UMaterialInterface*>& Materials, const FTransform& GeometryCollectionTransform, UGeometryCollection* TargetGeometryCollectionObject, bool ReindexMaterials = true);` — Appends a GeometryCollection to a GeometryCollectionComponent. @param SourceGeometryCollection : Const GeometryCollection to read vertex/normals/index data from @param Materials : Materials fetched from the GeometryCollectionComponent used to configure this geometry @param GeometryCollectionTransform : GeometryCollection transform. @param TargetGeometryCollection  : Collection to append the GeometryCollection into.
- L173 _public prototype_ `static void AppendGeometryCollection(const UGeometryCollection* SourceGeometryCollection, const UGeometryCollectionComponent* GeometryCollectionComponent, const FTransform& GeometryCollectionTransform, UGeometryCollection* TargetGeometryCollectionObject, bool ReindexMaterials = true);` — Appends a GeometryCollection to a GeometryCollectionComponent. @param GeometryCollectionComponent : Const GeometryCollection to read vertex/normals/index data from @param GeometryCollectionTransform : GeometryCollection transform. @param TargetGeometryCollection  : Collection to append the GeometryCollection into.
- L181 _public prototype_ `static void AppendGeometryCollectionSource(const FGeometryCollectionSource& GeometryCollectionSource, FGeometryCollection& GeometryCollectionInOut, TArray<UMaterial*>& MaterialsInOut, bool ReindexMaterials = true);` — Appends a GeometryCollectionSource to a GeometryCollection @param GeometryCollectionSource : geometry collection source object ( from UGeometryCollection collection asset ) @param GeometryCollectionInOut : GeometryCollection to append to @param MaterialsInOut  : array of materials to append to
- L182 _public prototype_ `static void AppendGeometryCollectionSource(const FGeometryCollectionSource& GeometryCollectionSource, FGeometryCollection& GeometryCollectionInOut, TArray<UMaterialInterface*>& MaterialInstancesInOut, bool ReindexMaterials = true);`
- L193 _public prototype_ `static void ConvertStaticMeshToGeometryCollection(const TObjectPtr<UStaticMesh> StaticMesh, FManagedArrayCollection& OutCollection, TArray<TObjectPtr<UMaterial>>& OutMaterials, TArray<FGeometryCollectionAutoInstanceMesh>& OutInstancedMeshes, bool bSetInternalFromMaterialIndex = true, bool bSplitComponents = false);` — Converts a StaticMesh to a GeometryCollection @param StaticMesh : Const mesh to read vertex/normals/index data from @param OutCollection : FGeometryCollection output @param OutMaterials : materials from the StaticMesh @param OutInstancedMeshes : InstancedMeshes @param bSetInternalFromMaterialIndex : Set the internal faces using the materials @param bSplitComponents : Split the components
- L194 _public prototype_ `static void ConvertStaticMeshToGeometryCollection(const TObjectPtr<UStaticMesh> StaticMesh, FManagedArrayCollection& OutCollection, TArray<TObjectPtr<UMaterialInterface>>& OutMaterialInstances, TArray<FGeometryCollectionAutoInstanceMesh>& OutInstancedMeshes, bool bSetInternalFromMaterialIndex = true, bool bSplitComponents = false);`
- L195 _public prototype_ `static void ConvertStaticMeshToGeometryCollection(const TObjectPtr<UStaticMesh> StaticMesh, const FTransform& MeshTransform, FManagedArrayCollection& OutCollection, TArray<TObjectPtr<UMaterialInterface>>& OutMaterialInstances, TArray<FGeometryCollectionAutoInstanceMesh>& OutInstancedMeshes, bool bSetInternalFromMaterialIndex = true, bool bSplitComponents = false);`
- L204 _public prototype_ `static void ConvertGeometryCollectionToGeometryCollection(const TObjectPtr<UGeometryCollection> InGeometryCollectionAssetPtr, FManagedArrayCollection& OutCollection, TArray<TObjectPtr<UMaterial>>& OutMaterials, TArray<FGeometryCollectionAutoInstanceMesh>& OutInstancedMeshes);` — Converts a UGeometryCollection asset to an FManagedArrayCollection, and arrays of materials and instanced meshes @param GeometryCollection : UGeometryCollection input to convert @param OutCollection : FGeometryCollection output @param OutMaterials : Materials from the UGeometryCollection @param OutInstancedMeshes : InstancedMeshes
- L205 _public prototype_ `static void ConvertGeometryCollectionToGeometryCollection(const TObjectPtr<UGeometryCollection> InGeometryCollectionAssetPtr, FManagedArrayCollection& OutCollection, TArray<TObjectPtr<UMaterialInterface>>& OutMaterialInstances, TArray<FGeometryCollectionAutoInstanceMesh>& OutInstancedMeshes);`
- L215 _public prototype_ `static void ConvertActorToGeometryCollection(const AActor* Actor, FManagedArrayCollection& OutCollection, TArray<TObjectPtr<UMaterial>>& OutMaterials, TArray<FGeometryCollectionAutoInstanceMesh>& OutInstancedMeshes, const FSkeletalMeshToCollectionConversionParameters& ConversionParameters, bool bSplitComponents = false);` — Converts an actor to an FManagedArrayCollection, and arrays of materials and instanced meshes @param Actor : actor input to convert @param OutCollection : FGeometryCollection output @param OutMaterials : Materials from the UGeometryCollection @param OutInstancedMeshes : InstancedMeshes @param bSplitComponents : Split the components
- L216 _public prototype_ `static void ConvertActorToGeometryCollection(const AActor* Actor, FManagedArrayCollection& OutCollection, TArray<TObjectPtr<UMaterialInterface>>& OutMaterialInstances, TArray<FGeometryCollectionAutoInstanceMesh>& OutInstancedMeshes, const FSkeletalMeshToCollectionConversionParameters& ConversionParameters, bool bSplitComponents = false);`
- L224 _public prototype_ `static void ConvertCollectionToSkeleton(const FManagedArrayCollection& InCollection, USkeleton* OutSkeleton, TArray<int32>& OutIndexRemap, bool bCenterBonesOnGeometry = false);` — Converts an FManagedArrayCollection to a USkeleton @param InManagedArrayCollection : Collection that supports transform hierarchy @param OutSkeleton : USkeleton to populate @param OutIndexRemap : Remapping from Collection transforms to skeletal transforms.
- L232 _public prototype_ `static void ConvertCollectionToSkeletalMesh(const FManagedArrayCollection& InCollection, const TArray<TObjectPtr<UMaterialInterface>> InMaterials, USkeletalMesh& OutSkeletalMesh, USkeleton& OutSkeleton);` — Converts a Geometry collection to a SkeletalMesh @param InCollection: Geometry collection to convert to a skeletal mesh @param OutSkeletalMesh : skeletal mesh asset to export to @param OutSkeleton : Skeleton asset to export the bone hierarchy to
- L235 _public prototype_ `static void GetMaterialsFromInstances(const TArray<TObjectPtr<UMaterialInterface>>& MaterialInstances, TArray<TObjectPtr<UMaterial>>& OutMaterials);` — utility function to convert an array of material instances to an array of material
- L245 _private prototype_ `static bool AppendGeometryCollectionSourceNoMaterial(const FGeometryCollectionSource& GeometryCollectionSource, FGeometryCollection& GeometryCollectionInOut, int32 StartMaterialIndex, bool ReindexMaterials = true);` — Appends a GeometryCollectionSource to a GeometryCollection ignoring the materials this is meant to be used by the AppendGeometryCollectionSource variants @param GeometryCollectionSource : geometry collection source object ( from UGeometryCollection collection asset ) @param GeometryCollectionInOut : GeometryCollection to append to @return true if the source was added successfully ( valid object )

#### struct `FGeometryCollectionEngineConversion::FSkeletalMeshToCollectionConversionParameters`  
`struct FSkeletalMeshToCollectionConversionParameters`  
_L30-33_
- L32 _public member_ `bool bParentAllBonesUnderNewRoot = true;`

#### Free symbols / members of external scopes

- L20 _typedef_ `typedef TTuple<const UStaticMesh *, const UStaticMeshComponent *, FTransform> GeometryCollectionStaticMeshConversionTuple;`
- L21 _typedef_ `typedef TTuple<const USkeletalMesh *, const USkeletalMeshComponent *, FTransform> GeometryCollectionSkeletalMeshConversionTuple;`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionEngineRemoval.h` (Public)


#### class `FGeometryCollectionRemoveOnBreakDynamicFacade`  
`class FGeometryCollectionRemoveOnBreakDynamicFacade`  
_L20-73_
- desc: Provides an API for the run time aspect of the remove on break feature this is to be used with the dynamic collection
- L23 _public member_ `static constexpr float DisabledBreakTimer = -1;`
- L24 _public member_ `static constexpr float BreakTimerStartValue = 0;`
- L25 _public member_ `static constexpr float DisabledPostBreakDuration = -1;`
- L26 _public member_ `static constexpr float CrumblingRemovalTimer = -1;`
- L28 _public prototype_ `FGeometryCollectionRemoveOnBreakDynamicFacade(FGeometryDynamicCollection& InCollection);`
- L34 _public prototype_ `bool IsValid() const;` — returns true if all the necessary attributes are present if not then the API can be used to create
- L37 _public prototype_ `bool IsConst() const;` — Is this facade const access
- L40 _public prototype_ `void DefineSchema();` — Add the relevant attributes
- L46 _public prototype_ `void SetAttributeValues(const GeometryCollection::Facades::FCollectionRemoveOnBreakFacade& RemoveOnBreakFacade);` — Add the necessary attributes if they are missing and initialize them if necessary @param RemoveOnBreakFacade remove on break facade from the rest collection that contain the original user set attributes
- L49 _public prototype_ `bool IsRemovalActive(int32 TransformIndex) const;` — true if the removal is active for a specific piece
- L52 _public prototype_ `bool UseClusterCrumbling(int32 TransformIndex) const;` — true if a specific transform uses cluster crumbling
- L60 _public prototype_ `float UpdateBreakTimerAndComputeDecay(int32 TransformIndex, float DeltaTime);` — Update break timer and return the matching decay @param TransformIndex index of the transform to update @param DeltaTime elapsed time since the last update in second @return decay value computed from the timer and duration ( [0,1] range )
- L64 _private member_ `TManagedArrayAccessor<float> BreakTimerAttribute;` — Time elapsed since the break in seconds
- L67 _private member_ `TManagedArrayAccessor<float> PostBreakDurationAttribute;` — duration after the break before the removal process starts
- L70 _private member_ `TManagedArrayAccessor<float> BreakRemovalDurationAttribute;` — removal duration
- L72 _private member_ `const FGeometryDynamicCollection& DynamicCollection;`

#### class `FGeometryCollectionRemoveOnSleepDynamicFacade`  
`class FGeometryCollectionRemoveOnSleepDynamicFacade`  
_L79-144_
- desc: Provides an API for the run time aspect of the remove on sleep feature this is to be used with the dynamic collection
- L82 _public prototype_ `FGeometryCollectionRemoveOnSleepDynamicFacade(FManagedArrayCollection& InCollection);`
- L88 _public prototype_ `bool IsValid() const;` — returns true if all the necessary attributes are present if not then the API can be used to create
- L91 _public prototype_ `bool IsConst() const;` — Is this facade const access
- L94 _public prototype_ `void DefineSchema();` — Add the relevant attributes
- L96 _public prototype_ `float GetSleepRemovalDuration(int32 TransformIndex) const;`
- L97 _public prototype_ `float GetMaxSleepTime(int32 TransformIndex) const;`
- L99 _public prototype_ `void SetSleepRemovalDuration(int32 TransformIndex, float SleepRemovalDuration);`
- L100 _public prototype_ `void SetMaxSleepTime(int32 TransformIndex, float MaxSleepTime);`
- L107 _public prototype_ `void SetAttributeValues(const FVector2D& MaximumSleepTime, const FVector2D& RemovalDuration);` — Add the necessary attributes if they are missing and initialize them if necessary @param MaximumSleepTime range of time to initialize the sleep duration @param RemovalDuration range of time to initialize the removal duration
- L110 _public prototype_ `bool IsRemovalActive(int32 TransformIndex) const;` — true if the removal is active for a specific piece
- L119 _public prototype_ `bool ComputeSlowMovingState(int32 TransformIndex, const FVector& Position, float DeltaTime, FVector::FReal VelocityThreshold);` — Compute the slow moving state and update from the last position After calling this method, LastPosition will be updated with Position @param Position Current world position @param DeltaTime elapsed time since last update @return true if the piece if the piece is considered slow moving
- L126 _public prototype_ `void UpdateSleepTimer(int32 TransformIndex, float DeltaTime);` — Update the sleep timer @param TransformIndex index of the transform to update @param DeltaTime elapsed time since last update
- L129 _public prototype_ `float ComputeDecay(int32 TransformIndex) const;` — Compute decay from elapsed timer and duration attributes
- L134 _private member_ `TManagedArrayAccessor<float> SleepTimerAttribute;` — Time elapsed since the sleep detection
- L137 _private member_ `TManagedArrayAccessor<float> MaxSleepTimeAttribute;` — duration after the sleep detection before the removal process starts (read only from outside)
- L140 _private member_ `TManagedArrayAccessor<float> SleepRemovalDurationAttribute;` — removal duration (read only from outside)
- L143 _private member_ `TManagedArrayAccessor<FVector> LastPositionAttribute;` — Last position used to detect slow moving pieces

#### class `FGeometryCollectionDecayDynamicFacade`  
`class FGeometryCollectionDecayDynamicFacade`  
_L149-175_
- desc: Provides an API for decay related attributes ( use for remove on break and remove on sleep )
- L152 _public prototype_ `FGeometryCollectionDecayDynamicFacade(FManagedArrayCollection& InCollection);`
- L158 _public prototype_ `bool IsValid() const;` — returns true if all the necessary attributes are present if not then the API can be used to create
- L161 _public prototype_ `void AddAttributes();` — Add the necessary attributes if they are missing and initialize them if necessary
- L164 _public prototype_ `float GetDecay(int32 TransformIndex) const;` — Get decay value for a specific transform index
- L167 _public prototype_ `void SetDecay(int32 TransformIndex, float DecayValue);` — Set decay value for a specific transform index
- L170 _public prototype_ `int32 GetDecayAttributeSize() const;` — Get the size of the decay attribute - this should match the number of transforms of the collection
- L174 _private member_ `TManagedArrayAccessor<float> DecayAttribute;` — state of decay ([0-1] range)

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace GeometryCollection`
- L11 _namespace_ `namespace Facades` (scope `GeometryCollection`)

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionEngineSizeSpecificUtility.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace GeometryCollection`
- L10 _namespace_ `namespace SizeSpecific` (scope `GeometryCollection`)
- L15 _prototype_ `bool UsesImplicitCollisionType(const TArray<FGeometryCollectionSizeSpecificData>& SizeSpecificData, EImplicitTypeEnum ImplicitType);` (scope `GeometryCollection::SizeSpecific`) — Return if true/false if this size specific object uses the specified collision type.
- L20 _prototype_ `void SetImplicitCollisionType(TArray<FGeometryCollectionSizeSpecificData>& SizeSpecificData, EImplicitTypeEnum ImplicitTypeTo, EImplicitTypeEnum ImplicitTypeFrom = EImplicitTypeEnum::Chaos_Implicit_None);` (scope `GeometryCollection::SizeSpecific`) — Set the collision types for a size specific data, also will only set the types matching ImplicitTypeFrom if specified.

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionEngineTypes.h` (Public)


#### enum `ECollectionAttributeEnum`  
`enum class UE_DEPRECATED(5.4, "ECollectionAttributeEnum is no longer supported") ECollectionAttributeEnum : uint8`  
_L13-20_
- reflection: `UENUM()`
- L15 _public enumerator_ `Chaos_Active UMETA(DisplayName = "Active")`
- L16 _public enumerator_ `Chaos_DynamicState UMETA(DisplayName = "DynamicState")`
- L17 _public enumerator_ `Chaos_CollisionGroup UMETA(DisplayName = "CollisionGroup")`
- L19 _public enumerator_ `Chaos_Max UMETA(Hidden)`

#### enum `ECollectionGroupEnum`  
`enum class UE_DEPRECATED(5.4, "ECollectionGroupEnum is no longer supported") ECollectionGroupEnum : uint8`  
_L28-33_
- reflection: `UENUM()`
- L30 _public enumerator_ `Chaos_Traansform UMETA(DisplayName = "Transform")`
- L32 _public enumerator_ `Chaos_Max UMETA(Hidden)`

#### Free symbols / members of external scopes

- L24 _prototype_ `FName GetCollectionAttributeName(ECollectionAttributeEnum TypeIn);` — `UE_DEPRECATED(5.4, "GetCollectionAttributeName is no longer supported")`
- L37 _prototype_ `FName GetCollectionGroupName(ECollectionGroupEnum TypeIn);` — `UE_DEPRECATED(5.4, "GetCollectionGroupName is no longer supported")`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionEngineUtility.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace GeometryCollectionEngineUtility`
- L13 _prototype_ `void PrintDetailedStatistics(const FGeometryCollection* GeometryCollection, const UGeometryCollectionCache* InCache);` (scope `GeometryCollectionEngineUtility`)
- L15 _prototype_ `void PrintDetailedStatisticsSummary(const TArray<const FGeometryCollection*> GeometryCollectionArray);` (scope `GeometryCollectionEngineUtility`)
- L17 _prototype_ `void ComputeNormals(FGeometryCollection* GeometryCollection);` (scope `GeometryCollectionEngineUtility`)
- L19 _prototype_ `void ComputeTangents(FGeometryCollection* GeometryCollection);` (scope `GeometryCollectionEngineUtility`)
- L33 _prototype_ `GenerateConnectedComponents(const USkeletalMesh* InSkeletalMesh, TArray<TArray<FIntVector>>& ComponentIndices, TArray<TArray<FIntVector2>>& TrangleComponentMap, TArray<int32>& VertexComponentMap, int32& TriangleCount, int32& VertexCount);` (scope `GeometryCollectionEngineUtility`)

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionExternalRenderInterface.h` (Public)


#### class `UGeometryCollectionExternalRenderInterface`  
`class UGeometryCollectionExternalRenderInterface : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGeometryCollectionExternalRenderInterface`  
`class IGeometryCollectionExternalRenderInterface`  
_L18-75_
- L31 _public function_ `virtual bool ShouldUseNativeFallback(uint32 InStateFlags) const` — Returns true if the custom renderer can't render for the given state, and requires native rendering instead.
- L33 _public function_ `virtual bool CanEverUseNativeFallback() const` — Returns true if this renderer can ever return true for ShouldUseNativeFallback().
- L36 _public prototype_ `virtual void OnRegisterGeometryCollection(UGeometryCollectionComponent& InComponent) = 0;` — Called on geometry collection component registration.
- L38 _public prototype_ `virtual void OnUnregisterGeometryCollection() = 0;` — Called on geometry collection component unregistration.
- L44 _public prototype_ `virtual void UpdateState(UGeometryCollection const& InGeometryCollection, FTransform const& InComponentTransform, uint32 InStateFlags) = 0;` — Set the state of the geometry collection. This is used by the renderer to managed resources with regards to the state (see EStateFlags).
- L50 _public prototype_ `virtual void UpdateRootTransform(UGeometryCollection const& InGeometryCollection, FTransform const& InRootTransform) = 0;` — Update the root bone transform of the geometry collection. If the geometry collection is using of multiple proxy root meshes this transform applies to all of them.
- L58 _public function_ `virtual void UpdateRootTransforms(UGeometryCollection const& InGeometryCollection, FTransform const& InRootTransform, TArrayView<const FTransform3f> InRootLocalTransforms)` — Update the root proxy transforms of the geometry collection. If the geometry collection is using of multiple proxy root meshes, InRootTransforms is expected to contain an entry for each of them . @param InRootTransform		Component space root transform @param InRootLocalTransforms	Root space local transforms
- L63 _public prototype_ `virtual void UpdateTransforms(UGeometryCollection const& InGeometryCollection, TArrayView<const FTransform3f> InTransforms) = 0;` — Update all the bones transforms.
- L66 _public function_ `virtual void UpdateState(UGeometryCollection const& InGeometryCollection, FTransform const& InComponentTransform, bool bInIsBroken, bool bInIsVisible)` — `UE_DEPRECATED(5.4, "Use flags version of UpdateState instead")`
- L74 _public function_ `virtual void UpdateTransforms(UGeometryCollection const& InGeometryCollection, TArrayView<const FMatrix> InMatrices)` — `UE_DEPRECATED(5.3, "Use FTransform version of UpdateTransforms instead")`

#### enum `IGeometryCollectionExternalRenderInterface::EStateFlags`  
`enum EStateFlags`  
_L23-28_
- L25 _public enumerator_ `EState_Visible = 1 << 0`
- L26 _public enumerator_ `EState_Broken = 1 << 1`
- L27 _public enumerator_ `EState_ForcedBroken = 1 << 2`

#### class `UGeometryCollectionCustomDataInterface`  
`class UGeometryCollectionCustomDataInterface : public UInterface`  
_L79-82_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGeometryCollectionCustomDataInterface`  
`class IGeometryCollectionCustomDataInterface`  
_L84-97_
- L90 _public prototype_ `virtual void SetCustomInstanceData(int32 CustomDataIndex, float CustomDataValue) = 0;` — Set value to a custom instance data slot by index. The value will be set for all instances the renderer is spawning.
- L93 _public prototype_ `virtual void SetCustomInstanceData(FName CustomDataName, float CustomDataValue) = 0;` — Set value a custom instance data slot by name. The value will be set for all instances the renderer is spawning.
- L96 _public prototype_ `virtual void SetRenderCustomDepthStencil(bool bEnable, int32 CustomStencilValue) = 0;` — Enable or disable custom depth writing and, if enabled, the value written to the stencil buffer. The value will be set for all instances the renderer is spawning.

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionHitProxy.h` (Public)


#### struct `HGeometryCollection`  
`struct HGeometryCollection : public HHitProxy`  
_L11-27_
- inherits: `HHitProxy`
- desc: HitProxy with transform index information.
- L13 _public prototype_ `DECLARE_HIT_PROXY() TObjectPtr<UGeometryCollectionComponent> Component;`
- L16 _public member_ `int32 BoneIndex;`
- L18 _public function_ `HGeometryCollection(UGeometryCollectionComponent* InGeometryCollectionComponent, int32 InBoneIndex) : Component(InGeometryCollectionComponent) , BoneIndex(InBoneIndex)`
- L23 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionISMPoolActor.h` (Public)


#### class `AGeometryCollectionISMPoolActor`  
`class UE_DEPRECATED(5.6, "AGeometryCollectionISMPoolActor is deprecated, please use AISMPoolActor instead.") AGeometryCollectionISMPoolActor : public AActor`  
_L11-31_
- reflection: `UCLASS(ConversionRoot, ComponentWrapperClass, MinimalAPI)`
- inherits: `AActor`
- L18 _private member_ `TObjectPtr<class UGeometryCollectionISMPoolComponent> ISMPoolComp;` — `UPROPERTY(Category = ISMPoolActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))`
- L23 _private member_ `TObjectPtr<class UGeometryCollectionISMPoolDebugDrawComponent> ISMPoolDebugDrawComp;` — `UPROPERTY(Category = ISMPoolActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))`
- L29 _public function_ `UGeometryCollectionISMPoolComponent* GetISMPoolComp() const` — Returns ISMPoolComp subobject

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionISMPoolComponent.h` (Public)


#### struct `FInstanceGroups`  
`struct FInstanceGroups`  
_L22-96_
- desc: Structure containing a set of allocated instance ranges in an FGeometryCollectionISM which is the manager for a single ISM component. The instance ranges don't change once allocated, and aren't the same as the actual render indices in the ISM. The reason that we don't store the the actual ISM render indices is that ISM component is free to reorder its instances whenever it likes.
- L24 _public typedef_ `using FInstanceGroupId = int32;`
- L40 _public function_ `void Reset()` — Reset all contents.
- L49 _public function_ `bool IsEmpty() const` — Returns true if no groups ranges are in use.
- L55 _public function_ `int32 GetMaxInstanceIndex() const` — Returns the maximum instance index that we have allocated in a group.
- L61 _public function_ `FInstanceGroupId AddGroup(int32 Count)` — Add a new group range.
- L84 _public function_ `void RemoveGroup(FInstanceGroupId GroupId)` — Remove a group range.
- L92 _public member_ `int32 TotalInstanceCount = 0;`
- L93 _public member_ `int32 TotalFreeInstanceCount = 0;`
- L94 _public member_ `TArray<FInstanceGroupRange> GroupRanges;`
- L95 _public member_ `TArray<FInstanceGroupId> FreeList;`

#### struct `FInstanceGroups::FInstanceGroupRange`  
`struct FInstanceGroupRange`  
_L27-37_
- desc: A single continuous range associated with an FInstanceGroupId.
- L29 _public function_ `FInstanceGroupRange(int32 InStart, int32 InCount) : Start(InStart) , Count(InCount)`
- L35 _public member_ `int32 Start = 0;`
- L36 _public member_ `int32 Count = 0;`

#### struct `FISMComponentDescription`  
`struct FISMComponentDescription`  
_L101-142_
- desc: A description for an ISM component.
- L118 _public member_ `uint32 Flags = WorldPositionOffsetWritesVelocity|EvaluateWorldPositionOffset|AffectShadow;`
- L119 _public member_ `int32 NumCustomDataFloats = 0;`
- L120 _public member_ `FVector Position = FVector::ZeroVector;`
- L121 _public member_ `int32 StartCullDistance = 0;`
- L122 _public member_ `int32 EndCullDistance = 0;`
- L123 _public member_ `int32 MinLod = 0;`
- L124 _public member_ `uint32 GroupHash = 0;` — Optional, allows identical SMs to be separated into different groups for finer grained culling
- L125 _public member_ `float LodScale = 1.f;`
- L126 _public member_ `TArray<FName> Tags;`
- L127 _public member_ `FName StatsCategory;`
- L129 _public function_ `bool operator==(const FISMComponentDescription& Other) const`

#### enum `FISMComponentDescription::EFlags`  
`enum EFlags`  
_L103-116_
- L105 _public enumerator_ `UseHISM = 1 << 1` — HISM is no longer supported. This flag is ignored.
- L106 _public enumerator_ `GpuLodSelection = 1 << 2`
- L107 _public enumerator_ `ReverseCulling = 1 << 3`
- L108 _public enumerator_ `StaticMobility = 1 << 4`
- L109 _public enumerator_ `WorldPositionOffsetWritesVelocity = 1 << 5`
- L110 _public enumerator_ `EvaluateWorldPositionOffset = 1 << 6`
- L111 _public enumerator_ `AffectShadow = 1 << 7`
- L112 _public enumerator_ `AffectDistanceFieldLighting = 1 << 8`
- L113 _public enumerator_ `AffectDynamicIndirectLighting = 1 << 9`
- L114 _public enumerator_ `AffectFarShadow = 1 << 10`
- L115 _public enumerator_ `DistanceCullPrimitive = 1 << 11`

#### struct `FGeometryCollectionStaticMeshInstance`  
`struct FGeometryCollectionStaticMeshInstance`  
_L161-203_
- desc: A mesh with potentially overriden materials and ISM property description. We batch instances into ISMs that have equivalent values for this structure.
- L163 _public member_ `TWeakObjectPtr<UStaticMesh> StaticMesh;`
- L164 _public member_ `TArray<TWeakObjectPtr<UMaterialInterface>> MaterialsOverrides;`
- L165 _public member_ `TArray<float> CustomPrimitiveData;`
- L166 _public member_ `FISMComponentDescription Desc;`
- L168 _public function_ `bool operator==(const FGeometryCollectionStaticMeshInstance& Other) const`

#### struct `FGeometryCollectionMeshInfo`  
`struct FGeometryCollectionMeshInfo`  
_L222-230_
- desc: Describes a group of instances within an ISM.
- L224 _public member_ `int32 ISMIndex;`
- L225 _public member_ `FInstanceGroups::FInstanceGroupId InstanceGroupIndex;`
- L227 _public member_ `TArray<float> CustomData;`
- L228 _public prototype_ `TArrayView<const float> CustomDataSlice(int32 InstanceIndex, int32 NumCustomDataFloatsPerInstance);`
- L229 _public prototype_ `void ShadowCopyCustomData(int32 InstanceCount, int32 NumCustomDataFloatsPerInstance, TArrayView<const float> CustomDataFloats);`

#### struct `FGeometryCollectionMeshGroup`  
`struct FGeometryCollectionMeshGroup`  
_L238-256_
- desc: A mesh group which is a collection of meshes and their related FGeometryCollectionMeshInfo. We group these with a single handle with the expectation that a client will want to own multiple meshs and release them together.
- L240 _public typedef_ `using FMeshId = int32;`
- L243 _public prototype_ `FMeshId AddMesh(const FGeometryCollectionStaticMeshInstance& MeshInstance, int32 InstanceCount, const FGeometryCollectionMeshInfo& ISMInstanceInfo, TArrayView<const float> CustomDataFloats);` — Adds a new mesh with instance count. We expect to only add a unique mesh instance once to each group. Returns a ID that can be used to update the instances.
- L245 _public prototype_ `bool BatchUpdateInstancesTransforms(FGeometryCollectionISMPool& ISMPool, FMeshId MeshId, int32 StartInstanceIndex, TArrayView<const FTransform> NewInstancesTransforms, bool bWorldSpace, bool bMarkRenderStateDirty, bool bTeleport);` — Update instance transforms for a group of instances.
- L246 _public prototype_ `void BatchUpdateInstanceCustomData(FGeometryCollectionISMPool& ISMPool, int32 CustomFloatIndex, float CustomFloatValue);`
- L249 _public prototype_ `void RemoveAllMeshes(FGeometryCollectionISMPool& ISMPool);` — Remove all of our managed meshes and associated instances.
- L252 _public member_ `TArray<FGeometryCollectionMeshInfo> MeshInfos;` — Array of allocated mesh infos.
- L255 _public member_ `bool bAllowPerInstanceRemoval = false;` — Flag for whether we allow removal of instances when transform scale is set to zero.

#### struct `FGeometryCollectionISM`  
`struct FGeometryCollectionISM`  
_L259-276_
- desc: Structure containting all info for a single ISM.
- L262 _public prototype_ `void CreateISM(USceneComponent* InOwningComponent);` — Create the ISMComponent according to settings on the mesh instance.
- L264 _public prototype_ `void InitISM(const FGeometryCollectionStaticMeshInstance& InMeshInstance, bool bKeepAlive, bool bOverrideTransformUpdates = false);` — Initialize the ISMComponent according to settings on the mesh instance.
- L266 _public prototype_ `FInstanceGroups::FInstanceGroupId AddInstanceGroup(int32 InstanceCount, TArrayView<const float> CustomDataFloats);` — Add a group to the ISM. Returns the group index.
- L269 _public member_ `FGeometryCollectionStaticMeshInstance MeshInstance;` — Unique description of ISM component settings.
- L271 _public member_ `TObjectPtr<UInstancedStaticMeshComponent> ISMComponent;` — Created ISM component. Will be nullptr when this slot has been recycled to FGeometryCollectionISMPool FreeList.
- L273 _public member_ `FInstanceGroups InstanceGroups;` — Groups of instances allocated in the ISM.
- L275 _public member_ `TArray<FPrimitiveInstanceId> InstanceIds;` — Id of Instance in ISMC

#### struct `FGeometryCollectionISMPool`  
`struct FGeometryCollectionISMPool`  
_L279-339_
- desc: A pool of ISMs.
- L281 _public typedef_ `using FISMIndex = int32;`
- L283 _public prototype_ `FGeometryCollectionISMPool();`
- L287 _public prototype_ `FISMIndex GetOrAddISM(UGeometryCollectionISMPoolComponent* OwningComponent, const FGeometryCollectionStaticMeshInstance& MeshInstance, bool& bOutISMCreated);` — Find or add an ISM and return an ISM index handle.
- L291 _public prototype_ `void RemoveISM(FISMIndex ISMIndex, bool bKeepAlive, bool bRecycle);` — Remove an ISM.
- L294 _public prototype_ `FGeometryCollectionMeshInfo AddInstancesToISM(UGeometryCollectionISMPoolComponent* OwningComponent, const FGeometryCollectionStaticMeshInstance& MeshInstance, int32 InstanceCount, TArrayView<const float> CustomDataFloats);` — Add instances to ISM and return a mesh info handle.
- L298 _public prototype_ `void RemoveInstancesFromISM(const FGeometryCollectionMeshInfo& MeshInfo);` — Remove instances from an ISM.
- L300 _public prototype_ `bool BatchUpdateInstancesTransforms(FGeometryCollectionMeshInfo& MeshInfo, int32 StartInstanceIndex, TArrayView<const FTransform> NewInstancesTransforms, bool bWorldSpace, bool bMarkRenderStateDirty, bool bTeleport, bool bAllowPerInstanceRemoval);` — Update ISM contents.
- L301 _public prototype_ `void BatchUpdateInstanceCustomData(FGeometryCollectionMeshInfo const& MeshInfo, int32 CustomFloatIndex, float CustomFloatValue);`
- L304 _public prototype_ `void Clear();` — Clear all ISM components and associated data.
- L308 _public prototype_ `void Tick(UGeometryCollectionISMPoolComponent* OwningComponent);` — Tick maintenance of free list and preallocation.
- L312 _public prototype_ `void RequestPreallocateMeshInstance(const FGeometryCollectionStaticMeshInstance& MeshInstances);` — Add an ISM description to the preallocation queue.
- L315 _public prototype_ `void ProcessPreallocationRequests(UGeometryCollectionISMPoolComponent* OwningComponent, int32 MaxPreallocations);` — Process the preallocation queue. Processing is timesliced so that only some of the queue will be processed in every call.
- L318 _public prototype_ `void UpdateAbsoluteTransforms(const FTransform& BaseTransform, EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport);`
- L321 _public member_ `TArray<FGeometryCollectionISM> ISMs;` — Array of ISM objects.
- L323 _public member_ `TMap<FGeometryCollectionStaticMeshInstance, FISMIndex> MeshToISMIndex;` — Mapping from mesh description to ISMs array slot.
- L326 _public member_ `TSet<FGeometryCollectionStaticMeshInstance> PrellocationQueue;` — Set of ISM descriptions that we would like to preallocate.
- L329 _public member_ `TArray<int32> FreeList;` — Free list of indices in ISMs that are empty.
- L331 _public member_ `TArray<int32> FreeListISM;` — Free list of indices in ISMs that have registered ISM components.
- L334 _public member_ `bool bCachedKeepAlive = false;` — Cached state of lifecycle cvars from the last Tick()
- L335 _public member_ `bool bCachedRecycle = false;`
- L338 _public member_ `bool bDisableBoundsAndTransformUpdate = false;` — Whether we force ISMs to use parent bounds and disable transform updates

#### class `UGeometryCollectionISMPoolComponent`  
`class UE_DEPRECATED(5.6, "UGeometryCollectionISMPoolComponent is deprecated, please use UISMPoolComponent instead.") UGeometryCollectionISMPoolComponent: public USceneComponent`  
_L349-405_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `USceneComponent`
- L354 _public typedef_ `using FMeshGroupId = int32;`
- L355 _public typedef_ `using FMeshId = int32;`
- L358 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L359 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L367 _public prototype_ `FMeshGroupId CreateMeshGroup(bool bAllowPerInstanceRemoval = false);` — Create an Mesh group which represent an arbitrary set of mesh with their instance no resources are created until the meshes are added for this group return a mesh group Id used to add and update instances
- L370 _public prototype_ `void DestroyMeshGroup(FMeshGroupId MeshGroupId);` — Destroy  a mesh group and its associated resources
- L373 _public prototype_ `FMeshId AddMeshToGroup(FMeshGroupId MeshGroupId, const FGeometryCollectionStaticMeshInstance& MeshInstance, int32 InstanceCount, TArrayView<const float> CustomDataFloats);` — Add a static mesh for a mesh group
- L376 _public prototype_ `bool BatchUpdateInstancesTransforms(FMeshGroupId MeshGroupId, FMeshId MeshId, int32 StartInstanceIndex, TArrayView<const FTransform> NewInstancesTransforms, bool bWorldSpace = false, bool bMarkRenderStateDirty = false, bool bTeleport = false);` — Update transforms for a mesh group
- L379 _public prototype_ `bool BatchUpdateInstancesTransforms(FMeshGroupId MeshGroupId, FMeshId MeshId, int32 StartInstanceIndex, const TArray<FTransform>& NewInstancesTransforms, bool bWorldSpace = false, bool bMarkRenderStateDirty = false, bool bTeleport = false);` — `UE_DEPRECATED(5.3, "BatchUpdateInstancesTransforms Array parameter version is deprecated, use the TArrayView version instead")`
- L382 _public prototype_ `bool BatchUpdateInstanceCustomData(FMeshGroupId MeshGroupId, int32 CustomFloatIndex, float CustomFloatValue);` — Update a single slot of custom instance data for all instances in a mesh group
- L388 _public prototype_ `void PreallocateMeshInstance(const FGeometryCollectionStaticMeshInstance& MeshInstance);` — Preallocate an ISM in the pool. Doing this early for known mesh instance descriptions can reduce the component registration cost of AddMeshToGroup() for newly discovered mesh descriptions.
- L390 _public prototype_ `void SetTickablePoolManagement(bool bEnablePoolManagement);`
- L392 _public prototype_ `void SetOverrideTransformUpdates(bool bOverrideUpdates);`
- L394 _public prototype_ `void UpdateAbsoluteTransforms(const FTransform& BaseTransform, EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport);`
- L397 _private member_ `uint32 NextMeshGroupId = 0;`
- L398 _private member_ `TMap<FMeshGroupId, FGeometryCollectionMeshGroup> MeshGroups;`
- L399 _private member_ `FGeometryCollectionISMPool Pool;`
- L403 _private member_ `friend UGeometryCollectionISMPoolDebugDrawComponent;` — Expose internals for debug draw support.

#### Free symbols / members of external scopes

- L144 _function_ `inline uint32 GetTypeHash(const FISMComponentDescription& Desc)`
- L205 _function_ `inline uint32 GetTypeHash(const FGeometryCollectionStaticMeshInstance& MeshInstance)`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionISMPoolDebugDrawComponent.h` (Public)


#### class `UGeometryCollectionISMPoolDebugDrawComponent`  
`class UE_DEPRECATED(5.6, "UGeometryCollectionISMPoolDebugDrawComponent is deprecated, please use UISMPoolDebugDrawComponent instead.") UGeometryCollectionISMPoolDebugDrawComponent : public UDebugDrawComponent`  
_L13-55_
- reflection: `UCLASS(ClassGroup = Debug)`
- inherits: `UDebugDrawComponent`
- L18 _private member_ `bool bShowGlobalStats = false;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L21 _private member_ `bool bShowStats = false;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L24 _private member_ `bool bShowBounds = false;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L27 _private member_ `TObjectPtr<const UInstancedStaticMeshComponent> SelectedComponent;` — `UPROPERTY(Transient)`
- L29 _private member_ `float SelectTimer = 0.f;`
- L32 _protected prototype_ `virtual void BeginPlay() override;`
- L33 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L34 _protected prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L35 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L38 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L41 _protected prototype_ `void UpdateTickEnabled();`
- L44 _protected prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L46 _protected member_ `FDebugDrawDelegateHelper DebugDrawDelegateHelper;`
- L47 _protected function_ `virtual FDebugDrawDelegateHelper& GetDebugDrawDelegateHelper() override`
- L49 _protected member_ `FDelegateHandle OnScreenMessagesHandle;`
- L50 _protected prototype_ `void GetOnScreenMessages(TMultiMap<FCoreDelegates::EOnScreenMessageSeverity, FText>& OutMessages);`
- L54 _public prototype_ `static void UpdateAllTickEnabled();`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionISMPoolSubSystem.h` (Public)


#### class `UGeometryCollectionISMPoolSubSystem`  
`class UE_DEPRECATED(5.6, "UGeometryCollectionISMPoolSubSystem is deprecated, please use UISMPoolSubSystem instead.") UGeometryCollectionISMPoolSubSystem : public UWorldSubsystem`  
_L15-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- desc: A subsystem managing ISMPool actors. Used by geometry collection now but repurposed for more general use.
- L20 _public prototype_ `UGeometryCollectionISMPoolSubSystem();`
- L23 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L24 _public prototype_ `virtual void Deinitialize() override;`
- L29 _public prototype_ `AGeometryCollectionISMPoolActor* FindISMPoolActor(ULevel* Level);` — Finds or creates an actor.
- L34 _public prototype_ `void GetISMPoolActors(TArray<AGeometryCollectionISMPoolActor*>& OutActors) const;` — Get all actors managed by the subsystem.
- L39 _protected prototype_ `void OnActorEndPlay(AActor* InSource, EEndPlayReason::Type Reason);` — `UFUNCTION()`
- L43 _protected member_ `TMap<TObjectPtr<ULevel>, TObjectPtr<AGeometryCollectionISMPoolActor> > PerLevelISMPoolActors;` — ISMPool are per level

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionObject.h` (Public)


#### struct `FGeometryCollectionSource`  
`struct FGeometryCollectionSource`  
_L30-67_
- reflection: `USTRUCT(BlueprintType)`
- L34 _public function_ `FGeometryCollectionSource()`
- L35 _public function_ `FGeometryCollectionSource(const FSoftObjectPath& SourceSoftObjectPath, const FTransform& ComponentTransform, const TArray<TObjectPtr<UMaterialInterface>>& SourceMaterials, bool bSplitComponents = false, bool bSetInternalFromMaterialIndex = false) : SourceGeometryObject(SourceSoftObjectPath), LocalTransform(ComponentTransform), SourceMaterial(SourceMaterials), bAddInternalMaterials(false), bSplitComponents(bSplitComponents), bSetInternalFromMaterialIndex(bSetInternalFromMaterialIndex)`
- L42 _public member_ `FSoftObjectPath SourceGeometryObject;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometrySource", meta=(AllowedClasses="/Script/Engine.StaticMesh, /Script/Engine.SkeletalMesh, /Script/GeometryCollectionEngine.GeometryCollection"))`
- L45 _public member_ `FTransform LocalTransform;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometrySource")`
- L48 _public member_ `TArray<TObjectPtr<UMaterialInterface>> SourceMaterial;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometrySource")`
- L51 _public member_ `TArray<float> InstanceCustomData;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometrySource|Instance")`
- L56 _public member_ `bool bAddInternalMaterials = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometrySource", DisplayName = "(Legacy) Add Internal Materials")` — (Legacy) Whether source materials will be duplicated to create new slots for internal materials, or existing odd materials will be considered internal. (For non-Geometry Collection inputs only.)
- L60 _public member_ `bool bSplitComponents = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometrySource", DisplayName = "Split Meshes")` — Whether individual source mesh components should be split into separate pieces of geometry based on mesh connectivity. If checked, triangles that are not topologically connected will be assigned separate bones. (For non-Geometry Collection inputs only.)
- L64 _public member_ `bool bSetInternalFromMaterialIndex = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometrySource")` — Whether to set the 'internal' flag for faces with odd-numbered materials slots.

#### struct `FGeometryCollectionAutoInstanceMesh`  
`struct FGeometryCollectionAutoInstanceMesh`  
_L70-94_
- reflection: `USTRUCT(BlueprintType)`
- L76 _public member_ `FSoftObjectPath StaticMesh_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Mesh instead."))`
- L80 _public member_ `TObjectPtr<const UStaticMesh> Mesh;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AutoInstance", meta = (AllowedClasses = "/Script/Engine.StaticMesh"))`
- L83 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AutoInstance")`
- L86 _public member_ `int32 NumInstances = 0;` — `UPROPERTY(VisibleAnywhere, Category = "AutoInstance")`
- L89 _public member_ `TArray<float> CustomData;` — `UPROPERTY(VisibleAnywhere, Category = "AutoInstance")`
- L91 _public prototype_ `int32 GetNumDataPerInstance() const;`
- L93 _public prototype_ `bool operator ==(const FGeometryCollectionAutoInstanceMesh& Other) const;`

#### struct `FGeometryCollectionEmbeddedExemplar`  
`struct FGeometryCollectionEmbeddedExemplar`  
_L97-126_
- reflection: `USTRUCT(BlueprintType)`
- L101 _public function_ `FGeometryCollectionEmbeddedExemplar() : StaticMeshExemplar(FString("None")) , StartCullDistance(0.0f) , EndCullDistance(0.0f) , InstanceCount(0)`
- L108 _public function_ `FGeometryCollectionEmbeddedExemplar(FSoftObjectPath NewExemplar) : StaticMeshExemplar(NewExemplar) , StartCullDistance(0.0f) , EndCullDistance(0.0f) , InstanceCount(0)`
- L116 _public member_ `FSoftObjectPath StaticMeshExemplar;` — `UPROPERTY(EditAnywhere, Category = "EmbeddedExemplar", meta = (AllowedClasses = "/Script/Engine.StaticMesh"))`
- L119 _public member_ `float StartCullDistance;` — `UPROPERTY(EditAnywhere, Category = "EmbeddedExemplar")`
- L122 _public member_ `float EndCullDistance;` — `UPROPERTY(EditAnywhere, Category = "EmbeddedExemplar")`
- L125 _public member_ `int32 InstanceCount;` — `UPROPERTY(VisibleAnywhere, Category = "EmbeddedExemplar")`

#### struct `FGeometryCollectionLevelSetData`  
`struct FGeometryCollectionLevelSetData`  
_L129-158_
- reflection: `USTRUCT()`
- L133 _public prototype_ `FGeometryCollectionLevelSetData();`
- L139 _public member_ `int32 MinLevelSetResolution;` — `UPROPERTY(EditAnywhere, Category = "LevelSet")` — Resolution on the smallest axes for the level set. (def: 5)
- L145 _public member_ `int32 MaxLevelSetResolution;` — `UPROPERTY(EditAnywhere, Category = "LevelSet")` — Resolution on the smallest axes for the level set. (def: 10)
- L151 _public member_ `int32 MinClusterLevelSetResolution;` — `UPROPERTY(EditAnywhere, Category = "LevelSet")` — Resolution on the smallest axes for the level set. (def: 5)
- L157 _public member_ `int32 MaxClusterLevelSetResolution;` — `UPROPERTY(EditAnywhere, Category = "LevelSet")` — Resolution on the smallest axes for the level set. (def: 10)

#### struct `FGeometryCollectionCollisionParticleData`  
`struct FGeometryCollectionCollisionParticleData`  
_L162-179_
- reflection: `USTRUCT()`
- L166 _public prototype_ `FGeometryCollectionCollisionParticleData();`
- L172 _public member_ `float CollisionParticlesFraction;` — `UPROPERTY(EditAnywhere, Category = "Particle")` — Number of particles on the triangulated surface to use for collisions.
- L178 _public member_ `int32 MaximumCollisionParticles;` — `UPROPERTY(EditAnywhere, Category = "Particle")` — Max number of particles.

#### struct `FGeometryCollectionCollisionTypeData`  
`struct FGeometryCollectionCollisionTypeData`  
_L184-228_
- reflection: `USTRUCT()`
- L188 _public prototype_ `FGeometryCollectionCollisionTypeData();`
- L194 _public member_ `ECollisionTypeEnum CollisionType;` — `UPROPERTY(EditAnywhere, Category = "Collisions")` — CollisionType defines how to initialize the rigid collision structures.
- L200 _public member_ `EImplicitTypeEnum ImplicitType;` — `UPROPERTY(EditAnywhere, Category = "Collisions")` — CollisionType defines how to initialize the rigid collision structures.
- L206 _public member_ `FGeometryCollectionLevelSetData LevelSet;` — `UPROPERTY(EditAnywhere, Category = "Collisions", meta = (EditCondition = "ImplicitType == EImplicitTypeEnum::Chaos_Implicit_LevelSet", EditConditionHides))` — LevelSet Resolution data for rasterization.
- L212 _public member_ `FGeometryCollectionCollisionParticleData CollisionParticles;` — `UPROPERTY(EditAnywhere, Category = "Collisions", meta = (EditCondition = "CollisionType == ECollisionTypeEnum::Chaos_Surface_Volumetric", EditConditionHides))` — Collision Particle data for surface samples during Particle-LevelSet collisions.
- L218 _public member_ `float CollisionObjectReductionPercentage;` — `UPROPERTY(EditAnywhere, Category = "Collisions")` — Uniform scale on the collision body. (def: 0)
- L226 _public member_ `float CollisionMarginFraction;` — `UPROPERTY(EditAnywhere, Category = "Collisions", meta = (EditCondition = "ImplicitType == EImplicitTypeEnum::Chaos_Implicit_Convex || ImplicitType == EImplicitTypeEnum::Chaos_Implicit_Box", EditConditionHides))` — A collision margin is a fraction of size used by some boxes and convex shapes to improve collision detection results. The core geometry of shapes that support a margin are reduced in size by the margin, and the margin is added back on during collision detection. The net result is a shape of the same size but with rounded corners.

#### struct `FGeometryCollectionSizeSpecificData`  
`struct FGeometryCollectionSizeSpecificData`  
_L232-314_
- reflection: `USTRUCT()`
- L236 _public prototype_ `FGeometryCollectionSizeSpecificData();`
- L240 _public member_ `float MaxSize;` — `UPROPERTY(EditAnywhere, Category = "Collisions")` — The max size these settings apply to
- L246 _public member_ `TArray<FGeometryCollectionCollisionTypeData> CollisionShapes;` — `UPROPERTY(EditAnywhere, Category = "Collisions")` — Collision Shapes allow kfor multiple collision types per rigid body.
- L253 _public member_ `ECollisionTypeEnum CollisionType_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Collision.CollisionType instead."))` — CollisionType defines how to initialize the rigid collision structures.
- L259 _public member_ `EImplicitTypeEnum ImplicitType_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Collision.ImplicitType instead."))` — CollisionType defines how to initialize the rigid collision structures.
- L265 _public member_ `int32 MinLevelSetResolution_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Collision.LevelSet.MinLevelSetResolution instead."))` — Resolution on the smallest axes for the level set. (def: 5)
- L271 _public member_ `int32 MaxLevelSetResolution_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Collision.LevelSet.MaxLevelSetResolution instead."))` — Resolution on the smallest axes for the level set. (def: 10)
- L277 _public member_ `int32 MinClusterLevelSetResolution_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Collision.LevelSet.MinClusterLevelSetResolution instead."))` — Resolution on the smallest axes for the level set. (def: 5)
- L283 _public member_ `int32 MaxClusterLevelSetResolution_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Collision.LevelSet.MaxClusterLevelSetResolution instead."))` — Resolution on the smallest axes for the level set. (def: 10)
- L289 _public member_ `int32 CollisionObjectReductionPercentage_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Collision.CollisionObjectReductionPercentage instead."))` — Resolution on the smallest axes for the level set. (def: 10)
- L295 _public member_ `float CollisionParticlesFraction_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Collision.CollisionParticlesFraction instead."))` — Number of particles on the triangulated surface to use for collisions.
- L301 _public member_ `int32 MaximumCollisionParticles_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Collision.MaximumCollisionParticles instead."))` — Max number of particles.
- L308 _public member_ `int32 DamageThreshold;` — `UPROPERTY(EditAnywhere, Category = "Collisions")` — Max number of particles.
- L310 _public prototype_ `bool Serialize(FArchive& Ar);`
- L312 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGeometryCollectionSizeSpecificData> : public TStructOpsTypeTraitsBase2<FGeometryCollectionSizeSpecificData>`  
_L317-327_
- inherits: `TStructOpsTypeTraitsBase2<FGeometryCollectionSizeSpecificData>`
- L326 _public member_ `static constexpr EPropertyObjectReferenceType WithSerializerObjectReferences = EPropertyObjectReferenceType::None;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L320-325_

#### struct `FGeometryCollectionProxyMeshMaterials`  
`struct FGeometryCollectionProxyMeshMaterials`  
_L330-336_
- reflection: `USTRUCT(BlueprintType)`
- L335 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")`

#### struct `FGeometryCollectionProxyMeshData`  
`struct FGeometryCollectionProxyMeshData`  
_L339-365_
- reflection: `USTRUCT(BlueprintType)`
- L345 _public member_ `TArray<TObjectPtr<UStaticMesh>> ProxyMeshes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (AllowedClasses = "/Script/Engine.StaticMesh"))` — References to meshes to be used as proxies for rendering when the geometry collection is not broken yet
- L353 _public member_ `TArray<FTransform3f> MeshTransforms;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Transform of the mesh relative to the geometry collection it belongs to if an entry is missing or if the arary is empty , those transforms are assume to be identity making any proxy mesh done before 5.6 be fully backward compatible
- L360 _public member_ `TArray<FGeometryCollectionProxyMeshMaterials> MeshOverrideMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Optional arrays of override material matching each proxy Mesh if an entry is missing or if the arary is empty , then no material will be assigned
- L362 _public prototype_ `const FTransform3f& GetMeshTransform(int32 MeshIndex) const;`
- L364 _public prototype_ `void Reset();`

#### struct `FGeometryCollectionRenderResourceSizeInfo`  
`struct FGeometryCollectionRenderResourceSizeInfo`  
_L368-379_
- reflection: `USTRUCT()`
- L374 _public member_ `uint64 MeshResourcesSize = 0;` — `UPROPERTY()` — Total size of the arrays for the MeshResources
- L378 _public member_ `uint64 NaniteResourcesSize = 0;` — `UPROPERTY()` — Total size of the arrays for the NaniteResources

#### class `UGeometryCollection`  
`class UGeometryCollection : public UObject, public IInterface_AssetUserData, public IDataflowContentOwner, public IDataflowInstanceInterface`  
_L388-1017_
- reflection: `UCLASS(BlueprintType, customconstructor, MinimalAPI)`
- inherits: `UObject,IInterface_AssetUserData,IDataflowContentOwner,IDataflowInstanceInterface`
- desc: UGeometryCollectionObject (UObject) UObject wrapper for the FGeometryCollection
- L397 _public prototype_ `UGeometryCollection(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L401 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L402 _public prototype_ `virtual void PostEditUndo() override;`
- L403 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;`
- L405 _public prototype_ `virtual void PostInitProperties() override;`
- L406 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L407 _public prototype_ `virtual void PostLoad() override;`
- L408 _public prototype_ `virtual void BeginDestroy() override;`
- L409 _public prototype_ `virtual bool IsReadyForFinishDestroy() override;`
- L412 _public prototype_ `void Serialize(FArchive& Ar);`
- L415 _public prototype_ `static void AppendToClassSchema(FAppendToClassSchemaContext& Context);`
- L416 _public prototype_ `void EnsureDataIsCooked(bool bInitResources, bool bIsTransacting, bool bIsPersistent, bool bAllowCopyFromDDC = true);`
- L420 _public function_ `void SetGeometryCollection(TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe> GeometryCollectionIn)` — Accessors for internal geometry collection
- L421 _public function_ `TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe> GetGeometryCollection()`
- L422 _public function_ `const TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe> GetGeometryCollection() const`
- L425 _public prototype_ `bool IsEmpty() const;` — Return true if the collection is "Empty" ( has no transforms at all )
- L428 _public prototype_ `void Reset();` — Return collection to initial (ie. empty) state.
- L431 _public prototype_ `void ResetFrom(const FManagedArrayCollection& InCollection, const TArray<UMaterial*>& InMaterials, bool bHasInternalMaterials);` — Reset the collection from another set of attributes and materials.
- L432 _public prototype_ `void ResetFrom(const FManagedArrayCollection& InCollection, const TArray<UMaterialInterface*>& InMaterialInstances, bool bHasInternalMaterials);`
- L434 _public prototype_ `int32 AppendGeometry(const UGeometryCollection & Element, bool ReindexAllMaterials = false, const FTransform& TransformRoot = FTransform::Identity);`
- L435 _public prototype_ `int32 NumElements(const FName& Group) const;`
- L436 _public prototype_ `void RemoveElements(const FName& Group, const TArray<int32>& SortedDeletionList);`
- L439 _public prototype_ `bool HasMeshData() const;` — Has data for static mesh rendering.
- L441 _public prototype_ `bool HasNaniteData() const;` — Has data for nanite rendering.
- L443 _public prototype_ `uint32 GetNaniteResourceID() const;`
- L444 _public prototype_ `uint32 GetNaniteHierarchyOffset() const;`
- L445 _public prototype_ `uint32 GetNaniteHierarchyOffset(int32 GeometryIndex, bool bFlattened = false) const;`
- L448 _public prototype_ `void ReindexMaterialSections();` — ReindexMaterialSections
- L451 _public prototype_ `void InitializeMaterials(bool bHasLegacyInternalMaterialsPairs = false);` — appends the standard materials to this UObject
- L454 _public prototype_ `int32 AddNewMaterialSlot(bool bCopyLastMaterial = true);` — Add a material to the materials array and update the selected bone material to be at the end of the array
- L457 _public prototype_ `bool RemoveLastMaterialSlot();` — Remove a material from the materials array, keeping the selected bone material at the end of the array. Returns false if materials could not be removed (e.g. because there were too few).
- L461 _public prototype_ `bool HasVisibleGeometry() const;` — Returns true if there is anything to render
- L464 _public prototype_ `void InvalidateCollection();` — Invalidates this collection signaling a structural change and renders any previously recorded caches unable to play with this collection
- L467 _public prototype_ `bool IsSimulationDataDirty() const;` — Check to see if Simulation Data requires regeneration
- L470 _public prototype_ `int32 AttachEmbeddedGeometryExemplar(const UStaticMesh* Exemplar);` — Attach a Static Mesh exemplar for embedded geometry, if that mesh has not already been attached. Return the exemplar index.
- L473 _public prototype_ `void RemoveExemplars(const TArray<int32>& SortedRemovalIndices);` — Remove embedded geometry exemplars with indices matching the sorted removal list.
- L476 _public prototype_ `const FGeometryCollectionAutoInstanceMesh& GetAutoInstanceMesh(int32 AutoInstanceMeshIndex) const;` — find or add a auto instance mesh and return its index
- L482 _public prototype_ `void SetAutoInstanceMeshes(const TArray<FGeometryCollectionAutoInstanceMesh>& InAutoInstanceMeshes);` — Assign an auto instanced meshes array if there's duplicate entry in the array , they will be collapsed as one and the index attribute will be adjusted acoordingly
- L485 _public prototype_ `int32 FindOrAddAutoInstanceMesh(const FGeometryCollectionAutoInstanceMesh& AutoInstanceMesh);` — find or add a auto instance mesh from another one and return its index
- L488 _public prototype_ `int32 FindOrAddAutoInstanceMesh(const UStaticMesh* StaticMesh, const TArray<UMaterialInterface*>& Materials);` — find or add a auto instance mesh from a mesh and alist of material and return its index
- L491 _public prototype_ `TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe> GenerateMinimalGeometryCollection() const;` — Produce a deep copy of GeometryCollection member, stripped of data unecessary for gameplay.
- L494 _public prototype_ `static TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe> CopyCollectionAndRemoveGeometry(const TSharedPtr<const FGeometryCollection, ESPMode::ThreadSafe>& CollectionToCopy);` — copy a collection and remove geometry from it
- L497 _public prototype_ `FGeometryCollectionRenderResourceSizeInfo GetRenderResourceSizeInfo() const;` — get the size of the render data resources associated with this collection
- L501 _public member_ `bool bManualDataCreate;` — If this flag is set, we only regenerate simulation data when requested via CreateSimulationData()
- L508 _public prototype_ `void CreateSimulationData();` — Create the simulation data that can be shared among all instances (mass, volume, etc...) Note : this does not check if the simulation data is drty or not and will cause a load from the DDC use CreateSimulationDataIfNeeded() for avoiding extra runtime cost
- L511 _public prototype_ `void CreateSimulationDataIfNeeded();` — Create the simulation data ( calls CreateSimulationData) only if the simulation data is dirty
- L514 _public prototype_ `void RebuildRenderData();` — Rebuild the render data.
- L517 _public prototype_ `void PropagateMarkDirtyToComponents() const;` — Propogate render state dirty to components
- L520 _public prototype_ `void PropagateTransformUpdateToComponents() const;` — Propogate the fact that transform have been updated to all components
- L523 _public prototype_ `void SetRootProxiesFromGeometrySources();` — Create root proxies from geometryt sources
- L527 _public prototype_ `void InitResources();`
- L528 _public prototype_ `void ReleaseResources();`
- L531 _public prototype_ `void GetSharedSimulationParams(FSharedSimulationParameters& OutParams) const;` — Fills params struct with parameters used for precomputing content.
- L538 _public prototype_ `float GetMassOrDensity(bool& bOutIsDensity) const;` — Get Mass or density as set by the asset ( this is the value used by to compute the cached attributes ) Mass is return in Kg and Density is returned in Kg/Cm3 @param bOutIsDensity  is set to true by the function if the returned value is to be treated as a density
- L544 _public prototype_ `void CacheMaterialDensity();` — cache the material density used to compute attribute Warning : this should only be called after recomputing the mass based on those values
- L547 _public prototype_ `FGuid GetIdGuid() const;` — Accessors for the two guids used to identify this collection
- L548 _public prototype_ `FGuid GetStateGuid() const;`
- L551 _public function_ `int32 GetRootIndex() const` — Get the cached root index
- L554 _public member_ `TUniquePtr<FGeometryCollectionRenderData> RenderData;` — Pointer to the data used to render this geometry collection.
- L557 _public member_ `bool EnableClustering;` — `UPROPERTY(EditAnywhere, Category = "Clustering")`
- L561 _public member_ `int32 ClusterGroupIndex;` — `UPROPERTY(EditAnywhere, Category = "Clustering")` — Cluster group index - Geometry Collections using the same index will simulate as one single cluster.
- L565 _public member_ `int32 MaxClusterLevel;` — `UPROPERTY(EditAnywhere, Category = "Clustering")` — Maximum level for cluster breaks.
- L569 _public member_ `EDamageModelTypeEnum DamageModel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")` — Damage model to use for evaluating destruction.
- L573 _public member_ `TArray<float> DamageThreshold;` — `UPROPERTY(EditAnywhere, Category = "Damage", meta = (EditCondition = "!bUseSizeSpecificDamageThreshold && DamageModel == EDamageModelTypeEnum::Chaos_Damage_Model_UserDefined_Damage_Threshold"))` — Damage threshold for clusters at different levels.
- L577 _public member_ `bool bUseSizeSpecificDamageThreshold;` — `UPROPERTY(EditAnywhere, Category = "Damage", meta = (EditCondition = "DamageModel == EDamageModelTypeEnum::Chaos_Damage_Model_UserDefined_Damage_Threshold"))` — whether to use size specific damage threshold instead of level based ones ( see Size Specific Data array ).
- L581 _public member_ `bool bUseMaterialDamageModifiers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (EditCondition = "DamageModel == EDamageModelTypeEnum::Chaos_Damage_Model_UserDefined_Damage_Threshold"))` — When on , use the modifiers on the material to adjust the user defined damage threshold values
- L587 _public member_ `bool PerClusterOnlyDamageThreshold;` — `UPROPERTY(EditAnywhere, Category = "Compatibility")` — compatibility check, when true, only cluster compute damage from parameters and propagate to direct children when false, each child will compute it's damage threshold allowing for more precise and intuitive destruction behavior
- L591 _public member_ `FGeometryCollectionDamagePropagationData DamagePropagationData;` — `UPROPERTY(EditAnywhere, Category = "Damage")` — Data about how damage propagation shoudl behave.
- L595 _public member_ `EClusterConnectionTypeEnum ClusterConnectionType;` — `UPROPERTY(EditAnywhere, Category = "Clustering")`
- L598 _public member_ `float ConnectionGraphBoundsFilteringMargin;` — `UPROPERTY(EditAnywhere, Category = "Clustering")`
- L602 _public member_ `TArray<FGeometryCollectionSource> GeometrySource;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GeometrySource")`
- L606 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(EditAnywhere, Category = "Materials")`
- L610 _public member_ `TArray<FGeometryCollectionEmbeddedExemplar> EmbeddedGeometryExemplar;` — `UPROPERTY(EditAnywhere, Category = "EmbeddedGeometry")` — References for embedded geometry generation
- L614 _public member_ `bool bUseFullPrecisionUVs = false;` — `UPROPERTY(EditAnywhere, Category = "Rendering")` — Whether to use full precision UVs when rendering this geometry. (Does not apply to Nanite rendering)
- L620 _public member_ `bool bStripOnCook;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (DisplayName = "Strip Source Data On Cook"))` — Strip unnecessary data from the Geometry Collection to keep the memory footprint as small as possible.
- L627 _public member_ `bool bStripRenderDataOnCook;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Strip unnecessary render data from the Geometry Collection to keep the memory footprint as small as possible. This may be used if the cooked build uses a custom renderer such as the ISMPool renderer.
- L633 _public member_ `uint8 bSupportRayTracing : 1;` — `UPROPERTY(EditAnywhere, Category = "Rendering")` — If true, a ray tracing acceleration structure will be built for this geometry collection and it may be used in ray tracing effects
- L637 _public member_ `TObjectPtr<UClass> CustomRendererType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (MustImplement = "/Script/GeometryCollectionEngine.GeometryCollectionExternalRenderInterface"))` — Custom class type that will be used to render the geometry collection instead of using the native rendering.
- L641 _public member_ `FGeometryCollectionProxyMeshData RootProxyData;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rendering")` — Static mesh to use as a proxy for rendering until the geometry collection is broken.
- L645 _public member_ `TArray<FGeometryCollectionAutoInstanceMesh> AutoInstanceMeshes;` — `UPROPERTY(EditAnywhere, Category = "Rendering")` — List of unique static mesh / materials pairs for auto instancing.
- L648 _public prototype_ `void SetEnableNanite(bool bValue);` — `UFUNCTION(BlueprintCallable, Category = "Nanite")`
- L654 _public member_ `bool EnableNanite;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetEnableNanite, Category = "Nanite")` — Enable support for Nanite.
- L660 _public member_ `bool bEnableNaniteFallback;` — `UPROPERTY(EditAnywhere, Category = "Nanite", Meta = (EditCondition = "EnableNanite"))` — Enable Non-Nanite fallback mesh when Nanite support is enabled.
- L666 _public member_ `uint32 NaniteMinimumResidencyInKB;` — `UPROPERTY(EditAnywhere, Category = "Nanite", Meta = (EditCondition = "EnableNanite", DisplayName = "Nanite Minimum Residency"))` — How much of the nanite resource should always be resident (In KB). Approximate due to paging. 0: Minimum size (single page). MAX_uint32: Entire mesh.
- L669 _public prototype_ `void SetConvertVertexColorsToSRGB(bool bValue);` — `UFUNCTION(BlueprintCallable, Category = "Rendering")`
- L675 _public member_ `bool bConvertVertexColorsToSRGB = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetConvertVertexColorsToSRGB, Category = "Rendering")` — Convert vertex colors to sRGB for rendering. Exposed to avoid changing vertex color rendering for legacy assets; should typically be true for new geometry collections.
- L682 _public member_ `ECollisionTypeEnum CollisionType_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Use the default SizeSpecificData instead."))` — CollisionType defines how to initialize the rigid collision structures.
- L688 _public member_ `EImplicitTypeEnum ImplicitType_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Use the default SizeSpecificData instead."))` — CollisionType defines how to initialize the rigid collision structures.
- L694 _public member_ `int32 MinLevelSetResolution_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Use the default SizeSpecificData instead."))` — Resolution on the smallest axes for the level set. (def: 5)
- L700 _public member_ `int32 MaxLevelSetResolution_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Use the default SizeSpecificData instead."))` — Resolution on the smallest axes for the level set. (def: 10)
- L706 _public member_ `int32 MinClusterLevelSetResolution_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Use the default SizeSpecificData instead."))` — Resolution on the smallest axes for the level set. (def: 5)
- L712 _public member_ `int32 MaxClusterLevelSetResolution_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Use the default SizeSpecificData instead."))` — Resolution on the smallest axes for the level set. (def: 10)
- L718 _public member_ `float CollisionObjectReductionPercentage_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Use the default SizeSpecificData instead."))` — Resolution on the smallest axes for the level set. (def: 10)
- L722 _public member_ `FSoftObjectPath RootProxy_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Use RootProxyData instead."))` — static mesh to use as a proxy for rendering until the geometry collection is broken
- L727 _public member_ `TObjectPtr<UPhysicalMaterial> PhysicsMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collisions")` — Physics material to use for the geometry collection
- L733 _public member_ `bool bDensityFromPhysicsMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collisions", meta = (EditCondition = "PhysicsMaterial != nullptr"))` — Whether to use density ( for mass computation ) from physics material ( if physics material is not set, use the component one or defaults )
- L740 _public member_ `float CachedDensityFromPhysicsMaterialInGCm3;` — `UPROPERTY()` — Cached Material density value used to compute the Mass attribute  ( In gram per cm3 ) this is necessary because the material properties could be changed after without causing the mass attribute to be recomputed ( because the GC asset will not get notified )
- L746 _public member_ `bool bMassAsDensity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collisions", meta = (EditCondition = "!bDensityFromPhysicsMaterial"))` — Mass As Density, units are in kg/m^3 ( only enabled if physics material is not set )
- L752 _public member_ `float Mass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collisions", meta = (EditCondition = "!bDensityFromPhysicsMaterial"))` — Total Mass of Collection. If density, units are in kg/m^3 ( only enabled if physics material is not set )
- L758 _public member_ `float MinimumMassClamp;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collisions")` — Smallest allowable mass (def:0.1)
- L764 _public member_ `bool bImportCollisionFromSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collisions")` — whether to import collision from the source asset
- L772 _public member_ `bool bOptimizeConvexes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collisions")` — whether to optimize convexes for collisions. If true the convex optimizer will generate at runtime one single convex shape for physics collisions ignoring all the user defined ones. Enable p.Chaos.Convex.SimplifyUnion cvar to be able to use it (experimental)
- L779 _public member_ `float CollisionParticlesFraction_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Use the default SizeSpecificData instead."))` — Number of particles on the triangulated surface to use for collisions.
- L785 _public member_ `int32 MaximumCollisionParticles_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Use the default SizeSpecificData instead."))` — Max number of particles.
- L790 _public member_ `bool bScaleOnRemoval;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Removal)` — When enabled, particle will scale down (shrink) when using being removed ( using both remove on sleep or remove on break ) - Enabled by default
- L794 _public member_ `bool bRemoveOnMaxSleep;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Removal, meta = (DisplayName = "Remove on Sleep"))` — Remove particle from simulation and dissolve rendered geometry once sleep threshold has been exceeded.
- L798 _public member_ `bool bAutomaticCrumblePartialClusters;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Removal, meta = (EditCondition = "bRemoveOnMaxSleep"))` — When using remove on sleep , automatically crumble partial cluster into smaller pieces when possible
- L802 _public member_ `FVector2D MaximumSleepTime;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Removal, meta = (DisplayName = "Sleep Min Max", EditCondition="bRemoveOnMaxSleep"))` — How long may the particle sleep before initiating removal (in seconds).
- L806 _public member_ `FVector2D RemovalDuration;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Removal, meta = (DisplayName = "Removal Duration", EditCondition="bRemoveOnMaxSleep"))` — How long does the removal process take (in seconds).
- L810 _public member_ `bool bSlowMovingAsSleeping;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Removal, meta = (DisplayName = "Slow-Moving as sleeping", EditCondition="bRemoveOnMaxSleep"))` — when on non-sleeping, slow moving pieces will be considered as sleeping, this helps removal of jittery but not really moving objects.
- L814 _public member_ `float SlowMovingVelocityThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Removal, meta = (DisplayName = "Slow-Moving Velocity Threshold", EditCondition="bRemoveOnMaxSleep && bSlowMovingAsSleeping"))` — When slow moving detection is on, this defines the linear velocity thresholds in cm/s to consider the object as sleeping .
- L822 _public member_ `TArray<FGeometryCollectionSizeSpecificData> SizeSpecificData;` — `UPROPERTY(EditAnywhere, Category = "Collisions")` — Size Specfic Data reflects the default geometry to bind to rigid bodies smaller than the max size volume. This can also be empty to reflect no collision geometry for the collection.
- L824 _public prototype_ `int GetDefaultSizeSpecificDataIndex() const;`
- L825 _public prototype_ `FGeometryCollectionSizeSpecificData& GetDefaultSizeSpecificData();`
- L826 _public prototype_ `const FGeometryCollectionSizeSpecificData& GetDefaultSizeSpecificData() const;`
- L827 _public prototype_ `static FGeometryCollectionSizeSpecificData GeometryCollectionSizeSpecificDataDefaults();`
- L833 _public member_ `bool EnableRemovePiecesOnFracture_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use remove on break feature instead ( Fracture editor tools )."))` — Enable remove pieces on fracture
- L839 _public member_ `TArray<TObjectPtr<UMaterialInterface>> RemoveOnFractureMaterials_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use remove on break feature instead ( Fracture editor tools )."))` — Materials relating to remove on fracture
- L842 _public function_ `FORCEINLINE const int32 GetBoneSelectedMaterialIndex() const` — `UE_DEPRECATED(5.5, "Bone Selected Material does not have a material index anymore.")`
- L845 _public prototype_ `static UMaterialInterface* GetBoneSelectedMaterial();` — Get the material to use for rendering bone selections in the editor, or nullptr
- L848 _public prototype_ `static const TCHAR* GetSelectedMaterialPath();` — Returns the asset path for the automatically populated selected material.
- L853 _public member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = ImportSettings)` — Importing data and options used for this geometry collection
- L857 _public member_ `TObjectPtr<class UThumbnailInfo> ThumbnailInfo;` — `UPROPERTY(VisibleAnywhere, Instanced, AdvancedDisplay, Category = GeometryCollection)` — Information for thumbnail rendering
- L863 _public prototype_ `void UpdateConvexGeometry();` — Update the convex geometry on the collection.
- L864 _public prototype_ `void UpdateConvexGeometryIfMissing();`
- L869 _public prototype_ `void UpdateGeometryDependentProperties();` — Update properties that depend on the geometry and clustering: Proximity, Convex Hulls, Volume and Size data.
- L873 _public prototype_ `virtual void AddAssetUserData(UAssetUserData* InUserData) override;`
- L874 _public prototype_ `virtual void RemoveUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L875 _public prototype_ `virtual UAssetUserData* GetAssetUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L876 _public prototype_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override;`
- L886 _public member_ `TObjectPtr<UDataflow> DataflowAsset;` — `UPROPERTY(BlueprintReadWrite, BlueprintSetter=SetDataflowAsset, BlueprintGetter = GetDataflowAsset, Category = "Dataflow")` — this is deprecated data replaced with Setter and Getter but it is exposed to blueprint so we use the Setter/Getter to make sure the blueprint will use them
- L889 _public member_ `FString DataflowTerminal_DEPRECATED = "Ge` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Dataflow terminal name is now stored in DataflowInstance"))`
- L893 _public member_ `TMap<FString, FString> Overrides;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dataflow", DisplayName = "DataFlow Overrides", meta = (DisplayAfter = "DataflowInstance"))`
- L896 _public member_ `FDataflowInstance DataflowInstance;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L899 _public prototype_ `void SetDataflowAsset(UDataflow* InDataflowAsset);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow")`
- L902 _public prototype_ `UDataflow* GetDataflowAsset() const;` — `UFUNCTION(BlueprintCallable, Category = "Dataflow")`
- L905 _public function_ `virtual const FDataflowInstance& GetDataflowInstance() const override`
- L906 _public function_ `virtual FDataflowInstance& GetDataflowInstance() override`
- L910 _public prototype_ `virtual TObjectPtr<UDataflowBaseContent> CreateDataflowContent() override;`
- L911 _public prototype_ `virtual void WriteDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) const override;`
- L912 _public prototype_ `virtual void ReadDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) override;`
- L915 _public function_ `const TArray<int32>& GetBreadthFirstTransformIndices() const`
- L917 _public function_ `const TArray<int32>& GetAutoInstanceTransformRemapIndices() const`
- L920 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L925 _private prototype_ `void CreateSimulationDataImp(bool bCopyFromDDC);`
- L926 _private prototype_ `void CreateRenderDataImp(bool bCopyFromDDC);`
- L928 _private prototype_ `void EnsureSimulationDataIsCooked(bool bIsTransacting, bool bAllowCopyFromDDC);`
- L929 _private prototype_ `void EnsureRenderDataIsCooked(bool bInitResources);`
- L937 _private prototype_ `void ValidateSizeSpecificDataDefaults();` — Used to transfer deprecated properties to the size specific structures during serialization and to add back the default size specific data when deleted.
- L940 _private prototype_ `void UpdateRootIndex();` — update cached root index using the current hierarchy setup
- L943 _private prototype_ `void FillAutoInstanceMeshesInstancesIfNeeded();` — fill instanced mesh instance count from geometry collection data if not done yet
- L945 _private prototype_ `void CacheBreadthFirstTransformIndices();`
- L946 _private prototype_ `void CacheAutoInstanceTransformRemapIndices();`
- L951 _private member_ `FGuid PersistentGuid;` — `UPROPERTY()` — Guid created on construction of this collection. It should be used to uniquely identify this collection
- L959 _private member_ `FGuid StateGuid;` — `UPROPERTY()` — Guid that can be invalidated on demand - essentially a 'version' that should be changed when a structural change is made to the geometry collection. This signals to any caches that attempt to link to a geometry collection whether the collection is still valid (hasn't structurally changed post-recording)
- L963 _private member_ `FGuid LastBuiltSimulationDataGuid;` — Used to determine whether we need to cook simulation data
- L965 _private member_ `FGuid SimulationDataGuid;` — Used to determine whether we need to regenerate simulation data
- L968 _private member_ `FGuid LastBuiltRenderDataGuid;` — Used to determine whether we need to cook render data
- L970 _private member_ `FGuid RenderDataGuid;` — Used to determine whether we need to regenerate render data
- L981 _private member_ `FGuid ValidRenderDataGuid;` — `UPROPERTY()` — Serialized version of RenderDataGuid. This is used to determine when the stored RenderData mismatches the current GC object state. This can happen temporarily in editor during a undo/redo transaction when a GC component processing the PostUndo() before the GC object. todo: Remove this fix and move all relevent state to the RenderData so that it is the only source of truth for render scene proxies.
- L986 _private member_ `int32 RootIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Clustering")` — cached root index for faster queries
- L990 _private member_ `TArray<int32> BreadthFirstTransformIndices;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "Clustering")` — cache transform indices in breadth-first order
- L994 _private member_ `TArray<int32> AutoInstanceTransformRemapIndices;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "Clustering")` — cache transform remapping for instanced meshes indices
- L1000 _private member_ `int32 BoneSelectedMaterialIndex = INDEX_NONE;` — `UPROPERTY()` — Legacy index of the bone selected material in the object's Materials array, or INDEX_NONE if it is not stored there. Note for new objects the bone selected material should not be stored in the Materials array, so this should be INDEX_NONE The property is kept solely to support deletion of the bone selected material from the materials list of legacy assets
- L1002 _private member_ `TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe> GeometryCollection;`
- L1006 _private member_ `TArray<TObjectPtr<UAssetUserData>> AssetUserData;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Instanced, Category = AssetUserData)` — Array of user data stored with the asset
- L1009 _private member_ `FRenderCommandFence RenderResourceReleaseFence;` — A fence to track render resource release before destroy.
- L1011 _private prototype_ `float GetMassOrDensityInternal(bool& bOutIsDensity, bool bCached) const;`
- L1013 _private prototype_ `void MigrateDeprecatedRootProxyData();`
- L1014 _private prototype_ `void MigrateDeprecatedDataflowData();`
- L1016 _private prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`

#### Free symbols / members of external scopes

- L321 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonb468153d0103`)
- L323 _enumerator_ `WithPostSerialize = true #endif` (scope `TStructOpsTypeTraits::__anonb468153d0103`)

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionParticlesData.h` (Public)


#### enum `EGeometryCollectionParticlesData`  
`enum class EGeometryCollectionParticlesData : uint8`  
_L26-58_
- desc: Enumeration of the synchronizable data.
- L28 _public enumerator_ `X`
- L29 _public enumerator_ `R`
- L30 _public enumerator_ `Geometry`
- L31 _public enumerator_ `GeometryType`
- L32 _public enumerator_ `GeometryIsConvex`
- L33 _public enumerator_ `GeometryHasBoundingBox`
- L34 _public enumerator_ `GeometryBoxMin`
- L35 _public enumerator_ `GeometryBoxMax`
- L36 _public enumerator_ `GeometrySphereCenter`
- L37 _public enumerator_ `GeometrySphereRadius`
- L38 _public enumerator_ `GeometryLevelSetGrid`
- L39 _public enumerator_ `V`
- L40 _public enumerator_ `W`
- L41 _public enumerator_ `F`
- L42 _public enumerator_ `Torque`
- L43 _public enumerator_ `I`
- L44 _public enumerator_ `InvI`
- L45 _public enumerator_ `M`
- L46 _public enumerator_ `InvM`
- L47 _public enumerator_ `CollisionParticlesSize`
- L48 _public enumerator_ `Disabled`
- L49 _public enumerator_ `Sleeping`
- L50 _public enumerator_ `Island`
- L51 _public enumerator_ `P`
- L52 _public enumerator_ `Q`
- L53 _public enumerator_ `PreV`
- L54 _public enumerator_ `PreW`
- L55 _public enumerator_ `ConnectivityEdges`
- L56 _public enumerator_ `ChildToParentMap`
- L57 _public enumerator_ `Count`

#### class `FGeometryCollectionParticlesData`  
`class FGeometryCollectionParticlesData`  
_L66-185_
- desc: Object holding selected particles data for a specific range of rigid body ids. Use SetDataSyncFlag, SetAllDataSyncFlag, or RequestSyncedData to have the required data made available at the next tick. Each time Sync is called, the particles' data is copied and the sync flags cleared. Use HasSyncedData or RequestSyncedData to check which data is available at any one time.
- L70 _public prototype_ `FGeometryCollectionParticlesData();` — Constructor.
- L73 _public function_ `void SetDataSyncFlag(EGeometryCollectionParticlesData Data) const` — Set this data type to copy at the next sync.
- L76 _public function_ `void SetAllDataSyncFlag() const` — Set all data type to copy at the next sync.
- L79 _public function_ `bool HasSyncedData(EGeometryCollectionParticlesData Data) const` — Return whether the specified type of data has been copied during the last sync.
- L82 _public function_ `bool RequestSyncedData(EGeometryCollectionParticlesData Data) const` — Shorthand for both setting the flag and checking the data has already been synced.
- L86 _public prototype_ `void Sync(Chaos::FPhysicsSolver* Solver, const TManagedArray<FGuid>& RigidBodyIds);` — void Sync(const Chaos::FPhysicsSolver* Solver, const TManagedArray<int32>& RigidBodyIds);
- L88 _public function_ `const Chaos::FVec3 & GetX (int32 Index) const`
- L89 _public function_ `const Chaos::FRotation3 & GetR (int32 Index) const`
- L90 _public function_ `const Chaos::FImplicitObject* const & GetGeometry (int32 Index) const`
- L91 _public function_ `const Chaos::EImplicitObjectType & GetGeometryType (int32 Index) const`
- L92 _public function_ `const bool & IsGeometryConvex (int32 Index) const`
- L93 _public function_ `const bool & HasGeometryBoundingBoxm (int32 Index) const`
- L94 _public function_ `const Chaos::FVec3 & GetGeometryBoxMin (int32 Index) const`
- L95 _public function_ `const Chaos::FVec3 & GetGeometryBoxMax (int32 Index) const`
- L96 _public function_ `const Chaos::FVec3 & GetGeometrySphereCenter (int32 Index) const`
- L97 _public function_ `const Chaos::FReal & GetGeometrySphereRadius (int32 Index) const`
- L98 _public function_ `const Chaos::TUniformGrid<Chaos::FReal, 3> & GetGeometryLevelSetGrid (int32 Index) const`
- L99 _public function_ `const Chaos::FVec3 & GetV (int32 Index) const`
- L100 _public function_ `const Chaos::FVec3 & GetW (int32 Index) const`
- L101 _public function_ `const Chaos::FVec3 & GetF (int32 Index) const`
- L102 _public function_ `const Chaos::FVec3 & GetTorque (int32 Index) const`
- L103 _public function_ `const Chaos::FMatrix33 & GetI (int32 Index) const`
- L104 _public function_ `const Chaos::FMatrix33 & GetInvI (int32 Index) const`
- L105 _public function_ `const Chaos::FReal & GetM (int32 Index) const`
- L106 _public function_ `const Chaos::FReal & GetInvM (int32 Index) const`
- L107 _public function_ `const int32 & GetCollisionParticlesSize(int32 Index) const`
- L108 _public function_ `const bool & IsDisabled (int32 Index) const`
- L109 _public function_ `const bool & IsSleeping (int32 Index) const`
- L110 _public function_ `const int32 & GetIsland (int32 Index) const`
- L111 _public function_ `const Chaos::FVec3 & GetP (int32 Index) const`
- L112 _public function_ `const Chaos::FRotation3 & GetQ (int32 Index) const`
- L113 _public function_ `const Chaos::FVec3 & GetPreV (int32 Index) const`
- L114 _public function_ `const Chaos::FVec3 & GetPreW (int32 Index) const`
- L115 _public function_ `const TArray<Chaos::TConnectivityEdge<Chaos::FReal>> & GetConnectivityEdges (int32 Index) const`
- L116 _public function_ `const Chaos::FRigidTransform3 & GetChildToParentMap (int32 Index) const`
- L119 _public function_ `FString ToString(int32 Index, const TCHAR* Separator = TEXT(", ")) cons` — Return a string with the entire set of value for the synced data of the specified particle.
- L123 _private typedef_ `typedef TStaticBitArray<uint32(EGeometryCollectionParticlesData::Count)> FDataFlags;` — Data bit selection type.
- L180 _private member_ `const FChaosSolversModule* ChaosModule;`
- L181 _private member_ `Chaos::TBufferedData<FData> BufferedData;`
- L182 _private member_ `FThreadSafeCounter PhysicsSyncCount;`
- L183 _private member_ `int32 GameSyncCount;`
- L184 _private member_ `uint64 SyncFrame;`

#### struct `FGeometryCollectionParticlesData::FData`  
`struct FData`  
_L126-178_
- desc: Structure used to exchange data between game and physics thread.
- L128 _public member_ `mutable FDataFlags RequiredDataFlags;` — Mutable in order to allow const versions of all of this object's methods outside of the Sync process.
- L129 _public member_ `FDataFlags SyncedDataFlags;`
- L130 _public member_ `Chaos::TArrayCollectionArray<Chaos::FVec3 > X;`
- L131 _public member_ `Chaos::TArrayCollectionArray<Chaos::FRotation3 > R;`
- L132 _public member_ `Chaos::TArrayCollectionArray<const Chaos::FImplicitObject* > Geometry;`
- L133 _public member_ `Chaos::TArrayCollectionArray<Chaos::EImplicitObjectType > GeometryType;`
- L134 _public member_ `Chaos::TArrayCollectionArray<bool > GeometryIsConvex;`
- L135 _public member_ `Chaos::TArrayCollectionArray<bool > GeometryHasBoundingBox;`
- L136 _public member_ `Chaos::TArrayCollectionArray<Chaos::FVec3 > GeometryBoxMin;`
- L137 _public member_ `Chaos::TArrayCollectionArray<Chaos::FVec3 > GeometryBoxMax;`
- L138 _public member_ `Chaos::TArrayCollectionArray<Chaos::FVec3 > GeometrySphereCenter;`
- L139 _public member_ `Chaos::TArrayCollectionArray<Chaos::FReal > GeometrySphereRadius;`
- L140 _public member_ `Chaos::TArrayCollectionArray<Chaos::TUniformGrid<Chaos::FReal, 3> > GeometryLevelSetGrid;`
- L141 _public member_ `Chaos::TArrayCollectionArray<Chaos::FVec3 > V;`
- L142 _public member_ `Chaos::TArrayCollectionArray<Chaos::FVec3 > W;`
- L143 _public member_ `Chaos::TArrayCollectionArray<Chaos::FVec3 > F;`
- L144 _public member_ `Chaos::TArrayCollectionArray<Chaos::FVec3 > Torque;`
- L145 _public member_ `Chaos::TArrayCollectionArray<Chaos::FMatrix33 > I;`
- L146 _public member_ `Chaos::TArrayCollectionArray<Chaos::FMatrix33 > InvI;`
- L147 _public member_ `Chaos::TArrayCollectionArray<Chaos::FReal > M;`
- L148 _public member_ `Chaos::TArrayCollectionArray<Chaos::FReal > InvM;`
- L149 _public member_ `Chaos::TArrayCollectionArray<int32 > CollisionParticlesSize;`
- L150 _public member_ `Chaos::TArrayCollectionArray<bool > Disabled;`
- L151 _public member_ `Chaos::TArrayCollectionArray<bool > Sleeping;`
- L152 _public member_ `Chaos::TArrayCollectionArray<int32 > Island;`
- L153 _public member_ `Chaos::TArrayCollectionArray<Chaos::FVec3 > P;`
- L154 _public member_ `Chaos::TArrayCollectionArray<Chaos::FRotation3 > Q;`
- L155 _public member_ `Chaos::TArrayCollectionArray<Chaos::FVec3 > PreV;`
- L156 _public member_ `Chaos::TArrayCollectionArray<Chaos::FVec3 > PreW;`
- L157 _public member_ `Chaos::TArrayCollectionArray<TArray<Chaos::TConnectivityEdge<Chaos::FReal>>> ConnectivityEdges;`
- L158 _public member_ `Chaos::TArrayCollectionArray<Chaos::FRigidTransform3 > ChildToParentMap;`
- L161 _public function_ `void SetDataSyncFlag(EGeometryCollectionParticlesData Data) const` — Set this data type to copy at the next sync.
- L164 _public prototype_ `void SetAllDataSyncFlag() const;` — Set all data type to copy at the next sync.
- L167 _public function_ `bool HasSyncedData(EGeometryCollectionParticlesData Data) const` — Return whether the specified type of data has been copied during the last sync.
- L170 _public prototype_ `void Reset(EGeometryCollectionParticlesData Data);` — Deallocate the array containing the specified particle information.
- L173 _public prototype_ `void Copy(EGeometryCollectionParticlesData Data, const Chaos::FPhysicsSolver* Solver, const TManagedArray<FGuid>& RigidBodyIds);` — Copy the specified particle information for the specified range of rigid body id.
- L176 _public prototype_ `FString ToString(int32 Index, const TCHAR* Separator) const;` — Return a string with the entire set of value for the synced data of the specified particle.

#### Free symbols / members of external scopes

- L9 _macro_ `#define GEOMETRYCOLLECTION_DEBUG_DRAW UE_ENABLE_DEBUG_DRAWING`
- L188 _typedef_ `template<class T, int d> using TGeometryCollectionParticlesData UE_DEPRECATED(4.27, "Deprecated. this class is to be delete`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionRenderLevelSetActor.h` (Public)


#### class `AGeometryCollectionRenderLevelSetActor`  
`class AGeometryCollectionRenderLevelSetActor : public AActor`  
_L28-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- desc: AGeometryCollectionRenderLevelSetActor An actor representing the collection of data necessary to render volumes.  This references a ray marching material, which is used internally by a post process component blendable.  This is a workflow that can be improved with a deeper implementation in the future if we decide to.  Note that behavior with multiple render level set actors isn't currently supported very well, but could be improved in the future
- L33 _public member_ `static int InstanceCount;`
- L37 _public member_ `TObjectPtr<UVolumeTexture> TargetVolumeTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volume")` — Volume texture to fill
- L42 _public member_ `TObjectPtr<UMaterial> RayMarchMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Material that performs ray marching.  Note this must have certain parameters in order to work correctly
- L47 _public member_ `float SurfaceTolerance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Surface tolerance used for rendering.  When surface reconstruction is noisy, try tweaking this value
- L53 _public member_ `float Isovalue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Isovalue of the level set to use for surface reconstruction.  Generally you want this to be zero, but it can be useful for exploring the distance values to make this negative to see the interior structure of the levelset
- L57 _public member_ `bool Enabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Enable or disable rendering
- L61 _public member_ `bool RenderVolumeBoundingBox;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Enable or disable rendering
- L64 _public prototype_ `static AGeometryCollectionRenderLevelSetActor* FindOrCreate(UWorld* World);` — Find/create the level set renderer singleton actor as required. Return whether the found or created actor.
- L67 _public prototype_ `bool SetLevelSetToRender(const Chaos::FLevelSet &LevelSet, const FTransform &LocalToWorld);` — Load a new level set to render
- L70 _public prototype_ `void SyncLevelSetTransform(const FTransform &LocalToWorld);` — Sync level set transform to the render material
- L73 _public prototype_ `virtual void BeginPlay() override;` — Some initialization happens in here
- L77 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;` — Allowed for live updates to parameters from inside the editor when ejected
- L81 _public function_ `void SetEnabled(bool enabled)` — set and sync enabled
- L88 _private member_ `FVector MinBBoxCorner;`
- L89 _private member_ `FVector MaxBBoxCorner;`
- L91 _private member_ `FMatrix WorldToLocal;`
- L93 _private member_ `float VoxelSize;`
- L95 _private member_ `UPostProcessComponent *PostProcessComponent;`
- L98 _private member_ `UMaterialInstanceDynamic* DynRayMarchMaterial;` — Dynamic material instance so we can update parameters based on volume changes
- L101 _private prototype_ `void SyncMaterialParameters();` — Synchronizes the state of this actor class with the post process render material
- L107 _private member_ `float StepSizeMult;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Private for now since step size mult might not be super useful due to the current rendering algorithms employed in the shaders @todo: expose this in a meaningful way in the future if necessary

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionRootProxyRenderer.h` (Public)


#### class `UGeometryCollectionRootProxyRenderer`  
`class UGeometryCollectionRootProxyRenderer : public UObject, public IGeometryCollectionExternalRenderInterface`  
_L13-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGeometryCollectionExternalRenderInterface`
- desc: Implementation of a geometry collection custom renderer that creates static mesh components representing the root proxies.
- L19 _private member_ `TArray<TObjectPtr<UStaticMeshComponent>> StaticMeshComponents;` — `UPROPERTY()` — Static mesh components for the root proxy meshes.
- L23 _public prototype_ `virtual void OnRegisterGeometryCollection(UGeometryCollectionComponent& InComponent) override;`
- L24 _public prototype_ `virtual void OnUnregisterGeometryCollection() override;`
- L25 _public prototype_ `virtual void UpdateState(UGeometryCollection const& InGeometryCollection, FTransform const& InComponentTransform, uint32 InStateFlags) override;`
- L26 _public prototype_ `virtual void UpdateRootTransform(UGeometryCollection const& InGeometryCollection, FTransform const& InRootTransform) override;`
- L27 _public prototype_ `virtual void UpdateRootTransforms(UGeometryCollection const& InGeometryCollection, FTransform const& InRootTransform, TArrayView<const FTransform3f> InRootLocalTransforms) override;`
- L28 _public prototype_ `virtual void UpdateTransforms(UGeometryCollection const& InGeometryCollection, TArrayView<const FTransform3f> InTransforms) override;`
- L29 _public function_ `virtual bool ShouldUseNativeFallback(uint32 InStateFlags) const override`
- L30 _public function_ `virtual bool CanEverUseNativeFallback() const override`
- L35 _protected member_ `bool bIsVisible = true;` — Current visibility state.
- L38 _private prototype_ `void CreateRootProxyComponents(UGeometryCollectionComponent& InComponent);`
- L39 _private prototype_ `void UpdateRootProxyTransforms(UGeometryCollection const& InGeometryCollection, FTransform const& InRootTransform, TArrayView<const FTransform3f> InLocalRootTransforms);`
- L40 _private prototype_ `void ClearRootProxyComponents();`

### `Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/PhysicsAssetSimulation.h` (Public)


#### struct `FPhysicsAssetSimulationUtil`  
`struct FPhysicsAssetSimulationUtil`  
_L17-21_
- L19 _public prototype_ `static void BuildParams(const UObject* Caller, const AActor* OwningActor, const USkeletalMeshComponent* SkelMeshComponent, const UPhysicsAsset* PhysicsAsset, FSkeletalMeshPhysicsProxyParams& OutParams);`
- L20 _public prototype_ `static bool UpdateAnimState(const UObject* Caller, const AActor* OwningActor, const USkeletalMeshComponent* SkelMeshComponent, const float Dt, FSkeletalMeshPhysicsProxyParams& OutParams);`
