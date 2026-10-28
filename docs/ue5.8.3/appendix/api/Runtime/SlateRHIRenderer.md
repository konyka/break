# Runtime / SlateRHIRenderer

- module root: `Source/Runtime/SlateRHIRenderer`
- headers: 24; symbols: 633
- symbol kinds: class=41, delegate=1, enum=1, enumerator=2, externvar=8, function=108, macro=4, member=165, namespace=1, prototype=277, struct=17, typedef=5, union=1, variable=2
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, HeadMountedDisplay, ImageCore, RHI, RenderCore, Renderer, Slate, SlateCore
- PublicDependencyModuleNames: SlateBaseRenderer

### `Source/Runtime/SlateRHIRenderer/Private/Slate3DRenderer.h` (Private)


#### class `FSlate3DRenderer`  
`class FSlate3DRenderer : public ISlate3DRenderer, public FDeferredCleanupInterface`  
_L16-57_
- inherits: `ISlate3DRenderer,FDeferredCleanupInterface`
- L19 _public prototype_ `FSlate3DRenderer( TSharedRef<FSlateFontServices> InSlateFontServices, TSharedRef<FSlateRHIResourceManager> InResourceManager, bool bUseGammaCorrection = false );`
- L21 _public prototype_ `void Cleanup();`
- L23 _public prototype_ `virtual void SetUseGammaCorrection(bool bUseGammaCorrection) override;`
- L24 _public prototype_ `virtual void SetApplyColorDeficiencyCorrection(bool bApplyColorCorrection) override;`
- L26 _public prototype_ `virtual FSlateDrawBuffer& AcquireDrawBuffer() override;`
- L27 _public prototype_ `virtual void ReleaseDrawBuffer(FSlateDrawBuffer& DrawBuffer) override;`
- L28 _public prototype_ `virtual void DrawWindow_GameThread(FSlateDrawBuffer& DrawBuffer) override;`
- L29 _public prototype_ `virtual void DrawWindowToTarget_RenderThread(FRDGBuilder& GraphBuilder, const struct FRenderThreadUpdateContext& Context) override;`
- L34 _private member_ `static const int32 NUM_DRAW_BUFFERS = 4;` — Double buffered draw buffers so that the rendering thread can be rendering windows while the game thread is setting up for next frame
- L35 _private member_ `FSlateDrawBuffer DrawBuffers[NUM_DRAW_BUFFERS];`
- L38 _private member_ `TSharedRef<FSlateFontServices> SlateFontServices;` — The font services to use for rendering text
- L41 _private member_ `TSharedRef<FSlateRHIResourceManager> ResourceManager;` — Texture manager for accessing textures on the game thread
- L44 _private member_ `TSharedPtr<class FSlateRHIRenderingPolicy> RenderTargetPolicy;` — The rendering policy to use for drawing to the render target
- L47 _private member_ `TUniquePtr<FSlateElementBatcher> ElementBatcher;` — Element batcher that renders draw elements
- L50 _private member_ `uint8 FreeBufferIndex;` — The draw buffer that is currently free for use by the game thread
- L53 _private member_ `bool bRenderTargetWasCleared = false;` — Set to true when the render target was cleared and prevent another clear to be called for nothing.
- L55 _private member_ `bool bAllowColorDeficiencyCorrection = true;`
- L56 _private member_ `bool bGammaCorrection;`

### `Source/Runtime/SlateRHIRenderer/Private/SlateAtlasedTextureResource.h` (Private)


#### class `FSlateAtlasedTextureResource`  
`class FSlateAtlasedTextureResource : public FSlateBaseUTextureResource`  
_L14-39_
- inherits: `FSlateBaseUTextureResource`
- desc: A resource for rendering a sub-rect of a UTexture atlas object in Slate. Each ISlateTextureAtlasInterface* should uniquely identify a subregion of the UTexture atlas.
- L18 _public prototype_ `FSlateAtlasedTextureResource(UTexture* InTexture);` — Initializes a new atlased UTexture resource, the incoming texture should be the entire atlas.
- L21 _public prototype_ `virtual ~FSlateAtlasedTextureResource();` — Destructor
- L24 _public prototype_ `virtual bool IsResourceValid() const override;`
- L32 _public prototype_ `FSlateShaderResourceProxy* FindOrCreateAtlasedProxy(UObject* InAtlasedObject, const FSlateAtlasData& AtlasData);` — Finds or creates the rendering proxy for a given atlas'ed object. @param InAtlasedObject The atlased object to find a rendering proxy for. @param InAtlasedObjectInterface The Interface pointer for the InAtlasedObject.
- L35 _public typedef_ `typedef TMap<TWeakObjectPtr<UObject>, FSlateShaderResourceProxy* > FObjectResourceMap;`
- L38 _public member_ `FObjectResourceMap ProxyMap;` — Map of all the atlased resources.

### `Source/Runtime/SlateRHIRenderer/Private/SlateElementVertexBuffer.h` (Private)


#### class `TSlateElementVertexBuffer`  
`template <typename VertexType> class TSlateElementVertexBuffer : public FVertexBuffer`  
_L21-168_
- inherits: `FVertexBuffer`
- desc: Vertex buffer containing all Slate vertices
- L24 _public function_ `TSlateElementVertexBuffer() : BufferSize(0) , MinBufferSize(0) , BufferUsageSize(0)`
- L30 _public prototype_ `~TSlateElementVertexBuffer() = default;`
- L32 _public function_ `void Init( int32 MinNumVertices )`
- L46 _public function_ `void Destroy()`
- L59 _public function_ `virtual void InitRHI(FRHICommandListBase& RHICmdList)` — Initializes the vertex buffers RHI resource.
- L80 _public function_ `virtual void ReleaseRHI()` — Releases the vertex buffers RHI resource.
- L87 _public function_ `virtual FString GetFriendlyName() const` — Returns a friendly name for this buffer.
- L90 _public function_ `int32 GetBufferSize() const` — Returns the size of the buffer in bytes.
- L93 _public function_ `int32 GetBufferUsageSize() const` — Returns the used size of this buffer
- L96 _public function_ `void ResetBufferUsage()` — Resets the usage of the buffer
- L99 _public function_ `void PreFillBuffer(FRHICommandListBase& RHICmdList, int32 RequiredVertexCount, bool bShrinkToMinSize)` — Resizes buffer, accumulates states safely on render thread
- L121 _public function_ `int32 GetMinBufferSize() const`
- L125 _private function_ `void ResizeBuffer(FRHICommandListBase& RHICmdList, int32 NewSizeBytes)` — Resizes the buffer to the passed in size.  Preserves internal data
- L148 _private function_ `void SetBufferSize(int32 NewBufferSize)`
- L157 _private member_ `int32 BufferSize;` — The size of the buffer in bytes.
- L160 _private member_ `int32 MinBufferSize;` — The minimum size the buffer should always be
- L163 _private member_ `int32 BufferUsageSize;` — The size of the used portion of the buffer
- L166 _private prototype_ `TSlateElementVertexBuffer( const TSlateElementVertexBuffer& );` — Hidden copy methods.
- L167 _private prototype_ `void operator=(const TSlateElementVertexBuffer& );`

#### class `FSlateStencilClipVertexBuffer`  
`class FSlateStencilClipVertexBuffer : public FVertexBuffer`  
_L171-201_
- inherits: `FVertexBuffer`
- L174 _public function_ `FSlateStencilClipVertexBuffer()`
- L177 _public prototype_ `~FSlateStencilClipVertexBuffer() = default;`
- L180 _public function_ `virtual void InitRHI(FRHICommandListBase& RHICmdList)` — Initializes the vertex buffers RHI resource.
- L194 _public function_ `virtual void ReleaseRHI()` — Releases the vertex buffers RHI resource.
- L200 _public function_ `virtual FString GetFriendlyName() const` — Returns a friendly name for this buffer.

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Vertex Buffer Memory (GPU)"), STAT_SlateVertexBufferMemory,`
- L203 _externvar_ `extern TGlobalResource<FSlateStencilClipVertexBuffer> GSlateStencilClipVertexBuffer;`

### `Source/Runtime/SlateRHIRenderer/Private/SlateFontBlueprintLibrary.h` (Private)


#### class `USlateFontBlueprintLibrary`  
`class USlateFontBlueprintLibrary : public UObject`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UObject`
- L19 _private prototype_ `static FSlateFontInfo MakeSlateFontInfo(const UObject* FontObject, UObject* FontMaterial, FFontOutlineSettings OutlineSettings, FName TypefaceFontName, float Size = 24.0f, int32 LetterSpacing = 0, float SkewAmount = 0.0f, bool bForceMonospaced = false, bool bMaterialIsStencil = false, float MonospacedWidth = 1.0f);` — `UFUNCTION(BlueprintPure, Category = "Slate Font", meta = (DeprecatedFunction, DeprecationMessage = "MakeSlateFontInfo from SlateFontBlueprintLibrary has been deprecated, use MakeSlateFontInfo from SlateFontInfoBlueprintLibrary instead."))` — TODO: add deprecation in a second step to make migration process easier

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSlateFontBlueprint, Log, All);`

### `Source/Runtime/SlateRHIRenderer/Private/SlateMaterialResource.h` (Private)


#### class `FSlateMaterialResource`  
`class FSlateMaterialResource : public FSlateShaderResource`  
_L14-77_
- inherits: `FSlateShaderResource`
- desc: A resource for rendering a UMaterial in Slate
- L17 _public prototype_ `FSlateMaterialResource(const UMaterialInterface& InMaterialResource, const FVector2f InImageSize, FSlateShaderResource* InTextureMask = nullptr );`
- L18 _public prototype_ `~FSlateMaterialResource();`
- L21 _public function_ `virtual uint32 GetWidth() const override`
- L22 _public function_ `virtual uint32 GetHeight() const override`
- L23 _public function_ `virtual ESlateShaderResource::Type GetType() const override`
- L24 _public prototype_ `virtual ESlatePostRT GetUsedSlatePostBuffers() const override;`
- L25 _public prototype_ `virtual bool RequiresVirtualTextureFeedback() const override;`
- L26 _public prototype_ `virtual bool IsResourceValid() const override;`
- L29 _public prototype_ `void UpdateMaterial(const UMaterialInterface& InMaterialResource, const FVector2f InImageSize, FSlateShaderResource* InTextureMask );`
- L30 _public prototype_ `void ResetMaterial();`
- L33 _public function_ `FMaterialRenderProxy* GetRenderProxy() const` — @return The material render proxy
- L36 _public function_ `const UMaterialInterface* GetMaterialObject() const` — @return the material object
- L42 _public function_ `FSlateShaderResourceProxy* GetResourceProxy() const` — Slate proxy used for batching the material
- L44 _public function_ `FSlateShaderResource* GetTextureMaskResource() const`
- L47 _public prototype_ `virtual void CheckForStaleResources() const override;`
- L51 _private member_ `const class UMaterialInterface* MaterialObject;`
- L52 _private member_ `class FMaterialRenderProxy* MaterialProxy;`
- L56 _private member_ `TWeakObjectPtr<const UMaterialInterface> MaterialObjectWeakPtr;` — Used to guard against crashes when the material object is deleted.  This is expensive so we do not do it in shipping
- L57 _private member_ `FName DebugName;`
- L61 _private member_ `FSlateShaderResourceProxy* SlateProxy;` — Slate proxy used for batching the material
- L63 _private member_ `FSlateShaderResource* TextureMaskResource;`
- L64 _private member_ `uint32 Width;`
- L65 _private member_ `uint32 Height;`
- L68 _private member_ `ESlatePostRT CachedSlatePostBuffers;` — Cached slate SlatePostRT assets / buffers in use
- L71 _private member_ `bool CachedUsesVirtualTextures;` — Cached result of whether we use virtual textures
- L75 _private prototype_ `void UpdateMaterialName();`

