# Runtime / WebBrowserTexture

- module root: `Source/Runtime/WebBrowserTexture`
- headers: 4; symbols: 88
- symbol kinds: class=6, function=27, member=27, prototype=27, struct=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine, InputCore, MediaUtils, RHI, RenderCore, Serialization, Slate, SlateCore, WebBrowser
- PublicIncludePathModuleNames: MediaUtils

### `Source/Runtime/WebBrowserTexture/Public/WebBrowserTexture.h` (Public)


#### class `UWebBrowserTexture`  
`class UWebBrowserTexture : public UTexture`  
_L24-103_
- reflection: `UCLASS(hidecategories = (Adjustments, Compositing, LevelOfDetail, Object))`
- inherits: `UTexture`
- desc: Implements a texture asset for rendering webbrowser output for Android. probably should have derived from UTexture2DDynamic (not UTexture)
- L30 _private member_ `TEnumAsByte<TextureAddress> AddressX;` — The addressing mode to use for the X axis.
- L33 _private member_ `TEnumAsByte<TextureAddress> AddressY;` — The addressing mode to use for the Y axis.
- L36 _private member_ `bool AutoClear;` — Whether to clear the texture when no media is being played (default = enabled).
- L39 _private member_ `FLinearColor ClearColor;` — The color used to clear the texture if AutoClear is enabled (default = black).
- L49 _public prototype_ `float GetAspectRatio() const;` — Gets the current aspect ratio of the texture. @return Texture aspect ratio. @see GetHeight, GetWidth
- L57 _public prototype_ `int32 GetHeight() const;` — Gets the current height of the texture. @return Texture height (in pixels). @see GetAspectRatio, GetWidth
- L65 _public prototype_ `int32 GetWidth() const;` — Gets the current width of the texture. @return Texture width (in pixels). @see GetAspectRatio, GetHeight
- L69 _public prototype_ `virtual void BeginDestroy() override;`
- L70 _public prototype_ `virtual FTextureResource* CreateResource() override;`
- L71 _public prototype_ `virtual EMaterialValueType GetMaterialType() const override;`
- L72 _public prototype_ `virtual float GetSurfaceWidth() const override;`
- L73 _public prototype_ `virtual float GetSurfaceHeight() const override;`
- L74 _public function_ `virtual float GetSurfaceDepth() const override`
- L75 _public function_ `virtual uint32 GetSurfaceArraySize() const override`
- L76 _public prototype_ `virtual FGuid GetExternalTextureGuid() const override;`
- L77 _public function_ `virtual ETextureClass GetTextureClass() const`
- L81 _public prototype_ `virtual FString GetDesc() override;`
- L82 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L84 _public prototype_ `void TickResource(TSharedPtr<FWebBrowserTextureSample, ESPMode::ThreadSafe> Sample);`
- L86 _public prototype_ `void SetExternalTextureGuid(FGuid guid);`
- L89 _protected prototype_ `void UnregisterPlayerGuid();` — Unregister the player's external texture GUID.
- L93 _private member_ `FIntPoint Dimensions;` — Current width and height of the resource (in pixels).
- L96 _private member_ `FGuid WebPlayerGuid;` — The previously used player GUID.
- L99 _private member_ `TSharedPtr<FWebBrowserTextureSampleQueue, ESPMode::ThreadSafe> SampleQueue;` — Texture sample queue.
- L102 _private member_ `SIZE_T Size;` — Current size of the resource (in bytes).

### `Source/Runtime/WebBrowserTexture/Public/WebBrowserTextureModule.h` (Public)


#### class `IWebBrowserTextureModule`  
`class IWebBrowserTextureModule : public IModuleInterface`  
_L12-14_
- inherits: `IModuleInterface`
- desc: WebBrowserTextureModule interface

### `Source/Runtime/WebBrowserTexture/Public/WebBrowserTextureResource.h` (Public)


