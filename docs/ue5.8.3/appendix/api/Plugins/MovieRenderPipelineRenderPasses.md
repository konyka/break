# Plugins / MovieRenderPipelineRenderPasses

- module root: `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses`
- headers: 15; symbols: 855
- symbol kinds: class=25, enum=2, enumerator=15, externvar=1, function=138, macro=13, member=329, namespace=31, prototype=272, struct=27, typedef=2
- PrivateDependencyModuleNames: AudioMixer, CinematicCamera, Core, CoreUObject, Engine, ImageCore, ImageWrapper, ImageWriteQueue, Imath, MovieRenderPipelineSettings, MovieScene, OpenColorIOWrapper, SignalProcessing, Slate, SlateCore, UEOpenExr, UEOpenExrRTTI
- PublicDependencyModuleNames: ActorLayerUtilities, MovieRenderPipelineCore, OpenColorIO, RHI, RenderCore, Renderer

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Private/Graph/DeferredLayerWarmUpHelpers.h` (Private)


#### struct `UE::MovieGraph::Private::FLumenCvarCache`  
`struct FLumenCvarCache`  
_L31-69_
- desc: Manages Lumen surface cache cvars during layer warm-ups. On the first warm-up frame the surface cache is forced to fully recapture (RecaptureEveryFrame=1, Feedback=0, CardCaptureFactor=1). On subsequent warm-up frames and the actual render, those three settings are relaxed via RelaxForConvergence() so Lumen can converge. RadiosityUpdateFactor stays overridden at 1 for the entire warm-up + render sequence (restored only by Restore()) to maximize radiosity accumulation. RAII: the destructor calls Restore() as a safety net if the cvars were overridden but never explicitly restored. Restore() is idempotent.
- L33 _public prototype_ `FLumenCvarCache() = default;`
- L34 _public prototype_ `~FLumenCvarCache();`
- L36 _public prototype_ `FLumenCvarCache(const FLumenCvarCache&) = delete;`
- L37 _public prototype_ `FLumenCvarCache& operator=(const FLumenCvarCache&) = delete;`
- L40 _public prototype_ `void StoreAndOverride();` — Store current cvar values and apply aggressive settings for the first warm-up frame.
- L52 _public prototype_ `void RelaxForConvergence() const;` — Relax the first-frame-only settings so Lumen can converge through temporal accumulation. Intended to be called EXACTLY ONCE per layer warm-up sequence, immediately after the first layer warm-up render. Calling it more often is not idempotent in practice: every IConsoleVariable::Set() invokes OnChanged() which enqueues an RT shadow-propagation command and flags all registered cvar sinks regardless of value equality, which disrupts Lumen's temporal convergence on subsequent warm-up frames. RadiosityUpdateFactor remains overridden through the final render (Restore() resets it).
- L55 _public prototype_ `void Restore();` — Restore all cvars to their original values. Safe to call multiple times; only acts if StoreAndOverride was called.
- L64 _private member_ `FCachedCvar RadiosityUpdateFactor;`
- L65 _private member_ `FCachedCvar SurfaceCacheCardCaptureFactor;`
- L66 _private member_ `FCachedCvar SurfaceCacheFeedback;`
- L67 _private member_ `FCachedCvar SurfaceCacheRecaptureEveryFrame;`
- L68 _private member_ `bool bHasOverriddenState = false;`

#### struct `UE::MovieGraph::Private::FLumenCvarCache::FCachedCvar`  
`struct FCachedCvar`  
_L58-62_
- L60 _public member_ `IConsoleVariable* CVar = nullptr;`
- L61 _public member_ `int32 PreviousValue = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MovieGraph` (scope `UE`)
- L14 _namespace_ `namespace Rendering` (scope `UE::MovieGraph`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MovieGraph` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::MovieGraph`)
- L75 _prototype_ `int32 ResolveEffectiveLayerWarmUpFrames(const UMovieGraphEvaluatedConfig* InEvaluatedConfig, FName InBranchName);` (scope `UE::MovieGraph::Private`) — Computes the number of layer warm-up frames to run for a given layer. The Warm Up Settings node provides the global value; a Render Layer node on the given branch can optionally override it.
- L86 _prototype_ `void PerformLayerWarmUps( const UWorld* InWorld, int32 InNumLayerWarmUpFrames, FMovieGraphTimeStepData& InOutWarmUpTimeStepData, const FMovieGraphTraversalContext& InFrameTraversalContext, UE::MovieGraph::Rendering::FMovieGraphImagePassBase& InPassInstance, FLumenCvarCache& InOutLumenCvarCache);` (scope `UE::MovieGraph::Private`) — Perform N layer warm-up frames before the layer's final render. The first layer warm-up frame is flagged as a camera cut to suppress velocity/motion-blur artifacts from stale previous-frame transforms. Skeletal mesh bone velocity buffers are cleared before warm-ups begin to prevent cross-layer leakage; mesh deformers that write deformed geometry buffers are skipped by default because those buffers are managed separately from the skeletal bone-buffer path. The Lumen cvar cache is relaxed after the first warm-up frame so Lumen can converge through temporal accumulation on subsequent frames and on the actual render.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/Graph/Nodes/MovieGraphDeferredPanoramicPassNode.h` (Public)


#### class `UMovieGraphDeferredPanoramicNode`  
`class UMovieGraphDeferredPanoramicNode final : public UMovieGraphImagePassBaseNode`  
_L18-194_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphImagePassBaseNode`
- L23 _public prototype_ `UMovieGraphDeferredPanoramicNode();`
- L27 _public prototype_ `virtual void RenderImpl(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;` — UMovieGraphRenderPassNode Interface
- L31 _public prototype_ `virtual FEngineShowFlags GetShowFlags() const override;` — UMovieGraphImagePassBaseNode Interface
- L32 _public prototype_ `virtual EViewModeIndex GetViewModeIndex() const override;`
- L33 _public prototype_ `virtual TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase> CreateInstance() const override;`
- L34 _public prototype_ `virtual bool GetWriteAllSamples() const override;`
- L35 _public prototype_ `virtual int32 GetNumSpatialSamples() const override;`
- L36 _public prototype_ `virtual bool GetDisableToneCurve() const override;`
- L37 _public prototype_ `virtual bool GetAllowOCIO() const override;`
- L38 _public function_ `virtual bool GetOverrideAntiAliasing() const override`
- L39 _public prototype_ `virtual EAntiAliasingMethod GetAntiAliasingMethod() const override;`
- L40 _public function_ `virtual bool GetEnableHistoryPerTile() const`
- L41 _public prototype_ `virtual void GetFormatResolveArgs(FMovieGraphResolveArgs& OutMergedFormatArgs, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier) const;`
- L42 _public prototype_ `virtual void PreLayerRender( const TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase>& InInstance, const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;`
- L46 _public prototype_ `virtual void PostLayerRender( const TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase>& InInstance, const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;`
- L54 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L55 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L59 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L63 _public member_ `uint8 bOverride_NumHorizontalSteps : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L66 _public member_ `uint8 bOverride_NumVerticalSteps : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L69 _public member_ `uint8 bOverride_bFollowCameraOrientation : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L72 _public member_ `uint8 bOverride_bAllocateHistoryPerPane : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L75 _public member_ `uint8 bOverride_bPageToSystemMemory : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L78 _public member_ `uint8 bOverride_SpatialSampleCount : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L81 _public member_ `uint8 bOverride_AntiAliasingMethod : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L84 _public member_ `uint8 bOverride_Filter : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L87 _public member_ `uint8 bOverride_bDisableToneCurve : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L90 _public member_ `uint8 bOverride_bAllowOCIO : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L93 _public member_ `uint8 bOverride_ViewModeIndex : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L96 _public member_ `uint8 bOverride_bWriteAllSamples : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L99 _public member_ `int32 NumHorizontalSteps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 8, ClampMin = 8), Category = "Sampling", meta = (EditCondition = "bOverride_NumHorizontalSteps"))`
- L102 _public member_ `int32 NumVerticalSteps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 3, ClampMin = 3), Category = "Sampling", meta = (EditCondition = "bOverride_NumVerticalSteps"))`
- L108 _public member_ `bool bFollowCameraOrientation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sampling", meta = (EditCondition = "bOverride_bFollowCameraOrientation"))` — Should the Pitch, Yaw and Roll of the camera be respected? If false, only the location will be taken from the camera.
- L115 _public member_ `bool bAllocateHistoryPerPane;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sampling", meta = (EditCondition = "bOverride_bAllocateHistoryPerPane"))` — Should we store the render scene history per individual render? This can consume a great deal of memory with many renders, but enables TAA/TSR and other history-based effects (denoisers, auto-exposure, Lumen, etc.) to work.
- L122 _public member_ `bool bPageToSystemMemory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sampling", meta = (EditCondition = "bOverride_bPageToSystemMemory"))` — If true, persistented GPU data per panoramic pane is paged to system memory, allowing higher resolutions, but significantly increasing render times. The GPU data is downloaded after each tile is rendered, and then re-uploaded for the next tile.
- L131 _public member_ `int32 SpatialSampleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 1, ClampMin = 1), Category = "Sampling", meta = (EditCondition = "bOverride_SpatialSampleCount"))` — How many sub-pixel jitter renders should we do per temporal sample? This can be used to achieve high sample counts without Temporal Sub-Sampling (allowing high sample counts without motion blur being enabled), but we generally recommend using Temporal Sub-Samples when possible. It can also be combined with temporal samples and you will get SpatialSampleCount many renders per temporal sample.
- L141 _public member_ `TEnumAsByte<EAntiAliasingMethod> AntiAliasingMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sampling", meta = (EditCondition = "bOverride_AntiAliasingMethod"))` — Which anti-aliasing method should this render use. If this is set to None, then Movie Render Graph will handle anti-aliasing by doing a sub-pixel jitter (one for each temporal/spatial sample). Some rendering effects rely on TSR or TAA to reduce noise so we recommend leaving them enabled where possible. All options work with Spatial and Temporal samples, but TSR/TAA may introduce minor visual artifacts (such as ghosting). MSAA is not supported in the deferred renderer.
- L147 _public member_ `EMoviePipelinePanoramicFilterType Filter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sampling", meta = (EditCondition = "bOverride_Filter"))` — Filter used when blending panoramic. Bilinear is fastest (Samples a 2x2 pixel grid) and produces nearly as good results as the others which require sampling 4x4 pixels.
- L155 _public member_ `bool bWriteAllSamples;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sampling", AdvancedDisplay, DisplayName = "Write All Samples (Debug)", meta = (EditCondition = "bOverride_bWriteAllsamples"))` — Debug Feature. Can use this to write out each individual Temporal and Spatial sample rendered by this render pass, which allows you to see which images are being accumulated together. Can be useful for debugging incorrect looking frames to see which sub-frame evaluations were incorrect.
- L163 _public member_ `bool bDisableToneCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Processing", meta = (EditCondition = "bOverride_bDisableToneCurve"))` — If true, the tone curve will be disabled for this render pass. This will result in values greater than 1.0 in final renders and can optionally be combined with OCIO profiles on the file output nodes to convert from Linear Values in Working Color Space (which is sRGB  (Rec. 709) by default, unless changed in the project settings).
- L169 _public member_ `bool bAllowOCIO;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Processing", meta = (EditCondition = "bOverride_bAllowOCIO"))` — Allow the output file OpenColorIO transform to be used on this render.
- L178 _public member_ `TEnumAsByte<EViewModeIndex> ViewModeIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View Mode", meta = (EditCondition = "bOverride_ViewModeIndex", InvalidEnumValues = "VMI_PathTracing,VMI_VisualizeBuffer,VMI_Unknown"))` — The view mode index that will be applied to renders. These mirror the View Modes you find in the Viewport, but most view modes other than Lit are used for debugging so they may not do what you expect, or may have to be used in combination with certain Show Flags to produce a result similar to what you see in the viewport.
- L186 _private member_ `TMap<const UE::MovieGraph::Rendering::FMovieGraphImagePassBase*, TUniquePtr<UE::MovieGraph::Private::FLumenCvarCache>> ActiveLayerCaches;` — Lumen cvar caches, one per pass instance, populated by PreLayerRender and consumed by PostLayerRender. Keyed by the instance pointer so that layers are isolated from one another. TUniquePtr guarantees the cache's destructor runs on removal (as a safety net).
- L193 _private member_ `FMovieGraphTimeStepData CurrentWarmUpTimeStepData;` — Shared across every PreLayerRender call within a single RenderImpl invocation so its RenderedFrameNumber accumulates monotonically across all layers' warm-up renders. That monotonic progression is required for stable Lumen lighting.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MovieGraph` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::MovieGraph`)
- L15 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/Graph/Nodes/MovieGraphDeferredPassNode.h` (Public)


#### class `UMovieGraphDeferredRenderPassNode`  
`class UMovieGraphDeferredRenderPassNode : public UMovieGraphImagePassBaseNode`  
_L23-301_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphImagePassBaseNode`
- desc: A render node which uses the Deferred Renderer.
- L28 _public prototype_ `UMovieGraphDeferredRenderPassNode();`
- L31 _public prototype_ `virtual void GetFormatResolveArgs(FMovieGraphResolveArgs& OutMergedFormatArgs, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier) const override;`
- L32 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L33 _public prototype_ `virtual void ResolveTokenContainingProperties(TFunction<void(FString&)>& ResolveFunc, const FMovieGraphTokenResolveContext& InContext) override;`
- L51 _public typedef_ `using FPassInstanceFactory = TFunction<TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase>( const FPassInstanceFactoryContext& )>;` — Factory function type for plugins that want to override deferred pass instance creation. Called once per layer during setup. Return a valid instance to override the default FMovieGraphDeferredPass, or nullptr to decline (fall back to next factory or default). Note: If multiple plugins register factories that claim the same layer, a warning is logged. The first registered factory that returns a non-null pass wins.
- L62 _public prototype_ `static void RegisterPassInstanceFactory(FName InName, FPassInstanceFactory InFactory);` — Register a named factory that can override pass instance creation. This is used to tweak the behavior of the Deferred Renderer node. Use sparingly; generally, creating a new node is the best approach. @param InName     Unique name identifying the pass instance factory. If a factory with this name is already registered, it is replaced. @param InFactory  The factory function.
- L65 _public prototype_ `static void UnregisterPassInstanceFactory(FName InName);` — Unregister a previously registered factory by name.
- L68 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L69 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L74 _protected prototype_ `virtual void SetupImpl(const FMovieGraphRenderPassSetupData& InSetupData) override;` — UMovieGraphRenderPassNode Interface
- L75 _protected prototype_ `virtual void RenderImpl(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;`
- L76 _protected prototype_ `virtual TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase> CreateInstance() const override;`
- L77 _protected prototype_ `virtual bool GetWriteAllSamples() const override;`
- L78 _protected prototype_ `virtual TArray<FMoviePipelinePostProcessPass> GetAdditionalPostProcessMaterials() const override;`
- L79 _protected prototype_ `virtual FString GetPPMFileNameFormatString() const override;`
- L80 _protected prototype_ `virtual int32 GetNumSpatialSamples() const override;`
- L81 _protected prototype_ `virtual bool GetDisableToneCurve() const override;`
- L82 _protected prototype_ `virtual bool GetAllowOCIO() const override;`
- L83 _protected function_ `virtual bool GetOverrideAntiAliasing() const override`
- L84 _protected prototype_ `virtual EAntiAliasingMethod GetAntiAliasingMethod() const override;`
- L85 _protected function_ `virtual bool GetEnableHighResolutionTiling() const override`
- L86 _protected function_ `virtual FIntPoint GetTileCount() const override`
- L87 _protected function_ `virtual float GetTileOverlapPercentage() const override`
- L88 _protected function_ `virtual bool GetEnablePageToSystemMemory() const override`
- L89 _protected function_ `virtual bool GetEnableHistoryPerTile() const override`
- L93 _protected prototype_ `virtual EViewModeIndex GetViewModeIndex() const override;` — UMovieGraphImagePassBaseNode Interface
- L94 _protected prototype_ `virtual bool GetWriteBeautyPassToDisk() const override;`
- L95 _protected prototype_ `virtual void PreLayerRender( const TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase>& InInstance, const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;`
- L99 _protected prototype_ `virtual void PostLayerRender( const TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase>& InInstance, const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;`
- L107 _public member_ `uint8 bOverride_SpatialSampleCount: 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L110 _public member_ `uint8 bOverride_AntiAliasingMethod : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L113 _public member_ `uint8 bOverride_bDisableToneCurve : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L116 _public member_ `uint8 bOverride_bAllowOCIO : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L119 _public member_ `uint8 bOverride_ViewModeIndex : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L122 _public member_ `uint8 bOverride_bWriteAllSamples : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L125 _public member_ `uint8 bOverride_bIncludeBeautyRenderInOutput : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L128 _public member_ `uint8 bOverride_PPMFileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L131 _public member_ `uint8 bOverride_AdditionalPostProcessMaterials : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L134 _public member_ `uint8 bOverride_bEnableHighResolutionTiling : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L137 _public member_ `uint8 bOverride_TileCount : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L140 _public member_ `uint8 bOverride_OverlapPercentage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L143 _public member_ `uint8 bOverride_bAllocateHistoryPerTile : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L146 _public member_ `uint8 bOverride_bPageToSystemMemory : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L155 _public member_ `int32 SpatialSampleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 1, ClampMin = 1), Category = "Sampling", meta=(EditCondition="bOverride_SpatialSampleCount"))` — How many sub-pixel jitter renders should we do per temporal sample? This can be used to achieve high sample counts without Temporal Sub-Sampling (allowing high sample counts without motion blur being enabled), but we generally recommend using Temporal Sub-Samples when possible. It can also be combined with temporal samples and you will get SpatialSampleCount many renders per temporal sample.
- L165 _public member_ `TEnumAsByte<EAntiAliasingMethod> AntiAliasingMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sampling", meta = (EditCondition = "bOverride_AntiAliasingMethod"))` — Which anti-aliasing method should this render use. If this is set to None, then Movie Render Graph will handle anti-aliasing by doing a sub-pixel jitter (one for each temporal/spatial sample). Some rendering effects rely on TSR or TAA to reduce noise so we recommend leaving them enabled where possible. All options work with Spatial and Temporal samples, but TSR/TAA may introduce minor visual artifacts (such as ghosting). MSAA is not supported in the deferred renderer.
- L173 _public member_ `bool bWriteAllSamples;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sampling", AdvancedDisplay, DisplayName="Write All Samples (Debug)", meta = (EditCondition = "bOverride_bWriteAllsamples"))` — Debug Feature. Can use this to write out each individual Temporal and Spatial sample rendered by this render pass, which allows you to see which images are being accumulated together. Can be useful for debugging incorrect looking frames to see which sub-frame evaluations were incorrect.
- L181 _public member_ `bool bDisableToneCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Processing", meta = (EditCondition = "bOverride_bDisableToneCurve"))` — If true, the tone curve will be disabled for this render pass. This will result in values greater than 1.0 in final renders and can optionally be combined with OCIO profiles on the file output nodes to convert from Linear Values in Working Color Space (which is sRGB  (Rec. 709) by default, unless changed in the project settings).
- L187 _public member_ `bool bAllowOCIO;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Processing", meta = (EditCondition = "bOverride_bAllowOCIO"))` — Allow the output file OpenColorIO transform to be used on this render.
- L196 _public member_ `TEnumAsByte<EViewModeIndex> ViewModeIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View Mode", meta=(EditCondition="bOverride_ViewModeIndex", InvalidEnumValues = "VMI_PathTracing,VMI_VisualizeBuffer,VMI_Unknown"))` — The view mode index that will be applied to renders. These mirror the View Modes you find in the Viewport, but most view modes other than Lit are used for debugging so they may not do what you expect, or may have to be used in combination with certain Show Flags to produce a result similar to what you see in the viewport.
- L204 _public member_ `bool bIncludeBeautyRenderInOutput;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process Materials", meta=(EditCondition="bOverride_bIncludeBeautyRenderInOutput"))` — Whether the main beauty pass should be written to disk. If just Post Process Material passes should be written to disk, turn this off.
- L210 _public member_ `FString PPMFileNameFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process Materials", DisplayName = "PPM File Name Format", meta=(EditCondition="bOverride_PPMFileNameFormat", MrgTokenAutocomplete))` — If specified, overrides the output node's file name format, and uses this file name format for Post Process Material passes instead.
- L216 _public member_ `TArray<FMoviePipelinePostProcessPass> AdditionalPostProcessMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process Materials", meta=(EditCondition="bOverride_AdditionalPostProcessMaterials"))` — An array of additional post-processing materials to run after the frame is rendered. Using this feature may add a notable amount of render time.
- L234 _public member_ `bool bEnableHighResolutionTiling;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Resolution Tiling", meta = (EditCondition = "bOverride_bEnableHighResolutionTiling"))` — If true, the render will be done using a "tiled" render, which can overcome size limitations of GPUs but comes with a significant number of limitations. The internal GBuffer used for rendering is quite memory intensive, so a very large (ie: 8-16k) render may be impractical from a memory standpoint. You can enable High Resolution Tiling to render this in multiple smaller passes, but there is overhead to each tile as well, in terms of raytracing and lumen acceleration structures. - If you have VRAM available, it's better to render with 1 tile instead of 2, and instead increase the TDR (Timeout Device Recovery) in your OS to allow frames to take longer than the default 2s limit. - If you need to use tiling, and you need to use Lumen, TAA/TSR, or other rendering features that require the previous frame's buffer, then you'll need to enable bAllocateHistoryPerTile. This can come at a large VRAM cost but may require less vram than having a larger GBuffer resolution. - If you have spare system memory (RAM), you can use the experimental bPageToSystemMemory feature to download all of the per-tile rendering history into CPU memory after each tile, and then upload it again before the next time that tile is used. This comes at a _significant_ performance and system memory cost but can allow utilizing significantly larger overall resolutions while still supporting Lumen, TAA/TSR and other features.
- L242 _public member_ `int32 TileCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Resolution Tiling", meta = (EditCondition = "bOverride_TileCount", UIMin = "1", ClampMin = "1", UIMax = "16"))` — If bEnableHighResolutionTiling is enabled, what is the tile count that the screen should be broken into. This is not in pixels, but in number of tiles per side, ie: an output resolution of 4k, and a tile count of 2, produces 4 tiles (2 horizontal, 2 vertical) with each tile being 1080p. Larger tile counts shrink the individual render resolution, but increase the total number of renders needed.
- L252 _public member_ `float OverlapPercentage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Resolution Tiling", meta = (EditCondition = "bOverride_OverlapPercentage", UIMin = "0", UIMax = "50", ClampMin = "0", ClampMax = "50"))` — Rendering effects such as Depth of Field may produce different results near the edge of a tile (as it cannot sample outside of the tile itself), so this setting allows you to create an overlapped region between tiles. 10% is a good starting point, but may need to be increased if you have extremely large depth of field. Note: This uses 0-50 and not 0-.5 like the previous system did to bring it in-line with other usages of overscan in the engine (nDisplay).
- L260 _public member_ `bool bAllocateHistoryPerTile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Resolution Tiling", meta = (EditCondition = "bOverride_bAllocateHistoryPerTile"))` — If enabled, a FSceneViewStateInterface is allocated for each tile in the high resolution image. This is required for TAA/TSR/Lumen and other modern rendering features to work correctly, but can consume significant amounts of VRAM to store the state for each tile. This can be mitigated (at significant render time impact) with the new experimental bPageToSystemMemory cost.
- L269 _public member_ `bool bPageToSystemMemory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Resolution Tiling", meta = (EditCondition = "bOverride_bPageToSystemMemory"))` — Experimental Feature: When enabled, after each tile is rendered, MRQ will download the per-tile image history back to system RAM, and then the next time the tile is rendered on the subsequent frame the data is transfered from sytem memory back to GPU memory for use. This significantly impacts rendering time, but can allow using Lumen and other features that rely on bAllocateHistoryPerTile to be used on GPUs that do not have enough VRAM to store all of the history data for every tile at once.
- L283 _private member_ `static FCriticalSection PassInstanceFactoriesCS;` — Protects mutations to PassInstanceFactories.
- L286 _private member_ `static TArray<FNamedPassFactory> PassInstanceFactories;` — The pass instance factories that have been registered.
- L293 _private member_ `TMap<const UE::MovieGraph::Rendering::FMovieGraphImagePassBase*, TUniquePtr<UE::MovieGraph::Private::FLumenCvarCache>> ActiveLayerCaches;` — Lumen cvar caches, one per pass instance, populated by PreLayerRender and consumed by PostLayerRender. Keyed by the instance pointer so that layers are isolated from one another. TUniquePtr guarantees the cache's destructor runs on removal (as a safety net).
- L300 _private member_ `FMovieGraphTimeStepData CurrentWarmUpTimeStepData;` — Shared across every PreLayerRender call within a single RenderImpl invocation so its RenderedFrameNumber accumulates monotonically across all layers' warm-up renders. That monotonic progression is required for stable Lumen lighting.