### `Source/Runtime/SlateRHIRenderer/Private/SlateMaterialShader.h` (Private)


#### class `FSlateMaterialShaderVS`  
`class FSlateMaterialShaderVS : public FMaterialShader`  
_L14-31_
- inherits: `FMaterialShader`
- L18 _public function_ `FSlateMaterialShaderVS()`
- L19 _public prototype_ `FSlateMaterialShaderVS(const FMaterialShaderType::CompiledShaderInitializerType& Initializer);`
- L21 _public prototype_ `static void ModifyCompilationEnvironment(const FMaterialShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L23 _public prototype_ `static bool ShouldCompilePermutation(const FMaterialShaderPermutationParameters& Parameters);`
- L25 _public prototype_ `void SetMaterialShaderParameters( FMeshDrawSingleShaderBindings& ShaderBindings, const FSceneInterface* Scene, const TUniformBufferRef<FViewUniformShaderParameters>& ViewUniformBuffer, const FMaterialRenderProxy* MaterialRenderProxy, const FMaterial* Material);`

#### class `FSlateMaterialShaderPS`  
`class FSlateMaterialShaderPS : public FMaterialShader`  
_L33-69_
- inherits: `FMaterialShader`
- L39 _public prototype_ `static bool ShouldCompilePermutation(const FMaterialShaderPermutationParameters& Parameters);` — Only compile shaders used with UI.
- L42 _public prototype_ `static void ModifyCompilationEnvironment(const FMaterialShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);` — Modifies the compilation of this shader.
- L44 _public function_ `FSlateMaterialShaderPS()`
- L45 _public prototype_ `FSlateMaterialShaderPS(const FMaterialShaderType::CompiledShaderInitializerType& Initializer);`
- L47 _public prototype_ `void SetMaterialShaderParameters( FMeshDrawSingleShaderBindings& ShaderBindings, const FSceneInterface* Scene, const TUniformBufferRef<FViewUniformShaderParameters>& ViewUniformBuffer, const FMaterialRenderProxy* MaterialRenderProxy, const FMaterial* Material, const FShaderParams& InShaderParams);`
- L55 _public prototype_ `void SetDisplayGammaAndContrast(FMeshDrawSingleShaderBindings& ShaderBindings, float InDisplayGamma, float InContrast);`
- L57 _public prototype_ `void SetAdditionalTexture(FMeshDrawSingleShaderBindings& ShaderBindings, FRHITexture* InTexture, const FSamplerStateRHIRef SamplerState );`
- L59 _public prototype_ `void SetDrawFlags(FMeshDrawSingleShaderBindings& ShaderBindings, ESlateShader InShaderType, bool bDrawDisabledEffect);`

#### class `TSlateMaterialShaderVS`  
`template<bool bUseInstancing> class TSlateMaterialShaderVS : public FSlateMaterialShaderVS`  
_L72-96_
- inherits: `FSlateMaterialShaderVS`
- L75 _public prototype_ `DECLARE_SHADER_TYPE(TSlateMaterialShaderVS,Material);`
- L77 _public function_ `TSlateMaterialShaderVS()`
- L79 _public function_ `TSlateMaterialShaderVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FSlateMaterialShaderVS( Initializer )`
- L84 _public function_ `static bool ShouldCompilePermutation(const FMaterialShaderPermutationParameters& Parameters)` — Only compile shaders used with UI.
- L90 _public function_ `static void ModifyCompilationEnvironment(const FMaterialShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)` — Modifies the compilation of this shader.

#### class `TSlateMaterialShaderPS`  
`template<ESlateShader ShaderType> class TSlateMaterialShaderPS : public FSlateMaterialShaderPS`  
_L101-125_
- inherits: `FSlateMaterialShaderPS`
- L104 _public prototype_ `DECLARE_SHADER_TYPE(TSlateMaterialShaderPS,Material);`
- L106 _public function_ `TSlateMaterialShaderPS()`
- L108 _public function_ `TSlateMaterialShaderPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FSlateMaterialShaderPS( Initializer )`
- L113 _public function_ `static bool ShouldCompilePermutation(const FMaterialShaderPermutationParameters& Parameters)` — Only compile shaders used with UI.
- L119 _public function_ `static void ModifyCompilationEnvironment(const FMaterialShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)` — Modifies the compilation of this shader.

#### Free symbols / members of external scopes

- L98 _prototype_ `bool IsValidSlateMaterialShaderType(ESlateShader ShaderType, EShaderPlatform ShaderPlatform);`

### `Source/Runtime/SlateRHIRenderer/Private/SlateNativeTextureResource.h` (Private)


#### class `FSlateDynamicTextureResource`  
`class FSlateDynamicTextureResource`  
_L11-19_
- desc: Represents a dynamic texture resource for rendering in Slate
- L14 _public prototype_ `FSlateDynamicTextureResource(FSlateTexture2DRHIRef* ExistingTexture);`
- L15 _public prototype_ `~FSlateDynamicTextureResource();`
- L17 _public member_ `FSlateShaderResourceProxy* Proxy;`
- L18 _public member_ `FSlateTexture2DRHIRef* RHIRefTexture;`

### `Source/Runtime/SlateRHIRenderer/Private/SlatePostProcessResource.h` (Private)


#### class `FSlatePostProcessResource`  
`class FSlatePostProcessResource : public FSlateShaderResource, public FRenderResource, private FDeferredCleanupInterface`  
_L13-51_
- inherits: `FSlateShaderResource,FRenderResource,FDeferredCleanupInterface`
- desc: Handle to resources used for post processing.  This should not be deleted manually because it implements FDeferredCleanupInterface
- L16 _public prototype_ `FSlatePostProcessResource(int32 InRenderTargetCount);`
- L17 _public prototype_ `~FSlatePostProcessResource();`
- L19 _public function_ `const FTextureRHIRef& GetRenderTarget(int32 Index)`
- L25 _public prototype_ `void Update(const FIntPoint& NewSize, EPixelFormat RequestedPixelFormat);` — Performs per frame updates to this resource
- L27 _public prototype_ `void CleanUp();`
- L30 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource interface
- L31 _public prototype_ `virtual void ReleaseRHI() override;`
- L34 _public function_ `virtual uint32 GetWidth() const override` — FSlateShaderResource interface
- L35 _public function_ `virtual uint32 GetHeight() const override`
- L36 _public function_ `virtual ESlateShaderResource::Type GetType() const override`
- L38 _public function_ `EPixelFormat GetPixelFormat() const`
- L39 _public function_ `uint64 GetFrameUsed()`
- L43 _private prototype_ `void ResizeTargets(FRHICommandListBase& RHICmdList, const FIntPoint& NewSize, EPixelFormat RequestedPixelFormat);` — Resizes targets to the new size
- L46 _private member_ `TArray<FTextureRHIRef, TInlineAllocator<2>> RenderTargets;`
- L47 _private member_ `EPixelFormat PixelFormat;`
- L48 _private member_ `FIntPoint RenderTargetSize;`
- L49 _private member_ `int32 RenderTargetCount;`
- L50 _private member_ `uint64 FrameUsed;`

### `Source/Runtime/SlateRHIRenderer/Private/SlatePostProcessor.h` (Private)


#### struct `FSlateClippingOp`  
`struct FSlateClippingOp`  
_L9-47_
- L24 _public member_ `FVector2f Offset;`
- L25 _public member_ `EClippingMethod Method;`
- L26 _public member_ `uint8 MaskingId;`
- L28 _public function_ `static inline FSlateClippingOp* Scissor(FRDGBuilder& GraphBuilder, FVector2f Offset, FSlateRect Rect)`
- L38 _public function_ `static inline FSlateClippingOp* Stencil(FRDGBuilder& GraphBuilder, FVector2f Offset, TConstArrayView<FSlateClippingZone> Zones, int32 MaskingId)`

#### union `FSlateClippingOp::(anonymous)`  
``  
_L12-22_

#### struct `FSlateClippingOp::__anonab09468a010a::(anonymous)`  
``  
_L14-16_

#### struct `FSlateClippingOp::__anonab09468a010a::(anonymous)`  
``  
_L19-21_

#### struct `FSlatePostProcessBlurPassInputs`  
`struct FSlatePostProcessBlurPassInputs`  
_L53-73_
- L56 _public member_ `FRDGTexture* SDRCompositeUITexture = nullptr;` — An optional in/out separately composited UI texture that is composited with the input and then the output rect is reset to transparent.
- L57 _public member_ `FRDGTexture* InputTexture = nullptr;`
- L58 _public member_ `FRDGTexture* OutputTexture = nullptr;`
- L59 _public member_ `ERenderTargetLoadAction OutputLoadAction = ERenderTargetLoadAction::ELoad;`
- L62 _public member_ `const FSlateClippingOp* ClippingOp = nullptr;` — An optional set of inputs for when a blur is performed as part of a slate render batch.
- L63 _public member_ `const FDepthStencilBinding* ClippingStencilBinding = nullptr;`
- L64 _public member_ `FIntRect ClippingElementsViewRect;`
- L66 _public member_ `FIntRect InputRect;`
- L67 _public member_ `FIntRect OutputRect;`
- L68 _public member_ `uint32 KernelSize = 0;`
- L69 _public member_ `float Strength = 0.0f;`
- L70 _public member_ `uint32 DownsampleAmount = 0;`
- L71 _public member_ `FVector4f CornerRadius = FVector4f::Zero();`
- L72 _public member_ `float HDRPaperWhiteInNits = 203.f;`

#### struct `FSlatePostProcessColorDeficiencyPassInputs`  
`struct FSlatePostProcessColorDeficiencyPassInputs`  
_L83-87_
- L85 _public member_ `FScreenPassTexture InputTexture;`
- L86 _public member_ `FScreenPassTexture OutputTexture;`

#### Free symbols / members of external scopes

- L15 _member_ `FSlateRect Rect;` (scope `FSlateClippingOp::__anonab09468a010a::__anonab09468a0208`)
- L16 _member_ `} Data_Scissor;` (scope `FSlateClippingOp::__anonab09468a010a`)
- L20 _member_ `TConstArrayView<FSlateClippingZone> Zones;` (scope `FSlateClippingOp::__anonab09468a010a::__anonab09468a0308`)
- L21 _member_ `} Data_Stencil;` (scope `FSlateClippingOp::__anonab09468a010a`)
- L49 _prototype_ `bool GetSlateClippingPipelineState(const FSlateClippingOp* ClippingStateOp, FRHIDepthStencilState*& OutDepthStencilState, uint8& OutStencilRef);`
- L51 _prototype_ `void SetSlateClipping(FRHICommandList& RHICmdList, const FSlateClippingOp* ClippingStateOp, FIntRect ViewportRect);`
- L75 _prototype_ `extern ETextureCreateFlags GetSlateTransientRenderTargetFlags();`
- L76 _prototype_ `extern ETextureCreateFlags GetSlateTransientDepthStencilFlags();`
- L79 _prototype_ `void AddSlatePostProcessCopy(FRDGBuilder& GraphBuilder, FScreenPassTexture Input, FScreenPassTexture Output);` — Directly copies or resamples Input into Output with bilinear interpolation if the extent is different.
- L81 _prototype_ `void AddSlatePostProcessBlurPass(FRDGBuilder& GraphBuilder, const FSlatePostProcessBlurPassInputs& Inputs);`
- L89 _prototype_ `void AddSlatePostProcessColorDeficiencyPass(FRDGBuilder& GraphBuilder, const FSlatePostProcessColorDeficiencyPassInputs& Inputs);`

### `Source/Runtime/SlateRHIRenderer/Private/SlateRHIFontTexture.h` (Private)


#### class `FSlateFontTextureRHIResource`  
`class FSlateFontTextureRHIResource : public TSlateTexture<FTextureRHIRef>, public FTextureResource`  
_L15-52_
- inherits: `TSlateTexture<FTextureRHIRef>,FTextureResource`
- desc: Override for font textures that saves data between Init and ReleaseRHI to ensure all characters in the font texture exist if the rendering resource has to be recreated between caching new characters
- L23 _public prototype_ `FSlateFontTextureRHIResource(uint32 InWidth, uint32 InHeight, ESlateFontAtlasContentType InContentType);` — Constructor.  Initializes the texture @param InWidth The width of the texture @param InHeight The height of the texture
- L26 _public function_ `virtual uint32 GetWidth() const override` — FSlateShaderResource interface
- L27 _public function_ `virtual uint32 GetHeight() const override`
- L30 _public function_ `virtual uint32 GetSizeX() const override` — FTextureResource interface
- L31 _public function_ `virtual uint32 GetSizeY() const override`
- L32 _public function_ `virtual FString GetFriendlyName() const override`
- L35 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource interface
- L36 _public prototype_ `virtual void ReleaseRHI() override;`
- L39 _public function_ `ESlateFontAtlasContentType GetContentType() const` — Returns texture content type
- L42 _private prototype_ `EPixelFormat GetRHIPixelFormat() const;`
- L45 _private member_ `uint32 Width;` — Width of this texture
- L47 _private member_ `uint32 Height;` — Height of this texture
- L49 _private member_ `ESlateFontAtlasContentType ContentType;` — Type of content
- L51 _private member_ `TArray<uint8> TempData;` — Temporary data stored between Release and InitRHI

#### class `FSlateFontAtlasRHI`  
`class FSlateFontAtlasRHI : public FSlateFontAtlas`  
_L57-72_
- inherits: `FSlateFontAtlas`
- desc: Representation of a texture for fonts in which characters are packed tightly based on their bounding rectangle
- L60 _public prototype_ `FSlateFontAtlasRHI(uint32 Width, uint32 Height, ESlateFontAtlasContentType InContentType, ESlateTextureAtlasPaddingStyle InPaddingStyle);`
- L61 _public prototype_ `~FSlateFontAtlasRHI();`
- L66 _public function_ `virtual class FSlateShaderResource* GetSlateTexture() const override` — FSlateFontAtlas interface
- L67 _public function_ `virtual class FTextureResource* GetEngineTexture() override`
- L68 _public prototype_ `virtual void ConditionalUpdateTexture() override;`
- L69 _public prototype_ `virtual void ReleaseResources() override;`
- L71 _private member_ `TUniquePtr<FSlateFontTextureRHIResource> FontTexture;`

#### class `FSlateFontTextureRHI`  
`class FSlateFontTextureRHI : public ISlateFontTexture`  
_L77-116_
- inherits: `ISlateFontTexture`
- desc: A RHI non-atlased font texture resource
- L80 _public prototype_ `FSlateFontTextureRHI(const uint32 InWidth, const uint32 InHeight, ESlateFontAtlasContentType InContentType, const TArray<uint8>& InRawData);`
- L81 _public prototype_ `~FSlateFontTextureRHI();`
- L86 _public function_ `virtual class FSlateShaderResource* GetSlateTexture() const override` — ISlateFontTexture interface
- L87 _public function_ `virtual class FTextureResource* GetEngineTexture() override`
- L88 _public function_ `virtual ESlateFontAtlasContentType GetContentType() const override`
- L89 _public function_ `virtual void ReleaseRenderingResources() override`
- L93 _public prototype_ `virtual void GetAtlasDataCopy(TArray<uint8>& OutData) const override;`
- L95 _public prototype_ `void ReleaseResources();`
- L97 _private prototype_ `void UpdateTextureFromSource(FRHICommandListImmediate& RHICmdList, const uint32 SourceWidth, const uint32 SourceHeight, const TArray<uint8>& SourceData);`
- L113 _private member_ `TUniquePtr<FPendingSourceData> PendingSourceData;`
- L115 _private member_ `TUniquePtr<FSlateFontTextureRHIResource> FontTexture;`

#### struct `FSlateFontTextureRHI::FPendingSourceData`  
`struct FPendingSourceData`  
_L99-111_
- L101 _public function_ `FPendingSourceData(uint32 InSourceWidth, uint32 InSourceHeight, TArray<uint8> InSourceData) : SourceWidth(InSourceWidth) , SourceHeight(InSourceHeight) , SourceData(MoveTemp(InSourceData))`
- L108 _public member_ `uint32 SourceWidth;`
- L109 _public member_ `uint32 SourceHeight;`
- L110 _public member_ `TArray<uint8> SourceData;`

### `Source/Runtime/SlateRHIRenderer/Private/SlateRHIRenderer.h` (Private)


#### class `FSlateRHIRenderer`  
`class FSlateRHIRenderer final : public FSlateRenderer`  
_L40-208_
- inherits: `FSlateRenderer`
- desc: A Slate rendering implementation for Unreal engine
- L43 _public prototype_ `FSlateRHIRenderer( TSharedRef<FSlateFontServices> InSlateFontServices, TSharedRef<FSlateRHIResourceManager> InResourceManager );`
- L46 _public prototype_ `virtual bool Initialize() override;` — FSlateRenderer interface
- L47 _public prototype_ `virtual void Destroy() override;`
- L48 _public prototype_ `virtual FSlateDrawBuffer& AcquireDrawBuffer() override;`
- L49 _public prototype_ `virtual void ReleaseDrawBuffer(FSlateDrawBuffer& InWindowDrawBuffer) override;`
- L50 _public prototype_ `virtual void OnWindowDestroyed( const TSharedRef<SWindow>& InWindow ) override;`
- L51 _public prototype_ `virtual void RequestResize( const TSharedPtr<SWindow>& Window, uint32 NewWidth, uint32 NewHeight ) override;`
- L52 _public prototype_ `virtual void CreateViewport( const TSharedRef<SWindow> Window ) override;`
- L53 _public prototype_ `virtual void UpdateFullscreenState( const TSharedRef<SWindow> Window, uint32 OverrideResX, uint32 OverrideResY ) override;`
- L54 _public prototype_ `virtual void SetSystemResolution(uint32 Width, uint32 Height) override;`
- L55 _public prototype_ `virtual void RestoreSystemResolution(const TSharedRef<SWindow> InWindow) override;`
- L56 _public prototype_ `virtual void DrawWindows( FSlateDrawBuffer& InWindowDrawBuffer ) override;`
- L57 _public prototype_ `virtual void FlushCommands() const override;`
- L58 _public prototype_ `virtual void Sync() const override;`
- L59 _public prototype_ `virtual void ReleaseDynamicResource( const FSlateBrush& InBrush ) override;`
- L60 _public prototype_ `virtual void RemoveDynamicBrushResource( TSharedPtr<FSlateDynamicImageBrush> BrushToRemove ) override;`
- L61 _public prototype_ `virtual FIntPoint GenerateDynamicImageResource(const FName InTextureName) override;`
- L62 _public prototype_ `virtual bool GenerateDynamicImageResource( FName ResourceName, uint32 Width, uint32 Height, const TArray< uint8 >& Bytes ) override;`
- L63 _public prototype_ `virtual bool GenerateDynamicImageResource( FName ResourceName, FSlateTextureDataRef TextureData ) override;`
- L64 _public prototype_ `virtual FSlateResourceHandle GetResourceHandle(const FSlateBrush& Brush, FVector2f LocalSize, float DrawScale) override;`
- L65 _public prototype_ `virtual bool CanRenderResource(UObject& InResourceObject) const override;`
- L66 _public prototype_ `virtual void* GetViewportResource( const SWindow& Window ) override;`
- L67 _public prototype_ `virtual ISlateViewportProvider* GetViewportProvider(const SWindow& Window) override;`
- L68 _public prototype_ `virtual void SetColorVisionDeficiencyType(EColorVisionDeficiency Type, int32 Severity, bool bCorrectDeficiency, bool bShowCorrectionWithDeficiency) override;`
- L69 _public prototype_ `virtual FSlateUpdatableTexture* CreateUpdatableTexture(uint32 Width, uint32 Height) override;`
- L70 _public prototype_ `virtual FSlateUpdatableTexture* CreateSharedHandleTexture(void* SharedHandle) override;`
- L71 _public prototype_ `virtual void ReleaseUpdatableTexture(FSlateUpdatableTexture* Texture) override;`
- L72 _public prototype_ `virtual ISlateAtlasProvider* GetTextureAtlasProvider() override;`
- L73 _public prototype_ `virtual FCriticalSection* GetResourceCriticalSection() override;`
- L74 _public prototype_ `virtual void ReleaseAccessedResources(bool bImmediatelyFlush) override;`
- L75 _public prototype_ `virtual int32 GetCurrentSceneIndex() const override;`
- L76 _public prototype_ `virtual void SetCurrentSceneIndex(int32 InIndex) override;`
- L77 _public prototype_ `virtual void ClearScenes() override;`
- L80 _protected prototype_ `virtual void RegisterCurrentScene_Impl(FSceneInterface* Scene) override;`
- L83 _public prototype_ `EPixelFormat GetSlateRecommendedColorFormat() override;`
- L84 _public prototype_ `virtual void DestroyCachedFastPathRenderingData(struct FSlateCachedFastPathRenderingData* InRenderingData) override;`
- L85 _public prototype_ `virtual void DestroyCachedFastPathElementData(FSlateCachedElementData* InCachedElementData) override;`
- L86 _public prototype_ `virtual void EndFrame() const override;`
- L87 _public prototype_ `virtual void AddWidgetRendererUpdate(const struct FRenderThreadUpdateContext& Context, bool bDeferredRenderTargetUpdate) override;`
- L90 _public prototype_ `virtual void CreateNativeLayer(int32 NewNativeLayer, SWindow& InWindow, void* NativeViewHandle) override;`
- L91 _public prototype_ `virtual void DeleteNativeLayer(int32 OldNativeLayer, SWindow& InWindow) override;`
- L97 _public prototype_ `virtual void ReloadTextureResources() override;` — Reloads texture resources from disk
- L99 _public prototype_ `virtual void LoadStyleResources( const ISlateStyle& Style ) override;`
- L102 _public prototype_ `virtual bool AreShadersInitialized() const override;` — Returns whether shaders that Slate depends on have been compiled.
- L104 _public prototype_ `virtual void PrepareToTakeScreenshot(const FIntRect& Rect, TArray<FColor>* OutColorData, SWindow* ScreenshotWindow) override;`
- L105 _public prototype_ `virtual void PrepareToTakeHDRScreenshot(const FIntRect& Rect, TArray<FLinearColor>* OutColorData, SWindow* ScreenshotWindow) override;`
- L108 _private prototype_ `FSlateDrawWindowPassOutputs DrawWindow_RenderThread(FRDGBuilder& GraphBuilder, const FSlateDrawWindowPassInputs& Inputs);`
- L110 _private prototype_ `void DrawWindowViewport_RenderThread(ISlateViewport* SlateViewport, FRDGBuilder& GraphBuilder, const FSlateDrawWindowPassInputs& Inputs, FRHITexture** ViewportTextureRHI, FRHITexture** OutputTextureRHI, FSlateViewportInfo& ViewportInfo, FSlateBatchData& BatchData, FSlateBatchData& BatchDataHDR, TOptional<int32> NativeLayer, TInterval<int32> LayerRange);`
- L116 _private prototype_ `void PresentWindow_RenderThread(FRHICommandListImmediate& RHICmdList, const FSlateDrawWindowPassInputs& DrawPassInputs, const FSlateDrawWindowPassOutputs& DrawPassOutputs);`
- L118 _private prototype_ `void DrawWindows_RenderThread(FRHICommandListImmediate& RHICmdList, TConstArrayView<FSlateDrawWindowPassInputs> Windows, TConstArrayView<FRenderThreadUpdateContext> DeferredUpdates);`
- L121 _private prototype_ `void LoadUsedTextures();` — Loads all known textures from Slate styles
- L123 _private prototype_ `EPixelFormat GetViewportPixelFormat(const SWindow& Window, bool bDisplayFormatIsHDR);`
- L130 _private prototype_ `void DrawWindows_Private(FSlateDrawBuffer& InWindowDrawBuffer);` — Creates necessary resources to render a window and sends draw commands to the rendering thread @param WindowDrawBuffer	The buffer containing elements to draw
- L136 _private prototype_ `void CleanUpdatableTextures();` — Delete the updateable textures we've marked for delete that have already had their GPU resources released, but may have already been used on the game thread at the time they were released.
- L138 _private prototype_ `void OnVirtualDesktopSizeChanged(const FDisplayMetrics& NewDisplayMetric);`
- L141 _private member_ `TMap<const SWindow*, FSlateViewportInfo*> WindowToViewportInfo;` — A mapping of SWindows to their RHI implementation
- L144 _private member_ `FSlateDrawBuffer* EnqueuedWindowDrawBuffer = nullptr;` — Keep a pointer around for when we have deferred drawing happening
- L147 _private member_ `FSlateDrawBuffer DrawBuffers[NumDrawBuffers];` — Double buffered draw buffers so that the rendering thread can be rendering windows while the game thread is setting up for next frame
- L150 _private member_ `uint8 FreeBufferIndex = 0;` — The draw buffer which is currently free for use by the game thread
- L153 _private member_ `TUniquePtr<FSlateElementBatcher> ElementBatcher;` — Element batcher which renders draw elements
- L156 _private member_ `TSharedPtr<FSlateRHIResourceManager> ResourceManager;` — Texture manager for accessing textures on the game thread
- L159 _private member_ `TSharedPtr<FSlateRHIRenderingPolicy> RenderingPolicy;` — Drawing policy
- L161 _private member_ `TArray<TSharedPtr<FSlateDynamicImageBrush>> DynamicBrushesToRemove[NumDrawBuffers];`
- L170 _private member_ `} PendingDeletes;`
- L172 _private prototype_ `void FlushPendingDeletes();`
- L174 _private member_ `TArray<FRenderThreadUpdateContext, FConcurrentLinearArrayAllocator> DeferredUpdateContexts;`
- L176 _private member_ `bool bIsStandaloneStereoOnlyDevice = false;`
- L177 _private member_ `bool bUpdateHDRDisplayInformation = false;`
- L178 _private member_ `ESlatePostRT bShrinkPostBufferRequested = ESlatePostRT::None;`
- L179 _private member_ `uint64 LastFramesPostBufferUsed[(uint8)ESlatePostRT::Num];`
- L180 _private member_ `FRenderCommandFence SlatePostRTFences[(uint8)ESlatePostRT::Num];`
- L186 _private member_ `} PostProcessRenderTargets;`
- L195 _private member_ `} ScreenshotState;`
- L197 _private prototype_ `void OnSceneRemoved(FSceneInterface* Scene);`
- L200 _private member_ `TArray<FSceneInterface*> ActiveScenes;` — These are state management variables for Scenes on the game thread. A similar copy exists on the RHI Rendering Policy for the rendering thread.
- L201 _private member_ `int32 CurrentSceneIndex = -1;`
- L202 _private member_ `FDelegateHandle SceneRemovedHandle;`
- L205 _private member_ `uint32 ResourceVersion = 0;` — Version that increments when it is okay to clean up older cached resources

#### struct `FSlateRHIRenderer::(anonymous)`  
``  
_L164-170_

#### struct `FSlateRHIRenderer::(anonymous)`  
``  
_L183-186_

#### struct `FSlateRHIRenderer::(anonymous)`  
``  
_L189-195_

#### Free symbols / members of external scopes

- L24 _prototype_ `extern FMatrix CreateSlateProjectionMatrix(uint32 Width, uint32 Height);`
- L27 _variable_ `const uint32 NumDrawBuffers = 3;` — Number of draw buffers that can be active at any given time
- L30 _macro_ `#define WITH_SLATE_VISUALIZERS !(UE_BUILD_SHIPPING || UE_BUILD_TEST)` — Enable to visualize overdraw in Slate
- L165 _member_ `TArray<FSlateCachedFastPathRenderingData*, FConcurrentLinearArrayAllocator> CachedFastPathRenderingData;` (scope `FSlateRHIRenderer::__anonca9ca47e0108`)
- L166 _member_ `TArray<FSlateCachedElementData*, FConcurrentLinearArrayAllocator> CachedElementData;` (scope `FSlateRHIRenderer::__anonca9ca47e0108`)
- L168 _function_ `bool IsEmpty() const` (scope `FSlateRHIRenderer::__anonca9ca47e0108`)
- L190 _member_ `FIntRect ViewRect;` (scope `FSlateRHIRenderer::__anonca9ca47e0308`)
- L191 _member_ `FSlateViewportInfo* ViewportToCapture = nullptr;` (scope `FSlateRHIRenderer::__anonca9ca47e0308`)
- L192 _member_ `TArray<FColor>* ColorData = nullptr;` (scope `FSlateRHIRenderer::__anonca9ca47e0308`)
- L193 _member_ `TArray<FLinearColor>* ColorDataHDR = nullptr;` (scope `FSlateRHIRenderer::__anonca9ca47e0308`)

