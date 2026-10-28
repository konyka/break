# Plugins / MediaIOCore

- module root: `Plugins/Media/MediaIOFramework/Source/MediaIOCore`
- headers: 38; symbols: 1490
- symbol kinds: class=53, delegate=12, enum=27, enumerator=91, function=316, macro=23, member=396, namespace=48, prototype=461, struct=41, typedef=8, variable=14
- PrivateDependencyModuleNames: AudioMixer, AudioMixerCore, EditorFramework, GPUTextureTransfer, ImageWrapper, LevelEditor, Renderer, SignalProcessing, SoundFieldRendering, UnrealEd
- PublicDependencyModuleNames: AudioExtensions, Core, CoreUObject, Engine, ImageWriteQueue, Media, MediaAssets, MediaUtils, MovieSceneCapture, OpenColorIO, Projects, RHI, RenderCore, Slate, SlateCore, TimeManagement

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Internal/MediaIOCoreDisplayedFieldRegistry.h` (Internal)


#### enum `UE::MediaIOCore::EDisplayedFieldIdentity`  
`enum class EDisplayedFieldIdentity : uint8`  
_L22-27_
- desc: Which field of an interlaced source a deinterlaced sample represents.
- L24 _public enumerator_ `Unknown`
- L25 _public enumerator_ `FirstField`
- L26 _public enumerator_ `SecondField`

#### class `UE::MediaIOCore::FDisplayedFieldRegistry`  
`class FDisplayedFieldRegistry`  
_L66-141_
- desc: Process-wide bridge that lets an interlaced output place each engine frame into the output field matching the field actually displayed for a named input, independent of pipeline latency or genlock phase. Held in Internal/ and keyed by sample in a side table (rather than tagging IMediaTextureSample or FMediaIOCoreTextureSampleBase) so the feature adds no engine vtable or class-layout change for hotfixes.
- L70 _public prototype_ `static FDisplayedFieldRegistry& Get();` — Returns the process-wide singleton.
- L73 _public prototype_ `static void Initialize();` — Subscribes the render-thread recorder to the media-sample-rendered delegate. Called once at module startup.
- L76 _public prototype_ `static void Shutdown();` — Unsubscribes the recorder and drops all state. Called once at module shutdown.
- L82 _public prototype_ `void TagSample(const FMediaIOCoreTextureSampleBase* InSample, FName InSyncTag, EDisplayedFieldIdentity InField);` — Associates a not-yet-rendered MediaIO sample with the input it came from and the field it represents. No-op when InSyncTag is NAME_None. Safe to call from any thread.
- L89 _public prototype_ `void PropagateTag(const FMediaIOCoreTextureSampleBase* InSource, const FMediaIOCoreTextureSampleBase* InProxy);` — Carries a pending tag from a source sample to the just-in-time render proxy that is actually rendered. Must be called wherever a proxy copies configuration from a source sample, or the displayed-field record is lost for JIT-rendered inputs. No-op if InSource was never tagged.
- L95 _public prototype_ `bool Lookup(FName InSyncTag, uint64 InRenderFrame, EDisplayedFieldIdentity& OutField) const;` — Looks up the field displayed for the named input at the given render-thread frame. @return true if a matching record was found.
- L116 _private prototype_ `static void OnSampleRendered_RenderThread(const FTextureResource* InTextureResource, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe> InSample);` — Render-thread handler broadcast by FMediaDelegates::OnSampleRendered_RenderThread.
- L119 _private prototype_ `void Record(FName InSyncTag, uint64 InRenderFrame, EDisplayedFieldIdentity InField);` — Records that the named input displayed the given field at the given render frame.
- L125 _private member_ `TMap<const IMediaTextureSample*, FPendingTag> PendingTags;` — Pending tags keyed by the canonical IMediaTextureSample pointer (the same pointer the rendered-sample delegate hands back). Entries are erased on render and the table is bounded to MaxPendingTags.
- L128 _private member_ `TMap<FName, TArray<FRecord>> RecordsByTag;` — Bounded recent displayed-field history per input sync name.
- L131 _private member_ `mutable FCriticalSection CriticalSection;` — Guards both maps for cross-thread access (deinterlace/game vs render vs output any-thread).
- L134 _private member_ `FDelegateHandle SampleRenderedHandle;` — Handle to the OnSampleRendered_RenderThread subscription.
- L137 _private member_ `static constexpr int32 MaxRecordsPerTag = 16;` — A few frames of history per input is plenty; bounds memory and lookup cost.
- L140 _private member_ `static constexpr int32 MaxPendingTags = 256;` — Upper bound on un-rendered tags; protects against samples that are dropped before being rendered.

#### struct `UE::MediaIOCore::FDisplayedFieldRegistry::FPendingTag`  
`struct FPendingTag`  
_L99-106_
- desc: Pending field metadata for a sample that has not yet been rendered.
- L101 _public member_ `FName SyncTag;`
- L102 _public member_ `EDisplayedFieldIdentity Field = EDisplayedFieldIdentity::Unknown;`
- L105 _public member_ `int64 ValidationTimeTicks = 0;` — Sample time (ticks) captured at tag time; re-checked at render time to reject a reused pooled pointer.

#### struct `UE::MediaIOCore::FDisplayedFieldRegistry::FRecord`  
`struct FRecord`  
_L109-113_
- desc: A displayed-field record for one render-thread frame.
- L111 _public member_ `uint64 RenderFrame = 0;`
- L112 _public member_ `EDisplayedFieldIdentity Field = EDisplayedFieldIdentity::Unknown;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MEDIAIOCORE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MediaIOCore` (scope `UE`)
- L37 _namespace_ `namespace InterlaceFieldSync` (scope `UE::MediaIOCore`)
- L43 _prototype_ `bool IsEnabled();` (scope `UE::MediaIOCore::InterlaceFieldSync`) — Top-level runtime gate (MediaIO.InterlaceFieldSync.Enabled). When false the whole feature is inert and adds no per-sample overhead.
- L49 _prototype_ `FName GetSyncName();` (scope `UE::MediaIOCore::InterlaceFieldSync`) — The sync name an interlaced output should follow, or NAME_None when disabled. This is a fixed internal join key, not user-configurable; the hotfix supports the common one-input-to-one-output case.
- L56 _prototype_ `FName GetInputSyncName(const FString& InSourceUrl);` (scope `UE::MediaIOCore::InterlaceFieldSync`) — Sync name an interlaced input should tag its samples with: GetSyncName() when InSourceUrl matches the configured input URL filter (or the filter is empty, matching any input), otherwise NAME_None (the input is left untagged).

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Private/MediaCaptureHelper.h` (Private)


#### class `UE::MediaCaptureData::FMediaCaptureHelper`  
`class FMediaCaptureHelper`  
_L19-65_
- desc: Helper class to be able to friend it and call methods on input media capture
- L25 _public prototype_ `static bool AreInputsValid(const UE::MediaCaptureData::FCaptureFrameArgs& Args);` — Validates the input and output size and format compatibility.
- L28 _public prototype_ `static bool CaptureFrame(const UE::MediaCaptureData::FCaptureFrameArgs& Args, TSharedPtr<UE::MediaCaptureData::FCaptureFrame> CapturingFrame);` — Kickstart the capture process for a frame.
- L32 _public function_ `template <typename CaptureType> static void AddSyncPointPass(FRDGBuilder& GraphBuilder, UMediaCapture* MediaCapture, TSharedPtr<UE::MediaCaptureData::FCaptureFrame> CapturingFrame, FRDGViewableResource* OutputResource)` — Add a sync point pass that will wait for a readback to complete before dispatching the result to the right capture callback on the media capture.
- L59 _private prototype_ `static void ExecuteSyncPointPass(FRHICommandListImmediate& RHICmdList, UMediaCapture* MediaCapture, TSharedPtr<UE::MediaCaptureData::FCaptureFrame> CapturingFrame);` — Implementation of the sync point pass that will poll a gpu fence until it's cleared.
- L64 _private prototype_ `static void OnReadbackComplete(UMediaCapture* MediaCapture, TSharedPtr<UE::MediaCaptureData::FCaptureFrame> ReadyFrame);` — Function called when the last copy of the media capture pipeline is completed. This will handle calling the right capture callback on the MediaCapture (ie. OnRHIResourceCaptured_RenderingThread)

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MediaCaptureData` (scope `UE`)
- L52 _function_ `` (scope `UE::MediaCaptureData::FMediaCaptureHelper::AddSyncPointPass`)

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Private/MediaCaptureRenderPass.h` (Private)


#### struct `FBaseRenderPassArgs`  
`struct FBaseRenderPassArgs`  
_L24-28_
- desc: Contains the most basic arguments needed for a render pass.
- L26 _public member_ `FRDGTextureRef SourceRGBTexture;`
- L27 _public member_ `FRHICopyTextureInfo CopyInfo;`

#### struct `FColorConversionPassArgs`  
`struct FColorConversionPassArgs : public FBaseRenderPassArgs`  
_L31-34_
- inherits: `FBaseRenderPassArgs`
- desc: Contains arguments for the color conversion pass.
- L33 _public member_ `FOpenColorIORenderPassResources OCIOResources;`

#### struct `FConversionPassArgs`  
`struct FConversionPassArgs : public FBaseRenderPassArgs`  
_L37-42_
- inherits: `FBaseRenderPassArgs`
- desc: Helper struct to contain arguments for AddConversionPass
- L39 _public member_ `bool bRequiresFormatConversion = false;`
- L40 _public member_ `FVector2D SizeU = FVector2D::ZeroVector;`
- L41 _public member_ `FVector2D SizeV = FVector2D::ZeroVector;`

#### struct `UE::MediaCapture::FInitializePassOutputArgs`  
`struct FInitializePassOutputArgs`  
_L47-51_
- desc: Parameters for calling the Initialize Pass Output callback.
- L49 _public member_ `const UMediaCapture* MediaCapture = nullptr;`
- L50 _public member_ `FRDGViewableResource* InputResource = nullptr;`

#### struct `UE::MediaCapture::FRenderPass`  
`struct FRenderPass`  
_L59-110_
- desc: Describes a render pass that will be applied to the captured texture before it's copied to the final output buffer. Every render pass must have a valid InitializePassOutputDelegate and ExecutePassDelegate. The InitializePassOutput delegate will be called on the render thread when we capture the first frame. The ExecutePassDelegate will be called on the render thread in the order defined in the media capture's render pipeline.
- L61 _public typedef_ `using TRDGResource = TVariant<TRefCountPtr<IPooledRenderTarget>, TRefCountPtr<FRDGPooledBuffer>>;`
- L64 _public prototype_ `static TArray<FRenderPass> CreateRenderPasses(const UMediaCapture* MediaCapture);` — Create media capture render passes based on media capture settings.
- L66 _public prototype_ `static void AddTextureResamplePass(const UE::MediaCaptureData::FCaptureFrameArgs& Args, const FBaseRenderPassArgs& ConversionPassArgs, FRDGViewableResource* OutputTexture);` — Add a texture Resample/upsample pass to the graph builder.
- L68 _public prototype_ `static void AddColorConversionPass(const UE::MediaCaptureData::FCaptureFrameArgs& Args, const TSharedPtr<UE::MediaCaptureData::FCaptureFrame> CapturingFrame, const FColorConversionPassArgs& ConversionPassArgs, FRDGViewableResource* OutputResource);` — Add a color conversion pass to the graph builder.
- L70 _public prototype_ `static void AddConversionPass(const UE::MediaCaptureData::FCaptureFrameArgs& Args, const FConversionPassArgs& ConversionPassArgs, FRDGViewableResource* OutputResource);` — Add a format conversion pass to the graph builder.
- L72 _public prototype_ `static void AddUncompressionPass(const UE::MediaCaptureData::FCaptureFrameArgs& Args, const FBaseRenderPassArgs& UncompressionPassArgs, FRDGViewableResource* OutputResource);` — Add a pass to uncompress a compressed texture into a proper uncompressed format (currently PF_FloatRGBA)
- L75 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TRDGResource , FInitializePassOutput, const UE::MediaCapture::FInitializePassOutputArgs& , uint32 );` — This delegate should return a TRDGResource constructed with either a pooled texture or buffer.
- L80 _public member_ `FInitializePassOutput InitializePassOutputDelegate;` — Method called to initialize the pass output texture in a given capturing frame. @Note: Will be called on the render thread.
- L82 _public prototype_ `DECLARE_DELEGATE_FourParams(FExecutePass, const UE::MediaCaptureData::FCaptureFrameArgs& , const TSharedPtr<UE::MediaCaptureData::FCaptureFrame> , FRDGViewableResource* , FRDGViewableResource* );`
- L87 _public member_ `FExecutePass ExecutePassDelegate;` — Method called to execute the pass. @Note: Will be called on the render thread.
- L92 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FShouldExecutePass, const UE::MediaCaptureData::FCaptureFrameArgs& , FRDGViewableResource* );` — Delegate invoked to query whether the pass should be executed.
- L93 _public member_ `FShouldExecutePass ShouldExecutePassDelegate;`
- L96 _public member_ `FName Name;` — Name of the pass.
- L99 _public member_ `ERDGViewableResourceType OutputType = ERDGViewableResourceType::Texture;` — Whether the output of the pass is a texture or a buffer.
- L103 _private prototype_ `static FRenderPass CreateColorConversionPass(const UMediaCapture* MediaCapture);` — Creates a color conversion pass.
- L105 _private prototype_ `static FRenderPass CreateResamplePass();` — Creates a resampling pass.
- L107 _private prototype_ `static FRenderPass CreateFormatConversionPass(const UMediaCapture* MediaCapture);` — Creates a format conversion pass according to the capture settings.
- L109 _private prototype_ `static FRenderPass CreateUncompressionPass(const UMediaCapture* MediaCapture);` — Creates an uncompression pass according to the capture settings.

#### struct `UE::MediaCapture::FRenderPassFrameResources`  
`struct FRenderPassFrameResources`  
_L131-165_
- desc: Data related to render passes that live on a capturing frame.
- L134 _public function_ `TRefCountPtr<IPooledRenderTarget> GetLastRenderTarget() const` — Get the render target used by the last render pass in the pipeline.
- L140 _public function_ `TRefCountPtr<FRDGPooledBuffer> GetLastBuffer() const` — Get the buffer used by the last render pass in the pipeline.
- L146 _public function_ `FRDGViewableResource* GetFinalRDGResource(FRDGBuilder& GraphBuilder) const` — Register and retrieve the final resource used by this capture frame in the render passes.
- L160 _public member_ `FName LastRenderPassName;` — Holds the name of the last render pass.
- L162 _public member_ `TMap<FName, TRefCountPtr<IPooledRenderTarget>> PassTextureOutputs;` — Map of pass name to output render target.
- L164 _public member_ `TMap<FName, TRefCountPtr<FRDGPooledBuffer>> PassBufferOutputs;` — Map of pass name to output buffer.

#### class `UE::MediaCapture::FRenderPipeline`  
`class FRenderPipeline`  
_L171-206_
- desc: Media Capture render pipeline. Holds and initializes render passes based on a media capture's settings.
- L174 _public prototype_ `FRenderPipeline(UMediaCapture* InMediaCapture);`
- L177 _public prototype_ `void AddPass(const FRenderPass& InPass, const FName& AfterPass = NAME_None);` — Adds a render pass to the media capture render pipeline, optionally positioning it after the pass with the specified name
- L180 _public prototype_ `void InitializeResources_RenderThread(const TSharedPtr<MediaCaptureData::FCaptureFrame>& CapturingFrame, FRDGBuilder& GraphBuilder, FRDGTextureRef InputResource) const;` — Initialize and register render pass resources for a given capture frame.
- L186 _public prototype_ `FRDGViewableResource* ExecutePasses_RenderThread(const UE::MediaCaptureData::FCaptureFrameArgs& Args, const TSharedPtr<MediaCaptureData::FCaptureFrame>& CapturingFrame, FRDGBuilder& GraphBuilder, FRDGTextureRef InputRGBTexture) const;` — Execute passes in the pipeline. @return The final output generated by the render pipeline.
- L189 _public function_ `FName GetLastPassName() const` — Returns the name of the last render pass.
- L200 _private prototype_ `static void InitializePassOutputResource(UE::MediaCapture::FRenderPassFrameResources& InOutFrameResources, int32 InFrameId, FInitializePassOutputArgs InArgs, const FRenderPass& InRenderPass);` — Initialize render pass resources for a given capture frame.
- L202 _private prototype_ `static FRDGViewableResource* RegisterPassOutputResource(const UE::MediaCapture::FRenderPassFrameResources& InFrameResources, FRDGBuilder& InRDGBuilder, const UE::MediaCapture::FRenderPass& InRenderPass);` — Register a render pass' resources with the render graph builder. Calling this multiple times will simply return the (already) registered resource.
- L204 _private member_ `UMediaCapture* MediaCapture = nullptr;`
- L205 _private member_ `TArray<FRenderPass> RenderPasses;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MediaCaptureData` (scope `UE`)
- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace MediaCapture` (scope `UE`)
- L75 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TRDGResource , FInitializePassOutput, const UE::MediaCapture::FInitializePassOutputArgs& , uint32 );` — This delegate should return a TRDGResource constructed with either a pooled texture or buffer.
- L82 _delegate_ `DECLARE_DELEGATE_FourParams(FExecutePass, const UE::MediaCaptureData::FCaptureFrameArgs& , const TSharedPtr<UE::MediaCaptureData::FCaptureFrame> , FRDGViewableResource* , FRDGViewableResource* );`
- L92 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FShouldExecutePass, const UE::MediaCaptureData::FCaptureFrameArgs& , FRDGViewableResource* );` — Delegate invoked to query whether the pass should be executed.
- L113 _function_ `static FRenderPass::TRDGResource RenderTargetResource(TRefCountPtr<IPooledRenderTarget>&& RenderTarget)` (scope `UE::MediaCapture`) — Instantiates a TRDGResource TVariant from a pooled render target.
- L119 _function_ `static FRenderPass::TRDGResource BufferResource(TRefCountPtr<FRDGPooledBuffer>&& Buffer)` (scope `UE::MediaCapture`) — Instantiates a TRDGResource TVariant from a pooled buffer.
- L125 _prototype_ `static FRenderPass::TRDGResource InitializeColorConversionPassOutputTexture(const FInitializePassOutputArgs& Args, uint32 FrameId);` (scope `UE::MediaCapture`) — Creates the necessary render target for the color conversion pass.
- L128 _prototype_ `static FRenderPass::TRDGResource InitializeResamplePassOutputTexture(const FInitializePassOutputArgs& Args, uint32 FrameId);` (scope `UE::MediaCapture`) — Creates the necessary render target for the Resample pass.

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Private/MediaCaptureSceneViewExtension.h` (Private)


