# Plugins / AccumulationDOF

- module root: `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF`
- headers: 15; symbols: 505
- symbol kinds: class=21, delegate=2, enum=6, enumerator=16, function=54, macro=2, member=225, namespace=6, prototype=156, struct=12, variable=5
- PrivateDependencyModuleNames: CoreUObject, Engine, ImageWriteQueue, MovieRenderPipelineRenderPasses, Projects, PropertyEditor, RHI, RenderCore, Renderer
- PublicDependencyModuleNames: CinematicCamera, Core, Engine, MovieRenderPipelineCore, Slate, SlateCore

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/MovieGraphAccumulationDOFModifier.h` (Private)


#### struct `FMovieGraphAccumulationDOFModifier_ComponentState`  
`struct FMovieGraphAccumulationDOFModifier_ComponentState`  
_L16-37_
- reflection: `USTRUCT()`
- desc: The state of an Accumulation DOF component before modification.
- L20 _public prototype_ `FMovieGraphAccumulationDOFModifier_ComponentState() = default;`
- L21 _public prototype_ `explicit FMovieGraphAccumulationDOFModifier_ComponentState(UAccumulationDOFComponent* InComponent);`
- L24 _public member_ `TWeakObjectPtr<UAccumulationDOFComponent> DOFComponent;` — The Accumulation DOF component that the below cached state is for.
- L27 _public member_ `bool bEnableAccumulationDepthOfField = false;` — The original enable/disable state of the Accumulation DOF component.
- L30 _public member_ `int32 NumSamples = 0;` — The original number of samples set on the Accumulation DOF component.
- L33 _public member_ `float DOFSplatSize = 0.f;` — The original splat size set on the Accumulation DOF component.
- L36 _public member_ `bool bComponentWasAdded = false;` — True if ApplyModifier created this component; UndoModifier will destroy it.

#### class `UMovieGraphAccumulationDOFModifier`  
`class UMovieGraphAccumulationDOFModifier final : public UMovieGraphModifierBase`  
_L43-85_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieGraphModifierBase`
- desc: Updates all Accumulation DOF components within the world to the settings specified on this modifier.
- L48 _public prototype_ `UMovieGraphAccumulationDOFModifier() = default;`
- L51 _public prototype_ `virtual void ApplyModifier(const UWorld* World) override;`
- L52 _public prototype_ `virtual void UndoModifier() override;`
- L53 _public prototype_ `virtual FText GetModifierName() override;`
- L59 _public member_ `bool bOverride_EnableDOFComponents = false;` — `UPROPERTY()` — Whether "EnableDOFComponents" state should be applied.
- L63 _public member_ `bool bOverride_NumSamples = false;` — `UPROPERTY()` — Whether "NumSamples" state should be applied.
- L67 _public member_ `bool bOverride_DOFSplatSize = false;` — `UPROPERTY()` — Whether "DOFSplatSize" state should be applied.
- L71 _public member_ `FMovieGraphAccumulationDOFEnableState EnableDOFComponents;` — `UPROPERTY()` — The enable/disable state of the Accumulation DOF component.
- L75 _public member_ `int32 NumSamples = 0;` — `UPROPERTY()` — The number of samples that the Accumulation DOF component should use.
- L79 _public member_ `float DOFSplatSize = 0.f;` — `UPROPERTY()` — The splat size that the Accumulation DOF component should use.
- L84 _private member_ `TArray<FMovieGraphAccumulationDOFModifier_ComponentState> OriginalComponentState;` — `UPROPERTY(Transient)` — Tracks the original component state before the modifier was applied.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ACCUMULATIONDOF_API`

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/MovieGraphAccumulationDOFModifierCustomization.h` (Private)


#### class `FMovieGraphAccumulationDOFModifierCustomization`  
`class FMovieGraphAccumulationDOFModifierCustomization final : public IDetailCustomization`  
_L12-25_
- inherits: `IDetailCustomization`
- desc: Customize how the Accumulation DOF modifier node appears in the details panel.
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L19 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override;`
- L24 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailBuilder;` — The details builder associated with the customization.

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Rendering/AccumulationDOFSceneViewExtension.h` (Private)


#### enum `EAccumulationDOFSVEMode`  
`enum class EAccumulationDOFSVEMode : uint8`  
_L17-27_
- desc: Operating mode for the AccumulationDOF Scene View Extension
- L20 _public enumerator_ `Capture` — Extract scene color at MotionBlur pass to external render target
- L23 _public enumerator_ `Inject` — Replace scene color at MotionBlur pass with accumulated texture
- L26 _public enumerator_ `InjectViaTemporalUpscaler` — Replace scene color before motion blur via temporal upscaler hook

#### struct `FAccumulationDOFSVESettings`  
`struct FAccumulationDOFSVESettings`  
_L32-41_
- desc: Settings for FAccumulationDOFSceneViewExtension to apply camera post-process settings.
- L35 _public member_ `TWeakObjectPtr<UCineCameraComponent> CineCameraComponent;` — CineCameraComponent to get post-process settings from during SetupView()
- L40 _public prototype_ `static FAccumulationDOFSVESettings FromCineCameraComponent(UCineCameraComponent* CineCamera);` — Create settings from a CineCameraComponent.

#### class `FAccumulationDOFSceneViewExtension`  
`class FAccumulationDOFSceneViewExtension : public ISceneViewExtension, public TSharedFromThis<FAccumulationDOFSceneViewExtension, ESPMode::ThreadSafe>`  
_L53-203_
- inherits: `ISceneViewExtension,TSharedFromThis<FAccumulationDOFSceneViewExtension,ESPMode::ThreadSafe>`
- desc: Scene View Extension for AccumulationDOF that hooks into post-processing. The extension operates in three modes (see EAccumulationDOFSVEMode): - Capture: extracts scene color at the MotionBlur pass to an external render target - Inject: replaces scene color at the MotionBlur pass with accumulated texture - InjectViaTemporalUpscaler: replaces scene color before motion blur via temporal upscaler hook This SVE is designed to be created fresh for each capture and added to the SVE array.
- L64 _public prototype_ `explicit FAccumulationDOFSceneViewExtension( UTextureRenderTarget2D* InRenderTarget, EAccumulationDOFSVEMode InMode, const FAccumulationDOFSVESettings& InSettings = FAccumulationDOFSVESettings() );` — @param InRenderTarget - The render target (dst in Capture mode, src in Inject modes) @param InMode         - The operating mode @param InSettings     - Optional camera/post-process settings (empty = no PP override)
- L70 _public prototype_ `virtual ~FAccumulationDOFSceneViewExtension() = default;`
- L74 _public function_ `virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override`
- L75 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L76 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L78 _public prototype_ `virtual void SubscribeToPostProcessingPass( EPostProcessingPass Pass, const FSceneView& View, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled) override;`
- L84 _public function_ `virtual int32 GetPriority() const override`
- L92 _public function_ `EAccumulationDOFSVEMode GetMode() const` — Get the current operating mode
- L106 _public prototype_ `void SetDOFSplatsSettings(float InFStop, float InFocusDistanceCm, float InSensorWidthMm, float InSqueezeFactor, bool bInForceNeutralBokeh = false);` — Set DOFSplats parameters for the current sample. @param InFStop              - FStop for DOFSplats (0 = disabled) @param InFocusDistanceCm    - Focus distance in cm @param InSensorWidthMm      - Sensor width in mm @param InSqueezeFactor      - Anamorphic squeeze factor @param bInForceNeutralBokeh - If true, forces petzval=0, circular aperture, and no cat's eye
- L113 _public function_ `void SetAllowSceneFringe(bool bAllow)` — Set whether to allow SceneFringe (lateral chromatic aberration) in post-process. When true, engine's SceneFringe will apply during post-processing. When false, SceneFringeIntensity is forced to 0.
- L124 _public function_ `void SetProgressBar(float InProgress)` — Set progress bar parameters for preview mode. When enabled, draws a progress bar overlay at the bottom of the frame during injection. @param InProgress - Progress fraction (0.0 to 1.0)
- L131 _public function_ `float GetProgressBarFraction() const` — Get progress bar fraction
- L137 _public function_ `bool ShouldDrawProgressBar() const` — Check if progress bar should be drawn
- L143 _public function_ `float GetCapturedSceneFringeIntensity() const` — Get the final blended SceneFringeIntensity value captured during SetupView()
- L155 _private prototype_ `FScreenPassTexture ProcessAtMotionBlurPass_RenderThread( FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs);` — Callback for the MotionBlur post-processing pass (@todo possibly move to before) In Capture mode: copies scene color to target RT In Inject mode: replaces scene color with accumulated texture
- L161 _private member_ `EAccumulationDOFSVEMode Mode;` — Operating mode
- L164 _private member_ `TWeakObjectPtr<UTextureRenderTarget2D> RenderTarget;` — The render target - destination in Capture mode, source in Inject mode
- L167 _private member_ `FAccumulationDOFSVESettings Settings;` — Settings for camera post-process override (populated at construction)
- L174 _private member_ `float DOFSplatsFStop = 0.0f;` — DOFSplats f-stop for current sample (0 = disabled)
- L177 _private member_ `float DOFSplatsFocusDistanceCm = 0.0f;` — Focus distance for DOFSplats in cm
- L180 _private member_ `float DOFSplatsSensorWidthMm = 0.0f;` — Sensor width for DOFSplats in mm
- L183 _private member_ `float DOFSplatsSqueezeFactor = 1.0f;` — Squeeze factor for DOFSplats
- L186 _private member_ `bool bDOFSplatsForceNeutralBokeh = false;` — If true, force neutral bokeh: petzval=0, circular aperture, no cat's eye
- L189 _private member_ `bool bAllowSceneFringe = false;` — Whether to allow SceneFringe (lateral chromatic aberration) in post-process or not.
- L196 _private member_ `float ProgressBarFraction = 0.0f;` — Progress bar fraction (0.0 to 1.0)
- L199 _private member_ `bool bDrawProgressBar = false;` — Whether to draw progress bar overlay during injection
- L202 _private member_ `float CapturedSceneFringeIntensity = 0.0f;` — Captured SceneFringeIntensity from the final blended PP settings in SetupView()

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Rendering/AccumulationDOFTemporalUpscaler.h` (Private)


#### class `FAccumulationDOFTemporalUpscaler`  
`class FAccumulationDOFTemporalUpscaler : public UE::Renderer::Private::ITemporalUpscaler`  
_L20-101_
- inherits: `UE::Renderer::Private::ITemporalUpscaler`
- desc: Custom temporal upscaler that injects the accumulated AccumulationDOF result before motion blur runs. This allows motion blur to be applied to the accumulated depth of field result. We do it like this because there currently isn´t a "BeforeMotionBlur" SVE callback available. The samples themselves can still use an upscaler, but since we're injecting an accumulation and discard the upscaler render, it doesn't affect the output.
- L59 _public function_ `static const TCHAR* GetUpscalerDebugName()` — Debug name
- L64 _public prototype_ `FAccumulationDOFTemporalUpscaler(TRefCountPtr<FRHITexture> InAccumulatedRHITexture, float InProgressBarFraction = -1.0f);`
- L66 _public prototype_ `virtual ~FAccumulationDOFTemporalUpscaler() = default;`
- L69 _public function_ `virtual const TCHAR* GetDebugName() const override` — ITemporalUpscaler interface
- L77 _public prototype_ `virtual FOutputs AddPasses( FRDGBuilder& GraphBuilder, const FSceneView& View, const FInputs& Inputs) const override;` — Add the injection pass to the render graph.
- L82 _public function_ `virtual float GetMinUpsampleResolutionFraction() const override`
- L87 _public function_ `virtual float GetMaxUpsampleResolutionFraction() const override`
- L92 _public prototype_ `virtual ITemporalUpscaler* Fork_GameThread(const class FSceneViewFamily& ViewFamily) const override;`
- L97 _private member_ `TRefCountPtr<FRHITexture> AccumulatedRHITexture;` — Accumulated RT, for render thread access
- L100 _private member_ `float ProgressBarFraction;` — Progress bar fraction (0-1), or negative to disable

