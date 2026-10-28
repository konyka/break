# Shaders / Plugins/Experimental/MeshPartition/Shaders

- files: 2; lines: 196
- record kinds: cpp_binding=5, entry=5, include=2, parameter=5, resource=12

### `Plugins/Experimental/MeshPartition/Shaders/MeshPartitionBorderFill.usf` (Other)

- lines: 130; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (3)

- L11-65 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint2 DTid : SV_DispatchThreadID)` — stage: **compute** — C++: `FMeshPartition_BorderFillCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/MeshPartition/Source/MeshPartitionCompute/Private/MeshPartitionChannelRasterizationShaders.cpp:8)
- L75-112 _entry_ `[numthreads(8, 8, 1)] void PullCS(uint2 DTid : SV_DispatchThreadID)` — stage: **compute** — C++: `FMeshPartition_FillPullCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/MeshPartition/Source/MeshPartitionCompute/Private/MeshPartitionChannelRasterizationShaders.cpp:9)
- L114-128 _entry_ `[numthreads(8, 8, 1)] void PushCS(uint2 DTid : SV_DispatchThreadID)` — stage: **compute** — C++: `FMeshPartition_FillPushCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/MeshPartition/Source/MeshPartitionCompute/Private/MeshPartitionChannelRasterizationShaders.cpp:10)

#### Global resources (textures / buffers / samplers) (7)

- L7 _resource_ `Texture2D<float> Mask;`
- L9 _resource_ `RWTexture2D<float4> RWSectionTexture;`
- L69 _resource_ `Texture2D<float4> SectionMipIn;`
- L70 _resource_ `RWTexture2D<float4> SectionMipOut;`
- L71 _resource_ `Texture2D<float> MaskMipIn;`
- L72 _resource_ `RWTexture2D<float> MaskMipOut;`
- L73 _resource_ `SamplerState MipSampler;`

#### Global parameters (uniforms) (3)

- L5 _parameter_ `uint2 Resolution;`
- L67 _parameter_ `float2 TexelSize;`
- L68 _parameter_ `int4 ResolutionPass;`

### `Plugins/Experimental/MeshPartition/Shaders/MeshPartitionMakeSectionChannels.usf` (Other)

- lines: 66; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (2)

- L19-51 _entry_ `void DrawUVDomainVS( uint VertexIndex : SV_VertexID, out float2 SourceUV : TEXCOORD0, out float4 OutWeight : TEXCOORD1, out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FMeshPartition_DrawUVDomainVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/MeshPartition/Source/MeshPartitionCompute/Private/MeshPartitionChannelRasterizationShaders.cpp:5)
- L56-65 _entry_ `void DrawUVDomainPS( float2 SourceUV : TEXCOORD0, float4 Weights : TEXCOORD1, float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0, out float OutMask : SV_Target1)` — stage: **pixel (from C++ binding)** — C++: `FMeshPartition_DrawUVDomainPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/MeshPartition/Source/MeshPartitionCompute/Private/MeshPartitionChannelRasterizationShaders.cpp:6)

#### Global resources (textures / buffers / samplers) (5)

- L7 _resource_ `Buffer<int> InMeshIndices;`
- L8 _resource_ `Buffer<float2> InMeshUVs;`
- L9 _resource_ `Buffer<float> InMeshChannels;`
- L10 _resource_ `Buffer<int> InMeshOutlines;`
- L11 _resource_ `Buffer<int> InUVElementToVertexID;`

#### Global parameters (uniforms) (2)

- L13 _parameter_ `uint4 InDrawCall;` — NumVertices, NumChannelAttribs, FirstVertIndex
- L14 _parameter_ `uint InChannelOffset;` — Offset to the first channel element in the Channel buffer
