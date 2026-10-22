# Shaders / Shaders/Private/Skinning

- files: 8; lines: 1215
- record kinds: cpp_binding=7, define=7, entry=7, function=43, groupshared=1, include=40, member=16, parameter=18, resource=12, struct=5

### `Shaders/Private/Skinning/AnimBankEval.usf` (Private)

- lines: 152; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`, L5 `/Engine/Private/SceneData.ush`, L6 `/Engine/Private/BoneTransform.ush`, L7 `/Engine/Private/Visualization.ush`, L8 `/Engine/Private/Skinning/SkinningDataDecode.ush`, L9 `/Engine/Shared/SkinningDefinitions.h`

#### Entry points (1)

- L74-152 _entry_ `[numthreads(BONES_PER_GROUP, 1, 1)] void BankEvaluateCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FAnimBankEvaluateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Skinning/AnimBankTransformProvider.cpp:89)

#### Structs / classes (1)

- L19-24 _struct_ **`FKeyIndices`** `struct FKeyIndices`
  - L21 _member_ `int KeyIndex1;`
  - L22 _member_ `int KeyIndex2;`
  - L23 _member_ `float Alpha;`

#### Global resources (textures / buffers / samplers) (3)

- L11 _resource_ `ByteAddressBuffer SequenceTransformBuffer;`
- L12 _resource_ `ByteAddressBuffer BankBlockBuffer;`
- L13 _resource_ `ByteAddressBuffer BoneMapBuffer;`

#### Global parameters (uniforms) (3)

- L14 _parameter_ `FCompressedBoneTransformRWBuffer TransformBuffer;`
- L16 _parameter_ `float SampleInterval;`
- L17 _parameter_ `uint bInterpolating;`

#### Functions (1)

- L26-72 _function_ `FKeyIndices GetKeyIndicesFromTime(float Time, int KeyCount, float SequenceLength, float FramesPerSecond)`

### `Shaders/Private/Skinning/AnimSequenceTransformProvider.usf` (Private)

- lines: 551; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`, L5 `/Engine/Private/SceneData.ush`, L6 `/Engine/Private/BoneTransform.ush`, L7 `/Engine/Private/Visualization.ush`, L8 `/Engine/Private/Skinning/SkinningDataDecode.ush`, L9 `/Engine/Shared/SkinningDefinitions.h`

#### Macros (#define, 6)

- L30 `#define RETARGET_MODE_ANIMATION 0`
- L31 `#define RETARGET_MODE_SKELETON 1`
- L32 `#define RETARGET_MODE_ANIMATION_SCALED 2`
- L33 `#define RETARGET_MODE_ANIMATION_RELATIVE 3`
- L34 `#define RETARGET_MODE_ORIENT_AND_SCALE 4`
- L36 `#define INVALID_BONE_INDEX 0xFFFF`
- L12 #pragma `warning(disable:7203)`

#### Entry points (1)

