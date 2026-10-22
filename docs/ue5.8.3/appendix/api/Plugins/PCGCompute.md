# Plugins / PCGCompute

- module root: `Plugins/PCG/Source/PCGCompute`
- headers: 10; symbols: 83
- symbol kinds: class=4, delegate=1, enum=2, enumerator=7, function=2, macro=1, member=34, namespace=6, prototype=19, struct=5, variable=2
- PrivateDependencyModuleNames: Engine
- PublicDependencyModuleNames: Core, CoreUObject, Projects, RHI, RenderCore, Renderer

### `Plugins/PCG/Source/PCGCompute/Internal/PCGDilate.h` (Internal)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PCGDilate`
- L12 _prototype_ `bool AddDilatePass(FRDGBuilder& GraphBuilder, FRDGTextureRef OutputTexture, int32 Iterations);` (scope `PCGDilate`) — Grows valid data (alpha == 1) outward by one texel per iteration into uncovered neighbors.

### `Plugins/PCG/Source/PCGCompute/Internal/PCGGrassMapUnpackerCS.h` (Internal)


#### class `FPCGGrassMapUnpackerCS`  
`class FPCGGrassMapUnpackerCS : public FGlobalShader`  
_L11-42_
- inherits: `FGlobalShader`
- desc: Compute shader for unpacking grass map textures rendered by FLandscapeGrassWeightExporter. Note: This class is subject to change without deprecation.
- L14 _public member_ `static constexpr uint32 ThreadGroupDim = 8;`
- L15 _public member_ `static constexpr uint32 MaxNumLandscapeComponents = 64;`
- L19 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FPCGGrassMapUnpackerCS, FGlobalShader);`
- L41 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

### `Plugins/PCG/Source/PCGCompute/Internal/PCGRayTrace.h` (Internal)


#### struct `FPCGRayTraceParams`  
`struct FPCGRayTraceParams`  
_L20-28_
- L22 _public member_ `const FSceneInterface* Scene = nullptr;`
- L23 _public member_ `const FSceneView* View = nullptr;`
- L24 _public member_ `int32 NumRays = 0;`
- L25 _public member_ `bool bNeedsUVData = false;`
- L26 _public member_ `int32 TexCoordsChannelIndex = 0;`
- L27 _public member_ `FRDGBufferUAVRef PackedDataUAV;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PCGRaytraceConstants`
- L15 _variable_ `constexpr int RAY_CULLED = -1;` (scope `PCGRaytraceConstants`)
- L16 _variable_ `constexpr int RAY_TRACE_PACKED_BUFFER_STRIDE_UINTS = 12;` (scope `PCGRaytraceConstants`)
- L30 _namespace_ `namespace PCGRayTrace`
- L32 _prototype_ `void RenderPCGRayTraceInline(FRDGBuilder& GraphBuilder, const FPCGRayTraceParams& InParams);` (scope `PCGRayTrace`)

### `Plugins/PCG/Source/PCGCompute/Internal/PCGRayTracingUVCacheUtils.h` (Internal)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PCGRayTracingUVCache`
- L12 _prototype_ `void RequestEnable_GameThread(FSceneInterface* SceneInterface);` (scope `PCGRayTracingUVCache`) — Enable the PCG ray tracing UV cache for a given scene. Enqueues a render command that builds the cache from all existing scene primitives. No-op if already enabled or if ray tracing is disabled.

### `Plugins/PCG/Source/PCGCompute/Internal/PCGSceneWriterCS.h` (Internal)