#### class `FWebBrowserTextureResource`  
`class FWebBrowserTextureResource : public FRenderTarget , public FTextureResource`  
_L24-134_
- inherits: `FRenderTarget,FTextureResource`
- desc: Texture resource type for webbrowser textures.
- L37 _public prototype_ `FWebBrowserTextureResource(UWebBrowserTexture& InOwner, FIntPoint& InOwnerDim, SIZE_T& InOwnerSize);` — Creates and initializes a new instance. @param InOwner The Movie texture object to create a resource for (must not be nullptr). @param InOwnerDim The initial width and height of the texture. @param InOwnerSize The initial memory allocated to the texture.
- L40 _public function_ `virtual ~FWebBrowserTextureResource()` — Virtual destructor.
- L66 _public prototype_ `void Render(FRHICommandList& RHICmdList, const FRenderParams& Params);` — Render the texture resource. This method is called on the render thread by the WebBrowserTexture that owns this texture resource to clear or redraw the resource using the given parameters. @param Params Render parameters.
- L72 _public prototype_ `virtual FIntPoint GetSizeXY() const override;`
- L78 _public prototype_ `virtual FString GetFriendlyName() const override;`
- L79 _public prototype_ `virtual uint32 GetSizeX() const override;`
- L80 _public prototype_ `virtual uint32 GetSizeY() const override;`
- L81 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L82 _public prototype_ `virtual void ReleaseRHI() override;`
- L91 _protected prototype_ `void ClearTexture(FRHICommandList& RHICmdList, const FLinearColor& ClearColor);` — Clear the texture using the given clear color. @param ClearColor The clear color to use.
- L100 _protected prototype_ `void CopySample(FRHICommandListBase& RHICmdList, const TSharedPtr<FWebBrowserTextureSample, ESPMode::ThreadSafe>& Sample, const FLinearColor& ClearColor);` — Render the given texture sample by using it as or copying it to the render target. @param Sample The texture sample to copy. @param ClearColor The clear color to use for the output texture. @see ConvertSample
- L103 _protected prototype_ `void UpdateResourceSize();` — Calculates the current resource size and notifies the owner texture.
- L110 _protected prototype_ `void UpdateTextureReference(FRHICommandListBase& RHICmdList, FRHITexture* NewTexture);` — Set the owner's texture reference to the given texture. @param NewTexture The texture to set.
- L115 _private member_ `bool Cleared;` — Whether the texture has been cleared.
- L118 _private member_ `FLinearColor CurrentClearColor;` — Tracks the current clear color.
- L121 _private member_ `TRefCountPtr<FRHITexture> InputTarget;` — Input render target if the texture samples don't provide one (for conversions).
- L124 _private member_ `TRefCountPtr<FRHITexture> OutputTarget;` — Output render target if the texture samples don't provide one.
- L127 _private member_ `UWebBrowserTexture& Owner;` — The webbrowser texture that owns this resource.
- L130 _private member_ `FIntPoint& OwnerDim;` — Reference to the owner's texture dimensions field.
- L133 _private member_ `SIZE_T& OwnerSize;` — Reference to the owner's texture size field.

#### struct `FWebBrowserTextureResource::FRenderParams`  
`struct FRenderParams`  
_L45-56_
- desc: Parameters for the Render method.
- L48 _public member_ `FLinearColor ClearColor;` — The clear color to use when clearing the texture.
- L51 _public member_ `FGuid PlayerGuid;` — Guid associated with the texture.
- L54 _public member_ `TWeakPtr<FWebBrowserTextureSampleQueue, ESPMode::ThreadSafe> SampleSource;` — The sample source to render.

#### Free symbols / members of external scopes

- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebBrowserTexture, Log, All);`

### `Source/Runtime/WebBrowserTexture/Public/WebBrowserTextureSample.h` (Public)


#### class `FWebBrowserTextureSample`  
`class FWebBrowserTextureSample : public IMediaPoolable`  
_L18-239_
- inherits: `IMediaPoolable`
- desc: Texture sample generated by the WebBrowser.
- L24 _public function_ `FWebBrowserTextureSample() : Buffer(nullptr) , BufferSize(0) , Dim(FIntPoint::ZeroValue) , ScaleRotation(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)) , Offset(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f))` — Default constructor.
- L33 _public function_ `virtual ~FWebBrowserTextureSample()` — Virtual destructor.
- L48 _public function_ `void* GetMutableBuffer()` — Get a writable pointer to the sample buffer. @return Sample buffer.
- L60 _public function_ `bool Initialize(const FIntPoint& InDim)` — Initialize the sample. @param InDim The sample buffer's width and height (in pixels). @param InDuration The duration for which the sample is valid. @return true on success, false otherwise.
- L79 _public function_ `void InitializeBuffer(void* InBuffer, bool Copy)` — Initialize the sample with a memory buffer. @param InBuffer The buffer containing the sample data. @param Copy Whether the buffer should be copied (true) or referenced (false). @see InitializeTexture
- L118 _public function_ `int32 InitializeBufferForCopy()` — Initialize the sample for copy externally. @return The size of the buffer @see InitializeTexture
- L145 _public function_ `FRHITexture* InitializeTexture(FRHICommandListBase& RHICmdList)` — Initialize the sample with a texture resource. @param RHICmdList the command list used to create the texture. @return The texture resource object that will hold the sample data. @note This method must be called on the render thread. @see InitializeBuffer
- L172 _public function_ `void SetScaleRotationOffset(FVector4& InScaleRotation, FVector4& InOffset)` — Set the sample Scale, Rotation, Offset. @param InScaleRotation The sample scale and rotation transform (2x2). @param InOffset The sample offset.
- L182 _public function_ `virtual const void* GetBuffer()`
- L187 _public function_ `virtual FIntPoint GetDim() const`
- L192 _public function_ `virtual uint32 GetStride() const`
- L199 _public function_ `virtual FRHITexture* GetTexture() const`
- L206 _public function_ `virtual FLinearColor GetScaleRotation() const`
- L211 _public function_ `virtual FLinearColor GetOffset() const`
- L219 _private member_ `void* Buffer;` — The sample's data buffer.
- L222 _private member_ `SIZE_T BufferSize;` — Current allocation size of Buffer.
- L225 _private member_ `FIntPoint Dim;` — Width and height of the texture sample.
- L228 _private member_ `FLinearColor ScaleRotation;` — ScaleRotation for the sample.
- L231 _private member_ `FLinearColor Offset;` — Offset for the sample.
- L236 _private member_ `TRefCountPtr<FRHITexture> Texture;` — Texture resource.

#### class `FWebBrowserTextureSampleQueue`  
`class FWebBrowserTextureSampleQueue`  
_L242-402_
- L247 _public function_ `FWebBrowserTextureSampleQueue() : NumSamples(0) , PendingFlushes(0)` — Default constructor.
- L253 _public function_ `virtual ~FWebBrowserTextureSampleQueue()` — Virtual destructor.
- L263 _public function_ `int32 Num() const` — Get the number of samples in the queue. @return Number of samples. @see Enqueue, Dequeue, Peek
- L272 _public function_ `virtual bool Dequeue(TSharedPtr<FWebBrowserTextureSample, ESPMode::ThreadSafe>& OutSample)`
- L298 _public function_ `virtual bool Peek(TSharedPtr<FWebBrowserTextureSample, ESPMode::ThreadSafe>& OutSample)`
- L319 _public function_ `virtual bool Pop()`
- L345 _public function_ `virtual bool Enqueue(const TSharedPtr<FWebBrowserTextureSample, ESPMode::ThreadSafe>& Sample)`
- L365 _public function_ `virtual void RequestFlush()`
- L374 _protected function_ `void DoPendingFlushes()` — Perform any pending flushes.
- L395 _private member_ `int32 NumSamples;` — Number of samples in the queue.
- L398 _private member_ `int32 PendingFlushes;` — Number of pending flushes.
- L401 _private member_ `TQueue<TSharedPtr<FWebBrowserTextureSample, ESPMode::ThreadSafe>, EQueueMode::Mpsc> Samples;` — Audio sample queue.

#### class `FWebBrowserTextureSamplePool`  
`class FWebBrowserTextureSamplePool : public TMediaObjectPool<FWebBrowserTextureSample>`  
_L406-406_
- inherits: `TMediaObjectPool<FWebBrowserTextureSample>`
- desc: Implements a pool for WebBrowser's texture sample objects.
