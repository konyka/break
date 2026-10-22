# Shaders / Plugins/Media/TmvMedia/Shaders/Private

- files: 4; lines: 491
- record kinds: cpp_binding=4, define=9, entry=4, function=12, include=7, member=2, parameter=32, resource=9, struct=1

### `Plugins/Media/TmvMedia/Shaders/Private/TmvColorProcessing.ush` (Private)

- lines: 50; parse: all-branches
- includes: L3 `/Engine/Private/GammaCorrectionCommon.ush`

#### Macros (#define, 5)

- L6 `#define UE_Color_EEncoding_Linear 1u`
- L7 `#define UE_Color_EEncoding_sRGB 2u`
- L8 `#define UE_Color_EEncoding_ST2084 3u`
- L9 `#define UE_Color_EEncoding_SLog3 12u`
- L10 `#define UE_Color_EEncoding_HLG 17u`

#### Functions (3)

- L13-32 _function_ `float3 ApplyColorTransformRGB(float3 InColor, float4x4 InColorSpaceMatrix, uint InEOTF)` — Simplified version of ApplyColorProcessingRGB, removed tonemapping.
- L34-44 _function_ `float3 YuvToRgb(float3 InYUV, float4x4 InYUVMatrix)`
- L47-50 _function_ `float3 ApplyColorTransform(float3 InYUV, float4x4 InYUVMatrix, float4x4 InColorSpaceMatrix, uint InEOTF)` — Simplified version of ApplyColorProcessing, removed tonemapping.

### `Plugins/Media/TmvMedia/Shaders/Private/TmvStructuredBufferSwizzler.usf` (Private)

- lines: 259; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Plugin/TmvMedia/Private/TmvColorProcessing.ush`

#### Macros (#define, 2)

- L7 `#define PERMUTATION_CHANNELS 0` _[#if !defined(PERMUTATION_CHANNELS)]_
- L10 `#define NUM_CHANNELS (PERMUTATION_CHANNELS + 1)`

#### Entry points (2)

- L83-90 _entry_ `void MainVS( in float4 InPosition : ATTRIBUTE0, in float2 InTexCoord : ATTRIBUTE1, out noperspective float4 OutUVAndScreenPos : TEXCOORD0, out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FTmvSwizzleVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/TmvMedia/Source/TmvMediaShaders/Private/TmvStructuredBufferSwizzlingShader.cpp:10) — Vertex Shader.
- L203-259 _entry_ `half4 MainPS(noperspective float4 UVAndScreenPos : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FTmvStructuredBufferSwizzlePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/TmvMedia/Source/TmvMediaShaders/Private/TmvStructuredBufferSwizzlingShader.cpp:9) — Pixel Shader.

#### Structs / classes (1)

- L20-26 _struct_ **`FTileDesc`** `struct FTileDesc` — Describes the memory mapping of a tile "sub" buffer in the unswizzled buffer.
  - L23 _member_ `uint4 Offsets;` — Offset within the tile buffer for the start of each plane.
  - L25 _member_ `uint4 Strides;` — Offset within the tile buffer for the start of each plane.

#### Global resources (textures / buffers / samplers) (2)

- L13 _resource_ `StructuredBuffer<uint> UnswizzledBuffer;` — The unswizzled buffer packed into 4 byte buffer stride.
- L29 _resource_ `StructuredBuffer<FTileDesc> TileMappingBuffer;` — For partial tiles, describes the mapping of each tile to its location in the unswizzled buffer.

#### Global parameters (uniforms) (17)

- L33 _parameter_ `int2 DestTextureSize;` — Texture size that the buffer is supposed to be unpacked to.
- L36 _parameter_ `int2 TileSize;` — Size (dimensions), in pixels, of tiles that represent this texture.
- L39 _parameter_ `int2 NumTiles;` — Total number of tiles in X and Y direction for the current mip level.
- L44 _parameter_ `int TileBufferFullStride;` — Total size of a single tile buffer (i.e. sum of all planes and padding).
- L47 _parameter_ `int4 TileBufferOffsets;` — Offset within the tile buffer for the start of each plane.
- L50 _parameter_ `int4 TileBufferStrides;` — Stride of each planes in the tile buffer.
- L54 _parameter_ `int4 PlaneBufferOffsets;` — --- Planar Addressing mode ---
- L55 _parameter_ `int4 PlaneBufferStrides;`
- L59 _parameter_ `int4 PlaneWidthRatios;` — Ratio of width for the chroma samples
- L62 _parameter_ `int4 PlaneHeightRatios;` — Ratio of height for the chroma samples
- L65 _parameter_ `uint bApplyColorTransform;` — Flag to enable color space transformations.
- L68 _parameter_ `uint EOTF;` — Source encoding to linearize.
- L71 _parameter_ `float4x4 ColorSpaceMatrix;` — Color space transformation matrix, from source to working.
- L73 _parameter_ `uint bConvertYUV;`
- L75 _parameter_ `float4x4 YUVMatrix;`
- L78 _parameter_ `float AlphaScale;` — Alpha is not part of the color correction.
- L80 _parameter_ `float4 MipTint;`