- L382-551 _entry_ `[numthreads(BONES_PER_GROUP, 1, 1)] void EvaluateConcatenateScatterCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FEvaluateConcatenateScatterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Skinning/AnimSequenceTransformProvider.cpp:241)

#### Structs / classes (1)

- L303-309 _struct_ **`FMeshSpaceBlendResult`** `struct FMeshSpaceBlendResult` _[#if HAS_MESH_SPACE_LAYERS]_
  - L305 _member_ `FQuat BlendedGlobal;` _[#if HAS_MESH_SPACE_LAYERS]_
  - L306 _member_ `uint ParentIndex;` _[#if HAS_MESH_SPACE_LAYERS]_
  - L307 _member_ `float3 Location;` _[#if HAS_MESH_SPACE_LAYERS]_
  - L308 _member_ `float Scale;` _[#if HAS_MESH_SPACE_LAYERS]_

#### Global resources (textures / buffers / samplers) (6)

- L14 _resource_ `ByteAddressBuffer RetargetingDataBuffer;`
- L15 _resource_ `ByteAddressBuffer BoneMapBuffer;`
- L16 _resource_ `StructuredBuffer<float4> SequenceTransformBuffer;`
- L17 _resource_ `StructuredBuffer<FEvaluateLayerHeader> LayerHeaderBuffer;`
- L18 _resource_ `StructuredBuffer<FSamplePoseData> SamplePoseBuffer;`
- L202 _resource_ `ByteAddressBuffer BoneMaskBuffer;`

#### Global parameters (uniforms) (8)

- L19 _parameter_ `FCompressedBoneTransformRWBuffer SkinningTransformBufferUAV;`
- L20 _parameter_ `uint NumTotalHeaders;`
- L21 _parameter_ `uint HeaderBaseOffset;`
- L22 _parameter_ `uint SlotsPerInstance;`
- L23 _parameter_ `uint NumCompactBones;`
- L24 _parameter_ `uint MeshSpaceMask;`
- L25 _parameter_ `uint LayerModeMask;`
- L26 _parameter_ `uint NumLayers;`

#### groupshared (1)

- L28 _groupshared_ `groupshared FBoneTransformWithUniformScale SharedTransform[BONES_PER_GROUP];`

#### Functions (19)

- L38-43 _function_ `FBoneRetargetingData LoadBoneRetargetingData(ByteAddressBuffer Buffer, uint BaseOffset, uint Index)`
- L45-71 _function_ `FBoneTransformWithUniformScale LoadBoneTransformWithUniformScale(StructuredBuffer<float4> Buffer, uint BaseIndex, uint Index)`
- L73-79 _function_ `void StoreBoneTransformWithUniformScale(RWByteAddressBuffer Buffer, uint BaseOffset, uint Index, FBoneTransformWithUniformScale Transform)`
- L81-158 _function_ `FBoneTransformWithUniformScale EvaluateAndRetargetBone( uint BoneIndex, uint SequenceTransformBufferOffset, uint RetargetingTransformBufferOffset, uint RetargetingDataBufferOffset, uint KeyIndex0, uint KeyIndex1, float Alpha, uint NumAnimBones)`
- L163-166 _function_ `float PackScaleWithParent(float Value, uint ParentIndex)` — SharedTransform .Scale field packing: Lower 16 bits = FFloat16 value (bone scale or mesh-space Q.w) Upper 16 bits = ParentIndex (for chain walk without BoneMapBuffer reads)
- L168-171 _function_ `float UnpackScale(float Packed)`
- L173-176 _function_ `uint UnpackParentIndex(float Packed)`
- L178-182 _function_ `void StoreSharedTransform(uint Index, FBoneTransformWithUniformScale Transform, uint ParentIndex)`
- L184-189 _function_ `FBoneTransformWithUniformScale LoadSharedTransform(uint Index)`
- L191-194 _function_ `uint GetSharedParentIndex(uint Index)`
- L196-200 _function_ `FBoneHierarchyData LoadBoneHierarchyData(ByteAddressBuffer Buffer, uint BaseOffset, uint Index)`
- L204-213 _function_ `float LoadBoneMaskWeight(FEvaluateLayerHeader Header, uint BoneIndex)`
- L215-257 _function_ `FBoneTransformWithUniformScale EvaluateWeightedSamples(uint BoneIndex, uint Offset, uint Count)`
- L259-275 _function_ `FBoneTransformWithUniformScale ConcatenateToGlobal( uint BoneIndex, uint SharedTransformOffset, uint InvGlobalRefPoseTransformBufferOffset)`
- L277-286 _function_ `void ScatterGlobalSpaceTransform(uint DstTransformBufferOffset1, uint DstTransformBufferOffset2, uint TransformIndex, FBoneTransformWithUniformScale GlobalTransform)`
- L290-294 _function_ `void StoreMeshSpaceLayerRotation(uint Index, FQuat Q, uint ParentIndex)` _[#if HAS_MESH_SPACE_LAYERS]_
- L296-301 _function_ `FQuat LoadMeshSpaceLayerRotation(uint Index)` _[#if HAS_MESH_SPACE_LAYERS]_
- L311-345 _function_ `FMeshSpaceBlendResult BlendMeshSpaceOverride( FBoneTransformWithUniformScale LayerPose, FBoneTransformWithUniformScale Result, uint BoneIndex, uint SharedOffset, float EffectiveWeight)` _[#if HAS_MESH_SPACE_LAYERS]_
- L347-378 _function_ `FMeshSpaceBlendResult BlendMeshSpaceAdditive( FBoneTransformWithUniformScale LayerPose, FBoneTransformWithUniformScale Result, uint BoneIndex, uint SharedOffset, float EffectiveWeight)` _[#if HAS_MESH_SPACE_LAYERS]_

### `Shaders/Private/Skinning/CopyPreviousTransforms.usf` (Private)

- lines: 76; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Shared/SkinningDefinitions.h`

#### Entry points (1)

