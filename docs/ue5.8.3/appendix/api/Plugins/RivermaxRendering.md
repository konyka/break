# Plugins / RivermaxRendering

- module root: `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering`
- headers: 2; symbols: 88
- symbol kinds: class=13, function=12, member=24, namespace=2, prototype=25, struct=12
- PrivateDependencyModuleNames: Core, Projects, RHI, RenderCore
- PublicDependencyModuleNames: 

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Private/RivermaxRenderingModule.h` (Private)


#### class `FRivermaxRenderingModule`  
`class FRivermaxRenderingModule : public IModuleInterface`  
_L11-17_
- inherits: `IModuleInterface`
- desc: Module used to define Rivermax shaders used for pixel format conversion
- L15 _public prototype_ `virtual void StartupModule() override;`

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxRendering/Public/RivermaxShaders.h` (Public)


#### class `UE::RivermaxShaders::FYUV8Bit422ToRGBACS`  
`class FYUV8Bit422ToRGBACS : public FGlobalShader`  
_L20-51_
- inherits: `FGlobalShader`
- desc: Compute shader to convert 2110 YUV8 to RGBA
- L31 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FYUV8Bit422ToRGBACS, FGlobalShader);`
- L44 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L50 _public prototype_ `FYUV8Bit422ToRGBACS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGBufferRef YUVBuffer, FRDGTextureRef OutputTexture, const FMatrix& ColorTransform, const FVector& YUVOffset, int32 TotalElementCount, int32 BufferLineCount);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FYUV8Bit422ToRGBACS::FYUV8Bit422Buffer`  
`struct FYUV8Bit422Buffer`  
_L25-28_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf
- L27 _public member_ `uint32 DWord0;`

#### class `UE::RivermaxShaders::FRGBToYUV8Bit422CS`  
`class FRGBToYUV8Bit422CS : public FGlobalShader`  
_L56-89_
- inherits: `FGlobalShader`
- desc: Compute shader to convert RGB to YUV422 8 bits
- L67 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FRGBToYUV8Bit422CS, FGlobalShader);`
- L82 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L88 _public prototype_ `FRGBToYUV8Bit422CS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGTextureRef SourceTexture, const FIntPoint& CaptureSize, const FIntRect& SourceViewRect, const FIntPoint& OutputSize, const FMatrix& ColorTransform, const FVector& YUVOffset, bool bDoLinearToSrgb, FRDGBufferRef OutputBuffer);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FRGBToYUV8Bit422CS::FYUV8Bit422Buffer`  
`struct FYUV8Bit422Buffer`  
_L60-63_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf
- L62 _public member_ `uint32 DWord0;`

#### class `UE::RivermaxShaders::FYUV10Bit422ToRGBACS`  
`class FYUV10Bit422ToRGBACS : public FGlobalShader`  
_L94-129_
- inherits: `FGlobalShader`
- desc: Compute shader to convert packed 8 bits RGB to RGBA 8bits
- L109 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FYUV10Bit422ToRGBACS, FGlobalShader);`
- L122 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L128 _public prototype_ `FYUV10Bit422ToRGBACS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGBufferRef YUVBuffer, FRDGTextureRef OutputTexture, const FMatrix& ColorTransform, const FVector& YUVOffset, int32 TotalElementCount, int32 BufferLineCount);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FYUV10Bit422ToRGBACS::FYUV10Bit422LEBuffer`  
`struct FYUV10Bit422LEBuffer`  
_L99-106_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf
- L101 _public member_ `uint32 DWord0;`
- L102 _public member_ `uint32 DWord1;`
- L103 _public member_ `uint32 DWord2;`
- L104 _public member_ `uint32 DWord3;`
- L105 _public member_ `uint32 DWord4;`

#### class `UE::RivermaxShaders::FRGBToYUV10Bit422LittleEndianCS`  
`class FRGBToYUV10Bit422LittleEndianCS : public FGlobalShader`  
_L136-173_
- inherits: `FGlobalShader`
- desc: Compute shader to convert RGB to packed YUV422 10 bits little endian This shader expects a single texture in PF_A2B10G10R10 format.
- L151 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FRGBToYUV10Bit422LittleEndianCS, FGlobalShader);`
- L166 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L172 _public prototype_ `FRGBToYUV10Bit422LittleEndianCS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGTextureRef SourceTexture, const FIntPoint& CaptureSize, const FIntRect& SourceViewRect, const FIntPoint& OutputSize, const FMatrix& ColorTransform, const FVector& YUVOffset, bool bDoLinearToSrgb, FRDGBufferRef OutputBuffer);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FRGBToYUV10Bit422LittleEndianCS::FYUV10Bit422LEBuffer`  
`struct FYUV10Bit422LEBuffer`  
_L140-147_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf
- L142 _public member_ `uint32 DWord0;`
- L143 _public member_ `uint32 DWord1;`
- L144 _public member_ `uint32 DWord2;`
- L145 _public member_ `uint32 DWord3;`
- L146 _public member_ `uint32 DWord4;`