### `Source/Runtime/SlateRHIRenderer/Private/SlateRHIRenderingPolicy.h` (Private)


#### class `FSlateRHIRenderingPolicy`  
`class FSlateRHIRenderingPolicy final : public FSlateRenderingPolicy`  
_L31-46_
- inherits: `FSlateRenderingPolicy`
- L34 _public prototype_ `FSlateRHIRenderingPolicy(TSharedRef<FSlateFontServices> InSlateFontServices, TSharedRef<FSlateRHIResourceManager> InResourceManager);`
- L36 _public function_ `virtual TSharedRef<FSlateShaderResourceManager> GetResourceManager() const override`
- L37 _public function_ `virtual bool IsVertexColorInLinearSpace() const override`
- L39 _public function_ `FSlateRHIResourceManager& GetResourceManagerRHI() const`
- L41 _public prototype_ `virtual void AddSceneAt(FSceneInterface* Scene, int32 Index) override;`
- L42 _public prototype_ `virtual void ClearScenes() override;`
- L45 _private member_ `TSharedRef<FSlateRHIResourceManager> ResourceManager;`

#### struct `FSlateElementsBuffers`  
`struct FSlateElementsBuffers`  
_L48-52_
- L50 _public member_ `FRDGBuffer* VertexBuffer = nullptr;`
- L51 _public member_ `FRDGBuffer* IndexBuffer = nullptr;`