- L32-75 _entry_ `[numthreads(COPY_THREAD_GROUP_SIZE, 1, 1)] void CopyPreviousTransformsCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FCopyPreviousTransformsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Skinning/SkinningSceneExtension.cpp:221)

#### Structs / classes (1)

- L14-20 _struct_ **`FCopyTransformsHeader`** `struct FCopyTransformsHeader`
  - L16 _member_ `uint SrcByteOffset;` — Byte offset in source buffer
  - L17 _member_ `uint DstByteOffset;` — Byte offset in destination buffer
  - L18 _member_ `uint Count;` — Number of compressed bone transforms to copy
  - L19 _member_ `uint _Pad0;`

#### Global resources (textures / buffers / samplers) (1)

- L23 _resource_ `StructuredBuffer<FCopyTransformsHeader> CopyHeaders;`

#### Global parameters (uniforms) (2)

- L22 _parameter_ `FCompressedBoneTransformRWBuffer DstTransformBuffer;`
- L26 _parameter_ `FCompressedBoneTransformBuffer SrcTransformBuffer;` _[#if USE_STAGING_BUFFER]_

### `Shaders/Private/Skinning/ResolveAttachments.usf` (Private)

- lines: 98; parse: all-branches
- includes: L4 `/Engine/Private/Common.ush`, L5 `/Engine/Private/GPUScene/GPUSceneWriter.ush`, L6 `/Engine/Private/BoneTransform.ush`, L7 `/Engine/Private/GpuSkinCommon.ush`, L8 `/Engine/Private/Skinning/SkinningDataDecode.ush`, L9 `/Engine/Shared/SkinningDefinitions.h`

#### Entry points (1)

- L64-97 _entry_ `[numthreads(64, 1, 1)] void ResolveAttachmentsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FResolveAttachmentsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Skinning/SkinningSceneExtension.cpp:2250)

#### Global resources (textures / buffers / samplers) (1)

- L11 _resource_ `StructuredBuffer<FResolveAttachmentBlockHeader> AttachmentBlockHeaderBuffer;`

#### Global parameters (uniforms) (2)

- L12 _parameter_ `FCompressedBoneTransformBuffer SkinningTransformBuffer;`
- L13 _parameter_ `uint NumAttachments;`

#### Functions (3)

- L15-23 _function_ `float4x4 LoadRefPoseMatrix(FResolveAttachmentBlockHeader Header)`
- L25-36 _function_ `float4x4 LoadLocalOffsetMatrix(FResolveAttachmentBlockHeader Header)`
- L40-62 _function_ `float4x4 ComposeBoneAttachmentTransform( uint BoneBase, float4x4 RefPoseMatrix, float4x4 LocalOffsetMatrix, float4x4 ParentLocalToWorld, float3 PositionHigh, uint BoneIndex)` — Resolve a bone from the skinning buffer, undo InvRefPose, compose with local offset and parent world transform. If BoneIndex is 0xFFFF (bone not in skinning buffer), uses ref pose directly (no animation).

### `Shaders/Private/Skinning/SkinnedMeshDebug.usf` (Private)