#### class `FAccumulationDOFTemporalUpscaler::FHistory`  
`class FHistory : public IHistory, public TRefCountingMixin<FHistory>`  
_L29-56_
- inherits: `IHistory,TRefCountingMixin<FHistory>`
- desc: History object required by the ITemporalUpscaler interface. Required for interface (GetDebugName must match upscaler), but we don't store temporal state since we inject an already accumulated buffer.
- L32 _public function_ `virtual const TCHAR* GetDebugName() const override`
- L37 _public function_ `virtual uint64 GetGPUSizeBytes() const override`
- L42 _public function_ `virtual void AddRef() const override`
- L47 _public function_ `virtual FReturnedRefCountValue Release() const override`
- L52 _public function_ `virtual FReturnedRefCountValue GetRefCount() const override`

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Rendering/ApertureSampler.h` (Private)


#### enum `AccumulationDOF::EApertureSamplerMode`  
`enum class EApertureSamplerMode : uint8`  
_L32-42_
- desc: Rendering mode for aperture sampling.
- L35 _public enumerator_ `OneShot` — Render all samples in one blocking call.
- L41 _public enumerator_ `Amortized` — Spread samples across multiple frames. Used in preview mode to not block the Engine. However if the scene has motion then they will smear the accumulation.

#### struct `AccumulationDOF::FApertureSamplerConfig`  
`struct FApertureSamplerConfig`  
_L47-198_
- desc: Configuration for aperture sampling.
- L50 _public member_ `FIntPoint Resolution = FIntPoint(1920, 1080);` — Output resolution
- L53 _public member_ `TWeakObjectPtr<UWorld> World;` — Reference to the world for rendering.
- L60 _public member_ `int32 NumSamples = 256;` — Number of aperture samples requested. Actual count may differ for Ring pattern.
- L63 _public member_ `EApertureSamplingPattern SamplingPattern = EApertureSamplingPattern::Hexaweb;` — Sampling pattern (Halton, Hexaweb, Vogel).
- L66 _public member_ `EApertureSamplerMode Mode = EApertureSamplerMode::OneShot;` — Rendering mode (OneShot vs Amortized).
- L69 _public member_ `int32 SamplesPerFrame = 1;` — Number of samples to render per frame in amortized mode
- L76 _public member_ `bool bUseJitterAA = true;` — Use Halton jitter AA instead of per-sample TAA.
- L86 _public member_ `float DOFSplatSize = 0.125f;` — Fraction of main aperture diameter for DOF splat size (0.125 = 1/8th, 0 = disabled). Smaller values fill less but produce sharper bokeh edges.
- L93 _public member_ `float AxialChromaticAberrationIntensity = 0.0f;` — Axial CA intensity as percentage of focus distance.
- L96 _public member_ `int32 AxialChromaticAberrationNumBands = 6;` — Number of spectral bands for axial CA (3-19).
- L99 _public member_ `bool bSpectralLateralChromaticAberration = true;` — Multi-band spectral lateral CA instead of engine's simple RGB split.
- L106 _public member_ `float SphericalAberration = 0.0f;` — Primary spherical aberration coefficient (Seidel W040) in cm.
- L109 _public member_ `float ComaAberration = 0.0f;` — Coma aberration strength (Seidel W131). Normalized and scaled by 0.1 before passing to shader.
- L116 _public member_ `TObjectPtr<UTexture2D> BokehTexture = nullptr;` — Custom bokeh texture for aperture weighting.
- L119 _public member_ `bool bEnableBokehTexture = true;` — Enable bokeh texture weighting.
- L122 _public member_ `EBokehWeightChannel WeightChannel = EBokehWeightChannel::Luminance;` — Which channel to use for bokeh weight (luminance or alpha channel).
- L125 _public member_ `float TintStrength = 0.0f;` — Strength of bokeh tint (0-1).
- L128 _public member_ `float BokehEdgeSoftness = 0.15f;` — Bokeh edge softness (0 = hard, 1 = very soft).
- L135 _public member_ `bool bEnableMedianFilter = true;` — Enable median filter after accumulation.
- L138 _public member_ `int32 MedianFilterIterations = 1;` — Number of median filter iterations.
- L145 _public member_ `ETemporalHistoryMode TemporalHistoryMode = ETemporalHistoryMode::LastSampleOnly;` — Controls which samples update temporal history.
- L152 _public member_ `TEnumAsByte<ESceneCaptureSource> PostProcessOutputFormat = ESceneCaptureSource::SCS_FinalToneCurveHDR;` — Output format for post-processed result.
- L161 _public member_ `float OverscanFraction = 0.0f;` — Overscan as a normalized fraction in [0,1] range (0.0 = none, 1.0 = 100% overscan).
- L167 _public member_ `float ScreenPercentage = -1.0f;` — Screen percentage fraction (0.1 to 4.0, where 1.0 = 100%). Negative value means use r.ScreenPercentage
- L174 _public member_ `EViewModeIndex ViewModeIndex = VMI_Lit;` — View mode for rendering (Lit, Detail Lighting, Lighting Only, Reflections).
- L181 _public member_ `bool bSaveIntermediateSamples = false;` — Save intermediate sample images to disk.
- L184 _public member_ `bool bSaveFinalAccumulation = false;` — Save final accumulated image to disk.
- L187 _public member_ `FString OutputDirectory;` — Output directory for saved images.
- L190 _public member_ `FString OutputFilenamePrefix;` — Output filename prefix.
- L197 _public member_ `FSceneViewStateInterface* ExposureViewState = nullptr;` — Optional view state for exposure calculations (shares exposure history with another view)

#### struct `AccumulationDOF::FApertureSamplerCameraState`  
`struct FApertureSamplerCameraState`  
_L204-220_
- desc: Per-frame camera state needed for rendering. Updated each frame or when camera parameters change.
- L207 _public member_ `TWeakObjectPtr<UCineCameraComponent> CineCameraComponent;` — CineCameraComponent to read parameters from.
- L210 _public member_ `FVector CameraLocation = FVector::ZeroVector;` — Camera world location.
- L213 _public member_ `FRotator CameraRotation = FRotator::ZeroRotator;` — Camera world rotation.
- L216 _public member_ `float SceneFringeIntensity = 0.0f;` — Captured SceneFringeIntensity from blended post-process settings. Cached because we replace lateral CA
- L219 _public member_ `bool bInitialized = false;` — Initialization state

#### struct `AccumulationDOF::FApertureSamplerProgress`  
`struct FApertureSamplerProgress`  
_L225-259_
- desc: Progress information for the sampling operation.
- L228 _public member_ `int32 CurrentIteration = 0;` — Current sample index being rendered
- L231 _public member_ `int32 TotalIterations = 0;` — Total number of iterations to render
- L236 _public member_ `int32 ActualNumSamples = 0;` — Actual number of aperture samples.
- L239 _public member_ `bool bComplete = false;` — Whether accumulation is complete or not.
- L242 _public member_ `bool bWasCancelled = false;` — Whether the operation was cancelled by user.
- L245 _public function_ `float GetProgressFraction() const` — Progress as a fraction [0, 1].
- L251 _public function_ `FString GetProgressString() const` — For progress display

#### class `UApertureSampler`  
`class UApertureSampler : public UObject`  
_L277-751_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Encapsulates the aperture sampling pipeline. This class manages the entire lifecycle of aperture-sampled rendering. Can render one-shot (blocking) or amortized.
- L282 _public prototype_ `UApertureSampler();`
- L293 _public prototype_ `bool Initialize(const AccumulationDOF::FApertureSamplerConfig& InConfig, const AccumulationDOF::FApertureSamplerCameraState& InCameraState);` — Initialize the sampler with configuration and camera state. Allocates render targets and generates aperture sample positions. @param InConfig      - Configuration for sampling behavior @param InCameraState - Initial camera state @return true if initialization succeeded
- L298 _public function_ `bool IsInitialized() const` — Check if the sampler is properly initialized and ready to render.
- L306 _public prototype_ `void Shutdown();` — Release all resources and reset state.
- L317 _public prototype_ `bool UpdateCameraState(const AccumulationDOF::FApertureSamplerCameraState& InCameraState);` — Update camera state for the current frame. Call this before RenderAmortizedSamples() in amortized mode. Detects significant changes and resets accumulation if needed. @param InCameraState - New camera state @return true if accumulation was reset due to significant changes
- L322 _public prototype_ `void ResetAccumulation();` — Force-reset accumulation (use when user clicks on Recapture button because the scene or a setting changed).
- L327 _public function_ `const AccumulationDOF::FApertureSamplerConfig& GetConfig() const` — Get the current configuration.
- L335 _public function_ `int32 GetActualNumSamples() const` — Get the actual number of samples (may differ from requested if the pattern requires it)
- L345 _public prototype_ `bool RenderAllSamples();` — Render all aperture samples in a blocking fashion. @return true if rendering succeeded
- L356 _public prototype_ `bool RenderAmortizedSamples();` — Render one frame's worth of samples (SamplesPerFrame). @return true if samples were rendered (false if complete or error)
- L361 _public function_ `bool IsComplete() const` — @return true if amortized accumulation is complete.
- L376 _public function_ `UTextureRenderTarget2D* GetAccumulatedResult() const` — Get the final accumulated result (after normalization and post-processing). Valid after RenderAllSamples() or when IsComplete() returns true. @return Accumulated render target (AccumA), or nullptr if not ready
- L388 _public prototype_ `UTextureRenderTarget2D* PreparePreviewTexture();` — Prepare and return the texture ready for preview/injection. Always returns PrefilterRT with normalized data copied/prepared into it. Call this from the game thread before injection. @return Normalized texture suitable for display, or nullptr if not ready
- L394 _public function_ `UTextureRenderTarget2D* GetPrefilterResult() const` — Get the pre-filter accumulated result (before median filter applied during finalization). Useful for re-filtering with different settings.
- L402 _public function_ `UTextureRenderTarget2D* GetSampleRT() const` — Get the sample render target (where individual samples are rendered).
- L410 _public function_ `UTextureRenderTarget2D* GetAccumA() const` — Get ping-pong accumulation buffer A
- L418 _public function_ `UTextureRenderTarget2D* GetAccumB() const` — Get ping-pong accumulation buffer B
- L429 _public prototype_ `void CopyToOutput(UTextureRenderTarget2D* OutputRT, bool bDrawProgress = false);` — Copy current normalized result to an external render target. @param OutputRT        Target render target @param bDrawProgress   Draw progress bar overlay (for preview)
- L440 _public prototype_ `void CopyToOutputCropped( UTextureRenderTarget2D* OutputRT, const FVector2f& SourceUVMin, const FVector2f& SourceUVMax, bool bDrawProgress = false );` — Copy current normalized result to an external render target with cropping. Used when overscan needs to be cropped from the output. @param OutputRT       Target render target (should already be sized to cropped dimensions) @param SourceUVMin    Minimum UV coordinates of source region to copy @param SourceUVMax    Maximum UV coordinates of source region to copy @param bDrawProgress  Draw progress bar overlay (for preview)
- L459 _public prototype_ `bool RenderWithPostProcessing( UTextureRenderTarget2D* OutputRT, bool bAllowSceneFringe = false, float ProgressBarFraction = -1.0f, float Overscan = 0.0f );` — Render with post-processing injection. Injects the accumulated result at MotionBlur pass, then captures with the following post process applied. If Overscan > 0, post-processes at internal resolution then crops to output. @param OutputRT            - Target render target for post-processed result @param bAllowSceneFringe   - Whether to allow engine's SceneFringe (lateral CA) @param ProgressBarFraction - Progress bar value (0-1), negative to disable @param Overscan            - Overscan fraction (e.g. 0.1 for 10%), 0 for no cropping @return true if rendering succeeded
- L469 _public function_ `const AccumulationDOF::FApertureSamplerProgress& GetProgress() const` — Get current progress information.
- L477 _public function_ `void SetOnProgress(AccumulationDOF::FOnApertureSamplerProgress InDelegate)` — Set delegate for progress updates.
- L485 _public function_ `void SetOnComplete(AccumulationDOF::FOnApertureSamplerComplete InDelegate)` — Set delegate for completion notification.
- L502 _public prototype_ `void SaveSampleImage(int32 SampleIndex, const FString& Directory, const FString& Prefix);` — Save last rendered aperture sample to disk. @param SampleIndex - Index of sample to save (used for filename suffix) @param Directory   - Output directory (relative to project or absolute) @param Prefix       Filename prefix
- L510 _public prototype_ `void SaveFinalImage(const FString& Directory, const FString& Prefix);` — Save final accumulated frame to disk. @param Directory - Output directory @param Prefix    - Filename prefix
- L520 _public prototype_ `void AccumulateExternalSample( int32 SampleIndex, const FVector2f& ApertureOffsetCm, const FVector3f& SpectralWeight = FVector3f(1.0f, 1.0f, 1.0f) );` — Manually accumulate a sample that was rendered externally to SampleRT. Used by MRQ which renders via its own view family. @param SampleIndex      - Index of the sample @param ApertureOffsetCm - Aperture offset in cm @param SpectralWeight   - RGB weight
- L529 _public prototype_ `void FinalizeAccumulation();` — Normalize after all samples have been accumulated.
- L534 _public prototype_ `FVector2f GetApertureOffset(int32 SampleIndex) const;` — Get aperture offset for a specific sample index, per the surrent sampling pattern.
- L540 _public prototype_ `FVector2f GetJitterOffset(int32 SampleIndex) const;` — Get AA jitter offset for the given specific sample index. Returns jitter in [-0.5, 0.5] pixel units and using the r.AccumulationDOF.JitterAA.Sequence cvar sequence.
- L551 _public prototype_ `FVector2D GetJitterForProjectionMatrix(int32 SampleIndex, const FIntPoint& Resolution) const;` — Get AA jitter in clip-space format for HackAddTemporalAAProjectionJitter(). This should be called after view creation and applied via View->ViewMatrices.HackAddTemporalAAProjectionJitter(). @param SampleIndex - Index of the aperture sample @param Resolution  - Render target resolution @return Jitter offset in clip-space units (matching MRQ convention with negated Y)
- L556 _public function_ `const TArray<FVector2f>& GetApertureOffsetsRef() const` — Get array ref. of aperture offsets.
- L571 _public prototype_ `bool ComputeProjectionMatrix( int32 SampleIndex, float FocusDistanceOverride, const FMinimalViewInfo& InCameraView, FMatrix& OutMatrix ) const;` — Compute off-axis projection matrix for a sample. @param SampleIndex           - Index of the aperture sample @param FocusDistanceOverride - Override focus distance (-1 to not override) @param InCameraView          - Camera view info; the near clip plane is read from here. @param OutMatrix             - Output projection matrix @return true if computation succeeded
- L587 _public prototype_ `AccumulationDOF::FApertureSampleParams ComputeSampleParams(int32 SampleIndex, float FocusDistanceOverride = -1.0f) const;` — Compute sample parameters for UApertureSamplingRenderer. Centralizes the projection, focus, and lens aberration calculations. @param SampleIndex           - Index of the aperture sample @param FocusDistanceOverride - Override focus distance (-1 to not override) @return Sample parameters struct
- L597 _public prototype_ `float ComputeSpectralFocusDistance(float NominalFocusCm, float NormalizedSpectralPosition) const;` — Compute spectral focus distance for axial chromatic aberration. @param NominalFocusCm             - Camera's nominal focus distance in cm @param NormalizedSpectralPosition - Position in [0,1]: [blue end, red end] @return Focus distance for this band in cm
- L606 _public prototype_ `FVector3f ComputeSpectralWeight(float NormalizedSpectralPosition) const;` — Computes spectral weight for axial chromatic aberration. @param NormalizedSpectralPosition - Position in [0,1]: [blue end, red end] @return RGB weight vector (R+G+B = 1)
- L611 _public prototype_ `int32 GetEffectiveBands() const;` — @return The effective number of spectral bands for axial CA.
- L616 _public prototype_ `int32 GetTotalIterations() const;` — @return The total number of iterations (may be more than num samples if aberrations require it)
- L621 _public function_ `FVector3f GetTotalSpectralWeightPerChannel() const` — Get the total spectral weight per channel for normalization.
- L629 _private prototype_ `void SetupRenderTargets();` — Setup render targets based on configuration.
- L632 _private prototype_ `void GenerateApertureOffsets();` — Generate aperture sample offsets based on pattern.
- L635 _private prototype_ `void InitializeRenderer();` — Initialize the internal renderer.
- L638 _private prototype_ `void RenderSample(int32 SampleIndex, const FVector2f& ApertureOffsetCm, float FocusDistanceOverride = -1.0f);` — Render a single sample using UApertureSamplingRenderer.
- L641 _private prototype_ `void AccumulateSampleInternal( int32 SampleIndex, const FVector2f& ApertureOffsetCm, const FVector3f& SpectralWeight );` — Accumulate sample into accumulation buffer (internal path).
- L648 _private prototype_ `void NormalizeAccumulation(float TotalWeightSum);` — Normalize accumulated result.
- L651 _private prototype_ `void ApplySpectralLateralCA();` — Apply spectral lateral chromatic aberration.
- L654 _private prototype_ `void ApplyMedianFilter();` — Apply median filter.
- L657 _private prototype_ `void ClearAccumulationBuffers();` — Clear accumulation buffers.
- L660 _private prototype_ `void CacheCurrentState();` — Cache current state for change detection.
- L663 _private prototype_ `bool HasSignificantChanges() const;` — Check if camera changed significantly (to restart the capture if so).
- L666 _private prototype_ `void NotifyProgress();` — Notify progress delegate.
- L669 _private prototype_ `void PrecomputeSpectralWeights();` — Pre-compute total spectral weights for normalization.
- L674 _private member_ `AccumulationDOF::FApertureSamplerConfig Config;` — Determines the behavior of the sampler
- L677 _private member_ `AccumulationDOF::FApertureSamplerCameraState CameraState;` — Information about the camera being rendered
- L680 _private member_ `AccumulationDOF::FApertureSamplerProgress Progress;` — How far along we are in sample render accumulation
- L683 _private member_ `bool bIsInitialized = false;` — Initialization flag
- L686 _private member_ `bool bHasValidAccumulatedData = false;` — Used to know if re-filtering would be valid
- L690 _private member_ `TObjectPtr<UTextureRenderTarget2D> SampleRT;` — `UPROPERTY(Transient)` — RT to hold aperture sample render
- L694 _private member_ `TObjectPtr<UTextureRenderTarget2D> AccumA;` — `UPROPERTY(Transient)` — Ping pong RT A
- L698 _private member_ `TObjectPtr<UTextureRenderTarget2D> AccumB;` — `UPROPERTY(Transient)` — Ping pong RT B
- L702 _private member_ `TObjectPtr<UTextureRenderTarget2D> PrefilterRT;` — `UPROPERTY(Transient)` — Caches the last accumulation to re-filter without re-rendering
- L706 _private member_ `TObjectPtr<UTextureRenderTarget2D> PostProcessRT;` — `UPROPERTY(Transient)` — Intermediate RT for post-processing when overscan cropping is needed
- L709 _private member_ `TArray<FVector2f> ApertureOffsetsCm;` — Array of aperture offsets to render from per the jitter pattern
- L712 _private member_ `FVector3f TotalSpectralWeightPerChannel = FVector3f(0.0f);` — Axial chromatic aberration weight per channel cache
- L715 _private member_ `float AccumulatedWeightSum = 0.0f;` — Accumulated weight sum
- L718 _private member_ `FTransform LastCameraTransform;` — Last camera transform for change detection
- L721 _private member_ `float LastFocusDistance = 0.0f;` — Last focus distance for change detection
- L724 _private member_ `float LastAperture = 0.0f;` — Last aperture for change detection
- L727 _private member_ `float LastFocalLength = 0.0f;` — Last focal length for change detection
- L730 _private member_ `bool bLastChangeDetectionValid = false;` — Whether cached change detection values are valid
- L734 _private member_ `TObjectPtr<UApertureSamplingRenderer> Renderer;` — `UPROPERTY(Transient)` — Internal renderer.
- L738 _private member_ `TObjectPtr<UTexture2D> BokehTextureRef;` — `UPROPERTY(Transient)` — BokehTexture reference (Config.BokehTexture points to same object)
- L741 _private member_ `AccumulationDOF::FOnApertureSamplerProgress OnProgressDelegate;` — Progress update delegate
- L744 _private member_ `AccumulationDOF::FOnApertureSamplerComplete OnCompleteDelegate;` — Frame completion delegate
- L747 _private member_ `int32 SavedDOFGatherResDivisor = 2;` — Saved value of r.DOF.Gather.ResolutionDivisor before we changed it
- L750 _private member_ `bool bModifiedDOFGatherResDivisor = false;` — Whether we modified the DOF gather resolution divisor CVar

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace AccumulationDOF`
- L262 _delegate_ `DECLARE_DELEGATE_OneParam(FOnApertureSamplerProgress, const FApertureSamplerProgress&);` — Delegate for progress updates during sampling.
- L262 _prototype_ `DECLARE_DELEGATE_OneParam(FOnApertureSamplerProgress, const FApertureSamplerProgress&);` (scope `AccumulationDOF`) — Delegate for progress updates during sampling.
- L265 _delegate_ `DECLARE_DELEGATE_OneParam(FOnApertureSamplerComplete, UTextureRenderTarget2D* );` — Delegate for completion notification.
- L265 _prototype_ `DECLARE_DELEGATE_OneParam(FOnApertureSamplerComplete, UTextureRenderTarget2D* );` (scope `AccumulationDOF`) — Delegate for completion notification.

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Rendering/ApertureSamplingRenderer.h` (Private)


#### struct `AccumulationDOF::FApertureSampleParams`  
`struct FApertureSampleParams`  
_L26-89_
- desc: Encapsulates all rendering configuration for one sample.
- L29 _public member_ `FVector CameraLocation = FVector::ZeroVector;` — Base camera world location
- L32 _public member_ `FRotator CameraRotation = FRotator::ZeroRotator;` — Base camera world rotation
- L35 _public member_ `FVector2f ApertureOffsetCm = FVector2f::ZeroVector;` — Aperture sample offset from optical axis in cm.
- L38 _public member_ `FMatrix ProjectionMatrix = FMatrix::Identity;` — Pre-computed off-axis projection matrix for this sample
- L43 _public member_ `float FOVDegrees = 90.0f;` — On-axis horizontal field of view in degrees. Default mirrors FSceneViewInitOptions::FOV's own default (90).
- L46 _public member_ `float FocalLengthMm = 35.0f;` — Focal length in mm
- L49 _public member_ `float FStop = 2.8f;` — F-stop (aperture)
- L52 _public member_ `float FocusDistanceCm = 100.0f;` — Focus distance in cm
- L55 _public member_ `float SensorWidthMm = 36.0f;` — Sensor width in mm
- L58 _public member_ `float SensorHeightMm = 24.0f;` — Sensor height in mm
- L61 _public member_ `float SqueezeFactor = 1.0f;` — Anamorphic squeeze factor
- L64 _public member_ `float DOFSplatsFStop = 0.0f;` — DOFSplats f-stop (0 = disabled)
- L67 _public member_ `bool bForceNeutralBokeh = false;` — Force neutral bokeh (no petzval, circular aperture, no cat's eye)
- L70 _public member_ `bool bWorldIsPaused = true;` — Whether world is paused (freezes temporal history)
- L73 _public member_ `EAntiAliasingMethod AntiAliasing = EAntiAliasingMethod::AAM_None;` — Anti-aliasing method to use
- L76 _public member_ `bool bEnableMotionBlur = false;` — Whether to enable motion blur
- L79 _public member_ `bool bUseRayTracing = true;` — Whether to use ray tracing
- L82 _public member_ `int32 SampleIndex = INDEX_NONE;` — Sample index for debug/logging and temporal history. INDEX_NONE if invalid.
- L85 _public member_ `float DOFSensorScale = 1.0f;` — DOF sensor scale for tiling support (1.0 = no tiling)
- L88 _public member_ `bool bAllowSceneFringe = false;` — Whether to allow SceneFringe (lateral CA) during capture

#### struct `AccumulationDOF::FApertureSamplingConfig`  
`struct FApertureSamplingConfig`  
_L95-114_
- desc: Configuration for the aperture sampling renderer. Applies to all samples.
- L98 _public member_ `FIntPoint Resolution = FIntPoint(1920, 1080);` — Output resolution
- L101 _public member_ `ESceneCaptureSource CaptureSource = ESceneCaptureSource::SCS_FinalColorHDR;` — Final capture source
- L104 _public member_ `FEngineShowFlags ShowFlags = FEngineShowFlags(ESFIM_Game);` — ShowFlags
- L107 _public member_ `bool bDisableEngineDOF = true;` — Should realtime DOF be disabled or not
- L110 _public member_ `float ScreenPercentageFraction = -1.0f;` — Screen percentage fraction (0.1 to 4.0). Negative = use CVar.
- L113 _public member_ `EViewModeIndex ViewModeIndex = VMI_Lit;` — View mode for rendering (Lit, Detail Lighting, etc.)

#### class `UApertureSamplingRenderer`  
`class UApertureSamplingRenderer : public UObject`  
_L122-248_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Renderer for aperture-sampled depth of field.
- L128 _public prototype_ `UApertureSamplingRenderer();`
- L131 _public prototype_ `void Initialize(UWorld* InWorld, FSceneViewStateInterface* InExposureViewState = nullptr);` — Initialize with world reference. Must be called after construction.
- L134 _public prototype_ `void Shutdown();` — Cleanup resources.
- L140 _public prototype_ `void SetupRenderTargets(const AccumulationDOF::FApertureSamplingConfig& Config);` — Initialize/update render targets based on configuration. Must be called before RenderSample if resolution changed.
- L152 _public prototype_ `bool RenderSample( const AccumulationDOF::FApertureSampleParams& Params, UTextureRenderTarget2D* OutputRT, UCineCameraComponent* CineCamera = nullptr, float* OutCapturedSceneFringeIntensity = nullptr );` — Render a single aperture sample. @param Params     - Sample parameters (location, projection, etc.) @param OutputRT   - Render target to write result to (via SVE) @param CineCamera - Optional camera component for PP settings (can be null) @param OutCapturedSceneFringeIntensity - Optional output for captured SceneFringe value @return true on success
- L173 _public prototype_ `bool RenderWithInjection( UTextureRenderTarget2D* AccumulatedRT, UTextureRenderTarget2D* OutputRT, UCineCameraComponent* CineCamera, ESceneCaptureSource CaptureSource, bool bAllowSceneFringe = false, bool bEnableMotionBlur = false, bool bWorldIsPaused = false, float ProgressBarFraction = -1.0f );` — Render scene with injection of accumulated texture into post-processing pipeline. @param AccumulatedRT         - The accumulated DOF result to inject @param OutputRT              - Render target to write the final post-processed result to @param CineCamera            - Camera component for PP settings and location @param CaptureSource         - What stage of post-processing to capture @param bAllowSceneFringe     - Whether to allow engine lateral chromatic aberration or not @param bEnableMotionBlur     - Whether to enable motion blur during injection or not @param bWorldIsPaused        - Whether temporal history updates are frozen or not @param ProgressBarFraction   - Optional progress bar value (0-1, -1 to disable) @return true on success
- L185 _public function_ `const AccumulationDOF::FApertureSamplingConfig& GetConfig() const` — Get the current configuration.
- L191 _public prototype_ `bool IsInitialized() const;` — Check if renderer is properly initialized.
- L194 _public function_ `UTextureRenderTarget2D* GetInternalRenderTarget() const` — Get the internal render target (for debugging).
- L202 _private prototype_ `TSharedRef<FSceneViewFamilyContext> CreateViewFamily( FRenderTarget* RenderTarget, const AccumulationDOF::FApertureSampleParams& Params ) const;` — Create FSceneViewFamily with our configuration.
- L208 _private prototype_ `FSceneViewInitOptions CreateViewInitOptions( const AccumulationDOF::FApertureSampleParams& Params, FSceneViewFamily* ViewFamily );` — Create FSceneViewInitOptions from parameters.
- L214 _private prototype_ `FSceneView* CreateSceneView( const FSceneViewInitOptions& InitOptions, FSceneViewFamily* ViewFamily, const AccumulationDOF::FApertureSampleParams& Params, UCineCameraComponent* CineCamera );` — Create and configure FSceneView.
- L222 _private prototype_ `void ConfigureViewPostProcess( FSceneView* View, const AccumulationDOF::FApertureSampleParams& Params, UCineCameraComponent* CineCamera ) const;` — Apply post-process settings from camera and configure for capture.
- L231 _private member_ `TWeakObjectPtr<UWorld> World = nullptr;` — World reference (weak to avoid preventing GC during level transitions)
- L234 _private member_ `AccumulationDOF::FApertureSamplingConfig CurrentConfig;` — Current configuration
- L237 _private member_ `FSceneViewStateReference SceneViewState;` — Scene view state shared between aperture samples
- L240 _private member_ `FSceneViewStateInterface* ExposureViewState = nullptr;` — External view state for shared exposure (if set, shares exposure history with another view)
- L244 _private member_ `TObjectPtr<UTextureRenderTarget2D> InternalRT = nullptr;` — `UPROPERTY(Transient)` — Internal render target for scene capture output
- L247 _private member_ `bool bIsInitialized = false;` — Tracks if we've been initialized

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace AccumulationDOF`

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.h` (Private)


#### class `FAccumulationDOFAccumulateVS`  
`class FAccumulationDOFAccumulateVS : public FGlobalShader`  
_L16-28_
- inherits: `FGlobalShader`
- desc: Vertex shader for aperture sample accumulation pass
- L18 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulationDOFAccumulateVS);`
- L19 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulationDOFAccumulateVS, FGlobalShader);`
- L22 _private function_ `END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `FAccumulationDOFAccumulatePS`  
`class FAccumulationDOFAccumulatePS : public FGlobalShader`  
_L33-101_
- inherits: `FGlobalShader`
- desc: Pixel shader for aperture sample accumulation pass
- L35 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulationDOFAccumulatePS);`
- L36 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulationDOFAccumulatePS, FGlobalShader);`
- L39 _private function_ `SHADER_PARAMETER_RDG_TEXTURE(Texture2D, PrevAccumTexture) SHADER_PARAMETER_SAMPLER(SamplerState, PrevAccumSampler) SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SampleTexture) SHADER_PARAMETER_SAMPLER(SamplerState, SampleSampler) SHADER_PARAMETER_TEXTURE(Texture2D, BokehTexture) SHADER_PARAMETER_SAMPLER(SamplerState, BokehSampler) SHADER_PARAMETER(FVector2f, ApertureOffsetCm) SHADER_PARAMETER(float, ApertureRadiusCm) SHADER_PARAMETER(int32, BokehWeightChannel) SHADER_PARAMETER(int32, BokehUseTint) SHADER_PARAMETER(float, BokehTintStrength) SHADER_PARAMETER(int32, BokehEnabled)`