#### class `FPCGSceneWriterCS`  
`class FPCGSceneWriterCS : public FGlobalShader`  
_L12-37_
- inherits: `FGlobalShader`
- desc: [EXPERIMENTAL] Compute shader for writing instance data into GPU Scene. Note: This class is subject to change without deprecation.
- L16 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FPCGSceneWriterCS, FGlobalShader);`
- L34 _public member_ `static constexpr uint32 NumThreadsPerGroup = 64;`
- L36 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

### `Plugins/PCG/Source/PCGCompute/Internal/PCGTextureDownsample.h` (Internal)


#### enum `EPCGTextureDownsampleMode`  
`enum class EPCGTextureDownsampleMode : uint8`  
_L11-17_
- reflection: `UENUM()`
- L13 _public enumerator_ `Average = 0`
- L14 _public enumerator_ `Min = 1`
- L15 _public enumerator_ `Max = 2`
- L16 _public enumerator_ `Sum = 3`

#### struct `PCGTextureDownsample::FParams`  
`struct FParams`  
_L21-28_
- L23 _public member_ `FRDGTextureRef Texture = nullptr;`
- L24 _public member_ `FRHISamplerState* Sampler = nullptr;`
- L25 _public member_ `int SliceIndex = 0;`
- L26 _public member_ `int NumSlices = 1;`
- L27 _public member_ `EPCGTextureDownsampleMode Mode = EPCGTextureDownsampleMode::Average;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace PCGTextureDownsample`
- L30 _prototype_ `void DownsampleTexture(FRDGBuilder& GraphBuilder, FParams& InParams);` (scope `PCGTextureDownsample`)

### `Plugins/PCG/Source/PCGCompute/Internal/PCGUnwrapMesh.h` (Internal)


#### enum `PCGUnwrapMesh::EMeshAttribute`  
`enum class EMeshAttribute : uint8`  
_L15-24_
- desc: Per-texel mesh attribute written by the unwrap pixel shader.
- L18 _public enumerator_ `LocalPosition = 0` — RGB = local-space vertex position interpolated to the texel; alpha = 1 marks "covered".
- L21 _public enumerator_ `Mask = 1` — Coverage mask. Writes 1 on every channel so the mask is readable from any RT format (R8, R16F, RGBA, ...).
- L23 _public enumerator_ `Num`

#### struct `PCGUnwrapMesh::FUnwrapParams`  
`struct FUnwrapParams`  
_L27-41_
- desc: Inputs for a single mesh-to-texture unwrap draw.
- L29 _public member_ `FBufferRHIRef PositionBufferRHI;`
- L30 _public member_ `FBufferRHIRef TexCoordBufferRHI;`
- L31 _public member_ `FBufferRHIRef IndexBufferRHI;`
- L32 _public member_ `uint32 NumVerts = 0;`
- L33 _public member_ `uint32 NumTris = 0;`
- L34 _public member_ `uint32 NumTexCoords = 1;`
- L35 _public member_ `uint32 UVChannelIndex = 0;`
- L36 _public member_ `bool bFullPrecisionUVs = true;`
- L37 _public member_ `EMeshAttribute Attribute = EMeshAttribute::LocalPosition;`
- L38 _public member_ `FIntPoint Resolution = FIntPoint::ZeroValue;`
- L40 _public prototype_ `void InitFromLOD(const FStaticMeshLODResources& LOD);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace PCGUnwrapMesh`
- L44 _prototype_ `bool ValidateParams(const FUnwrapParams& Params);` (scope `PCGUnwrapMesh`) — Check params are valid for rendering and log errors if not.
- L50 _prototype_ `bool AddUnwrapMeshPass(FRDGBuilder& GraphBuilder, FRDGTextureRef OutputTexture, const FUnwrapParams& Params);` (scope `PCGUnwrapMesh`) — Adds an RDG raster pass that draws the input mesh into OutputTexture, with triangles placed in UV space (UV mapped to clip space). The pixel shader writes the selected mesh attribute at every covered texel.

### `Plugins/PCG/Source/PCGCompute/Private/PCGRayTracingUVCache.h` (Private)


#### class `FPCGRayTracingUVCacheExtension`  
`class FPCGRayTracingUVCacheExtension : public ISceneExtension`  
_L14-42_
- inherits: `ISceneExtension`
- desc: Scene extension that caches per-primitive UV SRV pointers for PCG GPU ray tracing. Populated on-demand when the first runtime gen original component registers, then maintained incrementally by the scene updater.
- L25 _public prototype_ `explicit FPCGRayTracingUVCacheExtension(FScene& InScene);`
- L27 _public prototype_ `static bool ShouldCreateExtension(FScene& Scene);`
- L28 _public prototype_ `virtual ISceneExtensionUpdater* CreateUpdater() override;`
- L30 _public function_ `bool IsEnabled() const`
- L31 _public function_ `void SetEnabled(bool bInEnabled)`
- L34 _public member_ `TMap<int32, FCachedEntry> Cache;` — Keyed by FPersistentPrimitiveIndex::Index.
- L35 _public member_ `uint32 MaxPersistentIndex = 0;`
- L41 _private member_ `bool bEnabled = false;` — Set after initial build completes.

#### struct `FPCGRayTracingUVCacheExtension::FCachedEntry`  
`struct FCachedEntry`  
_L19-23_
- L21 _public member_ `FShaderResourceViewRHIRef BufferSRV = nullptr;`
- L22 _public member_ `uint32 NumCoordinates = 0;`

### `Plugins/PCG/Source/PCGCompute/Public/PCGComputeModule.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGCompute, Log, All);` — Logs
- L11 _delegate_ `DECLARE_STATS_GROUP(TEXT("PCGCompute"), STATGROUP_PCGCompute, STATCAT_Advanced) LLM_DECLARE_TAG(PCGCompute);` — Stats
- L13 _prototype_ `LLM_DECLARE_TAG(PCGCompute);`

### `Plugins/PCG/Source/PCGCompute/Public/PCGTextureReadback.h` (Public)


#### struct `FPCGTextureReadbackDispatchParams`  
`struct FPCGTextureReadbackDispatchParams`  
_L12-28_
- desc: Parameters to drive execution of a GPU texture readback. These mirror the fields in the texture readback compute shader (PCGTextureReadback.usf).
- L15 _public member_ `FTextureRHIRef SourceTexture;` — Source texture to sample from. Can be a UTexture2D or UTexture2DArray.
- L18 _public member_ `FSamplerStateRHIRef SourceSampler;` — Sampler used to sample the SourceTexture. Should use an SF_Point filter for precise per-pixel readback.
- L21 _public member_ `FIntPoint SourceDimensions;` — Width and Height of the SourceTexture. Should match the underlying dimensions exactly for precise per-pixel readback.
- L24 _public member_ `uint32 SourceTextureIndex = 0;` — Optional texture index. Should be 0 if the SourceTexture is not a texture array.
- L27 _public member_ `EPixelFormat OutputFormat = PF_B8G8R8A8;` — Pixel format for the staging texture used during readback. Must be a 4-channel uncompressed format (e.g. PF_B8G8R8A8, PF_FloatRGBA, PF_A32B32G32R32F).

#### class `FPCGTextureReadbackInterface`  
`class FPCGTextureReadbackInterface`  
_L33-41_
- desc: API for dispatching TextureReadback operations to the GPU.
- L36 _public prototype_ `static void Dispatch_RenderThread(FRHICommandListImmediate& RHICmdList, const FPCGTextureReadbackDispatchParams& Params, const TFunction<void(void* OutBuffer, int32 ReadbackWidth, int32 ReadbackHeight)>& AsyncCallback);`
- L37 _public prototype_ `static void Dispatch_GameThread(const FPCGTextureReadbackDispatchParams& Params, const TFunction<void(void* OutBuffer, int32 ReadbackWidth, int32 ReadbackHeight)>& AsyncCallback);`
- L40 _public prototype_ `static void Dispatch(const FPCGTextureReadbackDispatchParams& Params, const TFunction<void(void* OutBuffer, int32 ReadbackWidth, int32 ReadbackHeight)>& AsyncCallback);` — Dispatches the texture readback compute shader. Can be called from any thread.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PCGCOMPUTE_API`
