# Plugins / NiagaraVertexFactories

- module root: `Plugins/FX/Niagara/Source/NiagaraVertexFactories`
- headers: 11; symbols: 178
- symbol kinds: class=15, enum=2, enumerator=8, externvar=4, function=47, macro=8, member=32, prototype=48, struct=4, typedef=10
- PrivateDependencyModuleNames: Core, Engine, RHI, RenderCore, Renderer
- PublicDependencyModuleNames: VectorVM
- PublicIncludePathModuleNames: Niagara, NiagaraCore

### `Plugins/FX/Niagara/Source/NiagaraVertexFactories/Internal/NiagaraVertexFactoryExport.h` (Internal)


#### class `FNiagaraVertexFactoryExportCS`  
`class FNiagaraVertexFactoryExportCS : public FMeshMaterialShader`  
_L11-72_
- inherits: `FMeshMaterialShader`
- L16 _public member_ `static constexpr uint32 ThreadGroupSize = 64;`
- L18 _public prototype_ `FNiagaraVertexFactoryExportCS(const FMeshMaterialShaderType::CompiledShaderInitializerType& Initializer);`
- L19 _public prototype_ `FNiagaraVertexFactoryExportCS() = default;`
- L21 _public prototype_ `static bool IsEnabled();`
- L22 _public prototype_ `static bool SupportsVertexFactoryType(const FVertexFactoryType* VertexFactory);`
- L24 _public prototype_ `static bool ShouldCompilePermutation(const FMeshMaterialShaderPermutationParameters& Parameters);`
- L25 _public prototype_ `static void ModifyCompilationEnvironment(const FMaterialShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L27 _public function_ `void GetShaderBindings( const FScene* Scene, ERHIFeatureLevel::Type FeatureLevel, const FPrimitiveSceneProxy* PrimitiveSceneProxy, const FMaterialRenderProxy& MaterialRenderProxy, const FMaterial& Material, const FMeshMaterialShaderElementData& ShaderElementData, FMeshDrawSingleShaderBindings& ShaderBindings) const`
- L39 _public function_ `void GetElementShaderBindings( const FShaderMapPointerTable& PointerTable, const FScene* Scene, const FSceneView* ViewIfDynamicMeshCommand, const FVertexFactory* VertexFactory, const EVertexInputStreamType InputStreamType, ERHIFeatureLevel::Type FeatureLevel, const FPrimitiveSceneProxy* PrimitiveSceneProxy, const FMeshBatch& MeshBatch, const FMeshBatchElement& BatchElement, const FMeshMaterialShaderElementData& ShaderElementData, FMeshDrawSingleShaderBindings& ShaderBindings, FVertexInputStreamArray& VertexStreams) const`

### `Plugins/FX/Niagara/Source/NiagaraVertexFactories/Public/NiagaraCutoutVertexBuffer.h` (Public)


#### class `FNiagaraCutoutVertexBuffer`  
`class FNiagaraCutoutVertexBuffer : public FVertexBuffer`  
_L15-30_
- inherits: `FVertexBuffer`
- desc: Vertex buffer to hold cutout UVs.
- L19 _public prototype_ `FNiagaraCutoutVertexBuffer(int32 ZeroInitCount = 0);`
- L24 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — Initialize the RHI for this rendering resource
- L25 _public prototype_ `virtual void ReleaseRHI() override;`
- L26 _public member_ `FShaderResourceViewRHIRef VertexBufferSRV;`
- L29 _public member_ `TArray<FVector2f> Data;` — Data to initialize the buffer.

#### Free symbols / members of external scopes

- L32 _externvar_ `extern TGlobalResource<FNiagaraCutoutVertexBuffer> GFNiagaraNullCutoutVertexBuffer;`

### `Plugins/FX/Niagara/Source/NiagaraVertexFactories/Public/NiagaraDispatchIndirect.h` (Public)


#### struct `FNiagaraDispatchIndirectInfoCS`  
`struct FNiagaraDispatchIndirectInfoCS`  
_L11-24_
- L13 _public prototype_ `FNiagaraDispatchIndirectInfoCS() = default;`
- L14 _public function_ `explicit FNiagaraDispatchIndirectInfoCS(const FUintVector& InCounterOffsets, const FIntVector& InThreadGroupSize, uint32 InIndirectArgsOffset) : CounterOffsets(InCounterOffsets) , ThreadGroupSize(InThreadGroupSize) , IndirectArgsOffset(InIndirectArgsOffset)`
- L21 _public member_ `FUintVector CounterOffsets = FUintVector(INDEX_NONE, INDEX_NONE, INDEX_NONE);`
- L22 _public member_ `FIntVector ThreadGroupSize = FIntVector::ZeroValue;`
- L23 _public member_ `uint32 IndirectArgsOffset = 0;`

#### struct `FNiagaraDispatchIndirectParametersCS`  
`struct FNiagaraDispatchIndirectParametersCS`  
_L26-30_
- L28 _public member_ `FUintVector4 GroupCount = FUintVector4(0, 0, 0, 0);`
- L29 _public member_ `FUintVector4 ThreadCount = FUintVector4(0, 0, 0, 0);`

#### class `FNiagaraDispatchIndirectArgsGenCS`  
`class FNiagaraDispatchIndirectArgsGenCS : public FGlobalShader`  
_L32-50_
- inherits: `FGlobalShader`
- L35 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraDispatchIndirectArgsGenCS, FGlobalShader);`
- L38 _public member_ `static constexpr int ThreadCount = 32;`
- L41 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<uint>, DispatchInfos) SHADER_PARAMETER(uint32, NumDispatchInfos) SHADER_PARAMETER(FUintVector3, MaxGroupsPerDimension) SHADER_PARAMETER_SRV(Buffer<uint>, InstanceCounts) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<uint4>, RWDispatchIndirectArgs) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