#### class `FAccumulationDOFNormalizeVS`  
`class FAccumulationDOFNormalizeVS : public FGlobalShader`  
_L106-118_
- inherits: `FGlobalShader`
- desc: Vertex shader for normalization pass
- L108 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulationDOFNormalizeVS);`
- L109 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulationDOFNormalizeVS, FGlobalShader);`
- L112 _private function_ `END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `FAccumulationDOFNormalizePS`  
`class FAccumulationDOFNormalizePS : public FGlobalShader`  
_L123-139_
- inherits: `FGlobalShader`
- desc: Pixel shader for normalizing accumulated weighted samples
- L125 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulationDOFNormalizePS);`
- L126 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulationDOFNormalizePS, FGlobalShader);`
- L129 _private function_ `SHADER_PARAMETER_RDG_TEXTURE(Texture2D, AccumTexture) SHADER_PARAMETER_SAMPLER(SamplerState, AccumSampler) SHADER_PARAMETER(float, InvWeightSum) RENDER_TARGET_BINDING_SLOTS() END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### struct `AccumulationDOF::FAccumulateSampleParams`  
`struct FAccumulateSampleParams`  
_L148-236_
- desc: Parameters for accumulating aperture samples with bokeh weighting. Consolidates all shader parameters for AccumulateSample.
- L151 _public member_ `FVector2f ApertureOffsetCm = FVector2f::ZeroVector;` — Aperture sample offset from optical axis in cm
- L154 _public member_ `float ApertureRadiusCm = 0.0f;` — Aperture radius in cm
- L157 _public member_ `int32 BokehWeightChannel = 0;` — Bokeh weight channel (0 = Alpha, 1 = Luminance)
- L160 _public member_ `bool bUseTint = false;` — Whether to use bokeh tint
- L163 _public member_ `float TintStrength = 0.0f;` — Bokeh tint strength (0-1)
- L166 _public member_ `bool bBokehEnabled = false;` — Whether bokeh texture is enabled
- L169 _public member_ `float Petzval = 0.0f;` — Petzval field curvature coefficient
- L172 _public member_ `float PetzvalFalloffPower = 1.0f;` — Petzval falloff power
- L175 _public member_ `FVector2f PetzvalExclusionBoxExtents = FVector2f::ZeroVector;` — Petzval exclusion box extents
- L178 _public member_ `float PetzvalExclusionBoxRadius = 0.0f;` — Petzval exclusion box corner radius
- L181 _public member_ `float SqueezeFactor = 1.0f;` — Anamorphic squeeze factor
- L184 _public member_ `float BokehEdgeSoftness = 0.0f;` — Bokeh edge softness (0 = hard, 1 = very soft)
- L187 _public member_ `float BarrelRadiusCm = 0.0f;` — Barrel radius in cm for cat's eye vignetting
- L190 _public member_ `float BarrelLengthCm = 0.0f;` — Barrel length in cm for cat's eye vignetting
- L193 _public member_ `FVector2f SensorHalfSizeCm = FVector2f::ZeroVector;` — Half sensor size in cm for ray direction calculation
- L196 _public member_ `float FocalLengthCm = 0.0f;` — Focal length in cm for ray direction calculation
- L199 _public member_ `float FocusDistanceCm = 0.0f;` — Focus distance in cm for focus plane calculation
- L202 _public member_ `int32 DiaphragmBladeCount = 0;` — Number of diaphragm blades (0 = circular)
- L205 _public member_ `float DiaphragmRotationRad = 0.0f;` — Diaphragm rotation in radians
- L208 _public member_ `int32 BokehShape = 0;` — Bokeh shape: 0=Circle, 1=StraightBlades, 2=RoundedBlades
- L211 _public member_ `float CocRadiusToCircumscribedRadius = 1.0f;` — Scale factor for circumscribed radius
- L214 _public member_ `float CocRadiusToIncircleRadius = 1.0f;` — Scale factor for incircle radius
- L217 _public member_ `float DiaphragmBladeRadius = 0.0f;` — Blade arc radius for rounded blades
- L220 _public member_ `float DiaphragmBladeCenterOffset = 0.0f;` — Blade arc center offset for rounded blades
- L223 _public member_ `FVector3f SpectralWeight = FVector3f(1.0f, 1.0f, 1.0f);` — Spectral weight for axial chromatic aberration (1,1,1 = no CA)
- L226 _public member_ `float AntiAliasingWeight = 1.0f;` — AA reconstruction weight
- L229 _public member_ `FVector2f SubpixelOffset = FVector2f(0.5f, 0.5f);` — Sub-pixel offset for bilinear splatting [0,1]
- L232 _public member_ `FVector2f TexelSize = FVector2f(0.0f, 0.0f);` — Texel size (1/width, 1/height) for UV offset calculation
- L235 _public member_ `float ComaStrength = 0.0f;` — Coma aberration strength (Seidel W131), normalized

