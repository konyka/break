# Plugins / DisplayClusterShaders

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders`
- headers: 27; symbols: 336
- symbol kinds: class=18, delegate=1, enum=7, enumerator=30, function=76, macro=1, member=90, prototype=95, struct=17, typedef=1
- PrivateDependencyModuleNames: DisplayCluster, DisplayClusterWarp, RHI, Renderer, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Projects, RenderCore

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/DisplayClusterShadersLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterShaders, Log, All);` — Plugin-wide log categories
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterShaders, Log, All);` — Plugin-wide log categories

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/DisplayClusterShadersModule.h` (Private)


#### class `FDisplayClusterShadersModule`  
`class FDisplayClusterShadersModule : public IDisplayClusterShaders`  
_L7-34_
- inherits: `IDisplayClusterShaders`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `virtual bool RenderWarpBlend_MPCDI(FRHICommandListImmediate& RHICmdList, const FDisplayClusterShaderParameters_WarpBlend& InWarpBlendParameters) const override;`
- L20 _public prototype_ `virtual bool RenderWarpBlend_ICVFX(FRHICommandListImmediate& RHICmdList, const FDisplayClusterShaderParameters_WarpBlend& InWarpBlendParameters, const FDisplayClusterShaderParameters_ICVFX& InICVFXParameters) const override;`
- L21 _public function_ `virtual bool RenderPreprocess_UVLightCards(FRHICommandListImmediate& RHICmdList, FSceneInterface* InScene, FRenderTarget* InRenderTarget, float ProjectionPlaneSize, bool bRenderFinalColor) const override`
- L22 _public prototype_ `virtual bool RenderPreprocess_UVLightCards(FRHICommandListImmediate& RHICmdList, FSceneInterface* InScene, FRenderTarget* InRenderTarget, const FDisplayClusterShaderParameters_UVLightCards& InParameters) const override;`
- L23 _public prototype_ `virtual bool RenderPostprocess_OutputRemap(FRHICommandListImmediate& RHICmdList, FRHITexture* InSourceTexture, FRHITexture* InRenderTargetableDestTexture, const IDisplayClusterRender_MeshComponentProxy& MeshProxy) const override;`
- L24 _public prototype_ `virtual bool RenderPostprocess_Blur(FRHICommandListImmediate& RHICmdList, FRHITexture* InSourceTexture, FRHITexture* InRenderTargetableDestTexture, const FDisplayClusterShaderParameters_PostprocessBlur& InSettings) const override;`
- L25 _public prototype_ `virtual bool GenerateMips(FRHICommandListImmediate& RHICmdList, FRHITexture* InOutMipsTexture, const FDisplayClusterShaderParameters_GenerateMips& InSettings) const override;`
- L26 _public prototype_ `virtual void AddLinearToPQPass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_MediaPQ& Parameters) const override;`
- L27 _public prototype_ `virtual void AddPQToLinearPass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_MediaPQ& Parameters) const override;`
- L28 _public prototype_ `virtual void AddDrawOverlayPass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_Overlay& Parameters) const override;`
- L29 _public prototype_ `virtual void AddTransformTexturePass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_TransformTexture& Parameters) const override;`
- L31 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> CreateTextureUtils_RenderThread(FRHICommandListImmediate& RHICmdList) const override;`
- L32 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> CreateTextureUtils_RenderThread(FRDGBuilder& GraphBuilder) const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/DisplayClusterShadersTextureUtils.h` (Private)


#### class `FDisplayClusterShadersTextureUtils`  
`class FDisplayClusterShadersTextureUtils : public IDisplayClusterShadersTextureUtils , public TSharedFromThis<FDisplayClusterShadersTextureUtils>`  
_L12-181_
- inherits: `IDisplayClusterShadersTextureUtils,TSharedFromThis<FDisplayClusterShadersTextureUtils>`
- desc: Texture utils class for nDisplay.
- L17 _public prototype_ `virtual ~FDisplayClusterShadersTextureUtils() = default;`
- L24 _public prototype_ `static TSharedRef<IDisplayClusterShadersTextureUtils> CreateTextureUtils_RenderThread(FRHICommandListImmediate& RHICmdList);` — Return new instance of the resource utils. @param RHICmdList   - RHI API
- L30 _public prototype_ `static TSharedRef<IDisplayClusterShadersTextureUtils> CreateTextureUtils_RenderThread(FRDGBuilder& GraphBuilder);` — Return new instance of the resource utils. @param GraphBuilder - RDG builder
- L35 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> ResolveTextureContext(const FDisplayClusterShadersTextureViewportContext& Input, const FDisplayClusterShadersTextureViewportContext& Output) override;`
- L36 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> ResolveTextureContext(const FDisplayClusterShadersTextureUtilsSettings& InSettings, const FDisplayClusterShadersTextureViewportContext& Input, const FDisplayClusterShadersTextureViewportContext& Output) override;`
- L38 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> Resolve() override;`
- L39 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> Resolve(const FDisplayClusterShadersTextureUtilsSettings& Settings) override;`
- L41 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> ForEachContextByPredicate(TFunctionDisplayClusterShaders_TextureContextIterator&& InFunction) override;`
- L42 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> ForEachContextByPredicate(const FDisplayClusterShadersTextureUtilsSettings& Settings, TFunctionDisplayClusterShaders_TextureContextIterator&& InFunction) override;`
- L44 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetInput(const FDisplayClusterShadersTextureViewport& InTextureViewport, const int32 InContextNum = INDEX_NONE) override;`
- L45 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetOutput(const FDisplayClusterShadersTextureViewport& InTextureViewport, const int32 InContextNum = INDEX_NONE) override;`
- L47 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetInput(const IDisplayClusterViewportProxy* InViewportProxy, const EDisplayClusterViewportResourceType InResourceType, const int32 InContextNum = INDEX_NONE) override;`
- L48 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetOutput(const IDisplayClusterViewportProxy* InViewportProxy, const EDisplayClusterViewportResourceType InResourceType,const int32 InContextNum = INDEX_NONE) override;`
- L51 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetInputEncoding(const FDisplayClusterColorEncoding& InColorEncoding) override;`
- L52 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetOutputEncoding(const FDisplayClusterColorEncoding& InColorEncoding) override;`
- L54 _public function_ `virtual const FDisplayClusterShadersTextureParameters& GetInputTextureParameters() const override`
- L58 _public function_ `virtual const FDisplayClusterShadersTextureParameters& GetOutputTextureParameters() const override`
- L67 _public function_ `virtual bool ShouldUseRDG() const` — Return true if RDG is required.
- L81 _public function_ `virtual bool TransitionAndCopyTexture( const FDisplayClusterShadersTextureViewport& Input, const FDisplayClusterShadersTextureViewport& Output, const FDisplayClusterShadersTextureUtilsSettings& Settings)` — Implements Transition and copy @param Input    - Input texture with rect @param Output   - Output texture with rect @param Settings - current settings @return false, if it isn't possible
- L98 _public function_ `virtual bool ResampleColorEncodingCopyRect( const FDisplayClusterShadersTextureViewportContext& Input, const FDisplayClusterShadersTextureViewportContext& Output, const FDisplayClusterShadersTextureUtilsSettings& Settings)` — Implements resample shader @param Input    - Input texture with rect @param Output   - Output texture with rect @param Settings - current settings @return false, if it isn't possible
- L114 _public function_ `virtual bool CloneTextureViewportResourceForRenderPass( FDisplayClusterShadersTextureViewport& OutTextureViewport, const FDisplayClusterShadersTextureViewport& InTextureViewport, const TCHAR* InDebugName)` — Create a new input texture from the output and copy the image as well. @param OutTextureViewport - (out) The new texture @param InTextureViewport  - (in) the source texture to be clone (size and format) @param InDebugName - (opt) texture debug name @return true on success.
- L125 _public function_ `virtual bool InitializeTextureViewportForRenderPass( FDisplayClusterShadersTextureViewport& InOutTextureViewport, const TCHAR* InDebugName)` — Update texture viewport data for render pass return false if error
- L141 _public prototype_ `virtual bool ImplementTextureContextResolve( const FDisplayClusterShadersTextureViewportContext& Input, const FDisplayClusterShadersTextureViewportContext& Output, const FDisplayClusterShadersTextureUtilsSettings& Settings);` — Implements texture context resolving @param Input    - Input texture with rect @param Output   - Output texture with rect @param Settings - current settings @return false, if it isn't possible
- L154 _public prototype_ `static FDisplayClusterShadersTextureParameters GetTextureParametersFromViewport( const IDisplayClusterViewportProxy* InViewportProxy, const EDisplayClusterViewportResourceType InResourceType);` — Get texture parameter from the nDisplay viewport resourece @param InViewportProxy  - viewport proxy object with resources to retrieve @param InResourceType   - Type of the viewport resource @return themself
- L164 _public prototype_ `bool ShouldUseResampleShader( const FDisplayClusterShadersTextureViewportContext& InputTextureContext, const FDisplayClusterShadersTextureViewportContext& OutputTextureContext, const FDisplayClusterShadersTextureUtilsSettings& Settings) const;` — Returns true if a resampling shader should be used to copy this texture. @param InputTextureContext  - input texture context @param OutputTextureContext - output texture context @param Settings             - current settings
- L171 _public prototype_ `void ImplForEachContextByPredicate( const FDisplayClusterShadersTextureUtilsSettings& Settings, TFunctionDisplayClusterShaders_TextureContextIterator&& TextureContextIteratorFunc);` — Iterate through contexts matching these settings.
- L177 _protected member_ `FDisplayClusterShadersTextureParameters InputTextureParameters;` — Input textures parameters.
- L180 _protected member_ `FDisplayClusterShadersTextureParameters OutputTextureParameters;` — Output textures parameters.

