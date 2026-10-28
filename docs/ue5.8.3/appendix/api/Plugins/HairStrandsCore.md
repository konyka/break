# Plugins / HairStrandsCore

- module root: `Plugins/Runtime/HairStrands/Source/HairStrandsCore`
- headers: 55; symbols: 3591
- symbol kinds: class=41, delegate=9, enum=58, enumerator=229, externvar=28, function=347, macro=31, member=1385, namespace=17, prototype=1135, struct=240, typedef=64, union=1, variable=6
- PrivateDependencyModuleNames: Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEngine, DerivedDataCache, Eigen, Engine, GeometryCache, GeometryCore, MeshBuilder, MeshDescription, MovieScene, NaniteBuilder, NiagaraCore, NiagaraShader, Projects, RHI, RenderCore, Renderer, StaticMeshDescription, TraceLog, VectorVM
- PrivateIncludePathModuleNames: DerivedDataCache, Shaders
- PublicDependencyModuleNames: ChaosCaching, Niagara

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomBindingCommon.h` (Private)


#### struct `FHairRootGroupData`  
`struct FHairRootGroupData`  
_L11-23_
- desc: Binding data
- L13 _public member_ `TArray<FHairStrandsRootData> SimRootDatas;`
- L14 _public member_ `TArray<FHairStrandsRootData> RenRootDatas;`
- L15 _public member_ `TArray<TArray<FHairStrandsRootData>>CardsRootDatas;`
- L18 _public member_ `TArray<TArray<FVector3f>> MeshPositions;` — (Skel.) Mesh Positions for each LODs
- L19 _public member_ `TArray<TArray<FVector3f>> MeshPositions_Transferred;`
- L22 _public member_ `int32 TargetMeshMinLOD = INDEX_NONE;` — The index of the best LOD on the target mesh that is supported by this data

#### Free symbols / members of external scopes

- L24 _prototype_ `bool BuildHairRootGroupData(const FGroomBindingBuilder::FInput& In, uint32 InGroupIndex, const ITargetPlatform* TargetPlatform, FHairRootGroupData& OutData);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomCacheStreamingData.h` (Private)


#### struct `FResidentGroomCacheChunk`  
`struct FResidentGroomCacheChunk`  
_L16-22_
- desc: Info about a chunk, loaded or not
- L18 _public member_ `FGroomCacheAnimationData* AnimDataPtr = nullptr;`
- L19 _public member_ `IBulkDataIORequest* IORequest = nullptr;` — null when resident, non-null when in flight
- L20 _public member_ `int32 Refcount = 0;`
- L21 _public member_ `int32 DataSize = 0;`

#### struct `FCompletedGroomCacheChunk`  
`struct FCompletedGroomCacheChunk`  
_L25-35_
- desc: Info about read request status of a chunk
- L27 _public member_ `FGroomCacheAnimationData* AnimDataPtr = nullptr;`
- L28 _public member_ `IBulkDataIORequest* ReadRequest;`
- L29 _public member_ `int32 LoadedChunkIndex;`
- L30 _public member_ `bool bReadSuccessful;`
- L32 _public function_ `FCompletedGroomCacheChunk() : AnimDataPtr(nullptr), ReadRequest(nullptr), LoadedChunkIndex(0), bReadSuccessful(false)`
- L33 _public function_ `FCompletedGroomCacheChunk(int32 SetLoadedChunkIndex, FGroomCacheAnimationData* AnimBuffer, IBulkDataIORequest* SetReadRequest) : AnimDataPtr(AnimBuffer), ReadRequest(SetReadRequest), LoadedChunkIndex(SetLoadedChunkIndex), bReadSuccessful(false)`

#### class `FGroomCacheStreamingData`  
`class FGroomCacheStreamingData`  
_L38-104_
- desc: Class that manages the streaming and cached data for a GroomCache
- L41 _public prototype_ `FGroomCacheStreamingData(UGroomCache* GroomCache);`
- L42 _public prototype_ `~FGroomCacheStreamingData();`
- L45 _public prototype_ `void UpdateStreamingStatus(bool bAsyncDeletionAllowed);` — Updates the internal state of the streaming data.
- L48 _public prototype_ `const FGroomCacheAnimationData* MapAnimationData(uint32 ChunkIndex);` — Returns a pointer to the cache data for ChunkIndex if it's loaded; nullptr otherwise.
- L51 _public prototype_ `void UnmapAnimationData(uint32 ChunkIndex);` — Informs the streaming data that the ChunkIndex data is not used anymore.
- L54 _public prototype_ `bool IsStreamingInProgress();` — Returns true if there are read requests in flight; false otherwise.
- L57 _public prototype_ `bool BlockTillAllRequestsFinished(float TimeLimit = 0.0f);` — Blocks until all read requests are completed. Returns true if they were all completed before TimeLimit (0 means no limit); false otherwise.
- L60 _public prototype_ `void PrefetchData(UGroomComponent* Component);` — Synchronously loads the initial frames needed to display the given component
- L63 _public prototype_ `void ResetNeededChunks();` — Resets the list of chunks needed by users of this GroomCache
- L66 _public prototype_ `void AddNeededChunk(uint32 ChunkIndex);` — Adds ChunkIndex to the list of chunks needed to be loaded
- L68 _public function_ `UGroomCache* GetGroomCache() const`
- L72 _private prototype_ `FResidentGroomCacheChunk& AddResidentChunk(int32 ChunkId, const struct FGroomCacheChunk& ChunkInfo);`
- L73 _private prototype_ `void RemoveResidentChunk(FResidentGroomCacheChunk& LoadedChunk);`
- L74 _private prototype_ `void ProcessCompletedChunks();`
- L77 _private member_ `UGroomCache* GroomCache;` — The GroomCache being streamed
- L80 _private member_ `TArray<int32> ChunksNeeded;` — List of chunks that need to be loaded
- L83 _private member_ `TSet<int32> ChunksAvailable;` — List of chunks currently resident in memory
- L86 _private member_ `TSet<int32> ChunksRequested;` — List of chunks being streamed, ie. their read requests are in-flight
- L89 _private member_ `TSet<int32> ChunksEvicted;` — List of chunks to be evicted, not needed anymore so they can be unloaded
- L92 _private member_ `TMap<int32, FResidentGroomCacheChunk> Chunks;` — ChunkIndex to chunk info
- L95 _private member_ `TQueue<FCompletedGroomCacheChunk, EQueueMode::Mpsc> CompletedChunks;` — List of read requests that are completed that need to be processed for bookkeeping (to be marked as available)
- L98 _private member_ `TSet<IBulkDataIORequest*> DelayedDeleteReadRequests;` — List of read requests to be deleted after completion
- L101 _private member_ `uint64 LastUpdate = 0;` — Timestamp of the last update
- L103 _private member_ `FCriticalSection CriticalSection;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGroomCacheStreaming, Verbose, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGroomCacheStreaming, Verbose, All);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomGeometryCache.h` (Private)


#### Free symbols / members of external scopes

- L14 _prototype_ `void BuildCacheGeometry( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const FGeometryCacheSceneProxy* Proxy, const bool bOutputTriangleData, FCachedGeometry& OutCachedGeometry);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.h` (Private)


#### enum `EHairStrandsProjectionMeshType`  
`enum class EHairStrandsProjectionMeshType`  
_L33-39_
- L35 _public enumerator_ `RestMesh`
- L36 _public enumerator_ `DeformedMesh`
- L37 _public enumerator_ `SourceMesh`
- L38 _public enumerator_ `TargetMesh`

#### enum `EHairBufferSwapType`  
`enum EHairBufferSwapType`  
_L41-47_
- L43 _public enumerator_ `BeginOfFrame`
- L44 _public enumerator_ `EndOfFrame`
- L45 _public enumerator_ `Tick`
- L46 _public enumerator_ `RenderFrame`

#### Free symbols / members of external scopes

- L49 _prototype_ `EHairBufferSwapType GetHairSwapBufferType();`
- L54 _prototype_ `void RegisterHairStrands(struct FHairGroupInstance* Instance);`
- L55 _prototype_ `void UnregisterHairStrands(uint32 ComponentId);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsClusterCulling.h` (Private)


#### struct `FHairStrandClusterData`  
`struct FHairStrandClusterData`  
_L14-47_
- L46 _public member_ `TArray<FHairGroup> HairGroups;`

#### struct `FHairStrandClusterData::FHairGroup`  
`struct FHairGroup`  
_L16-44_
- L18 _public member_ `uint32 InstanceRegisteredIndex = ~0;`
- L19 _public member_ `float ClusterScale = 0;`
- L20 _public member_ `uint32 MaxPointPerCurve = 0;`
- L21 _public member_ `FVector4f ClusterInfoParameters = FVector4f::Zero();`
- L22 _public member_ `float LODIndex = -1;`
- L23 _public member_ `float LODBias = 0.0f;`
- L24 _public member_ `bool bVisible = false;`
- L26 _public member_ `FRDGExternalBuffer* CurveBuffer = nullptr;`
- L27 _public member_ `FRDGExternalBuffer* PointLODBuffer = nullptr;`
- L30 _public member_ `FRDGExternalBuffer* ClusterInfoBuffer = nullptr;` — See FHairStrandsClusterResource fro details about those buffers.
- L31 _public member_ `FRDGExternalBuffer* CurveToClusterIdBuffer = nullptr;` — SRV
- L33 _public member_ `TRefCountPtr<FRDGPooledBuffer> ClusterIdBuffer;`
- L34 _public member_ `TRefCountPtr<FRDGPooledBuffer> ClusterIndexOffsetBuffer;`
- L35 _public member_ `TRefCountPtr<FRDGPooledBuffer> ClusterIndexCountBuffer;`
- L38 _public function_ `FRDGExternalBuffer* GetCulledCurveBuffer() const` — Culling & LOD output
- L39 _public function_ `FRDGExternalBuffer* GetCulledVertexIdBuffer() const`
- L40 _public function_ `bool GetCullingResultAvailable() const`
- L41 _public function_ `void SetCullingResultAvailable(bool b)`
- L43 _public member_ `FHairGroupPublicData* HairGroupPublicPtr = nullptr;`

#### Free symbols / members of external scopes

- L49 _prototype_ `void AddInstanceToClusterData( FHairGroupInstance* In, FHairStrandClusterData& Out);`
- L53 _prototype_ `void AddClusterCullingPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const FSceneView* View, const FShaderPrintData* ShaderPrintData, FHairStrandClusterData& ClusterDatas, FRDGBufferUAVRef IndirectDispatchArgsGlobalUAV);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/MovieSceneGroomCacheTemplate.h` (Private)


#### struct `FMovieSceneGroomCacheSectionTemplateParameters`  
`struct FMovieSceneGroomCacheSectionTemplateParameters : public FMovieSceneGroomCacheParams`  
_L10-29_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneGroomCacheParams`
- L14 _public function_ `FMovieSceneGroomCacheSectionTemplateParameters()`
- L16 _public function_ `FMovieSceneGroomCacheSectionTemplateParameters(const FMovieSceneGroomCacheParams& BaseParams, FFrameNumber InSectionStartTime, FFrameNumber InSectionEndTime) : FMovieSceneGroomCacheParams(BaseParams) , SectionStartTime(InSectionStartTime) , SectionEndTime(InSectionEndTime)`
- L22 _public prototype_ `float MapTimeToAnimation(float ComponentDuration, FFrameTime InPosition, FFrameRate InTickResolution) const;`
- L25 _public member_ `FFrameNumber SectionStartTime;` — `UPROPERTY()`
- L28 _public member_ `FFrameNumber SectionEndTime;` — `UPROPERTY()`

#### struct `FMovieSceneGroomCacheSectionTemplate`  
`struct FMovieSceneGroomCacheSectionTemplate : public FMovieSceneEvalTemplate`  
_L32-44_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- L36 _public function_ `FMovieSceneGroomCacheSectionTemplate()`
- L37 _public prototype_ `FMovieSceneGroomCacheSectionTemplate(const UMovieSceneGroomCacheSection& Section);`
- L39 _public function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L40 _public prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L43 _public member_ `FMovieSceneGroomCacheSectionTemplateParameters Params;` — `UPROPERTY()`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/NaniteGroomAsset.h` (Private)


#### class `FGroomAssetRenderData`  
`class FGroomAssetRenderData`  
_L18-57_
- L22 _public function_ `FGroomAssetRenderData()` — Default constructor.
- L23 _public function_ `~FGroomAssetRenderData()`
- L25 _public prototype_ `void InitResources(ERHIFeatureLevel::Type InFeatureLevel, UGroomAsset* Owner);`
- L26 _public prototype_ `void ReleaseResources();`
- L28 _public prototype_ `bool HasValidNaniteData() const;`
- L31 _public prototype_ `void Cache(const ITargetPlatform* TargetPlatform, const UGroomAsset* InGroomAsset);` — Build and cache render data
- L34 _public prototype_ `void BuildMaterials(const UGroomAsset* InGroomAsset, bool bSetMaterialUsage = true);` — Gather Nanite materials
- L36 _public prototype_ `bool IsValid() const;`
- L38 _public prototype_ `void Serialize(FArchive& Ar, UObject* Owner, bool bCooked);`
- L39 _public prototype_ `void InitNaniteResources();`
- L42 _public prototype_ `Nanite::FResources* GetResources();` — Accessors
- L43 _public prototype_ `const Nanite::FMaterialAudit* GetMaterialAudit() const;`
- L46 _private member_ `TPimplPtr<Nanite::FResources> NaniteResourcesPtr;`
- L47 _private member_ `TUniquePtr<Nanite::FMaterialAudit> NaniteMaterials;`
- L51 _private member_ `FString DerivedDataKey;` — The derived data key associated with this render data.
- L52 _private member_ `uint32 NumCacheAttempts = 0;`
- L56 _private member_ `bool bIsInitialized = false;`

#### class `Nanite::FGroomSceneProxy`  
`class FGroomSceneProxy: public FSceneProxyBase`  
_L66-114_
- inherits: `FSceneProxyBase`
- L69 _public typedef_ `using Super = FSceneProxyBase;`
- L71 _public prototype_ `FGroomSceneProxy( const FMaterialAudit& MaterialAudit, const UGroomComponent* InComponent, const UGroomAsset* InAsset, FGroomAssetRenderData* InRenderData, bool bAllowScaling = true);`
- L78 _public prototype_ `virtual ~FGroomSceneProxy();`
- L82 _public prototype_ `virtual void CreateRenderThreadResources(FRHICommandListBase& RHICmdList) override;` — FPrimitiveSceneProxy interface.
- L83 _public prototype_ `virtual void DestroyRenderThreadResources() override;`
- L84 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L85 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L87 _public prototype_ `virtual HHitProxy* CreateHitProxies(UPrimitiveComponent* Component, TArray<TRefCountPtr<HHitProxy> >& OutHitProxies) override;`
- L89 _public prototype_ `virtual void DrawStaticElements(FStaticPrimitiveDrawInterface* PDI) override;`
- L90 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L92 _public prototype_ `virtual void GetPreSkinnedLocalBounds(FBoxSphereBounds& OutBounds) const override;`
- L94 _public function_ `virtual bool CanApplyStreamableRenderAssetScaleFactor() const override`
- L96 _public prototype_ `virtual uint32 GetMemoryFootprint() const override;`
- L98 _public prototype_ `virtual FResourceMeshInfo GetResourceMeshInfo() const override;`
- L99 _public prototype_ `virtual FResourcePrimitiveInfo GetResourcePrimitiveInfo() const override;`
- L101 _public prototype_ `virtual FDesiredLODLevel GetDesiredLODLevel_RenderThread(const FSceneView* View) const final override;`
- L103 _public prototype_ `virtual uint8 GetCurrentFirstLODIdx_RenderThread() const final override;`
- L107 _protected member_ `const FResources* Resources = nullptr;`
- L108 _protected member_ `const UGroomAsset* GroomAsset = nullptr;`
- L110 _protected member_ `FBoxSphereBounds PreSkinnedLocalBounds;`
- L112 _protected member_ `uint32 NaniteResourceID = INDEX_NONE;`
- L113 _protected member_ `uint32 NaniteHierarchyOffset = INDEX_NONE;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L63 _namespace_ `namespace Nanite`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/NaniteGroomBuilder.h` (Private)


#### class `FGroomAssetNaniteBuilder`  
`class FGroomAssetNaniteBuilder`  
_L17-23_
- L20 _public prototype_ `FGroomAssetNaniteBuilder() = default;`
- L21 _public prototype_ `bool Build(TPimplPtr<Nanite::FResources>& OutNaniteResourcesPtr, const UGroomAsset* InGroomAsset);`
- L22 _public prototype_ `~FGroomAssetNaniteBuilder() = default;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomActor.h` (Public)


#### class `AGroomActor`  
`class AGroomActor : public AActor`  
_L16-40_
- reflection: `UCLASS(MinimalAPI, HideCategories = (Input, Replication, Mobility), showcategories = ("Input|MouseInput", "Input|TouchInput"))`
- inherits: `AActor`
- desc: An actor that renders a simulated hair
- L22 _private member_ `TObjectPtr<class UGroomComponent> GroomComponent;` — `UPROPERTY(Category = StrandHair, VisibleAnywhere, BlueprintReadOnly)` — Strand hair component that performs simulation and rendering
- L26 _private prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L34 _protected member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY()` — Billboard used to see the scene in the editor
- L39 _public function_ `class UGroomComponent* GetGroomComponent() const` — Returns GroomComponent subobject

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomAsset.h` (Public)


#### enum `EHairGroupInfoFlags`  
`enum class EHairGroupInfoFlags : uint8`  
_L42-47_
- L44 _public enumerator_ `HasTrimmedPoint = 1<<0`
- L45 _public enumerator_ `HasTrimmedCurve = 1<<1`
- L46 _public enumerator_ `HasInvalidPoint = 1<<2`

#### struct `FHairGroupLODInfo`  
`struct FHairGroupLODInfo`  
_L50-59_
- reflection: `USTRUCT(BlueprintType)`
- L55 _public member_ `int32 NumPoints = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Point Count"))`
- L58 _public member_ `int32 NumCurves = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Curve Count"))`

#### struct `FHairGroupInfo`  
`struct FHairGroupInfo`  
_L62-95_
- reflection: `USTRUCT(BlueprintType)`
- L67 _public member_ `int32 GroupIndex = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info")`
- L70 _public member_ `int32 GroupID = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info")`
- L73 _public member_ `FName GroupName = NAME_None;` — `UPROPERTY(VisibleAnywhere, Category = "Info")`
- L76 _public member_ `int32 NumCurves = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Curve Count"))`
- L79 _public member_ `int32 NumGuides = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Guide Count"))`
- L82 _public member_ `int32 NumCurveVertices = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Curve Vertex Count"))`
- L85 _public member_ `int32 NumGuideVertices = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Guide Vertex Count"))`
- L88 _public member_ `float MaxCurveLength = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Length of the longest hair strands"))`
- L91 _public member_ `uint32 Flags = 0;` — `UPROPERTY()`
- L94 _public member_ `TArray<FHairGroupLODInfo> LODInfos;` — `UPROPERTY()`

#### struct `FHairGroupsMaterial`  
`struct FHairGroupsMaterial`  
_L98-107_
- reflection: `USTRUCT(BlueprintType)`
- L103 _public member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Material")`
- L106 _public member_ `FName SlotName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Material")`

#### struct `FHairGroupResources`  
`struct FHairGroupResources`  
_L110-240_
- L126 _public member_ `} Guides;`
- L153 _public member_ `} Strands;`
- L197 _public member_ `} Cards;`
- L234 _public member_ `} Meshes;`
- L239 _public member_ `} Debug;`

#### struct `FHairGroupResources::FGuides`  
`struct FGuides`  
_L112-126_
- L114 _public function_ `bool IsValid() const`
- L117 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L124 _public member_ `FHairStrandsRestResource* RestResource = nullptr;`

#### struct `FHairGroupResources::FStrands`  
`struct FStrands`  
_L128-153_
- L130 _public function_ `bool IsValid() const`
- L133 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L145 _public member_ `FHairStrandsRestResource* RestResource = nullptr;`
- L146 _public member_ `FHairStrandsInterpolationResource* InterpolationResource = nullptr;`
- L147 _public member_ `FHairStrandsClusterResource* ClusterResource = nullptr;`
- L149 _public member_ `FHairStrandsRaytracingResource* RaytracingResource = nullptr;`
- L152 _public member_ `bool bIsCookedOut = false;`

#### struct `FHairGroupResources::FCards`  
`struct FCards`  
_L155-197_
- L158 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L196 _public member_ `TArray<FLOD> LODs;`

#### struct `FHairGroupResources::FCards::FLOD`  
`struct FLOD`  
_L168-195_
- L171 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L184 _public function_ `bool IsValid() const`
- L186 _public member_ `FHairCardsRestResource* RestResource = nullptr;`
- L187 _public member_ `FHairCardsInterpolationResource* InterpolationResource = nullptr;`
- L188 _public member_ `FHairStrandsRestResource* GuideRestResource = nullptr;`
- L189 _public member_ `FHairStrandsInterpolationResource* GuideInterpolationResource = nullptr;`
- L191 _public member_ `FHairStrandsRaytracingResource* RaytracingResource = nullptr;`
- L194 _public member_ `bool bIsCookedOut = false;`

#### struct `FHairGroupResources::FMeshes`  
`struct FMeshes`  
_L199-234_
- L202 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L233 _public member_ `TArray<FLOD> LODs;`

#### struct `FHairGroupResources::FMeshes::FLOD`  
`struct FLOD`  
_L212-232_
- L215 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L225 _public function_ `bool IsValid() const`
- L227 _public member_ `FHairMeshesRestResource* RestResource = nullptr;`
- L229 _public member_ `FHairStrandsRaytracingResource* RaytracingResource = nullptr;`
- L231 _public member_ `bool bIsCookedOut = false;`

#### struct `FHairGroupResources::FDebug`  
`struct FDebug`  
_L236-239_
- L238 _public member_ `FHairStrandsDebugResources* Resource = nullptr;`

#### struct `FHairGroupPlatformData`  
`struct FHairGroupPlatformData`  
_L263-410_
- L271 _public member_ `} Guides;`
- L287 _public member_ `} Strands;`
- L350 _public member_ `} Cards;`
- L404 _public member_ `} Meshes;`
- L409 _public member_ `} Debug;`

#### struct `FHairGroupPlatformData::FGuides`  
`struct FGuides`  
_L265-271_
- L267 _public function_ `bool HasValidData() const`
- L268 _public function_ `const FBox& GetBounds() const`
- L269 _public function_ `uint32 GetDataSize() const`
- L270 _public member_ `FHairStrandsBulkData BulkData;`

#### struct `FHairGroupPlatformData::FStrands`  
`struct FStrands`  
_L273-287_
- L275 _public function_ `bool HasValidData() const`
- L276 _public function_ `const FBox& GetBounds() const`
- L278 _public prototype_ `uint32 GetDataSize() const;`
- L279 _public member_ `FHairStrandsBulkData BulkData;`
- L280 _public member_ `FHairStrandsInterpolationBulkData InterpolationBulkData;`
- L281 _public member_ `FHairStrandsClusterBulkData ClusterBulkData;`
- L284 _public member_ `FRenderCurveResourceData CurveResourceData;` — Experimental (Optional)
- L286 _public member_ `bool bIsCookedOut = false;`

#### struct `FHairGroupPlatformData::FCards`  
`struct FCards`  
_L289-350_
- L291 _public function_ `bool HasValidData() const`
- L301 _public function_ `bool HasValidData(uint32 LODIt) const`
- L302 _public function_ `bool IsValid(uint32 LODIt) const`
- L303 _public function_ `FBox GetBounds() const`
- L312 _public function_ `uint32 GetDataSize() const`
- L349 _public member_ `TArray<FLOD> LODs;`

#### struct `FHairGroupPlatformData::FCards::FLOD`  
`struct FLOD`  
_L322-348_
- L324 _public function_ `uint32 GetDataSize() const`
- L338 _public function_ `bool HasValidData() const`
- L339 _public function_ `bool IsValid() const`
- L342 _public member_ `FHairCardsBulkData BulkData;` — Main data & Resources
- L343 _public member_ `FHairCardsInterpolationBulkData InterpolationBulkData;`
- L344 _public member_ `FHairStrandsBulkData GuideBulkData;`
- L345 _public member_ `FHairStrandsInterpolationBulkData GuideInterpolationBulkData;`
- L347 _public member_ `bool bIsCookedOut = false;`

#### struct `FHairGroupPlatformData::FMeshes`  
`struct FMeshes`  
_L352-404_
- L354 _public function_ `bool HasValidData() const`
- L363 _public function_ `bool HasValidData(uint32 LODIt) const`
- L364 _public function_ `bool IsValid(uint32 LODIt) const`
- L365 _public function_ `FBox GetBounds() const`
- L374 _public function_ `uint32 GetDataSize() const`
- L403 _public member_ `TArray<FLOD> LODs;`

#### struct `FHairGroupPlatformData::FMeshes::FLOD`  
`struct FLOD`  
_L384-402_
- L386 _public function_ `uint32 GetDataSize() const`
- L397 _public function_ `bool HasValidData() const`
- L398 _public function_ `bool IsValid() const`
- L400 _public member_ `FHairMeshesBulkData BulkData;`
- L401 _public member_ `bool bIsCookedOut = false;`

#### struct `FHairGroupPlatformData::FDebug`  
`struct FDebug`  
_L406-409_
- L408 _public member_ `FHairStrandsDebugDatas Data;`

#### struct `FHairDescriptionGroup`  
`struct FHairDescriptionGroup`  
_L412-419_
- L414 _public member_ `FHairGroupInfo Info;`
- L415 _public member_ `FHairStrandsRawDatas Strands;`
- L416 _public member_ `FHairStrandsRawDatas Guides;`
- L417 _public function_ `uint32 GetHairAttributes() const`
- L418 _public function_ `uint32 GetHairAttributeFlags() const`

#### struct `FHairDescriptionGroups`  
`struct FHairDescriptionGroups`  
_L421-426_
- L423 _public member_ `TArray<FHairDescriptionGroup> HairGroups;`
- L424 _public member_ `FBoxSphereBounds3f Bounds;`
- L425 _public prototype_ `bool IsValid() const;`

#### struct `FHairGroupInfoWithVisibility`  
`struct FHairGroupInfoWithVisibility : public FHairGroupInfo`  
_L429-436_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FHairGroupInfo`
- L435 _public member_ `bool bIsVisible = true;` — `UPROPERTY(EditAnywhere, Category = "Info", meta = (DisplayName = "Visible"))` — Toggle hair group visibility. This visibility flag is not persistent to the asset, and exists only as a preview/helper mechanism

#### enum `EHairAtlasTextureType`  
`enum class EHairAtlasTextureType : uint8`  
_L439-447_
- reflection: `UENUM(BlueprintType)`
- L441 _public enumerator_ `Depth`
- L442 _public enumerator_ `Tangent`
- L443 _public enumerator_ `Attribute`
- L444 _public enumerator_ `Coverage`
- L445 _public enumerator_ `AuxilaryData`
- L446 _public enumerator_ `Material`

#### struct `FHairVertexFactoryTypesPerMaterialData`  
`struct FHairVertexFactoryTypesPerMaterialData`  
_L449-454_
- L451 _public member_ `int16 MaterialIndex;`
- L452 _public member_ `EHairGeometryType HairGeometryType;`
- L453 _public member_ `FPSOPrecacheVertexFactoryDataList VertexFactoryDataList;`

#### enum `EHairDescriptionType`  
`enum class EHairDescriptionType : uint8`  
_L457-462_
- reflection: `UENUM()`
- L459 _public enumerator_ `Source`
- L460 _public enumerator_ `Edit`
- L461 _public enumerator_ `Count`

#### class `UGroomAsset`  
`class UGroomAsset : public UObject, public IInterface_AssetUserData, public IDataflowContentOwner, public IDataflowInstanceInterface`  
_L468-985_
- reflection: `UCLASS(BlueprintType, AutoExpandCategories = ("HairRendering", "HairPhysics", "HairInterpolation", "HairDataflow"), hidecategories = (Object, "Hidden"), MinimalAPI)`
- inherits: `UObject,IInterface_AssetUserData,IDataflowContentOwner,IDataflowInstanceInterface`
- desc: Implements an asset that can be used to store hair strands
- L474 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGroomAssetChanged);` — Notification when anything changed
- L475 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGroomAssetResourcesChanged);`
- L476 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGroomAsyncLoadFinished);`
- L477 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateGroomDataflow, UGroomAsset*);`
- L482 _private member_ `EGroomLODMode LODMode = EGroomLODMode::Default;` — `UPROPERTY(EditAnywhere, Category = "HairLOD", meta = (DisplayName = "LOD Mode", ToolTip = "Define how LOD adapts curves & points for strands geometry. Auto: adapts the curve count based on screen coverage. Manual: use the discrete LOD created for each groups"))`
- L485 _private member_ `float AutoLODBias = 0;` — `UPROPERTY(EditAnywhere, Category = "HairLOD", meta = (DisplayName = "Global Auto LOD Bias", ToolTip = "When LOD mode is set to Auto, decrease the screen size at which curves reduction will occur.", ClampMin = "-1", ClampMax = "1", UIMin = "-1.0", UIMax = "1.0"))`
- L489 _private member_ `FGroomDataflowSettings DataflowSettings;` — `UPROPERTY(EditAnywhere, Category = "HairDataflow")` — Dataflow settings used for any dataflow related operations
- L493 _public function_ `static FName GetDataflowBuilderCategoryName()` — Return the builder category name for layout
- L497 _public function_ `void CreateGroomDataflow()` — `UFUNCTION(CallInEditor, BlueprintCallable, Category = "HairDataflow")` — Create the dataflow from the groom asset
- L506 _public member_ `TArray<FHairGroupInfoWithVisibility> HairGroupsInfo;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, EditFixedSize, EditFixedSize, Category = "HairInfo", meta = (DisplayName = "Group", TitleProperty = "{GroupName}"))`
- L510 _public member_ `TArray<FHairGroupsRendering> HairGroupsRendering;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintGetter = GetHairGroupsRendering, BlueprintSetter = SetHairGroupsRendering, Category = "HairRendering", meta = (DisplayName = "Group", TitleProperty = "{GroupName}"))`
- L514 _public member_ `TArray<FHairGroupsPhysics> HairGroupsPhysics;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintGetter = GetHairGroupsPhysics, BlueprintSetter = SetHairGroupsPhysics, Category = "HairPhysics", meta = (DisplayName = "Group", TitleProperty = "{GroupName}"))`
- L518 _public member_ `TArray<FHairGroupsInterpolation> HairGroupsInterpolation;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintGetter = GetHairGroupsInterpolation, BlueprintSetter = SetHairGroupsInterpolation, Category = "HairInterpolation", meta = (DisplayName = "Group", TitleProperty = "{GroupName}"))`
- L522 _public member_ `TArray<FHairGroupsLOD> HairGroupsLOD;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintGetter = GetHairGroupsLOD, BlueprintSetter = SetHairGroupsLOD, Category = "HairLOD", meta = (DisplayName = "Group"))`
- L527 _public member_ `TArray<FHairGroupsCardsSourceDescription> HairGroupsCards;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetHairGroupsCards, BlueprintSetter = SetHairGroupsCards, Category = "HairCards", meta = (DisplayName = "Group"))` — Cards - Source description data
- L532 _public member_ `TArray<FHairGroupsMeshesSourceDescription> HairGroupsMeshes;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetHairGroupsMeshes, BlueprintSetter = SetHairGroupsMeshes, Category = "HairMeshes", meta = (DisplayName = "Group"))` — Meshes - Source description data
- L537 _public member_ `TArray<FHairGroupsMaterial> HairGroupsMaterials;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetHairGroupsMaterials, BlueprintSetter = SetHairGroupsMaterials, Category = "HairMaterials", meta = (DisplayName = "Group"))` — Meshes - Source description data
- L542 _public member_ `bool EnableGlobalInterpolation = false;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintGetter = GetEnableGlobalInterpolation, BlueprintSetter = SetEnableGlobalInterpolation, Category = "HairInterpolation", meta = (ToolTip = "Enable radial basis function interpolation to be used instead of the local skin rigid transform (WIP)", DisplayName = "RBF Interpolation"))` — Enable radial basis function interpolation to be used instead of the local skin rigid transform
- L547 _public member_ `bool EnableSimulationCache = false;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintGetter = GetEnableSimulationCache, BlueprintSetter = SetEnableSimulationCache, Category = "HairInterpolation", meta = (ToolTip = "Enable guide-cache support. This allows to attach a simulation-cache dynamically at runtime", DisplayName = "Enable Guide-Cache Support"))` — Enable guide-cache support. This allows to attach a guide-cache dynamically at runtime
- L552 _public member_ `EGroomInterpolationType HairInterpolationType = EGroomInterpolationType::SmoothTransform;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintGetter = GetHairInterpolationType, BlueprintSetter = SetHairInterpolationType, Category = "HairInterpolation", meta = (ToolTip = "Type of interpolation used (WIP)"))` — Type of interpolation used
- L557 _public member_ `TObjectPtr<USkeletalMesh> RiggedSkeletalMesh;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(VisibleAnywhere, BlueprintGetter = GetRiggedSkeletalMesh, BlueprintSetter = SetRiggedSkeletalMesh, Category = "HairInterpolation")` — Deformed skeletal mesh that will drive the groom deformation/simulation. For creating this skeletal mesh, enable EnableDeformation within the interpolation settings
- L562 _public member_ `TArray<int32> DeformedGroupSections;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY()` — Deformed skeletal mesh mapping from groups to sections
- L567 _public member_ `FPerPlatformInt MinLOD;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, Category = "HairLOD", meta = (DisplayName = "Minimum LOD"))` — Minimum LOD to cook
- L572 _public member_ `FPerPlatformBool DisableBelowMinLodStripping;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "HairLOD")` — When true all LODs below MinLod will still be cooked
- L577 _public member_ `TArray<float> EffectiveLODBias;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — `UPROPERTY()` — The LOD bias to use after LOD stripping, regardless of MinLOD. Computed at cook time
- L581 _public member_ `TArray<FHairGroupPlatformData> HairGroupsPlatformData;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomAsset accessor.")` — Store strands/cards/meshes data
- L584 _public prototype_ `bool UsesNanite() const;`
- L585 _public prototype_ `FGroomAssetRenderData* GetRenderData();`
- L586 _public prototype_ `const FGroomAssetRenderData* GetRenderData() const;`
- L588 _public prototype_ `bool HasValidNaniteData() const;`
- L589 _public prototype_ `bool HasNaniteFallbackMesh(EShaderPlatform ShaderPlatform) const;`
- L591 _public prototype_ `virtual void ClearAllCachedCookedPlatformData() override;`
- L593 _public prototype_ `UMaterialInterface* GetNaniteAuditMaterial(int32 MaterialIndex) const;`
- L594 _public prototype_ `const Nanite::FMaterialAudit* GetNaniteMaterials() const;`
- L597 _private prototype_ `void SetRenderData(TUniquePtr<class FGroomAssetRenderData>&& InRenderData);`
- L598 _private member_ `TUniquePtr<class FGroomAssetRenderData> RenderData;`
- L602 _private member_ `TArray<FHairGroupResources> HairGroupsResources;` — Store strands/cards/meshes resources
- L607 _public prototype_ `static FName GetDataflowSettingsMemberName();` — Static member to retrieve the member name
- L610 _public function_ `const FGroomDataflowSettings& GetDataflowSettings() const` — Return the Dataflow settings associated to this groom asset if any, const version.
- L613 _public function_ `FGroomDataflowSettings& GetDataflowSettings()` — Return the Dataflow settings associated to this groom asset if any.
- L616 _public function_ `void SetDataflowSettings(const FGroomDataflowSettings& InDataflowSettings)` — Set the Dataflow settings associated to this groom asset if any
- L618 _public prototype_ `static FName GetHairGroupsRenderingMemberName();`
- L619 _public prototype_ `UFUNCTION(BlueprintGetter) TArray<FHairGroupsRendering>& GetHairGroupsRendering();`
- L620 _public prototype_ `UFUNCTION(BlueprintSetter) void SetHairGroupsRendering(const TArray<FHairGroupsRendering>& In);` — `UFUNCTION(BlueprintGetter)`
- L621 _public prototype_ `const TArray<FHairGroupsRendering>& GetHairGroupsRendering() const;` — `UFUNCTION(BlueprintGetter)` — `UFUNCTION(BlueprintSetter)`
- L623 _public prototype_ `static FName GetHairGroupsPhysicsMemberName();`
- L624 _public prototype_ `UFUNCTION(BlueprintGetter) TArray<FHairGroupsPhysics>& GetHairGroupsPhysics();`
- L625 _public prototype_ `UFUNCTION(BlueprintSetter) void SetHairGroupsPhysics(const TArray<FHairGroupsPhysics>& In);` — `UFUNCTION(BlueprintGetter)`
- L626 _public prototype_ `const TArray<FHairGroupsPhysics>& GetHairGroupsPhysics() const;` — `UFUNCTION(BlueprintGetter)` — `UFUNCTION(BlueprintSetter)`
- L628 _public prototype_ `static FName GetHairGroupsInterpolationMemberName();`
- L629 _public prototype_ `UFUNCTION(BlueprintGetter) TArray<FHairGroupsInterpolation>& GetHairGroupsInterpolation();`
- L630 _public prototype_ `UFUNCTION(BlueprintSetter) void SetHairGroupsInterpolation(const TArray<FHairGroupsInterpolation>& In);` — `UFUNCTION(BlueprintGetter)`
- L631 _public prototype_ `const TArray<FHairGroupsInterpolation>& GetHairGroupsInterpolation() const;` — `UFUNCTION(BlueprintGetter)` — `UFUNCTION(BlueprintSetter)`
- L633 _public prototype_ `static FName GetHairGroupsLODMemberName();`
- L634 _public prototype_ `UFUNCTION(BlueprintGetter) TArray<FHairGroupsLOD>& GetHairGroupsLOD();`
- L635 _public prototype_ `UFUNCTION(BlueprintSetter) void SetHairGroupsLOD(const TArray<FHairGroupsLOD>& In);` — `UFUNCTION(BlueprintGetter)`
- L636 _public prototype_ `const TArray<FHairGroupsLOD>& GetHairGroupsLOD() const;` — `UFUNCTION(BlueprintGetter)` — `UFUNCTION(BlueprintSetter)`
- L638 _public prototype_ `static FName GetHairGroupsCardsMemberName();`
- L639 _public prototype_ `UFUNCTION(BlueprintGetter) TArray<FHairGroupsCardsSourceDescription>& GetHairGroupsCards();`
- L640 _public prototype_ `UFUNCTION(BlueprintSetter) void SetHairGroupsCards(const TArray<FHairGroupsCardsSourceDescription>& In);` — `UFUNCTION(BlueprintGetter)`
- L641 _public prototype_ `const TArray<FHairGroupsCardsSourceDescription>& GetHairGroupsCards() const;` — `UFUNCTION(BlueprintGetter)` — `UFUNCTION(BlueprintSetter)`
- L643 _public prototype_ `static FName GetHairGroupsMeshesMemberName();`
- L644 _public prototype_ `UFUNCTION(BlueprintGetter) TArray<FHairGroupsMeshesSourceDescription>& GetHairGroupsMeshes();`
- L645 _public prototype_ `UFUNCTION(BlueprintSetter) void SetHairGroupsMeshes(const TArray<FHairGroupsMeshesSourceDescription>& In);` — `UFUNCTION(BlueprintGetter)`
- L646 _public prototype_ `const TArray<FHairGroupsMeshesSourceDescription>& GetHairGroupsMeshes() const;` — `UFUNCTION(BlueprintGetter)` — `UFUNCTION(BlueprintSetter)`
- L648 _public prototype_ `static FName GetHairGroupsMaterialsMemberName();`
- L649 _public prototype_ `UFUNCTION(BlueprintGetter) TArray<FHairGroupsMaterial>& GetHairGroupsMaterials();`
- L650 _public prototype_ `UFUNCTION(BlueprintSetter) void SetHairGroupsMaterials(const TArray<FHairGroupsMaterial>& In);` — `UFUNCTION(BlueprintGetter)`
- L651 _public prototype_ `const TArray<FHairGroupsMaterial>& GetHairGroupsMaterials() const;` — `UFUNCTION(BlueprintGetter)` — `UFUNCTION(BlueprintSetter)`
- L653 _public prototype_ `static FName GetEnableGlobalInterpolationMemberName();`
- L654 _public prototype_ `UFUNCTION(BlueprintGetter) bool GetEnableGlobalInterpolation() const;`
- L655 _public prototype_ `UFUNCTION(BlueprintSetter) void SetEnableGlobalInterpolation(bool In);` — `UFUNCTION(BlueprintGetter)`
- L657 _public prototype_ `static FName GetEnableSimulationCacheMemberName();`
- L658 _public prototype_ `UFUNCTION(BlueprintGetter) bool GetEnableSimulationCache() const;`
- L659 _public prototype_ `UFUNCTION(BlueprintSetter) void SetEnableSimulationCache(bool In);` — `UFUNCTION(BlueprintGetter)`
- L661 _public prototype_ `static FName GetHairInterpolationTypeMemberName();`
- L662 _public prototype_ `UFUNCTION(BlueprintGetter) EGroomInterpolationType GetHairInterpolationType() const;`
- L663 _public prototype_ `UFUNCTION(BlueprintSetter) void SetHairInterpolationType(EGroomInterpolationType In);` — `UFUNCTION(BlueprintGetter)`
- L665 _public prototype_ `static FName GetRiggedSkeletalMeshMemberName();`
- L666 _public prototype_ `UFUNCTION(BlueprintGetter) USkeletalMesh* GetRiggedSkeletalMesh() const;`
- L667 _public prototype_ `UFUNCTION(BlueprintSetter) void SetRiggedSkeletalMesh(USkeletalMesh* In);` — `UFUNCTION(BlueprintGetter)`
- L669 _public prototype_ `static FName GetDeformedGroupSectionsMemberName();`
- L670 _public prototype_ `UFUNCTION(BlueprintGetter) TArray<int32>& GetDeformedGroupSections();`
- L671 _public prototype_ `UFUNCTION(BlueprintSetter) void SetDeformedGroupSections(const TArray<int32>& In);` — `UFUNCTION(BlueprintGetter)`
- L672 _public prototype_ `const TArray<int32>& GetDeformedGroupSections() const;` — `UFUNCTION(BlueprintGetter)` — `UFUNCTION(BlueprintSetter)`
- L674 _public prototype_ `static FName GetMinLODMemberName();`
- L675 _public prototype_ `FPerPlatformInt GetMinLOD() const;`
- L676 _public prototype_ `void SetMinLOD(FPerPlatformInt In);`
- L678 _public prototype_ `static FName GetDisableBelowMinLodStrippingMemberName();`
- L679 _public prototype_ `FPerPlatformBool GetDisableBelowMinLodStripping() const;`
- L680 _public prototype_ `void SetDisableBelowMinLodStripping(FPerPlatformBool In);`
- L682 _public prototype_ `static FName GetEffectiveLODBiasMemberName();`
- L683 _public prototype_ `TArray<float>& GetEffectiveLODBias();`
- L684 _public prototype_ `void SetEffectiveLODBias(const TArray<float>& In);`
- L685 _public prototype_ `const TArray<float>& GetEffectiveLODBias() const;`
- L687 _public prototype_ `static FName GetHairGroupsPlatformDataMemberName();`
- L688 _public prototype_ `TArray<FHairGroupPlatformData>& GetHairGroupsPlatformData();`
- L689 _public prototype_ `const TArray<FHairGroupPlatformData>& GetHairGroupsPlatformData() const;`
- L690 _public prototype_ `void SetHairGroupsPlatformData(const TArray<FHairGroupPlatformData>& In);`
- L692 _public prototype_ `static FName GetHairGroupsInfoMemberName();`
- L693 _public prototype_ `TArray<FHairGroupInfoWithVisibility>& GetHairGroupsInfo();`
- L694 _public prototype_ `const TArray<FHairGroupInfoWithVisibility>& GetHairGroupsInfo() const;`
- L695 _public prototype_ `void SetHairGroupsInfo(const TArray<FHairGroupInfoWithVisibility>& In);`
- L697 _public prototype_ `const TArray<FHairGroupResources>& GetHairGroupsResources() const;`
- L698 _public prototype_ `TArray<FHairGroupResources>& GetHairGroupsResources();`
- L700 _public prototype_ `static FName GetLODModeMemberName();`
- L701 _public prototype_ `EGroomLODMode GetLODMode() const;`
- L703 _public prototype_ `static FName GetAutoLODBiasMemberName();`
- L705 _public prototype_ `float GetAutoLODBias() const;` — Return the asset Auto LOD Bias
- L708 _public prototype_ `float GetAutoLODBias(int32 InGroupIndex) const;` — Return the group Auto LOD Bias, which combines both the asset's bias, and the group bias
- L713 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L714 _public prototype_ `virtual void PostLoad() override;`
- L715 _public prototype_ `virtual void BeginDestroy() override;`
- L716 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L719 _public prototype_ `virtual TObjectPtr<UDataflowBaseContent> CreateDataflowContent() override;`
- L720 _public prototype_ `virtual void WriteDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) const override;`
- L721 _public prototype_ `virtual void ReadDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) override;`
- L725 _public function_ `virtual const FDataflowInstance& GetDataflowInstance() const override` — Begin IDataflowInstanceInterface Interface
- L726 _public function_ `virtual FDataflowInstance& GetDataflowInstance() override`
- L730 _public function_ `FOnGroomAssetChanged& GetOnGroomAssetChanged()`
- L731 _public function_ `FOnGroomAssetResourcesChanged& GetOnGroomAssetResourcesChanged()`
- L732 _public function_ `FOnGroomAsyncLoadFinished& GetOnGroomAsyncLoadFinished()`
- L733 _public function_ `FOnCreateGroomDataflow& GetOnCreateGroomDataflow()`
- L736 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;` — Part of Uobject interface
- L737 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L744 _public member_ `TObjectPtr<class UThumbnailInfo> ThumbnailInfo;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = Thumbnail)` — Thumbnail Info used for Groom Assets
- L748 _public member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = ImportSettings)` — Asset data to be used when re-importing
- L751 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;` — Retrieve the asset tags
- L753 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L756 _public prototype_ `virtual void PostInitProperties() override;` — Part of Uobject interface
- L760 _public function_ `bool IsValid() const`
- L763 _public prototype_ `void SetStableRasterization(bool bEnable);` — Helper functions for setting options on all hair groups
- L764 _public prototype_ `void SetScatterSceneLighting(bool Enable);`
- L765 _public prototype_ `void SetHairWidth(float Width);`
- L768 _public prototype_ `void InitResources();` — Initialize/Update/Release resources.
- L769 _public prototype_ `void InitGuideResources();`
- L770 _public prototype_ `void InitStrandsResources();`
- L771 _public prototype_ `void InitCardsResources();`
- L772 _public prototype_ `void InitMeshesResources();`
- L774 _public prototype_ `void UpdateResource();`
- L776 _public prototype_ `void ReleaseResource();`
- L777 _public prototype_ `void ReleaseGuidesResource(uint32 GroupIndex);`
- L778 _public prototype_ `void ReleaseStrandsResource(uint32 GroupIndex);`
- L779 _public prototype_ `void ReleaseCardsResource(uint32 GroupIndex);`
- L780 _public prototype_ `void ReleaseMeshesResource(uint32 GroupIndex);`
- L782 _public prototype_ `void SetNumGroup(uint32 InGroupCount, bool bResetGroupData=true, bool bResetOtherData=true);`
- L783 _public prototype_ `void ClearNumGroup(uint32 InGroupCount);`
- L785 _public prototype_ `bool AreGroupsValid() const;`
- L786 _public prototype_ `int32 GetNumHairGroups() const;`
- L788 _public prototype_ `int32 GetLODCount() const;`
- L790 _public prototype_ `void StripLODs(const TArray<int32>& LODsToKeep, bool bRebuildResources);`
- L794 _public prototype_ `bool HasDebugData() const;` — Debug data for derived asset generation (strands textures, ...).
- L795 _public prototype_ `void CreateDebugData();`
- L798 _public prototype_ `bool CanRebuildFromDescription() const;` — Returns true if the asset has the HairDescription needed to recompute its groom data
- L801 _public prototype_ `virtual void AddAssetUserData(UAssetUserData* InUserData) override;`
- L802 _public prototype_ `virtual void RemoveUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L803 _public prototype_ `virtual UAssetUserData* GetAssetUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L804 _public prototype_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override;`
- L807 _public prototype_ `EGroomGeometryType GetGeometryType(int32 GroupIndex, int32 LODIndex) const;`
- L808 _public prototype_ `EGroomBindingType GetBindingType(int32 GroupIndex, int32 LODIndex) const;`
- L809 _public prototype_ `bool IsVisible(int32 GroupIndex, int32 LODIndex) const;`
- L810 _public prototype_ `bool IsSimulationEnable(int32 GroupIndex, int32 LODIndex) const;`
- L811 _public prototype_ `bool IsSimulationEnable() const;`
- L812 _public prototype_ `bool IsDeformationEnable(int32 GroupIndex) const;`
- L813 _public prototype_ `bool IsGlobalInterpolationEnable(int32 GroupIndex, int32 LODIndex) const;`
- L814 _public prototype_ `bool NeedsInterpolationData(int32 GroupIndex) const;`
- L815 _public prototype_ `bool NeedsInterpolationData() const;`
- L816 _public prototype_ `EGroomGuideType GetGuideType(int32 GroupIndex) const;`
- L818 _public prototype_ `void UpdateHairGroupsInfo();`
- L819 _public prototype_ `bool HasGeometryType(EGroomGeometryType Type) const;`
- L820 _public prototype_ `bool HasGeometryType(uint32 GroupIndex, EGroomGeometryType Type) const;`
- L823 _public prototype_ `TArray<FHairVertexFactoryTypesPerMaterialData> CollectVertexFactoryTypesPerMaterialData(EShaderPlatform ShaderPlatform);` — Used for PSO precaching of used materials and vertex factories
- L826 _public prototype_ `FName GetAssetPathName(int32 LODIndex = -1);` — Helper function to return the asset path name, optionally joined with the LOD index if LODIndex > -1.
- L827 _public function_ `uint32 GetAssetHash() const`
- L831 _public member_ `FOnGroomAssetChanged OnGroomAssetChanged;`
- L832 _public member_ `FOnGroomAssetResourcesChanged OnGroomAssetResourcesChanged;`
- L833 _public member_ `FOnGroomAsyncLoadFinished OnGroomAsyncLoadFinished;`
- L834 _public member_ `FOnCreateGroomDataflow OnCreateGroomDataflow;`
- L836 _public prototype_ `void MarkMaterialsHasChanged();`
- L838 _public prototype_ `void RecreateResources();`
- L840 _public prototype_ `void ChangeFeatureLevel(ERHIFeatureLevel::Type PendingFeatureLevel);` — `UE_DEPRECATED(5.8, "Use ChangeShaderPlatform(EShaderPlatform) instead.")`
- L842 _public prototype_ `void ChangePlatformLevel(ERHIFeatureLevel::Type PendingFeatureLevel);` — `UE_DEPRECATED(5.8, "Use ChangeShaderPlatform(EShaderPlatform) instead.")`
- L843 _public prototype_ `void ChangeShaderPlatform(EShaderPlatform InShaderPlatform);`
- L848 _public member_ `TArray<TObjectPtr<UAssetUserData>> AssetUserData;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Instanced, Category = Hidden)` — Array of user data stored with the asset
- L851 _public prototype_ `int32 GetMaterialIndex(FName MaterialSlotName) const;` — Return the material slot index corresponding to the material name
- L852 _public prototype_ `bool IsMaterialSlotNameValid(FName MaterialSlotName) const;`
- L853 _public prototype_ `bool IsMaterialUsed(int32 MaterialIndex) const;`
- L854 _public prototype_ `TArray<FName> GetMaterialSlotNames() const;`
- L856 _public prototype_ `bool BuildCardsData();`
- L857 _public prototype_ `bool BuildMeshesData();`
- L868 _public prototype_ `uint8 GenerateClassStripFlags(FArchive& Ar);`
- L871 _public prototype_ `void ValidateSimulationCache();` — Enable the simulation cache and recompute the cached derived data
- L874 _private prototype_ `void ApplyStripFlags(uint8 StripFlags, const class ITargetPlatform* CookTarget);`
- L877 _private prototype_ `void UpdatePhysicsSystems();` — Update the physics system based on the solver settings enum
- L880 _private prototype_ `FHairStrandsRestResource* AllocateGuidesResources(uint32 GroupIndex);` — Functions allocating lazily/on-demand resources (guides, interpolation, RT geometry, ...)
- L881 _private prototype_ `FHairStrandsInterpolationResource* AllocateInterpolationResources(uint32 GroupIndex);`
- L883 _private prototype_ `FHairStrandsRaytracingResource* AllocateCardsRaytracingResources(uint32 GroupIndex, uint32 LODIndex);`
- L884 _private prototype_ `FHairStrandsRaytracingResource* AllocateMeshesRaytracingResources(uint32 GroupIndex, uint32 LODIndex);`
- L885 _private prototype_ `FHairStrandsRaytracingResource* AllocateStrandsRaytracingResources(uint32 GroupIndex);`
- L886 _private prototype_ `FHairStrandsRaytracingResource** GetStrandsRaytracingResourcesPtr(uint32 GroupIndex);`
- L891 _private prototype_ `bool HasImportedStrandsData() const;`
- L893 _private prototype_ `bool BuildHairGroup_Cards(uint32 GroupIndex);`
- L894 _private prototype_ `bool BuildHairGroup_Meshes(uint32 GroupIndex);`
- L896 _private prototype_ `bool HasChanged_Cards(uint32 GroupIndex, TArray<bool>& OutIsValid) const;`
- L897 _private prototype_ `bool HasChanged_Meshes(uint32 GroupIndex, TArray<bool>& OutIsValid) const;`
- L899 _private prototype_ `bool HasValidData_Cards(uint32 GroupIndex) const;`
- L900 _private prototype_ `bool HasValidData_Meshes(uint32 GroupIndex) const;`
- L904 _public prototype_ `void CommitHairDescription(FHairDescription&& HairDescription, EHairDescriptionType Type);` — Commits a HairDescription to buffer for serialization
- L907 _public prototype_ `FHairDescription GetHairDescription() const;` — Get the current hair description
- L910 _public prototype_ `FHairDescription LoadHairDescription(const EHairDescriptionType DescriptionType) const;` — Loads a specific hair description stored on the asset
- L913 _public prototype_ `bool GetHairStrandsDatas(const int32 GroupIndex, FHairStrandsDatas& OutStrandsData, FHairStrandsDatas& OutGuidesData) const;` — Get/Build render & guides data based on the hair description and interpolation settings
- L914 _public prototype_ `bool GetHairCardsGuidesDatas(const int32 GroupIndex, const int32 LODIndex, FHairStrandsDatas& OutCardsGuidesData);`
- L919 _public prototype_ `bool CacheDerivedDatas();` — Caches the computed (group) groom data with the given build settings from/to the Derived Data Cache, building it if needed. This function assumes the interpolation settings are properly populated, as they will be used to build the asset.
- L920 _public prototype_ `bool CacheDerivedData(uint32 GroupIndex);`
- L921 _public prototype_ `bool CacheStrandsData(uint32 GroupIndex, FString& OutDerivedDataKey);`
- L922 _public prototype_ `bool CacheCardsData(uint32 GroupIndex, const FString& StrandsKey);`
- L923 _public prototype_ `bool CacheMeshesData(uint32 GroupIndex);`
- L925 _public prototype_ `FString GetDerivedDataKey(bool bUseCacheKey=false);`
- L926 _public prototype_ `FString GetDerivedDataKeyForCards(uint32 GroupIt, const FString& StrandsKey);`
- L927 _public prototype_ `FString GetDerivedDataKeyForStrands(uint32 GroupIndex);`
- L928 _public prototype_ `FString GetDerivedDataKeyForMeshes(uint32 GroupIndex);`
- L930 _public prototype_ `const FHairDescriptionGroups& GetHairDescriptionGroups() const;`
- L934 _private function_ `void SetHairDescriptionType(const EHairDescriptionType DescriptionType)` — Set the hair description type
- L937 _private function_ `EHairDescriptionType GetHairDescriptionType() const` — Get the hair description type
- L940 _private function_ `uint8 GetHairDescriptionIndex() const` — Get the hair description index
- L942 _private prototype_ `bool IsFullyCached();`
- L943 _private member_ `TUniquePtr<FHairDescriptionBulkData> HairDescriptionBulkData[static_cast<uint8>(EHairDescriptionType::Count)];`
- L946 _private member_ `EHairDescriptionType HairDescriptionType = EHairDescriptionType::Source;` — `UPROPERTY()`
- L951 _private member_ `mutable UE::FRecursiveMutex InternalLock;` — Transient HairDescription & HairDescriptionGroups, which are built from HairDescriptionBulkData. All these data (bulk/desc/groups) needs to be in sync. I.e., when the HairDescription is updated, HairDescriptionGroups needs to also be updated
- L952 _private member_ `mutable TUniquePtr<FHairDescription> CachedHairDescription[static_cast<uint8>(EHairDescriptionType::Count)];`
- L953 _private member_ `mutable TUniquePtr<FHairDescriptionGroups> CachedHairDescriptionGroups[static_cast<uint8>(EHairDescriptionType::Count)];`
- L955 _private member_ `TArray<FString> StrandsDerivedDataKey;`
- L956 _private member_ `TArray<FString> CardsDerivedDataKey;`
- L957 _private member_ `TArray<FString> MeshesDerivedDataKey;`
- L959 _private member_ `TStrongObjectPtr<UGroomAsset> GroomAssetStrongPtr;`
- L960 _private member_ `bool bRetryLoadFromGameThread = false;`
- L962 _private member_ `bool bIsInitialized = false;`
- L963 _private member_ `uint32 AssetNameHash = 0;`
- L967 _public prototype_ `void UpdateCachedSettings();`
- L969 _private prototype_ `void SavePendingProceduralAssets();`
- L973 _private member_ `TArray<FHairGroupsRendering> CachedHairGroupsRendering;` — Cached groom settings to know if we need to recompute interpolation data or decimation when the asset is saved
- L974 _private member_ `TArray<FHairGroupsPhysics> CachedHairGroupsPhysics;`
- L975 _private member_ `TArray<FHairGroupsInterpolation> CachedHairGroupsInterpolation;`
- L976 _private member_ `TArray<FHairGroupsLOD> CachedHairGroupsLOD;`
- L977 _private member_ `TArray<FHairGroupsCardsSourceDescription> CachedHairGroupsCards;`
- L978 _private member_ `TArray<FHairGroupsMeshesSourceDescription> CachedHairGroupsMeshes;`
- L979 _private member_ `EShaderPlatform CachedResourceShaderPlatform = SP_NumPlatforms;`
- L982 _private member_ `TQueue<UStaticMesh*> AssetToSave_Meshes;` — Queue of procedural assets which needs to be saved
- L983 _private member_ `TQueue<FHairGroupCardsTextures*> AssetToSave_Textures;`

#### enum `UGroomAsset::EClassDataStripFlag`  
`enum EClassDataStripFlag : uint8`  
_L859-866_
- L861 _public enumerator_ `CDSF_ImportedStrands = 1`
- L862 _public enumerator_ `CDSF_MinLodData = 2`
- L863 _public enumerator_ `CDSF_StrandsStripped = 4`
- L864 _public enumerator_ `CDSF_CardsStripped = 8`
- L865 _public enumerator_ `CDSF_MeshesStripped = 16`

#### struct `FGroomAssetMemoryStats`  
`struct FGroomAssetMemoryStats`  
_L987-1013_
- L996 _public member_ `FStats CPU;`
- L997 _public member_ `FStats GPU;`
- L1006 _public member_ `FStrandsDetails Memory;`
- L1007 _public member_ `FStrandsDetails Curves;`
- L1009 _public prototype_ `static FGroomAssetMemoryStats Get(const FHairGroupPlatformData& InData, const FHairGroupResources& In);`
- L1010 _public prototype_ `void Accumulate(const FGroomAssetMemoryStats& In);`
- L1011 _public prototype_ `uint32 GetTotalCPUSize() const;`
- L1012 _public prototype_ `uint32 GetTotalGPUSize() const;`

#### struct `FGroomAssetMemoryStats::FStats`  
`struct FStats`  
_L989-995_
- L991 _public member_ `uint32 Guides = 0;`
- L992 _public member_ `uint32 Strands= 0;`
- L993 _public member_ `uint32 Cards = 0;`
- L994 _public member_ `uint32 Meshes = 0;`

#### struct `FGroomAssetMemoryStats::FStrandsDetails`  
`struct FStrandsDetails`  
_L999-1005_
- L1001 _public member_ `uint32 Rest = 0;`
- L1002 _public member_ `uint32 Interpolation= 0;`
- L1003 _public member_ `uint32 Cluster = 0;`
- L1004 _public member_ `uint32 Raytracing = 0;`

#### Free symbols / members of external scopes

- L30 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L40 _namespace_ `namespace Nanite`
- L242 _function_ `inline uint32 GetDataSize(const FHairStrandsBulkData& BulkData)`
- L255 _function_ `inline uint32 GetDataSize(const FHairStrandsInterpolationBulkData& InterpolationBulkData)`
- L474 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGroomAssetChanged);` — Notification when anything changed
- L475 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGroomAssetResourcesChanged);`
- L476 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGroomAsyncLoadFinished);`
- L477 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateGroomDataflow, UGroomAsset*);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomAssetCards.h` (Public)


#### enum `EHairCardsSourceType`  
`enum class EHairCardsSourceType : uint8`  
_L20-24_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `Procedural UMETA(DisplayName = "Procedural (experimental)")`
- L23 _public enumerator_ `Imported UMETA(DisplayName = "Imported")`

#### enum `EHairCardsGuideType`  
`enum class EHairCardsGuideType : uint8`  
_L27-31_
- reflection: `UENUM(BlueprintType)`
- L29 _public enumerator_ `Generated UMETA(DisplayName = "Generated")`
- L30 _public enumerator_ `GuideBased UMETA(DisplayName = "Guide-Based")`

#### enum `EHairTextureLayout`  
`enum class EHairTextureLayout : uint8`  
_L34-40_
- reflection: `UENUM(BlueprintType)`
- L36 _public enumerator_ `Layout0 UMETA(DisplayName = "Card Default")`
- L37 _public enumerator_ `Layout1 UMETA(DisplayName = "Mesh Default")`
- L38 _public enumerator_ `Layout2 UMETA(DisplayName = "Card Compact")`
- L39 _public enumerator_ `Layout3 UMETA(DisplayName = "Mesh Compact")`

#### struct `FHairGroupCardsInfo`  
`struct FHairGroupCardsInfo`  
_L47-56_
- reflection: `USTRUCT(BlueprintType)`
- L52 _public member_ `int32 NumCards = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Card Count"))`
- L55 _public member_ `int32 NumCardVertices = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Card Vertex Count"))`

#### struct `FHairGroupCardsTextures`  
`struct FHairGroupCardsTextures`  
_L59-91_
- reflection: `USTRUCT(BlueprintType)`
- L64 _public member_ `EHairTextureLayout Layout = EHairTextureLayout::Layout0;` — `UPROPERTY(EditAnywhere, Category = "CardsTextures")`
- L67 _public member_ `TArray<TObjectPtr<UTexture2D>> Textures;` — `UPROPERTY(EditAnywhere, Category = "CardsTextures")`
- L70 _public member_ `TObjectPtr<UTexture2D> DepthTexture_DEPRECATED = nullptr;` — `UPROPERTY()`
- L73 _public member_ `TObjectPtr<UTexture2D> CoverageTexture_DEPRECATED = nullptr;` — `UPROPERTY()`
- L76 _public member_ `TObjectPtr<UTexture2D> TangentTexture_DEPRECATED = nullptr;` — `UPROPERTY()`
- L79 _public member_ `TObjectPtr<UTexture2D> AttributeTexture_DEPRECATED = nullptr;` — `UPROPERTY()`
- L82 _public member_ `TObjectPtr<UTexture2D> AuxilaryDataTexture_DEPRECATED = nullptr;` — `UPROPERTY()`
- L85 _public member_ `TObjectPtr<UTexture2D> MaterialTexture_DEPRECATED = nullptr;` — `UPROPERTY()`
- L87 _public prototype_ `void SetLayout(EHairTextureLayout InLayout);`
- L88 _public prototype_ `void SetTexture(int32 SlotID, UTexture2D* Texture);`
- L90 _public member_ `bool bNeedToBeSaved = false;`

#### class `UHairCardGenerationSettings`  
`class UHairCardGenerationSettings : public UObject`  
_L99-104_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew)`
- inherits: `UObject`
- desc: Since hair-card generation can be controlled external to this plugin, this provides a way for those external generators a way to store their own generation data along with the groom/cards-entry.
- L103 _public prototype_ `virtual void BuildDDCKey(FArchive& Ar) PURE_VIRTUAL(BuildDDCKey,);`

#### struct `FHairGroupsCardsSourceDescription`  
`struct FHairGroupsCardsSourceDescription`  
_L107-164_
- reflection: `USTRUCT(BlueprintType)`
- L111 _public prototype_ `FHairGroupsCardsSourceDescription();`
- L115 _public member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY()` — Deprecated
- L118 _public member_ `FName MaterialSlotName;` — `UPROPERTY()`
- L121 _public member_ `EHairCardsSourceType SourceType_DEPRECATED = EHairCardsSourceType::Imported;` — `UPROPERTY()`
- L124 _public member_ `TObjectPtr<UStaticMesh> ProceduralMesh_DEPRECATED = nullptr;` — `UPROPERTY()`
- L127 _public member_ `bool bInvertUV = false;` — `UPROPERTY()`
- L130 _public member_ `EHairCardsGuideType GuideType;` — `UPROPERTY(EditAnywhere, Category = "CardsSource")`
- L133 _public member_ `TObjectPtr<UStaticMesh> ImportedMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "CardsSource", meta = (DisplayName = "Mesh"))`
- L136 _public member_ `FHairGroupCardsTextures Textures;` — `UPROPERTY(EditAnywhere, Category = "CardsSource")`
- L140 _public member_ `int32 GroupIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "CardsSource")` — Group index on which this cards geometry will be used (#hair_todo: change this to be a dropdown selection menu in FHairLODSettings instead)
- L144 _public member_ `int32 LODIndex = -1;` — `UPROPERTY(EditAnywhere, Category = "CardsSource")` — LOD on which this cards geometry will be used. -1 means not used  (#hair_todo: change this to be a dropdown selection menu in FHairLODSettings instead)
- L149 _public member_ `TObjectPtr<UHairCardGenerationSettings> GenerationSettings = nullptr;` — `UPROPERTY(meta=(EditInline))` — Card generation data saved from the last procedural run. Dependent on the generator responsible for running the generation.
- L153 _public member_ `mutable FHairGroupCardsInfo CardsInfo;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "CardsSource")`
- L156 _public member_ `FString ImportedMeshKey;` — `UPROPERTY(Transient)`
- L158 _public prototype_ `bool operator==(const FHairGroupsCardsSourceDescription& A) const;`
- L160 _public prototype_ `UStaticMesh* GetMesh() const;`
- L161 _public prototype_ `FString GetMeshKey() const;`
- L162 _public prototype_ `bool HasMeshChanged() const;`
- L163 _public prototype_ `void UpdateMeshKey();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L43 _prototype_ `uint32 GetHairTextureLayoutTextureCount(EHairTextureLayout In);` — Returns the number of textures used for a particular layout
- L44 _prototype_ `const TCHAR* GetHairTextureLayoutTextureName(EHairTextureLayout InLayout, uint32 InIndex, bool bDetail);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomAssetDataflow.h` (Public)


#### class `UDataflowGroomContent`  
`class UDataflowGroomContent : public UDataflowSkeletalContent`  
_L20-47_
- reflection: `UCLASS()`
- inherits: `UDataflowSkeletalContent`
- desc: Dataflow content owning dataflow and binding assets that will be used to evaluate the graph
- L25 _public prototype_ `UDataflowGroomContent();`
- L26 _public prototype_ `virtual ~UDataflowGroomContent() override = default;`
- L29 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L33 _public prototype_ `void SetBindingAsset(const TObjectPtr<UGroomBindingAsset>& InBindingAsset);` — Data flow binding asset accessors
- L34 _public function_ `const TObjectPtr<UGroomBindingAsset>& GetBindingAsset() const`
- L37 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L40 _public prototype_ `virtual void SetActorProperties(TObjectPtr<AActor>& PreviewActor) const override;` — Set all the preview actor exposed properties
- L46 _protected member_ `TObjectPtr<UGroomBindingAsset> BindingAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Preview", Transient, SkipSerialization)` — Data flow skeletal mesh

#### struct `FGroomDataflowSettings`  
`struct FGroomDataflowSettings : public FDataflowInstance`  
_L50-130_
- reflection: `USTRUCT()`
- inherits: `FDataflowInstance`
- L54 _public prototype_ `explicit FGroomDataflowSettings(UObject* InOwner = nullptr, UDataflow* InDataflowAsset = nullptr, FName InTerminalNodeName = NAME_None);`
- L57 _public prototype_ `static FName GetDataflowAssetMemberName();` — Return the Dataflow asset name.
- L60 _public prototype_ `static FName GetDataflowTerminalMemberName();` — Return the Dataflow terminal name.
- L63 _public function_ `USkeletalMesh* GetSkeletalMesh(const int32 GroupIndex) const` — Return the skeletal mesh associated to this groom asset if any.
- L66 _public function_ `int32 GetMeshLOD(const int32 GroupIndex) const` — Return the mesh LOD used to transfer the skinning
- L69 _public function_ `const FManagedArrayCollection* GetRestCollection() const` — Return the groom asset dataflow settings rest collection .
- L72 _public function_ `void InitSkeletalMeshes(const int32 NumGroups)` — Init the skeletal mesh associated to this groom asset if any.
- L75 _public function_ `void SetSkeletalMesh(const int32 GroupIndex, USkeletalMesh* SkeletalMesh, const int32 MeshLOD)` — Set a group skeletal mesh and its associated LOD to this groom asset
- L85 _public function_ `void SetRestCollection(FManagedArrayCollection* InRestCollection)` — Set the rest collection onto the groom asset dataflow settings
- L88 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom serialization function for the ManagedArrayCollection
- L93 _public prototype_ `void SetPreviewBindingAsset(UGroomBindingAsset* BindingAsset);` — Preview scene binding asset setter
- L96 _public prototype_ `UGroomBindingAsset* GetPreviewBindingAsset() const;` — Preview scene binding asset setter
- L99 _public prototype_ `void SetPreviewAnimationAsset(UAnimationAsset* AnimationAsset);` — Preview scene animation setter
- L102 _public prototype_ `UAnimationAsset* GetPreviewAnimationAsset() const;` — Preview scene animation getter
- L110 _private member_ `TArray<TObjectPtr<USkeletalMesh>> SkeletalMeshes;` — `UPROPERTY()` — Hair geometry that could describe external cards and meshes.
- L114 _private member_ `TArray<int32> MeshLODs;` — `UPROPERTY()` — LOD indices of the hair geometry used to transfer the skinning weights
- L120 _private member_ `TSoftObjectPtr<UGroomBindingAsset> PreviewBindingAsset;` — `UPROPERTY(AssetRegistrySearchable)` — Optional binding asset used in the dataflow Editor preview scene
- L124 _private member_ `TSoftObjectPtr<UAnimationAsset> PreviewAnimationAsset;` — `UPROPERTY(AssetRegistrySearchable)` — Optional animation asset used in the dataflow Editor preview scene
- L129 _private member_ `TSharedPtr<FManagedArrayCollection> RestCollection;` — Rest collection used to store all the dataflow attributes

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGroomDataflowSettings> : public TStructOpsTypeTraitsBase2<FGroomDataflowSettings>`  
_L132-138_
- inherits: `TStructOpsTypeTraitsBase2<FGroomDataflowSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L135-137_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L136 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anone57dfe010103`)

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomAssetImportData.h` (Public)


#### class `UGroomAssetImportData`  
`class UGroomAssetImportData : public UAssetImportData`  
_L11-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetImportData`
- L18 _public member_ `TObjectPtr<class UGroomImportOptions> ImportOptions;` — `UPROPERTY()`
- L21 _public member_ `TObjectPtr<class UGroomCreateStrandsTexturesOptions> HairStrandsTexturesOptions;` — `UPROPERTY()`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomAssetInterpolation.h` (Public)


#### enum `EHairInterpolationQuality`  
`enum class EHairInterpolationQuality : uint8`  
_L13-19_
- reflection: `UENUM()`
- L15 _public enumerator_ `Low UMETA(DisplayName = "Low", ToolTip = "Build interpolation data based on nearst neighbor search. Low quality interpolation data, but fast to build (takes a few minutes)")`
- L16 _public enumerator_ `Medium UMETA(DisplayName = "Medium", ToolTip = "Build interpolation data using curve shape matching search but within a limited spatial range. This is a tradeoff between Low and high quality in term of quality & build time (can takes several dozen of minutes)")`
- L17 _public enumerator_ `High UMETA(DisplayName = "High", ToolTip = "Build interpolation data using curve shape matching search. This result in high quality interpolation data, but is relatively slow to build (can takes several dozen of minutes)")`
- L18 _public enumerator_ `Unknown UMETA(Hidden)`

#### enum `EHairInterpolationWeight`  
`enum class EHairInterpolationWeight : uint8`  
_L22-29_
- reflection: `UENUM()`
- L24 _public enumerator_ `Parametric UMETA(DisplayName = "Parametric", ToolTip = "Build interpolation data based on curve parametric distance")`
- L25 _public enumerator_ `Root UMETA(DisplayName = "Root", ToolTip = "Build interpolation data based on distance between guide's root and strands's root")`
- L26 _public enumerator_ `Index UMETA(DisplayName = "Index", ToolTip = "Build interpolation data based on guide and strands vertex indices")`
- L27 _public enumerator_ `Distance UMETA(DisplayName = "Distance", ToolTip = "Build interpolation data based on curve euclidean distance")`
- L28 _public enumerator_ `Unknown UMETA(Hidden)`

#### enum `EGroomGeometryType`  
`enum class EGroomGeometryType : uint8`  
_L32-37_
- reflection: `UENUM(BlueprintType)`
- L34 _public enumerator_ `Strands`
- L35 _public enumerator_ `Cards`
- L36 _public enumerator_ `Meshes`

#### enum `EGroomBindingType`  
`enum class EGroomBindingType : uint8`  
_L40-45_
- reflection: `UENUM(BlueprintType)`
- L42 _public enumerator_ `NoneBinding UMETA(Hidden)`
- L43 _public enumerator_ `Rigid UMETA(DisplayName = "Rigid", ToolTip = "When attached to a skeltal mesh, the hair follow the provided attachement name")`
- L44 _public enumerator_ `Skinning UMETA(DisplayName = "Skinning", ToolTip = "When attached to a skeltal mesh, the hair follow the skin surface")`

#### enum `EGroomOverrideType`  
`enum class EGroomOverrideType : uint8`  
_L48-53_
- reflection: `UENUM(BlueprintType)`
- L50 _public enumerator_ `Auto UMETA(DisplayName = "Auto", ToolTip = "Use the asset value")`
- L51 _public enumerator_ `Enable UMETA(DisplayName = "Enable", ToolTip = "Override the asset value, and force enabled")`
- L52 _public enumerator_ `Disable UMETA(DisplayName = "Disable", ToolTip = "Override the asset value, and force disabled")`

#### enum `EGroomGuideType`  
`enum class EGroomGuideType : uint8`  
_L56-61_
- reflection: `UENUM(BlueprintType)`
- L58 _public enumerator_ `Imported UMETA(DisplayName = "Imported Guides", ToolTip = "Use imported asset guides.")`
- L59 _public enumerator_ `Generated UMETA(DisplayName = "Generated Guides", ToolTip = "Generate guides from imported strands")`
- L60 _public enumerator_ `Rigged UMETA(DisplayName = "Rigged Guides", ToolTip = "Generated rigged guides from imported strands")`

#### enum `EGroomLODMode`  
`enum class EGroomLODMode : uint8`  
_L64-69_
- reflection: `UENUM(BlueprintType)`
- L66 _public enumerator_ `Default UMETA(DisplayName = "Default", ToolTip = "Hair strands curves & points adapt based on project settings LOD mode. (See 'Use Auto LOD' in project settings). ")`
- L67 _public enumerator_ `Manual UMETA(DisplayName = "Manual", ToolTip = "Hair strands curves & points adapt based on LOD settings")`
- L68 _public enumerator_ `Auto UMETA(DisplayName = "Auto", ToolTip = "Hair strands curves & points automatically adapt based on screen coverage. LOD settings are ignored.")`

#### struct `FHairLODSettings`  
`struct FHairLODSettings`  
_L72-113_
- reflection: `USTRUCT(BlueprintType)`
- L78 _public member_ `float CurveDecimation = 1;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (ToolTip = "Reduce the number of hair strands in a uniform manner", ClampMin = "0", UIMin = "0", UIMax = "1.0"))` — Reduce the number of hair strands
- L82 _public member_ `float VertexDecimation = 1;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (ToolTip = " Reduce the number of points for each hair strands", ClampMin = "0", UIMin = "0", UIMax = "1.0"))` — Reduce the number of points for each hair strands
- L86 _public member_ `float AngularThreshold = 1.f;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (ToolTip = "Max angular difference between adjacents vertices to remove vertices during simplification, in degrees", ClampMin = "0", ClampMax = "45", UIMin = "0", UIMax = "45.0"))` — Max angular difference between adjacents vertices to remove vertices during simplification, in degrees.
- L90 _public member_ `float ScreenSize = 1;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (ToolTip = "Screen size at which this LOD should be enabled", ClampMin = "0", UIMin = "0", UIMax = "1.0"))` — Screen size at which this LOD should be enabled
- L94 _public member_ `float ThicknessScale = 1;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (ToolTip = "Scales the hair Strands radius. This can be used for manually compensating the reduction of curves.", ClampMin = "0", UIMin = "0", UIMax = "1.0"))` — Scales the hair Strands radius. This can be used for manually compensating the reduction of curves..
- L98 _public member_ `bool bVisible = true;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (ToolTip = "If disable, the hair strands won't be rendered"))` — If true (default), the hair group is visible. If false, the hair group is culled.
- L101 _public member_ `EGroomGeometryType GeometryType = EGroomGeometryType::Strands;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (ToolTip = "Defines the type of geometry used by this LOD (Strands, Cards, or Meshes)"))`
- L104 _public member_ `EGroomBindingType BindingType = EGroomBindingType::Skinning;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", AdvancedDisplay, meta = (ToolTip = "Defines the type of attachment"))`
- L107 _public member_ `EGroomOverrideType Simulation = EGroomOverrideType::Auto;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", AdvancedDisplay, meta = (ToolTip = "Groom simulation"))`
- L110 _public member_ `EGroomOverrideType GlobalInterpolation = EGroomOverrideType::Auto;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", AdvancedDisplay, meta = (DisplayName = "RBF Interpolation", ToolTip = "Global interpolation"))`
- L112 _public prototype_ `bool operator==(const FHairLODSettings& A) const;`

#### struct `FHairDecimationSettings`  
`struct FHairDecimationSettings`  
_L116-131_
- reflection: `USTRUCT(BlueprintType)`
- L120 _public prototype_ `FHairDecimationSettings();`
- L124 _public member_ `float CurveDecimation;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (ToolTip = "Reduce the number of hair strands in a uniform manner", ClampMin = "0", UIMin = "0", UIMax = "1.0"))` — Reduce the number of hair strands in a uniform manner (initial decimation)
- L128 _public member_ `float VertexDecimation;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (ToolTip = "Reduce the number of verties for each hair strands in a uniform manner", ClampMin = "0", UIMin = "0", UIMax = "1.0"))` — Reduce the number of vertices for each hair strands in a uniform manner (initial decimation)
- L130 _public prototype_ `bool operator==(const FHairDecimationSettings& A) const;`

#### struct `FHairInterpolationSettings`  
`struct FHairInterpolationSettings`  
_L134-177_
- reflection: `USTRUCT(BlueprintType)`
- L138 _public prototype_ `FHairInterpolationSettings();`
- L142 _public member_ `EGroomGuideType GuideType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InterpolationSettings", meta = (ToolTip = "Type of guides:\n - Imported: use imported guides\n - Generated: generate guides from strands\n - Rigged: generated rigged guides from strands."))` — Flag to override the imported guides with generated guides.
- L146 _public member_ `bool bOverrideGuides_DEPRECATED;` — `UPROPERTY()` — Flag to override the imported guides with generated guides. DEPRECATED
- L150 _public member_ `float HairToGuideDensity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InterpolationSettings", meta = (DisplayName = "Generated guide density", ClampMin = "0", ClampMax = "1.0", UIMin = "0", UIMax = "1.0", EditCondition="GuideType == EGroomGuideType::Generated"))` — Density factor for converting hair into guide curve if no guides are provided. The value should be between 0 and 1, and can be thought as a ratio/percentage of strands used as guides.
- L154 _public member_ `int32 RiggedGuideNumCurves;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InterpolationSettings", meta = (DisplayName = "Rigged guide num. curves", ToolTip = "Number of guides that will be generated on the groom and the skeletal mesh", EditCondition="GuideType == EGroomGuideType::Rigged"))` — Number of curves to generate in the skel mesh
- L158 _public member_ `int32 RiggedGuideNumPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InterpolationSettings", meta = (DisplayName = "Rigged guide num. points", ToolTip = "Number of points/bones per generated guide", EditCondition="GuideType == EGroomGuideType::Rigged"))` — Number of points per curve
- L162 _public member_ `EHairInterpolationQuality InterpolationQuality;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InterpolationSettings")` — Interpolation data quality.
- L166 _public member_ `EHairInterpolationWeight InterpolationDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InterpolationSettings")` — Interpolation distance metric.
- L170 _public member_ `bool bRandomizeGuide;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InterpolationSettings")` — Randomize which guides affect a given hair strand.
- L174 _public member_ `bool bUseUniqueGuide;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InterpolationSettings")` — Force a hair strand to be affected by a unique guide.
- L176 _public prototype_ `bool operator==(const FHairInterpolationSettings& A) const;`

#### struct `FHairDeformationSettings`  
`struct FHairDeformationSettings`  
_L180-196_
- reflection: `USTRUCT(BlueprintType)`
- L184 _public prototype_ `FHairDeformationSettings();`
- L187 _public member_ `bool bEnableRigging_DEPRECATED;` — `UPROPERTY()`
- L190 _public member_ `int32 NumCurves_DEPRECATED;` — `UPROPERTY()`
- L193 _public member_ `int32 NumPoints_DEPRECATED;` — `UPROPERTY()`
- L195 _public prototype_ `bool operator==(const FHairDeformationSettings& A) const;`

#### struct `FHairGroupsInterpolation`  
`struct FHairGroupsInterpolation`  
_L199-224_
- reflection: `USTRUCT(BlueprintType)`
- L203 _public prototype_ `FHairGroupsInterpolation();`
- L206 _public member_ `FHairDecimationSettings DecimationSettings;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (ToolTip = "Decimation settings"))`
- L209 _public member_ `FHairInterpolationSettings InterpolationSettings;` — `UPROPERTY(EditAnywhere, Category = "InterpolationSettings", meta = (ToolTip = "Interpolation settings"))`
- L213 _public member_ `FHairDeformationSettings RiggingSettings;` — `UPROPERTY()` — DEPRECATED
- L218 _public member_ `FName GroupName = NAME_None;` — `UPROPERTY(VisibleDefaultsOnly, Transient, Category=AlwaysHidden, Meta=(EditCondition=False, EditConditionHides))` — Group name to be displayed in the array list
- L221 _public prototype_ `bool operator==(const FHairGroupsInterpolation& A) const;`
- L223 _public prototype_ `void BuildDDCKey(FArchive& Ar);`

#### struct `FHairGroupsLOD`  
`struct FHairGroupsLOD`  
_L227-242_
- reflection: `USTRUCT(BlueprintType)`
- L232 _public member_ `float AutoLODBias = 0;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (DisplayName = "Group Auto LOD Bias", ToolTip = "When LOD mode is set to Auto, decrease the screen size at which curves reduction will occur. The final bias value is computed by adding this value to the asset's Auto LOD bias value.", ClampMin = "-1", ClampMax = "1", UIMin = "-1.0", UIMax = "1.0"))`
- L236 _public member_ `TArray<FHairLODSettings> LODs;` — `UPROPERTY(EditAnywhere, Category = "DecimationSettings", meta = (ToolTip = "Reduce the number of hair strands in a uniform manner", ClampMin = "0", UIMin = "0", UIMax = "1.0"))` — LODs
- L238 _public prototype_ `bool operator==(const FHairGroupsLOD& A) const;`
- L240 _public prototype_ `void BuildDDCKey(FArchive& Ar);`
- L241 _public prototype_ `static FHairGroupsLOD GetDefault();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomAssetMeshes.h` (Public)


#### struct `FHairGroupsMeshesSourceDescription`  
`struct FHairGroupsMeshesSourceDescription`  
_L19-54_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public prototype_ `FHairGroupsMeshesSourceDescription();`
- L27 _public member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY()` — Deprecated
- L30 _public member_ `FName MaterialSlotName;` — `UPROPERTY()`
- L33 _public member_ `TObjectPtr<class UStaticMesh> ImportedMesh;` — `UPROPERTY(EditAnywhere, Category = "MeshSettings", meta = (ToolTip = "Mesh settings"))`
- L36 _public member_ `FHairGroupCardsTextures Textures;` — `UPROPERTY(EditAnywhere, Category = "MeshesSource")`
- L40 _public member_ `int32 GroupIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "MeshesSource")` — Group index on which this mesh geometry will be used (#hair_todo: change this to be a dropdown selection menu in FHairLODSettings instead)
- L44 _public member_ `int32 LODIndex = -1;` — `UPROPERTY(EditAnywhere, Category = "MeshesSource")` — LOD on which this mesh geometry will be used. -1 means not used  (#hair_todo: change this to be a dropdown selection menu in FHairLODSettings instead)
- L47 _public member_ `FString ImportedMeshKey;` — `UPROPERTY(Transient)`
- L49 _public prototype_ `bool operator==(const FHairGroupsMeshesSourceDescription& A) const;`
- L51 _public prototype_ `FString GetMeshKey() const;`
- L52 _public prototype_ `bool HasMeshChanged() const;`
- L53 _public prototype_ `void UpdateMeshKey();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomAssetPhysics.h` (Public)


#### enum `EGroomNiagaraSolvers`  
`enum class EGroomNiagaraSolvers : uint8`  
_L16-22_
- reflection: `UENUM(BlueprintType)`
- desc: List of niagara solvers
- L18 _public enumerator_ `None = 0 UMETA(Hidden)`
- L19 _public enumerator_ `CosseratRods = 0x02 UMETA(DisplayName = "Groom Rods")`
- L20 _public enumerator_ `AngularSprings = 0x04 UMETA(DisplayName = "Groom Springs")`
- L21 _public enumerator_ `CustomSolver = 0x08 UMETA(DisplayName = "Custom Solver")`

#### enum `EGroomStrandsSize`  
`enum class EGroomStrandsSize : uint8`  
_L26-34_
- reflection: `UENUM(BlueprintType)`
- desc: Size of each strands
- L28 _public enumerator_ `None = 0 UMETA(Hidden)`
- L29 _public enumerator_ `Size2 = 0x02 UMETA(DisplayName = "2")`
- L30 _public enumerator_ `Size4 = 0x04 UMETA(DisplayName = "4")`
- L31 _public enumerator_ `Size8 = 0x08 UMETA(DisplayName = "8")`
- L32 _public enumerator_ `Size16 = 0x10 UMETA(DisplayName = "16")`
- L33 _public enumerator_ `Size32 = 0x20 UMETA(DisplayName = "32")`

#### enum `EGroomInterpolationType`  
`enum class EGroomInterpolationType : uint8`  
_L38-44_
- reflection: `UENUM(BlueprintType)`
- desc: List of interpolation type
- L40 _public enumerator_ `None = 0 UMETA(DisplayName = "No skinning")`
- L41 _public enumerator_ `RigidTransform = 0x02 UMETA(DisplayName = "Rigid Transform")`
- L42 _public enumerator_ `OffsetTransform = 0x04 UMETA(DisplayName = "Offset Transform")`
- L43 _public enumerator_ `SmoothTransform = 0x08 UMETA(DisplayName = "Smooth Transform")`

#### struct `FHairSolverSettings`  
`struct FHairSolverSettings`  
_L47-86_
- reflection: `USTRUCT(BlueprintType)`
- L51 _public prototype_ `FHairSolverSettings();`
- L55 _public member_ `bool bEnableDeformation;` — `UPROPERTY(EditAnywhere, Category = "SolverSettings", meta = (ToolTip = "Use deformer for the groom solver", DisplayName = "Enable Deformation"))` — Use deformer for simulation
- L59 _public member_ `bool EnableSimulation;` — `UPROPERTY(EditAnywhere, Category = "SolverSettings", meta = (ToolTip = "Use niagara for the groom solver", DisplayName = "Enable Simulation"))` — Use niagara for simulation
- L63 _public member_ `EGroomNiagaraSolvers NiagaraSolver;` — `UPROPERTY(EditAnywhere, Category = "SolverSettings", meta = (ToolTip = "Niagara solver to be used for simulation"))` — Niagara solver to be used for simulation
- L67 _public member_ `TSoftObjectPtr<UNiagaraSystem> CustomSystem;` — `UPROPERTY(EditAnywhere, Category = "SolverSettings", meta = (EditCondition = "NiagaraSolver == EGroomNiagaraSolvers::CustomSolver", ToolTip = "Custom niagara system to be used if custom solver is picked"))` — Custom system to be used for simulation
- L71 _public member_ `float GravityPreloading;` — `UPROPERTY(EditAnywhere, Category = "SolverSettings", meta = (EditCondition = "NiagaraSolver == EGroomNiagaraSolvers::AngularSprings", ToolTip = "Optimisation of the rest state configuration to compensate from the gravity "))` — Optimisation of the rest state configuration to compensate from the gravity
- L75 _public member_ `int32 SubSteps;` — `UPROPERTY(EditAnywhere, Category = "SolverSettings", meta = (ToolTip = "Number of sub steps to be done per frame. The actual solver calls are done at 24 fps"))` — Number of substeps to be used
- L79 _public member_ `int32 IterationCount;` — `UPROPERTY(EditAnywhere, Category = "SolverSettings", meta = (ToolTip = "Number of iterations to solve the constraints with the xpbd solver"))` — Number of iterations for the constraint solver
- L83 _public member_ `bool bForceVisible;` — `UPROPERTY(EditAnywhere, Category = "SolverSettings", meta = (ToolTip = "Force the Niagara solver component to be visible"))` — Force the Niagara solver component to be visible
- L85 _public prototype_ `bool operator==(const FHairSolverSettings& A) const;`

#### struct `FHairExternalForces`  
`struct FHairExternalForces`  
_L89-108_
- reflection: `USTRUCT(BlueprintType)`
- L93 _public prototype_ `FHairExternalForces();`
- L97 _public member_ `FVector GravityVector;` — `UPROPERTY(EditAnywhere, Category = "ExternalForces", meta = (ToolTip = "Acceleration vector in cm/s2 to be used for the gravity"))` — Acceleration vector in cm/s2 to be used for the gravity
- L101 _public member_ `float AirDrag;` — `UPROPERTY(EditAnywhere, Category = "ExternalForces", meta = (ToolTip = "Coefficient between 0 and 1 to be used for the air drag"))` — Coefficient between 0 and 1 to be used for the air drag
- L105 _public member_ `FVector AirVelocity;` — `UPROPERTY(EditAnywhere, Category = "ExternalForces", meta = (ToolTip = "Velocity of the surrounding air in cm/s"))` — Velocity of the surrounding air in cm/s
- L107 _public prototype_ `bool operator==(const FHairExternalForces& A) const;`

#### struct `FHairBendConstraint`  
`struct FHairBendConstraint`  
_L111-138_
- reflection: `USTRUCT(BlueprintType)`
- L115 _public prototype_ `FHairBendConstraint();`
- L119 _public member_ `bool SolveBend;` — `UPROPERTY(EditAnywhere, Category = "BendConstraint", meta = (ToolTip = "Enable the solve of the bend constraint during the xpbd loop"))` — Enable the solve of the bend constraint during the xpbd loop
- L123 _public member_ `bool ProjectBend;` — `UPROPERTY(EditAnywhere, Category = "BendConstraint", meta = (ToolTip = "Enable ther projection of the bend constraint after the xpbd loop"))` — Enable the projection of the bend constraint after the xpbd loop
- L127 _public member_ `float BendDamping;` — `UPROPERTY(EditAnywhere, Category = "BendConstraint", meta = (ToolTip = "Damping for the bend constraint between 0 and 1"))` — Damping for the bend constraint between 0 and 1
- L131 _public member_ `float BendStiffness;` — `UPROPERTY(EditAnywhere, Category = "BendConstraint", meta = (ToolTip = "Stiffness for the bend constraint in GPa"))` — Stiffness for the bend constraint in GPa
- L135 _public member_ `FRuntimeFloatCurve BendScale;` — `UPROPERTY(EditAnywhere, Category = "BendConstraint", meta = (DisplayName = "Stiffness Scale", ViewMinInput = "0.0", ViewMaxInput = "1.0", ViewMinOutput = "0.0", ViewMaxOutput = "1.0", TimeLineLength = "1.0", XAxisName = "Strand Coordinate (0,1)", YAxisName = "Bend Scale", ToolTip = "This curve determines how much the bend stiffness will be scaled along each strand. \n The X axis range is [0,1], 0 mapping the root and 1 the tip"))` — Stiffness scale along the strand
- L137 _public prototype_ `bool operator==(const FHairBendConstraint& A) const;`

#### struct `FHairStretchConstraint`  
`struct FHairStretchConstraint`  
_L142-169_
- reflection: `USTRUCT(BlueprintType)`
- L146 _public prototype_ `FHairStretchConstraint();`
- L150 _public member_ `bool SolveStretch;` — `UPROPERTY(EditAnywhere, Category = "StretchConstraint", meta = (ToolTip = "Enable the solve of the stretch constraint during the xpbd loop"))` — Enable the solve of the stretch constraint during the xpbd loop
- L154 _public member_ `bool ProjectStretch;` — `UPROPERTY(EditAnywhere, Category = "StretchConstraint", meta = (ToolTip = "Enable ther projection of the stretch constraint after the xpbd loop"))` — Enable the projection of the stretch constraint after the xpbd loop
- L158 _public member_ `float StretchDamping;` — `UPROPERTY(EditAnywhere, Category = "StretchConstraint", meta = (ToolTip = "Damping for the stretch constraint between 0 and 1"))` — Damping for the stretch constraint between 0 and 1
- L162 _public member_ `float StretchStiffness;` — `UPROPERTY(EditAnywhere, Category = "StretchConstraint", meta = (ToolTip = "Stiffness for the stretch constraint in GPa"))` — Stiffness for the stretch constraint in GPa
- L166 _public member_ `FRuntimeFloatCurve StretchScale;` — `UPROPERTY(EditAnywhere, Category = "StretchConstraint", meta = (DisplayName = "Stiffness Scale", ViewMinInput = "0.0", ViewMaxInput = "1.0", ViewMinOutput = "0.0", ViewMaxOutput = "1.0", TimeLineLength = "1.0", XAxisName = "Strand Coordinate (0,1)", YAxisName = "Stretch Scale", ToolTip = "This curve determines how much the stretch stiffness will be scaled along each strand. \n The X axis range is [0,1], 0 mapping the root and 1 the tip"))` — Stretch scale along the strand
- L168 _public prototype_ `bool operator==(const FHairStretchConstraint& A) const;`

#### struct `FHairCollisionConstraint`  
`struct FHairCollisionConstraint`  
_L172-211_
- reflection: `USTRUCT(BlueprintType)`
- L176 _public prototype_ `FHairCollisionConstraint();`
- L180 _public member_ `bool SolveCollision;` — `UPROPERTY(EditAnywhere, Category = "CollisionConstraint", meta = (ToolTip = "Enable the solve of the collision constraint during the xpbd loop"))` — Enable the solve of the collision constraint during the xpbd loop
- L184 _public member_ `bool ProjectCollision;` — `UPROPERTY(EditAnywhere, Category = "CollisionConstraint", meta = (ToolTip = "Enable ther projection of the collision constraint after the xpbd loop"))` — Enable ther projection of the collision constraint after the xpbd loop
- L188 _public member_ `float StaticFriction;` — `UPROPERTY(EditAnywhere, Category = "Collision Constraint", meta = (ToolTip = "Static friction used for collision against the physics asset"))` — Static friction used for collision against the physics asset
- L192 _public member_ `float KineticFriction;` — `UPROPERTY(EditAnywhere, Category = "CollisionConstraint", meta = (ToolTip = "Kinetic friction used for collision against the physics asset"))` — Kinetic friction used for collision against the physics asset
- L196 _public member_ `float StrandsViscosity;` — `UPROPERTY(EditAnywhere, Category = "CollisionConstraint", meta = (ToolTip = "Viscosity parameter between 0 and 1 that will be used for self collision"))` — Viscosity parameter between 0 and 1 that will be used for self collision
- L200 _public member_ `FIntVector GridDimension;` — `UPROPERTY(EditAnywhere, Category = "CollisionConstraint", meta = (ToolTip = "Dimension of the grid used to compute the viscosity force"))` — Dimension of the grid used to compute the viscosity force
- L204 _public member_ `float CollisionRadius;` — `UPROPERTY(EditAnywhere, Category = "CollisionConstraint", meta = (ToolTip = "Radius that will be used for the collision detection against the physics asset"))` — Radius that will be used for the collision detection against the physics asset
- L208 _public member_ `FRuntimeFloatCurve RadiusScale;` — `UPROPERTY(EditAnywhere, Category = "CollisionConstraint", meta = (ViewMinInput = "0.0", ViewMaxInput = "1.0", ViewMinOutput = "0.0", ViewMaxOutput = "1.0", TimeLineLength = "1.0", XAxisName = "Strand Coordinate (0,1)", YAxisName = "Collision Radius", ToolTip = "This curve determines how much the collision radius will be scaled along each strand. \n The X axis range is [0,1], 0 mapping the root and 1 the tip"))` — Radius scale along the strand
- L210 _public prototype_ `bool operator==(const FHairCollisionConstraint& A) const;`

#### struct `FHairMaterialConstraints`  
`struct FHairMaterialConstraints`  
_L215-234_
- reflection: `USTRUCT(BlueprintType)`
- L219 _public prototype_ `FHairMaterialConstraints();`
- L223 _public member_ `FHairBendConstraint BendConstraint;` — `UPROPERTY(EditAnywhere, Category = "MaterialConstraints", meta = (ToolTip = "Bend constraint settings to be applied to the hair strands"))` — Radius scale along the strand
- L227 _public member_ `FHairStretchConstraint StretchConstraint;` — `UPROPERTY(EditAnywhere, Category = "MaterialConstraints", meta = (ToolTip = "Stretch constraint settings to be applied to the hair strands"))` — Radius scale along the strand
- L231 _public member_ `FHairCollisionConstraint CollisionConstraint;` — `UPROPERTY(EditAnywhere, Category = "MaterialConstraints", meta = (ToolTip = "Collision constraint settings to be applied to the hair strands"))` — Radius scale along the strand
- L233 _public prototype_ `bool operator==(const FHairMaterialConstraints& A) const;`

#### struct `FHairStrandsParameters`  
`struct FHairStrandsParameters`  
_L237-264_
- reflection: `USTRUCT(BlueprintType)`
- L241 _public prototype_ `FHairStrandsParameters();`
- L245 _public member_ `EGroomStrandsSize StrandsSize;` — `UPROPERTY(EditAnywhere, Category = "StrandsParameters", meta = (ToolTip = "Number of particles per guide that will be used for simulation"))` — Number of particles per guide that will be used for simulation
- L249 _public member_ `float StrandsDensity;` — `UPROPERTY(EditAnywhere, Category = "StrandsParameters", meta = (ToolTip = "Density of the strands in g/cm3"))` — Density of the strands in g/cm3
- L253 _public member_ `float StrandsSmoothing;` — `UPROPERTY(EditAnywhere, Category = "StrandsParameters", meta = (ToolTip = "Smoothing between 0 and 1 of the incoming guides curves for better stability"))` — Smoothing between 0 and 1 of the incoming guides curves for better stability
- L257 _public member_ `float StrandsThickness;` — `UPROPERTY(EditAnywhere, Category = "StrandsParameters", meta = (ToolTip = "Strands thickness in cm that will be used for mass and inertia computation"))` — Strands thickness in cm that will be used for mass and inertia computation
- L261 _public member_ `FRuntimeFloatCurve ThicknessScale;` — `UPROPERTY(EditAnywhere, Category = "StrandsParameters", meta = (ViewMinInput = "0.0", ViewMaxInput = "1.0", ViewMinOutput = "0.0", ViewMaxOutput = "1.0", TimeLineLength = "1.0", XAxisName = "Strand Coordinate (0,1)", YAxisName = "Strands Thickness", ToolTip = "This curve determines how much the strands thickness will be scaled along each strand. \n The X axis range is [0,1], 0 mapping the root and 1 the tip"))` — Thickness scale along the curve
- L263 _public prototype_ `bool operator==(const FHairStrandsParameters& A) const;`

#### struct `FHairGroupsPhysics`  
`struct FHairGroupsPhysics`  
_L267-299_
- reflection: `USTRUCT(BlueprintType)`
- L271 _public prototype_ `FHairGroupsPhysics();`
- L275 _public member_ `FHairSolverSettings SolverSettings;` — `UPROPERTY(EditAnywhere, Category = "GroupsPhysics", meta = (ToolTip = "Solver Settings for the hair physics"))` — Enable the simulation for the group
- L279 _public member_ `FHairExternalForces ExternalForces;` — `UPROPERTY(EditAnywhere, Category = "GroupsPhysics", meta = (ToolTip = "External Forces for the hair physics"))` — Enable the simulation for the group
- L283 _public member_ `FHairMaterialConstraints MaterialConstraints;` — `UPROPERTY(EditAnywhere, Category = "GroupsPhysics", meta = (ToolTip = "Material Constraints for the hair physics"))` — Enable the simulation for the group
- L287 _public member_ `FHairStrandsParameters StrandsParameters;` — `UPROPERTY(EditAnywhere, Category = "GroupsPhysics", meta = (ToolTip = "Strands Parameters for the hair physics"))` — Enable the simulation for the group
- L292 _public member_ `FName GroupName = NAME_None;` — `UPROPERTY(VisibleDefaultsOnly, Transient, Category=AlwaysHidden, Meta=(EditCondition=False, EditConditionHides))` — Group name to be displayed in the array list
- L295 _public prototype_ `bool operator==(const FHairGroupsPhysics& A) const;`
- L298 _public prototype_ `void BuildDDCKey(FArchive& Ar);` — Build DDC key

#### struct `FHairSimulationSolver`  
`struct FHairSimulationSolver`  
_L302-309_
- reflection: `USTRUCT(BlueprintType)`
- L308 _public member_ `bool bEnableSimulation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "SolverSettings", meta = (ToolTip = "Enable the simulation of the groom groups/LODs if both this boolean and the one in the groom asset are true"))` — Enable the simulation for the group

#### struct `FHairSimulationForces`  
`struct FHairSimulationForces`  
_L312-327_
- reflection: `USTRUCT(BlueprintType)`
- L318 _public member_ `FVector GravityVector = FVector(0.0, 0.0, -981.0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "ExternalForces", meta = (ToolTip = "Acceleration vector in cm/s2 to be used for the gravity"))` — Acceleration vector in cm/s2 to be used for the gravity
- L322 _public member_ `float AirDrag = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "ExternalForces", meta = (ToolTip = "Coefficient between 0 and 1 to be used for the air drag"))` — Coefficient between 0 and 1 to be used for the air drag
- L326 _public member_ `FVector AirVelocity = FVector(0.0, 0.0, 0.0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "ExternalForces", meta = (ToolTip = "Velocity of the surrounding air in cm/s"))` — Velocity of the surrounding air in cm/s

#### struct `FHairSimulationConstraints`  
`struct FHairSimulationConstraints`  
_L330-365_
- reflection: `USTRUCT(BlueprintType)`
- L336 _public member_ `float BendDamping = 0.001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, AdvancedDisplay, Category = "BendConstraint", meta = (ToolTip = "Damping for the bend constraint between 0 and 1"))` — Damping for the bend constraint between 0 and 1
- L340 _public member_ `float BendStiffness = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "BendConstraint", meta = (ToolTip = "Stiffness for the bend constraint in GPa"))` — Stiffness for the bend constraint in GPa
- L344 _public member_ `float StretchDamping = 0.001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, AdvancedDisplay, Category = "StretchConstraint", meta = (ToolTip = "Damping for the stretch constraint between 0 and 1"))` — Damping for the stretch constraint between 0 and 1
- L348 _public member_ `float StretchStiffness = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "StretchConstraint", meta = (ToolTip = "Stiffness for the stretch constraint in GPa"))` — Stiffness for the stretch constraint in GPa
- L352 _public member_ `float StaticFriction = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, AdvancedDisplay, Category = "Collision Constraint", meta = (ToolTip = "Static friction used for collision against the physics asset"))` — Static friction used for collision against the physics asset
- L356 _public member_ `float KineticFriction = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, AdvancedDisplay, Category = "CollisionConstraint", meta = (ToolTip = "Kinetic friction used for collision against the physics asset"))` — Kinetic friction used for collision against the physics asset
- L360 _public member_ `float StrandsViscosity = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "CollisionConstraint", meta = (ToolTip = "Viscosity parameter between 0 and 1 that will be used for self collision"))` — Viscosity parameter between 0 and 1 that will be used for self collision
- L364 _public member_ `float CollisionRadius = 0.001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "CollisionConstraint", meta = (ToolTip = "Radius that will be used for the collision detection against the physics asset"))` — Radius that will be used for the collision detection against the physics asset

#### struct `FHairSimulationSetup`  
`struct FHairSimulationSetup`  
_L368-399_
- reflection: `USTRUCT(BlueprintType)`
- L374 _public member_ `bool bResetSimulation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "SimulationSetup", meta = (ToolTip = "Boolean to control if we want to reset trhe simulation at some point in time"))` — Reset the simulation in time
- L378 _public member_ `bool bDebugSimulation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "SimulationSetup", meta = (ToolTip = "Boolean to make the simulation strands visible"))` — Boolean to make the simulation strands visible
- L382 _public member_ `bool bLocalSimulation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "SimulationSetup", meta = (ToolTip = "Strands simulation is done in local space"))` — Strands simulation is done in local space
- L386 _public member_ `float LinearVelocityScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "SimulationSetup", meta = (ToolTip = "The amount of linear velocities sent to the local groom space from the reference bone", EditCondition = "bLocalSimulation", UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The amount of linear velocities sent to the local groom space from the reference bone
- L390 _public member_ `float AngularVelocityScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "SimulationSetup", meta = (ToolTip = "The amount of angular velocities sent to the local groom space from the reference bone", EditCondition = "bLocalSimulation", UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The amount of angular velocities sent to the local groom space from the reference bone
- L394 _public member_ `FString LocalBone = "ro` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "SimulationSetup", meta = (ToolTip = "Bone used for the simulation local space", EditCondition = "bLocalSimulation"))` — Bone used for the simulation local space
- L398 _public member_ `float TeleportDistance = 50.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "SimulationSetup", meta = (ToolTip = "Teleport distance threshold to reset the simulation"))` — Teleport distance threshold to reset the simulation

#### struct `FHairSimulationSettings`  
`struct FHairSimulationSettings`  
_L402-425_
- reflection: `USTRUCT(BlueprintType)`
- L408 _public member_ `bool bOverrideSettings = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "GroupsPhysics", meta = (ToolTip = "Boolean to control if we are going to override the groom asset physics settings"))` — Override the asset simulation settings
- L412 _public member_ `FHairSimulationSetup SimulationSetup;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "GroupsPhysics", meta = (ToolTip = "Solver Settings for the hair physics"))` — Solver settings
- L416 _public member_ `FHairSimulationSolver SolverSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "GroupsPhysics", meta = (ToolTip = "Solver Settings for the hair physics", EditCondition = "bOverrideSettings"))` — Solver settings
- L420 _public member_ `FHairSimulationForces ExternalForces;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "GroupsPhysics", meta = (ToolTip = "External Forces for the hair physics", EditCondition = "bOverrideSettings"))` — Externalk forces
- L424 _public member_ `FHairSimulationConstraints MaterialConstraints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "GroupsPhysics", meta = (ToolTip = "Material Constraints for the hair physics", EditCondition = "bOverrideSettings"))` — Material Constraints

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomAssetRendering.h` (Public)


#### struct `FHairGeometrySettings`  
`struct FHairGeometrySettings`  
_L17-38_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public prototype_ `FHairGeometrySettings();`
- L25 _public member_ `float HairWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeometrySettings", meta = (editcondition = "HairWidth_Override", ClampMin = "0.0001", UIMin = "0.001", UIMax = "1.0", SliderExponent = 6))` — Hair width (in centimeters)
- L27 _public member_ `bool HairWidth_Override = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L31 _public member_ `float HairRootScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeometrySettings", AdvancedDisplay, meta = (ClampMin = "0.0001", UIMin = "0.001", UIMax = "2.0", SliderExponent = 6))` — Scale the hair width at the root
- L35 _public member_ `float HairTipScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeometrySettings", AdvancedDisplay, meta = (ClampMin = "0.0001", UIMin = "0.001", UIMax = "2.0", SliderExponent = 6))` — Scale the hair width at the tip
- L37 _public prototype_ `bool operator==(const FHairGeometrySettings& A) const;`

#### struct `FHairShadowSettings`  
`struct FHairShadowSettings`  
_L41-64_
- reflection: `USTRUCT(BlueprintType)`
- L45 _public prototype_ `FHairShadowSettings();`
- L49 _public member_ `float HairShadowDensity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShadowSettings", AdvancedDisplay, meta = (ClampMin = "0.0001", UIMin = "0.001", UIMax = "10.0", SliderExponent = 6))` — Override the hair shadow density factor (unit less).
- L53 _public member_ `float HairRaytracingRadiusScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShadowSettings", AdvancedDisplay, meta = (ClampMin = "0.0001", UIMin = "0.001", UIMax = "10.0", SliderExponent = 6))` — Scale the hair geometry radius for ray tracing effects (e.g. shadow)
- L57 _public member_ `bool bUseHairRaytracingGeometry;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShadowSettings", AdvancedDisplay)` — Enable hair strands geomtry for raytracing
- L61 _public member_ `bool bVoxelize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShadowSettings", AdvancedDisplay)` — Enable stands voxelize for casting shadow and environment occlusion
- L63 _public prototype_ `bool operator==(const FHairShadowSettings& A) const;`

#### struct `FHairAdvancedRenderingSettings`  
`struct FHairAdvancedRenderingSettings`  
_L67-82_
- reflection: `USTRUCT(BlueprintType)`
- L71 _public prototype_ `FHairAdvancedRenderingSettings();`
- L75 _public member_ `bool bUseStableRasterization;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdvancedRenderingSettings")` — Insure the hair does not alias. When enable, group of hairs might appear thicker. Isolated hair should remain thin.
- L79 _public member_ `bool bScatterSceneLighting;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AdvancedRenderingSettings")` — Light hair with the scene color. This is used for vellus/short hair to bring light from the surrounding surface, like skin.
- L81 _public prototype_ `bool operator==(const FHairAdvancedRenderingSettings& A) const;`

#### struct `FHairGroupsRendering`  
`struct FHairGroupsRendering`  
_L85-115_
- reflection: `USTRUCT(BlueprintType)`
- L89 _public prototype_ `FHairGroupsRendering();`
- L92 _public member_ `FName MaterialSlotName;` — `UPROPERTY()`
- L96 _public member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY()` — Deprecated
- L99 _public member_ `FHairGeometrySettings GeometrySettings;` — `UPROPERTY(EditAnywhere, Category = "GeometrySettings", meta = (ToolTip = "Geometry settings"))`
- L102 _public member_ `FHairShadowSettings ShadowSettings;` — `UPROPERTY(EditAnywhere, Category = "ShadowSettings", meta = (ToolTip = "Shadow settings"))`
- L105 _public member_ `FHairAdvancedRenderingSettings AdvancedSettings;` — `UPROPERTY(EditAnywhere, Category = "MiscSettings", meta = (ToolTip = "Advanced rendering settings "))`
- L110 _public member_ `FName GroupName = NAME_None;` — `UPROPERTY(VisibleDefaultsOnly, Transient, Category=AlwaysHidden, Meta=(EditCondition=False, EditConditionHides))` — Group name to be displayed in the array list
- L113 _public prototype_ `bool operator==(const FHairGroupsRendering& A) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomBindingAsset.h` (Public)


#### struct `FGoomBindingGroupInfo`  
`struct FGoomBindingGroupInfo`  
_L28-43_
- reflection: `USTRUCT(BlueprintType)`
- L33 _public member_ `int32 RenRootCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Curve Count"))`
- L36 _public member_ `int32 RenLODCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Curve LOD"))`
- L39 _public member_ `int32 SimRootCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Guide Count"))`
- L42 _public member_ `int32 SimLODCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Info", meta = (DisplayName = "Guide LOD"))`

#### enum `EGroomBindingMeshType`  
`enum class EGroomBindingMeshType : uint8`  
_L47-51_
- reflection: `UENUM(BlueprintType)`
- desc: Enum that describes the type of mesh to bind to
- L49 _public enumerator_ `SkeletalMesh`
- L50 _public enumerator_ `GeometryCache`

#### enum `EGroomBindingAsyncProperties`  
`enum class EGroomBindingAsyncProperties : uint64`  
_L58-78_
- reflection: `UENUM()`
- L60 _public enumerator_ `None = 0`
- L61 _public enumerator_ `GroomBindingType = 1 << 0`
- L62 _public enumerator_ `Groom = 1 << 1`
- L63 _public enumerator_ `SourceSkeletalMesh = 1 << 2`
- L64 _public enumerator_ `SourceMeshRequestedLOD = 1 << 3`
- L65 _public enumerator_ `SourceMeshUsedLOD = 1 << 4`
- L66 _public enumerator_ `TargetSkeletalMesh = 1 << 5`
- L67 _public enumerator_ `TargetMeshRequestedMinLOD = 1 << 6`
- L68 _public enumerator_ `TargetMeshUsedMinLOD = 1 << 7`
- L69 _public enumerator_ `SourceGeometryCache = 1 << 8`
- L70 _public enumerator_ `TargetGeometryCache = 1 << 9`
- L71 _public enumerator_ `NumInterpolationPoints = 1 << 10`
- L72 _public enumerator_ `MatchingSection = 1 << 11`
- L73 _public enumerator_ `GroupInfos = 1 << 12`
- L74 _public enumerator_ `HairGroupResources = 1 << 13`
- L75 _public enumerator_ `HairGroupPlatformData = 1 << 14`
- L76 _public enumerator_ `TargetBindingAttribute = 1 << 15`
- L77 _public enumerator_ `All = MAX_uint64`

#### enum `EGroomBindingAsyncPropertyLockType`  
`enum class EGroomBindingAsyncPropertyLockType`  
_L82-88_
- L84 _public enumerator_ `None = 0`
- L85 _public enumerator_ `ReadOnly = 1`
- L86 _public enumerator_ `WriteOnly = 2`
- L87 _public enumerator_ `ReadWrite = 3`

#### class `FGroomBindingAsyncBuildScope`  
`class FGroomBindingAsyncBuildScope`  
_L93-104_
- desc: Any thread implicated in the build must have a valid scope to be granted access to protected properties without causing any stalls.
- L96 _public prototype_ `FGroomBindingAsyncBuildScope(const UGroomBindingAsset* Asset);`
- L97 _public prototype_ `~FGroomBindingAsyncBuildScope();`
- L98 _public prototype_ `static bool ShouldWaitOnLockedProperties(const UGroomBindingAsset* Asset);`
- L101 _private member_ `const UGroomBindingAsset* PreviousScope = nullptr;`
- L103 _private member_ `static thread_local const UGroomBindingAsset* Asset;` — Only the thread(s) compiling this asset will have full access to protected properties without causing any stalls.

#### enum `EGroomBindingAssetBuildResult`  
`enum class EGroomBindingAssetBuildResult : uint8`  
_L107-111_
- reflection: `UENUM()`
- L109 _public enumerator_ `Succeeded`
- L110 _public enumerator_ `Failed`

#### struct `FGroomBindingBuildContext`  
`struct FGroomBindingBuildContext`  
_L116-136_
- L118 _public prototype_ `FGroomBindingBuildContext() = default;`
- L120 _public prototype_ `FGroomBindingBuildContext(const FGroomBindingBuildContext&) = delete;` — Non-copyable
- L121 _public prototype_ `FGroomBindingBuildContext& operator=(const FGroomBindingBuildContext&) = delete;`
- L123 _public prototype_ `FGroomBindingBuildContext(FGroomBindingBuildContext&&) = default;` — Movable
- L124 _public prototype_ `FGroomBindingBuildContext& operator=(FGroomBindingBuildContext&&) = default;`
- L128 _public member_ `TArray<TRefCountPtr<FSkeletalMeshLODRenderData>> MeshLODReferences;` — All mesh LODs needed to build the binding are referenced here to prevent them from being streamed out during the build.
- L130 _public member_ `FOnGroomBindingAssetBuildComplete DynamicCompletionDelegate;`
- L131 _public member_ `FOnGroomBindingAssetBuildCompleteNative NativeCompletionDelegate;`
- L133 _public member_ `int32 SourceMeshLOD = INDEX_NONE;`
- L134 _public member_ `int32 TargetMeshMinLOD = INDEX_NONE;`
- L135 _public member_ `bool bReloadResource = false;`

#### class `FGroomBindingAsyncBuildWorker`  
`class FGroomBindingAsyncBuildWorker : public FNonAbandonableTask`  
_L141-162_
- inherits: `FNonAbandonableTask`
- desc: Worker used to perform async compilation.
- L144 _public member_ `UGroomBindingAsset* GroomBinding;`
- L145 _public member_ `TOptional<FGroomBindingBuildContext> BuildContext;`
- L148 _public function_ `FGroomBindingAsyncBuildWorker( UGroomBindingAsset* InGroomBinding, FGroomBindingBuildContext&& InBuildContext) : GroomBinding(InGroomBinding) , BuildContext(MoveTemp(InBuildContext))` — Initialization constructor.
- L156 _public function_ `inline TStatId GetStatId() const`
- L161 _public prototype_ `void DoWork();`

#### struct `FGroomBindingAsyncBuildTask`  
`struct FGroomBindingAsyncBuildTask : public FAsyncTask<FGroomBindingAsyncBuildWorker>`  
_L164-175_
- inherits: `FAsyncTask<FGroomBindingAsyncBuildWorker>`
- L166 _public function_ `FGroomBindingAsyncBuildTask( UGroomBindingAsset* InGroomBinding, FGroomBindingBuildContext&& InBuildContext) : FAsyncTask<FGroomBindingAsyncBuildWorker>(InGroomBinding, MoveTemp(InBuildContext)) , GroomBinding(InGroomBinding)`
- L174 _public member_ `const UGroomBindingAsset* GroomBinding;`

#### class `UGroomBindingAsset`  
`class UGroomBindingAsset : public UObject, public IInterface_AsyncCompilation`  
_L181-593_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidecategories = (Object))`
- inherits: `UObject,IInterface_AsyncCompilation`
- desc: Implements an asset that can be used to store binding information between a groom and a skeletal mesh
- L187 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGroomBindingAssetChanged);` — Notification when anything changed
- L194 _private member_ `EGroomBindingMeshType GroomBindingType = EGroomBindingMeshType::SkeletalMesh;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetGroomBindingType() or UGroomBindingAsset::SetGroomBindingType().")` — `UPROPERTY(VisibleAnywhere, BlueprintGetter = GetGroomBindingType, BlueprintSetter = SetGroomBindingType, Category = "BuildSettings")` — Type of mesh to create groom binding for
- L197 _public prototype_ `static FName GetGroomBindingTypeMemberName();`
- L198 _public prototype_ `UFUNCTION(BlueprintGetter) EGroomBindingMeshType GetGroomBindingType() const;`
- L199 _public prototype_ `UFUNCTION(BlueprintSetter) void SetGroomBindingType(EGroomBindingMeshType InGroomBindingType);` — `UFUNCTION(BlueprintGetter)`
- L205 _private member_ `TObjectPtr<UGroomAsset> Groom;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetGroom() or UGroomBindingAsset::SetGroom().")` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetGroom, BlueprintSetter = SetGroom, Category = "BuildSettings", AssetRegistrySearchable)` — Groom to bind.
- L208 _public prototype_ `static FName GetGroomMemberName();`
- L209 _public prototype_ `UFUNCTION(BlueprintGetter) UGroomAsset* GetGroom() const;`
- L210 _public prototype_ `UFUNCTION(BlueprintSetter) void SetGroom(UGroomAsset* InGroom);` — `UFUNCTION(BlueprintGetter)`
- L217 _private member_ `TObjectPtr<USkeletalMesh> SourceSkeletalMesh;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetSourceSkeletalMesh() or UGroomBindingAsset::SetSourceSkeletalMesh().")` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetSourceSkeletalMesh, BlueprintSetter = SetSourceSkeletalMesh, Category = "BuildSettings")` — Skeletal mesh on which the groom has been authored. This is optional, and used only if the hair binding is done a different mesh than the one which it has been authored
- L220 _public prototype_ `static FName GetSourceSkeletalMeshMemberName();`
- L221 _public prototype_ `UFUNCTION(BlueprintGetter) USkeletalMesh* GetSourceSkeletalMesh() const;`
- L222 _public prototype_ `UFUNCTION(BlueprintSetter) void SetSourceSkeletalMesh(USkeletalMesh* InSkeletalMesh);` — `UFUNCTION(BlueprintGetter)`
- L227 _private member_ `int32 SourceMeshRequestedLOD;` — `UE_DEPRECATED(5.5, "Please do not access this member directly; use UGroomBindingAsset::GetSourceMeshRequestedLOD() or UGroomBindingAsset::SetSourceMeshRequestedLOD().")` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetSourceMeshRequestedLOD, BlueprintSetter = SetSourceMeshRequestedLOD, Category = "BuildSettings")`
- L230 _public prototype_ `static FName GetSourceMeshRequestedLODMemberName();`
- L231 _public prototype_ `UFUNCTION(BlueprintGetter) int32 GetSourceMeshRequestedLOD() const;`
- L232 _public prototype_ `UFUNCTION(BlueprintSetter) void SetSourceMeshRequestedLOD(int32 InSourceMeshRequestedLOD);` — `UFUNCTION(BlueprintGetter)`
- L237 _private member_ `int32 SourceMeshUsedLOD = INDEX_NONE;` — `UE_DEPRECATED(5.5, "Please do not access this member directly; use UGroomBindingAsset::GetSourceMeshUsedLOD().")` — `UPROPERTY(VisibleAnywhere, BlueprintGetter = GetSourceMeshUsedLOD, Category = "BuildSettings")`
- L239 _private prototype_ `UFUNCTION(BlueprintSetter) void SetSourceMeshUsedLOD(int32 InSourceMeshUsedLOD);`
- L241 _public prototype_ `static FName GetSourceMeshUsedLODMemberName();`
- L242 _public prototype_ `UFUNCTION(BlueprintGetter) int32 GetSourceMeshUsedLOD() const;`
- L248 _private member_ `TObjectPtr<USkeletalMesh> TargetSkeletalMesh;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetTargetSkeletalMesh() or UGroomBindingAsset::SetTargetSkeletalMesh().")` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetTargetSkeletalMesh, BlueprintSetter = SetTargetSkeletalMesh, Category = "BuildSettings")` — Skeletal mesh on which the groom is attached to.
- L251 _public prototype_ `static FName GetTargetSkeletalMeshMemberName();`
- L252 _public prototype_ `UFUNCTION(BlueprintGetter) USkeletalMesh* GetTargetSkeletalMesh() const;`
- L253 _public prototype_ `UFUNCTION(BlueprintSetter) void SetTargetSkeletalMesh(USkeletalMesh* InSkeletalMesh);` — `UFUNCTION(BlueprintGetter)`
- L258 _private member_ `int32 TargetMeshRequestedMinLOD;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetTargetMeshRequestedMinLOD() or UGroomBindingAsset::SetTargetMeshRequestedMinLOD().")` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetTargetMeshRequestedMinLOD, BlueprintSetter = SetTargetMeshRequestedMinLOD, Category = "BuildSettings")`
- L261 _public prototype_ `static FName GetTargetMeshRequestedMinLODMemberName();`
- L262 _public prototype_ `UFUNCTION(BlueprintGetter) int32 GetTargetMeshRequestedMinLOD() const;`
- L263 _public prototype_ `UFUNCTION(BlueprintSetter) void SetTargetMeshRequestedMinLOD(int32 InTargetMeshRequestedMinLOD);` — `UFUNCTION(BlueprintGetter)`
- L268 _private member_ `int32 TargetMeshUsedMinLOD = INDEX_NONE;` — `UE_DEPRECATED(5.5, "Please do not access this member directly; use UGroomBindingAsset::GetTargetMeshUsedMinLOD().")` — `UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTargetMeshUsedMinLOD, Category = "BuildSettings")`
- L270 _private prototype_ `UFUNCTION(BlueprintSetter) void SetTargetMeshUsedMinLOD(int32 InTargetMeshUsedMinLOD);`
- L272 _public prototype_ `static FName GetTargetMeshUsedMinLODMemberName();`
- L273 _public prototype_ `UFUNCTION(BlueprintGetter) int32 GetTargetMeshUsedMinLOD() const;`
- L278 _private member_ `TObjectPtr<UGeometryCache> SourceGeometryCache;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetSourceGeometryCache() or UGroomBindingAsset::SetSourceGeometryCache().")` — `UPROPERTY(VisibleAnywhere, BlueprintGetter = GetSourceGeometryCache, BlueprintSetter = SetSourceGeometryCache, Category = "BuildSettings")`
- L281 _public prototype_ `static FName GetSourceGeometryCacheMemberName();`
- L282 _public prototype_ `UFUNCTION(BlueprintGetter) UGeometryCache* GetSourceGeometryCache() const;`
- L283 _public prototype_ `UFUNCTION(BlueprintSetter) void SetSourceGeometryCache(UGeometryCache* InGeometryCache);` — `UFUNCTION(BlueprintGetter)`
- L288 _private member_ `TObjectPtr<UGeometryCache> TargetGeometryCache;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetTargetGeometryCache() or UGroomBindingAsset::SetTargetGeometryCache().")` — `UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTargetGeometryCache, BlueprintSetter = SetTargetGeometryCache, Category = "BuildSettings")`
- L291 _public prototype_ `static FName GetTargetGeometryCacheMemberName();`
- L292 _public prototype_ `UFUNCTION(BlueprintGetter) UGeometryCache* GetTargetGeometryCache() const;`
- L293 _public prototype_ `UFUNCTION(BlueprintSetter) void SetTargetGeometryCache(UGeometryCache* InGeometryCache);` — `UFUNCTION(BlueprintGetter)`
- L299 _private member_ `int32 NumInterpolationPoints = 100;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetNumInterpolationPoints() or UGroomBindingAsset::SetNumInterpolationPoints().")` — `UPROPERTY(VisibleAnywhere, BlueprintGetter = GetNumInterpolationPoints, BlueprintSetter = SetNumInterpolationPoints, Category = "BuildSettings")` — Number of points used for the rbf interpolation
- L302 _public prototype_ `static FName GetNumInterpolationPointsMemberName();`
- L303 _public prototype_ `UFUNCTION(BlueprintGetter) int32 GetNumInterpolationPoints() const;`
- L304 _public prototype_ `UFUNCTION(BlueprintSetter) void SetNumInterpolationPoints(int32 InNumInterpolationPoints);` — `UFUNCTION(BlueprintGetter)`
- L310 _private member_ `int32 MatchingSection = 0;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetMatchingSection() or UGroomBindingAsset::SetMatchingSection().")` — `UPROPERTY(VisibleAnywhere, BlueprintGetter = GetMatchingSection, BlueprintSetter = SetMatchingSection, Category = "BuildSettings")` — Number of points used for the rbf interpolation
- L313 _public prototype_ `static FName GetMatchingSectionMemberName();`
- L314 _public prototype_ `UFUNCTION(BlueprintGetter) int32 GetMatchingSection() const;`
- L315 _public prototype_ `UFUNCTION(BlueprintSetter) void SetMatchingSection(int32 InMatchingSection);` — `UFUNCTION(BlueprintGetter)`
- L321 _private member_ `FName TargetBindingAttribute = NAME_None;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetTargetBindingAttribute() or UGroomBindingAsset::SetTargetBindingAttribute().")` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetTargetBindingAttribute, BlueprintSetter = SetTargetBindingAttribute, Category = "BuildSettings")` — Optional binding attribute name on target skeletal mesh, to filter out which triangles are valid to bind groom to
- L324 _public prototype_ `static FName GetTargetBindingAttributeMemberName();`
- L325 _public prototype_ `UFUNCTION(BlueprintGetter) FName GetTargetBindingAttribute() const;`
- L326 _public prototype_ `UFUNCTION(BlueprintSetter) void SetTargetBindingAttribute(FName InAttributeName);` — `UFUNCTION(BlueprintGetter)`
- L331 _private member_ `TArray<FGoomBindingGroupInfo> GroupInfos;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetGroupInfos() or UGroomBindingAsset::SetGroupInfos().")` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintGetter = GetGroupInfos, BlueprintSetter = SetGroupInfos, Category = "HairGroups", meta = (DisplayName = "Group"))`
- L334 _public prototype_ `static FName GetGroupInfosMemberName();`
- L335 _public prototype_ `UFUNCTION(BlueprintGetter) const TArray<FGoomBindingGroupInfo>& GetGroupInfos() const;`
- L336 _public prototype_ `UFUNCTION(BlueprintSetter) void SetGroupInfos(const TArray<FGoomBindingGroupInfo>& InGroupInfos);` — `UFUNCTION(BlueprintGetter)`
- L337 _public prototype_ `TArray<FGoomBindingGroupInfo>& GetGroupInfos();` — `UFUNCTION(BlueprintGetter)` — `UFUNCTION(BlueprintSetter)`
- L346 _public typedef_ `typedef TArray<FHairGroupResource> FHairGroupResources;`
- L350 _private member_ `FHairGroupResources HairGroupResources;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetHairGroupResources() or UGroomBindingAsset::SetHairGroupResources().")`
- L353 _public prototype_ `static FName GetHairGroupResourcesMemberName();`
- L354 _public prototype_ `FHairGroupResources& GetHairGroupResources();`
- L355 _public prototype_ `const FHairGroupResources& GetHairGroupResources() const;`
- L356 _public prototype_ `void SetHairGroupResources(FHairGroupResources InHairGroupResources);`
- L373 _private member_ `TQueue<FHairGroupResource> HairGroupResourcesToDelete;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetHairGroupPlatformData().")` — Queue of resources which needs to be deleted. This queue is needed for keeping valid pointer on the group resources when the binding asset is recomputed
- L381 _private member_ `TQueue<FHairGroupPlatformDataArray*> HairGroupPlatformDataToDelete;`
- L385 _private member_ `TArray<FHairGroupPlatformData> HairGroupsPlatformData;` — `UE_DEPRECATED(5.3, "Please do not access this member directly; use UGroomBindingAsset::GetHairGroupPlatformData().")` — Platform data for each hair groups
- L388 _public prototype_ `void AddHairGroupResourcesToDelete(FHairGroupResource& In);`
- L389 _public prototype_ `bool RemoveHairGroupResourcesToDelete(FHairGroupResource& Out);`
- L391 _public prototype_ `static FName GetHairGroupPlatformDataMemberName();`
- L392 _public prototype_ `const TArray<FHairGroupPlatformData>& GetHairGroupsPlatformData() const;`
- L393 _public prototype_ `TArray<FHairGroupPlatformData>& GetHairGroupsPlatformData();`
- L397 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L398 _public prototype_ `virtual void PostLoad() override;`
- L399 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L400 _public prototype_ `virtual void PostSaveRoot(FObjectPostSaveRootContext ObjectSaveContext) override;`
- L401 _public prototype_ `virtual void BeginDestroy() override;`
- L402 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L404 _public prototype_ `static bool IsCompatible(const USkeletalMesh* InSkeletalMesh, const UGroomBindingAsset* InBinding, bool bIssueWarning);`
- L405 _public prototype_ `static bool IsCompatible(const UGeometryCache* InGeometryCache, const UGroomBindingAsset* InBinding, bool bIssueWarning);`
- L406 _public prototype_ `static bool IsCompatible(const UGroomAsset* InGroom, const UGroomBindingAsset* InBinding, bool bIssueWarning);`
- L407 _public prototype_ `static bool IsBindingAssetValid(const UGroomBindingAsset* InBinding, bool bIsBindingReloading, bool bIssueWarning);`
- L410 _public prototype_ `bool HasValidTarget() const;` — Returns true if the target is not null and matches the binding type
- L413 _public prototype_ `FName GetAssetPathName(int32 LODIndex = -1);` — Helper function to return the asset path name, optionally joined with the LOD index if LODIndex > -1.
- L414 _public function_ `uint32 GetAssetHash() const`
- L417 _public function_ `FOnGroomBindingAssetChanged& GetOnGroomBindingAssetChanged()`
- L420 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Part of UObject interface
- L425 _public prototype_ `void InitResource();` — Initialize resources.
- L428 _public prototype_ `void UpdateResource();` — Update resources.
- L431 _public prototype_ `void ReleaseResource(bool bResetLoadedSize);` — Release the hair strands resource.
- L440 _public prototype_ `void StreamInForCPUAccess(bool bWait);` — Stream in all of this binding's streamable resources and make them accessible from the CPU. This is only needed for advanced use cases involving editing grooms or binding data. @param bWait If true, this call will block until the resources have been streamed in
- L442 _public prototype_ `void Reset();`
- L445 _public function_ `bool IsValid() const` — Return true if the binding asset is valid, i.e., correctly built and loaded.
- L449 _private member_ `std::atomic<uint64> AccessedProperties;` — Used as a bit-field indicating which properties are read by async compilation.
- L451 _private member_ `std::atomic<uint64> ModifiedProperties;` — Used as a bit-field indicating which properties are written to by async compilation.
- L453 _private member_ `TUniquePtr<FGroomBindingAsyncBuildTask> AsyncTask;` — Holds the pointer to an async task if one exists.
- L455 _private function_ `bool IsAsyncTaskComplete() const`
- L460 _private function_ `bool TryCancelAsyncTasks()`
- L473 _private prototype_ `void ExecuteCacheDerivedDatas(FGroomBindingBuildContext& Context);`
- L474 _private prototype_ `void FinishCacheDerivedDatas(FGroomBindingBuildContext& Context);`
- L475 _private prototype_ `int32 GetClampedSourceMeshLOD(const ITargetPlatform* TargetPlatform) const;`
- L476 _private prototype_ `int32 GetClampedTargetMeshMinLOD(const ITargetPlatform* TargetPlatform) const;`
- L480 _public function_ `virtual bool IsCompiling() const override` — IInterface_AsyncCompilation begin
- L486 _public member_ `FOnGroomBindingAssetChanged OnGroomBindingAssetChanged;`
- L488 _public prototype_ `void RecreateResources();`
- L490 _public prototype_ `void ChangeFeatureLevel(ERHIFeatureLevel::Type PendingFeatureLevel);` — `UE_DEPRECATED(5.8, "Use ChangeShaderPlatform(EShaderPlatform) instead.")`
- L492 _public prototype_ `void ChangePlatformLevel(ERHIFeatureLevel::Type PendingFeatureLevel);` — `UE_DEPRECATED(5.8, "Use ChangeShaderPlatform(EShaderPlatform) instead.")`
- L493 _public prototype_ `void ChangeShaderPlatform(EShaderPlatform InShaderPlatform);`
- L496 _private prototype_ `void WaitUntilAsyncPropertyReleased(EGroomBindingAsyncProperties AsyncProperties, EGroomBindingAsyncPropertyLockType LockType) const;`
- L497 _private function_ `void AcquireAsyncProperty(uint64 AsyncProperties = MAX_uint64, EGroomBindingAsyncPropertyLockType LockType = EGroomBindingAsyncPropertyLockType::ReadWrite)`
- L510 _private function_ `void ReleaseAsyncProperty(uint64 AsyncProperties = MAX_uint64, EGroomBindingAsyncPropertyLockType LockType = EGroomBindingAsyncPropertyLockType::ReadWrite)`
- L523 _private prototype_ `static void FlushRenderingCommandIfUsed(const UGroomBindingAsset* In);`
- L536 _public prototype_ `void Build(FOnGroomBindingAssetBuildComplete CompletionDelegate);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Build/rebuild a binding asset. Avoid calling Build again while a build is already in progress on this asset, as this will cause the Game Thread to block until the earlier build is finished. Similarly, the Game Thread will block for a short time if a Groom Component is already using this binding asset, so if performance is critical avoid calling Build on bindings that are in use.
- L537 _public prototype_ `void Build(const FOnGroomBindingAssetBuildCompleteNative& CompletionDelegate = FOnGroomBindingAssetBuildCompleteNative());`
- L538 _public prototype_ `void Build(const FOnGroomBindingAssetBuildComplete& DynamicCompletionDelegate, const FOnGroomBindingAssetBuildCompleteNative& NativeCompletionDelegate);`
- L541 _public prototype_ `void BeginCacheDerivedDatas( const FOnGroomBindingAssetBuildComplete& DynamicCompletionDelegate = FOnGroomBindingAssetBuildComplete(), const FOnGroomBindingAssetBuildCompleteNative& NativeCompletionDelegate = FOnGroomBindingAssetBuildCompleteNative());` — Internal use only
- L545 _public prototype_ `bool HasAnyDependenciesCompiling() const;`
- L548 _private prototype_ `bool TryInitializeContextForMeshes(FGroomBindingBuildContext& OutContext) const;`
- L554 _public member_ `TObjectPtr<class UThumbnailInfo> ThumbnailInfo;` — `UPROPERTY(VisibleAnywhere, Instanced, AdvancedDisplay, Category = Thumbnail)` — Information for thumbnail rendering
- L556 _public prototype_ `virtual void BeginCacheForCookedPlatformData(const ITargetPlatform* TargetPlatform) override;`
- L557 _public prototype_ `virtual void ClearAllCachedCookedPlatformData() override;`
- L559 _public prototype_ `TArray<FHairGroupPlatformData>* GetCachedCookedPlatformData(const ITargetPlatform* TargetPlatform);`
- L561 _public prototype_ `void InvalidateBinding();`
- L562 _public prototype_ `void InvalidateBinding(class USkeletalMesh*);`
- L576 _public member_ `TArray<FCachedCookedPlatformData*> CachedCookedPlatformDatas;`
- L578 _public prototype_ `void RegisterGroomDelegates();`
- L579 _public prototype_ `void UnregisterGroomDelegates();`
- L580 _public prototype_ `void RegisterSkeletalMeshDelegates();`
- L581 _public prototype_ `void UnregisterSkeletalMeshDelegates();`
- L583 _public member_ `TArray<FString> CachedDerivedDataKey;`
- L586 _public member_ `EShaderPlatform CachedResourceShaderPlatform = SP_NumPlatforms;`
- L588 _public member_ `bool bIsValid = false;`
- L589 _public member_ `uint32 AssetNameHash = 0;`

#### struct `UGroomBindingAsset::FHairGroupResource`  
`struct FHairGroupResource`  
_L340-345_
- desc: GPU and CPU binding data for both simulation and rendering.
- L342 _public member_ `FHairStrandsRestRootResource* SimRootResources = nullptr;`
- L343 _public member_ `FHairStrandsRestRootResource* RenRootResources = nullptr;`
- L344 _public member_ `TArray<FHairStrandsRestRootResource*> CardsRootResources;`

#### struct `UGroomBindingAsset::FHairGroupPlatformData`  
`struct FHairGroupPlatformData`  
_L359-367_
- desc: Binding bulk data
- L361 _public member_ `TArray<FHairStrandsRootBulkData> SimRootBulkDatas;`
- L362 _public member_ `TArray<FHairStrandsRootBulkData> RenRootBulkDatas;`
- L363 _public member_ `TArray<TArray<FHairStrandsRootBulkData>> CardsRootBulkDatas;`
- L366 _public member_ `int32 TargetMeshMinLOD = -1;` — The minimum mesh LOD that this binding data can support

#### struct `UGroomBindingAsset::FHairGroupPlatformDataArray`  
`struct FHairGroupPlatformDataArray`  
_L377-380_
- desc: Queue of data which needs to be deleted. This queue is needed for keeping valid pointer on the group resources when the binding asset is recomputed
- L379 _public member_ `TArray<FHairGroupPlatformData> Data;`

#### struct `UGroomBindingAsset::FCachedCookedPlatformData`  
`struct FCachedCookedPlatformData`  
_L564-574_
- L567 _public member_ `TArray<FString> GroupDerivedDataKeys;` — Actual DDC key and platform data
- L568 _public member_ `TArray<FHairGroupPlatformData> GroupPlatformDatas;`
- L571 _public member_ `TArray<FString> GroupDerivedDataKeys_Query;` — DDC key without source/target MeshLOD and requested MeshLOD value
- L572 _public member_ `int32 SourceMeshLOD = INDEX_NONE;`
- L573 _public member_ `int32 TargetMeshMinLOD = INDEX_NONE;`

#### class `UGroomBindingAssetList`  
`class UGroomBindingAssetList : public UObject`  
_L596-602_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidecategories = (Object))`
- inherits: `UObject`
- L601 _public member_ `TArray<TObjectPtr<UGroomBindingAsset>> Bindings;` — `UPROPERTY(EditAnywhere, Transient, EditFixedSize, Category = "Bindings")`

#### struct `FGroomBindingAssetMemoryStats`  
`struct FGroomBindingAssetMemoryStats`  
_L604-619_
- L612 _public member_ `FStats CPU;`
- L613 _public member_ `FStats GPU;`
- L615 _public prototype_ `static FGroomBindingAssetMemoryStats Get(const UGroomBindingAsset::FHairGroupPlatformData& InCPU, const UGroomBindingAsset::FHairGroupResource& InGPU);`
- L616 _public prototype_ `void Accumulate(const FGroomBindingAssetMemoryStats& In);`
- L617 _public prototype_ `uint32 GetTotalCPUSize() const;`
- L618 _public prototype_ `uint32 GetTotalGPUSize() const;`

#### struct `FGroomBindingAssetMemoryStats::FStats`  
`struct FStats`  
_L606-611_
- L608 _public member_ `uint32 Guides = 0;`
- L609 _public member_ `uint32 Strands= 0;`
- L610 _public member_ `uint32 Cards = 0;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L80 _prototype_ `ENUM_CLASS_FLAGS(EGroomBindingAsyncProperties);`
- L90 _prototype_ `ENUM_CLASS_FLAGS(EGroomBindingAsyncPropertyLockType);`
- L113 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGroomBindingAssetBuildComplete, UGroomBindingAsset*, GroomBinding, EGroomBindingAssetBuildResult, Result);`
- L113 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGroomBindingAssetBuildComplete, UGroomBindingAsset*, GroomBinding, EGroomBindingAssetBuildResult, Result);`
- L114 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGroomBindingAssetBuildCompleteNative, UGroomBindingAsset*, EGroomBindingAssetBuildResult);`
- L114 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGroomBindingAssetBuildCompleteNative, UGroomBindingAsset*, EGroomBindingAssetBuildResult);`
- L187 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGroomBindingAssetChanged);` — Notification when anything changed

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomBindingBuilder.h` (Public)


#### struct `FGroomBindingBuilder`  
`struct FGroomBindingBuilder`  
_L24-74_
- L53 _public prototype_ `static FString GetVersion();`
- L57 _public prototype_ `static bool BuildBinding(UGroomBindingAsset* BindingAsset, bool bInitResource);` — `UE_DEPRECATED(5.4, "Please do not access this funciton; but rather call BindingAsset->CacheDerivedDatas()")` — Build binding asset data
- L61 _public prototype_ `static bool BuildBinding(UGroomBindingAsset* BindingAsset, uint32 InGroupIndex);` — `UE_DEPRECATED(5.4, "Please do not access this funciton; but rather call BindingAsset->CacheDerivedDatas()")` — Build binding asset data
- L66 _public prototype_ `static bool BuildBinding( const FInput& In, uint32 InGroupIndex, const ITargetPlatform* TargetPlatform, UGroomBindingAsset::FHairGroupPlatformData& Out);` — Build binding asset data The caller must ensure that the referenced mesh LODs stay loaded until this function returns.
- L73 _public prototype_ `static void GetRootData(FHairStrandsRootData& Out, const FHairStrandsRootBulkData& In);` — Extract root data from bulk data

#### struct `FGroomBindingBuilder::FInput`  
`struct FInput`  
_L26-51_
- L28 _public prototype_ `FInput() = default;`
- L29 _public prototype_ `FInput(UGroomBindingAsset* BindingAsset, const ITargetPlatform* TargetPlatform, int32 InSourceMeshLOD, int32 InTargetMeshMinLOD);`
- L31 _public member_ `EGroomBindingMeshType BindingType = EGroomBindingMeshType::SkeletalMesh;`
- L32 _public member_ `int32 NumInterpolationPoints = 0;`
- L33 _public member_ `int32 MatchingSection = 0;`
- L34 _public member_ `FName TargetBindingAttribute = NAME_None;`
- L39 _public member_ `int32 SourceMeshLOD = INDEX_NONE;` — These must be initialized to valid LODs. When binding to a geometry cache, they must be set to 0.
- L40 _public member_ `int32 TargetMeshMinLOD = INDEX_NONE;`
- L42 _public member_ `bool bHasValidTarget = false;`
- L43 _public member_ `UGroomAsset* GroomAsset = nullptr;`
- L44 _public member_ `USkeletalMesh* SourceSkeletalMesh = nullptr;`
- L45 _public member_ `USkeletalMesh* TargetSkeletalMesh = nullptr;`
- L46 _public member_ `UGeometryCache* SourceGeometryCache = nullptr;`
- L47 _public member_ `UGeometryCache* TargetGeometryCache = nullptr;`
- L50 _public member_ `bool bForceUseRunningPlatform = false;` — This is needed to work around a known deadlock issue

#### struct `GroomBinding_RBFWeighting::FPointsSampler`  
`struct FPointsSampler`  
_L78-96_
- L80 _public prototype_ `FPointsSampler(TArray<bool>& ValidPoints, const FVector3f* PointPositions, const int32 NumSamples);`
- L83 _public prototype_ `void BuildPositions(const FVector3f* PointPositions);` — Build the sample position from the sample indices
- L86 _public prototype_ `void FurthestPoint(const int32 NumPoints, const FVector3f* PointPositions, const uint32 SampleIndex, TArray<bool>& ValidPoints, TArray<float>& PointsDistance);` — Compute the furthest point
- L89 _public prototype_ `int32 StartingPoint(const TArray<bool>& ValidPoints, int32& NumPoints) const;` — Compute the starting point
- L92 _public member_ `TArray<uint32> SampleIndices;` — List of sampled points
- L95 _public member_ `TArray<FVector3f> SamplePositions;` — List of sampled positions

#### struct `GroomBinding_RBFWeighting::FWeightsBuilder`  
`struct FWeightsBuilder`  
_L99-112_
- L101 _public prototype_ `FWeightsBuilder(const uint32 NumRows, const uint32 NumColumns, const FVector3f* SourcePositions, const FVector3f* TargetPositions, const bool bLocalSpace = false);`
- L105 _public prototype_ `void ComputeWeights(const uint32 NumRows, const uint32 NumColumns);` — Compute the weights by inverting the matrix
- L108 _public member_ `TArray<float> MatrixEntries;` — Entries in the dense structure
- L111 _public member_ `TArray<float> InverseEntries;` — Entries of the matrix inverse

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Groom` (scope `UE`)
- L21 _prototype_ `bool IsRBFLocalSpaceEnabled();` (scope `UE::Groom`)
- L76 _namespace_ `namespace GroomBinding_RBFWeighting`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomBindingCompiler.h` (Public)


#### class `FGroomBindingCompilingManager`  
`class FGroomBindingCompilingManager : public IAssetCompilingManager`  
_L18-104_
- inherits: `IAssetCompilingManager`
- L21 _public prototype_ `static FGroomBindingCompilingManager& Get();`
- L26 _public prototype_ `bool IsAsyncCompilationEnabled() const;` — Returns true if the feature is currently activated.
- L31 _public prototype_ `int32 GetNumRemainingJobs() const;` — Returns the number of outstanding compilations.
- L36 _public prototype_ `void AddGroomBindings(TArrayView<UGroomBindingAsset* const> InGroomBindingAssets);` — Adds groom binding assets compiled asynchronously so they are monitored.
- L41 _public prototype_ `void AddGroomBindingsWithPendingDependencies(TArrayView<UGroomBindingAsset* const> InGroomBindingAssets);` — Register groom binding assets to compile once their dependencies are finished compiling.
- L46 _public prototype_ `void FinishCompilation(TArrayView<UGroomBindingAsset* const> InGroomBindingAssets);` — Blocks until completion of the requested groom binding assets.
- L51 _public prototype_ `void FinishAllCompilation() override;` — Blocks until completion of all async groom binding asset compilation.
- L56 _public prototype_ `bool IsAsyncCompilationAllowed(UGroomBindingAsset* InGroomBindingAsset) const;` — Returns if asynchronous compilation is allowed for this groom binding asset.
- L61 _public prototype_ `EQueuedWorkPriority GetBasePriority(UGroomBindingAsset* InGroomBindingAsset) const;` — Returns the priority at which the given groom binding asset should be scheduled.
- L66 _public prototype_ `FQueuedThreadPool* GetThreadPool() const;` — Returns the threadpool where groom binding asset compilation should be scheduled.
- L71 _public prototype_ `void Shutdown() override;` — Cancel any pending work and blocks until it is safe to shut down.
- L74 _private prototype_ `FGroomBindingCompilingManager();`
- L76 _private prototype_ `FName GetAssetTypeName() const override;`
- L77 _private prototype_ `FTextFormat GetAssetNameFormat() const override;`
- L78 _private prototype_ `TArrayView<FName> GetDependentTypeNames() const override;`
- L79 _private prototype_ `int32 GetNumRemainingAssets() const override;`
- L80 _private prototype_ `void ProcessAsyncTasks(bool bLimitExecutionTime = false) override;`
- L82 _private prototype_ `void FinishCompilationForObjects(TArrayView<UObject* const> InObjects) override;`
- L86 _private member_ `bool bHasShutdown = false;`
- L87 _private member_ `TSet<UGroomBindingAsset*> GroomBindingWithPendingDependencies;`
- L88 _private member_ `TSet<UGroomBindingAsset*> RegisteredGroomBindingAssets;`
- L89 _private member_ `TMultiMap<class USkeletalMesh*, UGroomBindingAsset*> RegisteredSkeletalMeshes;`
- L90 _private member_ `TMultiMap<class UGroomAsset*, UGroomBindingAsset*> RegisteredGroomAssets;`
- L91 _private member_ `FAsyncCompilationNotification Notification;`
- L92 _private prototype_ `void FinishCompilationsForGame();`
- L93 _private prototype_ `void Reschedule();`
- L94 _private prototype_ `void ProcessGroomBindingAssets(bool bLimitExecutionTime, int32 MinBatchSize = 1);`
- L95 _private prototype_ `void UpdateCompilationNotification();`
- L97 _private prototype_ `void AttachDependencies(UGroomBindingAsset* GroomBindingAsset);`
- L98 _private prototype_ `void DetachDependencies(UGroomBindingAsset* GroomBindingAsset);`
- L99 _private prototype_ `void SchedulePendingCompilations();`
- L100 _private prototype_ `void PostCompilation(UGroomBindingAsset* GroomBindingAsset);`
- L101 _private prototype_ `void PostCompilation(TArrayView<UGroomBindingAsset* const> InGroomBindingAssets);`
- L102 _private prototype_ `void OnPostReachabilityAnalysis();`
- L103 _private member_ `FDelegateHandle PostReachabilityAnalysisHandle;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomBlueprintLibrary.h` (Public)


#### class `UGroomBlueprintLibrary`  
`class UGroomBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L17-93_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GroomLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L31 _public prototype_ `static UGroomBindingAsset* CreateNewGroomBindingAssetWithPath( const FString& InDesiredPackagePath, UGroomAsset* InGroomAsset, USkeletalMesh* InSkeletalMesh, int32 InNumInterpolationPoints = 100, USkeletalMesh* InSourceSkeletalMeshForTransfer = nullptr, int32 InMatchingSection = 0);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Create a new groom binding asset within the contents space of the project. @param InDesiredPackagePath The package path to use for the groom binding @param InGroomAsset Groom asset for binding @param InSkeletalMesh Skeletal mesh on which the groom should be bound to @param InNumInterpolationPoints Number of point used for RBF constraint (if used) @param InSourceSkeletalMeshForTransfer Skeletal mesh on which the groom was authored. This should be used only if the skeletal mesh on which the groom is attached to, does not match the rest pose of the groom
- L47 _public prototype_ `static UGroomBindingAsset* CreateNewGroomBindingAsset( UGroomAsset* InGroomAsset, USkeletalMesh* InSkeletalMesh, int32 InNumInterpolationPoints = 100, USkeletalMesh* InSourceSkeletalMeshForTransfer = nullptr, int32 InMatchingSection = 0);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Create a new groom binding asset within the contents space of the project. The asset name will be auto generated based on the groom asset name and the skeletal asset name @param InGroomAsset Groom asset for binding @param InSkeletalMesh Skeletal mesh on which the groom should be bound to @param InNumInterpolationPoints (Optional) Number of point used for RBF constraint @param InSourceSkeletalMeshForTransfer  (Optional) Skeletal mesh on which the groom was authored. This should be used only if the skeletal mesh on which the groom is attached to, does not match the rest pose of the groom
- L63 _public prototype_ `static UGroomBindingAsset* CreateNewGeometryCacheGroomBindingAssetWithPath( const FString& DesiredPackagePath, UGroomAsset* GroomAsset, UGeometryCache* GeometryCache, int32 NumInterpolationPoints = 100, UGeometryCache* SourceGeometryCacheForTransfer = nullptr, int32 MatchingSection = 0);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Create a new groom binding asset within the contents space of the project. @param DesiredPackagePath The package path to use for the groom binding @param GroomAsset Groom asset for binding @param SkeletalMesh Skeletal mesh on which the groom should be bound to @param NumInterpolationPoints Number of point used for RBF constraint (if used) @param SourceSkeletalMeshForTransfer Skeletal mesh on which the groom was authored. This should be used only if the skeletal mesh on which the groom is attached to, does not match the rest pose of the groom
- L79 _public prototype_ `static UGroomBindingAsset* CreateNewGeometryCacheGroomBindingAsset( UGroomAsset* GroomAsset, UGeometryCache* GeometryCache, int32 NumInterpolationPoints = 100, UGeometryCache* SourceGeometryCacheForTransfer = nullptr, int32 MatchingSection = 0);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Create a new groom binding asset within the contents space of the project. The asset name will be auto generated based on the groom asset name and the skeletal asset name @param GroomAsset Groom asset for binding @param SkeletalMesh Skeletal mesh on which the groom should be bound to @param NumInterpolationPoints (Optional) Number of point used for RBF constraint @param SourceSkeletalMeshForTransfer  (Optional) Skeletal mesh on which the groom was authored. This should be used only if the skeletal mesh on which the groom is attached to, does not match the rest pose of the groom
- L92 _public prototype_ `static bool IsHairStrandsSupportedInWorld(const UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Groom", meta = (WorldContext="WorldContextObject"))` — Check for strands support in the world of a given Actor Component @param InWorld The world to check @return true if strands are going to be rendered for the world's scene and false otherwise

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomBuilder.h` (Public)


#### struct `FHairStrandsVoxelData`  
`struct FHairStrandsVoxelData`  
_L32-50_
- L34 _public member_ `static const uint8 InvalidGroupIndex = 0xFF;`
- L42 _public member_ `FVector3f MinBound;`
- L43 _public member_ `FVector3f MaxBound;`
- L44 _public member_ `FIntVector Resolution;`
- L45 _public member_ `TArray<FData> Datas;`
- L48 _public prototype_ `FData GetData(const FVector3f& P) const;` — Return the (closest) FData corresponding to position P
- L49 _public function_ `bool IsValid() const`

#### struct `FHairStrandsVoxelData::FData`  
`struct FData`  
_L35-40_
- L37 _public member_ `FVector3f BaseColor;`
- L38 _public member_ `float Roughness;`
- L39 _public member_ `uint8 GroupIndex;`

#### struct `FGroomBuilder`  
`struct FGroomBuilder`  
_L59-129_
- desc: HairDescription -> HairDescriptionGroups (HairStrandsRawData) -> HairStrandsData -> HairStrandsBulkData* -> HairStrandsInterpolationData ->HairStrandsInterpolationBulkData* -> HairStrandsClusterData* * Data used at runtime. Other type of data are intermediate data used only during building/within the editor
- L61 _public prototype_ `static FString GetVersion();`
- L64 _public prototype_ `static bool BuildHairDescriptionGroups( const FHairDescription& HairDescription, FHairDescriptionGroups& Out, const bool bAllowAddEndControlPoint = true);` — 1. Build hair *group* description based on the hair description. This builds HairStrandsRawData.
- L70 _public prototype_ `static void BuildData( const FHairDescriptionGroup& InHairDescriptionGroup, const FHairGroupsInterpolation& InSettings, FHairGroupInfo& OutGroupInfo, FHairStrandsDatas& OutStrands, FHairStrandsDatas& OutGuides, const bool bAllowCurveReordering = true, const bool bApplyDecimation = true, const bool bBuildSourceMapping = false);` — 2.a Build FHairStrandsDatas from HairDescriptionGroups(HairStrandsRawData) and DecimationSettings (Strands / Guides)
- L80 _public prototype_ `static void BuildData( const FHairDescriptionGroup& InHairDescriptionGroup, const FHairGroupsInterpolation& InSettings, FHairStrandsDatas& OutStrands, FHairStrandsDatas& OutGuides, const bool bAllowCurveReordering = true, const bool bApplyDecimation = true, const bool bBuildSourceMapping = false);`
- L91 _public prototype_ `static void BuildData(const FHairStrandsRawDatas& In, FHairStrandsDatas& Out);` — `UE_DEPRECATED(5.6, "Please, no longer use this build function, as it does not contains certain build steps (decimation/shuffling)")` — 2.b Build FHairStrandsDatas from a FHairStrandsRawDatas (Strands / Guides)
- L94 _public prototype_ `static void BuildBulkData( const FHairGroupInfo& InInfo, const FHairStrandsDatas& InData, FHairStrandsBulkData& OutBulkData, bool bAllowCompression);` — 3. Build bulk data from a FHairStrandsDatas (Strands / Guides)
- L101 _public prototype_ `static void BuildInterplationData( const FHairGroupInfo& InInfo, const FHairStrandsDatas& InRenData, const FHairStrandsDatas& InSimData, const FHairInterpolationSettings& InInterpolationSettings, FHairStrandsInterpolationDatas& OutInterpolationData);` — 4. Build interplation data based on the hairStrands data
- L109 _public prototype_ `static void BuildInterplationBulkData( const FHairStrandsDatas& InSimData, const FHairStrandsInterpolationDatas& InInterpolationData, FHairStrandsInterpolationBulkData& OutInterpolationData);` — 5. Build interplation bulk data
- L115 _public prototype_ `static void BuildClusterBulkData( const FHairStrandsDatas& InRenData, const float InGroomAssetRadius, const FHairGroupsLOD& InSettings, FHairStrandsClusterBulkData& OutClusterData);` — 6. Build cluster data
- L122 _public prototype_ `static void VoxelizeGroupIndex( const FHairDescriptionGroups& In, FHairStrandsVoxelData& Out);` — Optional: Voxelize hair group index
- L126 _public prototype_ `static void BuildRenderCurveResourceBulkData( const FHairStrandsDatas& In, FRenderCurveResourceData& Out);`

#### struct `FStrandsPositionOutput`  
`struct FStrandsPositionOutput`  
_L133-144_
- L135 _public typedef_ `typedef TArray<FVector3f> FStrand;`
- L136 _public typedef_ `typedef TArray<FStrand> FGroup;`
- L138 _public member_ `TArray<FGroup> Groups;`
- L139 _public member_ `const UGroomComponent* Component = nullptr;`
- L141 _public member_ `int32 Status = -1;`
- L143 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L146 _prototype_ `bool RequestStrandsPosition(const UGroomComponent* Component, TSharedPtr<FStrandsPositionOutput> Output, const bool bReadGuides = false);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomCache.h` (Public)


#### class `UGroomCache`  
`class UGroomCache : public UObject, public IInterface_AssetUserData, public IChaosCacheData`  
_L21-91_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject,IInterface_AssetUserData,IChaosCacheData`
- desc: Implements an asset that is used to store an animated groom
- L28 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L29 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L31 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L34 _public prototype_ `void Initialize(EGroomCacheType Type);`
- L35 _public prototype_ `int32 GetStartFrame() const;`
- L36 _public prototype_ `int32 GetEndFrame() const;`
- L39 _public prototype_ `virtual float GetDuration() const override;`
- L43 _public prototype_ `int32 GetFrameNumberAtTime(const float Time, bool bLooping) const;` — Get the frame number at the specified time within the animation range which might not start at 0
- L46 _public prototype_ `int32 GetFrameIndexAtTime(const float Time, bool bLooping) const;` — Get the (floored) frame index at the specified time with the index 0 being the start of the animation
- L49 _public prototype_ `void GetFrameIndicesAtTime(float Time, bool bLooping, bool bIsPlayingBackwards, int32 &OutFrameIndex, int32 &OutNextFrameIndex, float &InterpolationFactor);` — Get the frame indices and interpolation factor between them that correspond to the specified time
- L52 _public prototype_ `void GetFrameIndicesForTimeRange(float StartTime, float EndTime, bool Looping, TArray<int32>& OutFrameIndices);` — Get the frame indices that correspond to the specified time range
- L54 _public prototype_ `bool GetGroomDataAtTime(float Time, bool bLooping, FGroomCacheAnimationData& AnimData);`
- L55 _public prototype_ `bool GetGroomDataAtFrameIndex(int32 FrameIndex, FGroomCacheAnimationData& AnimData);`
- L57 _public prototype_ `void SetGroomAnimationInfo(const FGroomAnimationInfo& AnimInfo);`
- L58 _public function_ `const FGroomAnimationInfo& GetGroomAnimationInfo() const`
- L60 _public prototype_ `EGroomCacheType GetType() const;`
- L62 _public function_ `TArray<FGroomCacheChunk>& GetChunks()`
- L64 _public member_ `TOptional<FPackageFileVersion> ArchiveVersion;`
- L69 _public member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY(Category = ImportSettings, VisibleAnywhere, Instanced)` — Import options used for this GroomCache
- L75 _public member_ `TArray<TObjectPtr<UAssetUserData>> AssetUserData;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Instanced, Category = Hidden)` — Array of user data stored with the asset
- L78 _public prototype_ `virtual void AddAssetUserData(UAssetUserData* InUserData) override;`
- L79 _public prototype_ `virtual void RemoveUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L80 _public prototype_ `virtual UAssetUserData* GetAssetUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L81 _public prototype_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override;`
- L86 _protected member_ `FGroomCacheInfo GroomCacheInfo;` — `UPROPERTY(VisibleAnywhere, Category = GroomCache)`
- L88 _protected member_ `TArray<FGroomCacheChunk> Chunks;`

#### struct `FGroomCacheChunk`  
`struct FGroomCacheChunk`  
_L97-109_
- desc: The smallest unit of streamed GroomCache data The BulkData member is loaded on-demand so that loading the GroomCache itself is relatively lightweight
- L100 _public member_ `int32 DataSize = 0;` — Size of the chunk of data in bytes
- L103 _public member_ `int32 FrameIndex = 0;` — Frame index of the frame stored in this block
- L106 _public member_ `FByteBulkData BulkData;` — Bulk data if stored in the package.
- L108 _public prototype_ `void Serialize(FArchive& Ar, UObject* Owner, int32 ChunkIndex);`

#### class `FGroomCacheProcessor`  
`class FGroomCacheProcessor`  
_L112-125_
- desc: Proxy that processes the HairGroupData into GroomCacheChunks that contain the groom animation data
- L115 _public prototype_ `FGroomCacheProcessor(EGroomCacheType InType, EGroomCacheAttributes InAttributes);`
- L117 _public prototype_ `void AddGroomSample(TArray<FGroomCacheInputData>&& GroomData);`
- L118 _public prototype_ `void TransferChunks(UGroomCache* GroomCache);`
- L119 _public function_ `EGroomCacheType GetType() const`
- L122 _private member_ `TArray<FGroomCacheChunk> Chunks;`
- L123 _private member_ `EGroomCacheAttributes Attributes;`
- L124 _private member_ `EGroomCacheType Type;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L127 _namespace_ `namespace UE`
- L127 _namespace_ `namespace Groom` (scope `UE`)
- L130 _prototype_ `void BuildGroomCache(FGroomCacheProcessor& Processor, const FGroomAnimationInfo& AnimInfo, UGroomCache* GroomCache);` (scope `UE::Groom`) — Build (create and fill) a groom cache from a processor
- L133 _prototype_ `bool BuildGroupsData(const FHairDescription& HairDescription, const TArray<FHairGroupPlatformData>& PlatformData, TArray<FHairGroupInfoWithVisibility>& VisibilityData, const TArray<FHairGroupsInterpolation>& InterpolationData, TArray<FGroomCacheInputData>& GroupsData);` (scope `UE::Groom`) — Build the groom groups data

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomCacheData.h` (Public)


#### enum `EGroomCacheAttributes`  
`enum class EGroomCacheAttributes : uint8`  
_L15-27_
- reflection: `UENUM()`
- desc: Attributes in groom that can be animated
- L17 _public enumerator_ `None = 0`
- L18 _public enumerator_ `Position = 1`
- L19 _public enumerator_ `Width = 1 << 1`
- L20 _public enumerator_ `Color = 1 << 2`
- L23 _public enumerator_ `PositionWidth = (Position | Width) UMETA(DisplayName = "Position & Width")` — For display names
- L24 _public enumerator_ `PositionColor = (Position | Color) UMETA(DisplayName = "Position & Color")`
- L25 _public enumerator_ `WidthColor = (Width | Color) UMETA(DisplayName = "Width & Color")`
- L26 _public enumerator_ `PositionWidthColor = (Position | Width | Color) UMETA(DisplayName = "Position, Width, Color")`

#### struct `FGroomAnimationInfo`  
`struct FGroomAnimationInfo`  
_L33-64_
- reflection: `USTRUCT()`
- desc: Relevant information about a groom animation
- L37 _public prototype_ `FGroomAnimationInfo();`
- L40 _public member_ `uint32 NumFrames;` — `UPROPERTY(VisibleAnywhere, Category = GroomCache)`
- L43 _public member_ `float SecondsPerFrame;` — `UPROPERTY(VisibleAnywhere, Category = GroomCache)`
- L46 _public member_ `float Duration;` — `UPROPERTY(VisibleAnywhere, Category = GroomCache)`
- L49 _public member_ `float StartTime;` — `UPROPERTY()`
- L52 _public member_ `float EndTime;` — `UPROPERTY()`
- L55 _public member_ `int32 StartFrame;` — `UPROPERTY(VisibleAnywhere, Category = GroomCache)`
- L58 _public member_ `int32 EndFrame;` — `UPROPERTY(VisibleAnywhere, Category = GroomCache)`
- L61 _public member_ `EGroomCacheAttributes Attributes;` — `UPROPERTY(VisibleAnywhere, Category = GroomCache)`
- L63 _public prototype_ `bool IsValid() const;`

#### enum `EGroomCacheType`  
`enum class EGroomCacheType : uint8`  
_L72-77_
- reflection: `UENUM()`
- desc: Types of GroomCache Strands: animated render strands (including animatable hair attributes) Guides: animated guides that require in-engine simulation (position only)
- L74 _public enumerator_ `None`
- L75 _public enumerator_ `Strands`
- L76 _public enumerator_ `Guides`

#### enum `EGroomBasisType`  
`enum class EGroomBasisType : uint8`  
_L80-88_
- reflection: `UENUM(BlueprintType)`
- L82 _public enumerator_ `NoBasis`
- L83 _public enumerator_ `BezierBasis`
- L84 _public enumerator_ `BsplineBasis`
- L85 _public enumerator_ `CatmullromBasis`
- L86 _public enumerator_ `HermiteBasis`
- L87 _public enumerator_ `PowerBasis`

#### enum `EGroomCurveType`  
`enum class EGroomCurveType : uint8`  
_L91-96_
- reflection: `UENUM(BlueprintType)`
- L93 _public enumerator_ `Cubic`
- L94 _public enumerator_ `Linear`
- L95 _public enumerator_ `VariableOrder`

#### struct `FGroomCacheInfo`  
`struct FGroomCacheInfo`  
_L100-115_
- reflection: `USTRUCT()`
- desc: Information about the GroomCache itself
- L105 _public prototype_ `static int32 GetCurrentVersion();` — The serialization version of the GroomCache data
- L108 _public member_ `int32 Version = GetCurrentVersion();` — `UPROPERTY()`
- L111 _public member_ `EGroomCacheType Type = EGroomCacheType::None;` — `UPROPERTY(VisibleAnywhere, Category = GroomCache)`
- L114 _public member_ `FGroomAnimationInfo AnimationInfo;` — `UPROPERTY(VisibleAnywhere, Category = GroomCache)`

#### struct `FGroomCacheVertexData`  
`struct FGroomCacheVertexData`  
_L118-133_
- desc: Animatable vertex data that maps to FHairStrandsPoints
- L120 _public prototype_ `FGroomCacheVertexData() = default;`
- L121 _public prototype_ `FGroomCacheVertexData(struct FHairStrandsPoints&& PointsData);`
- L123 _public member_ `TArray<FVector3f> PointsPosition;`
- L124 _public member_ `TArray<float> PointsRadius;`
- L125 _public member_ `TArray<float> PointsCoordU;`
- L126 _public member_ `TArray<FLinearColor> PointsBaseColor;`
- L129 _public member_ `TRefCountPtr<FRDGPooledBuffer> PositionBuffer;` — GPU resources. Lazily allocated
- L130 _public member_ `TRefCountPtr<FRDGPooledBuffer> RadiusBuffer;`
- L132 _public prototype_ `void Serialize(FArchive& Ar, int32 Version, EGroomCacheAttributes InAttributes);`

#### struct `FGroomCacheStrandData`  
`struct FGroomCacheStrandData`  
_L136-146_
- desc: Animatable strand data that maps to FHairStrandsCurves
- L138 _public prototype_ `FGroomCacheStrandData() = default;`
- L139 _public prototype_ `FGroomCacheStrandData(struct FHairStrandsCurves&& CurvesData, float InMaxLength, float InMaxRadius);`
- L141 _public member_ `TArray<float> CurvesLength;`
- L142 _public member_ `float MaxLength = 0.0f;`
- L143 _public member_ `float MaxRadius = 0.0f;`
- L145 _public prototype_ `void Serialize(FArchive& Ar, int32 Version, EGroomCacheAttributes InAttributes);`

#### struct `FGroomCacheGroupData`  
`struct FGroomCacheGroupData`  
_L149-160_
- desc: Animatable group data that maps to FHairStrandsDatas
- L151 _public prototype_ `FGroomCacheGroupData() = default;`
- L152 _public prototype_ `FGroomCacheGroupData(struct FHairStrandsDatas&& GroupData);`
- L154 _public member_ `FGroomCacheVertexData VertexData;`
- L155 _public member_ `FGroomCacheStrandData StrandData;`
- L157 _public member_ `FBox BoundingBox;`
- L159 _public prototype_ `void Serialize(FArchive& Ar, int32 Version, EGroomCacheAttributes InAttributes);`

#### struct `FGroomCacheInputData`  
`struct FGroomCacheInputData`  
_L163-167_
- desc: Built groom data input used for a groom cache animation frame
- L165 _public member_ `FHairStrandsDatas Strands;`
- L166 _public member_ `FHairStrandsDatas Guides;`

#### struct `FGroomCacheAnimationData`  
`struct FGroomCacheAnimationData`  
_L170-180_
- desc: Groom animation data for a frame
- L172 _public prototype_ `FGroomCacheAnimationData() = default;`
- L173 _public prototype_ `FGroomCacheAnimationData(TArray<struct FGroomCacheInputData>&& HairGroupData, int32 Version, EGroomCacheType Type, EGroomCacheAttributes Attributes);`
- L175 _public member_ `TArray<FGroomCacheGroupData> GroupsData;`
- L176 _public member_ `EGroomCacheAttributes Attributes;`
- L177 _public member_ `int32 Version;`
- L179 _public prototype_ `void Serialize(FArchive& Ar);`

#### class `IGroomCacheBuffers`  
`class IGroomCacheBuffers`  
_L183-199_
- desc: Interface to access GroomCache buffers for playback
- L186 _public prototype_ `virtual ~IGroomCacheBuffers() = default;`
- L188 _public prototype_ `virtual const FGroomCacheAnimationData& GetCurrentFrameBuffer() = 0;`
- L189 _public prototype_ `virtual const FGroomCacheAnimationData& GetNextFrameBuffer() = 0;`
- L191 _public prototype_ `virtual int32 GetCurrentFrameIndex() const = 0;`
- L192 _public prototype_ `virtual int32 GetNextFrameIndex() const = 0;`
- L193 _public prototype_ `virtual float GetInterpolationFactor() const = 0;`
- L195 _public function_ `FCriticalSection* GetCriticalSection()`
- L198 _private member_ `FCriticalSection CriticalSection;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomCacheImportOptions.h` (Public)


#### enum `EGroomCacheImportType`  
`enum class EGroomCacheImportType : uint8`  
_L11-17_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `None = 0x00 UMETA(Hidden)`
- L14 _public enumerator_ `Strands = 0x01`
- L15 _public enumerator_ `Guides = 0x02`
- L16 _public enumerator_ `All = Strands | Guides`

#### struct `FGroomCacheImportSettings`  
`struct FGroomCacheImportSettings`  
_L22-61_
- reflection: `USTRUCT(BlueprintType)`
- L28 _public member_ `bool bImportGroomCache = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GroomCache)` — Import the animated groom that was detected in this file
- L32 _public member_ `EGroomCacheImportType ImportType = EGroomCacheImportType::All;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GroomCache)` — Groom Cache types to import
- L36 _public member_ `int32 FrameStart = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sampling)` — Starting index to start sampling the animation from
- L40 _public member_ `int32 FrameEnd = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sampling)` — Ending index to stop sampling the animation at
- L44 _public member_ `bool bSkipEmptyFrames = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sampling, meta = (DisplayName = "Skip Empty Frames at Start of Groom Animation"))` — Skip empty (pre-roll) frames and start importing at the frame which actually contains data
- L48 _public member_ `bool bImportGroomAsset = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GroomCache)` — Import or re-import the groom asset from this file
- L52 _public member_ `FSoftObjectPath GroomAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GroomCache, meta = (MetaClass = "/Script/HairStrandsCore.GroomAsset"))` — The groom asset the groom cache will be built from (must be compatible)
- L56 _public member_ `bool bOverrideConversionSettings = false;` — `UPROPERTY(BlueprintReadWrite, Category = GroomCache)` — Set to true to override the groom conversion settings. Otherwise, use the settings from the groom import options
- L60 _public member_ `FGroomConversionSettings ConversionSettings;` — `UPROPERTY(BlueprintReadWrite, Category = GroomCache)` — Conversion settings to apply to the groom cache import when override is enabled

#### class `UGroomCacheImportOptions`  
`class UGroomCacheImportOptions : public UObject`  
_L64-72_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L71 _public member_ `FGroomCacheImportSettings ImportSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = GroomCache)`

#### class `UGroomCacheImportData`  
`class UGroomCacheImportData : public UAssetImportData`  
_L76-84_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetImportData`
- desc: The asset import data to store the import settings within the GroomCache asset
- L83 _public member_ `FGroomCacheImportSettings Settings;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L19 _prototype_ `ENUM_CLASS_FLAGS(EGroomCacheImportType);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomCacheStreamingManager.h` (Public)


#### struct `IGroomCacheStreamingManager`  
`struct IGroomCacheStreamingManager : public IStreamingManager`  
_L10-50_
- inherits: `IStreamingManager`
- L12 _public prototype_ `virtual ~IGroomCacheStreamingManager() = default;`
- L14 _public prototype_ `static struct IGroomCacheStreamingManager& Get();`
- L15 _public prototype_ `static void Register();`
- L16 _public prototype_ `static void Unregister();`
- L19 _public prototype_ `virtual void RegisterComponent(UGroomComponent* GroomComponent) = 0;` — Registers a new component to the streaming manager.
- L22 _public prototype_ `virtual void UnregisterComponent(UGroomComponent* GroomComponent) = 0;` — Removes the component from the streaming manager.
- L28 _public prototype_ `virtual void PrefetchData(UGroomComponent* GroomComponent) = 0;` — Prefetch data for the component. Data is automatically prefetched when initially registering the component but exposing this may be useful in other cases (eg. when seeking, etc.)
- L37 _public prototype_ `virtual const struct FGroomCacheAnimationData* MapAnimationData(const UGroomCache* GroomCache, uint32 ChunkIndex) = 0;` — Returns a pointer to the cached GroomCacheAnimationData. @param GroomCache	The GroomCache for which to retrieve the data @param ChunkIndex	Index of the chunk we want @return The cached data or null if it's not loaded yet
- L46 _public prototype_ `virtual void UnmapAnimationData(const UGroomCache* GroomCache, uint32 ChunkIndex) = 0;` — Releases pointer to the cachedGroomCacheAnimationData. Must be called for every successful call to MapAnimationData. @param GroomCache	The GroomCache for which the data was retrieved @param ChunkIndex	Index of the chunk to release
- L49 _public prototype_ `virtual void Shutdown() = 0;` — Cleans up the resources managed by the streaming manager

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomComponent.h` (Public)


#### class `UGroomComponent`  
`class UGroomComponent : public UMeshComponent, public ILODSyncInterface, public INiagaraPhysicsAssetDICollectorInterface`  
_L29-391_
- reflection: `UCLASS(HideCategories = (Object, Physics, Activation, Mobility, "Components|Activation"), editinlinenew, meta = (BlueprintSpawnableComponent), ClassGroup = Rendering, MinimalAPI)`
- inherits: `UMeshComponent,ILODSyncInterface,INiagaraPhysicsAssetDICollectorInterface`
- L37 _public member_ `TObjectPtr<UGroomAsset> GroomAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, interp, Category = "Groom")` — Groom asset .
- L40 _public member_ `TObjectPtr<UGroomCache> GroomCache;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, interp, Category = "GroomCache")`
- L44 _public member_ `TArray<TObjectPtr<class UNiagaraComponent>> NiagaraComponents;` — `UPROPERTY(Transient)` — Niagara components that will be attached to the system
- L48 _public member_ `TObjectPtr<class USkeletalMesh> SourceSkeletalMesh;` — `UPROPERTY()` — Kept for debugging mesh transfer
- L52 _public member_ `TObjectPtr<class UGroomBindingAsset> BindingAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, interp, Category = "Groom")` — Optional binding asset for binding a groom onto a skeletal mesh. If the binding asset is not provided the projection is done at runtime, which implies a large GPU cost at startup time.
- L56 _public member_ `TObjectPtr<class UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation")` — Physics asset to be used for hair simulation
- L59 _public member_ `TArray<TWeakObjectPtr<class USkeletalMeshComponent>> CollisionComponents;` — List of collision components to be used
- L63 _public member_ `FHairSimulationSettings SimulationSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, interp, Category = "Simulation")` — Groom's simulation settings
- L67 _public member_ `TObjectPtr<UMeshDeformer> MeshDeformer;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deformer", Meta = (ToolTip = "Mesh deformer that will be applied on groom instance for deformation. Enable the groom asset deformation flags on groups to be able to set it."))` — If set the MeshDeformer will be applied on groom instance for deformation.
- L71 _public member_ `TObjectPtr<UMeshDeformerInstance> MeshDeformerInstance;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Deformer")` — Object containing state for the bound MeshDeformer.
- L75 _public member_ `TObjectPtr<UMeshDeformerInstanceSettings> MeshDeformerInstanceSettings;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = "Deformer", meta = (DisplayName = "Deformer Settings", EditCondition = "MeshDeformerInstanceSettings!=nullptr", ShowOnlyInnerProperties))` — Object containing instance settings for the bound MeshDeformer.
- L79 _public member_ `TObjectPtr<UMaterialInterface> Strands_DebugMaterial;` — `UPROPERTY()` — Reference of the default/debug materials for each geometric representation
- L81 _public member_ `TObjectPtr<UMaterialInterface> Strands_DefaultMaterial;` — `UPROPERTY()`
- L83 _public member_ `TObjectPtr<UMaterialInterface> Cards_DefaultMaterial;` — `UPROPERTY()`
- L85 _public member_ `TObjectPtr<UMaterialInterface> Meshes_DefaultMaterial;` — `UPROPERTY()`
- L88 _public member_ `TObjectPtr<class UNiagaraSystem> AngularSpringsSystem;` — `UPROPERTY()`
- L91 _public member_ `TObjectPtr<class UNiagaraSystem> CosseratRodsSystem;` — `UPROPERTY()`
- L95 _public member_ `FString AttachmentName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, interp, Category = "Groom")` — Optional socket name, where the groom component should be attached at, when parented with a skeletal mesh
- L98 _public member_ `bool bResetSimulation;` — Boolean to check when the simulation should be reset
- L101 _public member_ `bool bInitSimulation;` — Boolean to check when the simulation should be initialized
- L104 _public member_ `bool bWasHiddenLastTick = false;` — Tracks whether the component was hidden last tick, so we can detect visibility transitions and pause/resume the Niagara sim accordingly.
- L107 _public member_ `FMatrix PrevBoneMatrix;` — Previous bone matrix to compare the difference and decide to reset or not the simulation
- L110 _public prototype_ `void UpdateHairSimulation();` — Update Niagara components
- L113 _public prototype_ `void ReleaseHairSimulation();` — Release Niagara components
- L114 _public prototype_ `void ReleaseHairSimulation(const int32 GroupIndex);`
- L117 _public prototype_ `void CreateHairSimulation(const int32 GroupIndex, const int32 LODIndex);` — Create per Group/LOD the Niagara component
- L120 _public prototype_ `void SwitchSimulationLOD(const int32 PreviousLOD, const int32 CurrentLOD, const EHairLODSelectionType InLODSelectionType);` — Enable/Disable hair simulation while transitioning from one LOD to another one
- L123 _public prototype_ `bool IsSimulationEnable(int32 GroupIndex, int32 LODIndex) const;` — Check if the simulation is enabled or not
- L126 _public prototype_ `bool IsDeformationEnable(int32 GroupIndex) const;` — Check if the deformation is enabled or not (from the rigged guides or from the solver deformer)
- L129 _public prototype_ `void UpdateHairGroupsDesc();` — Update Group Description
- L130 _public prototype_ `void UpdateHairGroupsDescAndInvalidateRenderState(bool bInvalidate=true);`
- L133 _public prototype_ `void UpdateSimulatedGroups();` — Update simulated groups
- L136 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L137 _public prototype_ `uint32 GetResourcesSize() const;`
- L141 _public prototype_ `virtual void OnRegister() override;`
- L142 _public prototype_ `virtual void OnUnregister() override;`
- L143 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L144 _public prototype_ `virtual void BeginDestroy() override;`
- L145 _public prototype_ `virtual void FinishDestroy() override;`
- L146 _public prototype_ `virtual void OnAttachmentChanged() override;`
- L147 _public prototype_ `virtual void DetachFromComponent(const FDetachmentTransformRules& DetachmentRules) override;`
- L148 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L150 _public prototype_ `virtual void CreateRenderState_Concurrent(FRegisterComponentContext* Context) override;`
- L151 _public prototype_ `virtual void SendRenderDynamicData_Concurrent() override;`
- L152 _public prototype_ `virtual void DestroyRenderState_Concurrent() override;`
- L153 _public prototype_ `virtual bool RequiresGameThreadEndOfFrameRecreate() const override;`
- L157 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L161 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L162 _public prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams) override;`
- L166 _public prototype_ `virtual void PostLoad() override;`
- L170 _public prototype_ `FHairStrandsRestResource* GetGuideStrandsRestResource(uint32 GroupIndex);` — Return the guide hairs rest resources
- L173 _public prototype_ `FHairStrandsDeformedResource* GetGuideStrandsDeformedResource(uint32 GroupIndex);` — Return the guide hairs deformed resources
- L176 _public prototype_ `FHairStrandsRestRootResource* GetGuideStrandsRestRootResource(uint32 GroupIndex);` — Return the guide hairs root resources
- L177 _public prototype_ `FHairStrandsDeformedRootResource* GetGuideStrandsDeformedRootResource(uint32 GroupIndex);`
- L180 _public prototype_ `virtual void CheckForErrors() override;`
- L181 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L182 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L183 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L184 _public prototype_ `void ValidateMaterials(bool bMapCheck) const;`
- L185 _public prototype_ `void Invalidate();`
- L186 _public prototype_ `void InvalidateAndRecreate();`
- L188 _public prototype_ `virtual void PreFeatureLevelChange(ERHIFeatureLevel::Type PendingFeatureLevel) override;`
- L190 _public prototype_ `void HandlePlatformPreviewChanged(ERHIFeatureLevel::Type InFeatureLevel);` — `UE_DEPRECATED(5.8, "Use HandlePlatformPreviewChanged(EShaderPlatform) instead.")`
- L192 _public prototype_ `void HandleFeatureLevelChanged(ERHIFeatureLevel::Type InFeatureLevel);` — `UE_DEPRECATED(5.8, "Use HandlePlatformPreviewChanged(EShaderPlatform) instead.")`
- L193 _public prototype_ `void HandlePlatformPreviewChanged(EShaderPlatform InShaderPlatform);`
- L196 _public prototype_ `void PostCompilation();`
- L199 _public prototype_ `virtual bool IsCompiling() const override;`
- L204 _public prototype_ `void SetGroomAsset(UGroomAsset* Asset);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Accessor function for changing Groom asset from blueprint/sequencer
- L208 _public prototype_ `void SetBindingAsset(UGroomBindingAsset* InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Accessor function for changing Groom binding asset from blueprint/sequencer
- L212 _public prototype_ `void SetPhysicsAsset(UPhysicsAsset* InPhysicsAsset);` — `UFUNCTION(BlueprintCallable, Category = "Simulation")` — Accessor function for changing Groom physics asset from blueprint/sequencer
- L216 _public prototype_ `void SetMeshDeformer(UMeshDeformer* InMeshDeformer);` — `UFUNCTION(BlueprintCallable, Category = "Components|SkinnedMesh")` — Change the MeshDeformer that is used for this Component.
- L220 _public prototype_ `void AddCollisionComponent(USkeletalMeshComponent* SkeletalMeshComponent);` — `UFUNCTION(BlueprintCallable, Category = "Simulation")` — Add a skeletal mesh to the collision components
- L224 _public prototype_ `void ResetCollisionComponents();` — `UFUNCTION(BlueprintCallable, Category = "Simulation")` — Reset the collision components
- L228 _public prototype_ `void SetEnableSimulation(bool bInEnableSimulation);` — `UFUNCTION(BlueprintCallable, Category = "Simulation")` — Accessor function for changing the enable simulation flag from blueprint/sequencer
- L232 _public prototype_ `void ResetSimulation();` — `UFUNCTION(BlueprintCallable, Category = "Simulation")` — Reset the simulation, if enabled
- L236 _public function_ `UNiagaraComponent* GetNiagaraComponent(const int32 GroupIndex)` — `UFUNCTION(BlueprintCallable, Category = "Simulation")` — Given the group index return the matching niagara component
- L240 _public prototype_ `void SetHairLengthScale(float Scale);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Accessor function for changing hair length scale from blueprint/sequencer
- L243 _public prototype_ `void SetHairLengthScaleEnable(bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = "Groom")`
- L246 _public prototype_ `bool GetIsHairLengthScaleEnabled();` — `UFUNCTION(BlueprintCallable, Category = "Groom")`
- L248 _public prototype_ `void SetStableRasterization(bool bEnable);`
- L249 _public prototype_ `void SetGroomAsset(UGroomAsset* Asset, UGroomBindingAsset* InBinding, const bool bUpdateSimulation = true);`
- L250 _public prototype_ `void SetHairRootScale(float Scale);`
- L251 _public prototype_ `void SetHairWidth(float HairWidth);`
- L252 _public prototype_ `void SetScatterSceneLighting(bool Enable);`
- L253 _public prototype_ `void SetBinding(UGroomBindingAsset* InBinding);`
- L254 _public prototype_ `void SetUseCards(bool InbUseCards);`
- L255 _public function_ `void SetValidation(bool bEnable)`
- L258 _public prototype_ `virtual int32 GetDesiredSyncLOD() const override;` — ~ Begin ILODSyncInterface Interface.
- L259 _public prototype_ `virtual int32 GetBestAvailableLOD() const override;`
- L260 _public prototype_ `virtual void SetForceStreamedLOD(int32 LODIndex) override;`
- L261 _public prototype_ `virtual void SetForceRenderedLOD(int32 LODIndex) override;`
- L262 _public prototype_ `virtual int32 GetNumSyncLODs() const override;`
- L263 _public prototype_ `virtual int32 GetForceStreamedLOD() const override;`
- L264 _public prototype_ `virtual int32 GetForceRenderedLOD() const override;`
- L267 _public prototype_ `int32 GetNumLODs() const;`
- L268 _public prototype_ `int32 GetForcedLOD() const;`
- L269 _public prototype_ `void SetForcedLOD(int32 LODIndex);`
- L273 _public member_ `TArray<FHairGroupDesc> GroomGroupsDesc;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Groom")` — Groom's groups info.
- L277 _public member_ `bool bUseCards = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Groom")` — Force the groom to use cards/meshes geometry instead of strands.
- L280 _public function_ `uint32 GetGroupCount() const` — Hair group instance access
- L281 _public function_ `FHairGroupInstance* GetGroupInstance(int32 Index)`
- L282 _public function_ `const FHairGroupInstance* GetGroupInstance(int32 Index) const`
- L283 _public function_ `bool ContainsGroupInstance(FHairGroupInstance* Instance) const`
- L286 _public prototype_ `EHairGeometryType GetMaterialGeometryType(int32 ElementIndex) const;`
- L287 _public prototype_ `UMaterialInterface* GetMaterial(int32 ElementIndex, EHairGeometryType GeometryType, bool bUseDefaultIfIncompatible) const;`
- L288 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override;`
- L289 _public prototype_ `virtual int32 GetMaterialIndex(FName MaterialSlotName) const override;`
- L290 _public prototype_ `virtual TArray<FName> GetMaterialSlotNames() const override;`
- L291 _public prototype_ `virtual bool IsMaterialSlotNameValid(FName MaterialSlotName) const override;`
- L292 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L293 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L298 _public function_ `void SetPreviewMode(bool bValue)` — Set the component in preview mode, forcing the loading of certain data
- L302 _public function_ `UGroomCache* GetGroomCache() const` — GroomCache
- L306 _public prototype_ `void SetGroomCache(UGroomCache* InGroomCache);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Accessor function for changing GroomCache asset from blueprint/sequencer
- L308 _public prototype_ `float GetGroomCacheDuration() const;`
- L310 _public prototype_ `void SetManualTick(bool bInManualTick);`
- L311 _public prototype_ `bool GetManualTick() const;`
- L312 _public prototype_ `void TickAtThisTime(const float Time, bool bInIsRunning, bool bInBackwards, bool bInIsLooping);`
- L314 _public prototype_ `void ResetAnimationTime();`
- L315 _public prototype_ `float GetAnimationTime() const;`
- L316 _public function_ `bool IsLooping() const`
- L319 _public function_ `void SetGroomSolver(UMeshComponent* InGroomSolver)` — Set the groom solver onto the component
- L322 _public function_ `UMeshComponent* GetGroomSolver() const` — Get the groom solver from the component
- L325 _public prototype_ `void BuildSimulationTransform(FTransform& SimulationTransform) const;` — Build the local simulation transform that could be used in strands simulation
- L328 _public prototype_ `virtual UPhysicsAsset* BuildAndCollect(FTransform& BoneTransform, TArray<TWeakObjectPtr<USkeletalMeshComponent>>& SourceComponents, TArray<TWeakObjectPtr<UPhysicsAsset>>& PhysicsAssets) const override;`
- L332 _private prototype_ `void InitIfDependenciesReady(const bool bUpdateSimulation = true);`
- L333 _private prototype_ `void UpdateGroomCache(float Time);`
- L336 _private member_ `bool bRunning;` — `UPROPERTY(EditAnywhere, Category = GroomCache)`
- L339 _private member_ `bool bLooping;` — `UPROPERTY(EditAnywhere, Category = GroomCache)`
- L342 _private member_ `bool bManualTick;` — `UPROPERTY(EditAnywhere, Category = GroomCache)`
- L345 _private member_ `float ElapsedTime;` — `UPROPERTY(VisibleAnywhere, transient, Category = GroomCache)`
- L347 _private member_ `TSharedPtr<class IGroomCacheBuffers, ESPMode::ThreadSafe> GroomCacheBuffers;`
- L350 _private member_ `TArray<TRefCountPtr<FHairGroupInstance>> HairGroupInstances;`
- L354 _private member_ `TObjectPtr<UGroomAsset> GroomAssetBeingLoaded;` — `UPROPERTY(Transient)`
- L357 _private member_ `TObjectPtr<UGroomBindingAsset> BindingAssetBeingLoaded;` — `UPROPERTY(Transient)`
- L361 _private prototype_ `void CheckHairStrandsUsage(int32 ElementIndex) const;`
- L362 _private prototype_ `void DeleteDeferredHairGroupInstances();`
- L363 _private member_ `void* InitializedResources;`
- L366 _private member_ `TObjectPtr<UMeshComponent> RegisteredMeshComponent;` — `UPROPERTY(Transient)`
- L369 _private member_ `TObjectPtr<UMeshComponent> DeformedMeshComponent;` — `UPROPERTY(Transient)`
- L371 _private member_ `bool bIsGroomAssetCallbackRegistered;`
- L372 _private member_ `bool bIsGroomBindingAssetCallbackRegistered;`
- L373 _private member_ `bool bValidationEnable = true;`
- L374 _private member_ `bool bPreviewMode = false;`
- L377 _private member_ `EHairLODSelectionType LODSelectionType = EHairLODSelectionType::Immediate;` — LOD selection
- L378 _private member_ `float LODPredictedIndex = -1.f;`
- L379 _private member_ `float LODForcedIndex = -1.f;`
- L381 _private prototype_ `void InitResources(bool bIsBindingReloading=false);`
- L382 _private prototype_ `void ReleaseResources();`
- L390 _private member_ `TSoftObjectPtr<UMeshComponent> GroomSolver = nullptr;` — Groom solver pointer

#### class `FGroomComponentRecreateRenderStateContext`  
`class FGroomComponentRecreateRenderStateContext`  
_L395-403_
- desc: Used to recreate render context for all GroomComponents that use a given GroomAsset
- L398 _public prototype_ `FGroomComponentRecreateRenderStateContext(UGroomAsset* GroomAsset);`
- L399 _public prototype_ `~FGroomComponentRecreateRenderStateContext();`
- L402 _private member_ `TArray<UGroomComponent*> GroomComponents;`

#### struct `FGroomComponentMemoryStats`  
`struct FGroomComponentMemoryStats`  
_L410-420_
- L412 _public member_ `uint32 Guides = 0;`
- L413 _public member_ `uint32 Strands= 0;`
- L414 _public member_ `uint32 Cards = 0;`
- L415 _public member_ `uint32 Meshes = 0;`
- L417 _public prototype_ `static FGroomComponentMemoryStats Get(const FHairGroupInstance* In);`
- L418 _public prototype_ `void Accumulate(const FGroomComponentMemoryStats& In);`
- L419 _public prototype_ `uint32 GetTotalSize() const;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L406 _prototype_ `const FLinearColor GetHairGroupDebugColor(int32 GroupIt);` — Return the debug color of an hair group

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomCreateBindingOptions.h` (Public)


#### class `UGroomCreateBindingOptions`  
`class UGroomCreateBindingOptions : public UObject`  
_L10-52_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = EditorPerProjectUserSettings, autoCollapseCategories = (Conversion), hideCategories = (Hidden))`
- inherits: `UObject`
- L17 _public member_ `TWeakObjectPtr<UGroomAsset> GroomAsset;` — `UPROPERTY()` — Groom asset
- L21 _public member_ `EGroomBindingMeshType GroomBindingType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildSettings)` — Type of mesh to create groom binding for
- L27 _public member_ `TObjectPtr<USkeletalMesh> SourceSkeletalMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = Conversion)` — Skeletal mesh on which the groom has been authored. This is optional, and used only if the hair binding is done a different mesh than the one which it has been authored, i.e., only if the curves roots and the surface geometry don't aligned and need to be wrapped/transformed.
- L31 _public member_ `TObjectPtr<USkeletalMesh> TargetSkeletalMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildSettings)` — Skeletal mesh on which the groom is attached to.
- L35 _public member_ `TObjectPtr<UGeometryCache> SourceGeometryCache;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = Conversion)` — GeometryCache on which the groom has been authored
- L39 _public member_ `TObjectPtr<UGeometryCache> TargetGeometryCache;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildSettings)` — GeometryCache on which the groom is attached to.
- L43 _public member_ `int32 NumInterpolationPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties, ClampMin = "0", ClampMax = "100"), Category = HairInterpolation)` — Number of points used for the rbf interpolation
- L47 _public member_ `int32 MatchingSection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, meta = (ShowOnlyInnerProperties), Category = Conversion)` — Section to pick to transfer the position
- L51 _public member_ `FName TargetBindingAttribute = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = BuildSettings)` — Optional mesh attribute used to filter triangles to bind groom to

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomCreateFollicleMaskOptions.h` (Public)


#### enum `EFollicleMaskChannel`  
`enum class EFollicleMaskChannel : uint8`  
_L13-19_
- reflection: `UENUM(BlueprintType)`
- desc: List of channel
- L15 _public enumerator_ `R = 0 UMETA(DisplatName = "Red")`
- L16 _public enumerator_ `G = 1 UMETA(DisplatName = "Green")`
- L17 _public enumerator_ `B = 2 UMETA(DisplatName = "Blue")`
- L18 _public enumerator_ `A = 3 UMETA(DisplatName = "Alpha")`

#### struct `FFollicleMaskOptions`  
`struct FFollicleMaskOptions`  
_L23-34_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `TObjectPtr<UGroomAsset> Groom = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Groom)` — Groom asset
- L33 _public member_ `EFollicleMaskChannel Channel = EFollicleMaskChannel::R;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Groom)` — Texture channel in which the groom's roots mask will be writtent to.

#### class `UGroomCreateFollicleMaskOptions`  
`class UGroomCreateFollicleMaskOptions : public UObject`  
_L37-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = EditorPerProjectUserSettings, HideCategories = ("Hidden"))`
- inherits: `UObject`
- L45 _public member_ `int32 Resolution = 4096;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — Follicle mask texture resolution. The resolution will be rounded to the closest power of two.
- L49 _public member_ `int32 RootRadius = 8;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — Size of the root in the follicle mask (in pixels)
- L53 _public member_ `TArray<FFollicleMaskOptions> Grooms;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — Grooms which will be use to create the follicle texture

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomCreateStrandsTexturesOptions.h` (Public)


#### enum `EStrandsTexturesTraceType`  
`enum class EStrandsTexturesTraceType : uint8`  
_L14-19_
- reflection: `UENUM(BlueprintType)`
- desc: Size of each strands
- L16 _public enumerator_ `TraceInside = 0 UMETA(DisplatName = "Trace inside")`
- L17 _public enumerator_ `TraceOuside = 1 UMETA(DisplatName = "Trace outside")`
- L18 _public enumerator_ `TraceBidirectional = 2 UMETA(DisplatName = "Trace both sides")`

#### enum `EStrandsTexturesMeshType`  
`enum class EStrandsTexturesMeshType : uint8`  
_L23-27_
- reflection: `UENUM(BlueprintType)`
- desc: Size of each strands
- L25 _public enumerator_ `Static = 0 UMETA(DisplatName = "Use static mesh")`
- L26 _public enumerator_ `Skeletal = 1 UMETA(DisplatName = "Use skeletal mesh")`

#### class `UGroomCreateStrandsTexturesOptions`  
`class UGroomCreateStrandsTexturesOptions : public UObject`  
_L30-87_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = EditorPerProjectUserSettings, HideCategories = ("Hidden"))`
- inherits: `UObject`
- L38 _public member_ `EHairTextureLayout Layout = EHairTextureLayout::Layout1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — Resolution of the output texture maps (tangent, coverage, ...)
- L42 _public member_ `int32 Resolution = 2048;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — Resolution of the output texture maps (tangent, coverage, ...)
- L46 _public member_ `EStrandsTexturesTraceType TraceType = EStrandsTexturesTraceType::TraceBidirectional;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — Direction in which the tracing will be done: either from the mesh's surface to the outside, or from the mesh's surface to the inside.
- L50 _public member_ `float TraceDistance = 3.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options, meta = (ClampMin = "0.0001", UIMin = "0.001", UIMax = "10.0"))` — Distance from the mesh surface until hair are projected onto the mesh.
- L54 _public member_ `EStrandsTexturesMeshType MeshType = EStrandsTexturesMeshType::Static;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — Select which mesh should be used for tracing
- L58 _public member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — Mesh on which the groom strands will be projected on. If non empty and if the skeletal mesh entry is empty, the static mesh will be used for generating the textures.
- L62 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — Mesh on which the groom strands will be projected on. If non empty, the skeletal mesh will be used for generating the textures.
- L66 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — LOD of the mesh, on which the texture projection is done
- L70 _public member_ `int32 SectionIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — Section of the mesh, on which the texture projection is done
- L74 _public member_ `int32 UVChannelIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — UV channel to use
- L78 _public member_ `TArray<int32> GroupIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Options)` — Groom index which should be baked into the textures. When the array is empty, all groups will be included (Default).
- L82 _public member_ `int32 Dilation = 8;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties, ClampMin = 0, ClampMax = 32, UIMin = 0, UIMax = 32), Category = Options)` — Number pixels expanded by the post-process dilation (0..64).
- L86 _public member_ `TArray<TObjectPtr<UTexture2D>> GeneratedTextures;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties, ClampMin = 0, ClampMax = 32, UIMin = 0, UIMax = 32), Category = Options)` — Generated texure.

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomDeformerBuilder.h` (Public)


#### struct `FGroomDeformerBuilder`  
`struct FGroomDeformerBuilder`  
_L10-14_
- L13 _public prototype_ `static USkeletalMesh* CreateSkeletalMesh(UGroomAsset* GroomAsset);` — Create skeletal mesh bones+physics asset from groom asset guides

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomDesc.h` (Public)


#### struct `FHairGroupDesc`  
`struct FHairGroupDesc`  
_L13-83_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `float HairLength = 0;` — `UPROPERTY()` — Length of the longest hair strands
- L23 _public member_ `float HairWidth = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Groom", meta = (editcondition = "HairWidth_Override", ClampMin = "0.0001", UIMin = "0.001", UIMax = "1.0", SliderExponent = 6))` — Hair width (in centimeters)
- L25 _public member_ `bool HairWidth_Override = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L29 _public member_ `float HairRootScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Groom", AdvancedDisplay, meta = (editcondition = "HairRootScale_Override", ClampMin = "0.0001", UIMin = "0.001", UIMax = "2.0", SliderExponent = 6))` — Scale the hair width at the root
- L31 _public member_ `bool HairRootScale_Override = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L35 _public member_ `float HairTipScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Groom", AdvancedDisplay, meta = (editcondition = "HairTipScale_Override", ClampMin = "0.0001", UIMin = "0.001", UIMax = "2.0", SliderExponent = 6))` — Scale the hair width at the tip
- L37 _public member_ `bool HairTipScale_Override = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L41 _public member_ `float HairShadowDensity = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Groom", AdvancedDisplay, meta = (editcondition = "HairShadowDensity_Override", ClampMin = "0.0001", UIMin = "0.001", UIMax = "10.0", SliderExponent = 6))` — Override the hair shadow density factor (unit less).
- L43 _public member_ `bool HairShadowDensity_Override = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L47 _public member_ `float HairRaytracingRadiusScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Groom", AdvancedDisplay, meta = (editcondition = "HairRaytracingRadiusScale_Override", ClampMin = "0.0001", UIMin = "0.001", UIMax = "10.0", SliderExponent = 6))` — Scale the hair geometry radius for ray tracing effects (e.g. shadow)
- L49 _public member_ `bool HairRaytracingRadiusScale_Override = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L53 _public member_ `bool bUseHairRaytracingGeometry = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Groom", AdvancedDisplay, meta = (editcondition = "bUseHairRaytracingGeometry_Override", ClampMin = "0.0001", UIMin = "0.001", UIMax = "10.0", SliderExponent = 6))` — Enable hair strands geomtry for raytracing
- L55 _public member_ `bool bUseHairRaytracingGeometry_Override = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L59 _public member_ `float LODBias = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, interp, Category = "Performance", AdvancedDisplay, meta = (ClampMin = "-7.0", ClampMax = "7.0", UIMin = "-7.0", UIMax = "7.0", SliderExponent = 1))` — Bias the selected LOD. A value >0 will progressively select lower detailed lods. Used when r.HairStrands.Cluster.Culling = 1.
- L63 _public member_ `bool bUseStableRasterization = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Groom", meta = (editcondition = "bUseStableRasterization_Override"))` — Insure the hair does not alias. When enable, group of hairs might appear thicker. Isolated hair should remain thin.
- L65 _public member_ `bool bUseStableRasterization_Override = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L69 _public member_ `bool bScatterSceneLighting = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Groom", meta = (editcondition = "bScatterSceneLighting_Override"))` — Light hair with the scene color. This is used for vellus/short hair to bring light from the surrounding surface, like skin.
- L71 _public member_ `bool bScatterSceneLighting_Override = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L74 _public member_ `bool bSupportVoxelization = true;` — `UPROPERTY()`
- L76 _public member_ `bool bSupportVoxelization_Override = 0;` — `UPROPERTY()`
- L80 _public member_ `float HairLengthScale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, interp, Category = "Groom", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", SliderExponent = 1, editcondition = "HairLengthScale_Override"))` — When enabled, Length Scale allow to scale the length of the hair.
- L82 _public member_ `bool HairLengthScale_Override = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (PinHiddenByDefault, InlineEditConditionToggle))`

#### Free symbols / members of external scopes

- L84 _typedef_ `typedef FHairGroupDesc FHairGroupInstanceModifer;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomEdit.h` (Public)


#### struct `FEditableHairStrandControlPoint`  
`struct FEditableHairStrandControlPoint`  
_L13-25_
- desc: Strands
- L15 _public member_ `FVector3f Position;`
- L16 _public member_ `float Radius;`
- L17 _public member_ `float U;`
- L18 _public member_ `FLinearColor BaseColor;`
- L19 _public member_ `float Roughness;`
- L20 _public member_ `float AO;`
- L22 _public member_ `uint8 bHasColor : 1 = false;`
- L23 _public member_ `uint8 bHasRoughness : 1 = false;`
- L24 _public member_ `uint8 bHasAO : 1 = false;`

#### struct `FEditableHairStrand`  
`struct FEditableHairStrand`  
_L27-43_
- L29 _public member_ `TArray<FEditableHairStrandControlPoint> ControlPoints;`
- L31 _public member_ `uint32 StrandID;`
- L32 _public member_ `uint32 ClumpID;`
- L33 _public member_ `FVector2f RootUV;`
- L36 _public member_ `uint32 GuideIDs[3];` — Pre-computed Simulation
- L37 _public member_ `float GuideWeights[3];`
- L39 _public member_ `uint8 bHasStrandID : 1 = false;`
- L40 _public member_ `uint8 bHasClumpID : 1 = false;`
- L41 _public member_ `uint8 bHasClosestGuide : 1 = false;`
- L42 _public member_ `uint8 bHasRootUV : 1 = false;`

#### struct `FEditableHairGuideControlPoint`  
`struct FEditableHairGuideControlPoint`  
_L47-51_
- desc: Guides
- L49 _public member_ `FVector3f Position;`
- L50 _public member_ `float U;`

#### struct `FEditableHairGuide`  
`struct FEditableHairGuide`  
_L53-62_
- L55 _public member_ `TArray<FEditableHairGuideControlPoint> ControlPoints;`
- L57 _public member_ `uint32 GuideID;`
- L58 _public member_ `FVector2f RootUV;`
- L60 _public member_ `uint8 bHasGuideID : 1 = false;`
- L61 _public member_ `uint8 bHasRootUV : 1 = false;`

#### struct `FEditableGroomGroup`  
`struct FEditableGroomGroup`  
_L66-73_
- desc: Group & Groom
- L68 _public member_ `uint32 GroupIndex;`
- L69 _public member_ `uint32 GroupID;`
- L70 _public member_ `FName GroupName;`
- L71 _public member_ `TArray<FEditableHairStrand> Strands;`
- L72 _public member_ `TArray<FEditableHairGuide> Guides;`

#### struct `FEditableGroom`  
`struct FEditableGroom`  
_L75-78_
- L77 _public member_ `TArray<FEditableGroomGroup> Groups;`

#### enum `EEditableGroomOperations`  
`enum EEditableGroomOperations`  
_L80-92_
- L82 _public enumerator_ `ControlPoints_Added = 0x1`
- L83 _public enumerator_ `ControlPoints_Modified = 0x2`
- L84 _public enumerator_ `ControlPoints_Deleted = 0x4`
- L86 _public enumerator_ `Strands_Added = 0x8`
- L87 _public enumerator_ `Strands_Modified = 0x10`
- L88 _public enumerator_ `Strands_Deleted = 0x20`
- L90 _public enumerator_ `Group_Added = 0x40`
- L91 _public enumerator_ `Group_Deleted = 0x80`

#### Free symbols / members of external scopes

- L95 _prototype_ `void ConvertFromGroomAsset(UGroomAsset* In, FEditableGroom* Out, const bool bAllowCurveReordering = true, const bool bApplyDecimation = true, const bool bAllowAddEndControlPoint = true);` — Convert a groom asset into an editable groom asset
- L100 _prototype_ `void ConvertToGroomAsset(UGroomAsset* Out, const FEditableGroom* In, uint32 Operations);` — Convert an editable groom asset into a groom asset The 'operations' flag indicates what type of modifications have been done onto the editable groom. This helps to drive the update mechanism.

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomImportOptions.h` (Public)


#### class `UGroomImportOptions`  
`class UGroomImportOptions : public UObject`  
_L16-27_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = EditorPerProjectUserSettings, HideCategories = ("Hidden"))`
- inherits: `UObject`
- L22 _public member_ `FGroomConversionSettings ConversionSettings;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Conversion)`
- L26 _public member_ `TArray<FHairGroupsInterpolation> InterpolationSettings;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Hidden)` — Interpolation settings per group

#### struct `FGroomHairGroupPreview`  
`struct FGroomHairGroupPreview`  
_L30-60_
- reflection: `USTRUCT(BlueprintType)`
- L35 _public member_ `int32 GroupIndex = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Preview)`
- L38 _public member_ `FName GroupName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Preview)`
- L41 _public member_ `int32 GroupID = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Preview)`
- L44 _public member_ `int32 CurveCount = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Preview)`
- L47 _public member_ `int32 GuideCount = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Preview)`
- L50 _public member_ `uint32 Attributes = 0;` — `UPROPERTY()`
- L53 _public member_ `uint32 AttributeFlags = 0;` — `UPROPERTY()`
- L56 _public member_ `uint32 Flags = 0;` — `UPROPERTY()`
- L59 _public member_ `FHairGroupsInterpolation InterpolationSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Preview)`

#### class `UGroomHairGroupsPreview`  
`class UGroomHairGroupsPreview : public UObject`  
_L63-70_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = EditorPerProjectUserSettings, HideCategories = ("Hidden"))`
- inherits: `UObject`
- L69 _public member_ `TArray<FGroomHairGroupPreview> Groups;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = Preview)`

#### class `UGroomHairGroupsMapping`  
`class UGroomHairGroupsMapping : public UObject`  
_L73-106_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = EditorPerProjectUserSettings, HideCategories = ("Hidden"))`
- inherits: `UObject`
- L79 _public member_ `TArray<FName> OldGroupNames;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = GroupMapping)`
- L82 _public member_ `TArray<FName> NewGroupNames;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = GroupMapping)`
- L85 _public member_ `TArray<int32> OldToNewGroupIndexMapping;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = GroupMapping)`
- L88 _public member_ `TArray<int32> NewToOldGroupIndexMapping;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties), Category = GroupMapping)`
- L90 _public function_ `FName GetNewGroupName(int32 In)`
- L91 _public function_ `FName GetOldGroupName(int32 In)`
- L93 _public prototype_ `const TArray<TSharedPtr<FString>>& GetOldGroupNames();`
- L95 _public prototype_ `bool HasValidMapping() const;`
- L96 _public function_ `bool IsValid() const`
- L97 _public prototype_ `void SetIndex(int32 NewIndex, int32 OldIndex);`
- L99 _public member_ `TArray<TSharedPtr<FString>> CachedOldGroupNames;`
- L102 _public prototype_ `void Map(const FHairDescriptionGroups& OldGroup, const FHairDescriptionGroups& NewGroup);` — Initialize UGroomHairGroupsMapping by mapping OldGroup onto NewGroup
- L105 _public prototype_ `static void RemapHairDescriptionGroups(const FHairDescriptionGroups& SrcGroups, const FHairDescriptionGroups& DstGroups, TArray<int32>& Out);` — Recreate a mapping from SrcGroups to DstGroups

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L108 _prototype_ `UGroomImportOptions* CreateGroomImportOptions(const FHairDescriptionGroups& GroupsDescription, const TArray<FHairGroupsInterpolation>& BuildSettings);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomInstance.h` (Public)


#### enum `EHairLODSelectionType`  
`enum class EHairLODSelectionType`  
_L66-71_
- L68 _public enumerator_ `Immediate` — Done on the rendering thread, prior to render
- L69 _public enumerator_ `Predicted` — Predicted based on rendering->game thread feedback
- L70 _public enumerator_ `Forced` — Forced LOD value

#### enum `EHairViewRayTracingMask`  
`enum class EHairViewRayTracingMask`  
_L73-78_
- L75 _public enumerator_ `None = 0x0`
- L76 _public enumerator_ `RayTracing = 0x1` — Visible for raytracing effects (RT shadow, RT refleciton, Lumen, ...)
- L77 _public enumerator_ `PathTracing = 0x2` — Visible for pathtracing rendering

#### struct `FHairGroupInstance`  
`struct FHairGroupInstance : public FHairStrandsInstance`  
_L82-330_
- inherits: `FHairStrandsInstance`
- desc: Represent/Describe data & resources of a hair group belonging to a groom
- L84 _public prototype_ `virtual ~FHairGroupInstance();`
- L110 _public member_ `} Guides;`
- L160 _public member_ `} Strands;`
- L214 _public member_ `} Cards;`
- L244 _public member_ `} Meshes;`
- L282 _public member_ `} Debug;`
- L284 _public member_ `FTransform LocalToWorld = FTransform::Identity;`
- L285 _public member_ `FHairGroupPublicData* HairGroupPublicData = nullptr;`
- L286 _public member_ `EHairGeometryType GeometryType = EHairGeometryType::NoneGeometry;`
- L287 _public member_ `EHairBindingType BindingType = EHairBindingType::NoneBinding;`
- L288 _public member_ `bool bForceCards = false;`
- L289 _public member_ `bool bUpdatePositionOffset = false;`
- L290 _public member_ `bool bSupportStreaming = true;`
- L293 _public member_ `UMeshComponent* DeformedComponent = nullptr;` — Deformed component to extract the bone buffer
- L296 _public member_ `int32 DeformedSection = INDEX_NONE;` — Section of the deformed component to be used
- L298 _public function_ `bool IsValid() const`
- L303 _public function_ `virtual const FBoxSphereBounds& GetBounds() const override`
- L304 _public function_ `virtual const FBoxSphereBounds& GetLocalBounds() const`
- L305 _public function_ `virtual const FHairGroupPublicData* GetHairData() const`
- L306 _public function_ `virtual const EHairGeometryType GetHairGeometry() const`
- L309 _public function_ `inline const FTransform& GetRestLocalToWorld() const` — Get the rest local to world transform according to the internal binding type
- L316 _public function_ `inline const FTransform& GetCurrentLocalToWorld() const` — Get the current local to world transform according to the internal binding type
- L323 _public function_ `inline const FTransform& GetPreviousLocalToWorld() const` — Get the previous local to world transform according to the internal binding type
- L329 _public prototype_ `FHairStrandsVertexFactoryUniformShaderParameters GetHairStandsUniformShaderParameters(EGroomViewMode ViewMode) const;`

#### struct `FHairGroupInstance::FGuides`  
`struct FGuides`  
_L88-110_
- desc: Simulation
- L90 _public function_ `const FHairStrandsBulkData& GetData() const`
- L92 _public function_ `bool IsValid() const`
- L93 _public function_ `bool NeedsGuides() const`
- L94 _public function_ `bool HasValidRootData() const`
- L98 _public member_ `FHairStrandsRestResource* RestResource = nullptr;` — Resources - Strands rest position data for sim & render strands Resources - Strands deformed position data for sim & render strands
- L99 _public member_ `FHairStrandsDeformedResource* DeformedResource = nullptr;`
- L103 _public member_ `FHairStrandsRestRootResource* RestRootResource = nullptr;` — Resources - Rest root data, for deforming strands attached to a skinned mesh surface Resources - Deformed root data, for deforming strands attached to a skinned mesh surface
- L104 _public member_ `FHairStrandsDeformedRootResource* DeformedRootResource = nullptr;`
- L106 _public member_ `bool bIsSimulationEnable = false;`
- L107 _public member_ `bool bIsDeformationEnable = false;`
- L108 _public member_ `bool bHasGlobalInterpolation = false;`
- L109 _public member_ `bool bIsSimulationCacheEnable = false;`

#### struct `FHairGroupInstance::FStrands`  
`struct FStrands`  
_L114-160_
- desc: Strands
- L116 _public function_ `const FHairStrandsBulkData& GetData() const`
- L118 _public function_ `bool IsValid() const`
- L119 _public function_ `bool HasValidRootData() const`
- L123 _public member_ `FHairStrandsRestResource* RestResource = nullptr;` — Resources - Strands rest position data for sim & render strands Resources - Strands deformed position data for sim & render strands
- L124 _public member_ `FHairStrandsDeformedResource* DeformedResource = nullptr;`
- L128 _public member_ `FHairStrandsInterpolationResource* InterpolationResource = nullptr;` — Data - Interpolation data (weights/Id/...) for transfering sim strands (i.e. guide) motion to render strands Resources - Strands deformed position data for sim & render strands
- L131 _public member_ `FHairStrandsClusterResource* ClusterResource = nullptr;` — Resources - Strands cluster data for culling/voxelization purpose
- L132 _public member_ `FHairStrandsCullingResource* CullingResource = nullptr;`
- L136 _public member_ `FHairStrandsRestRootResource* RestRootResource = nullptr;` — Resources - Rest root data, for deforming strands attached to a skinned mesh surface Resources - Deformed root data, for deforming strands attached to a skinned mesh surface
- L137 _public member_ `FHairStrandsDeformedRootResource* DeformedRootResource = nullptr;`
- L141 _public member_ `FHairStrandsRaytracingResource* RenRaytracingResource = nullptr;`
- L142 _public member_ `FHairStrandsRaytracingResource** RenRaytracingResourceShared = nullptr;`
- L143 _public member_ `bool RenRaytracingResourceOwned = false;`
- L144 _public member_ `EHairViewRayTracingMask ViewRayTracingMask = EHairViewRayTracingMask::None;`
- L145 _public member_ `float CachedHairScaledRadius = 0;`
- L146 _public member_ `float CachedHairRootScale = 0;`
- L147 _public member_ `float CachedHairTipScale = 0;`
- L148 _public member_ `uint32 CachedProceduralSplits = 0;`
- L151 _public member_ `FRDGExternalBuffer DebugCurveAttributeBuffer;`
- L152 _public member_ `FHairGroupInstanceModifer Modifier;`
- L154 _public member_ `FHairStrandsUniformBuffer UniformBuffer;`
- L155 _public member_ `FHairStrandsVertexFactory* VertexFactory = nullptr;`
- L156 _public member_ `FLinearSweptSpheresHairStrandsVertexFactory* LinearSweptSphereVertexFactory = nullptr;`
- L158 _public member_ `EHairInterpolationType HairInterpolationType = EHairInterpolationType::NoneSkinning;`
- L159 _public member_ `bool bCullingEnable = false;` — Indicates if culling is enabled for this hair strands data.

#### struct `FHairGroupInstance::FCards`  
`struct FCards`  
_L164-214_
- desc: Cards
- L166 _public function_ `bool IsValid() const`
- L167 _public function_ `bool IsValid(int32 LODIndex) const`
- L213 _public member_ `TArray<FLOD> LODs;`

#### struct `FHairGroupInstance::FCards::FLOD`  
`struct FLOD`  
_L168-212_
- L170 _public function_ `bool IsValid() const`
- L171 _public function_ `const FHairCardsBulkData& GetData() const`
- L174 _public member_ `FHairCardsRestResource* RestResource = nullptr;` — Resources
- L175 _public member_ `FHairCardsDeformedResource* DeformedResource = nullptr;`
- L176 _public member_ `FHairCardsInterpolationResource* InterpolationResource = nullptr;`
- L178 _public member_ `FHairStrandsRaytracingResource* RaytracingResource = nullptr;`
- L179 _public member_ `bool RaytracingResourceOwned = false;`
- L202 _public member_ `} Guides;`
- L204 _public member_ `FHairCardsUniformBuffer UniformBuffer;`
- L205 _public member_ `FHairCardsVertexFactory* VertexFactory = nullptr;`
- L206 _public function_ `FHairCardsVertexFactory* GetVertexFactory() const`
- L210 _public prototype_ `void InitVertexFactory();`

#### struct `FHairGroupInstance::FCards::FLOD::FGuides`  
`struct FGuides`  
_L182-202_
- L184 _public function_ `bool IsValid() const`
- L185 _public function_ `bool HasValidRootData() const`
- L186 _public function_ `const FHairStrandsBulkData& GetData() const`
- L190 _public member_ `FHairStrandsRestResource* RestResource = nullptr;` — Resources - Strands rest position data for sim & render strands Resources - Strands deformed position data for sim & render strands
- L191 _public member_ `FHairStrandsDeformedResource* DeformedResource = nullptr;`
- L195 _public member_ `FHairStrandsRestRootResource* RestRootResource = nullptr;` — Resources - Rest root data, for deforming strands attached to a skinned mesh surface Resources - Deformed root data, for deforming strands attached to a skinned mesh surface
- L196 _public member_ `FHairStrandsDeformedRootResource* DeformedRootResource = nullptr;`
- L199 _public member_ `FHairStrandsInterpolationResource* InterpolationResource = nullptr;` — Resources - Strands deformed position data for sim & render strands
- L201 _public member_ `EHairInterpolationType HairInterpolationType = EHairInterpolationType::NoneSkinning;`

#### struct `FHairGroupInstance::FMeshes`  
`struct FMeshes`  
_L218-244_
- desc: Meshes
- L220 _public function_ `bool IsValid() const`
- L221 _public function_ `bool IsValid(int32 LODIndex) const`
- L243 _public member_ `TArray<FLOD> LODs;`

#### struct `FHairGroupInstance::FMeshes::FLOD`  
`struct FLOD`  
_L222-242_
- L224 _public function_ `bool IsValid() const`
- L225 _public function_ `const FHairMeshesBulkData& GetData() const`
- L228 _public member_ `FHairMeshesRestResource* RestResource = nullptr;` — Resources
- L229 _public member_ `FHairMeshesDeformedResource* DeformedResource = nullptr;`
- L231 _public member_ `FHairStrandsRaytracingResource* RaytracingResource = nullptr;`
- L232 _public member_ `bool RaytracingResourceOwned = false;`
- L235 _public member_ `FHairCardsUniformBuffer UniformBuffer;`
- L236 _public member_ `FHairCardsVertexFactory* VertexFactory = nullptr;`
- L237 _public function_ `FHairCardsVertexFactory* GetVertexFactory() const`
- L241 _public prototype_ `void InitVertexFactory();`

#### struct `FHairGroupInstance::FDebug`  
`struct FDebug`  
_L248-282_
- desc: Debug
- L251 _public member_ `uint32 GroupIndex = ~0;` — Data
- L252 _public member_ `uint32 GroupCount = 0;`
- L253 _public member_ `FString GroomAssetName;`
- L254 _public member_ `uint32 LastFrameIndex = ~0;`
- L255 _public member_ `uint32 GroomAssetHash = 0;`
- L256 _public member_ `uint32 GroomBindingAssetHash = 0;`
- L258 _public member_ `float LODPredictedIndex = -1.f;` — Computed on the rendering-thread, readback on the game-thread during tick()
- L259 _public member_ `float LODForcedIndex = -1.f;` — Set by the game-thread, read on the rendering-thread to force a particular LOD
- L260 _public member_ `EHairLODSelectionType LODSelectionTypeForDebug = EHairLODSelectionType::Immediate;` — For debug only, not used
- L262 _public member_ `int32 MeshLODIndex = ~0;`
- L263 _public member_ `EGroomBindingMeshType GroomBindingType;`
- L264 _public member_ `EGroomCacheType GroomCacheType;`
- L265 _public member_ `FPrimitiveSceneProxy* Proxy = nullptr;`
- L266 _public member_ `FString MeshComponentName;`
- L267 _public member_ `FPrimitiveComponentId MeshComponentId;`
- L268 _public member_ `FPersistentPrimitiveIndex CachedMeshPersistentPrimitiveIndex;`
- L269 _public member_ `const UMeshComponent* MeshComponentForDebug = nullptr;`
- L270 _public member_ `const UGroomComponent* GroomComponentForDebug = nullptr;` — For debug only, shouldn't be deferred on the rendering thread
- L271 _public member_ `FTransform RigidRestLocalToWorld = FTransform::Identity;`
- L272 _public member_ `FTransform RigidCurrentLocalToWorld = FTransform::Identity;`
- L273 _public member_ `FTransform SkinningRestLocalToWorld = FTransform::Identity;`
- L274 _public member_ `FTransform SkinningCurrentLocalToWorld = FTransform::Identity;`
- L275 _public member_ `FTransform RigidPreviousLocalToWorld = FTransform::Identity;`
- L276 _public member_ `FTransform SkinningPreviousLocalToWorld = FTransform::Identity;`
- L278 _public member_ `TSharedPtr<class IGroomCacheBuffers, ESPMode::ThreadSafe> GroomCacheBuffers;`
- L281 _public member_ `FHairStrandsDebugResources* HairDebugResource = nullptr;` — Resources

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L55 _typedef_ `typedef TUniformBufferRef<FHairCardsVertexFactoryUniformShaderParameters> FHairCardsUniformBuffer;`
- L64 _typedef_ `typedef TUniformBufferRef<FHairStrandsVertexFactoryUniformShaderParameters> FHairStrandsUniformBuffer;`
- L79 _prototype_ `ENUM_CLASS_FLAGS(EHairViewRayTracingMask);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomPluginSettings.h` (Public)


#### class `UGroomPluginSettings`  
`class UGroomPluginSettings : public UObject`  
_L14-25_
- reflection: `UCLASS(MinimalAPI, config=Engine)`
- inherits: `UObject`
- desc: Settings for the groom plug-in
- L20 _public prototype_ `UGroomPluginSettings();`
- L24 _public member_ `float GroomCacheLookAheadBuffer;` — `UPROPERTY(config, EditAnywhere, Category=GroomCache, meta = (ClampMin = "0.05", ClampMax = "60.0", DisplayName = "Look-Ahead Buffer (in seconds)"))` — The amount of groom cache animation (in seconds) to pre-load ahead of time by the streaming manager

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomRBFDeformer.h` (Public)


#### struct `FGroomRBFDeformer`  
`struct FGroomRBFDeformer`  
_L13-43_
- L32 _public prototype_ `void GetRBFDeformedGroomAsset( const UGroomAsset* InGroomAsset, const UGroomBindingAsset* BindingAsset, FTextureSource* MaskTextureSource, const float MaskScale, UGroomAsset* OutGroomAsset, const ITargetPlatform* TargetPlatform = nullptr, bool bShouldBuildStaticMeshes = true);` — Return a new GroomAsset with the RBF deformation from the BindingAsset baked into it If bShouldBuildStaticMeshes is true, this function will ensure the static meshes owned by the groom are built after being modified. In this case, GetRBFDeformedGroomAsset can only be called from the Game Thread. If bShouldBuildStaticMeshes is false, GetRBFDeformedGroomAsset may be called from a background thread, but the caller must: 1.	Call ConditionalPostLoad and PreEditChange on each ImportedMesh returned by both GetHairGroupsCards and GetHairGroupsMeshes *before* calling GetRBFDeformedGroomAsset. 2.	Call UStaticMesh::BatchBuild and MarkPackageDirty on the same ImportedMeshes *after* calling GetRBFDeformedGroomAsset to begin async building of the meshes. To block until the async build is finished (if necessary), call FStaticMeshCompilingManager::Get().FinishAllCompilation().
- L41 _public prototype_ `static uint32 GetEntryCount(uint32 InSampleCount);`
- L42 _public prototype_ `static uint32 GetWeightCount(uint32 InSampleCount);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomResources.h` (Public)


#### enum `EHairStrandsResourcesType`  
`enum class EHairStrandsResourcesType : uint8`  
_L27-32_
- L29 _public enumerator_ `Guides` — Guides used for simulation
- L30 _public enumerator_ `Strands` — Rendering strands
- L31 _public enumerator_ `Cards` — Guides used for deforming the cards geometry (which is different from the simulation guides)

#### enum `EHairStrandsAllocationType`  
`enum class EHairStrandsAllocationType : uint8`  
_L34-38_
- L36 _public enumerator_ `Immediate` — Resources are allocated immediately
- L37 _public enumerator_ `Deferred` — Resources allocation is deferred to first usage

#### struct `FHairResourceName`  
`struct FHairResourceName`  
_L42-59_
- L44 _public prototype_ `FHairResourceName() = default;`
- L46 _public function_ `FHairResourceName(const FName& In) : AssetName(In)`
- L47 _public function_ `FHairResourceName(const FName& In, int32 InGroupIndex) : AssetName(In), GroupIndex(InGroupIndex)`
- L48 _public function_ `FHairResourceName(const FName& In, int32 InGroupIndex, int32 InLODIndex) : AssetName(In), GroupIndex(InGroupIndex), InLODIndex(InLODIndex)`
- L50 _public member_ `FName AssetName;`
- L51 _public member_ `int32 GroupIndex = -1;`
- L52 _public member_ `int32 LODIndex = -1;`
- L53 _public member_ `TArray<FString> Names;`
- L55 _public function_ `FHairResourceName(const FName& In)`
- L56 _public function_ `FHairResourceName(const FName& In, int32 InGroupIndex)`
- L57 _public function_ `FHairResourceName(const FName& In, int32 InGroupIndex, int32 InLODIndex)`

#### enum `EHairResourceLoadingType`  
`enum class EHairResourceLoadingType : uint8`  
_L64-68_
- L66 _public enumerator_ `Async`
- L67 _public enumerator_ `Sync`

#### struct `EHairResourceStatus`  
`struct EHairResourceStatus`  
_L70-82_
- L78 _public function_ `void AddAvailableCurve(uint32 In)`
- L79 _public function_ `bool HasStatus(EStatus In) const`
- L80 _public member_ `EStatus Status = EStatus::None;`
- L81 _public member_ `uint32 AvailableCurveCount = 0;`

#### enum `EHairResourceStatus::EStatus`  
`enum class EStatus : uint8`  
_L72-77_
- L74 _public enumerator_ `None = 0`
- L75 _public enumerator_ `Loading = 1`
- L76 _public enumerator_ `Valid = 2`

#### struct `FHairCommonResource`  
`struct FHairCommonResource : public FRenderResource`  
_L96-131_
- inherits: `FRenderResource`
- desc: Hair resouces which whom allocation can be deferred
- L99 _public prototype_ `FHairCommonResource(EHairStrandsAllocationType AllocationType, const FHairResourceName& InResourceName, const FName& InOwnerName, bool bUseRenderGraph=true);` — Build the hair strands resource
- L102 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — Init/Release buffers (FRenderResource)
- L103 _public prototype_ `virtual void ReleaseRHI() override;`
- L106 _public prototype_ `void Allocate(FRDGBuilder& GraphBuilder, EHairResourceLoadingType LoadingType);` — Init/Release buffers (FHairCommonResource)
- L107 _public prototype_ `void Allocate(FRDGBuilder& GraphBuilder, EHairResourceLoadingType LoadingType, EHairResourceStatus& Status);`
- L108 _public prototype_ `void Allocate(FRDGBuilder& GraphBuilder, EHairResourceLoadingType LoadingType, EHairResourceStatus& Status, uint32 InRequestedCurveCount, uint32 InRequestedPointCount, bool bAllowDeallocation=true);`
- L110 _public prototype_ `void StreamInData();`
- L112 _public function_ `virtual void InternalAllocate()`
- L113 _public function_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder)`
- L114 _public function_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder, uint32 InCurveCount, uint32 InPointCount)`
- L115 _public function_ `virtual void InternalRelease()`
- L116 _public prototype_ `virtual bool InternalGetOrRequestData(uint32 InRequestedCurveCount, uint32 InRequestedPointCount);`
- L117 _public function_ `virtual void InternalResetLoadedSize()`
- L118 _public function_ `virtual FHairStrandsBulkCommon* InternalGetBulkData()`
- L120 _public member_ `bool bUseRenderGraph = true;`
- L121 _public member_ `bool bIsInitialized = false;`
- L122 _public member_ `EHairStrandsAllocationType AllocationType = EHairStrandsAllocationType::Deferred;`
- L125 _public member_ `FHairResourceName ResourceName;` — Store (precis) debug name
- L126 _public member_ `FName OwnerName;`
- L129 _public member_ `FHairStreamingRequest StreamingRequest;` — Handle streaming request
- L130 _public member_ `uint32 MaxAvailableCurveCount = HAIR_MAX_NUM_CURVE_PER_GROUP;`

#### struct `FHairStrandsRestResource`  
`struct FHairStrandsRestResource : public FHairCommonResource`  
_L137-218_
- inherits: `FHairCommonResource`
- desc: Render buffers that will be used for rendering
- L140 _public prototype_ `FHairStrandsRestResource(FHairStrandsBulkData& InBulkData, EHairStrandsResourcesType CurveType, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L143 _public prototype_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder) override;` — Init/Release buffers
- L144 _public prototype_ `virtual void InternalRelease() override;`
- L145 _public prototype_ `virtual bool InternalGetOrRequestData(uint32 InRequestedCurveCount, uint32 InRequestedPointCount) override;`
- L146 _public prototype_ `virtual void InternalResetLoadedSize() override;`
- L147 _public function_ `virtual FHairStrandsBulkCommon* InternalGetBulkData() override`
- L150 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L152 _public prototype_ `FRDGExternalBuffer GetTangentBuffer(class FRDGBuilder& GraphBuilder, class FGlobalShaderMap* ShaderMap, uint32 PointCount, uint32 CurveCount);`
- L154 _public function_ `FVector GetPositionOffset() const`
- L157 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L173 _public member_ `FRDGExternalBuffer PositionBuffer;` — Strand hair rest position buffer
- L176 _public member_ `FRDGExternalBuffer PositionOffsetBuffer;` — Strand hair rest offset position buffer
- L179 _public member_ `FRDGExternalBuffer TangentBuffer;` — Strand hair tangent buffer (non-allocated unless used for static geometry)
- L182 _public member_ `FRDGExternalBuffer PointAttributeBuffer;` — Strand hair per-point attribute buffer
- L185 _public member_ `FRDGExternalBuffer CurveAttributeBuffer;` — Strand hair per-curve attribute buffer
- L188 _public member_ `FRDGExternalBuffer CurveMappingBuffer;` — Strand hair per-curve source mapping buffer
- L191 _public member_ `FRDGExternalBuffer PointMappingBuffer;` — Strand hair per-point source mapping buffer
- L194 _public member_ `FRDGExternalBuffer PointToCurveBuffer;` — Strand hair vertex to curve index mapping
- L197 _public member_ `FRDGExternalBuffer CurveBuffer;` — Strand hair curves buffer (contains curves' points offset and count)
- L200 _public member_ `FHairStrandsBulkData& BulkData;` — Reference to the hair strands render data
- L203 _public member_ `const EHairStrandsResourcesType CurveType;` — Type of curves
- L206 _public member_ `TArray<FPackedHairCurve> CurveData;` — Curve: Point offset & count
- L208 _public function_ `inline uint32 GetPointCount() const`
- L209 _public function_ `inline uint32 GetCurveCount() const`
- L211 _public function_ `inline uint32 GetSourcePointCount() const`
- L212 _public function_ `inline uint32 GetSourceCurveCount() const`
- L214 _public member_ `uint32 CachedTangentPointCount = 0;`
- L217 _public member_ `TMap<FString,FRDGExternalBuffer> ExternalBuffers;` — List of external buffers

#### struct `FHairStrandsDeformedResource`  
`struct FHairStrandsDeformedResource : public FHairCommonResource`  
_L220-301_
- inherits: `FHairCommonResource`
- L223 _public prototype_ `FHairStrandsDeformedResource(FHairStrandsBulkData& BulkData, EHairStrandsResourcesType CurveType, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L226 _public prototype_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder, uint32 InCurveCount, uint32 InPointCount) override;` — Init/Release buffers
- L227 _public prototype_ `virtual void InternalRelease() override;`
- L230 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L233 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L244 _public member_ `FRDGExternalBuffer DeformedPositionBuffer[2];` — Strand hair deformed position buffer (previous and current)
- L247 _public member_ `FRDGExternalBuffer DeformedOffsetBuffer[2];` — Strand hair deformed position buffer (previous and current)
- L250 _public member_ `FRDGExternalBuffer TangentBuffer;` — Strand hair tangent buffer
- L253 _public member_ `FRDGExternalBuffer DeformerBuffer;` — Strand hair deformer buffer. This buffer is optionally created & filled in by a mesh deformer
- L254 _public member_ `FRDGExternalBuffer DeformerPointAttributeBuffer;`
- L255 _public member_ `FRDGExternalBuffer DeformerCurveAttributeBuffer;`
- L258 _public member_ `FVector PositionOffset[2] = {FVector::ZeroVector, FVector::ZeroVector};` — Position offset as the deformed positions are expressed in relative coordinate (16bits)
- L261 _public member_ `FHairStrandsBulkData& BulkData;` — Reference to the hair strands render data
- L264 _public member_ `uint32 CurrentIndex = 0;` — Whether the GPU data should be initialized with the asset data or not
- L270 _public member_ `uint32 UniqueViewIDs[2] = { 0, 0 };` — Track the view which has update the formed position. This is used when rendering the same instance accross several editor viewport (not views of the same viewport), to prevent incorrect motion vector, as editor viewport are refresh not on the same tick, but with a throttling mechanism which make the updates not coherent.
- L273 _public member_ `const EHairStrandsResourcesType CurveType;` — Type of curves
- L282 _public function_ `inline uint32 GetIndex(EFrameType T) const` — Helper accessors
- L283 _public function_ `inline FRDGExternalBuffer& GetBuffer(EFrameType T)`
- L284 _public function_ `inline FVector& GetPositionOffset(EFrameType T)`
- L285 _public function_ `inline const FRDGExternalBuffer& GetPositionOffsetBuffer(EFrameType T) const`
- L286 _public function_ `inline FRDGExternalBuffer& GetPositionOffsetBuffer(EFrameType T)`
- L287 _public function_ `inline const FVector& GetPositionOffset(EFrameType T) const`
- L288 _public function_ `inline void SetPositionOffset(EFrameType T, const FVector& Offset)`
- L289 _public function_ `inline void SwapBuffer()`
- L290 _public function_ `inline uint32& GetUniqueViewID(EFrameType T)`
- L291 _public function_ `inline uint32 GetUniqueViewID(EFrameType T) const`
- L295 _public prototype_ `FRDGExternalBuffer& GetDeformerBuffer(FRDGBuilder& GraphBuilder);` — Return deformer buffers
- L296 _public prototype_ `FRDGExternalBuffer& GetDeformerCurveAttributeBuffer(FRDGBuilder& GraphBuilder);`
- L297 _public prototype_ `FRDGExternalBuffer& GetDeformerPointAttributeBuffer(FRDGBuilder& GraphBuilder);`
- L300 _public member_ `TMap<FString,FRDGExternalBuffer> ExternalBuffers;` — List of external buffers

#### enum `FHairStrandsDeformedResource::EFrameType`  
`enum EFrameType`  
_L275-279_
- L277 _public enumerator_ `Previous`
- L278 _public enumerator_ `Current`

#### struct `FHairStrandsInterpolationResource`  
`struct FHairStrandsInterpolationResource : public FHairCommonResource`  
_L304-335_
- inherits: `FHairCommonResource`
- L307 _public prototype_ `FHairStrandsInterpolationResource(FHairStrandsInterpolationBulkData& InBulkData, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L310 _public prototype_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder) override;` — Init/Release buffers
- L311 _public prototype_ `virtual void InternalRelease() override;`
- L312 _public prototype_ `virtual bool InternalGetOrRequestData(uint32 InRequestedCurveCount, uint32 InRequestedPointCount) override;`
- L313 _public prototype_ `virtual void InternalResetLoadedSize() override;`
- L314 _public function_ `virtual FHairStrandsBulkCommon* InternalGetBulkData() override`
- L317 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L320 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L328 _public function_ `bool UseSingleGuide() const`
- L330 _public member_ `FRDGExternalBuffer CurveInterpolationBuffer;`
- L331 _public member_ `FRDGExternalBuffer PointInterpolationBuffer;`
- L334 _public member_ `FHairStrandsInterpolationBulkData& BulkData;` — Reference to the hair strands interpolation render data

#### struct `FHairStrandsClusterResource`  
`struct FHairStrandsClusterResource : public FHairCommonResource`  
_L338-372_
- inherits: `FHairCommonResource`
- L340 _public prototype_ `FHairStrandsClusterResource(FHairStrandsClusterBulkData& Data, const FHairResourceName& ResourceName, const FName& OwnerName);`
- L343 _public prototype_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder) override;` — Init/Release buffers
- L344 _public prototype_ `virtual void InternalRelease() override;`
- L345 _public prototype_ `virtual bool InternalGetOrRequestData(uint32 InRequestedCurveCount, uint32 InRequestedPointCount) override;`
- L346 _public prototype_ `virtual void InternalResetLoadedSize() override;`
- L347 _public function_ `virtual FHairStrandsBulkCommon* InternalGetBulkData() override`
- L350 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L353 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L363 _public member_ `FRDGExternalBuffer ClusterInfoBuffer;` — Cluster info buffer
- L366 _public member_ `FRDGExternalBuffer CurveToClusterIdBuffer;` — CurveId => ClusterId to know which AABB to contribute to
- L369 _public member_ `FRDGExternalBuffer PointLODBuffer;` — Min. LOD a which a Point becomes visible
- L371 _public member_ `FHairStrandsClusterBulkData& BulkData;`

#### struct `FHairStrandsCullingResource`  
`struct FHairStrandsCullingResource : public FHairCommonResource`  
_L374-400_
- inherits: `FHairCommonResource`
- L376 _public prototype_ `FHairStrandsCullingResource(uint32 InPointCount, uint32 InCurveCount, uint32 InClusterCount, const FHairResourceName& InResourceName, const FName& InOwnerName);`
- L379 _public prototype_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder, uint32 InCurveCount, uint32 InPointCount) override;` — Init/Release buffers
- L380 _public prototype_ `virtual void InternalRelease() override;`
- L383 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L386 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L396 _public member_ `uint32 ClusterCount = 0;`
- L397 _public member_ `uint32 MaxPointCount = 0;`
- L398 _public member_ `uint32 MaxCurveCount = 0;`
- L399 _public member_ `FHairGroupPublicData::FCulling Resources;`

#### struct `FHairStrandsLODRestRootResource`  
`struct FHairStrandsLODRestRootResource : public FHairCommonResource`  
_L403-486_
- inherits: `FHairCommonResource`
- desc: Render buffers for root deformation for dynamic meshes
- L406 _public prototype_ `FHairStrandsLODRestRootResource(TArray<FHairStrandsRootBulkData>& InBulkDataArray, int32 InBulkDataIndex, EHairStrandsResourcesType CurveType, uint32 InMeshLODIndex, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L409 _public prototype_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder, uint32 InCurveCount, uint32 InPointCount) override;` — Init/Release buffers
- L410 _public prototype_ `virtual void InternalRelease() override;`
- L411 _public prototype_ `virtual bool InternalGetOrRequestData(uint32 InRequestedCurveCount, uint32 InRequestedPointCount) override;`
- L412 _public prototype_ `virtual void InternalResetLoadedSize() override;`
- L413 _public function_ `virtual FHairStrandsBulkCommon* InternalGetBulkData() override`
- L416 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L419 _public prototype_ `void Reset();` — Populate GPU LOD data from RootData (this function doesn't initialize resources)
- L422 _public function_ `uint32 GetRootCount()const` — Accessors
- L425 _public function_ `inline bool IsBulkDataValid() const` — Accessor to deference bulk data
- L427 _public function_ `inline const FHairStrandsRootBulkData& GetBulkData() const`
- L433 _public function_ `inline FHairStrandsRootBulkData& GetBulkData()`
- L440 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L455 _public function_ `const bool IsDataValid() const`
- L456 _public function_ `const bool IsValid() const`
- L457 _public member_ `EStatus Status = EStatus::Invalid;`
- L458 _public member_ `uint32 AvailableCurveCount = 0;`
- L463 _public member_ `FRDGExternalBuffer UniqueTriangleIndexBuffer;` — When the projection is done with source to target mesh transfer, the projection indices does not match. In this case we need to separate index computation. The barycentric coords remain the same however.
- L465 _public member_ `FRDGExternalBuffer RootToUniqueTriangleIndexBuffer;` — Strands hair root to unique triangle index
- L466 _public member_ `FRDGExternalBuffer RootBarycentricBuffer;`
- L469 _public member_ `FRDGExternalBuffer RestUniqueTrianglePositionBuffer;` — Strand hair roots translation and rotation in rest position relative to the bound triangle. Positions are relative to the rest root center
- L472 _public member_ `uint32 SampleCount = 0;` — Strand hair mesh interpolation matrix and sample indices
- L473 _public member_ `FRDGExternalBuffer MeshInterpolationWeightsBuffer;`
- L474 _public member_ `FRDGExternalBuffer MeshSampleIndicesAndSectionsBuffer;`
- L475 _public member_ `FRDGExternalBuffer RestSamplePositionsBuffer;`
- L478 _public member_ `TArray<FHairStrandsRootBulkData>& BulkDataArray;` — Store CPU data for root info & root binding
- L479 _public member_ `int32 BulkDataIndex = -1;`
- L482 _public member_ `const EHairStrandsResourcesType CurveType;` — Type of curves
- L485 _public member_ `const uint32 MeshLODIndex = 0;` — Mesh LOD index for this root resource. Used for sanity check

#### enum `FHairStrandsLODRestRootResource::EStatus`  
`enum class EStatus`  
_L453-453_
- L453 _public enumerator_ `enum class EStatus { Invalid, Initialized, Completed }; const bool IsDataValid() const { return GetBulkData().Header.RootCount > 0 && GetBulkData().Header.LODIndex >= 0; } const bool IsValid() const { return Status == EStatus::Completed; } EStatus Status = EStatus::Invalid; uint32 AvailableCurveCount = 0;`
- L453 _public enumerator_ `enum class EStatus { Invalid, Initialized, Completed }; const bool IsDataValid() const { return GetBulkData().Header.RootCount > 0 && GetBulkData().Header.LODIndex >= 0; } const bool IsValid() const { return Status == EStatus::Completed; } EStatus Status = EStatus::Invalid; uint32 AvailableCurveCount = 0;`
- L453 _public enumerator_ `enum class EStatus { Invalid, Initialized, Completed }; const bool IsDataValid() const { return GetBulkData().Header.RootCount > 0 && GetBulkData().Header.LODIndex >= 0; } const bool IsValid() const { return Status == EStatus::Completed; } EStatus Status = EStatus::Invalid; uint32 AvailableCurveCount = 0;`

#### struct `FHairStrandsRestRootResource`  
`struct FHairStrandsRestRootResource`  
_L489-545_
- desc: Render buffers for root deformation for dynamic meshes
- L492 _public prototype_ `FHairStrandsRestRootResource(TArray<FHairStrandsRootBulkData>& BulkData, EHairStrandsResourcesType CurveType, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L494 _public prototype_ `void Allocate(FRDGBuilder& GraphBuilder, EHairResourceLoadingType LoadingType, EHairResourceStatus& Status, int32 InMeshLODIndex);`
- L495 _public prototype_ `void Allocate(FRDGBuilder& GraphBuilder, EHairResourceLoadingType LoadingType, EHairResourceStatus& Status, uint32 InRequestedCurveCount, uint32 InRequestedPointCount, bool bAllowDeallocation , int32 InMeshLODIndex);`
- L496 _public prototype_ `void StreamInData(int32 MeshLODIndex);`
- L499 _public prototype_ `void BeginInitResource();` — Forward call to each mesh LOD version
- L500 _public prototype_ `void BeginUpdateResourceRHI();`
- L501 _public prototype_ `void ReleaseResource();`
- L502 _public prototype_ `void InternalResetLoadedSize();`
- L505 _public function_ `bool IsDataValid(int32 InMeshLODIndex) const` — Accessors
- L506 _public function_ `bool IsValid(int32 InMeshLODIndex) const`
- L507 _public function_ `FHairStrandsLODRestRootResource* GetLOD(int32 InMeshLODIndex)`
- L508 _public function_ `const FHairStrandsLODRestRootResource* GetLOD(int32 InMeshLODIndex) const`
- L510 _public function_ `uint32 GetLODCount() const`
- L511 _public function_ `uint32 GetRootCount() const`
- L530 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L541 _public member_ `TArray<FHairStrandsLODRestRootResource*> LODs;` — Store the hair projection information for each mesh LOD
- L544 _public member_ `const EHairStrandsResourcesType CurveType;` — Type of curves

#### struct `FHairStrandsLODDeformedRootResource`  
`struct FHairStrandsLODDeformedRootResource : public FHairCommonResource`  
_L548-621_
- inherits: `FHairCommonResource`
- desc: Render buffers for root deformation for dynamic meshes
- L551 _public prototype_ `FHairStrandsLODDeformedRootResource (FHairStrandsRestRootResource* InRestResources, EHairStrandsResourcesType CurveType, const uint32 MeshLODIndex, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L554 _public prototype_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder, uint32 InCurveCount, uint32 InPointCount) override;` — Init/Release buffers
- L555 _public prototype_ `virtual void InternalRelease() override;`
- L558 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L561 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L583 _public function_ `bool IsDataValid() const` — A LOD is considered valid as long as its resources are initialized. Its state will become completed once its triangle position will be update, but in order to be update its status needs to be valid.
- L584 _public function_ `bool IsValid() const`
- L585 _public member_ `EStatus Status = EStatus::Invalid;`
- L586 _public member_ `uint32 AvailableCurveCount = 0;`
- L589 _public member_ `FRDGExternalBuffer DeformedUniqueTrianglePositionBuffer[2];` — Strand hair roots translation and rotation in triangle-deformed position relative to the bound triangle. Positions are relative the deformed root center
- L592 _public member_ `uint32 SampleCount = 0;` — Strand hair mesh interpolation matrix and sample indices
- L593 _public member_ `FRDGExternalBuffer DeformedSamplePositionsBuffer[2];`
- L594 _public member_ `FRDGExternalBuffer MeshSampleWeightsBuffer[2];`
- L597 _public member_ `uint32 CurrentIndex = 0;` — Whether the GPU data should be initialized with the asset data or not
- L606 _public function_ `inline uint32 GetIndex(EFrameType T) const` — Double buffering is disabled by default unless the read-only cvar r.HairStrands.ContinuousDecimationReordering is set
- L607 _public function_ `inline const FRDGExternalBuffer& GetDeformedUniqueTrianglePositionBuffer(EFrameType T) const`
- L608 _public function_ `inline const FRDGExternalBuffer& GetDeformedSamplePositionsBuffer(EFrameType T) const`
- L609 _public function_ `inline const FRDGExternalBuffer& GetMeshSampleWeightsBuffer(EFrameType T) const`
- L610 _public function_ `inline void SwapBuffer()`
- L614 _public member_ `uint32 RootCount = 0;` — Store the hair projection information for each mesh LOD
- L617 _public member_ `const int32 MeshLODIndex = -1;` — Mesh index corresponding for this root data. Used for sanity check.
- L620 _public member_ `const EHairStrandsResourcesType CurveType;` — Type of curves

#### enum `FHairStrandsLODDeformedRootResource::EStatus`  
`enum class EStatus`  
_L578-578_
- L578 _public enumerator_ `enum class EStatus { Invalid, Initialized, Completed }; bool IsDataValid() const { return RootCount > 0 && MeshLODIndex >= 0; } bool IsValid() const { return Status == EStatus::Initialized || Status == EStatus::Completed; } EStatus Status = EStatus::Invalid;`
- L578 _public enumerator_ `enum class EStatus { Invalid, Initialized, Completed }; bool IsDataValid() const { return RootCount > 0 && MeshLODIndex >= 0; } bool IsValid() const { return Status == EStatus::Initialized || Status == EStatus::Completed; } EStatus Status = EStatus::Invalid;`
- L578 _public enumerator_ `enum class EStatus { Invalid, Initialized, Completed }; bool IsDataValid() const { return RootCount > 0 && MeshLODIndex >= 0; } bool IsValid() const { return Status == EStatus::Initialized || Status == EStatus::Completed; } EStatus Status = EStatus::Invalid;`

#### enum `FHairStrandsLODDeformedRootResource::EFrameType`  
`enum EFrameType`  
_L599-603_
- L601 _public enumerator_ `Previous`
- L602 _public enumerator_ `Current`

#### struct `FHairStrandsDeformedRootResource`  
`struct FHairStrandsDeformedRootResource`  
_L624-658_
- desc: Render buffers for root deformation for dynamic meshes
- L627 _public prototype_ `FHairStrandsDeformedRootResource(FHairStrandsRestRootResource* InRestResources, EHairStrandsResourcesType CurveType, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L630 _public prototype_ `void Allocate(FRDGBuilder& GraphBuilder, EHairResourceLoadingType LoadingType, EHairResourceStatus& Status, int32 InMeshLODIndex);` — Init/Release buffers
- L631 _public prototype_ `void Allocate(FRDGBuilder& GraphBuilder, EHairResourceLoadingType LoadingType, EHairResourceStatus& Status, uint32 InRequestedCurveCount, uint32 InRequestedPointCount, bool bAllowDeallocation, int32 InMeshLODIndex);`
- L632 _public prototype_ `void ReleaseResource();`
- L634 _public prototype_ `void SwapBuffer();` — void InternalRelease();
- L637 _public function_ `bool IsDataValid(int32 InMeshLODIndex) const` — Indirect if the current root resources are valid and up to date
- L638 _public function_ `bool IsValid(int32 InMeshLODIndex) const`
- L639 _public function_ `FHairStrandsLODDeformedRootResource* GetLOD(int32 InMeshLODIndex)`
- L640 _public function_ `const FHairStrandsLODDeformedRootResource* GetLOD(int32 InMeshLODIndex) const`
- L643 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L654 _public member_ `TArray<FHairStrandsLODDeformedRootResource*> LODs;` — Store the hair projection information for each mesh LOD
- L657 _public member_ `const EHairStrandsResourcesType CurveType;` — Type of curves

#### struct `FHairStrandsRaytracingResource`  
`struct FHairStrandsRaytracingResource : public FHairCommonResource`  
_L661-692_
- inherits: `FHairCommonResource`
- L664 _public prototype_ `FHairStrandsRaytracingResource(const FHairStrandsBulkData& InData, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L665 _public prototype_ `FHairStrandsRaytracingResource(const FHairCardsBulkData& InData, const FHairResourceName& ResourceName, const FName& OwnerName);`
- L666 _public prototype_ `FHairStrandsRaytracingResource(const FHairMeshesBulkData& InData, const FHairResourceName& ResourceName, const FName& OwnerName);`
- L669 _public prototype_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder, uint32 InCurveCount, uint32 InPointCount) override;` — Init/Release buffers
- L670 _public prototype_ `virtual void InternalRelease() override;`
- L673 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L676 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L684 _public member_ `FRDGExternalBuffer PositionBuffer;`
- L685 _public member_ `FRDGExternalBuffer IndexBuffer;`
- L686 _public member_ `FRayTracingGeometry RayTracingGeometry;`
- L687 _public member_ `uint32 MaxVertexCount = 0;`
- L688 _public member_ `uint32 MaxIndexCount = 0;`
- L689 _public member_ `bool bOwnBuffers = false;`
- L690 _public member_ `bool bIsRTGeometryInitialized = false;`
- L691 _public member_ `EHairStrandsRayTracingPrimitiveType RayTracingPrimitiveType = EHairStrandsRayTracingPrimitiveType::Triangle;`

#### class `FHairCardsVertexBuffer`  
`class FHairCardsVertexBuffer : public FVertexBufferWithSRV`  
_L698-702_
- inherits: `FVertexBufferWithSRV`
- L701 _public function_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override`

#### class `FHairCardIndexBuffer`  
`class FHairCardIndexBuffer : public FIndexBuffer`  
_L704-710_
- inherits: `FIndexBuffer`
- L707 _public member_ `const TArray<FHairCardsIndexFormat::Type>& Indices;`
- L708 _public prototype_ `FHairCardIndexBuffer(const TArray<FHairCardsIndexFormat::Type>& InIndices, const FName& InOwnerName);`
- L709 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`

#### struct `FHairCardsRestResource`  
`struct FHairCardsRestResource : public FHairCommonResource`  
_L713-759_
- inherits: `FHairCommonResource`
- desc: Render buffers that will be used for rendering
- L716 _public prototype_ `FHairCardsRestResource(const FHairCardsBulkData& InBulkData, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L718 _public prototype_ `virtual void InitResource(FRHICommandListBase& RHICmdList) override;`
- L719 _public prototype_ `virtual void ReleaseResource() override;`
- L722 _public prototype_ `virtual void InternalAllocate() override;` — Init/release buffers
- L723 _public prototype_ `virtual void InternalRelease() override;`
- L726 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L729 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L740 _public function_ `uint32 GetVertexCount() const`
- L741 _public function_ `uint32 GetPrimitiveCount() const`
- L744 _public member_ `FHairCardsVertexBuffer RestPositionBuffer;` — Strand hair rest position buffer
- L745 _public member_ `FHairCardIndexBuffer RestIndexBuffer;`
- L746 _public member_ `bool bInvertUV = false;`
- L748 _public member_ `FHairCardsVertexBuffer NormalsBuffer;`
- L749 _public member_ `FHairCardsVertexBuffer UVsBuffer;`
- L750 _public member_ `FHairCardsVertexBuffer MaterialsBuffer;`
- L751 _public member_ `FHairCardsVertexBuffer VertexColorsBuffer;`
- L753 _public member_ `TArray<FSamplerStateRHIRef> Samplers;`
- L754 _public member_ `TArray<FTextureReferenceRHIRef> Textures;`
- L755 _public member_ `uint32 LayoutIndex = 0;`
- L758 _public member_ `const FHairCardsBulkData& BulkData;` — Reference to the hair strands render data

#### struct `FHairCardsDeformedResource`  
`struct FHairCardsDeformedResource : public FHairCommonResource`  
_L761-801_
- inherits: `FHairCommonResource`
- L764 _public prototype_ `FHairCardsDeformedResource(const FHairCardsBulkData& BulkData, bool bInitializeData, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L767 _public prototype_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder) override;` — Init/release buffers
- L768 _public prototype_ `virtual void InternalRelease() override;`
- L771 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L774 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L783 _public member_ `FRDGExternalBuffer DeformedPositionBuffer[2];` — Strand hair deformed position buffer (previous and current)
- L784 _public member_ `FRDGExternalBuffer DeformedNormalBuffer;`
- L787 _public member_ `const FHairCardsBulkData& BulkData;` — Reference to the hair strands render data
- L790 _public member_ `const bool bInitializedData = false;` — Whether the GPU data should be initialized with the asset data or not
- L799 _public function_ `inline uint32 GetIndex(EFrameType T)` — Helper accessors
- L800 _public function_ `inline FRDGExternalBuffer& GetBuffer(EFrameType T)`

#### enum `FHairCardsDeformedResource::EFrameType`  
`enum EFrameType`  
_L792-796_
- L794 _public enumerator_ `Previous`
- L795 _public enumerator_ `Current`

#### struct `FHairCardsInterpolationResource`  
`struct FHairCardsInterpolationResource : public FHairCommonResource`  
_L803-827_
- inherits: `FHairCommonResource`
- L806 _public prototype_ `FHairCardsInterpolationResource(FHairCardsInterpolationBulkData& InBulkData, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L809 _public prototype_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder) override;` — Init/release buffers
- L810 _public prototype_ `virtual void InternalRelease() override;`
- L813 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L816 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L823 _public member_ `FRDGExternalBuffer InterpolationBuffer;`
- L826 _public member_ `FHairCardsInterpolationBulkData& BulkData;` — Reference to the hair strands interpolation render data

#### struct `FHairMeshesRestResource`  
`struct FHairMeshesRestResource : public FHairCommonResource`  
_L833-878_
- inherits: `FHairCommonResource`
- desc: Render buffers that will be used for rendering
- L836 _public prototype_ `FHairMeshesRestResource(const FHairMeshesBulkData& BulkData, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L838 _public prototype_ `virtual void InitResource(FRHICommandListBase& RHICmdList) override;`
- L839 _public prototype_ `virtual void ReleaseResource() override;`
- L842 _public prototype_ `virtual void InternalAllocate() override;` — Init/release buffers
- L843 _public prototype_ `virtual void InternalRelease() override;`
- L846 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L849 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L860 _public function_ `uint32 GetVertexCount() const`
- L861 _public function_ `uint32 GetPrimitiveCount() const`
- L864 _public member_ `FHairCardsVertexBuffer RestPositionBuffer;` — Strand hair rest position buffer
- L865 _public member_ `FHairCardIndexBuffer IndexBuffer;`
- L866 _public member_ `bool bInvertUV = false;`
- L868 _public member_ `FHairCardsVertexBuffer NormalsBuffer;`
- L869 _public member_ `FHairCardsVertexBuffer UVsBuffer;`
- L870 _public member_ `FHairCardsVertexBuffer VertexColorsBuffer;`
- L872 _public member_ `TArray<FSamplerStateRHIRef> Samplers;`
- L873 _public member_ `TArray<FTextureReferenceRHIRef> Textures;`
- L874 _public member_ `uint32 LayoutIndex = 0;`
- L877 _public member_ `const FHairMeshesBulkData& BulkData;` — Reference to the hair strands render data

#### struct `FHairMeshesDeformedResource`  
`struct FHairMeshesDeformedResource : public FHairCommonResource`  
_L882-925_
- inherits: `FHairCommonResource`
- desc: Render buffers that will be used for rendering
- L885 _public prototype_ `FHairMeshesDeformedResource(const FHairMeshesBulkData& InBulkData, bool bInInitializedData, const FHairResourceName& ResourceName, const FName& OwnerName);` — Build the hair strands resource
- L888 _public prototype_ `virtual void InternalAllocate(FRDGBuilder& GraphBuilder) override;` — Init/release buffers
- L889 _public prototype_ `virtual void InternalRelease() override;`
- L892 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L895 _public function_ `uint32 GetResourcesSize() const` — Return the memory size for GPU resources
- L904 _public member_ `FRDGExternalBuffer DeformedPositionBuffer[2];` — Strand hair deformed position buffer (previous and current)
- L907 _public member_ `const FHairMeshesBulkData& BulkData;` — Reference to the hair strands render data
- L910 _public member_ `const bool bInitializedData = false;` — Whether the GPU data should be initialized with the asset data or not
- L913 _public member_ `uint32 CurrentIndex = 0;` — Whether the GPU data should be initialized with the asset data or not
- L922 _public function_ `inline uint32 GetIndex(EFrameType T)` — Helper accessors
- L923 _public function_ `inline FRDGExternalBuffer& GetBuffer(EFrameType T)`
- L924 _public function_ `inline void SwapBuffer()`

#### enum `FHairMeshesDeformedResource::EFrameType`  
`enum EFrameType`  
_L915-919_
- L917 _public enumerator_ `Previous`
- L918 _public enumerator_ `Current`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DerivedData` (scope `UE`)
- L22 _function_ `inline uint32 GetBufferTotalNumBytes(const FRDGExternalBuffer& In)`
- L41 _macro_ `#define HAIR_RESOURCE_DEBUG_NAME 0` — Hair resource name - Allow more precise resource name for debug purpose. Enabled with HAIR_RESOURCE_DEBUG_NAME
- L84 _function_ `inline EHairResourceStatus operator& (EHairResourceStatus In, EHairResourceStatus::EStatus InStatus)`
- L85 _function_ `inline EHairResourceStatus operator| (EHairResourceStatus In, EHairResourceStatus::EStatus InStatus)`
- L86 _function_ `inline EHairResourceStatus& operator|=(EHairResourceStatus&Out, EHairResourceStatus::EStatus InStatus)`
- L88 _function_ `inline bool operator! (EHairResourceStatus A)`
- L90 _prototype_ `EHairResourceLoadingType GetHairResourceLoadingType(EHairGeometryType InGeometryType, int32 InLODIndex);`
- L929 _prototype_ `void CreateHairStrandsDebugDatas(const FHairStrandsDatas& InData, FHairStrandsDebugDatas& Out);` — Debug data (used for debug visalization but also for texture generation)
- L930 _prototype_ `void CreateHairStrandsDebugResources(class FRDGBuilder& GraphBuilder, const FHairStrandsDebugDatas* In, FHairStrandsDebugResources* Out);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomSettings.h` (Public)


#### struct `FGroomConversionSettings`  
`struct FGroomConversionSettings`  
_L10-26_
- reflection: `USTRUCT(BlueprintType)`
- L14 _public function_ `FGroomConversionSettings() : Rotation(FVector::ZeroVector) , Scale(FVector(1.0f, 1.0f, 1.0f))`
- L21 _public member_ `FVector Rotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conversion)` — Rotation in Euler angles in degrees to fix up or front axes
- L25 _public member_ `FVector Scale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conversion)` — Scale value to convert file unit into centimeters

#### enum `EGroomInterpolationQuality`  
`enum class EGroomInterpolationQuality : uint8`  
_L29-35_
- reflection: `UENUM()`
- L31 _public enumerator_ `Low UMETA(DisplayName = "Low", ToolTip = "Build interpolation data based on nearst neighbor search. Low quality interpolation data, but fast to build (takes a few minutes)")`
- L32 _public enumerator_ `Medium UMETA(DisplayName = "Medium", ToolTip = "Build interpolation data using curve shape matching search but within a limited spatial range. This is a tradeoff between Low and high quality in term of quality & build time (can takes several dozen of minutes)")`
- L33 _public enumerator_ `High UMETA(DisplayName = "High", ToolTip = "Build interpolation data using curve shape matching search. This result in high quality interpolation data, but is relatively slow to build (can takes several dozen of minutes)")`
- L34 _public enumerator_ `Unknown UMETA(Hidden)`

#### enum `EGroomInterpolationWeight`  
`enum class EGroomInterpolationWeight : uint8`  
_L38-44_
- reflection: `UENUM()`
- L40 _public enumerator_ `Parametric UMETA(DisplayName = "Parametric", ToolTip = "Build interpolation data based on curve parametric distance")`
- L41 _public enumerator_ `Root UMETA(DisplayName = "Root", ToolTip = "Build interpolation data based on distance between guide's root and strands's root")`
- L42 _public enumerator_ `Index UMETA(DisplayName = "Index", ToolTip = "Build interpolation data based on guide and strands vertex indices")`
- L43 _public enumerator_ `Unknown UMETA(Hidden)`

#### struct `FGroomBuildSettings`  
`struct FGroomBuildSettings`  
_L47-85_
- reflection: `USTRUCT(BlueprintType)`
- L51 _public function_ `FGroomBuildSettings() : bOverrideGuides(false) , HairToGuideDensity(0.1f) , InterpolationQuality(EGroomInterpolationQuality::High) , InterpolationDistance(EGroomInterpolationWeight::Parametric) , bRandomizeGuide(false) , bUseUniqueGuide(false)`
- L62 _public member_ `bool bOverrideGuides;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildSettings", meta = (ToolTip = "If checked, override imported guides with generated ones."))` — Flag to override the imported guides with generated guides.
- L66 _public member_ `float HairToGuideDensity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildSettings", meta = (ClampMin = "0", UIMin = "0", UIMax = "1.0"))` — Density factor for converting hair into guide curve if no guides are provided.
- L70 _public member_ `EGroomInterpolationQuality InterpolationQuality;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildSettings")` — Interpolation data quality.
- L74 _public member_ `EGroomInterpolationWeight InterpolationDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildSettings")` — Interpolation distance metric.
- L78 _public member_ `bool bRandomizeGuide;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildSettings")` — Randomize which guides affect a given hair strand.
- L82 _public member_ `bool bUseUniqueGuide;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildSettings")` — Force a hair strand to be affected by a unique guide.

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomTextureBuilder.h` (Public)


#### struct `FFollicleInfo`  
`struct FFollicleInfo`  
_L24-32_
- L28 _public member_ `UGroomAsset*GroomAsset = nullptr;`
- L29 _public member_ `EChannel Channel = R;`
- L30 _public member_ `uint32 KernelSizeInPixels = 0;`
- L31 _public member_ `bool bGPUOnly = false;` — Indirect of the texture should be saved on CPU, or if it will only be used directly on GPU

#### enum `FFollicleInfo::EChannel`  
`enum EChannel`  
_L26-26_
- L26 _public enumerator_ `enum EChannel { R = 0, G = 1, B = 2, A = 3 }; UGroomAsset*GroomAsset = nullptr; EChannel Channel = R; uint32 KernelSizeInPixels = 0; bool bGPUOnly = false;`
- L26 _public enumerator_ `enum EChannel { R = 0, G = 1, B = 2, A = 3 }; UGroomAsset*GroomAsset = nullptr; EChannel Channel = R; uint32 KernelSizeInPixels = 0; bool bGPUOnly = false;`
- L26 _public enumerator_ `enum EChannel { R = 0, G = 1, B = 2, A = 3 }; UGroomAsset*GroomAsset = nullptr; EChannel Channel = R; uint32 KernelSizeInPixels = 0; bool bGPUOnly = false;`
- L26 _public enumerator_ `enum EChannel { R = 0, G = 1, B = 2, A = 3 }; UGroomAsset*GroomAsset = nullptr; EChannel Channel = R; uint32 KernelSizeInPixels = 0; bool bGPUOnly = false;`

#### struct `FStrandsTexturesInfo`  
`struct FStrandsTexturesInfo`  
_L37-51_
- L39 _public member_ `EHairTextureLayout Layout = EHairTextureLayout::Layout1;`
- L40 _public member_ `UGroomAsset* GroomAsset = nullptr;`
- L41 _public member_ `USkeletalMesh* SkeletalMesh = nullptr;`
- L42 _public member_ `UStaticMesh* StaticMesh = nullptr;`
- L43 _public member_ `uint32 Resolution = 2048;`
- L44 _public member_ `uint32 LODIndex = 0;`
- L45 _public member_ `uint32 SectionIndex = 0;`
- L46 _public member_ `uint32 UVChannelIndex = 0;`
- L47 _public member_ `float MaxTracingDistance = 1;`
- L48 _public member_ `int32 TracingDirection = 1;`
- L49 _public member_ `uint32 Dilation = 0;`
- L50 _public member_ `TArray<int32> GroupIndices;`

#### struct `FStrandsTexturesOutput`  
`struct FStrandsTexturesOutput`  
_L53-57_
- L55 _public member_ `TArray<UTexture2D*> Textures;`
- L56 _public function_ `bool IsValid() const`

#### struct `FGroomTextureBuilder`  
`struct FGroomTextureBuilder`  
_L61-76_
- L65 _public prototype_ `static UTexture2D* CreateGroomFollicleMaskTexture(const UGroomAsset* GroomAsset, uint32 Resolution);`
- L67 _public prototype_ `static void AllocateFollicleTextureResources(UTexture2D* OuTexture);`
- L68 _public prototype_ `static void AllocateFollicleTextureResources(UTexture2D* OuTexture, const FIntPoint& Resolution, uint32 MipCount);`
- L69 _public prototype_ `static void BuildFollicleTexture(const TArray<FFollicleInfo>& InInfos, UTexture2D* OutFollicleTexture, bool bUseGPU);`
- L73 _public prototype_ `static FStrandsTexturesOutput CreateGroomStrandsTexturesTexture(const UGroomAsset* GroomAsset, uint32 Resolution, EHairTextureLayout InLayout);`
- L74 _public prototype_ `static void BuildStrandsTextures(const FStrandsTexturesInfo& InInfo, const FStrandsTexturesOutput& Output);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/HairAttributes.h` (Public)


#### enum `EHairAttribute`  
`enum class EHairAttribute : uint8`  
_L50-61_
- L52 _public enumerator_ `RootUV`
- L53 _public enumerator_ `ClumpID`
- L54 _public enumerator_ `StrandID`
- L55 _public enumerator_ `PrecomputedGuideWeights`
- L56 _public enumerator_ `Color`
- L57 _public enumerator_ `Roughness`
- L58 _public enumerator_ `AO`
- L59 _public enumerator_ `Width`
- L60 _public enumerator_ `Count`

#### enum `EHairAttributeFlags`  
`enum class EHairAttributeFlags : uint8`  
_L65-69_
- L67 _public enumerator_ `HasRootUDIM`
- L68 _public enumerator_ `HasMultipleClumpIDs`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace HairAttribute`
- L9 _namespace_ `namespace Vertex` (scope `HairAttribute`)
- L11 _externvar_ `extern const FName Color;` (scope `HairAttribute::Vertex`) — FVector
- L12 _externvar_ `extern const FName Roughness;` (scope `HairAttribute::Vertex`) — float
- L13 _externvar_ `extern const FName AO;` (scope `HairAttribute::Vertex`) — float
- L14 _externvar_ `extern const FName Position;` (scope `HairAttribute::Vertex`) — FVector
- L15 _externvar_ `extern const FName Width;` (scope `HairAttribute::Vertex`) — float
- L18 _namespace_ `namespace Strand` (scope `HairAttribute`)
- L20 _externvar_ `extern const FName Color;` (scope `HairAttribute::Strand`) — FVector
- L21 _externvar_ `extern const FName Roughness;` (scope `HairAttribute::Strand`) — float
- L22 _externvar_ `extern const FName GroupID;` (scope `HairAttribute::Strand`) — int
- L23 _externvar_ `extern const FName Guide;` (scope `HairAttribute::Strand`) — int
- L24 _externvar_ `extern const FName ID;` (scope `HairAttribute::Strand`) — int
- L25 _externvar_ `extern const FName ClumpID;` (scope `HairAttribute::Strand`) — int
- L26 _externvar_ `extern const FName RootUV;` (scope `HairAttribute::Strand`) — FVector2f
- L27 _externvar_ `extern const FName VertexCount;` (scope `HairAttribute::Strand`) — int
- L28 _externvar_ `extern const FName Width;` (scope `HairAttribute::Strand`) — float
- L29 _externvar_ `extern const FName ClosestGuides;` (scope `HairAttribute::Strand`) — FVector
- L30 _externvar_ `extern const FName GuideWeights;` (scope `HairAttribute::Strand`) — FVector
- L31 _externvar_ `extern const FName BasisType;` (scope `HairAttribute::Strand`) — FName (EGroomBasisType)
- L32 _externvar_ `extern const FName CurveType;` (scope `HairAttribute::Strand`) — FName (EGroomCurveType)
- L33 _externvar_ `extern const FName Knots;` (scope `HairAttribute::Strand`) — float[]
- L34 _externvar_ `extern const FName GroupName;` (scope `HairAttribute::Strand`) — FName
- L35 _externvar_ `extern const FName GroupCardsName;` (scope `HairAttribute::Strand`) — FName
- L38 _namespace_ `namespace Groom` (scope `HairAttribute`)
- L40 _externvar_ `extern const FName Color;` (scope `HairAttribute::Groom`) — FVector
- L41 _externvar_ `extern const FName Roughness;` (scope `HairAttribute::Groom`) — float
- L42 _externvar_ `extern const FName MajorVersion;` (scope `HairAttribute::Groom`) — int
- L43 _externvar_ `extern const FName MinorVersion;` (scope `HairAttribute::Groom`) — int
- L44 _externvar_ `extern const FName Tool;` (scope `HairAttribute::Groom`) — FName
- L45 _externvar_ `extern const FName Properties;` (scope `HairAttribute::Groom`) — FName
- L46 _externvar_ `extern const FName Width;` (scope `HairAttribute::Groom`) — float
- L62 _prototype_ `bool HasHairAttribute(uint32 In, EHairAttribute InAttribute);`
- L63 _prototype_ `void SetHairAttribute(uint32& Out, EHairAttribute InAttribute);`
- L70 _prototype_ `bool HasHairAttributeFlags(uint32 In, EHairAttributeFlags InFlag);`
- L71 _prototype_ `void SetHairAttributeFlags(uint32& Out, EHairAttributeFlags InFlag);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/HairCardsBuilder.h` (Public)


#### Free symbols / members of external scopes

- L22 _namespace_ `namespace FHairCardsBuilder`
- L24 _prototype_ `bool ImportGeometry( const UStaticMesh* StaticMesh, const FHairStrandsDatas& InGuidesData, const FHairStrandsDatas& InStrandsData, const FHairStrandsVoxelData& InStrandsVoxelData, const bool bGenerateGuidesFromCardGeometry, FHairCardsBulkData& OutBulk, FHairStrandsDatas& OutCardGuides, FHairCardsInterpolationBulkData& OutInterpolationBulkData);` (scope `FHairCardsBuilder`)
- L34 _prototype_ `bool ExtractCardsData( const UStaticMesh* StaticMesh, const FHairStrandsDatas& InStrandsData, FHairCardsDatas& Out);` (scope `FHairCardsBuilder`)
- L39 _prototype_ `FString GetVersion();` (scope `FHairCardsBuilder`)
- L42 _namespace_ `namespace FHairMeshesBuilder`
- L44 _prototype_ `void BuildGeometry( const FBox& InBox, FHairMeshesBulkData& OutBulk);` (scope `FHairMeshesBuilder`)
- L48 _prototype_ `void ImportGeometry( const UStaticMesh* StaticMesh, FHairMeshesBulkData& OutBulk);` (scope `FHairMeshesBuilder`)
- L52 _prototype_ `FString GetVersion();` (scope `FHairMeshesBuilder`)

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/HairCardsDatas.h` (Public)


#### struct `FHairCardsPositionFormat`  
`struct FHairCardsPositionFormat`  
_L16-23_
- L18 _public typedef_ `typedef FVector4f Type;`
- L19 _public member_ `static const uint32 ComponentCount = 1;`
- L20 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L21 _public member_ `static const EVertexElementType VertexElementType = VET_Float4;`
- L22 _public member_ `static const EPixelFormat Format = PF_A32B32G32R32F;`

#### struct `FHairCardsUVFormat`  
`struct FHairCardsUVFormat`  
_L25-33_
- L28 _public typedef_ `typedef FVector4f Type;` — Store atlas UV and (approximated) root UV
- L29 _public member_ `static const uint32 ComponentCount = 1;`
- L30 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L31 _public member_ `static const EVertexElementType VertexElementType = VET_Float4;`
- L32 _public member_ `static const EPixelFormat Format = PF_A32B32G32R32F;` — TODO

#### struct `FHairCardsMaterialFormat`  
`struct FHairCardsMaterialFormat`  
_L35-42_
- L37 _public typedef_ `typedef uint32 Type;`
- L38 _public member_ `static const uint32 ComponentCount = 1;`
- L39 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L40 _public member_ `static const EVertexElementType VertexElementType = VET_UByte4N;`
- L41 _public member_ `static const EPixelFormat Format = PF_R8G8B8A8;`

#### struct `FHairCardsNormalFormat`  
`struct FHairCardsNormalFormat`  
_L44-53_
- L46 _public typedef_ `typedef FPackedNormal Type;`
- L49 _public member_ `static const uint32 ComponentCount = 2;` — TangentX & tangentZ are packed into 2 * PF_R8G8B8A8_SNORM
- L50 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L51 _public member_ `static const EVertexElementType VertexElementType = VET_PackedNormal;`
- L52 _public member_ `static const EPixelFormat Format = PF_R8G8B8A8_SNORM;`

#### struct `FHairCardsIndexFormat`  
`struct FHairCardsIndexFormat`  
_L55-62_
- L57 _public typedef_ `typedef uint32 Type;`
- L58 _public member_ `static const uint32 ComponentCount = 1;`
- L59 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L60 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L61 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairCardsInterpolationVertex`  
`struct FHairCardsInterpolationVertex`  
_L64-68_
- L66 _public member_ `uint32 VertexIndex : 24;`
- L67 _public member_ `uint32 VertexLerp : 8;`

#### struct `FHairCardsInterpolationFormat`  
`struct FHairCardsInterpolationFormat`  
_L72-79_
- L74 _public typedef_ `typedef FHairCardsInterpolationVertex Type;`
- L75 _public member_ `static const uint32 ComponentCount = 1;`
- L76 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L77 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L78 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairCardsGeometry`  
`struct FHairCardsGeometry`  
_L85-156_
- desc: Data structure holding cards geometry information
- L94 _public member_ `TArray<FUVChannel>UVs;` — Geometry
- L95 _public member_ `TArray<FVector3f>Normals;`
- L96 _public member_ `TArray<FVector3f>Tangents;`
- L97 _public member_ `TArray<FVector3f>Positions;`
- L98 _public member_ `TArray<uint32> Indices;`
- L99 _public member_ `TArray<float> CoordU;` — Transient data storing [0..1] parametric value along main axis. This is used for generating guides & interpolation data
- L100 _public member_ `TArray<FVector2f>LocalUVs;` — Transient data storing [0..1, 0..1] local UV of the cards. U is aligned with the card's main direction, and V is aligned perpendicularity
- L101 _public member_ `TArray<FLinearColor> VertexColors;`
- L104 _public member_ `TArray<uint32> IndexOffsets;` — Index offset and index count of each cards geometry
- L105 _public member_ `TArray<uint32> IndexCounts;`
- L107 _public member_ `FBox3f BoundingBox = FBox3f(EForceInit::ForceInit);`
- L109 _public function_ `void Reset()`
- L126 _public function_ `void SetNum(uint32 Count)`
- L142 _public function_ `uint32 GetNumTriangles() const`
- L147 _public function_ `uint32 GetNumVertices() const`
- L152 _public function_ `uint32 GetNumCards() const`

#### struct `FHairCardsGeometry::FUVChannel`  
`struct FUVChannel`  
_L87-91_
- L89 _public member_ `TArray<FVector2f> UV;`
- L90 _public function_ `static constexpr uint32 GetCardUVIndex()`

#### struct `FHairCardsDatas`  
`struct FHairCardsDatas`  
_L158-163_
- L160 _public function_ `bool IsValid() const`
- L162 _public member_ `FHairCardsGeometry Cards;`

#### struct `FHairCardsBulkData`  
`struct FHairCardsBulkData`  
_L165-209_
- L167 _public function_ `bool IsValid() const`
- L168 _public function_ `void Reset()`
- L184 _public function_ `uint32 GetNumTriangles() const`
- L185 _public function_ `uint32 GetNumVertices() const`
- L186 _public function_ `const FBox& GetBounds() const`
- L187 _public function_ `uint32 GetNumUVs() const`
- L189 _public member_ `UTexture2D* DepthTexture = nullptr;`
- L190 _public member_ `UTexture2D* TangentTexture = nullptr;`
- L191 _public member_ `UTexture2D* CoverageTexture = nullptr;`
- L192 _public member_ `UTexture2D* AttributeTexture = nullptr;`
- L194 _public member_ `TArray<FHairCardsPositionFormat::Type> Positions;`
- L195 _public member_ `TArray<FHairCardsNormalFormat::Type> Normals;`
- L196 _public member_ `TArray<FHairCardsUVFormat::Type> UVs;`
- L197 _public member_ `TArray<FHairCardsMaterialFormat::Type> Materials;`
- L198 _public member_ `TArray<FHairCardsMaterialFormat::Type> VertexColors;`
- L199 _public member_ `TArray<FHairCardsIndexFormat::Type> Indices;`
- L206 _public member_ `} Header;`
- L208 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FHairCardsBulkData::FHeader`  
`struct FHeader`  
_L201-206_
- L203 _public member_ `FBox BoundingBox = FBox(EForceInit::ForceInit);`
- L204 _public member_ `uint32 NumUVs = 0;`
- L205 _public member_ `bool bVertexColor = false;`

#### struct `FHairCardsInterpolationDatas`  
`struct FHairCardsInterpolationDatas`  
_L215-234_
- desc: Hair cards points interpolation attributes
- L218 _public prototype_ `void SetNum(const uint32 NumPoints);` — Set the number of interpolated points
- L221 _public prototype_ `void Reset();` — Reset the interpolated points to 0
- L224 _public function_ `uint32 Num() const` — Get the number of interpolated points
- L227 _public member_ `TArray<int32> PointsSimCurvesIndex;` — Simulation curve indices
- L230 _public member_ `TArray<int32> PointsSimCurvesVertexIndex;` — Closest vertex indices on simulation curve
- L233 _public member_ `TArray<float> PointsSimCurvesVertexLerp;` — Lerp value between the closest vertex indices and the next one

#### struct `FHairCardsInterpolationBulkData`  
`struct FHairCardsInterpolationBulkData`  
_L236-241_
- L238 _public member_ `TArray<FHairCardsInterpolationFormat::Type> Interpolation;`
- L240 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FHairMeshes`  
`struct FHairMeshes`  
_L246-278_
- L254 _public member_ `TArray<FUVChannel>UVs;` — Geometry
- L255 _public member_ `TArray<FColor> VertexColors;`
- L256 _public member_ `TArray<FVector3f> Normals;`
- L257 _public member_ `TArray<FVector3f> Tangents;`
- L258 _public member_ `TArray<FVector3f> Positions;`
- L259 _public member_ `TArray<uint32> Indices;`
- L261 _public member_ `FBox3f BoundingBox = FBox3f(EForceInit::ForceInit);`
- L263 _public function_ `void SetNum(uint32 Count)`
- L276 _public function_ `uint32 GetNumTriangles() const`
- L277 _public function_ `uint32 GetNumVertices() const`

#### struct `FHairMeshes::FUVChannel`  
`struct FUVChannel`  
_L248-251_
- L250 _public member_ `TArray<FVector2f> UV;`

#### struct `FHairMeshesDatas`  
`struct FHairMeshesDatas`  
_L280-285_
- L282 _public function_ `bool IsValid() const`
- L284 _public member_ `FHairMeshes Meshes;`

#### struct `FHairMeshesBulkData`  
`struct FHairMeshesBulkData`  
_L287-310_
- L289 _public function_ `bool IsValid() const`
- L291 _public function_ `uint32 GetNumTriangles() const`
- L292 _public function_ `uint32 GetNumVertices() const`
- L293 _public function_ `const FBox& GetBounds() const`
- L294 _public function_ `uint32 GetNumUVs() const`
- L296 _public member_ `TArray<FHairCardsPositionFormat::Type> Positions;`
- L297 _public member_ `TArray<FHairCardsNormalFormat::Type> Normals;`
- L298 _public member_ `TArray<FHairCardsUVFormat::Type> UVs;`
- L299 _public member_ `TArray<FHairCardsMaterialFormat::Type> VertexColors;`
- L300 _public member_ `TArray<FHairCardsIndexFormat::Type> Indices;`
- L307 _public member_ `} Header;`
- L309 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FHairMeshesBulkData::FHeader`  
`struct FHeader`  
_L302-307_
- L304 _public member_ `FBox BoundingBox = FBox(EForceInit::ForceInit);`
- L305 _public member_ `uint32 NumUVs = 0;`
- L306 _public member_ `bool bVertexColor = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L70 _prototype_ `FArchive& operator<<(FArchive& Ar, FHairCardsInterpolationVertex& Vertex);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/HairCardsVertexFactory.h` (Public)


#### class `FRDGWrapperVertexBuffer`  
`class FRDGWrapperVertexBuffer : public FVertexBuffer`  
_L21-38_
- inherits: `FVertexBuffer`
- desc: Wrapper to reinterepet FRDGPooledBuffer as a FVertexBuffer
- L24 _public function_ `FRDGWrapperVertexBuffer()`
- L25 _public function_ `FRDGWrapperVertexBuffer(FRDGExternalBuffer& In): ExternalBuffer(In)`
- L26 _public function_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override`
- L32 _public function_ `virtual void ReleaseRHI() override`
- L37 _public member_ `FRDGExternalBuffer ExternalBuffer;`

#### class `FHairCardsVertexFactory`  
`class FHairCardsVertexFactory : public FVertexFactory`  
_L43-105_
- inherits: `FVertexFactory`
- desc: A vertex factory which simply transforms explicit vertex attributes from local to world space.
- L45 _private prototype_ `DECLARE_VERTEX_FACTORY_TYPE(FHairCardsVertexFactory);`
- L54 _public prototype_ `FHairCardsVertexFactory(FHairGroupInstance* Instance, uint32 LODIndex, EHairGeometryType GeometryType, EShaderPlatform InShaderPlatform, ERHIFeatureLevel::Type InFeatureLevel, const char* InDebugName);`
- L59 _public prototype_ `static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);` — Should we cache the material's shadertype on this platform with this vertex factory?
- L60 _public prototype_ `static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L61 _public prototype_ `static void ValidateCompiledResult(const FVertexFactoryType* Type, EShaderPlatform Platform, const FShaderParameterMap& ParameterMap, TArray<FString>& OutErrors);`
- L62 _public prototype_ `static void GetPSOPrecacheVertexFetchElements(EVertexInputStreamType VertexInputStreamType, FVertexDeclarationElementList& Elements);`
- L65 _public prototype_ `EPrimitiveIdMode GetPrimitiveIdMode(ERHIFeatureLevel::Type In) const;` — Return the primitive id supported by the VF
- L70 _public prototype_ `void SetData(const FDataType& InData);` — An implementation of the interface used by TSynchronizedResource to update the resource with new data from the game thread.
- L76 _public prototype_ `void Copy(const FHairCardsVertexFactory& Other);` — Copy the data from another vertex factory @param Other - factory to copy from
- L78 _public prototype_ `void InitResources(FRHICommandListBase& RHICmdList);`
- L79 _public prototype_ `virtual void ReleaseResource() override;`
- L82 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource interface.
- L83 _public prototype_ `virtual void ReleaseRHI() override;`
- L84 _public function_ `const FDataType& GetData() const`
- L85 _public member_ `FDataType Data;`
- L88 _protected member_ `bool bIsInitialized = false;`
- L90 _protected member_ `FRDGWrapperVertexBuffer DeformedPositionVertexBuffer[2];`
- L91 _protected member_ `FRDGWrapperVertexBuffer DeformedNormalVertexBuffer;`
- L104 _protected member_ `} DebugName;`

#### struct `FHairCardsVertexFactory::FDataType`  
`struct FDataType`  
_L47-52_
- L49 _public member_ `FHairGroupInstance* Instance = nullptr;`
- L50 _public member_ `uint32 LODIndex = 0;`
- L51 _public member_ `EHairGeometryType GeometryType = EHairGeometryType::NoneGeometry;`

#### struct `FHairCardsVertexFactory::FDebugName`  
`struct FDebugName`  
_L93-104_
- L95 _public function_ `FDebugName(const char* InDebugName) #if !UE_BUILD_SHIPPING : DebugName(InDebugName) #endif`
- L102 _private member_ `const char* DebugName;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/HairDescription.h` (Public)


#### struct `FStrandID`  
`struct FStrandID : public FElementID`  
_L17-39_
- inherits: `FElementID`
- L19 _public function_ `FStrandID()`
- L23 _public function_ `explicit FStrandID(const FElementID InitElementID) : FElementID(InitElementID.GetValue())`
- L28 _public function_ `explicit FStrandID(const int32 InitIDValue) : FElementID(InitIDValue)`
- L38 _public member_ `static const FStrandID Invalid;`

#### struct `FGroomID`  
`struct FGroomID : public FElementID`  
_L41-63_
- inherits: `FElementID`
- L43 _public function_ `FGroomID()`
- L47 _public function_ `explicit FGroomID(const FElementID InitElementID) : FElementID(InitElementID.GetValue())`
- L52 _public function_ `explicit FGroomID(const int32 InitIDValue) : FElementID(InitIDValue)`
- L62 _public member_ `static const FGroomID Invalid;`

#### class `FHairDescription`  
`class FHairDescription`  
_L65-122_
- L68 _public prototype_ `FHairDescription();`
- L70 _public prototype_ `~FHairDescription() = default;`
- L71 _public prototype_ `FHairDescription(const FHairDescription&) = default;`
- L72 _public prototype_ `FHairDescription(FHairDescription&&) = default;`
- L73 _public prototype_ `FHairDescription& operator=(const FHairDescription&) = default;`
- L74 _public prototype_ `FHairDescription& operator=(FHairDescription&&) = default;`
- L76 _public prototype_ `void InitializeVertices(int32 InNumVertices);`
- L77 _public prototype_ `void InitializeStrands(int32 InNumStrands);`
- L79 _public prototype_ `FVertexID AddVertex();`
- L80 _public prototype_ `FStrandID AddStrand();`
- L82 _public prototype_ `void Reset();`
- L83 _public prototype_ `bool IsValid() const;`
- L85 _public function_ `TAttributesSet<FVertexID>& VertexAttributes()`
- L86 _public function_ `const TAttributesSet<FVertexID>& VertexAttributes() const`
- L88 _public function_ `TAttributesSet<FStrandID>& StrandAttributes()`
- L89 _public function_ `const TAttributesSet<FStrandID>& StrandAttributes() const`
- L91 _public function_ `TAttributesSet<FGroomID>& GroomAttributes()`
- L92 _public function_ `const TAttributesSet<FGroomID>& GroomAttributes() const`
- L94 _public function_ `int32 GetNumVertices() const`
- L95 _public function_ `int32 GetNumStrands() const`
- L97 _public prototype_ `void Serialize(FArchive& Ar);`
- L100 _public prototype_ `bool HasAttribute(EHairAttribute InAttribute) const;` — #ueent_todo: Expose "remove" operations to allow editing HairDescription
- L103 _public prototype_ `bool HasRootUV() const;` — `UE_DEPRECATED(5.3, "HasRootUV accessor is deprecated. Use HasAttribute instead")`
- L105 _public prototype_ `bool HasClumpID() const;` — `UE_DEPRECATED(5.3, "HasClumpID accessor is deprecated. Use HasAttribute instead")`
- L107 _public prototype_ `bool HasGuideWeights() const;` — `UE_DEPRECATED(5.3, "HasGuideWeights accessor is deprecated. Use HasAttribute instead")`
- L109 _public prototype_ `bool HasColorAttributes() const;` — `UE_DEPRECATED(5.3, "HasColorAttributes accessor is deprecated. Use HasAttribute instead")`
- L111 _public prototype_ `bool HasRoughnessAttributes() const;` — `UE_DEPRECATED(5.3, "HasRoughnessAttributes accessor is deprecated. Use HasAttribute instead")`
- L113 _public prototype_ `bool HasAOAttributes() const;` — `UE_DEPRECATED(5.3, "HasAOAttributes accessor is deprecated. Use HasAttribute instead")`
- L116 _private member_ `TAttributesSet<FVertexID> VertexAttributesSet;`
- L117 _private member_ `TAttributesSet<FStrandID> StrandAttributesSet;`
- L118 _private member_ `TAttributesSet<FGroomID> GroomAttributesSet;`
- L120 _private member_ `int32 NumVertices;`
- L121 _private member_ `int32 NumStrands;`

#### struct `FHairDescriptionVersion`  
`struct FHairDescriptionVersion`  
_L124-133_
- L126 _public member_ `FCustomVersionContainer CustomVersions;`
- L127 _public member_ `FPackageFileVersion UEVersion;`
- L128 _public member_ `int32 LicenseeVersion = 0;`
- L129 _public member_ `bool bIsValid = false;`
- L130 _public function_ `bool IsValid() const`
- L131 _public prototype_ `void CopyVersionsFromArchive(const FArchive& Ar);`
- L132 _public prototype_ `void CopyVersionsToArchive(FArchive& Ar) const;`

#### struct `FHairDescriptionBulkData`  
`struct FHairDescriptionBulkData`  
_L139-172_
- desc: Bulk data storage for FHairDescription
- L142 _public function_ `FHairDescriptionBulkData()`
- L145 _public prototype_ `void Serialize(FArchive& Ar, UObject* Owner);`
- L148 _public prototype_ `void SaveHairDescription(FHairDescription& HairDescription);` — Stores a new hair description in the bulk data
- L151 _public prototype_ `void LoadHairDescription(FHairDescription& HairDescription);` — Loads the hair description from the bulk data
- L154 _public prototype_ `void Empty();` — Empties the bulk data
- L157 _public function_ `bool IsEmpty() const` — Returns true if there is nothing in the bulk data
- L160 _public prototype_ `FString GetIdString() const;` — Returns unique ID string for this bulk data
- L164 _private member_ `UE::Serialization::FEditorBulkData BulkData;` — Internally store bulk data as bytes
- L167 _private member_ `FHairDescriptionVersion BulkDataVersion;` — UE/Custom/Licensee version to propagate to archive when serializing the bulk data
- L170 _private member_ `bool bBulkDataUpdated = false;` — Whether the bulk data has been written via SaveHairDescription

#### Free symbols / members of external scopes

- L33 _function_ `inline friend uint32 GetTypeHash(const FStrandID& Other)`
- L57 _function_ `inline friend uint32 GetTypeHash(const FGroomID& Other)`
- L134 _prototype_ `FArchive& operator<<(FArchive& Ar, FHairDescriptionVersion& Version);`
- L174 _typedef_ `template <typename AttributeType> using TStrandAttributesRef = TMeshAttributesRef<FStrandID, AttributeType>;`
- L175 _typedef_ `template <typename AttributeType> using TStrandAttributesRef = TMeshAttributesRef<FStrandID, AttributeType>;`
- L177 _typedef_ `template <typename AttributeType> using TStrandAttributesConstRef = TMeshAttributesConstRef<FStrandID, AttributeType>;`
- L178 _typedef_ `template <typename AttributeType> using TStrandAttributesConstRef = TMeshAttributesConstRef<FStrandID, AttributeType>;`
- L181 _function_ `template <typename AttributeType> void SetHairVertexAttribute(FHairDescription& HairDescription, FVertexID VertexID, FName AttributeName, AttributeType AttributeValue)`
- L193 _function_ `template <typename AttributeType> void SetHairStrandAttribute(FHairDescription& HairDescription, FStrandID StrandID, FName AttributeName, AttributeType AttributeValue)`
- L205 _function_ `template <typename AttributeType> void SetGroomAttribute(FHairDescription& HairDescription, FGroomID GroomID, FName AttributeName, AttributeType AttributeValue)`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/HairStrandsCore.h` (Public)


#### struct `FHairAssetHelper`  
`struct FHairAssetHelper`  
_L18-32_
- L21 _public typedef_ `typedef void (*TCreateFilename)(const FString& InAssetName, const FString& Suffix, FString& OutPackageName, FString& OutAssetName);` — Generate a unique asset & package name
- L24 _public typedef_ `typedef void (*TRegisterAsset)(UObject* Out);` — Register a texture asset
- L27 _public typedef_ `typedef void (*TSaveAsset)(UObject* Object);` — Save an object within a package
- L29 _public member_ `TCreateFilename CreateFilename;`
- L30 _public member_ `TRegisterAsset RegisterAsset;`
- L31 _public member_ `TSaveAsset SaveAsset;`

#### class `FHairStrandsCore`  
`class FHairStrandsCore : public IModuleInterface`  
_L35-67_
- inherits: `IModuleInterface`
- desc: Implements the HairStrands module
- L41 _public prototype_ `virtual void StartupModule() override;`
- L42 _public prototype_ `virtual void ShutdownModule() override;`
- L43 _public function_ `virtual bool SupportsDynamicReloading() override`
- L45 _public prototype_ `static void RegisterAssetHelper(const FHairAssetHelper& Helper);`
- L48 _public prototype_ `static UTexture2D* CreateTexture(const FString& PackgeName, const FIntPoint& Resolution, const FString& Suffix, TTextureAllocation TextureAllocation);`
- L49 _public prototype_ `static void ResizeTexture(UTexture2D* InTexture, const FIntPoint& Resolution, TTextureAllocation TextureAllocation);`
- L50 _public prototype_ `static UStaticMesh* CreateStaticMesh(const FString& InPackageName, const FString& Suffix);`
- L54 _public prototype_ `static UGroomBindingAsset* CreateGroomBindingAsset(UGroomAsset* GroomAsset, USkeletalMesh* SourceSkelMesh, USkeletalMesh* TargetSkelMesh, const int32 NumInterpolationPoints, const int32 MatchingSection);` — `UE_DEPRECATED(4.27, "CreateGroomBindingAsset with SkeletalMesh is deprecated. Use the version with binding type and UObject instead.")` — Create binding asset from groom asset and skeletal asset. These functions are only valid when build with the editor. They will return null asset otherwise
- L56 _public prototype_ `static UGroomBindingAsset* CreateGroomBindingAsset(const FString& InPackageName, UObject* InParent, UGroomAsset* GroomAsset, USkeletalMesh* SourceSkelMesh, USkeletalMesh* TargetSkelMesh, const int32 NumInterpolationPoints, const int32 MatchingSection);` — `UE_DEPRECATED(4.27, "CreateGroomBindingAsset with SkeletalMesh is deprecated. Use the version with binding type and UObject instead.")`
- L59 _public prototype_ `static UGroomBindingAsset* CreateGroomBindingAsset(EGroomBindingMeshType BindingType, UGroomAsset* GroomAsset, UObject* Source, UObject* Target, const int32 NumInterpolationPoints, const int32 MatchingSection, const FName TargetMeshAttribute = NAME_None);` — Create binding asset from groom asset and assets of specified groom binding type
- L60 _public prototype_ `static UGroomBindingAsset* CreateGroomBindingAsset(EGroomBindingMeshType BindingType, const FString& InPackageName, UObject* InParent, UGroomAsset* GroomAsset, UObject* Source, UObject* Target, const int32 NumInterpolationPoints, const int32 MatchingSection, const FName TargetMeshAttribute = NAME_None);`
- L62 _public prototype_ `static void SaveAsset(UObject* Object);`
- L64 _public prototype_ `static FHairAssetHelper& AssetHelper();`

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef void (*TTextureAllocation)(UTexture2D* Out, const FIntPoint& Resolution, uint32 MipCount);` — typedef UTexture2D* (TCreateTextureHelper*)(FName Package, const FIntPoint& Resolution);

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/HairStrandsDatas.h` (Public)


#### struct `FPackedHairVertex`  
`struct FPackedHairVertex`  
_L40-48_
- L42 _public typedef_ `typedef uint64 BulkType;`
- L44 _public member_ `FFloat16 X, Y, Z;`
- L44 _public member_ `FFloat16 X, Y, Z;`
- L44 _public member_ `FFloat16 X, Y, Z;`
- L45 _public member_ `uint8 UCoord;`
- L46 _public member_ `uint8 Radius : 6;`
- L47 _public member_ `uint8 Type : 2;`

#### struct `FTranscodedHairPositions`  
`struct FTranscodedHairPositions`  
_L50-91_
- L52 _public typedef_ `typedef FUintVector4 BulkType;`
- L83 _public member_ `FPosition CP0;`
- L84 _public member_ `FPosition CP1;`
- L85 _public member_ `FPosition CP2;`

#### struct `FTranscodedHairPositions::FPosition`  
`struct FPosition`  
_L54-60_
- L56 _public member_ `uint32 X : 10;`
- L57 _public member_ `uint32 Y : 10;`
- L58 _public member_ `uint32 Z : 10;`
- L59 _public member_ `uint32 Type : 2;`

#### struct `FTranscodedHairPositions::FAttributePacking0`  
`struct FAttributePacking0`  
_L62-71_
- L64 _public member_ `uint32 Radius0 : 6;`
- L65 _public member_ `uint32 Radius1 : 6;`
- L66 _public member_ `uint32 Radius2 : 6;`
- L68 _public member_ `uint32 UCoord0 : 6;`
- L69 _public member_ `uint32 UCoord2 : 6;`
- L70 _public member_ `uint32 Interp : 2;`

#### struct `FTranscodedHairPositions::FAttributePacking1`  
`struct FAttributePacking1`  
_L73-81_
- L75 _public member_ `uint32 Radius0 : 6;`
- L76 _public member_ `uint32 Radius1 : 6;`
- L77 _public member_ `uint32 Radius2 : 6;`
- L79 _public member_ `uint32 UCoord0 : 7;`
- L80 _public member_ `uint32 UCoord1 : 7;`

#### union `FTranscodedHairPositions::(anonymous)`  
``  
_L87-90_

#### struct `FPackedHairAttribute0Vertex`  
`struct FPackedHairAttribute0Vertex`  
_L93-99_
- L95 _public typedef_ `typedef uint16 BulkType;`
- L97 _public member_ `uint8 NormalizedLength;`
- L98 _public member_ `uint8 Seed;`

#### struct `FPackedHairCurve`  
`struct FPackedHairCurve`  
_L101-107_
- L103 _public typedef_ `typedef uint32 BulkType;`
- L105 _public member_ `uint32 PointOffset : 24;`
- L106 _public member_ `uint32 PointCount : 8;`

#### struct `FVector4_16`  
`struct FVector4_16`  
_L109-115_
- L111 _public member_ `FFloat16 X;`
- L112 _public member_ `FFloat16 Y;`
- L113 _public member_ `FFloat16 Z;`
- L114 _public member_ `FFloat16 W;`

#### struct `FHairStrandsTranscodedPositionFormat`  
`struct FHairStrandsTranscodedPositionFormat`  
_L118-126_
- L120 _public typedef_ `typedef FTranscodedHairPositions Type;`
- L121 _public typedef_ `typedef FTranscodedHairPositions::BulkType BulkType;`
- L122 _public member_ `static const uint32 ComponentCount = 1;`
- L123 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L124 _public member_ `static const EVertexElementType VertexElementType = VET_UShort4;`
- L125 _public member_ `static const EPixelFormat Format = PF_Unknown;`

#### struct `FHairStrandsPositionFormat`  
`struct FHairStrandsPositionFormat`  
_L128-136_
- L130 _public typedef_ `typedef FPackedHairVertex Type;`
- L131 _public typedef_ `typedef FPackedHairVertex::BulkType BulkType;`
- L132 _public member_ `static const uint32 ComponentCount = 1;`
- L133 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L134 _public member_ `static const EVertexElementType VertexElementType = VET_UShort4;`
- L135 _public member_ `static const EPixelFormat Format = PF_Unknown;`

#### struct `FHairStrandsPositionOffsetFormat`  
`struct FHairStrandsPositionOffsetFormat`  
_L138-145_
- L140 _public typedef_ `typedef FVector4f Type;`
- L141 _public member_ `static const uint32 ComponentCount = 1;`
- L142 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L143 _public member_ `static const EVertexElementType VertexElementType = VET_Float4;`
- L144 _public member_ `static const EPixelFormat Format = PF_A32B32G32R32F;`

#### struct `FHairStrandsAttributeFormat`  
`struct FHairStrandsAttributeFormat`  
_L147-155_
- L149 _public typedef_ `typedef uint32 Type;`
- L150 _public typedef_ `typedef uint32 BulkType;`
- L151 _public member_ `static const uint32 ComponentCount = 1;`
- L152 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L153 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L154 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairStrandsPointToCurveFormat`  
`struct FHairStrandsPointToCurveFormat`  
_L157-165_
- L159 _public typedef_ `typedef uint32 Type;`
- L160 _public typedef_ `typedef uint32 BulkType;`
- L161 _public member_ `static const uint32 ComponentCount = 1;`
- L162 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L163 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L164 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairStrandsTangentFormat`  
`struct FHairStrandsTangentFormat`  
_L167-176_
- L169 _public typedef_ `typedef FPackedNormal Type;`
- L170 _public typedef_ `typedef uint32 BulkType;`
- L172 _public member_ `static const uint32 ComponentCount = 2;` — TangentX & tangentZ are packed into 2 * PF_R8G8B8A8_SNORM
- L173 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L174 _public member_ `static const EVertexElementType VertexElementType = VET_Float4;`
- L175 _public member_ `static const EPixelFormat Format = PF_R8G8B8A8_SNORM;`

#### struct `FHairStrandsInterpolationFormat`  
`struct FHairStrandsInterpolationFormat`  
_L178-187_
- L180 _public typedef_ `typedef uint32 Type;`
- L181 _public typedef_ `typedef uint32 BulkType;`
- L183 _public member_ `static const uint32 ComponentCount = 1;`
- L184 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L185 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L186 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairStrandsRootIndexFormat`  
`struct FHairStrandsRootIndexFormat`  
_L189-198_
- L191 _public typedef_ `typedef uint32 Type;`
- L192 _public typedef_ `typedef uint32 BulkType;`
- L194 _public member_ `static const uint32 ComponentCount = 1;`
- L195 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L196 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L197 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairStrandsCurveFormat`  
`struct FHairStrandsCurveFormat`  
_L200-209_
- L202 _public typedef_ `typedef FPackedHairCurve Type;`
- L203 _public typedef_ `typedef FPackedHairCurve::BulkType BulkType;`
- L205 _public member_ `static const uint32 ComponentCount = 1;`
- L206 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L207 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L208 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairStrandsRaytracingFormat`  
`struct FHairStrandsRaytracingFormat`  
_L211-219_
- L213 _public typedef_ `typedef FVector4f Type;`
- L215 _public member_ `static const uint32 ComponentCount = 1;`
- L216 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L217 _public member_ `static const EVertexElementType VertexElementType = VET_Float4;`
- L218 _public member_ `static const EPixelFormat Format = PF_A32B32G32R32F;`

#### struct `FHairStrandsIndexFormat`  
`struct FHairStrandsIndexFormat`  
_L222-230_
- desc: Hair strands index format
- L224 _public typedef_ `using Type = uint32;`
- L225 _public typedef_ `using BulkType = uint32;`
- L226 _public member_ `static const uint32 ComponentCount = 1;`
- L227 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L228 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L229 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairStrandsRBFSampleIndexFormat`  
`struct FHairStrandsRBFSampleIndexFormat`  
_L233-241_
- desc: Hair strands RBF sample index format
- L235 _public typedef_ `using Type = uint32;`
- L236 _public typedef_ `using BulkType = uint32;`
- L237 _public member_ `static const uint32 ComponentCount = 1;`
- L238 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L239 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L240 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairStrandsWeightFormat`  
`struct FHairStrandsWeightFormat`  
_L244-252_
- desc: Hair strands weights format
- L246 _public typedef_ `using Type = float;`
- L247 _public typedef_ `using BulkType = float;`
- L248 _public member_ `static const uint32 ComponentCount = 1;`
- L249 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L250 _public member_ `static const EVertexElementType VertexElementType = VET_Float1;`
- L251 _public member_ `static const EPixelFormat Format = PF_R32_FLOAT;`

#### struct `FHairStrandsMeshTrianglePositionFormat`  
`struct FHairStrandsMeshTrianglePositionFormat`  
_L257-265_
- desc: Skinned mesh triangle vertex position format
- L259 _public typedef_ `using Type = FVector4f;`
- L260 _public typedef_ `using BulkType = FVector4f;`
- L261 _public member_ `static const uint32 ComponentCount = 1;`
- L262 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L263 _public member_ `static const EVertexElementType VertexElementType = VET_Float4;`
- L264 _public member_ `static const EPixelFormat Format = PF_A32B32G32R32F;`

#### struct `FHairStrandsUniqueTriangleIndexFormat`  
`struct FHairStrandsUniqueTriangleIndexFormat`  
_L268-276_
- desc: Encode Section ID and triangle Index from the source skel. mesh
- L270 _public typedef_ `using Type = uint32;`
- L271 _public typedef_ `using BulkType = uint32;`
- L272 _public member_ `static const uint32 ComponentCount = 1;`
- L273 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L274 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L275 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairStrandsRootToUniqueTriangleIndexFormat`  
`struct FHairStrandsRootToUniqueTriangleIndexFormat`  
_L278-286_
- L280 _public typedef_ `using Type = uint32;`
- L281 _public typedef_ `using BulkType = uint32;`
- L282 _public member_ `static const uint32 ComponentCount = 1;`
- L283 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L284 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L285 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairStrandsRootBarycentricFormat`  
`struct FHairStrandsRootBarycentricFormat`  
_L288-296_
- L290 _public typedef_ `using Type = uint32;`
- L291 _public typedef_ `using BulkType = uint32;`
- L292 _public member_ `static const uint32 ComponentCount = 1;`
- L293 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L294 _public member_ `static const EVertexElementType VertexElementType = VET_UInt;`
- L295 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairStrandsRootUtils`  
`struct FHairStrandsRootUtils`  
_L298-306_
- L300 _public prototype_ `static uint32 PackTriangleIndex(uint32 TriangleIndex, uint32 SectionIndex);`
- L301 _public prototype_ `static void UnpackTriangleIndex(uint32 Encoded, uint32& OutTriangleIndex, uint32& OutSectionIndex);`
- L302 _public prototype_ `static uint32 PackBarycentrics(const FVector2f& B);`
- L303 _public prototype_ `static FVector2f UnpackBarycentrics(uint32 B);`
- L304 _public prototype_ `static uint32 PackUVs(const FVector2f& UV);`
- L305 _public prototype_ `static float PackUVsToFloat(const FVector2f& UV);`

#### struct `FHairClusterInfo`  
`struct FHairClusterInfo`  
_L311-338_
- desc: Structure describing the LOD settings (Screen size, vertex info, ...) for each clusters. The packed version of this structure corresponds to the GPU data layout (HairStrandsClusterCommon.ush) This uses by the GPU LOD selection.
- L313 _public member_ `static const uint32 MaxLOD = 8;`
- L322 _public typedef_ `typedef FUintVector4 BulkType;`
- L324 _public function_ `FHairClusterInfo()`
- L334 _public member_ `uint32 LODCount = 0;`
- L335 _public member_ `TStaticArray<float,MaxLOD> ScreenSize;`
- L336 _public member_ `TStaticArray<float,MaxLOD> RadiusScale;`
- L337 _public member_ `TStaticArray<bool, MaxLOD> bIsVisible;`

#### struct `FHairClusterInfo::Packed`  
`struct Packed`  
_L315-321_
- L317 _public member_ `uint32 Screen0;`
- L318 _public member_ `uint32 Screen1;`
- L319 _public member_ `uint32 Radius0;`
- L320 _public member_ `uint32 Radius1;`

#### struct `FHairLODInfo`  
`struct FHairLODInfo`  
_L340-347_
- L342 _public member_ `uint32 CurveCount = 0;`
- L343 _public member_ `uint32 PointCount = 0;`
- L344 _public member_ `float RadiusScale = 1;`
- L345 _public member_ `float ScreenSize = 1;`
- L346 _public member_ `bool bIsVisible = true;`

#### struct `FHairClusterInfoFormat`  
`struct FHairClusterInfoFormat`  
_L349-354_
- L351 _public typedef_ `typedef FHairClusterInfo::Packed Type;`
- L352 _public typedef_ `typedef FHairClusterInfo::Packed BulkType;`
- L353 _public member_ `static const uint32 SizeInByte = sizeof(Type);`

#### struct `FHairClusterIndexFormat`  
`struct FHairClusterIndexFormat`  
_L356-362_
- L358 _public typedef_ `typedef uint32 Type;`
- L359 _public typedef_ `typedef uint32 BulkType;`
- L360 _public member_ `static const uint32 SizeInByte = sizeof(Type);`
- L361 _public member_ `static const EPixelFormat Format = PF_R32_UINT;`

#### struct `FHairStreamingRequest`  
`struct FHairStreamingRequest`  
_L383-428_
- L401 _public prototype_ `void Request(uint32 InRequestedCurveCount, uint32 InRequestedPointCount, FHairStrandsBulkCommon& In, bool bWait=false, bool bFillBulkData=false, bool bWarmCache=false, const FName& InOwnerName = NAME_None, bool* bWaitResult = nullptr);`
- L404 _public prototype_ `bool IsNone() const;`
- L405 _public prototype_ `bool IsCompleted();`
- L406 _public prototype_ `bool IsUnloading() const;`
- L409 _public prototype_ `bool WarmCache(uint32 InRequestedCurveCount, uint32 InRequestedPointCount, FHairStrandsBulkCommon& In);`
- L414 _public member_ `FBulkDataBatchRequest IORequest;` — IO
- L417 _public member_ `FString PathName;` — DDC
- L418 _public member_ `TUniquePtr<UE::DerivedData::FRequestOwner> DDCRequestOwner;`
- L420 _public member_ `TArray<FChunk> Chunks;`
- L421 _public member_ `uint32 CurveCount = 0;`
- L422 _public member_ `uint32 PointCount = 0;`
- L423 _public member_ `int32 LODIndex = 0;`
- L427 _public member_ `bool bSupportOffsetLoad = true;` — When enabled, data can be loaded from an offset. Otherwisee, start from the beginning of the resource This is used when cooking data to force the loading of the entire resource (i.e., bSupportOffsetLoad=false)

#### struct `FHairStreamingRequest::FChunk`  
`struct FChunk`  
_L386-399_
- desc: Hold request at the container level (transient to the request)
- L389 _public member_ `FSharedBuffer Data_DDC;`
- L390 _public member_ `FIoBuffer Data_IO;`
- L391 _public member_ `uint32 Offset = 0;` — Offset to the requested data
- L392 _public member_ `uint32 Size = 0;` — Size of the requested data
- L393 _public member_ `uint32 TotalSize = 0;` — Size of the total data (existing + requested)
- L394 _public member_ `EStatus Status = EStatus::None;` — Status of the current request
- L395 _public member_ `FHairBulkContainer* Container = nullptr;`
- L397 _public prototype_ `const uint8* GetData() const;`
- L398 _public prototype_ `void Release();`

#### enum `FHairStreamingRequest::FChunk::EStatus`  
`enum EStatus`  
_L388-388_
- L388 _public enumerator_ `enum EStatus { None, Pending, Completed, Failed, Unloading }; FSharedBuffer Data_DDC; FIoBuffer Data_IO; uint32 Offset = 0; uint32 Size = 0; uint32 TotalSize = 0; EStatus Status = EStatus::None; FHairBulkContainer* Container = nullptr;`
- L388 _public enumerator_ `enum EStatus { None, Pending, Completed, Failed, Unloading }; FSharedBuffer Data_DDC; FIoBuffer Data_IO; uint32 Offset = 0; uint32 Size = 0; uint32 TotalSize = 0; EStatus Status = EStatus::None; FHairBulkContainer* Container = nullptr;`
- L388 _public enumerator_ `enum EStatus { None, Pending, Completed, Failed, Unloading }; FSharedBuffer Data_DDC; FIoBuffer Data_IO; uint32 Offset = 0; uint32 Size = 0; uint32 TotalSize = 0; EStatus Status = EStatus::None; FHairBulkContainer* Container = nullptr;`
- L388 _public enumerator_ `enum EStatus { None, Pending, Completed, Failed, Unloading }; FSharedBuffer Data_DDC; FIoBuffer Data_IO; uint32 Offset = 0; uint32 Size = 0; uint32 TotalSize = 0; EStatus Status = EStatus::None; FHairBulkContainer* Container = nullptr;`
- L388 _public enumerator_ `enum EStatus { None, Pending, Completed, Failed, Unloading }; FSharedBuffer Data_DDC; FIoBuffer Data_IO; uint32 Offset = 0; uint32 Size = 0; uint32 TotalSize = 0; EStatus Status = EStatus::None; FHairBulkContainer* Container = nullptr;`

#### struct `FHairBulkContainer`  
`struct FHairBulkContainer`  
_L433-450_
- L436 _public member_ `uint32 LoadedSize = 0;` — Streaming
- L437 _public member_ `FByteBulkData Data;`
- L438 _public member_ `FHairStreamingRequest::FChunk* ChunkRequest = nullptr;`
- L441 _public function_ `bool IsBulkDataLoaded() const` — Forward BulkData functions
- L442 _public function_ `int64 GetBulkDataSize() const`
- L443 _public function_ `FString GetDebugName() const`
- L444 _public function_ `void SetBulkDataFlags(uint32 Flags)`
- L445 _public function_ `void RemoveBulkData()`
- L446 _public function_ `void Serialize(FArchive& Ar, UObject* Owner, int32 ChunkIndex, bool bAttemptFileMapping)`
- L449 _public function_ `bool IsBulkDataEmptyOrLoaded()const` — Returns true if all loadable data is loaded, i.e. either the data is loaded or there's no data to load

#### struct `FHairStrandsBulkCommon`  
`struct FHairStrandsBulkCommon`  
_L452-492_
- L454 _public prototype_ `virtual ~FHairStrandsBulkCommon() = default;`
- L455 _public prototype_ `void Serialize(FArchive& Ar, UObject* Owner);`
- L456 _public prototype_ `virtual void SerializeHeader(FArchive& Ar, UObject* Owner) = 0;`
- L457 _public prototype_ `void SerializeData(FArchive& Ar, UObject* Owner);`
- L459 _public prototype_ `void Write_DDC(UObject* Owner, TArray<UE::DerivedData::FCachePutValueRequest>& Out);`
- L460 _public prototype_ `void Read_DDC(FHairStreamingRequest* In, TArray<UE::DerivedData::FCacheGetChunkRequest>& Out);`
- L461 _public prototype_ `void Write_IO(UObject* Owner, FArchive& Out);`
- L462 _public prototype_ `void Read_IO(FHairStreamingRequest* In, FBulkDataBatchRequest& Out);`
- L463 _public prototype_ `void Unload(FHairStreamingRequest* In);`
- L483 _public prototype_ `virtual uint32 GetResourceCount() const = 0;`
- L484 _public prototype_ `virtual void GetResources(FQuery& Out) = 0;`
- L485 _public function_ `virtual void GetResourceVersion(FArchive& Ar) const`
- L486 _public prototype_ `virtual void ResetLoadedSize() = 0;`
- L490 _public member_ `FString DerivedDataKey;` — Transient Name/DDCkey for streaming

#### struct `FHairStrandsBulkCommon::FQuery`  
`struct FQuery`  
_L465-481_
- L467 _public prototype_ `void Add(FHairBulkContainer& In, const TCHAR* InSuffix, uint32& InOffset, uint32 InSize=0);`
- L468 _public function_ `uint32 GetCurveCount() const`
- L469 _public function_ `uint32 GetPointCount() const`
- L471 _public member_ `EQueryType Type = None;`
- L472 _public member_ `FHairStreamingRequest* StreamingRequest = nullptr;`
- L473 _public member_ `FBulkDataBatchRequest::FBatchBuilder* OutReadIO = nullptr;`
- L474 _public member_ `FArchive* OutWriteIO = nullptr;`
- L476 _public member_ `TArray<UE::DerivedData::FCacheGetChunkRequest>* OutReadDDC = nullptr;`
- L477 _public member_ `TArray<UE::DerivedData::FCachePutValueRequest>* OutWriteDDC = nullptr;`
- L478 _public member_ `FString* DerivedDataKey = nullptr;`
- L480 _public member_ `UObject* Owner = nullptr;`

#### enum `FHairStrandsBulkCommon::FQuery::EQueryType`  
`enum EQueryType`  
_L470-470_
- L470 _public enumerator_ `enum EQueryType { None, ReadDDC, WriteDDC, ReadIO, ReadWriteIO , UnloadData}; EQueryType Type = None; FHairStreamingRequest* StreamingRequest = nullptr; FBulkDataBatchRequest::FBatchBuilder* OutReadIO = nullptr; FArchive* OutWriteIO = nullptr; #if WITH_EDITORONLY_DATA TArray<UE::DerivedData::FCacheGetChunkRequest>* OutReadDDC = nullptr; TArray<UE::DerivedData::FCachePutValueRequest>* OutWriteDDC = nullptr;`
- L470 _public enumerator_ `enum EQueryType { None, ReadDDC, WriteDDC, ReadIO, ReadWriteIO , UnloadData}; EQueryType Type = None; FHairStreamingRequest* StreamingRequest = nullptr; FBulkDataBatchRequest::FBatchBuilder* OutReadIO = nullptr; FArchive* OutWriteIO = nullptr; #if WITH_EDITORONLY_DATA TArray<UE::DerivedData::FCacheGetChunkRequest>* OutReadDDC = nullptr; TArray<UE::DerivedData::FCachePutValueRequest>* OutWriteDDC = nullptr;`
- L470 _public enumerator_ `enum EQueryType { None, ReadDDC, WriteDDC, ReadIO, ReadWriteIO , UnloadData}; EQueryType Type = None; FHairStreamingRequest* StreamingRequest = nullptr; FBulkDataBatchRequest::FBatchBuilder* OutReadIO = nullptr; FArchive* OutWriteIO = nullptr; #if WITH_EDITORONLY_DATA TArray<UE::DerivedData::FCacheGetChunkRequest>* OutReadDDC = nullptr; TArray<UE::DerivedData::FCachePutValueRequest>* OutWriteDDC = nullptr;`
- L470 _public enumerator_ `enum EQueryType { None, ReadDDC, WriteDDC, ReadIO, ReadWriteIO , UnloadData}; EQueryType Type = None; FHairStreamingRequest* StreamingRequest = nullptr; FBulkDataBatchRequest::FBatchBuilder* OutReadIO = nullptr; FArchive* OutWriteIO = nullptr; #if WITH_EDITORONLY_DATA TArray<UE::DerivedData::FCacheGetChunkRequest>* OutReadDDC = nullptr; TArray<UE::DerivedData::FCachePutValueRequest>* OutWriteDDC = nullptr;`
- L470 _public enumerator_ `enum EQueryType { None, ReadDDC, WriteDDC, ReadIO, ReadWriteIO , UnloadData}; EQueryType Type = None; FHairStreamingRequest* StreamingRequest = nullptr; FBulkDataBatchRequest::FBatchBuilder* OutReadIO = nullptr; FArchive* OutWriteIO = nullptr; #if WITH_EDITORONLY_DATA TArray<UE::DerivedData::FCacheGetChunkRequest>* OutReadDDC = nullptr; TArray<UE::DerivedData::FCachePutValueRequest>* OutWriteDDC = nullptr;`
- L470 _public enumerator_ `enum EQueryType { None, ReadDDC, WriteDDC, ReadIO, ReadWriteIO , UnloadData}; EQueryType Type = None; FHairStreamingRequest* StreamingRequest = nullptr; FBulkDataBatchRequest::FBatchBuilder* OutReadIO = nullptr; FArchive* OutWriteIO = nullptr; #if WITH_EDITORONLY_DATA TArray<UE::DerivedData::FCacheGetChunkRequest>* OutReadDDC = nullptr; TArray<UE::DerivedData::FCachePutValueRequest>* OutWriteDDC = nullptr;`

#### enum `EHairStrandsFlags`  
`enum class EHairStrandsFlags : uint8`  
_L497-506_
- L499 _public enumerator_ `HasTrimmedPoint = 1<<0`
- L500 _public enumerator_ `HasTrimmedCurve = 1<<1`
- L501 _public enumerator_ `HasInvalidPoint = 1<<2`
- L502 _public enumerator_ `HasExtraEndingPoint = 1<<3`
- L503 _public enumerator_ `HasShuffledCurve = 1<<4`
- L504 _public enumerator_ `HasDecimatedPoint = 1<<5`
- L505 _public enumerator_ `HasDecimatedCurve = 1<<6`

#### struct `FHairStrandsPoints`  
`struct FHairStrandsPoints`  
_L509-545_
- desc: Hair strands points attribute
- L512 _public prototype_ `void SetNum(const uint32 NumPoints, uint32 InAttributes, bool bHasMapping = false);` — Set the number of points
- L515 _public prototype_ `void Reset();` — Reset the points to 0
- L518 _public function_ `uint32 Num() const` — Get the number of points
- L520 _public prototype_ `bool HasAttribute(EHairAttribute In) const;`
- L523 _public member_ `TArray<FVector3f> PointsPosition;` — Points position in local space
- L526 _public member_ `TArray<float> PointsRadius;` — Normalized radius relative to the max one
- L529 _public member_ `TArray<float> PointsCoordU;` — Normalized length
- L532 _public member_ `TArray<FLinearColor> PointsBaseColor;` — Material per-vertex 'baked' base color (optional)
- L535 _public member_ `TArray<float> PointsRoughness;` — Material per-vertex 'baked' roughness (optional)
- L538 _public member_ `TArray<float> PointsAO;` — Material per-vertex 'baked' AO (optional)
- L541 _public member_ `TArray<uint32> PointsMapping;` — Points source mapping
- L544 _public member_ `uint32 SourcePointCount = 0;` — Source point count

#### struct `FHairStrandsCurves`  
`struct FHairStrandsCurves`  
_L548-598_
- desc: Hair strands Curves attribute
- L551 _public prototype_ `void SetNum(const uint32 NumPoints, uint32 InAttributes, bool bHasMapping = false);` — Set the number of Curves
- L554 _public prototype_ `void Reset();` — Reset the curves to 0
- L557 _public function_ `uint32 Num() const` — Get the number of Curves
- L559 _public prototype_ `bool HasPrecomputedWeights() const;`
- L561 _public prototype_ `bool HasAttribute(EHairAttribute In) const;`
- L564 _public member_ `TArray<uint16> CurvesCount;` — Number of points per rod
- L567 _public member_ `TArray<uint32> CurvesOffset;` — An offset represent the rod start in the point list
- L570 _public member_ `TArray<float> CurvesLength;` — Normalized length relative to the max one
- L573 _public member_ `TArray<FVector2f> CurvesRootUV;` — Roots UV. Support UDIM coordinate up to 256x256 (optional)
- L576 _public member_ `TArray<int> StrandIDs;` — Strand ID associated with each curve (optional)
- L579 _public member_ `TArray<FIntVector> ClumpIDs;` — Clump ID associated with each curve (optional)
- L582 _public member_ `TMap<int, int> GroomIDToIndex;` — Mapping of imported Groom ID to index
- L585 _public member_ `TArray<FIntVector> CurvesClosestGuideIDs;` — Custom guide IDs (indexed with StrandID) (optional)
- L588 _public member_ `TArray<FVector3f> CurvesClosestGuideWeights;` — Custom guid weights (indexed with StrandID) (optional)
- L591 _public member_ `uint32 AttributeFlags = 0;` — Flags for attributes
- L594 _public member_ `TArray<uint32> CurvesMapping;` — Curves source mapping
- L597 _public member_ `uint32 SourceCurveCount = 0;` — Source curve count

#### struct `FHairStrandsCommonDatas`  
`struct FHairStrandsCommonDatas`  
_L601-642_
- desc: Hair strands datas that are stored on CPU
- L619 _public function_ `uint32 GetNumPoints() const` — Get the total number of points
- L622 _public function_ `uint32 GetNumCurves() const` — Get the total number of Curves
- L624 _public prototype_ `uint32 GetAttributes() const;`
- L625 _public prototype_ `uint32 GetAttributeFlags() const;`
- L626 _public function_ `bool HasFlags(EHairStrandsFlags In) const`
- L628 _public prototype_ `void Reset();`
- L630 _public function_ `bool IsValid() const`
- L632 _public prototype_ `FHash GetHash() const;`
- L635 _public member_ `FHairStrandsPoints StrandsPoints;` — List of all the strands points
- L638 _public member_ `FHairStrandsCurves StrandsCurves;` — List of all the strands curves
- L641 _public member_ `uint32 Flags = 0;` — General flags (shuffled curve, extra ending point, ...)

#### struct `FHairStrandsCommonDatas::FHash`  
`struct FHash`  
_L603-616_
- L605 _public member_ `uint64 PositionHash = 0;`
- L606 _public member_ `uint64 CurveCountHash = 0;`
- L607 _public member_ `uint64 CurveOffsetHash = 0;`
- L609 _public function_ `bool operator==(const FHash& In) const`

#### struct `FHairStrandsRawDatas`  
`struct FHairStrandsRawDatas : public FHairStrandsCommonDatas`  
_L646-649_
- inherits: `FHairStrandsCommonDatas`
- desc: Unlike FHairStrandsDatas, this is raw datas, i.e. not processed by any built step
- L648 _public prototype_ `void Reset();`

#### struct `FHairStrandsDatas`  
`struct FHairStrandsDatas : public FHairStrandsCommonDatas`  
_L652-666_
- inherits: `FHairStrandsCommonDatas`
- desc: Built hair strands data (decimated/shuffled/...)
- L654 _public prototype_ `void Reset();`
- L657 _public prototype_ `static void CopyCurve(const FHairStrandsDatas& In, FHairStrandsDatas& Out, uint32 InAttributes, uint32 InIndex, uint32 OutIndex);` — Copy a point or a curve from In to Out data
- L658 _public prototype_ `static void CopyPoint(const FHairStrandsDatas& In, FHairStrandsDatas& Out, uint32 InAttributes, uint32 InIndex, uint32 OutIndex);`
- L659 _public prototype_ `static void CopyPointLerp(const FHairStrandsDatas& In, FHairStrandsDatas& Out, uint32 InAttributes, uint32 InIndex0, uint32 InIndex1, float InAlpha, uint32 OutIndex);`
- L662 _public member_ `float HairDensity = 1;` — The Standard Hair Density
- L665 _public member_ `FBox3f BoundingBox = FBox3f(EForceInit::ForceInit);` — Strands bounding box

#### struct `FHairStrandsBulkData`  
`struct FHairStrandsBulkData : FHairStrandsBulkCommon`  
_L668-783_
- inherits: `FHairStrandsBulkCommon`
- L683 _public prototype_ `static uint32 ConvertDataFlagsToHairStrandsFlags(uint32 In);`
- L684 _public prototype_ `static uint32 ConvertDataFlagsFromHairStrandsFlags(uint32 In);`
- L686 _public prototype_ `virtual void SerializeHeader(FArchive& Ar, UObject* Owner) override;`
- L687 _public prototype_ `virtual uint32 GetResourceCount() const override;`
- L688 _public prototype_ `virtual void GetResources(FQuery& Out) override;`
- L689 _public prototype_ `virtual void GetResourceVersion(FArchive& Ar) const override;`
- L691 _public function_ `bool IsValid() const`
- L692 _public prototype_ `void Reset();`
- L693 _public prototype_ `virtual void ResetLoadedSize() override;`
- L694 _public prototype_ `float GetCoverageScale(float InCurvePercentage ) const;`
- L696 _public prototype_ `bool IsCookedBulkDataLoadedForCPUAccess() const;`
- L699 _public function_ `uint32 GetNumCurves() const`
- L700 _public function_ `uint32 GetNumPoints() const`
- L701 _public function_ `uint32 GetNumSourceCurves() const`
- L702 _public function_ `uint32 GetNumSourcePoints() const`
- L703 _public function_ `float GetMaxLength() const`
- L704 _public function_ `float GetMaxRadius() const`
- L705 _public function_ `FVector GetPositionOffset() const`
- L706 _public function_ `const FBox& GetBounds() const`
- L707 _public prototype_ `uint32 GetSize() const;`
- L708 _public function_ `bool HasFlags(EDataFlags In) const`
- L710 _public function_ `uint32 GetCurveAttributeSizeInBytes(uint32 InCurveCount=HAIR_MAX_NUM_CURVE_PER_GROUP) const`
- L711 _public function_ `uint32 GetPointAttributeSizeInBytes(uint32 InPointCount=HAIR_MAX_NUM_POINT_PER_GROUP) const`
- L712 _public function_ `uint32 GetPointToCurveSizeInBytes(uint32 InPointCount=HAIR_MAX_NUM_POINT_PER_GROUP) const`
- L713 _public function_ `uint32 GetTranscodedPositionSizeInBytes(uint32 InPointCount = HAIR_MAX_NUM_POINT_PER_GROUP) const`
- L770 _public member_ `} Header;`
- L782 _public member_ `} Data;`

#### enum `FHairStrandsBulkData::EDataFlags`  
`enum EDataFlags`  
_L670-681_
- L672 _public enumerator_ `DataFlags_HasData = 0x1u` — Contains valid data. Otherwise: Position, Attributes, ... are all empty
- L673 _public enumerator_ `DataFlags_HasPointAttribute = 0x2` — Contains point attribute data.
- L674 _public enumerator_ `DataFlags_HasTranscodedPosition = 0x4u` — Contains transcoded position
- L675 _public enumerator_ `DataFlags_HasTrimmedCurve = 0x8u` — Source data had more curves per group than the limit and some curves were trimmed
- L676 _public enumerator_ `DataFlags_HasTrimmedPoint = 0x10u` — Source data had more points per curve than the limit and some points were trimmed
- L677 _public enumerator_ `DataFlags_HasPointMapping = 0x20u` — Contains platform to source points mapping data
- L678 _public enumerator_ `DataFlags_HasCurveMapping = 0x40u` — Contains platform to source curves mapping data
- L679 _public enumerator_ `DataFlags_HasShuffledCurves = 0x80u` — Curve data has been shuffled
- L680 _public enumerator_ `DataFlags_HasExtraEndingPoint = 0x100u` — Curve contains an extra ending control point

#### struct `FHairStrandsBulkData::FHeader`  
`struct FHeader`  
_L715-770_
- L717 _public member_ `uint32 CurveCount = 0;`
- L718 _public member_ `uint32 PointCount = 0;`
- L719 _public member_ `uint32 MinPointPerCurve = 0;`
- L720 _public member_ `uint32 MaxPointPerCurve = 0;`
- L721 _public member_ `uint32 AvgPointPerCurve = 0;`
- L722 _public member_ `float MaxLength = 0;`
- L723 _public member_ `float MaxRadius = 0;`
- L724 _public member_ `FBox BoundingBox = FBox(EForceInit::ForceInit);`
- L725 _public member_ `uint32 Flags = 0;`
- L726 _public member_ `uint32 CurveAttributeOffsets[HAIR_CURVE_ATTRIBUTE_COUNT] = {0};`
- L727 _public member_ `uint32 PointAttributeOffsets[HAIR_POINT_ATTRIBUTE_COUNT] = {0};`
- L730 _public member_ `uint32 ImportedAttributes = 0;` — Imported attribute info
- L731 _public member_ `uint32 ImportedAttributeFlags = 0;`
- L734 _public member_ `uint32 SourceCurveCount = 0;` — Imported (Source) point/curve info
- L735 _public member_ `uint32 SourcePointCount = 0;`
- L738 _public member_ `TArray<uint32> CurveToPointCount;` — Map 'curve' count to 'point' count (used for CLOD)
- L741 _public member_ `TArray<float> CoverageScales;` — Coverage scale
- L743 _public member_ `FHairStrandsCommonDatas::FHash Hash;`
- L750 _public member_ `} Transcoding;`
- L769 _public member_ `} Strides;`

#### struct `FHairStrandsBulkData::FHeader::FTranscoding`  
`struct FTranscoding`  
_L746-750_
- desc: Data transcoding parameters
- L748 _public member_ `FVector3f PositionOffset = FVector3f::OneVector;`
- L749 _public member_ `FVector3f PositionScale = FVector3f::OneVector;`

#### struct `FHairStrandsBulkData::FHeader::FStrides`  
`struct FStrides`  
_L753-769_
- desc: Data strides
- L755 _public member_ `uint32 PositionStride = 0;`
- L756 _public member_ `uint32 CurveStride = 0;`
- L757 _public member_ `uint32 PointToCurveChunkStride = 0;`
- L758 _public member_ `uint32 CurveAttributeChunkStride = 0;`
- L759 _public member_ `uint32 PointAttributeChunkStride = 0;`
- L760 _public member_ `uint32 TranscodedPositionChunkStride = 0;`
- L761 _public member_ `uint32 CurveMappingStride = 0;`
- L762 _public member_ `uint32 PointMappingStride = 0;`
- L765 _public member_ `uint32 PointToCurveChunkElementCount = 0;` — Number of element per chunk block
- L766 _public member_ `uint32 CurveAttributeChunkElementCount = 0;`
- L767 _public member_ `uint32 PointAttributeChunkElementCount = 0;`
- L768 _public member_ `uint32 TranscodedPositionChunkElementCount = 0;`

#### struct `FHairStrandsBulkData::FData`  
`struct FData`  
_L772-782_
- L774 _public member_ `FHairBulkContainer Positions;` — Size = PointCount
- L775 _public member_ `FHairBulkContainer TranscodedPositions;` — Size = PointCount / TranscodedPositionChunkElementCount (=3)
- L776 _public member_ `FHairBulkContainer CurveAttributes;` — Size = y*CurveCount (depends on the per-curve stored attributes)
- L777 _public member_ `FHairBulkContainer PointAttributes;` — Size = x*PointCount (depends on the per-point stored attributes)
- L778 _public member_ `FHairBulkContainer PointToCurve;` — Size = PointCount
- L779 _public member_ `FHairBulkContainer Curves;` — Size = CurveCount
- L780 _public member_ `FHairBulkContainer CurveMapping;` — Size = CurveCount
- L781 _public member_ `FHairBulkContainer PointMapping;` — Size = PointCount

#### struct `FHairStrandsInterpolationDatas`  
`struct FHairStrandsInterpolationDatas`  
_L789-820_
- desc: Hair strands points interpolation attributes
- L792 _public prototype_ `void SetNum(const uint32 InCurveCount, const uint32 InPointCount);` — Set the number of interpolated points
- L795 _public prototype_ `void Reset();` — Reset the interpolated points to 0
- L798 _public function_ `uint32 GetPointCount() const` — Get the number of interpolated points
- L799 _public function_ `uint32 GetCurveCount() const`
- L801 _public function_ `bool IsValid() const`
- L804 _public member_ `TArray<FIntVector2> CurveSimIndices;` — Simulation curve indices, ordered by closest influence (per-curve data)
- L807 _public member_ `TArray<FVector2f> CurveSimWeights;` — Weight of simulation curve, ordered by closest influence (per-curve data)
- L810 _public member_ `TArray<FIntVector2> CurveSimRootPointIndex;` — (Global) Index of the root point of the curve
- L813 _public member_ `TArray<FIntVector2> PointSimIndices;` — Closest vertex (local, 0..255) indices on simulation curve, ordered by closest influence (per-point data)
- L816 _public member_ `TArray<FVector2f> PointSimLerps;` — Lerp value between the closest vertex indices and the next one, ordered by closest influence (per-point data)
- L819 _public member_ `bool bUseUniqueGuide = false;` — True, if interpolation data are built using a single guide

#### struct `FHairStrandsInterpolationBulkData`  
`struct FHairStrandsInterpolationBulkData : FHairStrandsBulkCommon`  
_L822-860_
- inherits: `FHairStrandsBulkCommon`
- L830 _public prototype_ `void Reset();`
- L831 _public prototype_ `virtual void ResetLoadedSize() override;`
- L832 _public prototype_ `virtual void SerializeHeader(FArchive& Ar, UObject* Owner) override;`
- L834 _public prototype_ `virtual uint32 GetResourceCount() const override;`
- L835 _public prototype_ `virtual void GetResources(FQuery& Out) override;`
- L836 _public function_ `uint32 GetPointCount() const`
- L837 _public prototype_ `uint32 GetSize() const;`
- L839 _public prototype_ `bool IsCookedBulkDataLoadedForCPUAccess() const;`
- L853 _public member_ `} Header;`
- L859 _public member_ `} Data;`

#### enum `FHairStrandsInterpolationBulkData::EDataFlags`  
`enum EDataFlags`  
_L824-828_
- L826 _public enumerator_ `DataFlags_HasData = 1`
- L827 _public enumerator_ `DataFlags_HasSingleGuideData = 2`

#### struct `FHairStrandsInterpolationBulkData::FHeader`  
`struct FHeader`  
_L842-853_
- L844 _public member_ `uint32 Flags = 0;`
- L845 _public member_ `uint32 PointCount = 0;`
- L846 _public member_ `uint32 CurveCount = 0;`
- L852 _public member_ `} Strides;`

#### struct `FHairStrandsInterpolationBulkData::FHeader::FStrides`  
`struct FStrides`  
_L848-852_
- L850 _public member_ `uint32 CurveInterpolationStride = 0;`
- L851 _public member_ `uint32 PointInterpolationStride = 0;`

#### struct `FHairStrandsInterpolationBulkData::FData`  
`struct FData`  
_L855-859_
- L857 _public member_ `FHairBulkContainer CurveInterpolation;` — FHairStrandsInterpolationFormat  - Per-rendering-curve interpolation data (closest guides, weight factors, ...). Data for a 1 or 2 guide(s))
- L858 _public member_ `FHairBulkContainer PointInterpolation;` — FHairStrandsInterpolationFormat  - Per-rendering-point interpolation data (local point index, lerp factors,...). Data for a 1 or 2 guide(s))

#### struct `FHairStrandsClusterData`  
`struct FHairStrandsClusterData`  
_L865-880_
- L867 _public prototype_ `void Reset();`
- L868 _public function_ `bool IsValid() const`
- L871 _public member_ `TArray<FHairClusterInfo> ClusterInfos;` — LOD info for the various clusters for LOD management on GPU
- L872 _public member_ `TArray<uint32> CurveToClusterIds;`
- L873 _public member_ `TArray<FHairLODInfo> LODInfos;`
- L874 _public member_ `TArray<uint32> PointLODs;`
- L876 _public member_ `uint32 ClusterCount = 0;` — Number of clusters
- L877 _public member_ `float ClusterScale = 0;` — Cluster scale factor
- L878 _public member_ `uint32 PointCount = 0;` — Number of points
- L879 _public member_ `uint32 CurveCount = 0;` — Number of curves

#### struct `FHairStrandsClusterBulkData`  
`struct FHairStrandsClusterBulkData : FHairStrandsBulkCommon`  
_L882-924_
- inherits: `FHairStrandsBulkCommon`
- L884 _public prototype_ `void Reset();`
- L885 _public prototype_ `virtual void ResetLoadedSize() override;`
- L887 _public prototype_ `virtual void SerializeHeader(FArchive& Ar, UObject* Owner) override;`
- L888 _public prototype_ `virtual uint32 GetResourceCount() const override;`
- L889 _public prototype_ `virtual void GetResources(FQuery& Out) override;`
- L890 _public prototype_ `uint32 GetCurveCount(float InLODIndex) const;`
- L891 _public prototype_ `uint32 GetSize() const;`
- L893 _public prototype_ `bool IsCookedBulkDataLoadedForCPUAccess() const;`
- L896 _public function_ `bool IsValid() const`
- L915 _public member_ `} Header;`
- L923 _public member_ `} Data;`

#### struct `FHairStrandsClusterBulkData::FHeader`  
`struct FHeader`  
_L898-915_
- L901 _public member_ `TArray<FHairLODInfo> LODInfos;` — Curve count and Point count per LOD
- L903 _public member_ `uint32 ClusterCount = 0;`
- L904 _public member_ `float ClusterScale = 0;`
- L905 _public member_ `uint32 PointCount = 0;`
- L906 _public member_ `uint32 CurveCount = 0;`
- L907 _public member_ `FVector4f ClusterInfoParameters = FVector4f::Zero();` — xy:Scale/Offset for ScreenSize, zw:Scale/Offset for Radius
- L914 _public member_ `} Strides;`

#### struct `FHairStrandsClusterBulkData::FHeader::FStrides`  
`struct FStrides`  
_L909-914_
- L911 _public member_ `uint32 PackedClusterInfoStride = 0;`
- L912 _public member_ `uint32 CurveToClusterIdStride = 0;`
- L913 _public member_ `uint32 PointLODStride = 0;`

#### struct `FHairStrandsClusterBulkData::FData`  
`struct FData`  
_L917-923_
- L920 _public member_ `FHairBulkContainer PackedClusterInfos;` — LOD info for the various clusters for LOD management on GPU
- L921 _public member_ `FHairBulkContainer CurveToClusterIds;` — Size - CurveCount
- L922 _public member_ `FHairBulkContainer PointLODs;` — Size - PointCount / HAIR_POINT_LOD_COUNT_PER_UINT

#### struct `FHairStrandsRootData`  
`struct FHairStrandsRootData`  
_L930-985_
- desc: Source data for building root bulk data
- L932 _public prototype_ `void Reset();`
- L933 _public prototype_ `bool HasProjectionData() const;`
- L934 _public function_ `bool IsValid() const`
- L939 _public member_ `TArray<FHairStrandsRootToUniqueTriangleIndexFormat::Type> RootToUniqueTriangleIndexBuffer;` — When the projection is done with source to target mesh transfer, the projection indices does not match. In this case we need to separate index computation. The barycentric coords remain the same however.
- L940 _public member_ `TArray<FHairStrandsRootBarycentricFormat::Type> RootBarycentricBuffer;`
- L943 _public member_ `TArray<FHairStrandsUniqueTriangleIndexFormat::Type> UniqueTriangleIndexBuffer;` — Strand hair roots translation and rotation in rest position relative to the bound triangle. Positions are relative to the rest root center
- L944 _public member_ `TArray<FHairStrandsMeshTrianglePositionFormat::Type> RestUniqueTrianglePositionBuffer;`
- L948 _public member_ `TArray<FHairStrandsMeshTrianglePositionFormat::Type> RestUniqueTrianglePositionBuffer_TargetNonTransfered;` — This data is available if triangles transfer from source to target was needed.
- L951 _public member_ `uint32 SampleCount = 0;` — Number of samples used for the mesh interpolation
- L954 _public member_ `TArray<FHairStrandsWeightFormat::Type> MeshInterpolationWeightsBuffer;` — Store the hair interpolation weights | Size = SamplesCount * SamplesCount
- L957 _public member_ `TArray<uint32> MeshSampleIndicesBuffer;` — Store the samples vertex indices
- L960 _public member_ `TArray<FHairStrandsMeshTrianglePositionFormat::Type> RestSamplePositionsBuffer;` — Store the samples rest positions
- L963 _public member_ `TArray<uint32> MeshSampleSectionsBuffer;` — Store the samples rest section
- L966 _public member_ `TArray<uint32> UniqueSectionIds;` — Store the mesh section indices which are relevant for this root LOD data
- L969 _public member_ `int32 LODIndex = -1;` — Mesh LOD index for which the root data are computed
- L972 _public member_ `uint32 MeshSectionCount = 0;` — Number of render section of the target mesh
- L975 _public member_ `uint32 RootCount = 0;` — Number of roots
- L978 _public member_ `uint32 PointCount = 0;` — Number of control points
- L981 _public member_ `uint32 Flags = 0;` — General flags (shuffled curve, extra ending point, ...)
- L984 _public member_ `FHairStrandsDatas::FHash Hash;` — Source data's hash for validation

#### struct `FHairStrandsRootBulkData`  
`struct FHairStrandsRootBulkData : FHairStrandsBulkCommon`  
_L988-1044_
- inherits: `FHairStrandsBulkCommon`
- desc: Bulk data for root resources (GPU resources are stored into FHairStrandsRootResources)
- L990 _public prototype_ `virtual void SerializeHeader(FArchive& Ar, UObject* Owner) override;`
- L991 _public prototype_ `virtual uint32 GetResourceCount() const override;`
- L992 _public prototype_ `virtual void GetResources(FQuery& Out) override;`
- L993 _public prototype_ `uint32 GetSize() const;`
- L995 _public prototype_ `void Reset();`
- L996 _public prototype_ `virtual void ResetLoadedSize() override;`
- L997 _public function_ `bool IsValid() const`
- L998 _public prototype_ `const TArray<uint32>& GetValidSectionIndices() const;`
- L999 _public function_ `uint32 GetRootCount()const`
- L1000 _public prototype_ `uint32 GetDataSize() const;`
- L1002 _public prototype_ `bool IsCookedBulkDataLoadedForCPUAccess() const;`
- L1004 _public function_ `bool HasFlags(FHairStrandsBulkData::EDataFlags In) const`
- L1029 _public member_ `} Header;`
- L1043 _public member_ `} Data;`

#### struct `FHairStrandsRootBulkData::FHeader`  
`struct FHeader`  
_L1006-1029_
- L1008 _public member_ `int32 LODIndex = -1;`
- L1009 _public member_ `uint32 RootCount = 0;` — Number of roots
- L1010 _public member_ `uint32 PointCount = 0;` — Number of control points
- L1011 _public member_ `uint32 SampleCount = 0;` — Number of samples used for the mesh interpolation
- L1012 _public member_ `uint32 MeshSectionCount = 0;` — Number of section of the target mesh
- L1013 _public member_ `uint32 UniqueTriangleCount = 0;`
- L1014 _public member_ `uint32 Flags = 0;`
- L1015 _public member_ `FHairStrandsDatas::FHash Hash;`
- L1016 _public member_ `TArray<uint32> UniqueSectionIndices;` — Store the mesh section indices which are relevant for this root LOD data
- L1028 _public member_ `} Strides;`

#### struct `FHairStrandsRootBulkData::FHeader::FStrides`  
`struct FStrides`  
_L1018-1028_
- L1020 _public member_ `uint32 RootToUniqueTriangleIndexBufferStride = 0;`
- L1021 _public member_ `uint32 RootBarycentricBufferStride = 0;`
- L1022 _public member_ `uint32 UniqueTriangleIndexBufferStride = 0;`
- L1023 _public member_ `uint32 RestUniqueTrianglePositionBufferStride = 0;`
- L1025 _public member_ `uint32 MeshInterpolationWeightsBufferStride = 0;`
- L1026 _public member_ `uint32 MeshSampleIndicesAndSectionsBufferStride = 0;`
- L1027 _public member_ `uint32 RestSamplePositionsBufferStride = 0;`

#### struct `FHairStrandsRootBulkData::FData`  
`struct FData`  
_L1031-1043_
- L1034 _public member_ `FHairBulkContainer RootToUniqueTriangleIndexBuffer;` — Binding
- L1035 _public member_ `FHairBulkContainer RootBarycentricBuffer;` — Root's barycentric (per-root)
- L1036 _public member_ `FHairBulkContainer UniqueTriangleIndexBuffer;` — Unique triangles list from skeleton mesh section IDs and triangle IDs (per-unique-triangle)
- L1037 _public member_ `FHairBulkContainer RestUniqueTrianglePositionBuffer;` — Rest triangle positions (per-unique-triangle)
- L1040 _public member_ `FHairBulkContainer MeshInterpolationWeightsBuffer;` — RBF
- L1041 _public member_ `FHairBulkContainer MeshSampleIndicesAndSectionsBuffer;` — Store the samples vertex indices (per-sample)
- L1042 _public member_ `FHairBulkContainer RestSamplePositionsBuffer;` — Store the samples rest positions (per-sample)

#### struct `FHairStrandsDebugDatas`  
`struct FHairStrandsDebugDatas`  
_L1050-1079_
- desc: Hair strands debug data
- L1052 _public function_ `bool IsValid() const`
- L1054 _public member_ `static const uint32 InvalidIndex = ~0u;`
- L1076 _public member_ `FDesc VoxelDescription;`
- L1077 _public member_ `TArray<FOffsetAndCount> VoxelOffsetAndCount;`
- L1078 _public member_ `TArray<FVoxel> VoxelData;`

#### struct `FHairStrandsDebugDatas::FOffsetAndCount`  
`struct FOffsetAndCount`  
_L1055-1059_
- L1057 _public member_ `uint32 Offset = 0u;`
- L1058 _public member_ `uint32 Count = 0u;`

#### struct `FHairStrandsDebugDatas::FVoxel`  
`struct FVoxel`  
_L1061-1065_
- L1063 _public member_ `uint32 Index0 = InvalidIndex;`
- L1064 _public member_ `uint32 Index1 = InvalidIndex;`

#### struct `FHairStrandsDebugDatas::FDesc`  
`struct FDesc`  
_L1067-1074_
- L1069 _public member_ `FVector3f VoxelMinBound = FVector3f::ZeroVector;`
- L1070 _public member_ `FVector3f VoxelMaxBound = FVector3f::ZeroVector;`
- L1071 _public member_ `FIntVector VoxelResolution = FIntVector::ZeroValue;`
- L1072 _public member_ `float VoxelSize = 0;`
- L1073 _public member_ `uint32 MaxSegmentPerVoxel = 0;`

#### struct `FHairStrandsDebugResources`  
`struct FHairStrandsDebugResources`  
_L1081-1086_
- L1083 _public member_ `FHairStrandsDebugDatas::FDesc VoxelDescription;`
- L1084 _public member_ `TRefCountPtr<FRDGPooledBuffer> VoxelOffsetAndCount;`
- L1085 _public member_ `TRefCountPtr<FRDGPooledBuffer> VoxelData;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHairStrands, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHairStrands, Log, All);`
- L26 _prototype_ `float GetHairStrandsMaxLength(const FHairStrandsDatas& In);`
- L27 _prototype_ `float GetHairStrandsMaxRadius(const FHairStrandsDatas& In);`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace DerivedData` (scope `UE`)
- L88 _member_ `FAttributePacking0 Attribute0;` (scope `FTranscodedHairPositions::__anon8134e7fb010a`)
- L89 _member_ `FAttributePacking1 Attribute1;` (scope `FTranscodedHairPositions::__anon8134e7fb010a`)
- L116 _prototype_ `FArchive& operator<<(FArchive& Ar, FVector4_16& Vertex);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/HairStrandsInterpolation.h` (Public)


#### struct `FGroomCacheResources`  
`struct FGroomCacheResources`  
_L64-69_
- L66 _public member_ `FRDGBufferSRVRef PositionBuffer = nullptr;`
- L67 _public member_ `FRDGBufferSRVRef RadiusBuffer = nullptr;`
- L68 _public member_ `bool bHasRadiusData = false;`

#### struct `FRDGHairStrandsCullingData`  
`struct FRDGHairStrandsCullingData`  
_L93-98_
- L95 _public member_ `bool bCullingResultAvailable = false;`
- L96 _public member_ `FRDGImportedBuffer HairStrandsVF_CullingIndirectBuffer;`
- L97 _public member_ `FRDGImportedBuffer HairStrandsVF_CullingIndexBuffer;`

#### enum `EHairAABBUpdateType`  
`enum class EHairAABBUpdateType`  
_L102-106_
- L104 _public enumerator_ `UpdateClusterAABB`
- L105 _public enumerator_ `UpdateGroupAABB`

#### enum `EHairPatchAttribute`  
`enum class EHairPatchAttribute : uint8`  
_L161-166_
- L163 _public enumerator_ `None`
- L164 _public enumerator_ `GuideInflucence`
- L165 _public enumerator_ `ClusterInfluence`

#### Free symbols / members of external scopes

- L36 _prototype_ `void AddDeformSimHairStrandsPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const uint32 InstanceRegisteredIndex, const uint32 MeshLODIndex, const uint32 VertexCount, FHairStrandsRestRootResource* SimRestRootResources, FHairStrandsDeformedRootResource* SimDeformedRootResources, FRDGBufferSRVRef SimRestPosePositionBuffer, FRDGBufferSRVRef SimPointToCurveBuffer, FRDGImportedBuffer& OutSimDeformedPositionBuffer, const FVector& SimRestOffset, FRDGBufferSRVRef SimDeformedOffsetBuffer, const bool bHasGlobalInterpolation, FRHIShaderResourceView* BoneBufferSRV);` — Reset the interpolation data. This needs to be called prior to ComputeHairStrandsInterpolation and prior to the actual hair simulation in order to insure that: 1) when hair simulation is enabled, the first frame is correct 2) when hair simulation is enabled/disabled (i.e., toggle/change) we reset to deform buffer to rest state)
- L52 _prototype_ `void ComputeHairStrandsInterpolation( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const uint32 ViewUniqueID, const uint32 ViewRayTracingMask, const EGroomViewMode ViewMode, const FVector& TranslatedWorldOffset, const FShaderPrintData* ShaderPrintData, FHairGroupInstance* Instance, int32 LODIndex, FHairStrandClusterData* ClusterData);`
- L70 _prototype_ `FGroomCacheResources CreateGroomCacheBuffer(FRDGBuilder& GraphBuilder, FGroomCacheVertexData& InVertexData);`
- L72 _prototype_ `void AddGroomCacheUpdatePass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, uint32 InstanceRegisteredIndex, uint32 PointCount, uint32 CurveCount, float InterpolationFactor, float InMaxHairRadius, bool bAllowAddedControlPoint, FGroomCacheResources CacheResources0, FGroomCacheResources CacheResources1, FRDGBufferSRVRef InRestPositionBuffer, FRDGBufferSRVRef InRestCurveBuffer, FRDGBufferSRVRef InRestPointToCurveBuffer, FRDGBufferSRVRef InDeformedOffsetBuffer, FRDGBufferUAVRef OutBuffer);`
- L89 _prototype_ `void ComputeInterpolationWeights(UGroomBindingAsset* BindingAsset, FSkeletalMeshRenderData* TargetRenderData, TArray<FRWBuffer>& TransferedPositions);`
- L91 _prototype_ `FHairGroupPublicData::FVertexFactoryInput ComputeHairStrandsVertexInputData(const FHairGroupInstance* Instance, EGroomViewMode ViewMode);`
- L100 _prototype_ `FRDGHairStrandsCullingData ImportCullingData(FRDGBuilder& GraphBuilder, FHairGroupPublicData* In);`
- L108 _prototype_ `void AddClearAABBPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, uint32 AABBCount, FRDGBufferUAVRef& OutAABBUAV);`
- L114 _prototype_ `void AddHairStrandsInterpolationPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, EShaderPlatform InPlatform, const FShaderPrintData* ShaderPrintData, const FHairGroupInstance* Instance, const uint32 VertexCount, const uint32 CurveCount, const FHairStrandsRestResource* RenRestResource, const FHairStrandsRestResource* SimRestResource, const bool bSimDataValid, const uint32 MaxPointPerCurve, const int32 MeshLODIndex, const float HairLengthScale, const EHairInterpolationType HairInterpolationType, const EHairGeometryType InstanceGeometryType, const FRDGHairStrandsCullingData& CullingData, const FVector& InRenHairWorldOffset, const FVector& InSimHairWorldOffset, const FRDGBufferSRVRef& OutRenHairPositionOffsetBuffer, const FRDGBufferSRVRef& OutSimHairPositionOffsetBuffer, const FHairStrandsRestRootResource* RenRestRootResources, const FHairStrandsRestRootResource* SimRestRootResources, const FHairStrandsDeformedRootResource* RenDeformedRootResources, const FHairStrandsDeformedRootResource* SimDeformedRootResources, const FRDGBufferSRVRef& RenRestPosePositionBuffer, const FRDGBufferSRVRef& RenCurveBuffer, const bool bUseSingleGuide, const FRDGBufferSRVRef& CurveInterpolationBuffer, const FRDGBufferSRVRef& PoinInterpolationBuffer, const FRDGBufferSRVRef& SimRestPosePositionBuffer, const FRDGBufferSRVRef& SimDeformedPositionBuffer, const FRDGBufferSRVRef& RenDeformerPositionBuffer, FRDGBufferUAVRef& OutRenPositionBuffer, const FHairStrandsLODDeformedRootResource::EFrameT ...`
- L152 _prototype_ `void AddHairTangentPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, uint32 PointCount, FHairGroupPublicData* HairGroupPublicData, FRDGBufferSRVRef PositionBuffer, FRDGBufferUAVRef OutTangentBuffer);`
- L168 _prototype_ `void AddPatchAttributePass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const uint32 CurveCount, const EHairPatchAttribute Mode, const bool bSimulation, const bool bUseSingleGuide, const FHairStrandsBulkData& RenBulkData, const FRDGBufferRef& RenAttributeBuffer, const FRDGBufferSRVRef& RenCurveBuffer, const FRDGBufferSRVRef& RenCurveToClusterIdBuffer, const FRDGBufferSRVRef& CurveInterpolationBuffer, const FRDGBufferSRVRef& PointInterpolationBuffer, FRDGImportedBuffer& OutRenAttributeBuffer);`
- L183 _prototype_ `void AddTransferPositionPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const uint32 PointOffset, const uint32 PointCount, const uint32 TotalPointCount, FRDGBufferSRVRef InBuffer, FRDGBufferUAVRef OutBuffer);`
- L193 _prototype_ `void AddGenerateRaytracingGeometryPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const FShaderPrintData* ShaderPrintData, uint32 InstanceRegisteredIndex, uint32 ActivePointCount, uint32 TotalPointCount, EHairStrandsRayTracingPrimitiveType RayTracingPrimitiveType, int ProceduralSplits, float HairRadius, float RootScale, float TipScale, const FRDGBufferSRVRef& HairWorldOffsetBuffer, FRDGHairStrandsCullingData& CullingData, const FRDGBufferSRVRef& PositionBuffer, const FRDGBufferSRVRef& TangentBuffer, const FRDGBufferUAVRef& OutPositionBuffer, const FRDGBufferUAVRef& OutIndexBuffer);`
- L212 _prototype_ `void AddBuildStrandsAccelerationStructurePass( FRDGBuilder& GraphBuilder, FHairGroupInstance* Instance, uint32 ProceduralSplits, bool bNeedUpdate, FRDGBufferRef Raytracing_PositionBuffer, FRDGBufferRef Raytracing_IndexBuffer);`
- L220 _prototype_ `void AddBuildHairCardAccelerationStructurePass( FRDGBuilder& GraphBuilder, FHairGroupInstance* Instance, int32 HairLODIndex, bool bNeedUpdate);`
- L226 _prototype_ `void AddBuildHairMeshAccelerationStructurePass( FRDGBuilder& GraphBuilder, FHairGroupInstance* Instance, int32 HairLODIndex, bool bNeedUpdate);`
- L233 _prototype_ `void AddHairCardsDeformationPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const ERHIFeatureLevel::Type FeatureLevel, const FShaderPrintData* ShaderPrintData, FHairGroupInstance* Instance, const int32 HairLODIndex, const int32 MeshLODIndex, ERHIPipeline CardPositionExternalAccessPipeline);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/HairStrandsMeshProjection.h` (Public)


#### struct `FSkinUpdateSection`  
`struct FSkinUpdateSection`  
_L81-90_
- L83 _public member_ `uint32 SectionIndex = 0;`
- L84 _public member_ `uint32 NumVertexToProcess = 0;`
- L85 _public member_ `uint32 SectionVertexBaseIndex = 0;`
- L86 _public member_ `FRHIShaderResourceView* BoneBuffer = nullptr;`
- L87 _public member_ `FRHIShaderResourceView* BonePrevBuffer = nullptr;`
- L88 _public member_ `uint32 BoneTransformOffset = 0;`
- L89 _public member_ `uint32 PrevBoneTransformOffset = 0;`

#### enum `EHairPositionUpdateType`  
`enum class EHairPositionUpdateType : uint8`  
_L119-124_
- L121 _public enumerator_ `Guides = 0`
- L122 _public enumerator_ `Strands = 1`
- L123 _public enumerator_ `Cards = 2`

#### Free symbols / members of external scopes

- L23 _prototype_ `uint32 GetHairStrandsMaxSectionCount();` — Return the max number of section/triangle a skeletal mesh can have. After this count, binding will be disabled
- L24 _prototype_ `uint32 GetHairStrandsMaxTriangleCount();`
- L27 _prototype_ `void AddHairStrandUpdateMeshTrianglesPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const int32 MeshLODIndex, const FCachedGeometry& MeshLODData, FHairStrandsRestRootResource* RestResources, FHairStrandsDeformedRootResource* DeformedResources);` — Update the triangles information on which hair stands have been projected
- L36 _prototype_ `void AddHairStrandInitMeshSamplesPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const int32 MeshLODIndex, const FCachedGeometry& MeshLODData, FHairStrandsRestRootResource* RestResources, FHairStrandsDeformedRootResource* DeformedResources);` — Init the samples information to be used for interpolation
- L45 _prototype_ `void AddHairStrandUpdateMeshSamplesPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const int32 MeshLODIndex, const FCachedGeometry& MeshLODData, FHairStrandsRestRootResource* RestResources, FHairStrandsDeformedRootResource* DeformedResources);` — Update the samples information to be used for interpolation
- L53 _prototype_ `void GenerateFolliculeMask( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const EPixelFormat Format, const FIntPoint Resolution, const uint32 MipCount, const uint32 KernelSizeInPixels, const uint32 Channel, const int32 LODIndex, FHairStrandsRestRootResource* RestResources, FRDGTextureRef& OutTexture);`
- L76 _prototype_ `void AddComputeMipsPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, FRDGTextureRef& OutTexture);`
- L92 _prototype_ `void AddSkinUpdatePass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, FSkeletalMeshLODRenderData& RenderData, const TArray<FSkinUpdateSection>& Sections, FRDGBufferRef OutDeformedPositionBuffer, FRDGBufferRef OutPrevDeformedPositionBuffer, FRDGBufferRef OutTangentBuffer);`
- L101 _prototype_ `void AddHairMeshesRBFInterpolationPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const int32 MeshLODIndex, FHairMeshesRestResource* RestResources, FHairMeshesDeformedResource* DeformedResources, FHairStrandsRestRootResource* RestRootResources, FHairStrandsDeformedRootResource* DeformedRootResources);`
- L110 _prototype_ `void AddHairCardsRBFInterpolationPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, const int32 MeshLODIndex, FHairCardsRestResource* RestResources, FHairCardsDeformedResource* DeformedResources, FHairStrandsRestRootResource* RestRootResources, FHairStrandsDeformedRootResource* DeformedRootResources);`
- L126 _prototype_ `void AddHairStrandUpdatePositionOffsetPass( FRDGBuilder& GraphBuilder, FGlobalShaderMap* ShaderMap, EHairPositionUpdateType UpdateType, const int32 InstanceRegisteredIndex, const int32 HairLODIndex, const int32 MeshLODIndex, FHairStrandsDeformedRootResource* DeformedRootResources, FHairStrandsDeformedResource* DeformedResources);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/HairStrandsVertexFactory.h` (Public)


#### class `THairStrandsVertexFactory`  
`template<bool bSupportLinearSweptSpheres> class THairStrandsVertexFactory : public FVertexFactory`  
_L27-88_
- inherits: `FVertexFactory`
- desc: A vertex factory which simply transforms explicit vertex attributes from local to world space. This is templated to allow different behavior for Linear Swept Spheres, which do not require an intersection shader.
- L29 _private prototype_ `DECLARE_VERTEX_FACTORY_TYPE(THairStrandsVertexFactory);`
- L37 _public function_ `THairStrandsVertexFactory(FHairGroupInstance* Instance, ERHIFeatureLevel::Type InFeatureLevel, const char* InDebugName) : FVertexFactory(InFeatureLevel) , DebugName(InDebugName)`
- L47 _public prototype_ `static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);` — Should we cache the material's shadertype on this platform with this vertex factory?
- L48 _public prototype_ `static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L49 _public prototype_ `static void ValidateCompiledResult(const FVertexFactoryType* Type, EShaderPlatform Platform, const FShaderParameterMap& ParameterMap, TArray<FString>& OutErrors);`
- L50 _public prototype_ `static void GetPSOPrecacheVertexFetchElements(EVertexInputStreamType VertexInputStreamType, FVertexDeclarationElementList& Elements);`
- L53 _public prototype_ `EPrimitiveIdMode GetPrimitiveIdMode(ERHIFeatureLevel::Type In) const;` — Return the primitive id supported by the VF
- L58 _public prototype_ `void SetData(const FDataType& InData);` — An implementation of the interface used by TSynchronizedResource to update the resource with new data from the game thread.
- L64 _public prototype_ `void Copy(const THairStrandsVertexFactory& Other);` — Copy the data from another vertex factory @param Other - factory to copy from
- L67 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource interface.
- L68 _public prototype_ `virtual void ReleaseRHI() override;`
- L69 _public prototype_ `void InitResources(FRHICommandListBase& RHICmdList);`
- L71 _public function_ `const FDataType& GetData() const`
- L72 _public member_ `FDataType Data;`
- L74 _protected member_ `bool bIsInitialized = false;`
- L87 _protected member_ `} DebugName;`

#### struct `THairStrandsVertexFactory::FDataType`  
`struct FDataType`  
_L32-35_
- L34 _public member_ `FHairGroupInstance* Instance = nullptr;`

#### struct `THairStrandsVertexFactory::FDebugName`  
`struct FDebugName`  
_L76-87_
- L78 _public function_ `FDebugName(const char* InDebugName) #if !UE_BUILD_SHIPPING : DebugName(InDebugName) #endif`
- L85 _private member_ `const char* DebugName;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L90 _typedef_ `using FLinearSweptSpheresHairStrandsVertexFactory = THairStrandsVertexFactory<true>;`
- L91 _typedef_ `using FHairStrandsVertexFactory = THairStrandsVertexFactory<false>;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/MovieSceneGroomCacheSection.h` (Public)


#### struct `FMovieSceneGroomCacheParams`  
`struct FMovieSceneGroomCacheParams`  
_L11-42_
- reflection: `USTRUCT()`
- L15 _public prototype_ `FMovieSceneGroomCacheParams();`
- L18 _public prototype_ `float GetSequenceLength() const;` — Gets the animation sequence length, not modified by play rate
- L21 _public member_ `TObjectPtr<class UGroomCache> GroomCache;` — `UPROPERTY(EditAnywhere, Category = GroomCache)` — The animation this section plays
- L25 _public member_ `FFrameNumber FirstLoopStartFrameOffset;` — `UPROPERTY(EditAnywhere, Category = GroomCache)` — The offset for the first loop of the animation clip
- L29 _public member_ `FFrameNumber StartFrameOffset;` — `UPROPERTY(EditAnywhere, Category = GroomCache)` — The offset into the beginning of the animation clip
- L33 _public member_ `FFrameNumber EndFrameOffset;` — `UPROPERTY(EditAnywhere, Category = GroomCache)` — The offset into the end of the animation clip
- L37 _public member_ `float PlayRate;` — `UPROPERTY(EditAnywhere, Category = GroomCache)` — The playback rate of the animation clip
- L41 _public member_ `uint32 bReverse : 1;` — `UPROPERTY(EditAnywhere, Category = "Animation")` — Reverse the playback of the animation clip

#### class `UMovieSceneGroomCacheSection`  
`class UMovieSceneGroomCacheSection : public UMovieSceneSection`  
_L48-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Movie scene section that control GroomCache playback
- L56 _public member_ `FMovieSceneGroomCacheParams Params;` — `UPROPERTY(EditAnywhere, Category = "Animation", meta = (ShowOnlyInnerProperties))`
- L59 _public prototype_ `virtual float MapTimeToAnimation(float ComponentDuration, FFrameTime InPosition, FFrameRate InTickResolution) const;` — Get Frame Time as Animation Time
- L63 _protected prototype_ `virtual TOptional<TRange<FFrameNumber> > GetAutoSizeRange() const override;`
- L64 _protected prototype_ `virtual void TrimSection(FQualifiedFrameTime TrimTime, bool bTrimLeft, bool bDeleteKeys) override;`
- L65 _protected prototype_ `virtual UMovieSceneSection* SplitSection(FQualifiedFrameTime SplitTime, bool bDeleteKeys) override;`
- L66 _protected prototype_ `virtual void GetSnapTimes(TArray<FFrameNumber>& OutSnapTimes, bool bGetSectionBorders) const override;`
- L67 _protected prototype_ `virtual TOptional<FFrameTime> GetOffsetTime() const override;`
- L73 _private prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L74 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L76 _public member_ `float PreviousPlayRate;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/MovieSceneGroomCacheTrack.h` (Public)


#### class `UMovieSceneGroomCacheTrack`  
`class UMovieSceneGroomCacheTrack : public UMovieSceneNameableTrack , public IMovieSceneTrackTemplateProducer`  
_L13-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack,IMovieSceneTrackTemplateProducer`
- desc: Handles animation of GroomCache
- L22 _public prototype_ `virtual UMovieSceneSection* AddNewAnimation(FFrameNumber KeyTime, class UGroomComponent* GroomComp);` — Adds a new animation to this track
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

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/Niagara/NiagaraDataInterfaceHairStrands.h` (Public)


#### struct `FNDIHairStrandsBuffer`  
`struct FNDIHairStrandsBuffer : public FRenderResource`  
_L31-79_
- inherits: `FRenderResource`
- desc: Render buffers that will be used in hlsl functions
- L34 _public prototype_ `void Initialize( const FNDIHairStrandsInfo& In, const TStaticArray<float, 32 * NumScales>& InParamsScale);` — Set the asset that will be used to affect the buffer
- L39 _public prototype_ `void Transfer(FRDGBuilder& GraphBuilder, const TStaticArray<float, 32 * NumScales>& InParamsScale);` — Transfer CPU datas to GPU
- L42 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — Init the buffer
- L45 _public prototype_ `virtual void ReleaseRHI() override;` — Release the buffer
- L48 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L51 _public member_ `FNiagaraPooledRWBuffer BoundingBoxBuffer;` — Bounding Box Buffer
- L54 _public member_ `FNiagaraPooledRWBuffer ParamsScaleBuffer;` — Params scale buffer
- L57 _public member_ `TStaticArray<float, 32 * NumScales> ParamsScale;` — Scales along the strand
- L60 _public member_ `FIntVector4 BoundingBoxOffsets;` — Bounding box offsets
- L63 _public member_ `bool bValidGeometryType = false;` — Valid geometry type for hair (strands, cards, mesh)
- L66 _public member_ `int32 CurrentMeshLOD = INDEX_NONE;` — Mesh LOD that is being used for the root resources
- L69 _public member_ `bool bNeedResouces = false;` — True if the internal resources (BoundingBoxBuffer/ParamsScaleBuffer) needs to be built
- L72 _public member_ `bool bShouldReset = false;` — Boolean to trigger the reset
- L75 _public member_ `int32 ResetCount = 0;` — Counter to reset the simulation once triggered

#### struct `FNDIHairStrandsData`  
`struct FNDIHairStrandsData`  
_L82-394_
- desc: Data stored per strand base instance
- L84 _public function_ `FNDIHairStrandsData()`
- L89 _public prototype_ `bool Init(class UNiagaraDataInterfaceHairStrands* Interface, FNiagaraSystemInstance* SystemInstance);` — Initialize the buffers
- L92 _public prototype_ `void Release();` — Release the buffers
- L95 _public prototype_ `void Update( UNiagaraDataInterfaceHairStrands* Interface, const FNDIHairStrandsInfo& InData, const float DeltaSeconds);` — Update the buffers
- L100 _public function_ `inline void ResetDatas()`
- L167 _public function_ `inline void CopyDatas(const FNDIHairStrandsData* OtherDatas)`
- L249 _public member_ `FTransform WorldTransform;` — Cached World transform.
- L252 _public member_ `FTransform BoneTransform;` — Bone transform that will be used for local strands simulation
- L255 _public member_ `FTransform PreviousBoneTransform;` — Bone transform that will be used for local strands simulation
- L258 _public member_ `FVector3f BoneLinearVelocity;` — Bone Linear Velocity
- L261 _public member_ `FVector3f PreviousBoneLinearVelocity;` — Bone Previous Linear Velocity
- L264 _public member_ `FVector3f BoneAngularVelocity;` — Bone Angular Velocity
- L267 _public member_ `FVector3f PreviousBoneAngularVelocity;` — Bone Previous Angular Velocity
- L270 _public member_ `FVector3f BoneLinearAcceleration;` — Bone Linear Acceleration
- L273 _public member_ `FVector3f BoneAngularAcceleration;` — Bone Angular Acceleration
- L276 _public member_ `bool GlobalInterpolation;` — Global Interpolation
- L279 _public member_ `bool bSkinningTransfer;` — Skinning transfer from a source to a target skelmesh
- L282 _public member_ `int32 NumStrands;` — Number of strands
- L285 _public member_ `int32 StrandsSize;` — Strand size
- L288 _public member_ `bool ForceReset;` — Force reset simulation
- L291 _public member_ `FNDIHairStrandsBuffer* HairStrandsBuffer = nullptr;` — Strands Gpu buffer
- L294 _public member_ `int32 HairGroupIndex = -1;` — Hair group index
- L297 _public member_ `FHairGroupInstance* HairGroupInstance = nullptr;` — Hair group instance
- L300 _public member_ `TWeakObjectPtr<class UGroomComponent> HairGroupInstSource;` — Source component of the hair group instance
- L303 _public member_ `EHairBindingType BindingType;` — Binding type between the groom asset and the attached skeletal mesh
- L306 _public member_ `int32 SubSteps;` — Number of substeps to be used
- L309 _public member_ `int32 IterationCount;` — Number of iterations for the constraint solver
- L312 _public member_ `FVector GravityVector;` — Acceleration vector in cm/s2 to be used for the gravity
- L315 _public member_ `float GravityPreloading;` — Optimisation of the rest state configuration to compensate from the gravity
- L318 _public member_ `float AirDrag;` — Coefficient between 0 and 1 to be used for the air drag
- L321 _public member_ `FVector AirVelocity;` — Velocity of the surrounding air in cm/s
- L324 _public member_ `bool SolveBend;` — Velocity of the surrounding air in cm/s
- L327 _public member_ `bool ProjectBend;` — Enable the solve of the bend constraint during the xpbd loop
- L330 _public member_ `float BendDamping;` — Damping for the bend constraint between 0 and 1
- L333 _public member_ `float BendStiffness;` — Stiffness for the bend constraint in GPa
- L336 _public member_ `bool SolveStretch;` — Enable the solve of the stretch constraint during the xpbd loop
- L339 _public member_ `bool ProjectStretch;` — Enable the projection of the stretch constraint after the xpbd loop
- L342 _public member_ `float StretchDamping;` — Damping for the stretch constraint between 0 and 1
- L345 _public member_ `float StretchStiffness;` — Stiffness for the stretch constraint in GPa
- L348 _public member_ `bool SolveCollision;` — Enable the solve of the collision constraint during the xpbd loop
- L351 _public member_ `bool ProjectCollision;` — Enable ther projection of the collision constraint after the xpbd loop
- L354 _public member_ `float StaticFriction;` — Static friction used for collision against the physics asset
- L357 _public member_ `float KineticFriction;` — Kinetic friction used for collision against the physics asset
- L360 _public member_ `float StrandsViscosity;` — Radius that will be used for the collision detection against the physics asset
- L363 _public member_ `FIntVector GridDimension;` — Grid Dimension used to compute the viscosity forces
- L366 _public member_ `float CollisionRadius;` — Radius scale along the strand
- L369 _public member_ `float StrandsDensity;` — Density of the strands in g/cm3
- L372 _public member_ `float StrandsSmoothing;` — Smoothing between 0 and 1 of the incoming guides curves for better stability
- L375 _public member_ `float StrandsThickness;` — Strands thickness in cm that will be used for mass and inertia computation
- L378 _public member_ `TStaticArray<float, 32 * NumScales> ParamsScale;` — Scales along the strand
- L381 _public member_ `uint32 SkeletalMeshes;` — List of all the skel meshes in the hierarchy
- L384 _public member_ `ETickingGroup TickingGroup;` — The instance ticking group
- L387 _public member_ `bool LocalSimulation;` — Check if the simulation is running in local coordinate
- L390 _public member_ `float TimeDilation;` — Get the world time dilation
- L393 _public member_ `bool bUsesNanite;` — Check if instance use Nanite geometry

#### class `UNiagaraDataInterfaceHairStrands`  
`class UNiagaraDataInterfaceHairStrands : public UNiagaraDataInterface, public INiagaraSimCacheCustomStorageInterface`  
_L398-684_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Category = "Strands", meta = (DisplayName = "Hair Strands"))`
- inherits: `UNiagaraDataInterface,INiagaraSimCacheCustomStorageInterface`
- desc: Data Interface for the strand base
- L405 _public member_ `TObjectPtr<UGroomAsset> DefaultSource;` — `UPROPERTY(EditAnywhere, Category = "Source")` — Hair Strands Asset used to sample from when not overridden by a source actor from the scene. Also useful for previewing in the editor.
- L409 _public member_ `TObjectPtr<AActor> SourceActor;` — `UPROPERTY(EditAnywhere, Category = "Source")` — The source actor from which to sample
- L412 _public member_ `TWeakObjectPtr<class UGroomComponent> SourceComponent;` — The source component from which to sample
- L415 _public prototype_ `virtual void PostInitProperties() override;` — UObject Interface
- L418 _public prototype_ `virtual void GetVMExternalFunction(const FVMExternalFunctionBindingInfo& BindingInfo, void* InstanceData, FVMExternalFunction &OutFunc) override;` — Begin UNiagaraDataInterface Interface
- L419 _public function_ `virtual bool CanExecuteOnTarget(ENiagaraSimTarget Target) const override`
- L420 _public prototype_ `virtual bool InitPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance) override;`
- L421 _public prototype_ `virtual void DestroyPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance)override;`
- L422 _public prototype_ `virtual bool PerInstanceTick(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance, float DeltaSeconds) override;`
- L423 _public function_ `virtual int32 PerInstanceDataSize()const override`
- L424 _public prototype_ `virtual bool Equals(const UNiagaraDataInterface* Other) const override;`
- L425 _public function_ `virtual bool HasPreSimulateTick() const override`
- L426 _public function_ `virtual bool HasTickGroupPrereqs() const override`
- L427 _public prototype_ `virtual ETickingGroup CalculateTickGroup(const void* PerInstanceData) const override;`
- L431 _public prototype_ `virtual void GetCommonHLSL(FString& OutHLSL) override;`
- L432 _public prototype_ `virtual void GetParameterDefinitionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, FString& OutHLSL) override;`
- L433 _public prototype_ `virtual bool GetFunctionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, const FNiagaraDataInterfaceGeneratedFunction& FunctionInfo, int FunctionInstanceIndex, FString& OutHLSL) override;`
- L434 _public prototype_ `virtual bool AppendCompileHash(FNiagaraCompileHashVisitor* InVisitor) const override;`
- L436 _public prototype_ `virtual void BuildShaderParameters(FNiagaraShaderParametersBuilder& ShaderParametersBuilder) const override;`
- L437 _public prototype_ `virtual void SetShaderParameters(const FNiagaraDataInterfaceSetShaderParametersContext& Context) const override;`
- L439 _public prototype_ `virtual void ProvidePerInstanceDataForRenderThread(void* DataForRenderThread, void* PerInstanceData, const FNiagaraSystemInstanceID& SystemInstance) override;`
- L443 _public prototype_ `virtual void SimCachePostReadFrame(void* OptionalPerInstanceData, FNiagaraSystemInstance* SystemInstance) override;` — Begin INiagaraSimCacheCustomStorageInterface Interface
- L444 _public prototype_ `virtual TArray<FNiagaraVariableBase> GetSimCacheRendererAttributes(const UObject* UsageContext) const override;`
- L448 _public prototype_ `void ExtractSourceComponent(FNiagaraSystemInstance* SystemInstance);` — Update the source component
- L451 _public prototype_ `bool IsComponentValid() const;` — Check if the component is Valid
- L454 _public prototype_ `void ExtractDatasAndResources( FNiagaraSystemInstance* SystemInstance, FNDIHairStrandsInfo& Out);` — Extract datas and resources
- L459 _public prototype_ `void GetNumStrands(FVectorVMExternalFunctionContext& Context);` — Get the number of strands
- L462 _public prototype_ `void GetStrandSize(FVectorVMExternalFunctionContext& Context);` — Get the groom asset datas
- L464 _public prototype_ `void GetSubSteps(FVectorVMExternalFunctionContext& Context);`
- L466 _public prototype_ `void GetIterationCount(FVectorVMExternalFunctionContext& Context);`
- L468 _public prototype_ `void GetGravityVector(FVectorVMExternalFunctionContext& Context);`
- L470 _public prototype_ `void GetGravityPreloading(FVectorVMExternalFunctionContext& Context);`
- L472 _public prototype_ `void GetAirDrag(FVectorVMExternalFunctionContext& Context);`
- L474 _public prototype_ `void GetAirVelocity(FVectorVMExternalFunctionContext& Context);`
- L476 _public prototype_ `void GetSolveBend(FVectorVMExternalFunctionContext& Context);`
- L478 _public prototype_ `void GetProjectBend(FVectorVMExternalFunctionContext& Context);`
- L480 _public prototype_ `void GetBendDamping(FVectorVMExternalFunctionContext& Context);`
- L482 _public prototype_ `void GetBendStiffness(FVectorVMExternalFunctionContext& Context);`
- L484 _public prototype_ `void GetBendScale(FVectorVMExternalFunctionContext& Context);`
- L486 _public prototype_ `void GetSolveStretch(FVectorVMExternalFunctionContext& Context);`
- L488 _public prototype_ `void GetProjectStretch(FVectorVMExternalFunctionContext& Context);`
- L490 _public prototype_ `void GetStretchDamping(FVectorVMExternalFunctionContext& Context);`
- L492 _public prototype_ `void GetStretchStiffness(FVectorVMExternalFunctionContext& Context);`
- L494 _public prototype_ `void GetStretchScale(FVectorVMExternalFunctionContext& Context);`
- L496 _public prototype_ `void GetSolveCollision(FVectorVMExternalFunctionContext& Context);`
- L498 _public prototype_ `void GetProjectCollision(FVectorVMExternalFunctionContext& Context);`
- L500 _public prototype_ `void GetStaticFriction(FVectorVMExternalFunctionContext& Context);`
- L502 _public prototype_ `void GetKineticFriction(FVectorVMExternalFunctionContext& Context);`
- L504 _public prototype_ `void GetStrandsViscosity(FVectorVMExternalFunctionContext& Context);`
- L506 _public prototype_ `void GetGridDimension(FVectorVMExternalFunctionContext& Context);`
- L508 _public prototype_ `void GetCollisionRadius(FVectorVMExternalFunctionContext& Context);`
- L510 _public prototype_ `void GetRadiusScale(FVectorVMExternalFunctionContext& Context);`
- L512 _public prototype_ `void GetStrandsSmoothing(FVectorVMExternalFunctionContext& Context);`
- L514 _public prototype_ `void GetStrandsDensity(FVectorVMExternalFunctionContext& Context);`
- L516 _public prototype_ `void GetTimeDilation(FVectorVMExternalFunctionContext& Context);`
- L518 _public prototype_ `void GetStrandsThickness(FVectorVMExternalFunctionContext& Context);`
- L520 _public prototype_ `void GetThicknessScale(FVectorVMExternalFunctionContext& Context);`
- L523 _public prototype_ `void GetWorldTransform(FVectorVMExternalFunctionContext& Context);` — Get the world transform
- L526 _public prototype_ `void GetWorldInverse(FVectorVMExternalFunctionContext& Context);` — Get the world inverse
- L529 _public prototype_ `void GetPointPosition(FVectorVMExternalFunctionContext& Context);` — Get the strand vertex position in world space
- L532 _public prototype_ `void ComputeNodePosition(FVectorVMExternalFunctionContext& Context);` — Get the strand node position in world space
- L535 _public prototype_ `void ComputeNodeOrientation(FVectorVMExternalFunctionContext& Context);` — Get the strand node orientation in world space
- L538 _public prototype_ `void ComputeNodeMass(FVectorVMExternalFunctionContext& Context);` — Get the strand node mass
- L541 _public prototype_ `void ComputeNodeInertia(FVectorVMExternalFunctionContext& Context);` — Get the strand node inertia
- L544 _public prototype_ `void ComputeEdgeLength(FVectorVMExternalFunctionContext& Context);` — Compute the edge length (diff between 2 nodes positions)
- L547 _public prototype_ `void ComputeEdgeRotation(FVectorVMExternalFunctionContext& Context);` — Compute the edge orientation (diff between 2 nodes orientations)
- L550 _public prototype_ `void ComputeRestPosition(FVectorVMExternalFunctionContext& Context);` — Compute the rest local position
- L553 _public prototype_ `void ComputeRestOrientation(FVectorVMExternalFunctionContext& Context);` — Compute the rest local orientation
- L556 _public prototype_ `void AttachNodePosition(FVectorVMExternalFunctionContext& Context);` — Update the root node orientation based on the current transform
- L559 _public prototype_ `void AttachNodeOrientation(FVectorVMExternalFunctionContext& Context);` — Update the root node position based on the current transform
- L562 _public prototype_ `void UpdatePointPosition(FVectorVMExternalFunctionContext& Context);` — Report the node displacement onto the points position
- L565 _public prototype_ `void ResetPointPosition(FVectorVMExternalFunctionContext& Context);` — Reset the point position to be the rest one
- L568 _public prototype_ `void AdvectNodePosition(FVectorVMExternalFunctionContext& Context);` — Add external force to the linear velocity and advect node position
- L571 _public prototype_ `void AdvectNodeOrientation(FVectorVMExternalFunctionContext& Context);` — Add external torque to the angular velocity and advect node orientation
- L574 _public prototype_ `void UpdateLinearVelocity(FVectorVMExternalFunctionContext& Context);` — Update the node linear velocity based on the node position difference
- L577 _public prototype_ `void UpdateAngularVelocity(FVectorVMExternalFunctionContext& Context);` — Update the node angular velocity based on the node orientation difference
- L580 _public prototype_ `void GetBoundingBox(FVectorVMExternalFunctionContext& Context);` — Get the bounding box center
- L583 _public prototype_ `void ResetBoundingBox(FVectorVMExternalFunctionContext& Context);` — Reset the bounding box extent
- L586 _public prototype_ `void BuildBoundingBox(FVectorVMExternalFunctionContext& Context);` — Build the groom bounding box
- L589 _public prototype_ `void SetupDistanceSpringMaterial(FVectorVMExternalFunctionContext& Context);` — Setup the distance spring material
- L592 _public prototype_ `void SolveDistanceSpringMaterial(FVectorVMExternalFunctionContext& Context);` — Solve the distance spring material
- L595 _public prototype_ `void ProjectDistanceSpringMaterial(FVectorVMExternalFunctionContext& Context);` — Project the distance spring material
- L598 _public prototype_ `void SetupAngularSpringMaterial(FVectorVMExternalFunctionContext& Context);` — Setup the angular spring material
- L601 _public prototype_ `void SolveAngularSpringMaterial(FVectorVMExternalFunctionContext& Context);` — Solve the angular spring material
- L604 _public prototype_ `void ProjectAngularSpringMaterial(FVectorVMExternalFunctionContext& Context);` — Project the angular spring material
- L607 _public prototype_ `void SetupStretchRodMaterial(FVectorVMExternalFunctionContext& Context);` — Setup the stretch rod material
- L610 _public prototype_ `void SolveStretchRodMaterial(FVectorVMExternalFunctionContext& Context);` — Solve the stretch rod material
- L613 _public prototype_ `void ProjectStretchRodMaterial(FVectorVMExternalFunctionContext& Context);` — Project the stretch rod material
- L616 _public prototype_ `void SetupBendRodMaterial(FVectorVMExternalFunctionContext& Context);` — Setup the bend rod material
- L619 _public prototype_ `void SolveBendRodMaterial(FVectorVMExternalFunctionContext& Context);` — Solve the bend rod material
- L622 _public prototype_ `void ProjectBendRodMaterial(FVectorVMExternalFunctionContext& Context);` — Project the bend rod material
- L625 _public prototype_ `void SolveHardCollisionConstraint(FVectorVMExternalFunctionContext& Context);` — Solve the static collision constraint
- L628 _public prototype_ `void ProjectHardCollisionConstraint(FVectorVMExternalFunctionContext& Context);` — Project the static collision constraint
- L631 _public prototype_ `void SolveSoftCollisionConstraint(FVectorVMExternalFunctionContext& Context);` — Solve the soft collision constraint
- L634 _public prototype_ `void ProjectSoftCollisionConstraint(FVectorVMExternalFunctionContext& Context);` — Project the soft collision constraint
- L637 _public prototype_ `void SetupSoftCollisionConstraint(FVectorVMExternalFunctionContext& Context);` — Setup the soft collision constraint
- L640 _public prototype_ `void ComputeEdgeDirection(FVectorVMExternalFunctionContext& Context);` — Compute the rest direction
- L643 _public prototype_ `void UpdateMaterialFrame(FVectorVMExternalFunctionContext& Context);` — Update the strands material frame
- L646 _public prototype_ `void ComputeMaterialFrame(FVectorVMExternalFunctionContext& Context);` — Compute the strands material frame
- L649 _public prototype_ `void ComputeAirDragForce(FVectorVMExternalFunctionContext& Context);` — Compute the air drag force
- L652 _public prototype_ `void ComputeLocalState(FVectorVMExternalFunctionContext& Context);` — Get the rest position and orientation relative to the transform or to the skin cache
- L655 _public prototype_ `void AttachNodeState(FVectorVMExternalFunctionContext& Context);` — Attach the node position and orientation to the transform or to the skin cache
- L658 _public prototype_ `void UpdateNodeState(FVectorVMExternalFunctionContext& Context);` — Update the node position and orientation based on rbf transfer
- L661 _public prototype_ `void NeedSimulationReset(FVectorVMExternalFunctionContext& Context);` — Check if we need or not a simulation reset
- L664 _public prototype_ `void HasGlobalInterpolation(FVectorVMExternalFunctionContext& Context);` — Check if we have a global interpolation
- L667 _public prototype_ `void NeedRestUpdate(FVectorVMExternalFunctionContext& Context);` — Check if we need a rest pose update
- L670 _public prototype_ `void EvalSkinnedPosition(FVectorVMExternalFunctionContext& Context);` — Eval the skinned position given a rest position
- L673 _public prototype_ `void InitGridSamples(FVectorVMExternalFunctionContext& Context);` — Init the samples along the strands that will be used to transfer informations to the grid
- L676 _public prototype_ `void GetSampleState(FVectorVMExternalFunctionContext& Context);` — Get the sample state given an index
- L680 _protected prototype_ `virtual void GetFunctionsInternal(TArray<FNiagaraFunctionSignature>& OutFunctions) const override;`
- L683 _protected prototype_ `virtual bool CopyToInternal(UNiagaraDataInterface* Destination) const override;` — Copy one niagara DI to this

#### struct `FNDIHairStrandsProxy`  
`struct FNDIHairStrandsProxy : public FNiagaraDataInterfaceProxy`  
_L687-709_
- inherits: `FNiagaraDataInterfaceProxy`
- desc: Proxy to send data to gpu
- L690 _public function_ `virtual int32 PerInstanceDataPassedToRenderThreadSize() const override` — Get the size of the data that will be passed to render
- L693 _public prototype_ `virtual void ConsumePerInstanceDataFromGameThread(void* PerInstanceData, const FNiagaraSystemInstanceID& Instance) override;` — Get the data that will be passed to render
- L696 _public prototype_ `void InitializePerInstanceData(const FNiagaraSystemInstanceID& SystemInstance);` — Initialize the Proxy data strands buffer
- L699 _public prototype_ `void DestroyPerInstanceData(const FNiagaraSystemInstanceID& SystemInstance);` — Destroy the proxy data if necessary
- L702 _public prototype_ `virtual void PreStage(const FNDIGpuComputePreStageContext& Context) override;` — Launch all pre stage functions
- L705 _public prototype_ `virtual void PostSimulate(const FNDIGpuComputePostSimulateContext& Context) override;` — MGPU buffer copy after simulation
- L708 _public member_ `TMap<FNiagaraSystemInstanceID, FNDIHairStrandsData> SystemInstancesToProxyData;` — List of proxy data for each system instances

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
- L17 _variable_ `static const int32 MaxDelay = 2;`
- L18 _variable_ `static const int32 NumScales = 4;`
- L19 _variable_ `static const int32 StretchOffset = 0;`
- L20 _variable_ `static const int32 BendOffset = 1;`
- L21 _variable_ `static const int32 RadiusOffset = 2;`
- L22 _variable_ `static const int32 ThicknessOffset = 3;`
- L27 _prototype_ `bool UsesNanite(const UGroomComponent* In);`
- L28 _prototype_ `FHairGroupInstance* GetHairGroupInstance(UGroomComponent* In, int32 InGroupIndex);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/Niagara/NiagaraDataInterfacePressureGrid.h` (Public)


#### class `UNiagaraDataInterfacePressureGrid`  
`class UNiagaraDataInterfacePressureGrid : public UNiagaraDataInterfaceVelocityGrid`  
_L16-64_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Category = "Grid", meta = (DisplayName = "Pressure Grid"))`
- inherits: `UNiagaraDataInterfaceVelocityGrid`
- desc: Data Interface for the strand base
- L22 _public prototype_ `virtual void GetVMExternalFunction(const FVMExternalFunctionBindingInfo& BindingInfo, void* InstanceData, FVMExternalFunction &OutFunc) override;` — UNiagaraDataInterface Interface
- L23 _public function_ `virtual bool HasPreSimulateTick() const override`
- L27 _public prototype_ `virtual void GetParameterDefinitionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, FString& OutHLSL) override;`
- L28 _public prototype_ `virtual bool GetFunctionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, const FNiagaraDataInterfaceGeneratedFunction& FunctionInfo, int FunctionInstanceIndex, FString& OutHLSL) override;`
- L29 _public prototype_ `virtual void GetCommonHLSL(FString& OutHLSL) override;`
- L30 _public prototype_ `virtual bool AppendCompileHash(FNiagaraCompileHashVisitor* InVisitor) const override;`
- L34 _public prototype_ `void BuildDistanceField(FVectorVMExternalFunctionContext& Context);` — Build the velocity field
- L37 _public prototype_ `void SolveGridPressure(FVectorVMExternalFunctionContext& Context);` — Project the velocity field to be divergence free
- L40 _public prototype_ `void ScaleCellFields(FVectorVMExternalFunctionContext& Context);` — Scale Cell Fields
- L43 _public prototype_ `void SetSolidBoundary(FVectorVMExternalFunctionContext& Context);` — Set the solid boundary
- L46 _public prototype_ `void ComputeBoundaryWeights(FVectorVMExternalFunctionContext& Context);` — Compute the solid weights
- L49 _public prototype_ `void GetNodePosition(FVectorVMExternalFunctionContext& Context);` — Get Node Position
- L52 _public prototype_ `void GetDensityField(FVectorVMExternalFunctionContext& Context);` — Get Density Field
- L55 _public prototype_ `void BuildDensityField(FVectorVMExternalFunctionContext& Context);` — Build the Density Field
- L58 _public prototype_ `void UpdateDeformationGradient(FVectorVMExternalFunctionContext& Context);` — Update the deformation gradient
- L62 _protected prototype_ `virtual void GetFunctionsInternal(TArray<FNiagaraFunctionSignature>& OutFunctions) const override;`

#### struct `FNDIPressureGridProxy`  
`struct FNDIPressureGridProxy : public FNDIVelocityGridProxy`  
_L67-71_
- inherits: `FNDIVelocityGridProxy`
- desc: Proxy to send data to gpu
- L70 _public prototype_ `virtual void PreStage(const FNDIGpuComputePreStageContext& Context) override;` — Launch all pre stage functions

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HAIRSTRANDSCORE_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/Niagara/NiagaraDataInterfaceVelocityGrid.h` (Public)


#### struct `FNDIVelocityGridBuffer`  
`struct FNDIVelocityGridBuffer : public FRenderResource`  
_L16-38_
- inherits: `FRenderResource`
- desc: Render buffers that will be used in hlsl functions
- L19 _public prototype_ `void Initialize(const FIntVector GridSize, const int32 NumAttributes);` — Set the grid size
- L22 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — Init the buffer
- L25 _public prototype_ `virtual void ReleaseRHI() override;` — Release the buffer
- L28 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L31 _public member_ `FNiagaraPooledRWBuffer GridDataBuffer;` — Grid data texture
- L34 _public member_ `FIntVector GridSize;` — Grid size that will be used for the collision
- L37 _public member_ `int32 NumAttributes;` — Num attributes in the buffer

#### struct `FNDIVelocityGridData`  
`struct FNDIVelocityGridData`  
_L41-75_
- desc: Data stored per strand base instance
- L44 _public prototype_ `void Swap();` — Swap the current and the destination data
- L47 _public prototype_ `bool Init(const FIntVector& InGridSize, const int32 InNumAttributes, FNiagaraSystemInstance* SystemInstance);` — Initialize the buffers
- L50 _public prototype_ `void Release();` — Release the buffers
- L53 _public prototype_ `void Resize();` — Resize the buffers
- L56 _public member_ `FIntVector GridSize;` — Grid Size
- L59 _public member_ `int32 NumAttributes;` — Num Attributes
- L62 _public member_ `bool NeedResize;` — Need a resize
- L65 _public member_ `FMatrix WorldTransform;` — World Transform
- L68 _public member_ `FMatrix WorldInverse;` — Inverse world transform
- L71 _public member_ `FNDIVelocityGridBuffer* CurrentGridBuffer;` — Pointer to the current buffer
- L74 _public member_ `FNDIVelocityGridBuffer* DestinationGridBuffer;` — Pointer to the destination buffer

#### class `UNiagaraDataInterfaceVelocityGrid`  
`class UNiagaraDataInterfaceVelocityGrid : public UNiagaraDataInterfaceRWBase`  
_L79-136_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Category = "Grid", meta = (DisplayName = "Velocity Grid"))`
- inherits: `UNiagaraDataInterfaceRWBase`
- desc: Data Interface for the strand base
- L86 _public member_ `FIntVector GridSize;` — `UPROPERTY(EditAnywhere, Category = "Spawn")` — Grid size along the X axis.
- L89 _public member_ `int32 NumAttributes;` — Num Attributes
- L92 _public prototype_ `virtual void PostInitProperties() override;` — UObject Interface
- L95 _public prototype_ `virtual void GetVMExternalFunction(const FVMExternalFunctionBindingInfo& BindingInfo, void* InstanceData, FVMExternalFunction &OutFunc) override;` — UNiagaraDataInterface Interface
- L96 _public function_ `virtual bool CanExecuteOnTarget(ENiagaraSimTarget Target) const override`
- L97 _public prototype_ `virtual bool InitPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance) override;`
- L98 _public prototype_ `virtual void DestroyPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance)override;`
- L99 _public prototype_ `virtual bool PerInstanceTick(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance, float DeltaSeconds) override;`
- L100 _public function_ `virtual int32 PerInstanceDataSize()const override`
- L101 _public prototype_ `virtual bool Equals(const UNiagaraDataInterface* Other) const override;`
- L105 _public prototype_ `virtual bool AppendCompileHash(FNiagaraCompileHashVisitor* InVisitor) const override;`
- L106 _public prototype_ `virtual void GetCommonHLSL(FString& OutHLSL) override;`
- L107 _public prototype_ `virtual void GetParameterDefinitionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, FString& OutHLSL) override;`
- L108 _public prototype_ `virtual bool GetFunctionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, const FNiagaraDataInterfaceGeneratedFunction& FunctionInfo, int FunctionInstanceIndex, FString& OutHLSL) override;`
- L110 _public prototype_ `virtual void BuildShaderParameters(FNiagaraShaderParametersBuilder& ShaderParametersBuilder) const override;`
- L111 _public prototype_ `virtual void SetShaderParameters(const FNiagaraDataInterfaceSetShaderParametersContext& Context) const override;`
- L113 _public prototype_ `virtual void ProvidePerInstanceDataForRenderThread(void* DataForRenderThread, void* PerInstanceData, const FNiagaraSystemInstanceID& SystemInstance) override;`
- L116 _public prototype_ `void BuildVelocityField(FVectorVMExternalFunctionContext& Context);` — Build the velocity field
- L119 _public prototype_ `void SampleVelocityField(FVectorVMExternalFunctionContext& Context);` — Sample the grid
- L122 _public prototype_ `void ComputeGridSize(FVectorVMExternalFunctionContext& Context);` — Compute the grid Size (Origin and length)
- L125 _public prototype_ `void UpdateGridTransform(FVectorVMExternalFunctionContext& Context);` — Update the grid transform
- L128 _public prototype_ `void SetGridDimension(FVectorVMExternalFunctionContext& Context);` — Set the grid dimension
- L132 _protected prototype_ `virtual void GetFunctionsInternal(TArray<FNiagaraFunctionSignature>& OutFunctions) const override;`
- L135 _protected prototype_ `virtual bool CopyToInternal(UNiagaraDataInterface* Destination) const override;` — Copy one niagara DI to this

#### struct `FNDIVelocityGridProxy`  
`struct FNDIVelocityGridProxy : public FNiagaraDataInterfaceProxyRW`  
_L139-164_
- inherits: `FNiagaraDataInterfaceProxyRW`
- desc: Proxy to send data to gpu
- L142 _public function_ `virtual int32 PerInstanceDataPassedToRenderThreadSize() const override` — Get the size of the data that will be passed to render
- L145 _public prototype_ `virtual void ConsumePerInstanceDataFromGameThread(void* PerInstanceData, const FNiagaraSystemInstanceID& Instance) override;` — Get the data that will be passed to render
- L148 _public prototype_ `virtual void PreStage(const FNDIGpuComputePreStageContext& Context) override;` — Launch all pre stage functions
- L151 _public prototype_ `virtual void PostStage(const FNDIGpuComputePostStageContext& Context) override;` — Launch all post stage functions
- L154 _public prototype_ `virtual void PostSimulate(const FNDIGpuComputePostSimulateContext& Context) override;` — Called at the end of each simulate tick.
- L157 _public prototype_ `virtual void ResetData(const FNDIGpuComputeResetContext& Context) override;` — Reset the buffers
- L160 _public prototype_ `virtual void GetDispatchArgs(const FNDIGpuComputeDispatchArgsGenContext& Context) override;` — Get the dispatch arguments for this instance
- L163 _public member_ `TMap<FNiagaraSystemInstanceID, FNDIVelocityGridData> SystemInstancesToProxyData;` — List of proxy data for each system instances

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HAIRSTRANDSCORE_API`