- lines: 121; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`, L5 `/Engine/Private/SceneData.ush`, L6 `/Engine/Private/BoneTransform.ush`, L7 `/Engine/Private/Visualization.ush`, L8 `/Engine/Private/Skinning/SkinningSceneDataDecode.ush`

#### Entry points (2)

- L61-112 _entry_ `void LineVS( in uint InstanceID : SV_InstanceID, in uint VertexID : SV_VertexID, out float4 OutPosition : SV_POSITION, out float4 OutColor : TEXCOORD0 )` — stage: **vertex (from C++ binding)** — C++: `FSkinnedMeshDrawLineVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Skinning/SkinnedMeshDebugView.cpp:82)
- L114-121 _entry_ `void LinePS( in float4 Position : SV_POSITION, in float4 Color : TEXCOORD0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FSkinnedMeshDrawLinePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Skinning/SkinnedMeshDebugView.cpp:83)

#### Structs / classes (1)

- L30-34 _struct_ **`FPackedBone`** `struct FPackedBone`
  - L32 _member_ `uint BoneParent : 16;`
  - L33 _member_ `uint BoneDepth : 16;`

#### Global parameters (uniforms) (2)

- L10 _parameter_ `uint PersistentPrimitiveIndex;`
- L11 _parameter_ `uint bPreviousTransform;`

#### Functions (3)

- L13-28 _function_ `float3 GetBoneColor(uint BoneIndex, uint BoneDepth, uint BoneCount)`
- L36-49 _function_ `FPackedBone GetPackedBone(FSkinningHeader SkinningHeader, uint BoneIndex)`
- L51-59 _function_ `float4x4 MatrixFrom4x3(float4x3 M)`

### `Shaders/Private/Skinning/SkinningDataDecode.ush` (Private)

- lines: 110; parse: all-branches
- includes: L5 `../Common.ush`, L6 `/Engine/Shared/SkinningDefinitions.h`, L7 `/Engine/Shared/HLSLStaticAssert.h`
- L3 #pragma `once`

#### Functions (10)

- L11-19 _function_ `float4x3 UnpackCompressedBoneTransform(uint4 Data0, uint4 Data1)` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L21-29 _function_ `float4x3 LoadCompressedBoneTransform(FCompressedBoneTransformBuffer SrcBuffer, uint BaseOffset, uint BoneIndex)` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L31-38 _function_ `float3x4 UnpackCompressedBoneTransformTransposed(uint4 Data0, uint4 Data1)` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L40-48 _function_ `float3x4 LoadCompressedBoneTransformTransposed(FCompressedBoneTransformBuffer SrcBuffer, uint BaseOffset, uint BoneIndex)` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L50-58 _function_ `float4x3 LoadCompressedBoneTransform(FCompressedBoneTransformRWBuffer SrcBuffer, uint BaseOffset, uint BoneIndex)` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L60-73 _function_ `void StoreCompressedBoneTransform(FCompressedBoneTransformRWBuffer DstBuffer, uint BaseOffset, uint BoneIndex, float4x3 BoneTransform)` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L78-83 _function_ `float3x4 LoadCompressedBoneTransformTransposed(FCompressedBoneTransformBuffer SrcBuffer, uint BaseOffset, uint BoneIndex)` _[#if !(USE_COMPRESSED_BONE_TRANSFORM)]_
- L85-88 _function_ `float4x3 LoadCompressedBoneTransform(FCompressedBoneTransformBuffer SrcBuffer, uint BaseOffset, uint BoneIndex)` _[#if !(USE_COMPRESSED_BONE_TRANSFORM)]_
- L90-95 _function_ `float4x3 LoadCompressedBoneTransform(FCompressedBoneTransformRWBuffer SrcBuffer, uint BaseOffset, uint BoneIndex)` _[#if !(USE_COMPRESSED_BONE_TRANSFORM)]_
- L99-106 _function_ `void StoreCompressedBoneTransform(FCompressedBoneTransformRWBuffer DstBuffer, uint BaseOffset, uint BoneIndex, float4x3 BoneTransform)` _[#if !(USE_COMPRESSED_BONE_TRANSFORM) && COMPILER_SUPPORTS_HLSL2021]_

### `Shaders/Private/Skinning/SkinningSceneDataDecode.ush` (Private)

- lines: 67; parse: all-branches
- includes: L5 `SkinningDataDecode.ush`, L6 `../SceneData.ush`, L7 `../BitPacking.ush`, L8 `../BoneTransform.ush`

#### Macros (#define, 1)

- L12 `#define SKINNING_REF_POSE_TRANSFORM_OFFSET 0x80000000u`
- L3 #pragma `once`

#### Functions (7)

- L14-21 _function_ `float4x3 LoadSkinningBoneTransform(uint TransformIndex)`
- L23-30 _function_ `float3x4 LoadSkinningBoneTransformTransposed(uint TransformIndex)`
- L34-38 _function_ `FSkinningHeader LoadSkinningHeader(uint InPrimitiveIndex)` _[#if COMPILER_SUPPORTS_HLSL2021]_
- L40-44 _function_ `FBoneTransformWithScale LoadSkinningBoneObjectSpaceWithScale(uint BufferOffset, uint BoneIndex)` _[#if COMPILER_SUPPORTS_HLSL2021]_
- L46-50 _function_ `FBoneTransform LoadSkinningBoneObjectSpace(uint BufferOffset, uint BoneIndex)` _[#if COMPILER_SUPPORTS_HLSL2021]_
- L52-59 _function_ `uint GetSkinningBoneTransformOffset(FSkinningHeader SkinningHeader, uint InstanceIndex, bool bPrevious)` _[#if COMPILER_SUPPORTS_HLSL2021]_
- L61-65 _function_ `uint GetSkinningBoneTransformOffset(uint PrimitiveIndex, uint InstanceIndex, bool bPrevious)` _[#if COMPILER_SUPPORTS_HLSL2021]_

### `Shaders/Private/Skinning/TransformProviders.usf` (Private)

- lines: 40; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`, L5 `/Engine/Private/SceneData.ush`, L6 `/Engine/Private/BoneTransform.ush`, L7 `SkinningDataDecode.ush`

#### Entry points (1)

- L19-40 _entry_ `[numthreads(TRANSFORMS_PER_GROUP, 1, 1)] void RefPoseProviderCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FRefPoseTransformProviderCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Skinning/SkinningSceneExtension.cpp:178)

#### Structs / classes (1)

- L9-14 _struct_ **`FTransformBlockHeader`** `struct FTransformBlockHeader`
  - L11 _member_ `uint BlockLocalIndex;`
  - L12 _member_ `uint BlockTransformCount;`
  - L13 _member_ `uint BlockTransformOffset;`

#### Global resources (textures / buffers / samplers) (1)

- L17 _resource_ `StructuredBuffer<FTransformBlockHeader> HeaderBuffer;`

#### Global parameters (uniforms) (1)

- L16 _parameter_ `FCompressedBoneTransformRWBuffer TransformBuffer;`
