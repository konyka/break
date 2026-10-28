# Plugins / TmvMediaShaders

- module root: `Plugins/Media/TmvMedia/Source/TmvMediaShaders`
- headers: 6; symbols: 21
- symbol kinds: class=5, enum=1, enumerator=4, function=1, member=2, prototype=5, struct=1, typedef=2
- PrivateDependencyModuleNames: Core, Projects, RHI, RenderCore
- PublicDependencyModuleNames: 

### `Plugins/Media/TmvMedia/Source/TmvMediaShaders/Internal/TmvMediaShaderParameters.h` (Internal)
_(no declarations extracted)_

### `Plugins/Media/TmvMedia/Source/TmvMediaShaders/Internal/TmvStructuredBufferSwizzlingShader.h` (Internal)


#### class `FTmvSwizzleVS`  
`class FTmvSwizzleVS : public FGlobalShader`  
_L12-21_
- inherits: `FGlobalShader`
- desc: The vertex shader used by DrawScreenPass to draw a rectangle.
- L17 _public prototype_ `FTmvSwizzleVS() = default;`
- L18 _public function_ `FTmvSwizzleVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)`

#### enum `ETmvSwizzleBufferLayouts`  
`enum class ETmvSwizzleBufferLayouts`  
_L24-34_
- desc: Define the buffer memory layout (depend on decoder).
- L27 _public enumerator_ `TiledPartial = 0` — The buffer contains a subset of tiles. Requires a separate tile mapping buffer.
- L29 _public enumerator_ `TiledFull = 1` — The buffer contains a full set of tiles for the frame.
- L31 _public enumerator_ `PlanarFull = 2` — The buffer planar component buffers (not tiled).
- L33 _public enumerator_ `Count`

#### class `FTmvStructuredBufferSwizzlePS`  
`class FTmvStructuredBufferSwizzlePS : public FGlobalShader`  
_L39-70_
- inherits: `FGlobalShader`
- desc: Pixel shader swizzle multi-component planar or tiled buffer into a packed RGBA texture.
- L42 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FTmvStructuredBufferSwizzlePS, FGlobalShader);`
- L53 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FNumComponents, FBufferLayout, FElementFormat>;`

### `Plugins/Media/TmvMedia/Source/TmvMediaShaders/Internal/TmvTextureBufferSwizzlingShader.h` (Internal)


#### class `FTmvTextureBufferSwizzlePS`  
`class FTmvTextureBufferSwizzlePS : public FGlobalShader`  
_L13-30_
- inherits: `FGlobalShader`
- desc: Pixel shader swizzle multi-component planar texture buffer into a packed RGBA texture.
- L16 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FTmvTextureBufferSwizzlePS, FGlobalShader);`
- L20 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FNumComponents>;`

### `Plugins/Media/TmvMedia/Source/TmvMediaShaders/Internal/TmvTextureYuvConvertShader.h` (Internal)


#### class `FTmvTextureYuvConverterPS`  
`class FTmvTextureYuvConverterPS : public FGlobalShader`  
_L13-26_
- inherits: `FGlobalShader`
- desc: Pixel shader to convert an RGBA (media) texture back to YUVA.
- L16 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FTmvTextureYuvConverterPS, FGlobalShader);`

### `Plugins/Media/TmvMedia/Source/TmvMediaShaders/Private/TmvMediaShadersModule.h` (Private)


#### class `FTmvMediaShadersModule`  
`class FTmvMediaShadersModule : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- desc: Module used to define TMV media shaders used for pixel format conversion
- L14 _public prototype_ `virtual void StartupModule() override;`

### `Plugins/Media/TmvMedia/Source/TmvMediaShaders/Public/TmvMediaShaderDefines.h` (Public)


#### struct `FTmvMediaShaderTileDesc`  
`struct FTmvMediaShaderTileDesc`  
_L13-20_
- desc: Defines the memory layout of a planar tile buffer. When using tiled memory layout, the size of tiles per plane is defined in FTmvMediaFrameMipInfo::Planes (FTmvMediaFramePlaneInfo). @remark For YUV color components, each plane can have different strides because of chroma subsampling.
- L16 _public member_ `FIntVector4 Offsets;` — Offset of each component plane. Includes padding if any.
- L19 _public member_ `FIntVector4 Strides;` — Stride of each component plane.