#### class `FMediaCaptureSceneViewExtension`  
`class FMediaCaptureSceneViewExtension : public FSceneViewExtensionBase`  
_L24-149_
- inherits: `FSceneViewExtensionBase`
- desc: View extension that calls into MediaCapture to capture frames as soon as the frame is rendered.
- L28 _public function_ `FMediaCaptureSceneViewExtension(const FAutoRegister& InAutoRegister, UMediaCapture* InMediaCapture, EMediaCapturePhase InCapturePhase, int32 InPriority, FRenderTarget* InRenderTarget) : FSceneViewExtensionBase(InAutoRegister) , WeakCapture(InMediaCapture) , CapturePhase(InCapturePhase) , Priority(InPriority) , CurrentRenderTarget(InRenderTarget)`
- L38 _public function_ `virtual int32 GetPriority() const override`
- L43 _public function_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override`
- L75 _public function_ `virtual void SubscribeToPostProcessingPass(EPostProcessingPass PassId, const FSceneView& InView, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled) override`
- L89 _public function_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override`
- L94 _public function_ `virtual void PostRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override`
- L111 _public function_ `FScreenPassTexture PostProcessCallback_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& InOutInputs)`
- L135 _public function_ `bool IsValid() const`
- L141 _private member_ `TWeakObjectPtr<UMediaCapture> WeakCapture;`
- L142 _private member_ `EMediaCapturePhase CapturePhase = EMediaCapturePhase::AfterMotionBlur;`
- L143 _private member_ `bool bPostProcessingEnabled = true;`
- L144 _private member_ `bool bValidPhase = true;`
- L145 _private member_ `FString LastErrorMessage;`
- L146 _private member_ `int32 Priority = 0;`
- L148 _private member_ `FRenderTarget* CurrentRenderTarget = nullptr;` — Render target that should be considered by this scene view extension.

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Private/MediaCaptureSources.inl` (Private)


#### enum `UE::MediaCapture::Private::ECaptureType`  
`enum class ECaptureType : uint8`  
_L157-161_
- L159 _public enumerator_ `Immediate`
- L160 _public enumerator_ `OnTick`

#### class `UE::MediaCapture::Private::FCaptureSource`  
`class FCaptureSource`  
_L163-222_
- L166 _public function_ `FCaptureSource(UMediaCapture* InMediaCapture, FMediaCaptureOptions InCaptureOptions) : MediaCapture(InMediaCapture) , CaptureOptions(MoveTemp(InCaptureOptions))`
- L172 _public prototype_ `virtual ~FCaptureSource() = default;`
- L174 _public function_ `virtual void ResizeSourceBuffer(FIntPoint Size)`
- L175 _public function_ `virtual void ResetSourceBufferSize(bool bFlushRenderingCommands)`
- L176 _public function_ `virtual void ApplyShowFlagChanges()`
- L177 _public function_ `virtual void RestoreShowFlags()`
- L178 _public prototype_ `virtual bool ValidateSource(const FIntPoint& DesiredSize, const EPixelFormat DesiredPixelFormat, const bool bCurrentlyCapturing) = 0;`
- L179 _public prototype_ `virtual bool PostInitialize() = 0;`
- L180 _public prototype_ `virtual EMediaCaptureSourceType GetSourceType() = 0;`
- L181 _public prototype_ `virtual FIntPoint GetSize() = 0;`
- L183 _public prototype_ `virtual bool IsValid() const = 0;` — Returns whether the underlying captured resource is still valid.
- L185 _public function_ `virtual ECaptureType GetCaptureType() const`
- L190 _public function_ `virtual bool UpdateSourceImpl()`
- L196 _public function_ `virtual FTextureRHIRef GetSourceTextureForInput_RenderThread()` — Only returns a valid texture for scene viewports and render targets as the RHI Sources don't keep a pointer to the RHI texture.
- L201 _public function_ `virtual UTextureRenderTarget2D* GetRenderTarget() const`
- L206 _public function_ `virtual TSharedPtr<FSceneViewport> GetSceneViewport() const`
- L212 _public function_ `virtual void AddPasses(FRenderPipeline& Pipeline)` — Allows the capture source to add its own render passes to the media capture render pipeline
- L214 _public function_ `virtual TSharedPtr<SWindow> GetTargetWindow() const`
- L220 _public member_ `TWeakObjectPtr<UMediaCapture> MediaCapture;`
- L221 _public member_ `FMediaCaptureOptions CaptureOptions;`

#### class `UE::MediaCapture::Private::FSceneViewportCaptureSource`  
`class FSceneViewportCaptureSource : public FCaptureSource`  
_L224-396_
- inherits: `FCaptureSource`
- L227 _public function_ `FSceneViewportCaptureSource(UMediaCapture* InMediaCapture, FMediaCaptureOptions InCaptureOptions, TSharedPtr<FSceneViewport> InSceneViewport) : FCaptureSource(InMediaCapture, MoveTemp(InCaptureOptions)) , WeakViewport(InSceneViewport)`
- L237 _public function_ `virtual ECaptureType GetCaptureType() const override`
- L246 _public function_ `virtual EMediaCaptureSourceType GetSourceType() override`
- L251 _public function_ `virtual void ResetSourceBufferSize(bool bFlushRenderingCommands) override`
- L263 _public function_ `virtual void ApplyShowFlagChanges() override`
- L284 _public function_ `virtual void RestoreShowFlags() override`
- L306 _public function_ `virtual void ResizeSourceBuffer(FIntPoint Size) override`
- L317 _public function_ `virtual bool ValidateSource(const FIntPoint& InDesiredSize, const EPixelFormat InDesiredPixelFormat, const bool bInCurrentlyCapturing) override`
- L332 _public function_ `virtual bool PostInitialize() override`
- L341 _public function_ `virtual FIntPoint GetSize() override`
- L350 _public function_ `virtual bool UpdateSourceImpl() override`
- L363 _public function_ `virtual FTextureRHIRef GetSourceTextureForInput_RenderThread() override`
- L374 _public function_ `virtual TSharedPtr<FSceneViewport> GetSceneViewport() const override`
- L379 _public function_ `virtual bool IsValid() const override`
- L384 _public function_ `virtual TSharedPtr<SWindow> GetTargetWindow() const override`
- L389 _public member_ `TWeakPtr<FSceneViewport> WeakViewport;`
- L390 _public member_ `TWeakPtr<SWindow> TargetWindow;`
- L392 _public member_ `bool bOriginalBillboardSprites = true;`
- L394 _public member_ `bool bShowFlagsApplied = false;` — Whether the sprite show flag was actually overridden, so a failed apply doesn't restore a value we never read.

#### class `UE::MediaCapture::Private::FRHIResourceCaptureSource`  
`class FRHIResourceCaptureSource : public FCaptureSource`  
_L398-439_
- inherits: `FCaptureSource`
- L401 _public function_ `FRHIResourceCaptureSource(UMediaCapture* InMediaCapture, FMediaCaptureOptions InCaptureOptions, const FRHICaptureResourceDescription& InResourceDescription) : FCaptureSource(InMediaCapture, MoveTemp(InCaptureOptions)) , ResourceDescription(InResourceDescription)`
- L407 _public function_ `virtual ECaptureType GetCaptureType() const override`
- L412 _public function_ `virtual EMediaCaptureSourceType GetSourceType() override`
- L417 _public function_ `virtual bool PostInitialize() override`
- L422 _public function_ `virtual FIntPoint GetSize() override`
- L427 _public function_ `virtual bool ValidateSource(const FIntPoint& DesiredSize, const EPixelFormat DesiredPixelFormat, const bool bCurrentlyCapturing) override`
- L432 _public function_ `virtual bool IsValid() const override`
- L438 _public member_ `FRHICaptureResourceDescription ResourceDescription;`

#### class `UE::MediaCapture::Private::FRenderTargetCaptureSource`  
`class FRenderTargetCaptureSource : public FCaptureSource`  
_L442-515_
- inherits: `FCaptureSource`
- L445 _public function_ `FRenderTargetCaptureSource(UMediaCapture* InMediaCapture, FMediaCaptureOptions InCaptureOptions, UTextureRenderTarget2D* InRenderTarget) : FCaptureSource(InMediaCapture, MoveTemp(InCaptureOptions)) , RenderTarget(InRenderTarget)`
- L451 _public function_ `virtual EMediaCaptureSourceType GetSourceType() override`
- L456 _public function_ `virtual void ResizeSourceBuffer(FIntPoint Size) override`
- L464 _public function_ `virtual bool ValidateSource(const FIntPoint& InDesiredSize, const EPixelFormat InDesiredPixelFormat, const bool bInCurrentlyCapturing) override`
- L469 _public function_ `virtual bool PostInitialize() override`
- L474 _public function_ `virtual FIntPoint GetSize() override`
- L484 _public function_ `virtual bool UpdateSourceImpl() override`
- L493 _public function_ `virtual FTextureRHIRef GetSourceTextureForInput_RenderThread()`
- L504 _public function_ `virtual UTextureRenderTarget2D* GetRenderTarget() const override`
- L509 _public function_ `virtual bool IsValid() const override`
- L514 _public member_ `TWeakObjectPtr<UTextureRenderTarget2D> RenderTarget;`

#### class `UE::MediaCapture::Private::MediaTextureCapture::FMediaTextureTransformPS`  
`class FMediaTextureTransformPS : public FGlobalShader`  
_L519-556_
- inherits: `FGlobalShader`
- L522 _public prototype_ `DECLARE_GLOBAL_SHADER(FMediaTextureTransformPS);`
- L523 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FMediaTextureTransformPS, FGlobalShader);`
- L526 _public function_ `SHADER_PARAMETER_STRUCT(FScreenPassTextureViewportParameters, Input) SHADER_PARAMETER_STRUCT(FScreenPassTextureViewportParameters, Output) SHADER_PARAMETER_RDG_TEXTURE(Texture2D, InputTexture) SHADER_PARAMETER_SAMPLER(SamplerState, InputSampler) SHADER_PARAMETER(FVector4f, RotationScale) RENDER_TARGET_BINDING_SLOTS() END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L540 _public function_ `static FParameters* AllocateAndSetParameters(FRDGBuilder& GraphBuilder, const FScreenPassTexture& InputTexture, const FScreenPassTexture& OutputTexture, const FMatrix2x2f& RotationScale)` — Allocates and setup shader parameter in the incoming graph builder

#### class `UE::MediaCapture::Private::FMediaTextureCaptureSource`  
`class FMediaTextureCaptureSource : public FCaptureSource`  
_L561-699_
- inherits: `FCaptureSource`
- L564 _public function_ `FMediaTextureCaptureSource(UMediaCapture* InMediaCapture, const FMediaCaptureOptions& InCaptureOptions, UMediaTexture* InMediaTexture, float InRotation, const FVector2f& InScale) : FCaptureSource(InMediaCapture, InCaptureOptions) , MediaTexture(InMediaTexture)`
- L576 _public function_ `virtual bool ValidateSource(const FIntPoint& DesiredSize, const EPixelFormat DesiredPixelFormat, const bool bCurrentlyCapturing) override`
- L581 _public function_ `virtual bool PostInitialize() override`
- L590 _public function_ `virtual EMediaCaptureSourceType GetSourceType() override`
- L595 _public function_ `virtual FIntPoint GetSize() override`
- L607 _public function_ `virtual bool IsValid() const override`
- L612 _public function_ `virtual bool UpdateSourceImpl() override`
- L621 _public function_ `virtual FTextureRHIRef GetSourceTextureForInput_RenderThread() override`
- L633 _public function_ `virtual void AddPasses(FRenderPipeline& Pipeline) override`
- L697 _private member_ `TWeakObjectPtr<UMediaTexture> MediaTexture;`
- L698 _private member_ `FMatrix2x2f RotationScale;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MediaCapture` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::MediaCapture`)
- L23 _function_ `bool ValidateSize(const FIntPoint TargetSize, const FIntPoint& DesiredSize, const FMediaCaptureOptions& CaptureOptions, const bool bCurrentlyCapturing)` (scope `UE::MediaCapture::Private`)
- L65 _function_ `bool ValidateSceneViewport(const TSharedPtr<FSceneViewport>& SceneViewport, const FMediaCaptureOptions& CaptureOptions, const FIntPoint& DesiredSize, const EPixelFormat DesiredPixelFormat, const bool bCurrentlyCapturing)` (scope `UE::MediaCapture::Private`)
- L104 _function_ `bool ValidateTextureRenderTarget2D(const UTextureRenderTarget2D* InRenderTarget2D, const FMediaCaptureOptions& CaptureOptions, const FIntPoint& DesiredSize, const EPixelFormat DesiredPixelFormat, const bool bCurrentlyCapturing)` (scope `UE::MediaCapture::Private`)
- L140 _function_ `bool ValidateMediaTexture(const UMediaTexture* InMediaTexture, const FMediaCaptureOptions& CaptureOptions, const FIntPoint& TransformedMediaTextureSize, const FIntPoint& DesiredSize, const EPixelFormat DesiredPixelFormat, const bool bCurrentlyCapturing)` (scope `UE::MediaCapture::Private`)
- L517 _namespace_ `namespace MediaTextureCapture` (scope `UE::MediaCapture::Private`)
- L642 _function_ `` (scope `UE::MediaCapture::Private::FMediaTextureCaptureSource::AddPasses`)

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Private/MediaCaptureSyncPointWatcher.h` (Private)


#### struct `UE::MediaCaptureData::FPendingCaptureData`  
`struct FPendingCaptureData`  
_L14-21_
- L17 _public member_ `TSharedPtr<UMediaCapture::FMediaCaptureSyncData> SyncHandler;` — Sync handler holding the fence used for this frame
- L20 _public member_ `TSharedPtr<class FCaptureFrame> CapturingFrame;` — Frame we are waiting on to be captured

#### class `UE::MediaCaptureData::FSyncPointWatcher`  
`class FSyncPointWatcher : public FRunnable`  
_L28-72_
- inherits: `FRunnable`
- desc: Class dealing with sync points. Goes over each pending capture frame data and wait until it's done capturing. Notifies implementation from render thread or watcher's own thread if supported.
- L31 _public prototype_ `FSyncPointWatcher(UMediaCapture* InMediaCapture);`
- L32 _public prototype_ `virtual ~FSyncPointWatcher();`
- L35 _public prototype_ `virtual uint32 Run() override;`
- L36 _public prototype_ `virtual void Stop() override;`
- L40 _public prototype_ `void WaitForAllPendingTasksToComplete();` — Wait for all pending tasks to be completed
- L43 _public prototype_ `void WaitForSinglePendingTaskToComplete();` — Waits for one pending task to be completed in order to have one free capture frame
- L46 _public prototype_ `void QueuePendingCapture(FPendingCaptureData NewData);` — Queue work to be processed by our thread
- L51 _private prototype_ `void ProcessPendingCapture(const FPendingCaptureData& Data);` — Process pending frame being captured
- L56 _protected member_ `TUniquePtr<FRunnableThread> WorkingThread;` — Thread running sync point watch
- L59 _protected member_ `std::atomic<bool> bIsEnabled = false;` — Whether watcher is enabled or not
- L62 _protected member_ `std::atomic<uint32> PendingCaptureFramesCount = 0;` — Number of pending frames to process
- L65 _protected member_ `FEventRef PendingTaskSignal;` — Event used to wake up / wait for new work
- L68 _protected member_ `UMediaCapture* MediaCapture = nullptr;` — Media capture linked to this watcher
- L71 _protected member_ `TSpscQueue<FPendingCaptureData> PendingCaptureFrames;` — Queue of work

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MediaCaptureData` (scope `UE`)

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Private/MediaIOCoreModule.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaIOCore, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaIOCore, Log, All);`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Private/MediaIOFrameManager.h` (Private)


#### struct `UE::MediaCaptureData::FCaptureFrameArgs`  
`struct FCaptureFrameArgs`  
_L21-62_
- desc: Helper struct to contain arguments for CaptureFrame
- L23 _public member_ `FRDGBuilder& GraphBuilder;`
- L24 _public member_ `TObjectPtr<UMediaCapture> MediaCapture = nullptr;`
- L25 _public member_ `FTextureRHIRef ResourceToCapture;`
- L26 _public member_ `FRDGTextureRef RDGResourceToCapture = nullptr;`
- L27 _public member_ `FIntPoint DesiredSize = FIntPoint::ZeroValue;`
- L28 _public member_ `FIntRect SourceViewRect{ 0,0,0,0 };`
- L30 _public function_ `EPixelFormat GetFormat() const`
- L39 _public function_ `bool HasValidResource() const`
- L44 _public function_ `FIntPoint GetSizeXY() const`
- L53 _public function_ `int32 GetSizeX() const`
- L58 _public function_ `int32 GetSizeY() const`

#### class `UE::MediaCaptureData::FFrame`  
`class FFrame`  
_L64-72_
- L67 _public prototype_ `virtual ~FFrame() = default;`
- L69 _public prototype_ `virtual int32 GetId() const = 0;` — Get the ID of a frame (Starts at 0 when a capture is started and is incremented on every frame captured).
- L71 _public prototype_ `virtual bool IsPending() const = 0;` — Returns whether we're doing waiting for a readback to complete or it's in the process of doing a GPU copy.

#### class `UE::MediaCaptureData::FFrameManager`  
`class FFrameManager`  
_L77-196_
- desc: Manages a queue of frames used by MediaCapture.
- L80 _public function_ `~FFrameManager()`
- L90 _public function_ `void ForEachFrame(TFunctionRef<void(const TSharedPtr<FFrame>&)> Function)` — Execute a function for all frames.
- L99 _public function_ `FString GetFramesState()` — Get a string representation of the state of all managed frames (ie. Is frame pending or idle).
- L112 _public function_ `TConstArrayView<TSharedPtr<FFrame>> GetFrames() const` — Returns the list of managed frames.
- L118 _public function_ `void AddFrame(TSharedPtr<FFrame> NewFrame)` — Add a new frame to the list of frames used by the manager.
- L125 _public function_ `void MarkAvailable(const FFrame& InFrame)` — Mark a frame as available, meaning it can be used for a capture.
- L134 _public function_ `void MarkPending(const FFrame& InFrame)` — Mark a frame as pending, meaning it and its resources are being actively used by the media capture.
- L143 _public function_ `void CompleteNextPending(const FFrame& InFrame)` — Mark a frame as available (*Must* match the next pending frame in the queue).
- L154 _public function_ `template<typename FrameType> TSharedPtr<FrameType> GetNextAvailable()` — Get the next available (Not in use) frame.
- L178 _public function_ `template<typename FrameType> TSharedPtr<FrameType> PeekNextPending()` — Get the next pending frame from the queue without dequeuing it.
- L191 _private member_ `TArray<TSharedPtr<FFrame>> Frames;` — List of frames managed by this object.
- L193 _private member_ `TSpscQueue<int32> AvailableFrames;` — List of available frames.
- L195 _private member_ `TSpscQueue<int32> PendingFrames;` — List of frames in use.

#### class `UE::MediaCaptureData::FCaptureFrame`  
`class FCaptureFrame : public FFrame`  
_L199-292_
- inherits: `FFrame`
- desc: Base implementation of a capture frame. Contains common options and resources shared by texture and buffer frames.
- L202 _public function_ `FCaptureFrame(int32 InFrameId) : FrameId(InFrameId)`
- L208 _public function_ `virtual int32 GetId() const override`
- L214 _public function_ `virtual bool IsPending() const override`
- L220 _public function_ `virtual bool HasValidResource() const` — Returns true if its output resource is valid
- L226 _public prototype_ `virtual bool IsTextureResource() const = 0;` — Simple way to validate the resource type and cast safely
- L228 _public prototype_ `virtual bool IsBufferResource() const = 0;` — Simple way to validate the resource type and cast safely
- L231 _public prototype_ `virtual void* Lock(FRHICommandListImmediate& RHICmdList, int32& OutRowStride) = 0;` — Locks the readback resource and returns a pointer to access data from system memory
- L234 _public function_ `virtual void* Lock_Unsafe(int32& OutRowStride)` — Unsafe version of the Lock method, used outside of the rendering thread.
- L237 _public prototype_ `virtual void Unlock() = 0;` — Unlocks the readback resource
- L240 _public function_ `virtual void Unlock_Unsafe()` — Unsafe version of the Unlock method, used outside of the rendering thread.
- L243 _public prototype_ `virtual bool IsReadbackReady(FRHIGPUMask GPUMask) = 0;` — Returns true if the readback is ready to be used
- L246 _public prototype_ `virtual void EnqueueCopy(FRDGBuilder& RDGBuilder, FRDGViewableResource* ResourceToReadback, bool bIsAnyThreadSupported) = 0;` — Enqueue a copy pass on the rdg builder.
- L252 _public function_ `virtual FRHITexture* GetTextureResource() const` — @return The last texture in the capture pipeline that will be readback. @note This will only return a valid texture after CaptureFrame has been called once since it will initialize the resource.
- L266 _public function_ `virtual FRHIBuffer* GetBufferResource() const` — @return The last buffer in the capture pipeline that will be readback. @note This will only return a valid buffer after CaptureFrame has been called once since it will initialize the resource.
- L278 _public member_ `int32 FrameId = 0;` — Index that increments for every capture.
- L280 _public member_ `UMediaCapture::FCaptureBaseData CaptureBaseData;` — Frame and timecode data.
- L282 _public member_ `std::atomic<bool> bReadbackRequested = false;` — Whether readback was requested.
- L284 _public member_ `std::atomic<bool> bDoingGPUCopy = false;` — Whether the captured resource is undergoing a gpy copy at the moment.
- L286 _public member_ `std::atomic<bool> bMediaCaptureActive = true;` — Flag that keeps track of whether MediaCapture is still actively capturing.
- L287 _public member_ `TSharedPtr<FMediaCaptureUserData> UserData;`
- L289 _public member_ `UE::MediaCapture::FRenderPassFrameResources RenderPassResources;` — Resources used by the media capture render pipeline (ie. Color conversion render target )
- L291 _public member_ `bool bPrerollFrame = true;` — Whether this frame is used to preroll the output. Preroll frames are only used to create render resources to avoid a startup hitch.

#### class `UE::MediaCaptureData::FTextureCaptureFrame`  
`class FTextureCaptureFrame : public FCaptureFrame`  
_L304-374_
- inherits: `FCaptureFrame`
- desc: Capture frame implementation for texture resources.
- L308 _public typedef_ `using FOutputResourceType = FRDGTextureRef;` — Type alias for the output resource type used during capture frame
- L309 _public typedef_ `using PassParametersType = FMediaCaptureTextureSyncPassParameters;`
- L311 _public function_ `FTextureCaptureFrame(int32 InFrameId) : FCaptureFrame(InFrameId)`
- L318 _public function_ `virtual bool IsTextureResource() const override`
- L323 _public function_ `virtual bool IsBufferResource() const override`
- L328 _public function_ `virtual void* Lock(FRHICommandListImmediate& RHICmdList, int32& OutRowStride) override`
- L341 _public function_ `virtual void* Lock_Unsafe(int32& OutRowStride) override`
- L350 _public function_ `virtual void Unlock() override`
- L355 _public function_ `virtual void Unlock_Unsafe() override`
- L360 _public function_ `virtual bool IsReadbackReady(FRHIGPUMask GPUMask) override`
- L365 _public function_ `virtual void EnqueueCopy(FRDGBuilder& RDGBuilder, FRDGViewableResource* ResourceToReadback, bool bIsAnyThreadSupported) override`
- L373 _public member_ `TUniquePtr<FRHIGPUTextureReadback> ReadbackTexture;` — Holds the GPU readback texture used to give a CPU buffer to the media capture callbacks.

#### class `UE::MediaCaptureData::FBufferCaptureFrame`  
`class FBufferCaptureFrame : public FCaptureFrame, public TSharedFromThis<UE::MediaCaptureData::FBufferCaptureFrame, ESPMode::ThreadSafe>`  
_L377-493_
- inherits: `FCaptureFrame,TSharedFromThis<UE::MediaCaptureData::FBufferCaptureFrame,ESPMode::ThreadSafe>`
- desc: Capture frame implementation for buffer resources.
- L381 _public typedef_ `using FOutputResourceType = FRDGBufferRef;` — Type alias for the output resource type used during capture frame
- L382 _public typedef_ `using PassParametersType = FMediaCaptureBufferSyncPassParameters;`
- L384 _public function_ `FBufferCaptureFrame(int32 InFrameId) : FCaptureFrame(InFrameId)`
- L390 _public function_ `virtual bool IsTextureResource() const override`
- L395 _public function_ `virtual bool IsBufferResource() const override`
- L400 _public function_ `virtual void* Lock(FRHICommandListImmediate& RHICmdList, int32& OutRowStride) override`
- L412 _public function_ `virtual void* Lock_Unsafe(int32& OutRowStride) override`
- L419 _public function_ `virtual void Unlock() override`
- L424 _public function_ `virtual void Unlock_Unsafe() override`
- L429 _public function_ `virtual bool IsReadbackReady(FRHIGPUMask GPUMask) override`
- L436 _public function_ `RDG_BUFFER_ACCESS(Buffer, ERHIAccess::CopySrc) END_SHADER_PARAMETER_STRUCT() virtual void EnqueueCopy(FRDGBuilder& RDGBuilder, FRDGViewableResource* ResourceToReadback, bool bIsAnyThreadSupported) override`
- L480 _public member_ `TUniquePtr<FRHIGPUBufferReadback> ReadbackBuffer;` — Holds the GPU readback buffer used to give a CPU buffer to the media capture callbacks.
- L484 _public member_ `FStagingBufferRHIRef DestinationStagingBuffers[MAX_NUM_GPUS];`
- L486 _public member_ `FStagingBufferRHIRef DestinationStagingBuffers[1];`
- L490 _public member_ `FRHIGPUMask LastCopyGPUMask;` — Used to keep track of the last gpu used for the readback copy.
- L492 _public member_ `uint32 LastLockGPUIndex = 0;` — Used to keep track of the last gpu used for locking the buffer.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MediaCaptureData` (scope `UE`)
- L84 _function_ `` (scope `UE::MediaCaptureData::FFrameManager::~FFrameManager`)
- L454 _function_ `` (scope `UE::MediaCaptureData::FBufferCaptureFrame::RDG_BUFFER_ACCESS`)

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Private/RenderTargetMediaCapture.h` (Private)


#### class `URenderTargetMediaCapture`  
`class URenderTargetMediaCapture : public UMediaCapture`  
_L12-45_
- reflection: `UCLASS()`
- inherits: `UMediaCapture`
- L18 _protected function_ `virtual bool ShouldCaptureRHIResource() const override`
- L23 _protected prototype_ `virtual void OnRHIResourceCaptured_RenderingThread( FRHICommandListImmediate& RHICmdList, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture ) override;`
- L31 _protected prototype_ `virtual bool InitializeCapture() override;`
- L32 _protected prototype_ `virtual bool PostInitializeCaptureViewport(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L33 _protected prototype_ `virtual bool PostInitializeCaptureRenderTarget(UTextureRenderTarget2D* InRenderTarget) override;`
- L34 _protected prototype_ `virtual bool PostInitializeCaptureRHIResource(const FRHICaptureResourceDescription& InResourceDescription) override;`
- L35 _protected prototype_ `virtual bool PostInitializeCaptureMediaTexture(UMediaTexture* InMediaTexture) override;`
- L36 _protected prototype_ `virtual void StopCaptureImpl(bool bAllowPendingFrameToBeProcess) override;`
- L39 _protected member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY(Transient)`
- L42 _private prototype_ `bool StartNewCapture(const FIntPoint& InSourceTargetSize, EPixelFormat InSourceTargetFormat);`
- L44 _private member_ `FCriticalSection RenderTargetCriticalSection;`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Private/RenderTargetMediaOutput.h` (Private)


#### class `URenderTargetMediaOutput`  
`class URenderTargetMediaOutput : public UMediaOutput`  
_L16-44_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaOutput`
- desc: Captures Media to a Render Target. This can be useful to make a texture available from a source that has a Media output interface.
- L24 _public member_ `bool bInvertAlpha = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media")` — Invert the alpha channel
- L28 _public member_ `TSoftObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media")` — Specify the render target to be capturing to.
- L34 _public prototype_ `virtual bool Validate(FString& FailureReason) const override;`
- L35 _public prototype_ `virtual FIntPoint GetRequestedSize() const override;`
- L36 _public prototype_ `virtual EPixelFormat GetRequestedPixelFormat() const override;`
- L37 _public prototype_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override;`
- L41 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/CaptureCardMediaSource.h` (Public)


#### enum `EMediaIOCoreSourceEncoding`  
`enum class UE_DEPRECATED(5.8, "EMediaIOCoreSourceEncoding is deprecated. This functionality is now available with EMediaSourceEncoding in BaseMediaSourceColorSettings.") EMediaIOCoreSourceEncoding : uint8`  
_L50-57_
- reflection: `UENUM(meta = (Deprecated = "5.8", DeprecationMessage = "EMediaIOCoreSourceEncoding is deprecated. This functionality is now available with EMediaSourceEncoding in BaseMediaSourceColorSettings.h"))`
- L52 _public enumerator_ `Linear = 1 UMETA(DisplayName = "Linear")`
- L53 _public enumerator_ `sRGB = 2 UMETA(DisplayName = "sRGB")`
- L54 _public enumerator_ `ST2084 = 3 UMETA(DisplayName = "ST 2084/PQ")`
- L55 _public enumerator_ `SLog3 = 12 UMETA(DisplayName = "SLog3")`
- L56 _public enumerator_ `MAX`

#### class `UCaptureCardMediaSource`  
`class UCaptureCardMediaSource : public UTimeSynchronizableMediaSource`  
_L63-190_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UTimeSynchronizableMediaSource`
- desc: Base class for media sources that are coming from a capture card.
- L69 _public prototype_ `UCaptureCardMediaSource();`
- L74 _public member_ `bool bRenderJIT = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Synchronization, meta = (DisplayName = "Just-In-Time Rendering"))` — Should use JITR technique? It enables late sample picking for render.
- L78 _public member_ `bool bFramelock = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Synchronization, meta = (DisplayName = "Framelock"))` — Should wait for some time until requested frame arrives? Requires JIT rendering.
- L82 _public member_ `EMediaIOSampleEvaluationType EvaluationType = EMediaIOSampleEvaluationType::PlatformTime;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Synchronization, meta = (DisplayName = "Sample Evaluation Type"))` — Sample evaluation type.
- L88 _public member_ `TObjectPtr<UVideoDeinterlacer> Deinterlacer;` — `UPROPERTY(BlueprintReadOnly, Instanced, EditAnywhere, Category = "Video")` — How interlaced video should be treated.
- L94 _public member_ `EMediaIOInterlaceFieldOrder InterlaceFieldOrder = EMediaIOInterlaceFieldOrder::TopFieldFirst;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Video")` — The order in which interlace fields should be copied.
- L100 _public member_ `FOpenColorIOColorConversionSettings ColorConversionSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ColorManagement", meta = (DisplayName = "OpenColorIO Override"))` — OpenColorIO transform settings used for applying a color conversion override to the incoming source.
- L104 _public member_ `FMediaSourceColorSettings SourceColorSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ColorManagement", meta = (ShowOnlyInnerProperties))` — Manual definition of media source color space & encoding.
- L108 _private member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> NativeSourceColorSettings;` — Native source color settings.
- L119 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const override;`
- L120 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const override;`
- L121 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool bDefaultValue) const override;`
- L122 _public prototype_ `virtual TSharedPtr<FDataContainer, ESPMode::ThreadSafe> GetMediaOption(const FName& Key, const TSharedPtr<FDataContainer, ESPMode::ThreadSafe>& DefaultValue) const override;`
- L123 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
- L126 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L127 _public prototype_ `virtual void PostLoad() override;`
- L129 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L130 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L137 _public prototype_ `void SetLastDetectedConfiguration(const FMediaIOConfiguration& InConfiguration);` — Cache the configuration the player auto-detected from the live signal so the editor's Media Profile info panel can show the actual format instead of the stored default. Game-thread only.
- L144 _public prototype_ `void ClearLastDetectedConfiguration();` — Drop the cached detected configuration. Called from a player's Close path so the panel reverts to "Auto (no signal)" instead of showing stale R/F/S after disconnect. Game-thread only.
- L146 _public function_ `bool HasLastDetectedConfiguration() const`
- L147 _public function_ `const FMediaIOConfiguration& GetLastDetectedConfiguration() const`
- L150 _public function_ `FSimpleMulticastDelegate& OnLastDetectedConfigurationChanged()` — Broadcast on the game thread whenever the detected configuration is set or cleared, so editor UIs can refresh.
- L157 _private member_ `FMediaIOConfiguration LastDetectedConfiguration;` — `UPROPERTY(Transient)` — The configuration last reported by a running player's auto-detection. Transient, never serialized.
- L161 _private member_ `bool bHasLastDetectedConfiguration = false;` — `UPROPERTY(Transient)` — True once a player has published a detected configuration this session.
- L166 _private member_ `FSimpleMulticastDelegate LastDetectedConfigurationChanged;` — Notifies editor listeners (e.g. the Media Profile info panel) when the detected configuration changes.
- L175 _public member_ `bool bOverrideSourceEncoding_DEPRECATED = true;` — `UE_DEPRECATED(5.8, "This property is deprecated. Please use SourceColorSettings instead.")` — `UPROPERTY(meta = (ScriptName = "IsOverrideSourceEncoding", DeprecatedProperty, DeprecationMessage = "This property is deprecated. Please use SourceColorSettings instead."))`
- L179 _public member_ `EMediaIOCoreSourceEncoding OverrideSourceEncoding_DEPRECATED = EMediaIOCoreSourceEncoding::Linear;` — `UE_DEPRECATED(5.8, "This property is deprecated. Please use SourceColorSettings instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Please use SourceColorSettings instead."))`
- L183 _public member_ `bool bOverrideSourceColorSpace_DEPRECATED = true;` — `UE_DEPRECATED(5.8, "This property is deprecated. Please use SourceColorSettings instead.")` — `UPROPERTY(meta = (ScriptName = "IsOverrideSourceColorSpace", DeprecatedProperty, DeprecationMessage = "This property is deprecated. Please use SourceColorSettings instead."))`
- L187 _public member_ `ETextureColorSpace OverrideSourceColorSpace_DEPRECATED = ETextureColorSpace::TCS_sRGB;` — `UE_DEPRECATED(5.8, "This property is deprecated. Please use SourceColorSettings instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property is deprecated. Please use SourceColorSettings instead."))`

