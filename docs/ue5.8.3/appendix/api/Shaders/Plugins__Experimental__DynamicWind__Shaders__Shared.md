# Shaders / Plugins/Experimental/DynamicWind/Shaders/Shared

- files: 1; lines: 100
- record kinds: define=2, function=12, member=16, namespace=1, struct=3, typedef=3

### `Plugins/Experimental/DynamicWind/Shaders/Shared/DynamicWindCommon.ush` (Shared)

- lines: 100; parse: all-branches

#### Macros (#define, 2)

- L5 `#define DYNAMIC_WIND_INVALID_BONE_INDEX 65535`
- L7 `#define DYNAMIC_WIND_DIRECTIONALITY_SLICES 8`
- L3 #pragma `once`

#### Structs / classes (3)

- L14-27 _struct_ **`UE::HLSL::FDynamicWindSkeletonData`** `struct FDynamicWindSkeletonData`
  - L17 _member_ `uint BoneDataOffset;` — The index of the first element of the FDynamicWindBoneData for this skeleton
  - L20 _member_ `float SkeletonHeight;` — The height (in units) of the skeleton
  - L23 _member_ `float GustAttenuation;` — How much to attenuate trunk bones in the skeleton (0-1)
  - L26 _member_ `uint PackedSimGroupAndGroundCover;` — Packed: MaxSimulationGroupIndex (bits 0-30), bIsGroundCover (bit 31)
- L29-51 _struct_ **`UE::HLSL::FDynamicWindBoneData`** `struct FDynamicWindBoneData`
  - L32 _member_ `uint ParentBoneIndex;` — The index of this bone's parent bone, in the skeleton
  - L35 _member_ `float Influence;` — The wind influence of this bone
  - L38 _member_ `int SimulationGroupIndex;` — The simulation group for this bone
  - L41 _member_ `float BoneChainLength;` — The length of bone chain that this bone is a member of
  - L44 _member_ `float4 BindPoseRotation;` — Initial local-space orientation of the bone
  - L47 _member_ `float3 BindPosePosition;` — Initial local-space position of the bone
  - L50 _member_ `uint bIsTrunkBone;` — Whether this bone is to be considered part of a tree trunk
- L53-69 _struct_ **`UE::HLSL::FDynamicWindBlockHeader`** `struct FDynamicWindBlockHeader`
  - L56 _member_ `uint SkeletonDataIndex;` — Index of the related FDynamicWindSkeletonData for the block
  - L59 _member_ `uint BlockDstTransformOffset;` — Byte offset of the transforms to be written in the transform buffer
  - L62 _member_ `uint PackedNumBonesAndOffset;` — Packed: BlockNumBones (bits 0-7), BlockBoneOffset (bits 8-31)
  - L65 _member_ `uint PackedDirectionalityAndTransformCount;` — Packed: BlockDirectionalityIndex (bits 0-7), TotalTransformCount (bits 8-31)
  - L68 _member_ `uint BoneMapBufferOffset;` — Byte offset of the bone map in the bone map buffer, or ~0u if not present

#### Namespaces (1)

- L10-72 _namespace_ **`UE::HLSL`** `namespace UE::HLSL` _[#if defined(__cplusplus)]_

#### typedef / using (3)

- L74 _typedef_ `using FDynamicWindSkeletonData = UE::HLSL::FDynamicWindSkeletonData;` _[#if defined(__cplusplus)]_
- L75 _typedef_ `using FDynamicWindBoneData = UE::HLSL::FDynamicWindBoneData;` _[#if defined(__cplusplus)]_
- L76 _typedef_ `using FDynamicWindBlockHeader = UE::HLSL::FDynamicWindBlockHeader;` _[#if defined(__cplusplus)]_

#### Functions (12)

- L80 _function_ `inline void SetMaxSimulationGroupIndex(FDynamicWindSkeletonData& S, uint32 V)` _[#if defined(__cplusplus)]_
- L81 _function_ `inline void SetIsGroundCover(FDynamicWindSkeletonData& S, uint32 V)` _[#if defined(__cplusplus)]_
- L83 _function_ `inline void SetBlockNumBones(FDynamicWindBlockHeader& H, uint32 V)` _[#if defined(__cplusplus)]_
- L84 _function_ `inline void SetBlockBoneOffset(FDynamicWindBlockHeader& H, uint32 V)` _[#if defined(__cplusplus)]_
- L86 _function_ `inline void SetBlockDirectionalityIndex(FDynamicWindBlockHeader& H, uint32 V)` _[#if defined(__cplusplus)]_
- L87 _function_ `inline void SetTotalTransformCount(FDynamicWindBlockHeader& H, uint32 V)` _[#if defined(__cplusplus)]_
- L91 _function_ `uint GetMaxSimulationGroupIndex(FDynamicWindSkeletonData S)` _[#if !(defined(__cplusplus))]_
- L92 _function_ `uint GetIsGroundCover(FDynamicWindSkeletonData S)` _[#if !(defined(__cplusplus))]_
- L94 _function_ `uint GetBlockNumBones(FDynamicWindBlockHeader H)` _[#if !(defined(__cplusplus))]_
- L95 _function_ `uint GetBlockBoneOffset(FDynamicWindBlockHeader H)` _[#if !(defined(__cplusplus))]_
- L96 _function_ `uint GetBlockDirectionalityIndex(FDynamicWindBlockHeader H)` _[#if !(defined(__cplusplus))]_
- L97 _function_ `uint GetTotalTransformCount(FDynamicWindBlockHeader H)` _[#if !(defined(__cplusplus))]_