#### struct `UMovieGraphDeferredRenderPassNode::FPassInstanceFactoryContext`  
`struct FPassInstanceFactoryContext`  
_L36-41_
- desc: Context provided to pass instance factories during setup.
- L38 _public member_ `const FMovieGraphRenderPassLayerData& LayerData;`
- L39 _public member_ `UMovieGraphDefaultRenderer* Renderer = nullptr;`
- L40 _public member_ `UMovieGraphEvaluatedConfig* EvaluatedConfig = nullptr;`

#### struct `UMovieGraphDeferredRenderPassNode::FNamedPassFactory`  
`struct FNamedPassFactory`  
_L273-280_
- desc: Information identifying a registered pass instance factory.
- L276 _public member_ `FName Name;` — The name of the pass instance factory.
- L279 _public member_ `FPassInstanceFactory Factory;` — The function that will create the pass instance factory.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MovieGraph` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::MovieGraph`)
- L17 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/Graph/Nodes/MovieGraphImagePassBaseNode.h` (Public)


#### class `UMovieGraphImagePassBaseNode`  
`class UMovieGraphImagePassBaseNode : public UMovieGraphRenderPassNode`  
_L27-162_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMovieGraphRenderPassNode`
- desc: The UMovieGraphImagePassBaseNode is an abstract base-class for render nodes that wish to create renders of the 3d scene. You are not required to inherit from this node (can inherit from UMovieGraphRenderPassNode), but this node provides a helpful set of functions and default values for constructing the required matrices and settings for viewport-like renders.
- L31 _public prototype_ `UMovieGraphImagePassBaseNode();`
- L33 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L36 _public prototype_ `virtual EViewModeIndex GetViewModeIndex() const;` — Gets the view mode index that should be active for this renderer.
- L39 _public prototype_ `virtual FEngineShowFlags GetShowFlags() const;` — Gets the show flags that should be active for this renderer.
- L42 _public prototype_ `virtual TArray<uint32> GetDefaultShowFlags() const;` — Gets any show flags that should be applied as defaults, before user changes are applied.
- L45 _public function_ `virtual bool GetWriteAllSamples() const` — Should each individual sample rendered be written out for debugging?
- L48 _public function_ `virtual TArray<FMoviePipelinePostProcessPass> GetAdditionalPostProcessMaterials() const` — Get an array of user-added post-process materials for the render
- L54 _public function_ `virtual FString GetPPMFileNameFormatString() const` — Get the post-process material file name format string, if any. If empty, no file name format override will be used for PPMs, and the value on the output node will be used.
- L57 _public function_ `virtual int32 GetNumSpatialSamples() const` — How many spatial samples should be rendered each frame?
- L61 _public function_ `virtual int32 GetNumSpatialSamplesDuringWarmUp() const` — `UE_DEPRECATED(5.8, "Override the version that takes arguments instead, this version is no longer called.")` — DEPRECATED - How many spatial samples should be used during warm-up frames?
- L67 _public prototype_ `virtual int32 GetNumSpatialSamplesDuringWarmUp(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) const;` — The number of spatial samples that are performed during warm-up frames. This is called per-frame, so the value returned here can vary during the warm-up process.
- L70 _public function_ `virtual int32 GetSeedOffset() const` — Offset to apply to random number generator seed.
- L73 _public function_ `virtual bool GetDisableToneCurve() const` — Should the tone curve be disabled while rendering? Allows for linear values in exrs but changes the look of the final image.
- L76 _public function_ `virtual bool GetAllowOCIO() const` — Should the output file be allowed to apply an OCIO transform on this render?
- L79 _public function_ `virtual bool GetAllowDenoiser() const` — Should the denoiser be run on the resulting image (only has any effect with the Path Tracer)
- L82 _public function_ `virtual bool GetOverrideAntiAliasing() const` — Should we override the anti-aliasing setting specified by the Project Settings?
- L85 _public function_ `virtual EAntiAliasingMethod GetAntiAliasingMethod() const` — Which AA Method should be used?
- L88 _public function_ `virtual bool GetAllowsShowFlagsCustomization() const` — Whether this node allows changing the Show Flags in the details panel.
- L91 _public function_ `virtual bool GetAllowsCompositing() const` — Whether this pass allows other passes to be composited on it.
- L94 _public function_ `virtual bool GetWriteBeautyPassToDisk() const` — Whether this node's beauty pass should be written to disk. For some nodes, this will have no effect because there is no "beauty" pass.
- L97 _public function_ `virtual bool GetForceLosslessCompression() const` — Whether lossless compression must be forced on for this node.
- L100 _public function_ `virtual bool GetEnableHighResolutionTiling() const` — Are we using high resolution tiling?
- L103 _public function_ `virtual FIntPoint GetTileCount() const` — If using high resolution tiling, how many tiles are being rendered? If not using tiling should be (1, 1).
- L106 _public function_ `virtual float GetTileOverlapPercentage() const` — If using high resolution tiling, what percentage of overlap should be used between tiles? 0-100 scale.
- L109 _public function_ `virtual bool GetEnablePageToSystemMemory() const` — If using high resolution tiling, should each tile be paged to system memory after rendering?
- L112 _public function_ `virtual bool GetEnableHistoryPerTile() const` — If using high resolution tiling, do we keep a unique scene view history for each tile?
- L118 _protected member_ `uint8 bOverride_ShowFlags : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))` — Note: Since *individual* show flags are overridden instead of the entire ShowFlags property, manually set to overridden so the traversal picks the changes up (otherwise they will be ignored).
- L122 _protected member_ `TObjectPtr<UMovieGraphShowFlags> ShowFlags;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Show Flags")` — The show flags that should be active during a render for this node.
- L124 _protected member_ `TArray<TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase>> CurrentInstances;`
- L126 _protected member_ `static FString DefaultDepthAsset;`
- L127 _protected member_ `static FString DefaultMotionVectorsAsset;`
- L131 _protected prototype_ `virtual void SetupImpl(const FMovieGraphRenderPassSetupData& InSetupData) override;` — UMovieGraphRenderPassNode Interface
- L132 _protected prototype_ `virtual void TeardownImpl() override;`
- L133 _protected prototype_ `virtual void RenderImpl(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;`
- L134 _protected prototype_ `virtual void GatherOutputPassesImpl(UMovieGraphEvaluatedConfig* InConfig, TArray<FMovieGraphRenderDataIdentifier>& OutExpectedPasses) const override;`
- L135 _protected prototype_ `virtual void UpdateRenderPassTelemetryImpl(FMoviePipelineEndShotRenderTelemetryContext& InOutTelemetry) const override;`
- L136 _protected prototype_ `virtual void GatherRenderCameraSourcesImpl(TArray<TSharedRef<FMovieGraphRenderCameraSource>>& OutSources) const override;`
- L137 _protected function_ `virtual int32 GetNumSceneViewsRenderedImpl() const`
- L138 _protected prototype_ `virtual void GetPreviewBannerMessagesImpl(const FMovieGraphRenderDataIdentifier& InIdentifier, TArray<FMovieGraphPreviewBannerMessage>& OutMessages) const override;`
- L141 _protected function_ `virtual TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase> CreateInstance() const`
- L148 _protected function_ `virtual void PreLayerRender( const TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase>& InInstance, const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData)` — Called once per pass instance, immediately after the render layer modifiers are activated and immediately before the instance's Render() is invoked. Override to insert per-layer setup. Does nothing by default.
- L158 _protected function_ `virtual void PostLayerRender( const TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase>& InInstance, const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData)` — Called once per pass instance, immediately after the instance's Render() returns and before the render-layer modifiers are cleared. Override to insert per-layer teardown. Does nothing by default.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/Graph/Nodes/MovieGraphPathTracerPassNode.h` (Public)


#### enum `EMovieGraphPathTracerDenoiserType`  
`enum class EMovieGraphPathTracerDenoiserType : uint8`  
_L13-28_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `Spatial = 0` — The active spatial denoiser plugin will be used for denoising. If the denoiser is not loaded, a warning will show in the log. If multiple spatial denoiser plugins are enabled, the last one to get loaded will be the one used.
- L27 _public enumerator_ `Temporal = 1` — The active spatial-temporal denoiser plugin will be used for denoising. It provides more temporal stability than spatial denoiser if the Frame Count of past/future frames are used (Frame Count > 0) in the plugin. The user needs to config `Frame Count` to match the requirements of the chosen denoiser plugin. If the denoiser is not loaded, a warning will show in the log. If multiple spatial-temporal denoiser plugins are enabled, the last one to get loaded will be the one used.

