# Shaders / Plugins/Media/ImgMedia/Shaders/Private

- files: 1; lines: 196
- record kinds: cpp_binding=2, define=6, entry=2, function=4, include=2, member=3, parameter=6, resource=3, struct=1

### `Plugins/Media/ImgMedia/Shaders/Private/ExrSwizzler.usf` (Private)

- lines: 196; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/GammaCorrectionCommon.ush`

#### Macros (#define, 6)

- L6 `#define NUM_CHANNELS (PERMUTATION_CHANNELS + 1)`
- L47 `#define UE_Color_EEncoding_Linear 1u`
- L48 `#define UE_Color_EEncoding_sRGB 2u`
- L49 `#define UE_Color_EEncoding_ST2084 3u`
- L50 `#define UE_Color_EEncoding_SLog3 12u`
- L51 `#define UE_Color_EEncoding_HLG 17u`

#### Entry points (2)

- L88-95 _entry_ `void MainVS( in float4 InPosition : ATTRIBUTE0, in float2 InTexCoord : ATTRIBUTE1, out noperspective float4 OutUVAndScreenPos : TEXCOORD0, out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FExrSwizzleVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/ImgMedia/Source/ExrReaderGpu/Private/ExrSwizzlingShader.cpp:12) — Vertex Shader.
- L152-196 _entry_ `half4 MainPS(noperspective float4 UVAndScreenPos : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FExrSwizzlePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/ImgMedia/Source/ExrReaderGpu/Private/ExrSwizzlingShader.cpp:11) — Pixel Shader.

#### Structs / classes (1)

- L9-14 _struct_ **`FTileDesc`** `struct FTileDesc` _[#if PARTIAL_TILES]_
  - L11 _member_ `int2 TileResolution;` _[#if PARTIAL_TILES]_
  - L12 _member_ `uint BufferOffset;` _[#if PARTIAL_TILES]_
  - L13 _member_ `int AlignPadding;` _[#if PARTIAL_TILES]_

#### Global resources (textures / buffers / samplers) (3)

- L18 _resource_ `StructuredBuffer<uint> UnswizzledBuffer;` — The unswizzled buffer packed into 4 byte buffer stride.
- L22 _resource_ `StructuredBuffer<FTileDesc> TileDescBuffer;` — The unswizzled buffer packed into 4 byte buffer stride. _[#if PARTIAL_TILES]_
- L26 _resource_ `int2 TextureSize;` — Texture size that the buffer is supposed to be unpacked to.

#### Global parameters (uniforms) (6)

- L29 _parameter_ `int2 TileSize;` — Size of tiles that represent this texture.
- L32 _parameter_ `int2 NumTiles;` — Total number of tiles in X and Y direction for the current mip level.
- L35 _parameter_ `int NumChannels;` — Number of channels per pixel.
- L38 _parameter_ `uint bApplyColorTransform;` — Flag to enable color space transformations.
- L41 _parameter_ `uint EOTF;` — Source encoding to linearize.
- L44 _parameter_ `float4x4 ColorSpaceMatrix;` — Color space transformation matrix, from source to working.

#### Functions (4)

- L53-67 _function_ `float3 ApplyColorTransform(float3 Color, float3x3 InColorSpaceMatrix, uint InEOTF)`
- L70-84 _function_ `half GetBufferValue(int Offset, int2 TextureSize, int ChannelIndex)` — Unpacks data from the provided structured buffer.
- L98-116 _function_ `void GetStartScanlinePosition_PartialTiles(in int2 PixelPos, out int2 SampleSize, out int StartPosition)` _[#if PARTIAL_TILES]_
- L119-149 _function_ `void GetStartScanlinePosition(in int2 PixelPos, out int2 SampleSize, out int StartPosition)`