#### struct `FSlateDrawElementsPassInputs`  
`struct FSlateDrawElementsPassInputs`  
_L56-76_
- L58 _public member_ `FRDGTexture* StencilTexture = nullptr;`
- L59 _public member_ `FRDGTexture* ElementsTexture = nullptr;`
- L60 _public member_ `FRDGTexture* SceneViewportTexture = nullptr;`
- L61 _public member_ `ERenderTargetLoadAction ElementsLoadAction = ERenderTargetLoadAction::ENoAction;`
- L62 _public member_ `FSlateElementsBuffers ElementsBuffers;`
- L63 _public member_ `FMatrix44f ElementsMatrix;`
- L64 _public member_ `FVector2f ElementsOffset = FVector2f::Zero();`
- L65 _public member_ `FIntRect SceneViewRect;`
- L66 _public member_ `FIntPoint CursorPosition = FIntPoint::ZeroValue;`
- L67 _public member_ `FGameTime Time;`
- L68 _public member_ `EDisplayColorGamut HDRDisplayColorGamut = EDisplayColorGamut::sRGB_D65;`
- L69 _public member_ `float HDRPaperWhiteInNits = 203.f;`
- L70 _public member_ `ESlatePostRT UsedSlatePostBuffers = ESlatePostRT::None;`
- L71 _public member_ `float ViewportScaleUI = 1.0f;`
- L72 _public member_ `bool bWireframe = false;`
- L73 _public member_ `bool bElementsTextureIsHDRDisplay = false;`
- L74 _public member_ `bool bAllowGammaCorrection = true;`
- L75 _public member_ `bool bAllowColorDeficiencyCorrection = true;`

#### Free symbols / members of external scopes

