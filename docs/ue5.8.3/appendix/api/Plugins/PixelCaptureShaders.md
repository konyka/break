# Plugins / PixelCaptureShaders

- module root: `Plugins/Media/PixelCapture/Source/PixelCaptureShaders`
- headers: 1; symbols: 10
- symbol kinds: class=1, macro=1, member=6, prototype=1, struct=1
- PrivateDependencyModuleNames: Core, Engine, Projects, RHI, RenderCore
- PublicDependencyModuleNames: 

### `Plugins/Media/PixelCapture/Source/PixelCaptureShaders/Public/RGBToYUVShader.h` (Public)


#### struct `FRGBToYUVShaderParameters`  
`struct FRGBToYUVShaderParameters`  
_L12-22_
- L14 _public member_ `FTextureRHIRef SourceTexture;`
- L16 _public member_ `FIntPoint DestPlaneYDimensions;`
- L17 _public member_ `FIntPoint DestPlaneUVDimensions;`
- L19 _public member_ `FUnorderedAccessViewRHIRef DestPlaneY;`
- L20 _public member_ `FUnorderedAccessViewRHIRef DestPlaneU;`
- L21 _public member_ `FUnorderedAccessViewRHIRef DestPlaneV;`

#### class `FRGBToYUVShader`  
`class FRGBToYUVShader`  
_L24-28_
- L27 _public prototype_ `static void Dispatch(FRHICommandListImmediate& RHICmdList, const FRGBToYUVShaderParameters& InParameters);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PIXELCAPTURESHADERS_API`