#### class `UE::RivermaxShaders::FRGB8BitToRGBA8CS`  
`class FRGB8BitToRGBA8CS : public FGlobalShader`  
_L178-211_
- inherits: `FGlobalShader`
- desc: Compute shader to convert packed 8 bits RGB to RGBA 8bits
- L192 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FRGB8BitToRGBA8CS, FGlobalShader);`
- L204 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L210 _public prototype_ `FRGB8BitToRGBA8CS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGBufferRef RGBBuffer, FRDGTextureRef OutputTexture, int32 TotalElementCount, int32 BufferLineCount);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FRGB8BitToRGBA8CS::FRGB8BitBuffer`  
`struct FRGB8BitBuffer`  
_L184-189_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf For 8bit output, it's 3 bytes per pixels. To align with 4 bytes (32bit) we use 12 bytes (4 pixels) per output
- L186 _public member_ `uint32 DWord0;`
- L187 _public member_ `uint32 DWord1;`
- L188 _public member_ `uint32 DWord2;`

#### class `UE::RivermaxShaders::FRGBToRGB8BitCS`  
`class FRGBToRGB8BitCS : public FGlobalShader`  
_L216-255_
- inherits: `FGlobalShader`
- desc: Compute shader to convert RGBA to packed 8 bits RGB
- L231 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FRGBToRGB8BitCS, FGlobalShader);`
- L248 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L254 _public prototype_ `FRGBToRGB8BitCS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGTextureRef SourceTexture, const FIntPoint& CaptureSize, const FIntRect& SourceViewRect, const FIntPoint& OutputSize, FRDGBufferRef OutputBuffer);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FRGBToRGB8BitCS::FRGB8BitBuffer`  
`struct FRGB8BitBuffer`  
_L222-227_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf For 8bit output, it's 3 bytes per pixels. To align with 4 bytes (32bit) we use 12 bytes (4 pixels) per output
- L224 _public member_ `uint32 DWord0;`
- L225 _public member_ `uint32 DWord1;`
- L226 _public member_ `uint32 DWord2;`

#### class `UE::RivermaxShaders::FRGBToRGB10BitCS`  
`class FRGBToRGB10BitCS : public FGlobalShader`  
_L260-298_
- inherits: `FGlobalShader`
- desc: Compute shader to convert RGBA to packed 10 bits RGB
- L274 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FRGBToRGB10BitCS, FGlobalShader);`
- L291 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L297 _public prototype_ `FRGBToRGB10BitCS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGTextureRef SourceTexture, const FIntPoint& CaptureSize, const FIntRect& SourceViewRect, const FIntPoint& OutputSize, FRDGBufferRef OutputBuffer);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FRGBToRGB10BitCS::FRGB10BitBuffer`  
`struct FRGB10BitBuffer`  
_L267-270_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf 10 bits per channel, 30 bits per pixel. Aligns on 15 32bits -> 480bits -> 16RGB10 pixels 2110-20 says it's 4 pixels per pgroup.
- L269 _public member_ `uint32 DWords[15];`

#### class `UE::RivermaxShaders::FRGB10BitToRGBA10CS`  
`class FRGB10BitToRGBA10CS : public FGlobalShader`  
_L303-335_
- inherits: `FGlobalShader`
- desc: Compute shader to convert packed 10 bits RGB to RGBA
- L316 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FRGB10BitToRGBA10CS, FGlobalShader);`
- L328 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L334 _public prototype_ `FRGB10BitToRGBA10CS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGBufferRef RGBBuffer, FRDGTextureRef OutputTexture, int32 TotalElementCount, int32 BufferLineCount);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FRGB10BitToRGBA10CS::FRGB10BitBuffer`  
`struct FRGB10BitBuffer`  
_L310-313_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf 10 bits per channel, 30 bits per pixel. Aligns on 15 32bits -> 480bits -> 16RGB10 pixels 2110-20 says it's 4 pixels per pgroup.
- L312 _public member_ `uint32 DWords[15];`

