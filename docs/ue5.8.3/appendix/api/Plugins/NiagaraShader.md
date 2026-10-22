# Plugins / NiagaraShader

- module root: `Plugins/FX/Niagara/Source/NiagaraShader`
- headers: 24; symbols: 571
- symbol kinds: class=34, delegate=3, enum=9, enumerator=25, externvar=4, function=88, macro=4, member=162, namespace=11, prototype=177, struct=22, typedef=29, variable=3
- PrivateDependencyModuleNames: CoreUObject, DerivedDataCache, Engine, Renderer
- PrivateIncludePathModuleNames: DerivedDataCache, Niagara
- PublicDependencyModuleNames: Core, NiagaraCore, NiagaraVertexFactories, Projects, RHI, RenderCore, TargetPlatform, VectorVM
- PublicIncludePathModuleNames: 

### `Plugins/FX/Niagara/Source/NiagaraShader/Internal/NiagaraLWCTileShiftPositions.h` (Internal)


#### class `FNiagaraLWCTileShiftPositionsCS`  
`class FNiagaraLWCTileShiftPositionsCS : public FGlobalShader`  
_L11-34_
- inherits: `FGlobalShader`
- L13 _private prototype_ `DECLARE_GLOBAL_SHADER(FNiagaraLWCTileShiftPositionsCS);`
- L14 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraLWCTileShiftPositionsCS, FGlobalShader);`
- L16 _private member_ `static constexpr uint32 ThreadGroupSize = 64;`
- L17 _private member_ `static constexpr uint32 MaxPositions = 8;`
- L20 _private prototype_ `SHADER_PARAMETER_UAV(RWBuffer<float>, FloatBuffer) SHADER_PARAMETER(uint32, FloatBufferStride) SHADER_PARAMETER(uint32, NumInstances) SHADER_PARAMETER_SRV(Buffer<int>, CountBuffer) SHADER_PARAMETER(uint32, CountBufferOffset) SHADER_PARAMETER(uint32, NumPositions) SHADER_PARAMETER_SCALAR_ARRAY(uint32, PositionComponentOffsets, [MaxPositions]) SHADER_PARAMETER(FVector3f, TileShift) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L33 _private prototype_ `static void Execute(FRHIComputeCommandList& RHICmdList, const FParameters& Parameters);`

### `Plugins/FX/Niagara/Source/NiagaraShader/Internal/Stateless/NiagaraStatelessEmitterShaders.h` (Internal)


#### class `NiagaraStateless::FSimulationShaderDefaultCS`  
`class FSimulationShaderDefaultCS : public FSimulationShader`  
_L19-78_
- inherits: `FSimulationShader`
- L23 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSimulationShaderDefaultCS, FSimulationShader);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace NiagaraStateless`
- L15 _macro_ `#define STATELESS_MODULE_COMBINE2(A, B) A##B`
- L16 _macro_ `#define STATELESS_MODULE_COMBINE(A, B) STATELESS_MODULE_COMBINE2(A, B)`
- L17 _macro_ `#define ADD_STATELESS_MODULE(NAME) SHADER_PARAMETER_STRUCT_INCLUDE(NAME, STATELESS_MODULE_COMBINE(ModuleParam,__LINE__))`

### `Plugins/FX/Niagara/Source/NiagaraShader/Internal/Stateless/NiagaraStatelessModuleShaderParameters.h` (Internal)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace NiagaraStateless`

### `Plugins/FX/Niagara/Source/NiagaraShader/Internal/Stateless/NiagaraStatelessSimulationShader.h` (Internal)


#### class `NiagaraStateless::FSimulationShader`  
`class FSimulationShader : public FGlobalShader`  
_L45-61_
- inherits: `FGlobalShader`
- L48 _public typedef_ `using FParameters = FCommonShaderParameters;`
- L49 _public member_ `static constexpr uint32 ThreadGroupSize = 64;`
- L51 _public function_ `FSimulationShader()`
- L52 _public function_ `FSimulationShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)`
- L54 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace NiagaraStateless`
- L12 _variable_ `static constexpr uint32 MaxGpuSpawnInfos = 8;` (scope `NiagaraStateless`)

### `Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraAsyncGpuTraceProviderGsdf.h` (Private)


#### class `FNiagaraAsyncGpuTraceProviderGsdf`  
`class FNiagaraAsyncGpuTraceProviderGsdf : public FNiagaraAsyncGpuTraceProvider`  
_L10-27_
- inherits: `FNiagaraAsyncGpuTraceProvider`
- L13 _public member_ `static const EProviderType Type;`
- L15 _public prototype_ `FNiagaraAsyncGpuTraceProviderGsdf(EShaderPlatform InShaderPlatform, FNiagaraGpuComputeDispatchInterface* Dispatcher);`
- L17 _public prototype_ `static bool IsSupported();`
- L18 _public prototype_ `virtual void PostRenderOpaque(FRHICommandList& RHICmdList, TConstStridedView<FSceneView> Views, TUniformBufferRef<FSceneUniformParameters> SceneUniformBufferRHI, FCollisionGroupHashMap* CollisionGroupHash) override;`
- L19 _public prototype_ `virtual bool IsAvailable() const override;`
- L20 _public prototype_ `virtual void IssueTraces(FRHICommandList& RHICmdList, const FDispatchRequest& Request, TUniformBufferRef<FSceneUniformParameters> SceneUniformBufferRHI, FCollisionGroupHashMap* CollisionGroupHash) override;`
- L21 _public prototype_ `virtual void Reset() override;`
- L22 _public function_ `virtual EProviderType GetType() const override`
- L25 _private member_ `FGlobalDistanceFieldParameterData m_DistanceFieldData;`
- L26 _private member_ `TUniformBufferRef<FViewUniformShaderParameters> m_ViewUniformBuffer;`

### `Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraAsyncGpuTraceProviderHwrt.h` (Private)


#### class `FNiagaraAsyncGpuTraceProviderHwrt`  
`class FNiagaraAsyncGpuTraceProviderHwrt : public FNiagaraAsyncGpuTraceProvider`  
_L12-32_
- inherits: `FNiagaraAsyncGpuTraceProvider`
- L15 _public member_ `static const EProviderType Type;`
- L17 _public prototype_ `FNiagaraAsyncGpuTraceProviderHwrt(EShaderPlatform InShaderPlatform, FNiagaraGpuComputeDispatchInterface* Dispatcher);`
- L19 _public prototype_ `static bool IsSupported();`
- L20 _public prototype_ `virtual void PostRenderOpaque(FRHICommandList& RHICmdList, TConstStridedView<FSceneView> Views, TUniformBufferRef<FSceneUniformParameters> SceneUniformBufferRHI, FCollisionGroupHashMap* CollisionGroupHash) override;`
- L21 _public prototype_ `virtual bool IsAvailable() const override;`
- L22 _public prototype_ `virtual void IssueTraces(FRHICommandList& RHICmdList, const FDispatchRequest& Request, TUniformBufferRef<FSceneUniformParameters> SceneUniformBufferRHI, FCollisionGroupHashMap* CollisionGroupHash) override;`
- L23 _public prototype_ `virtual void Reset() override;`
- L24 _public function_ `virtual EProviderType GetType() const override`
- L27 _private member_ `FRayTracingPipelineState* RayTracingPipelineState = nullptr;`
- L28 _private member_ `FRHIShaderBindingTable* RayTracingSBT = nullptr;` — TODO: Hold reference?
- L29 _private member_ `FRHIShaderResourceView* TLASSRV = nullptr;`
- L30 _private member_ `TUniformBufferRef<FViewUniformShaderParameters> ViewUniformBuffer;`
- L31 _private member_ `FRHIShaderResourceView* InlineRayTracingBindingDataBufferSRV = nullptr;`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraAsyncGpuTraceProvider.h` (Public)


#### struct `FNiagaraAsyncGpuTrace`  
`struct FNiagaraAsyncGpuTrace`  
_L17-23_
- desc: mirrors structure in Engine\Plugins\FX\Niagara\Shaders\Private\NiagaraAsyncGpuTraceCommon.ush
- L19 _public member_ `float Origin[3];`
- L20 _public member_ `float TFar;`
- L21 _public member_ `float Direction[3];`
- L22 _public member_ `uint32 CollisionGroup;`

#### struct `FNiagaraAsyncGpuTraceResult`  
`struct FNiagaraAsyncGpuTraceResult`  
_L26-32_
- desc: mirrors structure in Engine\Plugins\FX\Niagara\Shaders\Private\NiagaraAsyncGpuTraceCommon.ush
- L28 _public member_ `float WorldPosition[3];`
- L29 _public member_ `float HitT;`
- L30 _public member_ `float WorldNormal[3];`
- L31 _public member_ `float _Pad0;` — padding to force 16 byte alignment to meet requirements for VK

#### class `FNiagaraAsyncGpuTraceProvider`  
`class FNiagaraAsyncGpuTraceProvider`  
_L34-98_
- L37 _public typedef_ `using EProviderType = ENDICollisionQuery_AsyncGpuTraceProvider::Type;`
- L38 _public typedef_ `using FProviderPriorityArray = TArray<TEnumAsByte<EProviderType>>;`
- L40 _public function_ `FNiagaraAsyncGpuTraceProvider(EShaderPlatform InShaderPlatform, FNiagaraGpuComputeDispatchInterface* InDispatcher) : ShaderPlatform(InShaderPlatform) , Dispatcher(InDispatcher)`
- L46 _public prototype_ `FNiagaraAsyncGpuTraceProvider() = delete;`
- L47 _public prototype_ `virtual ~FNiagaraAsyncGpuTraceProvider() = default;`
- L61 _public prototype_ `static EProviderType ResolveSupportedType(EProviderType InType, const FProviderPriorityArray& Priorities);`
- L62 _public prototype_ `static bool RequiresGlobalDistanceField(EProviderType InType, const FProviderPriorityArray& Priorities);`
- L63 _public prototype_ `static bool RequiresRayTracingScene(EProviderType InType, const FProviderPriorityArray& Priorities);`
- L75 _public prototype_ `static void BuildCollisionGroupHashMap(FRHICommandList& RHICmdList, ERHIFeatureLevel::Type FeatureLevel, FSceneInterface* Scene, const TMap<FPrimitiveComponentId, uint32>& CollisionGroupMap, FCollisionGroupHashMap& Result);`
- L77 _public prototype_ `static TArray<TUniquePtr<FNiagaraAsyncGpuTraceProvider>> CreateSupportedProviders(EShaderPlatform ShaderPlatform, FNiagaraGpuComputeDispatchInterface* Dispatcher, const FProviderPriorityArray& Priorities);`
- L78 _public prototype_ `static void ClearResults(FRHICommandList& RHICmdList, EShaderPlatform ShaderPlatform, const FDispatchRequest& Request);`
- L80 _public prototype_ `virtual bool IsAvailable() const = 0;`
- L81 _public prototype_ `virtual EProviderType GetType() const = 0;`
- L83 _public prototype_ `virtual void PostRenderOpaque(FRHICommandList& RHICmdList, TConstStridedView<FSceneView> Views, TUniformBufferRef<FSceneUniformParameters> SceneUniformBufferRHI, FCollisionGroupHashMap* CollisionGroupHash);`
- L85 _public function_ `virtual void IssueTraces(FRHICommandList& RHICmdList, const FDispatchRequest& Request, TUniformBufferRef<FSceneUniformParameters> SceneUniformBufferRHI, FCollisionGroupHashMap* CollisionGroupHash)`
- L89 _public function_ `virtual void Reset()`
- L93 _public member_ `const EShaderPlatform ShaderPlatform;`
- L94 _public member_ `FNiagaraGpuComputeDispatchInterface* Dispatcher;`