#### class `FDisplayClusterShadersRHITextureUtils`  
`class FDisplayClusterShadersRHITextureUtils : public FDisplayClusterShadersTextureUtils`  
_L186-243_
- inherits: `FDisplayClusterShadersTextureUtils`
- desc: RDI:Texture utils class for nDisplay.
- L190 _public function_ `virtual ~FDisplayClusterShadersRHITextureUtils()`
- L203 _public function_ `FDisplayClusterShadersRHITextureUtils(FRHICommandListImmediate& InRHICmdList) : FDisplayClusterShadersTextureUtils(), RHICmdList(InRHICmdList)`
- L209 _public function_ `virtual FRDGBuilder& GetOrCreateRDGBuilder() override`
- L222 _public prototype_ `virtual bool TransitionAndCopyTexture(const FDisplayClusterShadersTextureViewport& Input, const FDisplayClusterShadersTextureViewport& Output, const FDisplayClusterShadersTextureUtilsSettings& Settings) override;`
- L223 _public prototype_ `virtual bool ResampleColorEncodingCopyRect(const FDisplayClusterShadersTextureViewportContext& Input, const FDisplayClusterShadersTextureViewportContext& Output, const FDisplayClusterShadersTextureUtilsSettings& Settings) override;`
- L224 _public prototype_ `virtual bool CloneTextureViewportResourceForRenderPass(FDisplayClusterShadersTextureViewport& OutTextureViewport, const FDisplayClusterShadersTextureViewport& InTextureViewport, const TCHAR* InDebugName) override;`
- L225 _public prototype_ `virtual bool InitializeTextureViewportForRenderPass(FDisplayClusterShadersTextureViewport& InOutTextureViewport, const TCHAR* InDebugName) override;`
- L227 _public function_ `virtual bool ShouldUseRDG() const override`
- L236 _private member_ `FRHICommandListImmediate& RHICmdList;` — Stored RHI api ref
- L239 _private member_ `TArray<TRefCountPtr<IPooledRenderTarget>> PooledRenderTargets;` — Temporary RTTs
- L242 _private member_ `TUniquePtr<FRDGBuilder> GraphBuilderUniquePtr;` — A GraphBuilder that can be created on request.

#### class `FDisplayClusterShadersRDGTextureUtils`  
`class FDisplayClusterShadersRDGTextureUtils : public FDisplayClusterShadersTextureUtils`  
_L248-281_
- inherits: `FDisplayClusterShadersTextureUtils`
- desc: RDG:Texture utils class for nDisplay.
- L252 _public prototype_ `virtual ~FDisplayClusterShadersRDGTextureUtils() = default;`
- L253 _public function_ `FDisplayClusterShadersRDGTextureUtils(FRDGBuilder& InGraphBuilder) : FDisplayClusterShadersTextureUtils(), GraphBuilder(InGraphBuilder)`
- L259 _public function_ `virtual FRDGBuilder& GetOrCreateRDGBuilder() override`
- L267 _public prototype_ `virtual bool TransitionAndCopyTexture(const FDisplayClusterShadersTextureViewport& Input, const FDisplayClusterShadersTextureViewport& Output, const FDisplayClusterShadersTextureUtilsSettings& Settings) override;`
- L268 _public prototype_ `virtual bool ResampleColorEncodingCopyRect(const FDisplayClusterShadersTextureViewportContext& Input, const FDisplayClusterShadersTextureViewportContext& Output, const FDisplayClusterShadersTextureUtilsSettings& Settings) override;`
- L269 _public prototype_ `virtual bool CloneTextureViewportResourceForRenderPass(FDisplayClusterShadersTextureViewport& OutTextureViewport, const FDisplayClusterShadersTextureViewport& InTextureViewport, const TCHAR* InDebugName) override;`
- L270 _public prototype_ `virtual bool InitializeTextureViewportForRenderPass(FDisplayClusterShadersTextureViewport& InOutTextureViewport, const TCHAR* InDebugName) override;`
- L271 _public function_ `virtual bool ShouldUseRDG() const override`
- L280 _private member_ `FRDGBuilder& GraphBuilder;` — Stored RDG api ref

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersCopyTexture.h` (Private)


#### class `FDisplayClusterShadersCopyTexture`  
`class FDisplayClusterShadersCopyTexture`  
_L12-76_
- desc: Implementation of texture copying.
- L24 _public prototype_ `static bool ColorEncodingCopyRect_RenderThread( FRHICommandListImmediate& RHICmdList, const FDisplayClusterShadersTextureViewportContext& Input, const FDisplayClusterShadersTextureViewportContext& Output, const FDisplayClusterShadersTextureUtilsSettings& InSettings);` — Implements texture copy via pixel shader. @param RHICmdList   - RHI API @param Input        - input texture context @param Output       - output texture context @param InSettings @return - true if success
- L39 _public prototype_ `static bool AddPassColorEncodingCopyRect_RenderThread( FRDGBuilder& GraphBuilder, const FDisplayClusterShadersTextureViewportContext& Input, const FDisplayClusterShadersTextureViewportContext& Output, const FDisplayClusterShadersTextureUtilsSettings& InSettings);` — Implements texture copy via pixel shader. @param RHICmdList   - RHI API @param Input        - input texture context @param Output       - output texture context @param InSettings @return - true if success
- L55 _public prototype_ `static bool TransitionAndCopyTexture_RenderThread( FRHICommandListImmediate& RHICmdList, const FDisplayClusterShadersTextureViewport& Input, const FDisplayClusterShadersTextureViewport& Output, const FDisplayClusterShadersTextureUtilsSettings& InSettings);` — Call TransitionAndCopyTexture() @param RHICmdList   - RHI API @param Input        - input texture context @param Output       - output texture context @param InSettings @return - true if success
- L71 _public prototype_ `static bool AddPassTransitionAndCopyTexture_RenderThread( FRDGBuilder& GraphBuilder, const FDisplayClusterShadersTextureViewport& Input, const FDisplayClusterShadersTextureViewport& Output, const FDisplayClusterShadersTextureUtilsSettings& InSettings);` — Call TransitionAndCopyTexture() @param GraphBuilder - RDG builder @param Input        - input texture context @param Output       - output texture context @param InSettings @return - true if success

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersGenerateMips.h` (Private)


