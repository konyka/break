# Shaders / Shaders/Private/OIT

- files: 1; lines: 481
- record kinds: cpp_binding=4, define=7, entry=4, function=8, groupshared=4, include=3, member=11, parameter=32, resource=13, struct=2

### `Shaders/Private/OIT/OITSorting.usf` (Private)

- lines: 481; parse: all-branches
- includes: L8 `../Common.ush`, L30 `../ShaderPrint.ush` [PERMUTATION_DEBUG \|\| SHADER_DEBUG], L31 `../ColorMap.ush` [PERMUTATION_DEBUG \|\| SHADER_DEBUG]

#### Macros (#define, 7)

- L12 `#define PRIMITIVE_TRILIST 0`
- L13 `#define PRIMITIVE_TRISTRIP 1`
- L14 `#define ENCODING_TYPE 1`
- L20 `#define BACK_TO_FRONT 0`
- L21 `#define FRONT_TO_BACK 1`
- L24 `#define FPackedSliceAndOffset uint` _[#if ENCODING_TYPE == 1]_
- L26 `#define FPackedSliceAndOffset uint2` _[#if !(ENCODING_TYPE == 1)]_
- L3 #pragma `once`; L6 #pragma `message("UESHADERMETADATA_VERSION 78C3EBBB-59EA-459D-A2D4-67170905D7FC")`

#### Entry points (4)

- L188-280 _entry_ `[numthreads(SORTING_SLICE_COUNT, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID, uint GroupThreadId : SV_GroupIndex)` — stage: **compute** — C++: `FOITSortTriangleIndex_ScanCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:529) — C++: `FOITSortTriangleIndex_AllocateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:555) — C++: `FOITSortTriangleIndex_WriteOutCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:590) — C++: `FOITSortTriangleIndex_Debug` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:631) _[#if SHADER_SCAN]_
- L292-322 _entry_ `[numthreads(SORTING_SLICE_COUNT, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FOITSortTriangleIndex_ScanCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:529) — C++: `FOITSortTriangleIndex_AllocateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:555) — C++: `FOITSortTriangleIndex_WriteOutCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:590) — C++: `FOITSortTriangleIndex_Debug` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:631) _[#if SHADER_ALLOCATE]_
- L342-372 _entry_ `[numthreads(256, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FOITSortTriangleIndex_ScanCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:529) — C++: `FOITSortTriangleIndex_AllocateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:555) — C++: `FOITSortTriangleIndex_WriteOutCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:590) — C++: `FOITSortTriangleIndex_Debug` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:631) _[#if SHADER_WRITE]_
- L413-480 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FOITSortTriangleIndex_ScanCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:529) — C++: `FOITSortTriangleIndex_AllocateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:555) — C++: `FOITSortTriangleIndex_WriteOutCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:590) — C++: `FOITSortTriangleIndex_Debug` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/OIT/OIT.cpp:631) _[#if SHADER_DEBUG]_

#### Structs / classes (2)

- L36-41 _struct_ **`FTriIndex`** `struct FTriIndex`
  - L38 _member_ `uint I0;`
  - L39 _member_ `uint I1;`
  - L40 _member_ `uint I2;`
- L94-105 _struct_ **`FOITDebugData`** `struct FOITDebugData`
  - L96 _member_ `uint Index;`
  - L97 _member_ `uint PrimitiveCount;`
  - L98 _member_ `uint Type;`
  - L99 _member_ `uint SizeInBytes;`
  - L101 _member_ `uint FirstIndex;`
  - L102 _member_ `uint BaseVertexIndex;`
  - L103 _member_ `uint MinVertexIndex;`
  - L104 _member_ `uint MaxVertexIndex;`

#### Global resources (textures / buffers / samplers) (13)

- L176 _resource_ `Buffer<float> PositionBuffer;` _[#if SHADER_SCAN]_
- L177 _resource_ `Buffer<uint> IndexBuffer;` _[#if SHADER_SCAN]_
- L179 _resource_ `RWBuffer<uint> OutIndexBuffer;` _[#if SHADER_SCAN]_
- L180 _resource_ `RWBuffer<uint> OutSliceCounterBuffer;` _[#if SHADER_SCAN]_
- L181 _resource_ `RWBuffer<FPackedSliceAndOffset> OutPrimitiveSliceBuffer;` _[#if SHADER_SCAN]_
- L183 _resource_ `RWBuffer<uint> OutDebugData;` _[#if SHADER_SCAN]_
- L286 _resource_ `Buffer<uint> SliceCounterBuffer;` _[#if SHADER_ALLOCATE]_
- L287 _resource_ `RWBuffer<uint> SliceOffsetsBuffer;` _[#if SHADER_ALLOCATE]_
- L336 _resource_ `Buffer<uint> SliceOffsetsBuffer;` _[#if SHADER_WRITE]_
- L337 _resource_ `Buffer<FPackedSliceAndOffset> PrimitiveSliceBuffer;` _[#if SHADER_WRITE]_
- L339 _resource_ `Buffer<uint> IndexBuffer;` _[#if SHADER_WRITE]_
- L340 _resource_ `RWBuffer<uint> OutIndexBuffer;` _[#if SHADER_WRITE]_
- L392 _resource_ `Buffer<uint> DebugData;` _[#if SHADER_DEBUG]_

#### Global parameters (uniforms) (32)

- L153 _parameter_ `float4x4 ViewToWorld;` _[#if SHADER_SCAN && PERMUTATION_DEBUG]_
- L154 _parameter_ `float3 WorldBound_Min;` _[#if SHADER_SCAN && PERMUTATION_DEBUG]_
- L155 _parameter_ `float3 WorldBound_Max;` _[#if SHADER_SCAN && PERMUTATION_DEBUG]_
- L156 _parameter_ `float3 ViewBound_Min;` _[#if SHADER_SCAN && PERMUTATION_DEBUG]_
- L157 _parameter_ `float3 ViewBound_Max;` _[#if SHADER_SCAN && PERMUTATION_DEBUG]_
- L160 _parameter_ `float4x4 LocalToWorld;` — GPU scene buffer instead? How? _[#if SHADER_SCAN]_
- L161 _parameter_ `float4x4 LocalToView;` _[#if SHADER_SCAN]_
- L163 _parameter_ `uint SourcePrimitiveType;` _[#if SHADER_SCAN]_
- L164 _parameter_ `uint NumPrimitives;` _[#if SHADER_SCAN]_
- L165 _parameter_ `uint NumIndices;` _[#if SHADER_SCAN]_
- L166 _parameter_ `uint SourceFirstIndex;` _[#if SHADER_SCAN]_
- L167 _parameter_ `uint SourceBaseVertexIndex;` _[#if SHADER_SCAN]_
- L168 _parameter_ `uint SourceMinVertexIndex;` _[#if SHADER_SCAN]_
- L169 _parameter_ `uint SourceMaxVertexIndex;` _[#if SHADER_SCAN]_
- L170 _parameter_ `uint SortType;` _[#if SHADER_SCAN]_
- L171 _parameter_ `uint SortedIndexBufferSizeInByte;` _[#if SHADER_SCAN]_
- L173 _parameter_ `float ViewBoundMaxZ;` _[#if SHADER_SCAN]_
- L174 _parameter_ `float ViewBoundMinZ;` _[#if SHADER_SCAN]_
- L329 _parameter_ `uint SourcePrimitiveType;` _[#if SHADER_WRITE]_
- L330 _parameter_ `uint NumPrimitives;` _[#if SHADER_WRITE]_
- L331 _parameter_ `uint NumIndices;` _[#if SHADER_WRITE]_
- L332 _parameter_ `uint SrcFirstIndex;` _[#if SHADER_WRITE]_
- L333 _parameter_ `uint DstFirstIndex;` _[#if SHADER_WRITE]_
- L334 _parameter_ `uint SortType;` _[#if SHADER_WRITE]_
- L380 _parameter_ `uint VisibleInstances;` _[#if SHADER_DEBUG]_
- L381 _parameter_ `uint VisiblePrimitives;` _[#if SHADER_DEBUG]_
- L382 _parameter_ `uint VisibleIndexSizeInBytes;` _[#if SHADER_DEBUG]_
- L384 _parameter_ `uint AllocatedBuffers;` _[#if SHADER_DEBUG]_
- L385 _parameter_ `uint AllocatedIndexSizeInBytes;` _[#if SHADER_DEBUG]_
- L387 _parameter_ `uint UnusedBuffers;` _[#if SHADER_DEBUG]_
- L388 _parameter_ `uint UnusedIndexSizeInBytes;` _[#if SHADER_DEBUG]_
- L390 _parameter_ `uint TotalEntries;` _[#if SHADER_DEBUG]_

#### groupshared (4)

- L185 _groupshared_ `groupshared uint s_SliceIndices[SORTING_SLICE_COUNT];` _[#if SHADER_SCAN]_
- L186 _groupshared_ `groupshared uint s_SliceOffsets[SORTING_SLICE_COUNT];` _[#if SHADER_SCAN]_
- L289 _groupshared_ `groupshared uint s_Counters[SORTING_SLICE_COUNT];` _[#if SHADER_ALLOCATE]_
- L290 _groupshared_ `groupshared uint s_Offsets[SORTING_SLICE_COUNT];` _[#if SHADER_ALLOCATE]_

#### Functions (8)

- L43-60 _function_ `FTriIndex GetTriangleIndices(uint InPrimitiveId, uint InFirstIndex, uint InPrimitiveType)`
- L62-65 _function_ `bool IsValid(FTriIndex InTri, uint InNumIndices)`
- L71-78 _function_ `FPackedSliceAndOffset PackSliceAndOffset(uint InSliceIndex, uint InLocalOffset)`
- L80-89 _function_ `void UnpackSliceAndOffset(FPackedSliceAndOffset In, inout uint OutSliceIndex, inout uint OutLocalOffset)`
- L107-121 _function_ `void AddDebugInfo(RWBuffer<uint> InDebugData, FOITDebugData In)`
- L123-126 _function_ `uint GetDebugInfoCount(Buffer<uint> InDebugData)`
- L128-146 _function_ `FOITDebugData GetDebugInfo(Buffer<uint> InDebugData, uint Index)`
- L394-411 _function_ `void PrintSize(inout FShaderPrintContext Context, uint SizeInBytes, FFontColor Color)` _[#if SHADER_DEBUG]_
