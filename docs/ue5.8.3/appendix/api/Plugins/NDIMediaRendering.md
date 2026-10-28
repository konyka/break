# Plugins / NDIMediaRendering

- module root: `Plugins/Media/NDIMedia/Source/NDIMediaRendering`
- headers: 2; symbols: 45
- symbol kinds: class=4, function=12, member=22, prototype=4, struct=3
- PrivateDependencyModuleNames: Core, Projects, RHI, RenderCore
- PublicDependencyModuleNames: 

### `Plugins/Media/NDIMedia/Source/NDIMediaRendering/Internal/NDIMediaShaders.h` (Internal)


#### class `FNDIMediaShaderUYVAtoBGRAPS`  
`class FNDIMediaShaderUYVAtoBGRAPS : public FGlobalShader`  
_L18-65_
- inherits: `FGlobalShader`
- desc: Pixel shader for ndi media sample converter. Converts UYVY-A 2 planes format. The first plane is a regular UYVY 4:2:2 followed by a alpha channel plane.
- L23 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& InParameters)`
- L28 _public function_ `FNDIMediaShaderUYVAtoBGRAPS()`
- L31 _public function_ `FNDIMediaShaderUYVAtoBGRAPS(const ShaderMetaType::CompiledShaderInitializerType& InInitializer) : FGlobalShader(InInitializer)`
- L64 _public prototype_ `void SetParameters(FRHIBatchedShaderParameters& InBatchedParameters, const FParameters& InParameters);`

#### struct `FNDIMediaShaderUYVAtoBGRAPS::FParameters`  
`struct FParameters`  
_L35-62_
- L37 _public function_ `FParameters( const TRefCountPtr<FRHITexture>& InYUVTexture, const TRefCountPtr<FRHITexture>& InAlphaTexture, const FIntPoint& InOutputSize, const FMatrix44f& InColorTransform, UE::Color::EEncoding InEncoding, const FMatrix44f& InCSTransform, MediaShaders::EToneMapMethod InToneMapMethod) : YUVTexture(InYUVTexture) , AlphaTexture(InAlphaTexture) , OutputSize(InOutputSize) , ColorTransform(InColorTransform) , Encoding(InEncoding) , CSTransform(InCSTransform) , ToneMapMethod(InToneMapMethod)`
- L55 _public member_ `TRefCountPtr<FRHITexture> YUVTexture;`
- L56 _public member_ `TRefCountPtr<FRHITexture> AlphaTexture;`
- L57 _public member_ `FIntPoint OutputSize;`
- L58 _public member_ `FMatrix44f ColorTransform;`
- L59 _public member_ `UE::Color::EEncoding Encoding;`
- L60 _public member_ `FMatrix44f CSTransform;`
- L61 _public member_ `MediaShaders::EToneMapMethod ToneMapMethod;`

#### class `FNDIMediaShaderP216toBGRAPS`  
`class FNDIMediaShaderP216toBGRAPS : public FGlobalShader`  
_L71-118_
- inherits: `FGlobalShader`
- desc: Pixel shader for ndi media sample converter. Converts P216 16-bit 4:2:2 two-plane format (Y + UV) to RGBA.
- L76 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& InParameters)`
- L81 _public function_ `FNDIMediaShaderP216toBGRAPS()`
- L84 _public function_ `FNDIMediaShaderP216toBGRAPS(const ShaderMetaType::CompiledShaderInitializerType& InInitializer) : FGlobalShader(InInitializer)`
- L117 _public prototype_ `void SetParameters(FRHIBatchedShaderParameters& InBatchedParameters, const FParameters& InParameters);`

#### struct `FNDIMediaShaderP216toBGRAPS::FParameters`  
`struct FParameters`  
_L88-115_
- L90 _public function_ `FParameters( const TRefCountPtr<FRHITexture>& InYTexture, const TRefCountPtr<FRHITexture>& InUVTexture, const FIntPoint& InOutputSize, const FMatrix44f& InColorTransform, UE::Color::EEncoding InEncoding, const FMatrix44f& InCSTransform, MediaShaders::EToneMapMethod InToneMapMethod) : YTexture(InYTexture) , UVTexture(InUVTexture) , OutputSize(InOutputSize) , ColorTransform(InColorTransform) , Encoding(InEncoding) , CSTransform(InCSTransform) , ToneMapMethod(InToneMapMethod)`
- L108 _public member_ `TRefCountPtr<FRHITexture> YTexture;`
- L109 _public member_ `TRefCountPtr<FRHITexture> UVTexture;`
- L110 _public member_ `FIntPoint OutputSize;`
- L111 _public member_ `FMatrix44f ColorTransform;`
- L112 _public member_ `UE::Color::EEncoding Encoding;`
- L113 _public member_ `FMatrix44f CSTransform;`
- L114 _public member_ `MediaShaders::EToneMapMethod ToneMapMethod;`

#### class `FNDIMediaShaderPA16toBGRAPS`  
`class FNDIMediaShaderPA16toBGRAPS : public FGlobalShader`  
_L124-174_
- inherits: `FGlobalShader`
- desc: Pixel shader for ndi media sample converter. Converts PA16 16-bit 4:2:2 three-plane format (Y + UV + A) to RGBA.
- L129 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& InParameters)`
- L134 _public function_ `FNDIMediaShaderPA16toBGRAPS()`
- L137 _public function_ `FNDIMediaShaderPA16toBGRAPS(const ShaderMetaType::CompiledShaderInitializerType& InInitializer) : FGlobalShader(InInitializer)`
- L173 _public prototype_ `void SetParameters(FRHIBatchedShaderParameters& InBatchedParameters, const FParameters& InParameters);`

#### struct `FNDIMediaShaderPA16toBGRAPS::FParameters`  
`struct FParameters`  
_L141-171_
- L143 _public function_ `FParameters( const TRefCountPtr<FRHITexture>& InYTexture, const TRefCountPtr<FRHITexture>& InUVTexture, const TRefCountPtr<FRHITexture>& InAlphaTexture, const FIntPoint& InOutputSize, const FMatrix44f& InColorTransform, UE::Color::EEncoding InEncoding, const FMatrix44f& InCSTransform, MediaShaders::EToneMapMethod InToneMapMethod) : YTexture(InYTexture) , UVTexture(InUVTexture) , AlphaTexture(InAlphaTexture) , OutputSize(InOutputSize) , ColorTransform(InColorTransform) , Encoding(InEncoding) , CSTransform(InCSTransform) , ToneMapMethod(InToneMapMethod)`
- L163 _public member_ `TRefCountPtr<FRHITexture> YTexture;`
- L164 _public member_ `TRefCountPtr<FRHITexture> UVTexture;`
- L165 _public member_ `TRefCountPtr<FRHITexture> AlphaTexture;`
- L166 _public member_ `FIntPoint OutputSize;`
- L167 _public member_ `FMatrix44f ColorTransform;`
- L168 _public member_ `UE::Color::EEncoding Encoding;`
- L169 _public member_ `FMatrix44f CSTransform;`
- L170 _public member_ `MediaShaders::EToneMapMethod ToneMapMethod;`

### `Plugins/Media/NDIMedia/Source/NDIMediaRendering/Private/NDIMediaRenderingModule.h` (Private)


#### class `FNDIMediaRenderingModule`  
`class FNDIMediaRenderingModule : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- desc: Module used to define NDI media shaders used for pixel format conversion
- L14 _public prototype_ `virtual void StartupModule() override;`