#### class `UMovieGraphPathTracerRenderPassNode`  
`class UMovieGraphPathTracerRenderPassNode : public UMovieGraphImagePassBaseNode`  
_L33-346_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphImagePassBaseNode`
- desc: A render node which uses the path tracer.
- L38 _public prototype_ `UMovieGraphPathTracerRenderPassNode();`
- L41 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L42 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L46 _public prototype_ `virtual void SetupImpl(const FMovieGraphRenderPassSetupData& InSetupData) override;` — UMovieGraphRenderPassNode Interface
- L47 _public prototype_ `virtual void TeardownImpl() override;`
- L51 _public prototype_ `virtual bool GetWriteAllSamples() const override;` — UMovieGraphImagePassBaseNode Interface
- L52 _public prototype_ `virtual TArray<FMoviePipelinePostProcessPass> GetAdditionalPostProcessMaterials() const override;`
- L53 _public prototype_ `virtual FString GetPPMFileNameFormatString() const override;`
- L54 _public prototype_ `virtual int32 GetNumSpatialSamples() const override;`
- L55 _public prototype_ `virtual int32 GetNumSpatialSamplesDuringWarmUp(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) const override;`
- L56 _public prototype_ `virtual int32 GetSeedOffset() const override;`
- L57 _public prototype_ `virtual bool GetDisableToneCurve() const override;`
- L58 _public prototype_ `virtual bool GetAllowOCIO() const override;`
- L59 _public prototype_ `virtual bool GetAllowDenoiser() const override;`
- L60 _public prototype_ `virtual bool GetWriteBeautyPassToDisk() const override;`
- L61 _public prototype_ `virtual TUniquePtr<UE::MovieGraph::Rendering::FMovieGraphImagePassBase> CreateInstance() const override;`
- L62 _public prototype_ `virtual FEngineShowFlags GetShowFlags() const override;`
- L63 _public prototype_ `virtual bool GetEnableHighResolutionTiling() const override;`
- L64 _public prototype_ `virtual FIntPoint GetTileCount() const override;`
- L65 _public prototype_ `virtual float GetTileOverlapPercentage() const override;`
- L66 _public prototype_ `virtual bool GetEnablePageToSystemMemory() const override;`
- L67 _public prototype_ `virtual bool GetEnableHistoryPerTile() const override;`
- L71 _public prototype_ `virtual void GetFormatResolveArgs(FMovieGraphResolveArgs& OutMergedFormatArgs, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier) const override;` — UMovieGraphSettingNode Interface
- L74 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L75 _public prototype_ `virtual void ResolveTokenContainingProperties(TFunction<void(FString&)>& ResolveFunc, const FMovieGraphTokenResolveContext& InContext) override;`
- L79 _protected prototype_ `virtual int32 GetCoolingDownFrameCount() const override;` — UMovieGraphRenderPassNode Interface
- L83 _protected prototype_ `virtual EViewModeIndex GetViewModeIndex() const override;` — UMovieGraphCoreRenderPassNode Interface
- L89 _public member_ `uint8 bOverride_SpatialSampleCount : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L92 _public member_ `uint8 bOverride_SeedOffset : 1;` — `UPROPERTY(BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L95 _public member_ `uint8 bOverride_bEnableReferenceMotionBlur : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L98 _public member_ `uint8 bOverride_bEnableDenoiser : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L101 _public member_ `uint8 bOverride_DenoiserType : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L104 _public member_ `uint8 bOverride_FrameCount : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L107 _public member_ `uint8 bOverride_bDisableToneCurve : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L110 _public member_ `uint8 bOverride_bAllowOCIO : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L113 _public member_ `uint8 bOverride_bLightingComponents_IncludeEmissive : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L116 _public member_ `uint8 bOverride_bLightingComponents_IncludeDiffuse : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L119 _public member_ `uint8 bOverride_bLightingComponents_IncludeIndirectDiffuse : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L122 _public member_ `uint8 bOverride_bLightingComponents_IncludeSpecular : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L125 _public member_ `uint8 bOverride_bLightingComponents_IncludeIndirectSpecular : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L128 _public member_ `uint8 bOverride_bLightingComponents_IncludeVolume : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L131 _public member_ `uint8 bOverride_bLightingComponents_IncludeIndirectVolume : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L134 _public member_ `uint8 bOverride_bWriteAllSamples : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L137 _public member_ `uint8 bOverride_bIncludeBeautyRenderInOutput : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L140 _public member_ `uint8 bOverride_PPMFileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L143 _public member_ `uint8 bOverride_AdditionalPostProcessMaterials : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L146 _public member_ `uint8 bOverride_bEnableHighResolutionTiling : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L149 _public member_ `uint8 bOverride_TileCount : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L152 _public member_ `uint8 bOverride_OverlapPercentage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L155 _public member_ `uint8 bOverride_bAllocateHistoryPerTile : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L158 _public member_ `uint8 bOverride_bPageToSystemMemory : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L167 _public member_ `int32 SpatialSampleCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 1, ClampMin = 1), Category = "Sampling", meta = (EditCondition = "bOverride_SpatialSampleCount"))` — How many sub-pixel jitter renders should we do per temporal sample? This can be used to achieve high sample counts without Temporal Sub-Sampling (allowing high sample counts without motion blur being enabled), but we generally recommend using Temporal Sub-Samples when possible. It can also be combined with temporal samples and you will get SpatialSampleCount many renders per temporal sample.
- L174 _public member_ `int32 SeedOffset;` — `UPROPERTY(BlueprintReadWrite, Category = "Sampling", AdvancedDisplay, meta = (EditCondition = "bOverride_SeedOffset"))` — Offset to apply to random number generator seed. Intentionally not exposed to the UI as meant for automated pipelines. Should be edited via scripting if needs to be changed.
- L182 _public member_ `bool bEnableReferenceMotionBlur;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 1, ClampMin = 1), Category = "Reference Motion Blur", meta = (EditCondition = "bOverride_bEnableReferenceMotionBlur"))` — When enabled, the path tracer will blend all spatial and temporal samples prior to the denoising and will disable post-processed motion blur. In this mode it is possible to use higher temporal sample counts to improve the motion blur quality. This mode also automatically enabled reference DOF. When this option is disabled, the path tracer will accumulate spatial samples, but denoise them prior to accumulation of temporal samples.
- L186 _public member_ `bool bEnableDenoiser;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Denoiser", meta = (EditCondition = "bOverride_bEnableDenoiser"))` — If true the resulting image will be denoised at the end of each set of Spatial Samples.
- L194 _public member_ `EMovieGraphPathTracerDenoiserType DenoiserType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Denoiser", meta = (EditCondition = "bOverride_DenoiserType"))` — Select which type of denoiser to use when the denoiser is enabled. Temporal denoisers will provide better results when denoising animated sequences (the denoising results will look more stable), especially when combined with an appropriate Frame Count (non-zero). Denoisers are implemented as plugins so you may need to enable a plugin as well for this to work.
- L203 _public member_ `int32 FrameCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0, ClampMin = 0, UIMax = 3), Category = "Denoiser")` — The number of frames to consider when using temporal-based denoisers. Generally higher numbers will result in longer denoising times and higher memory requirements. For NFOR this number refers to how many frames to consider on both sides of the current frame (ie: 2 means consider 2 before, and 2 after the currently denoised frame), but other denoiser implementations may interpret this value differently.
- L211 _public member_ `bool bWriteAllSamples;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sampling", AdvancedDisplay, DisplayName = "Write All Samples (Debug)", meta = (EditCondition = "bOverride_bWriteAllsamples"))` — Debug Feature. This can be used to write out each individual spatial sample rendered by this render pass, which allows you to see which images are being accumulated together. Can be useful for debugging incorrect looking frames to see which sub-frame evaluations were incorrect.
- L219 _public member_ `bool bDisableToneCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Processing", meta = (EditCondition = "bOverride_bDisableToneCurve"))` — If true, the tone curve will be disabled for this render pass. This will result in values greater than 1.0 in final renders and can optionally be combined with OCIO profiles on the file output nodes to convert from Linear Values in Working Color Space (which is sRGB  (Rec. 709) by default, unless changed in the project settings).
- L225 _public member_ `bool bAllowOCIO;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Processing", meta = (EditCondition = "bOverride_bAllowOCIO"))` — Allow the output file OpenColorIO transform to be used on this render.
- L229 _public member_ `bool bLightingComponents_IncludeEmissive = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Components", DisplayName = "Emissive", meta = (EditCondition = "bOverride_bLightingComponents_IncludeEmissive"))` — Whether the render should include directly visible emissive components.
- L233 _public member_ `bool bLightingComponents_IncludeDiffuse = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Components", DisplayName = "Diffuse", meta = (EditCondition = "bOverride_bLightingComponents_IncludeDiffuse"))` — Whether the render should include diffuse lighting contributions.
- L237 _public member_ `bool bLightingComponents_IncludeIndirectDiffuse = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Components", DisplayName = "Indirect Diffuse", meta = (EditCondition = "bOverride_bLightingComponents_IncludeIndirectDiffuse"))` — Whether the render should include indirect diffuse lighting contributions.
- L241 _public member_ `bool bLightingComponents_IncludeSpecular = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Components", DisplayName = "Specular", meta = (EditCondition = "bOverride_bLightingComponents_IncludeSpecular"))` — Whether the render should include specular lighting contributions.
- L245 _public member_ `bool bLightingComponents_IncludeIndirectSpecular = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Components", DisplayName = "Indirect Specular", meta = (EditCondition = "bOverride_bLightingComponents_IncludeIndirectSpecular"))` — Whether the render should include indirect specular lighting contributions.
- L249 _public member_ `bool bLightingComponents_IncludeVolume = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Components", DisplayName = "Volume", meta = (EditCondition = "bOverride_bLightingComponents_IncludeVolume"))` — Whether the render should include volume lighting contributions.
- L253 _public member_ `bool bLightingComponents_IncludeIndirectVolume = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Components", DisplayName = "Indirect Volume", meta = (EditCondition = "bOverride_bLightingComponents_IncludeIndirectVolume"))` — Whether the render should include indirect volume lighting contributions.
- L261 _public member_ `bool bIncludeBeautyRenderInOutput;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process Materials", meta=(EditCondition="bOverride_bIncludeBeautyRenderInOutput"))` — Whether the main beauty pass should be written to disk. If just Post Process Material passes should be written to disk, turn this off.
- L267 _public member_ `FString PPMFileNameFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process Materials", DisplayName = "PPM File Name Format", meta=(EditCondition="bOverride_PPMFileNameFormat", MrgTokenAutocomplete))` — If specified, overrides the output node's file name format, and uses this file name format for Post Process Material passes instead.
- L273 _public member_ `TArray<FMoviePipelinePostProcessPass> AdditionalPostProcessMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process Materials", meta=(EditCondition="bOverride_AdditionalPostProcessMaterials"))` — An array of additional post-processing materials to run after the frame is rendered. Using this feature may add a notable amount of render time.
- L291 _public member_ `bool bEnableHighResolutionTiling;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Resolution Tiling", meta = (EditCondition = "bOverride_bEnableHighResolutionTiling"))` — If true, the render will be done using a "tiled" render, which can overcome size limitations of GPUs but comes with a significant number of limitations. The internal GBuffer used for rendering is quite memory intensive, so a very large (ie: 8-16k) render may be impractical from a memory standpoint. You can enable High Resolution Tiling to render this in multiple smaller passes, but there is overhead to each tile as well, in terms of raytracing and lumen acceleration structures. - If you have VRAM available, it's better to render with 1 tile instead of 2, and instead increase the TDR (Timeout Device Recovery) in your OS to allow frames to take longer than the default 2s limit. - If you need to use tiling, and you need to use Lumen, TAA/TSR, or other rendering features that require the previous frame's buffer, then you'll need to enable bAllocateHistoryPerTile. This can come at a large VRAM cost but may require less vram than having a larger GBuffer resolution. - If you have spare system memory (RAM), you can use the experimental bPageToSystemMemory feature to download all of the per-tile rendering history into CPU memory after each tile, and then upload it again before the next time that tile is used. This comes at a _significant_ performance and system memory cost but can allow utilizing significantly larger overall resolutions while still supporting Lumen, TAA/TSR and other features.
- L299 _public member_ `int32 TileCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Resolution Tiling", meta = (EditCondition = "bOverride_TileCount", UIMin = "1", ClampMin = "1", UIMax = "16"))` — If bEnableHighResolutionTiling is enabled, what is the tile count that the screen should be broken into. This is not in pixels, but in number of tiles per side, ie: an output resolution of 4k, and a tile count of 2, produces 4 tiles (2 horizontal, 2 vertical) with each tile being 1080p. Larger tile counts shrink the individual render resolution, but increase the total number of renders needed.
- L309 _public member_ `float OverlapPercentage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Resolution Tiling", meta = (EditCondition = "bOverride_OverlapPercentage", UIMin = "0", UIMax = "50", ClampMin = "0", ClampMax = "50"))` — Rendering effects such as Depth of Field may produce different results near the edge of a tile (as it cannot sample outside of the tile itself), so this setting allows you to create an overlapped region between tiles. 10% is a good starting point, but may need to be increased if you have extremely large depth of field. Only has an effect if bEnableHighResolutionTiling is enabled. Note: This uses 0-50 and not 0-.5 like the previous system did to bring it in-line with other usages of overscan in the engine (nDisplay).
- L317 _public member_ `bool bAllocateHistoryPerTile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Resolution Tiling", meta = (EditCondition = "bOverride_bAllocateHistoryPerTile"))` — If enabled, a FSceneViewStateInterface is allocated for each tile in the high resolution image. This is required for TAA/TSR/Lumen and other modern rendering features to work correctly, but can consume significant amounts of VRAM to store the state for each tile. This can be mitigated (at significant render time impact) with the new experimental bPageToSystemMemory cost.
- L326 _public member_ `bool bPageToSystemMemory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "High Resolution Tiling", meta = (EditCondition = "bOverride_bPageToSystemMemory"))` — Experimental Feature: When enabled, after each tile is rendered, MRQ will download the per-tile image history back to system RAM, and then the next time the tile is rendered on the subsequent frame the data is transfered from sytem memory back to GPU memory for use. This significantly impacts rendering time, but can allow using Lumen and other features that rely on bAllocateHistoryPerTile to be used on GPUs that do not have enough VRAM to store all of the history data for every tile at once.
- L333 _private member_ `bool bOriginalProgressDisplayCvarValue = false;` — The original value of the "r.PathTracing.ProgressDisplay" cvar before the render starts. The progress display will be hidden during the render.
- L339 _private member_ `int32 OriginalFrameCountCvarValue = 2;` — The original value of the "r.NFOR.FrameCount" cvar before the render starts. Will use the new value set in this node during the render.
- L345 _private member_ `int32 OriginalDenoiserType = 0;` — The original value of the "r.PathTracing.SpatialDenoiser.Type" cvar before the render starts. Will use the new value set in this node during the render.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/Graph/Renderers/MovieGraphDeferredPanoramicPass.h` (Public)


#### struct `UE::MovieGraph::Rendering::FMovieGraphDeferredPanoramicPass`  
`struct FMovieGraphDeferredPanoramicPass : public FMovieGraphImagePassBase`  
_L14-55_
- inherits: `FMovieGraphImagePassBase`
- L16 _public prototype_ `FMovieGraphDeferredPanoramicPass();`
- L19 _public prototype_ `virtual void Setup(TWeakObjectPtr<UMovieGraphDefaultRenderer> InRenderer, TWeakObjectPtr<UMovieGraphImagePassBaseNode> InRenderPassNode, const FMovieGraphRenderPassLayerData& InLayer) override;` — FMovieGraphImagePassBase Interface
- L20 _public prototype_ `virtual void Teardown() override;`
- L21 _public prototype_ `virtual UMovieGraphImagePassBaseNode* GetParentNode(UMovieGraphEvaluatedConfig* InConfig) const override;`
- L22 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L23 _public prototype_ `virtual TSharedRef<::MoviePipeline::IMoviePipelineAccumulationArgs> GetOrCreateAccumulator(TObjectPtr<UMovieGraphDefaultRenderer> InGraphRenderer, const UE::MovieGraph::FMovieGraphSampleState& InSampleState) const override;`
- L24 _public prototype_ `virtual FAccumulatorSampleFunc GetAccumulateSampleFunction() const override;`
- L25 _public prototype_ `virtual void GatherOutputPasses(UMovieGraphEvaluatedConfig* InConfig, TArray<FMovieGraphRenderDataIdentifier>& OutExpectedPasses) const override;`
- L26 _public prototype_ `virtual FName GetBranchName() const;`
- L27 _public prototype_ `virtual FString GetCameraName() const override;`
- L28 _public prototype_ `virtual int32 GetRenderCameraIndex() const override;`
- L32 _public prototype_ `virtual void Render(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;` — FMovieGraphDeferredPass Interface
- L36 _protected prototype_ `virtual bool ShouldDiscardOutput(const TSharedRef<FSceneViewFamilyContext>& InFamily, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const;`
- L37 _protected prototype_ `virtual FSceneViewStateInterface* GetSceneViewState(UMovieGraphDeferredPanoramicNode* ParentNodeThisFrame, int32_t PaneX, int32_t PaneY);`
- L41 _protected member_ `TArray<FSceneViewStateReference> PaneViewStates;` — A view state for each Pane (if History Per Pane is enabled)
- L44 _protected member_ `TArray<FSceneViewStateReference> AutoExposureViewStates;` — When using an auto exposure render pass, holds view states for 6 cube faces
- L47 _protected member_ `TPimplPtr<FSceneViewStateSystemMemoryMirror> SystemMemoryMirror;` — Used when using Page to System Memory
- L49 _protected member_ `bool bHasPrintedRenderingInfo = false;`
- L50 _protected member_ `bool bHasPrintedWarnings = false;`
- L51 _protected member_ `FMovieGraphRenderDataIdentifier RenderDataIdentifier;`
- L52 _protected member_ `FMovieGraphRenderPassLayerData LayerData;`
- L53 _protected member_ `TSharedPtr<UE::MovieGraph::IMovieGraphOutputMerger> PanoramicOutputBlender;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MovieGraph` (scope `UE`)
- L12 _namespace_ `namespace Rendering` (scope `UE::MovieGraph`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/Graph/Renderers/MovieGraphDeferredPass.h` (Public)


#### struct `UE::MovieGraph::Rendering::FMovieGraphPostRendererSubmissionParams`  
`struct FMovieGraphPostRendererSubmissionParams`  
_L12-17_
- L14 _public member_ `UE::MovieGraph::FMovieGraphSampleState SampleState;`
- L15 _public member_ `UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams RenderTargetInitParams;`
- L16 _public member_ `UE::MovieGraph::DefaultRenderer::FCameraInfo CameraInfo;`

#### struct `UE::MovieGraph::Rendering::FMovieGraphDeferredPass`  
`struct FMovieGraphDeferredPass : public FMovieGraphImagePassBase`  
_L19-141_
- inherits: `FMovieGraphImagePassBase`
- L22 _public prototype_ `virtual void Setup(TWeakObjectPtr<UMovieGraphDefaultRenderer> InRenderer, TWeakObjectPtr<UMovieGraphImagePassBaseNode> InRenderPassNode, const FMovieGraphRenderPassLayerData& InLayer) override;` — FMovieGraphImagePassBase Interface
- L23 _public prototype_ `virtual void Teardown() override;`
- L24 _public prototype_ `virtual void Render(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;`
- L25 _public prototype_ `virtual void GatherOutputPasses(UMovieGraphEvaluatedConfig* InConfig, TArray<FMovieGraphRenderDataIdentifier>& OutExpectedPasses) const override;`
- L26 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L27 _public prototype_ `virtual FName GetBranchName() const override;`
- L28 _public prototype_ `virtual FString GetCameraName() const override;`
- L29 _public prototype_ `virtual UMovieGraphImagePassBaseNode* GetParentNode(UMovieGraphEvaluatedConfig* InConfig) const override;`
- L30 _public prototype_ `virtual bool ShouldDiscardOutput(const TSharedRef<FSceneViewFamilyContext>& InFamily, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const override;`
- L31 _public prototype_ `virtual int32 GetRenderCameraIndex() const override;`
- L59 _protected prototype_ `bool HasRenderResourceParametersChanged(const FIntPoint& AccumulatorResolution, const FIntPoint& BackbufferResolution) const;`
- L60 _protected prototype_ `virtual void PostRendererSubmission(const UE::MovieGraph::FMovieGraphSampleState& InSampleState, const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InRenderTargetInitParams, FCanvas& InCanvas, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const override;`
- L61 _protected prototype_ `virtual FSceneViewStateInterface* GetSceneViewState(UMovieGraphImagePassBaseNode* ParentNodeThisFrame, int32_t TileX, int32_t TileY);`
- L64 _protected prototype_ `FResolutionAndCameraInfo GetResolutionAndCameraInfo(UMovieGraphEvaluatedConfig* InEvaluatedConfig) const;` — Provides the resolution and camera information that should be used for the next render.
- L73 _protected prototype_ `FCreateViewResult CreateConfiguredView( UE::MovieGraph::DefaultRenderer::FCameraInfo& InOutCameraInfo, const FViewFamilyInitData& InViewFamilyInitData, const FIntPoint& InBackbufferResolution, const FIntPoint& InAccumulatorResolution, UMovieGraphImagePassBaseNode* InParentNode, const int32 TileX, const int32 TileY);` — Encapsulates the shared view creation pipeline: GetSceneViewState -> CreateSceneViewFamily -> CreateViewInitOptions -> CalculateProjectionMatrix -> ModifyProjectionMatrixForTiling -> CreateSceneView -> ApplyMovieGraphOverrides. Used by both the base Render() and derived passes. Respects the bAutoRestoreViewStateMirror flag: when false, the per-call SystemMemoryMirrorRestore() is skipped so derived passes can manage restore/backup at their own granularity.
- L83 _protected prototype_ `virtual FVector2D ComputeProjectionMatrixJitter(const FVector2D& InDefaultJitter, const FIntPoint& InBackbufferResolution) const;` — Computes the projection matrix jitter amount for the current sample. Override to provide a custom jitter.
- L91 _protected prototype_ `static void WritePerViewMetadata( TMap<FString, FString>& InOutMetadata, const FSceneView& InView, const FSceneViewInitOptions& InViewInitOptions, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo, const FMovieGraphRenderDataIdentifier& InIdentifier);` — Populates the standard per-layer/per-view metadata (camera matrices, location/rotation, cine-camera attributes, blended PP settings) shared by all deferred-style passes. Derived passes that build their own SampleState should call this so their layers carry the same camera/view metadata as stock deferred passes.
- L99 _protected member_ `FMovieGraphRenderPassLayerData LayerData;`
- L102 _protected member_ `FMovieGraphRenderDataIdentifier RenderDataIdentifier;` — Unique identifier passed in GatherOutputPasses and with each render that identifies the data produced by this renderer.
- L105 _protected member_ `FSceneViewStateReference SceneViewState;` — `UE_DEPRECATED(5.6, "SceneViewState is no longer used. Use SceneViewStates instead with reference at FIntPoint(0,0).")`
- L108 _protected member_ `TMap<FIntPoint, FSceneViewStateReference> SceneViewStates;` — Scene View history used by the renderer. When using an auto-exposure pass it'll use (-1, -1), otherwise one-per tile (and one at 0,0 if not using tiling).
- L111 _protected member_ `TPimplPtr<FSceneViewStateSystemMemoryMirror> SystemMemoryMirror;` — Used when using Page to System Memory
- L119 _protected member_ `bool bAutoRestoreViewStateMirror = true;` — When true (default), CreateConfiguredView() calls SystemMemoryMirrorRestore() on the view state returned by GetSceneViewState (gated on GetEnableHistoryPerTile() && GetEnablePageToSystemMemory()). Derived passes that reuse the same view state across multiple renders within a single logical iteration should clear this flag in Setup() and backup/restore view state as needed.
- L122 _protected member_ `int32 FramesToDelayPostSubmission;` — The number of frames to delay to send frames from SubmissionQueue to post-render submission.
- L125 _protected member_ `int32 RemainingCooldownReadbackFrames;` — If using cooldown, the number of cool-down frames we still need to process.
- L128 _protected member_ `TQueue<FMovieGraphPostRendererSubmissionParams> SubmissionQueue;` — FIFO queue of rendered frames. It allows frames to be sent to post-render submission with a delay if needed (e.g., when temporal denoising is used with path tracers).
- L131 _protected member_ `bool bHasAutoExposurePass = false;` — Did we initialize a auto-exposure sceneview history during setup?
- L134 _protected member_ `bool bWriteBeautyPassToDisk = true;` — Whether the main beauty pass should be written to disk. Turn this off if only the PPM passes should be written.
- L137 _protected member_ `FIntPoint PrevAccumulatorResolution;` — Track the last Accumulator resolution we used, so that we can detect when it is changed and log that information.
- L140 _protected member_ `FIntPoint PrevBackbufferResolution;` — Track the last backbuffer resolution we used, so that we can detect when it is changed and log that information.

#### struct `UE::MovieGraph::Rendering::FMovieGraphDeferredPass::FResolutionAndCameraInfo`  
`struct FResolutionAndCameraInfo`  
_L36-46_
- desc: Data about the resolution and camera that can be used in the next render.
- L38 _public member_ `float OverscanFraction = 0.f;`
- L39 _public member_ `float CameraAspectRatio = 0.f;`
- L40 _public member_ `bool bRenderAllCameras = false;`
- L41 _public member_ `DefaultRenderer::FCameraInfo CameraInfo;`
- L42 _public member_ `FIntPoint BackbufferResolution;`
- L43 _public member_ `FIntPoint AccumulatorResolution;`
- L44 _public member_ `FIntRect AccumulatorResolutionCropRect;`
- L45 _public member_ `FIntPoint TileSize;`

#### struct `UE::MovieGraph::Rendering::FMovieGraphDeferredPass::FCreateViewResult`  
`struct FCreateViewResult`  
_L49-57_
- desc: Result of CreateConfiguredView() — contains the fully configured ViewFamily, View, FViewFamilyInitData, and FSceneViewInitOptions.
- L51 _public prototype_ `explicit FCreateViewResult(const TSharedRef<FSceneViewFamilyContext> InViewFamily);`
- L53 _public member_ `TSharedRef<FSceneViewFamilyContext> ViewFamily;`
- L54 _public member_ `FSceneView* View = nullptr;`
- L55 _public member_ `FViewFamilyInitData ViewFamilyInitData;`
- L56 _public member_ `FSceneViewInitOptions SceneViewInitOptions;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MovieGraph` (scope `UE`)
- L10 _namespace_ `namespace Rendering` (scope `UE::MovieGraph`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/Graph/Renderers/MovieGraphImagePassBase.h` (Public)


#### struct `UE::MovieGraph::Rendering::FMovieGraphRenderDataAccumulationArgs`  
`struct FMovieGraphRenderDataAccumulationArgs : ::MoviePipeline::IMoviePipelineAccumulationArgs`  
_L17-38_
- inherits: `::MoviePipeline::IMoviePipelineAccumulationArgs`
- L20 _public member_ `TWeakPtr<::MoviePipeline::IMoviePipelineOverlappedAccumulator, ESPMode::ThreadSafe> ImageAccumulator;`
- L21 _public member_ `DefaultRenderer::FSurfaceAccumulatorPool::FInstancePtr AccumulatorInstance;`
- L22 _public member_ `TWeakPtr<IMovieGraphOutputMerger, ESPMode::ThreadSafe> OutputMerger;`
- L25 _public member_ `bool bIsFirstSample;` — `UE_DEPRECATED(5.6, "No longer used, calling code now looks at sample state directly.")`
- L27 _public member_ `bool bIsLastSample;` — `UE_DEPRECATED(5.6, "No longer used, calling code now looks at sample state directly.")`
- L31 _public prototype_ `FMovieGraphRenderDataAccumulationArgs() = default;`
- L32 _public prototype_ `~FMovieGraphRenderDataAccumulationArgs() = default;`
- L33 _public prototype_ `FMovieGraphRenderDataAccumulationArgs(const FMovieGraphRenderDataAccumulationArgs&) = default;`
- L34 _public prototype_ `FMovieGraphRenderDataAccumulationArgs(FMovieGraphRenderDataAccumulationArgs&&) = default;`
- L35 _public prototype_ `FMovieGraphRenderDataAccumulationArgs& operator=(const FMovieGraphRenderDataAccumulationArgs&) = default;`
- L36 _public prototype_ `FMovieGraphRenderDataAccumulationArgs& operator=(FMovieGraphRenderDataAccumulationArgs&&) = default;`

#### struct `UE::MovieGraph::Rendering::FViewFamilyInitData`  
`struct FViewFamilyInitData`  
_L43-69_
- L45 _public function_ `FViewFamilyInitData() : RenderTarget(nullptr) , World(nullptr) , SceneCaptureSource(ESceneCaptureSource::SCS_MAX) , bWorldIsPaused(false) , FrameIndex(-1) , AntiAliasingMethod(EAntiAliasingMethod::AAM_None) , ShowFlags(ESFIM_Game) , ViewModeIndex(VMI_Lit) , bIsCameraCut(false)`
- L58 _public member_ `class FRenderTarget* RenderTarget;`
- L59 _public member_ `class UWorld* World;`
- L60 _public member_ `FMovieGraphTimeStepData TimeData;`
- L61 _public member_ `ESceneCaptureSource SceneCaptureSource;`
- L62 _public member_ `bool bWorldIsPaused;`
- L63 _public member_ `int32 FrameIndex;`
- L64 _public member_ `EAntiAliasingMethod AntiAliasingMethod;`
- L65 _public member_ `FEngineShowFlags ShowFlags;`
- L66 _public member_ `EViewModeIndex ViewModeIndex;`
- L67 _public member_ `TEnumAsByte<ECameraProjectionMode::Type> ProjectionMode;`
- L68 _public member_ `bool bIsCameraCut;`

#### struct `UE::MovieGraph::Rendering::FMovieGraphImagePassBase`  
`struct FMovieGraphImagePassBase`  
_L73-180_
- L75 _public prototype_ `FMovieGraphImagePassBase() = default;`
- L76 _public prototype_ `virtual ~FMovieGraphImagePassBase() = default;`
- L78 _public prototype_ `virtual void Setup(TWeakObjectPtr<UMovieGraphDefaultRenderer> InRenderer, TWeakObjectPtr<UMovieGraphImagePassBaseNode> InRenderPassNode, const FMovieGraphRenderPassLayerData& InLayer);`
- L79 _public prototype_ `virtual void Teardown();`
- L81 _public function_ `virtual void Render(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData)`
- L82 _public function_ `virtual void GatherOutputPasses(UMovieGraphEvaluatedConfig* InConfig, TArray<FMovieGraphRenderDataIdentifier>& OutExpectedPasses) const`
- L83 _public prototype_ `virtual void UpdateRenderPassTelemetry(FMoviePipelineEndShotRenderTelemetryContext& InOutTelemetry) const;`
- L84 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector);`
- L85 _public function_ `virtual FName GetBranchName() const`
- L86 _public function_ `virtual FString GetCameraName() const`
- L87 _public function_ `virtual TWeakObjectPtr<UMovieGraphDefaultRenderer> GetRenderer() const`
- L93 _public function_ `virtual void GetPreviewBannerMessages(TArray<FMovieGraphPreviewBannerMessage>& OutMessages) const` — Optional per-tile banner messages to overlay on this pass's preview tile in the Render Preview window. The default implementation contributes nothing.
- L96 _public function_ `virtual TSharedPtr<const FMovieGraphRenderCameraSource> GetRenderCameraSource() const` — Returns the shared camera source for this pass. Use when a shared reference is needed to extend lifetime.
- L97 _public function_ `virtual TSharedPtr<FMovieGraphRenderCameraSource> GetRenderCameraSource()`
- L100 _protected typedef_ `typedef TFunction<void(TUniquePtr<FImagePixelData>&&, const TSharedRef<FMovieGraphSampleState>, const TSharedRef<::MoviePipeline::IMoviePipelineAccumulationArgs>)> FAccumulatorSampleFunc;`
- L105 _protected function_ `virtual int32 GetRenderCameraIndex() const` — Returns the camera index used for this pass. Returns [0..N) when using multi-camera rendering; otherwise INDEX_NONE.
- L108 _protected prototype_ `virtual UE::MovieGraph::DefaultRenderer::FCameraInfo GetRenderCameraInfo() const;` — Returns the camera info for the given camera index, forwarding this pass's camera source to the renderer.
- L111 _protected prototype_ `virtual float GetRenderCameraOverscan() const;` — Returns the overscan fraction for the given camera index, forwarding this pass's camera source to the renderer.
- L114 _protected prototype_ `virtual void CalculateProjectionMatrix(UE::MovieGraph::DefaultRenderer::FCameraInfo& InOutCameraInfo, FSceneViewProjectionData& InOutProjectionData, const FIntPoint InBackbufferResolution, const FIntPoint InAccumulatorResolution) const;` — Utility function for calculating a Projection Matrix (Orthographic or Perspective), and modify it based on the overscan percentage, aspect ratio, etc.
- L117 _protected prototype_ `virtual void ModifyProjectionMatrixForTiling(const UE::MovieGraph::DefaultRenderer::FMovieGraphTilingParams& InTilingParams, const bool bInOrthographic, FMatrix& InOutProjectionMatrix, float& OutDoFSensorScale) const;` — Utility function for modifying the projection matrix to match the given tiling parameters.
- L120 _protected prototype_ `virtual FVector4f CalculatePrinciplePointOffsetForTiling(const UE::MovieGraph::DefaultRenderer::FMovieGraphTilingParams& InTilingParams) const;` — Utility function for calculating the PrinciplePointOffset with the given tiling parameters. Used to make some effects (like vignette) work with tiling.
- L123 _protected prototype_ `virtual FSceneViewInitOptions CreateViewInitOptions(const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo, FSceneViewFamilyContext* InViewFamily, FSceneViewStateInterface* InViewStateInterface) const;` — Utility function for creating FSceneViewInitOptions based on the specified camera info.
- L134 _protected prototype_ `static void ReapplyOverscanPreservingEngineScaling( UE::MovieGraph::DefaultRenderer::FCameraInfo& InOutCameraInfo, float InOverscanMagnitude, const FIntPoint& InAccumulatorResolution, const FIntPoint& InOutputResolution);` — Reapplies an overscan magnitude to ViewInfo and enables engine-side view-rect scaling so the renderer supersamples for quality preservation. Note: The camera's bScaleResolutionWithOverscan is intentionally ignored to preserve offline render quality. Render passes should call this instead of ClearOverscan + ApplyOverscan directly because the raw pattern silently drops OverscanResolutionFraction.
- L141 _protected prototype_ `virtual FSceneViewInitOptions CreateViewInitOptions(const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo, FSceneViewFamilyContext* InViewFamily, FSceneViewStateReference& InViewStateRef) const;` — `UE_DEPRECATED(5.6, "Use the version which takes a FSceneViewStateInterface pointer instead.")`
- L144 _protected prototype_ `virtual FSceneView* CreateSceneView(const FSceneViewInitOptions& InInitOptions, TSharedRef<FSceneViewFamilyContext> InViewFamily, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const;` — Utility function for creating a FSceneView for the given InitOptions, Family, and Camera.
- L147 _protected prototype_ `virtual DefaultRenderer::FRenderTargetInitParams GetRenderTargetInitParams(const FMovieGraphTimeStepData& InTimeData, const FIntPoint& InResolution);` — Gets the render target init params that will be used when creating the render target.
- L149 _protected prototype_ `virtual void ApplyCameraManagerPostProcessBlends(FSceneView* InView, const FMinimalViewInfo& InViewInfo, bool bApplyCameraManagerPostProcessBlends) const;`
- L150 _protected prototype_ `virtual TSharedRef<FSceneViewFamilyContext> CreateSceneViewFamily(const FViewFamilyInitData& InInitData) const;`
- L151 _protected prototype_ `virtual void ApplyMovieGraphOverridesToSceneView(TSharedRef<FSceneViewFamilyContext> InOutFamily, const FViewFamilyInitData& InInitData, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const;`
- L152 _protected prototype_ `virtual void ApplyMovieGraphOverridesToViewFamily(TSharedRef<FSceneViewFamilyContext> InOutFamily, const FViewFamilyInitData& InInitData) const;`
- L153 _protected prototype_ `virtual void PostRendererSubmission(const UE::MovieGraph::FMovieGraphSampleState& InSampleState, const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InRenderTargetInitParams, FCanvas& InCanvas, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const;`
- L154 _protected prototype_ `virtual TFunction<void(TUniquePtr<FImagePixelData>&&)> MakeForwardingEndpoint(const FMovieGraphSampleState& InSampleState, const FMovieGraphTimeStepData& InTimeData);`
- L155 _protected function_ `virtual bool ShouldDiscardOutput(const TSharedRef<FSceneViewFamilyContext>& InFamily, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const`
- L156 _protected function_ `virtual void ApplyMovieGraphOverridesToSampleState(FMovieGraphSampleState& SampleState) const`
- L158 _protected function_ `virtual UMovieGraphImagePassBaseNode* GetParentNode(UMovieGraphEvaluatedConfig* InConfig) const` — For this image pass, look up the associated node by type for the given config.
- L161 _protected prototype_ `virtual TSharedRef<::MoviePipeline::IMoviePipelineAccumulationArgs> GetOrCreateAccumulator(TObjectPtr<UMovieGraphDefaultRenderer> InGraphRenderer, const FMovieGraphSampleState& InSampleState) const;` — Gets an accumulator that's in use for the provided sample state (or creates a new one), and returns the accumulator args that are in use.
- L164 _protected prototype_ `virtual FAccumulatorSampleFunc GetAccumulateSampleFunction() const;` — Gets the function that the accumulator will use to perform accumulation.
- L167 _protected member_ `TWeakObjectPtr<UMovieGraphDefaultRenderer> WeakGraphRenderer;`
- L179 _protected member_ `TSharedPtr<FMovieGraphRenderCameraSource> RenderCameraSource;` — Optional camera source shared among all FMovieGraphImagePassBase instances spawned by the same UMovieGraphRenderPassNode. The node creates at most one FMovieGraphRenderCameraSource and hands the same TSharedPtr to every pass instance it owns. Null when using default sequence cameras. FMovieGraphRenderCameraSource is a non-UObject, so the GC cannot trace into it. Each pass instance forwards AddReferencedObjects() to the shared source, so the source's UObject references are reported once per pass instance. Duplicate reports are safe; Unreal's GC handles them correctly.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MovieGraph` (scope `UE`)
- L15 _namespace_ `namespace Rendering` (scope `UE::MovieGraph`)
- L41 _prototype_ `void AccumulateSample_TaskThread(TUniquePtr<FImagePixelData>&& InPixelData, const TSharedRef<::UE::MovieGraph::FMovieGraphSampleState> InSampleState, const TSharedRef<::MoviePipeline::IMoviePipelineAccumulationArgs> InAccumulatorArgs);` (scope `UE::MovieGraph::Rendering`) — Forward Declare

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/Graph/Renderers/MovieGraphPathTracerPass.h` (Public)


#### struct `UE::MovieGraph::Rendering::FMovieGraphPathTracerPass`  
`struct FMovieGraphPathTracerPass : public FMovieGraphDeferredPass`  
_L10-16_
- inherits: `FMovieGraphDeferredPass`
- L12 _public prototype_ `virtual UMovieGraphImagePassBaseNode* GetParentNode(UMovieGraphEvaluatedConfig* InConfig) const override;`
- L13 _public prototype_ `virtual void ApplyMovieGraphOverridesToSceneView(TSharedRef<FSceneViewFamilyContext> InOutFamily, const FViewFamilyInitData& InInitData, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const override;`
- L14 _public prototype_ `virtual void ApplyMovieGraphOverridesToSampleState(FMovieGraphSampleState& SampleState) const override;`
- L15 _public prototype_ `virtual bool ShouldDiscardOutput(const TSharedRef<FSceneViewFamilyContext>& InFamily, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const override;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MovieGraph` (scope `UE`)
- L8 _namespace_ `namespace Rendering` (scope `UE::MovieGraph`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/MovieGraphImageSequenceOutputNode.h` (Public)


#### class `UMovieGraphImageSequenceOutputNode`  
`class UMovieGraphImageSequenceOutputNode : public UMovieGraphFileOutputNode`  
_L26-93_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMovieGraphFileOutputNode`
- desc: The UMovieGraphImageSequenceOutputNode node is the base class for all image sequence outputs, such as a series of jpeg, png, bmp, or .exr images. Create an instance of the appropriate class (such as UMovieGraphImageSequenceOutputNode_JPG) instead of this abstract base class.
- L30 _public prototype_ `UMovieGraphImageSequenceOutputNode();`
- L33 _public prototype_ `virtual void OnReceiveImageDataImpl(UMovieGraphPipeline* InPipeline, UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, const TSet<FMovieGraphRenderDataIdentifier>& InMask) override;` — UMovieGraphFileOutputNode Interface
- L34 _public prototype_ `virtual void OnAllFramesSubmittedImpl(UMovieGraphPipeline* InPipeline, TObjectPtr<UMovieGraphEvaluatedConfig>& InPrimaryJobEvaluatedGraph) override;`
- L35 _public prototype_ `virtual bool IsFinishedWritingToDiskImpl() const override;`
- L39 _public member_ `uint8 bOverride_OCIOConfiguration : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L42 _public member_ `uint8 bOverride_OCIOContext : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L52 _public member_ `FOpenColorIODisplayConfiguration OCIOConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", DisplayName="OCIO Configuration", meta = (EditCondition = "bOverride_OCIOConfiguration"))` — OCIO configuration/transform settings. Note: There are differences from the previous implementation in MRQ given that we are now doing CPU-side processing. 1) This feature only works on desktop platforms when the OpenColorIO library is available. 2) Users are now responsible for setting the renderer output space to Final Color (HDR) in Linear Working Color Space (SCS_FinalColorHDR).
- L62 _public member_ `TMap<FString, FString> OCIOContext;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", DisplayName = "OCIO Context", meta = (EditCondition = "bOverride_OCIOContext"))` — OCIO context of key-value string pairs, typically used to apply shot-specific looks (such as a CDL color correction, or a 1D grade LUT). Notes: 1) If a configuration asset base context was set, it remains active but can be overridden here with new key-values. 2) Format tokens such as {shot_name} are supported and will get resolved before submission.
- L66 _protected prototype_ `FString CreateFileName( UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, const UMovieGraphImageSequenceOutputNode* InParentNode, const UMovieGraphPipeline* InPipeline, const TPair<FMovieGraphRenderDataIdentifier, TUniquePtr<FImagePixelData>>& InRenderData, const EImageFormat InImageFormat, FMovieGraphResolveArgs& OutMergedFormatArgs, FString& OutFrameTemplatedFileName) const;` — Convenience function to create the output file name.
- L76 _protected prototype_ `FString GetFrameTemplatedFileName( const FMovieGraphFilenameResolveParams& InParams, const FString& InFileNameFormatString, FMovieGraphResolveArgs& OutMergedFormatArgs) const;` — Gets a "frame-number templated" filename (eg, Seq.Shot.{frame_placeholder}.exr) where '{frame_placeholder}' is used in place of the frame number.
- L83 _protected member_ `EImageFormat OutputFormat;` — The output format (as known used by the ImageWriteQueue) to output into.
- L86 _protected member_ `bool bQuantizeTo8Bit;` — Whether we enforce 8-bit depth on the output.
- L89 _protected member_ `IImageWriteQueue* ImageWriteQueue;` — A pointer to the image write queue used for asynchronously writing images
- L92 _protected member_ `TFuture<void> FinalizeFence;` — A fence to keep track of when the Image Write queue has fully flushed.