#### class `FDisplayClusterShadersGenerateMips`  
`class FDisplayClusterShadersGenerateMips`  
_L11-15_
- L14 _public prototype_ `static bool GenerateMips(FRHICommandListImmediate& RHICmdList, FRHITexture* InOutMipsTexture, const FDisplayClusterShaderParameters_GenerateMips& InSettings);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersMedia.h` (Private)


#### class `FDisplayClusterShadersMedia`  
`class FDisplayClusterShadersMedia`  
_L14-23_
- desc: API for media shaders
- L19 _public prototype_ `static void AddLinearToPQPass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_MediaPQ& Parameters);` — Adds Linear-To-PQ encoding pass (API wrapper)
- L22 _public prototype_ `static void AddPQToLinearPass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_MediaPQ& Parameters);` — Adds PQ-To-Linear decoding pass (API wrapper)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersOverlay.h` (Private)


#### class `FDisplayClusterShadersOverlay`  
`class FDisplayClusterShadersOverlay`  
_L14-20_
- desc: API for overlay drawing
- L19 _public prototype_ `static void AddOverlayBlendingPass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_Overlay& Parameters);` — Draws overlay on top of the base texture (refer function arguments)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersPostprocess_Blur.h` (Private)


#### class `FDisplayClusterShadersPostprocess_Blur`  
`class FDisplayClusterShadersPostprocess_Blur`  
_L11-15_
- L14 _public prototype_ `static bool RenderPostprocess_Blur(FRHICommandListImmediate& RHICmdList, FRHITexture* InSourceTexture, FRHITexture* InRenderTargetableDestTexture, const FDisplayClusterShaderParameters_PostprocessBlur& InSettings);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersPostprocess_OutputRemap.h` (Private)


#### class `FDisplayClusterShadersPostprocess_OutputRemap`  
`class FDisplayClusterShadersPostprocess_OutputRemap`  
_L11-15_
- L14 _public prototype_ `static bool RenderPostprocess_OutputRemap(FRHICommandListImmediate& RHICmdList, FRHITexture* InSourceTexture, FRHITexture* InRenderTargetableDestTexture, const IDisplayClusterRender_MeshComponentProxy& MeshProxy);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersPreprocess_UVLightCards.h` (Private)


#### class `FDisplayClusterShadersPreprocess_UVLightCards`  
`class FDisplayClusterShadersPreprocess_UVLightCards`  
_L12-16_
- L15 _public prototype_ `static bool RenderPreprocess_UVLightCards(FRHICommandListImmediate& RHICmdList, FSceneInterface* InScene, FRenderTarget* InRenderTarget, const FDisplayClusterShaderParameters_UVLightCards& InParameters);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersTransformTexture.h` (Private)


#### class `FDisplayClusterShadersTransformTexture`  
`class FDisplayClusterShadersTransformTexture`  
_L14-29_
- desc: Encapsulates the texture transformation implementation
- L19 _public prototype_ `static void AddTransformTexturePass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_TransformTexture& Parameters);` — Adds a texture transformation pass with the specified parameters
- L22 _public prototype_ `static void CreateOutputTexture(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_TransformTexture& Parameters);` — Creates output texture based on the requested transformation
- L25 _public prototype_ `static FIntPoint GetOutputTextureSize(const FDisplayClusterShaderParameters_TransformTexture& Parameters);` — Finds output texture size according to the input data
- L28 _public prototype_ `static FVector4f GetTransformationMatrix(const FDisplayClusterShaderParameters_TransformTexture& Parameters);` — Returns transformation matrix according to the input data

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersWarpblend_ICVFX.h` (Private)


#### class `FDisplayClusterShadersWarpblend_ICVFX`  
`class FDisplayClusterShadersWarpblend_ICVFX`  
_L14-18_
- L17 _public prototype_ `static bool RenderWarpBlend_ICVFX(FRHICommandListImmediate& RHICmdList, const FDisplayClusterShaderParameters_WarpBlend& InWarpBlendParameters, const FDisplayClusterShaderParameters_ICVFX& InICVFXParameters);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define MAX_INNER_CAMERAS_AMOUNT 10`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersWarpblend_MPCDI.h` (Private)


#### class `FDisplayClusterShadersWarpblend_MPCDI`  
`class FDisplayClusterShadersWarpblend_MPCDI`  
_L11-15_
- L14 _public prototype_ `static bool RenderWarpBlend_MPCDI(FRHICommandListImmediate& RHICmdList, const FDisplayClusterShaderParameters_WarpBlend& InWarpBlendParameters);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/Blueprints/MPCDIGeometryData.h` (Public)


#### struct `FMPCDIGeometryImportData`  
`struct FMPCDIGeometryImportData`  
_L10-23_
- reflection: `USTRUCT(BlueprintType, Category = "MPCDI")`
- L16 _public member_ `int32 Width = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MPCDI")`
- L19 _public member_ `int32 Height = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MPCDI")`
- L22 _public member_ `TArray<FVector> Vertices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MPCDI")`

#### struct `FMPCDIGeometryExportData`  
`struct FMPCDIGeometryExportData`  
_L27-45_
- reflection: `USTRUCT(BlueprintType, Category = "MPCDI")`
- L33 _public member_ `TArray<FVector> Vertices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MPCDI")`
- L36 _public member_ `TArray<FVector> Normal;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MPCDI")`
- L39 _public member_ `TArray<FVector2D> UV;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MPCDI")`
- L42 _public member_ `TArray<int32> Triangles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MPCDI")`
- L44 _public prototype_ `void PostAddFace(int32 f0, int32 f1, int32 f2);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/Containers/DisplayClusterShaderContainers_TextureUtils.h` (Public)