#### class `FAccumulationDOFCopyPS`  
`class FAccumulationDOFCopyPS : public FGlobalShader`  
_L373-394_
- inherits: `FGlobalShader`
- desc: Pixel shader for copying with format conversion
- L375 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulationDOFCopyPS);`
- L376 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulationDOFCopyPS, FGlobalShader);`
- L379 _private function_ `SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SourceTexture) SHADER_PARAMETER_SAMPLER(SamplerState, SourceSampler)`

#### class `FAccumulationDOFMedianVS`  
`class FAccumulationDOFMedianVS : public FGlobalShader`  
_L399-411_
- inherits: `FGlobalShader`
- desc: Vertex shader for median filter pass
- L401 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulationDOFMedianVS);`
- L402 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulationDOFMedianVS, FGlobalShader);`
- L405 _private function_ `END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `FAccumulationDOFMedianPS`  
`class FAccumulationDOFMedianPS : public FGlobalShader`  
_L416-432_
- inherits: `FGlobalShader`
- desc: Pixel shader for 3x3 median filter (noise reduction)
- L418 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulationDOFMedianPS);`
- L419 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulationDOFMedianPS, FGlobalShader);`
- L422 _private function_ `SHADER_PARAMETER_RDG_TEXTURE(Texture2D, InputTexture) SHADER_PARAMETER_SAMPLER(SamplerState, InputSampler) SHADER_PARAMETER(FVector2f, InputTexelSize) RENDER_TARGET_BINDING_SLOTS() END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `FAccumulationDOFInjectVS`  
`class FAccumulationDOFInjectVS : public FGlobalShader`  
_L441-453_
- inherits: `FGlobalShader`
- desc: Vertex shader for scene color injection pass
- L443 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulationDOFInjectVS);`
- L444 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulationDOFInjectVS, FGlobalShader);`
- L447 _private function_ `END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `FAccumulationDOFInjectPS`  
`class FAccumulationDOFInjectPS : public FGlobalShader`  
_L458-490_
- inherits: `FGlobalShader`
- desc: Pixel shader for injecting accumulated DOF result into scene color
- L460 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulationDOFInjectPS);`
- L461 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulationDOFInjectPS, FGlobalShader);`
- L464 _private function_ `SHADER_PARAMETER_RDG_TEXTURE(Texture2D, AccumulatedTexture) SHADER_PARAMETER_SAMPLER(SamplerState, AccumulatedSampler) SHADER_PARAMETER(FVector4f, ViewportRect) SHADER_PARAMETER(FVector2f, AccumulatedTextureSize) SHADER_PARAMETER(FVector2f, OutputTextureSize) SHADER_PARAMETER(float, ProgressBarFraction) SHADER_PARAMETER(uint32, bDrawProgressBar) SHADER_PARAMETER(FVector2f, ViewportSize) SHADER_PARAMETER(float, OverscanFraction) SHADER_PARAMETER(uint32, bDrawPreviewLabel) SHADER_PARAMETER(uint32, bIsFrozen) SHADER_PARAMETER(uint32, bApplyAspectFit) SHADER_PARAMETER_TEXTURE(Texture2D, MiniFontTexture) SHADER_PARAMETER(uint32, FrameCounter) SHADER_PARAMETER(float, DitherStrength)`

#### class `FAccumulationDOFLateralCAVS`  
`class FAccumulationDOFLateralCAVS : public FGlobalShader`  
_L499-511_
- inherits: `FGlobalShader`
- desc: Vertex shader for lateral CA UV shift pass
- L501 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulationDOFLateralCAVS);`
- L502 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulationDOFLateralCAVS, FGlobalShader);`
- L505 _private function_ `END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `FAccumulationDOFLateralCAPS`  
`class FAccumulationDOFLateralCAPS : public FGlobalShader`  
_L517-535_
- inherits: `FGlobalShader`
- desc: Pixel shader for applying spectral lateral chromatic aberration. Uses multi-band spectral sampling for smooth rainbow fringes.
- L519 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulationDOFLateralCAPS);`
- L520 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulationDOFLateralCAPS, FGlobalShader);`
- L523 _private function_ `SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SampleTexture) SHADER_PARAMETER_SAMPLER(SamplerState, SampleSampler) SHADER_PARAMETER(float, IntensityUV)`

