# Shaders / Plugins/FX/NiagaraNanite/Shaders

- files: 1; lines: 173
- record kinds: cpp_binding=1, define=7, entry=1, function=2, include=7, parameter=34, resource=4

### `Plugins/FX/NiagaraNanite/Shaders/NiagaraNaniteGPUScene.usf` (Other)

- lines: 173; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ComputeShaderUtils.ush`, L5 `/Engine/Private/GPUScene/GPUSceneWriter.ush`, L7 `/Plugin/FX/Niagara/Private/NiagaraCommon.ush`, L8 `/Plugin/FX/Niagara/Private/NiagaraQuaternionUtils.ush`, L9 `/Plugin/FX/Niagara/Private/NiagaraTransformUtils.ush`, L68 `/Plugin/FX/Niagara/Private/NiagaraParticleAccess.ush`

#### Macros (#define, 7)

- L61 `#define USE_GLOBAL_NIAGARA_DATA_BUFFERS 0`
- L62 `#define ENABLE_NIAGARA_INT_DATA_ACCESS 1`
- L63 `#define NiagaraGetFloatBuffer() ParticleFloatData`
- L64 `#define NiagaraGetHalfBuffer() ParticleHalfData`
- L65 `#define NiagaraGetIntBuffer() ParticleIntData`
- L66 `#define NiagaraGetFloatDataStride() ParticleBufferStride`
- L67 `#define NiagaraGetIntDataStride() ParticleBufferStride`

#### Entry points (1)

- L84-172 _entry_ `[numthreads(THREAD_GROUP_SIZE, 1, 1)] void UpdateMeshInstancesCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNiagaraNaniteGPUSceneCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/NiagaraNanite/Source/NiagaraNaniteShader/Private/NiagaraNaniteShaders.cpp:14)

#### Global resources (textures / buffers / samplers) (4)

- L16 _resource_ `Buffer<float> ParticleFloatData;`
- L17 _resource_ `Buffer<float> ParticleHalfData;`
- L18 _resource_ `Buffer<int> ParticleIntData;`
- L19 _resource_ `Buffer<uint> ParticleCountBuffer;`

#### Global parameters (uniforms) (34)

- L11 _parameter_ `uint NumAllocatedInstances;`
- L12 _parameter_ `uint ParticleCpuCount;`
- L13 _parameter_ `uint ParticleGpuCountOffset;`
- L15 _parameter_ `uint ParticleBufferStride;`
- L21 _parameter_ `uint NumCustomFloats;`
- L22 _parameter_ `uint NumCustomFloat4s;`
- L23 _parameter_ `uint4 CustomFloatComponents[MAX_CUSTOM_FLOAT4S];`
- L24 _parameter_ `float4 DefaultCustomFloats[MAX_CUSTOM_FLOAT4S];`
- L26 _parameter_ `uint PositionComponentOffset;`
- L27 _parameter_ `uint RotationComponentOffset;`
- L28 _parameter_ `uint ScaleComponentOffset;`
- L30 _parameter_ `uint PrevPositionComponentOffset;`
- L31 _parameter_ `uint PrevRotationComponentOffset;`
- L32 _parameter_ `uint PrevScaleComponentOffset;`
- L34 _parameter_ `float3 DefaultPosition;`
- L35 _parameter_ `float4 DefaultRotation;`
- L36 _parameter_ `float3 DefaultScale;`
- L38 _parameter_ `float3 DefaultPrevPosition;`
- L39 _parameter_ `float4 DefaultPrevRotation;`
- L40 _parameter_ `float3 DefaultPrevScale;`
- L42 _parameter_ `float3 MeshScale;`
- L43 _parameter_ `float4 MeshRotation;`
- L45 _parameter_ `int MeshIndex;`
- L46 _parameter_ `int RendererVis;`
- L47 _parameter_ `uint MeshIndexComponentOffset;`
- L48 _parameter_ `uint RendererVisComponentOffset;`
- L50 _parameter_ `float3 SimulationToComponent_Translation;`
- L51 _parameter_ `float4 SimulationToComponent_Rotation;`
- L52 _parameter_ `float3 SimulationToComponent_Scale;`
- L53 _parameter_ `float3 PreviousSimulationToComponent_Translation;`
- L54 _parameter_ `float4 PreviousSimulationToComponent_Rotation;`
- L55 _parameter_ `float3 PreviousSimulationToComponent_Scale;`
- L57 _parameter_ `float3 SimulationLWCTile;`
- L59 _parameter_ `uint PrimitiveId;`

#### Functions (2)

- L70-76 _function_ `uint GetPayloadDataFlags()`
- L78-82 _function_ `void CullInstance(uint InstanceId)`