#### enum `EDisplayClusterShaderTextureUtilsFlags`  
`enum class EDisplayClusterShaderTextureUtilsFlags : uint16`  
_L15-72_
- desc: Texture utiles flags.
- L17 _public enumerator_ `None = 0`
- L25 _public enumerator_ `UseOutputTextureAsInput = 1 << 0` — Use only output texture as the source and destination. A temporary texture will be used as the output texture, which is then copied back to the output texture. The input texture is not defined. Custom implementations must perform the copying from the output texture to the input texture themselves.
- L30 _public enumerator_ `InvertDirection = 1 << 1` — Invert direction: From `Output` to the `Input`
- L36 _public enumerator_ `DisableResize = 1 << 4` — Trim the input and output rect sizes to the same value. (The input rect size will be equal to the output rect size.)
- L41 _public enumerator_ `DisableResampleShader = 1 << 5` — When enabled, bypasses all shader processing and performs a simple texture copy only.
- L46 _public enumerator_ `DisableUpdateResourcesRectsForResolve = 1 << 6` — Dont update resource rects, they are expected to be user defined.
- L58 _public enumerator_ `EnableLinearAlphaFeather = 1 << 8` — Applies a linear alpha fade (feathering) to all edges of the rectangle. Requires specifying the feather (attenuation) width in pixels per side. NOTE: Only one alpha feathering mode(linear or smooth) should be enabled at a time. Although these are bit flags, do not combine multiple alpha feather modes. Note: Enabling this flag disables the use of EColorWriteMask, so all color channels will be written regardless of mask settings.
- L71 _public enumerator_ `EnableSmoothAlphaFeather = 1 << 9` — Enables smooth (cubic Hermite) alpha feathering (fade-out) on all sides of the rectangle. When set, alpha transitions smoothly from opaque to transparent along each edge using a smoothstep (S-curve) function. Requires additional parameters specifying the feather (attenuation) width in pixels for each side. NOTE: Only one alpha feathering mode(linear or smooth) should be enabled at a time. Although these are bit flags, do not combine multiple alpha feather modes. Note: Enabling this flag disables the use of EColorWriteMask, so all color channels will be written regardless of mask settings.

#### enum `EDisplayClusterShaderTextureUtilsOverrideAlpha`  
`enum class EDisplayClusterShaderTextureUtilsOverrideAlpha : uint8`  
_L76-89_
- desc: Alpha channel rendering mode.
- L79 _public enumerator_ `None = 0` — Alpha does not change
- L82 _public enumerator_ `Invert_Alpha` — Invert alpha channel
- L85 _public enumerator_ `Set_Alpha_One` — set alpha to One(1)
- L88 _public enumerator_ `Set_Alpha_Zero` — Set alpha to Zero(0)

#### struct `FDisplayClusterShadersTextureViewport`  
`struct FDisplayClusterShadersTextureViewport`  
_L94-146_
- desc: A container with a texture on which a rectangular area is located.
- L96 _public prototype_ `FDisplayClusterShadersTextureViewport() = default;`
- L98 _public function_ `FDisplayClusterShadersTextureViewport(FRHITexture* InTextureRHI, const TCHAR* InDebugName = nullptr) : TextureRHI(InTextureRHI), TextureRDG(nullptr), DebugName(InDebugName)`
- L101 _public function_ `FDisplayClusterShadersTextureViewport(FRDGTextureRef InTextureRDG) : TextureRHI(nullptr), TextureRDG(InTextureRDG)`
- L104 _public function_ `FDisplayClusterShadersTextureViewport(FRHITexture* InTextureRHI, const FIntRect& InTextureRect, const TCHAR* InDebugName = nullptr) : TextureRHI(InTextureRHI), TextureRDG(nullptr), Rect(InTextureRect), DebugName(InDebugName)`
- L107 _public function_ `FDisplayClusterShadersTextureViewport(FRDGTextureRef InTextureRDG, const FIntRect& InTextureRect) : TextureRHI(nullptr), TextureRDG(InTextureRDG), Rect(InTextureRect)`
- L110 _public function_ `FDisplayClusterShadersTextureViewport(const FScreenPassTexture& InScreenPass) : TextureRHI(nullptr), TextureRDG(InScreenPass.Texture), Rect(InScreenPass.ViewRect)`
- L114 _public function_ `inline bool IsValid() const` — Returns true if these parameters are valid.
- L120 _public function_ `inline FScreenPassTexture ToScreenPassTexture() const` — Convert to the ScreenPass texture type.
- L126 _public function_ `inline FScreenPassTextureViewport ToScreenPassTextureViewport() const` — Convert to the ScreenPass viewport type.
- L133 _public member_ `FRHITexture* TextureRHI = nullptr;` — RHI Texture. If this parameter is nullptr, the TextureRDG parameter is used.
- L136 _public member_ `FRDGTextureRef TextureRDG = nullptr;` — RDG texture.
- L139 _public member_ `bool bExternalTextureRDG = false;` — true if RDG texture external.
- L142 _public member_ `FIntRect Rect = { FIntPoint::ZeroValue, FIntPoint::ZeroValue };` — Texture sub-region
- L145 _public member_ `const TCHAR* DebugName = nullptr;` — Optional debug name for this resource, used to name the external RHI resource for RDG.

#### struct `FDisplayClusterShadersTextureParameters`  
`struct FDisplayClusterShadersTextureParameters`  
_L151-175_
- desc: A container with textures and their configurations to be used as input and output data.
- L154 _public function_ `bool IsValid() const` — Returns true if these parameters are valid.
- L171 _public member_ `TMap<uint32, FDisplayClusterShadersTextureViewport> TextureViewports;` — Textures of all viewport contexts. The default is context 0.
- L174 _public member_ `FDisplayClusterColorEncoding ColorEncoding;` — texture color space.

#### struct `FDisplayClusterShadersTextureUtilsSettings`  
`struct FDisplayClusterShadersTextureUtilsSettings`  
_L180-251_
- desc: Container with the texture utils settings
- L182 _public prototype_ `FDisplayClusterShadersTextureUtilsSettings() = default;`
- L184 _public function_ `FDisplayClusterShadersTextureUtilsSettings( const FDisplayClusterShadersTextureUtilsSettings& InSettigns, const EDisplayClusterShaderTextureUtilsFlags InFlags, const uint32 InDestSliceIndex = 0) : FDisplayClusterShadersTextureUtilsSettings(InSettigns)`
- L194 _public function_ `FDisplayClusterShadersTextureUtilsSettings(const EColorWriteMask InColorMask) : ColorMask(InColorMask)`
- L197 _public function_ `FDisplayClusterShadersTextureUtilsSettings( const FDisplayClusterShadersTextureUtilsSettings& InSettigns, const EColorWriteMask InColorMask) : FDisplayClusterShadersTextureUtilsSettings(InSettigns)`
- L205 _public function_ `FDisplayClusterShadersTextureUtilsSettings(const EDisplayClusterShaderTextureUtilsOverrideAlpha InOverrideAlpha) : OverrideAlpha(InOverrideAlpha)`
- L208 _public function_ `FDisplayClusterShadersTextureUtilsSettings( const EColorWriteMask InColorMask, const EDisplayClusterShaderTextureUtilsFlags InFlags, const uint32 InDestSliceIndex = 0) : ColorMask(InColorMask), Flags(InFlags), DestSliceIndex(InDestSliceIndex)`
- L214 _public function_ `FDisplayClusterShadersTextureUtilsSettings( const EDisplayClusterShaderTextureUtilsFlags InFlags, const FIntMarginSet& InSideMargins) : Flags(InFlags), SideMargins(InSideMargins)`
- L219 _public function_ `FDisplayClusterShadersTextureUtilsSettings( const EDisplayClusterShaderTextureUtilsFlags InFlags, const uint32 InDestSliceIndex = 0) : Flags(InFlags), DestSliceIndex(InDestSliceIndex)`
- L225 _public function_ `inline bool HasAnyFlags(const EDisplayClusterShaderTextureUtilsFlags InFlags) const`
- L230 _public function_ `inline void AddFlags(const EDisplayClusterShaderTextureUtilsFlags InFlags)`
- L237 _public member_ `EColorWriteMask ColorMask = EColorWriteMask::CW_RGBA;` — Color mask
- L240 _public member_ `EDisplayClusterShaderTextureUtilsFlags Flags = EDisplayClusterShaderTextureUtilsFlags::None;` — Additional flags.
- L243 _public member_ `EDisplayClusterShaderTextureUtilsOverrideAlpha OverrideAlpha = EDisplayClusterShaderTextureUtilsOverrideAlpha::None;` — Override alpha channel.
- L246 _public member_ `uint32 SourceSliceIndex = 0;` — Additional parameters for the FRHICopyTextureInfo.
- L247 _public member_ `uint32 DestSliceIndex = 0;`
- L250 _public member_ `FIntMarginSet SideMargins;` — Per-side margins in pixels.