#### struct `FNiagaraAsyncGpuTraceProvider::FDispatchRequest`  
`struct FDispatchRequest`  
_L49-59_
- L51 _public member_ `FRWBufferStructured* TracesBuffer = nullptr;`
- L52 _public member_ `FRWBufferStructured* ResultsBuffer = nullptr;`
- L53 _public member_ `FRWBuffer* TraceCountsBuffer = nullptr;`
- L54 _public member_ `uint32 TracesOffset = 0;`
- L55 _public member_ `uint32 ResultsOffset = 0;`
- L56 _public member_ `uint32 TraceCountsOffset = 0;`
- L57 _public member_ `uint32 MaxTraceCount = 0;`
- L58 _public member_ `uint32 MaxRetraceCount = 0;`

#### struct `FNiagaraAsyncGpuTraceProvider::FCollisionGroupHashMap`  
`struct FCollisionGroupHashMap`  
_L68-73_
- desc: Hash table. PrimIdHashTable is the main hash table that maps GPUSceneInstanceIndex to and Index we can use to store Collision Groups inside HashToCollisionGroups.
- L70 _public member_ `FRWBufferStructured PrimIdHashTable;`
- L71 _public member_ `FRWBuffer HashToCollisionGroups;`
- L72 _public member_ `uint32 HashTableSize = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENDICollisionQuery_AsyncGpuTraceProvider`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraBatchedElements.h` (Public)


#### class `FBatchedElementNiagara2DArrayAttribute`  
`class FBatchedElementNiagara2DArrayAttribute : public FBatchedElementParameters`  
_L12-29_
- inherits: `FBatchedElementParameters`
- desc: Batched element parameters for gathering attributes from different slices into a single color
- L15 _public typedef_ `typedef TFunction<void(FRHITexture*&, FRHISamplerState*&)> FGetTextureAndSamplerDelegate;`
- L17 _public function_ `FBatchedElementNiagara2DArrayAttribute(const FIntVector4& InAttributeSlices, FGetTextureAndSamplerDelegate InGetTextureAndSampler = nullptr) : AttributeSlices(InAttributeSlices) , GetTextureAndSampler(InGetTextureAndSampler)`
- L24 _public prototype_ `virtual void BindShaders(FRHICommandList& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit, ERHIFeatureLevel::Type InFeatureLevel, const FMatrix& InTransform, const float InGamma, const FMatrix& ColorWeights, const FTexture* Texture) override;` — Binds vertex and pixel shaders for this element
- L27 _private member_ `FIntVector4 AttributeSlices;`
- L28 _private member_ `FGetTextureAndSamplerDelegate GetTextureAndSampler;`

#### class `FBatchedElementNiagaraVolumeAttribute`  
`class FBatchedElementNiagaraVolumeAttribute : public FBatchedElementParameters`  
_L34-56_
- inherits: `FBatchedElementParameters`
- desc: Batched element parameters for gathering attributes from a volume texture into a single color
- L37 _public typedef_ `typedef TFunction<void(FRHITexture*&, FRHISamplerState*&)> FGetTextureAndSamplerDelegate;`
- L39 _public function_ `FBatchedElementNiagaraVolumeAttribute(const FVector2f& InTileUVs, TConstArrayView<FVector3f> InAttributeUVs, TConstArrayView<int32> InAttributeChannels, FGetTextureAndSamplerDelegate InGetTextureAndSampler = nullptr) : TileUVs(InTileUVs) , AttributeUVs(InAttributeUVs) , AttributeChannels(InAttributeChannels) , GetTextureAndSampler(InGetTextureAndSampler)`
- L48 _public prototype_ `virtual void BindShaders(FRHICommandList& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit, ERHIFeatureLevel::Type InFeatureLevel, const FMatrix& InTransform, const float InGamma, const FMatrix& ColorWeights, const FTexture* Texture) override;` — Binds vertex and pixel shaders for this element
- L51 _private member_ `FVector2f TileUVs;`
- L52 _private member_ `TArray<FVector3f, TInlineAllocator<4>> AttributeUVs;`
- L53 _private member_ `TArray<int32, TInlineAllocator<4>> AttributeChannels;`
- L55 _private member_ `FGetTextureAndSamplerDelegate GetTextureAndSampler;`

#### class `FBatchedElementNiagaraInvertColorChannel`  
`class FBatchedElementNiagaraInvertColorChannel : public FBatchedElementParameters`  
_L61-74_
- inherits: `FBatchedElementParameters`
- desc: Batched element parameters for inverting a color channel
- L64 _public function_ `FBatchedElementNiagaraInvertColorChannel(uint32 InChannelMask) : ChannelMask(InChannelMask)`
- L70 _public prototype_ `virtual void BindShaders(FRHICommandList& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit, ERHIFeatureLevel::Type InFeatureLevel, const FMatrix& InTransform, const float InGamma, const FMatrix& ColorWeights, const FTexture* Texture) override;` — Binds vertex and pixel shaders for this element
- L73 _private member_ `uint32 ChannelMask;`

#### class `FBatchedElementNiagaraSimple`  
`class FBatchedElementNiagaraSimple : public FBatchedElementParameters`  
_L79-94_
- inherits: `FBatchedElementParameters`
- desc: Simple batched element using a 2d texture
- L82 _public function_ `FBatchedElementNiagaraSimple(FMatrix InColorTransform = FMatrix::Identity, bool InAlphaBlend = false) : ColorTransform(InColorTransform) , bAlphaBlend(InAlphaBlend)`
- L89 _public prototype_ `virtual void BindShaders(FRHICommandList& RHICmdList, FGraphicsPipelineStateInitializer& GraphicsPSOInit, ERHIFeatureLevel::Type InFeatureLevel, const FMatrix& InTransform, const float InGamma, const FMatrix& ColorWeights, const FTexture* Texture) override;` — Binds vertex and pixel shaders for this element
- L92 _private member_ `FMatrix ColorTransform;`
- L93 _private member_ `bool bAlphaBlend;`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraClearCounts.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace NiagaraClearCounts`
- L14 _prototype_ `void ClearCountsInt(FRDGBuilder& GraphBuilder, FRDGBufferUAVRef UAV, TConstArrayView<TPair<uint32, int32>> IndexAndValueArray);` (scope `NiagaraClearCounts`)
- L15 _prototype_ `void ClearCountsUInt(FRDGBuilder& GraphBuilder, FRDGBufferUAVRef UAV, TConstArrayView<TPair<uint32, uint32>> IndexAndValueArray);` (scope `NiagaraClearCounts`)
- L18 _prototype_ `void ClearCountsInt(FRHICommandList& RHICmdList, FRHIUnorderedAccessView* UAV, TConstArrayView<TPair<uint32, int32>> IndexAndValueArray);` (scope `NiagaraClearCounts`) — -TODO:RDG: Deprecated
- L19 _prototype_ `void ClearCountsUInt(FRHICommandList& RHICmdList, FRHIUnorderedAccessView* UAV, TConstArrayView<TPair<uint32, uint32>> IndexAndValueArray);` (scope `NiagaraClearCounts`)

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraDebugShaders.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace NiagaraDebugShaders`
- L15 _prototype_ `void ClearUAV(FRDGBuilder& GraphBuilder, FRDGBufferUAVRef UAV, FUintVector4 ClearValues, uint32 UIntsToSet);` (scope `NiagaraDebugShaders`)
- L17 _prototype_ `void DrawDebugLines( class FRDGBuilder& GraphBuilder, const class FSceneView& View, FRDGTextureRef SceneColor, FRDGTextureRef SceneDepth, const uint32 LineInstanceCount, FRDGBufferRef LineBuffer );` (scope `NiagaraDebugShaders`)
- L22 _prototype_ `void DrawDebugLines( class FRDGBuilder& GraphBuilder, const class FSceneView& View, FRDGTextureRef SceneColor, FRDGTextureRef SceneDepth, FRDGBufferRef ArgsBuffer, FRDGBufferRef LineBuffer );` (scope `NiagaraDebugShaders`)
- L27 _prototype_ `void VisualizeTexture( class FRDGBuilder& GraphBuilder, const FSceneView& View, const FScreenPassRenderTarget& Output, const FIntPoint& Location, const int32& DisplayHeight, const FIntVector4& AttributesToVisualize, FRDGTextureRef Texture, const FIntVector4& NumTextureAttributes, uint32 TickCounter, const FVector2D& PreviewDisplayRange = FVector2D::ZeroVector );` (scope `NiagaraDebugShaders`)

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraDistanceFieldHelper.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace FNiagaraDistanceFieldHelper`
- L14 _prototype_ `void SetGlobalDistanceFieldParameters(const FGlobalDistanceFieldParameterData* OptionalParameterData, FGlobalDistanceFieldParameters2& ShaderParameters);` (scope `FNiagaraDistanceFieldHelper`)

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraGPUSceneUtils.h` (Public)


#### class `FNiagaraGPUSceneUtils`  
`class FNiagaraGPUSceneUtils`  
_L13-45_
- L17 _public prototype_ `SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View) SHADER_PARAMETER_RDG_UNIFORM_BUFFER(FSceneUniformParameters, Scene) SHADER_PARAMETER_STRUCT_INCLUDE(FGPUSceneWriterParameters, GPUSceneWriterParameters) SHADER_PARAMETER_STRUCT_INCLUDE(FNiagaraMeshCommonParameters, Common) SHADER_PARAMETER(uint32, PrimitiveId) SHADER_PARAMETER(uint32, ParticleCount) SHADER_PARAMETER_SRV(Buffer<uint>, GPUParticleCountBuffer) SHADER_PARAMETER(uint32, GPUParticleCountOffset) SHADER_PARAMETER(int, MeshIndex) SHADER_PARAMETER(int, MeshIndexDataOffset) SHADER_PARAMETER(int, RendererVisibility) SHADER_PARAMETER(int, VisibilityTagDataOffset) SHADER_PARAMETER(FVector3f, LocalBoundingCenter) SHADER_PARAMETER(FVector2f, DistanceCullRangeSquared) SHADER_PARAMETER(FVector4f, LODScreenSize) SHADER_PARAMETER(int, bNeedsPrevTransform) END_SHADER_PARAMETER_STRUCT() static void AddUpdateMeshParticleInstancesPass( FRDGBuilder& GraphBuilder, FUpdateMeshParticleInstancesParams& Params, ERHIFeatureLevel::Type FeatureLevel, bool bPreciseMotionVectors );`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraGenerateMips.h` (Public)