#### class `UE::RivermaxShaders::FRGBToRGB12BitCS`  
`class FRGBToRGB12BitCS : public FGlobalShader`  
_L340-378_
- inherits: `FGlobalShader`
- desc: Compute shader to convert RGBA to packed 12 bits RGB
- L354 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FRGBToRGB12BitCS, FGlobalShader);`
- L371 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L377 _public prototype_ `FRGBToRGB12BitCS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGTextureRef SourceTexture, const FIntPoint& CaptureSize, const FIntRect& SourceViewRect, const FIntPoint& OutputSize, FRDGBufferRef OutputBuffer);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FRGBToRGB12BitCS::FRGB12BitBuffer`  
`struct FRGB12BitBuffer`  
_L347-350_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf 12 bits per channel, 36 bits per pixel. Aligns on 9 32bits -> 288bits -> 8x RGB12 pixels 2110-20 says it's 2 pixels per pgroup.
- L349 _public member_ `uint32 DWords[9];`

#### class `UE::RivermaxShaders::FRGB12BitToRGBA12CS`  
`class FRGB12BitToRGBA12CS : public FGlobalShader`  
_L383-415_
- inherits: `FGlobalShader`
- desc: Compute shader to convert packed 12 bits RGB to RGBA
- L396 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FRGB12BitToRGBA12CS, FGlobalShader);`
- L408 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L414 _public prototype_ `FRGB12BitToRGBA12CS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGBufferRef RGBBuffer, FRDGTextureRef OutputTexture, int32 TotalElementCount, int32 BufferLineCount);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FRGB12BitToRGBA12CS::FRGB12BitBuffer`  
`struct FRGB12BitBuffer`  
_L390-393_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf 12 bits per channel, 36 bits per pixel. Aligns on 9 32bits -> 288bits -> 8x RGB12 pixels 2110-20 says it's 2 pixels per pgroup.
- L392 _public member_ `uint32 DWords[9];`

#### class `UE::RivermaxShaders::FRGBToRGB16fCS`  
`class FRGBToRGB16fCS : public FGlobalShader`  
_L420-457_
- inherits: `FGlobalShader`
- desc: Compute shader to convert RGBA to Float16 RGB
- L426 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FRGBToRGB16fCS, FGlobalShader);`
- L450 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L456 _public prototype_ `FRGBToRGB16fCS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGTextureRef SourceTexture, const FIntPoint& CaptureSize, const FIntRect& SourceViewRect, const FIntPoint& OutputSize, FRDGBufferRef OutputBuffer);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FRGBToRGB16fCS::FRGB16fBuffer`  
`struct FRGB16fBuffer`  
_L430-433_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf To align on 32bits, use 2 pixels (16 bit * 3 * 2 = 3x32bits)
- L432 _public member_ `uint32 DWords[3];`

#### class `UE::RivermaxShaders::FRGB16fBitToRGBA16fCS`  
`class FRGB16fBitToRGBA16fCS : public FGlobalShader`  
_L462-493_
- inherits: `FGlobalShader`
- desc: Compute shader to convert 16 bits float RGB to RGBA
- L474 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FRGB16fBitToRGBA16fCS, FGlobalShader);`
- L486 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Called by the engine to determine which permutations to compile for this shader
- L492 _public prototype_ `FRGB16fBitToRGBA16fCS::FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, FRDGBufferRef RGBBuffer, FRDGTextureRef OutputTexture, int32 TotalElementCount, int32 BufferLineCount);` — Allocates and setup shader parameter in the incoming graph builder

#### struct `UE::RivermaxShaders::FRGB16fBitToRGBA16fCS::FRGB16fBuffer`  
`struct FRGB16fBuffer`  
_L468-471_
- desc: Structure definition to match StructuredBuffer in RivermaxShaders.usf To align on 32bits, use 2 pixels (16 bit * 3 * 2 = 3x32bits)
- L470 _public member_ `uint32 DWords[3];`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RivermaxShaders` (scope `UE`)