#### struct `FDisplayClusterShadersTextureViewportContext`  
`struct FDisplayClusterShadersTextureViewportContext : public FDisplayClusterShadersTextureViewport`  
_L254-274_
- inherits: `FDisplayClusterShadersTextureViewport`
- desc: This container is used for IDisplayClusterShadersTextureUtils::ForEachContextByPredicate()
- L256 _public prototype_ `FDisplayClusterShadersTextureViewportContext() = default;`
- L258 _public function_ `FDisplayClusterShadersTextureViewportContext( const FDisplayClusterShadersTextureViewport& InTextureViewport, const uint32 InContextNum = 0) : FDisplayClusterShadersTextureViewport(InTextureViewport), ContextNum(InContextNum)`
- L263 _public function_ `FDisplayClusterShadersTextureViewportContext( const FDisplayClusterShadersTextureViewport& InTextureViewport, const FDisplayClusterColorEncoding& InColorEncoding, const uint32 InContextNum = 0) : FDisplayClusterShadersTextureViewport(InTextureViewport), ContextNum(InContextNum), ColorEncoding(InColorEncoding)`
- L270 _public member_ `uint32 ContextNum = 0;` — Texture context num.
- L273 _public member_ `FDisplayClusterColorEncoding ColorEncoding;` — texture color space.

#### Free symbols / members of external scopes

- L73 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterShaderTextureUtilsFlags);`
- L277 _typedef_ `using TFunctionDisplayClusterShaders_TextureContextIterator = TFunction<void( const FDisplayClusterShadersTextureViewportContext& Input, const FDisplayClusterShadersTextureViewportContext& Output)>;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/Containers/DisplayClusterShader_Enums.h` (Public)


#### enum `EDisplayClusterShaderParametersICVFX_ChromakeySource`  
`enum class EDisplayClusterShaderParametersICVFX_ChromakeySource : uint8`  
_L10-23_
- desc: Rendering mode for chromakey
- L13 _public enumerator_ `Disabled = 0` — Dont use chromakey
- L16 _public enumerator_ `FrameColor` — Render color over camera frame
- L19 _public enumerator_ `ChromakeyLayers` — Render specified layer from scene
- L22 _public enumerator_ `Default` — Use default value.

#### enum `EDisplayClusterShaderParametersICVFX_LightCardRenderMode`  
`enum class EDisplayClusterShaderParametersICVFX_LightCardRenderMode : uint8`  
_L28-37_
- desc: The rendering order of the lightcard layer
- L30 _public enumerator_ `None = 0`
- L33 _public enumerator_ `Under` — Render incamera frame over lightcard
- L36 _public enumerator_ `Over` — Over lightcard over incamera frame

#### enum `EDisplayClusterShaderParametersICVFX_CameraOverlappingRenderMode`  
`enum class EDisplayClusterShaderParametersICVFX_CameraOverlappingRenderMode : uint8`  
_L42-49_
- desc: Rendering mode for overlapping areas of camera projections
- L45 _public enumerator_ `None = 0` — Disabled
- L48 _public enumerator_ `FinalPass` — The overlapping area is rendered at the very end, on top of all the layers

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/IDisplayClusterShaders.h` (Public)


#### class `IDisplayClusterShaders`  
`class IDisplayClusterShaders : public IModuleInterface`  
_L30-186_
- inherits: `IModuleInterface`
- L33 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L36 _public prototype_ `virtual ~IDisplayClusterShaders() = default;`
- L45 _public function_ `static inline IDisplayClusterShaders& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L55 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L69 _public prototype_ `virtual bool RenderWarpBlend_MPCDI(FRHICommandListImmediate& RHICmdList, const FDisplayClusterShaderParameters_WarpBlend& InWarpBlendParameters) const = 0;` — Render warp&blend @param RHICmdList      - RHI command list @param InWarpBlendParameters - warp blend parameters @return - true if success
- L80 _public prototype_ `virtual bool RenderWarpBlend_ICVFX(FRHICommandListImmediate& RHICmdList, const FDisplayClusterShaderParameters_WarpBlend& InWarpBlendParameters, const FDisplayClusterShaderParameters_ICVFX& InICVFXParameters) const = 0;` — Render ICVFX warp&blend @param RHICmdList            - RHI command list @param InWarpBlendParameters - WarpBlend parameters @param InICVFXParameters     - ICVFX parameters @return - true if success
- L93 _public prototype_ `virtual bool RenderPreprocess_UVLightCards(FRHICommandListImmediate& RHICmdList, FSceneInterface* InScene, FRenderTarget* InRenderTarget, float ProjectionPlaneSize, bool bRenderFinalColor) const = 0;` — `UE_DEPRECATED(5.2, "Use version that takes FDisplayClusterShaderParameters_UVLightCards instead")` — Render UV light cards to texture that can be sampled by viewports to place light cards in UV space @param RHICmdList                    - RHI command list @param InScene                       - The scene the light cards live in @param InRenderTargetableDestTexture - Destination RTT texture @param ProjectionPlaneSize           - The size of the plane the UV light cards are projected to @return - true if success
- L105 _public prototype_ `virtual bool RenderPreprocess_UVLightCards(FRHICommandListImmediate& RHICmdList, FSceneInterface* InScene, FRenderTarget* InRenderTarget, const FDisplayClusterShaderParameters_UVLightCards& InParameters) const = 0;` — Render UV light cards to texture that can be sampled by viewports to place light cards in UV space @param RHICmdList                    - RHI command list @param InScene                       - The scene the light cards live in @param InRenderTarget                - Destination RTT texture @param InParameters                  - Parameters for the render @return - true if success
- L117 _public prototype_ `virtual bool RenderPostprocess_OutputRemap(FRHICommandListImmediate& RHICmdList, FRHITexture* InSourceTexture, FRHITexture* InRenderTargetableDestTexture, const IDisplayClusterRender_MeshComponentProxy& MeshProxy) const = 0;` — Render postprocess OutputRemap @param RHICmdList                    - RHI command list @param InSourceTexture -             - Source shader resource texture @param InRenderTargetableDestTexture - Destination RTT texture @param MeshProxy                     - mesh for output remapping @return - true if success
- L129 _public prototype_ `virtual bool RenderPostprocess_Blur(FRHICommandListImmediate& RHICmdList, FRHITexture* InSourceTexture, FRHITexture* InRenderTargetableDestTexture, const FDisplayClusterShaderParameters_PostprocessBlur& InSettings) const = 0;` — Render postprocess Blur @param RHICmdList                    - RHI command list @param InSourceTexture -             - Source shader resource texture @param InRenderTargetableDestTexture - Destination RTT texture @param InSettings                    - Blur pp settings @return - true if success
- L140 _public prototype_ `virtual bool GenerateMips(FRHICommandListImmediate& RHICmdList, FRHITexture* InOutMipsTexture, const FDisplayClusterShaderParameters_GenerateMips& InSettings) const = 0;` — Generate Mips texture @param RHICmdList       - RHI command list @param InOutMipsTexture - Mips textures with assigned mip0 @param InSettings       - mips settings @return - true if success
- L148 _public prototype_ `virtual void AddLinearToPQPass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_MediaPQ& Parameters) const = 0;` — Adds Linear-To-PQ encoding pass @param GraphBuilder - RDG builder @param Parameters   - Conversion parameters
- L156 _public prototype_ `virtual void AddPQToLinearPass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_MediaPQ& Parameters) const = 0;` — Adds PQ-To-Linear decoding pass (API wrapper) @param GraphBuilder - RDG builder @param Parameters   - Conversion parameters
- L164 _public prototype_ `virtual void AddDrawOverlayPass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_Overlay& Parameters) const = 0;` — Adds overlay drawing pass @param GraphBuilder - RDG builder @param Parameters   - Render parameters
- L172 _public prototype_ `virtual void AddTransformTexturePass(FRDGBuilder& GraphBuilder, const FDisplayClusterShaderParameters_TransformTexture& Parameters) const = 0;` — Adds a texture transformation pass @param GraphBuilder - RDG builder @param Parameters   - Render parameters
- L179 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> CreateTextureUtils_RenderThread(FRHICommandListImmediate& RHICmdList) const = 0;` — Return new instance of the resource utils. @param RHICmdList   - RHI API
- L185 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> CreateTextureUtils_RenderThread(FRDGBuilder& GraphBuilder) const = 0;` — Return new instance of the resource utils. @param GraphBuilder - RDG builder

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/IDisplayClusterShadersTextureUtils.h` (Public)