#### enum `ENiagaraMipMapGenerationType`  
`enum class ENiagaraMipMapGenerationType : uint8`  
_L11-25_
- reflection: `UENUM()`
- L14 _public enumerator_ `Unfiltered` — Result is taken from whatever texel the sample lies on, aka Point Sampling.
- L16 _public enumerator_ `Linear` — Linear blending is performed between a 2x2 (or 2x2x2) region of texels, aka Bilinear / Trilinear.
- L18 _public enumerator_ `Blur1 UMETA(DisplayName="Gaussian 3 texel filter")` — A blur filter across a 3x3 (or 3x3x3) region of texels.
- L20 _public enumerator_ `Blur2 UMETA(DisplayName="Gaussian 5 texel filter")` — A blur filter across a 5x5 (or 5x5x5) region of texels.
- L22 _public enumerator_ `Blur3 UMETA(DisplayName="Gaussian 7 texel filter")` — A blur filter across a 7x7 (or 7x7x7) region of texels.
- L24 _public enumerator_ `Blur4 UMETA(DisplayName="Gaussian 9 texel filter")` — A blur filter across a 9x9 (or 9x9x9) region of texels.

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace NiagaraGenerateMips`
- L29 _prototype_ `void GenerateMips(FRDGBuilder& GraphBuilder, FRDGTextureRef RDGTexture, ENiagaraMipMapGenerationType GenType);` (scope `NiagaraGenerateMips`)

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraNeighborQuerySort.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace NiagaraNeighborQuerySort`
- L18 _variable_ `static constexpr uint32 NQDistBits = 0;` (scope `NiagaraNeighborQuerySort`) — Number of low bits in the combined sort key reserved for quantized distance-to-cell-center. The remaining (32 - NQDistBits) high bits hold the cell ID. Set to 0 to disable intra-cell distance sorting (full 32-bit cell ID, no distance packing). Must agree with NQ_DIST_BITS in NiagaraDataInterfaceNeighborQuery.ush — both are fed from this constant via ModifyCompilationEnvironment / GetParameterDefinitionHLSL.
- L23 _variable_ `static constexpr uint64 NQMaxSortCells = (uint64(1) << (32u - NQDistBits)) - uint64(NQDistBits == 0);` (scope `NiagaraNeighborQuerySort`) — Max valid cell count. Stored as uint64 so 2^32 is representable without overflow. When NQDistBits==0 the raw cell ID is the sort key, so one value is lost to the NEIGHBORQUERY_INVALID_CELL sentinel (0xFFFFFFFF). When NQDistBits>0 the dist cap (NQ_DIST_MAX = 2^N-2) ensures no valid combined key reaches 0xFFFFFFFF.
- L26 _prototype_ `void Histogram(FRDGBuilder& GraphBuilder, FRDGBufferSRVRef CellIdSRV, FRDGBufferUAVRef CellCountUAV, uint32 NumSlots);` (scope `NiagaraNeighborQuerySort`) — Pass 2: Build histogram — count particles per cell
- L29 _prototype_ `void PrefixSum(FRDGBuilder& GraphBuilder, FRDGBufferUAVRef CellCountUAV, FRDGBufferUAVRef CellOffsetUAV, uint32 NumCells);` (scope `NiagaraNeighborQuerySort`) — Pass 3: Exclusive prefix sum over cell counts
- L34 _prototype_ `void Scatter(FRDGBuilder& GraphBuilder, FRDGBufferSRVRef CellIdSRV, FRDGBufferSRVRef ParticleIdIndexSRV, FRDGBufferUAVRef CellOffsetUAV, FRDGBufferUAVRef ParticleListUAV, FRDGBufferSRVRef AcquireTagSRV, FRDGBufferUAVRef AcquireTagListUAV, uint32 NumSlots, uint32 MaxCellsPerParticle, bool bHasPersistentIDBuffers);` (scope `NiagaraNeighborQuerySort`) — Pass 4: Scatter sorted particle indices (and AcquireTag satellite data) When bHasPersistentIDBuffers is false, particle index is derived from slot / MaxCellsPerParticle and AcquireTag is not carried.

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraRibbonCompute.h` (Public)


#### struct `FNiagaraRibbonComputeCommon`  
`struct FNiagaraRibbonComputeCommon`  
_L66-78_
- L68 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment, int32 ThreadGroupSize);`
- L70 _public member_ `static constexpr uint32 VertexGenReductionInitializationThreadSize = 64;`
- L71 _public member_ `static constexpr uint32 VertexGenReductionPropagationThreadSize = 64;`
- L72 _public member_ `static constexpr uint32 VertexGenReductionFinalizationThreadSize = 64;`
- L73 _public member_ `static constexpr uint32 VertexGenFinalizationThreadSize = 64;`
- L75 _public member_ `static constexpr uint32 IndexGenThreadSize = 64;`
- L77 _public member_ `static constexpr uint32 IndexGenOptimalLoopVertexLimit = 32;`

#### class `FNiagaraRibbonSortPhase1CS`  
`class FNiagaraRibbonSortPhase1CS : public FGlobalShader`  
_L91-102_
- inherits: `FGlobalShader`
- desc: Compute shader used to generate particle sort keys.
- L94 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraRibbonSortPhase1CS, FGlobalShader);`
- L96 _private member_ `static constexpr uint32 BubbleSortGroupWidth = 32;`
- L98 _private typedef_ `using FParameters = FRibbonOrderSortParameters;`
- L99 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FRibbonHasFullRibbonID, FRibbonHasRibbonID>;`
- L101 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `FNiagaraRibbonSortPhase2CS`  
`class FNiagaraRibbonSortPhase2CS : public FGlobalShader`  
_L107-118_
- inherits: `FGlobalShader`
- desc: Compute shader used to generate particle sort keys.
- L110 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraRibbonSortPhase2CS, FGlobalShader);`
- L112 _private member_ `static constexpr uint32 ThreadGroupSize = 64;`
- L114 _private typedef_ `using FParameters = FRibbonOrderSortParameters;`
- L115 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FRibbonHasFullRibbonID, FRibbonHasRibbonID>;`
- L117 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `FNiagaraRibbonVertexReductionInitializationCS`  
`class FNiagaraRibbonVertexReductionInitializationCS : public FGlobalShader`  
_L136-145_
- inherits: `FGlobalShader`
- L139 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraRibbonVertexReductionInitializationCS, FGlobalShader);`
- L141 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FRibbonHasFullRibbonID, FRibbonHasRibbonID>;`
- L142 _private typedef_ `using FParameters = FNiagaraRibbonVertexReductionParameters;`
- L144 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `FNiagaraRibbonVertexReductionFinalizeCS`  
`class FNiagaraRibbonVertexReductionFinalizeCS : public FGlobalShader`  
_L161-170_
- inherits: `FGlobalShader`
- L164 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraRibbonVertexReductionFinalizeCS, FGlobalShader);`
- L166 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FRibbonHasFullRibbonID, FRibbonHasRibbonID>;`
- L167 _private typedef_ `using FParameters = FNiagaraRibbonVertexReductionFinalizationParameters;`
- L169 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `FNiagaraRibbonUVParamCalculationCS`  
`class FNiagaraRibbonUVParamCalculationCS : public FGlobalShader`  
_L195-204_
- inherits: `FGlobalShader`
- L198 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraRibbonUVParamCalculationCS, FGlobalShader);`
- L200 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FRibbonHasFullRibbonID, FRibbonHasRibbonID>;`
- L201 _private typedef_ `using FParameters = FNiagaraRibbonVertexFinalizationParameters;`
- L203 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `FNiagaraRibbonCreateIndexBufferParamsCS`  
`class FNiagaraRibbonCreateIndexBufferParamsCS : public FGlobalShader`  
_L235-243_
- inherits: `FGlobalShader`
- L238 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraRibbonCreateIndexBufferParamsCS, FGlobalShader);`
- L240 _private typedef_ `using FParameters = FNiagaraRibbonInitializeIndices;`
- L242 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `FNiagaraRibbonCreateIndexBufferCS`  
`class FNiagaraRibbonCreateIndexBufferCS : public FGlobalShader`  
_L274-283_
- inherits: `FGlobalShader`
- L277 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraRibbonCreateIndexBufferCS, FGlobalShader);`
- L279 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FRibbonHasFullRibbonID, FRibbonHasRibbonID>;`
- L280 _private typedef_ `using FParameters = FNiagaraRibbonGenerateIndices;`
- L282 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `FNiagaraRibbonAggregationStepCS`  
`class FNiagaraRibbonAggregationStepCS : public FGlobalShader`  
_L293-302_
- inherits: `FGlobalShader`
- L296 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraRibbonAggregationStepCS, FGlobalShader);`
- L298 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FRibbonHasFullRibbonID, FRibbonHasRibbonID>;`
- L299 _private typedef_ `using FParameters = FNiagaraRibbonAggregationStepParameters;`
- L301 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `FNiagaraRibbonAggregationApplyCS`  
`class FNiagaraRibbonAggregationApplyCS : public FGlobalShader`  
_L314-323_
- inherits: `FGlobalShader`
- L317 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraRibbonAggregationApplyCS, FGlobalShader);`
- L319 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FRibbonHasFullRibbonID, FRibbonHasRibbonID>;`
- L320 _private typedef_ `using FParameters = FNiagaraRibbonAggregationApplyParameters;`
- L322 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraSVTShaders.h` (Public)