#### struct `UCaptureCardMediaSource::FOpenColorIODataContainer`  
`struct FOpenColorIODataContainer : public IMediaOptions::FDataContainer`  
_L111-114_
- inherits: `IMediaOptions::FDataContainer`
- L113 _public member_ `FOpenColorIOColorConversionSettings ColorConversionSettings;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API MEDIAIOCORE_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace CaptureCardMediaSource` (scope `UE`)
- L26 _variable_ `static FName RenderJIT("Ren` (scope `UE::CaptureCardMediaSource`)
- L27 _variable_ `static FName Framelock("Fra` (scope `UE::CaptureCardMediaSource`)
- L28 _variable_ `static FName EvaluationType("Eva` (scope `UE::CaptureCardMediaSource`)
- L29 _variable_ `static FName Deinterlacer("Dei` (scope `UE::CaptureCardMediaSource`)
- L30 _variable_ `static FName InterlaceFieldOrder("Int` (scope `UE::CaptureCardMediaSource`)
- L31 _variable_ `static FName SourceColorSettingsOption("Sou` (scope `UE::CaptureCardMediaSource`)
- L32 _variable_ `static FName OpenColorIOSettings("Ope` (scope `UE::CaptureCardMediaSource`)
- L36 _variable_ `static FName OverrideSourceEncoding("Ove` (scope `UE::CaptureCardMediaSource`) — `UE_DEPRECATED(5.8, "OverrideSourceEncoding is deprecated.")` — 5.8 deprecated options
- L39 _variable_ `static FName SourceEncoding("Sou` (scope `UE::CaptureCardMediaSource`) — `UE_DEPRECATED(5.8, "SourceEncoding is deprecated.")`
- L42 _variable_ `static FName OverrideSourceColorSpace("Ove` (scope `UE::CaptureCardMediaSource`) — `UE_DEPRECATED(5.8, "OverrideSourceColorSpace is deprecated.")`
- L45 _variable_ `static FName SourceColorSpace("Sou` (scope `UE::CaptureCardMediaSource`) — `UE_DEPRECATED(5.8, "SourceColorSpace is deprecated.")`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/FileMediaCapture.h` (Public)


#### class `UFileMediaCapture`  
`class UFileMediaCapture : public UMediaCapture`  
_L16-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMediaCapture`
- L21 _protected prototype_ `virtual void OnFrameCaptured_RenderingThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, void* InBuffer, int32 Width, int32 Height, int32 BytesPerRow) override;`
- L22 _protected prototype_ `virtual bool InitializeCapture() override;`
- L25 _private prototype_ `void CacheMediaOutputValues();`
- L28 _private member_ `FString BaseFilePathName;`
- L29 _private member_ `EImageFormat ImageFormat;`
- L30 _private member_ `TFunction<void(bool)> OnCompleteWrapper;`
- L31 _private member_ `bool bOverwriteFile;`
- L32 _private member_ `int32 CompressionQuality;`
- L33 _private member_ `bool bAsync;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MEDIAIOCORE_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/FileMediaOutput.h` (Public)


#### enum `EFileMediaOutputPixelFormat`  
`enum class EFileMediaOutputPixelFormat`  
_L17-21_
- reflection: `UENUM()`
- desc: Texture format supported by UFileMediaOutput.
- L19 _public enumerator_ `B8G8R8A8 UMETA(DisplayName = "8bit RGBA")`
- L20 _public enumerator_ `FloatRGBA UMETA(DisplayName = "Float RGBA")`

#### class `UFileMediaOutput`  
`class UFileMediaOutput : public UMediaOutput`  
_L30-85_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMediaOutput`
- desc: Output information for a file media capture. @note	'Frame Buffer Pixel Format' must be set to at least 8 bits of alpha to enabled the Key. @note	'Enable alpha channel support in post-processing' must be set to 'Allow through tonemapper' to enabled the Key.
- L35 _public prototype_ `UFileMediaOutput();`
- L40 _public member_ `FImageWriteOptions WriteOptions;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="File")` — Options on how to save the images.
- L44 _public member_ `FDirectoryPath FilePath;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="File", meta=(RelativePath))` — The file path for the images.
- L48 _public member_ `FString BaseFileName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="File", meta=(RelativePath))` — The base file name of the images. The frame number will be append to the base file name.
- L52 _public member_ `bool bOverrideDesiredSize;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media", meta = (InlineEditConditionToggle))` — Use the default back buffer size or specify a specific size to capture.
- L56 _public member_ `FIntPoint DesiredSize;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media", meta=(EditCondition="bOverrideDesiredSize"))` — Use the default back buffer size or specify a specific size to capture.
- L60 _public member_ `bool bOverridePixelFormat;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media", meta = (InlineEditConditionToggle))` — Use the default back buffer pixel format or specify a specific the pixel format to capture.
- L64 _public member_ `EFileMediaOutputPixelFormat DesiredPixelFormat;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media", meta=(EditCondition="bOverridePixelFormat"))` — Use the default back buffer pixel format or specify a specific the pixel format to capture.
- L68 _public member_ `bool bInvertAlpha;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media")` — Invert the alpha for formats that support alpha.
- L72 _public prototype_ `virtual bool Validate(FString& FailureReason) const override;`
- L73 _public prototype_ `virtual FIntPoint GetRequestedSize() const override;`
- L74 _public prototype_ `virtual EPixelFormat GetRequestedPixelFormat() const override;`
- L75 _public prototype_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override;`
- L78 _public prototype_ `virtual FString GetDescriptionString() const override;`
- L79 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`
- L83 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MEDIAIOCORE_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/IMediaIOCoreDeviceProvider.h` (Public)


#### class `IMediaIOCoreDeviceProvider`  
`class IMediaIOCoreDeviceProvider`  
_L12-51_
- L15 _public prototype_ `virtual FName GetFName() = 0;`
- L17 _public prototype_ `virtual TArray<FMediaIOConnection> GetConnections() const = 0;`
- L18 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations() const = 0;`
- L19 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations(bool bAllowInput, bool bAllowOutput) const = 0;`
- L20 _public prototype_ `virtual TArray<FMediaIODevice> GetDevices() const = 0;`
- L21 _public prototype_ `virtual TArray<FMediaIOMode> GetModes(const FMediaIODevice& InDevice, bool bInOutput) const = 0;`
- L22 _public prototype_ `virtual TArray<FMediaIOInputConfiguration> GetInputConfigurations() const = 0;`
- L23 _public prototype_ `virtual TArray<FMediaIOOutputConfiguration> GetOutputConfigurations() const = 0;`
- L24 _public prototype_ `virtual TArray<FMediaIOVideoTimecodeConfiguration> GetTimecodeConfigurations() const = 0;`
- L26 _public prototype_ `virtual FMediaIOConfiguration GetDefaultConfiguration() const = 0;`
- L27 _public prototype_ `virtual FMediaIOMode GetDefaultMode() const = 0;`
- L28 _public prototype_ `virtual FMediaIOInputConfiguration GetDefaultInputConfiguration() const = 0;`
- L29 _public prototype_ `virtual FMediaIOOutputConfiguration GetDefaultOutputConfiguration() const = 0;`
- L30 _public prototype_ `virtual FMediaIOVideoTimecodeConfiguration GetDefaultTimecodeConfiguration() const = 0;`
- L32 _public function_ `virtual UMediaSource* CreateMediaSource(const FMediaIOConfiguration& InConfiguration, UObject* Outer) const`
- L35 _public prototype_ `virtual FText ToText(const FMediaIOConfiguration& InConfiguration, bool bInIsAutoDetected = false) const;`
- L36 _public prototype_ `virtual FText ToText(const FMediaIOConnection& InConnection) const;`
- L37 _public prototype_ `virtual FText ToText(const FMediaIODevice& InDevice) const;`
- L38 _public prototype_ `virtual FText ToText(const FMediaIOMode& InMode) const;`
- L39 _public prototype_ `virtual FText ToText(const FMediaIOInputConfiguration& InMode) const;`
- L40 _public prototype_ `virtual FText ToText(const FMediaIOOutputConfiguration& InMode) const;`
- L42 _public prototype_ `static FText GetTransportName(EMediaIOTransportType InLinkType, EMediaIOQuadLinkTransportType InQuadLinkType);`
- L45 _public function_ `virtual bool ShowInputTransportInSelector() const`
- L46 _public function_ `virtual bool ShowOutputTransportInSelector() const`
- L47 _public function_ `virtual bool ShowInputKeyInSelector() const`
- L48 _public function_ `virtual bool ShowOutputKeyInSelector() const`
- L49 _public function_ `virtual bool ShowReferenceInSelector() const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MEDIAIOCORE_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/IMediaIOCoreHardwareSync.h` (Public)


#### class `IMediaIOCoreHardwareSync`  
`class IMediaIOCoreHardwareSync`  
_L9-21_
- L13 _public prototype_ `virtual bool IsValid() const = 0;` — Is hardware valid, and ready to synchronize.
- L16 _public prototype_ `virtual bool WaitVSync() = 0;` — Wait on hardware synchronization.
- L20 _public prototype_ `virtual ~IMediaIOCoreHardwareSync() = default;` — Virtual destructor for the interface.

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/IMediaIOCoreModule.h` (Public)


#### class `IMediaIOCoreModule`  
`class IMediaIOCoreModule : public IModuleInterface`  
_L16-27_
- inherits: `IModuleInterface`
- desc: Definition the MediaIOCore module.
- L19 _public prototype_ `static bool IsAvailable();`
- L20 _public prototype_ `static IMediaIOCoreModule& Get();`
- L23 _public prototype_ `virtual void RegisterDeviceProvider(IMediaIOCoreDeviceProvider* InProvider) = 0;`
- L24 _public prototype_ `virtual void UnregisterDeviceProvider(IMediaIOCoreDeviceProvider* InProvider) = 0;`
- L25 _public prototype_ `virtual IMediaIOCoreDeviceProvider* GetDeviceProvider(FName InProviderName) = 0;`
- L26 _public prototype_ `virtual TConstArrayView<IMediaIOCoreDeviceProvider*> GetDeviceProviders() const = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MEDIAIOCORE_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaCapture.h` (Public)


#### enum `EMediaCaptureState`  
`enum class EMediaCaptureState : uint8`  
_L72-88_
- reflection: `UENUM(BlueprintType)`
- desc: Possible states of media capture.
- L75 _public enumerator_ `Error` — Unrecoverable error occurred during capture.
- L78 _public enumerator_ `Capturing` — Media is currently capturing.
- L81 _public enumerator_ `Preparing` — Media is being prepared for capturing.
- L84 _public enumerator_ `StopRequested` — Capture has been stopped but some frames may need to be process.
- L87 _public enumerator_ `Stopped` — Capture has been stopped.

#### enum `EMediaCaptureResourceType`  
`enum class EMediaCaptureResourceType : uint8`  
_L94-101_
- reflection: `UENUM()`
- desc: Possible resource type the MediaCapture can create based on the conversion operation.
- L97 _public enumerator_ `Texture` — Texture resources are used for the readback.
- L100 _public enumerator_ `Buffer` — RWBuffer resources are used for the readback.

#### class `FMediaCaptureUserData`  
`class FMediaCaptureUserData`  
_L106-108_
- desc: Base class of additional data that can be stored for each requested capture.

#### enum `EMediaCaptureCroppingType`  
`enum class EMediaCaptureCroppingType : uint8`  
_L114-124_
- reflection: `UENUM(BlueprintType)`
- desc: Type of cropping
- L117 _public enumerator_ `None` — Do not crop the captured image.
- L119 _public enumerator_ `Center` — Keep the center of the captured image.
- L121 _public enumerator_ `TopLeft` — Keep the top left corner of the captured image.
- L123 _public enumerator_ `Custom` — Use the StartCapturePoint and the size of the MediaOutput to keep of the captured image.

#### enum `EMediaCaptureOverrunAction`  
`enum class EMediaCaptureOverrunAction : uint8`  
_L130-136_
- reflection: `UENUM(BlueprintType)`
- desc: Action when overrun occurs
- L133 _public enumerator_ `Flush` — Flush rendering thread such that all scheduled commands are executed.
- L135 _public enumerator_ `Skip` — Skip capturing a frame if readback is trailing too much.

#### struct `FRHICaptureResourceDescription`  
`struct FRHICaptureResourceDescription`  
_L141-145_
- desc: Description of resource to be captured when in rhi capture / immediate mode.
- L143 _public member_ `FIntPoint ResourceSize = FIntPoint::ZeroValue;`
- L144 _public member_ `EPixelFormat PixelFormat = EPixelFormat::PF_Unknown;`

#### enum `EMediaCapturePhase`  
`enum class EMediaCapturePhase : uint8`  
_L148-157_
- reflection: `UENUM(BlueprintType)`
- L150 _public enumerator_ `BeforePostProcessing` — Will happen after TSR in order to get a texture of the right size.
- L151 _public enumerator_ `AfterMotionBlur`
- L152 _public enumerator_ `AfterToneMap`
- L153 _public enumerator_ `AfterFXAA`
- L154 _public enumerator_ `PostRender`
- L155 _public enumerator_ `BackBufferReady`
- L156 _public enumerator_ `EndFrame`

#### enum `EMediaCaptureResizeMethod`  
`enum class EMediaCaptureResizeMethod : uint8`  
_L160-170_
- reflection: `UENUM(BlueprintType)`
- L163 _public enumerator_ `None` — Leaves the source texture as is, which might be incompatible with the output size, causing an error.
- L165 _public enumerator_ `ResizeSource` — Resize the source that is being captured. This will resize the viewport when doing a viewport capture and will resize the render target when capturing a render target. Not valid for immediate capture of RHI resource
- L167 _public enumerator_ `ResizeInRenderPass` — Leaves the source as is, but will add a render pass where we resize the captured texture, leaving the source intact. This is useful when the output size is smaller than the captured source.
- L169 _public enumerator_ `ResizeInCapturePass` — Leaves the source as is, but expects the capture pass to fully re-render the source texture to the output texture.

#### struct `FMediaCaptureOptions`  
`struct FMediaCaptureOptions`  
_L177-269_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base class of additional data that can be stored for each requested capture.
- L181 _public prototype_ `FMediaCaptureOptions();`
- L184 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L187 _public prototype_ `FString GetColorConversionSettingsString() const;` — Gets the string version of ColorConversionSettings
- L191 _public member_ `bool bAutoRestartOnSourceSizeChange = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MediaCapture")` — If source texture's size change, auto restart capture to follow source resolution if implementation supports it.
- L195 _public member_ `EMediaCaptureOverrunAction OverrunAction = EMediaCaptureOverrunAction::Flush;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MediaCapture")` — Action to do when game thread overruns render thread and all frames are in flights being captured / readback.
- L199 _public member_ `EMediaCaptureCroppingType Crop;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MediaCapture")` — Crop the captured SceneViewport or TextureRenderTarget2D to the desired size.
- L203 _public member_ `FOpenColorIOColorConversionSettings ColorConversionSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MediaCapture")` — Color conversion settings used by the OCIO conversion pass.
- L210 _public member_ `FIntPoint CustomCapturePoint;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MediaCapture", meta=(editcondition = "Crop == EMediaCaptureCroppingType::Custom"))` — Crop the captured SceneViewport or TextureRenderTarget2D to the desired size. @note Only valid when Crop is set to Custom.
- L217 _public member_ `EMediaCaptureResizeMethod ResizeMethod = EMediaCaptureResizeMethod::None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MediaCapture", meta = (editcondition = "Crop == EMediaCaptureCroppingType::None"))` — When the capture start, control if and how the source buffer should be resized to the desired size. @note Only valid when a size is specified by the MediaOutput.
- L225 _public member_ `bool bSkipFrameWhenRunningExpensiveTasks;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MediaCapture")` — When the application enters responsive mode, skip the frame capture. The application can enter responsive mode on mouse down, viewport resize, ... That is to ensure responsiveness in low FPS situations.
- L231 _public member_ `bool bConvertToDesiredPixelFormat;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MediaCapture")` — Allows to enable/disable pixel format conversion for the cases where render target is not of the desired pixel format.
- L238 _public member_ `bool bForceAlphaToOneOnConversion;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MediaCapture")` — In some cases when we want to stream irregular render targets containing limited number of channels (for example RG16f), we would like to force Alpha to 1.
- L245 _public member_ `bool bDisableEditorSpritesDuringCapture = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MediaCapture")` — When enabled, editor-only overlays such as actor sprites (player start, light icons, etc.) are hidden during capture. Has no effect in non-editor builds.
- L251 _public member_ `bool bApplyLinearToSRGBConversion = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MediaCapture", meta=(DisplayName="Apply linear to sRGB conversion"))` — Whether to apply a linear to sRGB conversion to the texture before outputting.
- L255 _public member_ `bool bAutostopOnCapture;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MediaCapture")` — Automatically stop capturing after a predetermined number of images.
- L259 _public member_ `int32 NumberOfFramesToCapture;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MediaCapture", meta=(editcondition="bAutostopOnCapture"))` — The number of images to capture
- L262 _public member_ `EMediaCapturePhase CapturePhase = EMediaCapturePhase::EndFrame;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MediaCapture")`
- L267 _private member_ `bool bResizeSourceBuffer_DEPRECATED = false;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage="bResizeSourceBuffer, please use ResizeMethod instead."))`

#### enum `EMediaCaptureRotation`  
`enum class EMediaCaptureRotation : uint8`  
_L272-278_
- reflection: `UENUM()`
- L274 _public enumerator_ `None UMETA(DisplayName = "0°")`
- L275 _public enumerator_ `CW90 UMETA(DisplayName = "90°")`
- L276 _public enumerator_ `CCW90 UMETA(DisplayName = "-90°")`
- L277 _public enumerator_ `CW180 UMETA(DisplayName = "180°")`

#### struct `FMediaCaptureTransform`  
`struct FMediaCaptureTransform`  
_L281-296_
- reflection: `USTRUCT()`
- L286 _public member_ `EMediaCaptureRotation Rotation = EMediaCaptureRotation::None;` — `UPROPERTY(EditAnywhere, Category="Media Texture Capture")`
- L289 _public member_ `bool bFlipHorizontal = false;` — `UPROPERTY(EditAnywhere, Category="Media Texture Capture")`
- L292 _public member_ `bool bFlipVertical = false;` — `UPROPERTY(EditAnywhere, Category="Media Texture Capture")`
- L294 _public prototype_ `float GetRotationValue(bool bInDegrees = false) const;`
- L295 _public prototype_ `FVector2f GetScaleValue() const;`