#### class `UMovieGraphImageSequenceOutputNode_EXR`  
`class UMovieGraphImageSequenceOutputNode_EXR : public UMovieGraphImageSequenceOutputNode, public IMovieGraphEvaluationNodeInjector`  
_L99-245_
- reflection: `UCLASS(MinimalAPI, meta=(PrioritizeCategories="EXR OCIO"))`
- inherits: `UMovieGraphImageSequenceOutputNode,IMovieGraphEvaluationNodeInjector`
- desc: Image sequence output node that can write single-layer EXR files.
- L104 _public function_ `UMovieGraphImageSequenceOutputNode_EXR()`
- L113 _public prototype_ `virtual void OnReceiveImageDataImpl(UMovieGraphPipeline* InPipeline, UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, const TSet<FMovieGraphRenderDataIdentifier>& InMask) override;`
- L116 _public function_ `virtual bool ShouldCropOverscanImpl() const override`
- L119 _public function_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override`
- L125 _public function_ `virtual FText GetKeywords() const override`
- L131 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L136 _public function_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override`
- L146 _public prototype_ `virtual void InjectNodesPostEvaluation(const FName& InBranchName, UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<UMovieGraphSettingNode*>& OutInjectedNodes) override;`
- L150 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L155 _public member_ `uint8 bOverride_Compression : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L158 _public member_ `uint8 bOverride_CompressionLevel : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L161 _public member_ `uint8 bOverride_LosslessCompression : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L164 _public member_ `uint8 bOverride_bEnableBurnIn : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L167 _public member_ `uint8 bOverride_BurnInClass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L170 _public member_ `uint8 bOverride_bCompositeOntoFinalImage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L173 _public member_ `uint8 bOverride_BurnInFileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L180 _public member_ `EEXRCompressionFormat Compression;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bOverride_Compression"), Category = "EXR")` — The type of compression the EXR file should be compressed with. This compression method will be applied to all layers unless the data in a layer has been flagged as needing lossless compression. See "Lossless Compression" for more details.
- L190 _public member_ `int32 CompressionLevel = 45;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bOverride_CompressionLevel", ClampMin="0", ClampMax="500", UIMin="0", UIMax="500"), Category = "EXR")` — The DWA quality level to use when the compression type is DWAA or DWAB. 0 - Visually lossless and maximum file size. 45 - Perceptually lossless. 100+ - Maximum compression and minimum file size.
- L197 _public member_ `EEXRCompressionFormat LosslessCompression;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bOverride_LosslessCompression", ValidEnumValues="None,RLE,ZIPS,ZIP,PIZ"), Category = "EXR")` — The type of lossless compression that should be used when a render pass is either forced to use lossless (eg, Object ID), or when the pass has been flagged to need lossless (eg, Post Process Material passes can opt-in to lossless).
- L201 _public member_ `bool bEnableBurnIn = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bEnableBurnIn"))` — If true, this output node will also generate a burn-in.
- L205 _public member_ `FSoftClassPath BurnInClass = FSoftClassPath(TEXT("/Mov` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Burn In", meta=(MetaClass="/Script/MovieRenderPipelineCore.MovieGraphBurnInWidget", EditCondition="bOverride_BurnInClass"))` — The widget that the burn-in should use.
- L209 _public member_ `bool bCompositeOntoFinalImage = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bCompositeOntoFinalImage"))` — If true, the burn-in that's generated will be composited onto this output. Otherwise, the burn-in will be written to a different file.
- L213 _public member_ `FString BurnInFileNameFormat = TEXT("{se` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_BurnInFileNameFormat", MrgTokenAutocomplete))` — The file name format used for writing out the burn-in image (if not composited).
- L220 _protected prototype_ `TUniquePtr<FEXRImageWriteTask> CreateImageWriteTask( FString InFileName, EEXRCompressionFormat InCompression, bool bMultiPart = false, int32 InCompressionLevel = 45 ) const;` — Convenience function to create a new EXR image write task, given a file name and compression format.
- L228 _protected prototype_ `void PrepareTaskGlobalMetadata( FEXRImageWriteTask& InOutImageTask, UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, TMap<FString, FString>& InMetadata ) const;` — Convenience function to prepare the image write task's global file metadata.
- L235 _protected prototype_ `void UpdateTaskPerLayer( FEXRImageWriteTask& InOutImageTask, const UMovieGraphImageSequenceOutputNode* InParentNode, TUniquePtr<FImagePixelData> InImageData, int32 InLayerIndex, const FString& InLayerName = {}, const TMap<FString, FString>& InResolvedOCIOContext = {} ) const;` — Convenience function to update the image write task for layer data.