- L54 _prototype_ `FSlateElementsBuffers BuildSlateElementsBuffers(FRDGBuilder& GraphBuilder, FSlateBatchData& BatchData);`
- L78 _prototype_ `void AddSlateDrawElementsPass( FRDGBuilder& GraphBuilder, const FSlateRHIRenderingPolicy& RenderingPolicy, const FSlateDrawElementsPassInputs& Inputs, TConstArrayView<FSlateRenderBatch> RenderBatches, int32 FirstBatchIndex, TInterval<int32> LayerRange = TInterval<int32>(std::numeric_limits<int32>::min(), std::numeric_limits<int32>::max()));`

### `Source/Runtime/SlateRHIRenderer/Private/SlateRHIResourceManager.h` (Private)


#### struct `FMaterialKey`  
`struct FMaterialKey`  
_L31-52_
- desc: Lookup key for materials.  Sometimes the same material is used with different masks so there must be unique resource per material/mask combination
- L33 _public member_ `FObjectKey Material;`
- L34 _public member_ `const FVector2f ImageSize;`
- L35 _public member_ `int32 MaskKey;`
- L37 _public function_ `FMaterialKey(const UMaterialInterface* InMaterial, const FVector2f InImageSize, int32 InMaskKey) : Material(InMaterial) , ImageSize(InImageSize) , MaskKey(InMaskKey)`

#### struct `FDynamicResourceMap`  
`struct FDynamicResourceMap`  
_L54-109_
- L57 _public prototype_ `FDynamicResourceMap();`
- L59 _public prototype_ `TSharedPtr<FSlateDynamicTextureResource> GetDynamicTextureResource( FName ResourceName ) const;`
- L61 _public prototype_ `TSharedPtr<FSlateUTextureResource> GetUTextureResource( UTexture* TextureObject ) const;`
- L63 _public prototype_ `TSharedPtr<FSlateAtlasedTextureResource> GetAtlasedTextureResource(UTexture* InObject) const;`
- L65 _public prototype_ `TSharedPtr<FSlateMaterialResource> GetMaterialResource( const FMaterialKey& InKey ) const;`
- L67 _public prototype_ `void AddUTextureResource( UTexture* TextureObject, TSharedRef<FSlateUTextureResource> InResource );`
- L68 _public prototype_ `void RemoveUTextureResource( UTexture* TextureObject );`
- L70 _public prototype_ `void AddDynamicTextureResource( FName ResourceName, TSharedRef<FSlateDynamicTextureResource> InResource);`
- L71 _public prototype_ `void RemoveDynamicTextureResource( FName ResourceName );`
- L73 _public prototype_ `void AddMaterialResource( const FMaterialKey& InKey, TSharedRef<FSlateMaterialResource> InResource );`
- L74 _public prototype_ `void RemoveMaterialResource( const FMaterialKey& InKey );`
- L76 _public prototype_ `void AddAtlasedTextureResource(UTexture* TextureObject, TSharedRef<FSlateAtlasedTextureResource> InResource);`
- L77 _public prototype_ `void RemoveAtlasedTextureResource(UTexture* TextureObject);`
- L79 _public prototype_ `FSlateShaderResourceProxy* FindOrCreateAtlasedProxy(UObject* InObject);`
- L81 _public prototype_ `void Empty();`
- L83 _public prototype_ `void EmptyUTextureResources();`
- L84 _public prototype_ `void EmptyMaterialResources();`
- L85 _public prototype_ `void EmptyDynamicTextureResources();`
- L87 _public prototype_ `void ReleaseResources();`
- L89 _public function_ `uint32 GetNumObjectResources() const`
- L92 _public prototype_ `void RemoveExpiredTextureResources(TArray< TSharedPtr<FSlateUTextureResource> >& RemovedTextures);`
- L93 _public prototype_ `void RemoveExpiredMaterialResources(TArray< TSharedPtr<FSlateMaterialResource> >& RemovedMaterials);`
- L96 _private member_ `TMap<FName, TSharedPtr<FSlateDynamicTextureResource> > NativeTextureMap;`
- L99 _private typedef_ `typedef TMap<TWeakObjectPtr<UTexture>, TSharedPtr<FSlateUTextureResource> > FTextureResourceMap;` — Map of all texture resources
- L100 _private member_ `FTextureResourceMap TextureMap;`
- L103 _private typedef_ `typedef TMap<FMaterialKey, TSharedPtr<FSlateMaterialResource> > FMaterialResourceMap;` — Map of all material resources
- L104 _private member_ `FMaterialResourceMap MaterialMap;`
- L107 _private typedef_ `typedef TMap<TWeakObjectPtr<UObject>, TSharedPtr<FSlateAtlasedTextureResource> > FObjectResourceMap;` — Map of all object resources
- L108 _private member_ `FObjectResourceMap ObjectMap;`

#### class `FSlateRHIResourceManager`  
`class FSlateRHIResourceManager : public ISlateAtlasProvider, public FSlateShaderResourceManager, public FTickableGameObject`  
_L114-328_
- inherits: `ISlateAtlasProvider,FSlateShaderResourceManager,FTickableGameObject`
- desc: Stores a mapping of texture names to their RHI texture resource
- L117 _public prototype_ `FSlateRHIResourceManager();`
- L118 _public prototype_ `virtual ~FSlateRHIResourceManager();`
- L121 _public prototype_ `virtual int32 GetNumAtlasPages() const override;` — ISlateAtlasProvider interface
- L122 _public prototype_ `virtual FSlateShaderResource* GetAtlasPageResource(const int32 InIndex) const override;`
- L123 _public prototype_ `virtual bool IsAtlasPageResourceAlphaOnly(const int32 InIndex) const override;`
- L125 _public prototype_ `virtual FAtlasSlotInfo GetAtlasSlotInfoAtPosition(FIntPoint InPosition, int32 AtlasIndex) const override;`
- L129 _public function_ `virtual ETickableTickType GetTickableTickType() const override` — FTickableGameObject interface
- L130 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L131 _public function_ `virtual bool IsTickableInEditor() const override`
- L132 _public function_ `virtual TStatId GetStatId() const override`
- L133 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L139 _public prototype_ `void LoadUsedTextures();` — Loads and creates rendering resources for all used textures. In this implementation all textures must be known at startup time or they will not be found
- L141 _public prototype_ `void LoadStyleResources( const ISlateStyle& Style );`
- L146 _public prototype_ `void UpdateTextureAtlases();` — Updates texture atlases if needed
- L147 _public prototype_ `void ConditionalFlushAtlases();`
- L150 _public prototype_ `virtual FSlateShaderResourceProxy* GetShaderResource(const FSlateBrush& InBrush, FVector2f LocalSize, float DrawScale) override;` — FSlateShaderResourceManager interface
- L151 _public prototype_ `virtual FSlateShaderResource* GetFontShaderResource( int32 InTextureAtlasIndex, FSlateShaderResource* FontTextureAtlas, const class UObject* FontMaterial ) override;`
- L152 _public prototype_ `virtual ISlateAtlasProvider* GetTextureAtlasProvider() override;`
- L159 _public prototype_ `TSharedPtr<FSlateUTextureResource> MakeDynamicUTextureResource( UTexture* InTextureObject);` — Makes a dynamic texture resource and begins use of it @param InTextureObject	The texture object to create the resource from
- L169 _public prototype_ `TSharedPtr<FSlateDynamicTextureResource> MakeDynamicTextureResource( FName ResourceName, uint32 Width, uint32 Height, const TArray< uint8 >& Bytes );` — Makes a dynamic texture resource and begins use of it @param ResourceName			The name identifier of the resource @param Width					The width of the resource @param Height				The height of the resource @param Bytes					The payload containing the resource
- L171 _public prototype_ `TSharedPtr<FSlateDynamicTextureResource> MakeDynamicTextureResource(FName ResourceName, FSlateTextureDataRef TextureData);`
- L178 _public prototype_ `TSharedPtr<FSlateDynamicTextureResource> GetDynamicTextureResourceByName( FName ResourceName );` — Find a dynamic texture resource @param ResourceName			The name identifier of the resource
- L183 _public prototype_ `bool ContainsTexture( const FName& ResourceName ) const;` — Returns true if a texture resource with the passed in resource name is available
- L186 _public prototype_ `void ReleaseDynamicResource( const FSlateBrush& InBrush );` — Releases a specific dynamic resource
- L193 _public prototype_ `virtual bool LoadTexture( const FName& TextureName, const FString& ResourcePath, uint32& Width, uint32& Height, TArray<uint8>& DecodedImage );` — Creates a new texture from the given texture name @param TextureName	The name of the texture to load
- L194 _public prototype_ `virtual bool LoadTexture( const FSlateBrush& InBrush, uint32& Width, uint32& Height, TArray<uint8>& DecodedImage );`
- L200 _public prototype_ `void ReleaseResources();` — Releases rendering resources
- L207 _public prototype_ `void ReloadTextures();` — Reloads texture resources for all used textures. @param InExtraResources     Optional list of textures to create that aren't in the style.
- L209 _public prototype_ `int32 GetSceneCount();`
- L210 _public prototype_ `FSceneInterface* GetSceneAt(int32 Index);`
- L211 _public prototype_ `void AddSceneAt(FSceneInterface* Scene, int32 Index);`
- L212 _public prototype_ `void ClearScenes();`
- L214 _public function_ `FCriticalSection* GetResourceCriticalSection()`
- L217 _private prototype_ `void CreateVectorGraphicsCache();`
- L219 _private prototype_ `void OnPreGarbageCollect();`
- L220 _private prototype_ `void OnPostGarbageCollect();`
- L222 _private prototype_ `void TryToCleanupExpiredResources(bool bForceCleanup);`
- L223 _private prototype_ `void CleanupExpiredResources();`
- L228 _private prototype_ `void DeleteResources();` — Deletes resources created by the manager
- L233 _private prototype_ `void DeleteUObjectBrushResources();` — Deletes re-creatable brush resources - a soft reset.
- L238 _private prototype_ `void DeleteBrushResourcesCommand();` — Debugging command to try forcing a refresh of UObject brushes.
- L245 _private prototype_ `void CreateTextures( const TArray< const FSlateBrush* >& Resources );` — Creates textures from files on disk and atlases them if possible @param Resources	The brush resources to load images for
- L252 _private prototype_ `FSlateShaderResourceProxy* GenerateTextureResource( const FNewTextureInfo& Info, const FName TextureName );` — Generates rendering resources for a texture @param Info	Information on how to generate the texture
- L260 _private prototype_ `FSlateShaderResourceProxy* FindOrCreateDynamicTextureResource( const FSlateBrush& InBrush );` — Returns a texture rendering resource from for a dynamically loaded texture or utexture object Note: this will load the UTexture or image if needed @param InBrush	Slate brush for the dynamic resource
- L267 _private prototype_ `FSlateMaterialResource* GetMaterialResource( const UObject* InMaterial, const FSlateBrush* InBrush, FSlateShaderResource* TextureMask, int32 InMaskKey );` — Returns a rendering resource for a material @param InMaterial	The material object
- L276 _private prototype_ `FSlateShaderResourceProxy* GetVectorResource(const FSlateBrush& Brush, FVector2f LocalSize, float DrawScale);` — Returns a rendering resource for a brush that generates ector graphics (may generate it internally) @param InBrush	The brush to with texture to get @param LocalSize	The unscaled local size of the final image @param DrawScale	Any scaling applied to the final image
- L281 _private prototype_ `void OnAppExit();` — Called when the application exists before the UObject system shuts down so we can free object resources
- L286 _private prototype_ `UTexture* GetBadResourceTexture();` — Get or create the bad resource texture.
- L293 _private member_ `FCriticalSection ResourceCriticalSection;` — Necessary to grab before flushing the resource pool, as it may be being accessed by multiple threads when loading.
- L296 _private member_ `bool bResourceCriticalSectionLockedForGC;` — Was ResourceCriticalSection lock before GC and need to be released
- L299 _private member_ `bool bExpiredResourcesNeedCleanup;` — Attempt to cleanup
- L302 _private member_ `FDynamicResourceMap DynamicResourceMap;` — Map of all active dynamic resources being used by brushes
- L304 _private member_ `TArray< TSharedPtr<FSlateUTextureResource> > UTextureFreeList;` — List of old utexture resources that are free to use as new resources
- L306 _private member_ `TArray< TSharedPtr<FSlateDynamicTextureResource> > DynamicTextureFreeList;` — List of old dynamic resources that are free to use as new resources
- L308 _private member_ `TArray< TSharedPtr<FSlateMaterialResource> > MaterialResourceFreeList;` — List of old material resources that are free to use as new resources
- L310 _private member_ `TArray<class FSlateTextureAtlasRHI*> PrecachedTextureAtlases;` — Static Texture atlases which have been created
- L312 _private member_ `TArray<class FSlateTexture2DRHIRef*> NonAtlasedTextures;` — Static Textures created that are not atlased
- L314 _private member_ `uint32 AtlasSize;` — The size of each texture atlas (square)
- L316 _private member_ `FIntPoint MaxAltasedTextureSize;` — This max size of each texture in an atlas
- L318 _private member_ `UTexture* BadResourceTexture;` — Needed for displaying an error texture when we end up with bad resources.
- L321 _private member_ `TArray<FSceneInterface*> ActiveScenes;`
- L324 _private member_ `FAutoConsoleCommand DeleteResourcesCommand;` — Debugging Commands
- L327 _private member_ `TUniquePtr<FSlateVectorGraphicsCache> VectorGraphicsCache;` — Cache for atlases generated from vector graphics