#### class `FNiagaraCopySVTToDenseBufferCS`  
`class FNiagaraCopySVTToDenseBufferCS : public FGlobalShader`  
_L8-25_
- inherits: `FGlobalShader`
- L11 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraCopySVTToDenseBufferCS, FGlobalShader);`
- L13 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `FNiagaraBlendSVTsToDenseBufferCS`  
`class FNiagaraBlendSVTsToDenseBufferCS : public FGlobalShader`  
_L27-57_
- inherits: `FGlobalShader`
- L30 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraBlendSVTsToDenseBufferCS, FGlobalShader);`
- L32 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L33 _private prototype_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraScriptBase.h` (Public)


#### enum `ENiagaraGpuDispatchType`  
`enum class ENiagaraGpuDispatchType : uint8`  
_L11-21_
- reflection: `UENUM()`
- L14 _public enumerator_ `OneD` — Instances will distribute along X using platforms specific thread counts.
- L16 _public enumerator_ `TwoD` — Instances will distribute along X & Y using platforms specific thread counts.
- L18 _public enumerator_ `ThreeD` — Instances will distribute along X, Y & Z using platforms specific thread counts.
- L20 _public enumerator_ `Custom UMETA(Hidden)` — NumThreads will be determined manually.

#### enum `ENiagaraDirectDispatchElementType`  
`enum class ENiagaraDirectDispatchElementType : uint8`  
_L24-45_
- reflection: `UENUM()`
- L31 _public enumerator_ `NumThreads` — Number of elements is the number of threads launched in that dimension. Threads that are out of bounds due to shader thread group size will be automatically clipped (i.e. code will not run). For example, if GroupSize = 64,1,1 and NumElements = 32,1,1 only the first 32 threads will run the code.
- L39 _public enumerator_ `NumThreadsNoClipping` — Number of elements is the number of threads launched in that dimension. Threads that are out of bounds due to shader thread group size will not be clipped and your code will execute. You are responsible for ensuring you do not make invalid access from these OOB threads. For example, if GroupSize = 64,1,1 and NumElements = 32,1,1 you code will execute 64 times. Use this path if you need to add group sync's within you graph code.
- L44 _public enumerator_ `NumGroups` — Number of elements refers to the number of groups to launch. For example, if you defined NumElements as 3,1,1 and GroupSize was 64,1,1 you are effectively launching 192 threads.

#### enum `ENiagaraSimStageExecuteBehavior`  
`enum class ENiagaraSimStageExecuteBehavior : uint8`  
_L48-56_
- reflection: `UENUM()`
- L51 _public enumerator_ `Always` — The stage will run every frame.
- L53 _public enumerator_ `OnSimulationReset` — The stage will only run on the frame when the simulation is reset.
- L55 _public enumerator_ `NotOnSimulationReset` — The stage will not run on the frame where the simulation is reset.

#### struct `FSimulationStageMetaData`  
`struct FSimulationStageMetaData`  
_L59-162_
- reflection: `USTRUCT()`
- L63 _public prototype_ `FSimulationStageMetaData();`
- L67 _public member_ `FName SimulationStageName;` — `UPROPERTY()` — User simulation stage name.
- L70 _public member_ `FName EnabledBinding;` — `UPROPERTY()`
- L74 _public member_ `FIntVector ElementCount = FIntVector::ZeroValue;` — `UPROPERTY()` — Optional binding to manually specify the element count.
- L78 _public member_ `FName ElementCountXBinding;` — `UPROPERTY()` — Optional binding to manually specify the element count.
- L82 _public member_ `FName ElementCountYBinding;` — `UPROPERTY()` — Optional binding to manually specify the element count.
- L86 _public member_ `FName ElementCountZBinding;` — `UPROPERTY()` — Optional binding to manually specify the element count.
- L90 _public member_ `ENiagaraIterationSource IterationSourceType = ENiagaraIterationSource::Particles;` — `UPROPERTY()` — The source we are iteration over.
- L94 _public member_ `FName IterationDataInterface;` — `UPROPERTY()` — When IterationSource is ENiagaraIterationSource::DataInterface this is the data interface name.
- L98 _public member_ `FName IterationDirectBinding;` — `UPROPERTY()` — When IterationSource is ENiagaraIterationSource::IterationDirectBinding this is the variable we are bound to.
- L102 _public member_ `ENiagaraSimStageExecuteBehavior ExecuteBehavior = ENiagaraSimStageExecuteBehavior::Always;` — `UPROPERTY()` — Controls when the simulation stage will execute.
- L106 _public member_ `uint32 bWritesParticles : 1;` — `UPROPERTY()` — Do we write to particles this stage?
- L110 _public member_ `uint32 bPartialParticleUpdate : 1;` — `UPROPERTY()` — When enabled the simulation stage does not write all variables out, so we are reading / writing to the same buffer.
- L113 _public member_ `uint32 bParticleIterationStateEnabled : 1;` — `UPROPERTY()`
- L116 _public member_ `uint32 bGpuIndirectDispatch : 1;` — `UPROPERTY()`
- L120 _public member_ `FName ParticleIterationStateBinding;` — `UPROPERTY()` — When the value is not none this is the binding used for particle state iteration stages.
- L123 _public member_ `int32 ParticleIterationStateComponentIndex = INDEX_NONE;` — Cached component index for particle iteration stage.
- L127 _public member_ `FIntPoint ParticleIterationStateRange = FIntPoint(0, 0);` — `UPROPERTY()` — Inclusive range to compare the particle state value with.
- L131 _public member_ `TArray<FName> OutputDestinations;` — `UPROPERTY()` — DataInterfaces that we write to in this stage.
- L135 _public member_ `TArray<FName> InputDataInterfaces;` — `UPROPERTY()` — DataInterfaces that we read from in this stage.
- L139 _public member_ `int32 NumIterations = 1;` — `UPROPERTY()` — The number of iterations for the stage.
- L143 _public member_ `FName NumIterationsBinding;` — `UPROPERTY()` — Optional binding to gather num iterations from.
- L145 _public function_ `inline bool ShouldRunStage(bool bResetData) const`
- L154 _public member_ `ENiagaraGpuDispatchType GpuDispatchType = ENiagaraGpuDispatchType::OneD;` — `UPROPERTY()` — Dispatch type set for this stage.
- L157 _public member_ `ENiagaraDirectDispatchElementType GpuDirectDispatchElementType = ENiagaraDirectDispatchElementType::NumThreads;` — `UPROPERTY()`
- L161 _public member_ `FIntVector GpuDispatchNumThreads = FIntVector(0, 0, 0);` — `UPROPERTY()` — When in custom mode this is the num threads.

#### class `UNiagaraScriptBase`  
`class UNiagaraScriptBase : public UObject`  
_L165-172_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UObject`
- L169 _private prototype_ `virtual void ModifyCompilationEnvironment(EShaderPlatform Platform, struct FShaderCompilerEnvironment& OutEnvironment) const PURE_VIRTUAL(UNiagaraScriptBase::ModifyCompilationEnvironment, );`
- L170 _private prototype_ `virtual bool ShouldCompile(EShaderPlatform Platform) const PURE_VIRTUAL(UNiagaraScriptBase::ShouldCompile, return true; );`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraShader.h` (Public)


#### class `FNiagaraShader`  
`class FNiagaraShader : public FShader`  
_L23-245_
- inherits: `FShader`
- desc: Base class for all generated Niagara compute shaders.
- L26 _public prototype_ `DECLARE_SHADER_TYPE(FNiagaraShader, Niagara);`
- L200 _public typedef_ `using FPermutationParameters = FNiagaraShaderPermutationParameters;`
- L202 _public member_ `static FName UniformBufferLayoutName;`
- L204 _public function_ `static FIntVector GetDefaultThreadGroupSize(ENiagaraGpuDispatchType DispatchType)`
- L216 _public function_ `static void ModifyCompilationEnvironment(const FNiagaraShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`
- L223 _public function_ `FNiagaraShader()`
- L224 _public prototype_ `FNiagaraShader(const FNiagaraShaderType::CompiledShaderInitializerType& Initializer);`
- L226 _public function_ `TConstArrayView<FNiagaraDataInterfaceParamRef> GetDIParameters()`
- L235 _public prototype_ `static void BuildClassSchema(FAppendToClassSchemaContext& Context);` — Called from UNiagaraSystem::AppendToClassSchema() to collect the Script specific details for iterative cooking

#### Free symbols / members of external scopes

- L247 _externvar_ `extern int32 GNiagaraSkipVectorVMBackendOptimizations;`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraShaderCompilationManager.h` (Public)


#### struct `FNiagaraShaderMapCompileResults`  
`struct FNiagaraShaderMapCompileResults`  
_L10-20_
- desc: Results for a single compiled shader map.
- L12 _public function_ `FNiagaraShaderMapCompileResults() : NumJobsQueued(0), bAllJobsSucceeded(true)`
- L17 _public member_ `int32 NumJobsQueued;`
- L18 _public member_ `bool bAllJobsSucceeded;`
- L19 _public member_ `TArray<FShaderCommonCompileJobPtr> FinishedJobs;`

#### struct `FNiagaraShaderMapFinalizeResults`  
`struct FNiagaraShaderMapFinalizeResults : public FNiagaraShaderMapCompileResults`  
_L24-33_
- inherits: `FNiagaraShaderMapCompileResults`
- desc: Results for a single compiled and finalized shader map.
- L27 _public member_ `int32 FinalizeJobIndex;` — Tracks finalization progress on this shader map.
- L29 _public function_ `FNiagaraShaderMapFinalizeResults(const FNiagaraShaderMapCompileResults& InCompileResults) : FNiagaraShaderMapCompileResults(InCompileResults), FinalizeJobIndex(0)`

#### class `FNiagaraShaderCompilationManager`  
`class FNiagaraShaderCompilationManager`  
_L38-57_
- desc: handles gpu compute shader compile jobs, applying of the shaders to their scripts, and some error handling
- L41 _public prototype_ `FNiagaraShaderCompilationManager() = default;`
- L43 _public prototype_ `void AddJobs(TArray<FShaderCommonCompileJobPtr> InNewJobs);`
- L44 _public prototype_ `void ProcessAsyncResults();`
- L46 _public prototype_ `void FinishCompilation(const TArray<int32>& ShaderMapIdsToFinishCompiling);`
- L48 _private prototype_ `void ProcessCompiledNiagaraShaderMaps(TMap<int32, FNiagaraShaderMapFinalizeResults>& CompiledShaderMaps, float TimeBudget);`
- L50 _private member_ `TArray<FShaderCommonCompileJobPtr> JobQueue;`
- L53 _private member_ `TMap<int32, FNiagaraShaderMapCompileResults> NiagaraShaderMapJobs;` — Map from shader map Id to the compile results for that map, used to gather compiled results.
- L56 _private member_ `TMap<int32, FNiagaraShaderMapFinalizeResults> PendingFinalizeNiagaraShaderMaps;` — Map from shader map id to results being finalized.  Used to track shader finalizations over multiple frames.

#### Free symbols / members of external scopes

- L59 _externvar_ `extern FNiagaraShaderCompilationManager GNiagaraShaderCompilationManager;`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraShaderModule.h` (Public)


#### class `INiagaraShaderModule`  
`class INiagaraShaderModule : public IModuleInterface`  
_L14-46_
- inherits: `IModuleInterface`
- desc: Niagara shader module interface
- L17 _public prototype_ `DECLARE_DELEGATE_RetVal(void, FOnProcessQueue);`
- L18 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(UNiagaraDataInterfaceBase*, FOnRequestDefaultDataInterface, const FString&);`
- L20 _public prototype_ `FDelegateHandle SetOnProcessShaderCompilationQueue(FOnProcessQueue InOnProcessQueue);`
- L21 _public prototype_ `void ResetOnProcessShaderCompilationQueue(FDelegateHandle DelegateHandle);`
- L22 _public prototype_ `void ProcessShaderCompilationQueue();`
- L25 _public prototype_ `FDelegateHandle SetOnRequestDefaultDataInterfaceHandler(FOnRequestDefaultDataInterface InHandler);` — Handles converting string name to data interface CDO pointer
- L26 _public prototype_ `void ResetOnRequestDefaultDataInterfaceHandler();`
- L27 _public prototype_ `UNiagaraDataInterfaceBase* RequestDefaultDataInterface(const FString& DIClassName);`
- L29 _public prototype_ `virtual void StartupModule() override;`
- L31 _public function_ `virtual void ShutdownModule() override`
- L37 _public function_ `static INiagaraShaderModule* Get()` — If you know that you want the shader module and have access to the header you don't have to find the module.
- L43 _private member_ `FOnProcessQueue OnProcessQueue;`
- L44 _private member_ `FOnRequestDefaultDataInterface OnRequestDefaultDataInterface;`
- L45 _private member_ `static INiagaraShaderModule* Singleton;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_RetVal(void, FOnProcessQueue);`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(UNiagaraDataInterfaceBase*, FOnRequestDefaultDataInterface, const FString&);`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraShaderParametersBuilder.h` (Public)


#### class `FNiagaraShaderParametersBuilder`  
`class FNiagaraShaderParametersBuilder`  
_L8-75_
- L11 _public function_ `explicit FNiagaraShaderParametersBuilder(const FNiagaraDataInterfaceGPUParamInfo& InGPUParamInfo, TArray<FString>& InLooseNames, TArray<FNiagaraDataInterfaceStructIncludeInfo>& InStructIncludeInfos, FShaderParametersMetadataBuilder& InMetadataBuilder) : GPUParamInfo(InGPUParamInfo) , StructIncludeInfos(InStructIncludeInfos) , LooseNames(InLooseNames) , MetadataBuilder(InMetadataBuilder)`
- L21 _public function_ `template<typename T> void AddLooseParam(const TCHAR* Name)` — Adds a loose parameter that is scoped to the data interface i.e. if the parameter was called "MyFloat" the shader variable would be "UniqueDataInterfaceName_MyFloat"
- L29 _public function_ `template<typename T> void AddLooseParamArray(const TCHAR* Name, int32 NumElements)` — Adds a loose array parameter that is scoped to the data interface i.e. if the parameter was called "MyFloat" the shader variable would be "UniqueDataInterfaceName_MyFloat"
- L37 _public function_ `template<typename T> void AddNestedStruct()` — Adds a shader parameters structure that is scoped to the data interface i.e. if the structured contained "MyFloat" the shader variable would be "UniqueDataInterfaceName_MyFloat"
- L44 _public function_ `inline void AddIncludedStruct(const FShaderParametersMetadata* StructMetadata)` — Adds a shader parameters structure that is global in scope i.e. if the structure contained "MyFloat" the shader variable would be named "MyFloat"
- L63 _public function_ `template<typename T> void AddIncludedStruct()` — Adds a shader parameters structure that is global in scope i.e. if the structure contained "MyFloat" the shader variable would be named "MyFloat"
- L68 _public function_ `TConstArrayView<FNiagaraDataInterfaceGeneratedFunction> GetGeneratedFunctions() const`
- L71 _private member_ `const FNiagaraDataInterfaceGPUParamInfo& GPUParamInfo;`
- L72 _private member_ `TArray<FNiagaraDataInterfaceStructIncludeInfo>& StructIncludeInfos;`
- L73 _private member_ `TArray<FString>& LooseNames;`
- L74 _private member_ `FShaderParametersMetadataBuilder& MetadataBuilder;`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraShaderParticleID.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ERHIFeatureLevel`
- L12 _prototype_ `extern void NiagaraInitGPUFreeIDList(FRHICommandList& RHICmdList, ERHIFeatureLevel::Type FeatureLevel, FRHIUnorderedAccessView* NewBufferUAV, uint32 NewBufferNumElements, FRHIShaderResourceView* ExistingBufferSRV, uint32 ExistingBufferNumElements);`
- L13 _prototype_ `extern void NiagaraComputeGPUFreeIDs(FRHICommandList& RHICmdList, ERHIFeatureLevel::Type FeatureLevel, FRHIShaderResourceView* IDToIndexTableSRV, uint32 NumIDs, FRHIUnorderedAccessView* FreeIDUAV, FRHIUnorderedAccessView* FreeIDListSizesUAV, uint32 FreeIDListIndex);`
- L14 _prototype_ `extern void NiagaraFillGPUIntBuffer(FRHICommandList& RHICmdList, ERHIFeatureLevel::Type FeatureLevel, FRHIUnorderedAccessView* BufferUAV, uint32 NumElements, int32 FillValue);`

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraShaderType.h` (Public)


#### struct `FNiagaraShaderPermutationParameters`  
`struct FNiagaraShaderPermutationParameters : public FShaderPermutationParameters`  
_L42-50_
- inherits: `FShaderPermutationParameters`
- L44 _public member_ `const FNiagaraShaderScript* Script;`
- L46 _public function_ `FNiagaraShaderPermutationParameters(EShaderPlatform InPlatform, const FNiagaraShaderScript* InScript) : FShaderPermutationParameters(InPlatform) , Script(InScript)`

#### class `FNiagaraShaderType`  
`class FNiagaraShaderType : public FShaderType`  
_L55-198_
- inherits: `FShaderType`
- desc: A shader meta type for niagara-linked shaders.
- L82 _public function_ `FNiagaraShaderType( FTypeLayoutDesc& InTypeLayout, const TCHAR* InName, const TCHAR* InSourceFilename, const TCHAR* InFunctionName, uint32 InFrequency,`
- L138 _public prototype_ `void BeginCompileShader( uint32 ShaderMapId, int32 PermutationId, const FNiagaraShaderScript* Script, FSharedShaderCompilerEnvironment* CompilationEnvironment, EShaderPlatform Platform, TArray<TRefCountPtr<FShaderCommonCompileJob>>& NewJobs, FShaderTarget Target );` — Enqueues a compilation for a new shader of this type. @param Script - The script to link the shader with.
- L148 _public prototype_ `void BeginCompileShaderFromSource( FStringView FriendlyName, uint32 ShaderMapId, int32 PermutationId, TSharedRef<FNiagaraShaderScriptParametersMetadata> ShaderParameters, FSharedShaderCompilerEnvironment* CompilationEnvironment, FStringView ScriptSource, EShaderPlatform Platform, const FSimulationStageMetaData& SimStageMetaData, FShaderTarget Target, TArray<TRefCountPtr<FShaderCommonCompileJob>>& NewJobs ) const;`
- L166 _public prototype_ `FShader* FinishCompileShader( uint64 NiagaraShaderMapHash, const FShaderCompileJob& CurrentJob ) const;` — Either creates a new instance of this type or returns an equivalent existing shader. @param NiagaraShaderMapHash - The hash computed for the owning shadermap @param CurrentJob - Compile job that was enqueued by BeginCompileShader.
- L178 _public function_ `bool ShouldCache(EShaderPlatform Platform,const FNiagaraShaderScript* Script) const` — Checks if the shader type should be cached for a particular platform and script. @param Platform - The platform to check. @param script - The script to check. @return True if this shader type should be cached.
- L185 _public prototype_ `void AddUniformBufferIncludesToEnvironment(FShaderCompilerEnvironment& OutEnvironment, EShaderPlatform Platform) const;` — Adds include statements for uniform buffers that this shader type references, and builds a prefix for the shader file with the include statements.
- L193 _protected function_ `void SetupCompileEnvironment(EShaderPlatform Platform, const FNiagaraShaderScript* Script, FShaderCompilerEnvironment& Environment) const` — Sets up the environment used to compile an instance of this shader type. @param Platform - Platform to compile for. @param Environment - The shader compile environment that the function modifies.

#### struct `FNiagaraShaderType::FParameters`  
`struct FParameters : public FShaderType::FParameters`  
_L58-66_
- inherits: `FShaderType::FParameters`
- L60 _public member_ `TSharedRef<FNiagaraShaderScriptParametersMetadata> ScriptParametersMetadata;`
- L62 _public function_ `FParameters(const TSharedRef<FNiagaraShaderScriptParametersMetadata>& InScriptParametersMetadata) : ScriptParametersMetadata(InScriptParametersMetadata)`

#### struct `FNiagaraShaderType::CompiledShaderInitializerType`  
`struct CompiledShaderInitializerType : FShaderCompiledShaderInitializerType`  
_L68-80_
- inherits: `FShaderCompiledShaderInitializerType`
- L70 _public function_ `CompiledShaderInitializerType( const FShaderType* InType, const FParameters* InParameters, int32 InPermutationId, const FShaderCompilerOutput& CompilerOutput, uint64 InNiagaraShaderMapHash ) : FShaderCompiledShaderInitializerType(InType, InParameters, InPermutationId, CompilerOutput, InNiagaraShaderMapHash, nullptr, nullptr)`

#### Free symbols / members of external scopes

- L16 _macro_ `#define IMPLEMENT_NIAGARA_SHADER_TYPE(TemplatePrefix,ShaderClass,SourceFilename,FunctionName,Frequency) \` — A macro to implement Niagara shaders.
- L33 _prototype_ `extern void UpdateNiagaraShaderCompilingStats(const FNiagaraShaderScript* Script);` — Called for every Niagara shader to update the appropriate stats.
- L40 _prototype_ `extern void DumpComputeShaderStats( EShaderPlatform Platform );` — Dump shader stats for a given platform. @param	Platform	Platform to dump stats for.

### `Plugins/FX/Niagara/Source/NiagaraShader/Public/NiagaraShared.h` (Public)


#### enum `FNiagaraCompileEventSeverity`  
`enum class FNiagaraCompileEventSeverity : uint8`  
_L41-47_
- reflection: `UENUM()`
- desc: Defines the compile event types for translation/compilation.
- L43 _public enumerator_ `Log = 0`
- L44 _public enumerator_ `Display = 1`
- L45 _public enumerator_ `Warning = 2`
- L46 _public enumerator_ `Error = 3`

#### enum `FNiagaraCompileEventSource`  
`enum class FNiagaraCompileEventSource : uint8`  
_L50-54_
- reflection: `UENUM()`
- L52 _public enumerator_ `Unset = 0` — No specific source of compile event.
- L53 _public enumerator_ `ScriptDependency = 1` — Compile event is from a dependency to other scripts.

#### struct `FNiagaraCompileEvent`  
`struct FNiagaraCompileEvent`  
_L58-117_
- reflection: `USTRUCT()`
- desc: Records necessary information to give UI cues for errors/logs/warnings during compile.
- L62 _public function_ `FNiagaraCompileEvent()`
- L73 _public function_ `FNiagaraCompileEvent( FNiagaraCompileEventSeverity InSeverity, const FString& InMessage, FString InShortDescription = FString(), FGuid InNodeGuid = FGuid(), FGuid InPinGuid = FGuid(), const TArray<FGuid>& InCallstackGuids = TArray<FGuid>(), FNiagaraCompileEventSource InSource = FNiagaraCompileEventSource::Unset ) : Severity(InSeverity) , Message(InMessage) , ShortDescription(InShortDescription) , NodeGuid(InNodeGuid) , PinGuid(InPinGuid) , StackGuids(InCallstackGuids) , Source(InSource)`
- L93 _public member_ `FNiagaraCompileEventSeverity Severity;` — `UPROPERTY()` — Whether or not this is an error, warning, or info
- L96 _public member_ `FString Message;` — `UPROPERTY()` — The message itself
- L99 _public member_ `FString ShortDescription;` — `UPROPERTY()` — A short, optional description of the event.
- L102 _public member_ `FGuid NodeGuid;` — `UPROPERTY()` — The node guid that generated the compile event
- L105 _public member_ `FGuid PinGuid;` — `UPROPERTY()` — The pin persistent id that generated the compile event
- L108 _public member_ `TArray<FGuid> StackGuids;` — `UPROPERTY()` — The compile stack frame of node id's
- L111 _public member_ `FNiagaraCompileEventSource Source;` — `UPROPERTY()` — The source of the compile event for partial invalidation purposes.
- L113 _public function_ `bool operator==(const FNiagaraCompileEvent& Other) const`

#### class `FNiagaraShaderMapPointerTable`  
`class FNiagaraShaderMapPointerTable : public FShaderMapPointerTable`  
_L120-132_
- inherits: `FShaderMapPointerTable`
- L123 _public typedef_ `using Super = FShaderMapPointerTable;`
- L125 _public prototype_ `virtual int32 AddIndexedPointer(const FTypeLayoutDesc& TypeDesc, void* Ptr) override;`
- L126 _public prototype_ `virtual void* GetIndexedPointer(const FTypeLayoutDesc& TypeDesc, uint32 i) const override;`
- L128 _public prototype_ `virtual void SaveToArchive(FArchive& Ar, const FPlatformTypeLayoutParameters& LayoutParams, const void* FrozenObject) const override;`
- L129 _public prototype_ `virtual bool LoadFromArchive(FArchive& Ar, const FPlatformTypeLayoutParameters& LayoutParams, void* FrozenObject) override;`
- L131 _public member_ `TPtrTable<UNiagaraDataInterfaceBase> DITypes;`

#### struct `FNiagaraDataInterfaceGeneratedFunction`  
`struct FNiagaraDataInterfaceGeneratedFunction`  
_L142-202_
- reflection: `USTRUCT()`
- desc: Information about a data interface function generated by the translator.
- L147 _public member_ `FName DefinitionName;` — Name of the function as defined by the data interface.
- L150 _public member_ `FString InstanceName;` — Name of the instance. Derived from the definition name but made unique for this DI instance and specifier values.
- L153 _public typedef_ `using FunctionSpecifier = TTuple<FName, FName>;` — Specifier values for this instance.
- L154 _public member_ `TArray<FunctionSpecifier> Specifiers;`
- L156 _public member_ `uint16 MiscUsageBitMask = 0;`
- L159 _public member_ `TArray<FNiagaraVariableCommonReference> VariadicInputs;` — `UPROPERTY()`
- L161 _public member_ `TArray<FNiagaraVariableCommonReference> VariadicOutputs;` — `UPROPERTY()`
- L163 _public function_ `const FName* FindSpecifierValue(const FName& Name) const`
- L175 _public prototype_ `bool Serialize(FArchive& Ar);`
- L178 _public function_ `bool operator==(const FNiagaraDataInterfaceGeneratedFunction& Other) const`
- L198 _public function_ `bool operator!=(const FNiagaraDataInterfaceGeneratedFunction& Other) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNiagaraDataInterfaceGeneratedFunction> : public TStructOpsTypeTraitsBase2<FNiagaraDataInterfaceGeneratedFunction>`  
_L204-210_
- inherits: `TStructOpsTypeTraitsBase2<FNiagaraDataInterfaceGeneratedFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L207-209_

#### struct `FNiagaraDataInterfaceGPUParamInfo`  
`struct FNiagaraDataInterfaceGPUParamInfo`  
_L216-246_
- reflection: `USTRUCT()`
- desc: Data coming from that translator that describes parameters needed for each data interface.
- L222 _public member_ `FString DataInterfaceHLSLSymbol;` — `UPROPERTY()` — Symbol of this DI in the hlsl. Used for binding parameters.
- L226 _public member_ `FString DIClassName;` — `UPROPERTY()` — Name of the class for this data interface. Used for constructing the correct parameters struct.
- L230 _public member_ `uint32 ShaderParametersOffset = INDEX_NONE;` — `UPROPERTY()` — The offset for any shader parameters, when this member is INDEX_NONE we are in legacy mode for the data interface.
- L234 _public member_ `TArray<FNiagaraDataInterfaceGeneratedFunction> GeneratedFunctions;` — `UPROPERTY()` — Information about all the functions generated by the translator for this data interface.
- L240 _public prototype_ `bool IsExternalParameter() const;` — Check to see if this is an external parameter or not. An external parameter is defined as one that is not contained within the Niagara system, i.e. a user or parameter collection parameter.
- L243 _public prototype_ `bool IsUserParameter() const;` — `UE_DEPRECATED(5.7, "Please use IsExternalParameter as IsUserParameter does not cover NPCs and can result in incorrect behavior")`
- L245 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNiagaraDataInterfaceGPUParamInfo> : public TStructOpsTypeTraitsBase2<FNiagaraDataInterfaceGPUParamInfo>`  
_L248-254_
- inherits: `TStructOpsTypeTraitsBase2<FNiagaraDataInterfaceGPUParamInfo>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L251-253_

#### struct `FNiagaraShaderScriptExternalConstant`  
`struct FNiagaraShaderScriptExternalConstant`  
_L257-266_
- reflection: `USTRUCT()`
- L262 _public member_ `FName Type;` — `UPROPERTY()`
- L265 _public member_ `FString Name;` — `UPROPERTY()`

#### struct `FNiagaraDataInterfaceStructIncludeInfo`  
`struct FNiagaraDataInterfaceStructIncludeInfo`  
_L269-273_
- desc: Shader side information about global structures includes.
- L271 _public member_ `const FShaderParametersMetadata* StructMetadata = nullptr;`
- L272 _public member_ `int32 ParamterOffset = 0;`

#### struct `FNiagaraShaderScriptParametersMetadata`  
`struct FNiagaraShaderScriptParametersMetadata`  
_L278-291_
- reflection: `USTRUCT()`
- desc: Data provided from the translator to track information requires to bind data interface or parameters at runtime.
- L283 _public member_ `TArray<FNiagaraDataInterfaceGPUParamInfo> DataInterfaceParamInfo;` — `UPROPERTY()`
- L286 _public member_ `TArray<FString> LooseMetadataNames;` — `UPROPERTY()`
- L289 _public member_ `TArray<FNiagaraDataInterfaceStructIncludeInfo> StructIncludeInfos;` — Runtime generated bindings, not serialized
- L290 _public member_ `TSharedPtr<FShaderParametersMetadata> ShaderParametersMetadata;`

#### struct `FNiagaraDataInterfaceParamRef`  
`struct FNiagaraDataInterfaceParamRef`  
_L297-312_
- desc: Shader side data needed for binding data interface parameters.
- L301 _public function_ `FNiagaraDataInterfaceParamRef()`
- L302 _public function_ `~FNiagaraDataInterfaceParamRef()`
- L310 _public prototype_ `void WriteFrozenParameters(FMemoryImageWriter& Writer, const TMemoryImagePtr<FNiagaraDataInterfaceParametersCS>& InParameters) const;` — Pointer to parameters struct for this data interface.
- L311 _public prototype_ `LAYOUT_FIELD_WITH_WRITER(TMemoryImagePtr<FNiagaraDataInterfaceParametersCS>, Parameters, WriteFrozenParameters);`

#### class `FNiagaraShaderMapId`  
`class FNiagaraShaderMapId`  
_L315-396_
- desc: Contains all the information needed to uniquely identify a FNiagaraShaderMapID.
- L352 _public function_ `FNiagaraShaderMapId() : CompilerVersionID() , FeatureLevel(GMaxRHIFeatureLevel)`
- L357 _public prototype_ `~FNiagaraShaderMapId() = default;`
- L368 _public function_ `SIZE_T GetSizeBytes() const`
- L374 _public prototype_ `uint64 GetScriptHash() const;` — Hashes the script-specific part of this shader map Id.
- L382 _public prototype_ `bool operator==(const FNiagaraShaderMapId& ReferenceSet) const;` — Tests this set against another for equality, disregarding override settings. @param ReferenceSet	The set to compare against @return				true if the sets are equal
- L384 _public function_ `bool operator!=(const FNiagaraShaderMapId& ReferenceSet) const`
- L391 _public prototype_ `void AppendKeyString(FString& KeyString) const;` — Appends string representations of this Id to a key string.

#### class `FNiagaraCompilationQueue`  
`class FNiagaraCompilationQueue`  
_L407-460_
- L419 _public function_ `static FNiagaraCompilationQueue *Get()`
- L428 _public function_ `TArray<NiagaraCompilationQueueItem> &GetQueue()`
- L433 _public function_ `void Queue(FNiagaraShaderScript *InScript, FNiagaraShaderMapRef InShaderMap, const FNiagaraShaderMapId &MapId, EShaderPlatform InPlatform, bool InApply)`
- L445 _public function_ `void RemovePending(FNiagaraShaderScript* InScript)`
- L458 _private member_ `TArray<NiagaraCompilationQueueItem> CompilationQueue;`
- L459 _private member_ `static FNiagaraCompilationQueue *Singleton;`

#### struct `FNiagaraCompilationQueue::NiagaraCompilationQueueItem`  
`struct NiagaraCompilationQueueItem`  
_L410-417_
- L412 _public member_ `FNiagaraShaderScript* Script;`
- L413 _public member_ `FNiagaraShaderMapRef ShaderMap;`
- L414 _public member_ `FNiagaraShaderMapId ShaderMapId;`
- L415 _public member_ `EShaderPlatform Platform;`
- L416 _public member_ `bool bApply;`

#### class `FNiagaraShaderMapContent`  
`class FNiagaraShaderMapContent : public FShaderMapContent`  
_L464-474_
- inherits: `FShaderMapContent`
- L466 _private typedef_ `using Super = FShaderMapContent;`
- L470 _private function_ `explicit FNiagaraShaderMapContent(const EShaderPlatform InPlatform) : Super(InPlatform)`

#### class `FNiagaraShaderMap`  
`class FNiagaraShaderMap : public TShaderMap<FNiagaraShaderMapContent, FNiagaraShaderMapPointerTable>, public FDeferredCleanupInterface`  
_L479-675_
- inherits: `TShaderMap<FNiagaraShaderMapContent,FNiagaraShaderMapPointerTable>,FDeferredCleanupInterface`
- desc: The set of shaders for a single script.
- L482 _public typedef_ `using Super = TShaderMap<FNiagaraShaderMapContent, FNiagaraShaderMapPointerTable>;`
- L491 _public prototype_ `static FNiagaraShaderMap* FindId(const FNiagaraShaderMapId& ShaderMapId, EShaderPlatform Platform);` — Finds the shader map for a script. @param Platform - The platform to lookup for @return NULL if no cached shader map was found.
- L494 _public function_ `template<typename ShaderType> TNiagaraShaderRef<ShaderType> GetShader(int32 PermutationId) const` — ShaderMap interface
- L504 _public prototype_ `static void LoadFromDerivedDataCache(const FNiagaraShaderScript* Script, const FNiagaraShaderMapId& ShaderMapId, EShaderPlatform Platform, FNiagaraShaderMapRef& InOutShaderMap);` — Attempts to load the shader map for the given script from the Derived Data Cache. If InOutShaderMap is valid, attempts to load the individual missing shaders instead.
- L507 _public prototype_ `FNiagaraShaderMap();`
- L509 _public prototype_ `FNiagaraShaderMap(EWorkerThread);`
- L513 _public prototype_ `~FNiagaraShaderMap();` — Destructor.
- L522 _public prototype_ `void Compile( FNiagaraShaderScript* Script, const FNiagaraShaderMapId& ShaderMapId, TRefCountPtr<FSharedShaderCompilerEnvironment> CompilationEnvironment, EShaderPlatform Platform, bool bSynchronousCompile, bool bApplyCompletedShaderMapForRendering );` — Compiles the shaders for a script and caches them in this shader map. @param script - The script to compile shaders for. @param ShaderMapId - the set of static parameters to compile for @param Platform - The platform to compile to
- L537 _public prototype_ `void CreateCompileJobs( const FNiagaraShaderType* ShaderType, FStringView FriendlyName, const FNiagaraShaderMapId& ShaderMapId, FStringView SourceSource, TRefCountPtr<FSharedShaderCompilerEnvironment> CompilationEnvironment, TConstArrayView<FSimulationStageMetaData> StageMetaData, int32 PermutationCount, EShaderPlatform Platform, TSharedPtr<FNiagaraShaderScriptParametersMetadata> ShaderParameters, TArray<TRefCountPtr<FShaderCommonCompileJob>>& CompileJobs);` — Compiles the shaders for a script and caches them in this shader map. @param script - The script to compile shaders for. @param ShaderMapId - the set of static parameters to compile for @param Platform - The platform to compile to
- L549 _public prototype_ `void ProcessAndFinalizeShaderCompileJob(const TRefCountPtr<FShaderCommonCompileJob>& SingleJob);`
- L552 _public prototype_ `bool ProcessCompilationResults(const TArray<FNiagaraShaderScript*>& InScripts, const TArray<TRefCountPtr<class FShaderCommonCompileJob>>& InCompilationResults, int32& ResultIndex, float& TimeBudget);` — Sorts the incoming compiled jobs into the appropriate mesh shader maps, and finalizes this shader map so that it can be used for rendering.
- L559 _public prototype_ `bool IsComplete(const FNiagaraShaderScript* Script, bool bSilent);` — Checks whether the shader map is missing any shader types necessary for the given script. @param Script - The Niagara Script which is checked. @return True if the shader map has all of the shader types necessary.
- L567 _public prototype_ `bool TryToAddToExistingCompilationTask(FNiagaraShaderScript* Script);` — Checks to see if the shader map is already being compiled for another script, and if so adds the specified script to the list to be applied to once the compile finishes. @param Script - The Niagara Script we also wish to apply the compiled shader map to. @return True if the shader map was being compiled and we added Script to the list to be applied.
- L571 _public prototype_ `void GetShaderList(TMap<FShaderId, TShaderRef<FShader>>& OutShaders) const;` — Builds a list of the shaders in a shader map.
- L572 _public prototype_ `virtual void GetShaderList(TMap<FHashedName, TShaderRef<FShader>>& OutShaders) const override;`
- L573 _public prototype_ `virtual void GetShaderPipelineList(TArray<FShaderPipelineRef>& OutShaderPipelines) const override;`
- L576 _public prototype_ `void Register(EShaderPlatform InShaderPlatform);` — Registers a niagara shader map in the global map so it can be used by Niagara scripts.
- L579 _public prototype_ `void AddRef();` — Reference counting.
- L580 _public prototype_ `void Release();`
- L586 _public prototype_ `static bool RemovePendingScript(FNiagaraShaderScript* Script);` — Removes a Script from NiagaraShaderMapsBeingCompiled. @return true if something was actually removed.
- L587 _public prototype_ `static void RemovePendingMap(FNiagaraShaderMap* Map);`
- L590 _public prototype_ `static const FNiagaraShaderMap* GetShaderMapBeingCompiled(const FNiagaraShaderScript* Script);` — Finds a shader map currently being compiled that was enqueued for the given script.
- L595 _public prototype_ `bool Serialize(FArchive& Ar, bool bInlineShaderResources = true, bool bLoadingCooked = false);` — `UE_DEPRECATED(5.5, "Use overload taking a FShaderSerializeContext")` — Serializes the shader map.
- L597 _public prototype_ `bool Serialize(FShaderSerializeContext& Ctx);`
- L601 _public prototype_ `void SaveToDerivedDataCache(const FNiagaraShaderScript* Script);` — Saves this shader map to the derived data cache.
- L605 _public function_ `const FNiagaraShaderMapId& GetShaderMapId() const` — Accessors.
- L606 _public function_ `EShaderPlatform GetShaderPlatform() const`
- L607 _public function_ `uint32 GetCompilingId() const`
- L608 _public function_ `bool IsCompilationFinalized() const`
- L609 _public function_ `bool CompiledSuccessfully() const`
- L611 _public function_ `bool IsValid() const`
- L618 _public function_ `int32 GetNumRefs() const`
- L619 _public function_ `uint32 GetCompilingId()`
- L622 _public function_ `static TMap<FNiagaraShaderMapRef, TArray<FNiagaraShaderScript*>>& GetInFlightShaderMaps()`
- L629 _public function_ `void SetCompiledSuccessfully(bool bSuccess)`
- L639 _private member_ `static TMap<FNiagaraShaderMapId, FNiagaraShaderMap*> GIdToNiagaraShaderMap[SP_NumPlatforms];` — A global map from a script's ID and static switch set to any shader map cached for that script. Note: this does not necessarily contain all script shader maps in memory.  Shader maps with the same key can evict each other. No ref counting needed as these are removed on destruction of the shader map.
- L643 _private member_ `static TMap<FNiagaraShaderMapRef, TArray<FNiagaraShaderScript*> > NiagaraShaderMapsBeingCompiled;` — Tracks resources and their shader maps that need to be compiled but whose compilation is being deferred.
- L647 _private member_ `uint32 CompilingId;` — Uniquely identifies this shader map during compilation, needed for deferred compilation where shaders from multiple shader maps are compiled together.
- L649 _private member_ `mutable int32 NumRefs;`
- L652 _private member_ `bool bDeletedThroughDeferredCleanup;` — Used to catch errors where the shader map is deleted directly.
- L655 _private member_ `uint32 bRegistered : 1;` — Indicates whether this shader map has been registered in GIdToNiagaraShaderMap
- L661 _private member_ `uint32 bCompilationFinalized : 1;` — Indicates whether this shader map has had ProcessCompilationResults called after Compile. The shader map must not be used on the rendering thread unless bCompilationFinalized is true.
- L663 _private member_ `uint32 bCompiledSuccessfully : 1;`
- L666 _private member_ `uint32 bIsPersistent : 1;` — Indicates whether the shader map should be stored in the shader cache.
- L669 _private prototype_ `FShader* ProcessCompilationResultsForSingleJob(const TRefCountPtr<class FShaderCommonCompileJob>& SingleJob, uint64 ShaderMapHash);`
- L671 _private prototype_ `bool IsNiagaraShaderComplete(const FNiagaraShaderScript* Script, const FNiagaraShaderType* ShaderType, bool bSilent);`

#### enum `FNiagaraShaderMap::EWorkerThread`  
`enum EWorkerThread`  
_L484-484_
- L484 _public enumerator_ `enum EWorkerThread { WorkerThread }; /** * Finds the shader map for a script. * @param Platform - The platform to lookup for * @return NULL if no cached shader map was found. */ static FNiagaraShaderMap* FindId(const FNiagaraShaderMapId& ShaderMapId, EShaderPlatform Platform);`

#### class `FNiagaraShaderScript`  
`class FNiagaraShaderScript`  
_L682-1005_
- desc: FNiagaraShaderScript represents a Niagara script to the shader compilation process
- L705 _public prototype_ `FNiagaraShaderScript();` — Minimal initialization constructor.
- L710 _public prototype_ `virtual ~FNiagaraShaderScript();` — Destructor
- L715 _public prototype_ `bool CacheShaders(bool bApplyCompletedShaderMapForRendering, bool bForceRecompile, bool bSynchronous = false, const ITargetPlatform* TargetPlatform = nullptr);` — Caches the shaders for this script with no static parameters on the given platform.
- L716 _public prototype_ `bool CacheShaders(const FNiagaraShaderMapId& ShaderMapId, bool bApplyCompletedShaderMapForRendering, bool bForceRecompile, bool bSynchronous = false);`
- L718 _public prototype_ `bool GetUsesCompressedAttributes() const;`
- L730 _public prototype_ `virtual bool ShouldCache(EShaderPlatform Platform, const FShaderType* ShaderType) const;` — Should the shader for this script with the given platform, shader type and vertex factory type combination be compiled @param Platform		The platform currently being compiled for @param ShaderType	Which shader is being compiled @param VertexFactory	Which vertex factory is being compiled (can be NULL) @return true if the shader should be compiled
- L736 _public prototype_ `virtual void ModifyCompilationEnvironment(EShaderPlatform Platform, struct FShaderCompilerEnvironment& OutEnvironment) const;` — Allow Niagara script the opportunity to modify the compilation environment for GPU simulations. Generally used for data interfaces to inject project defines.
- L739 _public prototype_ `void SerializeShaderMap(FArchive& Ar);` — Serializes the script.
- L742 _public prototype_ `void ReleaseShaderMap();` — Releases this script's shader map.  Must only be called on scripts not exposed to the rendering thread!
- L745 _public prototype_ `void GetDependentShaderTypes(EShaderPlatform Platform, TArray<FShaderType*>& OutShaderTypes) const;`
- L747 _public prototype_ `virtual void GetShaderMapId(EShaderPlatform Platform, const ITargetPlatform* TargetPlatform, FNiagaraShaderMapId& OutId) const;`
- L750 _public prototype_ `void Invalidate();`
- L755 _public function_ `virtual bool IsPersistent() const` — Should shaders compiled for this script be saved to disk?
- L761 _public prototype_ `virtual void NotifyCompilationFinished();` — Called when compilation finishes, after the GameThreadShaderMap is set and the render command to set the RenderThreadShaderMap is queued
- L766 _public prototype_ `void CancelCompilation();` — Cancels all outstanding compilation jobs
- L771 _public prototype_ `void FinishCompilation();` — Blocks until compilation has completed. Returns immediately if a compilation is not outstanding.
- L779 _public prototype_ `bool IsCompilationFinished() const;` — Checks if the compilation for this shader is finished @return returns true if compilation is complete false otherwise
- L783 _public function_ `const TArray<FString>& GetCompileErrors() const` — Accessors.
- L784 _public function_ `void SetCompileErrors(const TArray<FString>& InCompileErrors)`
- L787 _public function_ `ERHIFeatureLevel::Type GetFeatureLevel() const`
- L788 _public function_ `EShaderPlatform GetShaderPlatform() const`
- L790 _public function_ `class FNiagaraShaderMap* GetGameThreadShaderMap() const`
- L797 _public function_ `void SetGameThreadShaderMap(FNiagaraShaderMap* InShaderMap)` — Note: SetRenderingThreadShaderMap must also be called with the same value, but from the rendering thread.
- L808 _public prototype_ `void SetRenderingThreadShaderMap(FNiagaraShaderMap* InShaderMap);` — Note: SetGameThreadShaderMap must also be called with the same value, but from the game thread.
- L809 _public prototype_ `void SetRenderThreadCachedData(const FNiagaraShaderMapCachedData& CachedData);`
- L811 _public prototype_ `bool QueueForRelease(FThreadSafeBool& Fence);`
- L814 _public function_ `void AddCompileId(uint32 Id)`
- L821 _public function_ `void SetShaderMap(FNiagaraShaderMap* InShaderMap)`
- L834 _public prototype_ `void RemoveOutstandingCompileId(const int32 OldOutstandingCompileShaderMapId);`
- L837 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector);`
- L846 _public function_ `bool GetScriptHLSLSource(FString& OutSource) const` — Get user source code for the shader @param OutSource - generated source code @param OutHighlightMap - source code highlight list @return - true on Success
- L852 _public function_ `void SetHlslOutput(const FString& InHlslOutput)`
- L853 _public function_ `void SetSourceName(FString InSourceName)`
- L856 _public prototype_ `void SaveShaderStableKeys(EShaderPlatform TargetShaderPlatform, struct FStableShaderKeyAndValue& SaveKeyVal);` — Save "stable" shader for identifying the shader in the recorded PSO cache.
- L859 _public function_ `const FString& GetFriendlyName() const`
- L861 _public prototype_ `void SetScript(UNiagaraScriptBase* InScript, ERHIFeatureLevel::Type InFeatureLevel, EShaderPlatform InShaderPlatform, const FGuid& InCompilerVersion, const TArray<FString>& InAdditionalDefines, const TArray<FString>& InAdditionalVariables, const FNiagaraCompileHash& InBaseCompileHash, const TArray<FNiagaraCompileHash>& InReferencedCompileHashes, bool bInUsesRapidIterationParams, FString InFriendlyName);`
- L866 _public prototype_ `bool MatchesScript(ERHIFeatureLevel::Type InFeatureLevel, EShaderPlatform InShaderPlatform, const FNiagaraVMExecutableDataId& ScriptId) const;`
- L869 _public function_ `UNiagaraScriptBase* GetBaseVMScript()`
- L870 _public function_ `const UNiagaraScriptBase* GetBaseVMScript() const`
- L872 _public prototype_ `FName GetOwnerFName() const;` — Returns owner name for tracking
- L874 _public prototype_ `FNiagaraShaderRef GetShader(int32 PermutationId) const;`
- L875 _public prototype_ `FNiagaraShaderRef GetShaderGameThread(int32 PermutationId) const;`
- L877 _public prototype_ `void BuildScriptParametersMetadata(const FNiagaraShaderScriptParametersMetadata& ScriptParametersMetadata);`
- L878 _public function_ `TSharedRef<FNiagaraShaderScriptParametersMetadata> GetScriptParametersMetadata() const`
- L879 _public function_ `const FNiagaraShaderScriptParametersMetadata& GetScriptParametersMetadata_RT() const`
- L881 _public function_ `FOnNiagaraScriptCompilationComplete& OnCompilationComplete()`
- L886 _public prototype_ `bool IsSame(const FNiagaraShaderMapId& InId) const;`
- L888 _public function_ `int32 GetNumPermutations() const`
- L890 _public prototype_ `bool IsShaderMapComplete() const;`
- L892 _public function_ `inline bool IsShaderMapComplete_RenderThread() const`
- L893 _public function_ `inline int32 GetNumPermutations_RenderThread() const`
- L894 _public function_ `inline bool IsExternalConstantBufferUsed_RenderThread(int32 Index) const`
- L895 _public function_ `inline bool IsViewUniformBufferUsed_RenderThread() const`
- L897 _public function_ `FNiagaraCompileHash GetBaseCompileHash()const`
- L904 _protected prototype_ `void GetShaderMapIDsWithUnfinishedCompilation(TArray<int32>& ShaderMapIds);` — Fills the passed array with IDs of shader maps unfinished compilation jobs.
- L907 _protected function_ `void SetFeatureLevel(ERHIFeatureLevel::Type InFeatureLevel)`
- L912 _protected prototype_ `void UpdateCachedData_All();`
- L913 _protected prototype_ `void UpdateCachedData_PreCompile();`
- L914 _protected prototype_ `void UpdateCachedData_PostCompile(bool bCalledFromSerialize = false);`
- L917 _private member_ `UNiagaraScriptBase* BaseVMScript;`
- L920 _private member_ `FString SourceName;`
- L921 _private member_ `FString HlslOutput;`
- L922 _private member_ `TArray<FString> CompileErrors;`
- L931 _private member_ `FNiagaraShaderMapRef GameThreadShaderMap;` — Game thread tracked shader map, which is ref counted and manages shader map lifetime. The shader map uses deferred deletion so that the rendering thread has a chance to process a release command when the shader map is no longer referenced. Code that sets this is responsible for updating RenderingThreadShaderMap in a thread safe way. During an async compile, this will be NULL and will not contain the actual shader map until compilation is complete.
- L937 _private member_ `FNiagaraShaderMap* RenderingThreadShaderMap;` — Shader map for this FNiagaraShaderScript which is accessible by the rendering thread. This must be updated along with GameThreadShaderMap, but on the rendering thread.
- L939 _private member_ `TSharedPtr<FNiagaraShaderScriptParametersMetadata> ScriptParametersMetadata;`
- L940 _private member_ `TSharedPtr<FNiagaraShaderScriptParametersMetadata> ScriptParametersMetadata_RT;`
- L943 _private member_ `TArray<FString> AdditionalDefines;` — Configuration options
- L946 _private member_ `TArray<FString> AdditionalVariables;` — Additional variables needed
- L949 _private member_ `bool bUsesRapidIterationParams = true;` — Whether or not we need to bake Rapid Iteration params. True to keep params, false to bake.
- L952 _private member_ `FNiagaraCompileHash BaseCompileHash;` — Compile hash for the base script.
- L955 _private member_ `FGuid CompilerVersionId;` — The compiler version the script was generated with.
- L958 _private member_ `TArray<FNiagaraCompileHash> ReferencedCompileHashes;` — The compile hashes for the top level scripts referenced by the script.
- L965 _private member_ `TArray<int32, TInlineAllocator<1> > OutstandingCompileShaderMapIds;` — Contains the compiling id of this shader map when it is being compiled asynchronously. This can be used to access the shader map during async compiling, since GameThreadShaderMap will not have been set yet.
- L969 _private member_ `ERHIFeatureLevel::Type FeatureLevel;` — Feature level and shader platform that this script is representing.
- L970 _private member_ `EShaderPlatform ShaderPlatform;`
- L972 _private member_ `uint32 bLoadedCookedShaderMapId : 1;`
- L973 _private member_ `uint32 bLoadedFromCookedMaterial : 1;`
- L974 _private member_ `uint32 bQueuedForRelease : 1;`
- L976 _private member_ `int32 NumPermutations = 0;`
- L978 _private member_ `FNiagaraShaderMapCachedData CachedData_RenderThread;`
- L980 _private member_ `FNiagaraShaderMapId CookedShaderMapId;`
- L982 _private member_ `FOnNiagaraScriptCompilationComplete OnCompilationCompleteDelegate;`
- L988 _private prototype_ `bool BeginCompileShaderMap( const FNiagaraShaderMapId& ShaderMapId, TRefCountPtr<class FNiagaraShaderMap>& OutShaderMap, bool bApplyCompletedShaderMapForRendering, bool bSynchronous = false);` — Compiles this script for Platform, storing the result in OutShaderMap if the compile was synchronous
- L995 _private prototype_ `void SetupShaderCompilationEnvironment( EShaderPlatform Platform, FShaderCompilerEnvironment& OutEnvironment ) const;` — Populates OutEnvironment with defines needed to compile shaders for this script.
- L1001 _private member_ `FString FriendlyName;`

#### struct `FNiagaraShaderScript::FNiagaraShaderMapCachedData`  
`struct FNiagaraShaderMapCachedData`  
_L684-698_
- L686 _public function_ `FNiagaraShaderMapCachedData()`
- L694 _public member_ `int32 NumPermutations;`
- L695 _public member_ `uint32 bIsComplete : 1;`
- L696 _public member_ `uint32 bExternalConstantBufferUsed : 2;`
- L697 _public member_ `uint32 bViewUniformBufferUsed : 1;`

#### Free symbols / members of external scopes

- L135 _typedef_ `template<typename ShaderType> using TNiagaraShaderRef = TShaderRefBase<ShaderType, FNiagaraShaderMapPointerTable>;`
- L136 _typedef_ `using FNiagaraShaderRef = TNiagaraShaderRef<FNiagaraShader>;`
- L208 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonfe9f421d0103`)
- L252 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonfe9f421d0203`)
- L363 _function_ `friend uint32 GetTypeHash(const FNiagaraShaderMapId& Ref)`
- L677 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNiagaraScriptCompilationComplete);`
- L677 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNiagaraScriptCompilationComplete);`
- L1008 _externvar_ `extern int32 GNiagaraTranslatorFailIfNotSetSeverity;` — CVars
- L1009 _externvar_ `extern int32 GbNiagaraEnableTraversalCache;`
- L1011 _namespace_ `namespace FNiagaraCVarUtilities`
- L1013 _prototype_ `FNiagaraCompileEventSeverity GetCompileEventSeverityForFailIfNotSet();` (scope `FNiagaraCVarUtilities`)
- L1014 _prototype_ `bool GetShouldEmitMessagesForFailIfNotSet();` (scope `FNiagaraCVarUtilities`)