#### class `UMediaCapture`  
`class UMediaCapture : public UObject`  
_L311-885_
- reflection: `UCLASS(MinimalAPI, Abstract, editinlinenew, BlueprintType, hidecategories = (Object))`
- inherits: `UObject`
- desc: Abstract base class for media capture. MediaCapture capture the texture of the Render target or the SceneViewport and sends it to an external media device. MediaCapture should be created by a MediaOutput.
- L316 _public prototype_ `UMediaCapture();`
- L319 _public prototype_ `virtual ~UMediaCapture();` — Default constructor / destructor to use forward declared uniqueptr
- L329 _public prototype_ `bool CaptureSceneViewport(TSharedPtr<FSceneViewport>& SceneViewport, FMediaCaptureOptions CaptureOptions);` — Stop the actual capture if there is one. Then start the capture of a SceneViewport. If the SceneViewport is destroyed, the capture will stop. The SceneViewport needs to be of the same size and have the same pixel format as requested by the media output. @note make sure the size of the SceneViewport doesn't change during capture. @return True if the capture was successfully started
- L337 _public prototype_ `bool CaptureRHITexture(const FRHICaptureResourceDescription& ResourceDescription, FMediaCaptureOptions CaptureOptions);` — Stop the actual capture if there is one. Then start a capture for a RHI resource. @note For this to work, it is expected that CaptureImmediate_RenderThread is called periodically with the resource to capture. @return True if the capture was successfully initialize
- L348 _public prototype_ `bool CaptureActiveSceneViewport(FMediaCaptureOptions CaptureOptions);` — `UFUNCTION(BlueprintCallable, Category = "Media|Output")` — Stop the current capture if there is one. Then find and capture every frame from active SceneViewport. It can only find a SceneViewport when you play in Standalone or in "New Editor Window PIE". If the active SceneViewport is destroyed, the capture will stop. The SceneViewport needs to be of the same size and have the same pixel format as requested by the media output. @return True if the capture was successfully started
- L357 _public prototype_ `bool CaptureTextureRenderTarget2D(UTextureRenderTarget2D* RenderTarget, FMediaCaptureOptions CaptureOptions);` — `UFUNCTION(BlueprintCallable, Category = "Media|Output")` — Stop the actual capture if there is one. Then capture every frame for a TextureRenderTarget2D. The TextureRenderTarget2D needs to be of the same size and have the same pixel format as requested by the media output. @return True if the capture was successfully started
- L366 _public prototype_ `bool CaptureMediaTexture(UMediaTexture* InMediaTexture, FMediaCaptureOptions CaptureOptions, float Rotation, const FVector2f& Scale);` — `UFUNCTION(BlueprintCallable, Category = "Media|Output")` — Stop the actual capture if there is one. Then capture every frame for a MediaTexture. The MediaTexture needs to be of the same size and have the same pixel format as requested by the media output. @return True if the capture was successfully started
- L375 _public prototype_ `bool UpdateSceneViewport(TSharedPtr<FSceneViewport>& SceneViewport);` — Update the current capture with a SceneViewport. If the SceneViewport is destroyed, the capture will stop. The SceneViewport needs to be of the same size and have the same pixel format as requested by the media output. @note make sure the size of the SceneViewport doesn't change during capture. @return Return true if the capture was successfully updated. If false is returned, the capture was stopped.
- L383 _public prototype_ `bool UpdateTextureRenderTarget2D(UTextureRenderTarget2D* RenderTarget);` — `UFUNCTION(BlueprintCallable, Category = "Media|Output")` — Update the current capture with every frame for a TextureRenderTarget2D. The TextureRenderTarget2D needs to be of the same size and have the same pixel format as requested by the media output. @return Return true if the capture was successfully updated. If false is returned, the capture was stopped.
- L389 _public prototype_ `bool TryCaptureImmediate_RenderThread(FRDGBuilder& GraphBuilder, FRHITexture* InSourceTexture, FIntRect SourceViewRect = FIntRect(0,0,0,0));` — Captures a resource immediately from the render thread. Used in RHI_RESOURCE capture mode @return Return true if the capture was successfully processed.
- L390 _public prototype_ `bool TryCaptureImmediate_RenderThread(FRDGBuilder& GraphBuilder, FRDGTextureRef InSourceTextureRef, FIntRect SourceViewRect = FIntRect(0,0,0,0));`
- L393 _public prototype_ `void CaptureImmediate_RenderThread(FRDGBuilder& GraphBuilder, FRHITexture* InSourceTexture, FIntRect SourceViewRect = FIntRect(0,0,0,0));` — `UE_DEPRECATED(5.5, "This method has been deprecated. Please use TryCaptureImmediate_RenderThread as it returns a boolean to signify that the capture was successfully processed.")`
- L396 _public prototype_ `void CaptureImmediate_RenderThread(FRDGBuilder& GraphBuilder, FRDGTextureRef InSourceTextureRef, FIntRect SourceViewRect = FIntRect(0,0,0,0));` — `UE_DEPRECATED(5.5, "This method has been deprecated. Please use TryCaptureImmediate_RenderThread as it returns a boolean to signify that the capture was successfully processed.")`
- L403 _public prototype_ `void StopCapture(bool bAllowPendingFrameToBeProcess);` — `UFUNCTION(BlueprintCallable, Category = "Media|Output")` — Stop the previous requested capture. @param bAllowPendingFrameToBeProcess	Keep copying the pending frames asynchronously or stop immediately without copying the pending frames.
- L410 _public prototype_ `void StopCapture_Callback(bool bAllowPendingFrameToBeProcess, FSimpleDelegate Callback);` — Implementation of StopCapture that allows providing a callback that's invoked when the capture has completely stopped. Some capture implementations (ie. Aja), need a few frames to completely stop the capture, so this method can be used to act when the underlying SDK is done shutting down.
- L414 _public function_ `virtual EMediaCaptureState GetState() const` — `UFUNCTION(BlueprintCallable, Category = "Media|Output")` — Get the current state of the capture.
- L418 _public prototype_ `void SetMediaOutput(UMediaOutput* InMediaOutput);` — `UFUNCTION(BlueprintCallable, Category = "Media|Output")` — Set the media output. Can only be set when the capture is stopped.
- L421 _public prototype_ `bool SetCaptureAudioDevice(const FAudioDeviceHandle& InAudioDeviceHandle);` — Set the audio device to capture.
- L424 _public function_ `const FAudioDeviceHandle& GetCaptureAudioDevice() const` — Get the audio device to capture.
- L428 _public function_ `FIntPoint GetDesiredSize() const` — `UFUNCTION(BlueprintCallable, Category = "Media|Output")` — Get the desired size of the current capture.
- L432 _public function_ `EPixelFormat GetDesiredPixelFormat() const` — `UFUNCTION(BlueprintCallable, Category = "Media|Output")` — Get the desired pixel format of the current capture.
- L435 _public function_ `const FMediaCaptureOptions& GetDesiredCaptureOptions() const` — Get the capture options specified by the user.
- L438 _public prototype_ `virtual bool HasFinishedProcessing() const;` — Check whether this capture has any processing left to do.
- L442 _public member_ `FMediaCaptureStateChangedSignature OnStateChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Media|Output")` — Called when the state of the capture changed.
- L445 _public prototype_ `virtual void SetValidSourceGPUMask(FRHIGPUMask GPUMask);` — Set the valid GPU mask of the source buffer/texture being captured. Can be called from any thread.
- L451 _public member_ `FMediaCaptureStateChangedSignatureNative OnStateChangedNative;` — Called when the state of the capture changed. The callback is called on the game thread. Note that the change may occur on the rendering thread.
- L457 _public function_ `virtual bool IsOutputSynchronizationSupported() const` — Returns true if media capture implementation supports synchronization logic. If so, OnOutputSynchronization delegate below must be called before each captured frame is exported.
- L465 _public member_ `FMediaCaptureOutputSynchronization OnOutputSynchronization;` — Called when output data is ready to be sent out. This blocking call allows to postpone data export based on the synchronization logic. This delegate must be called if IsOutputSynchronizationSupported() returns true.
- L467 _public prototype_ `void SetFixedViewportSize(TSharedPtr<FSceneViewport> InSceneViewport, FIntPoint InSize);`
- L468 _public prototype_ `void ResetFixedViewportSize(TSharedPtr<FSceneViewport> InViewport, bool bInFlushRenderingCommands);`
- L471 _public function_ `virtual bool PostInitializeCaptureViewport(TSharedPtr<FSceneViewport>& InSceneViewport)` — Called after initialize for viewport capture type
- L474 _public function_ `virtual bool PostInitializeCaptureRenderTarget(UTextureRenderTarget2D* InRenderTarget)` — Called after initialize for render target capture type
- L477 _public function_ `virtual bool PostInitializeCaptureRHIResource(const FRHICaptureResourceDescription& InResourceDescription)` — Called after initialize for rhi resource capture type
- L480 _public function_ `virtual bool PostInitializeCaptureMediaTexture(UMediaTexture* InMediaTexture)` — Called after initialize for media texture capture type
- L482 _public function_ `virtual bool UpdateSceneViewportImpl(TSharedPtr<FSceneViewport>& InSceneViewport)`
- L483 _public function_ `virtual bool UpdateRenderTargetImpl(UTextureRenderTarget2D* InRenderTarget)`
- L484 _public function_ `virtual bool UpdateMediaTextureImpl(UMediaTexture* InMediaTexture)`
- L485 _public function_ `virtual bool UpdateAudioDeviceImpl(const FAudioDeviceHandle& InAudioDeviceHandle)`
- L491 _public prototype_ `virtual const FMatrix& GetRGBToYUVConversionMatrix() const;` — Get the RGB to YUV Conversion Matrix, should be overriden for media outputs that support different color gamuts (ie. BT 2020). Will default to returning the RGBToYUV Rec709 matrix.
- L493 _public prototype_ `static const TSet<EPixelFormat>& GetSupportedRgbaSwizzleFormats();`
- L496 _public function_ `FString GetMediaOutputName() const` — Get the name of the media output that created this capture.
- L503 _public prototype_ `virtual void BeginDestroy() override;`
- L504 _public prototype_ `virtual FString GetDesc() override;`
- L508 _protected function_ `virtual bool IsReadyToOutput() const` — Implementations can return false when the output sdk is not ready. When this function returns false, the current output frame will be discarded.
- L511 _protected prototype_ `virtual bool ValidateMediaOutput() const;`
- L514 _protected prototype_ `virtual bool CaptureSceneViewportImpl(TSharedPtr<FSceneViewport>& InSceneViewport) final;` — `UE_DEPRECATED(5.1, "This method has been deprecated. Please override InitializeCapture() and PostInitializeCapture variants if needed instead.")`
- L517 _protected prototype_ `virtual bool CaptureRenderTargetImpl(UTextureRenderTarget2D* InRenderTarget) final;` — `UE_DEPRECATED(5.1, "This method has been deprecated. Please override InitializeCapture() and PostInitializeCapture variants if needed instead.")`
- L520 _protected prototype_ `virtual bool InitializeCapture() PURE_VIRTUAL(UMediaCapture::InitializeCapture, return false; );` — Initialization method to prepare implementation for capture
- L522 _protected function_ `virtual void StopCaptureImpl(bool bAllowPendingFrameToBeProcess)`
- L525 _protected function_ `virtual bool SupportsStopCapture_Future() const` — Returns whether the capture implementation supports the implementation of StopCapture that returns a future.
- L532 _protected function_ `virtual TFuture<void> StopCapture_Future()` — Version of StopCaptureImpl that returns a future. Override this in your capture implementation to allow MediaCapture to wait on the StopCapture to complete. @note: Must be called from Game thread.
- L542 _protected function_ `virtual void PostCaptureCleanupImpl()` — Override this to cleanup resources in the capture implementation after StopCapture is done. @note: Will be invoked from the game thread.
- L547 _protected function_ `virtual void LockDMATexture_RenderThread(FTextureRHIRef InTexture)`
- L548 _protected function_ `virtual void UnlockDMATexture_RenderThread(FTextureRHIRef InTexture)`
- L551 _protected function_ `virtual bool SupportsAnyThreadCapture() const` — Whether the capture callbacks can be called on any thread. If true, the _AnyThread callbacks will be used instead of the _RenderThread ones.
- L557 _protected function_ `virtual bool SupportsAutoRestart() const` — Whether the capture implementation supports restarting on input format change.
- L579 _protected function_ `virtual TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> GetCaptureFrameUserData_GameThread()` — Capture the data that will pass along to the callback. @note The capture is done on the Render Thread but triggered from the Game Thread.
- L582 _protected function_ `virtual bool ShouldCaptureRHITexture() const` — `UE_DEPRECATED(5.1, "ShouldCaptureRHITexture has been deprecated to support both texture and buffer output resource. Please use the ShouldCaptureRHIResource instead.")`
- L585 _protected function_ `virtual bool ShouldCaptureRHIResource() const` — Should we call OnFrameCaptured_RenderingThread() with a RHI resource -or- readback the memory to CPU ram and call OnFrameCaptured_RenderingThread().
- L588 _protected function_ `virtual bool ShouldCaptureThisFrame(const FCaptureBaseData& InBaseData) const` — Allows capture implementaion to decide whether to discard a frame based on its base data.
- L591 _protected function_ `virtual void BeforeFrameCaptured_RenderingThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture)` — Called at the beginning of the Capture_RenderThread call if output resource type is Texture
- L594 _protected function_ `virtual void BeforeFrameCaptured_RenderingThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FBufferRHIRef InBuffer)` — Called at the beginning of the Capture_RenderThread call if output resource type is Buffer
- L601 _protected function_ `virtual void OnFrameCaptured_RenderingThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, void* InBuffer, int32 Width, int32 Height, int32 BytesPerRow)` — Callback when the buffer was successfully copied to CPU ram. The callback in called from a critical point. If you intend to process the buffer, do so in another thread. The buffer is only valid for the duration of the callback.
- L619 _protected function_ `virtual void OnFrameCaptured_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, const FMediaCaptureResourceData& InResourceData)` — Callback when the buffer was successfully copied to CPU ram. The buffer is only valid for the duration of the callback. @Note SupportsAnyThreadCapture must return true in the implementation in order for this to be called.
- L622 _protected function_ `virtual void OnRHITextureCaptured_RenderingThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture)` — `UE_DEPRECATED(5.1, "OnRHITextureCaptured_RenderingThread has been deprecated to support texture and buffer output resource. Please use OnRHIResourceCaptured_RenderingThread instead.")`
- L629 _protected function_ `virtual void OnRHIResourceCaptured_RenderingThread(FRHICommandListImmediate& RHICmdList, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture)` — Callbacks when the buffer was successfully copied on the GPU ram. The callback in called from a critical point. If you intend to process the texture/buffer, do so in another thread. The texture is valid for the duration of the callback.
- L630 _protected function_ `virtual void OnRHIResourceCaptured_RenderingThread(FRHICommandListImmediate& RHICmdList, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FBufferRHIRef InBuffer)`
- L636 _protected function_ `virtual void OnRHIResourceCaptured_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture)` — AnyThread version of the above callbacks. @Note SupportsAnyThreadCapture must return true in the implementation in order for this to be called.
- L637 _protected function_ `virtual void OnRHIResourceCaptured_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FBufferRHIRef InBuffer)`
- L646 _protected function_ `virtual void OnCustomCapture_RenderingThread(FRDGBuilder& GraphBuilder, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FRDGTextureRef InSourceTexture, FRDGTextureRef OutputTexture, const FRHICopyTextureInfo& CopyInfo, FVector2D CropU, FVector2D CropV)` — Callback when the source texture is ready to be copied on the GPU. You need to copy yourself. You may use the callback to add passes to the graph builder. Graph execution and output texture readback will be handled after this call. No need to do it in the override. The callback in called from a critical point be fast. The texture is valid for the duration of the callback. Only called when the conversion operation is custom and the output resource type is Texture.
- L657 _protected function_ `virtual void OnCustomCapture_RenderingThread(FRDGBuilder& GraphBuilder, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FRDGTextureRef InSourceTexture, FRDGBufferRef OutputBuffer, const FRHICopyTextureInfo& CopyInfo, FVector2D CropU, FVector2D CropV)` — Callback when the source texture is ready to be copied on the GPU. You need to copy yourself. You may use the callback to add passes to the graph builder. Graph execution and output buffer readback will be handled after this call. No need to do it in the override. The callback in called from a critical point be fast. The texture is valid for the duration of the callback. Only called when the conversion operation is custom and the output resource type is Buffer.
- L662 _protected function_ `virtual FIntPoint GetCustomOutputSize(const FIntPoint& InSize) const` — Get the size of the buffer when the conversion operation is custom. The function is called once at initialization and the result is cached.
- L668 _protected function_ `virtual EPixelFormat GetCustomOutputPixelFormat(const EPixelFormat& InPixelFormat) const` — Get the pixel format of the buffer when the conversion operation is custom. The function is called once at initialization and the result is cached.
- L674 _protected function_ `virtual EMediaCaptureResourceType GetCustomOutputResourceType() const` — Get the desired output resource type when the conversion is custom. This function is called once at initialization and the result is cached
- L680 _protected function_ `virtual FRDGBufferDesc GetCustomBufferDescription(const FIntPoint& InDesiredSize) const` — Get the desired output buffer description when the conversion is custom and operating in buffer resource type
- L689 _protected function_ `virtual ETextureCreateFlags GetOutputTextureFlags() const` — Get the output texture's flags. This can overriden to specify custom texture flags for the output texture. This method can be overriden when doing a custom capture pass; however, this is advanced usage so proceed with caution when changing these.
- L695 _protected function_ `virtual void WaitForGPU(FRHITexture* InRHITexture)` — When using GPUTextureTransfer, calling this will wait for a signal set by the underlying library.
- L698 _protected prototype_ `UTextureRenderTarget2D* GetTextureRenderTarget() const;`
- L699 _protected prototype_ `TSharedPtr<FSceneViewport> GetCapturingSceneViewport() const;`
- L700 _protected prototype_ `FString GetCaptureSourceType() const;`
- L701 _protected prototype_ `void SetState(EMediaCaptureState InNewState);`
- L702 _protected prototype_ `void RestartCapture();`
- L703 _protected function_ `EMediaCaptureConversionOperation GetConversionOperation() const`
- L709 _protected prototype_ `bool UseExperimentalScheduling() const;` — Whether capture should be done using experimental scheduling. Experimental scheduling means that readback is started on the render thread but we don't block on the game thread if it hasn't been completed by the next frame.
- L713 _protected function_ `virtual FString GetAnalyticsEventPrefix() const` — Gets the prefix to attach to engine analytics events for this media capture
- L716 _protected prototype_ `virtual void GetAnalyticsEventAttributes(const FString& EventName, TArray<FAnalyticsEventAttribute>& InOutAttributes) const;` — Allows media captures to add additional analytics event attributes to an analytics event being recorded
- L719 _protected prototype_ `void RecordCaptureStartedEvent() const;` — Records a new event to engine analytics to indicate the capture has been started
- L725 _protected function_ `virtual bool ShouldAutoRecordCaptureStartedEvent() const` — Gets whether the media capture should automatically record a capture started event after InitializeCapture is called. Media captures that operate asynchronously should set this to false and call RecordCaptureStartedEvent manually when appropriate.
- L729 _private prototype_ `void InitializeOutputResources(int32 InNumberOfBuffers);`
- L731 _private prototype_ `void OnBeginFrame_GameThread();`
- L732 _private prototype_ `void OnEndFrame_GameThread();`
- L733 _private prototype_ `void OnViewportRendered_GameThread(FViewport* Viewport);`
- L734 _private prototype_ `void CacheMediaOutput(EMediaCaptureSourceType InSourceType);`
- L735 _private prototype_ `void CacheOutputOptions();`
- L736 _private prototype_ `FIntPoint GetOutputSize() const;`
- L737 _private prototype_ `EPixelFormat GetOutputPixelFormat() const;`
- L738 _private prototype_ `EMediaCaptureResourceType GetOutputResourceType() const;`
- L739 _private prototype_ `FRDGBufferDesc GetOutputBufferDescription() const;`
- L740 _private prototype_ `FRDGTextureDesc GetOutputTextureDescription() const;`
- L741 _private prototype_ `void BroadcastStateChanged();`
- L742 _private prototype_ `void WaitForPendingTasks();`
- L743 _private prototype_ `void OnBackBufferReadyToPresent(SWindow& SlateWindow, ISlateViewportProvider& ViewportProvider);`
- L745 _private prototype_ `void WaitForSingleExperimentalSchedulingTaskToComplete();`
- L746 _private prototype_ `void WaitForAllExperimentalSchedulingTasksToComplete();`
- L748 _private prototype_ `bool CaptureImmediate_RenderThread(const UE::MediaCaptureData::FCaptureFrameArgs& Args);`
- L750 _private prototype_ `void ProcessCapture_GameThread();` — Capture pipeline stuff
- L751 _private prototype_ `void PrepareAndDispatchCapture_GameThread(const TSharedPtr<UE::MediaCaptureData::FCaptureFrame>& CapturingFrame);`
- L753 _private prototype_ `bool ProcessCapture_RenderThread(const TSharedPtr<UE::MediaCaptureData::FCaptureFrame>& CapturingFrame, UE::MediaCaptureData::FCaptureFrameArgs Args);`
- L754 _private prototype_ `bool ProcessReadyFrame_RenderThread(FRHICommandListImmediate& RHICmdList, UMediaCapture* InMediaCapture, const TSharedPtr<UE::MediaCaptureData::FCaptureFrame>& ReadyFrame);`
- L756 _private prototype_ `void InitializeSyncHandlers_RenderThread();`
- L757 _private prototype_ `void InitializeCaptureFrame(const TSharedPtr<UE::MediaCaptureData::FCaptureFrame>& CaptureFrame);`
- L761 _private prototype_ `TSharedPtr<FMediaCaptureSyncData> GetAvailableSyncHandler() const;` — Return a sync handler if there is a free one available.
- L764 _private prototype_ `void PrintFrameState();` — Print the state (Ready/Capturing) of all capture frames.
- L767 _private prototype_ `bool StartSourceCapture(TSharedPtr<UE::MediaCapture::Private::FCaptureSource> InSource);` — Common path used by the different capture methods (Scene viewport, render target) to start doing a media capture.
- L770 _private prototype_ `bool UpdateSource(TSharedPtr<UE::MediaCapture::Private::FCaptureSource> InCaptureSource);` — Common path used by the different capture methods (Scene viewport, render target) to update the capture source.
- L776 _private prototype_ `bool UseAnyThreadCapture() const;` — When using anythread capture, the capture callback will be called directly after readback is complete, meaning there will be minimal delay. When not using it, the capture callback will be called on the render thread which can introduce a delay.
- L779 _private prototype_ `void AddFrameInfoForCaptureImmediate(const uint64 FrameNumber);` — Caches game thread dependent frame data for use by Capture Immediate.
- L782 _private prototype_ `static int32 GetBytesPerPixel(EPixelFormat InPixelFormat);` — Returns bytes per pixel based on pixel format
- L785 _private prototype_ `void PostCaptureCleanup();` — Cleanup config and resources after StopCaptureImpl is invoked.
- L791 _protected member_ `TObjectPtr<UMediaOutput> MediaOutput;` — `UPROPERTY(Transient)` — MediaOutput associated with this capture
- L794 _protected member_ `FAudioDeviceHandle AudioDeviceHandle;` — Audio device to be captured. If none, main engine's audio device is captured.
- L797 _protected member_ `FIntPoint DesiredOutputSize = FIntPoint(1920, 1080);` — Output size of the media capture. If a conversion is done, this resolution might be different than source resolution. i.e. 1080p RGB might be 960x1080 in YUV
- L800 _protected member_ `std::atomic<FRHIGPUMask> ValidSourceGPUMask;` — Valid source gpu mask of the source.
- L803 _protected member_ `EMediaCaptureSourceType CaptureSourceType = EMediaCaptureSourceType::SCENE_VIEWPORT;` — Type of capture currently being done. i.e Viewport, RT, RHI Resource
- L805 _protected member_ `int32 NumberOfCaptureFrame = 2;`
- L808 _private member_ `TPimplPtr<UE::MediaCaptureData::FFrameManager> FrameManager;`
- L809 _private member_ `int32 CaptureRequestCount = 0;`
- L810 _private member_ `std::atomic<EMediaCaptureState> MediaState = EMediaCaptureState::Stopped;`
- L812 _private member_ `FCriticalSection AccessingCapturingSource;`
- L814 _private member_ `FIntPoint DesiredSize = FIntPoint(1920, 1080);`
- L815 _private member_ `EPixelFormat DesiredPixelFormat = EPixelFormat::PF_A2B10G10R10;`
- L816 _private member_ `EPixelFormat DesiredOutputPixelFormat = EPixelFormat::PF_A2B10G10R10;`
- L818 _private member_ `FRDGTextureDesc DesiredOutputTextureDescription;` — The TextureDesc used to create the final output texture that will be readback to the output.
- L820 _private member_ `FRDGBufferDesc DesiredOutputBufferDescription;` — The BufferDesc used to create the final output buffer that will be readback to the output.
- L821 _private member_ `FMediaCaptureOptions DesiredCaptureOptions;`
- L822 _private member_ `EMediaCaptureConversionOperation ConversionOperation = EMediaCaptureConversionOperation::NONE;`
- L823 _private member_ `EMediaCaptureResourceType DesiredOutputResourceType = EMediaCaptureResourceType::Texture;`
- L824 _private member_ `FString MediaOutputName = FString(TEXT("[und`
- L825 _private member_ `bool bUseRequestedTargetSize = false;`
- L827 _private member_ `bool bLoggedOutputNotReady = false;` — Used to avoid repeatedly logging while the underlying sdk is not ready to output.
- L830 _private member_ `bool bWaitingForStopCapture = false;` — This indicates the capture is in the process of stopping and is waiting for StopCapture_Future's result to be ready.
- L832 _private member_ `bool bViewportHasFixedViewportSize = false;`
- L833 _private member_ `std::atomic<bool> bPendingOutputResourcesInitialized;`
- L834 _private member_ `std::atomic<bool> bSyncHandlersInitialized;`
- L835 _private member_ `std::atomic<bool> bShouldCaptureRHIResource;`
- L836 _private member_ `std::atomic<int32> WaitingForRenderCommandExecutionCounter;`
- L837 _private member_ `TArray<TFuture<void>> PendingCommands;`
- L838 _private member_ `std::atomic<int32> PendingFrameCount;`
- L839 _private member_ `std::atomic<bool> bIsAutoRestartRequired;`
- L848 _private member_ `FCriticalSection CaptureDataQueueCriticalSection;` — Used to synchronize access to the capture data queue.
- L849 _private member_ `TArray<FQueuedCaptureData> CaptureDataQueue;`
- L850 _private member_ `static constexpr int32 MaxCaptureDataAgeInFrames = 20;`
- L868 _private member_ `TArray<TSharedPtr<FMediaCaptureSyncData>> SyncHandlers;` — Array of sync handlers (fence) to sync when captured buffer is completed
- L871 _private member_ `TPimplPtr<UE::MediaCaptureData::FSyncPointWatcher> SyncPointWatcher;` — Watcher thread looking after end of capturing frames
- L874 _private member_ `TSharedPtr<UE::MediaCapture::Private::FCaptureSource, ESPMode::ThreadSafe> CaptureSource;` — Capture source
- L877 _private member_ `TSharedPtr<class FMediaCaptureSceneViewExtension> ViewExtension;` — Holds a view extension that callbacks
- L880 _private member_ `TPimplPtr<UE::MediaCapture::FRenderPipeline> CaptureRenderPipeline;` — Holds the render passes that a texture will go through during media capture.

#### struct `UMediaCapture::FCaptureBaseData`  
`struct FCaptureBaseData`  
_L565-571_
- L567 _public member_ `FTimecode SourceFrameTimecode;`
- L568 _public member_ `FFrameRate SourceFrameTimecodeFramerate;`
- L569 _public member_ `uint64 SourceFrameNumberRenderThread = 0;`
- L570 _public member_ `uint64 SourceFrameNumber = 0;`

#### struct `UMediaCapture::FMediaCaptureResourceData`  
`struct FMediaCaptureResourceData`  
_L606-612_
- desc: Args passed to OnFrameCaptured
- L608 _public member_ `void* Buffer = nullptr;`
- L609 _public member_ `int32 Width = 0;`
- L610 _public member_ `int32 Height = 0;`
- L611 _public member_ `int32 BytesPerRow = 0;`

#### struct `UMediaCapture::FQueuedCaptureData`  
`struct FQueuedCaptureData`  
_L841-845_
- L843 _public member_ `FCaptureBaseData BaseData;`
- L844 _public member_ `TSharedPtr<FMediaCaptureUserData> UserData;`