#### class `IDisplayClusterShadersTextureUtils`  
`class IDisplayClusterShadersTextureUtils`  
_L17-167_
- desc: Auxiliary Texture utils class for nDisplay.
- L21 _public prototype_ `virtual ~IDisplayClusterShadersTextureUtils() = default;` — Default destructor.
- L31 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetInput(const FDisplayClusterShadersTextureViewport& InTextureViewport, const int32 InContextNum = INDEX_NONE) = 0;` — Set the input texture viewport for the specified context. @parama InTextureViewport - texture viewport @param InContextNum       - (opt) context(eye)  number, otherwise all contexts will be collected. @return themself
- L41 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetOutput(const FDisplayClusterShadersTextureViewport& InTextureViewport, const int32 InContextNum = INDEX_NONE) = 0;` — Set the output texture viewport for the specified context. @parama InTextureViewport - texture viewport @param InContextNum       - (opt) context(eye)  number, otherwise all contexts will be collected. @return themself
- L51 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetInput( const IDisplayClusterViewportProxy* InViewportProxy, const EDisplayClusterViewportResourceType InResourceType, const int32 InContextNum = INDEX_NONE) = 0;` — Set input texture from a viewport proxy object. @param InViewportProxy  - viewport proxy object with resources to retrieve @param InResourceType   - Type of the viewport resource @param InContextNum       - (opt) context(eye)  number, otherwise all contexts will be collected. @return themself
- L64 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetOutput( const IDisplayClusterViewportProxy* InViewportProxy, const EDisplayClusterViewportResourceType InResourceType, const int32 InContextNum = INDEX_NONE) = 0;` — Set output texture from a viewport proxy object. @param InViewportProxy  - viewport proxy object with resources to retrieve @param InResourceType   - Type of the viewport resource @param InContextNum       - (opt) context(eye)  number, otherwise all contexts will be collected. @return themself
- L75 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetInputEncoding(const FDisplayClusterColorEncoding& InColorEncoding) = 0;` — Set input color encodig for texture @param InColorEncoding  - color encoding @return themself
- L83 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> SetOutputEncoding(const FDisplayClusterColorEncoding& InColorEncoding) = 0;` — Set output color encodig for texture @param InColorEncoding  - color encoding @return themself
- L87 _public prototype_ `virtual const FDisplayClusterShadersTextureParameters& GetInputTextureParameters() const = 0;` — Return input texture parameters.
- L90 _public prototype_ `virtual const FDisplayClusterShadersTextureParameters& GetOutputTextureParameters() const = 0;` — Return input texture parameters.
- L97 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> Resolve() = 0;` — Resolve all contexts @return themself
- L107 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> Resolve(const FDisplayClusterShadersTextureUtilsSettings& InSettings) = 0;` — Resolve all contexts @param ColorMask - Color Recording Mask. Used to copy only selected channels. @param InSettings - (in) render settings @return themself
- L117 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> ResolveTextureContext( const FDisplayClusterShadersTextureViewportContext& Input, const FDisplayClusterShadersTextureViewportContext& Output) = 0;` — Resolve one context to the other @param Input  - input texture context @param Output - output texture context @return - themself
- L130 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> ResolveTextureContext( const FDisplayClusterShadersTextureUtilsSettings& InSettings, const FDisplayClusterShadersTextureViewportContext& Input, const FDisplayClusterShadersTextureViewportContext& Output) = 0;` — Resolve one context to the other @param InSettings - (in) render settings @param Input      - input texture context @param Output     - output texture context @return - themself
- L145 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> ForEachContextByPredicate(TFunctionDisplayClusterShaders_TextureContextIterator&& TextureContextIteratorFunc) = 0;` — Custom implementation of an action between input and output contexts. Iterate over all contexts on input and output textures. Note: This function creates unique TextureContexts instances for the iterator arguments. Multiple calls to ForEachContextByPredicate() will create unique contexts for each use. @param TextureContextIteratorFunc - predicate function that processes pairs of input and output textures (via resolve or any other way). @ returns themself
- L158 _public prototype_ `virtual TSharedRef<IDisplayClusterShadersTextureUtils> ForEachContextByPredicate( const FDisplayClusterShadersTextureUtilsSettings& InSettings, TFunctionDisplayClusterShaders_TextureContextIterator&& TextureContextIteratorFunc) = 0;` — Custom implementation of an action between input and output contexts. Iterate over all contexts on input and output textures. Note: This function creates unique TextureContexts instances for the iterator arguments. Multiple calls to ForEachContextByPredicate() will create unique contexts for each use. @param InSettings - (in) render settings @param TextureContextIteratorFunc - predicate function that processes pairs of input and output textures (via resolve or any other way). @ returns themself
- L166 _public prototype_ `virtual FRDGBuilder& GetOrCreateRDGBuilder() = 0;` — Get or create RDG builder for this texture utils instance Instances created for RHI after this call will only use RDG.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/ShaderParameters/DisplayClusterShaderParameters_GenerateMips.h` (Public)