#### Free symbols / members of external scopes

- L141 _namespace_ `namespace AccumulationDOF`
- L242 _prototype_ `void AccumulateSample( FRHICommandListImmediate& RHICmdList, FTextureRenderTargetResource* PrevAccumRT, FTextureRenderTargetResource* SampleRT, FTextureRenderTargetResource* OutputRT, FRHITexture* BokehTextureRHI, FRHISamplerState* BokehSamplerRHI, const FAccumulateSampleParams& Params );` (scope `AccumulationDOF`) — High-level accumulation function Accumulates a sample into the accumulation buffer using custom shader with bokeh weighting
- L256 _prototype_ `void NormalizeAccumulation( FRHICommandListImmediate& RHICmdList, FTextureRenderTargetResource* AccumRT, FTextureRenderTargetResource* OutputRT, float InvWeightSum );` (scope `AccumulationDOF`) — High-level normalization function Normalizes accumulated samples by total weight sum
- L266 _prototype_ `void CopyTexture( FRHICommandListImmediate& RHICmdList, FTextureRenderTargetResource* SourceRT, FTextureRenderTargetResource* OutputRT );` (scope `AccumulationDOF`) — Copies source texture to output texture.
- L282 _prototype_ `void CopyCropped( FRHICommandListImmediate& RHICmdList, FTextureRenderTargetResource* SourceRT, FTextureRenderTargetResource* OutputRT, const FVector2f& SourceUVMin, const FVector2f& SourceUVMax );` (scope `AccumulationDOF`) — Copies a cropped region from source texture to output texture. Used for overscan cropping where source is larger than destination. @param RHICmdList  - RHI command list @param SourceRT    - Source render target (overscanned) @param OutputRT    - Output render target (nominal size) @param SourceUVMin - Minimum UV coordinates of source region to copy @param SourceUVMax - Maximum UV coordinates of source region to copy
- L293 _prototype_ `void ApplyMedianFilter( FRHICommandListImmediate& RHICmdList, FTextureRenderTargetResource* InputRT, FTextureRenderTargetResource* OutputRT );` (scope `AccumulationDOF`) — Applies 3x3 median filter for noise reduction (per Life of a Bokeh - Siggraph 2018)
- L318 _prototype_ `void InjectToSceneColor( FRDGBuilder& GraphBuilder, FRDGTextureRef AccumulatedRDG, FRDGTextureRef OutputRDG, const FIntRect& ViewRect, float ProgressBarFraction = -1.0f, bool bDrawProgressBar = false, float OverscanFraction = 0.0f, bool bDrawPreviewLabel = false, bool bIsFrozen = false, bool bApplyAspectFit = true, const FLensDistortionLUT* LensDistortionLUT = nullptr );` (scope `AccumulationDOF`) — Inject accumulated DOF texture into scene color using RDG Used by the scene view extension to replace scene color with accumulated result @param GraphBuilder        - The RDG builder @param AccumulatedRDG      - The accumulated texture @param OutputRDG           - The output scene color texture @param ViewRect            - The viewport rectangle @param ProgressBarFraction - Progress bar fill fraction (0.0 to 1.0), or negative to disable @param bDrawProgressBar    - Whether to draw the progress bar overlay or not @param OverscanFraction    - Overscan fraction for progress bar positioning @param bDrawPreviewLabel   - Whether to draw "Accumulation DOF Preview" label (level editor only) @param bIsFrozen           - Whether preview is frozen (appends "(FROZEN)" to label) @param bApplyAspectFit     - When true, letterbox/pillarbox if the accumulator and viewport aspects differ. Set false when the caller has already shrunk the ViewRect to the target aspect. @param LensDistortionLUT   - When non-null and IsEnabled(), the shader applies the undistorting displacement to warp the accumulated buffer through the lens.
- L341 _prototype_ `void CopyWithProgressBar( FRHICommandListImmediate& RHICmdList, FTextureRenderTargetResource* SourceRT, FTextureRenderTargetResource* OutputRT, float Progress );` (scope `AccumulationDOF`) — Copies source texture to output texture with optional progress bar overlay. Used for preview mode without post-processing. @param RHICmdList - RHI command list @param SourceRT   - Source render target @param OutputRT   - Output render target @param Progress   - Progress bar fill fraction [0, 1]
- L359 _prototype_ `void ApplyLateralCA( FRHICommandListImmediate& RHICmdList, FTextureRenderTargetResource* SampleRT, FTextureRenderTargetResource* OutputRT, float IntensityUV, float StartOffset, const FVector2f& Center );` (scope `AccumulationDOF`) — Apply spectral lateral chromatic aberration. Uses multi-band spectral sampling for smooth rainbow fringes instead of simple RGB split. @param RHICmdList  - RHI command list @param SampleRT    - Input sample render target @param OutputRT    - Output render target (receives result with spectral chromatic aberration) @param IntensityUV - Intensity in UV space (SceneFringeIntensity / min dimension) @param StartOffset - Per-axis threshold where effect begins [0,1] @param Center      - Center point in UV space

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Utils/AccumulationDOFMath.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace AccumulationDOFMath`
- L17 _variable_ `constexpr float ApertureSampleMargin = 0.02f;` (scope `AccumulationDOFMath`) — Inward margin applied to aperture radius when generating sample positions. Prevents outer ring samples from landing exactly on the boundary where they may fail validity tests. Expressed as fraction of radius (0.02 = 2%).
- L25 _variable_ `constexpr int32 RingSamplesIncrement = 6;` (scope `AccumulationDOFMath`) — Number of samples added per ring increment. Ring i has (i+1) * RingSamplesIncrement samples. Ideally 2*pi (~6.28) for equal radial/tangential spacing, using 6 as closest integer.
- L35 _variable_ `constexpr float GoldenAngle = 2.39996322972865332f;` (scope `AccumulationDOFMath`) — Golden angle in radians for inter-ring rotation useful in breaking potential radial patterns. Comes from the golden ratio phi = (1+sqrt(5))/2 = L/S, with L + S = 1 (the circle normalized to unit circumference) We use the shorter segment S = 1/phi^2. The rotation angle being that fraction of 2*pi radians: 2*pi * (1/phi^2) = 137.507... deg, or 2.399... rad.
- L38 _function_ `FORCEINLINE float MmToCm(float Mm)` (scope `AccumulationDOFMath`) — Convert millimeters to centimeters
- L44 _function_ `FORCEINLINE float CmToMm(float Cm)` (scope `AccumulationDOFMath`) — Convert centimeters to millimeters
- L50 _function_ `FORCEINLINE float GetApertureRadiusCm(float FocalLengthMm, float FStop)` (scope `AccumulationDOFMath`) — Calculate aperture radius in cm from focal length (mm) and f-stop
- L70 _function_ `FORCEINLINE float ComputeSphericalAberrationShift( const FVector2f& ApertureOffsetCm, float ApertureRadiusCm, float FocalLengthCm, float SphericalAberrationCm)` (scope `AccumulationDOFMath`) — Compute spherical aberration focus distance shift (additive) for a given aperture sample. Based on primary spherical aberration model: dZ = -(4 / (n' * NA^2)) * W040 * rho^2 @param ApertureOffsetCm - 2D offset on the aperture (in cm) @param ApertureRadiusCm - Physical aperture radius (in cm) @param FocalLengthCm    - Focal length (in cm) @param SphericalAberrationCm - Primary spherical aberration coefficient (Seidel W040) in cm @return Additive shift to apply to focus distance
- L110 _function_ `FORCEINLINE float ComputeDOFSplatsFStop( float ApertureRadiusCm, float FocalLengthMm, float BaseFraction)` (scope `AccumulationDOFMath`) — Compute the f-stop value for DOFSplats. Uses a constant f-stop for all samples based on the specified fraction of the main aperture. @param ApertureRadiusCm - Physical main aperture radius (in cm) @param FocalLengthMm    - Focal length in mm (needed for f-stop calculation) @param BaseFraction     - Fraction of main aperture diameter for DOFSplats (e.g., 0.125 = 1/8th, 1.0 = full) @return F-stop value for DOFSplats, or 0 if DOFSplats should be disabled
- L136 _prototype_ `float Halton(int32 Index, int32 Base);` (scope `AccumulationDOFMath`) — Generate Halton sequence value for given index and base. Index is 0-based.
- L142 _prototype_ `FVector2f ConcentricDiskSample(float U, float V);` (scope `AccumulationDOFMath`) — Map uniform [0,1) samples to a unit disk using Shirley-Chiu concentric disk mapping Returns point on disk with radius <= 1.0
- L152 _prototype_ `void GenerateApertureSamplesHalton(int32 NumSamples, float ApertureRadiusCm, TArray<FVector2f>& OutOffsets);` (scope `AccumulationDOFMath`) — Generate aperture sample offsets using Halton sequence for thin-lens camera. Samples are mapped to a unit disk using Shirley-Chiu concentric disk mapping. @param NumSamples       - Number of samples to generate @param ApertureRadiusCm - Aperture radius in cm @param OutOffsets       - Output array of 2D offsets
- L163 _prototype_ `void GenerateApertureSamplesRing(int32 NumRings, float ApertureRadiusCm, TArray<FVector2f>& OutOffsets);` (scope `AccumulationDOFMath`) — Generate aperture sample offsets using concentric ring pattern. Samples are arranged in rings with staggered angular offsets between rings to maximize minimum distance between samples. @param NumRings         - Number of rings (0 = center only, 1 = 1 + RingSamplesIncrement samples, 2 = 1 + 2*RingSamplesIncrement samples, etc.) @param ApertureRadiusCm - Aperture radius in cm @param OutOffsets       - Output array of 2D offsets
- L172 _prototype_ `void GenerateApertureSamplesVogel(int32 NumSamples, float ApertureRadiusCm, TArray<FVector2f>& OutOffsets);` (scope `AccumulationDOFMath`) — Generate aperture sample offsets using Vogel spiral @param NumSamples       - Number of samples to generate (uses exact count) @param ApertureRadiusCm - Aperture radius in cm @param OutOffsets       - Output array of 2D offsets
- L177 _prototype_ `int32 ComputeRingCountForSamples(int32 DesiredSamples);` (scope `AccumulationDOFMath`) — Compute the number of rings needed to achieve at least the desired sample count.
- L183 _function_ `FORCEINLINE int32 GetRingSampleCount(int32 NumRings)` (scope `AccumulationDOFMath`) — Compute total sample count for a given number of rings (includes center sample). Ring i has (i+1)*RingSamplesIncrement samples, so sum = RingSamplesIncrement*(1+2+...+N) = RingSamplesIncrement*N*(N+1)/2
- L203 _prototype_ `void ComputeSensorCorners(float SensorWidthCm, float SensorHeightCm, float FocalLengthCm, FVector OutCorners[4]);` (scope `AccumulationDOFMath`) — Compute sensor corners in camera local space @param SensorWidthCm  - Sensor width in cm @param SensorHeightCm - Sensor height in cm @param FocalLengthCm  - Focal length in cm @param OutCorners     - Output array of 4 corner positions
- L213 _prototype_ `void ComputeFocusPlaneCorners(const FVector SensorCorners[4], float FocusDistanceCm, FVector OutFocusCorners[4]);` (scope `AccumulationDOFMath`) — Compute focus plane corners by intersecting rays from aperture center through sensor corners with the focus plane at FocusDistanceCm @param SensorCorners   - 4 sensor corners in camera local space @param FocusDistanceCm - Focus distance in cm @param OutFocusCorners - Output array of 4 focus plane corners
- L223 _prototype_ `void ComputeOffAxisFrustum( const FVector FocusCorners[4], const FVector2f& ApertureOffsetCm, float NearCm, float& OutLeft, float& OutRight, float& OutBottom, float& OutTop );` (scope `AccumulationDOFMath`) — Compute off-axis frustum bounds at the near plane for a given aperture sample offset @param FocusCorners     - 4 corners of the focus plane quad @param ApertureOffsetCm - 2D offset on the lens, in cm @param NearCm           - Near clipping plane distance @params OutLeft, OutRight, OutBottom, OutTop - Frustum bounds at near plane
- L236 _prototype_ `FMatrix BuildOffAxisProjectionMatrix( float Left, float Right, float Bottom, float Top, float NearPlane, float FarPlane );` (scope `AccumulationDOFMath`) — Build an off-axis perspective projection matrix.
- L251 _prototype_ `void ReorderSamplesForPendulum(TArray<FVector2f>& InOutOffsets);` (scope `AccumulationDOFMath`) — Reorder samples in a pendulum (forth and back) pattern to minimize perspective jumps between frames and also start and end near the center of the lens. @param InOutOffsets - Array of aperture offsets for in-place reordering.
- L260 _prototype_ `FVector2f GenerateHaltonJitter(int32 SampleIndex);` (scope `AccumulationDOFMath`) — Generate Halton 2D jitter using bases 2 and 3 for AA. @param SampleIndex - Sample index (0-based) @return 2D jitter in range [-0.5, 0.5]
- L271 _prototype_ `FVector2f GenerateSobolJitter(int32 SampleIndex, uint32 RotationSeed = 0x12345678);` (scope `AccumulationDOFMath`) — Generate Sobol 2D jitter with Cranley-Patterson rotation for AA. Uses a constant seed for temporal stability across frames. @param SampleIndex  - Sample index (0-based) @param RotationSeed - Seed for Cranley-Patterson rotation @return 2D jitter in range [-0.5, 0.5]
- L281 _prototype_ `float MitchellNetravali1D(float Distance);` (scope `AccumulationDOFMath`) — Mitchell-Netravali 1D reconstruction filter Support range: [-2, 2], returns 0 outside. @param Distance - Distance from filter center in pixels @return Filter weight
- L290 _function_ `FORCEINLINE float MitchellNetravali2D(const FVector2f& OffsetPixels)` (scope `AccumulationDOFMath`) — Separable 2D Mitchell-Netravali filter. @param OffsetPixels - 2D offset from filter center in pixel units @return Filter weight

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Utils/AccumulationDOFUtils.h` (Private)