### `Plugins/FX/Niagara/Source/NiagaraVertexFactories/Public/NiagaraDrawIndirect.h` (Public)


#### enum `ENiagaraDrawIndirectArgGenTaskFlags`  
`enum class ENiagaraDrawIndirectArgGenTaskFlags : uint32`  
_L23-29_
- L25 _public enumerator_ `None = 0`
- L26 _public enumerator_ `UseCulledCounts = 1 << 0`
- L27 _public enumerator_ `InstancedStereo = 1 << 1`
- L28 _public enumerator_ `PostOpaque = 1 << 2`

#### struct `FNiagaraDrawIndirectArgGenTaskInfo`  
`struct FNiagaraDrawIndirectArgGenTaskInfo`  
_L37-61_
- desc: Task info when generating draw indirect frame buffer. Task is either about generate Niagara renderers drawindirect buffer, or about resetting released instance counters.
- L39 _public function_ `explicit FNiagaraDrawIndirectArgGenTaskInfo(uint32 InInstanceCountBufferOffset, uint32 InNumIndicesPerInstance, uint32 InStartIndexLocation, ENiagaraDrawIndirectArgGenTaskFlags InFlags) : IndirectArgsBufferOffset(INDEX_NONE) , InstanceCountBufferOffset(InInstanceCountBufferOffset) , NumIndicesPerInstance(InNumIndicesPerInstance) , StartIndexLocation(InStartIndexLocation) , Flags((uint32)InFlags)`
- L48 _public member_ `uint32 IndirectArgsBufferOffset;` — Ignored in hash / comparison since we can de-duplicate the rest
- L49 _public member_ `uint32 InstanceCountBufferOffset;`
- L50 _public member_ `uint32 NumIndicesPerInstance;` — When -1 the counter needs to be reset to 0.
- L51 _public member_ `uint32 StartIndexLocation;`
- L52 _public member_ `uint32 Flags;`
- L54 _public function_ `bool operator==(const FNiagaraDrawIndirectArgGenTaskInfo& Rhs) const`

