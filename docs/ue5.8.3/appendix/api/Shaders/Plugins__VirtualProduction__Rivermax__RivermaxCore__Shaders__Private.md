# Shaders / Plugins/VirtualProduction/Rivermax/RivermaxCore/Shaders/Private

- files: 1; lines: 751
- record kinds: cpp_binding=12, define=1, entry=12, function=2, include=3, member=12, parameter=9, resource=15, struct=6

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Shaders/Private/RivermaxShaders.usf` (Private)

- lines: 751; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`, L8 `/Engine/Private/ColorUtils.ush`, L9 `/Engine/Private/GammaCorrectionCommon.ush`

#### Macros (#define, 1)

- L25 `#define DISPATCH_GROUP_COUNT 512, 1, 1`

#### Entry points (12)

- L79-106 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void RGBToYUV8Bit422(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRGBToYUV8Bit422CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:32)
- L111-143 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void RGBToYUV10Bit422(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRGBToYUV10Bit422LittleEndianCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:79)
- L147-200 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void RGBToRGB10BitCS(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRGBToRGB10BitCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:169)
- L204-304 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void RGB10BitToRGBACS(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRGB10BitToRGBA10CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:151)
- L308-338 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void RGBToRGB8BitCS(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRGBToRGB8BitCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:125)
- L342-395 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void RGB8BitToRGBA8CS(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRGB8BitToRGBA8CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:108)
- L399-434 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void RGBToRGB12BitCS(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRGBToRGB12BitCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:215)
- L438-506 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void RGB12BitToRGBACS(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRGB12BitToRGBA12CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:197)
- L509-539 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void RGBToRGB16fBitCS(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRGBToRGB16fCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:242) — Shader to convert from RGBA to RGB Float16
- L572-623 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void RGB16fBitToRGBACS(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRGB16fBitToRGBA16fCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:269)
- L627-680 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void YUV8Bit422ToRGBACS(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FYUV8Bit422ToRGBACS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:14)
- L684-750 _entry_ `[numthreads(DISPATCH_GROUP_COUNT)] void YUV10Bit422ToRGBACS(uint3 ThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FYUV10Bit422ToRGBACS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxShaders.cpp:61)

#### Structs / classes (6)

- L27-30 _struct_ **`FYUV8Bit422Buffer`** `struct FYUV8Bit422Buffer`
  - L29 _member_ `uint DWord0;`
- L34-41 _struct_ **`FYCbCr10Bit422`** `struct FYCbCr10Bit422`
  - L36 _member_ `uint DWord0;`
  - L37 _member_ `uint DWord1;`
  - L38 _member_ `uint DWord2;`
  - L39 _member_ `uint DWord3;`
  - L40 _member_ `uint DWord4;`
- L45-50 _struct_ **`FRGB8BitBuffer`** `struct FRGB8BitBuffer`
  - L47 _member_ `uint DWord0;`
  - L48 _member_ `uint DWord1;`
  - L49 _member_ `uint DWord2;`
- L54-57 _struct_ **`FRGB10BitBuffer`** `struct FRGB10BitBuffer`
  - L56 _member_ `uint DWords[15];`
- L61-64 _struct_ **`FRGB12BitBuffer`** `struct FRGB12BitBuffer`
  - L63 _member_ `uint DWords[9];`
- L68-71 _struct_ **`FRGB16fBuffer`** `struct FRGB16fBuffer`
  - L70 _member_ `uint DWords[3];`

#### Global resources (textures / buffers / samplers) (15)

- L11 _resource_ `Texture2D InputTexture;`
- L12 _resource_ `SamplerState InputSampler;`
- L22 _resource_ `RWTexture2D<float4> OutTexture;`
- L31 _resource_ `RWStructuredBuffer<FYUV8Bit422Buffer> OutYUV4228bitBuffer;`
- L32 _resource_ `StructuredBuffer<FYUV8Bit422Buffer> InputYUV4228bitBuffer;`
- L42 _resource_ `RWStructuredBuffer<FYCbCr10Bit422> OutYCbCrBuffer;`
- L43 _resource_ `StructuredBuffer<FYCbCr10Bit422> InputYCbCrBuffer;`
- L51 _resource_ `RWStructuredBuffer<FRGB8BitBuffer> OutRGB8Buffer;`
- L52 _resource_ `StructuredBuffer<FRGB8BitBuffer> InputRGB8Buffer;`
- L58 _resource_ `RWStructuredBuffer<FRGB10BitBuffer> OutRGB10Buffer;`
- L59 _resource_ `StructuredBuffer<FRGB10BitBuffer> InputBuffer;`
- L65 _resource_ `RWStructuredBuffer<FRGB12BitBuffer> OutRGB12Buffer;`
- L66 _resource_ `StructuredBuffer<FRGB12BitBuffer> InputRGB12Buffer;`
- L72 _resource_ `RWStructuredBuffer<FRGB16fBuffer> OutRGB16fBuffer;`
- L73 _resource_ `StructuredBuffer<FRGB16fBuffer> InputRGB16fBuffer;`

#### Global parameters (uniforms) (9)

- L13 _parameter_ `float4x4 ColorTransform;`
- L14 _parameter_ `uint DoLinearToSrgb;`
- L15 _parameter_ `float OnePixelDeltaX;`
- L16 _parameter_ `float OnePixelDeltaY;`
- L17 _parameter_ `float InputPixelOffsetX;`
- L18 _parameter_ `float InputPixelOffsetY;`
- L19 _parameter_ `uint CapturedSizeX;`
- L20 _parameter_ `uint OutputTextureSizeX;`
- L21 _parameter_ `uint TotalElementCount;`

#### Functions (2)

- L545-555 _function_ `float UintContainingFloatToFloat(in uint Value)` — This function extracts the 16bit (float) data stored in uint (32 bit) Same used in EXRSwizzler.
- L557-568 _function_ `float GetEncodedFloatValue(in uint Value)`
