# Shaders / Plugins/FX/Niagara/Shaders/Private

- files: 95; lines: 17370
- record kinds: cpp_binding=41, define=162, entry=35, function=931, groupshared=22, include=103, macro_call=6, member=254, parameter=410, prototype=34, resource=244, static_const=3, static_var=17, struct=26

### `Plugins/FX/Niagara/Shaders/Private/NiagaraAsyncGpuTraceCommon.ush` (Private)

- lines: 28; parse: all-branches
- includes: L5 `/Engine/Private/Common.ush`
- L3 #pragma `once`

#### Structs / classes (2)

- L7-13 _struct_ **`FNiagaraAsyncGpuTrace`** `struct FNiagaraAsyncGpuTrace`
  - L9 _member_ `float3 Origin;`
  - L10 _member_ `float TFar;`
  - L11 _member_ `float3 Direction;`
  - L12 _member_ `uint CollisionGroup;`
- L15-23 _struct_ **`FNiagaraAsyncGpuTraceResult`** `struct FNiagaraAsyncGpuTraceResult`
  - L17 _member_ `float3 WorldPosition;`
  - L18 _member_ `float HitT;`
  - L20 _member_ `float3 WorldNormal;`
  - L22 _member_ `float _Pad0;` — padding to force 16 byte alignment to meet requirements for VK

#### Functions (1)

- L25-28 _function_ `bool IsHit(FNiagaraAsyncGpuTraceResult Result)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraAsyncGpuTraceUtils.usf` (Private)

- lines: 29; parse: all-branches
- includes: L5 `/Engine/Private/Common.ush`, L6 `NiagaraAsyncGpuTraceCommon.ush`

#### Macros (#define, 1)

- L9 `#define THREADGROUP_SIZE_X 32` _[#if !defined(THREADGROUP_SIZE_X)]_
- L3 #pragma `once`

#### Entry points (1)

- L17-29 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void NiagaraClearAsyncGpuTraceCS(uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNiagaraClearAsyncGpuTraceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraAsyncGpuTraceProvider.cpp:42)

#### Global resources (textures / buffers / samplers) (1)

- L12 _resource_ `RWStructuredBuffer<FNiagaraAsyncGpuTraceResult> Results;`

#### Global parameters (uniforms) (2)

- L14 _parameter_ `uint TraceCount;`
- L15 _parameter_ `uint ResultsOffset;`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraBaryCentricUtils.ush` (Private)

- lines: 93; parse: all-branches
- L3 #pragma `once`

#### Functions (2)

- L6-12 _function_ `float3 GetBaryCentric2D(float2 P, float2 A, float2 B, float2 C)` — from FMath::GetBaryCentric2D()
- L14-93 _function_ `float3 GetClosestBaryCentric2D(float2 P, float2 A, float2 B, float2 C)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraBatchedElements.usf` (Private)

- lines: 157; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L5 `/Engine/Private/GammaCorrectionCommon.ush`, L6 `NiagaraCommon.ush`

#### Macros (#define, 1)

- L12 `#define INDEX_NONE -1` _[#if NIAGARA_2DARRAY_ATTRIBUTE_PS]_

#### Entry points (3)

- L20-56 _entry_ `void MainPS( in float2 InTextureCoordinate : TEXCOORD0, in float4 InColor : TEXCOORD1, in float4 InHitProxyId : TEXCOORD2, in float4 InPosition : SV_POSITION, out float4 OutColor : SV_Target0 ,out float4 OutWorldNormal : SV_Target1 )` — stage: **pixel (from C++ binding)** — C++: `FNiagaraSimpleElement2DArrayAttribute` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraBatchedElements.cpp:40) — C++: `FNiagaraSimpleElementVolumeAttribute` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraBatchedElements.cpp:110) — C++: `FNiagaraSimpleElementPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraBatchedElements.cpp:185) _[#if NIAGARA_2DARRAY_ATTRIBUTE_PS]_
- L72-109 _entry_ `void MainPS( in float2 InTextureCoordinate : TEXCOORD0, in float4 InColor : TEXCOORD1, in float4 InHitProxyId : TEXCOORD2, in float4 InPosition : SV_POSITION, out float4 OutColor : SV_Target0 ,out float4 OutWorldNormal : SV_Target1 )` — stage: **pixel (from C++ binding)** — C++: `FNiagaraSimpleElement2DArrayAttribute` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraBatchedElements.cpp:40) — C++: `FNiagaraSimpleElementVolumeAttribute` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraBatchedElements.cpp:110) — C++: `FNiagaraSimpleElementPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraBatchedElements.cpp:185) _[#if NIAGARA_VOLUME_ATTRIBUTE_PS]_
- L122-152 _entry_ `void MainPS( in float2 InTextureCoordinate : TEXCOORD0, in float4 InColor : TEXCOORD1, in float4 InHitProxyId : TEXCOORD2, in float4 InPosition : SV_POSITION, out float4 OutColor : SV_Target0 ,out float4 OutWorldNormal : SV_Target1 )` — stage: **pixel (from C++ binding)** — C++: `FNiagaraSimpleElement2DArrayAttribute` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraBatchedElements.cpp:40) — C++: `FNiagaraSimpleElementVolumeAttribute` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraBatchedElements.cpp:110) — C++: `FNiagaraSimpleElementPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraBatchedElements.cpp:185) _[#if NIAGARA_SIMPLE_PS]_

#### Global resources (textures / buffers / samplers) (6)

- L14 _resource_ `Texture2DArray InTexture;` _[#if NIAGARA_2DARRAY_ATTRIBUTE_PS]_
- L15 _resource_ `SamplerState InTextureSampler;` _[#if NIAGARA_2DARRAY_ATTRIBUTE_PS]_
- L64 _resource_ `Texture3D InTexture;` _[#if NIAGARA_VOLUME_ATTRIBUTE_PS]_
- L65 _resource_ `SamplerState InTextureSampler;` _[#if NIAGARA_VOLUME_ATTRIBUTE_PS]_
- L117 _resource_ `Texture2D InTexture;` _[#if NIAGARA_SIMPLE_PS]_
- L118 _resource_ `SamplerState InTextureSampler;` _[#if NIAGARA_SIMPLE_PS]_

#### Global parameters (uniforms) (10)

- L16 _parameter_ `int4 InAttributeSlices;` _[#if NIAGARA_2DARRAY_ATTRIBUTE_PS]_
- L17 _parameter_ `float4x4 InColorWeights;` _[#if NIAGARA_2DARRAY_ATTRIBUTE_PS]_
- L18 _parameter_ `float InGamma;` _[#if NIAGARA_2DARRAY_ATTRIBUTE_PS]_
- L66 _parameter_ `int InNumAttributes;` _[#if NIAGARA_VOLUME_ATTRIBUTE_PS]_
- L67 _parameter_ `float4 InAttributeUVAndChannel[4];` _[#if NIAGARA_VOLUME_ATTRIBUTE_PS]_
- L68 _parameter_ `float2 InTileUV;` _[#if NIAGARA_VOLUME_ATTRIBUTE_PS]_
- L69 _parameter_ `float4x4 InColorWeights;` _[#if NIAGARA_VOLUME_ATTRIBUTE_PS]_
- L70 _parameter_ `float InGamma;` _[#if NIAGARA_VOLUME_ATTRIBUTE_PS]_
- L119 _parameter_ `float4x4 InColorWeights;` _[#if NIAGARA_SIMPLE_PS]_
- L120 _parameter_ `float InGamma;` _[#if NIAGARA_SIMPLE_PS]_

### `Plugins/FX/Niagara/Shaders/Private/NiagaraBlendSVTsToDenseBuffer.usf` (Private)

- lines: 41; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/SparseVolumeTexture/SparseVolumeTextureCommon.ush`

#### Entry points (1)

- L25-40 _entry_ `[numthreads(4, 4, 4)] void PerformBlendCS(uint3 Index : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraBlendSVTsToDenseBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraSVTShaders.cpp:22)

#### Global resources (textures / buffers / samplers) (9)

- L5 _resource_ `RWTexture3D<float4> DestinationBuffer;`
- L7 _resource_ `SamplerState TileDataTextureSampler_A;`
- L8 _resource_ `Texture3D<uint> SparseVolumeTexturePageTable_A;`
- L9 _resource_ `Texture3D SparseVolumeTextureA_A;`
- L12 _resource_ `int3 TextureSize_A;`
- L15 _resource_ `SamplerState TileDataTextureSampler_B;`
- L16 _resource_ `Texture3D<uint> SparseVolumeTexturePageTable_B;`
- L17 _resource_ `Texture3D SparseVolumeTextureA_B;`
- L20 _resource_ `int3 TextureSize_B;`

#### Global parameters (uniforms) (7)

- L10 _parameter_ `uint4 PackedSVTUniforms0_A;`
- L11 _parameter_ `uint4 PackedSVTUniforms1_A;`
- L13 _parameter_ `int MipLevels_A;`
- L18 _parameter_ `uint4 PackedSVTUniforms0_B;`
- L19 _parameter_ `uint4 PackedSVTUniforms1_B;`
- L21 _parameter_ `int MipLevels_B;`
- L23 _parameter_ `float LerpAmount;`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraClearCounts.usf` (Private)

- lines: 44; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (2)