#### class `FNiagaraDrawIndirectArgsGenCS`  
`class FNiagaraDrawIndirectArgsGenCS : public FGlobalShader`  
_L67-87_
- inherits: `FGlobalShader`
- desc: Compute shader used to generate GPU emitter draw indirect args. It also resets unused instance count entries.
- L70 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraDrawIndirectArgsGenCS, FGlobalShader);`
- L74 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FSupportsTextureRW>;`
- L77 _public prototype_ `SHADER_PARAMETER_SRV(Buffer<uint>, TaskInfos) SHADER_PARAMETER_SRV(Buffer<uint>, CulledInstanceCounts) SHADER_PARAMETER_UAV(RWBuffer<uint>, RWInstanceCounts) SHADER_PARAMETER_UAV(RWBuffer<uint>, RWDrawIndirectArgs) SHADER_PARAMETER(FUintVector4, TaskCount) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `FNiagaraDrawIndirectResetCountsCS`  
`class FNiagaraDrawIndirectResetCountsCS : public FGlobalShader`  
_L92-107_
- inherits: `FGlobalShader`
- desc: Compute shader used to reset unused instance count entries. Used if the platform doesn't support RW texture buffers
- L95 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraDrawIndirectResetCountsCS, FGlobalShader);`
- L98 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<>;`
- L101 _public prototype_ `SHADER_PARAMETER_SRV(Buffer<uint>, TaskInfos) SHADER_PARAMETER_UAV(RWBuffer<uint>, RWInstanceCounts) SHADER_PARAMETER(FUintVector4, TaskCount) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `FNiagaraInstanceCountsInitCS`  
`class FNiagaraInstanceCountsInitCS : public FGlobalShader`  
_L112-127_
- inherits: `FGlobalShader`
- desc: Compute shader used to initialize instance count entries to specific values. Used if the platform doesn't support RW texture buffers
- L115 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraInstanceCountsInitCS, FGlobalShader);`
- L118 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<>;`
- L121 _public prototype_ `SHADER_PARAMETER_SRV(Buffer<uint>, TaskInfos) SHADER_PARAMETER_UAV(RWBuffer<uint>, RWInstanceCounts) SHADER_PARAMETER(FUintVector4, TaskCount) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define NIAGARA_DRAW_INDIRECT_ARGS_GEN_THREAD_COUNT 64`
- L16 _macro_ `#define NIAGARA_DRAW_INDIRECT_ARGS_SIZE 5`
- L17 _macro_ `#define NIAGARA_DRAW_INDIRECT_TASK_INFO_SIZE 5`
- L18 _macro_ `#define NIAGARA_INIT_INSTANCE_COUNT_TASK_INFO_SIZE 2`
- L30 _prototype_ `ENUM_CLASS_FLAGS(ENiagaraDrawIndirectArgGenTaskFlags);`

### `Plugins/FX/Niagara/Source/NiagaraVertexFactories/Public/NiagaraGPURayTracingTransformsShader.h` (Public)


