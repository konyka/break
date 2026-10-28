# Shaders / Plugins/PCG/Shaders/Private

- files: 16; lines: 2900
- record kinds: cpp_binding=8, define=39, entry=8, function=148, include=22, macro_call=13, member=4, parameter=90, resource=60, stray_block=26, struct=2

### `Plugins/PCG/Shaders/Private/PCGDataCollectionDataInterface.ush` (Private)

- lines: 836; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++); parse notes: 22

#### Structs / classes (1)

- L43-53 _struct_ **`FPCGAttributeHeader_{DataInterfaceName}`** `struct FPCGAttributeHeader_{DataInterfaceName}`
  - L46 _member_ `uint FirstElementAddress;` — Absolute address of this attribute's first data element in the buffer.
  - L49 _member_ `uint Stride;` — Stride (in bytes) of this attribute.
  - L52 _member_ `bool bAllocated;` — Whether or not this attribute is full-width allocated.

#### Global resources (textures / buffers / samplers) (4)

- L22 _resource_ `ByteAddressBuffer {DataInterfaceName}_DataCollectionBufferSRV;`
- L23 _resource_ `RWByteAddressBuffer {DataInterfaceName}_DataCollectionBufferUAV;`
- L35 _resource_ `StructuredBuffer<int> {DataInterfaceName}_GraphToBufferAttributeId;`
- L39 _resource_ `StructuredBuffer<int> {DataInterfaceName}_BufferToGraphStringKey;`

#### Global parameters (uniforms) (4)

- L26 _parameter_ `uint {DataInterfaceName}_ElementCountMultiplier;` — Multiplier that can be configured on output pins.
- L33 _parameter_ `uint {DataInterfaceName}_AllocatedNativePropertiesMask;` — Union of EPCGPointNativeProperties bits across ALL output data items. Non-zero bit = that property is N-slot (fully allocated) in at least one data item. Set from C++ at dispatch time; cheaper to read than querying the buffer header per-thread. Consequence for multi-data: if a property is N-slot in any data item, the preamble does per-element copies for ALL data items, including those where the property is CVR - those writes are redundant but harmless (all hit slot 0 via bAllocated clamping). todo_pcg: could be moved into the per-data GPU buffer header, making it truly per-data and eliminating
- L37 _parameter_ `int {DataInterfaceName}_FirstRemappedAttributeId;`
- L41 _parameter_ `int {DataInterfaceName}_NumRemappedStringKeys;`

#### Functions (77)

- L58-61 _function_ `uint GetElementCountMultiplier_{DataInterfaceName}()` — @todo_pcg: This parameter is broader than this data interface. Needs to be shared in some way (e.g. with TextureDataInterface).
- L66-69 _function_ `uint GetAllocatedNativePropertiesMask_{DataInterfaceName}()` — Returns the union of EPCGPointNativeProperties bits across all output data items. Non-zero bit = that property is N-slot (fully allocated) in at least one data item. Used in the processor preamble to branch between CVR (write at element 0) and N-slot (write per-element) copies. See comment on the uniform above for multi-data implications.
- L76-79 _function_ `uint GetNumData_{NameSuffix}_{DataInterfaceName}()`
- L81-89 _function_ `uint GetNumElements_{NameSuffix}_{DataInterfaceName}(uint InDataIndex)`
- L91-113 _function_ `bool GetThreadData_{NameSuffix}_{DataInterfaceName}(uint InThreadIndex, out uint OutDataIndex, out uint OutElementIndex)`
- L115-126 _function_ `uint GetNumElements_{NameSuffix}_{DataInterfaceName}()`
- L135-138 _function_ `uint LoadBufferInternal_{NameSuffix}_{DataInterfaceName}(uint InAddress)`
- L145-148 _function_ `void StoreBufferInternal_{NameSuffix}_{DataInterfaceName}(uint InAddress, uint InValue)`
- L152-164 _function_ `int GetRemappedAttributeIdInternal_{DataInterfaceName}(int InGraphAttributeId)`
- L168-186 _function_ `FPCGAttributeHeader_{DataInterfaceName} GetAttributeHeaderInternal_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, int InAttributeId)`
- L188-194 _function_ `uint2 GetElementAddressAndStrideInternal_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L196-199 _function_ `uint GetElementAddressInternal_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L201-214 _function_ `uint GetFirstValidAttributeElementInternal_{NameSuffix}_{DataInterfaceName}()`
- L216-224 _function_ `uint GetDataNumAttributesInternal_{NameSuffix}_{DataInterfaceName}(uint InDataIndex)`
- L231-233 _function_ `void SetAsExecutedInternal_{NameSuffix}_{DataInterfaceName}()` — Deprecated (5.8)
- L242-254 _function_ `uint GetUint_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L256-259 _function_ `bool GetBool_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L261-264 _function_ `int GetInt_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L266-269 _function_ `float GetFloat_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L271-283 _function_ `float2 GetFloat2_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L285-297 _function_ `float3 GetFloat3_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L299-311 _function_ `float4 GetFloat4_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L313-316 _function_ `float3 GetRotator_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L318-321 _function_ `float4 GetQuat_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L323-339 _function_ `float4x4 GetTransform_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L341-353 _function_ `int GetStringKey_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L355-359 _function_ `int GetName_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId)`
- L368-376 _function_ `void SetBool_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, bool InValue)`
- L378-386 _function_ `void SetInt_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, int InValue)`
- L388-396 _function_ `void SetUint_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, uint InValue)`
- L398-406 _function_ `void SetFloat_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, float InValue)`
- L408-416 _function_ `void SetFloat2_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, float2 InValue)`
- L418-426 _function_ `void SetFloat3_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, float3 InValue)`
- L428-436 _function_ `void SetFloat4_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, float4 InValue)`
- L438-446 _function_ `void SetRotator_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, float3 InValue)`
- L448-456 _function_ `void SetQuat_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, float4 InValue)`
- L458-469 _function_ `void SetTransform_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, float4x4 InValue)`
- L471-475 _function_ `void SetStringKey_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, int InValue)`
- L477-481 _function_ `void SetName_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, int InValue)`
- L489-501 _function_ `uint GetFirstAttributeAsUint_{NameSuffix}_{DataInterfaceName}()`
- L503-506 _function_ `bool GetFirstAttributeAsBool_{NameSuffix}_{DataInterfaceName}()`
- L508-511 _function_ `int GetFirstAttributeAsInt_{NameSuffix}_{DataInterfaceName}()`
- L513-516 _function_ `float GetFirstAttributeAsFloat_{NameSuffix}_{DataInterfaceName}()`
- L518-530 _function_ `float2 GetFirstAttributeAsFloat2_{NameSuffix}_{DataInterfaceName}()`
- L532-544 _function_ `float3 GetFirstAttributeAsFloat3_{NameSuffix}_{DataInterfaceName}()`
- L546-558 _function_ `float4 GetFirstAttributeAsFloat4_{NameSuffix}_{DataInterfaceName}()`
- L560-563 _function_ `float3 GetFirstAttributeAsRotator_{NameSuffix}_{DataInterfaceName}()`
- L565-568 _function_ `float4 GetFirstAttributeAsQuat_{NameSuffix}_{DataInterfaceName}()`
- L570-584 _function_ `float4x4 GetFirstAttributeAsTransform_{NameSuffix}_{DataInterfaceName}()`
- L586-590 _function_ `int GetFirstAttributeAsStringKey_{NameSuffix}_{DataInterfaceName}()`
- L592-596 _function_ `int GetFirstAttributeAsName_{NameSuffix}_{DataInterfaceName}()`
- L605-620 _function_ `int AtomicAddInt_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, int InValueToAdd)` — Returns value of attribute before incrementing.
- L623-638 _function_ `uint AtomicMaxUint_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, int InAttributeId, uint InValueToMax)` — Returns value of attribute before max operation.
- L646-649 _function_ `float3 GetPosition_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L651-654 _function_ `float4 GetRotation_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L656-659 _function_ `float3 GetScale_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L661-664 _function_ `float3 GetBoundsMin_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L666-669 _function_ `float3 GetBoundsMax_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L671-674 _function_ `float4 GetColor_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L676-679 _function_ `float GetDensity_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L681-684 _function_ `float GetSteepness_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L686-689 _function_ `uint GetSeed_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L691-707 _function_ `float4x4 GetPointTransform_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L709-712 _function_ `bool IsPointRemoved_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L720-723 _function_ `void SetPosition_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, float3 Position)`
- L725-728 _function_ `void SetRotation_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, float4 Rotation)`
- L730-733 _function_ `void SetScale_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, float3 Scale)`
- L735-738 _function_ `void SetBoundsMin_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, float3 BoundsMin)`
- L740-743 _function_ `void SetBoundsMax_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, float3 BoundsMax)`
- L745-748 _function_ `void SetColor_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, float4 Color)`
- L750-753 _function_ `void SetDensity_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, float Density)`
- L755-758 _function_ `void SetSteepness_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, float Steepness)`
- L760-763 _function_ `void SetSeed_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, uint Seed)`
- L765-781 _function_ `void SetPointTransform_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex, float4x4 Transform)`
- L783-786 _function_ `void RemovePoint_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)`
- L789-818 _function_ `void InitializeMetadata_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)` — Zero-initialize all metadata (user-defined) attributes for a single element.
- L821-833 _function_ `void InitializePoint_{NameSuffix}_{DataInterfaceName}(uint InDataIndex, uint InElementIndex)` — Initialize a single point with default values (native properties + metadata attributes).