#### class `UMovieGraphImageSequenceOutputNode_MultiLayerEXR`  
`class UMovieGraphImageSequenceOutputNode_MultiLayerEXR : public UMovieGraphImageSequenceOutputNode_EXR`  
_L252-372_
- reflection: `UCLASS(MinimalAPI, meta=(PrioritizeCategories="EXR OCIO"))`
- inherits: `UMovieGraphImageSequenceOutputNode_EXR`
- desc: Image sequence output node that can write multi-layer EXR files.
- L257 _public function_ `UMovieGraphImageSequenceOutputNode_MultiLayerEXR() : UMovieGraphImageSequenceOutputNode_EXR()`
- L264 _public function_ `virtual EMovieGraphBranchRestriction GetBranchRestriction() const override`
- L270 _public prototype_ `virtual void OnReceiveImageDataImpl(UMovieGraphPipeline* InPipeline, UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, const TSet<FMovieGraphRenderDataIdentifier>& InMask) override;`
- L273 _public function_ `virtual bool ShouldCropOverscanImpl() const override`
- L276 _public function_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override`
- L282 _public function_ `virtual FText GetBasicConfigShortDisplayName() const override`
- L287 _public function_ `virtual FText GetKeywords() const override`
- L293 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L298 _public function_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override`
- L306 _public function_ `virtual FText GetMenuCategory() const override`
- L313 _public prototype_ `virtual void InjectNodesPostEvaluation(const FName& InBranchName, UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<UMovieGraphSettingNode*>& OutInjectedNodes) override;`
- L317 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L336 _private prototype_ `void GetFilenameToEXROutputConfigMappings( const UMovieGraphImageSequenceOutputNode_MultiLayerEXR* InParentNode, UMovieGraphPipeline* InPipeline, UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, TMap<FString, FEXROutputConfigForFilename>& OutFilenameToOutputConfigs) const;` — Generates an output config for each filename, which consists of a list of render IDs, the resolve args that were created when resolving the filename, the frame-templated filenames (ie, filenames that have placeholders in the place of frame numbers), and the maximum resolution of all the layers written to the file, which will be used to pad out lower resolution layers so that they can all be in the same EXR file (when multi-part is not used).
- L345 _private prototype_ `FString ResolveOutputFilename( const UMovieGraphImageSequenceOutputNode_MultiLayerEXR* InParentNode, const UMovieGraphPipeline* InPipeline, const UE::MovieGraph::FMovieGraphOutputMergerFrame* InRawFrameData, const FMovieGraphRenderDataIdentifier& InRenderDataIdentifier, FMovieGraphResolveArgs& OutResolveArgs, FString& OutFrameTemplatedFilename) const;` — Generates the filename that the EXR will be written to, as well as the resulting resolve args via OutResolveArgs. Use GetFilenameToRenderIDMappings() to guarantee that the filename respects EXR limitations.
- L353 _public member_ `uint8 bOverride_bMultiPart : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L356 _public member_ `uint8 bOverride_BurnInLayerNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L367 _public member_ `bool bMultipart = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EXR", meta=(EditCondition="bOverride_bMultiPart"))` — Indicates whether the exr file should be written as a multi-part exr file, which supports having different image types and resolutions for each layer. Multi-part EXRs are a feature of EXR 2.0 and may not be supported by all software. If the console variable 'MoviePipeline.PadLayersForMultiPartEXR' is enabled, then all parts of the multi-part EXR will be padded to match the data window of the largest layer, as some software does not support different data window sizes. Note that multi-part will be forced on if layers are using more than one compression type (this can happen if rendering a beauty pass using lossy compression, and Object IDs using lossless compression, for example).
- L371 _public member_ `FString BurnInLayerNameFormat = TEXT("Bur` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (DisplayAfter = "BurnInClass", EditCondition = "bOverride_BurnInLayerNameFormat"))` — The layer name used for this burn-in inside of multi-layer EXRs.

#### struct `UMovieGraphImageSequenceOutputNode_MultiLayerEXR::FEXROutputConfigForFilename`  
`struct FEXROutputConfigForFilename`  
_L322-328_
- desc: Stores the EXR output config to use for a specific file name
- L324 _public member_ `TArray<FMovieGraphRenderDataIdentifier> RenderIDs;`
- L325 _public member_ `FMovieGraphResolveArgs ResolveArgs;`
- L326 _public member_ `FString FrameTemplatedFilename;`
- L327 _public member_ `FIntPoint MaximumResolution;`

#### class `UMovieGraphImageSequenceOutputNode_BMP`  
`class UMovieGraphImageSequenceOutputNode_BMP : public UMovieGraphImageSequenceOutputNode, public IMovieGraphEvaluationNodeInjector`  
_L380-462_
- reflection: `UCLASS(MinimalAPI, meta=(PrioritizeCategories="OCIO"))`
- inherits: `UMovieGraphImageSequenceOutputNode,IMovieGraphEvaluationNodeInjector`
- desc: Save the images generated by the Movie Graph Pipeline as an lossless 8 bit bmp format. This can be useful in rare occasions (bmp files are uncompressed but larger). sRGB is applied. No metadata is supported.
- L385 _public function_ `UMovieGraphImageSequenceOutputNode_BMP()`
- L392 _public function_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override`
- L401 _public function_ `virtual FText GetBasicConfigShortDisplayName() const override`
- L406 _public function_ `virtual FText GetKeywords() const override`
- L412 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L417 _public function_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override`
- L427 _public prototype_ `virtual void InjectNodesPostEvaluation(const FName& InBranchName, UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<UMovieGraphSettingNode*>& OutInjectedNodes) override;`
- L431 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L436 _public member_ `uint8 bOverride_bEnableBurnIn : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L439 _public member_ `uint8 bOverride_BurnInClass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L442 _public member_ `uint8 bOverride_bCompositeOntoFinalImage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L445 _public member_ `uint8 bOverride_BurnInFileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L449 _public member_ `bool bEnableBurnIn = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bEnableBurnIn"))` — If true, this output node will also generate a burn-in.
- L453 _public member_ `FSoftClassPath BurnInClass = FSoftClassPath(TEXT("/Mov` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Burn In", meta=(MetaClass="/Script/MovieRenderPipelineCore.MovieGraphBurnInWidget", EditCondition="bOverride_BurnInClass"))` — The widget that the burn-in should use.
- L457 _public member_ `bool bCompositeOntoFinalImage = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bCompositeOntoFinalImage"))` — If true, the burn-in that's generated will be composited onto this output. Otherwise, the burn-in will be written to a different file.
- L461 _public member_ `FString BurnInFileNameFormat = TEXT("{se` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_BurnInFileNameFormat", MrgTokenAutocomplete))` — The file name format used for writing out the burn-in image (if not composited).