#### Free symbols / members of external scopes

- L43 _function_ `friend bool operator==(const FMaterialKey& Lhs, const FMaterialKey& Rhs)`
- L48 _function_ `friend uint32 GetTypeHash(const FMaterialKey& Key)`

### `Source/Runtime/SlateRHIRenderer/Private/SlateRHITextureAtlas.h` (Private)


#### class `FSlateTextureAtlasRHI`  
`class FSlateTextureAtlasRHI : public FSlateTextureAtlas`  
_L15-63_
- inherits: `FSlateTextureAtlas`
- desc: Represents a texture atlas for use with RHI.
- L27 _public prototype_ `FSlateTextureAtlasRHI( uint32 InWidth, uint32 InHeight, ESlateTextureAtlasPaddingStyle PaddingStyle, bool bUpdatesAfterInitialization);` — Creates and initializes a new instance. @param InWidth @param InHeight @param PaddingStyle
- L32 _public prototype_ `~FSlateTextureAtlasRHI( );` — Destructor.
- L41 _public prototype_ `virtual FSlateShaderResource* GetAtlasTexture() const override;` — Gets the atlas' underlying texture resource. @return The texture resource.
- L43 _public prototype_ `virtual void ReleaseResources() override;`
- L51 _public prototype_ `void UpdateTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FSlateTextureData* RenderThreadData);` — Updates the texture on the render thread. @param RHICmdList @param RenderThreadData
- L57 _public prototype_ `virtual void ConditionalUpdateTexture( );`
- L62 _private member_ `FSlateTexture2DRHIRef* AtlasTexture;` — The texture rendering resource

### `Source/Runtime/SlateRHIRenderer/Private/SlateShaders.h` (Private)


#### class `FSlateVertexDeclaration`  
`class FSlateVertexDeclaration : public FRenderResource`  
_L24-36_
- inherits: `FRenderResource`
- desc: The vertex declaration for the slate vertex shader
- L27 _public member_ `FVertexDeclarationRHIRef VertexDeclarationRHI;`
- L29 _public prototype_ `virtual ~FSlateVertexDeclaration() = default;`
- L32 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — Initializes the vertex declaration RHI resource
- L35 _public prototype_ `virtual void ReleaseRHI() override;` — Releases the vertex declaration RHI resource

#### class `FSlateInstancedVertexDeclaration`  
`class FSlateInstancedVertexDeclaration : public FSlateVertexDeclaration`  
_L41-48_
- inherits: `FSlateVertexDeclaration`
- desc: The vertex declaration for the slate instanced vertex shader
- L44 _public prototype_ `virtual ~FSlateInstancedVertexDeclaration() = default;`
- L47 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — Initializes the vertex declaration RHI resource

#### class `FSlateMaskingVertexDeclaration`  
`class FSlateMaskingVertexDeclaration : public FRenderResource`  
_L50-62_
- inherits: `FRenderResource`
- L53 _public member_ `FVertexDeclarationRHIRef VertexDeclarationRHI;`
- L55 _public prototype_ `virtual ~FSlateMaskingVertexDeclaration() = default;`
- L58 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — Initializes the vertex declaration RHI resource
- L61 _public prototype_ `virtual void ReleaseRHI() override;` — Releases the vertex declaration RHI resource

#### class `FSlateElementVS`  
`class FSlateElementVS : public FGlobalShader`  
_L64-74_
- inherits: `FGlobalShader`
- L67 _public prototype_ `DECLARE_GLOBAL_SHADER(FSlateElementVS);`
- L69 _public prototype_ `FSlateElementVS() = default;`
- L71 _public function_ `FSlateElementVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)`

#### class `FSlateElementPS`  
`class FSlateElementPS : public FGlobalShader`  
_L76-144_
- inherits: `FGlobalShader`
- L79 _public prototype_ `DECLARE_GLOBAL_SHADER(FSlateElementPS);`
- L81 _public prototype_ `FSlateElementPS() = default;`
- L83 _public function_ `FSlateElementPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)`
- L94 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L102 _public function_ `void SetTexture(FMeshDrawSingleShaderBindings& ShaderBindings, FRHITexture* InTexture, const FSamplerStateRHIRef SamplerState)` — Sets the texture used by this shader @param Texture	Texture resource to use when this pixel shader is bound @param SamplerState	Sampler state to use when sampling this texture
- L112 _public prototype_ `void SetVirtualTextureParameters(FMeshDrawSingleShaderBindings& ShaderBindings, FVirtualTexture2DResource* InVirtualTexture);` — Sets the texture used by this shader in case a VirtualTexture is used @param InVirtualTexture	Virtual Texture resource to use when this pixel shader is bound
- L119 _public function_ `void SetShaderParams(FMeshDrawSingleShaderBindings& ShaderBindings, const FShaderParams& InShaderParams)` — Sets shader params used by the shader @param InShaderParams Shader params to use
- L130 _public function_ `void SetDisplayGammaAndInvertAlphaAndContrast(FMeshDrawSingleShaderBindings& ShaderBindings, float InDisplayGamma, float bInvertAlpha, float InContrast)` — Sets the display gamma. @param DisplayGamma The display gamma to use

#### class `TSlateElementPS`  
`template<ESlateShader ShaderType, bool bDrawDisabledEffect, bool bUseTextureAlpha=true, bool bUseTextureGrayscale=false, bool bIsVirtualTexture=false> class TSlateElementPS : public FSlateElementPS`  
_L150-181_
- inherits: `FSlateElementPS`
- desc: Pixel shader types for all elements
- L152 _private prototype_ `DECLARE_SHADER_TYPE( TSlateElementPS, Global );`
- L155 _public function_ `TSlateElementPS()`
- L160 _public function_ `TSlateElementPS( const ShaderMetaType::CompiledShaderInitializerType& Initializer ) : FSlateElementPS( Initializer )` — Constructor.  Binds all parameters used by the shader
- L169 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)` — Modifies the compilation of this shader

#### class `FSlateDebugOverdrawPS`  
`class FSlateDebugOverdrawPS : public FSlateElementPS`  
_L186-205_
- inherits: `FSlateElementPS`
- desc: Pixel shader for debugging Slate overdraw
- L188 _private prototype_ `DECLARE_SHADER_TYPE( FSlateDebugOverdrawPS, Global );`
- L191 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Indicates that this shader should be cached
- L196 _public function_ `FSlateDebugOverdrawPS()`
- L201 _public function_ `FSlateDebugOverdrawPS( const ShaderMetaType::CompiledShaderInitializerType& Initializer ) : FSlateElementPS( Initializer )` — Constructor.  Binds all parameters used by the shader

#### class `FSlateDebugBatchingPS`  
`class FSlateDebugBatchingPS : public FSlateElementPS`  
_L210-243_
- inherits: `FSlateElementPS`
- desc: Pixel shader for debugging Slate overdraw
- L212 _private prototype_ `DECLARE_SHADER_TYPE(FSlateDebugBatchingPS, Global );`
- L215 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)` — Indicates that this shader should be cached
- L220 _public function_ `FSlateDebugBatchingPS()`
- L225 _public function_ `FSlateDebugBatchingPS( const ShaderMetaType::CompiledShaderInitializerType& Initializer ) : FSlateElementPS( Initializer )` — Constructor.  Binds all parameters used by the shader
- L236 _public function_ `void SetBatchColor(FMeshDrawSingleShaderBindings& ShaderBindings, const FLinearColor& InBatchColor)` — Sets shader params used by the shader @param InShaderParams Shader params to use

#### class `FSlateMaskingVS`  
`class FSlateMaskingVS : public FGlobalShader`  
_L245-254_
- inherits: `FGlobalShader`
- L248 _public prototype_ `DECLARE_GLOBAL_SHADER(FSlateMaskingVS);`
- L249 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSlateMaskingVS, FGlobalShader);`

#### class `FSlateMaskingPS`  
`class FSlateMaskingPS : public FGlobalShader`  
_L256-264_
- inherits: `FGlobalShader`
- L259 _public prototype_ `DECLARE_GLOBAL_SHADER(FSlateMaskingPS);`
- L260 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FSlateMaskingPS, FGlobalShader);`

#### Free symbols / members of external scopes