- L11-21 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ClearCountsIntCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraClearCountsIntCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraClearCounts.cpp:55) — C++: `FNiagaraClearCountsIntCS_Legacy` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraClearCounts.cpp:150) _[#if NIAGARA_CLEAR_COUNTS_INT_CS]_
- L31-41 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ClearCountsUIntCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraClearCountsUIntCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraClearCounts.cpp:56) — C++: `FNiagaraClearCountsUIntCS_Legacy` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraClearCounts.cpp:151) _[#if NIAGARA_CLEAR_COUNTS_UINT_CS]_

#### Global resources (textures / buffers / samplers) (4)

- L7 _resource_ `RWBuffer<int> CountBuffer;` _[#if NIAGARA_CLEAR_COUNTS_INT_CS]_
- L8 _resource_ `Buffer<int> CountsAndValuesBuffer;` _[#if NIAGARA_CLEAR_COUNTS_INT_CS]_
- L27 _resource_ `RWBuffer<uint> CountBuffer;` _[#if NIAGARA_CLEAR_COUNTS_UINT_CS]_
- L28 _resource_ `Buffer<uint> CountsAndValuesBuffer;` _[#if NIAGARA_CLEAR_COUNTS_UINT_CS]_

#### Global parameters (uniforms) (2)

- L9 _parameter_ `uint NumCounts;` _[#if NIAGARA_CLEAR_COUNTS_INT_CS]_
- L29 _parameter_ `uint NumCounts;` _[#if NIAGARA_CLEAR_COUNTS_UINT_CS]_

### `Plugins/FX/Niagara/Shaders/Private/NiagaraCommon.ush` (Private)

- lines: 110; parse: all-branches
- L3 #pragma `once`

#### Functions (8)

- L5-19 _function_ `float3x3 NiagaraQuatTo3x3(float4 Q)`
- L21-35 _function_ `float4x4 NiagaraComposeTransformMatrix(float3 S, float3x3 R, float3 T)`
- L37-40 _function_ `FLWCMatrix NiagaraComposeTransformMatrix(float3 S, float3x3 R, FLWCVector3 T)`
- L42-65 _function_ `float4x4 NiagaraComposeInvTransformMatrix(float3 S, float3x3 R, float3 T)`
- L67-70 _function_ `FLWCInverseMatrix NiagaraComposeInvTransformMatrix(float3 S, float3x3 R, FLWCVector3 T)`
- L72-94 _function_ `float3x3 NiagaraFindRotationBetweenNormals(float3 A, float3 B)`
- L96-102 _function_ `float4 NiagaraQuatMul(float4 Quat1, float4 Quat2)`
- L104-108 _function_ `float3 NiagaraQuatRotateVector(float4 Quat, float3 Vector)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraComputeFreeIDs.usf` (Private)

- lines: 126; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (2)

- L21-58 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ComputeFreeIDs(uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `NiagaraComputeFreeIDsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraShaderParticleID.cpp:106) — This happens to be fixed on PS4 and XB1, but we'll need to configure it externally _[#if USE_WAVE_INTRINSICS]_
- L67-123 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ComputeFreeIDs(uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `NiagaraComputeFreeIDsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraShaderParticleID.cpp:106) _[#if !(USE_WAVE_INTRINSICS)]_

#### Global resources (textures / buffers / samplers) (3)

- L6 _resource_ `Buffer<int> IDToIndexTable;` — ID mapping table produced by the simulate step.
- L9 _resource_ `RWBuffer<int> RWFreeIDList;` — Output list of free IDs.
- L13 _resource_ `RWBuffer<int> RWFreeIDListSizes;` — Buffer containing the current size of each list that's currently being processed. Multiple invocations of this shader might be running concurrently, for independent emitters.

#### Global parameters (uniforms) (1)

- L16 _parameter_ `uint FreeIDListIndex;` — Index of the free list that's being computed by this invocation. The current size of the list is at RWFreeIDListSizes[FreeIDListIndex].

#### groupshared (2)

- L63 _groupshared_ `groupshared uint GroupWriteOffsets[2*THREADGROUP_SIZE];` — Temporary buffer where we compute the number of elements to write before each input element. _[#if !(USE_WAVE_INTRINSICS)]_
- L65 _groupshared_ `groupshared uint GroupWriteStart;` — The offset where this thread group will start writing its output. _[#if !(USE_WAVE_INTRINSICS)]_

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceActorComponentTemplate.ush` (Private)

- lines: 29; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (5)

- L3 _parameter_ `uint {ParameterName}_Valid;`
- L4 _parameter_ `float4x4 {ParameterName}_Matrix;`
- L5 _parameter_ `float4 {ParameterName}_Rotation;`
- L6 _parameter_ `float3 {ParameterName}_Scale;`
- L7 _parameter_ `float3 {ParameterName}_Velocity;`

#### Functions (3)

- L9-13 _function_ `void GetMatrix_{ParameterName}(out bool bOutValid, out float4x4 OutMatrix)`
- L15-21 _function_ `void GetTransform_{ParameterName}(out bool bOutValid, out float3 OutPosition, out float4 OutRotation, out float3 OutScale)`
- L23-27 _function_ `void GetVelocity_{ParameterName}(out bool bOutValid, out float3 OutVelocity)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceArrayDistributionIntTemplate.ush` (Private)

- lines: 49; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L4 _resource_ `ByteAddressBuffer {ParameterName}_BuiltTableData;`

#### Global parameters (uniforms) (1)

- L3 _parameter_ `int {ParameterName}_Length;`

#### Functions (6)

- L6-9 _function_ `void Length_{ParameterName}(out int OutLength)`
- L11-14 _function_ `void IsValidIndex_{ParameterName}(in int InIndex, out bool OutIsValid)`
- L16-19 _function_ `void LastIndex_{ParameterName}(out int OutLastIndex)`
- L21-28 _function_ `void Get_{ParameterName}(in int InIndex, out NDIDistributionIntArrayEntry OutEntry)`
- L30-37 _function_ `void GetProbabilityAlias_{ParameterName}(in int InIndex, out float Prob, out int Alias)`
- L39-48 _function_ `void GetRandomValue_{ParameterName}(NiagaraRandInfo RandInfo, out int OutValue)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceArrayRWTemplate.ush` (Private)

- lines: 146; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Macros (#define, 4)

- L34 `#define BUFFER_NAME {ParameterName}_ArrayRWBuffer`
- L45 `#define BUFFER_NAME {ParameterName}_ArrayRWBuffer`
- L62 `#define BUFFER_NAME {ParameterName}_ArrayRWBuffer`
- L90 `#define BUFFER_NAME {ParameterName}_ArrayRWBuffer`
- L36 #undef `BUFFER_NAME`; L47 #undef `BUFFER_NAME`; L64 #undef `BUFFER_NAME`; L92 #undef `BUFFER_NAME`

#### Global resources (textures / buffers / samplers) (1)

- L8 _resource_ `RWBuffer<{RWBufferType}> {ParameterName}_ArrayRWBuffer;`

#### Global parameters (uniforms) (1)

- L9 _parameter_ `int2 {ParameterName}_ArrayBufferParams;` — Where x=CountOffset & y=BufferCapacity

#### Functions (13)

- L11 _function_ `int GetCountOffset_{ParameterName}()`
- L12 _function_ `int GetCapacity_{ParameterName}()`
- L13 _function_ `int GetLength_{ParameterName}()`
- L15-18 _function_ `void Length_{ParameterName}(out int ArrayLength)`
- L20-23 _function_ `void IsValidIndex_{ParameterName}(int Index, out bool bIsValid)`
- L25-28 _function_ `void LastIndex_{ParameterName}(out int Index)`
- L30-37 _function_ `void Get_{ParameterName}(int Index, out {VariableType} Value)`
- L39-49 _function_ `void SetArrayElem_{ParameterName}_UEImpureCall(bool bSkip, int Index, {VariableType} Value)`
- L51-70 _function_ `void Add_{ParameterName}_UEImpureCall(bool bSkip, {VariableType} Value)`
- L72-93 _function_ `void RemoveLastElem_{ParameterName}_UEImpureCall(bool bSkip, out {VariableType} Value, out bool bOutValid)`
- L97-111 _function_ `void AtomicAdd_{ParameterName}_UEImpureCall(bool bSkip, int Index, int Value, out {VariableType} PrevValue, out {VariableType} CurrValue)` _[#if {bSupportsAtomicOps}]_
- L113-127 _function_ `void AtomicMin_{ParameterName}_UEImpureCall(bool bSkip, int Index, int Value, out {VariableType} PrevValue, out {VariableType} CurrValue)` _[#if {bSupportsAtomicOps}]_
- L129-143 _function_ `void AtomicMax_{ParameterName}_UEImpureCall(bool bSkip, int Index, int Value, out {VariableType} PrevValue, out {VariableType} CurrValue)` _[#if {bSupportsAtomicOps}]_

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceArrayTemplate.ush` (Private)

- lines: 35; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Macros (#define, 1)

- L31 `#define BUFFER_NAME {ParameterName}_ArrayReadBuffer`
- L33 #undef `BUFFER_NAME`

#### Global resources (textures / buffers / samplers) (1)

- L7 _resource_ `Buffer<{ReadBufferType}> {ParameterName}_ArrayReadBuffer;`

#### Global parameters (uniforms) (1)

- L8 _parameter_ `int2 {ParameterName}_ArrayBufferParams;` — Where x=Length & y=max(Length-1,0)

#### Functions (6)

- L10 _function_ `int GetLength_{ParameterName}()`
- L11 _function_ `int GetLengthMinusOne_{ParameterName}()`
- L13-16 _function_ `void Length_{ParameterName}(out int ArrayLength)`
- L18-21 _function_ `void IsValidIndex_{ParameterName}(int Index, out bool bIsValid)`
- L23-26 _function_ `void LastIndex_{ParameterName}(out int Index)`
- L28-34 _function_ `void Get_{ParameterName}(int Index, out {VariableType} Value)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceAsyncGpuTrace.ush` (Private)

- lines: 114; parse: all-branches
- includes: L5 `NiagaraAsyncGpuTraceCommon.ush`
- L3 #pragma `once`

#### Functions (4)

- L7-43 _function_ `void NDIAsyncGpuTrace_IssueAsyncRayTrace( uint MaxRayTraceCount, RWStructuredBuffer<FNiagaraAsyncGpuTrace> RWRayRequests, uint RayRequestOffset, RWBuffer<uint> RWRayTraceCounts, uint RayTraceCountsOffset, float3 In_LWCTile, int In_QueryID, float3 In_TraceStart, float3 In_TraceEnd, int In_CollisionGroup, out bool Out_IsQueryValid)`
- L45-67 _function_ `void NDIAsyncGpuTrace_ReserveRayTraceIndex(uint MaxRayTraceCount, RWBuffer<uint> RWRayTraceCounts, uint RayTraceCountsOffset, int In_TraceCount, out int Out_StartQueryID, out bool Out_IndicesValid)`
- L69-93 _function_ `void NDIAsyncGpuTrace_CreateAsyncRayTrace( uint MaxRayTraceCount, RWStructuredBuffer<FNiagaraAsyncGpuTrace> RWRayRequests, uint RayRequestsOffset, RWBuffer<uint> RWRayTraceCounts, uint RayTraceCountsOffset, float3 In_LWCTile, float3 In_TraceStart, float3 In_TraceEnd, int In_CollisionGroup, out int Out_QueryID, out bool Out_IsQueryValid)`
- L95-114 _function_ `void NDIAsyncGpuTrace_ReadAsyncRayTrace(uint MaxRayTraceCount, StructuredBuffer<FNiagaraAsyncGpuTraceResult> IntersectionResults, uint IntersectionRestultsOffest, float3 In_LWCTile, int In_PreviousFrameQueryID, out bool Out_CollisionValid, out float Out_CollisionDistance, out float3 Out_CollisionPosWorld, out float3 Out_CollisionNormal)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceAsyncGpuTraceTemplate.ush` (Private)

- lines: 52; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (3)

- L5 _resource_ `RWStructuredBuffer<FNiagaraAsyncGpuTrace> {ParameterName}_RWRayRequests;`
- L7 _resource_ `StructuredBuffer<FNiagaraAsyncGpuTraceResult> {ParameterName}_IntersectionResults;`
- L9 _resource_ `RWBuffer<uint> {ParameterName}_RWRayTraceCounts;`

#### Global parameters (uniforms) (4)

- L4 _parameter_ `uint {ParameterName}_MaxRayTraceCount;` — Niagara ray tracing uses shared buffers between dispatches so each buffer has a buffer + and offset into that buffer for the current dispatch.
- L6 _parameter_ `uint {ParameterName}_RayRequestsOffset;`
- L8 _parameter_ `uint {ParameterName}_IntersectionResultsOffset;`
- L10 _parameter_ `uint {ParameterName}_RayTraceCountsOffset;`

#### Functions (4)

- L12-19 _function_ `void IssueAsyncRayTraceGpu_{ParameterName}_UEImpureCall(bool bExecute, int In_QueryID, float3 In_TraceStart, float3 In_TraceEnd, int In_CollisionGroup, out bool Out_IsQueryValid)`
- L21-29 _function_ `void ReserveAsyncRayTraceGpu_{ParameterName}_UEImpureCall(bool bExecute, int In_TraceCount, out int Out_StartQueryID, out bool Out_IndicesValid)`
- L31-39 _function_ `void CreateAsyncRayTraceGpu_{ParameterName}_UEImpureCall(bool bExecute, float3 In_TraceStart, float3 In_TraceEnd, int In_CollisionGroup, out int Out_QueryID, out bool Out_IsQueryValid)`
- L41-51 _function_ `void ReadAsyncRayTraceGpu_{ParameterName}(bool bExecute, int In_PreviousFrameQueryID, out bool Out_CollisionValid, out float Out_CollisionDistance, out float3 Out_CollisionPosWorld, out float3 Out_CollisionNormal)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceAudioCommon.ush` (Private)

- lines: 35; parse: all-branches
- L3 #pragma `once`

#### Functions (2)

- L5-18 _function_ `float SampleInterleavedFloatBuffer(Buffer<float> InBuffer, int ChannelCount, int ChannelResolution, float NormalizedPosition, int ChannelIndex)`
- L20-33 _function_ `float SamplePlanarFloatBuffer(Buffer<float> InBuffer, int ChannelCount, int ChannelResolution, float NormalizedPosition, int ChannelIndex)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceAudioOscilloscopeTemplate.ush` (Private)

- lines: 22; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L3 _resource_ `Buffer<float> {ParameterName}_OscilloscopeBuffer;`

#### Global parameters (uniforms) (2)

- L4 _parameter_ `int {ParameterName}_ChannelCount;`
- L5 _parameter_ `int {ParameterName}_Resolution;`

#### Functions (2)

- L7-15 _function_ `void SampleAudioBuffer_{ParameterName}(float In_NormalizedPosition, int In_ChannelIndex, out float Out_Val)`
- L17-20 _function_ `void GetAudioBufferNumChannels_{ParameterName}(out int Out_Val)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceAudioSpectrumTemplate.ush` (Private)

- lines: 21; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L3 _resource_ `Buffer<float> {ParameterName}_SpectrumBuffer;`

#### Global parameters (uniforms) (2)

- L4 _parameter_ `int {ParameterName}_ChannelCount;`
- L5 _parameter_ `int {ParameterName}_Resolution;`

#### Functions (2)

- L7-15 _function_ `void AudioSpectrum_{ParameterName}(float In_NormalizedPosition, int In_ChannelIndex, out float Out_Val)`
- L17-20 _function_ `void GetNumChannels_{ParameterName}(out int Out_Val)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceCamera.ush` (Private)

- lines: 93; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (1)

- L3 _parameter_ `int {ParameterName}_SplitscreenMode;`

#### Functions (9)

- L5-8 _function_ `void GetFieldOfView_{ParameterName}(out float Out_FieldOfViewAngle)`
- L10-13 _function_ `void GetSplitscreenInfo_{ParameterName}(out int Out_CurrentSplitscreenMode)`
- L15-19 _function_ `void GetTAAJitter_{ParameterName}(out float2 Out_CurrentJitter, out float2 Out_PreviousJitter)`
- L21-31 _function_ `void GetCameraPropertiesCPUASC47GPU_{ParameterName}(out float3 Out_CameraPositionWorld, out float3 Out_ViewForwardVector, out float3 Out_ViewUpVector, out float3 Out_ViewRightVector, out float2 Out_ViewportSize, out float Out_NearClipPlane)`
- L33-53 _function_ `void GetViewPropertiesGPU_{ParameterName}(out float3 Out_ViewPositionWorld, out float3 Out_ViewForwardVector, out float3 Out_ViewUpVector, out float3 Out_ViewRightVector, out float4 Out_ViewSizeAndInverseSize, out float4 Out_ScreenToViewSpace, out float2 Out_Current_TAAJitter, out float2 Out_Previous_TAAJitter, out float3 Out_PreViewTranslation, out float4 Out_BufferSizeAndInverseSize, out float2 Out_ViewportOffset, out float Out_NearPlane, out float2 Out_FOVCurrent, out float2 Out_FOVPrevious)`
- L55-66 _function_ `void GetClipSpaceTransformsGPU_{ParameterName}(out float4x4 Out_WorldToClipTransform, out float4x4 Out_TranslatedWorldToClipTransform, out float4x4 Out_ClipToWorldTransform, out float4x4 Out_ClipToViewTransform, out float4x4 Out_ClipToTranslatedWorldTransform, out float4x4 Out_ScreenToWorldTransform, out float4x4 Out_ScreenToTranslatedWorldTransform, out float4x4 Out_ClipToPreviousClipTransform)`
- L68-77 _function_ `void GetViewSpaceTransformsGPU_{ParameterName}(out float4x4 Out_TranslatedWorldToViewTransform, out float4x4 Out_ViewToTranslatedWorldTransform, out float4x4 Out_TranslatedWorldToCameraViewTransform, out float4x4 Out_CameraViewToTranslatedWorldTransform, out float4x4 Out_ViewToClipTransform, out float4x4 Out_ViewToClipNoAATransform)`
- L79-84 _function_ `void ApplyPreViewTranslationToPositionGPU_{ParameterName}(in float3 In_WorldPosition, out float4 Out_TranslatedPosition)`
- L86-92 _function_ `void RemovePreViewTranslationFromPositionGPU_{ParameterName}(in float4 In_TranslatedPosition, out float3 Out_WorldPosition)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceCollisionQuery.ush` (Private)

- lines: 223; parse: all-branches
- includes: L5 `/Engine/Private/Common.ush`, L6 `/Engine/Private/DeferredShadingCommon.ush`, L11 `/Engine/Public/SubstratePublic.ush`

#### Macros (#define, 4)

- L8 `#define NEEDS_SCENE_TEXTURES 1`
- L9 `#define SCENE_TEXTURES_DISABLED 0`
- L10 `#define SubstratePublicStruct SubstratePublic`
- L14 `#define NDICOLLISIONQUERY_USE_GBUFFER_NORMAL (FEATURE_LEVEL >= FEATURE_LEVEL_SM5) \|\| (MOBILE_DEFERRED_SHADING && !ALLOW_FRAMEBUFFER_FETCH)`
- L3 #pragma `once`

#### Functions (6)

- L16-23 _function_ `float NDICollisionQuery_GetCustomSceneDepth(float2 ScreenUV)`
- L25-32 _function_ `float NDICollisionQuery_GetScenePartialDepth(float2 ScreenUV)`
- L34-95 _function_ `void NDICollisionQuery_QuerySceneDepthGPU(in float3 In_SamplePos, in float3 In_LWCTile, out float Out_SceneDepth, out float3 Out_CameraPosWorld, out bool Out_IsInsideView, out float3 Out_WorldPos, out float3 Out_WorldNormal)`
- L97-153 _function_ `void NDICollisionQuery_QueryScenePartialDepthGPU(in float3 In_SamplePos, in float3 In_LWCTile, out float Out_SceneDepth, out float3 Out_CameraPosWorld, out bool Out_IsInsideView, out float3 Out_WorldPos, out float3 Out_WorldNormal)`
- L155-206 _function_ `void NDICollisionQuery_QueryCustomDepthGPU(in float3 In_SamplePos, in float3 In_LWCTile, out float Out_SceneDepth, out float3 Out_CameraPosWorld, out bool Out_IsInsideView, out float3 Out_WorldPos, out float3 Out_WorldNormal)`
- L208-222 _function_ `void NDICollisionQuery_QueryMeshDistanceFieldGPU(in float3 In_SamplePos, in float3 In_LWCTile, out float Out_DistanceToNearestSurface, out float3 Out_FieldGradient, out bool Out_IsDistanceFieldValid)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceCollisionQueryTemplate.ush` (Private)

- lines: 49; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Functions (8)

- L3-6 _function_ `void QuerySceneDepthGPU_{ParameterName}(in float3 In_SamplePos, out float Out_SceneDepth, out float3 Out_CameraPosWorld, out bool Out_IsInsideView, out float3 Out_WorldPos, out float3 Out_WorldNormal)`
- L8-11 _function_ `void QueryScenePartialDepthGPU_{ParameterName}(in float3 In_SamplePos, out float Out_SceneDepth, out float3 Out_CameraPosWorld, out bool Out_IsInsideView, out float3 Out_WorldPos, out float3 Out_WorldNormal)`
- L13-16 _function_ `void QueryCustomDepthGPU_{ParameterName}(in float3 In_SamplePos, out float Out_SceneDepth, out float3 Out_CameraPosWorld, out bool Out_IsInsideView, out float3 Out_WorldPos, out float3 Out_WorldNormal)`
- L18-21 _function_ `void QueryMeshDistanceFieldGPU_{ParameterName}(in float3 In_SamplePos, out float Out_DistanceToNearestSurface, out float3 Out_FieldGradient, out bool Out_IsDistanceFieldValid)`
- L24-27 _function_ `void IssueAsyncRayTraceGpu_{ParameterName}_UEImpureCall(int In_QueryID, float3 In_TraceStart, float3 In_TraceEnd, int In_TraceChannel, out bool Out_IsQueryValid)` — DEPRECATE_BEGIN
- L29-33 _function_ `void ReserveRayTraceIndex_{ParameterName}_UEImpureCall(int In_TraceCount, out int Out_StartQueryID, out bool Out_IndicesValid)`
- L35-39 _function_ `void CreateAsyncRayTraceGpu_{ParameterName}_UEImpureCall(float3 In_TraceStart, float3 In_TraceEnd, int In_TraceChannel, out int Out_QueryID, out bool Out_IsQueryValid)`
- L41-47 _function_ `void ReadAsyncRayTraceGpu_{ParameterName}(int In_PreviousFrameQueryID, out bool Out_CollisionValid, out float Out_CollisionDistance, out float3 Out_CollisionPosWorld, out float3 Out_CollisionNormal)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceCubeTextureTemplate.ush` (Private)

- lines: 17; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (2)

- L4 _resource_ `TextureCube {ParameterName}_Texture;`
- L5 _resource_ `SamplerState {ParameterName}_TextureSampler;`

#### Global parameters (uniforms) (1)

- L3 _parameter_ `int2 {ParameterName}_TextureSize;`

#### Functions (2)

- L7-10 _function_ `void SampleCubeTexture_{ParameterName}(in float3 UVW, in float MipLevel, out float4 OutValue)`
- L12-16 _function_ `void TextureDimensions_{ParameterName}(out int OutWidth, out int OutHeight)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceCurveTemplate.ush` (Private)

- lines: 60; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L8 _resource_ `Buffer<float> {ParameterName}_CurveLUT;`

#### Global parameters (uniforms) (5)

- L3 _parameter_ `float {ParameterName}_MinTime;`
- L4 _parameter_ `float {ParameterName}_MaxTime;`
- L5 _parameter_ `float {ParameterName}_InvTimeRange;`
- L6 _parameter_ `uint {ParameterName}_CurveLUTNumMinusOne;`
- L7 _parameter_ `uint {ParameterName}_LUTOffset;`

#### Functions (4)

- L10-16 _function_ `void GetCurveLUTIndices_{ParameterName}(float Time, out uint IndexA, out uint IndexB, out float Fraction)`
- L18-25 _function_ `float SampleCurveLUT_{ParameterName}(uint index)`
- L28-42 _function_ `void {CurveSampleFunctionName}_{ParameterName}(float Time, out float Value)` _[#if {NumElements} == 1]_
- L44-58 _function_ `void {CurveSampleFunctionName}_{ParameterName}(float Time, out float{NumElements} Value)` _[#if !({NumElements} == 1)]_

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceDataTableTemplate.ush` (Private)

- lines: 61; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `ByteAddressBuffer {ParameterName}_TableDataBuffer;`
- L8 _resource_ `Buffer<uint> {ParameterName}_FilteredRowDataOffsetBuffer;`

#### Global parameters (uniforms) (4)

- L3 _parameter_ `int {ParameterName}_NumRows;`
- L4 _parameter_ `uint {ParameterName}_RowStride;`
- L5 _parameter_ `uint {ParameterName}_InvalidRowReadOffset;`
- L6 _parameter_ `int {ParameterName}_NumFilteredRows;`

#### Functions (12)

- L11-15 _function_ `uint GetReadOffset_{ParameterName}(uint RowOffset, uint Column)`
- L17 _function_ `void ReadValue_{ParameterName}(uint RowOffset, uint Column, out bool Value)`
- L18 _function_ `void ReadValue_{ParameterName}(uint RowOffset, uint Column, out int Value)`
- L19 _function_ `void ReadValue_{ParameterName}(uint RowOffset, uint Column, out float Value)`
- L20 _function_ `void ReadValue_{ParameterName}(uint RowOffset, uint Column, out float2 Value)`
- L21 _function_ `void ReadValue_{ParameterName}(uint RowOffset, uint Column, out float3 Value)`
- L22 _function_ `void ReadValue_{ParameterName}(uint RowOffset, uint Column, out float4 Value)`
- L24-30 _function_ `uint GetFilteredRowReadOffset_{ParameterName}(int RowIndex, out bool bIsValid)`
- L32-36 _function_ `uint GetRowReadOffset_{ParameterName}(int RowIndex, out bool bIsValid)`
- L38-41 _function_ `void IsValid_{ParameterName}(out bool bIsValid)`
- L43-46 _function_ `void GetNumRows_{ParameterName}(out int OutNumRows)`
- L48-51 _function_ `void GetNumFilteredRows_{ParameterName}(out int OutNumRows)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceDebugDraw.ush` (Private)

- lines: 515; parse: all-branches
- includes: L5 `NiagaraCommon.ush`, L6 `NiagaraQuaternionUtils.ush`, L7 `NiagaraDebugDraw.ush`

#### Macros (#define, 11)

- L504 `#define MakeDrawBoxPersistent(NAME) void NAME(float3 Center, int CenterCoordinateSpace, float3 Offset, int OffsetCoordinateSpace, float3 Extents, bool HalfExtents, float3 RotationAxis, float RotationNormalizedAngle, int RotationCoordina ...`
- L505 `#define MakeDrawCirclePersistent(NAME) void NAME(float3 Center, int CenterCoordinateSpace, float3 Offset, int OffsetCoordinateSpace, float Radius, float3 XAxis, float3 YAxis, int AxisCoordinateSpace, int NumSegments, float4 Color) {}`
- L506 `#define MakeDrawConePersistent(NAME) void NAME(float3 Center, int CenterCoordinateSpace, float3 Offset, int OffsetCoordinateSpace, float Angle, float Length, float3 OrientationAxis, int OrientationAxisCoordinateSpace, float3 NonUniformSc ...`
- L507 `#define MakeDrawCoordinateSystemPersistent(NAME) void NAME(float3 Center, int CenterCoordinateSpace, float3 OffsetFromCenter, int OffsetCoordinateSpace, float4 Rotation, int RotationCoordinateSpace, float Scale) {}`
- L508 `#define MakeDrawCylinderPersistent(NAME) void NAME(float3 Center, int CenterCoordinateSpace, float3 Offset, int OffsetCoordinateSpace, float Radius, float Height, bool IsHalfHeight, bool HemisphereX, bool HemisphereY, int OrientationAxis, in ...`
- L509 `#define MakeDrawGrid2DPersistent(NAME) void NAME(float3 Center, int CenterCoordinateSpace, float3 OffsetFromCenter, int OffsetCoordinateSpace, float4 Rotation, int RotationCoordinateSpace, float2 Extents, int NumCellsX, int NumCellsY, floa ...`
- L510 `#define MakeDrawGrid3DPersistent(NAME) void NAME(float3 Center, int CenterCoordinateSpace, float3 OffsetFromCenter, int OffsetCoordinateSpace, float4 Rotation, int RotationCoordinateSpace, float3 Extents, int NumCellsX, int NumCellsY, int  ...`
- L511 `#define MakeDrawLinePersistent(NAME) void NAME(float3 StartLocation, int StartLocationCoordinateSpace, float3 EndLocation, int EndLocationCoordinateSpace, float4 Color) {}`
- L512 `#define MakeDrawRectanglePersistent(NAME) void NAME(float3 Center, int CenterCoordinateSpace, float3 Offset, int OffsetCoordinateSpace, float2 Extents, bool HalfExtents, float3 XAxis, float3 YAxis, int AxisVectorsCoordinateSpace, int NumXSegm ...`
- L513 `#define MakeDrawSpherePersistent(NAME) void NAME(float3 Center, int CenterCoordinateSpace, float3 OffsetFromCenter, int OffsetCoordinateSpace, float Radius, int RadiusCoordinateSpace, bool HemisphereX, bool HemisphereY, bool HemisphereZ, f ...`
- L514 `#define MakeDrawTorusPersistent(NAME) void NAME(float3 Center, int CenterCoordinateSpace, float3 OffsetFromCenter, int OffsetCoordinateSpace, float MajorRadius, float MinorRadius, float3 OrientationAxis, int OrientationAxisCoordinateSpace ...`
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (2)

- L9 _resource_ `RWBuffer<uint> RWNDIDebugDrawArgs;`
- L10 _resource_ `RWBuffer<uint> RWNDIDebugDrawLineVertex;`

#### Global parameters (uniforms) (1)

- L11 _parameter_ `uint NDIDebugDrawLineMaxInstances;`

#### Functions (11)

- L13-56 _function_ `void NDIDebugDraw_DrawBox(bool bDraw, float3 Location, float4 Rotation, float3 Extents, float4 Color)`
- L58-89 _function_ `void NDIDebugDraw_Circle(bool bDraw, float3 Location, float3 XAxis, float3 YAxis, float Scale, int Segments, float4 Color)`
- L91-137 _function_ `void NDIDebugDraw_DrawRectangle(bool bDraw, float3 Location, float3 XAxis, float3 YAxis, float2 Extents, int SegmentsX, int SegmentsY, float4 Color, bool bUnbounded)`
- L139-160 _function_ `void NDIDebugDraw_CoordinateSystem(bool bDraw, float3 Location, float4 Rotation, float Scale)`
- L162-196 _function_ `void NDIDebugDraw_Grid2D(bool bDraw, float3 Center, float4 Rotation, float2 Extents, int2 NumCells, float4 Color)`
- L198-243 _function_ `void NDIDebugDraw_Grid3D(bool bDraw, float3 Center, float4 Rotation, float3 Extents, int3 NumCells, float4 Color)`
- L245-261 _function_ `void NDIDebugDraw_Line(bool bDraw, float3 LineStart, float3 LineEnd, float4 Color)`
- L263-315 _function_ `void NDIDebugDraw_Sphere(bool bDraw, float3 Location, float Radius, int Segments, float4 Color)`
- L318-379 _function_ `void NDIDebugDraw_Cylinder(bool bDraw, float3 Location, float3 Axis, float Height, float Radius, int NumHeightSegments, int NumRadiusSegments, float4 Color)`
- L381-434 _function_ `void NDIDebugDraw_Cone(bool bDraw, float3 Location, float3 Axis, float Height, float RadiusTop, float RadiusBottom, int NumHeightSegments, int NumRadiusSegments, float4 Color)`
- L436-501 _function_ `void NDIDebugDraw_Torus(bool bDraw, float3 Location, float3 Axis, float MajorRadius, float MinorRadius, float MajorRadiusSegments, float MinorRadiusSegments, float4 Color)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceDebugDrawTemplate.ush` (Private)

- lines: 58; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Functions (11)

- L3-6 _function_ `void DrawLine_{ParameterName}_UEImpureCall(bool bExecute, float3 LineStart, float3 LineEnd, float4 Color)`
- L8-11 _function_ `void DrawRectangle_{ParameterName}_UEImpureCall(bool bExecute, float3 Location, float3 XAxis, float3 YAxis, float2 Extents, int NumXSegments, int NumYSegments, float4 Color, bool bUnbounded)`
- L14-17 _function_ `void DrawCircle_{ParameterName}_UEImpureCall(bool bExecute, float3 Location, float3 XAxis, float3 YAxis, float Scale, int Segments, float4 Color)`
- L19-22 _function_ `void DrawBox_{ParameterName}_UEImpureCall(bool bExecute, float3 Location, float4 Rotation, float3 Extents, float4 Color)`
- L24-27 _function_ `void DrawSphere_{ParameterName}_UEImpureCall(bool bExecute, float3 LineStart, float Radius, int Segments, float4 Color)`
- L29-32 _function_ `void DrawCylinder_{ParameterName}_UEImpureCall(bool bExecute, float3 Location, float3 Axis, float Height, float Radius, int NumHeightSegments, int NumRadiusSegments, float4 Color)`
- L34-37 _function_ `void DrawCone_{ParameterName}_UEImpureCall(bool bExecute, float3 Location, float3 Axis, float Height, float RadiusTop, float RadiusBottom, int NumHeightSegments, int NumRadiusSegments, float4 Color)`
- L39-42 _function_ `void DrawTorus_{ParameterName}_UEImpureCall(bool bExecute, float3 Location, float3 Axis, float MajorRadius, float MinorRadius, int MajorRadiusSegments, int MinorRadiusSegments, float4 Color)`
- L44-47 _function_ `void DrawCoordinateSystem_{ParameterName}_UEImpureCall(bool bExecute, float3 Location, float4 Rotation, float Scale)`
- L49-52 _function_ `void DrawGrid2D_{ParameterName}_UEImpureCall(bool bExecute, float3 Center, float4 Rotation, float2 Extents, int NumCellsX, int NumCellsY, float4 Color)`
- L54-57 _function_ `void DrawGrid3D_{ParameterName}_UEImpureCall(bool bExecute, float3 Center, float4 Rotation, float3 Extents, int NumCellsX, int NumCellsY, int NumCellsZ, float4 Color)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceDynamicMeshTemplate.ush` (Private)

- lines: 396; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (3)

- L13 _resource_ `RWBuffer<uint> {ParameterName}_SectionBuffer;`
- L14 _resource_ `RWBuffer<uint> {ParameterName}_IndexBuffer;`
- L15 _resource_ `RWBuffer<uint> {ParameterName}_VertexBuffer;`

#### Global parameters (uniforms) (8)

- L3 _parameter_ `uint {ParameterName}_NumSections;`
- L4 _parameter_ `uint {ParameterName}_NumTriangles;`
- L5 _parameter_ `uint {ParameterName}_NumVertices;`
- L6 _parameter_ `uint {ParameterName}_NumTexCoords;`
- L8 _parameter_ `uint {ParameterName}_PositionOffset;`
- L9 _parameter_ `uint {ParameterName}_TangentBasisOffset;`
- L10 _parameter_ `uint {ParameterName}_TexCoordOffset;`
- L11 _parameter_ `uint {ParameterName}_ColorOffset;`

#### Functions (30)

- L19 _function_ `uint {ParameterName}_GetPositionOffsetUnsafe(int Vertex)` — Helper functions
- L20 _function_ `uint {ParameterName}_GetTangentBasisOffsetUnsafe(int Vertex)`
- L21 _function_ `uint {ParameterName}_GetTexCoordOffsetUnsafe(int Vertex, int TexCoord)`
- L22 _function_ `uint {ParameterName}_GetColorOffsetUnsafe(int Vertex)`
- L24-27 _function_ `uint {ParameterName}_GetPositionOffset(int Vertex)`
- L29-32 _function_ `uint {ParameterName}_GetTangentBasisOffset(int Vertex)`
- L34-37 _function_ `uint {ParameterName}_GetTexCoordOffset(int Vertex, int TexCoord)`
- L39-42 _function_ `uint {ParameterName}_GetColorOffset(int Vertex)`
- L44-52 _function_ `float4 {ParameterName}_UnpackTangent(uint Packed)`
- L54-62 _function_ `uint {ParameterName}_PackTangent(float3 Tangent, uint TangentSign)`
- L64-73 _function_ `float4 {ParameterName}_UnpackColor(uint Packed)`
- L75-86 _function_ `uint {ParameterName}_PackColor(float4 Color)`
- L88-94 _function_ `void {ParameterName}_SetVertexPositionUnsafe(int Vertex, float3 Position)`
- L96-102 _function_ `void {ParameterName}_SetVertexTangentBasisUnsafe(int Vertex, float3 TangentX, float3 TangentY, float3 TangentZ)`
- L104-109 _function_ `void {ParameterName}_SetVertexTexCoordUnsafe(int Vertex, float2 TexCoord, int TexCoordIndex)`
- L111-115 _function_ `void {ParameterName}_SetVertexColorUnsafe(int Vertex, float4 Color)`
- L119-141 _function_ `void AllocateSectionTriangles_{ParameterName}_UEImpureCall(bool bExecute, int SectionIndex, int NumTriangles, out int TriangleIndex, out int NumAllocated)` — Mutable Functions
- L143-156 _function_ `void SetTriangleVertices_{ParameterName}_UEImpureCall(in bool bExecute, in int TriangleIndex, in int Index0, in int Index1, in int Index2)`
- L158-172 _function_ `void SetVertexPosition_{ParameterName}_UEImpureCall(in bool bExecute, in int Vertex, in float3 Position)`
- L174-188 _function_ `void SetVertexTangentBasis_{ParameterName}_UEImpureCall(in bool bExecute, in int Vertex, in float3 TangentX, in float3 TangentY, in float3 TangentZ)`
- L190-203 _function_ `void SetVertexTexCoord_{ParameterName}_UEImpureCall(in bool bExecute, in int Vertex, in int TexCoordIndex, in float2 TexCoord)`
- L205-217 _function_ `void SetVertexColor_{ParameterName}_UEImpureCall(in bool bExecute, in int Vertex, in float4 Color)`
- L219-234 _function_ `void SetVertexData_{ParameterName}_UEImpureCall(in bool bExecute, in int Vertex, in float3 Position, in float3 TangentX, in float3 TangentY, in float3 TangentZ, in float2 TexCoord, in float4 Color)`
- L236-286 _function_ `void AppendTriangle_{ParameterName}_UEImpureCall( in bool bExecute, in int SectionIndex, in float3 Position0, in float3 TangentX0, in float3 TangentY0, in float3 TangentZ0, in float2 TexCoord0, in float4 Color0, in float3 Position1, in float3 TangentX1, in float3 TangentY1, in float3 TangentZ1, in float2 TexCoord1, in float4 Color1, in float3 Position2, in float3 TangentX2, in float3 TangentY2, in float3 TangentZ2, in float2 TexCoord2, in float4 Color2, out int TriangleIndex )`
- L291-307 _function_ `void GetTriangleVertices_{ParameterName}(in int TriangleIndex, out bool bValid, out int Index0, out int Index1, out int Index2)`
- L309-324 _function_ `void GetVertexPosition_{ParameterName}(in int Vertex, out bool bValid, out float3 Position)`
- L326-347 _function_ `void GetVertexTangentBasis_{ParameterName}(in int Vertex, out bool bValid, out float3 OutTangentX, out float3 OutTangentY, out float3 OutTangentZ)`
- L349-363 _function_ `void GetVertexTexCoord_{ParameterName}(in int Vertex, in int TexCoordIndex, out bool bValid, out float2 TexCoord)`
- L365-378 _function_ `void GetVertexColor_{ParameterName}(in int Vertex, out bool bValid, out float4 Color)`
- L380-395 _function_ `void GetVertexData_{ParameterName}(in int Vertex, out bool bValid, out float3 Position, out float3 TangentX, out float3 TangentY, out float3 TangentZ, out float2 TexCoord, out float4 Color)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceEmitterPropertiesTemplate.ush` (Private)

- lines: 30; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (7)

- L3 _parameter_ `uint {ParameterName}_LocalSpace;`
- L4 _parameter_ `uint {ParameterName}_BoundsValid;`
- L5 _parameter_ `float3 {ParameterName}_BoundsMin;`
- L6 _parameter_ `float3 {ParameterName}_BoundsMax;`
- L7 _parameter_ `uint {ParameterName}_FixedBoundsValid;`
- L8 _parameter_ `float3 {ParameterName}_FixedBoundsMin;`
- L9 _parameter_ `float3 {ParameterName}_FixedBoundsMax;`

#### Functions (3)

- L11-14 _function_ `void GetLocalSpace_{ParameterName}(out bool bLocalSpace)`
- L16-22 _function_ `void GetBounds_{ParameterName}(out bool bValid, out float3 Min, out float3 Max)`
- L24-29 _function_ `void GetFixedBounds_{ParameterName}(out bool bValid, out float3 Min, out float3 Max)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceExportTemplate.ush` (Private)

- lines: 36; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L4 _resource_ `RWBuffer<uint> {ParameterName}_RWWriteBuffer;`

#### Global parameters (uniforms) (1)

- L3 _parameter_ `uint {ParameterName}_WriteBufferSize;`

#### Functions (2)

- L6-30 _function_ `void ExportParticleData_{ParameterName}_UEImpureCall(in bool bStoreData, in float3 Position, in float Size, in float3 Velocity, out bool bSuccess)`
- L32-35 _function_ `void StoreParticleData_{ParameterName}_UEImpureCall(in bool bStoreData, in float3 Position, in float Size, in float3 Velocity, out bool bSuccess)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceGBufferTemplate.ush` (Private)

- lines: 338; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Engine/Private/DeferredShadingCommon.ush`, L16 `/Engine/Public/SubstratePublic.ush` [NIAGARA_SAMPLE_SUBSTRATE]

#### Macros (#define, 7)

- L6 `#define NDIGBUFFER_HAS_GBUFFER (FEATURE_LEVEL >= FEATURE_LEVEL_SM5) \|\| (MOBILE_DEFERRED_SHADING && !ALLOW_FRAMEBUFFER_FETCH)`
- L7 `#define NDIGBUFFER_USE_GBUFFER_VELOCITY (false && NDIGBUFFER_HAS_GBUFFER)`
- L8 `#define NDIGBUFFER_IS_MOBILE (FEATURE_LEVEL <= FEATURE_LEVEL_ES3_1)`
- L10 `#define NIAGARA_SAMPLE_SUBSTRATE (SUBSTRATE_GBUFFER_FORMAT==1 && !NDIGBUFFER_IS_MOBILE)`
- L13 `#define NEEDS_SCENE_TEXTURES 1` _[#if NIAGARA_SAMPLE_SUBSTRATE]_
- L14 `#define SCENE_TEXTURES_DISABLED 0` _[#if NIAGARA_SAMPLE_SUBSTRATE]_
- L15 `#define SubstratePublicStruct SubstratePublic` _[#if NIAGARA_SAMPLE_SUBSTRATE]_

#### Global resources (textures / buffers / samplers) (2)

- L21 _resource_ `Texture2D {ParameterName}_VelocityTexture;`
- L22 _resource_ `SamplerState {ParameterName}_VelocityTextureSampler;`

#### Functions (17)

- L25-29 _function_ `FSubstrateGBuffer GetNiagaraSubstrateGBuffer_{ParameterName}(in float2 ScreenUV)` _[#if NIAGARA_SAMPLE_SUBSTRATE]_
- L32-39 _function_ `float2 ApplyViewportOffset_{ParameterName}(float2 UV, bool bApplyViewportOffset)`
- L41-58 _function_ `void DecodeDiffuseColor_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float3 OutValue)`
- L60-77 _function_ `void DecodeWorldNormal_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float3 OutValue)`
- L79-101 _function_ `void DecodeScreenVelocity_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float3 OutValue)`
- L103-140 _function_ `void DecodeWorldVelocity_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float3 OutValue)`
- L142-159 _function_ `void DecodeBaseColor_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float3 OutValue)`
- L161-178 _function_ `void DecodeMetallic_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float OutValue)`
- L180-197 _function_ `void DecodeSpecular_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float OutValue)`
- L199-217 _function_ `void DecodeRoughness_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float OutValue)`
- L219-233 _function_ `void DecodeDepth_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float OutValue)`
- L237-250 _function_ `void DecodeStencil_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out int OutValue)` — This has not been tested yet _[#if 0]_
- L253-267 _function_ `void DecodePartialDepth_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float OutValue)`
- L270-284 _function_ `void DecodeCustomDepth_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float OutValue)`
- L286-300 _function_ `void DecodeCustomStencil_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out int OutValue)`
- L302-318 _function_ `void DecodeSceneColor_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out float4 OutValue)`
- L320-337 _function_ `void DecodeShadingModelID_{ParameterName}(in float2 ScreenUV, in bool bApplyViewportOffset, out bool IsValid, out int OutValue)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceGrid2DCollection.ush` (Private)

- lines: 137; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Functions (5)

- L6-26 _function_ `float Monotonic1DCubic_{ParameterName}(float fm1, float f0, float f1, float f2, float t)` — cubic interpolation between values. note f0 = function at t=0 f1 = function at t=1
- L28-40 _function_ `float Basic1DCubic_{ParameterName}(float fm1, float f0, float f1, float f2, float t)`
- L42-86 _function_ `float Basic2DCubic_{ParameterName}(SamplerState Sampler, float3 UVW, int MipLevel)`
- L88-132 _function_ `float Monotonic2DCubic_{ParameterName}(SamplerState Sampler, float3 UVW, int MipLevel)`
- L134-137 _function_ `float SampleBiCubic_{ParameterName}(SamplerState Sampler, float3 UVW, int MipLevel)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceGrid3DCollection.ush` (Private)

- lines: 116; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Functions (1)

- L35-116 _function_ `float{NumChannels} SampleTriCubicLagrange_{ParameterName}(SamplerState Sampler, float3 UVW, int MipLevel)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceIntRenderTarget2D.ush` (Private)

- lines: 100; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L4 _resource_ `RWTexture2D<int> {ParameterName}_RWTextureUAV;`

#### Global parameters (uniforms) (1)

- L3 _parameter_ `float4 {ParameterName}_TextureSizeAndInvSize;`

#### Functions (11)

- L6-9 _function_ `void GetValue_{ParameterName}(int X, int Y, out int CurrValue)`
- L11-17 _function_ `void SetValue_{ParameterName}_UEImpureCall(in bool bExecute, int X, int Y, int Value)`
- L19-31 _function_ `void AtomicAdd_{ParameterName}_UEImpureCall(in bool bExecute, int X, int Y, int Amount, out int CurrValue, out int PrevValue)`
- L33-43 _function_ `void AtomicCompareAndExchange_{ParameterName}_UEImpureCall(in bool bExecute, int X, int Y, int ComparisonValue, int Value, out int OriginalValue)`
- L45-57 _function_ `void AtomicMax_{ParameterName}_UEImpureCall(in bool bExecute, int X, int Y, int InValue, out int CurrValue, out int PrevValue)`
- L59-71 _function_ `void AtomicMin_{ParameterName}_UEImpureCall(in bool bExecute, int X, int Y, int InValue, out int CurrValue, out int PrevValue)`
- L73-77 _function_ `void GetRenderTargetSize_{ParameterName}(out int Width, out int Height)`
- L79-83 _function_ `void LinearToIndex_{ParameterName}(int Linear, out int X, out int Y)`
- L85-89 _function_ `void LinearToUV_{ParameterName}(int Linear, out float2 UV)`
- L91-94 _function_ `void ExecToIndex_{ParameterName}(out int X, out int Y)`
- L96-99 _function_ `void ExecToUV_{ParameterName}(out float2 UV)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceLandscape.ush` (Private)

- lines: 313; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L7 `/Engine/Private/VirtualTextureCommon.ush`, L8 `/Engine/Private/Landscape/LandscapeCommon.ush`

#### Macros (#define, 4)

- L4 `#define NUM_VIRTUALTEXTURE_SAMPLES 1` _[#if !defined(NUM_VIRTUALTEXTURE_SAMPLES)]_
- L11 `#define VIRTUAL_TEXTURE_UNPACK_NORMAL_NONE 0`
- L12 `#define VIRTUAL_TEXTURE_UNPACK_NORMAL_BC3BC3 1`
- L13 `#define VIRTUAL_TEXTURE_UNPACK_NORMAL_BC5BC1 2`
- L310 #undef `VIRTUAL_TEXTURE_UNPACK_NORMAL_NONE`; L311 #undef `VIRTUAL_TEXTURE_UNPACK_NORMAL_BC3BC3`; L312 #undef `VIRTUAL_TEXTURE_UNPACK_NORMAL_BC5BC1`

#### Global resources (textures / buffers / samplers) (15)

- L15 _resource_ `Texture2D {ParameterName}_BaseColorVirtualTexture;`
- L16 _resource_ `Texture2D<uint4> {ParameterName}_BaseColorVirtualTexturePageTable;`
- L17 _resource_ `SamplerState {ParameterName}_BaseColorVirtualTextureSampler;`
- L26 _resource_ `Texture2D {ParameterName}_HeightVirtualTexture;`
- L27 _resource_ `Texture2D<uint4> {ParameterName}_HeightVirtualTexturePageTable;`
- L28 _resource_ `SamplerState {ParameterName}_HeightVirtualTextureSampler;`
- L35 _resource_ `Texture2D {ParameterName}_NormalVirtualTexture0;`
- L36 _resource_ `Texture2D {ParameterName}_NormalVirtualTexture1;`
- L37 _resource_ `Texture2D<uint4> {ParameterName}_NormalVirtualTexturePageTable;`
- L38 _resource_ `SamplerState {ParameterName}_NormalVirtualTexture0Sampler;`
- L39 _resource_ `SamplerState {ParameterName}_NormalVirtualTexture1Sampler;`
- L48 _resource_ `Texture2D {ParameterName}_CachedHeightTexture;`
- L49 _resource_ `SamplerState {ParameterName}_CachedHeightTextureSampler;`
- L57 _resource_ `SamplerState {ParameterName}_PointClampedSampler;`
- L58 _resource_ `Texture2D<uint> {ParameterName}_CachedPhysMatTexture;`

#### Global parameters (uniforms) (30)

- L18 _parameter_ `float3 {ParameterName}_BaseColorVirtualTextureLWCTile;`
- L19 _parameter_ `float4x4 {ParameterName}_BaseColorVirtualTextureWorldToUvTransform;`
- L20 _parameter_ `uint {ParameterName}_BaseColorVirtualTextureUnpackSRGB;`
- L21 _parameter_ `uint {ParameterName}_BaseColorVirtualTextureUnpackYCoCg;`
- L22 _parameter_ `uint {ParameterName}_BaseColorVirtualTextureEnabled;`
- L23 _parameter_ `uint4 {ParameterName}_BaseColorVirtualTexturePackedUniform0;`
- L24 _parameter_ `uint4 {ParameterName}_BaseColorVirtualTexturePackedUniform1;`
- L25 _parameter_ `uint4 {ParameterName}_BaseColorVirtualTextureUniforms;`
- L29 _parameter_ `float3 {ParameterName}_HeightVirtualTextureLWCTile;`
- L30 _parameter_ `float4x4 {ParameterName}_HeightVirtualTextureWorldToUvTransform;`
- L31 _parameter_ `uint {ParameterName}_HeightVirtualTextureEnabled;`
- L32 _parameter_ `uint4 {ParameterName}_HeightVirtualTexturePackedUniform0;`
- L33 _parameter_ `uint4 {ParameterName}_HeightVirtualTexturePackedUniform1;`
- L34 _parameter_ `uint4 {ParameterName}_HeightVirtualTextureUniforms;`
- L40 _parameter_ `float3 {ParameterName}_NormalVirtualTextureLWCTile;`
- L41 _parameter_ `float4x4 {ParameterName}_NormalVirtualTextureWorldToUvTransform;`
- L42 _parameter_ `uint4 {ParameterName}_NormalVirtualTexturePackedUniform0;`
- L43 _parameter_ `uint4 {ParameterName}_NormalVirtualTexturePackedUniform1;`
- L44 _parameter_ `uint4 {ParameterName}_NormalVirtualTextureUniforms0;`
- L45 _parameter_ `uint4 {ParameterName}_NormalVirtualTextureUniforms1;`
- L46 _parameter_ `int {ParameterName}_NormalVirtualTextureUnpackMode;`
- L47 _parameter_ `uint {ParameterName}_NormalVirtualTextureEnabled;`
- L50 _parameter_ `uint {ParameterName}_CachedHeightTextureEnabled;`
- L51 _parameter_ `float3 {ParameterName}_CachedHeightTextureLWCTile;`
- L52 _parameter_ `float4x4 {ParameterName}_CachedHeightTextureWorldToUvTransform;`
- L53 _parameter_ `float4x4 {ParameterName}_CachedHeightTextureUvToWorldTransform;`
- L54 _parameter_ `float4 {ParameterName}_CachedHeightTextureUvScaleBias;`
- L55 _parameter_ `float2 {ParameterName}_CachedHeightTextureWorldGridSize;`
- L56 _parameter_ `int2 {ParameterName}_CachedHeightTextureDimension;`
- L59 _parameter_ `int2 {ParameterName}_CachedPhysMatTextureDimension;`

#### Functions (5)

- L61-70 _function_ `float2 GetCachedHeightTextureUv_{ParameterName}(float3 InWorldPos)`
- L72-118 _function_ `void GetBaseColor_{ParameterName}(float3 InWorldPos, out float3 OutBaseColor, out bool OutIsValid)`
- L120-163 _function_ `void GetHeight_{ParameterName}(float3 InWorldPos, out float OutHeight, out bool OutIsValid)`
- L165-290 _function_ `void GetWorldNormal_{ParameterName}(float3 InWorldPos, out float3 OutNormal, out bool OutIsValid)`
- L292-308 _function_ `void GetPhysicalMaterialIndex_{ParameterName}(float3 InWorldPos, out int OutIndex, out bool OutIsValid)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceMemoryBufferTemplate.ush` (Private)

- lines: 231; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L4 _resource_ `RWByteAddressBuffer {ParameterName}_Buffer;`

#### Global parameters (uniforms) (1)

- L3 _parameter_ `int {ParameterName}_NumElements;`

#### Functions (25)

- L8-13 _function_ `bool ValidateOffset_{ParameterName}(inout int ElementOffset, int Size)` — Helper functions
- L17-20 _function_ `void GetNumElements_{ParameterName}(out int NumElements)` — Misc Functions
- L24-29 _function_ `void LoadInt_{ParameterName}(int ElementOffset, out bool bValid, out int OutValue)` — Load operations
- L31-37 _function_ `void LoadInt2_{ParameterName}(int ElementOffset, out bool bValid, out int OutValue0, out int OutValue1)`
- L39-46 _function_ `void LoadInt3_{ParameterName}(int ElementOffset, out bool bValid, out int OutValue0, out int OutValue1, out int OutValue2)`
- L48-56 _function_ `void LoadInt4_{ParameterName}(int ElementOffset, out bool bValid, out int OutValue0, out int OutValue1, out int OutValue2, out int OutValue3)`
- L58-63 _function_ `void LoadFloat_{ParameterName}(int ElementOffset, out bool bValid, out float OutValue)`
- L65-70 _function_ `void LoadFloat2_{ParameterName}(int ElementOffset, out bool bValid, out float2 OutValue)`
- L72-77 _function_ `void LoadFloat3_{ParameterName}(int ElementOffset, out bool bValid, out float3 OutValue)`
- L79-84 _function_ `void LoadFloat4_{ParameterName}(int ElementOffset, out bool bValid, out float4 OutValue)`
- L88-95 _function_ `void StoreInt_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, int Value, out bool bSuccess)` — Store operations
- L97-104 _function_ `void StoreInt2_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, int Value0, int Value1, out bool bSuccess)`
- L106-113 _function_ `void StoreInt3_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, int Value0, int Value1, int Value2, out bool bSuccess)`
- L115-122 _function_ `void StoreInt4_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, int Value0, int Value1, int Value2, int Value3, out bool bSuccess)`
- L124-131 _function_ `void StoreFloat_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, float Value, out bool bSuccess)`
- L133-140 _function_ `void StoreFloat2_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, float2 Value, out bool bSuccess)`
- L142-149 _function_ `void StoreFloat3_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, float3 Value, out bool bSuccess)`
- L151-158 _function_ `void StoreFloat4_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, float4 Value, out bool bSuccess)`
- L162-170 _function_ `void AtomicAdd_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, int Value, out int PreviousValue, out int CurrentValue)` — Atomic Ops
- L172-180 _function_ `void AtomicAnd_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, int Value, out int PreviousValue, out int CurrentValue)`
- L182-190 _function_ `void AtomicCompareAndExchange_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, int Value, int Comperand, out int PreviousValue, out int CurrentValue)`
- L192-200 _function_ `void AtomicMax_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, int Value, out int PreviousValue, out int CurrentValue)`
- L202-210 _function_ `void AtomicMin_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, int Value, out int PreviousValue, out int CurrentValue)`
- L212-220 _function_ `void AtomicOr_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, int Value, out int PreviousValue, out int CurrentValue)`
- L222-230 _function_ `void AtomicXor_{ParameterName}_UEImpureCall(bool bExecute, int ElementOffset, int Value, out int PreviousValue, out int CurrentValue)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceMeshRendererInfoTemplate.ush` (Private)

- lines: 41; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Buffer<float> {ParameterName}_MeshDataBuffer;`

#### Global parameters (uniforms) (3)

- L3 _parameter_ `uint {ParameterName}_bSubImageBlend;`
- L4 _parameter_ `float2 {ParameterName}_SubImageSize;`
- L5 _parameter_ `uint {ParameterName}_NumMeshes;`

#### Functions (3)

- L8-11 _function_ `void GetNumMeshes_{ParameterName}(out int OutNumMeshes)`
- L13-34 _function_ `void GetMeshLocalBounds_{ParameterName}(int MeshIndex, out float3 OutMinBounds, out float3 OutMaxBounds, out float3 OutSize)`
- L36-40 _function_ `void GetSubUVDetails_{ParameterName}(out bool bBlendEnabled, out float2 SubImageSize)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceNeighborQuery.ush` (Private)

- lines: 258; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Macros (#define, 4)

- L23 `#define NEIGHBORQUERY_INVALID_CELL 0xFFFFFFFF` _[#if !defined(NEIGHBORQUERY_INVALID_CELL)]_
- L53 `#define NQ_DIST_BITS 0` _[#if !defined(NQ_DIST_BITS)]_
- L55 `#define NQ_DIST_MASK ((1 << NQ_DIST_BITS) - 1)`
- L56 `#define NQ_DIST_MAX ((1 << NQ_DIST_BITS) - 2)`

#### Global resources (textures / buffers / samplers) (7)

- L14 _resource_ `Buffer<int> {ParameterName}_CellCount;`
- L15 _resource_ `Buffer<int> {ParameterName}_CellOffset;`
- L16 _resource_ `Buffer<int> {ParameterName}_ParticleList;`
- L17 _resource_ `RWBuffer<int> {ParameterName}_OutputCellId;`
- L18 _resource_ `RWBuffer<int> {ParameterName}_OutputParticleIdIndex;`
- L19 _resource_ `RWBuffer<int> {ParameterName}_OutputAcquireTag;`
- L20 _resource_ `Buffer<int> {ParameterName}_AcquireTagList;`

#### Global parameters (uniforms) (1)

- L12 _parameter_ `int {ParameterName}_MaxCellsPerParticleValue;`

#### Functions (14)

- L62-67 _function_ `uint ComputeNQSqDistQuantized_{ParameterName}(float3 IndexPos, int3 CellCoord)` — Quantize squared distance from IndexPos to CellCoord (NQ index-space units) → [0, NQ_DIST_MAX]. 0.75 = (sqrt(3)/2)^2 = squared half-diagonal of a unit NQ cell (max for round-based assignment). Squared distance avoids sqrt; monotonic so sort order is preserved. Multi-cell variants may exceed this; they saturate to NQ_DIST_MAX, sorting last — correct.
- L74-79 _function_ `int IndexToLinear_{ParameterName}(int3 CellCoord)`
- L85-95 _function_ `void WriteParticleSlot_{ParameterName}(int SlotIndex, int LinearIndex, float3 IndexPos, int3 CellCoord, int ParticleIndex, int AcquireTag)` — Write one particle assignment into OutputCellId/ParticleIdIndex/AcquireTag at SlotIndex. When NQ_DIST_BITS > 0 the combined key packs the quantized dist-to-cell-center into the low bits so the bitonic scatter produces closest-first order within each cell. When NQ_DIST_BITS == 0 the cell ID is stored directly (no dist cost, no sort key overhead).
- L101-104 _function_ `void MaxCellsPerParticle_{ParameterName}(out int OutMaxCellsPerParticle)` — Grid property queries
- L111-127 _function_ `void AddParticle_{ParameterName}(bool Enabled, float3 IndexPos, int ParticleIndex, int AcquireTag, out bool Success)`
- L130-133 _function_ `void AddParticle_{ParameterName}_UEImpureCall(bool In_Enabled, float3 In_IndexPos, int In_ParticleIndex, int In_AcquireTag, out bool Out_Success)` — Exec-pin wrapper — Niagara appends _UEImpureCall to the generated function name for bRequiresExecPin functions
- L135-157 _function_ `void AddParticleWithRadius_{ParameterName}(bool Enabled, float3 IndexPos, float Radius, int ParticleIndex, int AcquireTag, out bool Success)`
- L160-163 _function_ `void AddParticleWithRadius_{ParameterName}_UEImpureCall(bool In_Enabled, float3 In_IndexPos, float In_Radius, int In_ParticleIndex, int In_AcquireTag, out bool Out_Success)` — Exec-pin wrapper
- L165-186 _function_ `void AddParticleToOverlappedCells_{ParameterName}(bool Enabled, float3 IndexPos, int ParticleIndex, int AcquireTag, out bool Success)`
- L189-192 _function_ `void AddParticleToOverlappedCells_{ParameterName}_UEImpureCall(bool In_Enabled, float3 In_IndexPos, int In_ParticleIndex, int In_AcquireTag, out bool Out_Success)` — Exec-pin wrapper
- L194-215 _function_ `void AddParticleToNeighborCells_{ParameterName}(bool Enabled, float3 IndexPos, int ParticleIndex, int AcquireTag, out bool Success)`
- L218-221 _function_ `void AddParticleToNeighborCells_{ParameterName}_UEImpureCall(bool In_Enabled, float3 In_IndexPos, int In_ParticleIndex, int In_AcquireTag, out bool Out_Success)` — Exec-pin wrapper
- L228-238 _function_ `void GetParticleNeighborCount_{ParameterName}(int IndexX, int IndexY, int IndexZ, out int OutCount)`
- L240-257 _function_ `void GetParticleNeighbor_{ParameterName}(int IndexX, int IndexY, int IndexZ, int NeighborIdx, out int OutParticleIdx, out int OutAcquireTag)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceOcclusion.ush` (Private)

- lines: 274; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L4 `/Engine/Private/SkyAtmosphereCommon.ush`

#### Macros (#define, 1)

- L3 `#define AP_SUPPORT_SAMPLE_ATMOSHPERE 0`

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `Texture2D<float4> {ParameterName}_CloudVolumetricTexture;`
- L9 _resource_ `SamplerState {ParameterName}_CloudVolumetricTextureSampler;`

#### Global parameters (uniforms) (2)

- L6 _parameter_ `float2 {ParameterName}_CloudVolumetricTextureUVScale;`
- L7 _parameter_ `float2 {ParameterName}_CloudVolumetricTextureUVMax;`

#### Functions (5)

- L11-63 _function_ `void QueryOcclusionFactorWithRectangle_{ParameterName}(in float3 In_SampleCenterWorldPos, in float In_SampleWindowWidthWorld, in float In_SampleWindowHeightWorld, in float In_SampleSteps, out float Out_VisibilityFraction, out float Out_SampleFraction)`
- L65-68 _function_ `void QueryOcclusionFactorWithRectangleGPU_{ParameterName}(in float3 In_SampleCenterWorldPos, in float In_SampleWindowWidthWorld, in float In_SampleWindowHeightWorld, in float In_SampleSteps, out float Out_VisibilityFraction, out float Out_SampleFraction)`
- L70-136 _function_ `void QueryOcclusionFactorWithCircleGPU_{ParameterName}(in float3 In_SampleCenterWorldPos, in float In_SampleWindowDiameterWorld, in float In_SampleRays, in float In_SampleStepsPerRay, out float Out_VisibilityFraction, out float Out_SampleFraction)`
- L138-196 _function_ `void QueryOcclusionFactorWithCircle_{ParameterName}(float3 WorldPosition, float WorldDiameter, bool bIncludeCenterSample, int NumberOfRings, int SamplesPerRing, out float VisibilityFraction, out float OnScreenFraction, out float DepthPassFraction)`
- L198-273 _function_ `void QueryCloudOcclusionWithCircle_{ParameterName}(float3 WorldPosition, float WorldDiameter, bool bIncludeCenterSample, int NumberOfRings, int SamplesPerRing, out float VisibilityFraction, out float SampleFraction, out float3 AtmosphereTransmittance)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfacePhysicsAsset.ush` (Private)

- lines: 518; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Macros (#define, 7)

- L12 `#define PHYSICS_ASSET_MAX_TRANSFORMS 300`
- L14 `#define CURRENT_OFFSET 0`
- L15 `#define PREVIOUS_OFFSET PHYSICS_ASSET_MAX_TRANSFORMS`
- L16 `#define REST_OFFSET 2*PHYSICS_ASSET_MAX_TRANSFORMS`
- L18 `#define BOX_INDEX 0`
- L19 `#define SPHERE_INDEX 1`
- L20 `#define CAPSULE_INDEX 2`
- L509 #undef `PHYSICS_ASSET_MAX_TRANSFORMS`; L511 #undef `CURRENT_OFFSET`; L512 #undef `PREVIOUS_OFFSET`; L513 #undef `REST_OFFSET`; L515 #undef `BOX_INDEX`; L516 #undef `SPHERE_INDEX`; L517 #undef `CAPSULE_INDEX`

#### Global resources (textures / buffers / samplers) (4)

- L23 _resource_ `Buffer<float4> {ParameterName}_WorldTransformBuffer;`
- L24 _resource_ `Buffer<float4> {ParameterName}_InverseTransformBuffer;`
- L25 _resource_ `Buffer<float4> {ParameterName}_ElementExtentBuffer;`
- L26 _resource_ `Buffer<uint> {ParameterName}_PhysicsTypeBuffer;`

#### Global parameters (uniforms) (3)

- L22 _parameter_ `uint4 {ParameterName}_ElementOffsets;`
- L27 _parameter_ `float3 {ParameterName}_BoxOrigin;`
- L28 _parameter_ `float3 {ParameterName}_BoxExtent;`

#### Functions (26)

- L35-38 _function_ `void GetNumBoxes_{ParameterName}(out int OutNumBoxes)`
- L40-43 _function_ `void GetNumSpheres_{ParameterName}(out int OutNumSpheres)`
- L45-48 _function_ `void GetNumCapsules_{ParameterName}(out int OutNumCapsules)`
- L56-60 _function_ `float3 GetCurrentPosition_{ParameterName}(in int ElementIndex)`
- L62-66 _function_ `float3 GetPreviousPosition_{ParameterName}(in int ElementIndex)`
- L68-77 _function_ `float4 GetCurrentOrientation_{ParameterName}(in int ElementIndex)`
- L79-87 _function_ `float4 GetPreviousOrientation_{ParameterName}(in int ElementIndex)`
- L89-93 _function_ `float3x4 GetCurrentTransform_{ParameterName}(in int ElementIndex)`
- L95-99 _function_ `float3x4 GetInverseTransform_{ParameterName}(in int ElementIndex)`
- L101-105 _function_ `float3x4 GetPreviousTransform_{ParameterName}(in int ElementIndex)`
- L107-111 _function_ `float3x4 GetPreviousInverse_{ParameterName}(in int ElementIndex)`
- L113-117 _function_ `float3x4 GetRestTransform_{ParameterName}(in int ElementIndex)`
- L119-123 _function_ `float3x4 GetRestInverse_{ParameterName}(in int ElementIndex)`
- L131-147 _function_ `float GetSphereProjection_{ParameterName}(in float3 LocalPosition, in float3 SphereCenter, in float SphereRadius, in int SphereIndex, inout float3 OutClosestPosition, inout float3 OutClosestNormal, inout int OutElementIndex, inout float OutMinDistance)` — Given a world space position (NodePosition) compute the sphere closest point (position,normal,velocity)
- L150-158 _function_ `float GetCapsuleProjection_{ParameterName}(in float3 LocalPosition, in float2 CapsuleSize, in int CapsuleIndex, inout float3 OutClosestPosition, inout float3 OutClosestNormal, inout int OutElementIndex, inout float OutMinDistance)` — Given a world space position (NodePosition) compute the sphere closest point (position,normal,velocity)
- L161-205 _function_ `float GetBoxProjection_{ParameterName}(in float3 LocalPosition, in float3 BoxExtent, in int BoxIndex, inout float3 OutClosestPosition, inout float3 OutClosestNormal, inout int OutElementIndex, inout float OutMinDistance)` — Given a world space position (NodePosition) compute the sphere closest point (position,normal,velocity)
- L229-235 _function_ `float3 GetLocalPosition_{ParameterName}(in float3 NodePosition, in int ElementIndex, in float TimeFraction )`
- L238-282 _function_ `int GetClosestElement_{ParameterName}(in float3 NodePosition, out float3 OutClosestPosition, out float3 OutClosestNormal, out float OutMinDistance, in float TimeFraction, in bool IsRestSpace )` — Given a world space position (NodePosition) compute the sphere closest point (position,normal,velocity)
- L290-337 _function_ `void GetElementPoint_{ParameterName}(in float3 NodePosition, in float DeltaTime, in float TimeFraction, in int ElementIndex, out float3 OutClosestPosition, out float3 OutClosestNormal, out float3 OutClosestVelocity)` — Given a world space position (NodePosition) and an element index compute the physics asset closest point (position,normal,velocity)
- L340-375 _function_ `void GetElementDistance_{ParameterName}(in float3 NodePosition, in float TimeFraction, in int ElementIndex, out float OutClosestDistance)` — Given a world space position (NodePosition) and an element index compute the physics asset closest distance
- L378-385 _function_ `void GetClosestElement_{ParameterName}(in float3 NodePosition, in float TimeFraction, out int OutElementIndex)` — Given a world space position (NodePosition) compute the physics asset closest element
- L388-414 _function_ `void GetClosestPoint_{ParameterName}(in float3 NodePosition, in float DeltaTime, in float TimeFraction, out float3 OutClosestPosition, out float3 OutClosestNormal, out float3 OutClosestVelocity)` — Given a world space position (NodePosition) compute the physics asset closest point (position,normal,velocity)
- L417-431 _function_ `void GetClosestDistance_{ParameterName}(in float3 NodePosition, in float TimeFraction, out float OutClosestDistance)` — Given a world space position (NodePosition) compute the physics asset closest distance
- L439-453 _function_ `void GetRestDistance_{ParameterName}(in float3 RestPosition, out float OutRestDistance)`
- L455-478 _function_ `void GetTexturePoint_{ParameterName}(in float3 NodePosition, out int OutElementIndex, out float3 OutTexturePosition)`
- L480-507 _function_ `void GetProjectionPoint_{ParameterName}(in float3 NodePosition, in float DeltaTime, in int ElementIndex, in float TextureValue, in float3 TextureGradient, out float3 OutClosestPosition, out float3 OutClosestNormal, out float3 OutClosestVelocity, out float OutClosestDistance)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfacePlatformSetTemplate.ush` (Private)

- lines: 9; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (1)

- L3 _parameter_ `int {ParameterName}_bIsActive;`

#### Functions (1)

- L5-8 _function_ `void IsActive_{ParameterName}(out bool bIsActive)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfacePropertyInterfaceTemplate.ush` (Private)

- lines: 13; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L4 _resource_ `ByteAddressBuffer {ParameterName}_PropertyInterfaceData;`

#### Functions (6)

- L7 _function_ `void ReadValue_{ParameterName}(uint ReadOffset, out bool Value)`
- L8 _function_ `void ReadValue_{ParameterName}(uint ReadOffset, out int Value)`
- L9 _function_ `void ReadValue_{ParameterName}(uint ReadOffset, out float Value)`
- L10 _function_ `void ReadValue_{ParameterName}(uint ReadOffset, out float2 Value)`
- L11 _function_ `void ReadValue_{ParameterName}(uint ReadOffset, out float3 Value)`
- L12 _function_ `void ReadValue_{ParameterName}(uint ReadOffset, out float4 Value)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceRenderTarget2DArrayTemplate.ush` (Private)

- lines: 63; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (3)

- L5 _resource_ `RWTexture2DArray<float4> {ParameterName}_RWTexture;`
- L6 _resource_ `Texture2DArray<float4> {ParameterName}_Texture;`
- L7 _resource_ `SamplerState {ParameterName}_TextureSampler;`

#### Global parameters (uniforms) (2)

- L3 _parameter_ `int3 {ParameterName}_TextureSize;`
- L4 _parameter_ `int {ParameterName}_MipLevels;`

#### Functions (9)

- L9-15 _function_ `void SetRenderTargetValue_{ParameterName}_UEImpureCall(bool bExecute, int IndexX, int IndexY, int IndexZ, float4 Value)`
- L17-20 _function_ `void GetRenderTargetValue_{ParameterName}(int IndexX, int IndexY, int IndexZ, out float4 Value)`
- L22-25 _function_ `void LoadRenderTargetValue_{ParameterName}(int IndexX, int IndexY, int IndexZ, int MipLevel, out float4 Value)`
- L27-30 _function_ `void SampleRenderTargetValue_{ParameterName}(float2 UV, int Slice, float MipLevel, out float4 Value)`
- L32-37 _function_ `void GetRenderTargetSize_{ParameterName}(out int Width, out int Height, out int Slices)`
- L39-42 _function_ `void GetNumMipLevels_{ParameterName}(out int OutMipLevels)`
- L44-49 _function_ `void LinearToIndex_{ParameterName}(int Linear, out int IndexX, out int IndexY, out int IndexZ)`
- L51-54 _function_ `void ExecToIndex_{ParameterName}(out int IndexX, out int IndexY, out int IndexZ)`
- L56-62 _function_ `void ExecToUnit_{ParameterName}(out float2 Unit, out int Slice)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceRenderTarget2DTemplate.ush` (Private)

- lines: 61; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (3)

- L5 _resource_ `RWTexture2D<float4> {ParameterName}_RWTexture;`
- L6 _resource_ `Texture2D<float4> {ParameterName}_Texture;`
- L7 _resource_ `SamplerState {ParameterName}_TextureSampler;`

#### Global parameters (uniforms) (2)

- L3 _parameter_ `int2 {ParameterName}_TextureSize;`
- L4 _parameter_ `int {ParameterName}_MipLevels;`

#### Functions (9)

- L9-15 _function_ `void SetRenderTargetValue_{ParameterName}_UEImpureCall(bool bExecute, int IndexX, int IndexY, float4 Value)`
- L17-20 _function_ `void GetRenderTargetValue_{ParameterName}(int IndexX, int IndexY, out float4 Value)`
- L22-25 _function_ `void LoadRenderTargetValue_{ParameterName}(int IndexX, int IndexY, int MipLevel, out float4 Value)`
- L27-30 _function_ `void SampleRenderTargetValue_{ParameterName}(float2 UV, float MipLevel, out float4 Value)`
- L32-36 _function_ `void GetRenderTargetSize_{ParameterName}(out int Width, out int Height)`
- L38-41 _function_ `void GetNumMipLevels_{ParameterName}(out int OutMipLevels)`
- L43-47 _function_ `void LinearToIndex_{ParameterName}(int Linear, out int IndexX, out int IndexY)`
- L49-52 _function_ `void ExecToIndex_{ParameterName}(out int IndexX, out int IndexY)`
- L54-60 _function_ `void ExecToUnit_{ParameterName}(out float2 Unit)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceRenderTargetCubeTemplate.ush` (Private)

- lines: 62; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (3)

- L5 _resource_ `RWTextureCube<float4> {ParameterName}_RWTexture;`
- L6 _resource_ `TextureCube<float4> {ParameterName}_Texture;`
- L7 _resource_ `SamplerState {ParameterName}_TextureSampler;`

#### Global parameters (uniforms) (2)

- L3 _parameter_ `int {ParameterName}_TextureSize;`
- L4 _parameter_ `int {ParameterName}_MipLevels;`

#### Functions (7)

- L9-15 _function_ `void SetRenderTargetValue_{ParameterName}_UEImpureCall(bool bExecute, int IndexX, int IndexY, int Face, float4 Value)`
- L28-31 _function_ `void SampleRenderTargetValue_{ParameterName}(float3 UVW, float MipLevel, out float4 Value)`
- L33-36 _function_ `void GetRenderTargetSize_{ParameterName}(out int Size)`
- L38-41 _function_ `void GetNumMipLevels_{ParameterName}(out int OutMipLevels)`
- L43-48 _function_ `void LinearToIndex_{ParameterName}(int Linear, out int IndexX, out int IndexY, out int Face)`
- L50-53 _function_ `void ExecToIndex_{ParameterName}(out int IndexX, out int IndexY, out int Face)`
- L55-61 _function_ `void ExecToUnit_{ParameterName}(out float2 Unit, out int Face)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceRenderTargetVolumeTemplate.ush` (Private)

- lines: 64; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (3)

- L5 _resource_ `RWTexture3D<float4> {ParameterName}_RWTexture;`
- L6 _resource_ `Texture3D<float4> {ParameterName}_Texture;`
- L7 _resource_ `SamplerState {ParameterName}_TextureSampler;`

#### Global parameters (uniforms) (2)

- L3 _parameter_ `int3 {ParameterName}_TextureSize;`
- L4 _parameter_ `int {ParameterName}_MipLevels;`

#### Functions (9)

- L9-15 _function_ `void SetRenderTargetValue_{ParameterName}_UEImpureCall(bool bExecute, int IndexX, int IndexY, int IndexZ, float4 Value)`
- L17-20 _function_ `void GetRenderTargetValue_{ParameterName}(int IndexX, int IndexY, int IndexZ, out float4 Value)`
- L22-25 _function_ `void LoadRenderTargetValue_{ParameterName}(int IndexX, int IndexY, int IndexZ, int MipLevel, out float4 Value)`
- L27-30 _function_ `void SampleRenderTargetValue_{ParameterName}(float3 UVW, float MipLevel, out float4 Value)`
- L32-37 _function_ `void GetRenderTargetSize_{ParameterName}(out int Width, out int Height, out int Slices)`
- L39-42 _function_ `void GetNumMipLevels_{ParameterName}(out int OutMipLevels)`
- L44-49 _function_ `void LinearToIndex_{ParameterName}(int Linear, out int IndexX, out int IndexY, out int IndexZ)`
- L51-54 _function_ `void ExecToIndex_{ParameterName}(out int IndexX, out int IndexY, out int IndexZ)`
- L56-63 _function_ `void ExecToUnit_{ParameterName}(out float3 Unit)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceRigidMeshCollisionQuery.ush` (Private)

- lines: 726; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L7 `/Plugin/FX/Niagara/Private/NiagaraDistanceFieldQueries.ush`, L8 `/Plugin/FX/Niagara/Private/NiagaraQuaternionUtils.ush`, L9 `/Plugin/FX/Niagara/Private/NiagaraTransformUtils.ush`

#### Macros (#define, 4)

- L16 `#define BOX_INDEX 0`
- L17 `#define SPHERE_INDEX 1`
- L18 `#define CAPSULE_INDEX 2`
- L19 `#define NUM_ELEMENTS_INDEX 3`
- L724 #undef `BOX_INDEX`; L725 #undef `SPHERE_INDEX`; L726 #undef `CAPSULE_INDEX`

#### Global resources (textures / buffers / samplers) (6)

- L25 _resource_ `Buffer<float4> {ParameterName}_WorldTransformBuffer;`
- L26 _resource_ `Buffer<float4> {ParameterName}_InverseTransformBuffer;`
- L27 _resource_ `Buffer<float4> {ParameterName}_MeshScaleBuffer;`
- L28 _resource_ `Buffer<float4> {ParameterName}_ElementExtentBuffer;`
- L29 _resource_ `Buffer<uint> {ParameterName}_PhysicsTypeBuffer;`
- L30 _resource_ `Buffer<uint> {ParameterName}_DFIndexBuffer;`

#### Global parameters (uniforms) (6)

- L21 _parameter_ `uint {ParameterName}_MaxTransforms;`
- L22 _parameter_ `uint {ParameterName}_CurrentOffset;`
- L23 _parameter_ `uint {ParameterName}_PreviousOffset;`
- L24 _parameter_ `uint4 {ParameterName}_ElementOffsets;`
- L31 _parameter_ `float3 {ParameterName}_CombinedBBoxWorldMin;`
- L32 _parameter_ `float3 {ParameterName}_CombinedBBoxWorldMax;`

#### Functions (37)

- L39-42 _function_ `void GetNumBoxes_{ParameterName}(out int OutNumBoxes)`
- L44-47 _function_ `void GetNumSpheres_{ParameterName}(out int OutNumSpheres)`
- L49-52 _function_ `void GetNumCapsules_{ParameterName}(out int OutNumCapsules)`
- L54-57 _function_ `void GetNumElements_{ParameterName}(out int OutNumElements)`
- L59-62 _function_ `void GetBoxElementsStartIndex_{ParameterName}(out int OutStartIndex)`
- L64-67 _function_ `void GetSphereElementsStartIndex_{ParameterName}(out int OutStartIndex)`
- L69-72 _function_ `void GetCapsuleElementsStartIndex_{ParameterName}(out int OutStartIndex)`
- L74-77 _function_ `void GetSphereRadius_{ParameterName}(in int ElementIndex, out float OutRadius)`
- L79-82 _function_ `void GetCapsuleSize_{ParameterName}(in int ElementIndex, out float2 OutSize)`
- L84-87 _function_ `void GetBoxSize_{ParameterName}(in int ElementIndex, out float3 OutSize)`
- L94-98 _function_ `float3x4 GetCurrentTransform_{ParameterName}(in int ElementIndex)`
- L100-104 _function_ `float3x4 GetInverseTransform_{ParameterName}(in int ElementIndex)`
- L106-110 _function_ `float3x4 GetPreviousTransform_{ParameterName}(in int ElementIndex)`
- L112-116 _function_ `float3x4 GetPreviousInverse_{ParameterName}(in int ElementIndex)`
- L118-121 _function_ `float3 GetMeshScale_{ParameterName}(in int ElementIndex)`
- L123-134 _function_ `void IsWorldPositionInsideCombinedBounds_{ParameterName}(in float3 WorldPosition, out bool IsInside)`
- L142-158 _function_ `float GetSphereProjection_{ParameterName}(in float3 LocalPosition, in float3 SphereCenter, in float SphereRadius, in int SphereIndex, inout float3 OutClosestPosition, inout float3 OutClosestNormal, inout int OutElementIndex, inout float OutMinDistance)` — Given a world space position (WorldPosition) compute the sphere closest point (position,normal,velocity)
- L161-169 _function_ `float GetCapsuleProjection_{ParameterName}(in float3 LocalPosition, in float2 CapsuleSize, in int CapsuleIndex, inout float3 OutClosestPosition, inout float3 OutClosestNormal, inout int OutElementIndex, inout float OutMinDistance)` — Given a world space position (WorldPosition) compute the sphere closest point (position,normal,velocity)
- L172-216 _function_ `float GetBoxProjection_{ParameterName}(in float3 LocalPosition, in float3 BoxExtent, in int BoxIndex, inout float3 OutClosestPosition, inout float3 OutClosestNormal, inout int OutElementIndex, inout float OutMinDistance)` — Given a world space position (WorldPosition) compute the sphere closest point (position,normal,velocity)
- L224-230 _function_ `float3 GetLocalPosition_{ParameterName}(in float3 WorldPosition, in int ElementIndex, in float TimeFraction )`
- L232-235 _function_ `float3 GetCurrentLocalPosition_{ParameterName}(in float3 WorldPosition, in int ElementIndex )`
- L238-278 _function_ `int GetClosestElement_{ParameterName}(in float3 WorldPosition, out float3 OutClosestPosition, out float3 OutClosestNormal, out float OutMinDistance, in float TimeFraction)` — Given a world space position (WorldPosition) compute the sphere closest point (position,normal,velocity)
- L281-321 _function_ `int GetClosestElementSimple_{ParameterName}(in float3 WorldPosition, out float3 OutClosestPosition, out float OutMinDistance)` — Given a world space position (WorldPosition) compute the sphere closest point (position,normal,velocity)
- L329-375 _function_ `void GetElementPoint_{ParameterName}(in float3 WorldPosition, in float DeltaTime, in float TimeFraction, in int ElementIndex, out float3 OutClosestPosition, out float3 OutClosestNormal, out float3 OutClosestVelocity)` — Given a world space position (WorldPosition) and an element index compute the static mesh closest point (position,normal,velocity)
- L378-421 _function_ `void GetElementPointMeshDistanceFieldNoNormal_{ParameterName}(in float3 WorldPosition, in float DeltaTime, in float TimeFraction, in float MaxDistance, in int ElementIndex, out float OutClosestDistance, out float3 OutClosestVelocity)` — Given a world space position (WorldPosition) and an element index compute the static mesh closest point using distance fields (position,velocity)
- L424-459 _function_ `void GetElementDistance_{ParameterName}(in float3 WorldPosition, in float TimeFraction, in int ElementIndex, out float OutClosestDistance)` — Given a world space position (WorldPosition) and an element index compute the static mesh closest distance
- L462-469 _function_ `void GetClosestElement_{ParameterName}(in float3 WorldPosition, in float TimeFraction, out int OutElementIndex)` — Given a world space position (WorldPosition) compute the static mesh closest element
- L472-497 _function_ `void GetClosestPoint_{ParameterName}(in float3 WorldPosition, in float DeltaTime, in float TimeFraction, out float OutClosestDistance, out float3 OutClosestPosition, out float3 OutClosestNormal, out float3 OutClosestVelocity)` — Given a world space position (WorldPosition) compute the static mesh closest point (position,normal,velocity)
- L500-515 _function_ `void GetClosestPointSimple_{ParameterName}(in float3 WorldPosition, in float DeltaTime, out float OutClosestDistance, out float3 OutClosestVelocity)` — Given a world space position (WorldPosition) compute the static mesh closest point (position,normal,velocity)
- L518-532 _function_ `void GetClosestDistance_{ParameterName}(in float3 WorldPosition, in float TimeFraction, out float OutClosestDistance)` — Given a world space position (WorldPosition) compute the static mesh closest distance
- L534-543 _function_ `void EvaluateWorldPositionOnElement_{ParameterName}(int ElementIndex, float3 WorldPosition, float DeltaTime, float TimeFraction, out float3 OutPosition, out float3 OutVelocity)`
- L546-585 _function_ `void GetClosestPointMeshDistanceField_{ParameterName}(in float3 WorldPosition, in float DeltaTime, in float TimeFraction, in float MaxDistance, out float OutClosestDistance, out float3 OutClosestPosition, out float3 OutClosestNormal, out float3 OutClosestVelocity, out bool NormalIsValid, out float MaxEncodedDistance)` — Given a world space position (WorldPosition) compute the static mesh closest point (position,normal,velocity)
- L588-627 _function_ `void GetClosestPointMeshDistanceFieldAccurate_{ParameterName}(in float3 WorldPosition, in float DeltaTime, in float TimeFraction, in float MaxDistance, out float OutClosestDistance, out float3 OutClosestPosition, out float3 OutClosestNormal, out float3 OutClosestVelocity, out bool NormalIsValid, out float MaxEncodedDistance)` — Given a world space position (WorldPosition) compute the static mesh closest point (position,normal,velocity) by querying all overlapping mesh distance fields
- L630-666 _function_ `void GetClosestPointMeshDistanceFieldNoNormal_{ParameterName}(in float3 WorldPosition, in float DeltaTime, in float TimeFraction, in float MaxDistance, out float OutClosestDistance, out float3 OutClosestPosition, out float3 OutClosestVelocity)` — Given a world space position (WorldPosition) compute the static mesh closest point (position,normal,velocity)
- L668-684 _function_ `void GetMaxEncodedDistanceMeshDistanceField_{ParameterName}(in int ElementIndex, out float MaxEncodedDistance)`
- L686-703 _function_ `void GetElementTransform_{ParameterName}(in int ElementIndex, in float TimeFraction, out float3 OutTranslation, out float4 OutRotation, out float3 OutScale, out bool OutIsValid)`
- L705-722 _function_ `void GetElementInverseTransform_{ParameterName}(in int ElementIndex, in float TimeFraction, out float3 OutTranslation, out float4 OutRotation, out float3 OutScale, out bool OutIsValid)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceSceneCapture2DTemplate.ush` (Private)

- lines: 86; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (2)

- L3 _resource_ `Texture2D {ParameterName}_Texture;`
- L4 _resource_ `SamplerState {ParameterName}_TextureSampler;`

#### Global parameters (uniforms) (5)

- L5 _parameter_ `int3 {ParameterName}_TextureSize;`
- L6 _parameter_ `float4x4 {ParameterName}_TextureViewMatrix;`
- L7 _parameter_ `float4x4 {ParameterName}_TextureProjMatrix;`
- L8 _parameter_ `float4x4 {ParameterName}_InvTextureProjMatrix;`
- L9 _parameter_ `uint {ParameterName}_IsPerspective;`

#### Functions (8)

- L11-16 _function_ `void GetTextureSize_{ParameterName}(out int OutSizeX, out int OutSizeY, out int NumMips)`
- L18-21 _function_ `void TextureLoad_{ParameterName}(in int TexelX, in int TexelY, in int MipLevel, out float4 OutValue)`
- L23-26 _function_ `void TextureSample_{ParameterName}(in float2 UV, in float MipLevel, out float4 OutValue)`
- L28-33 _function_ `void Project_{ParameterName}(in float3 Position, out float3 UVW)`
- L35-43 _function_ `void Deproject_{ParameterName}(in float2 UV, in float Depth, out float3 Position)`
- L45-52 _function_ `void TextureProject_{ParameterName}(in float3 Position, in float MipLevel, in bool bValidateTextureBounds, in bool bValidateDepthBounds, in float4 DefaultColor, out bool OutInBounds, out float4 OutValue, out float3 UVW)`
- L54-71 _function_ `void TextureProjectDepth_{ParameterName}(in float3 Position, in float MipLevel, in bool bPointSample, in bool bValidateTextureBounds, in float DefaultDepth, out bool OutInBounds, out float OutCaptureDepth, out float OutPositionDepth, out float2 OutUV)`
- L73-85 _function_ `void TextureDeprojectDepth_{ParameterName}(in float2 UV, in float MipLevel, in bool bPointSample, out float3 OutPosition, out float OutCaptureDepth)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceSimCacheReaderTemplate.ush` (Private)

- lines: 164; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Structs / classes (1)

- L8-14 _struct_ **`{ParameterName}_EmitterFrameData`** `struct {ParameterName}_EmitterFrameData`
  - L10 _member_ `int NumInstances;`
  - L11 _member_ `uint Int32DataOffset;`
  - L12 _member_ `uint FloatDataOffset;`
  - L13 _member_ `uint HalfDataOffset;`

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Buffer<uint> {ParameterName}_CacheData;`

#### Global parameters (uniforms) (3)

- L3 _parameter_ `int {ParameterName}_NumFrames;`
- L4 _parameter_ `int {ParameterName}_NumEmitters;`
- L5 _parameter_ `int {ParameterName}_EmitterIndex;`

#### Functions (12)

- L16-19 _function_ `void GetNumFrames_{ParameterName}(out int NumFrames)`
- L21-24 _function_ `void GetNumEmitters_{ParameterName}(out int NumEmitters)`
- L26-29 _function_ `void GetEmitterIndex_{ParameterName}(out int EmitterIndex)`
- L31-48 _function_ `{ParameterName}_EmitterFrameData GetEmitterFrameData_{ParameterName}(int FrameIndex, int EmitterIndex)`
- L50-54 _function_ `void GetNumInstances_{ParameterName}(in int FrameIndex, out int NumInstances)`
- L56-67 _function_ `void GetInstanceInt_{ParameterName}(int FrameIndex, int EmitterIndex, int AttributeIndex, int InstanceIndex, out bool bValid, out int Value)`
- L69-80 _function_ `void GetInstanceFloat_{ParameterName}(int FrameIndex, int EmitterIndex, int AttributeIndex, int InstanceIndex, out bool bValid, out float Value)`
- L82-94 _function_ `void GetInstanceFloat2_{ParameterName}(int FrameIndex, int EmitterIndex, int AttributeIndex, int InstanceIndex, out bool bValid, out float2 Value)`
- L96-109 _function_ `void GetInstanceFloat3_{ParameterName}(int FrameIndex, int EmitterIndex, int AttributeIndex, int InstanceIndex, out bool bValid, out float3 Value)`
- L111-125 _function_ `void GetInstanceFloat4_{ParameterName}(int FrameIndex, int EmitterIndex, int AttributeIndex, int InstanceIndex, out bool bValid, out float4 Value)`
- L127-140 _function_ `void GetInstanceID_{ParameterName}(int FrameIndex, int EmitterIndex, int AttributeIndex, int InstanceIndex, out bool bValid, out NiagaraID Value)`
- L142-163 _function_ `void GetInstanceIndexFromID_{ParameterName}(int FrameIndex, int EmitterIndex, int AttributeIndex, NiagaraID ID, out bool bValid, out int Value)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceSimpleCounterTemplate.ush` (Private)

- lines: 55; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (1)

- L4 _parameter_ `int {ParameterName}_CountOffset;`

#### Functions (6)

- L6-9 _function_ `void Get_{ParameterName}(out int CurrValue)`
- L11-18 _function_ `void Set_{ParameterName}_UEImpureCall(in bool bExecute, in int NewValue)`
- L20-30 _function_ `void Exchange_{ParameterName}_UEImpureCall(in bool bExecute, in int NewValue, out int PrevValue)`
- L32-44 _function_ `void Add_{ParameterName}_UEImpureCall(in bool bExecute, in int Amount, out int PrevValue, out int CurrValue)`
- L46-49 _function_ `void Increment_{ParameterName}_UEImpureCall(in bool bExecute, out int PrevValue, out int CurrValue)`
- L51-54 _function_ `void Decrement_{ParameterName}_UEImpureCall(in bool bExecute, out int PrevValue, out int CurrValue)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceSkeletalMesh.ush` (Private)

- lines: 144; parse: all-branches
- includes: L5 `NiagaraBaryCentricUtils.ush`

#### Macros (#define, 16)

- L7 `#define DISKELMESH_BONE_INFLUENCES_MAX4 0`
- L8 `#define DISKELMESH_BONE_INFLUENCES_MAX8 1`
- L9 `#define DISKELMESH_BONE_INFLUENCES_UNLIMITED 2`
- L12 `#define DISKELMESH_BONE_INFLUENCES DISKELMESH_BONE_INFLUENCES_UNLIMITED` _[#if !defined(DISKELMESH_BONE_INFLUENCES)]_
- L15 `#define DISKELMESH_PROBALIAS_FORMAT_64 0`
- L16 `#define DISKELMESH_PROBALIAS_FORMAT_24_8 1`
- L17 `#define DISKELMESH_PROBALIAS_FORMAT_23_9 2`
- L20 `#define DISKELMESH_PROBALIAS_FORMAT DISKELMESH_PROBALIAS_FORMAT_64` _[#if !defined(DISKELMESH_PROBALIAS_FORMAT)]_
- L23 `#define DISKELMESH_ADJ_INDEX_FORMAT_FULL 0`
- L24 `#define DISKELMESH_ADJ_INDEX_FORMAT_HALF 1`
- L27 `#define DISKELMESH_ADJ_INDEX_FORMAT DISKELMESH_ADJ_INDEX_FORMAT_FULL` _[#if !defined(DISKELMESH_ADJ_INDEX_FORMAT)]_
- L32 `#define DISKELMESH_ALLOW_DEFORMED 0` _[#if FEATURE_LEVEL <= FEATURE_LEVEL_ES3_1]_
- L87 `#define DISkelMesh_ElementCountOffset 4`
- L88 `#define DISkelMesh_TriangleIndexOffset 5`
- L89 `#define DISkelMesh_MinValidUvMappingBufferSize 24`
- L101 `#define AXIS_COUNT 3`
- L3 #pragma `once`; L31 #undef `DISKELMESH_ALLOW_DEFORMED`

#### Structs / classes (1)

- L41-48 _struct_ **`FDISkelMeshSkinnedVertex`** `struct FDISkelMeshSkinnedVertex`
  - L43 _member_ `float3 Position;`
  - L44 _member_ `float3 PrevPosition;`
  - L45 _member_ `float3 TangentX;`
  - L46 _member_ `float3 TangentY;`
  - L47 _member_ `float3 TangentZ;`

#### Functions (8)

- L36-39 _function_ `float DISKelMesh_Random(uint S1, uint S2, uint S3)` — -TODO: We need to consolodate the random interface inside NiagaraEmitterInstanceShader.usf it's a bit messy at the moment but should follow what FNDIRandomHelper does
- L50-57 _function_ `float3 DISKelMesh_RandomBarycentricCoord(uint Seed1, uint Seed2, uint Seed3)`
- L59-62 _function_ `int4 DISkelMesh_UnpackIndices4x8(uint Packed)`
- L64-67 _function_ `int4 DISkelMesh_UnpackIndices4x16(uint PackedA, uint PackedB)`
- L69-72 _function_ `float4 DISkelMesh_UnpackWeights4x8(uint Packed)`
- L74-77 _function_ `float4 DISkelMesh_UnpackWeights4x16(uint PackedA, uint PackedB)`
- L91-118 _function_ `bool DISkelMesh_NormalizedAabbTriangleIntersection(float2 A, float2 B, float2 C)`
- L120-143 _function_ `float4 DISKelMesh_QuatSlerp(float4 Quat1, float4 Quat2, float Slerp)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceSkeletalMeshTemplate.ush` (Private)

- lines: 1228; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (22)

- L6 _resource_ `Buffer<uint> {ParameterName}_MeshIndexBuffer;`
- L7 _resource_ `Buffer<float> {ParameterName}_MeshVertexBuffer;`
- L8 _resource_ `Buffer<uint> {ParameterName}_MeshSkinWeightBuffer;`
- L9 _resource_ `Buffer<uint> {ParameterName}_MeshSkinWeightLookupBuffer;`
- L10 _resource_ `Buffer<float4> {ParameterName}_MeshCurrBonesBuffer;`
- L11 _resource_ `Buffer<float4> {ParameterName}_MeshPrevBonesBuffer;`
- L12 _resource_ `Buffer<float4> {ParameterName}_MeshCurrSamplingBonesBuffer;`
- L13 _resource_ `Buffer<float4> {ParameterName}_MeshPrevSamplingBonesBuffer;`
- L14 _resource_ `Buffer<float4> {ParameterName}_MeshTangentBuffer;`
- L15 _resource_ `Buffer<float2> {ParameterName}_MeshTexCoordBuffer;`
- L16 _resource_ `Buffer<float4> {ParameterName}_MeshColorBuffer;`
- L17 _resource_ `Buffer<uint> {ParameterName}_MeshTriangleSamplerProbAliasBuffer;`
- L20 _resource_ `Buffer<uint> {ParameterName}_MeshSamplingRegionsProbAliasBuffer;`
- L21 _resource_ `Buffer<uint> {ParameterName}_MeshSampleRegionsTriangleIndices;`
- L22 _resource_ `Buffer<uint> {ParameterName}_MeshSampleRegionsVertices;`
- L23 _resource_ `Buffer<uint> {ParameterName}_MeshTriangleMatricesOffsetBuffer;`
- L36 _resource_ `Buffer<uint> {ParameterName}_FilteredAndUnfilteredBones;`
- L39 _resource_ `Buffer<int> {ParameterName}_UvMappingBuffer;`
- L42 _resource_ `Buffer<uint> {ParameterName}_ConnectivityBuffer;`
- L54 _resource_ `Buffer<float> {ParameterName}_DeformedCurrPositionBuffer;` _[#if DISKELMESH_ALLOW_DEFORMED]_
- L55 _resource_ `Buffer<float> {ParameterName}_DeformedPrevPositionBuffer;` _[#if DISKELMESH_ALLOW_DEFORMED]_
- L56 _resource_ `Buffer<float4> {ParameterName}_DeformedTangentBuffer;` _[#if DISKELMESH_ALLOW_DEFORMED]_

#### Global parameters (uniforms) (28)

- L18 _parameter_ `uint {ParameterName}_MeshNumSamplingRegionTriangles;`
- L19 _parameter_ `uint {ParameterName}_MeshNumSamplingRegionVertices;`
- L24 _parameter_ `uint {ParameterName}_MeshTriangleCount;`
- L25 _parameter_ `uint {ParameterName}_MeshVertexCount;`
- L26 _parameter_ `uint {ParameterName}_MeshNumTexCoord;`
- L27 _parameter_ `uint {ParameterName}_MeshNumWeights;`
- L28 _parameter_ `uint {ParameterName}_MeshBoneWeightStride;`
- L29 _parameter_ `uint {ParameterName}_MeshBoneIndexSizeBytes;`
- L30 _parameter_ `uint {ParameterName}_MeshBoneWeightSizeBytes;`
- L31 _parameter_ `int {ParameterName}_NumBones;`
- L32 _parameter_ `int {ParameterName}_NumFilteredBones;`
- L33 _parameter_ `int {ParameterName}_NumUnfilteredBones;`
- L34 _parameter_ `int {ParameterName}_RandomMaxBone;`
- L35 _parameter_ `int {ParameterName}_ExcludeBoneIndex;`
- L37 _parameter_ `int {ParameterName}_NumFilteredSockets;`
- L38 _parameter_ `int {ParameterName}_FilteredSocketBoneOffset;`
- L40 _parameter_ `uint {ParameterName}_UvMappingBufferLength;`
- L41 _parameter_ `uint {ParameterName}_UvMappingSet;`
- L43 _parameter_ `uint {ParameterName}_ConnectivityBufferLength;`
- L44 _parameter_ `uint {ParameterName}_ConnectivityMaxAdjacentPerVertex;`
- L45 _parameter_ `float4x4 {ParameterName}_InstanceTransform;`
- L46 _parameter_ `float4x4 {ParameterName}_InstancePrevTransform;`
- L47 _parameter_ `float4 {ParameterName}_InstanceRotation;`
- L48 _parameter_ `float4 {ParameterName}_InstancePrevRotation;`
- L49 _parameter_ `float {ParameterName}_InstanceInvDeltaTime;`
- L50 _parameter_ `float3 {ParameterName}_PreSkinnedLocalBoundsCenter;`
- L51 _parameter_ `float3 {ParameterName}_PreSkinnedLocalBoundsExtents;`
- L52 _parameter_ `uint {ParameterName}_EnabledFeatures;`

#### Functions (81)

- L61 _function_ `bool UniformTriangleSamplingEnable_{ParameterName}()` — Flags test
- L62 _function_ `bool UniformSamplingRegionEnabled_{ParameterName}()`
- L63 _function_ `bool UnlimitedBoneInfluences_{ParameterName}()`
- L64 _function_ `bool HasMeshColors_{ParameterName}()`
- L67 _function_ `bool UseDeformedPositions_{ParameterName}()` _[#if DISKELMESH_ALLOW_DEFORMED]_
- L68 _function_ `bool UseDeformedTangents_{ParameterName}()` _[#if DISKELMESH_ALLOW_DEFORMED]_
- L71-85 _function_ `void GetIndexWeight_{ParameterName}(int BoneIndexOffset, int BoneWeightOffset, int Layer, out int4 BlendIndices, out float4 BlendWeights)`
- L89-96 _function_ `void GetPreSkinnedLocalBounds_{ParameterName}(out float3 OutCenter, out float3 OutExtentsMin, out float3 OutExtentsMax, out float3 OutExtents, out float3 OutHalfExtents)` — Misc functions
- L100-103 _function_ `float3x4 GetPrevBoneSkinningMatrix_{ParameterName}(uint Bone)` — Triangle Sampling
- L105-113 _function_ `float3x4 GetPrevSkinningMatrix_{ParameterName}(uint SectionBoneOffset, int4 BlendIndices, float4 BlendWeights)`
- L115-118 _function_ `float3x4 GetCurrBoneSkinningMatrix_{ParameterName}(uint Bone)`
- L120-128 _function_ `float3x4 GetCurrSkinningMatrix_{ParameterName}(uint SectionBoneOffset, int4 BlendIndices, float4 BlendWeights)`
- L130-133 _function_ `void IsValidTriCoord_{ParameterName}(in int TriangleIndex, out bool IsValid)`
- L135-159 _function_ `void GetVertex_{ParameterName}(uint VertexIndex, out float3 OutPosition, out float3 OutTangentX, out float3 OutTangentY, out float3 OutTangentZ)`
- L161-164 _function_ `void GetVertexData_{ParameterName}(int VertexIndex, out float3 OutPosition, out float3 OutTangentX, out float3 OutTangentY, out float3 OutTangentZ)`
- L166-193 _function_ `void GetPointOnTriangle_{ParameterName}(uint TriangleIndex, float3 BaryCoord, out float3 OutPosition, out float3 OutTangentX, out float3 OutTangentY, out float3 OutTangentZ)`
- L195-335 _function_ `FDISkelMeshSkinnedVertex GetSkinnedVertex_{ParameterName}(uint VertexIndex)`
- L337-346 _function_ `FDISkelMeshSkinnedVertex GetSkinnedVertexWS_{ParameterName}(uint VertexIndex)`
- L348-381 _function_ `FDISkelMeshSkinnedVertex GetSkinnedPointOnTriangle_{ParameterName}(uint TriangleIndex, float3 BaryCoord)`
- L383-393 _function_ `FDISkelMeshSkinnedVertex GetSkinnedPointOnTriangleWS_{ParameterName}(uint TriangleIndex, float3 BaryCoord)`
- L395-441 _function_ `void RandomTriCoord_{ParameterName}(uint Seed1, uint Seed2, uint Seed3, out int OutTriangle, out float3 OutBaryCoord)`
- L443-451 _function_ `void GetSkinnedTriangleDataWS_{ParameterName}(in uint TriangleIndex, in float3 BaryCoord, out float3 OutPosition, out float3 OutVelocity, out float3 OutNormal, out float3 OutBinormal, out float3 OutTangent)`
- L453-461 _function_ `void GetSkinnedTriangleData_{ParameterName}(in uint TriangleIndex, in float3 BaryCoord, out float3 OutPosition, out float3 OutVelocity, out float3 OutNormal, out float3 OutBinormal, out float3 OutTangent)`
- L463-471 _function_ `void GetSkinnedTriangleDataInterpolatedWS_{ParameterName}(in uint TriangleIndex, in float3 BaryCoord, in float Interp, out float3 OutPosition, out float3 OutVelocity, out float3 OutNormal, out float3 OutBinormal, out float3 OutTangent)`
- L473-481 _function_ `void GetSkinnedTriangleDataInterpolated_{ParameterName}(in uint TriangleIndex, in float3 BaryCoord, in float Interp, out float3 OutPosition, out float3 OutVelocity, out float3 OutNormal, out float3 OutBinormal, out float3 OutTangent)`
- L483-539 _function_ `void GetSkinnedTriangleVertexDataHelper_{ParameterName}( int TriangleIndex, float Interp, bool bWorldSpace, out float3 Position0, out float3 Velocity0, out float3 Normal0, out float3 Binormal0, out float3 Tangent0, out float3 Position1, out float3 Velocity1, out float3 Normal1, out float3 Binormal1, out float3 Tangent1, out float3 Position2, out float3 Velocity2, out float3 Normal2, out float3 Binormal2, out float3 Tangent2 )`
- L541-552 _function_ `void GetSkinnedTriangleVertexData_{ParameterName}( int TriangleIndex, out float3 Position0, out float3 Velocity0, out float3 Normal0, out float3 Binormal0, out float3 Tangent0, out float3 Position1, out float3 Velocity1, out float3 Normal1, out float3 Binormal1, out float3 Tangent1, out float3 Position2, out float3 Velocity2, out float3 Normal2, out float3 Binormal2, out float3 Tangent2 )`
- L554-565 _function_ `void GetSkinnedTriangleVertexDataWS_{ParameterName}( int TriangleIndex, out float3 Position0, out float3 Velocity0, out float3 Normal0, out float3 Binormal0, out float3 Tangent0, out float3 Position1, out float3 Velocity1, out float3 Normal1, out float3 Binormal1, out float3 Tangent1, out float3 Position2, out float3 Velocity2, out float3 Normal2, out float3 Binormal2, out float3 Tangent2 )`
- L567-579 _function_ `void GetSkinnedTriangleVertexDataInterpolated_{ParameterName}( int TriangleIndex, float Interp, out float3 Position0, out float3 Velocity0, out float3 Normal0, out float3 Binormal0, out float3 Tangent0, out float3 Position1, out float3 Velocity1, out float3 Normal1, out float3 Binormal1, out float3 Tangent1, out float3 Position2, out float3 Velocity2, out float3 Normal2, out float3 Binormal2, out float3 Tangent2 )`
- L581-593 _function_ `void GetSkinnedTriangleVertexDataWSInterpolated_{ParameterName}( int TriangleIndex, float Interp, out float3 Position0, out float3 Velocity0, out float3 Normal0, out float3 Binormal0, out float3 Tangent0, out float3 Position1, out float3 Velocity1, out float3 Normal1, out float3 Binormal1, out float3 Tangent1, out float3 Position2, out float3 Velocity2, out float3 Normal2, out float3 Binormal2, out float3 Tangent2 )`
- L595-616 _function_ `void GetTriUV_{ParameterName}(in uint TriangleIndex, in float3 BaryCoord, in int UVSet, out float2 OutUV)`
- L618-650 _function_ `void RandomTriangle_{ParameterName}(uint Seed1, uint Seed2, uint Seed3, out int OutTriangle, out float3 OutBaryCoord)`
- L652-655 _function_ `void GetTriangleCount_{ParameterName}(out int OutCount)`
- L657-693 _function_ `void RandomFilteredTriangle_{ParameterName}(uint Seed1, uint Seed2, uint Seed3, out int OutTriangle, out float3 OutBaryCoord)`
- L695-698 _function_ `void GetFilteredTriangleCount_{ParameterName}(out int OutCount)`
- L700-711 _function_ `void GetFilteredTriangleAt_{ParameterName}(int FilteredIndex, out int OutTriangle)`
- L715-726 _function_ `void GetTriangleCoordAtUV_{ParameterName}(bool Enabled, float2 InUv, float InTolerance, out int OutTriangle, out float3 OutBaryCoord, out bool OutIsValid)` — Uv Mapping
- L728-739 _function_ `void GetTriangleCoordInAabb_{ParameterName}(bool Enabled, float2 InUvMin, float2 InUvMax, out int OutTriangle, out float3 OutBaryCoord, out bool OutIsValid)`
- L744-781 _function_ `void GetSkinnedBoneCommon_{ParameterName}(in int Bone, in float Interp, in bool bWorldSpace, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`
- L783-786 _function_ `void GetSkinnedBoneData_{ParameterName}(in int Bone, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`
- L788-791 _function_ `void GetSkinnedBoneDataInterpolated_{ParameterName}(in int Bone, in float Interp, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`
- L793-796 _function_ `void GetSkinnedBoneDataWS_{ParameterName}(in int Bone, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`
- L798-801 _function_ `void GetSkinnedBoneDataWSInterpolated_{ParameterName}(in int Bone, in float Interp, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`
- L806-822 _function_ `void GetTriVertices_{ParameterName}(in uint TriangleIndex, out int VertexIndex0, out int VertexIndex1, out int VertexIndex2)`
- L824-827 _function_ `void GetTriCoordVertices_{ParameterName}(in int TriangleIndex, out int VertexIndex0, out int VertexIndex1, out int VertexIndex2)`
- L829-832 _function_ `void GetTriangleIndices_{ParameterName}(int Tri, out int Index0, out int Index1, out int Index2)`
- L834-849 _function_ `void GetTriColor_{ParameterName}(in uint TriangleIndex, in float3 BaryCoord, out float4 OutColor)`
- L851-859 _function_ `void GetSkinnedVertexData_{ParameterName}(in int VertexIndex, out float3 OutPosition, out float3 OutVelocity, out float3 OutNormal, out float3 OutBinormal, out float3 OutTangent)`
- L861-870 _function_ `void GetSkinnedVertexDataWS_{ParameterName}(in int VertexIndex, out float3 OutPosition, out float3 OutVelocity, out float3 OutNormal, out float3 OutBinormal, out float3 OutTangent)`
- L872-880 _function_ `void GetSkinnedVertexDataInterpolated_{ParameterName}(in int VertexIndex, in float Interp, out float3 OutPosition, out float3 OutVelocity, out float3 OutNormal, out float3 OutBinormal, out float3 OutTangent)`
- L882-892 _function_ `void GetSkinnedVertexDataInterpolatedWS_{ParameterName}(in int VertexIndex, in float Interp, out float3 OutPosition, out float3 OutVelocity, out float3 OutNormal, out float3 OutBinormal, out float3 OutTangent)`
- L894-897 _function_ `void GetVertexColor_{ParameterName}(in int VertexIndex, out float4 OutColor)`
- L899-911 _function_ `void GetVertexUV_{ParameterName}(in int VertexIndex, in int UVSet, out float2 OutUV)`
- L913-916 _function_ `void IsValidVertex_{ParameterName}(int Vertex, out bool IsValid)`
- L918-922 _function_ `void RandomVertex_{ParameterName}(NiagaraRandInfo RandInfo, out int OutVertex)`
- L924-927 _function_ `void GetVertexCount_{ParameterName}(out int VertexCount)`
- L929-932 _function_ `void IsValidFilteredVertex_{ParameterName}(int FilteredIndex, out bool IsValid)`
- L934-946 _function_ `void RandomFilteredVertex_{ParameterName}(NiagaraRandInfo RandInfo, out int OutVertex)`
- L948-951 _function_ `void GetFilteredVertexCount_{ParameterName}(out int VertexCount)`
- L953-964 _function_ `void GetFilteredVertex_{ParameterName}(int FilteredIndex, out int VertexIndex)`
- L968-971 _function_ `void IsValidBone_{ParameterName}(in int BoneIndex, out bool IsValid)` — Filtered Bones / Sockets
- L973-978 _function_ `void RandomBone_{ParameterName}(NiagaraRandInfo RandInfo, out int Bone)`
- L980-983 _function_ `void GetBoneCount_{ParameterName}(out int Count)`
- L985-993 _function_ `void GetParentBone_{ParameterName}(int BoneIndex, out int ParentIndex)`
- L995-998 _function_ `void GetFilteredBoneCount_{ParameterName}(out int Count)`
- L1000-1004 _function_ `void GetFilteredBone_{ParameterName}(in int InBoneIndex, out int Bone)`
- L1006-1011 _function_ `void RandomFilteredBone_{ParameterName}(NiagaraRandInfo RandInfo, out int Bone)`
- L1013-1016 _function_ `void GetUnfilteredBoneCount_{ParameterName}(out int Count)`
- L1018-1022 _function_ `void GetUnfilteredBone_{ParameterName}(in int InBoneIndex, out int Bone)`
- L1024-1037 _function_ `void RandomUnfilteredBone_{ParameterName}(NiagaraRandInfo RandInfo, out int Bone)`
- L1039-1042 _function_ `void GetFilteredSocketCount_{ParameterName}(out int Count)`
- L1044-1068 _function_ `void GetFilteredSocketTransform_{ParameterName}(in int SocketIndex, in bool bApplyTransform, out float3 OutTranslation, out float4 OutRotation, out float3 OutScale)`
- L1070-1073 _function_ `void GetFilteredSocket_{ParameterName}(in int InSocketIndex, out int Bone)`
- L1075-1079 _function_ `void RandomFilteredSocket_{ParameterName}(NiagaraRandInfo RandInfo, out int SocketBone)`
- L1081-1094 _function_ `void RandomFilteredSocketOrBone_{ParameterName}(NiagaraRandInfo RandInfo, out int Bone)`
- L1096-1099 _function_ `void GetFilteredSocketOrBoneCount_{ParameterName}(out int Count)`
- L1101-1117 _function_ `void GetFilteredSocketOrBone_{ParameterName}(int FilteredIndex, out int Bone)`
- L1122-1146 _function_ `void GetAdjacentTriangleIndex_{ParameterName}(int VertexId, uint AdjacencyIndex, out int TriangleIndex)`
- L1148-1164 _function_ `bool IsAdjacent_{ParameterName}(int VertexIndex, int TriangleIndex)`
- L1166-1221 _function_ `void GetTriangleNeighbor_{ParameterName}(int TriangleIndex, int EdgeIndex, out int NeighborTriangleIndex, out int NeighborEdgeIndex, out bool IsValid)`
- L1223-1227 _function_ `void GetAdjacentTriangleIndex_{ParameterName}(in int VertexId, in int AdjacencyIndex, out int TriangleIndex, out bool IsValid)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceSocketReaderTemplate.ush` (Private)

- lines: 126; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/FX/Niagara/Private/NiagaraTransformUtils.ush`

#### Global resources (textures / buffers / samplers) (1)

- L18 _resource_ `ByteAddressBuffer {ParameterName}_SocketData;`

#### Global parameters (uniforms) (13)

- L5 _parameter_ `uint {ParameterName}_IsDataValid;`
- L6 _parameter_ `float {ParameterName}_InvDeltaSeconds;`
- L7 _parameter_ `int {ParameterName}_NumSockets;`
- L8 _parameter_ `int {ParameterName}_NumFilteredSockets;`
- L9 _parameter_ `int {ParameterName}_NumUnfilteredSockets;`
- L10 _parameter_ `float3 {ParameterName}_ComponentToTranslatedWorld_Translation;`
- L11 _parameter_ `float4 {ParameterName}_ComponentToTranslatedWorld_Rotation;`
- L12 _parameter_ `float3 {ParameterName}_ComponentToTranslatedWorld_Scale;`
- L13 _parameter_ `float3 {ParameterName}_PreviousComponentToTranslatedWorld_Translation;`
- L14 _parameter_ `float4 {ParameterName}_PreviousComponentToTranslatedWorld_Rotation;`
- L15 _parameter_ `float3 {ParameterName}_PreviousComponentToTranslatedWorld_Scale;`
- L16 _parameter_ `uint {ParameterName}_SocketTransformOffset;`
- L17 _parameter_ `uint {ParameterName}_PreviousSocketTransformOffset;`

#### Functions (15)

- L23-26 _function_ `int SanitizeSocketIndex_{ParameterName}(int SocketIndex)`
- L28-32 _function_ `int SanitizeFilteredSocketIndex_{ParameterName}(int SocketIndex)`
- L34-38 _function_ `int SanitizeUnfilteredSocketIndex_{ParameterName}(int SocketIndex)`
- L40-60 _function_ `void GetSocketData_{ParameterName}(int SocketIndex, float Interp, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`
- L64-69 _function_ `void GetComponentToWorld_{ParameterName}(out float3 Translation, out float4 Rotation, out float3 Scale)`
- L71-74 _function_ `void IsValid_{ParameterName}(out bool bValid)`
- L76-79 _function_ `void GetSocketCount_{ParameterName}(out int Count)`
- L81-84 _function_ `void GetFilteredSocketCount_{ParameterName}(out int Count)`
- L86-89 _function_ `void GetUnfilteredSocketCount_{ParameterName}(out int Count)`
- L91-95 _function_ `void GetSocketTransform_{ParameterName}(int SocketIndex, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`
- L97-101 _function_ `void GetFilteredSocketTransform_{ParameterName}(int SocketIndex, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`
- L103-107 _function_ `void GetUnfilteredSocketTransform_{ParameterName}(int SocketIndex, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`
- L109-113 _function_ `void GetSocketTransformInterpolated_{ParameterName}(int SocketIndex, float Interpolation, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`
- L115-119 _function_ `void GetFilteredSocketTransformInterpolated_{ParameterName}(int SocketIndex, float Interpolation, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`
- L121-125 _function_ `void GetUnfilteredSocketTransformInterpolated_{ParameterName}(int SocketIndex, float Interpolation, out float3 OutPosition, out float4 OutRotation, out float3 OutScale, out float3 OutVelocity)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceSparseVolumeTextureTemplate.ush` (Private)

- lines: 47; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Engine/Private/SparseVolumeTexture/SparseVolumeTextureCommon.ush`

#### Global resources (textures / buffers / samplers) (4)

- L5 _resource_ `SamplerState {ParameterName}_TileDataTextureSampler;`
- L6 _resource_ `Texture3D<uint> {ParameterName}_PageTableTexture;`
- L7 _resource_ `Texture3D {ParameterName}_PhysicalTileDataATexture;`
- L8 _resource_ `Texture3D {ParameterName}_PhysicalTileDataBTexture;`

#### Global parameters (uniforms) (5)

- L9 _parameter_ `uint4 {ParameterName}_PackedUniforms0;`
- L10 _parameter_ `uint4 {ParameterName}_PackedUniforms1;`
- L11 _parameter_ `int3 {ParameterName}_TextureSize;`
- L12 _parameter_ `int {ParameterName}_MipLevels;`
- L13 _parameter_ `int {ParameterName}_NumFrames;`

#### Functions (5)

- L16-22 _function_ `void LoadSparseVolumeTexture_{ParameterName}(in int TexelX, in int TexelY, in int TexelZ, in int MipLevel, out float4 OutAttributesA, out float4 OutAttributesB)`
- L24-30 _function_ `void SampleSparseVolumeTexture_{ParameterName}(in float3 UVW, in int MipLevel, out float4 OutAttributesA, out float4 OutAttributesB)`
- L32-37 _function_ `void GetTextureDimensions_{ParameterName}(int MipLevel, out int SizeX, out int SizeY, out int SizeZ)`
- L39-42 _function_ `void GetNumMipLevels_{ParameterName}(out int OutMipLevels)`
- L44-47 _function_ `void GetNumFrames_{ParameterName}(out int OutNumFrames)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceSplineTemplate.ush` (Private)

- lines: 226; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (3)

- L14 _resource_ `Buffer<float4> {ParameterName}_SplinePositionsLUT;`
- L15 _resource_ `Buffer<float4> {ParameterName}_SplineScalesLUT;`
- L16 _resource_ `Buffer<float4> {ParameterName}_SplineRotationsLUT;`

#### Global parameters (uniforms) (10)

- L3 _parameter_ `float4x4 {ParameterName}_SplineTransform;`
- L4 _parameter_ `float4x4 {ParameterName}_SplineTransformRotationMat;`
- L5 _parameter_ `float4x4 {ParameterName}_SplineTransformInverse;`
- L6 _parameter_ `float4x4 {ParameterName}_SplineTransformInverseTranspose;`
- L7 _parameter_ `float4 {ParameterName}_SplineTransformRotation;`
- L8 _parameter_ `float3 {ParameterName}_DefaultUpVector;`
- L9 _parameter_ `float {ParameterName}_SplineLength;`
- L10 _parameter_ `float {ParameterName}_SplineDistanceStep;`
- L11 _parameter_ `float {ParameterName}_InvSplineDistanceStep;`
- L12 _parameter_ `int {ParameterName}_MaxIndex;`

#### Functions (23)

- L18-24 _function_ `void FindNeighborKeys_{ParameterName}(float InDistance, out int PrevKey, out int NextKey, out float Alpha)`
- L26-42 _function_ `float3 EvaluatePosition_{ParameterName}(float InDistance)`
- L44-60 _function_ `float3 EvaluateScale_{ParameterName}(float InDistance)`
- L62-78 _function_ `float4 EvaluateRotation_{ParameterName}(float InDistance)`
- L80-84 _function_ `float4 GetRotationAtDistanceAlongSpline_{ParameterName}(float InDistance)`
- L86-113 _function_ `float3 EvaluateDerivativePosition_{ParameterName}(float InDistance)`
- L115-134 _function_ `float EvaluateFindNearestPosition_{ParameterName}(float3 InPosition)`
- L136-139 _function_ `void SampleSplinePositionByUnitDistance_{ParameterName}(float U, out float3 Position)`
- L141-145 _function_ `void SampleSplinePositionByUnitDistanceWS_{ParameterName}(float U, out float3 Position)`
- L147-150 _function_ `void SampleSplineRotationByUnitDistance_{ParameterName}(float U, out float4 Rotation)`
- L152-156 _function_ `void SampleSplineRotationByUnitDistanceWS_{ParameterName}(float U, out float4 Rotation)`
- L158-161 _function_ `void SampleSplineDirectionByUnitDistance_{ParameterName}(float U, out float3 Direction)`
- L163-167 _function_ `void SampleSplineDirectionByUnitDistanceWS_{ParameterName}(float U, out float3 Direction)`
- L169-173 _function_ `void SampleSplineUpVectorByUnitDistance_{ParameterName}(float U, out float3 UpVector)`
- L175-180 _function_ `void SampleSplineUpVectorByUnitDistanceWS_{ParameterName}(float U, out float3 UpVector)`
- L182-186 _function_ `void SampleSplineRightVectorByUnitDistance_{ParameterName}(float U, out float3 RightVector)`
- L188-193 _function_ `void SampleSplineRightVectorByUnitDistanceWS_{ParameterName}(float U, out float3 RightVector)`
- L195-198 _function_ `void SampleSplineTangentByUnitDistance_{ParameterName}(float U, out float3 Tangent)`
- L200-204 _function_ `void SampleSplineTangentByUnitDistanceWS_{ParameterName}(float U, out float3 Tangent)`
- L206-209 _function_ `void GetSplineLocalToWorld_{ParameterName}(out float4x4 Transform)`
- L211-214 _function_ `void GetSplineLocalToWorldInverseTransposed_{ParameterName}(out float4x4 Transform)`
- L216-220 _function_ `void FindClosestUnitDistanceFromPositionWS_{ParameterName}(float3 PositionWS, out float U)`
- L222-225 _function_ `void GetSplineLength_{ParameterName}(out float Length)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceSpriteRendererInfoTemplate.ush` (Private)

- lines: 36; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (6)

- L3 _parameter_ `uint {ParameterName}_bIsValid;`
- L4 _parameter_ `int {ParameterName}_SourceMode;`
- L5 _parameter_ `int {ParameterName}_Alignment;`
- L6 _parameter_ `int {ParameterName}_FacingMode;`
- L7 _parameter_ `uint {ParameterName}_bSubImageBlend;`
- L8 _parameter_ `float2 {ParameterName}_SubImageSize;`

#### Functions (5)

- L10-13 _function_ `void IsValid_{ParameterName}(out bool bIsValid)`
- L15-18 _function_ `void GetSourceMode_{ParameterName}(out int SourceMode)`
- L20-23 _function_ `void GetAlignment_{ParameterName}(out int Alignment)`
- L25-28 _function_ `void GetFacingMode_{ParameterName}(out int FacingMode)`
- L30-34 _function_ `void GetSubUVDetails_{ParameterName}(out bool bBlendEnabled, out float2 SubImageSize)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceStaticMeshIndirectTemplate.ush` (Private)

- lines: 69; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/FX/Niagara/Private/NiagaraQuaternionUtils.ush`, L4 `/Plugin/FX/Niagara/Private/NiagaraDistanceFieldQueries.ush`, L5 `/Plugin/FX/Niagara/Private/NiagaraSharedDataGPU_StaticMesh.ush`

#### Functions (2)

- L10-33 _function_ `void QueryDistanceField_{ParameterName}(bool bExecute, float3 WorldPosition, NiagaraSharedDataID_StaticMesh StaticMeshID, bool bUseMaxDistance, float MaxDistance, out bool OutIsValid, out float OutDistance)`
- L35-69 _function_ `void GetClosestPointOnMeshDistanceField_{ParameterName}(bool bExecute, float3 WorldPosition, NiagaraSharedDataID_StaticMesh StaticMeshID, bool bUseMaxDistance, float MaxDistance, out bool OutIsValid, out float OutClosestDistance, out float3 OutClosestPosition, out float3 OutClosestNormal, out float OutMaxEncodedDistance, out bool OutNormalIsValid)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceStaticMeshTemplate.ush` (Private)

- lines: 817; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/FX/Niagara/Private/NiagaraQuaternionUtils.ush`

#### Global resources (textures / buffers / samplers) (11)

- L9 _resource_ `Buffer<uint> {ParameterName}_IndexBuffer;`
- L10 _resource_ `Buffer<float> {ParameterName}_PositionBuffer;`
- L11 _resource_ `Buffer<float4> {ParameterName}_TangentBuffer;`
- L12 _resource_ `Buffer<float2> {ParameterName}_UVBuffer;`
- L13 _resource_ `Buffer<float4> {ParameterName}_ColorBuffer;`
- L16 _resource_ `Buffer<uint2> {ParameterName}_UniformSamplingTriangles;`
- L19 _resource_ `Buffer<uint4> {ParameterName}_SectionInfos;` — FirstTriangle, NumTriangles, Prob, Alias
- L20 _resource_ `Buffer<uint> {ParameterName}_FilteredAndUnfilteredSections;`
- L23 _resource_ `Buffer<float4> {ParameterName}_SocketTransforms;`
- L24 _resource_ `Buffer<uint> {ParameterName}_FilteredAndUnfilteredSockets;`
- L45 _resource_ `Buffer<int> {ParameterName}_UvMappingBuffer;`

#### Global parameters (uniforms) (23)

- L5 _parameter_ `int3 {ParameterName}_NumTriangles;` — x = Num Sections, y = Num Filtered, z = Num Unfiltered
- L6 _parameter_ `int {ParameterName}_NumVertices;`
- L7 _parameter_ `int {ParameterName}_NumUVs;`
- L8 _parameter_ `uint {ParameterName}_HasColors;`
- L15 _parameter_ `uint {ParameterName}_HasUniformSampling;`
- L18 _parameter_ `int3 {ParameterName}_SectionCounts;` — x = Num Sections, y = Num Filtered, z = Num Unfiltered
- L22 _parameter_ `int3 {ParameterName}_SocketCounts;` — x = Num Sockets, y = Num Filtered, z = Num Unfiltered
- L26 _parameter_ `float {ParameterName}_InvDeltaSeconds;`
- L27 _parameter_ `float4x4 {ParameterName}_InstanceTransform;`
- L28 _parameter_ `float4x4 {ParameterName}_InstanceTransformInverseTransposed;`
- L29 _parameter_ `float4 {ParameterName}_InstanceRotation;`
- L30 _parameter_ `float4x4 {ParameterName}_InstancePreviousTransform;`
- L31 _parameter_ `float4x4 {ParameterName}_InstancePreviousTransformInverseTransposed;`
- L32 _parameter_ `float4 {ParameterName}_InstancePreviousRotation;`
- L33 _parameter_ `float3 {ParameterName}_InstanceWorldVelocity;`
- L35 _parameter_ `float3 {ParameterName}_PreSkinnedLocalBoundsCenter;`
- L36 _parameter_ `float3 {ParameterName}_PreSkinnedLocalBoundsExtents;`
- L37 _parameter_ `float3 {ParameterName}_MeshBoundsWSCenter;`
- L38 _parameter_ `float3 {ParameterName}_MeshBoundsWSExtents;`
- L39 _parameter_ `float3 {ParameterName}_OwnerToMeshVector;`
- L42 _parameter_ `int {ParameterName}_InstanceDistanceFieldIndex;` _[#if DISTATICMESH_ALLOWDISTANCEFIELD]_
- L46 _parameter_ `uint {ParameterName}_UvMappingBufferLength;`
- L47 _parameter_ `uint {ParameterName}_UvMappingSet;`

#### Functions (65)

- L58-64 _function_ `int UniformTriangle_{ParameterName}(NiagaraRandInfo RandInfo, int Tri, int SectionOffset)` — Misc functions
- L66-73 _function_ `void GetPreSkinnedLocalBounds_{ParameterName}(out float3 OutCenter, out float3 OutExtentsMin, out float3 OutExtentsMax, out float3 OutExtents, out float3 OutHalfExtents)`
- L77-80 _function_ `void IsValidVertex_{ParameterName}(out bool IsValid)` — Vertex Sampling
- L82-85 _function_ `void RandomVertex_{ParameterName}(NiagaraRandInfo RandInfo, out int Vertex)`
- L87-90 _function_ `void GetVertexCount_{ParameterName}(out int Count)`
- L92-131 _function_ `void GetVertex_{ParameterName}(int Vertex, out float3 Position, out float3 Velocity, out float3 Normal, out float3 Bitangent, out float3 Tangent)`
- L133-144 _function_ `void GetVertexWS_{ParameterName}(int Vertex, out float3 Position, out float3 Velocity, out float3 Normal, out float3 Bitangent, out float3 Tangent)`
- L146-166 _function_ `void GetVertexWSInterpolated_{ParameterName}(int Vertex, float Interp, out float3 Position, out float3 Velocity, out float3 Normal, out float3 Bitangent, out float3 Tangent)`
- L168-172 _function_ `void GetVertexColor_{ParameterName}(int Vertex, out float4 Color)`
- L174-179 _function_ `void GetVertexUV_{ParameterName}(int Vertex, int UVSet, out float2 UV)`
- L183-186 _function_ `void IsValidTriangle_{ParameterName}(int Tri, out bool IsValid)` — VM Triangle Sampling
- L188-193 _function_ `void RandomTriangle_{ParameterName}(NiagaraRandInfo RandInfo, out int Tri, out float3 BaryCoord)`
- L195-198 _function_ `void GetTriangleCount_{ParameterName}(out int Count)`
- L200-203 _function_ `void IsValidFilteredTriangle_{ParameterName}(int Tri, out bool IsValid)`
- L205-218 _function_ `void RandomFilteredTriangle_{ParameterName}(NiagaraRandInfo RandInfo, out int Tri, out float3 BaryCoord)`
- L220-223 _function_ `void GetFilteredTriangleCount_{ParameterName}(out int Count)`
- L225-241 _function_ `void GetFilteredTriangleAt_{ParameterName}(int TriangleIndex, out int Tri)`
- L243-246 _function_ `void IsValidUnfilteredTriangle_{ParameterName}(int Tri, out bool IsValid)`
- L248-261 _function_ `void RandomUnfilteredTriangle_{ParameterName}(NiagaraRandInfo RandInfo, out int Tri, out float3 BaryCoord)`
- L263-266 _function_ `void GetUnfilteredTriangleCount_{ParameterName}(out int Count)`
- L268-284 _function_ `void GetUnfilteredTriangleAt_{ParameterName}(int TriangleIndex, out int Tri)`
- L286-302 _function_ `void GetTriangleIndices_{ParameterName}(int Tri, out int Index0, out int Index1, out int Index2)`
- L304-319 _function_ `void GetTriangle_{ParameterName}(int Tri, float3 BaryCoord, out float3 Position, out float3 Velocity, out float3 Normal, out float3 Bitangent, out float3 Tangent)`
- L321-332 _function_ `void GetTriangleWS_{ParameterName}(int Tri, float3 BaryCoord, out float3 Position, out float3 Velocity, out float3 Normal, out float3 Bitangent, out float3 Tangent)`
- L334-354 _function_ `void GetTriangleWSInterpolated_{ParameterName}(int Tri, float3 BaryCoord, float Interp, out float3 Position, out float3 Velocity, out float3 Normal, out float3 Bitangent, out float3 Tangent)`
- L356-367 _function_ `void GetTriangleColor_{ParameterName}(int Tri, float3 BaryCoord, out float4 Color)`
- L369-380 _function_ `void GetTriangleUV_{ParameterName}(int Tri, float3 BaryCoord, int UVSet, out float2 UV)`
- L384-387 _function_ `void GetSocketCount_{ParameterName}(out int Count)` — Socket Functions
- L389-392 _function_ `void GetFilteredSocketCount_{ParameterName}(out int Count)`
- L394-397 _function_ `void GetUnfilteredSocketCount_{ParameterName}(out int Count)`
- L399-407 _function_ `void GetFilteredSocket_{ParameterName}(int Index, out int SocketIndex)`
- L409-417 _function_ `void GetUnfilteredSocket_{ParameterName}(int Index, out int SocketIndex)`
- L419-426 _function_ `void RandomSocket_{ParameterName}(NiagaraRandInfo RandInfo, out int Index)`
- L428-436 _function_ `void RandomFilteredSocket_{ParameterName}(NiagaraRandInfo RandInfo, out int Index)`
- L438-446 _function_ `void RandomUnfilteredSocket_{ParameterName}(NiagaraRandInfo RandInfo, out int Index)`
- L448-466 _function_ `void GetSocketTransform_{ParameterName}(int Socket, out float3 Position, out float4 Rotation, out float3 Scale, out float3 Velocity)`
- L468-478 _function_ `void GetSocketTransformWS_{ParameterName}(int Socket, out float3 Position, out float4 Rotation, out float3 Scale, out float3 Velocity)`
- L480-497 _function_ `void GetSocketTransformWSInterpolated_{ParameterName}(int Socket, float Interp, out float3 Position, out float4 Rotation, out float3 Scale, out float3 Velocity)`
- L499-516 _function_ `void GetFilteredSocketTransform_{ParameterName}(int SocketIndex, out float3 Position, out float4 Rotation, out float3 Scale, out float3 Velocity)`
- L518-528 _function_ `void GetFilteredSocketTransformWS_{ParameterName}(int SocketIndex, out float3 Position, out float4 Rotation, out float3 Scale, out float3 Velocity)`
- L530-535 _function_ `void GetFilteredSocketTransformWSInterpolated_{ParameterName}(int Index, float Interp, out float3 Position, out float4 Rotation, out float3 Scale, out float3 Velocity)`
- L537-554 _function_ `void GetUnfilteredSocketTransform_{ParameterName}(int SocketIndex, out float3 Position, out float4 Rotation, out float3 Scale, out float3 Velocity)`
- L556-566 _function_ `void GetUnfilteredSocketTransformWS_{ParameterName}(int SocketIndex, out float3 Position, out float4 Rotation, out float3 Scale, out float3 Velocity)`
- L568-573 _function_ `void GetUnfilteredSocketTransformWSInterpolated_{ParameterName}(int Index, float Interp, out float3 Position, out float4 Rotation, out float3 Scale, out float3 Velocity)`
- L577-580 _function_ `void IsValidSection_{ParameterName}(int Section, out bool IsValid)` — Section functions
- L582-585 _function_ `void GetSectionTriangleCount_{ParameterName}(int Section, out int Count)`
- L587-605 _function_ `void RandomSectionTriangle_{ParameterName}(NiagaraRandInfo RandInfo, int Section, out int Tri, out float3 BaryCoord)`
- L607-622 _function_ `void GetSectionTriangleAt_{ParameterName}(int Section, int SectionTriangleIndex, out int Tri)`
- L624-636 _function_ `void GetFilteredSectionAt_{ParameterName}(int SectionIndex, out int Section)`
- L638-651 _function_ `void GetUnfilteredSectionAt_{ParameterName}(int SectionIndex, out int Section)`
- L653-656 _function_ `void GetSectionCount_{ParameterName}(out int Count)`
- L658-661 _function_ `void GetFilteredSectionCount_{ParameterName}(out int Count)`
- L663-666 _function_ `void GetUnfilteredSectionCount_{ParameterName}(out int Count)`
- L668-682 _function_ `void RandomSection_{ParameterName}(NiagaraRandInfo RandInfo, out int Section)`
- L684-701 _function_ `void RandomFilteredSection_{ParameterName}(NiagaraRandInfo RandInfo, out int Section)`
- L703-721 _function_ `void RandomUnfilteredSection_{ParameterName}(NiagaraRandInfo RandInfo, out int Section)`
- L725-728 _function_ `void IsValid_{ParameterName}(out bool IsValid)` — VM Misc Functions
- L730-733 _function_ `void GetLocalToWorld_{ParameterName}(out float4x4 OutMatrix)`
- L735-738 _function_ `void GetLocalToWorldInverseTransposed_{ParameterName}(out float4x4 OutMatrix)`
- L740-743 _function_ `void GetWorldVelocity_{ParameterName}(out float3 Velocity)`
- L745-753 _function_ `void GetMeshBounds_{ParameterName}(out float3 Center, out float3 ExtentsMin, out float3 ExtentsMax, out float3 Extents, out float3 HalfExtents, out float3 OwnerToMeshVector)`
- L755-763 _function_ `void GetMeshBoundsWS_{ParameterName}(out float3 Center, out float3 ExtentsMin, out float3 ExtentsMax, out float3 Extents, out float3 HalfExtents, out float3 OwnerToMeshVector)`
- L767-789 _function_ `void QueryDistanceField_{ParameterName}(bool bExecute, float3 WorldPosition, bool bUseMaxDistance, float MaxDistance, out bool OutIsValid, out float OutDistance)` — Experimental Distance Field Functions
- L793-804 _function_ `void GetTriangleCoordAtUV_{ParameterName}(bool Enabled, float2 InUv, float InTolerance, out int OutTriangle, out float3 OutBaryCoord, out bool OutIsValid)` — Uv Mapping
- L806-817 _function_ `void GetTriangleCoordInAabb_{ParameterName}(bool Enabled, float2 InUvMin, float2 InUvMax, out int OutTriangle, out float3 OutBaryCoord, out bool OutIsValid)`

#### Prototypes (4)

- L51 _prototype_ `void RandomSection_{ParameterName}(NiagaraRandInfo RandInfo, out int Section)` — Fwd declarations
- L52 _prototype_ `void RandomFilteredSection_{ParameterName}(NiagaraRandInfo RandInfo, out int Section)`
- L53 _prototype_ `void RandomUnfilteredSection_{ParameterName}(NiagaraRandInfo RandInfo, out int Section)`
- L54 _prototype_ `void RandomSectionTriangle_{ParameterName}(NiagaraRandInfo RandInfo, int Section, out int Tri, out float3 BaryCoord)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceTexture2DArrayTemplate.ush` (Private)

- lines: 26; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (2)

- L4 _resource_ `Texture2DArray {ParameterName}_Texture;`
- L5 _resource_ `SamplerState {ParameterName}_TextureSampler;`

#### Global parameters (uniforms) (1)

- L3 _parameter_ `float3 {ParameterName}_TextureSize;`

#### Functions (4)

- L7-10 _function_ `void LoadTexture_{ParameterName}(in int TexelX, in int TexelY, in int TexelZ, in int MipLevel, out float4 OutValue)`
- L12-15 _function_ `void GatherRedTexture_{ParameterName}(in float3 UVW, out float4 OutValue)`
- L17-20 _function_ `void SampleTexture_{ParameterName}(in float3 UVW, in float MipLevel, out float4 OutValue)`
- L22-25 _function_ `void TextureDimensions_{ParameterName}(out float3 OutValue)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceTextureTemplate.ush` (Private)

- lines: 38; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D {ParameterName}_Texture;`
- L6 _resource_ `SamplerState {ParameterName}_TextureSampler;`

#### Global parameters (uniforms) (2)

- L3 _parameter_ `int2 {ParameterName}_TextureSize;`
- L4 _parameter_ `int {ParameterName}_MipLevels;`

#### Functions (6)

- L8-11 _function_ `void LoadTexture2D_{ParameterName}(in int TexelX, in int TexelY, in int MipLevel, out float4 OutValue)`
- L13-16 _function_ `void GatherRedTexture2D_{ParameterName}(in float2 UV, out float4 OutValue)`
- L18-21 _function_ `void SampleTexture2D_{ParameterName}(in float2 UV, in float MipLevel, out float4 OutValue)`
- L23-27 _function_ `void GetTextureDimensions_{ParameterName}(int MipLevel, out float2 OutValue)`
- L29-32 _function_ `void GetNumMipLevels_{ParameterName}(out int OutMipLevels)`
- L34-37 _function_ `void SamplePseudoVolumeTexture_{ParameterName}(in float3 UVW, in float2 XYNumFrames, in float TotalNumFrames, in int MipMode, in float MipLevel, in float2 DDX, in float2 DDY, out float4 OutValue)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceVirtualTexture.ush` (Private)

- lines: 22; parse: all-branches
- includes: L9 `/Engine/Private/VirtualTextureCommon.ush`

#### Macros (#define, 10)

- L6 `#define NUM_VIRTUALTEXTURE_SAMPLES 1` _[#if !defined(NUM_VIRTUALTEXTURE_SAMPLES)]_
- L12 `#define ERuntimeVirtualTextureMaterialType_BaseColor 0`
- L13 `#define ERuntimeVirtualTextureMaterialType_Mask4 1`
- L14 `#define ERuntimeVirtualTextureMaterialType_BaseColor_Normal_Roughness 2`
- L15 `#define ERuntimeVirtualTextureMaterialType_BaseColor_Normal_Specular 3`
- L16 `#define ERuntimeVirtualTextureMaterialType_BaseColor_Normal_Specular_YCoCg 4`
- L17 `#define ERuntimeVirtualTextureMaterialType_BaseColor_Normal_Specular_Mask_YCoCg 5`
- L18 `#define ERuntimeVirtualTextureMaterialType_WorldHeight 6`
- L19 `#define ERuntimeVirtualTextureMaterialType_Displacement 7`
- L20 `#define ERuntimeVirtualTextureMaterialType_Count 8`
- L3 #pragma `once`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceVirtualTextureSampleTemplate.ush` (Private)

- lines: 42; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L7 `/Engine/Private/VirtualTextureCommon.ush`

#### Macros (#define, 2)

- L3 `#define NUM_VIRTUALTEXTURE_SAMPLES 0`
- L5 `#define VT_DISABLE_VIEW_UNIFORM_BUFFER 1`

#### Global resources (textures / buffers / samplers) (4)

- L12 _resource_ `Texture2D<uint4> {ParameterName}_PageTableTexture0;`
- L13 _resource_ `Texture2D<uint4> {ParameterName}_PageTableTexture1;`
- L14 _resource_ `Texture2D {ParameterName}_PhysicalTexture;`
- L19 _resource_ `SamplerState {ParameterName}_TextureSampler;`

#### Global parameters (uniforms) (4)

- L9 _parameter_ `int2 {ParameterName}_TextureSize;`
- L10 _parameter_ `int {ParameterName}_MipLevels;`
- L16 _parameter_ `uint4 {ParameterName}_VTPackedPageTableUniform[2];`
- L17 _parameter_ `uint4 {ParameterName}_VTPackedUniform;`

#### Functions (3)

- L21-28 _function_ `void SampleTexture2D_{ParameterName}(in float2 UV, in float MipLevel, out float4 OutValue)`
- L30-34 _function_ `void GetTextureDimensions_{ParameterName}(int MipLevel, out float2 OutValue)`
- L36-39 _function_ `void GetNumMipLevels_{ParameterName}(out int OutMipLevels)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceVirtualTextureTemplate.ush` (Private)

- lines: 178; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (7)

- L3 _resource_ `Texture2D {ParameterName}_VirtualTexture0;`
- L4 _resource_ `Texture2D<uint4> {ParameterName}_VirtualTexture0PageTable;`
- L7 _resource_ `Texture2D {ParameterName}_VirtualTexture1;`
- L8 _resource_ `Texture2D<uint4> {ParameterName}_VirtualTexture1PageTable;`
- L11 _resource_ `Texture2D {ParameterName}_VirtualTexture2;`
- L12 _resource_ `Texture2D<uint4> {ParameterName}_VirtualTexture2PageTable;`
- L20 _resource_ `SamplerState {ParameterName}_SharedSampler;`

#### Global parameters (uniforms) (8)

- L5 _parameter_ `uint4 {ParameterName}_VirtualTexture0TextureUniforms;`
- L9 _parameter_ `uint4 {ParameterName}_VirtualTexture1TextureUniforms;`
- L13 _parameter_ `uint4 {ParameterName}_VirtualTexture2TextureUniforms;`
- L15 _parameter_ `uint {ParameterName}_ValidLayersMask;`
- L16 _parameter_ `int {ParameterName}_MaterialType;`
- L17 _parameter_ `float4 {ParameterName}_UVUniforms[3];`
- L18 _parameter_ `uint4 {ParameterName}_PageTableUniforms[2];`
- L19 _parameter_ `float2 {ParameterName}_WorldHeightUnpack;`

#### Functions (3)

- L22-79 _function_ `void GetAttributesValid_{ParameterName}(out bool BaseColorValid, out bool SpecularValid, out bool RoughnessValid, out bool NormalValid, out bool WorldHeightValid, out bool MaskValid, out bool DisplacementValid, out bool Mask4Valid)`
- L81-85 _function_ `float4 SampleRVTLayer_{ParameterName}(float2 SampleUV, Texture2D InTexture, Texture2D<uint4> InPageTable, uint4 InTextureUniforms)`
- L87-177 _function_ `void SampleRVT_{ParameterName}(in float3 WorldPosition, out bool bInsideVolume, out float3 BaseColor, out float Specular, out float Roughness, out float3 Normal, out float WorldHeight, out float Mask, out float Displacement, out float4 Mask4)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceVolumeCache.ush` (Private)

- lines: 26; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (2)

- L4 _resource_ `Texture3D {ParameterName}_Texture;`
- L5 _resource_ `SamplerState {ParameterName}_TextureSampler;`

#### Global parameters (uniforms) (1)

- L3 _parameter_ `float3 {ParameterName}_TextureSize;`

#### Functions (4)

- L7-10 _function_ `void SampleCurrentFrameValue_{ParameterName}(in float3 UV, in float MipLevel, out float4 OutValue)`
- L12-15 _function_ `void GetCurrentFrameValue_{ParameterName}(in int x, in int y, in int z, in float MipLevel, out float4 OutValue)`
- L17-20 _function_ `void GetCurrentFrameNumCells_{ParameterName}(out float3 OutValue)`
- L22-25 _function_ `void IndexToUnit_{ParameterName}(float3 Index, out float3 Unit)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDataInterfaceVolumeTextureTemplate.ush` (Private)

- lines: 21; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (2)

- L4 _resource_ `Texture3D {ParameterName}_Texture;`
- L5 _resource_ `SamplerState {ParameterName}_TextureSampler;`

#### Global parameters (uniforms) (1)

- L3 _parameter_ `float3 {ParameterName}_TextureSize;`

#### Functions (3)

- L7-10 _function_ `void LoadVolumeTexture_{ParameterName}(in int TexelX, in int TexelY, in int TexelZ, in int MipLevel, out float4 OutValue)`
- L12-15 _function_ `void SampleVolumeTexture_{ParameterName}(in float3 UV, in float MipLevel, out float4 OutValue)`
- L17-20 _function_ `void TextureDimensions3D_{ParameterName}(out float3 OutValue)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDebugDraw.usf` (Private)

- lines: 79; parse: all-branches
- includes: L7 `/Engine/Private/Common.ush`, L8 `NiagaraCommon.ush`, L9 `NiagaraDebugDraw.ush`

#### Entry points (3)

- L18-25 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void MainCS(in uint3 ThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraClearUAVCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraDebugShaders.cpp:117) _[#if NIAGARA_DEBUGDRAW_CLEARUAV_UINT_CS]_
- L33-49 _entry_ `void MainVS( in uint InstanceID : SV_InstanceID, in uint VertexID : SV_VertexID, out float4 OutPosition : SV_POSITION, out float4 OutColor : TEXCOORD0 )` — stage: **vertex (from C++ binding)** — C++: `FNiagaraDebugDrawLineVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraDebugShaders.cpp:184) _[#if NIAGARA_DEBUGDRAW_DRAWLINE_VS]_
- L62-77 _entry_ `void MainPS ( in float4 Position : SV_POSITION, in float4 Color : TEXCOORD0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FNiagaraDebugDrawLinePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraDebugShaders.cpp:185) _[#if NIAGARA_DEBUGDRAW_DRAWLINE_PS]_

#### Global resources (textures / buffers / samplers) (4)

- L14 _resource_ `RWBuffer<uint> BufferToClear;` _[#if NIAGARA_DEBUGDRAW_CLEARUAV_UINT_CS]_
- L31 _resource_ `Buffer<uint> GpuLineBuffer;` _[#if NIAGARA_DEBUGDRAW_DRAWLINE_VS]_
- L54 _resource_ `Texture2D<float> DepthTexture;` _[#if NIAGARA_DEBUGDRAW_DRAWLINE_PS]_
- L55 _resource_ `SamplerState DepthSampler;` _[#if NIAGARA_DEBUGDRAW_DRAWLINE_PS]_

#### Global parameters (uniforms) (7)

- L15 _parameter_ `uint4 ClearValue;` _[#if NIAGARA_DEBUGDRAW_CLEARUAV_UINT_CS]_
- L16 _parameter_ `uint ClearSize;` _[#if NIAGARA_DEBUGDRAW_CLEARUAV_UINT_CS]_
- L56 _parameter_ `float2 OutputInvResolution;` _[#if NIAGARA_DEBUGDRAW_DRAWLINE_PS]_
- L57 _parameter_ `float2 OriginalViewRectMin;` _[#if NIAGARA_DEBUGDRAW_DRAWLINE_PS]_
- L58 _parameter_ `float2 OriginalViewSize;` _[#if NIAGARA_DEBUGDRAW_DRAWLINE_PS]_
- L59 _parameter_ `float2 OriginalBufferInvSize;` _[#if NIAGARA_DEBUGDRAW_DRAWLINE_PS]_
- L60 _parameter_ `float OccludedColorScale;` _[#if NIAGARA_DEBUGDRAW_DRAWLINE_PS]_

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDebugDraw.ush` (Private)

- lines: 53; parse: all-branches
- L3 #pragma `once`

#### Functions (3)

- L10-23 _function_ `void PackLine(RWBuffer<uint> OutBuffer, uint InstanceIndex, float3 InPosition0, float3 InPosition1, uint InPackedColor)`
- L25-33 _function_ `void PackLine(RWBuffer<uint> OutBuffer, uint InstanceIndex, float3 InPosition0, float3 InPosition1, float4 InColor)`
- L35-52 _function_ `void UnpackLine(in Buffer<uint> InBuffer, uint InstanceIndex, out float3 OutPosition0, out float3 OutPosition1, out float4 OutColor)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDispatchIndirectArgsGen.usf` (Private)

- lines: 62; parse: all-branches
- includes: L7 `/Engine/Private/Common.ush`

#### Macros (#define, 1)

- L9 `#define INDEX_NONE uint(-1)`

#### Entry points (1)

- L26-61 _entry_ `[numthreads(THREAD_COUNT,1,1)] void IndirectArgsGenCS(uint DispatchIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraDispatchIndirectArgsGenCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraVertexFactories/Private/NiagaraDispatchIndirect.cpp:5)

#### Global resources (textures / buffers / samplers) (3)

- L15 _resource_ `Buffer<uint> DispatchInfos;` — Input Format (FNiagaraDispatchIndirectInfoCS) uint3 - Counter Offsets uint3 - Thread Group Size uint  - Indirect Args Offset
- L19 _resource_ `Buffer<uint> InstanceCounts;`
- L24 _resource_ `RWBuffer<uint> RWDispatchIndirectArgs;` — Output Format (FNiagaraDispatchIndirectParametersCS) uint4 - Indirect Group Count uint4 - Indirect Thread Count

#### Global parameters (uniforms) (2)

- L16 _parameter_ `uint NumDispatchInfos;`
- L17 _parameter_ `uint3 MaxGroupsPerDimension;`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDistanceFieldQueries.ush` (Private)

- lines: 69; parse: all-branches
- L7 #pragma `once`

#### Functions (2)

- L9-34 _function_ `float GetDistanceToMeshDistanceField(int DFIndex, const FDFVector3 LWCWorldPosition, const float MaxDistance)`
- L36-68 _function_ `void ComputeClosestPointMeshDistanceField(int DFIndex, const FDFVector3 LWCWorldPosition, const float GridSampledDistance, out float3 OutClosestPosition, out float3 OutClosestNormal, out float MaxEncodedDistance, out bool bNormalIsValid)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraDrawIndirectArgsGen.usf` (Private)

- lines: 119; parse: all-branches
- includes: L7 `/Engine/Private/Common.ush`

#### Macros (#define, 2)

- L20 `#define FLAG_USE_CULLED_COUNTS (1u << 0u)`
- L21 `#define FLAG_INSTANCED_STEREO (1u << 1u)`

#### Entry points (3)

- L23-92 _entry_ `[numthreads(THREAD_COUNT,1,1)] void MainCS(uint TaskIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraDrawIndirectArgsGenCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraVertexFactories/Private/NiagaraDrawIndirect.cpp:11)
- L94-105 _entry_ `[numthreads(THREAD_COUNT,1,1)] void ResetCountsCS(uint TaskIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraDrawIndirectResetCountsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraVertexFactories/Private/NiagaraDrawIndirect.cpp:12)
- L107-119 _entry_ `[numthreads(THREAD_COUNT,1,1)] void InitInstanceCountsCS(uint TaskIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraInstanceCountsInitCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraVertexFactories/Private/NiagaraDrawIndirect.cpp:13)

#### Global resources (textures / buffers / samplers) (4)

- L12 _resource_ `Buffer<uint> TaskInfos;` — Array of task info. Each being a draw indirect arg gen or instance count reset. ArgGen = (InstanceCountBufferOffset, NumIndicesPerInstance, StartIndexLocation) InstanceCountClear = (InstanceCountBufferOffset)
- L13 _resource_ `Buffer<uint> CulledInstanceCounts;`
- L15 _resource_ `RWBuffer<uint> RWInstanceCounts;`
- L16 _resource_ `RWBuffer<uint> RWDrawIndirectArgs;`

#### Global parameters (uniforms) (1)

- L18 _parameter_ `uint4 TaskCount;` — (ArgGenTaskOffset, NumArgGenTasks, NumInstanceCountClearTasks, NumArgGenTasks + NumInstanceCountClearTasks)

### `Plugins/FX/Niagara/Shaders/Private/NiagaraEmitterInstanceShader.usf` (Private)

- lines: 879; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`, L9 `NiagaraShaderVersion.ush`, L19 `/Engine/Private/Common.ush` [GPU_SIMULATION], L20 `/Engine/Private/DistanceField/GlobalDistanceFieldShared.ush` [GPU_SIMULATION], L24 `/Engine/Generated/UniformBuffers/SubstratePublic.ush` [GPU_SIMULATION], L30 `/Engine/Private/Definitions.usf`, L106 `/Engine/Private/SceneTexturesCommon.ush` [GPU_SIMULATION], L110 `NiagaraPhysicsCommon.ush` [GPU_SIMULATION], L878 `/Engine/Generated/NiagaraEmitterInstance.ush`

#### Macros (#define, 13)

- L12 `#define SMALL_NUMBER 1e-8` _[#if !defined(SMALL_NUMBER)]_
- L15 `#define MAX_DISTANCE 1e+38` _[#if !defined(MAX_DISTANCE)]_
- L22 `#define NEEDS_SCENE_TEXTURES 1` _[#if GPU_SIMULATION]_
- L23 `#define SCENE_TEXTURES_DISABLED 0` _[#if GPU_SIMULATION]_
- L68 `#define GetEngineOwnerLWCTile() Engine_Owner_LWCTile.xyz`
- L76 `#define NIAGARA_PARTICLE_PARTIAL_ENABLED 0` _[#if GPU_SIMULATION && !defined(NIAGARA_PARTICLE_PARTIAL_ENABLED)]_
- L80 `#define NIAGARA_DISPATCH_TYPE_ONE_D 0` _[#if GPU_SIMULATION]_
- L81 `#define NIAGARA_DISPATCH_TYPE_TWO_D 1` _[#if GPU_SIMULATION]_
- L82 `#define NIAGARA_DISPATCH_TYPE_THREE_D 2` _[#if GPU_SIMULATION]_
- L83 `#define NIAGARA_DISPATCH_TYPE_CUSTOM 3` _[#if GPU_SIMULATION]_
- L85 `#define NIAGARA_DISPATCH_TYPE NIAGARA_DISPATCH_TYPE_ONE_D` _[#if GPU_SIMULATION && !defined(NIAGARA_DISPATCH_TYPE)]_
- L140 `#define NIAGARA_MAX_GPU_SPAWN_INFOS_V4 ((NIAGARA_MAX_GPU_SPAWN_INFOS + 3) / 4)` _[#if GPU_SIMULATION]_
- L613 `#define USE_GROUP_SHARED ((THREADGROUP_SIZE == 64 \|\| THREADGROUP_SIZE == 32) && !USE_WAVE_INTRINSICS && !VULKAN_PROFILE_SM5 && !VULKAN_PROFILE_SM6 && !VULKAN_PROFILE)` _[#if GPU_SIMULATION]_
- L6 #pragma `warning(disable:4008)`

#### Structs / classes (1)

- L837-842 _struct_ **`NiagaraRandInfo`** `struct NiagaraRandInfo` — Random number functions
  - L839 _member_ `int Seed1;`
  - L840 _member_ `int Seed2;`
  - L841 _member_ `int Seed3;`

#### Global resources (textures / buffers / samplers) (11)

- L90 _resource_ `Buffer<uint4> IndirectDispatchArgs;` — Indirect count buffer we lookup into to get actual thread count _[#if GPU_SIMULATION && NIAGARA_DISPATCH_INDIRECT]_
- L549 _resource_ `Buffer<float> InputFloat;` _[#if GPU_SIMULATION && NIAGARA_PARTICLE_PARTIAL_ENABLED == 0]_
- L550 _resource_ `Buffer<int> InputInt;` _[#if GPU_SIMULATION && NIAGARA_PARTICLE_PARTIAL_ENABLED == 0]_
- L551 _resource_ `Buffer<half> InputHalf;` _[#if GPU_SIMULATION && NIAGARA_PARTICLE_PARTIAL_ENABLED == 0]_
- L553 _resource_ `RWBuffer<int> RWOutputInt;` _[#if GPU_SIMULATION]_
- L554 _resource_ `RWBuffer<float> RWOutputFloat;` _[#if GPU_SIMULATION]_
- L555 _resource_ `RWBuffer<half> RWOutputHalf;` _[#if GPU_SIMULATION]_
- L557 _resource_ `Buffer<float> StaticInputFloat;` _[#if GPU_SIMULATION]_
- L559 _resource_ `RWBuffer<uint> RWInstanceCounts;` _[#if GPU_SIMULATION]_
- L563 _resource_ `Buffer<int> FreeIDList;` _[#if GPU_SIMULATION]_
- L564 _resource_ `RWBuffer<int> RWIDToIndexTable;` _[#if GPU_SIMULATION]_

#### Global parameters (uniforms) (14)

- L91 _parameter_ `uint IndirectDispatchArgsOffset;` — Offset into the indirect count buffer _[#if GPU_SIMULATION && NIAGARA_DISPATCH_INDIRECT]_
- L93 _parameter_ `uint3 DispatchThreadIdBounds;` — Used to track thread bounds _[#if GPU_SIMULATION && !(NIAGARA_DISPATCH_INDIRECT)]_
- L94 _parameter_ `uint3 DispatchThreadIdToLinear;` — Used to convert from DispatchThreadId to a linear thread id _[#if GPU_SIMULATION && !(NIAGARA_DISPATCH_INDIRECT)]_
- L112 _parameter_ `uint EmitterTickCounter;` _[#if GPU_SIMULATION]_
- L142 _parameter_ `int4 EmitterSpawnInfoOffsets[NIAGARA_MAX_GPU_SPAWN_INFOS_V4];` _[#if GPU_SIMULATION]_
- L143 _parameter_ `float4 EmitterSpawnInfoParams[NIAGARA_MAX_GPU_SPAWN_INFOS];` — Packed data where x = IntervalDt, y = InterpStartDt, z = Group, w = Start Particle Index _[#if GPU_SIMULATION]_
- L154 _parameter_ `uint NumSpawnedInstances;` _[#if GPU_SIMULATION]_
- L542 _parameter_ `uint ComponentBufferSizeRead;` _[#if GPU_SIMULATION]_
- L543 _parameter_ `uint ComponentBufferSizeWrite;` _[#if GPU_SIMULATION]_
- L544 _parameter_ `uint SimStart;` _[#if GPU_SIMULATION]_
- L560 _parameter_ `uint ReadInstanceCountOffset;` _[#if GPU_SIMULATION]_
- L561 _parameter_ `uint WriteInstanceCountOffset;` _[#if GPU_SIMULATION]_
- L570 _parameter_ `uint4 SimulationStageIterationInfo;` — X = Count Buffer Instance Count Offset (INDEX_NONE == Use Instance Count) Y = Instance Count Z = Iteration Num \| Index W = Loop Num \| Index _[#if GPU_SIMULATION]_
- L587 _parameter_ `uint3 ParticleIterationStateInfo;` — Where X = Parameter Binding, YZ = Inclusive Range _[#if GPU_SIMULATION]_

#### groupshared (8)

- L617 _groupshared_ `groupshared uint GroupSharedIndex[64];` _[#if GPU_SIMULATION && USE_GROUP_SHARED && THREADGROUP_SIZE == 64]_
- L618 _groupshared_ `groupshared uint GroupSharedIndex4[16];` _[#if GPU_SIMULATION && USE_GROUP_SHARED && THREADGROUP_SIZE == 64]_
- L619 _groupshared_ `groupshared uint GroupSharedIndex16[4];` _[#if GPU_SIMULATION && USE_GROUP_SHARED && THREADGROUP_SIZE == 64]_
- L620 _groupshared_ `groupshared uint GroupSharedIndex64;` _[#if GPU_SIMULATION && USE_GROUP_SHARED && THREADGROUP_SIZE == 64]_
- L622 _groupshared_ `groupshared uint GroupSharedIndex[32];` _[#if GPU_SIMULATION && USE_GROUP_SHARED && !(THREADGROUP_SIZE == 64) && THREADGROUP_SIZE == 32]_
- L623 _groupshared_ `groupshared uint GroupSharedIndex4[8];` _[#if GPU_SIMULATION && USE_GROUP_SHARED && !(THREADGROUP_SIZE == 64) && THREADGROUP_SIZE == 32]_
- L624 _groupshared_ `groupshared uint GroupSharedIndex16[2];` _[#if GPU_SIMULATION && USE_GROUP_SHARED && !(THREADGROUP_SIZE == 64) && THREADGROUP_SIZE == 32]_
- L625 _groupshared_ `groupshared uint GroupSharedIndex64;` _[#if GPU_SIMULATION && USE_GROUP_SHARED && !(THREADGROUP_SIZE == 64) && THREADGROUP_SIZE == 32]_

#### static const (2)

- L26 _static_const_ `const static float PI = 3.1415926535897932f;` _[#if !(GPU_SIMULATION)]_
- L28 _static_const_ `const static float TWO_PI = 3.1415926535897932f*2.0f;`

#### static variables (17)

- L89 _static_var_ `static uint3 DispatchThreadIdBounds;` — Used to track thread bounds _[#if GPU_SIMULATION && NIAGARA_DISPATCH_INDIRECT]_
- L97 _static_var_ `static uint3 GDispatchThreadId;` — SV_DispatchThreadId _[#if GPU_SIMULATION]_
- L98 _static_var_ `static uint3 GGroupId;` — SV_GroupdId _[#if GPU_SIMULATION]_
- L99 _static_var_ `static uint3 GGroupThreadId;` — SV_GroupThreadId _[#if GPU_SIMULATION]_
- L100 _static_var_ `static uint GGroupIndex;` — SV_GroupIndex _[#if GPU_SIMULATION]_
- L101 _static_var_ `static uint GLinearThreadId;` _[#if GPU_SIMULATION]_
- L102 _static_var_ `static uint GEmitterTickCounter;` _[#if GPU_SIMULATION]_
- L103 _static_var_ `static uint GRandomSeedOffset = 0;` _[#if GPU_SIMULATION]_
- L145 _static_var_ `static int GInterpSpawnIndex;` _[#if GPU_SIMULATION]_
- L146 _static_var_ `static float Emitter_SpawnInterval;` _[#if GPU_SIMULATION]_
- L147 _static_var_ `static float Emitter_InterpSpawnStartDt;` _[#if GPU_SIMULATION]_
- L148 _static_var_ `static int Emitter_SpawnGroup;` _[#if GPU_SIMULATION]_
- L150 _static_var_ `static int Engine_ExecutionCount;` _[#if GPU_SIMULATION]_
- L151 _static_var_ `static int GGPUExecIndex;` _[#if GPU_SIMULATION]_
- L153 _static_var_ `static uint GSpawnStartInstance;` _[#if GPU_SIMULATION]_
- L276 _static_var_ `static int RandomCounterDeterministic = 0;` — Internal counter used to generate a different sequence of random numbers for each call
- L328 _static_var_ `static int RandomCounterNonDeterministic = -1;` — Internal counter used to generate a different sequence of random numbers for each call We need to keep this separate from the Deterministic version so that non-deterministic calls do not interfere with the deterministic ones. _[#if GPU_SIMULATION]_

#### Functions (90)

- L33 _function_ `float4 ModuloPrecise(float4 x, float4 y)` — Most of the vector implementations work this way. This helps us keep proper precision.
- L34 _function_ `float3 ModuloPrecise(float3 x, float3 y)`
- L35 _function_ `float2 ModuloPrecise(float2 x, float2 y)`
- L36 _function_ `float ModuloPrecise(float x, float y)`
- L37 _function_ `int ModuloPrecise(int x, int y)`
- L38 _function_ `int Modulo(int x, int y)`
- L42 _function_ `float4 Reciprocal(float4 x)` — using rcp is only 12 bits of precision, we should usually pay for perf
- L43 _function_ `float3 Reciprocal(float3 x)`
- L44 _function_ `float2 Reciprocal(float2 x)`
- L45 _function_ `float Reciprocal(float x)`
- L49 _function_ `bool NiagaraAll(bool b)` — Annoyingly, all(bool) and any(bool) don't exist, so we'll make Niagara versions which work with both scalars and vectors.
- L50 _function_ `bool NiagaraAny(bool b)`
- L52 _function_ `bool NiagaraAll(bool2 b)` _[#if GPU_SIMULATION]_
- L53 _function_ `bool NiagaraAll(bool3 b)` _[#if GPU_SIMULATION]_
- L54 _function_ `bool NiagaraAll(bool4 b)` _[#if GPU_SIMULATION]_
- L55 _function_ `bool NiagaraAny(bool2 b)` _[#if GPU_SIMULATION]_
- L56 _function_ `bool NiagaraAny(bool3 b)` _[#if GPU_SIMULATION]_
- L57 _function_ `bool NiagaraAny(bool4 b)` _[#if GPU_SIMULATION]_
- L60 _function_ `bool NiagaraAll(bool2 b)` — No all() and any() opcodes in our VM, emulate them. _[#if !(GPU_SIMULATION)]_
- L61 _function_ `bool NiagaraAll(bool3 b)` _[#if !(GPU_SIMULATION)]_
- L62 _function_ `bool NiagaraAll(bool4 b)` _[#if !(GPU_SIMULATION)]_
- L63 _function_ `bool NiagaraAny(bool2 b)` _[#if !(GPU_SIMULATION)]_
- L64 _function_ `bool NiagaraAny(bool3 b)` _[#if !(GPU_SIMULATION)]_
- L65 _function_ `bool NiagaraAny(bool4 b)` _[#if !(GPU_SIMULATION)]_
- L114 _function_ `float4 Modulo(float4 x, float4 y)` _[#if GPU_SIMULATION]_
- L115 _function_ `float3 Modulo(float3 x, float3 y)` _[#if GPU_SIMULATION]_
- L116 _function_ `float2 Modulo(float2 x, float2 y)` _[#if GPU_SIMULATION]_
- L117 _function_ `float Modulo(float x, float y)` _[#if GPU_SIMULATION]_
- L120-126 _function_ `FLWCVector3 WorldPositionFromSceneDepth(float2 ScreenPosition, float SceneDepth)` — utility function used for scene depth calculations _[#if GPU_SIMULATION]_
- L132-137 _function_ `float NiagaraInternalNoise(uint u, uint v, uint s)` — MASSIVE HACK - Tracked in JIRA UE-69298 Hardcoded random function accessible from inner part of node implementation. It works for now at least and avoids exposing every random needed in the UI. Temporary solution, it will be replaced when a design is validated. _[#if GPU_SIMULATION]_
- L156-160 _function_ `void SetupExecIndexForGPU()` _[#if GPU_SIMULATION]_
- L162-192 _function_ `void SetupExecIndexAndSpawnInfoForGPU()` _[#if GPU_SIMULATION]_
- L196-199 _function_ `int ExecIndex()` — Returns the current instance index relative to the operation (spawn/update) _[#if GPU_SIMULATION]_
- L201-209 _function_ `float4 NiagaraGPU_QuatMul(float4 Q1, float4 Q2)` _[#if GPU_SIMULATION]_
- L233-253 _function_ `float4 rand4(int Seed1, int Seed2, int Seed3, int Seed4)` — Returns 4 random normalized floats based on 4 explicit integer seeds
- L261-273 _function_ `float3 rand3(int Seed1, int Seed2, int Seed3, int Seed4)` — float3 specialization of the above: Returns 3 random normalized floats based on 4 explicit integer seeds. All bits of the first and second seeds are used, while only the lower 16 bits of the third and fourth seeds are used.
- L279-283 _function_ `float rand(float x, int Seed1, int Seed2, int Seed3)` — Cost using rand4: 6 imad, 1 itof, 1 ishr, 1 add, 2 mul
- L286-290 _function_ `float2 rand(float2 x, int Seed1, int Seed2, int Seed3)` — Cost using rand4: 7 imad, 1 itof, 1 ishr, 1 add, 2 mul
- L293-297 _function_ `float3 rand(float3 x, int Seed1, int Seed2, int Seed3)` — Cost using rand4: 8 imad, 1 itof, 1 ishr, 1 add, 2 mul
- L300-304 _function_ `float4 rand(float4 x, int Seed1, int Seed2, int Seed3)` — Cost using rand4: 9 imad, 1 itof, 1 ishr, 1 and, 2 mul
- L307-313 _function_ `int rand(int x, int Seed1, int Seed2, int Seed3)` — Cost using rand4: 6 imad, 2 itof, 1 ishr, 1 add, 2 mul, 1 ftoi
- L330-334 _function_ `float rand(float x)` _[#if GPU_SIMULATION]_
- L336-340 _function_ `float2 rand(float2 x)` _[#if GPU_SIMULATION]_
- L342-346 _function_ `float3 rand(float3 x)` _[#if GPU_SIMULATION]_
- L348-352 _function_ `float4 rand(float4 x)` _[#if GPU_SIMULATION]_
- L355-359 _function_ `int rand(int x)` — Integer randoms are INCLUSIVE, i.e. includes both the upper and lower limits _[#if GPU_SIMULATION]_
- L365-368 _function_ `float2 rand(float2 x)` _[#if !(GPU_SIMULATION)]_
- L370-373 _function_ `float3 rand(float3 x)` _[#if !(GPU_SIMULATION)]_
- L375-378 _function_ `float4 rand(float4 x)` _[#if !(GPU_SIMULATION)]_
- L385-393 _function_ `int hash_single(int a)` — Small changes in the input bits should propagate to a lot of output bits, so the resulting hash is not periodic. This is important because the hash inputs are often things like particle ID, but the output should be pseudo-random.
- L395-398 _function_ `int hash(int a, int b)`
- L400-403 _function_ `float hash_float(int a, int b)`
- L406-409 _function_ `float hash_float(float a, int b)` — this is used when chaining calls from variable number of inputs, e.g. hash_float(hash_float(a, b), c)
- L412-415 _function_ `float rand_float(float x)` — Explicit non-deterministic random overrides used by Random Float/Integer and Seeded Random Float/Integer op nodes
- L417-420 _function_ `float2 rand_float(float2 x)`
- L422-425 _function_ `float3 rand_float(float3 x)`
- L427-430 _function_ `float4 rand_float(float4 x)`
- L432-438 _function_ `int rand_int(int x)`
- L441-444 _function_ `float rand_float(float x, int Seed1, int Seed2, int Seed3)` — Explicit deterministic random overrides used by Random Float/Integer and Seeded Random Float/Integer op nodes
- L446-449 _function_ `float2 rand_float(float2 x, int Seed1, int Seed2, int Seed3)`
- L451-454 _function_ `float3 rand_float(float3 x, int Seed1, int Seed2, int Seed3)`
- L456-459 _function_ `float4 rand_float(float4 x, int Seed1, int Seed2, int Seed3)`
- L461-466 _function_ `int rand_int(int x, int Seed1, int Seed2, int Seed3)`
- L469-491 _function_ `float4 NiagaraQuatSLerp(float4 Quat1, float4 Quat2, float Slerp)` — used to interpolate rotations in interpolated spawn scripts
- L574 _function_ `int SimulationStage_GetInstanceCount()` _[#if GPU_SIMULATION && NIAGARA_DISPATCH_INDIRECT]_
- L576 _function_ `int SimulationStage_GetInstanceCount()` _[#if GPU_SIMULATION && !(NIAGARA_DISPATCH_INDIRECT)]_
- L578 _function_ `int SimulationStage_GetNumIterations()` _[#if GPU_SIMULATION]_
- L579 _function_ `int SimulationStage_GetIterationIndex()` _[#if GPU_SIMULATION]_
- L580 _function_ `int SimulationStage_GetNumLoops()` _[#if GPU_SIMULATION]_
- L581 _function_ `int SimulationStage_GetLoopIndex()` _[#if GPU_SIMULATION]_
- L583 _function_ `float SimulationStage_GetNormalizedIterationIndex()` _[#if GPU_SIMULATION]_
- L584 _function_ `float SimulationStage_GetNormalizedLoopIndex()` _[#if GPU_SIMULATION]_
- L589-601 _function_ `void AcquireID(int DataSetID, out int IDIndex, out int IDAcquireTag)` _[#if GPU_SIMULATION]_
- L603-611 _function_ `void UpdateID(int DataSetID, int IDIndex, int InstanceIndex)` _[#if GPU_SIMULATION]_
- L632-745 _function_ `int AcquireIndex(uniform int DataSetID, bool bDoAcquire)` — Acquire an output index - the default index is the scratch instance; one additional instance is allocated at the end of the buffer, so no branching on -1 is necessary during OutputData operations _[#if GPU_SIMULATION]_
- L751-758 _function_ `float InputDataFloat(int DataSetIndex, int RegisterIdx, int InstanceIdx)` — InputData operations _[#if GPU_SIMULATION]_
- L760-767 _function_ `int InputDataInt(int DataSetIndex, int RegisterIdx, int InstanceIdx)` _[#if GPU_SIMULATION]_
- L769-776 _function_ `bool InputDataBool(int DataSetIndex, int RegisterIdx, int InstanceIdx)` _[#if GPU_SIMULATION]_
- L778-785 _function_ `float InputDataHalf(int DataSetIndex, int RegisterIdx, int InstanceIdx)` _[#if GPU_SIMULATION]_
- L791-794 _function_ `void OutputDataFloat(int DataSetIndex, int RegisterIndex, int InstanceIndex, float Value)` — OutputData operations _[#if GPU_SIMULATION]_
- L796-799 _function_ `void OutputDataInt(int DataSetIndex, int RegisterIndex, int InstanceIndex, int Value)` _[#if GPU_SIMULATION]_
- L801-804 _function_ `void OutputDataBool(int DataSetIndex, int RegisterIndex, int InstanceIndex, bool Value)` _[#if GPU_SIMULATION]_
- L806-809 _function_ `void OutputDataHalf(int DataSetIndex, int RegisterIndex, int InstanceIndex, float Value)` _[#if GPU_SIMULATION]_
- L811 _function_ `void EnterStatScope(int ID)` _[#if GPU_SIMULATION]_
- L812 _function_ `void ExitStatScope()` _[#if GPU_SIMULATION]_
- L818-833 _function_ `int OutputIndex(const int DataSetID, const bool bStageKillsParticles, const bool bIsValid)` — Get the index to write onto the output buffer
- L845-854 _function_ `NiagaraRandInfo MakeRandInfo()` _[#if GPU_SIMULATION]_
- L856-859 _function_ `float NiagaraRandomFloat(NiagaraRandInfo RandInfo)` _[#if GPU_SIMULATION]_
- L861-865 _function_ `int NiagaraRandomInt(NiagaraRandInfo RandInfo, int Range)` _[#if GPU_SIMULATION]_
- L867-873 _function_ `float3 NiagaraRandomBaryCoord(NiagaraRandInfo RandInfo)` _[#if GPU_SIMULATION]_

#### Prototypes (24)

- L363 _prototype_ `float rand(float x)` — Invokes EVectorVMOp::random _[#if !(GPU_SIMULATION)]_
- L380 _prototype_ `int rand(int x)` — Invokes EVectorVMOp::randomi and is semi-open. This is inconsistent with the rest of the functions above. As a result this function and the ones above should be deprecated in favor of the functions below _[#if !(GPU_SIMULATION)]_
- L498 _prototype_ `float noise(float x)` _[#if VM_SIMULATION]_
- L499 _prototype_ `float noise(float2 x)` _[#if VM_SIMULATION]_
- L500 _prototype_ `float noise(float3 x)` _[#if VM_SIMULATION]_
- L504 _prototype_ `float4 Modulo(float4 x, float4 y)` — Total hack to get around the cross compiler converting fmod() to "X - (Y * trunc(X/Y))"; On gpu just define these as fmod(x,y) _[#if VM_SIMULATION]_
- L505 _prototype_ `float3 Modulo(float3 x, float3 y)` _[#if VM_SIMULATION]_
- L506 _prototype_ `float2 Modulo(float2 x, float2 y)` _[#if VM_SIMULATION]_
- L507 _prototype_ `float Modulo(float x, float y)` _[#if VM_SIMULATION]_
- L510 _prototype_ `int ExecIndex()` — Returns the index for this particle in the current execution context. On gpu this'll likely be derived from DispatchThreadId _[#if VM_SIMULATION]_
- L514 _prototype_ `int AcquireIndex(int DataSetID, bool DoAcquire)` — Some functions that we use to map to special VM operations for reading in data. TODO: replace with proper buffer reading capability and use standard hlsl. _[#if VM_SIMULATION]_
- L516 _prototype_ `void AcquireID(int DataSetID, out int IDIndex, out int IDAcquireTag)` _[#if VM_SIMULATION]_
- L517 _prototype_ `void UpdateID(int DataSetID, int IDIndex, int InstanceIndex)` _[#if VM_SIMULATION]_
- L519 _prototype_ `float InputDataFloat(int DataSetIndex, int RegisterIdx)` — DataSetIndex is 0 for main dataset _[#if VM_SIMULATION]_
- L520 _prototype_ `int InputDataInt(int DataSetIndex, int RegisterIdx)` _[#if VM_SIMULATION]_
- L521 _prototype_ `bool InputDataBool(int DataSetIndex, int RegisterIdx)` _[#if VM_SIMULATION]_
- L522 _prototype_ `float InputDataHalf(int DataSetIndex, int RegisterIdx)` _[#if VM_SIMULATION]_
- L524 _prototype_ `float InputDataNoadvanceFloat(int DataSetIndex, int RegisterIdx)` — DataSetIndex is 0 for main dataset _[#if VM_SIMULATION]_
- L525 _prototype_ `int InputDataNoadvanceInt(int DataSetIndex, int RegisterIdx)` _[#if VM_SIMULATION]_
- L526 _prototype_ `bool InputDataNoadvanceBool(int DataSetIndex, int RegisterIdx)` _[#if VM_SIMULATION]_
- L528 _prototype_ `void OutputDataFloat(int DataSetIndex, int RegisterIndex, int InstanceIndex, float Value)` _[#if VM_SIMULATION]_
- L529 _prototype_ `void OutputDataInt(int DataSetIndex, int RegisterIndex, int InstanceIndex, int Value)` _[#if VM_SIMULATION]_
- L530 _prototype_ `void OutputDataBool(int DataSetIndex, int RegisterIndex, int InstanceIndex, bool Value)` _[#if VM_SIMULATION]_
- L531 _prototype_ `void OutputDataHalf(int DataSetIndex, int RegisterIndex, int InstanceIndex, float Value)` _[#if VM_SIMULATION]_

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `SimulateMain` → entry not found in file (macro-generated or #include'd); C++ `FNiagaraShader` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraShader.cpp:31)

### `Plugins/FX/Niagara/Shaders/Private/NiagaraFillIntBuffer.usf` (Private)

- lines: 18; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (1)

- L9-17 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void FillIntBuffer(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `NiagaraFillIntBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraShaderParticleID.cpp:153)

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `RWBuffer<int> BufferUAV;`

#### Global parameters (uniforms) (2)

- L6 _parameter_ `uint NumElements;`
- L7 _parameter_ `int FillValue;`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraGPURayTracingTransforms.usf` (Private)

- lines: 150; parse: all-branches
- includes: L7 `/Engine/Private/Common.ush`, L8 `NiagaraCommon.ush`

#### Macros (#define, 1)

- L79 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_

#### Entry points (1)

- L86-149 _entry_ `[numthreads(THREADGROUP_SIZE,1,1)] void NiagaraGPURayTracingTransformsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraGPURayTracingTransformsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraVertexFactories/Private/NiagaraGPURayTracingTransformsShader.cpp:14) — TODO: This doesn't take a lot of features into account that are needed to solve for a Niagara mesh's transform. See NiagaraCalculateMeshParticleTransforms in NiagaraMeshParticleUtils.ush for exactly what all goes into it. In an upcoming update, this shader should be deprecated and instead, RayTracing should be getting transforms from GPU Scene so this work doesn't have to be duplicated.

#### Global resources (textures / buffers / samplers) (4)

- L40 _resource_ `Buffer<float> ParticleDataFloatBuffer;`
- L42 _resource_ `Buffer<int> ParticleDataIntBuffer;` — Buffer<half>	ParticleDataHalfBuffer;
- L43 _resource_ `Buffer<uint> GPUInstanceCountBuffer;`
- L50 _resource_ `RWStructuredBuffer<float4> TLASTransforms;` — Transforms are float3x4 row-major matrices stored as 3 float4 because of FXC matrix packing issues when using StructuredBuffer<float3x4>

#### Global parameters (uniforms) (22)

- L13 _parameter_ `uint ParticleDataFloatStride;`
- L15 _parameter_ `uint ParticleDataIntStride;` — uint	ParticleDataHalfStride;
- L16 _parameter_ `uint CPUNumInstances;`
- L17 _parameter_ `uint InstanceCountOffset;`
- L19 _parameter_ `float3 SystemLWCTile;`
- L21 _parameter_ `uint PositionDataOffset;`
- L22 _parameter_ `uint RotationDataOffset;`
- L23 _parameter_ `uint ScaleDataOffset;`
- L24 _parameter_ `uint bLocalSpace;`
- L25 _parameter_ `uint RenderVisibilityOffset;`
- L26 _parameter_ `uint MeshIndexOffset;`
- L28 _parameter_ `uint RenderVisibilityValue;`
- L29 _parameter_ `uint MeshIndexValue;`
- L31 _parameter_ `float3 DefaultPosition;`
- L32 _parameter_ `float4 DefaultRotation;`
- L33 _parameter_ `float3 DefaultScale;`
- L34 _parameter_ `float3 MeshScale;`
- L35 _parameter_ `float4 MeshRotation;`
- L37 _parameter_ `float4x4 LocalTransform;`
- L38 _parameter_ `float3 LocalTransformTile;`
- L45 _parameter_ `float3 ViewTilePosition;`
- L46 _parameter_ `float3 RelativePreViewTranslation;`

#### Functions (4)

- L55-59 _function_ `float GetFloat(int RegisterIdx, uint InstanceID)`
- L61-64 _function_ `float GetInt(int RegisterIdx, uint InstanceID)`
- L66-69 _function_ `float3 SafeGetVec3(int RegisterIndex, uint InstanceID, float3 DefaultValue)`
- L71-74 _function_ `float4 SafeGetVec4(int RegisterIndex, uint InstanceID, float4 DefaultValue)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraGenerateMips.usf` (Private)

- lines: 59; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/GammaCorrectionCommon.ush`

#### Entry points (1)

- L17-58 _entry_ `[numthreads(THREADGROUPSIZE, THREADGROUPSIZE, 1)] void MainCS(uint3 ThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraGenerateMipsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraGenerateMips.cpp:40)

#### Global resources (textures / buffers / samplers) (3)

- L9 _resource_ `Texture2D MipInSRV;`
- L10 _resource_ `SamplerState MipInSampler;`
- L13 _resource_ `RWTexture2D<float4> MipOutUAV;`

#### Global parameters (uniforms) (4)

- L6 _parameter_ `float2 SrcTexelSize;`
- L7 _parameter_ `float2 DstTexelSize;`
- L12 _parameter_ `int2 MipOutSize;`
- L15 _parameter_ `int KernelHWidth;`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraInitFreeIDBuffer.usf` (Private)

- lines: 25; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (1)

- L10-24 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void InitIDBufferCS(uint Index : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraInitFreeIDBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraShaderParticleID.cpp:39)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `RWBuffer<int> RWNewBuffer;`
- L6 _resource_ `Buffer<int> ExistingBuffer;`

#### Global parameters (uniforms) (2)

- L7 _parameter_ `uint NumNewElements;`
- L8 _parameter_ `uint NumExistingElements;`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraLWCHelper.usf` (Private)

- lines: 36; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ComputeShaderUtils.ush`

#### Entry points (1)

- L16-35 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void TileShiftPositions(uint3 GroupId : SV_GroupID, int GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNiagaraLWCTileShiftPositionsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraLWCTileShiftPositions.cpp:7)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `RWBuffer<float> FloatBuffer;`
- L9 _resource_ `Buffer<int> CountBuffer;`

#### Global parameters (uniforms) (4)

- L7 _parameter_ `uint FloatBufferStride;`
- L10 _parameter_ `uint CountBufferOffset;`
- L12 _parameter_ `uint NumPositions;`
- L14 _parameter_ `float3 TileShift;`

#### Top-level macro invocations (1)

- L13 _macro_call_ `DECLARE_SCALAR_ARRAY(uint, PositionComponentOffsets, MaxPositions)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraMeshParticleUtils.ush` (Private)

- lines: 477; parse: all-branches
- includes: L11 `/Plugin/FX/Niagara/Private/NiagaraCommon.ush`, L12 `/Plugin/FX/Niagara/Private/NiagaraParticleAccess.ush`

#### Macros (#define, 7)

- L15 `#define MESH_FACING_DEFAULT 0`
- L16 `#define MESH_FACING_VELOCITY 1`
- L17 `#define MESH_FACING_CAMERA_POSITION 2`
- L18 `#define MESH_FACING_CAMERA_PLANE 3`
- L21 `#define PARTICLE_SPACE_SIMULATION 0`
- L22 `#define PARTICLE_SPACE_WORLD 1`
- L23 `#define PARTICLE_SPACE_LOCAL 2`
- L3 #pragma `once`

#### Structs / classes (4)

- L26-31 _struct_ **`NiagaraMeshParticleSRT`** `struct NiagaraMeshParticleSRT` — Decomposed scale, rotation, and translation of a mesh particle
  - L28 _member_ `float3 Scale;`
  - L29 _member_ `float3x3 Rotation;`
  - L30 _member_ `FLWCVector3 Translation;`
- L34-40 _struct_ **`NiagaraMeshParticleTransforms`** `struct NiagaraMeshParticleTransforms` — Transform data for a single mesh particle, used for rendering and culling
  - L36 _member_ `FLWCMatrix LocalToWorld;`
  - L37 _member_ `FLWCInverseMatrix WorldToLocal;`
  - L38 _member_ `FLWCMatrix PrevLocalToWorld;`
  - L39 _member_ `float3x3 LocalToWorldNoScale;`
- L43-88 _struct_ **`NiagaraMeshParticleSRTParams`** `struct NiagaraMeshParticleSRTParams` — Parameters needed to compute the NiagaraMeshParticleSRT of a mesh particle
  - L46 _member_ `uint ParticleIndex;` — Index of particle, used to fetch from the Niagara data buffer
  - L48 _member_ `float3 SystemLWCTile;` — The render tile of the system for Large World Coordinates
  - L50 _member_ `bool bLocalSpace;` — Whether or not the Niagara emitter is in local space.
  - L52 _member_ `uint FacingMode;` — The mesh particle facing mode (see MESH_FACING_* values above)
  - L55 _member_ `float3 MeshScale;` — Additional mesh scale and offset to apply to mesh
  - L56 _member_ `float4 MeshRotation;`
  - L57 _member_ `float3 MeshOffset;`
  - L58 _member_ `bool bMeshOffsetIsWorldSpace;`
  - L61 _member_ `bool bLockedAxisEnable;` — Locked axis options
  - L62 _member_ `float3 LockedAxis;`
  - L63 _member_ `uint LockedAxisSpace;`
  - L66 _member_ `int ScaleDataOffset;` — Offsets for accessing transform information from particle data
  - L67 _member_ `int RotationDataOffset;`
  - L68 _member_ `int PositionDataOffset;`
  - L69 _member_ `int CameraOffsetDataOffset;`
  - L72 _member_ `float3 DefaultScale;` — Defaults for the above data when no offset provided
  - L73 _member_ `float4 DefaultRotation;`
  - L74 _member_ `float3 DefaultPosition;`
  - L75 _member_ `float DefaultCameraOffset;`
  - L78 _member_ `float4 VelocityDirMag;` — Velocity unit direction (XYZ), and velocity magnitude (W) of particle (see NiagaraGetVelocityDirMag)
  - L81 _member_ `FLWCVector3 CameraOrigin;` — Camera basis vectors (in world space)
  - L82 _member_ `float3 CameraForwardDir;`
  - L83 _member_ `float3 CameraUpDir;`
  - L86 _member_ `FLWCMatrix PrimitiveLocalToWorld;` — Primitive transform data
  - L87 _member_ `float3 PrimitiveInvNonUniformScale;`
- L91-154 _struct_ **`NiagaraMeshParticleTransformsParams`** `struct NiagaraMeshParticleTransformsParams` — Parameters needed to compute the final transforms (current, previous, and inverse) of a mesh particle
  - L94 _member_ `uint ParticleIndex;` — Index of particle, used to fetch from the Niagara data buffer
  - L96 _member_ `float3 SystemLWCTile;` — The render tile of the system for Large World Coordinates
  - L98 _member_ `bool bLocalSpace;` — If true, specifies that the Niagara emitter is in local space
  - L100 _member_ `bool bPreciseMotionVectors;` — If true, will perform more expensive calculation to determine previous transform
  - L102 _member_ `uint FacingMode;` — The mesh particle facing mode (see MESH_FACING_* values above)
  - L104 _member_ `float DeltaSeconds;` — Elapsed seconds this frame
  - L107 _member_ `float3 MeshScale;` — Additional scale and offset to apply to mesh
  - L108 _member_ `float4 MeshRotation;`
  - L109 _member_ `float3 MeshOffset;`
  - L110 _member_ `bool bMeshOffsetIsWorldSpace;`
  - L113 _member_ `bool bLockedAxisEnable;` — Locked axis options
  - L114 _member_ `float3 LockedAxis;`
  - L115 _member_ `uint LockedAxisSpace;`
  - L118 _member_ `int ScaleDataOffset;` — Offsets for accessing transform information from particle data
  - L119 _member_ `int RotationDataOffset;`
  - L120 _member_ `int PositionDataOffset;`
  - L121 _member_ `int CameraOffsetDataOffset;`
  - L122 _member_ `int PrevScaleDataOffset;`
  - L123 _member_ `int PrevRotationDataOffset;`
  - L124 _member_ `int PrevPositionDataOffset;`
  - L125 _member_ `int PrevCameraOffsetDataOffset;`
  - L128 _member_ `float3 DefaultScale;` — Defaults for the above data when no offset provided
  - L129 _member_ `float4 DefaultRotation;`
  - L130 _member_ `float3 DefaultPosition;`
  - L131 _member_ `float DefaultCameraOffset;`
  - L132 _member_ `float3 DefaultPrevScale;`
  - L133 _member_ `float4 DefaultPrevRotation;`
  - L134 _member_ `float3 DefaultPrevPosition;`
  - L135 _member_ `float DefaultPrevCameraOffset;`
  - L138 _member_ `float4 VelocityDirMag;` — Velocity unit direction (XYZ), and velocity magnitude (W) of particle (see NiagaraGetVelocityDirMag)
  - L139 _member_ `float4 PrevVelocityDirMag;`
  - L142 _member_ `FLWCVector3 CameraOrigin;` — Camera position and basis vectors (in world space)
  - L143 _member_ `float3 CameraForwardDir;`
  - L144 _member_ `float3 CameraUpDir;`
  - L145 _member_ `FLWCVector3 PrevCameraOrigin;`
  - L146 _member_ `float3 PrevCameraForwardDir;`
  - L147 _member_ `float3 PrevCameraUpDir;`
  - L150 _member_ `FLWCMatrix PrimitiveLocalToWorld;` — Primitive transform data
  - L151 _member_ `FLWCInverseMatrix PrimitiveWorldToLocal;`
  - L152 _member_ `FLWCMatrix PrimitivePrevLocalToWorld;`
  - L153 _member_ `float3 PrimitiveInvNonUniformScale;`

#### Functions (11)

- L157-160 _function_ `FLWCVector3 NiagaraLocalToWorldPos(float3 LocalSpacePos, NiagaraMeshParticleSRTParams Params)` — Transforms a local-space position to world space
- L163-171 _function_ `FLWCVector3 NiagaraSimToWorldPos(FLWCVector3 SimSpacePos, NiagaraMeshParticleSRTParams Params)` — Transforms a simulation-space position to world space
- L174-180 _function_ `float3 NiagaraLocalToWorldVec(float3 LocalSpaceVec, NiagaraMeshParticleSRTParams Params)` — Transforms a local-space direction vector to world space (does not apply scale)
- L183-193 _function_ `float3 NiagaraWorldToLocalVec(float3 WorldSpaceVec, NiagaraMeshParticleSRTParams Params)` — Transforms a world-space direction vector to local space
- L196-204 _function_ `float3 NiagaraSimToWorldVec(float3 SimSpaceVec, NiagaraMeshParticleSRTParams Params)` — Transforms a simulation-space direction vector to world space
- L207-215 _function_ `float3 NiagaraWorldToSimVec(float3 InVector, NiagaraMeshParticleSRTParams Params)` — Transforms a world-space direction vector to simulation space
- L218-227 _function_ `float4 NiagaraGetVelocityDirMag(int VelocityDataOffset, float3 DefaultVelocity, uint ParticleIndex)` — Helper to get decomposed velocity direction and magnitude from Niagara particle data
- L230-325 _function_ `float3x3 NiagaraGetMeshFacingMatrix(FLWCVector3 ParticleSimPosition, NiagaraMeshParticleSRTParams Params)` — Constructs a rotation matrix that satisfies the mesh particle's FacingMode
- L328-337 _function_ `float3 NiagaraCalculateCameraOffset(FLWCVector3 ParticleSimPosition, NiagaraMeshParticleSRTParams Params)` — Calculates the simulation-space CameraOffset of the mesh particle
- L340-391 _function_ `NiagaraMeshParticleSRT NiagaraCalculateMeshParticleSRT(NiagaraMeshParticleSRTParams Params)` — Calculates scale, rotation, and translation of a mesh particle. NOTE: translation and rotation are in particle simulation space
- L394-477 _function_ `NiagaraMeshParticleTransforms NiagaraCalculateMeshParticleTransforms(NiagaraMeshParticleTransformsParams Params)` — Calculates final transforms of a mesh particle, used for culling and/or rendering

### `Plugins/FX/Niagara/Shaders/Private/NiagaraMeshVertexFactory.ush` (Private)

- lines: 989; parse: all-branches
- includes: L7 `/Engine/Private/VertexFactoryCommon.ush`, L8 `NiagaraCommon.ush`, L9 `NiagaraVFCommon.usf`, L10 `NiagaraMeshParticleUtils.ush`, L13 `/Engine/Private/RayTracing/RayTracingCommon.ush` [COMPUTESHADER \|\| RAYHITGROUPSHADER], L14 `/Engine/Private/RayTracing/RayTracingHitGroupCommon.ush` [COMPUTESHADER \|\| RAYHITGROUPSHADER], L988 `/Engine/Private/VertexFactoryDefaultInterface.ush`

#### Macros (#define, 11)

- L17 `#define USE_PARTICLE_POSITION (NEEDS_PARTICLE_POSITION)`
- L18 `#define USE_PARTICLE_VELOCITY (NEEDS_PARTICLE_VELOCITY)`
- L19 `#define USE_PARTICLE_TIME (NEEDS_PARTICLE_TIME)`
- L20 `#define USE_PARTICLE_RANDOM (NEEDS_PARTICLE_RANDOM)`
- L21 `#define USE_PARTICLE_TRANSFORM (NEEDS_PARTICLE_TRANSFORM)`
- L22 `#define USE_PARTICLE_LOCAL_TO_WORLD (NEEDS_PARTICLE_LOCAL_TO_WORLD \|\| NEEDS_INSTANCE_LOCAL_TO_WORLD_PS)`
- L23 `#define USE_PARTICLE_WORLD_TO_LOCAL (NEEDS_PARTICLE_WORLD_TO_LOCAL \|\| NEEDS_INSTANCE_WORLD_TO_LOCAL_PS)`
- L26 `#define MANUAL_VERTEX_FETCH 0` _[#if !defined(MANUAL_VERTEX_FETCH)]_
- L29 `#define VF_ColorIndexMask_Index 0`
- L30 `#define VF_NumTexcoords_Index 1`
- L73 `#define GetInstanceIdFromVF(VFInput) (VFInput.InstanceId)` _[#if !((VF_USE_PRIMITIVE_SCENE_DATA == 1))]_
- L72 #undef `GetInstanceIdFromVF`

#### Structs / classes (4)

- L32-82 _struct_ **`FVertexFactoryInput`** `struct FVertexFactoryInput`
  - L34 _member_ `float4 Position : ATTRIBUTE0;`
  - L37 _member_ `half3 TangentX : ATTRIBUTE1;` _[#if !MANUAL_VERTEX_FETCH]_
  - L39 _member_ `half4 TangentZ : ATTRIBUTE2;` — TangentZ.w contains sign of tangent basis determinant _[#if !MANUAL_VERTEX_FETCH]_
  - L40 _member_ `half4 VertexColor : ATTRIBUTE3;` _[#if !MANUAL_VERTEX_FETCH]_
  - L44 _member_ `float2 TexCoords0 : ATTRIBUTE4;` _[#if !MANUAL_VERTEX_FETCH && NUM_MATERIAL_TEXCOORDS_VERTEX && NUM_MATERIAL_TEXCOORDS_VERTEX == 1]_
  - L46 _member_ `float4 TexCoords01 : ATTRIBUTE4;` _[#if !MANUAL_VERTEX_FETCH && NUM_MATERIAL_TEXCOORDS_VERTEX && !(NUM_MATERIAL_TEXCOORDS_VERTEX == 1) && NUM_MATERIAL_TEXCOORDS_VERTEX >= 2]_
  - L49 _member_ `float2 TexCoords2 : ATTRIBUTE5;` _[#if !MANUAL_VERTEX_FETCH && NUM_MATERIAL_TEXCOORDS_VERTEX && NUM_MATERIAL_TEXCOORDS_VERTEX == 3]_
  - L51 _member_ `float4 TexCoords23 : ATTRIBUTE5;` _[#if !MANUAL_VERTEX_FETCH && NUM_MATERIAL_TEXCOORDS_VERTEX && !(NUM_MATERIAL_TEXCOORDS_VERTEX == 3) && NUM_MATERIAL_TEXCOORDS_VERTEX >= 4]_
  - L54 _member_ `float2 TexCoords4 : ATTRIBUTE6;` _[#if !MANUAL_VERTEX_FETCH && NUM_MATERIAL_TEXCOORDS_VERTEX && NUM_MATERIAL_TEXCOORDS_VERTEX == 5]_
  - L56 _member_ `float4 TexCoords45 : ATTRIBUTE6;` _[#if !MANUAL_VERTEX_FETCH && NUM_MATERIAL_TEXCOORDS_VERTEX && !(NUM_MATERIAL_TEXCOORDS_VERTEX == 5) && NUM_MATERIAL_TEXCOORDS_VERTEX >= 6]_
  - L59 _member_ `float2 TexCoords6 : ATTRIBUTE7;` _[#if !MANUAL_VERTEX_FETCH && NUM_MATERIAL_TEXCOORDS_VERTEX && NUM_MATERIAL_TEXCOORDS_VERTEX == 7]_
  - L61 _member_ `float4 TexCoords67 : ATTRIBUTE7;` _[#if !MANUAL_VERTEX_FETCH && NUM_MATERIAL_TEXCOORDS_VERTEX && !(NUM_MATERIAL_TEXCOORDS_VERTEX == 7) && NUM_MATERIAL_TEXCOORDS_VERTEX >= 8]_
  - L64 _member_ `float2 TexCoords0 : ATTRIBUTE4;` _[#if !MANUAL_VERTEX_FETCH && !(NUM_MATERIAL_TEXCOORDS_VERTEX) && USE_PARTICLE_SUBUVS]_
  - L75 _member_ `uint InstanceId : SV_InstanceID;` _[#if !((VF_USE_PRIMITIVE_SCENE_DATA == 1))]_
  - L80 _member_ `uint VertexId : SV_VertexID;` _[#if PASS_NEEDS_VERTEX_ID \|\| MANUAL_VERTEX_FETCH]_
- L84-148 _struct_ **`FVertexFactoryInterpolantsVSToPS`** `struct FVertexFactoryInterpolantsVSToPS`
  - L86 _member_ `TANGENTTOWORLD_INTERPOLATOR_BLOCK float4 SubUV0AndTexCoord0 : TEXCOORD1;`
  - L90 _member_ `float4 SubUV1AndLerp : TEXCOORD2;` _[#if USE_PARTICLE_SUBUVS]_
  - L93 _member_ `float4 TexCoords[(NUM_TEX_COORD_INTERPOLATORS+1)/2] : TEXCOORD0;` _[#if !(USE_PARTICLE_SUBUVS) && NUM_TEX_COORD_INTERPOLATORS]_
  - L98 _member_ `float4 VertexColor : COLOR0;` _[#if INTERPOLATE_VERTEX_COLOR]_
  - L102 _member_ `nointerpolation float4 ParticleColor : COLOR1;` _[#if NEEDS_PARTICLE_COLOR]_
  - L106 _member_ `nointerpolation float4 DynamicParameter : COLOR2;` _[#if (DYNAMIC_PARAMETERS_MASK & 1)]_
  - L109 _member_ `nointerpolation float4 DynamicParameter1 : COLOR3;` _[#if (DYNAMIC_PARAMETERS_MASK & 2)]_
  - L112 _member_ `nointerpolation float4 DynamicParameter2 : COLOR4;` _[#if (DYNAMIC_PARAMETERS_MASK & 4)]_
  - L115 _member_ `nointerpolation float4 DynamicParameter3 : COLOR5;` _[#if (DYNAMIC_PARAMETERS_MASK & 8)]_
  - L120 _member_ `nointerpolation float3 ParticleTranslatedWorldPosition : PARTICLE_POSITION;` — Particle position in camera-centered translated world space _[#if USE_PARTICLE_POSITION]_
  - L125 _member_ `nointerpolation float4 ParticleVelocity : PARTICLE_VELOCITY;` — The velocity of the particle, XYZ: direction, W: speed. _[#if USE_PARTICLE_VELOCITY]_
  - L130 _member_ `nointerpolation float RelativeTime : PARTICLE_TIME;` — Relative alive time of the particle _[#if USE_PARTICLE_TIME]_
  - L134 _member_ `nointerpolation float ParticleRandom : PARTICLE_RANDOM;` _[#if USE_PARTICLE_RANDOM]_
  - L138 _member_ `nointerpolation float4 ParticleToWorld[3] : PARTICLE_LOCAL_TO_WORLD;` _[#if USE_PARTICLE_LOCAL_TO_WORLD]_
  - L142 _member_ `nointerpolation float4 WorldToParticle[3] : PARTICLE_WORLD_TO_LOCAL;` _[#if USE_PARTICLE_WORLD_TO_LOCAL]_
  - L146 _member_ `nointerpolation uint PrimitiveId : PRIMITIVE_ID;` _[#if (VF_USE_PRIMITIVE_SCENE_DATA == 1)]_
- L150-210 _struct_ **`FVertexFactoryIntermediates`** `struct FVertexFactoryIntermediates`
  - L153 _member_ `uint ParticleIndex;` — The index of the particle to use when accessing data buffers
  - L156 _member_ `float4 VertexColor;` — The color of the vertex.
  - L159 _member_ `float4 ParticleColor;` — The color of the particle.
  - L163 _member_ `float2 TexCoords[NUM_MATERIAL_TEXCOORDS_VERTEX];` _[#if NUM_MATERIAL_TEXCOORDS_VERTEX]_
  - L166 _member_ `float4 SubUVCoords;` _[#if USE_PARTICLE_SUBUVS]_
  - L167 _member_ `nointerpolation float SubUVLerp;` _[#if USE_PARTICLE_SUBUVS]_
  - L172 _member_ `float4 DynamicParameter;` _[#if (DYNAMIC_PARAMETERS_MASK & 1)]_
  - L175 _member_ `float4 DynamicParameter1;` _[#if (DYNAMIC_PARAMETERS_MASK & 2)]_
  - L178 _member_ `float4 DynamicParameter2;` _[#if (DYNAMIC_PARAMETERS_MASK & 4)]_
  - L181 _member_ `float4 DynamicParameter3;` _[#if (DYNAMIC_PARAMETERS_MASK & 8)]_
  - L185 _member_ `float4 ParticleVelocity;` — The velocity of the particle, XYZ: direction, W: speed.
  - L188 _member_ `float3 ParticleTranslatedWorldPosition;` — Particle position in camera-centered translated world space.
  - L192 _member_ `float RelativeTime;` — Relative time. _[#if NEEDS_PARTICLE_TIME]_
  - L197 _member_ `float ParticleRandom;` — Particle Random value _[#if NEEDS_PARTICLE_RANDOM]_
  - L200 _member_ `FLWCMatrix ParticleToWorld;`
  - L201 _member_ `FLWCInverseMatrix WorldToParticle;`
  - L202 _member_ `FLWCMatrix PrevParticleToWorld;`
  - L203 _member_ `float3x3 ParticleToWorldNoScale;`
  - L205 _member_ `float3x3 TangentToLocal;`
  - L206 _member_ `float TangentDeterminant;`
  - L209 _member_ `FSceneDataIntermediates SceneData;` — Cached primitive and instance data
- L873-876 _struct_ **`FVertexFactoryRayTracingInterpolants`** `struct FVertexFactoryRayTracingInterpolants` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION \|\| RAYHITGROUPSHADER]_
  - L875 _member_ `FVertexFactoryInterpolantsVSToPS InterpolantsVSToPS;` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION \|\| RAYHITGROUPSHADER]_

#### Functions (27)

- L212-215 _function_ `FPrimitiveSceneData GetPrimitiveData(FVertexFactoryIntermediates Intermediates)`
- L217-220 _function_ `FDFMatrix GetParticleTransform(FVertexFactoryIntermediates Inters)`
- L222-225 _function_ `FDFInverseMatrix GetParticleInvTransform(FVertexFactoryIntermediates Inters)`
- L227-230 _function_ `FDFMatrix GetParticlePrevTransform(FVertexFactoryIntermediates Inters)`
- L232-235 _function_ `float3x3 GetParticleRotationNoScale(FVertexFactoryIntermediates Inters)`
- L237-247 _function_ `float2 GetUV(FVertexFactoryInterpolantsVSToPS Interpolants, int UVIndex)`
- L250-363 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(FVertexFactoryInterpolantsVSToPS Interpolants, float4 SvPosition)` — Converts from vertex factory specific interpolants to a FMaterialPixelParameters, which is used by material inputs.
- L369-463 _function_ `FMaterialVertexParameters GetMaterialVertexParameters( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, float3x3 TangentToLocal, bool bIsPreviousFrame = false)` — Converts from vertex factory specific input to a FMaterialVertexParameters, which is used by vertex shader material inputs.
- L465-491 _function_ `float3x3 CalculateTangentToLocal(FVertexFactoryInput Input, out float TangentDeterminant)`
- L493-684 _function_ `FVertexFactoryIntermediates GetVertexFactoryIntermediates(FVertexFactoryInput Input)`
- L693-696 _function_ `float3x3 VertexFactoryGetTangentToLocal( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates )` — Get the 3x3 tangent basis vectors for this vertex factory this vertex factory will calculate the binormal on-the-fly @param Input - vertex input stream structure @return 3x3 matrix
- L699-704 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — @return translated world position
- L706-709 _function_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L711-714 _function_ `float4 VertexFactoryGetRasterizedWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float4 InWorldPosition)`
- L716-719 _function_ `float3 VertexFactoryGetWorldNormal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L721-724 _function_ `float3 VertexFactoryGetPositionForVertexLighting(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 TranslatedWorldPosition)`
- L726-739 _function_ `void CalcTangentToWorld(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, out float3 TangentToWorld0, out float4 TangentToWorld2)`
- L741-842 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryGetInterpolantsVSToPS(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)`
- L845-850 _function_ `float4 VertexFactoryGetPreviousWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — @return previous translated world position
- L853-856 _function_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — local position relative to primitive
- L858-865 _function_ `uint VertexFactoryGetPrimitiveId(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L867-870 _function_ `float4 VertexFactoryGetTranslatedPrimitiveVolumeBounds(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L878-887 _function_ `float2 VertexFactoryGetRayTracingTextureCoordinate( FVertexFactoryRayTracingInterpolants Interpolants )` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION \|\| RAYHITGROUPSHADER]_
- L889-892 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryAssignInterpolants(FVertexFactoryRayTracingInterpolants Input)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION \|\| RAYHITGROUPSHADER]_
- L894-899 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryGetRayTracingInterpolants(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION \|\| RAYHITGROUPSHADER]_
- L901-957 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryInterpolate(FVertexFactoryRayTracingInterpolants a, float aInterp, FVertexFactoryRayTracingInterpolants b, float bInterp)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION \|\| RAYHITGROUPSHADER]_
- L962-985 _function_ `FVertexFactoryInput LoadVertexFactoryInputForHGS(uint TriangleIndex, int VertexIndex)` _[#if RAYHITGROUPSHADER]_

#### Prototypes (2)

- L365 _prototype_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L366 _prototype_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`

#### Top-level macro invocations (3)

- L69 _macro_call_ `VF_GPUSCENE_DECLARE_INPUT_BLOCK(13)` (scope `FVertexFactoryInput`) _[#if (VF_USE_PRIMITIVE_SCENE_DATA == 1)]_
- L70 _macro_call_ `VF_INSTANCED_STEREO_DECLARE_INPUT_BLOCK()` (scope `FVertexFactoryInput`) _[#if (VF_USE_PRIMITIVE_SCENE_DATA == 1)]_
- L77 _macro_call_ `VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FVertexFactoryInput`)

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `NIAGARA_MESH_VF_FLAGS` → entry not found in file (macro-generated or #include'd); C++ `FNiagaraMeshVertexFactory`  via IMPLEMENT_VERTEX_FACTORY_TYPE (Plugins/FX/Niagara/Source/NiagaraVertexFactories/Private/NiagaraMeshVertexFactory.cpp:269)

### `Plugins/FX/Niagara/Shaders/Private/NiagaraNeighborQuerySort.usf` (Private)

- lines: 487; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Macros (#define, 2)

- L15 `#define NEIGHBORQUERY_INVALID_CELL 0xFFFFFFFF`
- L326 `#define USE_BITONIC_SCATTER ` _[#if NEIGHBOR_QUERY_SCATTER_CS]_

#### Entry points (4)

- L136-179 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void HistogramCS(uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FNiagaraNeighborQueryHistogramCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraNeighborQuerySort.cpp:36) _[#if NEIGHBOR_QUERY_HISTOGRAM_CS]_
- L207-280 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void PrefixSumLocalScanCS(uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FNiagaraNeighborQueryPrefixSumLocalScanCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraNeighborQuerySort.cpp:78) _[#if NEIGHBOR_QUERY_PREFIX_SUM_LOCAL_SCAN_CS]_
- L293-315 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void PrefixSumPropagateCS(uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FNiagaraNeighborQueryPrefixSumPropagateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraNeighborQuerySort.cpp:103) _[#if NEIGHBOR_QUERY_PREFIX_SUM_PROPAGATE_CS]_
- L380-484 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ScatterCS(uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FNiagaraNeighborQueryScatterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraNeighborQuerySort.cpp:137) _[#if NEIGHBOR_QUERY_SCATTER_CS]_

#### Global resources (textures / buffers / samplers) (13)

- L32 _resource_ `Buffer<int> CellIdBuffer;` _[#if NEIGHBOR_QUERY_HISTOGRAM_CS]_
- L33 _resource_ `RWBuffer<int> CellCountBuffer;` _[#if NEIGHBOR_QUERY_HISTOGRAM_CS]_
- L198 _resource_ `Buffer<int> InputBuffer;` _[#if NEIGHBOR_QUERY_PREFIX_SUM_LOCAL_SCAN_CS]_
- L199 _resource_ `RWBuffer<int> OutputBuffer;` _[#if NEIGHBOR_QUERY_PREFIX_SUM_LOCAL_SCAN_CS]_
- L200 _resource_ `RWBuffer<int> BlockSumsBuffer;` _[#if NEIGHBOR_QUERY_PREFIX_SUM_LOCAL_SCAN_CS]_
- L287 _resource_ `Buffer<int> BlockSumsBuffer;` _[#if NEIGHBOR_QUERY_PREFIX_SUM_PROPAGATE_CS]_
- L288 _resource_ `RWBuffer<int> OutputBuffer;` _[#if NEIGHBOR_QUERY_PREFIX_SUM_PROPAGATE_CS]_
- L328 _resource_ `Buffer<int> CellIdBuffer;` _[#if NEIGHBOR_QUERY_SCATTER_CS]_
- L329 _resource_ `Buffer<int> ParticleIdIndexBuffer;` _[#if NEIGHBOR_QUERY_SCATTER_CS]_
- L330 _resource_ `RWBuffer<int> CellOffsetBuffer;` _[#if NEIGHBOR_QUERY_SCATTER_CS]_
- L331 _resource_ `RWBuffer<int> ParticleListBuffer;` _[#if NEIGHBOR_QUERY_SCATTER_CS]_
- L332 _resource_ `Buffer<int> AcquireTagBuffer;` _[#if NEIGHBOR_QUERY_SCATTER_CS]_
- L333 _resource_ `RWBuffer<int> AcquireTagListBuffer;` _[#if NEIGHBOR_QUERY_SCATTER_CS]_

#### Global parameters (uniforms) (12)

- L34 _parameter_ `uint NumSlots;` _[#if NEIGHBOR_QUERY_HISTOGRAM_CS]_
- L35 _parameter_ `uint GroupsX;` _[#if NEIGHBOR_QUERY_HISTOGRAM_CS]_
- L201 _parameter_ `uint NumElements;` _[#if NEIGHBOR_QUERY_PREFIX_SUM_LOCAL_SCAN_CS]_
- L202 _parameter_ `uint GroupsX;` _[#if NEIGHBOR_QUERY_PREFIX_SUM_LOCAL_SCAN_CS]_
- L203 _parameter_ `uint NumGroups;` _[#if NEIGHBOR_QUERY_PREFIX_SUM_LOCAL_SCAN_CS]_
- L289 _parameter_ `uint NumElements;` _[#if NEIGHBOR_QUERY_PREFIX_SUM_PROPAGATE_CS]_
- L290 _parameter_ `uint GroupsX;` _[#if NEIGHBOR_QUERY_PREFIX_SUM_PROPAGATE_CS]_
- L291 _parameter_ `uint NumGroups;` _[#if NEIGHBOR_QUERY_PREFIX_SUM_PROPAGATE_CS]_
- L334 _parameter_ `uint NumSlots;` _[#if NEIGHBOR_QUERY_SCATTER_CS]_
- L335 _parameter_ `uint MaxCellsPerParticle;` _[#if NEIGHBOR_QUERY_SCATTER_CS]_
- L336 _parameter_ `uint GroupsX;` _[#if NEIGHBOR_QUERY_SCATTER_CS]_
- L337 _parameter_ `uint bHasPersistentIDBuffers;` _[#if NEIGHBOR_QUERY_SCATTER_CS]_

#### groupshared (5)

- L42 _groupshared_ `groupshared int SortedCellIds[THREADGROUP_SIZE];` _[#if NEIGHBOR_QUERY_HISTOGRAM_CS && defined(USE_BITONIC_HISTOGRAM)]_
- L205 _groupshared_ `groupshared int SharedPartials[THREADGROUP_SIZE];` _[#if NEIGHBOR_QUERY_PREFIX_SUM_LOCAL_SCAN_CS]_
- L345 _groupshared_ `groupshared int ScatterSortedCellIds[THREADGROUP_SIZE];` — Parallel arrays in shared memory: cell IDs and original slot indices. After bitonic sort (keyed on cell ID, carrying slot index), each thread can derive its local offset within the run and write to a contiguous block claimed by one coalesced atomic per unique cell per group. _[#if NEIGHBOR_QUERY_SCATTER_CS && defined(USE_BITONIC_SCATTER)]_
- L346 _groupshared_ `groupshared uint ScatterSortedSlotIndices[THREADGROUP_SIZE];` _[#if NEIGHBOR_QUERY_SCATTER_CS && defined(USE_BITONIC_SCATTER)]_
- L347 _groupshared_ `groupshared uint RunWriteBase[THREADGROUP_SIZE];` _[#if NEIGHBOR_QUERY_SCATTER_CS && defined(USE_BITONIC_SCATTER)]_

#### Functions (2)

- L86-132 _function_ `void BitonicSortShared(uint LocalId)` — Parallel bitonic sort of SortedCellIds in shared memory. All threads in the group must participate (even if they hold INVALID_CELL). Bitonic sort works by building increasingly large "bitonic sequences" (sequences that go up then down, or down then up) and merging them. The outer loop doubles the block size each iteration; the inner loop performs the merge steps within each block. For THREADGROUP_SIZE=64: 21 barrier steps. For 128: 28 barrier steps. _[#if NEIGHBOR_QUERY_HISTOGRAM_CS && defined(USE_BITONIC_HISTOGRAM)]_
- L352-376 _function_ `void BitonicSortScatterShared(uint LocalId)` — Parallel bitonic sort of ScatterSortedCellIds in shared memory, carrying ScatterSortedSlotIndices as satellite data (swap when keys swap). All threads in the group must participate. _[#if NEIGHBOR_QUERY_SCATTER_CS && defined(USE_BITONIC_SCATTER)]_

### `Plugins/FX/Niagara/Shaders/Private/NiagaraParticleAccess.ush` (Private)

- lines: 276; parse: all-branches

#### Macros (#define, 5)

- L23 `#define USE_GLOBAL_NIAGARA_DATA_BUFFERS 1` _[#if !defined(USE_GLOBAL_NIAGARA_DATA_BUFFERS)]_
- L27 `#define ENABLE_NIAGARA_INT_DATA_ACCESS 1` _[#if !defined(ENABLE_NIAGARA_INT_DATA_ACCESS)]_
- L36 `#define NiagaraGetFloatBuffer() (NiagaraParticleDataFloat)` _[#if USE_GLOBAL_NIAGARA_DATA_BUFFERS]_
- L37 `#define NiagaraGetHalfBuffer() (NiagaraParticleDataHalf)` _[#if USE_GLOBAL_NIAGARA_DATA_BUFFERS]_
- L44 `#define NiagaraGetIntBuffer() (NiagaraParticleDataInt)` _[#if USE_GLOBAL_NIAGARA_DATA_BUFFERS && ENABLE_NIAGARA_INT_DATA_ACCESS]_
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (3)

- L31 _resource_ `Buffer<float> NiagaraParticleDataFloat;` _[#if USE_GLOBAL_NIAGARA_DATA_BUFFERS]_
- L32 _resource_ `Buffer<float> NiagaraParticleDataHalf;` _[#if USE_GLOBAL_NIAGARA_DATA_BUFFERS]_
- L41 _resource_ `Buffer<int> NiagaraParticleDataInt;` _[#if USE_GLOBAL_NIAGARA_DATA_BUFFERS && ENABLE_NIAGARA_INT_DATA_ACCESS]_

#### Global parameters (uniforms) (2)

- L33 _parameter_ `uint NiagaraFloatDataStride;` _[#if USE_GLOBAL_NIAGARA_DATA_BUFFERS]_
- L42 _parameter_ `uint NiagaraIntDataStride;` _[#if USE_GLOBAL_NIAGARA_DATA_BUFFERS && ENABLE_NIAGARA_INT_DATA_ACCESS]_

#### Functions (23)

- L38 _function_ `uint NiagaraGetFloatDataStride()` _[#if USE_GLOBAL_NIAGARA_DATA_BUFFERS]_
- L45 _function_ `uint NiagaraGetIntDataStride()` _[#if USE_GLOBAL_NIAGARA_DATA_BUFFERS && ENABLE_NIAGARA_INT_DATA_ACCESS]_
- L49-60 _function_ `bool NiagaraGetIsHalfAndFixupRegister(inout int RegisterIdx)`
- L62-65 _function_ `float NiagaraGetFloat_Internal(Buffer<float> FloatBuffer, int RegisterIdx, uint ParticleIdx)`
- L67-71 _function_ `float2 NiagaraGetVec2_Internal(Buffer<float> FloatBuffer, int RegisterIdx, uint ParticleIdx)`
- L73-78 _function_ `float3 NiagaraGetVec3_Internal(Buffer<float> FloatBuffer, int RegisterIdx, uint ParticleIdx)`
- L80-86 _function_ `float4 NiagaraGetVec4_Internal(Buffer<float> FloatBuffer, int RegisterIdx, uint ParticleIdx)`
- L88-99 _function_ `float NiagaraGetFloat(int RegisterIdx, uint ParticleIdx)`
- L101-112 _function_ `float2 NiagaraGetVec2(int RegisterIdx, uint ParticleIdx)`
- L114-125 _function_ `float3 NiagaraGetVec3(int RegisterIdx, uint ParticleIdx)`
- L127-138 _function_ `float4 NiagaraGetVec4(int RegisterIdx, uint ParticleIdx)`
- L140-152 _function_ `float NiagaraSafeGetFloat(int RegisterIdx, uint ParticleIdx, float Default)`
- L154-166 _function_ `float2 NiagaraSafeGetVec2(int RegisterIdx, uint ParticleIdx, float2 Default)`
- L168-180 _function_ `float3 NiagaraSafeGetVec3(int RegisterIdx, uint ParticleIdx, float3 Default)`
- L182-194 _function_ `float4 NiagaraSafeGetVec4(int RegisterIdx, uint ParticleIdx, float4 Default)`
- L198-201 _function_ `int NiagaraGetInt(int RegisterIdx, uint ParticleIdx)` _[#if ENABLE_NIAGARA_INT_DATA_ACCESS]_
- L203-207 _function_ `int2 NiagaraGetInt2(int RegisterIdx, uint ParticleIdx)` _[#if ENABLE_NIAGARA_INT_DATA_ACCESS]_
- L209-214 _function_ `int3 NiagaraGetInt3(int RegisterIdx, uint ParticleIdx)` _[#if ENABLE_NIAGARA_INT_DATA_ACCESS]_
- L216-222 _function_ `int4 NiagaraGetInt4(int RegisterIdx, uint ParticleIdx)` _[#if ENABLE_NIAGARA_INT_DATA_ACCESS]_
- L224-235 _function_ `int NiagaraSafeGetInt(int RegisterIdx, uint ParticleIdx, int Default)` _[#if ENABLE_NIAGARA_INT_DATA_ACCESS]_
- L237-248 _function_ `int2 NiagaraSafeGetInt2(int RegisterIdx, uint ParticleIdx, int2 Default)` _[#if ENABLE_NIAGARA_INT_DATA_ACCESS]_
- L250-261 _function_ `int3 NiagaraSafeGetInt3(int RegisterIdx, uint ParticleIdx, int3 Default)` _[#if ENABLE_NIAGARA_INT_DATA_ACCESS]_
- L263-274 _function_ `int4 NiagaraSafeGetInt4(int RegisterIdx, uint ParticleIdx, int4 Default)` _[#if ENABLE_NIAGARA_INT_DATA_ACCESS]_

### `Plugins/FX/Niagara/Shaders/Private/NiagaraPhysicsCommon.ush` (Private)

- lines: 20; parse: all-branches

#### groupshared (6)

- L12 _groupshared_ `groupshared float3 SharedNodePosition[THREADGROUP_SIZE];`
- L13 _groupshared_ `groupshared float4 SharedNodeOrientation[THREADGROUP_SIZE];`
- L15 _groupshared_ `groupshared float SharedInverseMass[THREADGROUP_SIZE];`
- L16 _groupshared_ `groupshared float SharedInverseInertia[THREADGROUP_SIZE];`
- L18 _groupshared_ `groupshared float3 SharedPreviousPosition[THREADGROUP_SIZE];`
- L19 _groupshared_ `groupshared float4 SharedPreviousOrientation[THREADGROUP_SIZE];`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraQuaternionUtils.ush` (Private)

- lines: 182; parse: all-branches

#### Macros (#define, 2)

- L5 `#define QUATERNION_IDENTITY float4(0,0,0,1)`
- L7 `#define SMALL_NUMBER 1e-8` _[#if !defined(SMALL_NUMBER)]_
- L3 #pragma `once`

#### Functions (12)

- L10-14 _function_ `float4 NormalizeQuat(in float4 Quat)`
- L16-19 _function_ `float4 InverseQuat(in float4 Quat)`
- L21-26 _function_ `float4 MultiplyQuat(in float4 QuatA, in float4 QuatB)`
- L28-32 _function_ `float3 RotateVectorByQuat(in float3 Vector, in float4 Quat)`
- L34-38 _function_ `float3 UnrotateVectorByQuat(in float3 Vector, in float4 Quat)`
- L40-78 _function_ `float4 SlerpQuat(in float4 QuatA, in float4 QuatB, float Slerp)`
- L80-87 _function_ `float4 FindQuatBetweenHelper(in float3 A, in float3 B, in float NormAB)`
- L89-93 _function_ `float4 FindQuatBetweenInternal(in float3 An, in float3 Bn)`
- L95-99 _function_ `float4 FindQuatBetweenNormals(in float3 NormalA, in float3 NormalB)`
- L101-105 _function_ `float4 FindQuatBetweenVectors(in float3 VectorA, in float3 VectorB)`
- L107-165 _function_ `float4 QuatFromMatrix(in float3 R[3])`
- L167-181 _function_ `float4 RotatorToQuat(float3 Rotator)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraRayMarchingShaders.usf` (Private)

- lines: 76; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/DistanceField/GlobalDistanceFieldShared.ush`, L5 `NiagaraAsyncGpuTraceCommon.ush`

#### Macros (#define, 2)

- L8 `#define THREADGROUP_SIZE_X 32` _[#if !defined(THREADGROUP_SIZE_X)]_
- L12 `#define MAX_MARCH_COUNT 16` _[#if !defined(MAX_MARCH_COUNT)]_

#### Entry points (1)

- L24-76 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void NiagaraRayMarchGlobalSdfCS(uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNiagaraRayMarchGlobalSdfCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraAsyncGpuTraceProviderGsdf.cpp:76)

#### Global resources (textures / buffers / samplers) (3)

- L15 _resource_ `StructuredBuffer<FNiagaraAsyncGpuTrace> Traces;`
- L16 _resource_ `Buffer<uint> TraceCounts;`
- L17 _resource_ `RWStructuredBuffer<FNiagaraAsyncGpuTraceResult> Results;`

#### Global parameters (uniforms) (4)

- L19 _parameter_ `uint TracesOffset;`
- L20 _parameter_ `uint TraceCountsOffset;`
- L21 _parameter_ `uint ResultsOffset;`
- L22 _parameter_ `float DistanceThreshold;`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraRayTraceCollisionGroupShaders.usf` (Private)

- lines: 30; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/HashTable.ush`

#### Entry points (1)

- L12-30 _entry_ `[numthreads(THREAD_COUNT, 1, 1)] void UpdatePrimIdToCollisionGroupMap(uint Index : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraUpdateCollisionGroupMapCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraAsyncGpuTraceProvider.cpp:71)

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `RWBuffer<uint> RWHashToCollisionGroups;`
- L9 _resource_ `Buffer<uint2> NewPrimIdCollisionGroupPairs;`

#### Global parameters (uniforms) (1)

- L10 _parameter_ `uint NumNewPrims;`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraRayTracingShaders.usf` (Private)

- lines: 163; parse: per-group
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/SceneData.ush`, L5 `/Engine/Private/ShadingCommon.ush`, L6 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L7 `/Engine/Private/RayTracing/RayTracingHitGroupCommon.ush`, L8 `NiagaraAsyncGpuTraceCommon.ush`, L9 `/Engine/Private/HashTable.ush`, L10 `/Engine/Private/RayTracing/VFXTraceRay.ush`

#### Entry points (3)

- L41-150 _entry_ `[numthreads(RAY_TRACING_THREAD_GROUP_SIZE_X, 1, 1)] void NiagaraCollisionRayTraceCS(uint3 DispatchThreadIndex : SV_DispatchThreadID, uint3 DispatchGroupId : SV_GroupID, uint DispatchGroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNiagaraCollisionRayTraceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraAsyncGpuTraceProviderHwrt.cpp:240) _[#if COMPUTESHADER]_
- L152-157 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(NiagaraCollisionRayTraceCH, FVFXTracePayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FNiagaraCollisionRayTraceCH` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraAsyncGpuTraceProviderHwrt.cpp:242)
- L159-162 _entry_ `RAY_TRACING_ENTRY_MISS(NiagaraCollisionRayTraceMiss, FVFXTracePayload, Payload)` — stage: **miss** — C++: `FNiagaraCollisionRayTraceMiss` SF_RayMiss via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraAsyncGpuTraceProviderHwrt.cpp:243)

#### Global resources (textures / buffers / samplers) (5)

- L12 _resource_ `RaytracingAccelerationStructure TLAS;`
- L13 _resource_ `StructuredBuffer<FNiagaraAsyncGpuTrace> Rays;`
- L15 _resource_ `RWStructuredBuffer<FNiagaraAsyncGpuTraceResult> CollisionOutput;`
- L19 _resource_ `Buffer<uint> RayTraceCounts;` _[#if NIAGARA_RAYTRACE_FAKE_INDIRECT \|\| COMPUTESHADER]_
- L23 _resource_ `Buffer<uint> HashToCollisionGroups;`

#### Global parameters (uniforms) (4)

- L14 _parameter_ `uint RaysOffset;`
- L16 _parameter_ `uint CollisionOutputOffset;`
- L20 _parameter_ `uint RayTraceCountsOffset;` _[#if NIAGARA_RAYTRACE_FAKE_INDIRECT \|\| COMPUTESHADER]_
- L24 _parameter_ `uint MaxRetraces;`

#### Functions (1)

- L27-37 _function_ `bool FindCollisionGroup(int GPUSceneIndexId, out int CollisionGroup)` _[#if NIAGARA_SUPPORTS_COLLISION_GROUPS]_

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `NiagaraCollisionRayTraceRG` → entry not found in file (macro-generated or #include'd); C++ `FNiagaraCollisionRayTraceRG` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraAsyncGpuTraceProviderHwrt.cpp:241)

### `Plugins/FX/Niagara/Shaders/Private/NiagaraRibbonVertexFactory.ush` (Private)

- lines: 1213; parse: all-branches
- includes: L7 `/Engine/Private/VertexFactoryCommon.ush`, L8 `NiagaraVFCommon.usf`, L1212 `/Engine/Private/VertexFactoryDefaultInterface.ush`

#### Macros (#define, 18)

- L10 `#define USE_PARTICLE_POSITION (NEEDS_PARTICLE_POSITION)`
- L11 `#define USE_PARTICLE_VELOCITY (NEEDS_PARTICLE_VELOCITY)`
- L12 `#define USE_PARTICLE_TIME (NEEDS_PARTICLE_TIME)`
- L13 `#define USE_PARTICLE_SIZE (NEEDS_PARTICLE_SIZE)`
- L14 `#define USE_PARTICLE_RANDOM (NEEDS_PARTICLE_RANDOM)`
- L15 `#define USE_PARTICLE_INTERPOLATION 1`
- L17 `#define U_DISTRIBUTION_SCALED_UNIFORMLY 0`
- L18 `#define U_DISTRIBUTION_SCALED_USING_RIBBON_LENGTH 1`
- L19 `#define U_DISTRIBUTION_TILED_OVER_RIBBON_LENGTH 2`
- L20 `#define U_DISTRIBUTION_TILED_FROM_START_OVER_RIBBON_LENGTH 3`
- L22 `#define SLICEVERTEXDATA_POSITION_OFFSET 0`
- L23 `#define SLICEVERTEXDATA_NORMAL_OFFSET 2`
- L24 `#define SLICEVERTEXDATA_TEXTUREV_OFFSET 4`
- L25 `#define SLICEVERTEXDATA_STRIDE 5`
- L27 `#define INDEX_GEN_DRAW_INDIRECT_OFFSET 3`
- L29 `#define INDEX_GEN_NUM_SUB_SEGMENTS_OFFSET 15`
- L30 `#define INDEX_GEN_ONE_OVER_NUM_SUB_SEGMENTS_OFFSET 16`
- L114 `#define GetInstanceIdFromVF(VFInput) (VFInput.InstanceId)` _[#if FEATURE_LEVEL >= FEATURE_LEVEL_SM4 && SUPPORT_SHADOW_DEPTH_POINT && USING_VERTEX_SHADER_LAYER]_
- L113 #undef `GetInstanceIdFromVF`

#### Structs / classes (7)

- L107-121 _struct_ **`FVertexFactoryInput`** `struct FVertexFactoryInput`
  - L109 _member_ `uint InterpVtxId : SV_VertexID;`
  - L115 _member_ `uint InstanceId : SV_InstanceID;` _[#if FEATURE_LEVEL >= FEATURE_LEVEL_SM4 && SUPPORT_SHADOW_DEPTH_POINT && USING_VERTEX_SHADER_LAYER]_
- L124-131 _struct_ **`FInterpVtxData`** `struct FInterpVtxData` — The interpolation data required for an interp vertex.
  - L126 _member_ `uint RawParticleId0;`
  - L127 _member_ `uint RawParticleId1;`
  - L128 _member_ `uint ParticleId0;`
  - L129 _member_ `uint ParticleId1;`
  - L130 _member_ `float Alpha;`
- L133-143 _struct_ **`FSegmentData`** `struct FSegmentData`
  - L135 _member_ `float2 UV0Scale;`
  - L136 _member_ `float2 UV0Offset;`
  - L137 _member_ `float2 UV1Scale;`
  - L138 _member_ `float2 UV1Offset;`
  - L139 _member_ `float U0DistributionScaler;`
  - L140 _member_ `float U1DistributionScaler;`
  - L141 _member_ `uint StartParticleId;`
  - L142 _member_ `uint LastParticleId;`
- L145-159 _struct_ **`FRibbonPositionIntermediates`** `struct FRibbonPositionIntermediates`
  - L147 _member_ `FLWCVector3 Position;`
  - L148 _member_ `float3 LocalPosition;`
  - L149 _member_ `float3 Direction;`
  - L150 _member_ `float DistanceOnSegment;`
  - L151 _member_ `float RibbonWidth;`
  - L153 _member_ `float3 GeoUp;`
  - L154 _member_ `float3 GeoRight;`
  - L156 _member_ `float3 TangentX;`
  - L157 _member_ `float3 TangentY;`
  - L158 _member_ `float3 TangentZ;`
- L161-201 _struct_ **`FVertexFactoryIntermediates`** `struct FVertexFactoryIntermediates`
  - L163 _member_ `FRibbonPositionIntermediates Current;`
  - L164 _member_ `FRibbonPositionIntermediates Previous;`
  - L165 _member_ `float4 Color;`
  - L167 _member_ `float4 TexCoord;`
  - L170 _member_ `float4 TranslatedWorldPositionAndSize;` _[#if USE_PARTICLE_POSITION]_
  - L173 _member_ `float4 ParticleVelocity;`
  - L176 _member_ `float RelativeTime;` _[#if USE_PARTICLE_TIME]_
  - L180 _member_ `float2 ParticleSize;` _[#if USE_PARTICLE_SIZE]_
  - L184 _member_ `float ParticleRandom;` _[#if USE_PARTICLE_RANDOM]_
  - L188 _member_ `float4 DynamicParameter;` _[#if (DYNAMIC_PARAMETERS_MASK & 1) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
  - L191 _member_ `float4 DynamicParameter1;` _[#if (DYNAMIC_PARAMETERS_MASK & 2) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
  - L194 _member_ `float4 DynamicParameter2;` _[#if (DYNAMIC_PARAMETERS_MASK & 4) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
  - L197 _member_ `float4 DynamicParameter3;` _[#if (DYNAMIC_PARAMETERS_MASK & 8) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
  - L200 _member_ `FSceneDataIntermediates SceneData;` — Cached primitive and instance data
- L208-253 _struct_ **`FVertexFactoryInterpolantsVSToPS`** `struct FVertexFactoryInterpolantsVSToPS`
  - L210 _member_ `TANGENTTOWORLD_INTERPOLATOR_BLOCK float4 DynamicParameter : PARTICLE_DYNAMIC_PARAM0;`
  - L216 _member_ `float4 DynamicParameter1 : PARTICLE_DYNAMIC_PARAM1;` _[#if (DYNAMIC_PARAMETERS_MASK & 2)]_
  - L219 _member_ `float4 DynamicParameter2 : PARTICLE_DYNAMIC_PARAM2;` _[#if (DYNAMIC_PARAMETERS_MASK & 4)]_
  - L222 _member_ `float4 DynamicParameter3 : PARTICLE_DYNAMIC_PARAM3;` _[#if (DYNAMIC_PARAMETERS_MASK & 8)]_
  - L226 _member_ `float4 Color : TEXCOORD0;` _[#if NEEDS_PARTICLE_COLOR]_
  - L230 _member_ `float4 TexCoords[(NUM_TEX_COORD_INTERPOLATORS + 1) / 2] : TEXCOORD1;` _[#if NUM_TEX_COORD_INTERPOLATORS]_
  - L235 _member_ `float4 TranslatedWorldPositionAndSize : PARTICLE_POSITION;` — Cam-relative (translated) particle center and radius _[#if USE_PARTICLE_POSITION]_
  - L239 _member_ `float4 ParticleVelocity : PARTICLE_VELOCITY;` _[#if USE_PARTICLE_VELOCITY]_
  - L243 _member_ `float RelativeTime : PARTICLE_TIME;` _[#if USE_PARTICLE_TIME]_
  - L247 _member_ `float2 ParticleSize : PARTICLE_SIZE;` _[#if USE_PARTICLE_SIZE]_
  - L251 _member_ `float ParticleRandom : PARTICLE_RANDOM;` _[#if USE_PARTICLE_RANDOM]_
- L1044-1047 _struct_ **`FVertexFactoryRayTracingInterpolants`** `struct FVertexFactoryRayTracingInterpolants` _[#if RAYHITGROUPSHADER]_
  - L1046 _member_ `FVertexFactoryInterpolantsVSToPS InterpolantsVSToPS;` _[#if RAYHITGROUPSHADER]_

#### Functions (52)

- L32-35 _function_ `uint UnpackParticleId(uint InterpIdx)`
- L37-40 _function_ `uint UnpackInterpSlice(uint InterpIdx)`
- L42-45 _function_ `uint UnpackParticleVertexId(uint InterpIdx)`
- L47-52 _function_ `float2 UnpackParticleVertexPosition(uint InterpIdx)`
- L54-59 _function_ `float2 UnpackParticleVertexNormal(uint InterpIdx)`
- L61-64 _function_ `float UnpackParticleVertexTextureV(uint InterpIdx)`
- L66-76 _function_ `FLWCVector3 TransformPosition(FLWCMatrix LocalToWorld, float3 InPosition)`
- L78-88 _function_ `float3 TransformVector(FLWCMatrix LocalToWorld, float3 InvScale, float3 InVector)`
- L90-95 _function_ `float3 CubicInterp(float3 P0, float3 T0, float3 P1, float3 T1, float A, float TS)`
- L203-206 _function_ `FPrimitiveSceneData GetPrimitiveData(FVertexFactoryIntermediates Intermediates)`
- L256-259 _function_ `bool UVIndexUseZW(int UVIndex)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L261-265 _function_ `float2 GetUV(FVertexFactoryInterpolantsVSToPS Interpolants, int UVIndex)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L267-278 _function_ `void SetUV(inout FVertexFactoryInterpolantsVSToPS Interpolants, int UVIndex, float2 InValue)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L282-293 _function_ `uint GetInterpCount()`
- L295-306 _function_ `float GetOneOverInterpCount()`
- L308-340 _function_ `void GetInterpVtxAndRibbonDataData(FVertexFactoryInput Input, out FInterpVtxData InterpVtxData, out FSegmentData SegmentData)`
- L343-409 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(FVertexFactoryInterpolantsVSToPS Interpolants, float4 SvPosition)` — Converts from vertex factory specific interpolants to a FMaterialPixelParameters, which is used by material inputs.
- L415-495 _function_ `FMaterialVertexParameters GetMaterialVertexParameters( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, float3x3 TangentToLocal, bool bIsPreviousFrame = false)` — Converts from vertex factory specific input to a FMaterialVertexParameters, which is used by vertex shader material inputs.
- L497-505 _function_ `float3 SafeNormalize(float3 V, float3 Default)`
- L507-517 _function_ `float4 GetDirectionAndMagnitude(float3 V)`
- L520-523 _function_ `float3x3 CalcTangentBasis(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — derive basis vectors
- L525-528 _function_ `float GetTangentAndDistanceComponent(int RawParticleID, int ElementIndex)`
- L535-643 _function_ `FRibbonPositionIntermediates GetRibbonPositionIntermediates( FInterpVtxData InterpVtxData, int PositionDataOffset, int FacingDataOffset, int TwistDataOffset, int WidthDataOffset, float2 SliceVertexNormals, FLWCMatrix LocalToWorld, float3 InvScale)` — known limitations: -TangentsAndDistances is from the current frame and if we're generating intermediates for the previous frame for velocity rendering we won't get the exact same results.  Issues around trying to supply a previous version of the TangentsAndDistances buffer include the fact that the active particles can differ between frames and so we'd also need to supply particle indices for the previous frames as well
- L645-859 _function_ `FVertexFactoryIntermediates GetVertexFactoryIntermediates(FVertexFactoryInput Input)`
- L861-866 _function_ `FLWCVector3 ConstructWorldPositionLWC(FVertexFactoryInput Input, FRibbonPositionIntermediates Intermediates)`
- L868-873 _function_ `float3 ConstructWorldPosition(FVertexFactoryInput Input, FRibbonPositionIntermediates Intermediates, FLWCVector3 PreViewTranslation)`
- L875-878 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L880-883 _function_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L885-888 _function_ `float4 VertexFactoryGetPreviousWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L891-894 _function_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — local position relative to instance
- L896-899 _function_ `float3 VertexFactoryGetWorldNormal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L902-905 _function_ `float4 VertexFactoryGetRasterizedWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float4 InWorldPosition)`
- L907-910 _function_ `float3 VertexFactoryGetPositionForVertexLighting(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 TranslatedWorldPosition)`
- L912-973 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryGetInterpolantsVSToPS(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)`
- L981-984 _function_ `float3x3 VertexFactoryGetTangentToLocal( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates )` — Get the 3x3 tangent basis vectors for this vertex factory @param Input - vertex input stream structure @return 3x3 matrix
- L986-989 _function_ `float4 VertexFactoryGetTranslatedPrimitiveVolumeBounds(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L991-994 _function_ `uint VertexFactoryGetPrimitiveId(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L998-1012 _function_ `FVertexFactoryInput LoadVertexFactoryInputForDynamicUpdate(uint TriangleIndex, int VertexIndex, uint PrimitiveId, uint DrawInstanceId)` _[#if COMPUTESHADER]_
- L1014-1017 _function_ `uint GetNumRayTracingDynamicMeshVerticesIndirect()` _[#if COMPUTESHADER]_
- L1021-1032 _function_ `FVertexFactoryInput LoadVertexFactoryInputForHGS(uint TriangleIndex, int VertexIndex)` _[#if RAYHITGROUPSHADER]_
- L1034-1037 _function_ `uint GetNumRayTracingDynamicMeshVerticesIndirect()` _[#if RAYHITGROUPSHADER]_
- L1049-1056 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryGetRayTracingInterpolants(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)` _[#if RAYHITGROUPSHADER]_
- L1058-1065 _function_ `float2 VertexFactoryGetRayTracingTextureCoordinate( FVertexFactoryRayTracingInterpolants Interpolants )` _[#if RAYHITGROUPSHADER]_
- L1067-1120 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryInterpolate(FVertexFactoryRayTracingInterpolants a, float aInterp, FVertexFactoryRayTracingInterpolants b, float bInterp)` _[#if RAYHITGROUPSHADER]_
- L1122-1125 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryAssignInterpolants(FVertexFactoryRayTracingInterpolants Input)` _[#if RAYHITGROUPSHADER]_
- L1130-1141 _function_ `FVertexFactoryInput NiagaraVertexFactoryExport_InitVertexFactoryInput(uint TriangleIndex, int VertexIndex, uint PrimitiveId, uint DrawInstanceId)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1143-1146 _function_ `uint NiagaraVertexFactoryExport_GetIndirectVertexCount()` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1148-1151 _function_ `FLWCVector3 NiagaraVertexFactoryExport_GetPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1153-1156 _function_ `float4 NiagaraVertexFactoryExport_GetColor(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1158-1161 _function_ `float3x3 NiagaraVertexFactoryExport_GetTangentBasis(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1163-1175 _function_ `float2 NiagaraVertexFactoryExport_GetTexCoord(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, uint CoordIndex)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1177-1208 _function_ `float4 NiagaraVertexFactoryExport_GetDynamicParameter(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, uint ParameterIndex)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_

#### Prototypes (2)

- L411 _prototype_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L412 _prototype_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`

#### Top-level macro invocations (1)

- L117-121 _macro_call_ `VF_INSTANCED_STEREO_DECLARE_INPUT_BLOCK() VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FVertexFactoryInput`) _[#if !(FEATURE_LEVEL >= FEATURE_LEVEL_SM4 && SUPPORT_SHADOW_DEPTH_POINT && USING_VERTEX_SHADER_LAYER)]_

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `EVertexFactoryFlags::UsedWithMaterials 
	\| EVertexFactoryFlags::SupportsDynamicLighting
	\| EVertexFactoryFlags::SupportsRayTracing
	\| EVertexFactoryFlags::SupportsRayTracingDynamicGeometry
	\| EVertexFactoryFlags::SupportsPSOPrecaching` → entry not found in file (macro-generated or #include'd); C++ `FNiagaraRibbonVertexFactory`  via IMPLEMENT_VERTEX_FACTORY_TYPE (Plugins/FX/Niagara/Source/NiagaraVertexFactories/Private/NiagaraRibbonVertexFactory.cpp:197)

### `Plugins/FX/Niagara/Shaders/Private/NiagaraSVTToDenseBuffer.usf` (Private)

- lines: 25; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/SparseVolumeTexture/SparseVolumeTextureCommon.ush`

#### Entry points (1)

- L15-24 _entry_ `[numthreads(4, 4, 4)] void PerformCopyCS(uint3 Index : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraCopySVTToDenseBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraSVTShaders.cpp:10)

#### Global resources (textures / buffers / samplers) (5)

- L5 _resource_ `RWTexture3D<float4> DestinationBuffer;`
- L7 _resource_ `SamplerState TileDataTextureSampler;`
- L8 _resource_ `Texture3D<uint> SparseVolumeTexturePageTable;`
- L9 _resource_ `Texture3D SparseVolumeTextureA;`
- L12 _resource_ `int3 TextureSize;`

#### Global parameters (uniforms) (3)

- L10 _parameter_ `uint4 PackedSVTUniforms0;`
- L11 _parameter_ `uint4 PackedSVTUniforms1;`
- L13 _parameter_ `int MipLevels;`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraShaderVersion.ush` (Private)

- lines: 8; parse: all-branches
- L7 #pragma `message("UESHADERMETADATA_VERSION 409FA156-9F7E-4807-917C-BF2C380C51C5")`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraSharedDataGPU_StaticMesh.ush` (Private)

- lines: 87; parse: all-branches
- L10 #pragma `once`

#### Structs / classes (1)

- L13-19 _struct_ **`FNiagaraSharedDataGPU_StaticMesh`** `struct FNiagaraSharedDataGPU_StaticMesh` — Counterpart to struct in NiagaraManagedReference_StaticMesh.h
  - L15 _member_ `int IDTag;`
  - L16 _member_ `int DistanceFieldIndex;`
  - L17 _member_ `int PrimitiveIndex;`
  - L18 _member_ `int Padding;`

#### Global resources (textures / buffers / samplers) (1)

- L21 _resource_ `StructuredBuffer<FNiagaraSharedDataGPU_StaticMesh> NiagaraSharedData_StaticMesh_Buffer;`

#### Global parameters (uniforms) (1)

- L22 _parameter_ `int NiagaraSharedData_StaticMesh_NumSlots;`

#### Functions (2)

- L25-40 _function_ `int ResolveNiagaraManagedReferenceID_StaticMesh(NiagaraSharedDataID_StaticMesh StaticMeshID)` — Resolves a mesh DF Reference into a DFIndex that can be used to access distance field data.
- L46-87 _function_ `void ComputeClosestPointMeshDistanceField_LWCTiled(int DFIndex, const float3 WorldPosition, const float GridSampledDistance, out float3 OutClosestPosition, out float3 OutClosestNormal, out float MaxEncodedDistance, out bool bNormalIsValid)` — Returns closest point and normal on a mesh distance field to a given world space point. Duplicate implementation to NiagaraDistanceFieldQueries.ush but this handles LWC internally and takes in a tiled point directly from a Niagara Sim and outputs the correctly tiled point back ready for the Niagara Sim.

### `Plugins/FX/Niagara/Shaders/Private/NiagaraSortKeyGen.usf` (Private)

- lines: 296; parse: all-branches
- includes: L17 `/Engine/Private/Common.ush`, L18 `/Engine/Private/ComputeShaderUtils.ush`

#### Entry points (1)

- L219-294 _entry_ `[numthreads(THREAD_COUNT,1,1)] void GenerateParticleSortKeys(uint3 GroupId : SV_GroupID, int GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNiagaraSortKeyGenCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraVertexFactories/Private/NiagaraSortingGPU.cpp:29)

#### Global resources (textures / buffers / samplers) (7)

- L20 _resource_ `Buffer<float> NiagaraParticleDataFloat;`
- L21 _resource_ `Buffer<half> NiagaraParticleDataHalf;`
- L22 _resource_ `Buffer<int> NiagaraParticleDataInt;`
- L23 _resource_ `Buffer<uint> GPUParticleCountBuffer;`
- L56 _resource_ `RWBuffer<uint> OutKeys;`
- L57 _resource_ `RWBuffer<int> OutParticleIndices;`
- L58 _resource_ `RWBuffer<uint> OutCulledParticleCounts;`

#### Global parameters (uniforms) (28)

- L25 _parameter_ `uint FloatDataStride;`
- L26 _parameter_ `uint HalfDataStride;`
- L27 _parameter_ `uint IntDataStride;`
- L28 _parameter_ `uint ParticleCount;`
- L29 _parameter_ `uint GPUParticleCountOffset;`
- L30 _parameter_ `uint CulledGPUParticleCountOffset;`
- L31 _parameter_ `uint EmitterKey;`
- L32 _parameter_ `uint OutputOffset;`
- L33 _parameter_ `float3 CameraPosition;`
- L34 _parameter_ `float3 CameraDirection;`
- L35 _parameter_ `uint SortMode;`
- L36 _parameter_ `uint SortAttributeOffset;`
- L38 _parameter_ `uint SortKeyMask;` _[#if SORT_MAX_PRECISION]_
- L39 _parameter_ `uint SortKeyShift;` _[#if SORT_MAX_PRECISION]_
- L40 _parameter_ `uint SortKeySignBit;` _[#if SORT_MAX_PRECISION]_
- L42 _parameter_ `uint CullPositionAttributeOffset;`
- L43 _parameter_ `uint CullOrientationAttributeOffset;`
- L44 _parameter_ `uint CullScaleAttributeOffset;`
- L45 _parameter_ `int NumCullPlanes;`
- L46 _parameter_ `float4 CullPlanes[NIAGARA_KEY_GEN_MAX_CULL_PLANES];`
- L47 _parameter_ `int RendererVisibility;`
- L48 _parameter_ `uint RendererVisTagAttributeOffset;`
- L49 _parameter_ `int MeshIndex;`
- L50 _parameter_ `uint MeshIndexAttributeOffset;`
- L51 _parameter_ `float2 CullDistanceRangeSquared;`
- L52 _parameter_ `float4 LODScreenSize;`
- L53 _parameter_ `float4 LocalBoundingSphere;`
- L54 _parameter_ `float3 CullingWorldSpaceOffset;`

#### groupshared (1)

- L61 _groupshared_ `groupshared uint CullGroupCount;` _[#if ENABLE_CULLING && !USE_WAVE_INTRINSICS]_

#### Functions (9)

- L64-76 _function_ `float GetFloat(uint RegisterIdx, uint InstanceID)`
- L78-81 _function_ `int GetInt(uint RegisterIdx, uint InstanceID)`
- L83-86 _function_ `float2 GetVec2(uint RegisterIndex, uint InstanceID)`
- L88-91 _function_ `float3 GetVec3(uint RegisterIndex, uint InstanceID)`
- L93-96 _function_ `float4 GetVec4(uint RegisterIndex, uint InstanceID)`
- L98-102 _function_ `float3 RotateVectorByQuat(in float3 Vector, in float4 Quat)`
- L104-114 _function_ `void CullingPrologue(in uint GroupTID)`
- L116-137 _function_ `void CullingEpilogue(in bool bCulled, in uint GroupTID)`
- L139-217 _function_ `bool CullParticle(in uint ParticleIndex)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraSpriteVertexFactory.ush` (Private)

- lines: 1445; parse: all-branches
- includes: L8 `/Engine/Private/VertexFactoryCommon.ush`, L9 `/Engine/Private/ParticleVertexFactoryCommon.ush`, L10 `NiagaraVFCommon.usf`, L1444 `/Engine/Private/VertexFactoryDefaultInterface.ush`

#### Macros (#define, 16)

- L12 `#define USE_PARTICLE_LIGHTING_OFFSET (FEATURE_LEVEL >= FEATURE_LEVEL_SM5 && !MATERIAL_SHADINGMODEL_UNLIT)`
- L13 `#define USE_PARTICLE_POSITION (NEEDS_PARTICLE_POSITION \|\| PASS_NEEDS_PRIMITIVE_VOLUME_BOUNDS)`
- L14 `#define USE_PARTICLE_VELOCITY (NEEDS_PARTICLE_VELOCITY)`
- L15 `#define USE_PARTICLE_TIME (NEEDS_PARTICLE_TIME)`
- L16 `#define USE_PARTICLE_SIZE (NEEDS_PARTICLE_SIZE)`
- L17 `#define USE_PARTICLE_RANDOM (NEEDS_PARTICLE_RANDOM)`
- L18 `#define USE_PARTICLE_SPRITE_ROTATION (NEEDS_PARTICLE_SPRITE_ROTATION)`
- L22 `#define ALIGNMENT_MODE_UNALIGNED 0`
- L24 `#define ALIGNMENT_MODE_VELOCITYALIGNED 1`
- L26 `#define ALIGNMENT_MODE_CUSTOMALIGNMENT 2`
- L29 `#define FACING_MODE_FACECAMERA 0`
- L31 `#define FACING_MODE_FACECAMERAPLANE 1`
- L33 `#define FACING_MODE_CUSTOMFACINGVECTOR 2`
- L35 `#define FACING_MODE_FACECAMERAPOSITION 3`
- L37 `#define FACING_MODE_FACECAMERADISTANCEBLEND 4`
- L40 `#define GetInstanceIdFromVF(VFInput) (VFInput.InstanceId)`
- L39 #undef `GetInstanceIdFromVF`

#### Structs / classes (4)

- L42-48 _struct_ **`FVertexFactoryInput`** `struct FVertexFactoryInput`
  - L44 _member_ `float2 TexCoord : ATTRIBUTE0;`
  - L45 _member_ `uint VertexId : SV_VertexID;`
  - L46 _member_ `uint InstanceId : SV_InstanceID;`
- L119-187 _struct_ **`FVertexFactoryInterpolantsVSToPS`** `struct FVertexFactoryInterpolantsVSToPS`
  - L122 _member_ `float4 TangentToWorld0AndInterp_Sizer : TANGENTTOWORLD0;` — First row of the tangent to world matrix, Interp_Sizer used by SUBUV_PARTICLES in w
  - L124 _member_ `float4 TangentToWorld2 : TANGENTTOWORLD2;` — Last row of the tangent to world matrix in xyz
  - L127 _member_ `nointerpolation float4 DynamicParameter : PARTICLE_DYNAMIC_PARAM0;` _[#if (DYNAMIC_PARAMETERS_MASK & 1)]_
  - L130 _member_ `nointerpolation float4 DynamicParameter1 : PARTICLE_DYNAMIC_PARAM1;` _[#if (DYNAMIC_PARAMETERS_MASK & 2)]_
  - L133 _member_ `nointerpolation float4 DynamicParameter2 : PARTICLE_DYNAMIC_PARAM2;` _[#if (DYNAMIC_PARAMETERS_MASK & 4)]_
  - L136 _member_ `nointerpolation float4 DynamicParameter3 : PARTICLE_DYNAMIC_PARAM3;` _[#if (DYNAMIC_PARAMETERS_MASK & 8)]_
  - L140 _member_ `float4 Color : TEXCOORD0;` _[#if NEEDS_PARTICLE_COLOR]_
  - L144 _member_ `float4 TexCoords[(NUM_TEX_COORD_INTERPOLATORS + 1) / 2] : TEXCOORD1;` _[#if NUM_TEX_COORD_INTERPOLATORS]_
  - L149 _member_ `float2 LightMapUVs : LIGHTMAP_UVS;` _[#if LIGHTMAP_UV_ACCESS]_
  - L153 _member_ `float4 ParticleSubUVs : PARTICLE_SUBUVS;` _[#if USE_PARTICLE_SUBUVS]_
  - L158 _member_ `nointerpolation float4 ParticleTranslatedWorldPositionAndSize : PARTICLE_POSITION;` — Cam-relative (translated) particle center and radius _[#if USE_PARTICLE_POSITION]_
  - L160 _member_ `float3 DisplacedParticleCenterForNormal : PARTICLE_POSITION_FSN;` _[#if USE_PARTICLE_POSITION && GENERATE_SPHERICAL_PARTICLE_NORMALS]_
  - L165 _member_ `nointerpolation float4 ParticleVelocity : PARTICLE_VELOCITY;` _[#if USE_PARTICLE_VELOCITY]_
  - L169 _member_ `nointerpolation float RelativeTime : PARTICLE_TIME;` _[#if USE_PARTICLE_TIME]_
  - L173 _member_ `float3 LightingPositionOffset : PARTICLE_LIGHTING_OFFSET;` _[#if USE_PARTICLE_LIGHTING_OFFSET]_
  - L177 _member_ `nointerpolation float2 ParticleSize : PARTICLE_SIZE;` _[#if USE_PARTICLE_SIZE]_
  - L181 _member_ `nointerpolation float ParticleSpriteRotation : PARTICLE_SPRITE_ROTATION;` _[#if USE_PARTICLE_SPRITE_ROTATION]_
  - L185 _member_ `nointerpolation float ParticleRandom : PARTICLE_RANDOM;` _[#if USE_PARTICLE_RANDOM]_
- L189-267 _struct_ **`FVertexFactoryIntermediates`** `struct FVertexFactoryIntermediates`
  - L192 _member_ `FLWCVector3 VertexWorldPosition;` — The position of the vertex in translated world space.
  - L194 _member_ `FLWCVector3 PreviousVertexWorldPosition;` — Last frame's position of the vertex in translated world space.
  - L196 _member_ `float4 TranslatedWorldPositionAndSize;` — Particle translated world space position and size.
  - L197 _member_ `float4 PrevTranslatedWorldPositionAndSize;`
  - L199 _member_ `float3 TranslatedWorldPosition;` — Particle translated world space position without offsets.
  - L202 _member_ `float3 LightingPositionOffset;` _[#if USE_PARTICLE_LIGHTING_OFFSET]_
  - L206 _member_ `float4 TexCoord;` — The texture coordinate at this vertex.
  - L209 _member_ `float4 TexCoord_Unflipped;` — A second UV set. Always non-UV flipped. Allows use of UV flipping with Normal maps etc. _[#if NUM_MATERIAL_TEXCOORDS_VERTEX >= 3]_
  - L212 _member_ `float3 TangentUp;` — The sprite tangent in world space (+V).
  - L214 _member_ `float3 TangentRight;` — The sprite tangent in world space (+U).
  - L216 _member_ `float4 Color;` — The color of the sprite.
  - L218 _member_ `float4 ParticleVelocity;` — The velocity of the particle, XYZ: direction, W: speed.
  - L220 _member_ `float2 UVScale;` — The uv scale of the sprite.
  - L222 _member_ `FLWCVector3 Position;` — The particle worldspace position
  - L224 _member_ `float2 Size;`
  - L226 _member_ `float3 CustomFacingVector;`
  - L227 _member_ `float3 CustomAlignmentVector;`
  - L230 _member_ `float4 DynamicParameter;` _[#if (DYNAMIC_PARAMETERS_MASK & 1) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
  - L233 _member_ `float4 DynamicParameter1;` _[#if (DYNAMIC_PARAMETERS_MASK & 2) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
  - L236 _member_ `float4 DynamicParameter2;` _[#if (DYNAMIC_PARAMETERS_MASK & 4) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
  - L239 _member_ `float4 DynamicParameter3;` _[#if (DYNAMIC_PARAMETERS_MASK & 8) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
  - L243 _member_ `float SubImageLerp;` — The sub-image lerp.
  - L247 _member_ `float RelativeTime;` — Relative time. _[#if USE_PARTICLE_TIME]_
  - L251 _member_ `float3x3 TangentToLocal;` — Transform from tangent space to local space.
  - L253 _member_ `float2 ParticleSize;` — Size of the particle
  - L257 _member_ `float ParticleSpriteRotation;` _[#if USE_PARTICLE_SPRITE_ROTATION]_
  - L262 _member_ `float ParticleRandom;` — Particle Random value _[#if USE_PARTICLE_RANDOM]_
  - L266 _member_ `FSceneDataIntermediates SceneData;` — Cached primitive and instance data
- L1236-1239 _struct_ **`FVertexFactoryRayTracingInterpolants`** `struct FVertexFactoryRayTracingInterpolants` _[#if RAYHITGROUPSHADER]_
  - L1238 _member_ `FVertexFactoryInterpolantsVSToPS InterpolantsVSToPS;` _[#if RAYHITGROUPSHADER]_

#### Functions (72)

- L50-53 _function_ `uint GetCutoutNumVertices()`
- L55-58 _function_ `bool GetCutoutUseSubImage()`
- L60-63 _function_ `float2 NoneZeroSign(float2 v)`
- L67-105 _function_ `FVertexFactoryInput LoadVertexFactoryInputForHGS(uint TriangleIndex, int VertexIndex)` _[#if COMPUTESHADER \|\| RAYHITGROUPSHADER]_
- L107-110 _function_ `FVertexFactoryInput LoadVertexFactoryInputForDynamicUpdate(uint TriangleIndex, int VertexIndex, uint PrimitiveId, uint DrawInstanceId)` _[#if COMPUTESHADER \|\| RAYHITGROUPSHADER]_
- L111-116 _function_ `uint GetNumRayTracingDynamicMeshVerticesIndirect()` _[#if COMPUTESHADER \|\| RAYHITGROUPSHADER]_
- L269-272 _function_ `FPrimitiveSceneData GetPrimitiveData(FVertexFactoryIntermediates Intermediates)`
- L274-292 _function_ `float2 GetUV(FVertexFactoryIntermediates Intermediates, uint CoordIndex)`
- L295-298 _function_ `bool UVIndexUseZW(int UVIndex)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L300-304 _function_ `float2 GetUV(FVertexFactoryInterpolantsVSToPS Interpolants, int UVIndex)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L306-317 _function_ `void SetUV(inout FVertexFactoryInterpolantsVSToPS Interpolants, int UVIndex, float2 InValue)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L321-422 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(FVertexFactoryInterpolantsVSToPS Interpolants, float4 SvPosition)` — Converts from vertex factory specific interpolants to a FMaterialPixelParameters, which is used by material inputs.
- L428-532 _function_ `FMaterialVertexParameters GetMaterialVertexParameters( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, float3x3 TangentToLocal, bool bIsPreviousFrame = false)` — Converts from vertex factory specific input to a FMaterialVertexParameters, which is used by vertex shader material inputs.
- L534-541 _function_ `float3 SafeNormalize(float3 V)`
- L543-547 _function_ `float3 SafeNormalizeWithFallback(float3 V, float3 Fallback)`
- L549-641 _function_ `void GetTangents(FVertexFactoryInput Input, float3 ParticleTranslatedPosition, float Rotation, float3 CustomFacing, float3 CustomAlignment, float3 ParticleDirection, out float3 OutRight, out float3 OutUp)`
- L644-681 _function_ `float3x3 CalcTangentBasis(FVertexFactoryIntermediates Intermediates)` — derive basis vectors
- L683-726 _function_ `void ComputeBillboardUVs(FVertexFactoryInput Input, float2 ParticleSize, float SubImageIndex, float2 UVScale, out float2 UVForPosition, out float2 UVForTexturing, out float2 UVForTexturingUnflipped)`
- L728-736 _function_ `FLWCVector3 SimToWorldPos(float3 SimSpacePos, FLWCMatrix LocalToWorld)`
- L738-745 _function_ `float3 LocalToWorldVec(float3 LocalSpaceVec, float3x3 LocalToWorld)`
- L747-755 _function_ `float3 SimToWorldVec(float3 SimSpaceVec, float3x3 LocalToWorld)`
- L761-764 _function_ `float3 GetNiagaraParticleSimPosition(uint InstanceID)`
- L766-770 _function_ `FLWCVector3 GetNiagaraParticlePosition(uint InstanceID)`
- L772-776 _function_ `float3 GetNiagaraParticleTranslatedWorldPosition(uint InstanceID)`
- L778-782 _function_ `FLWCVector3 GetNiagaraPreviousParticlePosition(uint InstanceID)`
- L784-788 _function_ `float3 GetNiagaraPreviousParticleTranslatedWorldPosition(uint InstanceID)`
- L790-793 _function_ `float3 GetNiagaraParticleVelocity(uint InstanceID)`
- L795-798 _function_ `float3 GetNiagaraPreviousParticleVelocity(uint InstanceID)`
- L800-803 _function_ `float2 GetNiagaraParticleSize(uint InstanceID)`
- L805-808 _function_ `float2 GetNiagaraPreviousParticleSize(uint InstanceID)`
- L810-815 _function_ `float GetNiagaraParticleRotation(uint InstanceID)`
- L817-822 _function_ `float GetNiagaraPreviousParticleRotation(uint InstanceID)`
- L824-827 _function_ `float4 GetNiagaraParticleColor(uint InstanceID)`
- L829-832 _function_ `float2 GetNiagaraUVScale(uint InstanceID)`
- L834-837 _function_ `float2 GetNiagaraPivotOffset(uint InstanceID)`
- L839-842 _function_ `float2 GetNiagaraPreviousPivotOffset(uint InstanceID)`
- L844-847 _function_ `float GetNiagaraParticleRandom(uint InstanceID)`
- L849-852 _function_ `float GetNiagaraCameraOffset(uint InstanceID)`
- L854-857 _function_ `float GetNiagaraPreviousCameraOffset(uint InstanceID)`
- L860-863 _function_ `float GetNiagaraNormalizedAge(uint InstanceID)` _[#if USE_PARTICLE_TIME]_
- L867-870 _function_ `float4 GetNiagaraParticleDynamicParameters(uint InstanceID)` _[#if (DYNAMIC_PARAMETERS_MASK & 1) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L873-876 _function_ `float4 GetNiagaraParticleDynamicParameters1(uint InstanceID)` _[#if (DYNAMIC_PARAMETERS_MASK & 2) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L879-882 _function_ `float4 GetNiagaraParticleDynamicParameters2(uint InstanceID)` _[#if (DYNAMIC_PARAMETERS_MASK & 4) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L885-888 _function_ `float4 GetNiagaraParticleDynamicParameters3(uint InstanceID)` _[#if (DYNAMIC_PARAMETERS_MASK & 8) \|\| WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L891-895 _function_ `float GetNiagaraParticleSubimage(uint InstanceID)`
- L897-901 _function_ `float3 GetNiagaraParticleFacingVector(uint InstanceID)`
- L903-907 _function_ `float3 GetNiagaraPreviousParticleFacingVector(uint InstanceID)`
- L909-912 _function_ `float3 GetNiagaraParticleAlignmentVector(uint InstanceID)`
- L914-917 _function_ `float3 GetNiagaraPreviousParticleAlignmentVector(uint InstanceID)`
- L919-1105 _function_ `FVertexFactoryIntermediates GetVertexFactoryIntermediates(FVertexFactoryInput Input)`
- L1107-1110 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L1112-1116 _function_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L1118-1121 _function_ `float3 VertexFactoryGetWorldNormal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L1123-1135 _function_ `float4 VertexFactoryGetRasterizedWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float4 TranslatedWorldPosition)`
- L1137-1145 _function_ `float3 VertexFactoryGetPositionForVertexLighting(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 TranslatedWorldPosition)`
- L1147-1233 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryGetInterpolantsVSToPS(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)`
- L1241-1248 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryGetRayTracingInterpolants(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)` _[#if RAYHITGROUPSHADER]_
- L1250-1257 _function_ `float2 VertexFactoryGetRayTracingTextureCoordinate(FVertexFactoryRayTracingInterpolants Interpolants)` _[#if RAYHITGROUPSHADER]_
- L1259-1328 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryInterpolate(FVertexFactoryRayTracingInterpolants a, float aInterp, FVertexFactoryRayTracingInterpolants b, float bInterp)` _[#if RAYHITGROUPSHADER]_
- L1330-1333 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryAssignInterpolants(FVertexFactoryRayTracingInterpolants Input)` _[#if RAYHITGROUPSHADER]_
- L1336-1339 _function_ `float4 VertexFactoryGetPreviousWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L1342-1346 _function_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — local position relative to primitive
- L1354-1357 _function_ `float3x3 VertexFactoryGetTangentToLocal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — Get the 3x3 tangent basis vectors for this vertex factory @param Input - vertex input stream structure @return 3x3 matrix
- L1359-1366 _function_ `float4 VertexFactoryGetTranslatedPrimitiveVolumeBounds(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L1368-1371 _function_ `uint VertexFactoryGetPrimitiveId(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L1374-1381 _function_ `FVertexFactoryInput NiagaraVertexFactoryExport_InitVertexFactoryInput(uint TriangleIndex, int VertexIndex, uint PrimitiveId, uint DrawInstanceId)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1383-1388 _function_ `uint NiagaraVertexFactoryExport_GetIndirectVertexCount()` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1390-1393 _function_ `FLWCVector3 NiagaraVertexFactoryExport_GetPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1395-1398 _function_ `float4 NiagaraVertexFactoryExport_GetColor(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1400-1403 _function_ `float3x3 NiagaraVertexFactoryExport_GetTangentBasis(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1405-1408 _function_ `float2 NiagaraVertexFactoryExport_GetTexCoord(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, uint CoordIndex)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_
- L1410-1441 _function_ `float4 NiagaraVertexFactoryExport_GetDynamicParameter(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, uint ParameterIndex)` _[#if WITH_NIAGARA_VERTEX_FACTORY_EXPORT]_

#### Prototypes (2)

- L424 _prototype_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L425 _prototype_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`

#### Top-level macro invocations (1)

- L47-48 _macro_call_ `VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FVertexFactoryInput`)

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `EVertexFactoryFlags::UsedWithMaterials
	\| EVertexFactoryFlags::SupportsDynamicLighting
	\| EVertexFactoryFlags::SupportsRayTracing
	\| EVertexFactoryFlags::SupportsRayTracingDynamicGeometry
	\| EVertexFactoryFlags::SupportsPSOPrecaching` → entry not found in file (macro-generated or #include'd); C++ `FNiagaraSpriteVertexFactory`  via IMPLEMENT_VERTEX_FACTORY_TYPE (Plugins/FX/Niagara/Source/NiagaraVertexFactories/Private/NiagaraSpriteVertexFactory.cpp:176)

### `Plugins/FX/Niagara/Shaders/Private/NiagaraTransformUtils.ush` (Private)

- lines: 89; parse: all-branches
- includes: L5 `/Plugin/FX/Niagara/Private/NiagaraCommon.ush`, L6 `/Plugin/FX/Niagara/Private/NiagaraQuaternionUtils.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L8-13 _struct_ **`FNiagaraTransform`** `struct FNiagaraTransform`
  - L10 _member_ `float3 Translation;`
  - L11 _member_ `float4 Rotation;`
  - L12 _member_ `float3 Scale;`

#### Functions (7)

- L15-22 _function_ `FNiagaraTransform LoadTransform(ByteAddressBuffer RawBufferData, uint Offset)`
- L24-31 _function_ `FNiagaraTransform MakeTransform(float3 Translation, float4 Rotation, float3 Scale)`
- L33-40 _function_ `FNiagaraTransform MultiplyTransform(in FNiagaraTransform A, in FNiagaraTransform B)`
- L42-52 _function_ `float4x4 TransformToMatrix44(FNiagaraTransform T)`
- L54-58 _function_ `float3x3 TransformToMatrix33(FNiagaraTransform T)`
- L60-81 _function_ `FNiagaraTransform DecomposeMatrix(float4x4 InMatrix)`
- L84-89 _function_ `FNiagaraTransform DecomposePackedMatrix(float3x4 InPackedMatrix)` — PackedMatrix here is a linear matrix packed for serialization.  Effectively a float4x3 transposed into vec4s

### `Plugins/FX/Niagara/Shaders/Private/NiagaraUpdateMeshGPUSceneInstances.usf` (Private)

- lines: 209; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ComputeShaderUtils.ush`, L5 `/Engine/Private/GPUScene/GPUSceneWriter.ush`, L6 `NiagaraMeshParticleUtils.ush`

#### Entry points (1)

- L80-209 _entry_ `[numthreads(THREAD_GROUP_SIZE, 1, 1)] void UpdateMeshInstancesCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNiagaraUpdateMeshGPUSceneInstancesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraGPUSceneUtils.cpp:36)

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `Buffer<uint> SortedIndices;`
- L50 _resource_ `Buffer<uint> GPUParticleCountBuffer;`

#### Global parameters (uniforms) (43)

- L9 _parameter_ `int SortedIndicesOffset;`
- L11 _parameter_ `float3 SystemLWCTile;`
- L12 _parameter_ `int bLocalSpace;`
- L13 _parameter_ `float DeltaSeconds;`
- L14 _parameter_ `uint FacingMode;`
- L16 _parameter_ `int ScaleDataOffset;`
- L17 _parameter_ `int RotationDataOffset;`
- L18 _parameter_ `int PositionDataOffset;`
- L19 _parameter_ `int VelocityDataOffset;`
- L20 _parameter_ `int CameraOffsetDataOffset;`
- L21 _parameter_ `int PrevScaleDataOffset;`
- L22 _parameter_ `int PrevRotationDataOffset;`
- L23 _parameter_ `int PrevPositionDataOffset;`
- L24 _parameter_ `int PrevVelocityDataOffset;`
- L25 _parameter_ `int PrevCameraOffsetDataOffset;`
- L27 _parameter_ `float3 DefaultScale;`
- L28 _parameter_ `float4 DefaultRotation;`
- L29 _parameter_ `float3 DefaultPosition;`
- L30 _parameter_ `float3 DefaultVelocity;`
- L31 _parameter_ `float DefaultCameraOffset;`
- L32 _parameter_ `float3 DefaultPrevScale;`
- L33 _parameter_ `float4 DefaultPrevRotation;`
- L34 _parameter_ `float3 DefaultPrevPosition;`
- L35 _parameter_ `float3 DefaultPrevVelocity;`
- L36 _parameter_ `float DefaultPrevCameraOffset;`
- L38 _parameter_ `float3 MeshScale;`
- L39 _parameter_ `float4 MeshRotation;`
- L40 _parameter_ `int bMeshOffsetIsWorldSpace;`
- L41 _parameter_ `float3 MeshOffset;`
- L43 _parameter_ `uint bLockedAxisEnable;`
- L44 _parameter_ `float3 LockedAxis;`
- L45 _parameter_ `uint LockedAxisSpace;`
- L47 _parameter_ `uint PrimitiveId;`
- L49 _parameter_ `uint ParticleCount;`
- L51 _parameter_ `uint GPUParticleCountOffset;`
- L53 _parameter_ `int MeshIndex;`
- L54 _parameter_ `int MeshIndexDataOffset;`
- L55 _parameter_ `int RendererVisibility;`
- L56 _parameter_ `int VisibilityTagDataOffset;`
- L58 _parameter_ `float3 LocalBoundingCenter;`
- L59 _parameter_ `float2 DistanceCullRangeSquared;`
- L60 _parameter_ `float4 LODScreenSize;`
- L62 _parameter_ `int bNeedsPrevTransform;`

#### Functions (2)

- L64-72 _function_ `uint GetPayloadDataFlags()`
- L74-78 _function_ `void CullInstance(uint InstanceId)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraVFCommon.usf` (Private)

- lines: 5; parse: all-branches
- includes: L4 `NiagaraVFParticleAccess.usf`
- L2 #pragma `once`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraVFParticleAccess.usf` (Private)

- lines: 25; parse: all-branches
- includes: L14 `/Plugin/FX/Niagara/Private/NiagaraParticleAccess.ush`

#### Macros (#define, 4)

- L9 `#define NiagaraGetFloatBuffer() (NiagaraVFLooseParameters.NiagaraParticleDataFloat)`
- L10 `#define NiagaraGetHalfBuffer() (NiagaraVFLooseParameters.NiagaraParticleDataHalf)`
- L12 `#define USE_GLOBAL_NIAGARA_DATA_BUFFERS 0`
- L13 `#define ENABLE_NIAGARA_INT_DATA_ACCESS 0`

#### Functions (9)

- L11 _function_ `uint NiagaraGetFloatDataStride()`
- L17 _function_ `float GetFloat(int RegisterIdx, uint InstanceID)` — Define some shorter name functions for legacy use in existing VFs
- L18 _function_ `float2 GetVec2(int RegisterIdx, uint InstanceID)`
- L19 _function_ `float3 GetVec3(int RegisterIdx, uint InstanceID)`
- L20 _function_ `float4 GetVec4(int RegisterIdx, uint InstanceID)`
- L21 _function_ `float SafeGetFloat(int RegisterIdx, uint InstanceID, float Default)`
- L22 _function_ `float2 SafeGetVec2(int RegisterIdx, uint InstanceID, float2 Default)`
- L23 _function_ `float3 SafeGetVec3(int RegisterIdx, uint InstanceID, float3 Default)`
- L24 _function_ `float4 SafeGetVec4(int RegisterIdx, uint InstanceID, float4 Default)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraVertexFactoryExport.usf` (Private)

- lines: 160; parse: all-branches
- includes: L5 `/Engine/Private/Common.ush`, L6 `/Engine/Private/ComputeShaderUtils.ush`, L7 `/Engine/Generated/Material.ush`, L8 `/Engine/Generated/VertexFactory.ush`

#### Macros (#define, 1)

- L11 `#define THREAD_GROUP_SIZE 64` _[#if !defined(THREAD_GROUP_SIZE)]_

#### Entry points (1)

- L75-159 _entry_ `[numthreads(THREAD_GROUP_SIZE, 1, 1)] void VertexFactoryExportCS(uint3 GroupId : SV_GroupID, int GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNiagaraVertexFactoryExportCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/FX/Niagara/Source/NiagaraVertexFactories/Private/NiagaraVertexFactoryExport.cpp:63)

#### Global resources (textures / buffers / samplers) (1)

- L29 _resource_ `RWByteAddressBuffer RWVertexData;`

#### Global parameters (uniforms) (14)

- L14 _parameter_ `uint IsIndirectDraw;`
- L15 _parameter_ `uint NumInstances;`
- L16 _parameter_ `uint NumVerticesPerInstance;`
- L17 _parameter_ `uint bApplyWPO;`
- L18 _parameter_ `uint bWorldSpace;`
- L19 _parameter_ `uint SectionInfoOutputOffset;`
- L21 _parameter_ `uint VertexStride;`
- L22 _parameter_ `uint VertexPositionOffset;`
- L23 _parameter_ `uint VertexColorOffset;`
- L24 _parameter_ `uint VertexTangentBasisOffset;`
- L25 _parameter_ `uint VertexTexCoordOffset;`
- L26 _parameter_ `uint VertexTexCoordNum;`
- L27 _parameter_ `uint4 VertexTexCoordBindings[(8 * 2) / 4];` — NUM_TEXCOORDS * Channels
- L28 _parameter_ `uint VertexOutputOffset;`

#### static const (1)

- L31 _static_const_ `static const uint INVALID_COMPONENT = 0xffffffff;`

#### Functions (4)

- L33-41 _function_ `void OutputPosition(uint VertexIndex, float3 Value)`
- L43-51 _function_ `void OutputColor(uint VertexIndex, float4 Value)`
- L53-63 _function_ `void OutputTangentBasis(uint VertexIndex, float3x3 Value)`
- L65-73 _function_ `void OutputTexCoord(uint VertexIndex, uint TexCoord, float2 Value)`

### `Plugins/FX/Niagara/Shaders/Private/NiagaraVisualizeTexture.usf` (Private)

- lines: 215; parse: all-branches
- includes: L7 `/Engine/Private/Common.ush`

#### Entry points (1)

- L98-214 _entry_ `void Main( FScreenVertexOutput Input, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FNiagaraVisualizeTexturePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraDebugShaders.cpp:92)

#### Global resources (textures / buffers / samplers) (11)

- L10 _resource_ `Texture2D<int4> Texture2DObject;` _[#if TEXTURE_INTEGER]_
- L11 _resource_ `Texture2DArray<int4> Texture2DArrayObject;` _[#if TEXTURE_INTEGER]_
- L12 _resource_ `Texture3D<int4> Texture3DObject;` _[#if TEXTURE_INTEGER]_
- L13 _resource_ `TextureCube<int4> TextureCubeObject;` _[#if TEXTURE_INTEGER]_
- L15 _resource_ `Texture2D<float4> Texture2DObject;` _[#if !(TEXTURE_INTEGER)]_
- L16 _resource_ `Texture2DArray<float4> Texture2DArrayObject;` _[#if !(TEXTURE_INTEGER)]_
- L17 _resource_ `Texture3D<float4> Texture3DObject;` _[#if !(TEXTURE_INTEGER)]_
- L18 _resource_ `TextureCube<float4> TextureCubeObject;` _[#if !(TEXTURE_INTEGER)]_
- L20 _resource_ `SamplerState TextureSampler;`
- L25 _resource_ `uint3 TextureDimensions;` — Dimensions of the texture
- L30 _resource_ `uint TextureSlice;`

#### Global parameters (uniforms) (7)

- L22 _parameter_ `int4 NumTextureAttributes;` — Number of attributes the texture holds in each dimension
- L23 _parameter_ `int NumAttributesToVisualize;` — Number of valid attributes to visualize, up to 4
- L24 _parameter_ `int4 AttributesToVisualize;` — Indicies of each attribute to visualize
- L26 _parameter_ `float4 PerChannelScale;`
- L27 _parameter_ `float4 PerChannelBias;`
- L28 _parameter_ `uint DebugFlags;`
- L29 _parameter_ `uint TickCounter;`

#### Functions (5)

- L32-44 _function_ `float4 ContainsNaNInf(float4 Color)`
- L46-56 _function_ `float2 GetAttributeUV(float2 UV, int AttributeIndex)`
- L58-66 _function_ `float ReadAttribute2D(float2 UV, int AttributeIndex)`
- L68-84 _function_ `float3 GetAttributeUVW(float2 UV, int AttributeIndex)`
- L86-94 _function_ `float ReadAttribute3D(float2 UV, int AttributeIndex)`