#### struct `AccumulationDOFUtils::FBokehShapeParams`  
`struct FBokehShapeParams`  
_L19-28_
- desc: Output structure for diaphragm bokeh model computation. Used to render realistic aperture blade shapes.
- L21 _public member_ `int32 BokehShape = 0;` — 0:Circle, 1:StraightBlades, 2:RoundedBlades
- L22 _public member_ `int32 DiaphragmBladeCount = 0;` — 0 for circle, 4-16 for bladed aperture
- L23 _public member_ `float DiaphragmRotationRad = 0.0f;` — Rotation angle for blade orientation
- L24 _public member_ `float CocRadiusToCircumscribedRadius = 1.0f;`
- L25 _public member_ `float CocRadiusToIncircleRadius = 1.0f;`
- L26 _public member_ `float DiaphragmBladeRadius = 0.0f;` — Blade arc radius (for rounded blades)
- L27 _public member_ `float DiaphragmBladeCenterOffset = 0.0f;` — Blade arc center offset (for rounded blades)

#### struct `AccumulationDOFUtils::FCameraParams`  
`struct FCameraParams`  
_L47-78_
- desc: Camera and lens parameters extracted from CineCameraComponent and PostProcessSettings. Consolidates all camera-related values needed for DOF accumulation.
- L50 _public member_ `float FocalLengthMm = 0.0f;` — Core lens parameters
- L51 _public member_ `float FocalLengthCm = 0.0f;`
- L52 _public member_ `float FStop = 2.8f;`
- L53 _public member_ `float ApertureRadiusCm = 0.0f;`
- L54 _public member_ `float FocusDistanceCm = 0.0f;`
- L57 _public member_ `float SensorWidthMm = 0.0f;` — Sensor dimensions
- L58 _public member_ `float SensorHeightMm = 0.0f;`
- L59 _public member_ `float SensorWidthCm = 0.0f;`
- L60 _public member_ `float SensorHeightCm = 0.0f;`
- L63 _public member_ `float SqueezeFactor = 1.0f;` — Anamorphic
- L66 _public member_ `float Petzval = 0.0f;` — Petzval field curvature (from PostProcessSettings)
- L67 _public member_ `float PetzvalFalloffPower = 1.0f;`
- L68 _public member_ `FVector2f PetzvalExclusionBoxExtents = FVector2f::ZeroVector;`
- L69 _public member_ `float PetzvalExclusionBoxRadius = 0.0f;`
- L72 _public member_ `float BarrelRadiusCm = 0.0f;` — Barrel occlusion (cat's eye bokeh)
- L73 _public member_ `float BarrelLengthCm = 0.0f;`
- L76 _public member_ `int32 BladeCountRaw = 4;` — Diaphragm blade settings (raw values for bokeh shape computation)
- L77 _public member_ `float MinFstop = 0.0f;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace AccumulationDOFUtils`
- L40 _prototype_ `FBokehShapeParams ComputeBokehShape(float FStop, float MinFstop, int32 BladeCountRaw);` (scope `AccumulationDOFUtils`) — Compute bokeh shape parameters from f-stop and diaphragm settings. Implements the same logic as DiaphragmDOF::FBokehModel::Compile. @param FStop         - Current f-stop value @param MinFstop      - Minimum f-stop before blades become visible @param BladeCountRaw - Raw blade count (4-16, from PP settings) @return FBokehShapeParams with computed values
- L88 _prototype_ `FCameraParams ExtractCameraParams(const UCineCameraComponent* CineCam);` (scope `AccumulationDOFUtils`) — Extract camera parameters from CineCameraComponent. Reads lens settings and merged PostProcessSettings. @param CineCam - The CineCameraComponent to extract parameters from. @return FCameraParams with all relevant values
- L98 _prototype_ `int32 OverrideLUTSizeIfNeeded(bool bShouldOverride);` (scope `AccumulationDOFUtils`) — Override engine color grading LUT size to 64 if currently smaller. Returns the original value so it can be restored later. @param bShouldOverride - Whether to apply the override @return Original LUT size value (0 if no override was applied)
- L105 _prototype_ `void RestoreLUTSize(int32 PreviousSize);` (scope `AccumulationDOFUtils`) — Restore the engine color grading LUT size to a previous value. @param PreviousSize - The LUT size to restore (from OverrideLUTSizeIfNeeded)
- L108 _variable_ `static constexpr int32 RenderingMemoryFlushBatchSize = 256;` (scope `AccumulationDOFUtils`) — Number of samples to render before releasing rendering memory to prevent OOM.
- L111 _variable_ `static constexpr int32 UIFlushBatchSize = 8;` (scope `AccumulationDOFUtils`) — Number of samples between GPU flushes for UI responsiveness during one-shot preview.
- L116 _prototype_ `void ReleaseRenderingMemory();` (scope `AccumulationDOFUtils`) — Releases rendering memory to prevent accumulation during long render loops.

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Public/AccumulationDOF.h` (Public)


#### class `FAccumulationDOFModule`  
`class FAccumulationDOFModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `static const FName MRGPassFactoryPassName;` — The name that will be given to the DOF pass that's provided to the pass factory in MRG's deferred renderer.

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Public/AccumulationDOFComponent.h` (Public)


#### class `UAccumulationDOFComponent`  
`class UAccumulationDOFComponent : public UActorComponent`  
_L23-130_
- reflection: `UCLASS(Blueprintable, ClassGroup = (Rendering), meta = (BlueprintSpawnableComponent, DisplayName = "Accumulation DOF"))`
- inherits: `UActorComponent`
- desc: Settings component for cinematic aperture-sampled depth of field. Attach to a CineCameraActor to configure DOF rendering settings for: - Movie Render Queue (via AccumulationDOF pass) - Editor viewport preview (Level Viewport >> Scalability & Performance >> Accumulation DOF)
- L28 _public function_ `UAccumulationDOFComponent()`
- L38 _public member_ `int32 NumSamples = 256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation Depth of Field", meta = (ClampMin = "1", UIMin = "1", UIMax = "32768"))` — Specifies the number of aperture samples to render (use more for better quality, but will take more time). The actual number of rendered samples may be different in order to comply with the sampling pattern.
- L47 _public member_ `float DOFSplatSize = 0.125f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation Depth of Field", meta = (DisplayName = "DOF Splat Size", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Fraction of main aperture diameter for DOF splat size (0.125 = 1/8th, 1.0 = full aperture, 0 = disabled). DOF splats add small engine DOF blur to each sample to fill gaps between sparse samples. This reduces the number of samples needed for a smooth bokeh, but will be softer at the edges than ideal.
- L51 _public member_ `bool bEnableMotionBlur = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation Depth of Field")` — Enable motion blur on the accumulated DOF result.
- L55 _public member_ `EApertureSamplingPattern SamplingPattern = EApertureSamplingPattern::Hexaweb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation Depth of Field", AdvancedDisplay)` — Aperture sampling pattern. Hexaweb is generally preferred but Vogel Spirals are pretty good too.
- L59 _public member_ `ETemporalHistoryMode TemporalHistoryMode = ETemporalHistoryMode::LastSampleOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation Depth of Field", AdvancedDisplay)` — Controls how temporal history is updated during aperture sampling. Prefer Last for now
- L63 _public member_ `bool bUseJitterAA = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation Depth of Field", AdvancedDisplay)` — Use Halton jitter AA instead of per-sample TAA. When disabled, TAA runs on each sample.
- L71 _public member_ `TObjectPtr<UTexture2D> BokehTexture = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation Depth of Field|Bokeh")` — Bokeh texture to weight aperture samples. Texture should be linear. If it has an alpha channel, you can optionally pick it as transmission mask.
- L75 _public member_ `bool bEnableBokehTexture = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation Depth of Field|Bokeh")` — Enable bokeh texture
- L79 _public member_ `EBokehWeightChannel WeightChannel = EBokehWeightChannel::Luminance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation Depth of Field|Bokeh", meta = (EditCondition = "BokehTexture != nullptr"))` — Which channel to extract weight from bokeh texture
- L83 _public member_ `float TintStrength = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation Depth of Field|Bokeh", meta = (EditCondition = "BokehTexture != nullptr", ClampMin = "0.0", ClampMax = "1.0"))` — Strength of bokeh tint application 0.0 - 1.0
- L87 _public member_ `float BokehEdgeSoftness = 0.15f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation Depth of Field|Bokeh", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Softness of bokeh edges 0.0 - 1.0. Higher values create smoother bokeh boundaries by applying a soft falloff near the aperture edge.
- L98 _public member_ `float AxialChromaticAberrationIntensity = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chromatic Aberration", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "100.0"))` — Axial chromatic aberration intensity as percentage of focus distance in %. Note: Lateral chromatic aberration uses the camera's PostProcessSettings.SceneFringeIntensity.
- L106 _public member_ `int32 AxialChromaticAberrationNumBands = 6;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chromatic Aberration", meta = (ClampMin = "3", ClampMax = "19", UIMin = "3", UIMax = "19", EditCondition = "AxialChromaticAberrationIntensity > 0"))` — Number of focal planes for axial chromatic aberration. Controls how many distinct focal distances are used across the spectrum.
- L114 _public member_ `bool bSpectralLateralChromaticAberration = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chromatic Aberration")` — Spectral (actually multi-band) lateral chromatic aberration When disabled, uses the Engine's default lateral chromatic aberration.
- L121 _public member_ `float SphericalAberration = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monochromatic Aberrations", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "100.0"))` — Primary spherical aberration coefficient (Seidel W040) in cm. Positive values cause marginal rays to focus closer than paraxial rays.
- L129 _public member_ `float ComaAberration = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monochromatic Aberrations", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Coma aberration strength (Seidel W131). Off-axis points develop comet-like tails pointing away from the optical axis. The effect increases with distance from the image center.

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Public/AccumulationDOFLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAccumulationDOF, Log, All);`

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Public/AccumulationDOFTypes.h` (Public)


#### enum `EBokehWeightChannel`  
`enum class EBokehWeightChannel : uint8`  
_L13-17_
- reflection: `UENUM()`
- desc: Options for what texture channel(s) to use to weigh the rgb values during accumulation (i.e. a transmission mask). Note: This is independent of whether the bokeh tints the rgb values or not.
- L15 _public enumerator_ `Alpha UMETA(DisplayName = "Alpha Channel")`
- L16 _public enumerator_ `Luminance UMETA(DisplayName = "RGB Luminance")`

#### enum `EApertureSamplingPattern`  
`enum class EApertureSamplingPattern : uint8`  
_L21-45_
- reflection: `UENUM()`
- desc: Aperture sampling pattern
- L29 _public enumerator_ `Halton UMETA(DisplayName = "Halton")` — Halton sequence with Shirley-Chiu disk mapping. Will use the sample count specified. Note: Shirley-Chiu produced more visually consistent results than culling the Halton square to the aperture circle.
- L38 _public enumerator_ `Hexaweb UMETA(DisplayName = "Golden Hexaweb")` — Concentric rings with staggered angular offsets. Sample distances are roughly maintained (both radially and tangentially). Actual number of samples will be picked based on completed ring sample counts, so may not use the exact number of samples requested. Note: Produces more even bokeh compared to Halton.
- L44 _public enumerator_ `Vogel UMETA(DisplayName = "Vogel Spiral")` — Vogel spiral Similar quality results as with Golden Hexaweb

#### enum `ETemporalHistoryMode`  
`enum class ETemporalHistoryMode : uint8`  
_L49-62_
- reflection: `UENUM()`
- desc: Controls how temporal history (e.g. Lumen/TAA) is updated during aperture sampling.
- L52 _public enumerator_ `AllSamplesUpdate UMETA(DisplayName = "All Samples Update")` — All samples update history.
- L55 _public enumerator_ `LastSampleOnly UMETA(DisplayName = "Last Sample Only")` — Only last sample updates history.
- L58 _public enumerator_ `FirstSampleOnly UMETA(DisplayName = "First Sample Only")` — Only first sample updates history.
- L61 _public enumerator_ `NoSamplesUpdate UMETA(DisplayName = "No Samples Update")` — No samples update history. Baseline for comparison.

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Public/MovieGraphAccumulationDOFModifierNode.h` (Public)


#### enum `EMovieGraphAccumulationDOFEnableType`  
`enum class EMovieGraphAccumulationDOFEnableType : uint8`  
_L14-21_
- reflection: `UENUM(BlueprintType)`
- desc: Specifies how the enable state of the Accumulation DOF component will be set.
- L17 _public enumerator_ `CameraActorDefault` — Use the current enable state on the camera (ie, no change is made).
- L20 _public enumerator_ `CustomValue` — Use a custom value that will be used as the enable state.

#### struct `FMovieGraphAccumulationDOFEnableState`  
`struct FMovieGraphAccumulationDOFEnableState`  
_L25-38_
- reflection: `USTRUCT(BlueprintType)`
- desc: Specifies if the enable state of the Accumulation DOF component should be set, and if so, what the value of the enable state should be.
- L29 _public prototype_ `FMovieGraphAccumulationDOFEnableState() = default;`
- L33 _public member_ `EMovieGraphAccumulationDOFEnableType Type = EMovieGraphAccumulationDOFEnableType::CameraActorDefault;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation DOF")` — How the Accumulation DOF enable state should be treated.
- L37 _public member_ `bool Value = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation DOF", meta = (EditCondition = "Type == EMovieGraphAccumulationDOFEnableType::CustomValue"))` — If the enable Type is "Custom", this is the value the enable state should be set to.

#### class `UMovieGraphAccumulationDOFModifierNode`  
`class UMovieGraphAccumulationDOFModifierNode final : public UMovieGraphSettingNode, public IMovieGraphModifierNodeInterface`  
_L44-103_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieGraphSettingNode,IMovieGraphModifierNodeInterface`
- desc: Modifies the properties on the Accumulation DOF component (on all cameras within the world).
- L49 _public prototype_ `UMovieGraphAccumulationDOFModifierNode();`
- L53 _public prototype_ `virtual FText GetNodeTitle(const bool bGetDescriptive = false) const override;`
- L54 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L55 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L56 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L61 _public prototype_ `virtual TArray<UMovieGraphModifierBase*> GetAllModifiers() const override;`
- L62 _public prototype_ `virtual bool SupportsCollections() const override;`
- L66 _public prototype_ `virtual FString GetNodeInstanceName() const override;`
- L71 _public member_ `uint8 bOverride_EnableAccumulationDepthOfField : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L74 _public member_ `uint8 bOverride_NumSamples : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L77 _public member_ `uint8 bOverride_DOFSplatSize : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (InlineEditConditionToggle))`
- L83 _public member_ `FMovieGraphAccumulationDOFEnableState EnableAccumulationDepthOfField;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation DOF", meta = (EditCondition = "bOverride_EnableAccumulationDepthOfField"))` — Whether the Accumulation DOF component should be enabled/disabled.
- L90 _public member_ `int32 NumSamples = 256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation DOF", meta = (EditCondition = "bOverride_NumSamples", ClampMin = "1", UIMin = "1", UIMax = "32768"))` — The number of samples that the Accumulation DOF component should use.
- L97 _public member_ `float DOFSplatSize = 0.125f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accumulation DOF", meta = (EditCondition = "bOverride_DOFSplatSize", DisplayName = "DOF Splat Size", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The splat size that the Accumulation DOF component should use.
- L102 _private member_ `mutable TObjectPtr<class UMovieGraphAccumulationDOFModifier> Modifier;` — `UPROPERTY(meta = (HideInActiveRenderSettings))` — The modifier associated with this node.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ACCUMULATIONDOF_API`