- L16 _externvar_ `extern EColorVisionDeficiency GSlateColorDeficiencyType;`
- L17 _externvar_ `extern int32 GSlateColorDeficiencySeverity;`
- L18 _externvar_ `extern bool GSlateColorDeficiencyCorrection;`
- L19 _externvar_ `extern bool GSlateShowColorDeficiencyCorrectionWithDeficiency;`
- L267 _externvar_ `extern TGlobalResource<FSlateVertexDeclaration> GSlateVertexDeclaration;` — The simple element vertex declaration.
- L270 _externvar_ `extern TGlobalResource<FSlateInstancedVertexDeclaration> GSlateInstancedVertexDeclaration;` — The instanced simple element vertex declaration.
- L273 _externvar_ `extern TGlobalResource<FSlateMaskingVertexDeclaration> GSlateMaskingVertexDeclaration;` — The vertex declaration for rendering stencil masks.

### `Source/Runtime/SlateRHIRenderer/Private/SlateUTextureResource.h` (Private)


#### class `FSlateBaseUTextureResource`  
`class FSlateBaseUTextureResource : public FSlateShaderResource`  
_L12-66_
- inherits: `FSlateShaderResource`
- desc: A resource for rendering a UTexture object in Slate
- L15 _public prototype_ `FSlateBaseUTextureResource(UTexture* InTexture);`
- L16 _public prototype_ `virtual ~FSlateBaseUTextureResource();`
- L21 _public prototype_ `virtual uint32 GetWidth() const;` — FSlateShaderRsourceInterface
- L22 _public prototype_ `virtual uint32 GetHeight() const;`
- L23 _public prototype_ `virtual ESlateShaderResource::Type GetType() const;`
- L24 _public prototype_ `virtual ESlatePostRT GetUsedSlatePostBuffers() const override;`
- L25 _public prototype_ `virtual bool RequiresVirtualTextureFeedback() const override;`
- L28 _public function_ `FTextureRHIRef AccessRHIResource()` — Gets the RHI resource used for rendering and updates the last render time for texture streaming
- L41 _public function_ `UTexture* GetTextureObject() const`
- L45 _public prototype_ `virtual void CheckForStaleResources() const override;`
- L50 _protected prototype_ `void UpdateDebugName();`
- L54 _protected member_ `UTexture* TextureObject;` — Texture UObject.  Note: lifetime is managed externally
- L58 _protected member_ `TWeakObjectPtr<UTexture> ObjectWeakPtr;` — Used to guard against crashes when the material object is deleted.  This is expensive so we do not do it in shipping
- L59 _protected member_ `FName DebugName;`
- L63 _protected member_ `ESlatePostRT CachedSlatePostBuffers;` — Cached slate SlatePostRT assets / buffers in use
- L65 _protected member_ `bool CachedIsVirtualTexture;` — Cached result of whether we use virtual textures

#### class `FSlateUTextureResource`  
`class FSlateUTextureResource : public FSlateBaseUTextureResource`  
_L70-86_
- inherits: `FSlateBaseUTextureResource`
- desc: A resource for rendering a UTexture object in Slate
- L73 _public member_ `static TSharedPtr<FSlateUTextureResource> NullResource;`
- L75 _public prototype_ `FSlateUTextureResource(UTexture* InTexture);`
- L76 _public prototype_ `virtual ~FSlateUTextureResource();`
- L81 _public prototype_ `void UpdateTexture(UTexture* InTexture);` — Updates the rendering resource with a potentially new texture
- L82 _public prototype_ `void ResetTexture();`
- L85 _public member_ `FSlateShaderResourceProxy* Proxy;` — Slate rendering proxy

### `Source/Runtime/SlateRHIRenderer/Private/SlateUpdatableBuffer.h` (Private)


#### class `FSlateUpdatableInstanceBuffer`  
`class FSlateUpdatableInstanceBuffer final : public ISlateUpdatableInstanceBuffer`  
_L14-48_
- inherits: `ISlateUpdatableInstanceBuffer`
- desc: Represents a per instance data buffer for a custom Slate mesh element
- L32 _private member_ `} *Proxy;`
- L35 _public prototype_ `FSlateUpdatableInstanceBuffer(int32 InstanceCount);`
- L36 _public prototype_ `~FSlateUpdatableInstanceBuffer();`
- L40 _private function_ `virtual uint32 GetNumInstances() const override final` — BEGIN ISlateUpdatableInstanceBuffer
- L41 _private function_ `virtual ISlateUpdatableInstanceBufferRenderProxy* GetRenderProxy() const override final`
- L42 _private prototype_ `virtual void Update(FSlateInstanceBufferData& Data) override final;`
- L47 _private member_ `uint32 NumInstances = 0;`

#### struct `FSlateUpdatableInstanceBuffer::FRenderProxy`  
`struct FRenderProxy final : public ISlateUpdatableInstanceBufferRenderProxy`  
_L17-32_
- inherits: `ISlateUpdatableInstanceBufferRenderProxy`
- desc: Owned by the render thread
- L19 _public member_ `TSlateElementVertexBuffer<FVector4> InstanceBufferResource;`
- L21 _public function_ `virtual ~FRenderProxy()`
- L26 _public prototype_ `void Update(FRHICommandListImmediate& RHICmdList, FSlateInstanceBufferData& Data);`
- L28 _public function_ `FRHIBuffer* GetRHI() const override`

### `Source/Runtime/SlateRHIRenderer/Public/FX/SlateFXSubsystem.h` (Public)


#### class `USlateFXSubsystem`  
`class USlateFXSubsystem : public USlateFXBaseSubsystem`  
_L15-44_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Slate FX Subsystem (RHI)")`
- inherits: `USlateFXBaseSubsystem`
- L21 _public prototype_ `static TSharedPtr<FSlateRHIPostBufferProcessorProxy> GetPostProcessorProxy(ESlatePostRT InSlatePostBufferBit);`
- L24 _public prototype_ `virtual void BeginDestroy() override;`
- L28 _public prototype_ `TSharedPtr<FSlateRHIPostBufferProcessorProxy> GetSlatePostProcessorProxy(ESlatePostRT InPostBufferBit);` — Get post processor proxy for a particular post buffer index, if it exists
- L31 _public prototype_ `USlatePostBufferProcessor* GetSlatePostProcessor(ESlatePostRT InPostBufferBit);` — Get post processor for a particular post buffer index, if it exists
- L35 _protected prototype_ `virtual void OnInitProcessors() override;`
- L36 _protected prototype_ `virtual void OnCleanupProcessors() override;`
- L40 _private prototype_ `static TSharedPtr<FSlateRHIPostBufferProcessorProxy> CreatePostBufferProcessorProxy(TSubclassOf<USlatePostBufferProcessor> PostProcessorClass);`
- L43 _private member_ `TMap<ESlatePostRT, TSharedPtr<FSlateRHIPostBufferProcessorProxy>> SlatePostBufferProcessorProxies;` — Map of post RT buffer index to buffer processor renderthread proxies, if they exist

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SLATERHIRENDERER_API`

### `Source/Runtime/SlateRHIRenderer/Public/FX/SlateRHIPostBufferBlur.h` (Public)


#### class `FSlatePostBufferBlurProxy`  
`class FSlatePostBufferBlurProxy : public FSlateRHIPostBufferProcessorProxy`  
_L14-38_
- inherits: `FSlateRHIPostBufferProcessorProxy`
- desc: Proxy for post buffer processor that the renderthread uses to perform processing This proxy exists because generally speaking usage on UObjects on the renderthread is a race condition due to UObjects being managed / updated by the game thread
- L20 _public prototype_ `virtual void PostProcess_Renderthread(FRDGBuilder& GraphBuilder, const FScreenPassTexture& InputTexture, const FScreenPassTexture& OutputTexture) override;`
- L21 _public prototype_ `virtual void OnUpdateValuesRenderThread() override;`
- L25 _public member_ `float GaussianBlurStrength_RenderThread = 10;` — Blur strength to use when processing, renderthread version actually used to draw. Must be updated via render command except during initialization.
- L32 _public member_ `float GaussianBlurStrengthPreDraw = 10;` — Blur strength can be updated from both renderthread during draw and gamethread update. Store the last value gamethread provided so we know if we should use the renderthread value or gamethread value. We will use the most recently updated one.
- L37 _protected member_ `FRenderCommandFence ParamUpdateFence;` — Fence to allow for us to queue only one update per draw command from the gamethread

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SLATERHIRENDERER_API`

### `Source/Runtime/SlateRHIRenderer/Public/FX/SlateRHIPostBufferProcessor.h` (Public)


#### class `FSlateRHIPostBufferProcessorProxy`  
`class FSlateRHIPostBufferProcessorProxy : public FSlatePostBufferProcessorProxy`  
_L22-55_
- inherits: `FSlatePostBufferProcessorProxy`
- desc: Proxy for post buffer processor that the renderthread uses to perform processing This proxy exists because generally speaking usage on UObjects on the renderthread is a race condition due to UObjects being managed / updated by the game thread
- L27 _public prototype_ `virtual ~FSlateRHIPostBufferProcessorProxy() = default;`
- L30 _public function_ `virtual void PostProcess_Renderthread(FRDGBuilder& GraphBuilder, const FScreenPassTexture& InputTexture, const FScreenPassTexture& OutputTexture)` — Called on the render thread to run a post processing operation on the input texture and produce the output texture.
- L39 _public function_ `virtual void OnUpdateValuesRenderThread()` — Called when an post buffer update element is added to a renderbatch, gives proxies a chance to queue updates to their renderthread values based on the UObject processor. These updates should likely be guarded by an 'FRenderCommandFence' to avoid duplicate updates
- L46 _public function_ `void SetOwningProcessorObject(USlatePostBufferProcessor* InParentObject)` — Set the UObject that we are a renderthread proxy for, useful for doing gamethread updates from the proxy
- L54 _protected member_ `TWeakObjectPtr<USlatePostBufferProcessor> ParentObject;` — Pointer to processor that we are a proxy for, external design constraints should ensure that this is always valid

#### class `USlateRHIPostBufferProcessor`  
`class UE_DEPRECATED(5.8, "Use USlatePostBufferProcessor instead") USlateRHIPostBufferProcessor : public UObject`  
_L63-77_
- inherits: `UObject`
- desc: Base class for types that can process the backbuffer scene into the slate post buffer. You need to create a renderthread proxy that derives from 'FSlateRHIPostBufferProcessorProxy' For an example see: USlatePostBufferBlur.
- L68 _public prototype_ `virtual ~USlateRHIPostBufferProcessor() = default;`
- L73 _public function_ `virtual TSharedPtr<FSlateRHIPostBufferProcessorProxy> GetRenderThreadProxy()` — Gets proxy for this post buffer processor, for execution on the renderthread

### `Source/Runtime/SlateRHIRenderer/Public/Interfaces/ISlate3DRenderer.h` (Public)