#### Stray brace blocks (function body split by #if) (22)

- L74 _stray_block_ `{ ... }`
- L128 _stray_block_ `{ ... }`
- L133 _stray_block_ `{ ... }`
- L140 _stray_block_ `{ ... }`
- L143 _stray_block_ `{ ... }`
- L150 _stray_block_ `{ ... }`
- L167 _stray_block_ `{ ... }`
- L225 _stray_block_ `{ ... }`
- L228 _stray_block_ `{ ... }`
- L235 _stray_block_ `{ ... }`
- L240 _stray_block_ `{ ... }`
- L361 _stray_block_ `{ ... }`
- L366 _stray_block_ `{ ... }`
- L483 _stray_block_ `{ ... }`
- L488 _stray_block_ `{ ... }`
- L597 _stray_block_ `{ ... }`
- L602 _stray_block_ `{ ... }`
- L640 _stray_block_ `{ ... }`
- L645 _stray_block_ `{ ... }`
- L713 _stray_block_ `{ ... }`
- L718 _stray_block_ `{ ... }`
- L835 _stray_block_ `{ ... }`

<details><summary>parse notes</summary>

- L74: brace block without header (code split across #if branches)
- L128: brace block without header (code split across #if branches)
- L133: brace block without header (code split across #if branches)
- L140: brace block without header (code split across #if branches)
- L143: brace block without header (code split across #if branches)
- L150: brace block without header (code split across #if branches)
- L167: brace block without header (code split across #if branches)
- L225: brace block without header (code split across #if branches)
- L228: brace block without header (code split across #if branches)
- L235: brace block without header (code split across #if branches)
- L240: brace block without header (code split across #if branches)
- L361: brace block without header (code split across #if branches)
- L366: brace block without header (code split across #if branches)
- L483: brace block without header (code split across #if branches)
- L488: brace block without header (code split across #if branches)
- L597: brace block without header (code split across #if branches)
- L602: brace block without header (code split across #if branches)
- L640: brace block without header (code split across #if branches)
- L645: brace block without header (code split across #if branches)
- L713: brace block without header (code split across #if branches)
- L718: brace block without header (code split across #if branches)
- L835: brace block without header (code split across #if branches)

</details>

### `Plugins/PCG/Shaders/Private/PCGDilate.usf` (Private)

- lines: 58; parse: all-branches
- includes: L6 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L11-57 _entry_ `void MainPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `PCGDilate::FPCGDilatePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/PCG/Source/PCGCompute/Private/PCGDilate.cpp:28)

#### Global resources (textures / buffers / samplers) (1)

- L8 _resource_ `Texture2D<float4> InputTexture;`

#### Global parameters (uniforms) (1)

- L9 _parameter_ `int2 ResolutionMinusOne;`

### `Plugins/PCG/Shaders/Private/PCGGrassMapUnpackerCS.usf` (Private)

- lines: 146; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Public/Platform.ush`, L5 `/Engine/Private/Landscape/LandscapeCommon.ush`

#### Entry points (1)

- L72-145 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, THREADGROUPSIZE_Z)] void PCGGrassMapUnpacker_CS(const uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPCGGrassMapUnpackerCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/PCG/Source/PCGCompute/Private/PCGGrassMapUnpackerCS.cpp:15) — Dispatch group count is (ceil(InDispatchSize / 8), Max(1, NumGrassMaps)).

#### Global resources (textures / buffers / samplers) (6)

- L21 _resource_ `Texture2D<float4> InPackedGrassMaps;`
- L51 _resource_ `RWTexture2DArray<float> OutUnpackedGrassMaps;` — Grass map output. Dimension is (OutputWidth, InOutputHeight, NumGrassMaps).
- L54 _resource_ `RWTexture2D<float> OutUnpackedHeight;` — Height map output. Dimension is (OutputWidth, InOutputHeight).
- L56 _resource_ `StructuredBuffer<int> InComponentHeightOffsets;`
- L57 _resource_ `StructuredBuffer<int2> InComponentGrassmapOffsetAndChannels;`
- L58 _resource_ `StructuredBuffer<int> InOutputIndexToExportIndex;`

#### Global parameters (uniforms) (10)

- L59 _parameter_ `int InNumExportedGrassMaps;`
- L61 _parameter_ `int4 InLinearTileIndexToComponentIndex[PCG_MAX_NUM_LANDSCAPE_COMPONENTS];` — Only x component used, 16 byte alignment on arrays
- L62 _parameter_ `uint2 InNumTiles;`
- L63 _parameter_ `int2 InTileGridOrigin;` — Coordinate of bottom left corner of export tile grid, in output coordinates.
- L64 _parameter_ `uint InLandscapeComponentResolution;` — One texel per vert, so number of quads + 1
- L65 _parameter_ `float InLandscapeScaleZ;` — LS Actor DrawScale.z / 128.0f (ZSCALE)
- L66 _parameter_ `float InLandscapeRootZ;`
- L67 _parameter_ `uint InOutputHeight;`
- L68 _parameter_ `uint2 InDispatchOffset;` — Bottom left coordinate of this dispatch, in output coordinates.
- L69 _parameter_ `uint2 InDispatchSize;` — Number of XY threads in this dispatch.

### `Plugins/PCG/Shaders/Private/PCGInstanceDataInterface.ush` (Private)

- lines: 62; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (4)

- L8 _resource_ `StructuredBuffer<uint2> {DataInterfaceName}_PrimitiveParameters;` — Per primitive, per culling cell: (NumInstancesAllocated, InstanceOffset)
- L10 _resource_ `RWStructuredBuffer<uint4> {DataInterfaceName}_InstanceData;`
- L11 _resource_ `RWStructuredBuffer<uint> {DataInterfaceName}_InstanceCustomFloatData;`
- L12 _resource_ `RWStructuredBuffer<uint> {DataInterfaceName}_WriteCounters;`

#### Global parameters (uniforms) (4)

- L3 _parameter_ `uint {DataInterfaceName}_NumPrimitives;`
- L4 _parameter_ `uint {DataInterfaceName}_NumInstancesAllPrimitives;`
- L5 _parameter_ `uint {DataInterfaceName}_NumCustomFloatsPerInstance;`
- L6 _parameter_ `int {DataInterfaceName}_NumCullingCellsTotal;`

#### Functions (6)

- L14-17 _function_ `uint InstanceData_GetNumPrimitives_{DataInterfaceName}()`
- L19-22 _function_ `uint InstanceData_GetNumInstancesAllPrimitives_{DataInterfaceName}()`
- L24-42 _function_ `int InstanceData_GetIndexToWriteTo_{DataInterfaceName}(uint InPrimitiveIndex, uint InCullingCellId)`
- L44-51 _function_ `void InstanceData_WriteInstanceLocalToWorld_{DataInterfaceName}(uint InInstanceIndex, float4x4 InLocalToRelativeWorld)`
- L53-56 _function_ `void InstanceData_WriteCustomFloat_{DataInterfaceName}(uint InInstanceIndex, uint InCustomFloatIndex, float InValue)`
- L58-61 _function_ `void InstanceData_WriteCustomFloatRaw_{DataInterfaceName}(uint InInstanceIndex, uint InCustomFloatIndex, uint InValueAsUint)`

### `Plugins/PCG/Shaders/Private/PCGLandscapeDataInterface.ush` (Private)

- lines: 292; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/PCG/Private/PCGVirtualTextureCommon.ush`
- L288 #undef `VIRTUAL_TEXTURE_UNPACK_NORMAL_NONE`; L289 #undef `VIRTUAL_TEXTURE_UNPACK_NORMAL_BC3BC3`; L290 #undef `VIRTUAL_TEXTURE_UNPACK_NORMAL_BC5BC1`; L291 #undef `VIRTUAL_TEXTURE_UNPACK_NORMAL_B5G6R5`

#### Global resources (textures / buffers / samplers) (16)

- L6 _resource_ `Texture2D {DataInterfaceName}_HeightVirtualTexture;` — Height RVT
- L7 _resource_ `Texture2D<uint4> {DataInterfaceName}_HeightVirtualTexturePageTable;`
- L8 _resource_ `Texture2D<uint> {DataInterfaceName}_HeightVirtualTexturePageTableIndirection;`
- L10 _resource_ `SamplerState {DataInterfaceName}_HeightVirtualTextureSampler;`
- L19 _resource_ `Texture2D {DataInterfaceName}_NormalVirtualTexture0;` — Normal RVT
- L20 _resource_ `Texture2D {DataInterfaceName}_NormalVirtualTexture1;`
- L21 _resource_ `Texture2D<uint4> {DataInterfaceName}_NormalVirtualTexturePageTable;`
- L22 _resource_ `Texture2D<uint> {DataInterfaceName}_NormalVirtualTexturePageTableIndirection;`
- L25 _resource_ `SamplerState {DataInterfaceName}_NormalVirtualTexture0Sampler;`
- L26 _resource_ `SamplerState {DataInterfaceName}_NormalVirtualTexture1Sampler;`
- L37 _resource_ `Texture2D {DataInterfaceName}_BaseColorVirtualTexture;` — Base Color RVT
- L38 _resource_ `Texture2D<uint4> {DataInterfaceName}_BaseColorVirtualTexturePageTable;`
- L39 _resource_ `Texture2D<uint> {DataInterfaceName}_BaseColorVirtualTexturePageTableIndirection;`
- L41 _resource_ `SamplerState {DataInterfaceName}_BaseColorVirtualTextureSampler;`
- L52 _resource_ `Texture2D {DataInterfaceName}_CollisionHeightTexture;` — Collision based height texture
- L53 _resource_ `SamplerState {DataInterfaceName}_CollisionHeightTextureSampler;`

#### Global parameters (uniforms) (33)

- L9 _parameter_ `uint {DataInterfaceName}_HeightVirtualTextureAdaptive;`
- L11 _parameter_ `float3 {DataInterfaceName}_HeightVirtualTextureLWCTile;`
- L12 _parameter_ `float4x4 {DataInterfaceName}_HeightVirtualTextureWorldToUVTransform;`
- L13 _parameter_ `uint {DataInterfaceName}_HeightVirtualTextureEnabled;`
- L14 _parameter_ `uint4 {DataInterfaceName}_HeightVirtualTexturePackedUniform0;`
- L15 _parameter_ `uint4 {DataInterfaceName}_HeightVirtualTexturePackedUniform1;`
- L16 _parameter_ `uint4 {DataInterfaceName}_HeightVirtualTextureUniforms;`
- L23 _parameter_ `uint {DataInterfaceName}_NormalVirtualTextureAdaptive;`
- L24 _parameter_ `uint2 {DataInterfaceName}_NormalVirtualTexturePageTableLayers;`
- L27 _parameter_ `float3 {DataInterfaceName}_NormalVirtualTextureLWCTile;`
- L28 _parameter_ `float4x4 {DataInterfaceName}_NormalVirtualTextureWorldToUVTransform;`
- L29 _parameter_ `uint4 {DataInterfaceName}_NormalVirtualTexturePackedUniform0;`
- L30 _parameter_ `uint4 {DataInterfaceName}_NormalVirtualTexturePackedUniform1;`
- L31 _parameter_ `uint4 {DataInterfaceName}_NormalVirtualTextureUniforms0;`
- L32 _parameter_ `uint4 {DataInterfaceName}_NormalVirtualTextureUniforms1;`
- L33 _parameter_ `int {DataInterfaceName}_NormalVirtualTextureUnpackMode;`
- L34 _parameter_ `uint {DataInterfaceName}_NormalVirtualTextureEnabled;`
- L40 _parameter_ `uint {DataInterfaceName}_BaseColorVirtualTextureAdaptive;`
- L42 _parameter_ `float3 {DataInterfaceName}_BaseColorVirtualTextureLWCTile;`
- L43 _parameter_ `float4x4 {DataInterfaceName}_BaseColorVirtualTextureWorldToUVTransform;`
- L44 _parameter_ `uint {DataInterfaceName}_BaseColorVirtualTextureUnpackSRGB;`
- L45 _parameter_ `uint {DataInterfaceName}_BaseColorVirtualTextureUnpackYCoCg;`
- L46 _parameter_ `uint {DataInterfaceName}_BaseColorVirtualTextureEnabled;`
- L47 _parameter_ `uint4 {DataInterfaceName}_BaseColorVirtualTexturePackedUniform0;`
- L48 _parameter_ `uint4 {DataInterfaceName}_BaseColorVirtualTexturePackedUniform1;`
- L49 _parameter_ `uint4 {DataInterfaceName}_BaseColorVirtualTextureUniforms;`
- L54 _parameter_ `uint {DataInterfaceName}_CollisionHeightTextureEnabled;`
- L55 _parameter_ `float3 {DataInterfaceName}_CollisionHeightTextureLWCTile;`
- L56 _parameter_ `float4x4 {DataInterfaceName}_CollisionHeightTextureWorldToUVTransform;`
- L57 _parameter_ `float4x4 {DataInterfaceName}_CollisionHeightTextureUVToWorldTransform;`
- L58 _parameter_ `float4 {DataInterfaceName}_CollisionHeightTextureUVScaleBias;`
- L59 _parameter_ `int2 {DataInterfaceName}_CollisionHeightTextureDimension;`
- L62 _parameter_ `float2 {DataInterfaceName}_LandscapeGridSize;` — Misc parameters

#### Functions (5)

- L64-75 _function_ `float2 GetCollisionHeightTextureUV_{DataInterfaceName}(float3 InWorldPos)`
- L77-133 _function_ `float GetHeight_{DataInterfaceName}(float3 InWorldPos)`
- L135-149 _function_ `float3 CalculateNormalFromHeights_{DataInterfaceName}(float3 InWorldPos)`
- L151-223 _function_ `float3 GetNormal_{DataInterfaceName}(float3 InWorldPos)`
- L225-286 _function_ `float3 GetBaseColor_{DataInterfaceName}(float3 InWorldPos)`

### `Plugins/PCG/Shaders/Private/PCGRawBufferDataInterface.ush` (Private)

- lines: 73; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++); parse notes: 4

#### Global resources (textures / buffers / samplers) (2)

- L9 _resource_ `ByteAddressBuffer {DataInterfaceName}_DataSRV;`
- L10 _resource_ `RWByteAddressBuffer {DataInterfaceName}_DataUAV;`

#### Global parameters (uniforms) (1)

- L13 _parameter_ `uint {DataInterfaceName}_SizeBytes;` — Number of bytes in buffer.

#### Functions (7)

- L17-20 _function_ `uint GetNumElements_{DataInterfaceName}()`
- L26-29 _function_ `uint Load_{NameSuffix}_{DataInterfaceName}(uint InElementIndex)`
- L31-34 _function_ `uint4 Load4_{NameSuffix}_{DataInterfaceName}(uint InFirstElementIndex)`
- L42-45 _function_ `void Store_{NameSuffix}_{DataInterfaceName}(uint InElementIndex, uint InValue)`
- L47-50 _function_ `void Store4_{NameSuffix}_{DataInterfaceName}(uint InFirstElementIndex, uint4 InValue)`
- L55-61 _function_ `uint AtomicAdd_{NameSuffix}_{DataInterfaceName}(uint InElementIndex, uint InValueToAdd)` — Returns value before incrementing.
- L64-70 _function_ `uint AtomicMax_{NameSuffix}_{DataInterfaceName}(uint InElementIndex, uint InValueToMax)` — Returns value of attribute before max operation.

#### Stray brace blocks (function body split by #if) (4)

- L25 _stray_block_ `{ ... }`
- L35 _stray_block_ `{ ... }`
- L38 _stray_block_ `{ ... }`
- L72 _stray_block_ `{ ... }`

<details><summary>parse notes</summary>

- L25: brace block without header (code split across #if branches)
- L35: brace block without header (code split across #if branches)
- L38: brace block without header (code split across #if branches)
- L72: brace block without header (code split across #if branches)

</details>

### `Plugins/PCG/Shaders/Private/PCGRayTrace.usf` (Private)

- lines: 174; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ComputeShaderUtils.ush`, L5 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L6 `/Engine/Private/RayTracing/TraceRayInline.ush`, L7 `/Engine/Public/BindlessResources.ush`, L8 `/Engine/Private/Visualization.ush`

#### Macros (#define, 1)

- L10 `#define PCG_DEFAULT_NORMAL float3(0.0f, 0.0f, 1.0f)`
- L173 #undef `PCG_DEFAULT_NORMAL`

#### Entry points (1)

- L145-171 _entry_ `[numthreads(PCG_NUM_THREADS_PER_GROUP, 1, 1)] void PCGRayTraceMainCS(const uint3 GroupId : SV_GroupID, const uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FPCGRayTraceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/PCG/Source/PCGCompute/Private/PCGRayTrace.cpp:74)

#### Global resources (textures / buffers / samplers) (4)

- L29 _resource_ `RWByteAddressBuffer InOutPackedData;` — Input packed data for each ray: - Ray Position    - 3 uints - Ray Culled      - 1 uint - Ray Direction   - 3 uints - Ray Max Length  - 1 uint - Empty packing   - 4 uints Output packed data for each ray: - Impact Position   - 3 uints - Ray Culled/Missed - 1 uint - Impact TexCoords  - 2 uints - Empty packing     - 2 uints - Impact Normals    - 3 uints - Empty packing     - 1 uint
- L30 _resource_ `RaytracingAccelerationStructure InTLAS;`
- L33 _resource_ `Buffer<uint> InPrimitiveUVOffsets;` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_ATTRIBUTES]_
- L34 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> InRayTracingSceneMetadata;` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_ATTRIBUTES]_

#### Global parameters (uniforms) (4)

- L32 _parameter_ `FResourceCollection InPrimitiveUVCollection;` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_ATTRIBUTES]_
- L36 _parameter_ `float3 InPreViewTranslation;`
- L37 _parameter_ `int InNumRays;`
- L38 _parameter_ `int InTexCoordsChannelIndex;`

#### Functions (3)

- L41-53 _function_ `void ReadInput(int InRayIndex, out float3 OutOrigin, out float3 OutDirection, out float OutLength, out int OutStatus)` — Unpack the data for this ray.
- L56-68 _function_ `void WriteOutput(int InRayIndex, float3 InHitPosition, float2 InTexCoords, float3 InNormals, int InStatus)` — Pack the impact data for this ray.
- L70-143 _function_ `void PCGRayTraceCommon(int InRayIndex, float3 InOrigin, float3 InDirection, float InLength)`

### `Plugins/PCG/Shaders/Private/PCGSceneWriter.usf` (Private)

- lines: 109; parse: all-branches
- includes: L5 `/Engine/Private/Common.ush`, L6 `/Engine/Private/ComputeShaderUtils.ush`, L7 `/Engine/Private/GPUScene/GPUSceneWriter.ush`, L8 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L44-108 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void SceneWriter_CS(const uint3 GroupId : SV_GroupID, const uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FPCGSceneWriterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/PCG/Source/PCGCompute/Private/PCGSceneWriterCS.cpp:14)

#### Global resources (textures / buffers / samplers) (3)

- L13 _resource_ `StructuredBuffer<uint4> InInstanceData;`
- L14 _resource_ `StructuredBuffer<uint> InInstanceCustomFloatData;`
- L15 _resource_ `StructuredBuffer<uint> InWriteCounters;`

#### Global parameters (uniforms) (8)

- L10 _parameter_ `uint InPrimitiveIndex;`
- L11 _parameter_ `uint InNumInstancesAllocatedInGPUScene;`
- L12 _parameter_ `uint InInstanceOffset;`
- L16 _parameter_ `uint InPrimitiveId;`
- L17 _parameter_ `uint InCustomDataCount;`
- L18 _parameter_ `uint InPayloadDataFlags;`
- L19 _parameter_ `uint InSeed;`
- L20 _parameter_ `uint InNumCullingCellsTotal;`

#### Functions (3)

- L23-26 _function_ `uint ComputeSeed(uint A, uint B)` — This follows the implementation in PCGHelpers.
- L29-36 _function_ `float FRand(inout uint InOutSeed)` — This follows the implementation in FRandomStream.
- L38-42 _function_ `void CullInstance(uint InstanceId)`

### `Plugins/PCG/Shaders/Private/PCGStaticMeshDataInterface.ush` (Private)

- lines: 169; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (5)

- L16 _resource_ `Buffer<uint> {DataInterfaceName}_IndexBuffer;`
- L17 _resource_ `Buffer<float> {DataInterfaceName}_PositionBuffer;`
- L18 _resource_ `Buffer<float4> {DataInterfaceName}_TangentBuffer;`
- L19 _resource_ `Buffer<float2> {DataInterfaceName}_UVBuffer;`
- L20 _resource_ `Buffer<float4> {DataInterfaceName}_ColorBuffer;`

#### Global parameters (uniforms) (5)

- L11 _parameter_ `int {DataInterfaceName}_NumVertices;`
- L12 _parameter_ `int {DataInterfaceName}_NumTriangles;`
- L13 _parameter_ `int {DataInterfaceName}_NumUVs;`
- L14 _parameter_ `uint {DataInterfaceName}_HasColors;`
- L22 _parameter_ `float3 {DataInterfaceName}_BoundsExtents;`

#### Functions (10)

- L26-29 _function_ `int GetNumVertices_{DataInterfaceName}(int DataIndex)`
- L31-66 _function_ `void GetVertex_{DataInterfaceName}(int DataIndex, int VertexIndex, out float3 OutPosition, out float3 OutNormal, out float3 OutTangent, out float3 OutBitangent)`
- L68-80 _function_ `float4 GetVertexColor_{DataInterfaceName}(int DataIndex, int VertexIndex)`
- L82-88 _function_ `float2 GetVertexUV_{DataInterfaceName}(int DataIndex, int VertexIndex, int UVSet)`
- L92-95 _function_ `int GetNumTriangles_{DataInterfaceName}(int DataIndex)`
- L97-112 _function_ `void GetTriangleIndices_{DataInterfaceName}(int DataIndex, int TriangleIndex, out int OutIndex0, out int OutIndex1, out int OutIndex2)`
- L114-135 _function_ `void SampleTriangle_{DataInterfaceName}( int DataIndex, int TriangleIndex, float3 BaryCoord, out float3 OutPosition, out float3 OutNormal, out float3 OutTangent, out float3 OutBitangent)`
- L137-148 _function_ `float4 SampleTriangleColor_{DataInterfaceName}(int DataIndex, int TriangleIndex, float3 BaryCoord)`
- L150-161 _function_ `float2 SampleTriangleUV_{DataInterfaceName}(int DataIndex, int TriangleIndex, float3 BaryCoord, int UVSet)`
- L165-168 _function_ `float3 GetMeshBoundsExtents_{DataInterfaceName}(int DataIndex)`

### `Plugins/PCG/Shaders/Private/PCGTexture2DArrayDataInterface.ush` (Private)

- lines: 117; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (3)

- L3 _resource_ `Texture2DArray {DataInterfaceName}_TextureSRV;`
- L4 _resource_ `RWTexture2DArray<float4> {DataInterfaceName}_TextureUAV;`
- L5 _resource_ `SamplerState {DataInterfaceName}_Sampler;`

#### Global parameters (uniforms) (6)

- L6 _parameter_ `uint2 {DataInterfaceName}_Resolution;`
- L7 _parameter_ `uint {DataInterfaceName}_ArraySize;`
- L8 _parameter_ `float4x4 {DataInterfaceName}_TextureTransform;`
- L9 _parameter_ `float4x4 {DataInterfaceName}_TextureInverseTransform;`
- L10 _parameter_ `float2 {DataInterfaceName}_TexelSizeWorld;`
- L11 _parameter_ `uint {DataInterfaceName}_NumMips;`

#### Functions (15)

- L15-18 _function_ `uint GetNumData_{DataInterfaceName}()`
- L20-23 _function_ `uint2 GetResolution_{DataInterfaceName}(uint InDataIndex)`
- L25-28 _function_ `uint GetArraySize_{DataInterfaceName}(uint InDataIndex)`
- L30-33 _function_ `uint3 GetNumElements_{DataInterfaceName}(uint InDataIndex)`
- L35-58 _function_ `bool GetThreadData_{DataInterfaceName}(uint InThreadIndex, out uint OutDataIndex, out uint3 OutElementIndex)`
- L62-68 _function_ `float2 GetTexCoords_{DataInterfaceName}(uint InDataIndex, float3 InWorldPos)`
- L70-73 _function_ `float2 GetTexelSize_{DataInterfaceName}(uint InDataIndex)`
- L75-78 _function_ `float2 GetTexelSizeWorld_{DataInterfaceName}(uint InDataIndex)`
- L80-83 _function_ `float4x4 GetTransform_{DataInterfaceName}(uint InDataIndex)`
- L85-88 _function_ `uint GetNumMips_{DataInterfaceName}(uint InDataIndex)`
- L90-93 _function_ `float4 Sample_{DataInterfaceName}(uint InDataIndex, float2 InTextureUV, uint InSliceIndex)`
- L95-99 _function_ `float4 SampleWorldPos_{DataInterfaceName}(uint InDataIndex, float3 WorldPos, uint InSliceIndex)`
- L101-104 _function_ `float4 Load_{DataInterfaceName}(uint InDataIndex, uint3 InElementIndex)`
- L106-109 _function_ `float4 Load_{DataInterfaceName}(uint InDataIndex, uint3 InElementIndex, uint InMipIndex)`
- L113-116 _function_ `void Store_{DataInterfaceName}(uint InDataIndex, uint3 InElementIndex, float4 InValue)`

### `Plugins/PCG/Shaders/Private/PCGTextureDataInterface.ush` (Private)

- lines: 423; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Macros (#define, 9)

- L5 `#define PCG_ENABLE_MULTIPLE_TEXTURE_OBJECTS {EnableMultipleTextureObjects}`
- L8 `#define PCG_TextureDimension_Texture2D 0`
- L9 `#define PCG_TextureDimension_Texture2DArray 1`
- L15 `#define PCG_TEXTURE_SRV_DECLARATION(Index) Texture2D {DataInterfaceName}_Texture_##Index; Texture2DArray {DataInterfaceName}_TextureArray_##Index;` (3 lines)
- L32 `#define PCG_TEXTURE_UAV_DECLARATION(Index) RWTexture2D<float4> {DataInterfaceName}_TextureUAV_##Index;` (3 lines)
- L178 `#define PCG_CONDITIONAL_TEXTURE_SAMPLE(Index) if (BindingIndex == Index) { if (TextureDimension == PCG_TextureDimension_Texture2D) { return {DataInterfaceName}_Texture_##Index.SampleLevel({DataInterfaceName}_Sampler, InTextureUV, 0); } else if (T ...` (17 lines)
- L235 `#define PCG_CONDITIONAL_TEXTURE_SAMPLE_WORLD_POS(Index) if (BindingIndex == Index) { const float2 TextureUV = GetTexCoords_{DataInterfaceName}(Index, WorldPos); if (TextureDimension == PCG_TextureDimension_Texture2D) { return {DataInterfaceName}_Texture_## ...` (18 lines)
- L295 `#define PCG_CONDITIONAL_TEXTURE_LOAD(Index) if (BindingIndex == Index) { if (TextureDimension == PCG_TextureDimension_Texture2D) { return {DataInterfaceName}_Texture_##Index.Load(uint3(InElementIndex, InMipIndex)); } else if (TextureDimension = ...` (17 lines)
- L357 `#define PCG_CONDITIONAL_TEXTURE_STORE(Index) if (BindingIndex == Index) { {DataInterfaceName}_TextureUAV_##Index[InElementIndex] = InValue; return; }` (6 lines)
- L30 #undef `PCG_TEXTURE_SRV_DECLARATION`; L37 #undef `PCG_TEXTURE_UAV_DECLARATION`; L233 #undef `PCG_CONDITIONAL_TEXTURE_SAMPLE`; L293 #undef `PCG_CONDITIONAL_TEXTURE_SAMPLE_WORLD_POS`; L355 #undef `PCG_CONDITIONAL_TEXTURE_LOAD`; L381 #undef `PCG_CONDITIONAL_TEXTURE_STORE`; L418 #undef `PCG_TextureDimension_Texture2D`; L419 #undef `PCG_TextureDimension_Texture2DArray`

#### Global resources (textures / buffers / samplers) (2)

- L39 _resource_ `SamplerState {DataInterfaceName}_Sampler;`
- L58 _resource_ `StructuredBuffer<uint4> {DataInterfaceName}_TextureInfos;` — Layout of TextureInfos buffer: - TextureInfo0 - uint32 - BindingIndex - uint32 - SliceIndex (aka TextureIndex if bound to a TextureArray, 0 otherwise.) - uint32 - Dimension - uint32 - NumMips - uint32 - ResolutionX - uint32 - ResolutionY - float  - TexelSizeWorldX (cm) - float  - TexelSizeWorldY (cm) - TextureInfo1 - TextureInfo2 - ...

#### Global parameters (uniforms) (3)

- L41 _parameter_ `float4x4 {DataInterfaceName}_TextureTransforms[PCG_MAX_NUM_SRV_BINDINGS];`
- L42 _parameter_ `float4x4 {DataInterfaceName}_TextureInverseTransforms[PCG_MAX_NUM_SRV_BINDINGS];`
- L59 _parameter_ `uint {DataInterfaceName}_NumTextureInfos;`

#### Functions (19)

- L63-81 _function_ `void GetTextureInfoInternal_{DataInterfaceName}(uint InDataIndex, out uint OutBindingIndex, out uint OutSliceIndex, out uint OutTextureDimension, out uint OutNumMips)`
- L83-93 _function_ `void GetTextureResolutionInternal_{DataInterfaceName}(uint InDataIndex, out uint2 OutResolution)`
- L97-100 _function_ `uint GetNumData_{DataInterfaceName}()`
- L102-112 _function_ `uint2 GetNumElements_{DataInterfaceName}(uint InDataIndex)`
- L114-137 _function_ `bool GetThreadData_{DataInterfaceName}(uint InThreadIndex, out uint OutDataIndex, out uint2 OutElementIndex)`
- L141-148 _function_ `float2 GetTexCoords_{DataInterfaceName}(uint InDataIndex, float3 InWorldPos)`
- L150-156 _function_ `float2 GetTexelSize_{DataInterfaceName}(uint InDataIndex)`
- L158-161 _function_ `float2 GetTexelSizeWorld_{DataInterfaceName}(uint InDataIndex)`
- L163-171 _function_ `uint GetNumMips_{DataInterfaceName}(uint InDataIndex)`
- L173-176 _function_ `float4x4 GetTransform_{DataInterfaceName}(uint InDataIndex)`
- L196-231 _function_ `float4 Sample_{DataInterfaceName}(uint InDataIndex, float2 InTextureUV)`
- L254-291 _function_ `float4 SampleWorldPos_{DataInterfaceName}(uint InDataIndex, float3 WorldPos)`
- L313-348 _function_ `float4 Load_{DataInterfaceName}(uint InDataIndex, uint2 InElementIndex, uint InMipIndex)`
- L350-353 _function_ `float4 Load_{DataInterfaceName}(uint InDataIndex, uint2 InElementIndex)`
- L366-379 _function_ `void Store_{DataInterfaceName}(uint InDataIndex, uint2 InElementIndex, float4 InValue)`
- L386-389 _function_ `float4 Sample_{DataInterfaceName}(float2 TexCoords)` — Deprecated (5.6). Fallback to using first data.
- L392-395 _function_ `float4 SampleWorldPos_{DataInterfaceName}(float2 WorldPos)` — Deprecated (5.6). Fallback to using first data.
- L398-410 _function_ `float2 GetTexCoords_{DataInterfaceName}(float2 WorldPos, float2 Min, float2 Max)` — Deprecated (5.7). Does not take data index, and assumes axis-aligned Z projection.
- L413-416 _function_ `float4 SampleWorldPos_{DataInterfaceName}(uint InDataIndex, float2 InWorldPos)` — Deprecated (5.7). Switched to using 3D world pos to support any texture orientation.

#### Top-level macro invocations (9)

- L19 _macro_call_ `PCG_TEXTURE_SRV_DECLARATION(0)`
- L21 _macro_call_ `PCG_TEXTURE_SRV_DECLARATION(1)` _[#if PCG_ENABLE_MULTIPLE_TEXTURE_OBJECTS]_
- L22 _macro_call_ `PCG_TEXTURE_SRV_DECLARATION(2)` _[#if PCG_ENABLE_MULTIPLE_TEXTURE_OBJECTS]_
- L23 _macro_call_ `PCG_TEXTURE_SRV_DECLARATION(3)` _[#if PCG_ENABLE_MULTIPLE_TEXTURE_OBJECTS]_
- L24 _macro_call_ `PCG_TEXTURE_SRV_DECLARATION(4)` _[#if PCG_ENABLE_MULTIPLE_TEXTURE_OBJECTS]_
- L25 _macro_call_ `PCG_TEXTURE_SRV_DECLARATION(5)` _[#if PCG_ENABLE_MULTIPLE_TEXTURE_OBJECTS]_
- L26 _macro_call_ `PCG_TEXTURE_SRV_DECLARATION(6)` _[#if PCG_ENABLE_MULTIPLE_TEXTURE_OBJECTS]_
- L27 _macro_call_ `PCG_TEXTURE_SRV_DECLARATION(7)` _[#if PCG_ENABLE_MULTIPLE_TEXTURE_OBJECTS]_
- L35 _macro_call_ `PCG_TEXTURE_UAV_DECLARATION(0)`

### `Plugins/PCG/Shaders/Private/PCGTextureReadback.usf` (Private)

- lines: 29; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L14-28 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, THREADGROUPSIZE_Z)] void PCGTextureReadback_CS(uint3 DispatchThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FPCGTextureReadbackCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/PCG/Source/PCGCompute/Private/PCGTextureReadback.cpp:41)

#### Global resources (textures / buffers / samplers) (4)

- L6 _resource_ `Texture2D<float4> SourceTexture;`
- L7 _resource_ `Texture2DArray<float4> SourceTextureArray;`
- L8 _resource_ `SamplerState SourceSampler;`
- L12 _resource_ `RWTexture2D<float4> OutputTexture;`

#### Global parameters (uniforms) (2)

- L9 _parameter_ `float2 SourceDimensions;`
- L10 _parameter_ `int SourceTextureIndex;`

### `Plugins/PCG/Shaders/Private/PCGTexureDownsample.usf` (Private)

- lines: 100; parse: all-branches
- includes: L5 `/Engine/Private/Common.ush`, L6 `/Engine/Private/GammaCorrectionCommon.ush`

#### Macros (#define, 12)

- L8 `#define PCG_DOWNSAMPLE_MODE_AVERAGE 0`
- L9 `#define PCG_DOWNSAMPLE_MODE_MIN 1`
- L10 `#define PCG_DOWNSAMPLE_MODE_MAX 2`
- L11 `#define PCG_DOWNSAMPLE_MODE_SUM 3`
- L18 `#define PCG_DATA_TYPE half4` _[#if PCG_DOWNSAMPLE_SRGB]_
- L20 `#define PCG_DATA_TYPE float4` _[#if !(PCG_DOWNSAMPLE_SRGB)]_
- L26 `#define PCG_TEXTURE_SAMPLE() MipArrayInSRV.SampleLevel(MipSampler, float3(UV, InThreadID.z), 0)` _[#if PCG_DOWNSAMPLE_TEXTUREARRAY]_
- L27 `#define PCG_TEXTURE_LOAD(Coords) MipArrayInSRV[uint3(Coords, InThreadID.z)]` _[#if PCG_DOWNSAMPLE_TEXTUREARRAY]_
- L28 `#define PCG_STORE_RESULT() MipArrayOutUAV[InThreadID] = OutColor` _[#if PCG_DOWNSAMPLE_TEXTUREARRAY]_
- L32 `#define PCG_TEXTURE_SAMPLE() MipInSRV.SampleLevel(MipSampler, UV, 0)` _[#if !(PCG_DOWNSAMPLE_TEXTUREARRAY)]_
- L33 `#define PCG_TEXTURE_LOAD(Coords) MipInSRV[Coords]` _[#if !(PCG_DOWNSAMPLE_TEXTUREARRAY)]_
- L34 `#define PCG_STORE_RESULT() MipOutUAV[InThreadID.xy] = OutColor` _[#if !(PCG_DOWNSAMPLE_TEXTUREARRAY)]_
- L3 #pragma `once`; L92 #undef `PCG_DOWNSAMPLE_MODE_AVERAGE`; L93 #undef `PCG_DOWNSAMPLE_MODE_MIN`; L94 #undef `PCG_DOWNSAMPLE_MODE_MAX`; L95 #undef `PCG_DOWNSAMPLE_MODE_SUM`; L96 #undef `PCG_DATA_TYPE`; L97 #undef `PCG_TEXTURE_SAMPLE`; L98 #undef `PCG_TEXTURE_LOAD`; L99 #undef `PCG_STORE_RESULT`

#### Entry points (1)

- L37-90 _entry_ `[numthreads(8, 8, 1)] void TextureDownsampleCS(const uint3 InThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FPCGTextureDownsampleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/PCG/Source/PCGCompute/Private/PCGTextureDownsample.cpp:36)

#### Global resources (textures / buffers / samplers) (5)

- L13 _resource_ `SamplerState MipSampler;`
- L24 _resource_ `Texture2DArray MipArrayInSRV;` _[#if PCG_DOWNSAMPLE_TEXTUREARRAY]_
- L25 _resource_ `RWTexture2DArray<PCG_DATA_TYPE> MipArrayOutUAV;` _[#if PCG_DOWNSAMPLE_TEXTUREARRAY]_
- L30 _resource_ `Texture2D MipInSRV;` _[#if !(PCG_DOWNSAMPLE_TEXTUREARRAY)]_
- L31 _resource_ `RWTexture2D<PCG_DATA_TYPE> MipOutUAV;` _[#if !(PCG_DOWNSAMPLE_TEXTUREARRAY)]_

#### Global parameters (uniforms) (2)

- L14 _parameter_ `uint2 MipOutSize;`
- L15 _parameter_ `float2 TexelSize;`

### `Plugins/PCG/Shaders/Private/PCGUnwrapMesh.usf` (Private)

- lines: 38; parse: all-branches
- includes: L6 `/Engine/Public/Platform.ush`

#### Entry points (2)

- L13-22 _entry_ `void MainVS( float3 InPosition : ATTRIBUTE0, float2 InUV : ATTRIBUTE1, out FUnwrapInterpolants OutInterps, out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `PCGUnwrapMesh::FPCGUnwrapMeshVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/PCG/Source/PCGCompute/Private/PCGUnwrapMesh.cpp:46)
- L24-37 _entry_ `void MainPS( FUnwrapInterpolants Interps, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `PCGUnwrapMesh::FPCGUnwrapMeshPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/PCG/Source/PCGCompute/Private/PCGUnwrapMesh.cpp:47)

#### Structs / classes (1)

- L8-11 _struct_ **`FUnwrapInterpolants`** `struct FUnwrapInterpolants`
  - L10 _member_ `float3 LocalPosition : TEXCOORD0;`

### `Plugins/PCG/Shaders/Private/PCGVirtualTextureCommon.ush` (Private)

- lines: 27; parse: all-branches
- includes: L9 `/Engine/Private/VirtualTextureCommon.ush`

#### Macros (#define, 15)

- L5 `#define NUM_VIRTUALTEXTURE_SAMPLES 1`
- L7 `#define VT_DISABLE_VIEW_UNIFORM_BUFFER 1`
- L12 `#define ERuntimeVirtualTextureMaterialType_BaseColor 0`
- L13 `#define ERuntimeVirtualTextureMaterialType_Mask4 1`
- L14 `#define ERuntimeVirtualTextureMaterialType_BaseColor_Normal_Roughness 2`
- L15 `#define ERuntimeVirtualTextureMaterialType_BaseColor_Normal_Specular 3`
- L16 `#define ERuntimeVirtualTextureMaterialType_BaseColor_Normal_Specular_YCoCg 4`
- L17 `#define ERuntimeVirtualTextureMaterialType_BaseColor_Normal_Specular_Mask_YCoCg 5`
- L18 `#define ERuntimeVirtualTextureMaterialType_WorldHeight 6`
- L19 `#define ERuntimeVirtualTextureMaterialType_Displacement 7`
- L20 `#define ERuntimeVirtualTextureMaterialType_Count 8`
- L23 `#define VIRTUAL_TEXTURE_UNPACK_NORMAL_NONE 0`
- L24 `#define VIRTUAL_TEXTURE_UNPACK_NORMAL_BC3BC3 1`
- L25 `#define VIRTUAL_TEXTURE_UNPACK_NORMAL_BC5BC1 2`
- L26 `#define VIRTUAL_TEXTURE_UNPACK_NORMAL_B5G6R5 3`
- L3 #pragma `once`

### `Plugins/PCG/Shaders/Private/PCGVirtualTextureDataInterface.ush` (Private)

- lines: 247; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/PCG/Private/PCGVirtualTextureCommon.ush`

#### Macros (#define, 2)

- L5 `#define PCG_VIRTUAL_TEXTURE_DECLARATION(DataIndex) Texture2D {DataInterfaceName}_VirtualTexture0_##DataIndex; Texture2D {DataInterfaceName}_VirtualTexture1_##DataIndex; Texture2D {DataInterfaceName}_VirtualTexture2_##DataIndex; Texture2D<uint4> {DataI ...` (6 lines)
- L79 `#define PCG_CONDITIONAL_VIRTUAL_TEXTURE_SAMPLE(DataIndex) if (InDataIndex == DataIndex) { VTPageTableResult PageTableResult = SamplePageTable_{DataInterfaceName}( InDataIndex, SampleUV, {DataInterfaceName}_PageTable_##DataIndex, {DataInterfaceName}_PageTable ...` (35 lines)
- L17 #undef `PCG_VIRTUAL_TEXTURE_DECLARATION`; L246 #undef `PCG_CONDITIONAL_VIRTUAL_TEXTURE_SAMPLE`

#### Global resources (textures / buffers / samplers) (1)

- L31 _resource_ `SamplerState {DataInterfaceName}_Sampler;`

#### Global parameters (uniforms) (7)

- L20 _parameter_ `uint4 {DataInterfaceName}_PageTableUniforms[PCG_MAX_NUM_BINDINGS * 2];` — Binding infos
- L21 _parameter_ `uint4 {DataInterfaceName}_PageTableInfo[PCG_MAX_NUM_BINDINGS];`
- L22 _parameter_ `float4 {DataInterfaceName}_LWCTiles[PCG_MAX_NUM_BINDINGS];`
- L23 _parameter_ `float4x4 {DataInterfaceName}_WorldToUVTransforms[PCG_MAX_NUM_BINDINGS];`
- L26 _parameter_ `uint4 {DataInterfaceName}_Uniforms[PCG_MAX_NUM_BINDINGS * PCG_MAX_NUM_LAYERS];` — Layer infos
- L27 _parameter_ `uint4 {DataInterfaceName}_ValidLayerMasks[PCG_MAX_NUM_BINDINGS];`
- L30 _parameter_ `uint {DataInterfaceName}_NumVirtualTextures;` — Shared

#### Functions (3)

- L34-67 _function_ `VTPageTableResult SamplePageTable_{DataInterfaceName}( uint InDataIndex, float2 InSampleUV, Texture2D<uint4> InPageTable, Texture2D<uint> InPageTableIndirection, uint4 PageTableUniforms[2], bool InAdaptive)` — Sample the page table
- L70-77 _function_ `float4 SampleLayer_{DataInterfaceName}( VTPageTableResult InPageTableResult, Texture2D InTexture, uint4 InUniforms, uint InLayerIndex)` — Sample the physical texture
- L115-244 _function_ `void SampleVirtualTexture_{DataInterfaceName}( uint InDataIndex, float3 InWorldPos, out bool bOutInsideVolume, out float3 OutBaseColor, out float OutSpecular, out float OutRoughness, out float OutWorldHeight, out float3 OutNormal, out float OutDisplacement, out float OutMask, out float4 OutMask4)`

#### Top-level macro invocations (4)

- L12 _macro_call_ `PCG_VIRTUAL_TEXTURE_DECLARATION(0)`
- L13 _macro_call_ `PCG_VIRTUAL_TEXTURE_DECLARATION(1)`
- L14 _macro_call_ `PCG_VIRTUAL_TEXTURE_DECLARATION(2)`
- L15 _macro_call_ `PCG_VIRTUAL_TEXTURE_DECLARATION(3)`