#### Functions (4)

- L93-113 _function_ `float GetBufferValue(int BufferOffset)` — Unpacks data from the provided structured buffer.
- L116-153 _function_ `void GetBufferPositions_PartialTiles(in int2 InPixelPos, out int4 OutBufferPositions)` — Calculate the buffer "position" of the given pixel for all planes (channels).
- L156-181 _function_ `void GetBufferPositions_RenderTiles(in int2 InPixelPos, out int4 OutBufferPositions)` — Calculate the buffer "position" of the given pixel for all planes (channels).
- L184-200 _function_ `void GetBufferPositions_Planar(in int2 InPixelPos, out int4 OutBufferPositions)` — Calculate the buffer "position" of the given pixel for all planes (channels).

### `Plugins/Media/TmvMedia/Shaders/Private/TmvTextureBufferSwizzler.usf` (Private)

- lines: 78; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Plugin/TmvMedia/Private/TmvColorProcessing.ush`

#### Macros (#define, 2)

- L7 `#define PERMUTATION_CHANNELS 0` _[#if !defined(PERMUTATION_CHANNELS)]_
- L10 `#define NUM_CHANNELS (PERMUTATION_CHANNELS + 1)`

#### Entry points (1)

- L42-78 _entry_ `half4 MainPS(noperspective float4 UVAndScreenPos : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FTmvTextureBufferSwizzlePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/TmvMedia/Source/TmvMediaShaders/Private/TmvTextureBufferSwizzlingShader.cpp:9) — Pixel Shader.

#### Global resources (textures / buffers / samplers) (5)

- L12 _resource_ `Texture2D InPlaneTexture0;`
- L13 _resource_ `Texture2D InPlaneTexture1;`
- L14 _resource_ `Texture2D InPlaneTexture2;`
- L15 _resource_ `Texture2D InPlaneTexture3;`
- L16 _resource_ `SamplerState InPlaneTextureSampler;`

#### Global parameters (uniforms) (7)

- L19 _parameter_ `uint bApplyColorTransform;` — Flag to enable color space transformations.
- L22 _parameter_ `uint EOTF;` — Source encoding to linearize.
- L25 _parameter_ `float4x4 ColorSpaceMatrix;` — Color space transformation matrix, from source to working.
- L27 _parameter_ `uint bConvertYUV;`
- L29 _parameter_ `float4x4 YUVMatrix;`
- L32 _parameter_ `float AlphaScale;` — Alpha is not part of the color correction.
- L34 _parameter_ `float4 MipTint;`

#### Functions (1)

- L36-39 _function_ `float SampleComponent(Texture2D InTexture, float2 UV)`

### `Plugins/Media/TmvMedia/Shaders/Private/TmvTextureYuvConverter.usf` (Private)

- lines: 104; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Plugin/TmvMedia/Private/TmvColorProcessing.ush`

#### Entry points (1)

- L90-103 _entry_ `half4 MainPS(float4 SvPosition : SV_POSITION) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FTmvTextureYuvConverterPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/TmvMedia/Source/TmvMediaShaders/Private/TmvTextureYuvConvertShader.cpp:10) — Pixel Shader.

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `Texture2D InTexture;` — Input media texture to convert.
- L10 _resource_ `SamplerState InTextureSampler;` — Sampler state for the media texture.

#### Global parameters (uniforms) (8)

- L12 _parameter_ `float4 UVScaleAndOffset;`
- L15 _parameter_ `uint bApplyColorTransform;` — Flag to enable color space transformations.
- L18 _parameter_ `uint EOTF;` — Destination encoding (transfer function) to apply. Enum value of UE::Color::EEncoding.
- L21 _parameter_ `float4x4 ColorSpaceMatrix;` — Color space transformation matrix from "working" to destination.
- L24 _parameter_ `uint bConvertYUV;` — If true (non-zero), perform the rgb to yuv conversion.
- L27 _parameter_ `float4x4 YUVMatrix;` — RGB to YUV conversion matrix.
- L30 _parameter_ `float4 DataScale;` — Final Scale applied to values before being stored.
- L32 _parameter_ `float4 MipTint;`

#### Functions (4)

- L35-43 _function_ `float3 GenericColorTransform(float3 InColor, float4x4 InMatrix)` — Transforms the given color with the given matrix.
- L48-53 _function_ `float3 LinearToSLog3(float3 Value)` — Sony S-Log3 (todo: test)
- L55-81 _function_ `float3 EncodeTransferFunction(float3 InColor, uint InEOTF)`
- L84-87 _function_ `float2 ScreenPosToUV(float2 InScreenPos)` — Converts from screen position (FScreenVertexShaderVS output) to texture UV according to draw info.