#### class `FNiagaraGPURayTracingTransformsCS`  
`class FNiagaraGPURayTracingTransformsCS : public FGlobalShader`  
_L17-68_
- inherits: `FGlobalShader`
- desc: Compute shader used to pass GPU instances transforms to the ray tracing TLAS.
- L20 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraGPURayTracingTransformsCS, FGlobalShader);`
- L22 _private member_ `static constexpr uint32 ThreadGroupSize = 64;`
- L24 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<>;`
- L26 _private prototype_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`
- L27 _private prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

### `Plugins/FX/Niagara/Source/NiagaraVertexFactories/Public/NiagaraMeshVertexFactory.h` (Public)


#### class `FNiagaraMeshVertexFactory`  
`class FNiagaraMeshVertexFactory : public FNiagaraVertexFactoryBase`  
_L120-222_
- inherits: `FNiagaraVertexFactoryBase`
- desc: Vertex factory for rendering instanced mesh particles with out dynamic parameter support.
- L126 _public function_ `FNiagaraMeshVertexFactory(ENiagaraVertexFactoryType InType, ERHIFeatureLevel::Type InFeatureLevel) : FNiagaraVertexFactoryBase(InType, InFeatureLevel) , bAddPrimitiveIDElement(true)` — Default constructor.
- L131 _public function_ `FNiagaraMeshVertexFactory() : FNiagaraVertexFactoryBase(NVFT_MAX, ERHIFeatureLevel::Num) , bAddPrimitiveIDElement(true)`
- L139 _public prototype_ `static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);` — Should we cache the material's shadertype on this platform with this vertex factory?
- L146 _public prototype_ `static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);` — Modify compile environment to enable instancing @param OutEnvironment - shader compile environment to modify
- L151 _public prototype_ `static void GetPSOPrecacheVertexFetchElements(EVertexInputStreamType VertexInputStreamType, FVertexDeclarationElementList& Elements);` — Get vertex elements used when during PSO precaching materials using this vertex factory type
- L152 _public prototype_ `static void GetVertexElements(ERHIFeatureLevel::Type FeatureLevel, bool bSupportsManualVertexFetch, FStaticMeshDataType& Data, FVertexDeclarationElementList& Elements);`
- L157 _public prototype_ `void SetData(FRHICommandListBase& RHICmdList, const FStaticMeshDataType& InData);` — An implementation of the interface used by TSynchronizedResource to update the resource with new data from the game thread.
- L162 _public function_ `inline void SetUniformBuffer(const FNiagaraMeshUniformBufferRef& InMeshParticleUniformBuffer)` — Set the uniform buffer for this vertex factory.
- L170 _public function_ `inline FRHIUniformBuffer* GetUniformBuffer() const` — Retrieve the uniform buffer for this vertex factory.
- L175 _public function_ `inline FRHIShaderResourceView* GetTangentsSRV() const`
- L180 _public function_ `inline FRHIShaderResourceView* GetTextureCoordinatesSRV() const`
- L185 _public function_ `inline FRHIShaderResourceView* GetColorComponentsSRV() const`
- L190 _public function_ `inline uint32 GetColorIndexMask() const`
- L195 _public function_ `inline int GetNumTexcoords() const`
- L201 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource interface.
- L203 _public function_ `bool IsPrimitiveIDElementEnabled() const`
- L204 _public function_ `void EnablePrimitiveIDElement(bool bEnable)`
- L206 _public function_ `inline void SetNiagaraMeshFeatureLevel(ERHIFeatureLevel::Type InFeatureLevel)`
- L211 _public prototype_ `static bool IsGPUSceneEnabled(const FStaticShaderPlatform Platform, const FStaticFeatureLevel FeatureLevel);`
- L214 _protected prototype_ `static void GetVertexElements(ERHIFeatureLevel::Type FeatureLevel, bool bSupportsManualVertexFetch, FStaticMeshDataType& Data, FVertexDeclarationElementList& Elements, FVertexStreamList& InOutStreams);`
- L217 _protected member_ `FStaticMeshDataType Data;`
- L218 _protected member_ `bool bAddPrimitiveIDElement;`
- L221 _protected member_ `FRHIUniformBuffer* MeshParticleUniformBuffer;` — Uniform buffer with mesh particle parameters.

#### Free symbols / members of external scopes

- L112 _typedef_ `typedef TUniformBufferRef<FNiagaraMeshUniformParameters> FNiagaraMeshUniformBufferRef;`

### `Plugins/FX/Niagara/Source/NiagaraVertexFactories/Public/NiagaraRibbonVertexFactory.h` (Public)


#### struct `FNiagaraRibbonVertexDynamicParameter`  
`struct FNiagaraRibbonVertexDynamicParameter`  
_L19-23_
- desc: FNiagaraRibbonVertexDynamicParameter
- L22 _public member_ `float DynamicValue[4];` — The dynamic parameter of the particle

#### class `FNiagaraRibbonVertexFactory`  
`class FNiagaraRibbonVertexFactory : public FNiagaraVertexFactoryBase`  
_L95-166_
- inherits: `FNiagaraVertexFactoryBase`
- desc: Beam/Trail particle vertex factory.
- L102 _public function_ `FNiagaraRibbonVertexFactory(ENiagaraVertexFactoryType InType, ERHIFeatureLevel::Type InFeatureLevel) : FNiagaraVertexFactoryBase(InType, InFeatureLevel) , DataSet(nullptr)` — Default constructor.
- L107 _public function_ `FNiagaraRibbonVertexFactory() : FNiagaraVertexFactoryBase(NVFT_MAX, ERHIFeatureLevel::Num) , DataSet(nullptr)`
- L115 _public prototype_ `static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);` — Should we cache the material's shadertype on this platform with this vertex factory?
- L120 _public prototype_ `static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);` — Can be overridden by FVertexFactory subclasses to modify their compile environment just before compilation occurs.
- L125 _public prototype_ `static void GetPSOPrecacheVertexFetchElements(EVertexInputStreamType VertexInputStreamType, FVertexDeclarationElementList& Elements);` — Get vertex elements used when during PSO precaching materials using this vertex factory type
- L128 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource interface.
- L133 _public function_ `inline void SetRibbonUniformBuffer(FNiagaraRibbonUniformBufferRef InSpriteUniformBuffer)` — Set the uniform buffer for this vertex factory.
- L141 _public function_ `inline FNiagaraRibbonUniformBufferRef GetRibbonUniformBuffer() const` — Retrieve the uniform buffer for this vertex factory.
- L149 _public prototype_ `void SetVertexBuffer(const FVertexBuffer* InBuffer, uint32 StreamOffset, uint32 Stride);` — Set the source vertex buffer.
- L154 _public prototype_ `void SetDynamicParameterBuffer(const FVertexBuffer* InDynamicParameterBuffer, int32 ParameterIndex, uint32 StreamOffset, uint32 Stride);` — Set the source vertex buffer that contains particle dynamic parameter data.
- L157 _public member_ `FUniformBufferRHIRef LooseParameterUniformBuffer;`
- L162 _private member_ `FNiagaraRibbonUniformBufferRef NiagaraRibbonUniformBuffer;` — Uniform buffer with beam/trail parameters.
- L165 _private member_ `const FNiagaraDataSet *DataSet;`

#### Free symbols / members of external scopes

- L70 _typedef_ `typedef TUniformBufferRef<FNiagaraRibbonUniformParameters> FNiagaraRibbonUniformBufferRef;`
- L90 _typedef_ `typedef TUniformBufferRef<FNiagaraRibbonVFLooseParameters> FNiagaraRibbonVFLooseParametersRef;`

### `Plugins/FX/Niagara/Source/NiagaraVertexFactories/Public/NiagaraSortingGPU.h` (Public)


#### class `FNiagaraSortKeyGenCS`  
`class FNiagaraSortKeyGenCS : public FGlobalShader`  
_L27-84_
- inherits: `FGlobalShader`
- desc: Compute shader used to generate particle sort keys.
- L30 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FNiagaraSortKeyGenCS, FGlobalShader);`
- L36 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FEnableCulling, FSortUsingMaxPrecision, FUseWaveOps>;`
- L39 _public prototype_ `SHADER_PARAMETER_SRV(Buffer, NiagaraParticleDataFloat) SHADER_PARAMETER_SRV(Buffer, NiagaraParticleDataHalf) SHADER_PARAMETER_SRV(Buffer, NiagaraParticleDataInt) SHADER_PARAMETER_SRV(Buffer, GPUParticleCountBuffer) SHADER_PARAMETER(uint32, FloatDataStride) SHADER_PARAMETER(uint32, HalfDataStride) SHADER_PARAMETER(uint32, IntDataStride) SHADER_PARAMETER(uint32, ParticleCount) SHADER_PARAMETER(uint32, GPUParticleCountOffset) SHADER_PARAMETER(uint32, CulledGPUParticleCountOffset) SHADER_PARAMETER(uint32, EmitterKey) SHADER_PARAMETER(uint32, OutputOffset) SHADER_PARAMETER(FVector3f, CameraPosition) SHADER_PARAMETER(FVector3f, CameraDirection) SHADER_PARAMETER(uint32, SortMode) SHADER_PARAMETER(uint32, SortAttributeOffset) SHADER_PARAMETER(uint32, SortKeyMask) SHADER_PARAMETER(uint32, SortKeyShift) SHADER_PARAMETER(uint32, SortKeySignBit) SHADER_PARAMETER(uint32, CullPositionAttributeOffset) SHADER_PARAMETER(uint32, CullOrientationAttributeOffset) SHADER_PARAMETER(uint32, CullScaleAttributeOffset) SHADER_PARAMETER(int32, NumCullPlanes) SHADER_PARAMETER_ARRAY(FVector4f, CullPlanes, [NIAGARA_KEY_GEN_MAX_CULL_PLANES]) SHADER_PARAMETER(int32, RendererVisibility) SHADER_PARAMETER(uint32, RendererVisTagAttributeOffset) SHADER_PARAMETER(int32, MeshIndex) SHADER_PARAMETER(uint32, MeshIndexAttributeOffset) SHADER_PARAMETER(FVector2f, CullDistanceRangeSquared) SHADER_PARAMETER(FVector4f, LODScreenSize) SHADER_PARAMETER(FVector4f, LocalBoundingSphere) SHADER_PARAMETER(FVector3f, CullingWorld ...`
- L81 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L83 _public prototype_ `static bool UseWaveOps(EShaderPlatform ShaderPlatform);`

#### Free symbols / members of external scopes

- L16 _externvar_ `extern int32 GNiagaraGPUSortingCPUToGPUThreshold;`
- L17 _externvar_ `extern int32 GNiagaraGPUCullingCPUToGPUThreshold;`
- L19 _macro_ `#define NIAGARA_KEY_GEN_THREAD_COUNT 64`
- L20 _macro_ `#define NIAGARA_COPY_BUFFER_THREAD_COUNT 64`
- L21 _macro_ `#define NIAGARA_COPY_BUFFER_BUFFER_COUNT 3`
- L22 _macro_ `#define NIAGARA_KEY_GEN_MAX_CULL_PLANES 12`

### `Plugins/FX/Niagara/Source/NiagaraVertexFactories/Public/NiagaraSpriteVertexFactory.h` (Public)


#### class `FNiagaraSpriteVertexFactory`  
`class FNiagaraSpriteVertexFactory : public FNiagaraVertexFactoryBase`  
_L113-196_
- inherits: `FNiagaraVertexFactoryBase`
- desc: Vertex factory for rendering particle sprites.
- L120 _public function_ `FNiagaraSpriteVertexFactory(ENiagaraVertexFactoryType InType, ERHIFeatureLevel::Type InFeatureLevel ) : FNiagaraVertexFactoryBase(InType, InFeatureLevel)` — Default constructor.
- L121 _public function_ `FNiagaraSpriteVertexFactory() : FNiagaraVertexFactoryBase(NVFT_MAX, ERHIFeatureLevel::Num)`
- L124 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource interface.
- L126 _public function_ `virtual bool RendersPrimitivesAsCameraFacingSprites() const override`
- L131 _public prototype_ `static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);` — Should we cache the material's shadertype on this platform with this vertex factory?
- L136 _public prototype_ `static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);` — Can be overridden by FVertexFactory subclasses to modify their compile environment just before compilation occurs.
- L141 _public prototype_ `static void GetPSOPrecacheVertexFetchElements(EVertexInputStreamType VertexInputStreamType, FVertexDeclarationElementList& Elements);` — Get vertex elements used when during PSO precaching materials using this vertex factory type
- L143 _public prototype_ `void SetTexCoordBuffer(const FVertexBuffer* InTexCoordBuffer);`
- L145 _public function_ `void SetSpriteUniformBuffer(const FNiagaraSpriteUniformBufferRef& InSpriteUniformBuffer )`
- L146 _public function_ `FRHIUniformBuffer* GetSpriteUniformBuffer() const`
- L148 _public function_ `void SetCutoutParameters(bool bUseSubImage, int32 InNumCutoutVertexPerSubImage)`
- L153 _public function_ `uint32 GetCutoutParameters() const`
- L155 _public function_ `void SetCutoutGeometry(FRHIShaderResourceView* InCutoutGeometrySRV)`
- L156 _public function_ `inline FRHIShaderResourceView* GetCutoutGeometrySRV() const`
- L158 _public function_ `void SetSortedIndices(const FShaderResourceViewRHIRef& InSortedIndicesSRV, uint32 InSortedIndicesOffset)`
- L164 _public function_ `FRHIShaderResourceView* GetSortedIndicesSRV() const`
- L165 _public function_ `int32 GetSortedIndicesOffset() const`
- L167 _public function_ `void SetFacingMode(uint32 InMode)`
- L168 _public function_ `uint32 GetFacingMode() const`
- L170 _public function_ `void SetAlignmentMode(uint32 InMode)`
- L171 _public function_ `uint32 GetAlignmentMode() const`
- L173 _public function_ `void SetVertexBufferOverride(const FVertexBuffer* InVertexBufferOverride)`
- L175 _public function_ `void SetLooseParameterUniformBuffer(FUniformBufferRHIRef InBuffer)`
- L176 _public function_ `FRHIUniformBuffer* GetLooseParameterUniformBuffer() const`
- L180 _protected prototype_ `void InitStreams();` — Initialize streams for this vertex factory.
- L184 _private member_ `const FVertexBuffer* VertexBufferOverride = nullptr;`
- L185 _private member_ `FUniformBufferRHIRef LooseParameterUniformBuffer;`
- L188 _private member_ `FUniformBufferRHIRef SpriteUniformBuffer;` — Uniform buffer with sprite parameters.
- L189 _private member_ `uint32 CutoutParameters = 0;`
- L190 _private member_ `FShaderResourceViewRHIRef CutoutGeometrySRV;`
- L191 _private member_ `uint32 AlignmentMode = 0;`
- L192 _private member_ `uint32 FacingMode = 0;`
- L194 _private member_ `FShaderResourceViewRHIRef SortedIndicesSRV;`
- L195 _private member_ `uint32 SortedIndicesOffset = 0;`

#### Free symbols / members of external scopes

- L92 _typedef_ `typedef TUniformBufferRef<FNiagaraSpriteUniformParameters> FNiagaraSpriteUniformBufferRef;`
- L108 _typedef_ `typedef TUniformBufferRef<FNiagaraSpriteVFLooseParameters> FNiagaraSpriteVFLooseParametersRef;`

### `Plugins/FX/Niagara/Source/NiagaraVertexFactories/Public/NiagaraVertexFactoriesModule.h` (Public)


#### class `INiagaraVertexFactoriesModule`  
`class INiagaraVertexFactoriesModule : public IModuleInterface`  
_L11-19_
- inherits: `IModuleInterface`
- desc: Niagara vertex factories module interface
- L15 _public function_ `virtual void StartupModule() override`
- L17 _public function_ `virtual void ShutdownModule() override`

### `Plugins/FX/Niagara/Source/NiagaraVertexFactories/Public/NiagaraVertexFactory.h` (Public)


#### class `FNiagaraNullSortedIndicesVertexBuffer`  
`class FNiagaraNullSortedIndicesVertexBuffer : public FVertexBuffer`  
_L18-47_
- inherits: `FVertexBuffer`
- L24 _public function_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override` — Initialize the RHI for this rendering resource
- L40 _public function_ `virtual void ReleaseRHI() override`
- L46 _public member_ `FShaderResourceViewRHIRef VertexBufferSRV;`

#### enum `ENiagaraVertexFactoryType`  
`enum ENiagaraVertexFactoryType`  
_L53-59_
- desc: Enum identifying the type of a particle vertex factory.
- L55 _public enumerator_ `NVFT_Sprite`
- L56 _public enumerator_ `NVFT_Ribbon`
- L57 _public enumerator_ `NVFT_Mesh`
- L58 _public enumerator_ `NVFT_MAX`

#### class `FNiagaraVertexFactoryBase`  
`class FNiagaraVertexFactoryBase : public FVertexFactory`  
_L64-82_
- inherits: `FVertexFactory`
- desc: Base class for particle vertex factories.
- L69 _public function_ `explicit FNiagaraVertexFactoryBase(ENiagaraVertexFactoryType Type, ERHIFeatureLevel::Type InFeatureLevel) : FVertexFactory(InFeatureLevel)` — Default constructor.
- L75 _public function_ `static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`
- L81 _public function_ `ERHIFeatureLevel::Type GetFeatureLevel() const`

#### class `FNiagaraVertexFactoryShaderParametersBase`  
`class FNiagaraVertexFactoryShaderParametersBase : public FVertexFactoryShaderParameters`  
_L87-103_
- inherits: `FVertexFactoryShaderParameters`
- desc: Base class for Niagara vertex factory shader parameters.
- L92 _public prototype_ `void Bind(const FShaderParameterMap& ParameterMap);`
- L93 _public prototype_ `void GetElementShaderBindings( const FSceneInterface* Scene, const FSceneView* View, const FMeshMaterialShader* Shader, const EVertexInputStreamType VertexStreamType, ERHIFeatureLevel::Type FeatureLevel, const FVertexFactory* VertexFactory, const FMeshBatchElement& BatchElement, class FMeshDrawSingleShaderBindings& ShaderBindings, FVertexInputStreamArray& VertexStreams) const;`

#### Free symbols / members of external scopes

- L48 _externvar_ `extern TGlobalResource<FNiagaraNullSortedIndicesVertexBuffer> GFNiagaraNullSortedIndicesVertexBuffer;`