#### struct `FDisplayClusterShaderParameters_GenerateMips`  
`struct FDisplayClusterShaderParameters_GenerateMips`  
_L11-56_
- L15 _public member_ `bool bAutoGenerateMips = false;` — Allow autogenerate num mips for this target
- L23 _public member_ `int32 MaxNumMipsLimit = -1;` — Positive values used as max NumMips value
- L26 _public function_ `inline void Reset()`
- L31 _public function_ `inline bool IsEnabled() const`
- L36 _public function_ `inline int32 GetRequiredNumMips(const FIntPoint& InDim) const`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/ShaderParameters/DisplayClusterShaderParameters_ICVFX.h` (Public)


#### struct `FDisplayClusterShaderParametersICVFX_CameraViewProjection`  
`struct FDisplayClusterShaderParametersICVFX_CameraViewProjection`  
_L12-17_
- desc: Camera view projection data
- L14 _public member_ `FRotator ViewRotation;`
- L15 _public member_ `FVector ViewLocation;`
- L16 _public member_ `FMatrix PrjMatrix;`

#### struct `FDisplayClusterShaderParametersICVFX_ViewportResource`  
`struct FDisplayClusterShaderParametersICVFX_ViewportResource`  
_L24-49_
- desc: ICVFX rendering uses the resources of other viewports During initialization on a game thread, only the name of the viewport is saved here Later on the rendering thread, the resource reference is initialized
- L27 _public function_ `bool IsValid() const`
- L32 _public function_ `bool IsDefined() const`
- L37 _public function_ `void Reset()`
- L45 _public member_ `FString ViewportId;` — Viewport name (Used to resolve viewport resource to texture ref)
- L48 _public member_ `FRHITexture* Texture = nullptr;` — This ref resolved runtime

#### class `FDisplayClusterShaderParameters_ICVFX`  
`class FDisplayClusterShaderParameters_ICVFX`  
_L54-426_
- desc: This is where the ICVFX data for the outer viewport is stored.
- L57 _public function_ `FDisplayClusterShaderParameters_ICVFX()`
- L61 _public function_ `inline bool IsLightCardOverUsed() const`
- L66 _public function_ `inline bool IsLightCardUnderUsed() const`
- L71 _public function_ `inline bool IsUVLightCardOverUsed() const`
- L76 _public function_ `inline bool IsUVLightCardUnderUsed() const`
- L81 _public function_ `inline bool IsCameraUsed(int32 CameraIndex) const`
- L86 _public function_ `inline bool IsAnyCameraUsed() const`
- L91 _public function_ `inline bool IsMultiCamerasUsed() const`
- L96 _public function_ `inline bool IsValid() const`
- L107 _public function_ `void Reset()`
- L122 _public function_ `void SetParameters(const FDisplayClusterShaderParameters_ICVFX& InParameters)` — Implement copy ref and arrays
- L142 _public function_ `inline void SortCamerasRenderOrder(const bool bReverseOrder = false)`
- L348 _public function_ `template <typename Predicate> void IterateViewportResourcesByPredicate(Predicate Pred)` — Iterate over all defined viewport resources with a predicate functor.
- L379 _public function_ `inline FCameraSettings* FindCameraByName(const FString& InViewportId)` — Find camera settings by viewport name
- L388 _public function_ `inline bool CleanupCamerasForRender()` — Remove unused cameras from render
- L405 _public member_ `TArray<FCameraSettings> Cameras;` — All cameras that render on this viewport
- L408 _public member_ `EDisplayClusterShaderParametersICVFX_CameraOverlappingRenderMode CameraOverlappingRenderMode = EDisplayClusterShaderParametersICVFX_CameraOverlappingRenderMode::None;` — Rendering mode for overlapping areas of camera projections
- L411 _public member_ `FDisplayClusterShaderParametersICVFX_ViewportResource LightCardUnder;` — LightCard resources
- L412 _public member_ `FDisplayClusterShaderParametersICVFX_ViewportResource LightCardOver;`
- L415 _public member_ `FDisplayClusterShaderParametersICVFX_ViewportResource UVLightCardUnder;` — UV LightCard resources
- L416 _public member_ `FDisplayClusterShaderParametersICVFX_ViewportResource UVLightCardOver;`
- L419 _public member_ `EDisplayClusterShaderParametersICVFX_LightCardRenderMode OverrideUVLightCardRenderMode = EDisplayClusterShaderParametersICVFX_LightCardRenderMode::None;` — Force UVLC to render merged (per-viewport LC)
- L422 _public member_ `float LightCardGamma = 2.2f;` — The gamma that the light card renders have been encoded with, used to linearize during final composite
- L425 _public member_ `TArray<FString> EnforcedCameraOrder;` — Enforced camera order for custom sorting. Contains the camera viewport ids, where index 0 should be composed on top, index 1 below it, and so on.

#### struct `FDisplayClusterShaderParameters_ICVFX::FCameraSettings`  
`struct FCameraSettings`  
_L209-342_
- desc: Incamera render settings
- L211 _public function_ `inline bool IsUsed() const`
- L216 _public function_ `inline bool IsChromakeyMarkerUsed() const`
- L222 _public function_ `inline bool IsOverlapChromakeyMarkerUsed() const` — Gets whether a valid texture is available to render chromakey markers for any overlapping ICVFX frustums
- L227 _public function_ `inline void SetViewProjection(const FDisplayClusterShaderParametersICVFX_CameraViewProjection& InCameraViewProjection, const FTransform& InOrigin2WorldTransform)`
- L240 _public function_ `template <typename Predicate> void IterateViewportResourcesByPredicate(Predicate Pred)` — Iterate over all defined viewport resources with a predicate functor.
- L260 _public function_ `inline void SetCameraSettings(const FCameraSettings& InCameraSettings, const bool bIncludeResources)` — Copying camera settings from the source camera. The function is moved here from the DisplayClusterMedia module, because it must also be updated when new settings are added. @param InCameraSettings - source camera settings @param bIncludeResources - enables resource copying
- L296 _public member_ `FDisplayClusterShaderParametersICVFX_ViewportResource Resource;` — resource with the camera image
- L298 _public member_ `FVector4 SoftEdge;`
- L300 _public member_ `FLinearColor InnerCameraBorderColor = FLinearColor::Black;`
- L301 _public member_ `float InnerCameraBorderThickness = 0.1f;`
- L304 _public member_ `FDisplayClusterShaderParametersICVFX_CameraViewProjection ViewProjection;` — Camera view projection data
- L307 _public member_ `EDisplayClusterShaderParametersICVFX_ChromakeySource ChromakeySource = EDisplayClusterShaderParametersICVFX_ChromakeySource::Disabled;` — Chromakey settings:
- L308 _public member_ `FDisplayClusterShaderParametersICVFX_ViewportResource Chromakey;`
- L309 _public member_ `FLinearColor ChromakeyColor = FLinearColor::Black;`
- L312 _public member_ `FLinearColor OverlapChromakeyColor = FLinearColor::Black;` — The color to use when rendering chromakey for any regions of overlapping ICVFX frustums
- L315 _public member_ `FLinearColor ChromakeyMarkersColor = FLinearColor::Black;` — Chromakey markers settings:
- L316 _public member_ `float ChromakeyMarkersScale;`
- L317 _public member_ `float ChromakeyMarkersDistance;`
- L318 _public member_ `FVector2D ChromakeyMarkersOffset;`
- L319 _public member_ `FTextureRHIRef ChromakeMarkerTextureRHI;`
- L322 _public member_ `FLinearColor OverlapChromakeyMarkersColor = FLinearColor::Black;` — The color of the chroamkey markers for any regions of overlapping ICVFX frustums
- L325 _public member_ `float OverlapChromakeyMarkersScale;` — The scale of the chroamkey markers for any regions of overlapping ICVFX frustums
- L328 _public member_ `float OverlapChromakeyMarkersDistance;` — The distance between the chroamkey markers for any regions of overlapping ICVFX frustums
- L331 _public member_ `FVector2D OverlapChromakeyMarkersOffset;` — The offset of the chroamkey markers for any regions of overlapping ICVFX frustums
- L334 _public member_ `FTextureRHIRef OverlapChromakeyMarkerTextureRHI;` — The texture to use to render the chromakey markers for any regions of overlaping ICVFX frustums
- L341 _public member_ `int32 RenderOrder = -1;` — Camera render order priority. Lower values render first (appear underneath), higher values render last (appear on top). When multiple cameras have the same RenderOrder, they are sorted alphabetically by viewport ID. Can be overridden per-viewport using EnforcedCameraOrder array.

#### Free symbols / members of external scopes

- L146 _function_ `` (scope `FDisplayClusterShaderParameters_ICVFX::SortCamerasRenderOrder`)
- L382 _function_ `` (scope `FDisplayClusterShaderParameters_ICVFX::FindCameraByName`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/ShaderParameters/DisplayClusterShaderParameters_Media.h` (Public)