#### class `ISlate3DRenderer`  
`class ISlate3DRenderer : public TSharedFromThis<ISlate3DRenderer, ESPMode::ThreadSafe>`  
_L12-84_
- inherits: `TSharedFromThis<ISlate3DRenderer,ESPMode::ThreadSafe>`
- L15 _public prototype_ `virtual ~ISlate3DRenderer() = default;`
- L49 _public prototype_ `virtual void SetUseGammaCorrection(bool bUseGammaCorrection) = 0;` — set if this renderer should render in gamma space by default.
- L50 _public prototype_ `virtual void SetApplyColorDeficiencyCorrection(bool bApplyColorCorrection) = 0;`
- L54 _public function_ `virtual FSlateDrawBuffer& GetDrawBuffer()` — `UE_DEPRECATED(5.1, "Use ISlate3DRenderer::AcquireDrawBuffer instead and release the draw buffer.")` — @return The free buffer for drawing
- L60 _public prototype_ `virtual FSlateDrawBuffer& AcquireDrawBuffer() = 0;` — @return The free buffer for drawing
- L63 _public prototype_ `virtual void ReleaseDrawBuffer(FSlateDrawBuffer& InWindowDrawBuffer) = 0;` — Return the previously acquired buffer.
- L71 _public prototype_ `virtual void DrawWindow_GameThread(FSlateDrawBuffer& DrawBuffer) = 0;` — Batches the draw elements in the buffer to prepare it for rendering. Call in the game thread before sending to the render thread. @param DrawBuffer The draw buffer to prepare
- L80 _public prototype_ `virtual void DrawWindowToTarget_RenderThread(FRDGBuilder& GraphBuilder, const struct FRenderThreadUpdateContext& Context) = 0;` — Renders the batched draw elements of the draw buffer to the given render target. Call after preparing the draw buffer and render target on the game thread. @param RenderTarget The render target to render the contents of the draw buffer to @param InDrawBuffer The draw buffer containing the batched elements to render
- L83 _public function_ `virtual void DrawWindowToTarget_RenderThread(FRHICommandListImmediate& RHICmdList, const struct FRenderThreadUpdateContext& Context)` — `UE_DEPRECATED(5.5, "Use the RDG version instead.")`

#### struct `ISlate3DRenderer::FScopedAcquireDrawBuffer`  
`struct FScopedAcquireDrawBuffer`  
_L19-46_
- desc: Acquire the draw buffer and release it at the end of the scope.
- L21 _public function_ `FScopedAcquireDrawBuffer(ISlate3DRenderer& InSlateRenderer, bool bInDeferRenderTargetUpdate = false) : SlateRenderer(InSlateRenderer) , DrawBuffer(InSlateRenderer.AcquireDrawBuffer()) , bDeferRenderTargetUpdate(bInDeferRenderTargetUpdate)`
- L27 _public function_ `~FScopedAcquireDrawBuffer()`
- L34 _public prototype_ `FScopedAcquireDrawBuffer(const FScopedAcquireDrawBuffer&) = delete;`
- L35 _public prototype_ `FScopedAcquireDrawBuffer& operator=(const FScopedAcquireDrawBuffer&) = delete;`
- L37 _public function_ `FSlateDrawBuffer& GetDrawBuffer()`
- L43 _private member_ `ISlate3DRenderer& SlateRenderer;`
- L44 _private member_ `FSlateDrawBuffer& DrawBuffer;`
- L45 _private member_ `bool bDeferRenderTargetUpdate;`

#### Free symbols / members of external scopes

- L86 _typedef_ `typedef TSharedPtr<ISlate3DRenderer, ESPMode::ThreadSafe> ISlate3DRendererPtr;`

### `Source/Runtime/SlateRHIRenderer/Public/Interfaces/ISlateRHIRendererModule.h` (Public)


#### class `ISlateRHIRendererModule`  
`class ISlateRHIRendererModule : public IModuleInterface`  
_L21-38_
- inherits: `IModuleInterface`
- desc: Interface for the Slate RHI Renderer module.
- L31 _public prototype_ `virtual TSharedRef<FSlateRenderer> CreateSlateRHIRenderer( ) = 0;` — Creates a Slate RHI renderer. @return A new renderer.
- L33 _public prototype_ `virtual TSharedRef<ISlate3DRenderer, ESPMode::ThreadSafe> CreateSlate3DRenderer(bool bUseGammaCorrection) = 0;`
- L35 _public prototype_ `virtual TSharedRef<ISlateFontAtlasFactory> CreateSlateFontAtlasFactory() = 0;`
- L37 _public prototype_ `virtual TSharedRef<ISlateUpdatableInstanceBuffer> CreateInstanceBuffer( int32 InitialInstanceCount ) = 0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace SlateRHIConstants`
- L15 _variable_ `const int32 NumBuffers = 3;` (scope `SlateRHIConstants`) — Number of vertex and index buffers we swap between when drawing windows

### `Source/Runtime/SlateRHIRenderer/Public/Interfaces/SlateRHIRenderingPolicyInterface.h` (Public)


#### struct `FSlatePostProcessSimpleBlurPassInputs`  
`struct FSlatePostProcessSimpleBlurPassInputs`  
_L7-12_
- L9 _public member_ `FScreenPassTexture InputTexture;`
- L10 _public member_ `FScreenPassTexture OutputTexture;`
- L11 _public member_ `float Strength = 0.0f;`

#### class `FSlateRHIRenderingPolicyInterface`  
`class UE_DEPRECATED(5.5, "FSlateRHIRenderingPolicyInterface is no longer used.") FSlateRHIRenderingPolicyInterface`  
_L27-38_
- L30 _public function_ `FSlateRHIRenderingPolicyInterface(const class FSlateRHIRenderingPolicy* InRenderingPolicy)`
- L32 _public function_ `static int32 GetProcessSlatePostBuffers()`
- L34 _public function_ `bool IsValid() const`
- L35 _public function_ `bool IsVertexColorInLinearSpace() const`
- L36 _public function_ `bool GetApplyColorDeficiencyCorrection() const`
- L37 _public function_ `void BlurRectExternal(FRHICommandListImmediate& RHICmdList, FRHITexture* BlurSrc, FRHITexture* BlurDst, FIntRect SrcRect, FIntRect DstRect, float BlurStrength) const`

#### class `ICustomSlateElementRHI`  
`class UE_DEPRECATED(5.5, "Use ICustomSlateElement instead.") ICustomSlateElementRHI : public ICustomSlateElement`  
_L40-47_
- inherits: `ICustomSlateElement`
- L45 _public function_ `virtual void Draw_RHIRenderThread(FRHICommandListImmediate& RHICmdList, const FTextureRHIRef& RenderTarget, const FSlateCustomDrawParams& Params, FSlateRHIRenderingPolicyInterface RenderingPolicyInterface)` — `UE_DEPRECATED(5.5, "Use Draw_RenderThread with an RDG builder instead")`

#### Free symbols / members of external scopes

- L14 _prototype_ `void AddSlatePostProcessCopy(FRDGBuilder& GraphBuilder, FScreenPassTexture Input, FScreenPassTexture Output);`
- L15 _prototype_ `void AddSlatePostProcessBlurPass(FRDGBuilder& GraphBuilder, const FSlatePostProcessSimpleBlurPassInputs& Inputs);`

### `Source/Runtime/SlateRHIRenderer/Public/SlateRHIRendererSettings.h` (Public)


#### enum `ESlatePostResolution`  
`enum class ESlatePostResolution : uint8`  
_L25-31_
- reflection: `UENUM(BlueprintType)`
- desc: Resolution of a particular Slate Post RT.
- L28 _public enumerator_ `Full = 0` — Full screen (window) resolution
- L30 _public enumerator_ `Half = 1` — Half resolution in each dimension (quarter by area)

#### struct `FSlatePostSettings`  
`struct FSlatePostSettings`  
_L38-82_
- reflection: `USTRUCT(BlueprintType, meta=(HiddenByDefault, DisableSplitPin))`
- desc: Settings for a particular Slate Post RT. Notably if enabled & blur by default. To be updated with additional effects & to be expandable in game code / settings.
- L44 _public prototype_ `FSlatePostSettings();`
- L53 _public member_ `uint8 bEnabled:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=BufferSettings, meta=(PinHiddenByDefault))` — Should this post buffer be enabled for updating
- L57 _public member_ `ESlatePostResolution Resolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=BufferSettings)` — Resolution of the post buffer
- L61 _public member_ `TSubclassOf<USlatePostBufferProcessor> PostProcessorClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BufferSettings, Meta = (AllowAbstract = false))` — Copy of actually loaded post processor class
- L67 _private member_ `FString PathToSlatePostRT;` — `UPROPERTY()` — Path to Slate Post RT Asset
- L72 _public function_ `const FString& GetPathToSlatePostRT() const` — Get asset name for post RT texture
- L78 _private member_ `TObjectPtr<UTextureRenderTarget2D> CachedSlatePostRT;` — `UPROPERTY(Transient)` — Cached load of Slate Post RT Asset
- L81 _private member_ `bool bLoadAttempted:1;` — True if we attempted to load the post RT asset already

#### class `USlateRHIRendererSettings`  
`class USlateRHIRendererSettings : public UDeveloperSettings`  
_L88-157_
- reflection: `UCLASS(MinimalAPI, config = Game, defaultconfig)`
- inherits: `UDeveloperSettings`
- desc: Settings used to control slate rendering
- L93 _public function_ `static const USlateRHIRendererSettings* Get()`
- L102 _public function_ `static USlateRHIRendererSettings* GetMutable()`
- L113 _public prototype_ `USlateRHIRendererSettings();`
- L114 _public prototype_ `~USlateRHIRendererSettings();`
- L117 _public prototype_ `virtual void BeginDestroy() override;`
- L124 _public prototype_ `FSlatePostSettings& GetMutableSlatePostSetting(ESlatePostRT InPostBufferBit);` — `UFUNCTION(BlueprintCallable, Category = "SlateFX")` — Get settings struct for a particular post buffer index
- L128 _public prototype_ `const FSlatePostSettings& GetSlatePostSetting(ESlatePostRT InPostBufferBit) const;` — `UFUNCTION(BlueprintCallable, Category = "SlateFX")` — Get settings struct for a particular post buffer index
- L133 _public prototype_ `UTextureRenderTarget2D* TryGetPostBufferRT(ESlatePostRT InPostBufferBit) const;` — Try to get post RT asset, returns nullptr if not already loaded
- L136 _public prototype_ `UTextureRenderTarget2D* LoadGetPostBufferRT(ESlatePostRT InPostBufferBit);` — Get post RT asset, loading if not already loaded
- L139 _public prototype_ `const TMap<ESlatePostRT, FSlatePostSettings>& GetSlatePostSettings() const;` — Get slate post settings map, non mutable
- L142 _public prototype_ `int32 GetSlatePostBufferDownscaleFactor(ESlatePostRT InPostBufferBit) const;` — Get Slate post buffer downscale factor based on its Resolution (ESlatePostResolution, Full -> 1, Half -> 2)
- L156 _private member_ `TMap<ESlatePostRT, FSlatePostSettings> SlatePostSettings;` — `UPROPERTY(config, EditAnywhere, EditFixedSize, Category = "PostProcessing")` — Map is nice since needs no editor customization. After initial run there should be no more than 5 lookups each frame.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API SLATERHIRENDERER_API`