#### class `UMovieGraphImageSequenceOutputNode_JPG`  
`class UMovieGraphImageSequenceOutputNode_JPG : public UMovieGraphImageSequenceOutputNode, public IMovieGraphEvaluationNodeInjector`  
_L471-553_
- reflection: `UCLASS(MinimalAPI, meta=(PrioritizeCategories="OCIO"))`
- inherits: `UMovieGraphImageSequenceOutputNode,IMovieGraphEvaluationNodeInjector`
- desc: Save the images generated by the Movie Graph Pipeline as an 8 bit jpg format. JPEG image files are lossy, but a good balance between compression speed and final filesize. sRGB is applied. No metadata is supported.
- L476 _public function_ `UMovieGraphImageSequenceOutputNode_JPG()`
- L483 _public function_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override`
- L492 _public function_ `virtual FText GetKeywords() const override`
- L498 _public function_ `virtual FText GetBasicConfigShortDisplayName() const override`
- L503 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L508 _public function_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override`
- L518 _public prototype_ `virtual void InjectNodesPostEvaluation(const FName& InBranchName, UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<UMovieGraphSettingNode*>& OutInjectedNodes) override;`
- L522 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L527 _public member_ `uint8 bOverride_bEnableBurnIn : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L530 _public member_ `uint8 bOverride_BurnInClass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L533 _public member_ `uint8 bOverride_bCompositeOntoFinalImage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L536 _public member_ `uint8 bOverride_BurnInFileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L540 _public member_ `bool bEnableBurnIn = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bEnableBurnIn"))` — If true, this output node will also generate a burn-in.
- L544 _public member_ `FSoftClassPath BurnInClass = FSoftClassPath(TEXT("/Mov` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Burn In", meta=(MetaClass="/Script/MovieRenderPipelineCore.MovieGraphBurnInWidget", EditCondition="bOverride_BurnInClass"))` — The widget that the burn-in should use.
- L548 _public member_ `bool bCompositeOntoFinalImage = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bCompositeOntoFinalImage"))` — If true, the burn-in that's generated will be composited onto this output. Otherwise, the burn-in will be written to a different file.
- L552 _public member_ `FString BurnInFileNameFormat = TEXT("{se` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_BurnInFileNameFormat", MrgTokenAutocomplete))` — The file name format used for writing out the burn-in image (if not composited).

#### class `UMovieGraphImageSequenceOutputNode_PNG`  
`class UMovieGraphImageSequenceOutputNode_PNG : public UMovieGraphImageSequenceOutputNode, public IMovieGraphEvaluationNodeInjector`  
_L561-645_
- reflection: `UCLASS(MinimalAPI, meta=(PrioritizeCategories="OCIO"))`
- inherits: `UMovieGraphImageSequenceOutputNode,IMovieGraphEvaluationNodeInjector`
- desc: Save the images generated by the Movie Graph Pipeline as an 8 bit png format. PNG image files are lossless but slow to compress and have a larger final filesize than JPEG. sRGB is applied. No metadata is supported.
- L566 _public function_ `UMovieGraphImageSequenceOutputNode_PNG()`
- L575 _public function_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override`
- L584 _public function_ `virtual FText GetKeywords() const override`
- L590 _public function_ `virtual FText GetBasicConfigShortDisplayName() const override`
- L595 _public function_ `virtual FLinearColor GetNodeTitleColor() const override`
- L600 _public function_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override`
- L610 _public prototype_ `virtual void InjectNodesPostEvaluation(const FName& InBranchName, UMovieGraphEvaluatedConfig* InEvaluatedConfig, TArray<UMovieGraphSettingNode*>& OutInjectedNodes) override;`
- L614 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L619 _public member_ `uint8 bOverride_bEnableBurnIn : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L622 _public member_ `uint8 bOverride_BurnInClass : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L625 _public member_ `uint8 bOverride_bCompositeOntoFinalImage : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L628 _public member_ `uint8 bOverride_BurnInFileNameFormat : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L632 _public member_ `bool bEnableBurnIn = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bEnableBurnIn"))` — If true, this output node will also generate a burn-in.
- L636 _public member_ `FSoftClassPath BurnInClass = FSoftClassPath(TEXT("/Mov` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Burn In", meta=(MetaClass="/Script/MovieRenderPipelineCore.MovieGraphBurnInWidget", EditCondition="bOverride_BurnInClass"))` — The widget that the burn-in should use.
- L640 _public member_ `bool bCompositeOntoFinalImage = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_bCompositeOntoFinalImage"))` — If true, the burn-in that's generated will be composited onto this output. Otherwise, the burn-in will be written to a different file.
- L644 _public member_ `FString BurnInFileNameFormat = TEXT("{se` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burn In", meta = (EditCondition = "bOverride_BurnInFileNameFormat", MrgTokenAutocomplete))` — The file name format used for writing out the burn-in image (if not composited).

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/MoviePipelineDeferredPasses.h` (Public)


#### struct `FMoviePipelinePostProcessPass`  
`struct FMoviePipelinePostProcessPass`  
_L19-53_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `bool bEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Additional passes add a significant amount of render time. May produce multiple output files if using Screen Percentage.
- L34 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (MrgTokenAutocomplete))` — An optional name which which will identify this material in the file name. For MRQ, the material name will be included in the {render_pass} token. For Movie Render Graph, the material name will be used in {renderer_sub_name}. If a name is not specified here, the full name of the material will be used in these tokens instead.
- L41 _public member_ `TSoftObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Material should be set to Post Process domain, and Blendable Location = After Tonemapping. This will need bDisableMultisampleEffects enabled for pixels to line up(ie : no DoF, MotionBlur, TAA)
- L45 _public member_ `bool bHighPrecisionOutput = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", DisplayName="Use High Precision (32-bit) Output")` — Request output to be 32-bit, usually for data exports. Note that scene color precision is still defined by r.SceneColorFormat.
- L52 _public member_ `bool bUseLosslessCompression = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Whether this pass should use lossless compression in formats that support it. Should usually be turned on for passes that need a highly accurate representation of the data (eg, depth).

#### class `UMoviePipelineDeferredPassBase`  
`class UMoviePipelineDeferredPassBase : public UMoviePipelineImagePassBase`  
_L56-231_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineImagePassBase`
- L61 _public prototype_ `UMoviePipelineDeferredPassBase();`
- L64 _public prototype_ `virtual void PostLoad() override;` — UObject Interface
- L69 _protected prototype_ `virtual void SetupImpl(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings) override;` — UMoviePipelineRenderPass API
- L70 _protected prototype_ `virtual void RenderSample_GameThreadImpl(const FMoviePipelineRenderPassMetrics& InSampleState) override;`
- L71 _protected prototype_ `virtual void OnTileStartImpl(FIntPoint TileIndexes) override;`
- L72 _protected prototype_ `virtual void OnTileEndImpl(FIntPoint TileIndexes) override;`
- L73 _protected prototype_ `virtual void TeardownImpl() override;`
- L75 _protected function_ `virtual FText GetDisplayText() const override`
- L77 _protected prototype_ `virtual void MoviePipelineRenderShowFlagOverride(FEngineShowFlags& OutShowFlag) override;`
- L78 _protected prototype_ `virtual void GatherOutputPassesImpl(TArray<FMoviePipelinePassIdentifier>& ExpectedRenderPasses) override;`
- L79 _protected function_ `virtual bool IsAntiAliasingSupported() const`
- L80 _protected function_ `virtual int32 GetOutputFileSortingOrder() const override`
- L81 _protected prototype_ `virtual FSceneViewStateInterface* GetSceneViewStateInterface(IViewCalcPayload* OptPayload = nullptr) override;`
- L82 _protected prototype_ `virtual FSceneViewStateInterface* GetExposureSceneViewStateInterface(IViewCalcPayload* OptPayload = nullptr, int32 CubeFaceIndex = INDEX_NONE) override;`
- L83 _protected prototype_ `virtual void AddViewExtensions(FSceneViewFamilyContext& InContext, FMoviePipelineRenderPassMetrics& InOutSampleState) override;`
- L84 _protected prototype_ `virtual bool IsAutoExposureAllowed(const FMoviePipelineRenderPassMetrics& InSampleState) const override;`
- L85 _protected prototype_ `virtual void BlendPostProcessSettings(FSceneView* InView, FMoviePipelineRenderPassMetrics& InOutSampleState, IViewCalcPayload* OptPayload = nullptr);`
- L86 _protected prototype_ `virtual UE::MoviePipeline::FImagePassCameraViewData GetCameraInfo(FMoviePipelineRenderPassMetrics& InOutSampleState, IViewCalcPayload* OptPayload = nullptr) const;`
- L90 _protected prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);` — FGCObject Interface
- L93 _protected prototype_ `TFunction<void(TUniquePtr<FImagePixelData>&&)> MakeForwardingEndpoint(const FMoviePipelinePassIdentifier InPassIdentifier, const FMoviePipelineRenderPassMetrics& InSampleState);`
- L94 _protected prototype_ `virtual void PostRendererSubmission(const FMoviePipelineRenderPassMetrics& InSampleState, const FMoviePipelinePassIdentifier InPassIdentifier, const int32 InSortingOrder, FCanvas& InCanvas);`
- L96 _protected prototype_ `virtual int32 GetNumCamerasToRender() const;`
- L97 _protected prototype_ `virtual int32 GetCameraIndexForRenderPass(const int32 InCameraIndex) const;`
- L98 _protected prototype_ `virtual FString GetCameraName(const int32 InCameraIndex) const;`
- L99 _protected prototype_ `virtual FString GetCameraNameOverride(const int32 InCameraIndex) const;`
- L101 _protected prototype_ `virtual FMoviePipelineRenderPassMetrics GetRenderPassMetricsForCamera(const int32 InCameraIndex, const FMoviePipelineRenderPassMetrics& InSampleState) const;`
- L104 _protected prototype_ `virtual FIntPoint GetEffectiveOutputResolutionForCamera(const int32 InCameraIndex) const;` — `UE_DEPRECATED(5.6, "GetEffectiveOutputResolutionForCamera is deprecated. Use GetOverscannedResolutionForCamera instead")`
- L105 _protected prototype_ `virtual FIntPoint GetOverscannedResolutionForCamera(const int32 InCameraIndex) const;`
- L106 _protected prototype_ `bool GetManualExposureEnabledForCamera(const int32 InCameraIndex) const;`
- L108 _protected prototype_ `bool IsUsingDataLayers() const;`
- L109 _protected prototype_ `int32 GetNumStencilLayers() const;`
- L110 _protected prototype_ `TArray<FString> GetStencilLayerNames() const;`
- L111 _protected prototype_ `bool IsActorInLayer(AActor* InActor, int32 InLayerIndex) const;`
- L112 _protected prototype_ `bool IsActorInAnyStencilLayer(AActor* InActor) const;`
- L113 _protected prototype_ `FSoftObjectPath GetValidDataLayerByIndex(const int32 InIndex) const;`
- L115 _protected prototype_ `bool CheckIfPathTracerIsSupported() const;`
- L116 _protected prototype_ `void PathTracerValidationImpl();`
- L118 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L122 _private prototype_ `FString GetNameForPostProcessMaterial(const UMaterialInterface* InMaterial);` — Gets the name for a post-process material (either the custom-specified name, or the material name).
- L131 _public member_ `bool bAccumulatorIncludesAlpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Should multiple temporal/spatial samples accumulate the alpha channel? This adds ~30% cost to the accumulation so you should not enable it unless necessary. You must delete both the sky and fog to ensure that they do not make all pixels opaque.
- L141 _public member_ `bool bDisableMultisampleEffects;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Processing")` — Certain passes don't support post-processing effects that blend pixels together. These include effects like Depth of Field, Temporal Anti-Aliasing, Motion Blur and chromattic abberation. When these post processing effects are used then each final output pixel is composed of the influence of many other pixels which is undesirable when rendering out an object id pass (which does not support post processing). This checkbox lets you disable them on a per-render basis instead of having to disable them in the editor as well.
- L149 _public member_ `bool bUse32BitPostProcessMaterials_DEPRECATED;` — `UE_DEPRECATED(5.5, "bUse32BitPostProcessMaterials has been deprecated, please use the setting per material.")` — `UPROPERTY()` — Should the additional post-process materials write out to a 32-bit render target instead of 16-bit?
- L156 _public member_ `TArray<FMoviePipelinePostProcessPass> AdditionalPostProcessMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deferred Renderer Data")` — An array of additional post-processing materials to run after the frame is rendered. Using this feature may add a notable amount of render time.
- L162 _public member_ `bool bRenderMainPass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stencil Clip Layers")` — This can be turned off if you're only doing a stencil-layer based render and don't need the main non-stencil approach.
- L170 _public member_ `bool bAddDefaultLayer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stencil Clip Layers")` — If true, an additional stencil layer will be rendered which contains all objects which do not belong to layers specified in the Stencil Layers. This is useful for wanting to isolate one or two layers but still have everything else to composite them over without having to remember to add all objects to a default layer.
- L179 _public member_ `TArray<FActorLayer> ActorLayers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stencil Clip Layers")` — For each layer in the array, the world will be rendered and then a stencil mask will clip all pixels not affected by the objects on that layer. This is NOT a true layer system, as translucent objects will show opaque objects from another layer behind them. Does not write out additional post-process materials per-layer as they will match the base layer. Only works with materials that can write to custom depth.
- L187 _public member_ `TArray<FSoftObjectPath> DataLayers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "/Script/Engine.DataLayerAsset"), Category = "Stencil Clip Layers")` — If the map you are working with is a World Partition map, you can specify Data layers instead of Actor Layers. If any Data Layers are specified, this will take precedence over any ActorLayers in this config. Does not affect whether or not the Data Layers are actually loaded, you must ensure layers are loaded for rendering.
- L192 _protected member_ `TArray<TObjectPtr<UMaterialInterface>> ActivePostProcessMaterials;` — `UPROPERTY(Transient, DuplicateTransient)` — While rendering, store an array of the non-null valid materials loaded from AdditionalPostProcessMaterials. Cleared on teardown.
- L195 _protected member_ `TSet<TObjectPtr<UMaterialInterface>> ActiveHighPrecisionPostProcessMaterials;` — `UPROPERTY(Transient, DuplicateTransient)`
- L198 _protected member_ `TObjectPtr<UMaterialInterface> StencilLayerMaterial;` — `UPROPERTY(Transient, DuplicateTransient)`
- L211 _protected member_ `TArray<FMultiCameraViewStateData> CameraViewStateData;`
- L214 _protected member_ `TOptional<int32> PreviousCustomDepthValue;` — Cache the custom stencil value. Only has meaning if they have stencil layers.
- L216 _protected member_ `TOptional<int32> PreviousDumpFramesValue;` — `UE_DEPRECATED(5.5, "PreviousDumpFramesValue has been deprecated.")`
- L218 _protected member_ `TOptional<int32> PreviousColorFormatValue;` — `UE_DEPRECATED(5.5, "PreviousColorFormatValue has been deprecated.")`
- L220 _protected member_ `TSharedPtr<FAccumulatorPool, ESPMode::ThreadSafe> AccumulatorPool;`
- L222 _protected member_ `TSharedPtr<FOpenColorIODisplayExtension, ESPMode::ThreadSafe> OCIOSceneViewExtension;` — The lifetime of this SceneViewExtension is only during the rendering process. It is destroyed as part of TearDown.
- L224 _public member_ `static FString StencilLayerMaterialAsset;`
- L225 _public member_ `static FString DefaultDepthAsset;`
- L226 _public member_ `static FString DefaultMotionVectorsAsset;`
- L230 _private member_ `TArray<FString> UniqueStencilLayerNames;` — Cached de-duplicated stencil layer names.