### `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Public/MovieGraphAccumulationDOFPass.h` (Public)


#### struct `FMovieGraphAccumulationDOFPass`  
`struct FMovieGraphAccumulationDOFPass : public UE::MovieGraph::Rendering::FMovieGraphDeferredPass`  
_L33-163_
- inherits: `UE::MovieGraph::Rendering::FMovieGraphDeferredPass`
- desc: Movie Graph deferred render pass for aperture-sampled depth of field. This pass renders multiple aperture samples with off-axis projection matrices and accumulates them using GPU shaders to produce plausible DOF. Camera parameters (focal length, aperture, focus distance) are read from the CineCameraActor being rendered by the sequence.
- L35 _public prototype_ `FMovieGraphAccumulationDOFPass();`
- L40 _protected prototype_ `virtual void Setup(TWeakObjectPtr<UMovieGraphDefaultRenderer> InRenderer, TWeakObjectPtr<UMovieGraphImagePassBaseNode> InRenderPassNode, const FMovieGraphRenderPassLayerData& InLayer) override;`
- L41 _protected prototype_ `virtual void Teardown() override;`
- L42 _protected prototype_ `virtual void Render(const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData) override;`
- L43 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L46 _protected prototype_ `virtual void UpdateRenderPassTelemetry(FMoviePipelineEndShotRenderTelemetryContext& InOutTelemetry) const override;`
- L47 _protected prototype_ `virtual TSharedRef<FSceneViewFamilyContext> CreateSceneViewFamily(const UE::MovieGraph::Rendering::FViewFamilyInitData& InInitData) const override;`
- L48 _protected prototype_ `virtual FVector2D ComputeProjectionMatrixJitter(const FVector2D& InDefaultJitter, const FIntPoint& InBackbufferResolution) const override;`
- L49 _protected prototype_ `virtual FSceneViewInitOptions CreateViewInitOptions(const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo, FSceneViewFamilyContext* InViewFamily, FSceneViewStateInterface* InViewStateInterface) const override;`
- L50 _protected prototype_ `virtual void CalculateProjectionMatrix(UE::MovieGraph::DefaultRenderer::FCameraInfo& InOutCameraInfo, FSceneViewProjectionData& InOutProjectionData, const FIntPoint InBackbufferResolution, const FIntPoint InAccumulatorResolution) const override;`
- L51 _protected prototype_ `virtual void ApplyMovieGraphOverridesToSceneView(TSharedRef<FSceneViewFamilyContext> InOutFamily, const UE::MovieGraph::Rendering::FViewFamilyInitData& InInitData, const UE::MovieGraph::DefaultRenderer::FCameraInfo& InCameraInfo) const override;`
- L52 _protected prototype_ `virtual FSceneViewStateInterface* GetSceneViewState(UMovieGraphImagePassBaseNode* ParentNodeThisFrame, int32_t TileX, int32_t TileY) override;`
- L53 _protected prototype_ `virtual void GetPreviewBannerMessages(TArray<FMovieGraphPreviewBannerMessage>& OutMessages) const override;`
- L57 _private member_ `TObjectPtr<UApertureSampler> ApertureSampler = nullptr;` — Aperture sampler that handles sample rendering and accumulation. GC-protected via AddReferencedObjects.
- L60 _private member_ `mutable int32 CurrentApertureSampleIndex = -1;` — Current sample being rendered
- L63 _private member_ `mutable float CurrentFocusDistanceOverride = -1.0f;` — Focus distance override for axial CA (negative means no override).
- L66 _private member_ `FVector3f CurrentAxialCAWeight = FVector3f(1.0f);` — RGB weight for current spectral band in axial chromatic aberration.
- L69 _private member_ `TWeakObjectPtr<UCineCameraComponent> CachedCineCameraComponent;` — Cached reference to CineCameraComponent for SVE settings.
- L72 _private member_ `TWeakObjectPtr<UAccumulationDOFComponent> CachedDOFComponent;` — Cached reference to AccumulationDOFComponent (found in CineCameraActor).
- L75 _private member_ `TSharedPtr<FAccumulationDOFSceneViewExtension, ESPMode::ThreadSafe> CaptureExtension;` — Scene View Extension for capture passes (one per aperture sample).
- L78 _private member_ `TSharedPtr<FAccumulationDOFSceneViewExtension, ESPMode::ThreadSafe> InjectionExtension;` — Scene View Extension for injection pass.
- L81 _private member_ `bool bInCapturePass = false;` — Flag to indicate we're doing a capture pass (so AddViewExtensions knows to add the capture SVE).
- L84 _private member_ `bool bInInjectionPass = false;` — Flag to indicate we're doing the injection pass (so AddViewExtensions knows to add the injection SVE).
- L87 _private member_ `bool bCameraParamsInitialized = false;` — Track whether we've initialized camera-dependent state.
- L90 _private member_ `float CachedSceneFringeIntensity = 0.0f;` — Cached SceneFringeIntensity from the first sample's SVE (blended with PP volumes).
- L93 _private member_ `TMap<FIntPoint, FSceneViewStateReference> InjectionViewStates;` — Separate view state for injection renders, keyed per tile so the injection pass keeps its own temporal history per tile.
- L96 _private member_ `TSet<FIntPoint> InjectionStatesInitialized;` — Tracks which per-tile injection view states have had their camera-cut prime applied.
- L99 _private member_ `FIntPoint CurrentTileIndex = FIntPoint(0, 0);` — Active tile index for the current Render() iteration, used by helper functions.
- L105 _private member_ `FIntPoint CurrentTileCount = FIntPoint(1, 1);` — Tile grid locked at Setup time. ADOF does not support mid-shot TileCount changes because the per-tile injection view state map (InjectionViewStates) is allocated once in Setup.
- L108 _private member_ `FIntPoint CurrentTileOverlappedPad = FIntPoint(0, 0);` — Tile overlap pad in pixels for the current Render() iteration.
- L111 _private member_ `mutable float CachedMotionBlurFraction = 0.0f;` — Cached motion blur fraction from current frame's sample state.
- L114 _private member_ `int32 SavedLUTSize = 0;` — Saved LUT size before override (0 if not overridden).
- L117 _private member_ `int32 CachedActualNumSamples = 0;` — Effective telemetry values captured while render-layer modifiers are active.
- L118 _private member_ `float CachedEffectiveDOFSplatSize = 0.f;`
- L122 _private prototype_ `AccumulationDOF::FApertureSamplerConfig BuildSamplerConfig(UMovieGraphEvaluatedConfig* InEvaluatedConfig) const;` — Build sampler config from graph settings and component.
- L125 _private prototype_ `AccumulationDOF::FApertureSamplerCameraState BuildCameraState() const;` — Build camera state from current sequence camera.
- L128 _private prototype_ `void InitializeSampler(UMovieGraphEvaluatedConfig* InEvaluatedConfig);` — Initialize the aperture sampler.
- L131 _private prototype_ `void UpdateCameraDependentState();` — Update camera-dependent state (called each frame).
- L134 _private prototype_ `UCineCameraComponent* FindCineCameraComponent() const;` — Find CineCameraComponent from MRG's camera binding.
- L137 _private prototype_ `UAccumulationDOFComponent* FindAccumulationDOFComponent();` — Find AccumulationDOFComponent on the camera actor.
- L140 _private prototype_ `float GetEffectiveDOFSplatSize() const;` — Get the DOF splat size from the component, or the default if there's no valid component.
- L143 _private prototype_ `void RenderSamples( const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData, const FResolutionAndCameraInfo& InResolutionInfo, const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InRenderTargetInitParams);` — Render all aperture samples in one temporal sample.
- L150 _private prototype_ `void RenderSingleApertureSample( int32 SampleIndex, const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData, const FResolutionAndCameraInfo& InResolutionInfo, const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InRenderTargetInitParams);` — Render a single aperture sample.
- L158 _private prototype_ `void RenderInjectionAndSubmit( const FMovieGraphTraversalContext& InFrameTraversalContext, const FMovieGraphTimeStepData& InTimeData, const FResolutionAndCameraInfo& InResolutionInfo, const UE::MovieGraph::DefaultRenderer::FRenderTargetInitParams& InRenderTargetInitParams);` — Injection pass and submit to MRG.

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAccumulationDOFMRG, Log, All);`
- L18 _namespace_ `namespace AccumulationDOF`