#### struct `FDisplayClusterShaderParameters_MediaPQ`  
`struct FDisplayClusterShaderParameters_MediaPQ`  
_L13-26_
- desc: A container to pass PQ coding & decoding parameters
- L16 _public member_ `FRDGTexture* InputTexture = nullptr;` — Source texture for coding/decoding
- L19 _public member_ `FIntRect InputRect = { FIntPoint::ZeroValue, FIntPoint::ZeroValue };` — Source texture sub-region
- L22 _public member_ `FRDGTexture* OutputTexture = nullptr;` — Output texture for coding/decoding
- L25 _public member_ `FIntRect OutputRect = { FIntPoint::ZeroValue, FIntPoint::ZeroValue };` — Output texture sub-region

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/ShaderParameters/DisplayClusterShaderParameters_Overlay.h` (Public)


#### struct `FDisplayClusterShaderParameters_Overlay`  
`struct FDisplayClusterShaderParameters_Overlay`  
_L13-31_
- desc: Holds overlay drawing parameters
- L16 _public member_ `FRDGTexture* BaseTexture = nullptr;` — Base texture (bottom layer)
- L19 _public member_ `FRDGTexture* OverlayTexture = nullptr;` — Overlay texture (top layer)
- L22 _public member_ `FRDGTexture* OutputTexture = nullptr;` — Output texture (the result of source-over blending)
- L27 _public function_ `bool IsValidData() const` — Parameters validation

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/ShaderParameters/DisplayClusterShaderParameters_Override.h` (Public)


#### class `FDisplayClusterShaderParameters_Override`  
`class FDisplayClusterShaderParameters_Override`  
_L10-44_
- L13 _public function_ `FDisplayClusterShaderParameters_Override()`
- L16 _public function_ `~FDisplayClusterShaderParameters_Override()`
- L22 _public function_ `inline bool IsEnabled() const`
- L28 _public function_ `inline void SetParameters(const FDisplayClusterShaderParameters_Override& InParameters)` — Copy with resource ref
- L36 _public function_ `inline void Reset()`
- L42 _public member_ `FTextureRHIRef TextureRHI;`
- L43 _public member_ `FIntRect Rect;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/ShaderParameters/DisplayClusterShaderParameters_PostprocessBlur.h` (Public)


#### enum `EDisplayClusterShaderParameters_PostprocessBlur`  
`enum class EDisplayClusterShaderParameters_PostprocessBlur : uint8`  
_L10-20_
- L13 _public enumerator_ `None = 0` — Not use blur postprocess
- L16 _public enumerator_ `Gaussian` — Blur viewport using Gaussian method
- L19 _public enumerator_ `Dilate` — Blur viewport using Dilate method

#### struct `FDisplayClusterShaderParameters_PostprocessBlur`  
`struct FDisplayClusterShaderParameters_PostprocessBlur`  
_L22-38_
- L24 _public member_ `EDisplayClusterShaderParameters_PostprocessBlur Mode = EDisplayClusterShaderParameters_PostprocessBlur::None;`
- L25 _public member_ `int32 KernelRadius = 1;`
- L26 _public member_ `float KernelScale = 1;`
- L29 _public function_ `inline void Reset()`
- L34 _public function_ `inline bool IsEnabled() const`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/ShaderParameters/DisplayClusterShaderParameters_TransformTexture.h` (Public)


#### struct `FDisplayClusterShaderParameters_TransformTexture`  
`struct FDisplayClusterShaderParameters_TransformTexture`  
_L12-75_
- desc: TransformTexture shader parameters
- L32 _public member_ `FRDGTexture* InputTexture = nullptr;` — Input texture
- L35 _public member_ `TOptional<FIntRect> InputRegion;` — Subregion to extract and transform, or whole texture if not set
- L38 _public member_ `ETranformation TranformationType = ETranformation::None;` — Transformation type to apply
- L41 _public member_ `mutable FRDGTexture* OutputTexture = nullptr;` — Output texture. If not set, a new one will be allocated
- L46 _public function_ `bool IsValidData() const` — Parameters validation

#### enum `FDisplayClusterShaderParameters_TransformTexture::ETranformation`  
`enum class ETranformation : uint8`  
_L19-27_
- desc: Supported texture transformations
- L21 _public enumerator_ `None` — No transformation
- L22 _public enumerator_ `Rotation_90` — Rotate  90 deg CW (same as 270 CCW)
- L23 _public enumerator_ `Rotation_180` — Rotate 180 deg CW (same as 180 CCW)
- L24 _public enumerator_ `Rotation_270` — Rotate 270 deg CW (same as  90 CCW)
- L25 _public enumerator_ `Flip_H` — Horizontal mirroring
- L26 _public enumerator_ `Flip_V` — Vertical mirroring

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/ShaderParameters/DisplayClusterShaderParameters_UVLightCards.h` (Public)


#### struct `FDisplayClusterShaderParameters_UVLightCards`  
`struct FDisplayClusterShaderParameters_UVLightCards`  
_L10-17_
- desc: A data struct that contains parameters for performing the UV light card render pass
- L13 _public member_ `TArray<FPrimitiveSceneProxy*> PrimitivesToRender;` — A list of primitive scene proxies to render
- L16 _public member_ `float ProjectionPlaneSize = 200.0f;` — The size of the plane in world units to project the UV space onto

### `Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Public/ShaderParameters/DisplayClusterShaderParameters_WarpBlend.h` (Public)


#### struct `FDisplayClusterShaderParameters_WarpBlend`  
`struct FDisplayClusterShaderParameters_WarpBlend`  
_L12-38_
- L27 _public member_ `FResourceWithRect Src;` — In\Out resources for warp
- L28 _public member_ `FResourceWithRect Dest;`
- L31 _public member_ `TSharedPtr<class IDisplayClusterWarpBlend, ESPMode::ThreadSafe> WarpInterface;` — Warp interface
- L34 _public member_ `FDisplayClusterWarpContext Context;` — Context data
- L37 _public member_ `bool bRenderAlphaChannel = false;` — Render alpha channel from input texture to warp output

#### struct `FDisplayClusterShaderParameters_WarpBlend::FResourceWithRect`  
`struct FResourceWithRect`  
_L14-24_
- L16 _public member_ `FRHITexture* Texture;`
- L17 _public member_ `FIntRect Rect;`
- L19 _public function_ `void Set(FRHITexture* InTexture, const FIntRect& InRect)`