#### struct `UMoviePipelineDeferredPassBase::FMultiCameraViewStateData`  
`struct FMultiCameraViewStateData`  
_L200-209_
- L207 _public member_ `TMap<FIntPoint, FPerTile> TileData;`
- L208 _public member_ `TPimplPtr<FSceneViewStateSystemMemoryMirror> SystemMemoryMirror;`

#### struct `UMoviePipelineDeferredPassBase::FMultiCameraViewStateData::FPerTile`  
`struct FPerTile`  
_L202-205_
- L204 _public member_ `TArray<FSceneViewStateReference> SceneViewStates;`

#### class `UMoviePipelineDeferredPass_Unlit`  
`class UMoviePipelineDeferredPass_Unlit : public UMoviePipelineDeferredPassBase`  
_L236-255_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineDeferredPassBase`
- L241 _public function_ `UMoviePipelineDeferredPass_Unlit() : UMoviePipelineDeferredPassBase()`
- L246 _public function_ `virtual FText GetDisplayText() const override`
- L248 _public function_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override`
- L253 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`

#### class `UMoviePipelineDeferredPass_DetailLighting`  
`class UMoviePipelineDeferredPass_DetailLighting : public UMoviePipelineDeferredPassBase`  
_L258-278_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineDeferredPassBase`
- L263 _public function_ `UMoviePipelineDeferredPass_DetailLighting() : UMoviePipelineDeferredPassBase()`
- L268 _public function_ `virtual FText GetDisplayText() const override`
- L270 _public function_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override`
- L276 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`

#### class `UMoviePipelineDeferredPass_LightingOnly`  
`class UMoviePipelineDeferredPass_LightingOnly : public UMoviePipelineDeferredPassBase`  
_L281-301_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineDeferredPassBase`
- L286 _public function_ `UMoviePipelineDeferredPass_LightingOnly() : UMoviePipelineDeferredPassBase()`
- L291 _public function_ `virtual FText GetDisplayText() const override`
- L293 _public function_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override`
- L299 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`

#### class `UMoviePipelineDeferredPass_ReflectionsOnly`  
`class UMoviePipelineDeferredPass_ReflectionsOnly : public UMoviePipelineDeferredPassBase`  
_L304-323_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineDeferredPassBase`
- L309 _public function_ `UMoviePipelineDeferredPass_ReflectionsOnly() : UMoviePipelineDeferredPassBase()`
- L314 _public function_ `virtual FText GetDisplayText() const override`
- L316 _public function_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override`
- L322 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`