#### struct `UMediaCapture::FMediaCaptureSyncData`  
`struct FMediaCaptureSyncData`  
_L854-865_
- L861 _public member_ `FGPUFenceRHIRef RHIFence;` — We use a RHIFence to write to in a pass following the buffer conversion one. We spawn a task that will poll for the fence to be over (Waiting is not exposed) and then we will push the captured buffer to the capture callback
- L864 _public member_ `std::atomic<bool> bIsBusy = false;` — Whether fence is currently waiting to be cleared

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMediaCaptureOptions> : public TStructOpsTypeTraitsBase2<FMediaCaptureOptions>`  
_L888-894_
- inherits: `TStructOpsTypeTraitsBase2<FMediaCaptureOptions>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L891-893_

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API MEDIAIOCORE_API`
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace MediaCaptureData` (scope `UE`)
- L57 _namespace_ `namespace UE`
- L57 _namespace_ `namespace MediaCapture` (scope `UE`)
- L57 _namespace_ `namespace Private` (scope `UE::MediaCapture`)
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace MediaCapture` (scope `UE`)
- L300 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMediaCaptureStateChangedSignature);` — Delegate signatures
- L300 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMediaCaptureStateChangedSignature);` — Delegate signatures
- L301 _delegate_ `DECLARE_MULTICAST_DELEGATE(FMediaCaptureStateChangedSignatureNative);`
- L301 _prototype_ `DECLARE_MULTICAST_DELEGATE(FMediaCaptureStateChangedSignatureNative);`
- L302 _delegate_ `DECLARE_DELEGATE(FMediaCaptureOutputSynchronization) UCLASS(MinimalAPI, Abstract, editinlinenew, BlueprintType, hidecategories = (Object)) class UMediaCapture : public UObject { GENERATED_BODY() public: UMediaCapture(); virtual ~UMediaCapture(); bool CaptureSceneViewport(TSharedPtr<FSceneViewport>& SceneViewport, FMediaCaptureOptions CaptureOptions); bool CaptureRHITexture(const FRHICaptureResourceDescription& ResourceDescription, FMediaCaptureOptions CaptureOptions); /** * Stop the current capture if there is one. * Then find and capture every frame from active SceneViewport.`
- L892 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anona371f9530103`)

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOAudioDebug.h` (Public)


#### struct `UE::MediaIOAudioDebug::FAudioDebugDump`  
`struct FAudioDebugDump`  
_L167-316_
- L170 _public function_ `template <typename Type> bool Start(const FString& InFileName, int32 InFramesToWrite)`
- L189 _public function_ `template <typename Type> void WriteToWavFile()`
- L212 _public function_ `template <typename Type> void WriteToCsvFile()`
- L240 _public function_ `template <typename Type> void Stop()`
- L252 _public function_ `template <typename Type> void CollectSamples(const TArray<Type>& AudioSamples)`
- L277 _public function_ `template <typename Type> void CollectSamples(const uint8* BufferToWrite, int32 BufferSize, uint8 NumChannels)` — Collects a single channel.
- L306 _public member_ `FString FolderPath;`
- L307 _public member_ `FString BaseFileName;`
- L308 _public member_ `int32 FrameWrittenIndex = 0;`
- L309 _public member_ `int32 LastWroteIndex = 0;`
- L310 _public member_ `int32 NumFramesToWrite = 0;`
- L311 _public member_ `bool bStarted = false;`
- L313 _public member_ `uint8 SampleSize = 0;`
- L314 _public member_ `TArray<uint8> CollectedSamples;`
- L315 _public member_ `int32 NumCollectedSamples = 0;`

#### struct `UE::MediaIOAudioDebug::FAudioDebugDumpSystem`  
`struct FAudioDebugDumpSystem`  
_L318-409_
- L320 _public member_ `TMap<FString, FAudioDebugDump> DebugInfoMap;`
- L323 _public function_ `template <typename Type> void StartDebugDump(const FString& BaseFileName)`
- L351 _public function_ `template <typename Type> void ProcessSamples(const FString& BaseFileName, const TArray<Type>& BufferToWrite)`
- L371 _public function_ `template <typename Type> void ProcessSamples(const FString& BaseFileName, const uint8* BufferToWrite, int32 BufferSize, uint8 NumChannels)`
- L391 _public function_ `template <typename Type> void ProcessAudio(const FString& BaseFileName, const TArray<Type>& BufferToWrite)`
- L401 _public function_ `template <typename Type> void ProcessAudio(const FString& BaseFileName, const uint8* BufferToWrite, int32 BufferSize, uint8 NumChannels)`

#### Free symbols / members of external scopes

- L28 _macro_ `#define MEDIA_IO_DUMP_AUDIO_MONO(Array)\`
- L31 _macro_ `#define MEDIA_IO_DUMP_AUDIO(Name, Buffer, BufferSize, SampleSize, NumChannels)\`
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace MediaIOAudioDebug` (scope `UE`)
- L36 _namespace_ `namespace Private` (scope `UE::MediaIOAudioDebug`)
- L38 _function_ `static void WriteUInt32ToByteArrayLE(TArray<uint8>& InByteArray, int32& Index, const uint32 Value)` (scope `UE::MediaIOAudioDebug::Private`)
- L46 _function_ `static void WriteUInt16ToByteArrayLE(TArray<uint8>& InByteArray, int32& Index, const uint16 Value)` (scope `UE::MediaIOAudioDebug::Private`)
- L52 _function_ `static void SerializeWaveFile(TArray<uint8>& OutWaveFileData, const uint8* InPCMData, const int32 NumBytes, const int32 NumChannels, const int32 SampleRate, const int32 BytesPerSample, bool bFloatingPoint)` (scope `UE::MediaIOAudioDebug::Private`)
- L146 _namespace_ `namespace UE`
- L146 _namespace_ `namespace MediaIOAudioDebug` (scope `UE`)
- L148 _variable_ `static int32 SecondsToDumpFor = 1;` (scope `UE::MediaIOAudioDebug`)
- L149 _variable_ `static bool bProcessAudio = false;` (scope `UE::MediaIOAudioDebug`)
- L151 _variable_ `static FAutoConsoleCommand CAudioDebug( TEXT("MediaIO.DumpAudio"), TEXT("[seconds (default: 1)] - Number of seconds to dump audio for."), FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args) { if (Args.Num()) { SecondsToDumpFor = FCString::Atoi(*Args[0]); } UE_LOGF(LogMediaIOAudioDebug, Display, "Starting to dump audio for %d seconds", SecondsToDumpFor); bProcessAudio = true; }), ECVF_Default);` (scope `UE::MediaIOAudioDebug`)
- L155 _function_ `` (scope `UE::MediaIOAudioDebug`)
- L411 _function_ `static FAudioDebugDumpSystem& GetSingleton()` (scope `UE::MediaIOAudioDebug`)

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreAudioOutput.h` (Public)


#### class `FMediaIOAudioOutput`  
`class FMediaIOAudioOutput`  
_L22-163_
- L34 _public prototype_ `FMediaIOAudioOutput(Audio::FPatchOutputStrongPtr InPatchOutput, const FAudioOptions& InAudioOptions);`
- L37 _public function_ `template <typename OutputType> static TArray<OutputType> ConvertAndUpmixBuffer(TConstArrayView<float> InBuffer, int32 InNumInputChannels, int32 InNumOutputChannels)`
- L86 _public function_ `template <typename OutputType> TArray<OutputType> GetAudioSamples() const` — Get the audio sample that were accumulated.
- L95 _public function_ `template <typename OutputType> TArray<OutputType> GetAudioSamples(uint32 NumSamplesToGet) const`
- L104 _public function_ `template <typename OutputType> TArray<OutputType> GetAllAudioSamples() const`
- L113 _public function_ `FOnBufferReceived& OnBufferReceived()` — `UE_DEPRECATED(5.6, "This function is deprecated because it is not implemented. Use UMediaIOCoreSubsystem::OnBufferReceived() instead.")`
- L120 _public member_ `int32 NumSamplesPerFrame = 0;` — @todo: Depend on frame number to correctly fetch the right amount of frames on framerates like 59.97
- L123 _public member_ `int32 NumInputChannels;` — Number of audio channels on the engine side.
- L126 _public member_ `int32 NumOutputChannels;` — Number of audio channels to output.
- L128 _public member_ `FFrameRate TargetFrameRate;`
- L131 _public member_ `uint32 MaxSampleLatency;` — Maximum number of samples to accumulate before they are discarded.
- L133 _public member_ `uint32 OutputSampleRate;`
- L136 _private prototype_ `int32 GetAudioBuffer(int32 InNumSamplesToPop, float* OutBuffer) const;`
- L137 _private prototype_ `Audio::FAlignedFloatBuffer GetFloatBuffer(uint32 NumSamplesToGet) const;`
- L159 _private member_ `Audio::FPatchOutputStrongPtr PatchOutput;` — The buffer accumulating audio samples.
- L162 _private member_ `FOnBufferReceived BufferReceivedDelegate;` — Callback called when a buffer is received. (Not used, deprecated)

#### struct `FMediaIOAudioOutput::FAudioOptions`  
`struct FAudioOptions`  
_L25-32_
- L27 _public member_ `uint32 InNumInputChannels = 0;`
- L28 _public member_ `uint32 InNumOutputChannels = 0;`
- L29 _public member_ `FFrameRate InTargetFrameRate;`
- L30 _public member_ `uint32 InMaxSampleLatency = 0;`
- L31 _public member_ `uint32 InOutputSampleRate = 0;`

#### struct `FMediaIOAudioOutput::TSampleConverter`  
`template <typename OutputType> struct TSampleConverter`  
_L141-155_
- desc: Sample conversion helper template.
- L143 _public member_ `const double Scale;`
- L145 _public function_ `constexpr TSampleConverter() : Scale(TNumericLimits<OutputType>::Max())`
- L149 _public function_ `OutputType ConvertSample(const float InFloatValue) const`
- L169 _public function_ `float ConvertSample(const float InFloatValue) const`

#### struct `FMediaIOAudioOutput::TSampleConverter`  
`template <> struct FMediaIOAudioOutput::TSampleConverter<float>`  
_L167-173_
- desc: Specialization for float buffers.
- L143 _public member_ `const double Scale;`
- L145 _public function_ `constexpr TSampleConverter() : Scale(TNumericLimits<OutputType>::Max())`
- L149 _public function_ `OutputType ConvertSample(const float InFloatValue) const`
- L169 _public function_ `float ConvertSample(const float InFloatValue) const`

#### class `FMediaIOAudioCapture`  
`class FMediaIOAudioCapture : public ISubmixBufferListener`  
_L178-250_
- inherits: `ISubmixBufferListener`
- desc: Handles capturing audio samples rendered by the engine and dispatching them to outputs.
- L181 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnAudioCaptured, float* , int32 );`
- L183 _public prototype_ `FMediaIOAudioCapture() = default;`
- L188 _public prototype_ `virtual void OnNewSubmixBuffer(const USoundSubmix* InOwningSubmix, float* InAudioData, int32 InNumSamples, int32 InNumChannels, const int32 InSampleRate, double InAudioClock) override;`
- L189 _public prototype_ `virtual const FString& GetListenerName() const override;`
- L193 _public prototype_ `void Initialize(const FAudioDeviceHandle& InAudioDeviceHandle);` — `UE_DEPRECATED(5.6, "Use the version that takes in the AudioCapturedDelegate.")`
- L199 _public prototype_ `void Initialize(const FAudioDeviceHandle& InAudioDeviceHandle, const FOnAudioCaptured& InAudioCapturedDelegate);` — Initializes audio capture for the given audio device The audio capture delegate can't be changed post Initialize.
- L202 _public prototype_ `TSharedPtr<FMediaIOAudioOutput> CreateAudioOutput(int32 InNumOutputChannels, FFrameRate InTargetFrameRate, uint32 InMaxSampleLatency, uint32 InOutputSampleRate);` — Create an audio output that will receive audio samples.
- L205 _public function_ `FOnAudioCaptured& OnAudioCaptured_RenderThread()` — `UE_DEPRECATED(5.6, "This function is not thread safe. AudioCapturedDelegate must be passed as parameter to Initialize instead.")`
- L211 _public function_ `int32 GetNumInputChannels() const` — Returns the number of channels from the audio mixer device (engine side).
- L217 _protected prototype_ `void RegisterBufferListener(FAudioDevice* AudioDevice);`
- L218 _protected prototype_ `void UnregisterBufferListener(FAudioDevice* AudioDevice);`
- L220 _protected prototype_ `void RegisterAudioDevice(const FAudioDeviceHandle& InAudioDeviceHandle);`
- L221 _protected prototype_ `void UnregisterAudioDevice();`
- L224 _protected prototype_ `void SetAudioCapturedDelegate(const FOnAudioCaptured& InAudioCapturedDelegate);` — This must be called in Initialize only, and before calling RegisterBufferListener.
- L228 _private member_ `Audio::FDeviceId RegisteredDeviceId = INDEX_NONE;` — Audio device Id this buffer listener is registered to.
- L231 _private member_ `uint32 SampleRate = 0;` — Sample rate on the engine side.
- L237 _private member_ `TSharedPtr<ISubmixBufferListener> SubmixBufferListenerProxy;` — We need to proxy the submit buffer listener to be able to unregister it in the destructor.
- L240 _private member_ `FName PrimarySubmixName;` — Used to make sure we only accumulate audio from the primary submix.
- L243 _private member_ `int32 NumChannels = 0;` — Number of channels on the engine side.
- L246 _private member_ `Audio::FPatchSplitter AudioSplitter;` — Utility that allows pushing audio samples to multiple outputs.
- L249 _private member_ `FOnAudioCaptured AudioCapturedDelegate;` — Callback for a audio rendered event.

#### class `FMainMediaIOAudioCapture`  
`class FMainMediaIOAudioCapture : public FMediaIOAudioCapture`  
_L258-278_
- inherits: `FMediaIOAudioCapture`
- desc: Audio capture that automatically registers to the main engine device. Also, handles automatically registering to the current PIE world's audio device. This audio capture is used by default if no audio device handle is specified when media capture creates the audio output.
- L261 _public prototype_ `FMainMediaIOAudioCapture();`
- L265 _public prototype_ `void Initialize();` — `UE_DEPRECATED(5.6, "Use the version that takes in the AudioCapturedDelegate.")`
- L268 _public prototype_ `void Initialize(const FOnAudioCaptured& InAudioCapturedDelegate);` — Initializes audio capture for the main audio device
- L272 _private prototype_ `void OnPIEStarted(const bool);`
- L273 _private prototype_ `void OnPIEEnded(const bool);`
- L276 _private prototype_ `void RegisterMainAudioDevice();`
- L277 _private prototype_ `void RegisterCurrentAudioDevice();`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBufferReceived, uint8* Buffer, int32 BufferSize);`
- L20 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnBufferReceived, uint8* Buffer, int32 BufferSize);`
- L181 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnAudioCaptured, float* , int32 );`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreAudioSampleBase.h` (Public)


#### class `FMediaIOCoreAudioSampleBase`  
`class FMediaIOCoreAudioSampleBase : public IMediaAudioSample , public IMediaPoolable`  
_L13-158_
- inherits: `IMediaAudioSample,IMediaPoolable`
- desc: Implements a media audio sample.
- L20 _public prototype_ `FMediaIOCoreAudioSampleBase();` — Default constructor.
- L32 _public prototype_ `bool Initialize(const int32* InAudioBuffer, uint32 InBufferSize, uint32 InNumberOfChannels, uint32 InSampleRate, FTimespan InTime, const TOptional<FTimecode>& InTimecode);` — Initialize the sample. @param InAudioBuffer The audio frame data. @param InBufferSize The size of the audio buffer. @param InNumberOfChannels The number of channel of the audio buffer. @param InSampleRate The sample rate of the audio buffer. @param InTime The sample time (in the player's own clock). @param InTimecode The sample timecode if available.
- L43 _public prototype_ `bool Initialize(TArray<int32> InAudioBuffer, uint32 InNumberOfChannels, uint32 InSampleRate, FTimespan InTime, const TOptional<FTimecode>& InTimecode);` — Initialize the sample. @param InAudioBuffer The audio frame data. @param InNumberOfChannels The number of channel of the audio buffer. @param InSampleRate The sample rate of the audio buffer. @param InTime The sample time (in the player's own clock). @param InTimecode The sample timecode if available.
- L52 _public prototype_ `bool SetBuffer(const int32* InAudioBuffer, uint32 InBufferSize);` — Set the sample buffer. @param InAudioBuffer The audio frame data. @param InBufferSize The size of the audio buffer.
- L59 _public prototype_ `bool SetBuffer(TArray<int32> InAudioBuffer);` — Set the sample buffer. @param InAudioBuffer The audio frame data.
- L70 _public prototype_ `bool SetProperties(uint32 InBufferSize, uint32 InNumberOfChannels, uint32 InSampleRate, FTimespan InTime, const TOptional<FTimecode>& InTimecode);` — Set the sample properties. @param InBufferSize The size of the audio buffer. @param InNumberOfChannels The number of channel of the audio buffer. @param InSampleRate The sample rate of the audio buffer. @param InTime The sample time (in the player's own clock). @param InTimecode The sample timecode if available.
- L79 _public prototype_ `virtual void* RequestBuffer(uint32 InBufferSize);` — Request an uninitialized sample buffer. Should be used when the buffer could be filled by something else. SetProperties should still be called after. @param InBufferSize The size of the audio buffer.
- L85 _public function_ `virtual const void* GetBuffer() override`
- L90 _public function_ `virtual uint32 GetChannels() const override`
- L95 _public function_ `virtual FTimespan GetDuration() const override`
- L100 _public function_ `virtual EMediaAudioSampleFormat GetFormat() const override`
- L105 _public function_ `virtual uint32 GetFrames() const override`
- L110 _public function_ `virtual uint32 GetSampleRate() const override`
- L115 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L120 _public function_ `virtual TOptional<FTimecode> GetTimecode() const override`
- L129 _public function_ `virtual void ShutdownPoolable() override`
- L135 _protected function_ `virtual void FreeSample()`
- L142 _protected member_ `TArray<int32> Buffer;` — The sample's frame buffer.
- L145 _protected member_ `uint32 Channels;` — Number of audio channels.
- L148 _protected member_ `FTimespan Duration;` — The duration for which the sample is valid.
- L151 _protected member_ `uint32 SampleRate;` — Audio sample rate (in samples per second).
- L154 _protected member_ `FTimespan Time;` — Sample time.
- L157 _protected member_ `TOptional<FTimecode> Timecode;` — Sample timecode.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MEDIAIOCORE_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreBinarySampleBase.h` (Public)


#### class `FMediaIOCoreBinarySampleBase`  
`class FMediaIOCoreBinarySampleBase : public IMediaBinarySample , public IMediaPoolable`  
_L13-132_
- inherits: `IMediaBinarySample,IMediaPoolable`
- desc: Implements a media binary data sample.
- L20 _public prototype_ `FMediaIOCoreBinarySampleBase();` — Default constructor.
- L31 _public prototype_ `bool Initialize(const uint8* InBinaryBuffer, uint32 InBufferSize, FTimespan InTime, const FFrameRate& InFrameRate, const TOptional<FTimecode>& InTimecode);` — Initialize the sample. @param InBinaryBuffer The metadata frame data. @param InBufferSize The size of the InBinaryBuffer. @param InTime The sample time (in the player's own clock). @param InFrameRate The framerate of the media that produce the sample. @param InTimecode The sample timecode if available.
- L40 _public prototype_ `bool Initialize(TArray<uint8> InBinaryBuffer, FTimespan InTime, const FFrameRate& InFrameRate, const TOptional<FTimecode>& InTimecode);` — Initialize the sample. @param InBinaryBuffer The metadata frame data. @param InTimecode The sample timecode if available. @param InTime The sample time (in the player's own clock).
- L48 _public prototype_ `bool SetBuffer(const uint8* InBinaryBuffer, uint32 InBufferSize);` — Set the sample buffer. @param InBinaryBuffer The metadata frame data. @param InBufferSize The size of the InBinaryBuffer.
- L55 _public prototype_ `bool SetBuffer(TArray<uint8> InBinaryBuffer);` — Set the sample buffer. @param InBinaryBuffer The metadata frame data.
- L64 _public prototype_ `bool SetProperties(FTimespan InTime, const FFrameRate& InFrameRate, const TOptional<FTimecode>& InTimecode);` — Set the sample properties. @param InTime The sample time (in the player's own clock). @param InFrameRate The framerate of the media that produce the sample. @param InTimecode The sample timecode if available.
- L73 _public prototype_ `virtual void* RequestBuffer(uint32 InBufferSize);` — Request an uninitialized sample buffer. Should be used when the buffer could be filled by something else. SetProperties should still be called after. @param InBufferSize The size of the metadata buffer.
- L79 _public function_ `virtual const void* GetData() override`
- L84 _public function_ `virtual FTimespan GetDuration() const override`
- L89 _public function_ `virtual uint32 GetSize() const override`
- L94 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L99 _public function_ `virtual TOptional<FTimecode> GetTimecode() const override`
- L108 _public function_ `virtual void ShutdownPoolable() override`
- L115 _protected function_ `virtual void FreeSample()`
- L122 _protected member_ `TArray<uint8> Buffer;` — The sample's frame buffer.
- L125 _protected member_ `FTimespan Duration;` — Duration for which the sample is valid.
- L128 _protected member_ `FTimespan Time;` — Sample time.
- L131 _protected member_ `TOptional<FTimecode> Timecode;` — Sample timecode.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MEDIAIOCORE_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreCaptionSampleBase.h` (Public)


#### class `FMediaIOCoreCaptionSampleBase`  
`class FMediaIOCoreCaptionSampleBase : public IMediaOverlaySample , public IMediaPoolable`  
_L12-16_
- inherits: `IMediaOverlaySample,IMediaPoolable`
- desc: Implements a media caption sample.

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreCommonDisplayMode.h` (Public)


#### struct `FMediaIOCommonDisplayModeInfo`  
`struct FMediaIOCommonDisplayModeInfo`  
_L12-19_
- L14 _public member_ `int32 Width;`
- L15 _public member_ `int32 Height;`
- L16 _public member_ `FFrameRate FrameRate;`
- L17 _public member_ `EMediaIOStandardType Standard;`
- L18 _public member_ `FText Name;`

#### struct `FMediaIOCommonDisplayModeResolutionInfo`  
`struct FMediaIOCommonDisplayModeResolutionInfo`  
_L21-26_
- L23 _public member_ `int32 Width;`
- L24 _public member_ `int32 Height;`
- L25 _public member_ `FText Name;`

#### struct `FMediaIOCommonDisplayModes`  
`struct FMediaIOCommonDisplayModes`  
_L28-40_
- L30 _public prototype_ `static TArrayView<const FMediaIOCommonDisplayModeInfo> GetAllModes();`
- L31 _public prototype_ `static TArrayView<const FMediaIOCommonDisplayModeResolutionInfo> GetAllResolutions();`
- L33 _public prototype_ `static const FMediaIOCommonDisplayModeResolutionInfo* Find(int32 InWidth, int32 InHeight);`
- L34 _public prototype_ `static const FMediaIOCommonDisplayModeInfo* Find(int32 InWidth, int32 InHeight, const FFrameRate& InFrameRate, EMediaIOStandardType InStandard);`
- L35 _public function_ `static bool Contains(int32 InWidth, int32 InHeight)`
- L36 _public function_ `static bool Contains(int32 InWidth, int32 InHeight, const FFrameRate& InFrameRate, EMediaIOStandardType InStandard)`
- L38 _public prototype_ `static FText GetMediaIOCommonDisplayModeResolutionInfoName(int32 InWidth, int32 InHeight);`
- L39 _public prototype_ `static FText GetMediaIOCommonDisplayModeInfoName(int32 InWidth, int32 InHeight, const FFrameRate& InFrameRate, EMediaIOStandardType InStandard);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MEDIAIOCORE_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreDefinitions.h` (Public)


#### enum `EMediaIOTransportType`  
`enum class EMediaIOTransportType`  
_L17-23_
- reflection: `UENUM()`
- desc: Media transport type.
- L19 _public enumerator_ `SingleLink`
- L20 _public enumerator_ `DualLink`
- L21 _public enumerator_ `QuadLink`
- L22 _public enumerator_ `HDMI`

#### enum `EMediaIOQuadLinkTransportType`  
`enum class EMediaIOQuadLinkTransportType`  
_L30-34_
- reflection: `UENUM()`
- desc: Quad link transport type.
- L32 _public enumerator_ `SquareDivision`
- L33 _public enumerator_ `TwoSampleInterleave`

#### enum `EMediaIOStandardType`  
`enum class EMediaIOStandardType`  
_L41-46_
- reflection: `UENUM()`
- desc: SDI transport type.
- L43 _public enumerator_ `Progressive`
- L44 _public enumerator_ `Interlaced`
- L45 _public enumerator_ `ProgressiveSegmentedFrame`

#### enum `EMediaIOTimecodeFormat`  
`enum class EMediaIOTimecodeFormat`  
_L52-57_
- reflection: `UENUM()`
- desc: Timecode formats.
- L54 _public enumerator_ `None`
- L55 _public enumerator_ `LTC`
- L56 _public enumerator_ `VITC`

#### enum `EMediaIOAutoDetectableTimecodeFormat`  
`enum class EMediaIOAutoDetectableTimecodeFormat : uint8`  
_L63-69_
- reflection: `UENUM()`
- desc: Timecode formats.
- L65 _public enumerator_ `None = 0`
- L66 _public enumerator_ `LTC`
- L67 _public enumerator_ `VITC`
- L68 _public enumerator_ `Auto = 255`

#### enum `EMediaIOInterlaceFieldOrder`  
`enum class EMediaIOInterlaceFieldOrder : uint8`  
_L75-79_
- reflection: `UENUM()`
- desc: Which interlace field should be set first in the buffer.
- L77 _public enumerator_ `TopFieldFirst`
- L78 _public enumerator_ `BottomFieldFirst`

#### enum `EMediaIOSampleEvaluationType`  
`enum class EMediaIOSampleEvaluationType : uint8`  
_L85-90_
- reflection: `UENUM()`
- desc: Various sample evaluation types available in MediaIO.
- L87 _public enumerator_ `Latest`
- L88 _public enumerator_ `PlatformTime`
- L89 _public enumerator_ `Timecode`

#### struct `FMediaIOAutoDetectableTimecodeFormat_Backup`  
`struct FMediaIOAutoDetectableTimecodeFormat_Backup`  
_L128-138_
- reflection: `USTRUCT()`
- L134 _public member_ `EMediaIOTimecodeFormat TimecodeFormat = EMediaIOTimecodeFormat::None;` — `UPROPERTY(EditAnywhere, Category = "Configuration")` — The timecode format if not autodetected.
- L137 _public member_ `bool bAutoDetect = false;` — `UPROPERTY(EditAnywhere, Category = "Configuration")` — Whether the timecode should be autodetected.

#### enum `EMediaIOInputType`  
`enum class EMediaIOInputType`  
_L144-148_
- reflection: `UENUM()`
- desc: SDI Input type.
- L146 _public enumerator_ `Fill UMETA(DisplayName="Fill")`
- L147 _public enumerator_ `FillAndKey UMETA(DisplayName="Fill & Key")`

#### enum `EMediaIOOutputType`  
`enum class EMediaIOOutputType`  
_L154-158_
- reflection: `UENUM()`
- desc: SDI Output type.
- L156 _public enumerator_ `Fill UMETA(DisplayName="Fill")`
- L157 _public enumerator_ `FillAndKey UMETA(DisplayName="Fill & Key")`

#### enum `EMediaIOReferenceType`  
`enum class EMediaIOReferenceType`  
_L165-170_
- reflection: `UENUM()`
- desc: SDI Output type.
- L167 _public enumerator_ `FreeRun`
- L168 _public enumerator_ `External`
- L169 _public enumerator_ `Input`

#### struct `FMediaIODevice`  
`struct FMediaIODevice`  
_L177-197_
- reflection: `USTRUCT()`
- desc: Identifies a device.
- L182 _public prototype_ `FMediaIODevice();`
- L186 _public member_ `FName DeviceName;` — `UPROPERTY(EditAnywhere, Category=Device)` — The retail/display name of the Device.
- L190 _public member_ `int32 DeviceIdentifier;` — `UPROPERTY(EditAnywhere, Category=Device)` — The device identifier.
- L193 _public prototype_ `bool operator==(const FMediaIODevice& Other) const;`
- L196 _public prototype_ `bool IsValid() const;` — Return true if the device has been set properly

#### struct `FMediaIOConnection`  
`struct FMediaIOConnection`  
_L204-242_
- reflection: `USTRUCT()`
- desc: Identifies an media connection.
- L209 _public prototype_ `FMediaIOConnection();`
- L213 _public member_ `FMediaIODevice Device;` — `UPROPERTY(EditAnywhere, Category=Connection)` — The device identifier.
- L217 _public member_ `FName Protocol;` — `UPROPERTY(EditAnywhere, Category=Connection)` — The protocol used by the MediaFramework.
- L221 _public member_ `EMediaIOTransportType TransportType;` — `UPROPERTY(EditAnywhere, Category=Connection)` — The type of cable link used for that configuration
- L225 _public member_ `EMediaIOQuadLinkTransportType QuadTransportType;` — `UPROPERTY(EditAnywhere, Category=Connection)` — The type of cable link used for that configuration
- L229 _public member_ `int32 PortIdentifier;` — `UPROPERTY(EditAnywhere, Category=Connection)` — The port of the video channel on the device.
- L232 _public prototype_ `bool operator==(const FMediaIOConnection& Other) const;`
- L238 _public prototype_ `FString ToUrl() const;` — Get a url used by the media framework @return Url representation, "protocol://device0/single1"
- L241 _public prototype_ `bool IsValid() const;` — Return true if the connection has been set properly

#### struct `FMediaIOMode`  
`struct FMediaIOMode`  
_L249-281_
- reflection: `USTRUCT()`
- desc: Identifies a media mode.
- L254 _public prototype_ `FMediaIOMode();`
- L259 _public member_ `FFrameRate FrameRate;` — `UPROPERTY(VisibleAnywhere, Category=Mode)` — The mode's frame rate.
- L263 _public member_ `FIntPoint Resolution;` — `UPROPERTY(VisibleAnywhere, Category=Mode)` — The mode's image resolution.
- L267 _public member_ `EMediaIOStandardType Standard;` — `UPROPERTY(VisibleAnywhere, Category=Mode)` — The mode's scanning type.
- L271 _public member_ `int32 DeviceModeIdentifier;` — `UPROPERTY(VisibleAnywhere, Category=Mode)` — The mode's identifier for the device.
- L274 _public prototype_ `bool operator==(const FMediaIOMode& Other) const;`
- L277 _public prototype_ `FText GetModeName() const;` — Return the name of this mode from MediaIOCommonDisplayModes.
- L280 _public prototype_ `bool IsValid() const;` — Return true if the mode has been set properly.

#### struct `FMediaIOConfiguration`  
`struct FMediaIOConfiguration`  
_L288-313_
- reflection: `USTRUCT()`
- desc: Configuration of a device input / output.
- L293 _public prototype_ `FMediaIOConfiguration();`
- L298 _public member_ `bool bIsInput;` — `UPROPERTY()` — Configured as an input or output.
- L302 _public member_ `FMediaIOConnection MediaConnection;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — The configuration's device and transport type.
- L306 _public member_ `FMediaIOMode MediaMode;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — The configuration's video mode.
- L309 _public prototype_ `bool operator== (const FMediaIOConfiguration& Other) const;`
- L312 _public prototype_ `bool IsValid() const;` — Return true if the configuration has been set properly

#### struct `FMediaIOInputConfiguration`  
`struct FMediaIOInputConfiguration`  
_L319-343_
- reflection: `USTRUCT()`
- desc: Configuration of a device input.
- L324 _public prototype_ `FMediaIOInputConfiguration();`
- L328 _public member_ `FMediaIOConfiguration MediaConfiguration;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — The signal input format.
- L332 _public member_ `EMediaIOInputType InputType;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — Whether to input the fill or the fill and key.
- L336 _public member_ `int32 KeyPortIdentifier;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — The port of the video channel on the device to input the key from.
- L339 _public prototype_ `bool operator== (const FMediaIOInputConfiguration& Other) const;`
- L342 _public prototype_ `bool IsValid() const;` — Return true if the configuration has been set properly

#### struct `FMediaIOOutputConfiguration`  
`struct FMediaIOOutputConfiguration`  
_L349-385_
- reflection: `USTRUCT()`
- desc: Configuration of a device output.
- L354 _public prototype_ `FMediaIOOutputConfiguration();`
- L358 _public member_ `FMediaIOConfiguration MediaConfiguration;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — The signal output format.
- L362 _public member_ `EMediaIOOutputType OutputType;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — Whether to output the fill or the fill and key.
- L370 _public member_ `int32 KeyPortIdentifier;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — The port of the video channel on the device to output the key to. @note	'Frame Buffer Pixel Format' must be set to at least 8 bits of alpha. @note	'Enable alpha channel support in post-processing' must be set to 'Allow through tonemapper'.
- L374 _public member_ `EMediaIOReferenceType OutputReference;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — The Device output sync with either its internal clock, an external reference, or an other input.
- L378 _public member_ `int32 ReferencePortIdentifier;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — The port of the video channel on the device to output the synchronize to.
- L381 _public prototype_ `bool operator== (const FMediaIOOutputConfiguration& Other) const;`
- L384 _public prototype_ `bool IsValid() const;` — Return true if the configuration has been set properly

#### struct `FMediaIOVideoTimecodeConfiguration`  
`struct FMediaIOVideoTimecodeConfiguration`  
_L391-414_
- reflection: `USTRUCT()`
- desc: Configuration of a Timecode from Video
- L397 _public member_ `FMediaIOConfiguration MediaConfiguration;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — Read the timecode from a video signal.
- L401 _public member_ `EMediaIOAutoDetectableTimecodeFormat TimecodeFormat = EMediaIOAutoDetectableTimecodeFormat::Auto;` — `UPROPERTY(VisibleAnywhere, Category=Configuration)` — Timecode format to read from a video signal.
- L405 _public prototype_ `bool IsValid() const;` — Return true if the configuration has been set properly
- L407 _public prototype_ `bool operator== (const FMediaIOVideoTimecodeConfiguration& Other) const;`
- L413 _public prototype_ `FText ToText(bool bAutoDetected = false) const;` — Get the configuration text representation. @return String representation, i.e. "Video/Single1/1080p30fps/LTC".

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MEDIAIOCORE_API`
- L92 _namespace_ `namespace UE`
- L92 _namespace_ `namespace MediaIO` (scope `UE`)
- L94 _function_ `static EMediaIOAutoDetectableTimecodeFormat ToAutoDetectableTimecodeFormat(EMediaIOTimecodeFormat TimecodeFormat)` (scope `UE::MediaIO`)
- L110 _function_ `static EMediaIOTimecodeFormat FromAutoDetectableTimecodeFormat(EMediaIOAutoDetectableTimecodeFormat TimecodeFormat)` (scope `UE::MediaIO`)

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreDeinterlacer.h` (Public)


#### struct `UE::MediaIOCore::FVideoFrame`  
`struct FVideoFrame`  
_L17-79_
- desc: Description of a video frame.
- L19 _public function_ `FVideoFrame(const void* InVideoBuffer , uint32 InBufferSize , uint32 InStride , uint32 InWidth , uint32 InHeight , EMediaTextureSampleFormat InSampleFormat , FTimespan InTime , const FFrameRate& InFrameRate , const TOptional<FTimecode>& InTimecode , TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> InSourceColorSettings) : VideoBuffer(InVideoBuffer) , BufferSize(InBufferSize) , Stride(InStride) , Width(InWidth) , Height(InHeight) , SampleFormat(InSampleFormat) , Time(InTime) , FrameRate(InFrameRate) , Timecode(InTimecode) , SourceColorSettings(InSourceColorSettings)`
- L42 _public member_ `const void* VideoBuffer;`
- L43 _public member_ `uint32 BufferSize;`
- L44 _public member_ `uint32 Stride;`
- L45 _public member_ `uint32 Width;`
- L46 _public member_ `uint32 Height;`
- L47 _public member_ `EMediaTextureSampleFormat SampleFormat;`
- L48 _public member_ `FTimespan Time;`
- L49 _public member_ `const FFrameRate& FrameRate;`
- L50 _public member_ `const TOptional<FTimecode>& Timecode;`
- L51 _public member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> SourceColorSettings;`

#### class `UE::MediaIOCore::FDeinterlacer`  
`class FDeinterlacer`  
_L84-109_
- desc: Handles deinterlacing a video signal.
- L87 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<FMediaIOCoreTextureSampleBase>, FOnAcquireSample_AnyThread);`
- L89 _public prototype_ `FDeinterlacer() = default;`
- L90 _public function_ `FDeinterlacer(FOnAcquireSample_AnyThread InOnAcquireSample, EMediaIOInterlaceFieldOrder InInterlaceFieldOrder) : AcquireSampleDelegate(MoveTemp(InOnAcquireSample)) , InterlaceFieldOrder(InInterlaceFieldOrder)`
- L96 _public prototype_ `virtual ~FDeinterlacer() = default;`
- L103 _public prototype_ `virtual TArray<TSharedRef<FMediaIOCoreTextureSampleBase>> Deinterlace(const FVideoFrame& InVideoFrame) const;` — Default implementation which applies no deinterlacing. @param InVideoFrame The video buffer and its metadata. @return One or more sample depending on the deinterlacing method.
- L106 _protected member_ `FOnAcquireSample_AnyThread AcquireSampleDelegate;` — Delegate called to acquire samples.
- L108 _protected member_ `EMediaIOInterlaceFieldOrder InterlaceFieldOrder = EMediaIOInterlaceFieldOrder::TopFieldFirst;` — What order should fields be read in.

#### class `UE::MediaIOCore::FBobDeinterlacer`  
`class FBobDeinterlacer : public FDeinterlacer`  
_L112-120_
- inherits: `FDeinterlacer`
- desc: Line-double each field independently. Two output samples per source frame at full vertical resolution; doubles temporal resolution.
- L115 _public function_ `FBobDeinterlacer(FOnAcquireSample_AnyThread InOnAcquireSample, EMediaIOInterlaceFieldOrder InInterlaceFieldOrder) : FDeinterlacer(MoveTemp(InOnAcquireSample), InInterlaceFieldOrder)`
- L119 _public prototype_ `virtual TArray<TSharedRef<FMediaIOCoreTextureSampleBase>> Deinterlace(const FVideoFrame& InVideoFrame) const override;`

#### class `UE::MediaIOCore::FBlendDeinterlacer`  
`class FBlendDeinterlacer : public FDeinterlacer`  
_L123-131_
- inherits: `FDeinterlacer`
- desc: Line-doubles both fields to full height and per-pixel averages them. One sample per source frame.
- L126 _public function_ `FBlendDeinterlacer(FOnAcquireSample_AnyThread InOnAcquireSample, EMediaIOInterlaceFieldOrder InInterlaceFieldOrder) : FDeinterlacer(MoveTemp(InOnAcquireSample), InInterlaceFieldOrder)`
- L130 _public prototype_ `virtual TArray<TSharedRef<FMediaIOCoreTextureSampleBase>> Deinterlace(const FVideoFrame& InVideoFrame) const override;`

#### class `UE::MediaIOCore::FDiscardDeinterlacer`  
`class FDiscardDeinterlacer : public FDeinterlacer`  
_L134-142_
- inherits: `FDeinterlacer`
- desc: Discards one of the fields (based on InterlaceFieldOrder) and line-doubles the kept field to full height. Halves temporal resolution; preserves vertical resolution via line-doubling.
- L137 _public function_ `FDiscardDeinterlacer(FOnAcquireSample_AnyThread InOnAcquireSample, EMediaIOInterlaceFieldOrder InInterlaceFieldOrder) : FDeinterlacer(MoveTemp(InOnAcquireSample), InInterlaceFieldOrder)`
- L141 _public prototype_ `virtual TArray<TSharedRef<FMediaIOCoreTextureSampleBase>> Deinterlace(const FVideoFrame& InVideoFrame) const override;`

#### class `UVideoDeinterlacer`  
`class UVideoDeinterlacer : public UObject`  
_L151-159_
- reflection: `UCLASS(MinimalAPI, Abstract, editinlinenew)`
- inherits: `UObject`
- desc: Represents a deinterlacing algorithm. Will dictate how the incoming video signal is converted from interlace to a progressive signal.
- L158 _public prototype_ `virtual TSharedPtr<UE::MediaIOCore::FDeinterlacer> Instantiate(UE::MediaIOCore::FDeinterlacer::FOnAcquireSample_AnyThread InAcquireSampleDelegate, EMediaIOInterlaceFieldOrder InInterlaceFieldOrder) const PURE_VIRTUAL(UVideoDeinterlacer::Instantiate, return nullptr; );` — Creates an instance of a FDeinterlacer that represents a deinterlacing algorithm.

#### class `UBobDeinterlacer`  
`class UBobDeinterlacer : public UVideoDeinterlacer`  
_L164-172_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UVideoDeinterlacer`
- desc: Doubles the frame rate by treating each field as its own moment. Smoothest motion when the engine can sustain the doubled rate.
- L168 _public function_ `virtual TSharedPtr<UE::MediaIOCore::FDeinterlacer> Instantiate(UE::MediaIOCore::FDeinterlacer::FOnAcquireSample_AnyThread InAcquireSampleDelegate, EMediaIOInterlaceFieldOrder InInterlaceFieldOrder) const override`

#### class `UBlendDeinterlacer`  
`class UBlendDeinterlacer : public UVideoDeinterlacer`  
_L176-184_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UVideoDeinterlacer`
- desc: Combines both fields into a single full-resolution image. Moving objects appear slightly ghosted.
- L180 _public function_ `virtual TSharedPtr<UE::MediaIOCore::FDeinterlacer> Instantiate(UE::MediaIOCore::FDeinterlacer::FOnAcquireSample_AnyThread InAcquireSampleDelegate, EMediaIOInterlaceFieldOrder InInterlaceFieldOrder) const override`

#### class `UDiscardDeinterlacer`  
`class UDiscardDeinterlacer : public UVideoDeinterlacer`  
_L188-196_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UVideoDeinterlacer`
- desc: Keeps a single field and line-doubles it. Simple and clean, but with reduced vertical detail.
- L192 _public function_ `virtual TSharedPtr<UE::MediaIOCore::FDeinterlacer> Instantiate(UE::MediaIOCore::FDeinterlacer::FOnAcquireSample_AnyThread InAcquireSampleDelegate, EMediaIOInterlaceFieldOrder InInterlaceFieldOrder) const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MEDIAIOCORE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MediaIOCore` (scope `UE`)
- L87 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<FMediaIOCoreTextureSampleBase>, FOnAcquireSample_AnyThread);`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreEncodeTime.h` (Public)


#### enum `EMediaIOCoreEncodePixelFormat`  
`enum class EMediaIOCoreEncodePixelFormat`  
_L10-16_
- L12 _public enumerator_ `A2B10G10R10`
- L13 _public enumerator_ `CharBGRA`
- L14 _public enumerator_ `CharUYVY`
- L15 _public enumerator_ `YUVv210`

#### class `FMediaIOCoreEncodeTime`  
`class FMediaIOCoreEncodeTime`  
_L18-61_
- L21 _public prototype_ `FMediaIOCoreEncodeTime(EMediaIOCoreEncodePixelFormat InFormat, void* InBuffer, uint32 InPitch, uint32 InWidth, uint32 InHeight, uint32 XOffset = 0, uint32 YOffset = 0);`
- L22 _public prototype_ `void Render(uint32 InHours, uint32 InMinutes, uint32 InSeconds, uint32 InFrames) const;`
- L25 _protected typedef_ `using TColor = int32;`
- L26 _protected prototype_ `void DrawChar(uint32 InX, uint32 InChar) const;`
- L27 _protected prototype_ `void DrawTime(uint32 InX, uint32 InTime) const;`
- L28 _protected prototype_ `void SetPixelScaled(uint32 InX, uint32 InY, bool InSet, uint32 InScale) const;`
- L29 _protected prototype_ `void SetPixel(uint32 InX, uint32 InY, bool InSet) const;`
- L31 _protected function_ `inline TColor& At(uint32 InX, uint32 InY) const`
- L38 _protected member_ `EMediaIOCoreEncodePixelFormat Format;` — Pixel format
- L41 _protected member_ `void* Buffer;` — Pointer to pixels
- L44 _protected member_ `uint32 Pitch;` — Pitch of image
- L47 _protected member_ `uint32 Width;` — Width of image
- L50 _protected member_ `uint32 Height;` — Height of image
- L53 _protected member_ `uint32 XPixelOffset;` — X pixel offset of the rendered timecode.
- L56 _protected member_ `uint32 YPixelOffset;` — Y pixel offset of the rendered timecode.
- L59 _protected member_ `TColor ColorBlack;`
- L60 _protected member_ `TColor ColorWhite;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MEDIAIOCORE_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreFileWriter.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace MediaIOCoreFileWriter`
- L9 _prototype_ `void WriteRawFile(const FString& InFilename, uint8* InBuffer, uint32 InSize, bool bAppend = true);` (scope `MediaIOCoreFileWriter`)

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCorePlayerBase.h` (Public)


#### enum `EMediaIOCoreColorFormat`  
`enum class EMediaIOCoreColorFormat : uint8`  
_L42-46_
- L44 _public enumerator_ `YUV8`
- L45 _public enumerator_ `YUV10`

#### struct `FMediaIOCoreMediaOption`  
`struct FMediaIOCoreMediaOption`  
_L48-55_
- L50 _public member_ `static const FName FrameRateNumerator;`
- L51 _public member_ `static const FName FrameRateDenominator;`
- L52 _public member_ `static const FName ResolutionWidth;`
- L53 _public member_ `static const FName ResolutionHeight;`
- L54 _public member_ `static const FName VideoModeName;`

#### class `FMediaIOCorePlayerBase`  
`class FMediaIOCorePlayerBase : public IMediaPlayer , protected IMediaCache , protected IMediaControls , protected IMediaTracks , protected IMediaView , public ITimedDataInput , public TSharedFromThis<FMediaIOCorePlayerBase>`  
_L79-440_
- inherits: `IMediaPlayer,IMediaCache,IMediaControls,IMediaTracks,IMediaView,ITimedDataInput,TSharedFromThis<FMediaIOCorePlayerBase>`
- desc: Implements a base player for hardware IO cards. The processing of metadata and video frames is delayed until the fetch stage (TickFetch) in order to increase the window of opportunity for receiving frames for the current render frame time code. Depending on whether the media source enables time code synchronization, the player's current play time (CurrentTime) is derived either from the time codes embedded in frames or from the Engine's global time code.
- L95 _public prototype_ `FMediaIOCorePlayerBase(IMediaEventSink& InEventSink);` — Create and initialize a new instance. @param InEventSink The object that receives media events from this player.
- L98 _public prototype_ `virtual ~FMediaIOCorePlayerBase();` — Virtual destructor.
- L104 _public prototype_ `virtual void Close() override;`
- L105 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L106 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) override;`
- L108 _public prototype_ `FString GetInfo() const;`
- L109 _public prototype_ `virtual IMediaCache& GetCache() override;`
- L110 _public prototype_ `virtual IMediaControls& GetControls() override;`
- L111 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L112 _public prototype_ `const FMediaIOCoreSamples& GetSamples() const;`
- L113 _public prototype_ `virtual FString GetStats() const override;`
- L114 _public prototype_ `virtual IMediaTracks& GetTracks() override;`
- L115 _public prototype_ `virtual FString GetUrl() const override;`
- L116 _public prototype_ `virtual IMediaView& GetView() override;`
- L117 _public prototype_ `virtual void TickTimeManagement();`
- L118 _public prototype_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode) override;`
- L121 _public prototype_ `virtual void RecordSourceOpenedEvent() const override;`
- L122 _public function_ `virtual bool ShouldAutoRecordSourceOpenedEvent() const override`
- L128 _public prototype_ `virtual bool QueryCacheState(EMediaCacheState State, TRangeSet<FTimespan>& OutTimeRanges) const override;`
- L129 _public prototype_ `virtual int32 GetSampleCount(EMediaCacheState State) const override;`
- L135 _protected prototype_ `virtual bool CanControl(EMediaControl Control) const override;`
- L136 _protected prototype_ `virtual FTimespan GetDuration() const override;`
- L137 _protected prototype_ `virtual float GetRate() const override;`
- L138 _protected prototype_ `virtual EMediaState GetState() const override;`
- L139 _protected prototype_ `virtual EMediaStatus GetStatus() const override;`
- L140 _protected prototype_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const override;`
- L141 _protected prototype_ `virtual FTimespan GetTime() const override;`
- L142 _protected prototype_ `virtual bool IsLooping() const override;`
- L143 _protected prototype_ `virtual bool Seek(const FTimespan& Time) override;`
- L144 _protected prototype_ `virtual bool SetLooping(bool Looping) override;`
- L145 _protected prototype_ `virtual bool SetRate(float Rate) override;`
- L151 _protected prototype_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const override;`
- L152 _protected prototype_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const override;`
- L153 _protected prototype_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L154 _protected prototype_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override;`
- L155 _protected prototype_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L156 _protected prototype_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L157 _protected prototype_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L158 _protected prototype_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L159 _protected prototype_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L160 _protected prototype_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override;`
- L161 _protected prototype_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) override;`
- L165 _public prototype_ `virtual FText GetDisplayName() const override;`
- L166 _public prototype_ `virtual TArray<ITimedDataInputChannel*> GetChannels() const override;`
- L167 _public prototype_ `virtual ETimedDataInputEvaluationType GetEvaluationType() const override;`
- L168 _public prototype_ `virtual void SetEvaluationType(ETimedDataInputEvaluationType Evaluation) override;`
- L169 _public prototype_ `virtual double GetEvaluationOffsetInSeconds() const override;`
- L170 _public prototype_ `virtual void SetEvaluationOffsetInSeconds(double Offset) override;`
- L171 _public prototype_ `virtual FFrameRate GetFrameRate() const override;`
- L172 _public prototype_ `virtual bool IsDataBufferSizeControlledByInput() const override;`
- L173 _public prototype_ `virtual void AddChannel(ITimedDataInputChannel* Channel) override;`
- L174 _public prototype_ `virtual void RemoveChannel(ITimedDataInputChannel * Channel) override;`
- L175 _public prototype_ `virtual bool SupportsSubFrames() const override;`
- L176 _public prototype_ `virtual UObject* GetSettingsObject() const override;`
- L193 _public prototype_ `virtual bool JustInTimeSampleRender_RenderThread(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDestinationTexture, TSharedPtr<FMediaIOCoreTextureSampleBase>& JITRProxySample);` — Just in time sample rendering. This method is responsible for late sample picking, then rendering it into the proxy sample provided.
- L198 _protected prototype_ `void AddAudioSample(const TSharedRef<FMediaIOCoreAudioSampleBase>& Sample);` — Internal API to push an audio sample to the internal samples pool
- L201 _protected prototype_ `void AddCaptionSample(const TSharedRef<FMediaIOCoreCaptionSampleBase>& Sample);` — Internal API to push a caption sample to the internal samples pool
- L204 _protected prototype_ `void AddMetadataSample(const TSharedRef<FMediaIOCoreBinarySampleBase>& Sample);` — Internal API to push a metadata sample to the internal samples pool
- L207 _protected prototype_ `void AddSubtitleSample(const TSharedRef<FMediaIOCoreSubtitleSampleBase>& Sample);` — Internal API to push a subtitle sample to the internal samples pool
- L210 _protected prototype_ `void AddVideoSample(const TSharedRef<FMediaIOCoreTextureSampleBase>& Sample);` — Internal API to push a video sample to the internal samples pool
- L214 _protected prototype_ `virtual bool IsHardwareReady() const = 0;` — Is the IO hardware/device ready to be used.
- L217 _protected prototype_ `virtual bool ReadMediaOptions(const IMediaOptions* Options);` — Return true if the options combination are valid.
- L223 _protected prototype_ `void NotifyVideoFormatDetected();` — Allows children to notify when video format is known after auto-detection. The main purpose is to start intialization of the DMA textures at the right moment.
- L226 _protected prototype_ `static double GetApplicationSeconds();` — Get the application time with a delta to represent the actual system time. Use instead of FApp::GetCurrentTime.
- L229 _protected prototype_ `static double GetPlatformSeconds();` — Get the platform time with a delta to represent the actual system time. Use instead of FApp::Seconds.
- L232 _protected prototype_ `static bool IsTimecodeLogEnabled();` — Log the timecode when a frame is received.
- L238 _protected prototype_ `virtual void SetupSampleChannels() = 0;` — Setup settings for the different kind of supported data channels. PlayerBase will setup the common settings
- L243 _protected function_ `virtual uint32 GetNumVideoFrameBuffers() const` — Get the number of video frames to buffer.
- L248 _protected function_ `virtual EMediaIOCoreColorFormat GetColorFormat() const`
- L254 _protected prototype_ `virtual void AddVideoSampleAfterGPUTransfer_RenderThread(const TSharedRef<FMediaIOCoreTextureSampleBase>& Sample);` — Called after fast GPUDirect texture transferring is finished
- L257 _protected prototype_ `virtual bool CanUseGPUTextureTransfer() const;` — Whether fast GPU transferring is available
- L260 _protected prototype_ `bool HasTextureAvailableForGPUTransfer() const;` — Whether a texture availabled for GPU transfer
- L263 _protected prototype_ `virtual bool IsJustInTimeRenderingEnabled() const;` — Whether JITR is available and active
- L266 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> AcquireTextureSample_AnyThread() const = 0;` — Factory method to generate texture samples.
- L269 _protected prototype_ `TArray<TSharedRef<FMediaIOCoreTextureSampleBase>> Deinterlace(const UE::MediaIOCore::FVideoFrame& InVideoFrame) const;` — Deinterlace a video frame. Only valid to call when the video stream is open.
- L274 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> AcquireJITRProxySampleInitialized();` — Acquire a proxy sample for JITR. That sample must be initialized for JITR.
- L277 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleConverter> CreateTextureSampleConverter() const;` — Factory method to create sample converters.
- L280 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> PickSampleToRender_RenderThread(const FFrameInfo& InFrameInformation);` — Pick a sample to render
- L281 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> PickSampleToRenderForLatest_RenderThread(const FFrameInfo& InFrameInformation);`
- L282 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> PickSampleToRenderForTimeSynchronized_RenderThread(const FFrameInfo& InFrameInformation);`
- L283 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> PickSampleToRenderFramelocked_RenderThread(const FFrameInfo& InFrameInformation);`
- L289 _protected prototype_ `void TransferTexture_RenderThread(FRHICommandListImmediate& RHICmdList, const TSharedPtr<FMediaIOCoreTextureSampleBase>& Sample, const TSharedPtr<FMediaIOCoreTextureSampleBase>& JITRProxySample);` — A wrapper method responsible for transferring of the sample textures into GPU memory based on the current settings and hardware capabilities.
- L293 _protected prototype_ `virtual FString GetAnalyticsEventPrefix() const;` — Gets the prefix to append to named analytics events recorded by the media player
- L296 _protected prototype_ `virtual void GetAnalyticsEventAttributes(const FString& EventName, TArray<FAnalyticsEventAttribute>& InOutAttributes) const;` — Allows media players to add additional analytics event attributes to an analytics event being recorded
- L301 _protected member_ `FString OpenUrl;` — Url used to open the media player.
- L304 _protected member_ `FMediaVideoTrackFormat VideoTrackFormat;` — format of the video.
- L307 _protected member_ `FMediaAudioTrackFormat AudioTrackFormat;` — format of the audio.
- L310 _protected member_ `EMediaState CurrentState = EMediaState::Closed;` — Current state of the media player.
- L313 _protected member_ `FTimespan CurrentTime = FTimespan::Zero();` — Current playback time.
- L316 _protected member_ `IMediaEventSink& EventSink;` — The media event handler.
- L319 _protected member_ `FFrameRate VideoFrameRate = { 30, 1 };` — Video frame rate in the last received sample.
- L322 _protected member_ `const TUniquePtr<FMediaIOCoreSamples> Samples;` — The media sample cache.
- L325 _protected member_ `EMediaIOSampleEvaluationType EvaluationType = EMediaIOSampleEvaluationType::PlatformTime;` — Sample evaluation type.
- L328 _protected member_ `bool bWarnedIncompatibleFrameRate = false;` — Warn when the video frame rate is not the same as the engine's frame rate.
- L331 _protected member_ `bool bAutoDetect = false;` — Whether we are using autodetection.
- L334 _protected member_ `int32 FrameDelay = 0;` — When using Time Synchronization (TC synchronization), how many frame back of a delay would you like.
- L337 _protected member_ `double TimeDelay = 0.0;` — When not using Time Synchronization (use computer time), how many sec back of a delay would you like.
- L340 _protected member_ `FTimespan PreviousFrameTimespan;` — Previous frame Timespan
- L343 _protected member_ `TArray<ITimedDataInputChannel*> Channels;` — Timed Data Input handler
- L346 _protected member_ `FMediaIOSamplingSettings BaseSettings;` — Base set of settings to start from when setuping channels
- L349 _protected member_ `TSharedPtr<struct FOpenColorIOColorConversionSettings> OCIOSettings;` — Open color IO conversion data.
- L352 _protected member_ `TWeakObjectPtr<UObject> MediaSourceObject;` — The media source that opened this player, for settings persistence.
- L355 _protected member_ `bool bFramelock = false;` — Whether media playback should be framelocked to the engine's timecode
- L358 _protected member_ `uint64 LastEngineRTFrameThatUpdatedJustInTime = TNumericLimits<uint64>::Max();` — Used to ensure that JIT rendering is executed only once per frame
- L361 _protected member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> SourceColorSettings;` — Container for media source color settings.
- L365 _protected member_ `bool bOverrideSourceEncoding = true;` — `UE_DEPRECATED(5.8, "This property is deprecated. Please use SourceColorSettings instead.")`
- L368 _protected member_ `ETextureSourceEncoding OverrideSourceEncoding = ETextureSourceEncoding::TSE_Linear;` — `UE_DEPRECATED(5.8, "This property is deprecated. Please use SourceColorSettings instead.")`
- L371 _protected member_ `bool bOverrideSourceColorSpace = true;` — `UE_DEPRECATED(5.8, "This property is deprecated. Please use SourceColorSettings instead.")`
- L374 _protected member_ `ETextureColorSpace OverrideSourceColorSpace = ETextureColorSpace::TCS_None;` — `UE_DEPRECATED(5.8, "This property is deprecated. Please use SourceColorSettings instead.")`
- L378 _private prototype_ `void OnSampleDestroyed(TRefCountPtr<FRHITexture> InTexture);`
- L379 _private prototype_ `void RegisterSampleBuffer(const TSharedPtr<FMediaIOCoreTextureSampleBase>& InSample);`
- L380 _private prototype_ `void UnregisterSampleBuffers();`
- L381 _private prototype_ `void CreateAndRegisterTextures();`
- L382 _private prototype_ `void UnregisterTextures();`
- L383 _private prototype_ `void PreGPUTransfer(const TSharedPtr<FMediaIOCoreTextureSampleBase>& InSample);`
- L384 _private prototype_ `void PreGPUTransferJITR(const TSharedPtr<FMediaIOCoreTextureSampleBase>& InSample, const TSharedPtr<FMediaIOCoreTextureSampleBase>& InJITRProxySample);`
- L385 _private prototype_ `void ExecuteGPUTransfer(const TSharedPtr<FMediaIOCoreTextureSampleBase>& InSample);`
- L388 _private prototype_ `FMediaIOCoreSamples& GetSamples_Internal();` — Get the right samples buffer for pushing samples depending on if we're in JITR mode or not.
- L391 _private member_ `UE::GPUTextureTransfer::TextureTransferPtr GPUTextureTransfer;` — GPU Texture transfer object
- L394 _private member_ `TSet<void*> RegisteredBuffers;` — Buffers Registered with GPU Texture Transfer
- L397 _private member_ `TSet<TRefCountPtr<FRHITexture>> RegisteredTextures;` — Textures registerd with GPU Texture transfer.
- L400 _private member_ `TArray<TRefCountPtr<FRHITexture>> Textures;` — Pool of textures available for GPU Texture transfer.
- L403 _private member_ `mutable FCriticalSection TexturesCriticalSection;` — Critical section to control access to the pool.
- L406 _private member_ `TSharedPtr<UE::MediaIOCore::FDeinterlacer> Deinterlacer;` — Utility object to handle deinterlacing.
- L411 _private prototype_ `void LogBookmark(const FString& Text, const TSharedRef<IMediaTextureSample>& Sample);` — Utility function to log various sample events (i.e. received/transferred/picked)
- L436 _private member_ `bool bJustInTimeRender = false;` — Is Just-In-Time Rendering enabled
- L439 _private member_ `const TUniquePtr<FJITRMediaTextureSamples> JITRSamples;` — JITR samples proxy

#### class `FMediaIOCorePlayerBase::FFrameInfo`  
`class FFrameInfo`  
_L180-187_
- desc: Class used to pass information about current frame for sample picking.
- L183 _public member_ `FTimecode RequestedTimecode = FTimecode();`
- L184 _public member_ `FTimespan SampleTimespan = FTimespan();`
- L185 _public member_ `double EvaluationOffset = 0.;`
- L186 _public member_ `uint32 FrameNumber = 0.;`

#### class `FMediaIOCorePlayerBase::FJITRMediaTextureSamples`  
`class FJITRMediaTextureSamples : public FMediaIOCoreSamples`  
_L416-433_
- inherits: `FMediaIOCoreSamples`
- desc: Special JITR sample container, overrides FetchVideo to return a ProxySample that will be populated by JustInTimeSampleRender_RenderThread.
- L420 _public prototype_ `FJITRMediaTextureSamples() = default;`
- L421 _public prototype_ `FJITRMediaTextureSamples(const FJITRMediaTextureSamples&) = delete;`
- L422 _public prototype_ `FJITRMediaTextureSamples& operator=(const FJITRMediaTextureSamples&) = delete;`
- L425 _public prototype_ `virtual bool FetchVideo(TRange<FTimespan> TimeRange, TSharedPtr<IMediaTextureSample>& OutSample) override;`
- L426 _public prototype_ `virtual bool PeekVideoSampleTime(FMediaTimeStamp& TimeStamp) override;`
- L427 _public prototype_ `virtual void FlushSamples() override;`
- L432 _public member_ `TSharedPtr<FMediaIOCoreTextureSampleBase> ProxySample;` — JITR sample

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API MEDIAIOCORE_API`
- L57 _namespace_ `namespace UE`
- L57 _namespace_ `namespace GPUTextureTransfer` (scope `UE`)
- L59 _typedef_ `using TextureTransferPtr = TSharedPtr<class ITextureTransfer>;` (scope `UE::GPUTextureTransfer`)
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace MediaIOCore` (scope `UE`)

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreSampleContainer.h` (Public)


#### struct `FMediaIOSamplingSettings`  
`struct FMediaIOSamplingSettings`  
_L17-28_
- L19 _public function_ `FMediaIOSamplingSettings() : FrameRate(24, 1)`
- L23 _public member_ `FFrameRate FrameRate;`
- L24 _public member_ `ETimedDataInputEvaluationType EvaluationType = ETimedDataInputEvaluationType::PlatformTime;`
- L25 _public member_ `int32 BufferSize = 8;`
- L26 _public member_ `double PlayerTimeOffset = 0.0;`
- L27 _public member_ `int32 AbsoluteMaxBufferSize = 32;`

#### class `FMediaIOCoreSampleContainer`  
`template<typename SampleType> class FMediaIOCoreSampleContainer : public ITimedDataInputChannel`  
_L34-417_
- inherits: `ITimedDataInputChannel`
- desc: MediaIO container for different types of samples. Also a TimedData channel that can be monitored
- L37 _public function_ `FMediaIOCoreSampleContainer(FName InChannelName) : ChannelName(InChannelName) , BufferUnderflow(0) , BufferOverflow(0) , FrameDrop(0) , bIsStatEnabled(true) , bIsChannelEnabled(false)`
- L47 _public prototype_ `FMediaIOCoreSampleContainer(const FMediaIOCoreSampleContainer&) = delete;`
- L48 _public prototype_ `FMediaIOCoreSampleContainer& operator=(const FMediaIOCoreSampleContainer&) = delete;`
- L49 _public prototype_ `virtual ~FMediaIOCoreSampleContainer() = default;`
- L53 _public function_ `void UpdateSettings(const FMediaIOSamplingSettings& InSettings)` — Update this sample container settings
- L60 _public function_ `void CacheState(FTimespan PlayerTime)` — Caches the current sample container states before samples will be taken out of it
- L135 _public function_ `void EnableChannel(ITimedDataInput* Input, bool bShouldEnable)` — Channel is disabled by default. It won't be added to the Timed Data collection if not enabled
- L164 _public function_ `bool AddSample(const TSharedRef<SampleType, ESPMode::ThreadSafe>& Sample)` — Add the given sample to the cache. @param Sample The sample to add. @return True if the operation succeeds.
- L186 _public function_ `bool PopSample()` — Pop a sample from the cache. @return True if the operation succeeds. @see AddSample, NumSamples
- L204 _public function_ `int32 NumSamples() const` — Get the number of queued samples. @return Number of samples. @see AddSample, PopSample
- L216 _public function_ `FTimespan GetNextSampleTime()` — Get next sample time from the sample list. @return Time of the next sample from the VideoSampleQueue @see AddSample, NumSamples
- L236 _public function_ `virtual FText GetDisplayName() const override`
- L241 _public function_ `virtual ETimedDataInputState GetState() const override`
- L246 _public function_ `virtual FTimedDataChannelSampleTime GetOldestDataTime() const override`
- L256 _public function_ `virtual FTimedDataChannelSampleTime GetNewestDataTime() const override`
- L273 _public function_ `virtual TArray<FTimedDataChannelSampleTime> GetDataTimes() const override`
- L278 _public function_ `virtual int32 GetNumberOfSamples() const override`
- L283 _public function_ `virtual int32 GetDataBufferSize() const override`
- L288 _public function_ `virtual void SetDataBufferSize(int32 BufferSize) override`
- L299 _public function_ `virtual bool IsBufferStatsEnabled() const override`
- L304 _public function_ `virtual void SetBufferStatsEnabled(bool bEnable) override`
- L315 _public function_ `virtual int32 GetBufferUnderflowStat() const override`
- L320 _public function_ `virtual int32 GetBufferOverflowStat() const override`
- L325 _public function_ `virtual int32 GetFrameDroppedStat() const override`
- L331 _public function_ `virtual void GetLastEvaluationData(FTimedDataInputEvaluationData& OutEvaluationData) const override`
- L336 _public function_ `virtual void ResetBufferStats() override`
- L347 _public function_ `bool FetchSample(TRange<FTimespan> TimeRange, TSharedPtr<SampleType, ESPMode::ThreadSafe>& OutSample)`
- L372 _public function_ `TArray<TSharedPtr<SampleType, ESPMode::ThreadSafe>> GetSamples() const` — Returns all available samples
- L378 _public function_ `void FlushSamples()`
- L388 _protected member_ `FName ChannelName;` — Name of this channel
- L391 _protected member_ `TArray<FTimedDataChannelSampleTime> CachedSamplesData;` — Samples are consumed by the the facade layer when evaluating and sending to render thread. Cache sample data before fetching happens
- L394 _protected member_ `FTimedDataInputEvaluationData CachedEvaluationData;` — Last evaluation data for that channel
- L397 _protected member_ `TAtomic<int32> BufferUnderflow;` — Evaluation statistics we keep track of
- L398 _protected member_ `TAtomic<int32> BufferOverflow;`
- L399 _protected member_ `TAtomic<int32> FrameDrop;`
- L402 _protected member_ `FMediaIOSamplingSettings EvaluationSettings;` — Channel settings
- L405 _protected member_ `bool bIsStatEnabled;` — Stats logging enabled or not
- L408 _protected member_ `bool bIsChannelEnabled;` — Should this channel be considered available
- L415 _protected member_ `mutable FCriticalSection CriticalSection;` — Sample container: We add at the beginning of the array [0] and we pop at the end [Size-1]. [0] == Newest sample [Size - 1] == Oldest sample
- L416 _protected member_ `TArray<TSharedPtr<SampleType, ESPMode::ThreadSafe>> Samples;`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreSamples.h` (Public)


#### enum `EMediaIOSampleType`  
`enum class EMediaIOSampleType`  
_L22-30_
- desc: Bitflags about different types of sample a MediaIO can push
- L24 _public enumerator_ `None = 0`
- L25 _public enumerator_ `Video = 1<<0`
- L26 _public enumerator_ `Audio = 1<<1`
- L27 _public enumerator_ `Metadata = 1<<2`
- L28 _public enumerator_ `Subtitles = 1<<3`
- L29 _public enumerator_ `Caption = 1<<4`

#### class `FMediaIOCoreSamples`  
`class FMediaIOCoreSamples : public IMediaSamples`  
_L37-320_
- inherits: `IMediaSamples`
- L40 _public prototype_ `FMediaIOCoreSamples();`
- L41 _public prototype_ `FMediaIOCoreSamples(const FMediaIOCoreSamples&) = delete;`
- L42 _public prototype_ `FMediaIOCoreSamples& operator=(const FMediaIOCoreSamples&) = delete;`
- L53 _public function_ `bool AddAudio(const TSharedRef<IMediaAudioSample, ESPMode::ThreadSafe>& Sample)` — Add the given audio sample to the cache. @param Sample The sample to add. @return True if the operation succeeds. @see AddCaption, AddMetadata, AddSubtitle, AddVideo, PopAudio, NumAudioSamples
- L65 _public function_ `bool AddCaption(const TSharedRef<IMediaOverlaySample, ESPMode::ThreadSafe>& Sample)` — Add the given caption sample to the cache. @param Sample The sample to add. @return True if the operation succeeds. @see AddAudio, AddMetadata, AddSubtitle, AddVideo, PopCaption, NumCaptionSamples
- L77 _public function_ `bool AddMetadata(const TSharedRef<IMediaBinarySample, ESPMode::ThreadSafe>& Sample)` — Add the given metadata sample to the cache. @param Sample The sample to add. @return True if the operation succeeds. @see AddAudio, AddCaption, AddSubtitle, AddVideo, PopMetadata, NumMetadataSamples
- L89 _public function_ `bool AddSubtitle(const TSharedRef<IMediaOverlaySample, ESPMode::ThreadSafe>& Sample)` — Add the given subtitle sample to the cache. @param Sample The sample to add. @return True if the operation succeeds. @see AddAudio, AddCaption, AddMetadata, AddVideo, PopSubtitle, NumSubtitleSamples
- L101 _public function_ `bool AddVideo(const TSharedRef<IMediaTextureSample, ESPMode::ThreadSafe>& Sample)` — Add the given video sample to the cache. @param Sample The sample to add. @return True if the operation succeeds. @see AddAudio, AddCaption, AddMetadata, AddSubtitle, PopVideo, NumVideoSamples
- L112 _public function_ `bool PopAudio()` — Pop a Audio sample from the cache. @return True if the operation succeeds. @see AddAudio, NumAudioSamples
- L123 _public function_ `bool PopCaption()` — Pop a Caption sample from the cache. @return True if the operation succeeds. @see AddCaption, NumCaption
- L134 _public function_ `bool PopMetadata()` — Pop a Metadata sample from the cache. @return True if the operation succeeds. @see AddMetadata, NumMetadata
- L145 _public function_ `bool PopSubtitle()` — Pop a Subtitle sample from the cache. @return True if the operation succeeds. @see AddSubtitle, NumSubtitle
- L156 _public function_ `bool PopVideo()` — Pop a video sample from the cache. @return True if the operation succeeds. @see AddVideo, NumVideo
- L167 _public function_ `int32 NumAudioSamples() const` — Get the number of queued audio samples. @return Number of samples. @see AddAudio, PopAudio
- L178 _public function_ `int32 NumCaptionSamples() const` — Get the number of queued caption samples. @return Number of samples. @see AddCaption, PopCaption
- L189 _public function_ `int32 NumMetadataSamples() const` — Get the number of queued metadata samples. @return Number of samples. @see AddMetadata, PopMetada
- L200 _public function_ `int32 NumSubtitleSamples() const` — Get the number of queued subtitle samples. @return Number of samples. @see AddSubtitle, PopSubtitle
- L211 _public function_ `int32 NumVideoSamples() const` — Get the number of queued video samples. @return Number of samples. @see AddVideo, PopVideo
- L222 _public function_ `FTimespan GetNextVideoSampleTime()` — Get next sample time from the VideoSampleQueue. @return Time of the next sample from the VideoSampleQueue @see AddVideo, NumVideoSamples
- L232 _public function_ `int32 GetAudioFrameDropCount() const` — Get Audio Samples frame dropped count. @return Number of frames dropped
- L242 _public function_ `int32 GetVideoFrameDropCount() const` — Get Video Samples frame dropped count. @return Number of frames dropped
- L252 _public function_ `int32 GetMetadataFrameDropCount() const` — Get Metadata Samples frame dropped count. @return Number of frames dropped
- L262 _public function_ `int32 GetSubtitlesFrameDropCount() const` — Get Subtitles Samples frame dropped count. @return Number of frames dropped
- L272 _public function_ `int32 GetCaptionsFrameDropCount() const` — Get Caption Samples frame dropped count. @return Number of frames dropped
- L280 _public function_ `TArray<TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>> GetVideoSamples() const` — Returns all available video samples
- L288 _public prototype_ `void CacheSamplesState(FTimespan PlayerTime);` — Caches the current sample container state for a given Player (evaluation) time
- L291 _public prototype_ `void EnableTimedDataChannels(ITimedDataInput* Input, EMediaIOSampleType SampleTypes);` — Enable or disable channels based on bitfield flag
- L294 _public prototype_ `void InitializeVideoBuffer(const FMediaIOSamplingSettings& InSettings);` — Initialize our different buffers with player's settings and wheter or not it should be displayed / supported in Timing monitor
- L295 _public prototype_ `void InitializeAudioBuffer(const FMediaIOSamplingSettings& InSettings);`
- L296 _public prototype_ `void InitializeMetadataBuffer(const FMediaIOSamplingSettings& InSettings);`
- L297 _public prototype_ `void InitializeSubtitlesBuffer(const FMediaIOSamplingSettings& InSettings);`
- L298 _public prototype_ `void InitializeCaptionBuffer(const FMediaIOSamplingSettings& InSettings);`
- L304 _public prototype_ `virtual bool FetchAudio(TRange<FTimespan> TimeRange, TSharedPtr<IMediaAudioSample, ESPMode::ThreadSafe>& OutSample) override;`
- L305 _public prototype_ `virtual bool FetchCaption(TRange<FTimespan> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample) override;`
- L306 _public prototype_ `virtual bool FetchMetadata(TRange<FTimespan> TimeRange, TSharedPtr<IMediaBinarySample, ESPMode::ThreadSafe>& OutSample) override;`
- L307 _public prototype_ `virtual bool FetchSubtitle(TRange<FTimespan> TimeRange, TSharedPtr<IMediaOverlaySample, ESPMode::ThreadSafe>& OutSample) override;`
- L308 _public prototype_ `virtual bool FetchVideo(TRange<FTimespan> TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample) override;`
- L309 _public prototype_ `virtual void FlushSamples() override;`
- L310 _public prototype_ `virtual bool PeekVideoSampleTime(FMediaTimeStamp & TimeStamp) override;`
- L311 _public prototype_ `virtual void SetSampleBufferSize(int32 BufferSize) override;`
- L315 _protected member_ `FMediaIOCoreSampleContainer<IMediaTextureSample> VideoSamples;`
- L316 _protected member_ `FMediaIOCoreSampleContainer<IMediaAudioSample> AudioSamples;`
- L317 _protected member_ `FMediaIOCoreSampleContainer<IMediaBinarySample> MetadataSamples;`
- L318 _protected member_ `FMediaIOCoreSampleContainer<IMediaOverlaySample> SubtitleSamples;`
- L319 _protected member_ `FMediaIOCoreSampleContainer<IMediaOverlaySample> CaptionSamples;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MEDIAIOCORE_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreSubsystem.h` (Public)


#### class `UMediaIOCoreSubsystem`  
`class UMediaIOCoreSubsystem : public UEngineSubsystem`  
_L16-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- L34 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& InCollection) override;`
- L35 _public prototype_ `virtual void Deinitialize() override;`
- L41 _public prototype_ `TSharedPtr<FMediaIOAudioOutput> CreateAudioOutput(const FCreateAudioOutputArgs& InArgs);` — Create an audio output that allows getting audio that was accumulated during the last frame.
- L46 _public prototype_ `int32 GetNumAudioInputChannels() const;` — Get the number of audio channels used by the main audio device.
- L51 _public function_ `FOnBufferReceived& OnBufferReceived_AudioThread()` — @Note: Called from the audio thread.
- L57 _private prototype_ `void OnAudioDeviceDestroyed(Audio::FDeviceId InAudioDeviceId);`
- L58 _private prototype_ `void OnBufferReceivedByCapture(float* Data, int32 NumSamples, Audio::FDeviceId AudioDeviceID) const;`
- L61 _private member_ `TSharedPtr<FMainMediaIOAudioCapture> MainMediaIOAudioCapture;`
- L63 _private member_ `TMap<Audio::FDeviceId, TSharedPtr<FMediaIOAudioCapture, ESPMode::ThreadSafe>> MediaIOAudioCaptures;`
- L65 _private member_ `FDelegateHandle DeviceDestroyedHandle;`
- L68 _private member_ `FOnBufferReceived BufferReceivedDelegate;` — Delegate called from the audio thread when a buffer is received. Must be thread safe.

#### struct `UMediaIOCoreSubsystem::FCreateAudioOutputArgs`  
`struct FCreateAudioOutputArgs`  
_L21-28_
- L23 _public member_ `uint32 NumOutputChannels = 0;`
- L24 _public member_ `FFrameRate TargetFrameRate;`
- L25 _public member_ `uint32 MaxSampleLatency = 0;`
- L26 _public member_ `uint32 OutputSampleRate = 0;`
- L27 _public member_ `FAudioDeviceHandle AudioDeviceHandle;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MEDIAIOCORE_API`
- L19 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnBufferReceived, Audio::FDeviceId , float* , int32 ) struct FCreateAudioOutputArgs { uint32 NumOutputChannels = 0; FFrameRate TargetFrameRate; uint32 MaxSampleLatency = 0; uint32 OutputSampleRate = 0; FAudioDeviceHandle AudioDeviceHandle; };`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreSubtitleSampleBase.h` (Public)


#### class `FMediaIOCoreSubtitleSampleBase`  
`class FMediaIOCoreSubtitleSampleBase : public IMediaOverlaySample , public IMediaPoolable`  
_L12-16_
- inherits: `IMediaOverlaySample,IMediaPoolable`
- desc: Implements a media subtitle sample.

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreTextureSampleBase.h` (Public)


#### struct `UE::MediaIOCore::FColorFormatArgs`  
`struct UE_DEPRECATED(5.8, "FColorFormatArgs is deprecated. Please use FNativeMediaSourceColorSettings instead.") FColorFormatArgs`  
_L21-52_
- L23 _public prototype_ `FColorFormatArgs() = default;`
- L26 _public function_ `FColorFormatArgs(bool bIsSRGBInput)` — Bool constructor to allow backwards compatibility with previous method definitions of FMediaIOCoreTextureSampleBase::Initialize.
- L40 _public function_ `FColorFormatArgs(UE::Color::EEncoding InEncoding, UE::Color::EColorSpace InColorSpaceType) : Encoding(InEncoding) , ColorSpaceType(InColorSpaceType)`
- L48 _public member_ `UE::Color::EEncoding Encoding = UE::Color::EEncoding::Linear;` — Encoding of the texture.
- L51 _public member_ `UE::Color::EColorSpace ColorSpaceType = UE::Color::EColorSpace::sRGB;` — Color space of the texture.

#### struct `FMediaIOCoreSampleJITRConfigurationArgs`  
`struct FMediaIOCoreSampleJITRConfigurationArgs`  
_L58-83_
- desc: Used to setup JITR data for a sample
- L61 _public member_ `uint32 Width = 0;` — Width of the sample in pixels
- L64 _public member_ `uint32 Height = 0;` — Height of the sample in pixels
- L67 _public member_ `FTimespan Time;` — Platform time fixed on the game thread for JITR sample picking
- L70 _public member_ `FTimecode Timecode;` — Engine timecode fixed on the game thread for JITR sample picking
- L73 _public member_ `double EvaluationOffsetInSeconds = 0;` — Time offset evaluated on game thread
- L76 _public member_ `TSharedPtr<FMediaIOCorePlayerBase> Player;` — Player that produced the sample
- L79 _public member_ `TSharedPtr<FMediaIOCoreTextureSampleConverter> Converter;` — Sample converter to process this sample
- L82 _public member_ `FFrameRate FrameRate;` — Frame rate of the current sample.

#### class `FMediaIOCoreTextureSampleBase`  
`class FMediaIOCoreTextureSampleBase : public IMediaTextureSample , public IMediaPoolable , public IMediaTextureSampleColorConverter , public TSharedFromThis<FMediaIOCoreTextureSampleBase, ESPMode::ThreadSafe>`  
_L89-502_
- inherits: `IMediaTextureSample,IMediaPoolable,IMediaTextureSampleColorConverter,TSharedFromThis<FMediaIOCoreTextureSampleBase,ESPMode::ThreadSafe>`
- desc: Implements the IMediaTextureSample/IMediaPoolable interface.
- L97 _public prototype_ `FMediaIOCoreTextureSampleBase();`
- L113 _public prototype_ `bool Initialize(const void* InVideoBuffer, uint32 InBufferSize, uint32 InStride, uint32 InWidth, uint32 InHeight, EMediaTextureSampleFormat InSampleFormat, FTimespan InTime, const FFrameRate& InFrameRate, const TOptional<FTimecode>& InTimecode, TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> InSourceColorSettings);` — Initialize the sample. @param InVideoBuffer The video frame data. @param InBufferSize The size of the video buffer. @param InStride The number of channel of the video buffer. @param InWidth The sample rate of the video buffer. @param InHeight The sample rate of the video buffer. @param InSampleFormat The sample format of the video buffer. @param InTime The sample time (in the player's own clock). @param InFrameRate The framerate of the media that produce the sample. @param InTimecode The sample timecode if available. @param InSourceColorSettings Information about the texture color encoding and color space.
- L128 _public prototype_ `bool Initialize(const TArray<uint8>& InVideoBuffer, uint32 InStride, uint32 InWidth, uint32 InHeight, EMediaTextureSampleFormat InSampleFormat, FTimespan InTime, const FFrameRate& InFrameRate, const TOptional<FTimecode>& InTimecode, TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> InSourceColorSettings);` — Initialize the sample. @param InVideoBuffer The video frame data. @param InStride The number of channel of the video buffer. @param InWidth The sample rate of the video buffer. @param InHeight The sample rate of the video buffer. @param InSampleFormat The sample format of the video buffer. @param InTime The sample time (in the player's own clock). @param InFrameRate The framerate of the media that produce the sample. @param InTimecode The sample timecode if available. @param InSourceColorSettings Information about the texture color encoding and color space.
- L143 _public prototype_ `bool Initialize(TArray<uint8>&& InVideoBuffer, uint32 InStride, uint32 InWidth, uint32 InHeight, EMediaTextureSampleFormat InSampleFormat, FTimespan InTime, const FFrameRate& InFrameRate, const TOptional<FTimecode>& InTimecode, TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> InSourceColorSettings);` — Initialize the sample. @param InVideoBuffer The video frame data. @param InStride The number of channel of the video buffer. @param InWidth The sample rate of the video buffer. @param InHeight The sample rate of the video buffer. @param InSampleFormat The sample format of the video buffer. @param InTime The sample time (in the player's own clock). @param InFrameRate The framerate of the media that produce the sample. @param InTimecode The sample timecode if available. @param InSourceColorSettings Information about the texture color encoding and color space.
- L151 _public prototype_ `bool SetBuffer(const void* InVideoBuffer, uint32 InBufferSize);` — Initialize the sample. @param InVideoBuffer The video frame data. @param InBufferSize The size of the video buffer.
- L158 _public prototype_ `bool SetBuffer(const TArray<uint8>& InVideoBuffer);` — Set the sample buffer. @param InVideoBuffer The video frame data.
- L165 _public prototype_ `bool SetBuffer(TArray<uint8>&& InVideoBuffer);` — Set the sample buffer. @param InVideoBuffer The video frame data.
- L179 _public prototype_ `bool SetProperties(uint32 InStride, uint32 InWidth, uint32 InHeight, EMediaTextureSampleFormat InSampleFormat, FTimespan InTime, const FFrameRate& InFrameRate, const TOptional<FTimecode>& InTimecode, TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> InSourceColorSettings);` — Set the sample properties. @param InStride The number of channel of the video buffer. @param InWidth The width the video buffer. @param InHeight The height of the video buffer. @param InSampleFormat The sample format of the video buffer. @param InTime The sample time (in the player's own clock). @param InFrameRate The framerate of the media that produce the sample. @param InTimecode The sample timecode if available. @param InSourceColorSettings Information about the texture color encoding and color space.
- L194 _public prototype_ `bool InitializeWithEvenOddLine(bool bUseEvenLine, const void* InVideoBuffer, uint32 InBufferSize, uint32 InStride, uint32 InWidth, uint32 InHeight, EMediaTextureSampleFormat InSampleFormat, FTimespan InTime, const FFrameRate& InFrameRate, const TOptional<FTimecode>& InTimecode, TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> InSourceColorSettings);` — Initialize the sample with half it's original height and take only the odd or even line. @param bUseEvenLine Should use the Even or the Odd line from the video buffer. @param InVideoBuffer The video frame data. @param InStride The number of channel of the video buffer. @param InWidth The width of the video buffer. @param InHeight The height of the video buffer. @param InSampleFormat The sample format of the video buffer. @param InTime The sample time (in the player's own clock). @param InTimecode The sample timecode if available. @param InSourceColorSettings Information about the texture color encoding and color space.
- L205 _public prototype_ `bool SetBufferWithEvenOddLine(bool bUseEvenLine, const void* InVideoBuffer, uint32 InBufferSize, uint32 InStride, uint32 InHeight);` — Set the sample buffer with half it's original height and take only the odd or even line. @param bUseEvenLine Should use the Even or the Odd line from the video buffer. @param InVideoBuffer The video frame data. @param InBufferSize The size of the video buffer. @param InStride The number of channel of the video buffer. @param InHeight The height of the video buffer.
- L210 _public prototype_ `void SetColorConversionSettings(TSharedPtr<struct FOpenColorIOColorConversionSettings> InColorConversionSettings);` — Set the OCIO settings used for color conversion.
- L219 _public prototype_ `virtual void* RequestBuffer(uint32 InBufferSize);` — Request an uninitialized sample buffer. Should be used when the buffer could be filled by something else. SetProperties should still be called after. @param InBufferSize The size of the video buffer.
- L227 _public prototype_ `virtual bool InitializeJITR(const FMediaIOCoreSampleJITRConfigurationArgs& Args);` — Configure this sample for JITR @param Args JITR configuration parameters.
- L230 _public function_ `void SetAwaitingForGPUTransfer(bool bIsAwaitingGPUTransfer = true)` — Marks this sample as one that is ready and awaiting for fast GPUDirect texture transfer
- L236 _public function_ `bool IsAwaitingForGPUTransfer() const` — Returns whether it's ready for GPUDirect texture transfer
- L242 _public prototype_ `TSharedPtr<FMediaIOCorePlayerBase> GetPlayer() const;` — Returns the player that created this sample
- L245 _public function_ `double GetEvaluationOffsetInSeconds() const` — Returns time evaluated on the game thread for JITR
- L251 _public prototype_ `virtual void CopyConfiguration(const TSharedPtr<FMediaIOCoreTextureSampleBase>& SourceSample);` — Copies all neccessary data from a source sample to render JIT
- L262 _public prototype_ `bool SetProperties(uint32 InStride, uint32 InWidth, uint32 InHeight, EMediaTextureSampleFormat InSampleFormat, FTimespan InTime, const FFrameRate& InFrameRate, const TOptional<FTimecode>& InTimecode, const UE::MediaIOCore::FColorFormatArgs& InColorFormatArgs);` — `UE_DEPRECATED(5.8, "Deprecated method. Please use method with FNativeMediaSourceColorSettings argument instead.")`
- L271 _protected prototype_ `void CacheColorCoversionSettings_GameThread();` — Method that caches color conversion settings on Game thread.
- L276 _public function_ `virtual FIntPoint GetDim() const override`
- L296 _public function_ `virtual FTimespan GetDuration() const override`
- L301 _public function_ `virtual EMediaTextureSampleFormat GetFormat() const override`
- L306 _public function_ `virtual FIntPoint GetOutputDim() const override`
- L311 _public function_ `virtual uint32 GetStride() const override`
- L316 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L321 _public function_ `virtual TOptional<FTimecode> GetTimecode() const override`
- L326 _public function_ `virtual bool IsCacheable() const override`
- L331 _public prototype_ `virtual bool IsOutputSrgb() const override;`
- L333 _public prototype_ `virtual bool HasEncodingOverride() const;`
- L334 _public prototype_ `virtual bool HasColorSpaceOverride() const;`
- L335 _public prototype_ `virtual const UE::Color::FColorSpace& GetSourceColorSpace() const override;`
- L336 _public prototype_ `virtual UE::Color::EEncoding GetEncodingType() const override;`
- L337 _public prototype_ `virtual UE::Color::EChromaticAdaptationMethod GetChromaticAdapationMethod() const override;`
- L338 _public prototype_ `virtual float GetHDRNitsNormalizationFactor() const override;`
- L341 _public prototype_ `virtual UE::Color::EColorSpace GetColorSpaceType() const;` — `UE_DEPRECATED(5.8, "GetColorSpaceType is deprecated, please use GetSourceColorSpace instead.")`
- L343 _public function_ `virtual const void* GetBuffer() override`
- L365 _public prototype_ `virtual void* GetOrRequestBuffer(uint32 InBufferSize);` — Attemps to get the initialized buffer. If buffer isn't initialized or of a different size, requests a new one. @param InBufferSize The size of the required video buffer.
- L368 _public function_ `virtual uint64 GetFrameNumber() const`
- L373 _public function_ `virtual void SetTime(const FTimespan& InTime)`
- L378 _public function_ `virtual void SetFrameNumber(uint32 InFrameNumber)`
- L384 _public prototype_ `virtual bool ApplyColorConversion(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InSrcTexture, FTextureRHIRef& InDstTexture) override;`
- L386 _public function_ `void* GetMutableBuffer()`
- L397 _public prototype_ `virtual IMediaTextureSampleConverter* GetMediaTextureSampleConverter() override;`
- L398 _public prototype_ `virtual FRHITexture* GetTexture() const override;`
- L400 _public prototype_ `virtual IMediaTextureSampleColorConverter* GetMediaTextureSampleColorConverter() override;`
- L403 _public function_ `void SetBuffer(void* InBuffer)`
- L408 _public prototype_ `void SetTexture(TRefCountPtr<FRHITexture> InRHITexture);`
- L409 _public prototype_ `void SetDestructionCallback(TFunction<void(TRefCountPtr<FRHITexture>)> InDestructionCallback);`
- L410 _public prototype_ `EPixelFormat GetPixelFormat();`
- L413 _private member_ `TRefCountPtr<FRHITexture> Texture;` — Hold a texture to be used for gpu texture transfers.
- L416 _private member_ `TFunction<void(TRefCountPtr<FRHITexture>)> DestructionCallback;` — Called when the sample is destroyed by its pool.
- L421 _public prototype_ `virtual void ShutdownPoolable() override;`
- L424 _protected function_ `virtual void FreeSample()`
- L438 _protected prototype_ `virtual const FMatrix& GetYUVToRGBMatrix() const override;` — Get YUV to RGB conversion matrix @return MediaIOCore Yuv To Rgb matrix
- L442 _protected member_ `FTimespan Duration;` — Duration for which the sample is valid.
- L445 _protected member_ `EMediaTextureSampleFormat SampleFormat;` — Sample format.
- L448 _protected member_ `FTimespan Time;` — Sample time.
- L451 _protected member_ `TOptional<FTimecode> Timecode;` — Sample timecode.
- L454 _protected member_ `std::atomic<uint64> FrameNumber;` — Which engine frame number this sample corresponds to.
- L457 _protected member_ `uint32 Stride = 0;` — Image dimensions
- L458 _protected member_ `uint32 Width = 0;`
- L459 _protected member_ `uint32 Height = 0;`
- L462 _protected member_ `TArray<uint8, TAlignedHeapAllocator<4096>> Buffer;` — Pointer to raw pixels
- L463 _protected member_ `void* ExternalBuffer = nullptr;`
- L467 _protected member_ `UE::Color::EEncoding Encoding = UE::Color::EEncoding::Linear;` — `UE_DEPRECATED(5.8, "Please use SourceColorSettings instead.")`
- L470 _protected member_ `UE::Color::EColorSpace ColorSpaceType = UE::Color::EColorSpace::sRGB;` — `UE_DEPRECATED(5.8, "Please use SourceColorSettings instead.")`
- L473 _protected member_ `UE::Color::FColorSpace ColorSpaceStruct = UE::Color::FColorSpace(UE::Color::EColorSpace::sRGB);` — `UE_DEPRECATED(5.8, "Please use SourceColorSettings instead.")`
- L477 _protected member_ `TWeakPtr<FMediaIOCorePlayerBase> Player;` — The player that created this sample
- L480 _protected member_ `TSharedPtr<FMediaIOCoreTextureSampleConverter> Converter;` — Custom converter that will be the one checking back with the player for just in time sample render purposes
- L487 _private member_ `TSharedPtr<FMediaIOCoreTextureSampleBase> OriginalSample;` — A reference to the original sample that was chosen during JITR. The idea of this member is to keep the original sample alive, prevent any of its resources from being released while this proxy sample is in use.
- L490 _private member_ `std::atomic<bool> bIsAwaitingForGPUTransfer;` — Whether this sample's texture data is awaiting to be transferred by GPUDirect
- L493 _private member_ `double EvaluationOffsetInSeconds = 0;` — Time offset evaluated on game thread for JITR
- L497 _private member_ `TSharedPtr<FNativeMediaSourceColorSettings, ESPMode::ThreadSafe> SourceColorSettings;` — Manual source color space & encoding overrides.
- L499 _private member_ `TSharedPtr<struct FOpenColorIOColorConversionSettings> ColorConversionSettings;` — Settings used to apply an OCIO conversion to the sample.
- L501 _private member_ `TSharedPtr<struct FOpenColorIORenderPassResources> CachedOCIOResources;` — Cached rendering resources used for the color conversion pass when using OCIO.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MEDIAIOCORE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MediaIOCore` (scope `UE`)

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreTextureSampleConverter.h` (Public)


#### class `FMediaIOCoreTextureSampleConverter`  
`class FMediaIOCoreTextureSampleConverter : public IMediaTextureSampleConverter`  
_L21-42_
- inherits: `IMediaTextureSampleConverter`
- desc: Media IO base texture sample converter. It's mostly responsible for Just-In-Time Rendering (JITR), but also provides a way to implement custom sample conversion when inherited. @note: Don't forget to call FMediaIOTextureSampleConverter::Convert(...) from the child classes to trigger JITR pipeline. This is the place where late sample picking is actually happens.
- L25 _public prototype_ `FMediaIOCoreTextureSampleConverter() = default;`
- L26 _public prototype_ `virtual ~FMediaIOCoreTextureSampleConverter() = default;`
- L30 _public prototype_ `virtual void Setup(const TSharedPtr<FMediaIOCoreTextureSampleBase>& InSample);` — Configures settings to convert incoming sample
- L34 _public prototype_ `virtual bool Convert(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, const FConversionHints& Hints) override;`
- L35 _public prototype_ `virtual uint32 GetConverterInfoFlags() const override;`
- L41 _protected member_ `TWeakPtr<FMediaIOCoreTextureSampleBase> JITRProxySample;` — Proxy sample for JITR

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MEDIAIOCORE_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreUtilities.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MediaIO` (scope `UE`)
- L19 _prototype_ `static void LogThrottle(const FNoLoggingCategory& InLogCategory, ELogVerbosity::Type InVerbosity, const FTimespan& InTimeBetweenLogs, const FString& LogDetails, const FString& FileName, int32 LineNumber);` (scope `UE::MediaIO`)
- L25 _macro_ `#define UE_MEDIA_IO_LOG_THROTTLE(LogCategory, Verbosity, TimeBetweenLogs, Format, ...) (UE::MediaIO::LogThrottle(LogCategory, ELogVerbosity::Verbosity, TimeBetweenLogs, *FString::Printf(Format, ##__VA_ARGS__), FString(__FILE__), __LINE__))`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace MediaIO` (scope `UE`)
- L30 _function_ `static void LogThrottle(const FNoLoggingCategory& InLogCategory, ELogVerbosity::Type InVerbosity, const FTimespan& InTimeBetweenLogs, const FString& LogDetails, const FString& FileName, int32 LineNumber)` (scope `UE::MediaIO`)

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaIOCoreWaitVsyncThread.h` (Public)


#### class `FMediaIOCoreWaitVSyncThread`  
`class FMediaIOCoreWaitVSyncThread : public FRunnable`  
_L17-36_
- inherits: `FRunnable`
- L20 _public prototype_ `FMediaIOCoreWaitVSyncThread(TSharedPtr<IMediaIOCoreHardwareSync> InHardwareSync);`
- L22 _public prototype_ `virtual bool Init() override;`
- L23 _public prototype_ `virtual uint32 Run() override;`
- L25 _public prototype_ `virtual void Stop() override;`
- L26 _public prototype_ `virtual void Exit() override;`
- L29 _public prototype_ `bool Wait_GameOrRenderThread();`
- L32 _protected member_ `TSharedPtr<IMediaIOCoreHardwareSync> HardwareSync;`
- L33 _protected member_ `FEvent* WaitVSync;`
- L34 _protected member_ `TAtomic<bool> bWaitingForSignal;`
- L35 _protected member_ `TAtomic<bool> bAlive;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MEDIAIOCORE_API`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/MediaOutput.h` (Public)


#### enum `EMediaCaptureConversionOperation`  
`enum class EMediaCaptureConversionOperation : int8`  
_L18-26_
- L20 _public enumerator_ `NONE`
- L21 _public enumerator_ `RGBA8_TO_YUV_8BIT`
- L22 _public enumerator_ `RGB10_TO_YUVv210_10BIT`
- L23 _public enumerator_ `INVERT_ALPHA`
- L24 _public enumerator_ `SET_ALPHA_ONE`
- L25 _public enumerator_ `CUSTOM` — ~ If Custom used, OnCustomCapture_RenderingThread, GetCustomOutputSize and GetCustomOutputPixelFormat on the MediaCapture need to be implemented

#### enum `EMediaCaptureSourceType`  
`enum class EMediaCaptureSourceType : int8`  
_L29-35_
- reflection: `UENUM()`
- L31 _public enumerator_ `RENDER_TARGET`
- L32 _public enumerator_ `SCENE_VIEWPORT`
- L33 _public enumerator_ `RHI_RESOURCE`
- L34 _public enumerator_ `MEDIA_TEXTURE`

#### class `UMediaOutput`  
`class UMediaOutput : public UObject`  
_L44-117_
- reflection: `UCLASS(MinimalAPI, Abstract, editinlinenew, BlueprintType, hidecategories = (Object))`
- inherits: `UObject`
- desc: Abstract base class for media output. Media output describe the location and/or settings of media objects that can be used to output the content of Unreal Engine to a target device via a MediaCapture.
- L56 _public member_ `int32 NumberOfTextureBuffers;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Output", meta=(ClampMin=1, ClampMax=8))` — Number of texture used to transfer the texture from the GPU to the system memory. A smaller number is most likely to block the GPU (wait for the transfer to complete). A bigger number is most likely to increase latency. @note Some Capture are not are executed on the GPU. If it's the case then no buffer will be needed and no buffer will be created.
- L60 _public prototype_ `UMediaCapture* CreateMediaCapture();` — `UFUNCTION(BlueprintCallable, Category="Media|Output")` — Creates the specific implementation of the MediaCapture for the MediaOutput.
- L68 _public prototype_ `virtual bool Validate(FString& OutFailureReason) const;` — `UFUNCTION(BlueprintCallable, Category = "Media|Output")` — Validate the media output settings (must be implemented in child classes). @return true if validation passed, false otherwise.
- L72 _public member_ `static const FIntPoint RequestCaptureSourceSize;`
- L79 _public prototype_ `virtual FIntPoint GetRequestedSize() const PURE_VIRTUAL(UMediaOutput::GetRequestedSize, return RequestCaptureSourceSize; );` — The size of the buffer we wish to capture. The size of the buffer can not change during the capture. Return UMediaOutput::RequestCaptureSourceSize if you wish to take the buffer size as the requested size.
- L85 _public prototype_ `virtual EPixelFormat GetRequestedPixelFormat() const PURE_VIRTUAL(UMediaOutput::GetRequestedPixelFormat, return EPixelFormat::PF_Unknown; );` — The pixel format of the buffer we wish to capture. Some conversion are available. See EMediaCaptureConversionOperation
- L90 _public function_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const` — The conversion we wish to accomplish on the GPU before the DMA transfer occurs.
- L94 _public function_ `virtual FString GetDescriptionString() const` — Gets a string that sums up the media output's description for UI purposes
- L96 _public typedef_ `typedef TTuple<FText, FText, FText> FInfoElement;`
- L102 _public function_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const` — Gets a list of text containing the media source's configuration and description for UI purposes @param OutInfoElements A list of elements, where an element is constructed from a group, a label, and a value
- L104 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOutputModified, UMediaOutput*);`
- L105 _public function_ `FOnOutputModified& OnOutputModified()`
- L106 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L110 _protected function_ `virtual UMediaCapture* CreateMediaCaptureImpl()`
- L114 _private member_ `FOnOutputModified OnOutputModifiedDelegate;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MEDIAIOCORE_API`
- L104 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOutputModified, UMediaOutput*);`

### `Plugins/Media/MediaIOFramework/Source/MediaIOCore/Public/OrderedAsyncGate.h` (Public)


#### class `UE::MediaIO::FOrderedAsyncGate`  
`class FOrderedAsyncGate`  
_L17-69_
- desc: Class to ensure that async tasks execute any critical path in order. It works like clients at a shop getting a number, waiting for their turn, and when they are done they give up their turn so that the next number can be serviced. Its functions can be called from any thread.
- L22 _public function_ `uint64 GetANumber()` — Gets a number that represents the when the number holder will get their turn.
- L28 _public function_ `bool IsMyTurn(const uint32 Number) const` — Returns true if it is the turn of the given number
- L38 _public function_ `void WaitForTurn(const uint32 Number) const` — This function will block until it is the turn of the given number to execute. It can be called multiple times until the turn is given up by calling GiveUpTurn. The number given must have been received from a call to GetANumber.
- L55 _public function_ `void GiveUpTurn(const uint32 Number)` — Call this function when you are ready to give up your turn. It must be called with the number received from GetANumber, and it must be called whether WaitForTurn was called or not. Not giving up the turn will prevent any others from getting their turn. Note: It will internally call WaitForTurn.
- L65 _private member_ `std::atomic<uint32> CurrentNumber = 0;` — The current number that has its turn without having to wait any longer
- L68 _private member_ `std::atomic<uint32> NextNumber = 0;` — The number that will be given out to the next client that calls GetANumber

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MediaIO` (scope `UE`)