#### class `UMoviePipelineDeferredPass_PathTracer`  
`class UMoviePipelineDeferredPass_PathTracer : public UMoviePipelineDeferredPassBase`  
_L327-364_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineDeferredPassBase`
- L332 _public function_ `UMoviePipelineDeferredPass_PathTracer() : UMoviePipelineDeferredPassBase()`
- L337 _public function_ `virtual FText GetDisplayText() const override`
- L338 _public prototype_ `virtual FText GetFooterText(UMoviePipelineExecutorJob* InJob) const override;`
- L340 _public function_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const override`
- L347 _public function_ `virtual int32 GetOutputFileSortingOrder() const override`
- L349 _public function_ `virtual bool IsAntiAliasingSupported() const`
- L350 _public prototype_ `virtual void ValidateStateImpl() override;`
- L351 _public prototype_ `virtual void SetupImpl(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings) override;`
- L353 _public prototype_ `virtual TSharedPtr<FSceneViewFamilyContext> CalculateViewFamily(FMoviePipelineRenderPassMetrics& InOutSampleState, IViewCalcPayload* OptPayload) override;`
- L355 _public function_ `virtual bool NeedsFrameThrottle() const override`
- L356 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L363 _public member_ `bool bReferenceMotionBlur;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference Motion Blur")` — When enabled, the path tracer will blend all spatial and temporal samples prior to the denoising and will disable post-processed motion blur. In this mode it is possible to use higher temporal sample counts to improve the motion blur quality. When this option is disabled, the path tracer will accumulate spatial samples, but denoise them prior to accumulation of temporal samples.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/MoviePipelineEXROutput.h` (Public)


#### struct `UE::MoviePipeline::FEXRColorSpaceMetadata`  
`struct FEXRColorSpaceMetadata`  
_L36-41_
- desc: Collection of color space metadata for EXR.
- L38 _public member_ `FString SourceName;`
- L39 _public member_ `FString DestinationName;`
- L40 _public member_ `TArray<FVector2d> Chromaticities;`

#### enum `EEXRCompressionFormat`  
`enum class EEXRCompressionFormat : uint8`  
_L53-81_
- reflection: `UENUM(BlueprintType)`
- desc: Exr compression format options. Exactly matches the exr library Imf::Compression enum.
- L56 _public enumerator_ `None = 0` — No compression is applied.
- L58 _public enumerator_ `RLE = 1` — This compression method is fast, and works well for images with large flat areas but yields worse results for grainy images. Lossless.
- L60 _public enumerator_ `ZIPS = 2 UMETA(DisplayName = "ZIP (1 scanline)")` — This compression method is similar to ZIP but compresses only one image row at a time. Lossless.
- L62 _public enumerator_ `ZIP = 3 UMETA(DisplayName = "ZIP (16 scanlines)")` — Good compression quality for images with low amounts of noise. This compression method operates in in blocks of 16 scan lines. Lossless.
- L64 _public enumerator_ `PIZ = 4` — Good compression quality for grainy images. Lossless.
- L66 _public enumerator_ `PXR24 = 5` — This format only stores 24 bits of the 32 bit data and has subsequently a significant loss of precision. This method is only applied when saving in FLOAT color depth. HALF and UINT remain unchanged. Lossy.
- L68 _public enumerator_ `B44 = 6` — This compression method only applies to images stored in HALF color depth. Blocks of 4×4 pixels are stored with using only 14 byte each (instead of the 32 byte they would normally need). Each block is compressed to the exact same size. Different images with the same dimensions require the same storage space regardless of image content. Lossy.
- L70 _public enumerator_ `B44A = 7` — A modified version of B44. If all pixels in a 4*4 block have the same color it will use only 3 instead of 14 byte.
- L72 _public enumerator_ `DWAA = 8` — Lossy DCT-based compression for RGB channels. Alpha and other channels are uncompressed. More efficient than DWAB for partial buffer access on read in 3rd party tools.
- L74 _public enumerator_ `DWAB = 9` — Similar to DWAA but goes in blocks of 256 scanlines instead of 32. More efficient disk space and faster to decode than DWAA.
- L76 _public enumerator_ `HTJ2K256 = 10` — High-Throughput JPEG2000 (HTJ2K), 256 scanlines
- L78 _public enumerator_ `HTJ2K32 = 11` — High-Throughput JPEG2000 (HTJ2K), 32 scanlines
- L80 _public enumerator_ `Max UMETA(Hidden)`

#### class `FEXRImageWriteTask`  
`class FEXRImageWriteTask : public IImageWriteTaskBase`  
_L84-198_
- inherits: `IImageWriteTaskBase`
- L89 _public member_ `FString Filename;` — The filename to write to
- L92 _public member_ `bool bOverwriteFile;` — True if this task is allowed to overwrite an existing file, false otherwise.
- L98 _public member_ `EEXRCompressionFormat Compression;` — Compression method used for the resulting EXR files. Applies to all layers, but per-layer compression can be specified in `CompressionByLayer` if needed.
- L104 _public member_ `TArray<EEXRCompressionFormat> CompressionByLayer;` — Controls the compression per layer. Only used if `bMultiPart` is true. Takes precedence over `Compression`, but is ignored if this array is either empty, or its size does not match the number of layers given in `Layers`.
- L107 _public member_ `int32 CompressionLevel;` — DWA compression quality level used for DWAA/DWAB compression.
- L110 _public member_ `TFunction<void(bool)> OnCompleted;` — A function to invoke on the game thread when the task has completed
- L113 _public member_ `int32 Width;` — Width/Height of the image data. All samples should match this.
- L115 _public member_ `int32 Height;`
- L118 _public member_ `TMap<FString, FStringFormatArg> FileMetadata;` — A set of key/value pairs to write into the exr file as metadata.
- L121 _public member_ `TArray<TUniquePtr<FImagePixelData>> Layers;` — The image data to write. Supports multiple layers of different bitdepths.
- L124 _public member_ `TSortedMap<int32, TArray<FPixelPreProcessor>> PixelPreprocessors;` — Per-layer array of preprocessors to apply serially to the pixel data when this task is executed.
- L127 _public member_ `TMap<FImagePixelData*, FString> LayerNames;` — Optional. A mapping between the FImagePixelData and a name. The standard is that the default layer is nameless (at which point it would be omitted) and other layers are prefixed.
- L130 _public member_ `float OverscanPercentage;` — Overscan info used to create apropriate dataWindow for EXR output. Goes from 0.0 to 1.0.
- L133 _public member_ `FIntRect CropRectangle;` — Crop rectangle used to set the displayWindow for EXR output. Used to crop out overscan
- L136 _public member_ `TArray<FVector2d> ColorSpaceChromaticities;` — Color space chromaticity metadata.
- L139 _public member_ `bool bMultipart;` — Indicates if a multi-part file should be used, which allows each channel to have its own header and properties
- L142 _public member_ `bool bPadToDataWindowSize;` — Indicates that any layers that do not match the base resolution of the EXR file should be inflated with empty pixels to that resolution
- L144 _public function_ `FEXRImageWriteTask() : bOverwriteFile(true) , Compression(EEXRCompressionFormat::PIZ) , CompressionLevel(45) , OverscanPercentage(0.0f) , CropRectangle(FIntRect()) , bMultipart(true) , bPadToDataWindowSize(true)`
- L156 _public prototype_ `virtual bool RunTask() override final;`
- L157 _public prototype_ `virtual void OnAbandoned() override final;`
- L170 _private prototype_ `bool GenerateFilePartsForResolution(const FIntPoint& Resolution, const TArray<FImagePixelData*>& InLayers, const EEXRCompressionFormat CompressionType, const FString& InPartName, FEXRPart& OutPart, TArray<TUniquePtr<FImagePixelData>>& OutQuantizedLayers);` — Generates EXR file parts (header, framebuffer, etc) for the specified layers at the specified resolution
- L177 _private prototype_ `bool WriteToDisk();` — Run the task, attempting to write out the raw data using the currently specified parameters @return true on success, false on any failure
- L184 _private prototype_ `bool EnsureWritableFile();` — Ensures that the desired output filename is writable, deleting an existing file if bOverwriteFile is true @return True if the file is writable and the task can proceed, false otherwise
- L189 _private prototype_ `void AddFileMetadata(Imf::Header& InHeader);` — Adds arbitrary key/value pair metadata to the header of the file.
- L194 _private prototype_ `void PreProcess();` — Run over all the processors for the pixel data
- L197 _private prototype_ `template <Imf::PixelType OutputFormat> int64 CompressRaw(Imf::Header& InHeader, Imf::FrameBuffer& InFrameBuffer, FImagePixelData* InLayer);`

#### struct `FEXRImageWriteTask::FEXRPart`  
`struct FEXRPart`  
_L161-167_
- desc: EXR file parts and their metadata (scanline count, bytes written)
- L163 _public member_ `Imf::Header Header;`
- L164 _public member_ `Imf::FrameBuffer FrameBuffer;`
- L165 _public member_ `int32 Scanlines = 0;`
- L166 _public member_ `int64 BytesWritten = 0;`

#### class `UMoviePipelineImageSequenceOutput_EXR`  
`class UMoviePipelineImageSequenceOutput_EXR : public UMoviePipelineImageSequenceOutputBase`  
_L202-246_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMoviePipelineImageSequenceOutputBase`
- L207 _public function_ `virtual FText GetDisplayText() const override`
- L210 _public function_ `UMoviePipelineImageSequenceOutput_EXR()`
- L219 _public prototype_ `virtual void OnReceiveImageDataImpl(FMoviePipelineMergerOutputFrame* InMergedOutputFrame) override;`
- L221 _public function_ `virtual bool IsAlphaAllowed() const override`
- L222 _public function_ `virtual bool ShouldCropOverscanImpl() const override`
- L224 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L231 _public member_ `EEXRCompressionFormat Compression;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EXR")` — Which compression method should the resulting EXR file be compressed with
- L237 _public member_ `bool bMultilayer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EXR")` — Should we write all render passes to the same exr file? Not all software supports multi-layer exr files.
- L245 _public member_ `bool bMultipart;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EXR")` — Indicates whether the exr file should be written as a multi-part exr file, which supports having different image types and resolutions for each layer Multi-part exr files are a feature of EXR 2.0 and may not be supported by all software. If the console variable 'MoviePipeline.PadLayersForMultiPartEXR' is enabled, then all parts of the multi-part EXR will be padded to match the data window of the largest layer, as some software does not support different data window sizes.

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L30 _namespace_ `namespace MoviePipeline` (scope `UE`)
- L33 _externvar_ `extern TAutoConsoleVariable<bool> CVarMoviePipelinePadLayersForMultiPartEXR;` (scope `UE::MoviePipeline`) — CVar indicating if the EXR file writer is allowed to inflate layers of a lower resolution
- L44 _prototype_ `void UpdateColorSpaceMetadata(const FOpenColorIOColorConversionSettings& InConversionSettings, FEXRImageWriteTask& InOutImageTask);` (scope `UE::MoviePipeline`) — Update the image write task with color space metadata from the OpenColorIO transform.
- L47 _prototype_ `void UpdateColorSpaceMetadata(ESceneCaptureSource InSceneCaptureSource, FEXRImageWriteTask& InOutImageTask);` (scope `UE::MoviePipeline`) — Update the image write task with color space metadata from the render capture source mode.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/MoviePipelineImagePassBase.h` (Public)


#### struct `UE::MoviePipeline::FImagePassCameraViewData`  
`struct FImagePassCameraViewData`  
_L33-46_
- L35 _public function_ `FImagePassCameraViewData() : ViewActor(nullptr) , bUseCustomProjectionMatrix(false)`
- L40 _public member_ `FMinimalViewInfo ViewInfo;`
- L41 _public member_ `TMap<FString, FString> FileMetadata;`
- L42 _public member_ `AActor* ViewActor;`
- L44 _public member_ `bool bUseCustomProjectionMatrix;`
- L45 _public member_ `FMatrix CustomProjectionMatrix;`

#### class `FMoviePipelineBackgroundAccumulateTask`  
`class FMoviePipelineBackgroundAccumulateTask`  
_L50-73_
- L53 _public member_ `FGraphEventRef LastCompletionEvent;`
- L56 _public function_ `FGraphEventRef Execute(TUniqueFunction<void()> InFunctor)`
- L69 _public function_ `inline TStatId GetStatId() const`

#### struct `MoviePipeline::FLetterboxData`  
`struct FLetterboxData`  
_L78-105_
- desc: Describes the data required to clear the letterbox pixels outside the active pixel area
- L81 _public member_ `FIntRect FrameActiveArea;` — Active pixel area of the full frame within channel plane dimensions. i.e. Region not letterboxed
- L84 _public member_ `bool bDrawLetterboxBorder;` — True if letterboxing is active and drawing the border was deferred
- L87 _public member_ `int32 LeftSamplePixelsClearedBeforeAccumulation;` — Left sample pixels already cleared that should therefore not be sampled
- L90 _public member_ `int32 RightSamplePixelsClearedBeforeAccumulation;` — Right sample pixels already cleared that should therefore not be sampled
- L93 _public member_ `int32 TopSamplePixelsClearedBeforeAccumulation;` — Top sample pixels already cleared that should therefore not be sampled
- L96 _public member_ `int32 BottomSamplePixelsClearedBeforeAccumulation;` — Bottom sample pixels already cleared that should therefore not be sampled
- L98 _public function_ `FLetterboxData() : bDrawLetterboxBorder(false) , LeftSamplePixelsClearedBeforeAccumulation(0) , RightSamplePixelsClearedBeforeAccumulation(0) , TopSamplePixelsClearedBeforeAccumulation(0) , BottomSamplePixelsClearedBeforeAccumulation(0)`

#### struct `MoviePipeline::FImageSampleAccumulationArgs`  
`struct FImageSampleAccumulationArgs`  
_L107-116_
- L110 _public member_ `TWeakPtr<FImageOverlappedAccumulator, ESPMode::ThreadSafe> ImageAccumulator;`
- L111 _public member_ `TWeakPtr<IMoviePipelineOutputMerger, ESPMode::ThreadSafe> OutputMerger;`
- L112 _public member_ `bool bAccumulateAlpha;`
- L115 _public member_ `FLetterboxData LetterboxData;` — Contains the data needed for clearing the letterbox area

#### class `UMoviePipelineImagePassBase`  
`class UMoviePipelineImagePassBase : public UMoviePipelineRenderPass`  
_L123-202_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UMoviePipelineRenderPass`
- L128 _public function_ `UMoviePipelineImagePassBase() : UMoviePipelineRenderPass() , bAllowCameraAspectRatio(true)`
- L140 _protected prototype_ `virtual void OnFrameStartImpl() override;` — UMoviePipelineRenderPass API
- L141 _protected prototype_ `virtual void GatherOutputPassesImpl(TArray<FMoviePipelinePassIdentifier>& ExpectedRenderPasses) override;`
- L142 _protected prototype_ `virtual void SetupImpl(const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings) override;`
- L143 _protected prototype_ `virtual void RenderSample_GameThreadImpl(const FMoviePipelineRenderPassMetrics& InSampleState) override;`
- L144 _protected prototype_ `virtual void WaitUntilTasksComplete() override;`
- L145 _protected prototype_ `virtual void TeardownImpl() override;`
- L149 _protected prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);` — FGCObject Interface
- L152 _protected prototype_ `FVector4 CalculatePrinciplePointOffsetForTiling(const FMoviePipelineRenderPassMetrics& InSampleState) const;`
- L153 _protected prototype_ `virtual void ModifyProjectionMatrixForTiling(const FMoviePipelineRenderPassMetrics& InSampleState, const bool bInOrthographic, FMatrix& InOutProjectionMatrix, float& OutDoFSensorScale) const;`
- L155 _protected prototype_ `virtual FMatrix CalcCubeFaceTransform(ECubeFace Face) const final;`
- L158 _protected prototype_ `virtual void GetViewShowFlags(FEngineShowFlags& OutShowFlag, EViewModeIndex& OutViewModeIndex) const;`
- L159 _protected prototype_ `virtual TSharedPtr<FSceneViewFamilyContext> CalculateViewFamily(FMoviePipelineRenderPassMetrics& InOutSampleState, IViewCalcPayload* OptPayload = nullptr);`
- L160 _protected prototype_ `virtual void BlendPostProcessSettings(FSceneView* InView, FMoviePipelineRenderPassMetrics& InOutSampleState, IViewCalcPayload* OptPayload = nullptr);`
- L161 _protected prototype_ `virtual void SetupViewForViewModeOverride(FSceneView* View);`
- L162 _protected function_ `virtual void MoviePipelineRenderShowFlagOverride(FEngineShowFlags& OutShowFlag)`
- L163 _protected function_ `virtual bool IsScreenPercentageSupported() const`
- L164 _protected function_ `virtual bool IsAntiAliasingSupported() const`
- L165 _protected function_ `virtual int32 GetOutputFileSortingOrder() const`
- L166 _protected function_ `virtual FSceneViewStateInterface* GetSceneViewStateInterface(IViewCalcPayload* OptPayload = nullptr)`
- L167 _protected function_ `virtual FSceneViewStateInterface* GetExposureSceneViewStateInterface(IViewCalcPayload* OptPayload = nullptr, int32 CubeFaceIndex = INDEX_NONE)`
- L168 _protected function_ `virtual void AddViewExtensions(FSceneViewFamilyContext& InContext, FMoviePipelineRenderPassMetrics& InOutSampleState)`
- L169 _protected function_ `virtual bool IsAutoExposureAllowed(const FMoviePipelineRenderPassMetrics& InSampleState) const`
- L170 _protected prototype_ `virtual FSceneView* GetSceneViewForSampleState(FSceneViewFamily* ViewFamily, FMoviePipelineRenderPassMetrics& InOutSampleState, IViewCalcPayload* OptPayload = nullptr);`
- L171 _protected prototype_ `virtual UE::MoviePipeline::FImagePassCameraViewData GetCameraInfo(FMoviePipelineRenderPassMetrics& InOutSampleState, IViewCalcPayload* OptPayload = nullptr) const;`
- L173 _protected prototype_ `virtual TWeakObjectPtr<UTextureRenderTarget2D> GetOrCreateViewRenderTarget(const FIntPoint& InSize, IViewCalcPayload* OptPayload = nullptr);`
- L174 _protected prototype_ `virtual TSharedPtr<FMoviePipelineSurfaceQueue, ESPMode::ThreadSafe> GetOrCreateSurfaceQueue(const FIntPoint& InSize, IViewCalcPayload* OptPayload = nullptr);`
- L176 _protected prototype_ `virtual TWeakObjectPtr<UTextureRenderTarget2D> CreateViewRenderTargetImpl(const FIntPoint& InSize, IViewCalcPayload* OptPayload = nullptr) const;`
- L177 _protected prototype_ `virtual TSharedPtr<FMoviePipelineSurfaceQueue, ESPMode::ThreadSafe> CreateSurfaceQueueImpl(const FIntPoint& InSize, IViewCalcPayload* OptPayload = nullptr) const;`
- L180 _protected function_ `virtual UTextureRenderTarget2D* GetViewRenderTarget(IViewCalcPayload* OptPayload = nullptr) const` — `UE_DEPRECATED(5.1, "GetViewRenderTarget is deprecated, please use GetOrCreateViewRenderTarget")`
- L187 _protected member_ `TMap<FIntPoint, TWeakObjectPtr<UTextureRenderTarget2D>> TileRenderTargets;` — A temporary render target that we render the view to.
- L190 _protected member_ `FSceneViewStateReference ViewState;` — The history for the view
- L193 _protected member_ `TMap<FIntPoint, TSharedPtr<FMoviePipelineSurfaceQueue, ESPMode::ThreadSafe>> SurfaceQueues;` — A queue of surfaces that the render targets can be copied to. If no surface is available the game thread should hold off on submitting more samples.
- L196 _protected member_ `bool bAllowCameraAspectRatio;` — Some render passes may ignore the aspect ratio of the camera.
- L198 _protected member_ `FMoviePipelinePassIdentifier PassIdentifier;`
- L201 _protected member_ `FGraphEventArray OutstandingTasks;` — Accessed by the Render Thread when starting up a new task.

#### struct `UMoviePipelineImagePassBase::IViewCalcPayload`  
`struct IViewCalcPayload`  
_L136-136_
- desc: Dummy interface to allow classes with overriden functiosn to pass their own data around.

#### struct `FAccumulatorPool`  
`struct FAccumulatorPool : public TSharedFromThis<FAccumulatorPool>`  
_L204-237_
- inherits: `TSharedFromThis<FAccumulatorPool>`
- L226 _public prototype_ `virtual ~FAccumulatorPool() = default;`
- L228 _public member_ `TArray<TSharedPtr<FAccumulatorInstance, ESPMode::ThreadSafe>> Accumulators;`
- L229 _public member_ `FCriticalSection CriticalSection;`
- L232 _public prototype_ `TSharedPtr<FAccumulatorPool::FAccumulatorInstance, ESPMode::ThreadSafe> BlockAndGetAccumulator_GameThread(int32 InFrameNumber, const FMoviePipelinePassIdentifier& InPassIdentifier);`
- L235 _protected function_ `virtual TSharedPtr<FAccumulatorInstance, ESPMode::ThreadSafe> CreateNewAccumulatorInstance()`
- L236 _protected function_ `virtual FName GetPoolName() const`

#### struct `FAccumulatorPool::FAccumulatorInstance`  
`struct FAccumulatorInstance`  
_L206-224_
- L208 _public function_ `FAccumulatorInstance(TSharedPtr<MoviePipeline::IMoviePipelineOverlappedAccumulator, ESPMode::ThreadSafe> InAccumulator)`
- L216 _public prototype_ `bool IsActive() const;`
- L217 _public prototype_ `void SetIsActive(const bool bInIsActive);`
- L219 _public member_ `TSharedPtr<MoviePipeline::IMoviePipelineOverlappedAccumulator, ESPMode::ThreadSafe> Accumulator;`
- L220 _public member_ `int32 ActiveFrameNumber;`
- L221 _public member_ `FMoviePipelinePassIdentifier ActivePassIdentifier;`
- L222 _public member_ `FThreadSafeBool bIsActive;`
- L223 _public member_ `FGraphEventRef TaskPrereq;`

#### struct `TAccumulatorPool`  
`template<typename AccumulatorType> struct TAccumulatorPool : FAccumulatorPool`  
_L240-265_
- inherits: `FAccumulatorPool`
- L242 _public function_ `TAccumulatorPool(int32 InNumAccumulators) : FAccumulatorPool()`
- L255 _protected function_ `virtual TSharedPtr<FAccumulatorInstance, ESPMode::ThreadSafe> CreateNewAccumulatorInstance() override`
- L261 _protected function_ `virtual FName GetPoolName() const override`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`
- L29 _namespace_ `namespace UE`
- L31 _namespace_ `namespace MoviePipeline` (scope `UE`)
- L75 _namespace_ `namespace MoviePipeline`
- L118 _prototype_ `void AccumulateSample_TaskThread(TUniquePtr<FImagePixelData>&& InPixelData, const MoviePipeline::FImageSampleAccumulationArgs& InParams);` (scope `MoviePipeline`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/MoviePipelineImageSequenceOutput.h` (Public)


#### struct `UE::MoviePipeline::FAsyncImageQuantization`  
`struct FAsyncImageQuantization`  
_L19-32_
- L22 _public prototype_ `FAsyncImageQuantization(FImageWriteTask* InWriteTask, const bool bInConvertToSRGB);` — Constructor.
- L25 _public prototype_ `void operator()(FImagePixelData* PixelData);` — Process/quantize pixel data
- L28 _public member_ `FImageWriteTask* ParentWriteTask;` — Parent image write task.
- L31 _public member_ `bool bConvertToSRGB;` — True if the quantization should also apply an sRGB encoding.

#### class `UMoviePipelineImageSequenceOutputBase`  
`class UMoviePipelineImageSequenceOutputBase : public UMoviePipelineOutputBase`  
_L37-64_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UMoviePipelineOutputBase`
- L41 _public prototype_ `UMoviePipelineImageSequenceOutputBase();`
- L43 _public prototype_ `virtual void OnReceiveImageDataImpl(FMoviePipelineMergerOutputFrame* InMergedOutputFrame) override;`
- L47 _protected prototype_ `virtual void BeginFinalizeImpl() override;` — UMovieRenderPipelineOutputContainer interface
- L48 _protected prototype_ `virtual bool HasFinishedProcessingImpl() override;`
- L49 _protected prototype_ `virtual void OnShotFinishedImpl(const UMoviePipelineExecutorShot* InShot, const bool bFlushToDisk) override;`
- L52 _protected prototype_ `virtual void GetFormatArguments(FMoviePipelineFormatArgs& InOutFormatArgs) const override;`
- L53 _protected function_ `virtual bool IsAlphaAllowed() const`
- L56 _protected member_ `EImageFormat OutputFormat;` — The format of the image to write out
- L59 _protected member_ `IImageWriteQueue* ImageWriteQueue;` — A pointer to the image write queue used for asynchronously writing images
- L63 _private member_ `TFuture<void> FinalizeFence;` — A fence to keep track of when the Image Write queue has fully flushed.

#### class `UMoviePipelineImageSequenceOutput_BMP`  
`class UMoviePipelineImageSequenceOutput_BMP : public UMoviePipelineImageSequenceOutputBase`  
_L67-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMoviePipelineImageSequenceOutputBase`
- L72 _public function_ `virtual FText GetDisplayText() const override`
- L75 _public function_ `UMoviePipelineImageSequenceOutput_BMP()`
- L80 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`

#### class `UMoviePipelineImageSequenceOutput_PNG`  
`class UMoviePipelineImageSequenceOutput_PNG : public UMoviePipelineImageSequenceOutputBase`  
_L84-104_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMoviePipelineImageSequenceOutputBase`
- L89 _public function_ `virtual FText GetDisplayText() const override`
- L91 _public function_ `virtual bool IsAlphaAllowed() const override`
- L94 _public function_ `UMoviePipelineImageSequenceOutput_PNG()`
- L100 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L103 _public member_ `bool bWriteAlpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PNG")`

#### class `UMoviePipelineImageSequenceOutput_JPG`  
`class UMoviePipelineImageSequenceOutput_JPG : public UMoviePipelineImageSequenceOutputBase`  
_L107-121_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMoviePipelineImageSequenceOutputBase`
- L112 _public function_ `virtual FText GetDisplayText() const override`
- L115 _public function_ `UMoviePipelineImageSequenceOutput_JPG()`
- L120 _public prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`
- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MoviePipeline` (scope `UE`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineRenderPasses/Public/MoviePipelineWaveOutput.h` (Public)


#### class `UMoviePipelineWaveOutput`  
`class UMoviePipelineWaveOutput : public UMoviePipelineOutputBase`  
_L11-43_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoviePipelineOutputBase`
- L15 _private function_ `UMoviePipelineWaveOutput()`
- L21 _public function_ `virtual FText GetDisplayText() const override`
- L23 _public prototype_ `virtual void OnShotFinishedImpl(const UMoviePipelineExecutorShot* InShot, const bool bFlushToDisk) override;`
- L26 _protected prototype_ `virtual void BeginFinalizeImpl() override;`
- L27 _protected prototype_ `virtual bool HasFinishedProcessingImpl() override;`
- L28 _protected prototype_ `virtual void ValidateStateImpl() override;`
- L29 _protected prototype_ `virtual void BuildNewProcessCommandLineArgsImpl(TArray<FString>& InOutUnrealURLParams, TArray<FString>& InOutCommandLineArgs, TArray<FString>& InOutDeviceProfileCvars, TArray<FString>& InOutExecCmds) const override;`
- L30 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
- L35 _public member_ `FString FileNameFormatOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "File Output")` — File name format string override. If specified it will override the FileNameFormat from the Output setting.
- L39 _private member_ `TArray<TUniquePtr<Audio::FSoundWavePCMWriter>> ActiveWriters;` — Kept alive during finalization because the writer writes async to disk but doesn't expect to fall out of scope
- L42 _private member_ `TSet<FGuid> AlreadyWrittenSegments;` — Keep track of segments that we've already written to disk to avoid re-writing them (and generating new Output Futures)

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINERENDERPASSES_API`
